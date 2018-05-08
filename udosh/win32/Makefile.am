AUTOMAKE_OPTIONS = subdir-objects

include ../../silent.am

if WITH_GUI_WIN32
bin_PROGRAMS = udosh
endif

SUBDIRS = Manual res
DIST_SUBDIRS = Manual res

#WINDRES = windres
WINDRES = orc --compiler none

UDO_SOURCE=$(top_srcdir)/src

AM_CPPFLAGS = -I$(UDO_SOURCE)

LIBS = -lshell32 -lgdi32 -lcomdlg32

AM_CFLAGS=	$(LOCAL_CFLAGS) $(DEFS) $(XCFLAGS)
AM_LDFLAGS=	$(LOCAL_LDFLAGS) $(XLDFLAGS) -mwindows


udosh_SOURCES = \
	udosh.c udosh.h \
	shconfig.c shconfig.h \
	misc.c misc.h \
	help.c help.h htmlhelp.h \
	dbgmsg.c dbgmsg.h \
	windows_.h

if UDO_INTEGRATED
AM_CPPFLAGS += -DUDO_INTEGRATED=1
udosh_SOURCES += \
	guish.c guish.h \
	$(UDO_SOURCE)/abo.c \
	$(UDO_SOURCE)/cfg.c \
	$(UDO_SOURCE)/chr.c \
	$(UDO_SOURCE)/debug.c \
	$(UDO_SOURCE)/env.c \
	$(UDO_SOURCE)/file.c \
	$(UDO_SOURCE)/img.c \
	$(UDO_SOURCE)/kwset.c \
	$(UDO_SOURCE)/lang.c \
	$(UDO_SOURCE)/msg.c \
	$(UDO_SOURCE)/obstack.c \
	$(UDO_SOURCE)/par.c \
	$(UDO_SOURCE)/str.c \
	$(UDO_SOURCE)/sty.c \
	$(UDO_SOURCE)/tab.c \
	$(UDO_SOURCE)/toc.c \
	$(UDO_SOURCE)/toc_html.c \
	$(UDO_SOURCE)/tp.c \
	$(UDO_SOURCE)/udo.c \
	$(UDO_SOURCE)/udomem.c \
	$(UDO_SOURCE)/udosym.c \
	$(UDO_SOURCE)/upr.c \
	$(UDO_SOURCE)/udointl.c
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
