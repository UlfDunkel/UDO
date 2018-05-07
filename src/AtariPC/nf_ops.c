#include <stdarg.h>
#include "udoport.h"
#include "debug.h"
#include <mint/arch/nf_ops.h>
#include <mint/cookie.h>
#include <osbind.h>
#include <stdint.h>

#define NATFEAT_ID   0x7300
#define NATFEAT_CALL 0x7301

#if defined(__AHCC__)

static long __asm__ __CDECL _nf_get_id(const char *feature_name)
{
	dc.w NATFEAT_ID
	rts
}


static long __asm__ __CDECL _nf_call(long id, ...)
{
	dc.w NATFEAT_CALL
	rts
}

static char const nf_version_str[] = NF_ID_VERSION;

static long __asm__ _nf_detect(void)
{
	pea		nf_version_str
	moveq	#0,d0			/* assume no NatFeats available */
	move.l	d0,-(sp)
	lea		_nf_illegal(pc),a1
	move.l	0x0010.w,a0		/* illegal instruction vector */
	move.l	a1,0x0010.w
	move.l	sp,a1			/* save the ssp */

	nop						/* flush pipelines (for 68040+) */

	dc.w	NATFEAT_ID		/* Jump to NATFEAT_ID */
	tst.l	d0
	beq.s	_nf_illegal
	moveq	#1,d0			/* NatFeats detected */
	move.l	d0,(sp)

_nf_illegal:
	move.l	a1,sp
	move.l	a0,0x0010.w
	nop						/* flush pipelines (for 68040+) */
	move.l	(sp)+,d0
	addq.l	#4,sp			/* pop nf_version argument */
	rts
}

#elif defined(__PUREC__)

static long nf_get_id_instr(void) NATFEAT_ID;
static long nf_call_instr(void) NATFEAT_CALL;

static long __CDECL _nf_get_id(const char *feature_name)
{
	UNUSED(feature_name);
	return nf_get_id_instr();
}


static long __CDECL _nf_call(long id, ...)
{
	UNUSED(id);
	return nf_call_instr();
}

static void push_a0(void *) 0x2f08;
static void moveq_0_d0(void) 0x7000;
static void moveq_1_d0(void) 0x7001;
static void push_d0(void) 0x2F00;
static void nop(void) 0x4e71;

/* lea nf_illegal(pc),a1 */
static void lea_nf_illegal_a(void) 0x43FA;
static void lea_nf_illegal_b(void) 0x0018;
#define lea_nf_illegal() lea_nf_illegal_a(); lea_nf_illegal_b()

/* move.l 0x0010.w,a1 */
static void fetch_illegal_vec_a(void) 0x2078;
static void fetch_illegal_vec_b(void) 0x0010;
#define fetch_illegal_vec() fetch_illegal_vec_a(); fetch_illegal_vec_b()

/* move.l a0,0x0010.w */
static void store_illegal_vec_a0_a(void) 0x21c8;
static void store_illegal_vec_a0_b(void) 0x0010;
#define store_illegal_vec_a0() store_illegal_vec_a0_a(); store_illegal_vec_a0_b()

/* move.l a1,0x0010.w */
static void store_illegal_vec_a1_a(void) 0x21c9;
static void store_illegal_vec_a1_b(void) 0x0010;
#define store_illegal_vec_a1() store_illegal_vec_a1_a(); store_illegal_vec_a1_b()

/* move.l sp,a1 */
static void get_sp(void) 0x224F;

/* tst.l d0 */
static void test_d0(void) 0x4a80;

/* beq.s _nf_illegal */
static void beqs_nf_illegal(void) 0x6704;

/* move d0,(sp) */
static void move_d0_sp(void) 0x2e80;

/* move.l a1,sp */
static void restore_sp(void) 0x2e49;

/* move.l (sp)+,d0 */
static void pop_d0(void) 0x201f;

/* addq.l #4,sp */
static long addq4_sp(void) 0x588F;

static long _nf_detect(void)
{
	push_a0(NF_ID_VERSION);
	moveq_0_d0();			/* assume no NatFeats available */
	push_d0();
	lea_nf_illegal();
	fetch_illegal_vec();	/* illegal instruction vector */
	store_illegal_vec_a1();
	get_sp();				/* save the ssp */

	nop();					/* flush pipelines (for 68040+) */

	nf_get_id_instr();		/* Jump to NATFEAT_ID */
	test_d0();
	beqs_nf_illegal();
	moveq_1_d0();			/* NatFeats detected */
	move_d0_sp();

/* _nf_illegal: */
	restore_sp();
	store_illegal_vec_a0();
	nop();					/* flush pipelines (for 68040+) */
	
	pop_d0();
	return addq4_sp();		/* pop nf_version argument */
}

