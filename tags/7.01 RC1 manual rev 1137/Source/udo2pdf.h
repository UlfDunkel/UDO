/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : udo2pdf.h
*  Symbol prefix: udo2pdf
*
*  Copyright    : 2002 Norbert Hanz
*  Open Source  : 
*                 This program is free software; you can redistribute it and/or
*                 modify it under the terms of the GNU General Public License
*                 as published by the Free Software Foundation; either version 2
*                 of the License, or (at your option) any later version.
*                 
*                 This program is distributed in the hope that it will be useful,
*                 but WITHOUT ANY WARRANTY; without even the implied warranty of
*                 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*                 GNU General Public License for more details.
*                 
*                 You should have received a copy of the GNU General Public License
*                 along with this program; if not, write to the Free Software
*                 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
*  Description  : ???
*
*
*-------------------------------------------------------------------------------
*
*  Author       : Norbert Hanz (norbert@familie-hanz.de) NHz
*  Co-Authors   : Gerhard Stoll (ggs)
*                 Ulf Dunkel (fd)
*  Write access : ggs, fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - check if this huge 'string' can be handled in a way which 
*                   does not make Linux gcc complain (in -pedantic mode only):
*
*                  "string length '14134' is greater than the length '509' ISO C90
*                   compilers are required to support"
*
*-------------------------------------------------------------------------------
*  History:
*
*  1999:
*    NHz Apr 27: error fixed in three reference functions; link wasn't wrapped
*                  when text didn't fit in a line
*    NHz Apr 28: - error in enumerate environment fixed
*                - hint for NameDest
*    NHz May 14: - footnote output
*                - header/footer lines output
*                - hint for description environment
*    NHz May 17: - links to other PDF files and links within PDF files can be 
*                  indicated by an image now
*                - EPS code of the AboutUDO image now in postscript.ui
*  2009:
*    ggs Jan 11: year updated
*  2010:
*    fd  May 20: - old history stuff added to header and removed from UDO2PDF
*                - year updated
*                - AboutUDO texts adjusted to changes in manual
*
******************************************|************************************/

