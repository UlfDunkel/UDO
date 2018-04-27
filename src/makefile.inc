# ###################################################################
# @(#) Make Include File, used for all systems
# @(#) Dirk Hagedorn (udo@dirk-hagedorn.de), 1998/05/25
# ###################################################################

OBJS =	abo$(O) cfg$(O) chr$(O) env$(O) file$(O) img$(O) msg$(O) par$(O) str$(O) sty$(O) \
		tab$(O) toc$(O) tp$(O) udo$(O) udosym$(O) obstack$(O) kwset$(O) debug$(O) \
		udomem$(O) upr$(O)

HEAD = portab.h version.h constant.h udo_type.h debug.h udomem.h

all::	udo$(X)

abo$(O):	$(HEAD) abo.h commands.h cfg.h file.h sty.h toc.h udo.h

cfg$(O):	$(HEAD) cfg.h file.h str.h

chr$(O):	$(HEAD) chr.h msg.h str.h sty.h udo.h chr_all.h chr_ttf.h \
		ansi2dos.h chr_tos.h chr_437.h \
		chr_850.h chr_hp8.h chr_next.h chr_iso.h chr_mac.h \
		tos2iso.h 437iso.h 850iso.h hp82iso.h next2iso.h mac2iso.h

cli$(O):	$(HEAD) gui.h file.h cfg.h msg.h udo.h udosym.h

env$(O):	$(HEAD) env.h commands.h abo.h cfg.h chr.h file.h img.h msg.h \
		par.h str.h sty.h toc.h tp.h udo.h gui.h udo2ps.h udo2pdf.h

file$(O): $(HEAD) file.h str.h msg.h

img$(O):	$(HEAD) img.h chr.h env.h file.h msg.h str.h sty.h udo.h \
		img_html.h img_win.h img_stg.h img_eps.h img_png.h

msg$(O):	$(HEAD) msg.h udo.h toc.h gui.h

par$(O):	$(HEAD) commands.h chr.h file.h msg.h str.h sty.h toc.h \
		udo.h img.h

str$(O):	$(HEAD) str.h

sty$(O):	$(HEAD) sty.h commands.h chr.h msg.h str.h udo.h

tab$(O):	$(HEAD) tab.h commands.h chr.h env.h msg.h par.h str.h \
		sty.h toc.h udo.h gui.h

toc$(O):	$(HEAD) toc.h commands.h abo.h chr.h env.h file.h img.h \
		msg.h par.h str.h sty.h tp.h udo.h gui.h

tp$(O):	$(HEAD) tp.h commands.h chr.h env.h file.h img.h msg.h \
		str.h sty.h toc.h udo.h

udo$(O):	$(HEAD) udo.h abo.h cfg.h chr.h env.h file.h img.h msg.h \
		par.h str.h sty.h tab.h toc.h tp.h gui.h udosym.h

upr$(O):	$(HEAD)

udosym$(O):	$(HEAD) udosym.h msg.h commands.h

udomem$(O):	$(HEAD)

debug$(O):	$(HEAD)

obstack$(O):	obstack.h

kwset$(O):	kwset.h obstack.h

clean::
	-$(RM) *$(O)
	-$(RM) udo$(X)
