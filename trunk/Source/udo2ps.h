/*	##############################################################
	# @(#) udo2ps.c
	# @(#)
	# @(#) Copyright (c) 1998 by Christian Krueger
	# @(#) (chrisker@freeyellow.com)
	#
	# This program is free software; you can redistribute it and/or
	# modify it under the terms of the GNU General Public License
	# as published by the Free Software Foundation; either version 2
	# of the License, or (at your option) any later version.
	# 
	# This program is distributed in the hope that it will be useful,
	# but WITHOUT ANY WARRANTY; without even the implied warranty of
	# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	# GNU General Public License for more details.
	# 
	# You should have received a copy of the GNU General Public License
	# along with this program; if not, write to the Free Software
	# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
	# 
	###############################################################*/

const char *UDO2PS=
	"%%!PS-Adobe-2.0\n"
	"%% ------------\n"
	"%% This is a very 'sophisticated' PostScript program.\n"
	"%% That's the reason why it doesn't use the DSC!\n"
	"%% It will not work under PostScript level 1!\n"
	"%% --------------------------------------------------\n"
	"%% UDO to PS V1.0 was written in 1998\n"
	"%% (c) by Christian 'chrisker' Kr\"uger\n"
	"%%     (chrisker@freeyellow.com)\n"
	"%% Extensions had been written in 2002\n"
	"%% (c) by Norbert Hanz\n"
	"%%     (norbert@familie-hanz.de)\n"
	"%% Use at own risk!\n"
	"%% --------------------------------------------------\n"
	"\n"
	"%%--- The set of 'private' variables\n"
	"\n"
	"/wordlen        0   def     %%--- aktuelle Wortlaenge\n"
	"/strlen         0   def     %%--- aktuelle Stringlaenge\n"
	"/linelen        0   def     %%--- aktuelle Zeilenlaenge \n"
	"/spacecounter   0   def     %%--- Anzahl der Spaces\n"
	"/spacewidth     0   def     %%--- initiale Weite eines Spaces\n"
	"\n"
	"/localvar       0       def\n"
	"/fontsize      11       def\n"
	"/basefont       2       def    %% 1 = Helvetica, 2 = Times-Roman\n"
	"/actualfont     0       def\n"
	"/actx           0       def\n"
	"/acty           0       def\n"
	"/underline      false   def\n"

	"/bold           false   def\n"

	"/descript       false   def\n"
	"/NodeName       ()      def\n"

	"/FootAuthor     ()      def\n"

	"\n"
	"/offCount       -1      def\n"

	"/offCountS      0       def\n"

	"/offList\n"

	"[/offList1 /offList2 /offList3 /offList4 () () () ()]\n"

	"def\n"

	"\n"
/* need for future use

	"100 string\n"

	"/oString exch def\n"

	"/oIndex 0 def\n"

	"100 string\n"

	"/Reset exch def\n"

	"/pAlign 0 def\n"

	"\n"*/
	"/UdoFonts\n"
	"[/UdoSwiss /UdoSwissItalic /UdoSwissBold /UdoSwissBoldItalic\n"
	" /UdoTimes /UdoTimesItalic /UdoTimesBold /UdoTimesBoldItalic\n"
	" /UdoCourier /UdoCourierItalic /UdoCourierBold /UdoCourierBoldItalic\n"

	" /UdoSymbol]\n"
	"def\n"
	"\n"
	"%%-- Procedures:\n"
	"\n"
	"/makeisomap          %% PRIVATE!\n"
	"{\n"
	"   findfont\n"
	"   dup length dict begin\n"
	"     {1 index /FID ne {def} {pop pop} ifelse} forall\n"
	"     /Encoding ISOLatin1Encoding def\n"
	"     currentdict\n"
	"   end\n"
	"   definefont pop\n"
	"}\n"
	"bind def\n"
	"\n"

