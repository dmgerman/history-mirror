/* $Id: nj_s.c,v 2.7.6.6 2001/09/23 22:24:50 kai Exp $
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#include <linux/config.h>
#include <linux/init.h>
#include "hisax.h"
#include "isac.h"
#include "isdnl1.h"
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/ppp_defs.h>
#include "netjet.h"

const char *NETjet_S_revision = "$Revision: 2.7.6.6 $";

static void
nj_s_interrupt(int intno, void *dev_id, struct pt_regs *regs)
{
	struct IsdnCardState *cs = dev_id;
	u8 val, sval;

	spin_lock(&cs->lock);
	if (!((sval = bytein(cs->hw.njet.base + NETJET_IRQSTAT1)) &
		NETJET_ISACIRQ)) {
		val = NETjet_ReadIC(cs, ISAC_ISTA);
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "tiger: i1 %x %x", sval, val);
		if (val) {
			isac_interrupt(cs, val);
			NETjet_WriteIC(cs, ISAC_MASK, 0xFF);
			NETjet_WriteIC(cs, ISAC_MASK, 0x0);
		}
	}
	/* start new code 13/07/00 GE */
	/* set bits in sval to indicate which page is free */
	if (inl(cs->hw.njet.base + NETJET_DMA_WRITE_ADR) <
		inl(cs->hw.njet.base + NETJET_DMA_WRITE_IRQ))
		/* the 2nd write page is free */
		sval = 0x08;
	else	/* the 1st write page is free */
		sval = 0x04;	
	if (inl(cs->hw.njet.base + NETJET_DMA_READ_ADR) <
		inl(cs->hw.njet.base + NETJET_DMA_READ_IRQ))
		/* the 2nd read page is free */
		sval = sval | 0x02;
	else	/* the 1st read page is free */
		sval = sval | 0x01;	
	if (sval != cs->hw.njet.last_is0) /* we have a DMA interrupt */
	{
		cs->hw.njet.irqstat0 = sval;
		if ((cs->hw.njet.irqstat0 & NETJET_IRQM0_READ) != 
			(cs->hw.njet.last_is0 & NETJET_IRQM0_READ))
			/* we have a read dma int */
			read_tiger(cs);
		if ((cs->hw.njet.irqstat0 & NETJET_IRQM0_WRITE) !=
			(cs->hw.njet.last_is0 & NETJET_IRQM0_WRITE))
			/* we have a write dma int */
			write_tiger(cs);
		/* end new code 13/07/00 GE */
	}
/*	if (!testcnt--) {
		cs->hw.njet.dmactrl = 0;
		byteout(cs->hw.njet.base + NETJET_DMACTRL,
			cs->hw.njet.dmactrl);
		byteout(cs->hw.njet.base + NETJET_IRQMASK0, 0);
	}
*/
	spin_unlock(&cs->lock);
}

static int
nj_s_reset(struct IsdnCardState *cs)
{
	cs->hw.njet.ctrl_reg = 0xff;  /* Reset On */
	byteout(cs->hw.njet.base + NETJET_CTRL, cs->hw.njet.ctrl_reg);
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_timeout((10*HZ)/1000);	/* Timeout 10ms */
	cs->hw.njet.ctrl_reg = 0x40;  /* Reset Off and status read clear */
	/* now edge triggered for TJ320 GE 13/07/00 */
	byteout(cs->hw.njet.base + NETJET_CTRL, cs->hw.njet.ctrl_reg);
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_timeout((10*HZ)/1000);	/* Timeout 10ms */
	cs->hw.njet.auxd = 0;
	cs->hw.njet.dmactrl = 0;
	byteout(cs->hw.njet.base + NETJET_AUXCTRL, ~NETJET_ISACIRQ);
	byteout(cs->hw.njet.base + NETJET_IRQMASK1, NETJET_ISACIRQ);
	byteout(cs->hw.njet.auxa, cs->hw.njet.auxd);
	return 0;
}

static void
nj_s_init(struct IsdnCardState *cs)
{
	inittiger(cs);
	initisac(cs);
}

static struct card_ops nj_s_ops = {
	.init     = nj_s_init,
	.reset    = nj_s_reset,
	.release  = netjet_release,
	.irq_func = nj_s_interrupt,
};

