include ../../silent.am

if WITH_GUI_GTK
bin_PROGRAMS = udogtk
endif

docdir = $(datarootdir)/doc/udosh
	
SUBDIRS = icons Manual

AM_CPPFLAGS =	-I$(top_srcdir)/src $(GTK_CFLAGS) \
		-DBINDIR="\"$(bindir)\""
	
udogtk_SOURCES = \
	udogtk.c udogtk.h \
	gtkcompat.h \
	gtkconfig.c gtkconfig.h \
	misc.c misc.h \
	help.c help.h htmlhelp.h \
	udointl.c
if OS_WIN32
udogtk_LDFLAGS = -mconsole
endif
udogtk_LDADD = $(GTK_LIBS) $(INTLLIBS)


if UDO_INTEGRATED
AM_CPPFLAGS += -DUDO_INTEGRATED=1
udogtk_SOURCES += \
	udogtkint.h \
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