/* Adobe Distiller doesn't konow anything about SymbolEncoding

   Smbols must done by Glyphs

	"%%-- for Symbol-Font\n"
	"/makeisomapSymbol          %% PRIVATE!\n"

	"{\n"

	"   findfont\n"

	"   dup length dict begin\n"

	"     {1 index /FID ne {def} {pop pop} ifelse} forall\n"

	"     /Encoding SymbolEncoding def\n"

	"     currentdict\n"

	"   end\n"

	"   definefont pop\n"

	"}\n"

	"bind def\n"

	"\n"*/

	"%%--------------------\n"
	"\n"
	"/setup               %% In: void\n"
	"{\n"
	"  /actx leftmargin def\n"
	"  /acty topmargin def\n"
	"  actx acty moveto\n"
	"  %%--- Setup the 12 fonts...\n"
	"  /UdoSwiss             /Helvetica             makeisomap\n"
	"  /UdoSwissItalic       /Helvetica-Oblique     makeisomap\n"
	"  /UdoSwissBold         /Helvetica-Bold        makeisomap\n"
	"  /UdoSwissBoldItalic   /Helvetica-BoldOblique makeisomap\n"
	"  /UdoTimes             /Times-Roman           makeisomap\n"
	"  /UdoTimesItalic       /Times-Italic          makeisomap\n"
	"  /UdoTimesBold         /Times-Bold            makeisomap\n"
	"  /UdoTimesBoldItalic   /Times-BoldItalic      makeisomap\n"
	"  /UdoCourier           /Courier               makeisomap\n"
	"  /UdoCourierItalic     /Courier-Oblique       makeisomap\n"
	"  /UdoCourierBold       /Courier-Bold          makeisomap\n"
	"  /UdoCourierBoldItalic /Courier-BoldQblique   makeisomap\n"
	"  /UdoSymbol            /Symbol                makeisomap\n"
	"  setUdoFont         \n"
	"}\n"
	"def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/newpage           %% In: void\n"
	"{\n"
	"  /fontmerk fontsize def\n"

	"  11 changeFontSize\n"

	"  bold true eq\n"

	"  { Boff\n"

	"   /Bmerk true def\n"

	"  } if\n"

	"\n"

	"  footout\n"

	"  /footnumbers 0 def\n"

	"  /lowermargin cclowermargin def\n"

	"  /Bmerk false def\n"

	"\n"

	"  ccleftmargin 2 sub cclowermargin 15 sub moveto\n"

	"  ccrightmargin cclowermargin 15 sub lineto\n"

	"  stroke\n"

	"\n"

	"  ccleftmargin cclowermargin 30 sub moveto\n"

	"  Ion NodeName udoshow\n"

	"  ccrightmargin FootAuthor stringwidth pop sub cclowermargin 30 sub moveto\n"

	"  FootAuthor udoshow Ioff\n"

	"\n"

	"  /strlen 0 def\n"
	"  /acty topmargin def\n"
	"  /actx leftmargin def\n"
	"  actx acty moveto\n"
	"\n"

	"  ccleftmargin cctopmargin moveto\n"

	"  /pagenumber pagenumber 1 add def\n"

	"  /Seite (Seite    ) def\n"

	"  Seite 6 pagenumber (xx) cvs putinterval\n"

	"  Ion Titeltext udoshow Seite Right setAlign Ioff\n"

	"\n"

	"  ccleftmargin 2 sub cctopmargin 5 sub moveto\n"

	"  ccrightmargin cctopmargin 5 sub lineto\n"

	"  stroke\n"

	"\n"

	"  /topmargin cctopmargin 30 sub def\n"

	"  Bmerk true eq\n"

	"  { Bon\n"

	"    /Bmerk false def\n"

	"  } if\n"

	"  fontmerk changeFontSize\n"

	"\n"

	"  showpage\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/newline            %% In: void\n"
	"{\n"
	"  /strlen 0 def                %% akt. Ausgabelaenge = 0\n"
	"	 foot\n"

	"  {\n"

	"  	/actx ccleftmargin 10 add def\n"

	"  	/acty acty fontsize sub def\n"

	"  }\n"

	"  {\n"

	"    /actx leftmargin def\n"
	"    /acty acty fontsize linespacing mul sub def\n"
	"    acty lowermargin lt\n"
	"    {\n"
	"      newpage\n"
	"    }\n"
	"    if\n"

	"  } ifelse\n"
	"  actx acty moveto\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/calcwordlen        %% PRIVATE! \n"
	"{\n"
	"    /wordlen\n"
	"    exch\n"
	"    stringwidth pop def\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/showout           %% PRIVATE!\n"
	"{\n"
	"    underline                        %% Unterstreichung beachten\n"
	"    { \n"
	"        currentpoint 3 -1 roll\n"
	"        show\n"
	"        currentpoint 4 2 roll\n"
	"        currentpoint 1 sub moveto   %% Unterstr. 1 Typopoint tiefer...\n"
	"        1 sub lineto\n"
	"        stroke moveto\n"
	"    }\n"
	"    {\n"
	"        show\n"
	"    }\n"
	"    ifelse\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/wordout            %% PRIVATE!\n"
	"{\n"
	"    exch\n"
	"    dup\n"
	"    () ne    %%-- Leere Strings ignorieren...\n"
	"    {\n"
	"      /strlen strlen wordlen add def\n"
	"      strlen linelen gt\n"
	"      {\n"
	"        newline\n"
	"        /strlen wordlen def\n"
	"      }\n"
	"      if\n"
	"         showout     %% -- Wort ausgeben\n"
	"      }\n"
	"     {\n"
	"       pop  %%-- Leerstring entfernen\n"
	"     }\n"
	"     ifelse\n"
	"     \n"
	"     {             %% Spaceflag auswerten...\n"
	"       showout   %% -- Space ausgeben\n"
	"       /strlen strlen spacewidth add def\n"
	"     }\n"
	"    if\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/udoshow            %% In: (String)\n"
	"{ \n"
	"  /linelen rightmargin leftmargin sub def\n"
	"  /spacewidth ( ) stringwidth pop def\n"
	"\n"
	"  {  \n"
	"    ( ) search      %%--- Spaces suchen\n"
	"    {               %%--- gefunden\n"
	"        dup            %%--- Wort duplizieren\n"
	"        calcwordlen\n"
	"        true        %%--- 2 x show (mit Space)        \n"
	"        wordout\n"
	"    }\n"
	"    {               %%--- kein Space gefunden\n"
	"        dup\n"
	"        calcwordlen\n"
	"        false       %%--- 1 x show\n"
	"        wordout\n"
	"        exit    \n"
	"    }\n"
	"    ifelse\n"
	"  }\n"
	"  loop\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"%%-- Fontprocs:\n"
	"\n"
	"/setUdoFont             %% PRIVATE!\n"
	"{\n"
	"    UdoFonts actualfont get fontsize selectfont\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/Ion                    %% In: void\n"
	"{\n"
	"   /actualfont actualfont 1 add def\n"
	"   setUdoFont\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/Ioff                   %% In: void\n"
	"{\n"
	"   /actualfont actualfont 1 sub def\n"
	"   setUdoFont\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/Bon                    %% In: void\n"
	"{\n"
	"   /actualfont actualfont 2 add def\n"
	"   setUdoFont\n"

	"   /bold true def\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/Boff                   %% In: void\n"
	"{\n"
	"   /actualfont actualfont 2 sub def\n"
	"   setUdoFont\n"

	"   /bold false def\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/Uon                    %% In: void\n"
	"{\n"
	"   /underline true def\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/Uoff                   %% In: void\n"
	"{\n"
	"   /underline false def\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/Von                    %% In: void\n"
	"{\n"
	"   /actualfont actualfont 3 basefont sub 4 mul add def\n"
	"   setUdoFont\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"                        %% In: void\n"
	"/Voff\n"
	"{\n"
	"   /actualfont actualfont 3 basefont sub 4 mul sub def\n"
	"   setUdoFont\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"

	"\n"

	"/Symbolon               %% In: void\n"

	"{\n"

	"   /remember actualfont def\n"

	"   /actualfont 12 def\n"

	"   setUdoFont\n"

	"}\n"

	"bind def\n"

	"\n"

	"%%--------------------\n"

	"\n"

	"/Symboloff              %% In: void\n"

	"{\n"

	"   /actualfont remember def\n"

	"   setUdoFont\n"

	"}\n"

	"bind def\n"

	"\n"

	"%%--------------------\n"

	"\n"

	"/setBaseFont         %% In: basefont\n"

	"{\n"

	"   1 basefont eq   %% Basis ist Helvetica\n"

	"   {\n"

	"     /actualfont 0 def\n"

	"     setUdoFont\n"

	"   }\n"

	"   {\n"

	"     /actualfont 4 def\n"

	"     setUdoFont\n"

	"   }\n"

	"   ifelse\n"

	"}\n"

	"bind def\n"

	"\n"

	"%%--------------------\n"
	"\n"
	"/changeBaseFont         %% In: void\n"
	"{\n"
	"   1 basefont eq\n"
	"   {\n"
	"     /basefont 2 def    %% Basis ist Times\n"
	"     actualfont 8 lt    %% -- Courier? -> nein -> gleich umschalten\n"
	"     {\n"
	"         /actualfont actualfont 4 add def\n"
	"         setUdoFont\n"
	"     }\n"
	"     if\n"
	"   }\n"
	"   {\n"
	"     /basefont 1 def    %% Basis ist Helvetica\n"
	"     actualfont 8 lt    %% -- Courier? -> nein -> gleich umschalten\n"
	"     {\n"
	"         /actualfont actualfont 4 sub def\n"
	"         setUdoFont\n"
	"     }\n"
	"     if\n"
	"   }\n"
	"   ifelse\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/changeFontSize        %% In: size\n"
	"{\n"
	"    /fontsize exch def\n"
	"    setUdoFont\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"%%-- Lists\n"
	"\n"
	"/description\n"

	"{\n"

	"  descript\n"

	"  {\n"

	"    /descript false def\n"

	"  }\n"

	"  {\n"

	"    /descript true def\n"

	"  } ifelse\n"

	"} bind def\n"

	"\n"
	"%%--------------------\n"
	"\n"
	"/addStrSpaceLeft        %% In: /var (String)\n"
	"{\n"
	"   /localvar exch stringwidth pop def\n"
	"   /leftmargin localvar leftmargin add def\n"
	"   localvar def\n"
	"		offList offCountS localvar put\n"

	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/addStrSpaceLeftList    %% In: /var [(String) (..)]\n"
	"{\n"
	"    /localvar 0 def\n"
	"    { stringwidth pop dup\n"
	"      localvar gt\n"
	"      {\n"
	"        /localvar exch def\n"
	"      }\n"
	"      {\n"
	"        pop\n"
	"      }\n"
	"      ifelse\n"
	"    }\n"
	"    forall\n"
	"       /leftmargin localvar leftmargin add def\n"
	"    localvar def\n"
	"}\n"
	"bind def \n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/subOffFromLeft         %% In: var\n"
	"{\n"
	"  /leftmargin exch leftmargin exch sub def\n"
	"  leftmargin acty moveto\n"

	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/writeBeforeLeft    %% In: (String) var\n"
	"{\n"
	"    /localvar exch def\n"

	"\n"

	"    newline\n"
	"%    leftmargin exch sub acty moveto\n"
	"    leftmargin localvar sub acty moveto\n"

	"    dup show\n"

	"\n"

	"    descript\n"

	"    {\n"

	"      calcwordlen\n"

	"      /strlen wordlen 10 add localvar sub def\n"

	"      currentpoint pop 10 add acty moveto\n"

	"    }\n"

	"    {\n"
	"      leftmargin acty moveto\n"

	"    } ifelse\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"\n"
	"/writeBulletLeft    %% In: (String) var\n"
	"{\n"
	"    newline\n"
	"     leftmargin 2 add exch sub acty moveto\n"
	"     glyphshow\n"
	"     leftmargin acty moveto\n"
	"}\n"
	"bind def\n"
	"\n"
	"%%--------------------\n"
	"%%-- GFX\n"
	"\n"
	"/hline              %% In: void\n"
	"{\n"
	"    newline\n"
	"    rightmargin acty lineto\n"
	"    stroke\n"
	"    newline\n"
	"}\n"
	"bind def\n"
	"\n"
	"%% --------------------------------------------------\n"
	"%% History:\n"

	"\n"

	"%% 27/04/1999\n"

	"%% Fehler bei den drei Verweisfunktionen beseitigt; der Link wurde nicht mit\n"

	"%% umgebrochen, wenn der auszugebende Text nicht mehr in die Zeile passte\n"

	"\n"

	"%% 28/04/1999\n"

	"%% Fehler bei der Enumerate-Umgebung\n"

	"%% Hinweis fÅr NameDest\n"

	"\n"

	"%% 14/05/1999\n"

	"%% Ausgabe von Fuûnoten\n"

	"%% Ausgabe von Kopf- und Fuûzeilen\n"

	"%% Hinweis fÅr die Description-Umgebung\n"

	"\n"

	"%% 17/05/1999\n"

	"%% Links zu anderen PDF-Dateien und Links innerhalb von PDF-Dateien kînnen\n"

	"%% jetzt auch als Bild dargestellt werden\n"

	"%% Der EPS-Code des AboutUDO-Images ist jetzt Teil der Datei postscript.ui\n"

	"\n"

	"\n"

	"%% ZusÑtzliche Funktionen fÅr die Postscriptausgabe\n"

	"%% 17.05.1999 Norbert Karl Hanz\n"

	"%% Version 1.3\n"

	"\n"

	"\n"

	"%% Damit der pdfmark-Operator nur im Distiller interpretiert wird\n"

	"/pdfmark where {pop} {userdict /pdfmark /cleartomark load put} ifelse\n"

	"/languagelevel where {pop languagelevel}{1} ifelse\n"

	"2 lt {\n"

	"    userdict (<<) cvn ([) cvn load put\n"

	"    userdict (>>) cvn (]) cvn load put\n"

	"} if\n"

	"\n"

	"% Default for 'How to open a document'\n"

	"  /Window false def\n"

	"  /Anordnung /SinglePage def\n"

	"  /Menubar false def\n"

	"  /Toolbar false def\n"

	"  /Seite 1 def\n"

	"  /Modus /UseNone def\n"

	"\n"

	"% Einige Definitionen zur Ausrichtung\n"

	"/Left 0 def\n"

	"/Center 1 def\n"

	"/Right 2 def\n"

	"/myAlign 0 def\n"

	"\n"

	"% Bild ist kein Link\n"

	"/Image false def\n"

	"\n"

	"/NImage 0 def     % Kein Link hinter dem Bild\n"

	"/WImage 1 def     % WebLink hinter dem Bild\n"

	"/FImage 2 def     % FileLink hinter dem Bild\n"

	"/LImage 3 def     % Link hinter dem Bild\n"

	"\n"

	"% Definition fÅr Description-Umgebung\n"

	"/descript false def\n"

	"\n"

	"% Definitionen fÅr die Kopfzeile\n"

	"/pagenumber 0 def\n"

	"/Seite (Seite    ) def\n"

	"\n"

	"% Definitionen fÅr die Fussnoten\n"

	"/footnumbers 0 def\n"

	"/footlines 1 def\n"

	"/strlentest 0 def\n"

	"/footnotetext 10 array def\n"

	"/foot false def\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"% Die Grundfarbe fÅr Text wird initalisiert\n"

	"\n"

	"/setBaseColor          % R G B setBaseColor -\n"

	"{\n"

	"  /bcb exch def\n"

	"  /bcg exch def\n"

	"  /bcr exch def\n"

	"\n"

	"  bcr bcg bcb setrgbcolor\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Wie wird die PDF-Datei geîffnet\n"

	"%% Bookmarks oder Thumbnails\n"

	"%% Welche Seite wird geîffnet\n"

	"\n"

	"/HowToOpen       % Modus Seite Toolbar Menubar Anordnung Window HowToOpen -\n"

	"{\n"

	"  /Window exch def\n"

	"  /Anordnung exch def\n"

	"  /Menubar exch def\n"

	"  /Toolbar exch def\n"

	"  /Seite exch def\n"

	"  /Modus exch def\n"

	"\n"

	"  [ /PageMode Modus /Page Seite\n"

	"  /DOCVIEW pdfmark\n"

	"\n"

	"  [{Catalog} << /ViewerPreferences << /HideToolbar Toolbar \n"

	"  /HideMenubar Menubar >> >>\n"

	"  /PUT pdfmark\n"

	"\n"

	"  [{Catalog} << /PageLayout Anordnung >>\n"

	"  /PUT pdfmark\n"

	"\n"

	"  [{Catalog} << /FitWindow Window >>\n"

	"  /PUT pdfmark\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Erzeugung von Bookmarks\n"

	"%% Als Ziel werden die benannten Ziele (Anker) benutzt\n"

	"%% Anzahl bezeichnet die Anzahl der Subnodes bzw. Susubnodes etc.\n"

	"%% Existieren keine Unterkapitel, bitte '0' Åbergeben\n"

	"%% Ist die Zahl positiv, werden die Bookmarks aufgeklappt,\n"

	"%% ist sie negativ sind die Bookmarks zugeklappt\n"

	"%% Achtung: zuerst mÅssen alle Nodes, dann die Subnodes etc. definiert werden\n"

	"\n"

	"/Bookmarks     % Title Ziel Anzahl Bookmarks -\n"

	"{\n"

	"  /Anzahl exch def\n"

	"  /Ziel exch def\n"

	"  /Title exch def\n"

	"  [ /Dest Ziel\n"

	"    /Title Title\n"

	"    /Count Anzahl\n"

	"  /OUT pdfmark\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Erzeugung von Weblinks\n"

	"%% Die Farbwerte kînnen zwischen 0 und 255 Åbergeben werden\n"

	"\n"

	"/WebLink        % Text Adresse R G B WebLink -\n"

	"{\n"

	"  /B exch def\n"

	"  /G exch def\n"

	"  /R exch def\n"

	"  /Adresse exch def\n"

	"  /Text exch def\n"

	"\n"

	"  Image          % Ist der Link ein Bild?\n"

	"  {\n"

	"    /Tx Text 0 get def\n"

	"    /Ty Text 1 get def\n"

	"    /Tw Text 2 get def\n"

	"    /Th Text 3 get def\n"

	"    [ /Rect [Tx Ty Tw Th]\n"

	"      /Border [0 0 0]\n"

	"      /Action << /Subtype /URI /URI Adresse >>\n"

	"      /Subtype /Link\n"

	"    /ANN pdfmark\n"

	"  }\n"

	"  {             % Link ist kein Bild\n"

	"    Text stringwidth pop\n"

	"    /wx exch def\n"

	"\n"

	"    /localvar strlen wx add def\n"

	"    localvar linelen gt\n"

	"    {\n"

	"      newline\n"

	"    } if\n"

	"%    localvar def\n"

	"\n"

	"    currentpoint\n"

	"    /y exch def\n"

	"    /x exch def\n"

	"    /y y fontsize add def\n"

	"    /x x wx add def\n"

	"    [ /Rect [currentpoint x y]\n"

	"      /Border [0 0 0]\n"

	"      /Action << /Subtype /URI /URI Adresse >>\n"

	"      /Subtype /Link\n"

	"    /ANN pdfmark\n"

	"    currentrgbcolor\n"

	"    R G B setrgbcolor\n"

	"    Uon Text udoshow Uoff\n"

	"    setrgbcolor\n"

	"  } ifelse\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Erzeugung von Links zu anderen PDF-Dateien\n"

	"%% Soll kein Anker Åbergeben werden 'Null' eingeben\n"

	"%% Die Farbwerte kînnen zwischen 0 und 255 Åbergeben werden\n"

	"\n"

	"/FileLink        % Text Datei Anker R G B FileLink -\n"

	"{\n"

	"  /B exch def\n"

	"  /G exch def\n"

	"  /R exch def\n"

	"  /Anker exch def\n"

	"  /Datei exch def\n"

	"  /Text exch def\n"

	"\n"

	"  Image          % Ist der Link ein Bild?\n"

	"  {\n"

	"    /Tx Text 0 get def\n"

	"    /Ty Text 1 get def\n"

	"    /Tw Text 2 get def\n"

	"    /Th Text 3 get def\n"

	"    [ /Rect [Tx Ty Tw Th]\n"

	"      /Border [0 0 0]\n"

	"      /Dest Anker\n"

	"      /File Datei\n"

	"      /Action /GoToR\n"

	"      /Subtype /Link\n"

	"    /ANN pdfmark\n"

	"  }\n"

	"  {             % Link ist kein Bild\n"

	"    Text stringwidth pop\n"

	"    /wx exch def\n"

	"\n"

	"    /localvar strlen wx add def\n"

	"    localvar linelen gt\n"

	"    {\n"

	"      newline\n"

	"    } if\n"

	"%    localvar 0 def\n"

	"\n"

	"    currentpoint\n"

	"    /y exch def\n"

	"    /x exch def\n"

	"    /y y fontsize add def\n"

	"    /x x wx add def\n"

	"    [ /Rect [currentpoint x y]\n"

	"      /Border [0 0 0]\n"

	"      /Dest Anker\n"

	"      /File Datei\n"

	"      /Action /GoToR\n"

	"      /Subtype /Link\n"

	"    /ANN pdfmark\n"

	"    currentrgbcolor\n"

	"    R G B setrgbcolor\n"

	"    Uon Text udoshow Uoff\n"

	"    setrgbcolor\n"

	"  } ifelse\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Erzeugung von Links innerhalb einer PDF-Datei\n"

	"%% Die Farbwerte kînnen zwischen 0 und 255 Åbergeben werden\n"

	"%% FÅr die Erzeugung eines Inhaltsverzeichnisses am besten\n"

	"%% 0 0 0 (schwarz) Åbergeben\n"

	"\n"

	"/Link        % Text Anker R G B Link -\n"

	"{\n"

	"  /B exch def\n"

	"  /G exch def\n"

	"  /R exch def\n"

	"  /Anker exch def\n"

	"  /Text exch def\n"

	"\n"

	"  Image          % Ist der Link ein Bild?\n"

	"  {\n"

	"    /Tx Text 0 get def\n"

	"    /Ty Text 1 get def\n"

	"    /Tw Text 2 get def\n"

	"    /Th Text 3 get def\n"

	"    [ /Rect [Tx Ty Tw Th]\n"

	"      /Border [0 0 0]\n"

	"      /Action /GoTo\n"

	"      /Dest Anker\n"

	"      /Subtype /Link\n"

	"    /ANN pdfmark\n"

	"  }\n"

	"  {             % Link ist kein Bild\n"

	"    Text stringwidth pop\n"

	"    /wx exch def\n"

	"\n"

	"    /localvar strlen wx add def\n"

	"    localvar linelen gt\n"

	"    {\n"

	"      newline\n"

	"    } if\n"

	"%    localvar 0 def\n"

	"\n"

	"    currentpoint\n"

	"    /y exch def\n"

	"    /x exch def\n"

	"    /y y fontsize add def\n"

	"    /x x wx add def\n"

	"    [ /Rect [currentpoint x y]\n"

	"      /Border [0 0 0]\n"

	"      /Action /GoTo\n"

	"      /Dest Anker\n"

	"      /Subtype /Link\n"

	"    /ANN pdfmark\n"

	"    currentrgbcolor\n"

	"    R G B setrgbcolor\n"

	"    Uon Text udoshow Uoff\n"

	"    setrgbcolor\n"

	"  } ifelse\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Erzeugung von Ankern\n"

	"\n"

	"/NameDest       % Name NameDest -\n"

	"{\n"

	"  /Name exch def\n"

	"  currentpoint\n"

	"  /y exch fontsize add def\n"

	"  /x exch def\n"

	"  [ /Dest Name\n"

	"    /View [ /XYZ null y null ]\n"

	"  /DEST pdfmark\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Erzeugung von Notizen\n"

	"%% Die Farbwerte kînnen als 1 oder 0 Åbergeben werden\n"

	"%% Es werden nur die Hauptfarben unterstÅtzt\n"

	"%% Die Notiz wird nur als Icon angezeigt und kann\n"

	"%% auf Doppelclick geîffnet werden\n"

	"\n"

	"/Comment        % Text Title R G B Comment -\n"

	"{\n"

	"  /B exch def\n"

	"  /G exch def\n"

	"  /R exch def\n"

	"  /Title exch def\n"

	"  /Text exch def\n"

	"  currentpoint\n"

	"  /y exch def\n"

	"  /x exch def\n"

	"  /wy y 150 sub def\n"

	"  /y y fontsize add def\n"

	"  [ /Rect [ 50 y 200 wy ]\n"

	"    /Open false\n"

	"    /Title Title\n"

	"    /Contents Text\n"

	"    /Color [R G B]\n"

	"  /ANN pdfmark\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Zentrierter Text\n"

	"%% Es wird nur der auszugebende Text Åbergeben\n"

	"\n"

	"/breite      % Text breite -\n"

	"{\n"

	"  /Text exch def\n"

	"  /Mitte rightmargin leftmargin sub 2 div def\n"

	"  Text stringwidth pop\n"

	"  /Breite exch def\n"

	"  /Halb Breite 2 div def\n"

	"  currentpoint exch pop\n"

	"  /y exch def\n"

	"  /x Mitte Halb sub leftmargin add def\n"

	"  x y moveto\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Text wird linksbÅndig, zentriert oder rechtsbÅndig ausgegeben\n"

	"\n"

	"/setAlign      % Text tAlign setAlign -\n"

	"{\n"

	"  /tAlign exch def\n"

	"  /Text exch def\n"

	"  /Mitte rightmargin leftmargin sub 2 div def\n"

	"  Text stringwidth pop\n"

	"  /Width exch def\n"

	"  /Halb Width 2 div def\n"

	"  currentpoint exch pop\n"

	"  /y exch def\n"

	"\n"

	"  tAlign 2 eq\n"

	"  {\n"

	"    /x rightmargin Width sub def\n"

	"  } if\n"

	"  tAlign 1 eq\n"

	"  {\n"

	"    /x Mitte Halb sub leftmargin add def\n"

	"  } if\n"

	"  tAlign 0 eq\n"

	"  {\n"

	"    /x actx def\n"

	"  } if\n"

	"\n"

	"  x y moveto\n"

	"  Text udoshow\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% About UDO german\n"

	"\n"

	"/aboutUDO_ger      % udo_rel_pl udo_os udo_url aboutUDO_ger -\n"

	"{\n"

	"  /udo_url exch def\n"

	"  /udo_os exch def\n"

	"  /udo_rel_pl exch def\n"

	"\n"

	"  11 changeFontSize\n"
	"  (Dieser Text wurde erzeugt mit) Center setAlign newline\n"
	"  18 changeFontSize newline\n"
	"  Bon (UDO) Center setAlign Boff newline\n"

	"  11 changeFontSize\n"
	"  udo_rel_pl Center setAlign newline\n"
	"  udo_os Center setAlign newline\n"
	"  newline \n"
	"  (Copyright \\251 1995-2001 by Dirk Hagedorn) Center setAlign newline\n"
	"  (UDO ist Open Source) Center setAlign newline\n"
	"  newline\n"
	"  (UDO ist ein Programm, welches Textdateien, die im) Center setAlign newline\n"
	"  (Universal Document Format erstellt wurden, in das ASCII-,) Center setAlign newline\n"
	"  (ST-Guide-, LaTeX-, Rich Text-, Pure-C-Help-, Manualpage-,) Center setAlign newline\n"
	"  (HTML-, WinHelp-, Texinfo-, Linuxdoc-SGML-, LyX-, Apple-QuickView-) Center setAlign newline\n"
	"  (und Turbo-Vision-Help-Format umwandeln kann.) Center setAlign newline\n"
	"  newline\n"
	"  (Weitere Informationen sowie die aktuellen Versionen findet man im World Wide Web unter) Center setAlign newline\n"
	"  udo_url breite\n"

	"  udo_url udo_url 0 0 255 WebLink\n"
	"} bind def\n"
	"\n"
	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% About UDO english\n"

	"\n"

	"/aboutUDO_eng      % udo_rel_pl udo_os udo_url aboutUDO_eng -\n"

	"{\n"

	"  /udo_url exch def\n"

	"  /udo_os exch def\n"

	"  /udo_rel_pl exch def\n"

	"\n"

	"  11 changeFontSize\n"
	"  (This text was made with) Center setAlign newline\n"
	"  18 changeFontSize newline\n"
	"  Bon (UDO) Center setAlign Boff newline\n"

	"  11 changeFontSize\n"
	"  udo_rel_pl Center setAlign newline\n"
	"  udo_os Center setAlign newline\n"
	"  newline\n"
	"  (Copyright \\251 1995-2001 by Dirk Hagedorn) Center setAlign newline\n"
	"  (UDO is Open Source) Center setAlign newline\n"
	"  newline\n"
	"  (UDO is a program that converts files that are written) Center setAlign newline\n"
	"  (in the Universal Document Format into ASCII, ST-Guide, LaTeX,) Center setAlign newline\n"
	"  (Rich Text Format, Pure C Help, Manualpage, HTML, WinHelp,) Center setAlign newline\n"
	"  (Texinfo, Linuxdoc-SGML, LyX, Apple QuickView and Turbo-Vision-Help.) Center setAlign newline\n"
	"  newline\n"

	"  (Further information and the current versions can be found at) Center setAlign newline\n"
	"  udo_url breite\n"

	"  udo_url udo_url 0 0 255 WebLink\n"

	"} bind def\n"
	"\n"
