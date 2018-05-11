if CROSS_COMPILING
UDO=		$(build_triplet)-udo
UDO_DEP=
else
UDO=		$(top_builddir)/src/udo
UDO_DEP=	$(UDO)$(EXEEXT)
endif
MKDIRHIER=	mkdir -p
RMDIRHIER=	rm -rf
CP=		cp
MV=		mv

# check for explicit .exe here, hcp.ttp might be the ST-Guide compiler
HC31=		hcp.exe
HCRTF=		hcrtf
HHC=		hhc
CHMC=		chmc


EXTRA_DIST = udosh.u images

all:   winhelp4 hh
	@

win winhelp:: winhelp/udosh.hlp

winhelp/udosh.hlp: $(srcdir)/udosh.u
	$(MKDIRHIER) winhelp
	$(UDO) --win -o winhelp/udosh.rtf $(srcdir)/udosh.u
	 if test "`type $(HC31) 2>/dev/null`" = ""; then \
	   echo "WinHelp Help Compiler ($(HC31)) not found" >& 2; \
	 else \
	  (cd "winhelp"; \
	   $(HC31) udosh.hpj; \
	   $(HC31) udosh.hpj \
	  ); \
	fi

win4 winhelp4:: winhelp4/udosh.hlp

winhelp4/udosh.hlp: $(srcdir)/udosh.u
	$(MKDIRHIER) winhelp4
	$(UDO) --win4 -o winhelp4/udosh.rtf $(srcdir)/udosh.u
	 if test "`type $(HCRTF) 2>/dev/null`" = ""; then \
	   echo "WinHelp4 Help Compiler ($(HCRTF)) not found" >& 2; \
	 else \
	   ( \
	   cd "winhelp4"; \
	   $(RM) udosh.HLP udosh.hlp; \
	   $(HCRTF) -x -NG udosh.hpj; \
	   $(HCRTF) -x -NG udosh.hpj; \
	   ); \
	fi

hh htmlhelp:: htmlhelp/udosh.chm

htmlhelp/udosh.chm: $(srcdir)/udosh.u
	$(MKDIRHIER) htmlhelp
	($(CP) $(srcdir)/images/*.gif htmlhelp; \
	$(UDO) --htmlhelp -o htmlhelp/udosh.html $(srcdir)/udosh.u || exit 1; \
	hhc="`type -p $(CHMC) 2>/dev/null`"; \
	if test "$$hhc" = ""; then \
	 hhc="`type -p $(HHC) 2>/dev/null`"; \
	fi; \
	if test "$$hhc" = ""; then \
	 echo "HTML Help Compiler ($(HHC)) not found" >& 2; \
	 else \
	(cd htmlhelp; \
	 "$$hhc" udosh.hhp; \
	 test -f udosh.chm || exit 1 \
	); \
	fi)

clean-local:
	for i in amguide applehelp ascii html htmlhelp ipf lyx manpage nroff c pascal pdflatex ps quickvw rtf texinfo tvhelp winhelp winhelp4; do \
		$(RMDIRHIER) $$i; \
	done

#
# There are several output formats that generate
# the same log file names, and automatically generated
# images may be the same for some, so we cant run anything
# in parallel here:
.NOTPARALLEL:
