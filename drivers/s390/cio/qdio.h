#ifndef _CIO_QDIO_H
#define _CIO_QDIO_H

#define VERSION_CIO_QDIO_H "$Revision: 1.8 $"

//#define QDIO_DBF_LIKE_HELL

#ifdef QDIO_DBF_LIKE_HELL
#define QDIO_VERBOSE_LEVEL 9
#else /* QDIO_DBF_LIKE_HELL */
#define QDIO_VERBOSE_LEVEL 5
#endif /* QDIO_DBF_LIKE_HELL */

#define QDIO_USE_PROCESSING_STATE

#ifdef CONFIG_QDIO_PERF_STATS
#define QDIO_PERFORMANCE_STATS
#endif /* CONFIG_QDIO_PERF_STATS */

#define QDIO_MINIMAL_BH_RELIEF_TIME 16
#define QDIO_TIMER_POLL_VALUE 1
#define IQDIO_TIMER_POLL_VALUE 1

#define IQDIO_FILL_LEVEL_TO_POLL (QDIO_MAX_BUFFERS_PER_Q*4/3)

#define IQDIO_THININT_ISC 3
#define IQDIO_DELAY_TARGET 0
#define QDIO_BUSY_BIT_PATIENCE 2000 /* in microsecs */
#define IQDIO_GLOBAL_LAPS 2 /* GLOBAL_LAPS are not used as we */
#define IQDIO_GLOBAL_LAPS_INT 1 /* dont global summary */
#define IQDIO_LOCAL_LAPS 4
#define IQDIO_LOCAL_LAPS_INT 1
#define IQDIO_GLOBAL_SUMMARY_CC_MASK 2
/*#define IQDIO_IQDC_INT_PARM 0x1234*/

#define QDIO_Q_LAPS 5

#define QDIO_STORAGE_KEY 0

#define L2_CACHELINE_SIZE 256
#define INDICATORS_PER_CACHELINE (L2_CACHELINE_SIZE/sizeof(__u32))

#define QDIO_PERF "qdio_perf"

/* must be a power of 2 */
/*#define QDIO_STATS_NUMBER 4

#define QDIO_STATS_CLASSES 2
#define QDIO_STATS_COUNT_NEEDED 2*/

#define QDIO_NO_USE_COUNT_TIME 10
#define QDIO_NO_USE_COUNT_TIMEOUT 1000 /* wait for 1 sec on each q before
					  exiting without having use_count
					  of the queue to 0 */

#define QDIO_ESTABLISH_TIMEOUT 1000
#define QDIO_ACTIVATE_TIMEOUT 100
#define QDIO_CLEANUP_CLEAR_TIMEOUT 20000
#define QDIO_CLEANUP_HALT_TIMEOUT 10000

#define QDIO_IRQ_STATE_FRESH 0 /* must be 0 -> memset has set it to 0 */
#define QDIO_IRQ_STATE_INACTIVE 1
#define QDIO_IRQ_STATE_ESTABLISHED 2
#define QDIO_IRQ_STATE_ACTIVE 3
#define QDIO_IRQ_STATE_STOPPED 4

/* used as intparm in do_IO: */
#define QDIO_DOING_SENSEID 0
#define QDIO_DOING_ESTABLISH 1
#define QDIO_DOING_ACTIVATE 2
#define QDIO_DOING_CLEANUP 3

/************************* DEBUG FACILITY STUFF *********************/

