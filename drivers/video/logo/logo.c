
/*
 *  Linux logo to be displayed on boot
 *
 *  Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)
 *  Copyright (C) 1996,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *  Copyright (C) 2001 Greg Banks <gnb@alphalink.com.au>
 *  Copyright (C) 2001 Jan-Benedict Glaw <jbglaw@lug-owl.de>
 *  Copyright (C) 2003 Geert Uytterhoeven <geert@linux-m68k.org>
 */

#include <linux/config.h>
#include <linux/linux_logo.h>

#ifdef CONFIG_M68K
#include <asm/setup.h>
#endif

#if defined(CONFIG_MIPS) || defined(CONFIG_MIPS64)
#include <asm/bootinfo.h>
#endif

extern const struct linux_logo logo_linux_mono;
extern const struct linux_logo logo_linux_vga16;
extern const struct linux_logo logo_linux_clut224;
extern const struct linux_logo logo_dec_clut224;
extern const struct linux_logo logo_mac_clut224;
extern const struct linux_logo logo_parisc_clut224;
extern const struct linux_logo logo_sgi_clut224;
extern const struct linux_logo logo_sun_clut224;
extern const struct linux_logo logo_superh_mono;
extern const struct linux_logo logo_superh_vga16;
extern const struct linux_logo logo_superh_clut224;


const struct linux_logo * __init fb_find_logo(int type)
{
	const struct linux_logo *logo = 0;

	switch (type) {
		case LINUX_LOGO_MONO:
#ifdef CONFIG_LOGO_LINUX_MONO
			/* Generic Linux logo */
			logo = &logo_linux_mono;
#endif
#ifdef CONFIG_LOGO_SUPERH_MONO
			/* SuperH Linux logo */
			logo = &logo_superh_mono;
#endif
			break;

		case LINUX_LOGO_VGA16:
#ifdef CONFIG_LOGO_LINUX_VGA16
			/* Generic Linux logo */
			logo = &logo_linux_vga16;
#endif
#ifdef CONFIG_LOGO_SUPERH_VGA16
			/* SuperH Linux logo */
			logo = &logo_superh_vga16;
#endif
			break;

		case LINUX_LOGO_CLUT224:
#ifdef CONFIG_LOGO_LINUX_CLUT224
			/* Generic Linux logo */
			logo = &logo_linux_clut224;
#endif
#ifdef CONFIG_LOGO_DEC_CLUT224
			/* DEC Linux logo on MIPS/MIPS64 */
			if (mips_machgroup == MACH_GROUP_SGI)
				logo = &logo_dec_clut224;
#endif
#ifdef CONFIG_LOGO_MAC_CLUT224
			/* Macintosh Linux logo on m68k */
			if (MACH_IS_MAC)
				logo = &logo_mac_clut224;
#endif
#ifdef CONFIG_LOGO_PARISC_CLUT224
			/* PA-RISC Linux logo */
			logo = &logo_parisc_clut224;
#endif
#ifdef CONFIG_LOGO_SGI_CLUT224
			/* SGI Linux logo on MIPS/MIPS64 */
			if (mips_machgroup == MACH_GROUP_SGI)
				logo = &logo_sgi_clut224;
#endif
#ifdef CONFIG_LOGO_SUN_CLUT224
			/* Sun Linux logo */
			logo = &logo_sun_clut224;
#endif
#ifdef CONFIG_LOGO_SUPERH_CLUT224
			/* SuperH Linux logo */
			logo = &logo_superh_clut224;
#endif
			break;

	}
	return logo;
}

