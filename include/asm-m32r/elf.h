#ifndef _ASM_M32R__ELF_H
#define _ASM_M32R__ELF_H

/* $Id$ */

/*
 * ELF register definitions..
 */

#include <asm/ptrace.h>
#include <asm/user.h>

#include <linux/utsname.h>

/* M32R relocation types  */
#define	R_M32R_NONE		0
#define	R_M32R_16		1
#define	R_M32R_32		2
#define	R_M32R_24		3
#define	R_M32R_10_PCREL		4
#define	R_M32R_18_PCREL		5
#define	R_M32R_26_PCREL		6
#define	R_M32R_HI16_ULO		7
#define	R_M32R_HI16_SLO		8
#define	R_M32R_LO16		9
#define	R_M32R_SDA16		10
#ifdef OLD_TYPE
#define	R_M32R_GOT24		11
#define	R_M32R_26_PLTREL	12
#define	R_M32R_GOT16_HI_ULO	13
#define	R_M32R_GOT16_HI_SLO	14
#define	R_M32R_GOT16_LO		15
#define	R_M32R_GOTPC24		16
#define	R_M32R_COPY		17
#define	R_M32R_GLOB_DAT		18
#define	R_M32R_JMP_SLOT		19
#define	R_M32R_RELATIVE		20
#define	R_M32R_GNU_VTINHERIT	21
#define	R_M32R_GNU_VTENTRY	22

#define R_M32R_16_RELA		R_M32R_16
#define R_M32R_32_RELA		R_M32R_32
#define R_M32R_24_RELA		R_M32R_24
#define R_M32R_10_PCREL_RELA	R_M32R_10_PCREL
#define R_M32R_18_PCREL_RELA	R_M32R_18_PCREL
#define R_M32R_26_PCREL_RELA	R_M32R_26_PCREL
#define R_M32R_HI16_ULO_RELA	R_M32R_HI16_ULO
#define R_M32R_HI16_SLO_RELA	R_M32R_HI16_SLO
#define R_M32R_LO16_RELA	R_M32R_LO16
#define R_M32R_SDA16_RELA	R_M32R_SDA16
#else /* OLD_TYPE */
#define	R_M32R_GNU_VTINHERIT	11
#define	R_M32R_GNU_VTENTRY	12

#define	R_M32R_GOT24_SAMPLE		11 /* comflict */
#define	R_M32R_26_PLTREL_SAMPLE	12 /* comflict */
#define	R_M32R_GOT16_HI_ULO_SAMPLE	13
#define	R_M32R_GOT16_HI_SLO_SAMPLE	14
#define	R_M32R_GOT16_LO_SAMPLE		15
#define	R_M32R_GOTPC24_SAMPLE		16
#define	R_M32R_COPY_SAMPLE		17
#define	R_M32R_GLOB_DAT_SAMPLE		18
#define	R_M32R_JMP_SLOT_SAMPLE		19
#define	R_M32R_RELATIVE_SAMPLE		20
#define	R_M32R_GNU_VTINHERIT_SAMPLE	21
#define	R_M32R_GNU_VTENTRY_SAMPLE	22

#define R_M32R_16_RELA		33
#define R_M32R_32_RELA		34
#define R_M32R_24_RELA		35
#define R_M32R_10_PCREL_RELA	36
#define R_M32R_18_PCREL_RELA	37
#define R_M32R_26_PCREL_RELA	38
#define R_M32R_HI16_ULO_RELA	39
#define R_M32R_HI16_SLO_RELA	40
#define R_M32R_LO16_RELA	41
#define R_M32R_SDA16_RELA	42
#define	R_M32R_RELA_GNU_VTINHERIT	43
#define	R_M32R_RELA_GNU_VTENTRY	44

#define R_M32R_GOT24		48
#define R_M32R_26_PLTREL	49
#define R_M32R_COPY		50
#define R_M32R_GLOB_DAT		51
#define R_M32R_JMP_SLOT		52
#define R_M32R_RELATIVE		53
#define R_M32R_GOTOFF		54
#define R_M32R_GOTPC24		55
#define R_M32R_GOT16_HI_ULO	56
#define R_M32R_GOT16_HI_SLO	57
#define R_M32R_GOT16_LO		58
#define R_M32R_GOTPC_HI_ULO	59
#define R_M32R_GOTPC_HI_SLO	60
#define R_M32R_GOTPC_LO		61

#endif /* OLD_TYPE */

#define R_M32R_NUM		256

typedef unsigned long elf_greg_t;

#define ELF_NGREG (sizeof (struct pt_regs) / sizeof(elf_greg_t))
typedef elf_greg_t elf_gregset_t[ELF_NGREG];

/* We have no FP mumumu.  */
typedef double elf_fpreg_t;
typedef elf_fpreg_t elf_fpregset_t;

/*
 * This is used to ensure we don't load something for the wrong architecture.
 */
#define elf_check_arch(x) \
	(((x)->e_machine == EM_M32R) || ((x)->e_machine == EM_CYGNUS_M32R))

/*
 * These are used to set parameters in the core dumps.
 */
#define ELF_CLASS	ELFCLASS32
#if defined(__LITTLE_ENDIAN)
#define ELF_DATA	ELFDATA2LSB
#elif defined(__BIG_ENDIAN)
#define ELF_DATA	ELFDATA2MSB
#else
#error no endian defined
#endif
#define ELF_ARCH	EM_M32R

/* SVR4/i386 ABI (pages 3-31, 3-32) says that when the program starts %edx
   contains a pointer to a function which might be registered using `atexit'.
   This provides a mean for the dynamic linker to call DT_FINI functions for
   shared libraries that have been loaded before the code runs.

   A value of 0 tells we have no such handler.

   We might as well make sure everything else is cleared too (except for %esp),
   just to make things more deterministic.
 */
#define ELF_PLAT_INIT(_r, load_addr)	do { \
	_r->r0 = 0; \
} while (0)

#define USE_ELF_CORE_DUMP
#define ELF_EXEC_PAGESIZE	4096

/* This is the location that an ET_DYN program is loaded if exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room for the brk.  */

#define ELF_ET_DYN_BASE         (TASK_SIZE / 3 * 2)

/* regs is struct pt_regs, pr_reg is elf_gregset_t (which is
   now struct_user_regs, they are different) */

#define ELF_CORE_COPY_REGS(pr_reg, regs)  \
	memcpy((char *)&pr_reg, (char *)&regs, sizeof (struct pt_regs));

/* This yields a mask that user programs can use to figure out what
   instruction set this CPU supports.  This could be done in user space,
   but it's not easy, and we've already done it here.  */

#define ELF_HWCAP	(0)

/* This yields a string that ld.so will use to load implementation
   specific libraries for optimization.  This is more specific in
   intent than poking at uname or /proc/cpuinfo.

   For the moment, we have only optimizations for the Intel generations,
   but that could change... */

#define ELF_PLATFORM  (NULL)

#ifdef __KERNEL__
#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
#endif

#endif  /* _ASM_M32R__ELF_H */
