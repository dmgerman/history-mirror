# 
# Copyright (C) 2002 Jeff Dike (jdike@karaya.com)
# Licensed under the GPL
#

extra-y := vmlinux.lds
clean-files := vmlinux.lds.S config.tmp

obj-y = checksum.o config.o exec_kern.o exitcode.o \
	helper.o init_task.o irq.o irq_user.o ksyms.o main.o mem.o mem_user.o \
	physmem.o process.o process_kern.o ptrace.o reboot.o resource.o \
	sigio_user.o sigio_kern.o signal_kern.o signal_user.o smp.o \
	syscall_kern.o sysrq.o sys_call_table.o tempfile.o time.o time_kern.o \
	tlb.o trap_kern.o trap_user.o uaccess_user.o um_arch.o umid.o \
	user_util.o

obj-$(CONFIG_BLK_DEV_INITRD) += initrd_kern.o initrd_user.o
obj-$(CONFIG_GPROF)	+= gprof_syms.o
obj-$(CONFIG_GCOV)	+= gmon_syms.o
obj-$(CONFIG_TTY_LOG)	+= tty_log.o
obj-$(CONFIG_SYSCALL_DEBUG) += syscall_user.o

obj-$(CONFIG_MODE_TT) += tt/
obj-$(CONFIG_MODE_SKAS) += skas/

# This needs be compiled with frame pointers regardless of how the rest of the
# kernel is built.
CFLAGS_frame.o := -fno-omit-frame-pointer

user-objs-$(CONFIG_TTY_LOG) += tty_log.o

USER_OBJS := $(user-objs-y) config.o helper.o main.o process.o tempfile.o \
	time.o tty_log.o umid.o user_util.o frame.o

include arch/um/scripts/Makefile.rules

targets += config.c

# Be careful with the below Sed code - sed is pitfall-rich!
# We use sed to lower build requirements, for "embedded" builders for instance.

$(obj)/config.tmp: $(objtree)/.config FORCE
	$(call if_changed,quote1)

quiet_cmd_quote1 = QUOTE   $@
      cmd_quote1 = sed -e 's/"/\\"/g' -e 's/^/"/' -e 's/$$/\\n"/' \
		   $< > $@

$(obj)/config.c: $(src)/config.c.in $(obj)/config.tmp FORCE
	$(call if_changed,quote2)

quiet_cmd_quote2 = QUOTE   $@
      cmd_quote2 = sed -e '/CONFIG/{'          \
		  -e 's/"CONFIG"\;/""/'        \
		  -e 'r $(obj)/config.tmp'     \
		  -e 'a""\;'                   \
		  -e '}'                       \
		  $< > $@
