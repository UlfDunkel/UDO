include ../../silent.am

if WITH_GUI_WIN32
bin_PROGRAMS = udosh
endif

SUBDIRS = Manual res
DIST_SUBDIRS = Manual res

#WINDRES = windres
WINDRES = orc --compiler none

AM_CPPFLAGS = -I$(top_srcdir)/src

LIBS = -lshell32 -lgdi32 -lcomdlg32

AM_CFLAGS=	$(LOCAL_CFLAGS) $(DEFS) $(XCFLAGS)
AM_LDFLAGS=	$(LOCAL_LDFLAGS) $(XLDFLAGS) -mwindows


udosh_SOURCES = \
	udosh.c udosh.h \
	shconfig.c shconfig.h \
	misc.c misc.h \
	help.c help.h htmlhelp.h \
	dbgmsg.c dbgmsg.h \
	udointl.c

if UDO_INTEGRATED
AM_CPPFLAGS += -DUDO_INTEGRATED=1
udosh_SOURCES += \
	guish.c guish.h \
	udo_abo.c \
	udo_cfg.c \
	udo_chr.c \
	udo_debug.c \
	udo_env.c \
	udo_file.c \
	udo_img.c \
	udo_kwset.c \
	udo_lang.c \
	udo_msg.c \
	udo_obstack.c \
	udo_par.c \
	udo_str.c \
	udo_sty.c \
	udo_tab.c \
	udo_toc.c \
	udo_toc_html.c \
	udo_tp.c \
	udo_udo.c \
	udo_udomem.c \
	udo_udosym.c \
	udo_upr.c
endif

udosh_DEPENDENCIES = resource.res
udosh_LDADD = resource.res $(INTLLIBS)

resource.res: $(srcdir)/resource.rc $(srcdir)/resource.rh
	$(AM_V_RC)$(WINDRES) --target=$(RC_TARGET) --input-format rc --output-format coff -o $@ $(srcdir)/resource.rc

Manual/winhelp/udosh.hpc::
	cd Manual && make winhelp

EXTRA_DIST = resource.rc resource.rh

clean-local:
	$(RM) resource.res