#define QDIO_DBF_HEX(ex,name,level,addr,len) \
	do { \
	if (ex) \
		debug_exception(qdio_dbf_##name,level,(void*)(addr),len); \
	else \
		debug_event(qdio_dbf_##name,level,(void*)(addr),len); \
	} while (0)
#define QDIO_DBF_TEXT(ex,name,level,text) \
	do { \
	if (ex) \
		debug_text_exception(qdio_dbf_##name,level,text); \
	else \
		debug_text_event(qdio_dbf_##name,level,text); \
	} while (0)


#define QDIO_DBF_HEX0(ex,name,addr,len) QDIO_DBF_HEX(ex,name,0,addr,len)
#define QDIO_DBF_HEX1(ex,name,addr,len) QDIO_DBF_HEX(ex,name,1,addr,len)
#define QDIO_DBF_HEX2(ex,name,addr,len) QDIO_DBF_HEX(ex,name,2,addr,len)
#ifdef QDIO_DBF_LIKE_HELL
#define QDIO_DBF_HEX3(ex,name,addr,len) QDIO_DBF_HEX(ex,name,3,addr,len)
#define QDIO_DBF_HEX4(ex,name,addr,len) QDIO_DBF_HEX(ex,name,4,addr,len)
#define QDIO_DBF_HEX5(ex,name,addr,len) QDIO_DBF_HEX(ex,name,5,addr,len)
#define QDIO_DBF_HEX6(ex,name,addr,len) QDIO_DBF_HEX(ex,name,6,addr,len)
#else /* QDIO_DBF_LIKE_HELL */
#define QDIO_DBF_HEX3(ex,name,addr,len) do {} while (0)
#define QDIO_DBF_HEX4(ex,name,addr,len) do {} while (0)
#define QDIO_DBF_HEX5(ex,name,addr,len) do {} while (0)
#define QDIO_DBF_HEX6(ex,name,addr,len) do {} while (0)
#endif /* QDIO_DBF_LIKE_HELL */

#define QDIO_DBF_TEXT0(ex,name,text) QDIO_DBF_TEXT(ex,name,0,text)
#define QDIO_DBF_TEXT1(ex,name,text) QDIO_DBF_TEXT(ex,name,1,text)
#define QDIO_DBF_TEXT2(ex,name,text) QDIO_DBF_TEXT(ex,name,2,text)
#ifdef QDIO_DBF_LIKE_HELL
#define QDIO_DBF_TEXT3(ex,name,text) QDIO_DBF_TEXT(ex,name,3,text)
#define QDIO_DBF_TEXT4(ex,name,text) QDIO_DBF_TEXT(ex,name,4,text)
#define QDIO_DBF_TEXT5(ex,name,text) QDIO_DBF_TEXT(ex,name,5,text)
#define QDIO_DBF_TEXT6(ex,name,text) QDIO_DBF_TEXT(ex,name,6,text)
#else /* QDIO_DBF_LIKE_HELL */
#define QDIO_DBF_TEXT3(ex,name,text) do {} while (0)
#define QDIO_DBF_TEXT4(ex,name,text) do {} while (0)
#define QDIO_DBF_TEXT5(ex,name,text) do {} while (0)
#define QDIO_DBF_TEXT6(ex,name,text) do {} while (0)
#endif /* QDIO_DBF_LIKE_HELL */

#define QDIO_DBF_SETUP_NAME "qdio_setup"
#define QDIO_DBF_SETUP_LEN 8
#define QDIO_DBF_SETUP_INDEX 2
#define QDIO_DBF_SETUP_NR_AREAS 1
#ifdef QDIO_DBF_LIKE_HELL
#define QDIO_DBF_SETUP_LEVEL 6
#else /* QDIO_DBF_LIKE_HELL */
#define QDIO_DBF_SETUP_LEVEL 2
#endif /* QDIO_DBF_LIKE_HELL */

#define QDIO_DBF_SBAL_NAME "qdio_labs" /* sbal */
#define QDIO_DBF_SBAL_LEN 256
#define QDIO_DBF_SBAL_INDEX 2
#define QDIO_DBF_SBAL_NR_AREAS 2
#ifdef QDIO_DBF_LIKE_HELL
#define QDIO_DBF_SBAL_LEVEL 6
#else /* QDIO_DBF_LIKE_HELL */
#define QDIO_DBF_SBAL_LEVEL 2
#endif /* QDIO_DBF_LIKE_HELL */

#define QDIO_DBF_TRACE_NAME "qdio_trace"
#define QDIO_DBF_TRACE_LEN 8
#define QDIO_DBF_TRACE_NR_AREAS 2
#ifdef QDIO_DBF_LIKE_HELL
#define QDIO_DBF_TRACE_INDEX 4
#define QDIO_DBF_TRACE_LEVEL 4 /* -------- could be even more verbose here */
#else /* QDIO_DBF_LIKE_HELL */
#define QDIO_DBF_TRACE_INDEX 2
#define QDIO_DBF_TRACE_LEVEL 2
#endif /* QDIO_DBF_LIKE_HELL */

#define QDIO_DBF_SENSE_NAME "qdio_sense"
#define QDIO_DBF_SENSE_LEN 64
#define QDIO_DBF_SENSE_INDEX 1
#define QDIO_DBF_SENSE_NR_AREAS 1
#ifdef QDIO_DBF_LIKE_HELL
#define QDIO_DBF_SENSE_LEVEL 6
#else /* QDIO_DBF_LIKE_HELL */
#define QDIO_DBF_SENSE_LEVEL 2
#endif /* QDIO_DBF_LIKE_HELL */

#ifdef QDIO_DBF_LIKE_HELL
#define QDIO_TRACE_QTYPE QDIO_ZFCP_QFMT

#define QDIO_DBF_SLSB_OUT_NAME "qdio_slsb_out"
#define QDIO_DBF_SLSB_OUT_LEN QDIO_MAX_BUFFERS_PER_Q
#define QDIO_DBF_SLSB_OUT_INDEX 8
#define QDIO_DBF_SLSB_OUT_NR_AREAS 1
#define QDIO_DBF_SLSB_OUT_LEVEL 6

#define QDIO_DBF_SLSB_IN_NAME "qdio_slsb_in"
#define QDIO_DBF_SLSB_IN_LEN QDIO_MAX_BUFFERS_PER_Q
#define QDIO_DBF_SLSB_IN_INDEX 8
#define QDIO_DBF_SLSB_IN_NR_AREAS 1
#define QDIO_DBF_SLSB_IN_LEVEL 6
#endif /* QDIO_DBF_LIKE_HELL */

#define QDIO_PRINTK_HEADER QDIO_NAME ": "

#if QDIO_VERBOSE_LEVEL>8
#define QDIO_PRINT_STUPID(x...) printk( KERN_DEBUG QDIO_PRINTK_HEADER x)
#else
#define QDIO_PRINT_STUPID(x...)
#endif

#if QDIO_VERBOSE_LEVEL>7
#define QDIO_PRINT_ALL(x...) printk( QDIO_PRINTK_HEADER x)
#else
#define QDIO_PRINT_ALL(x...)
#endif

#if QDIO_VERBOSE_LEVEL>6
#define QDIO_PRINT_INFO(x...) printk( QDIO_PRINTK_HEADER x)
#else
#define QDIO_PRINT_INFO(x...)
#endif

#if QDIO_VERBOSE_LEVEL>5
#define QDIO_PRINT_WARN(x...) printk( QDIO_PRINTK_HEADER x)
#else
#define QDIO_PRINT_WARN(x...)
#endif

#if QDIO_VERBOSE_LEVEL>4
#define QDIO_PRINT_ERR(x...) printk( QDIO_PRINTK_HEADER x)
#else
#define QDIO_PRINT_ERR(x...)
#endif

#if QDIO_VERBOSE_LEVEL>3
#define QDIO_PRINT_CRIT(x...) printk( QDIO_PRINTK_HEADER x)
#else
#define QDIO_PRINT_CRIT(x...)
#endif

#if QDIO_VERBOSE_LEVEL>2
#define QDIO_PRINT_ALERT(x...) printk( QDIO_PRINTK_HEADER x)
#else
#define QDIO_PRINT_ALERT(x...)
#endif

#if QDIO_VERBOSE_LEVEL>1
#define QDIO_PRINT_EMERG(x...) printk( QDIO_PRINTK_HEADER x)
#else
#define QDIO_PRINT_EMERG(x...)
#endif

#define HEXDUMP16(importance,header,ptr) \
QDIO_PRINT_##importance(header "%02x %02x %02x %02x  " \
			"%02x %02x %02x %02x  %02x %02x %02x %02x  " \
			"%02x %02x %02x %02x\n",*(((char*)ptr)), \
			*(((char*)ptr)+1),*(((char*)ptr)+2), \
			*(((char*)ptr)+3),*(((char*)ptr)+4), \
			*(((char*)ptr)+5),*(((char*)ptr)+6), \
			*(((char*)ptr)+7),*(((char*)ptr)+8), \
			*(((char*)ptr)+9),*(((char*)ptr)+10), \
			*(((char*)ptr)+11),*(((char*)ptr)+12), \
			*(((char*)ptr)+13),*(((char*)ptr)+14), \
			*(((char*)ptr)+15)); \
QDIO_PRINT_##importance(header "%02x %02x %02x %02x  %02x %02x %02x %02x  " \
			"%02x %02x %02x %02x  %02x %02x %02x %02x\n", \
			*(((char*)ptr)+16),*(((char*)ptr)+17), \
			*(((char*)ptr)+18),*(((char*)ptr)+19), \
			*(((char*)ptr)+20),*(((char*)ptr)+21), \
			*(((char*)ptr)+22),*(((char*)ptr)+23), \
			*(((char*)ptr)+24),*(((char*)ptr)+25), \
			*(((char*)ptr)+26),*(((char*)ptr)+27), \
			*(((char*)ptr)+28),*(((char*)ptr)+29), \
			*(((char*)ptr)+30),*(((char*)ptr)+31));

/****************** END OF DEBUG FACILITY STUFF *********************/

/*
 * Some instructions as assembly
 */
extern __inline__ int 
do_siga_sync(unsigned int irq, unsigned int mask1, unsigned int mask2)
{
	int cc;

#ifndef CONFIG_ARCH_S390X
	asm volatile (
		"lhi	0,2	\n\t"
		"lr	1,%1	\n\t"
		"lr	2,%2	\n\t"
		"lr	3,%3	\n\t"
		"siga   0	\n\t"
		"ipm	%0	\n\t"
		"srl	%0,28	\n\t"
		: "=d" (cc)
		: "d" (0x10000|irq), "d" (mask1), "d" (mask2)
		: "cc", "0", "1", "2", "3"
		);
#else /* CONFIG_ARCH_S390X */
	asm volatile (
		"lghi	0,2	\n\t"
		"llgfr	1,%1	\n\t"
		"llgfr	2,%2	\n\t"
		"llgfr	3,%3	\n\t"
		"siga   0	\n\t"
		"ipm	%0	\n\t"
		"srl	%0,28	\n\t"
		: "=d" (cc)
		: "d" (0x10000|irq), "d" (mask1), "d" (mask2)
		: "cc", "0", "1", "2", "3"
		);
#endif /* CONFIG_ARCH_S390X */
	return cc;
}

extern __inline__ int
do_siga_input(unsigned int irq, unsigned int mask)
{
	int cc;

#ifndef CONFIG_ARCH_S390X
	asm volatile (
		"lhi	0,1	\n\t"
		"lr	1,%1	\n\t"
		"lr	2,%2	\n\t"
		"siga   0	\n\t"
		"ipm	%0	\n\t"
		"srl	%0,28	\n\t"
		: "=d" (cc)
		: "d" (0x10000|irq), "d" (mask)
		: "cc", "0", "1", "2", "memory"
		);
#else /* CONFIG_ARCH_S390X */
	asm volatile (
		"lghi	0,1	\n\t"
		"llgfr	1,%1	\n\t"
		"llgfr	2,%2	\n\t"
		"siga   0	\n\t"
		"ipm	%0	\n\t"
		"srl	%0,28	\n\t"
		: "=d" (cc)
		: "d" (0x10000|irq), "d" (mask)
		: "cc", "0", "1", "2", "memory"
		);
#endif /* CONFIG_ARCH_S390X */
	
	return cc;
}

extern __inline__ int
do_siga_output(unsigned long irq, unsigned long mask, __u32 *bb)
{
	int cc;
	__u32 busy_bit;

#ifndef CONFIG_ARCH_S390X
	asm volatile (
		"lhi	0,0	\n\t"
		"lr	1,%2	\n\t"
		"lr	2,%3	\n\t"
		"siga	0	\n\t"
		"0:"
		"ipm	%0	\n\t"
		"srl	%0,28	\n\t"
		"srl	0,31	\n\t"
		"lr	%1,0	\n\t"
		"1:	\n\t"
		".section .fixup,\"ax\"\n\t"
		"2:	\n\t"
		"lhi	%0,%4	\n\t"
		"bras	1,3f	\n\t"
		".long 1b	\n\t"
		"3:	\n\t"
		"l	1,0(1)	\n\t"
		"br	1	\n\t"
		".previous	\n\t"
		".section __ex_table,\"a\"\n\t"
		".align 4	\n\t"
		".long	0b,2b	\n\t"
		".previous	\n\t"
		: "=d" (cc), "=d" (busy_bit)
		: "d" (0x10000|irq), "d" (mask),
		"i" (QDIO_SIGA_ERROR_ACCESS_EXCEPTION)
		: "cc", "0", "1", "2", "memory"
		);
#else /* CONFIG_ARCH_S390X */
	asm volatile (
		"lghi	0,0	\n\t"
		"llgfr	1,%2	\n\t"
		"llgfr	2,%3	\n\t"
		"siga	0	\n\t"
		"0:"
		"ipm	%0	\n\t"
		"srl	%0,28	\n\t"
		"srl	0,31	\n\t"
		"llgfr	%1,0	\n\t"
		"1:	\n\t"
		".section .fixup,\"ax\"\n\t"
		"lghi	%0,%4	\n\t"
		"jg	1b	\n\t"
		".previous\n\t"
		".section __ex_table,\"a\"\n\t"
		".align 8	\n\t"
		".quad	0b,1b	\n\t"
		".previous	\n\t"
		: "=d" (cc), "=d" (busy_bit)
		: "d" (0x10000|irq), "d" (mask),
		"i" (QDIO_SIGA_ERROR_ACCESS_EXCEPTION)
		: "cc", "0", "1", "2", "memory"
		);
#endif /* CONFIG_ARCH_S390X */
	
	(*bb) = busy_bit;
	return cc;
}

extern __inline__ unsigned long
do_clear_global_summary(void)
{

	unsigned long time;

#ifndef CONFIG_ARCH_S390X
	asm volatile (
		"lhi	1,3	\n\t"
		".insn	rre,0xb2650000,2,0	\n\t"
		"lr	%0,3	\n\t"
		: "=d" (time) : : "cc", "1", "2", "3"
		);
#else /* CONFIG_ARCH_S390X */
	asm volatile (
		"lghi	1,3	\n\t"
		".insn	rre,0xb2650000,2,0	\n\t"
		"lgr	%0,3	\n\t"
		: "=d" (time) : : "cc", "1", "2", "3"
		);
#endif /* CONFIG_ARCH_S390X */
	
	return time;
}
	
/*
 * QDIO device commands returned by extended Sense-ID
 */
#define DEFAULT_ESTABLISH_QS_CMD 0x1b
#define DEFAULT_ESTABLISH_QS_COUNT 0x1000
#define DEFAULT_ACTIVATE_QS_CMD 0x1f
#define DEFAULT_ACTIVATE_QS_COUNT 0

/*
 * additional CIWs returned by extended Sense-ID
 */
#define CIW_TYPE_EQUEUE 0x3       /* establish QDIO queues */
#define CIW_TYPE_AQUEUE 0x4       /* activate QDIO queues */

#define QDIO_CHSC_RESPONSE_CODE_OK 1
/* flags for st qdio sch data */
#define CHSC_FLAG_QDIO_CAPABILITY 0x80
#define CHSC_FLAG_VALIDITY 0x40

#define CHSC_FLAG_SIGA_INPUT_NECESSARY 0x40
#define CHSC_FLAG_SIGA_OUTPUT_NECESSARY 0x20
#define CHSC_FLAG_SIGA_SYNC_NECESSARY 0x10
#define CHSC_FLAG_SIGA_SYNC_DONE_ON_THININTS 0x08
#define CHSC_FLAG_SIGA_SYNC_DONE_ON_OUTB_PCIS 0x04

struct qdio_chsc_area {
	struct {
		/* word 0 */
		__u16 command_code1;
		__u16 command_code2;
		/* word 1 */
		__u16 operation_code;
		__u16 first_sch;
		/* word 2 */
		__u8 reserved1;
		__u8 image_id;
		__u16 last_sch;
		/* word 3 */
		__u32 reserved2;

		/* word 4 */
		union {
			struct {
				/* word 4&5 */
				__u64 summary_indicator_addr;
				/* word 6&7 */
				__u64 subchannel_indicator_addr;
				/* word 8 */
				int ks:4;
				int kc:4;
				int reserved1:21;
				int isc:3;
				/* word 9&10 */
				__u32 reserved2[2];
				/* word 11 */
				__u32 subsystem_id;
				/* word 12-1015 */
				__u32 reserved3[1004];
			} __attribute__ ((packed,aligned(4))) set_chsc;
			struct {
				/* word 4&5 */
				__u32 reserved1[2];	
				/* word 6 */
				__u32 delay_target;
				/* word 7-1015 */
				__u32 reserved4[1009];
			} __attribute__ ((packed,aligned(4))) set_chsc_fast;
			struct {
				/* word 0 */
				__u16 length;
				__u16 response_code;
				/* word 1 */
				__u32 reserved1;
				/* words 2 to 9 for st sch qdio data */
				__u8 flags;
				__u8 reserved2;
				__u16 sch;
				__u8 qfmt;
				__u8 reserved3;
				__u8 qdioac;
				__u8 sch_class;
				__u8 reserved4;
				__u8 icnt;
				__u8 reserved5;
				__u8 ocnt;
				/* plus 5 words of reserved fields */
			} __attribute__ ((packed,aligned(8)))
			store_qdio_data_response;
		} operation_data_area;
	} __attribute__ ((packed,aligned(8))) request_block;
	struct {
		/* word 0 */
		__u16 length;
		__u16 response_code;
		/* word 1 */
		__u32 reserved1;
	} __attribute__ ((packed,aligned(8))) response_block;
} __attribute__ ((packed,aligned(PAGE_SIZE)));


#ifdef QDIO_PERFORMANCE_STATS
struct qdio_perf_stats {
	unsigned int tl_runs;

	unsigned int siga_outs;
	unsigned int siga_ins;
	unsigned int siga_syncs;
	unsigned int pcis;
	unsigned int thinints;
	unsigned int fast_reqs;

	__u64 start_time_outbound;
	unsigned int outbound_cnt;
	unsigned int outbound_time;
	__u64 start_time_inbound;
	unsigned int inbound_cnt;
	unsigned int inbound_time;
};
#endif /* QDIO_PERFORMANCE_STATS */

#define atomic_swap(a,b) xchg((int*)a.counter,b)

#define SYNC_MEMORY if (q->siga_sync) qdio_siga_sync(q)
#define NOW qdio_get_micros()
#define SAVE_TIMESTAMP(q) q->timing.last_transfer_time=NOW
#define GET_SAVED_TIMESTAMP(q) (q->timing.last_transfer_time)
#define SAVE_FRONTIER(q,val) q->last_move_ftc=val
#define GET_SAVED_FRONTIER(q) (q->last_move_ftc)

#define MY_MODULE_STRING(x) #x

#ifdef CONFIG_ARCH_S390X
#define QDIO_GET_ADDR(x) ((__u32)(unsigned long)x)
#else /* CONFIG_ARCH_S390X */
#define QDIO_GET_ADDR(x) ((__u32)(long)x)
#endif /* CONFIG_ARCH_S390X */

#ifdef QDIO_DBF_LIKE_HELL 
#define set_slsb(x,y) \
  if(q->queue_type==QDIO_TRACE_QTYPE) { \
        if(q->is_input_q) { \
            QDIO_DBF_HEX2(0,slsb_in,&q->slsb,QDIO_MAX_BUFFERS_PER_Q); \
        } else { \
            QDIO_DBF_HEX2(0,slsb_out,&q->slsb,QDIO_MAX_BUFFERS_PER_Q); \
        } \
  } \
  qdio_set_slsb(x,y); \
  if(q->queue_type==QDIO_TRACE_QTYPE) { \
        if(q->is_input_q) { \
            QDIO_DBF_HEX2(0,slsb_in,&q->slsb,QDIO_MAX_BUFFERS_PER_Q); \
        } else { \
            QDIO_DBF_HEX2(0,slsb_out,&q->slsb,QDIO_MAX_BUFFERS_PER_Q); \
        } \
  }
#else /* QDIO_DBF_LIKE_HELL */
#define set_slsb(x,y) qdio_set_slsb(x,y)
#endif /* QDIO_DBF_LIKE_HELL */

struct qdio_q {
	volatile struct slsb slsb;

	__u32 * volatile dev_st_chg_ind;

	int is_input_q;
	int irq;

	unsigned int is_iqdio_q;

	/* bit 0 means queue 0, bit 1 means queue 1, ... */
	unsigned int mask;
	unsigned int q_no;

	qdio_handler_t (*handler);

	/* points to the next buffer to be checked for having
	 * been processed by the card (outbound)
	 * or to the next buffer the program should check for (inbound) */
	volatile int first_to_check;
	/* and the last time it was: */
	volatile int last_move_ftc;

	atomic_t number_of_buffers_used;
	atomic_t polling;

	unsigned int siga_in;
	unsigned int siga_out;
	unsigned int siga_sync;
	unsigned int siga_sync_done_on_thinints;
	unsigned int hydra_gives_outbound_pcis;

	/* used to save beginning position when calling dd_handlers */
	int first_element_to_kick;

	atomic_t use_count;
	atomic_t is_in_shutdown;

#ifdef QDIO_USE_TIMERS_FOR_POLLING
	struct timer_list timer;
	atomic_t timer_already_set;
	spinlock_t timer_lock;
#else /* QDIO_USE_TIMERS_FOR_POLLING */
	struct tasklet_struct tasklet;
#endif /* QDIO_USE_TIMERS_FOR_POLLING */

	unsigned int state;

	/* used to store the error condition during a data transfer */
	unsigned int qdio_error;
	unsigned int siga_error;
	unsigned int error_status_flags;

	/* list of interesting queues */
	volatile struct qdio_q *list_next;
	volatile struct qdio_q *list_prev;

	struct slib *slib; /* a page is allocated under this pointer,
			      sl points into this page, offset PAGE_SIZE/2
			      (after slib) */
	struct sl *sl;
	volatile struct sbal *sbal[QDIO_MAX_BUFFERS_PER_Q];

	struct qdio_buffer *qdio_buffers[QDIO_MAX_BUFFERS_PER_Q];

	unsigned long int_parm;

	/*struct {
		int in_bh_check_limit;
		int threshold;
	} threshold_classes[QDIO_STATS_CLASSES];*/

	struct {
		/* inbound: the time to stop polling
		   outbound: the time to kick peer */
		int threshold; /* the real value */

		/* outbound: last time of do_QDIO
		   inbound: last time of noticing incoming data */
		/*__u64 last_transfer_times[QDIO_STATS_NUMBER];
		int last_transfer_index; */

		__u64 last_transfer_time;
	} timing;
        unsigned int queue_type;
} __attribute__ ((aligned(256)));

struct qdio_irq {
	__u32 * volatile dev_st_chg_ind;

	unsigned long int_parm;
	int irq;

	unsigned int is_iqdio_irq;
	unsigned int hydra_gives_outbound_pcis;
	unsigned int sync_done_on_outb_pcis;

	unsigned int state;
	spinlock_t setting_up_lock;

	unsigned int no_input_qs;
	unsigned int no_output_qs;

	unsigned char qdioac;

	struct qdio_q *input_qs[QDIO_MAX_QUEUES_PER_IRQ];
	struct qdio_q *output_qs[QDIO_MAX_QUEUES_PER_IRQ];

	struct ccw1 ccw;

	struct qdr *qdr;

	struct ciw equeue;
	struct ciw aqueue;

	struct qib qib;
	
	/* Functions called via the generic cio layer */
	void (*cleanup_irq) (struct ccw_device *, unsigned long, struct irb *);
	void (*cleanup_timeout) (struct ccw_device *);
	void (*establish_irq) (struct ccw_device *, unsigned long,
			       struct irb *);
	void (*establish_timeout) (struct ccw_device *);
	void (*handler) (struct ccw_device *, unsigned long, struct irb *);

};
#endif