const char *UDO2PDF=
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
   "% Definition fuer Description-Umgebung\n"
   "/descript false def\n"
   "\n"
   "% Definitionen fuer die Kopfzeile\n"
   "/pagenumber 0 def\n"
   "/Seite (Seite    ) def\n"
   "\n"
   "% Definitionen fuer die Fussnoten\n"
   "/footnumbers 0 def\n"
   "/footlines 1 def\n"
   "/strlentest 0 def\n"
   "/footnotetext 10 array def\n"
   "/foot false def\n"
   "\n"
   "% ----------------------------------------------------------------------\n"
   "\n"
   "% Die Grundfarbe fuer Text wird initalisiert\n"
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
   "%% Wie wird die PDF-Datei geoeffnet\n"
   "%% Bookmarks oder Thumbnails\n"
   "%% Welche Seite wird geoeffnet\n"
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
   "%% Existieren keine Unterkapitel, bitte '0' uebergeben\n"
   "%% Ist die Zahl positiv, werden die Bookmarks aufgeklappt,\n"
   "%% ist sie negativ sind die Bookmarks zugeklappt\n"
   "%% Achtung: zuerst muessen alle Nodes, dann die Subnodes etc. definiert werden\n"
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
   "%% Die Farbwerte koennen zwischen 0 und 255 uebergeben werden\n"
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
   "    localvar def\n"
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
   "%% Soll kein Anker uebergeben werden 'Null' eingeben\n"
   "%% Die Farbwerte koennen zwischen 0 und 255 uebergeben werden\n"
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
   "%% Die Farbwerte koennen zwischen 0 und 255 uebergeben werden\n"
   "%% Fuer die Erzeugung eines Inhaltsverzeichnisses am besten\n"
   "%% 0 0 0 (schwarz) uebergeben\n"
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
   "%% Die Farbwerte koennen als 1 oder 0 uebergeben werden\n"
   "%% Es werden nur die Hauptfarben unterstuetzt\n"
   "%% Die Notiz wird nur als Icon angezeigt und kann\n"
   "%% auf Doppelclick geoeffnet werden\n"
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
   "%% Es wird nur der auszugebende Text uebergeben\n"
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
   "%% Text wird linksbuendig, zentriert oder rechtsbuendig ausgegeben\n"
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
   "  (Copyright \\251 2001-2010 by The UDO Community) Center setAlign newline\n"
   "  (UDO ist Open Source) Center setAlign newline\n"
   "  newline\n"
   "  (UDO ist ein Programm, mit dem Sie Textdateien, die im) Center setAlign newline\n"
   "  (Universal-Document-Format erstellt wurden,) Center setAlign newline\n"
   "  (in ueber 25 Zielformate umwandeln koennen.) Center setAlign newline\n"
   "  newline\n"
   "  (Weitere Informationen sowie die aktuellen Versionen finden Sie im Internet unter) Center setAlign newline\n"
   "  udo_url breite\n"
   "  udo_url udo_url 0 0 255 WebLink\n"
   "} bind def\n"
   "\n"
   "% ----------------------------------------------------------------------\n"
   "\n"
   "%% About UDO English\n"
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
   "  (Copyright \\251 2001-2010 by The UDO Community) Center setAlign newline\n"
   "  (UDO is Open Source) Center setAlign newline\n"
   "  newline\n"
   "  (UDO is a program that converts files which you have written) Center setAlign newline\n"
   "  (in the Universal Document Format,) Center setAlign newline\n"
   "  (into more than 25 different target formats.) Center setAlign newline\n"
   "  newline\n"
   "  (Get further information and the current versions on the Internet at) Center setAlign newline\n"
   "  udo_url breite\n"
   "  udo_url udo_url 0 0 255 WebLink\n"
   "} bind def\n"
   "\n"
   "% ----------------------------------------------------------------------\n"
   "\n"
   "%% Uebergabe der Fussnoten\n"
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
   "%% Ausgabe der Fussnoten\n"
   "\n"
   "/footout\n"
   "{\n"
   "  footnumbers 0 gt\n"
   "  {\n"
   "    /foot true def\n"
   "    /counter 0 def\n"
   "    /localstring (  ) def\n"
   "\n"
   "    myleftmargin lowermargin 15 sub moveto\n"
   "    myleftmargin 80 add lowermargin 15 sub lineto\n"
   "    stroke\n"
   "    myleftmargin lowermargin 20 sub moveto\n"
   "\n"
   "    footnumbers\n"
   "    {\n"
   "      /counter counter 1 add def\n"
   "      currentpoint\n"
   "      /acty exch fontsize 1.5 mul sub def\n"
   "      pop\n"
   "      myleftmargin acty moveto\n"
   "      fontsize dup\n"
   "      exch 2 sub changeFontSize\n"
   "      currentpoint\n"
   "      /acty exch 4 add def\n"
   "      acty moveto\n"
   "      counter localstring cvs udoshow\n"
   "      currentpoint\n"
   "      /acty exch 4 sub def\n"
   "      pop\n"
   "      /actx myleftmargin 10 add def\n"
   "      actx acty moveto\n"
   "      changeFontSize\n"
   "      footnotetext counter get udoshow\n"
   "      /strlen 0 def\n"
   "    } repeat\n"
   "  } if\n"
   "  /foot false def\n"
   "} bind def\n"
   "\n"
   "% ----------------------------------------------------------------------\n"
   "\n"
   "%% Hilfsfunktionen fuer Fussnoten\n"
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
   "% ----------------------------------------------------------------------\n"
   "\n"
   "%% Ein- und Ausschalten der Description-Umgebung\n"
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
   "\n"
   "% ----------------------------------------------------------------------\n"
   "%%--- This part is generated by UDO:\n";