static struct pci_dev *dev_netjet __initdata = NULL;

int __init
setup_netjet_s(struct IsdnCard *card)
{
	struct IsdnCardState *cs = card->cs;
	char tmp[64];

#ifdef __BIG_ENDIAN
#error "not running on big endian machines now"
#endif
	strcpy(tmp, NETjet_S_revision);
	printk(KERN_INFO "HiSax: Traverse Tech. NETjet-S driver Rev. %s\n", HiSax_getrev(tmp));
	if (cs->typ != ISDN_CTYPE_NETJET_S)
		return(0);

	for ( ;; ) {
		if ((dev_netjet = pci_find_device(PCI_VENDOR_ID_TIGERJET,
			PCI_DEVICE_ID_TIGERJET_300,  dev_netjet))) {
			if (pci_enable_device(dev_netjet))
				return(0);
			pci_set_master(dev_netjet);
			cs->irq = dev_netjet->irq;
			if (!cs->irq) {
				printk(KERN_WARNING "NETjet-S: No IRQ for PCI card found\n");
				return(0);
			}
			cs->hw.njet.base = pci_resource_start(dev_netjet, 0);
			if (!cs->hw.njet.base) {
				printk(KERN_WARNING "NETjet-S: No IO-Adr for PCI card found\n");
				return(0);
			}
 			/* 2001/10/04 Christoph Ersfeld, Formula-n Europe AG www.formula-n.com */
 			if ((dev_netjet->subsystem_vendor == 0x55) &&
 				(dev_netjet->subsystem_device == 0x02)) {
 				printk(KERN_WARNING "Netjet: You tried to load this driver with an incompatible TigerJet-card\n");
 				printk(KERN_WARNING "Use type=41 for Formula-n enter:now ISDN PCI and compatible\n");
 				return(0);
 			}
 			/* end new code */
			cs->hw.njet.pdev = dev_netjet;
		} else {
			printk(KERN_WARNING "NETjet-S: No PCI card found\n");
			return(0);
		}

		cs->hw.njet.auxa = cs->hw.njet.base + NETJET_AUXDATA;
		cs->hw.njet.isac = cs->hw.njet.base | NETJET_ISAC_OFF;

		cs->hw.njet.ctrl_reg = 0xff;  /* Reset On */
		byteout(cs->hw.njet.base + NETJET_CTRL, cs->hw.njet.ctrl_reg);

		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout((10*HZ)/1000);	/* Timeout 10ms */

		cs->hw.njet.ctrl_reg = 0x00;  /* Reset Off and status read clear */
		byteout(cs->hw.njet.base + NETJET_CTRL, cs->hw.njet.ctrl_reg);

		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout((10*HZ)/1000);	/* Timeout 10ms */

		cs->hw.njet.auxd = 0xC0;
		cs->hw.njet.dmactrl = 0;

		byteout(cs->hw.njet.base + NETJET_AUXCTRL, ~NETJET_ISACIRQ);
		byteout(cs->hw.njet.base + NETJET_IRQMASK1, NETJET_ISACIRQ);
		byteout(cs->hw.njet.auxa, cs->hw.njet.auxd);

		switch ( ( ( NETjet_ReadIC( cs, ISAC_RBCH ) >> 5 ) & 3 ) )
		{
			case 0 :
				break;

			case 3 :
				printk( KERN_WARNING "NETjet-S: NETspider-U PCI card found\n" );
				continue;

			default :
				printk( KERN_WARNING "NETjet-S: No PCI card found\n" );
				return 0;
                }
                break;
	}
	printk(KERN_INFO
		"NETjet-S: PCI card configured at %#lx IRQ %d\n",
		cs->hw.njet.base, cs->irq);
	if (!request_io(&cs->rs, cs->hw.njet.base, 0x100, "netjet-s isdn"))
		return 0;
	
	nj_s_reset(cs);
	cs->dc_hw_ops = &netjet_dc_ops;
	cs->irq_flags |= SA_SHIRQ;
	cs->card_ops = &nj_s_ops;
	ISACVersion(cs, "NETjet-S:");
	return 1;
}