#elif defined(__GNUC__)

#define ASM_NATFEAT3(opcode) "\t.word " #opcode "\n"
#define ASM_NATFEAT2(opcode) ASM_NATFEAT3(opcode)
#define ASM_NATFEAT(n) ASM_NATFEAT2(n)

static long __attribute__((noinline)) __CDECL _nf_get_id(const char *feature_name)
{
	register long ret __asm__ ("d0");
	__asm__ volatile(
		ASM_NATFEAT(NATFEAT_ID)
	: "=g"(ret)  /* outputs */
	: /* inputs  */
	: __CLOBBER_RETURN("d0") "d1" AND_MEMORY /* clobbered regs */
	);
	return ret;
}


static long __attribute__((noinline)) __CDECL _nf_call(long id, ...)
{
	register long ret __asm__ ("d0");
	__asm__ volatile(
		ASM_NATFEAT(NATFEAT_CALL)
	: "=g"(ret)  /* outputs */
	: /* inputs  */
	: __CLOBBER_RETURN("d0") "d1" AND_MEMORY /* clobbered regs */
	);
	return ret;
}


/*
 * on ColdFire, the NATFEAD_ID opcode is actually
 * "mvs.b d0,d1",
 * which means the following code will NOT detect
 * the presence of an emulator (should there ever
 * be an emulator capable of emulating a ColdFire processor).
 * Luckily, executing the code on a CF processor is still
 * harmless since all it does is clobber D1.
 */
static long _nf_detect(void)
{
	register long ret __asm__ ("d0");
	register const char *nf_version __asm__("a1") = NF_ID_VERSION;
	
	__asm__ volatile(
	"\tmove.l	%1,-(sp)\n"
	"\tmoveq	#0,d0\n"			/* assume no NatFeats available */
	"\tmove.l	d0,-(sp)\n"
	"\tlea		(1f:w,pc),a1\n"
	"\tmove.l	(0x0010).w,a0\n"	/* illegal instruction vector */
	"\tmove.l	a1,(0x0010).w\n"
	"\tmove.l	sp,a1\n"			/* save the ssp */

	"\tnop\n"						/* flush pipelines (for 68040+) */

	ASM_NATFEAT(NATFEAT_ID)			/* Jump to NATFEAT_ID */
	"\ttst.l	d0\n"
	"\tbeq.s	1f\n"
	"\tmoveq	#1,d0\n"			/* NatFeats detected */
	"\tmove.l	d0,(sp)\n"

"1:\n"
	"\tmove.l	a1,sp\n"
	"\tmove.l	a0,(0x0010).w\n"
	"\tmove.l	(sp)+,d0\n"
	"\taddq.l	#4,sp\n"			/* pop nf_version argument */

	"\tnop\n"						/* flush pipelines (for 68040+) */
	: "=g"(ret)  /* outputs */
	: "g"(nf_version)		/* inputs  */
	: __CLOBBER_RETURN("d0") "a0", "d1" AND_MEMORY
	);
	return ret;
}

#endif


static struct nf_ops _nf_ops = { _nf_get_id, _nf_call, { 0, 0, 0 } };
static struct nf_ops *nf_ops;

/* NatFeat code */
typedef struct {
	long magic;
	long __CDECL(*nfGetID) (const char *);
	long __CDECL(*nfCall) (long ID, ...);
} NatFeatCookie;

static int _nf_detect_cookie(void)
{
	NatFeatCookie *nf_ptr = NULL;

	if (Cookie_ReadJar(C___NF, (long *)&nf_ptr) == 0 ||		/* "__NF" */
		nf_ptr == NULL)
	{
		return FALSE;
	}

	if (nf_ptr->magic != 0x20021021L)		/* NatFeat magic constant */
	{
		return FALSE;
	}
	_nf_ops.get_id = nf_ptr->nfGetID;
	_nf_ops.call = nf_ptr->nfCall;
	return TRUE;
}



