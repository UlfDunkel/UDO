###########################################################
# @(#) Makefile.in template for unix,
# @(#) used by configure script to generate Makefile
# @(#) Thorsten Otto, 04.07.2002
###########################################################

include ../silent.am

AM_CFLAGS=	$(LOCAL_CFLAGS) $(DEFS) $(XCFLAGS)
AM_LDFLAGS=	$(LOCAL_LDFLAGS) $(LIBS) $(XLDFLAGS)
AM_CPPFLAGS=	-I$(srcdir) -DBINDIR="\"$(bindir)\""

bin_PROGRAMS = udo
if !CROSS_COMPILING
noinst_SCRIPTS = $(build_triplet)-udo$(EXEEXT)
endif

LIBRCINTL_DEP = $(top_builddir)/rcintl/librcintl.a
LIBRCINTL = $(LIBRCINTL_DEP)

udo_SOURCES = \
	abo.c abo.h \
	cfg.c cfg.h \
	chr.c chr.h chr_all.h chr_ttf.h \
	commands.h \
	constant.h \
	debug.c debug.h \
	env.c env.h \
	export.h \
	file.c file.h \
	gui.h \
	img.c img.h img_eps.h img_html.h img_png.h img_stg.h img_win.h \
	import.h \
	kwset.c kwset.h \
	lang.c lang.h lang_utf.h \
	msg.c msg.h \
	obstack.c uobstack.h \
	par.c par.h \
	udoport.h \
	str.c str.h \
	sty.c sty.h \
	tab.c tab.h \
	toc.c toc.h toc_html.c toc_html.h \
	tp.c tp.h \
	udo.c udo.h udolocal.h \
	udo2pdf.h \
	udo2ps.h \
	udo_type.h \
	udocmd.h \
	udointl.c udointl.h \
	udomem.c udomem.h \
	udosym.c udosym.h \
	upr.c upr.h \
	unicode.h u_dos.h u_hp.h u_iso.h u_mac.h u_mswin.h u_next.h u_tos.h u_udo.h u_utf.h \
	version.h \
	cli.c

udo_LDADD = $(INTLLIBS)
udo_DEPENDENCIES =
if OS_WIN32
udo_DEPENDENCIES += $(LIBRCINTL_DEP)
endif

$(build_triplet)-udo$(EXEEXT): udo$(EXEEXT)
	cp -a $? $@

EXTRA_DIST = \
	AtariPC \
	BCB4 \
	MacOSX \
	OpenWatcom \
	Win32MSVC \
	lcc \
	images \
	kwset_malloc.c \
	makefile.inc

install-exec-local::
	-(cd $(DESTDIR)$(bindir); $(LN_S) udo $(host_triplet)-udo)