/* for future use

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Das About-UDO Bild wird ausgegeben (inkl. Link auf die Homepage)\n"

	"\n"

	"/imageAboutUdo\n"

	"{\n"

	"  /Mitte rightmargin leftmargin sub 2 div leftmargin add def\n"

	"  currentpoint\n"

	"  /Y exch def\n"

	"  /X exch def\n"

	"  /NY1 Y 31 sub def\n"

	"  /NX1 Mitte 44 sub def\n"

	"  /EPSsave save def\n"

	"  NX1 NY1 translate\n"

	"  4 4 scale\n"

	"\n"

	"  [{ImageAboutUdo} /SP pdfmark\n"

	"\n"

	"  EPSsave restore\n"

	"  /Image true def\n"

	"  /NX2 NX1 88 add def\n"

	"  /NY2 NY1 31 add def\n"

	"  [NX1 NY1 NX2 NY2] (http://www.udo-open-source.de) 0 0 255 WebLink\n"

	"  /Image false def\n"

	"  /acty NY1 6 sub def\n"

	"  newline\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Bildvorspann mit Ausrichtung\n"

	"%% öbergabe von Breite und Hîhe des Bildes\n"

	"%% öbergabe von Skalierung und Ausrichtung des Bildes\n"

	"\n"

	"/imagePre       % Width Height Sc iAlign imagePre -\n"

	"{\n"

	"  /iAlign exch def\n"

	"  /Sc exch def\n"

	"  /Height exch 4 Sc div div def\n"

	"  /Width exch 4 Sc div div def\n"

	"\n"

	"  newline       % Damit die Bilder nicht am Seitenende abgeschnitten werden\n"

	"\n"

	"  /Mitte rightmargin leftmargin sub 2 div leftmargin add def\n"

	"  currentpoint\n"

	"  /Y exch def\n"

	"  /X exch def\n"

	"\n"

	"  /Y Y Height sub def\n"

	"  Y lowermargin lt\n"

	"  {\n"

	"    newpage\n"

	"  } if\n"

	"  /Y acty def\n"

	"\n"

	"  /NY1 Y Height sub def\n"

	"\n"

	"  iAlign 2 eq\n"

	"  {\n"

	"    /NX1 rightmargin Width sub def\n"

	"  } if\n"

	"  iAlign 1 eq\n"

	"  {\n"

	"    /NX1 Mitte Width 2 div sub def\n"

	"  } if\n"

	"  iAlign 0 eq\n"

	"  {\n"

	"    /NX1 X def\n"

	"  } if\n"

	"  /EPSsave save def\n"

	"\n"

	"  NX1 NY1 translate\n"

	"  Sc Sc scale\n"

	"} bind def\n"

	"\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Bildnachspann mit wahlweiser Ausgabe eines Links\n"

	"\n"

	"/imagePost      % Width Height Adresse Anker Type imagePost -\n"

	"{\n"

	"  /Type exch def\n"

	"  /Anker exch def\n"

	"  /Adresse exch def\n"

	"  /Height exch def\n"

	"  /Width exch def\n"

	"\n"

	"  Adresse length 0 ne Anker /Null ne or   % Steckt hinter dem Bild ein Link o. Anker?\n"

	"  {\n"

	"    /Image true def\n"

	"    /NX2 NX1 Width add def\n"

	"    /NY2 NY1 Height add def\n"

	"    Type 1 eq\n"

	"    {\n"

	"      [NX1 NY1 NX2 NY2] Adresse 0 0 255 WebLink\n"

	"    } if\n"

	"    Type 2 eq\n"

	"    {\n"

	"      [NX1 NY1 NX2 NY2] Adresse Anker 0 0 255 FileLink\n"

	"    } if\n"

	"    Type 3 eq\n"

	"    {\n"

	"      [NX1 NY1 NX2 NY2] Anker 0 0 255 Link\n"

	"    } if\n"

	"    /Image false def\n"

	"  } if\n"

	"  /acty NY1 def\n"

	"  newline\n"

	"} bind def\n"

	"\n"

	"\n"*/

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% öbergabe der Fuûnoten\n"

	"\n"

	"/footnote          % Text footnote -\n"

	"{\n"

	"  /localstring ( ) def\n"

	"\n"

	"  /footlines 1 def\n"

	"  /Text exch def\n"

	"  Text udofoot\n"

	"  /lowermargin lowermargin fontsize footlines 1 add mul add def\n"

	"  /footnumbers footnumbers 1 add def\n"

	"\n"

	"  fontsize\n"

	"  9 changeFontSize\n"

	"  currentpoint\n"

	"  /fy exch 5 add def\n"

	"  fy moveto\n"

	"  footnumbers localstring cvs udoshow\n"

	"  currentpoint\n"

	"  /fy exch 5 sub def\n"

	"  fy moveto\n"

	"  changeFontSize\n"

	"  footnotetext footnumbers Text put\n"

	"} bind def\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Ausgabe der Fuûnoten\n"

	"\n"

	"/footout\n"

	"{\n"

	"  footnumbers 0 gt\n"

	"  {\n"

	"    /foot true def\n"

	"    /counter 0 def\n"

	"    /localstring (  ) def\n"

	"\n"

	"    ccleftmargin lowermargin 15 sub moveto\n"

	"    ccleftmargin 80 add lowermargin 15 sub lineto\n"

	"    stroke\n"

	"    ccleftmargin lowermargin 20 sub moveto\n"

	"\n"

	"    footnumbers\n"

	"    {\n"

	"      /counter counter 1 add def\n"

	"      currentpoint\n"

	"      /acty exch fontsize 1.5 mul sub def\n"

	"      pop\n"

	"      ccleftmargin acty moveto\n"

	"      fontsize dup\n"

	"      exch 2 sub changeFontSize\n"

	"      currentpoint\n"

	"      /acty exch 4 add def\n"

	"      acty moveto\n"

	"      counter localstring cvs udoshow\n"

	"      currentpoint\n"

	"      /acty exch 4 sub def\n"

	"      pop\n"

	"      /actx ccleftmargin 10 add def\n"

	"      actx acty moveto\n"

	"      changeFontSize\n"

	"      footnotetext counter get udoshow\n"

	"      /strlen 0 def\n"

	"    } repeat\n"

	"  } if\n"

	"  /foot false def\n"

	"  /footlines 1 def\n"

	"} bind def\n"

	"\n"

	"% ----------------------------------------------------------------------\n"

	"\n"

	"%% Hilfsfunktionen fÅr Fuûnoten\n"

	"\n"

	"/calcwordlenfoot        %% PRIVATE!\n"

	"{\n"

	"    /wordlentest\n"

	"    exch\n"

	"    stringwidth pop def\n"

	"}\n"

	"bind def\n"

	"\n"

	"\n"

	"/wordtest            %% PRIVATE!\n"

	"{\n"

	"  exch\n"

	"  dup\n"

	"  () ne    %%-- Leere Strings ignorieren...\n"

	"  {\n"

	"    /strlentest strlentest wordlentest add def\n"

	"    strlentest linelen gt\n"

	"    {\n"

	"      /footlines footlines 1 add def\n"

	"      /strlentest wordlentest def\n"

	"    } if\n"

	"%    showout     %% -- Wort ausgeben\n"

	"     pop\n"

	"  }\n"

	"  {\n"

	"    pop  %%-- Leerstring entfernen\n"

	"  } ifelse\n"

	"\n"

	"  {             %% Spaceflag auswerten...\n"

	"%    showout   %% -- Space ausgeben\n"

	"     pop\n"

	"    /strlentest strlentest spacewidth add def\n"

	"  } if\n"

	"}\n"

	"bind def\n"

	"\n"

	"%%--------------------\n"

	"\n"

	"/udofoot            %% In: (String)\n"

	"{\n"

	"  /linelen rightmargin 90 sub def\n"

	"  /spacewidth ( ) stringwidth pop def\n"

	"\n"

	"  {\n"

	"    ( ) search      %%--- Spaces suchen\n"

	"    {               %%--- gefunden\n"

	"        dup            %%--- Wort duplizieren\n"

	"        calcwordlenfoot\n"

	"        true        %%--- 2 x show (mit Space)\n"

	"        wordtest\n"

	"    }\n"

	"    {               %%--- kein Space gefunden\n"

	"        dup\n"

	"        calcwordlenfoot\n"

	"        false       %%--- 1 x show\n"

	"        wordtest\n"

	"        exit\n"

	"    }\n"

	"    ifelse\n"

	"  }\n"

	"  loop\n"

	"}\n"

	"bind def\n"

	"\n"

	"%%----------------------------------------------------------------\n"
	"%%--- This part is generated by UDO:\n";