struct nf_ops *nf_init(void)
{
	/*
	 * The __NF cookie is deprecated, but there is currently
	 * no standard defined what to do e.g. on ColdFire, where the
	 * NF opcodes are not illegal, and the detection would fail.
	 * So there is current no choice but to check for the cookie,
	 * until we find ab better solution.
	 */
	if (nf_ops == NULL)
	{
		if (_nf_detect_cookie())
			nf_ops = &_nf_ops;
		if (Supexec(_nf_detect))
			nf_ops = &_nf_ops;
	}
	return nf_ops;
}


long nf_get_id(const char *feature_name)
{
	struct nf_ops *nf_ops;
	long id = 0;
	
	if ((nf_ops = nf_init()) != NULL)
	{
		id = NF_GET_ID(nf_ops, feature_name);
	}
	return id;
}


struct msgbuf {
	char *buf;
	size_t bufsize;
	size_t used;
};

/*** ---------------------------------------------------------------------- ***/

static long debugprintf_putchar(int c, struct msgbuf *msg)
{
	if (msg->used < msg->bufsize)
	{
		msg->buf[msg->used++] = c;
	}
	return 1;
}

/*** ---------------------------------------------------------------------- ***/

static long debugprintf_putc(struct msgbuf *msg, int c, int width)
{
	long put;
	
	put = debugprintf_putchar(c, msg);
	while (--width > 0)
	{
		put += debugprintf_putchar(' ', msg);
	}
	
	return put;
}

/*** ---------------------------------------------------------------------- ***/

static long debugprintf_putl(struct msgbuf *msg, unsigned long u, int base, int width, int fill_char, int upper)
{
	char obuf[32];
	char *t = obuf;
	long put = 0;
	
	do {
		*t = "0123456789abcdef"[u % base];
		if (upper && *t >= 'a' && *t <= 'f')
			*t = *t - 'a' + 'A';
		t++;
		u /= base;
		width--;
	} while (u > 0);
	
	while (width-- > 0)
	{
		put += debugprintf_putchar(fill_char, msg);
	}
	
	while (t != obuf)
	{
		put += debugprintf_putchar(*--t, msg);
	}
	
	return put;
}

/*** ---------------------------------------------------------------------- ***/

static long debugprintf_puts(struct msgbuf *msg, const char *s, int width)
{
	long put = 0;
	
	if (s == NULL)
		s = "(null)";
	
	while (*s)
	{
		put += debugprintf_putchar(*s++, msg);
		width--;
	}
	
	while (width-- > 0)
	{
		put += debugprintf_putchar(' ', msg);
	}
	
	return put;
}

/*** ---------------------------------------------------------------------- ***/

# define TIMESTEN(x)	((((x) << 2) + (x)) << 1)

static long debugprintf(struct msgbuf *msg, const char *fmt, va_list args)
{
	char c;
	char fill_char;
	long len = 0;
	int width;
	int long_flag;
	
	char *s_arg;
	int   i_arg;
	long  l_arg;

	while ((c = *fmt++) != 0)
	{
		if (c != '%')
		{
			len += debugprintf_putc(msg, c, 1);
			continue;
		}
		
		c = *fmt++;
		width = 0;
		long_flag = 0;
		fill_char = ' ';
		
		if (c == '0')
		{
			fill_char = '0';
			c = *fmt++;
		}
		
		while (c >= '0' && c <= '9')
		{
			width = TIMESTEN(width) + (c - '0');
			c = *fmt++;
		}
		
		if (c == 'l' || c == 'L')
		{
			long_flag = 1;
			c = *fmt++;
		}
		
		if (!c)
			break;
		
		switch (c)
		{
		case '%':
			len += debugprintf_putc(msg, c, width);
			break;
		case 'c':
			i_arg = (int)va_arg(args, int32_t);
			len += debugprintf_putc(msg, i_arg, width);
			break;
		case 's':
			s_arg = (char *)(va_arg(args, int32_t));
			len += debugprintf_puts(msg, s_arg, width);
			break;
		case 'i':
		case 'd':
			if (long_flag)
				l_arg = (long)va_arg(args, int32_t);
			else
				l_arg = (int)va_arg(args, int32_t);
			if (l_arg < 0)
			{
				len += debugprintf_putc(msg, '-', 1);
				width--;
				l_arg = -l_arg;
			}
			len += debugprintf_putl(msg, l_arg, 10, width, fill_char, FALSE);
			break;
		case 'o':
			if (long_flag)
				l_arg = (long)va_arg(args, int32_t);
			else
				l_arg = (unsigned int)va_arg(args, int32_t);
			len += debugprintf_putl(msg, l_arg, 8, width, fill_char, FALSE);
			break;
		case 'x':
		case 'X':
			if (long_flag)
				l_arg = (long)va_arg(args, int32_t);
			else
				l_arg = (unsigned int)va_arg(args, int32_t);
			len += debugprintf_putl(msg, l_arg, 16, width, fill_char, c == 'X');
			break;
		case 'b':
			if (long_flag)
				l_arg = (long)va_arg(args, int32_t);
			else
				l_arg = (unsigned int)va_arg(args, int32_t);
			len += debugprintf_putl(msg, l_arg, 2, width, fill_char, FALSE);
			break;
		case 'u':
			if (long_flag)
				l_arg = (long)va_arg(args, int32_t);
			else
				l_arg = (unsigned int)va_arg(args, int32_t);
			len += debugprintf_putl(msg, l_arg, 10, width, fill_char, FALSE);
			break;
		case 'p':
			l_arg = (long)va_arg(args, int32_t);
			while (width > 10)
			{
				len += debugprintf_putchar(' ', msg);
				width--;
			}
			len += debugprintf_puts(msg, "0x", 0);
			len += debugprintf_putl(msg, l_arg, 16, 8, '0', FALSE);
			break;
		}
	}
	
	return len;
}

/*** ---------------------------------------------------------------------- ***/

int nf_debugprintf(const char *format, ...)
{
	struct nf_ops *nf_ops;
	int ret = 0;
	
	if ((nf_ops = nf_init()) != NULL)
	{
		long nfid_stderr = NF_GET_ID(nf_ops, NF_ID_STDERR);
		
		if (nfid_stderr)
		{
			struct msgbuf msg;
			char buf[2048];
			va_list args;
			
			msg.buf = buf;
			msg.bufsize = sizeof(buf);
			msg.used = 0;
			va_start(args, format);
			ret = (int)debugprintf(&msg, format, args);
			va_end(args);
			if (ret >= sizeof(buf))
				ret = (int)sizeof(buf) - 1;
			buf[ret] = '\0';
			ret = (int)nf_ops->call(nfid_stderr | 0, (uint32_t)virt_to_phys(buf));
		}
	}
	
	return ret;
}

const char *nf_get_name(char *buf, size_t bufsize)
{
	const char *ret = NULL;
	struct nf_ops *nf_ops;
	
	if ((nf_ops = nf_init()) != NULL)
	{
		long nfid_name = NF_GET_ID(nf_ops, NF_ID_NAME);
			
		if (nfid_name)
			if (nf_ops->call(nfid_name | 0, (uint32_t)virt_to_phys(buf), (uint32_t)bufsize) != 0)
			{
				ret = buf;
			}
	}
        
	return ret;
}


const char *nf_get_fullname(char *buf, size_t bufsize)
{
	const char *ret = NULL;
	struct nf_ops *nf_ops;
	
	if ((nf_ops = nf_init()) != NULL)
	{
		long nfid_name = NF_GET_ID(nf_ops, NF_ID_NAME);
			
		if (nfid_name)
			if (nf_ops->call(nfid_name | 1, (uint32_t)virt_to_phys(buf), (uint32_t)bufsize) != 0)
			{
				ret = buf;
			}
	}
        
	return ret;
}


void nf_shutdown(void)
{
	struct nf_ops *nf_ops;

	if ((nf_ops = nf_init()) != NULL)
	{
		long shutdown_id = NF_GET_ID(nf_ops, NF_ID_SHUTDOWN);
		
		if (shutdown_id)
        	nf_ops->call(shutdown_id | 0);
	}
}


int nf_debug(const char *msg)
{
	struct nf_ops *nf_ops;

	if ((nf_ops = nf_init()) != NULL)
	{
		long nfid_stderr = NF_GET_ID(nf_ops, NF_ID_STDERR);
		
		if (nfid_stderr)
		{
			nf_ops->call(nfid_stderr | 0, virt_to_phys(msg));
			return 1;
		}
	}
	
	return 0;
}


long nf_version(void)
{
	struct nf_ops *nf_ops;
	long version = 0;
	
	if ((nf_ops = nf_init()) != NULL)
	{
		long nfid_version = NF_GET_ID(nf_ops, NF_ID_VERSION);
		
		if (nfid_version)
		{
			version = nf_ops->call(nfid_version | 0);
		}
	}
	return version;
}
