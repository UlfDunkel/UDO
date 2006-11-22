/*      ##############################################################
        # @(#) udo.c
        # @(#)
        # @(#) Copyright (c) 1995-2001 by Dirk Hagedorn
        # @(#) Dirk Hagedorn (udo@dirk-hagedorn.de)
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
        ##############################################################
        ##############################################################  */


#ifndef ID_LANG_C
#define ID_LANG_C
const char *id_lang_c= "@(#) lang.c       $Date$";
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "portab.h"

#include "version.h"    /* WICHTIGE Makros!                                     */
#include "constant.h"   /* WICHTIGE Makros!                                     */
#include "udo_type.h"   /* diverse Typen                                        */
#include "chr.h"        /* Zeichensatzumwandlungen                      */
#include "toc.h"        /* !node, !alias, !label, !toc          */
#include "udo.h"        /* globale Prototypen                           */

#include "export.h"


/*      ############################################################
        # Konstanten
        ############################################################    */
/*      ------------------------------------------------------
        Datum-Konstanten (Umlaut in Maerz besonders beachten!)
        Innerhalb init_lang() und init_lang_date() werden
        die Zeichen des "Universal Charset" angepasst.
        ------------------------------------------------------  */

/* Deutsch */
LOCAL const char *MONTH_GER[] =
{
   "Januar", "Februar", "M(!\"a)rz", "April", "Mai", "Juni",
   "Juli", "August", "September", "Oktober", "November", "Dezember"
};

/* Daenisch */ /* V6.5.18 */
LOCAL const char *MONTH_DAE[] =
{
   "Januar", "Februar", "Marts", "April", "Maj", "Juni",
   "Juli", "August", "September", "Oktober", "November", "December"
};

/* Niederlaendisch */
LOCAL const char *MONTH_DUT[] =
{
   "januari", "februari", "maart", "april", "mei", "juni",
   "juli", "augustus", "september", "oktober", "november", "december"
};

/* Englisch */
LOCAL const char *MONTH_ENG[] =
{
   "January", "February", "March", "April", "May", "June",
   "July", "August", "September", "October", "November", "December"
};

/* Franzoesisch */
LOCAL const char *MONTH_FRA[] =
{
   "janvier", "f(!'e)vrier", "mars", "avril", "mai", "juin",
   "juillet", "ao(!^u)t", "septembre", "octobre", "novembre", "d(!'e)cembre"
};

/* Italienisch */
LOCAL const char *MONTH_ITA[] =
{
   "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno",
   "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"
};

/* Schwedisch */
LOCAL const char *MONTH_SWE[] =
{
   "Januari", "Februari", "Mars", "April", "Maj", "Juni",
   "Juli", "Augusti", "September", "Oktober", "November", "December"
};

/* Spanisch */
LOCAL const char *MONTH_SPA[] =
{
   "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
   "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
};


/* Czech windows-1250 encoding */ /* V6.5.19 */
LOCAL const char *MONTH_CZE[] =
{
   "ledna", "(!'u)nora", "b(!\\o)ezna", "dubna", "kv(!`i)tna", "(!`e)ervna",
   "(!`e)ervence", "srpna", "z(!'a)(!\\o)(!'i)", "(!\\o)(!'i)jna", "listopadu", "prosince"
};

/* Czech x-mac-ce encoding */ /* V6.5.19 */
/* fd:20061122: temporarily faded as there is noone else using this stuff at the moment 
LOCAL const char *MONTH_CZE[] =
{
   "ledna", "œnora", "bÞezna", "dubna", "kvžtna", "‹ervna",
   "‹ervence", "srpna", "z‡Þ’", "Þ’jna", "listopadu", "prosince"
};
*/

   


/*      ############################################################
        # init_lang
        # Strings fuer die ausgewaehlte Sprache setzen (destlang)
        ############################################################    */

/*      --------------------------------------------------------------
        init_lang_date()
        Setzt Uhrzeit und Datum abhaengig von der jeweiligen Sprache
        --------------------------------------------------------------  */
GLOBAL void init_lang_date ( void )
{
   time_t      timer;        /* */
   struct tm  *zeit;         /* */
   int         old_charset;  /* */


   time(&timer);
   zeit = localtime(&timer);

   iDateDay   = zeit->tm_mday;  /* Global sichern z.B. fuer RTF */
   iDateMonth = zeit->tm_mon+1;
   iDateYear  = zeit->tm_year+1900;
   iDateHour  = zeit->tm_hour;
   iDateMin   = zeit->tm_min;
   iDateSec   = zeit->tm_sec;

   switch (destlang)
   {
   case TOENG:     /* Englisch */
      sprintf(lang.today, "%s %d, %d", MONTH_ENG[zeit->tm_mon], zeit->tm_mday, 1900+zeit->tm_year);
      sprintf(lang.short_today, "%0d/%02d/%02d", 1900+zeit->tm_year, zeit->tm_mon+1, zeit->tm_mday);
      break;

   case TOFRA:     /* Franzoesisch */
      sprintf(lang.today, "%d %s %d", zeit->tm_mday, MONTH_FRA[zeit->tm_mon], 1900+zeit->tm_year);
      sprintf(lang.short_today, "%02d.%02d.%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
      break;

   case TOITA:     /* Italienisch */
      sprintf(lang.today, "%d. %s %d", zeit->tm_mday, MONTH_ITA[zeit->tm_mon], 1900+zeit->tm_year);
      sprintf(lang.short_today, "%02d.%02d.%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
      break;

   case TOSWE:     /* Schwedisch */
      sprintf(lang.today, "%s %d, %d", MONTH_SWE[zeit->tm_mon], zeit->tm_mday, 1900+zeit->tm_year);
      sprintf(lang.short_today, "%0d-%02d-%02d", 1900+zeit->tm_year, zeit->tm_mon+1, zeit->tm_mday);
      break;

   case TOSPA:     /* Spanisch */
      sprintf(lang.today, "%d. %s %d", zeit->tm_mday, MONTH_SPA[zeit->tm_mon], 1900+zeit->tm_year);
      sprintf(lang.short_today, "%02d.%02d.%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
      break;

   case TODUT:     /* Hollaendisch */
      sprintf(lang.today, "%d %s %d", zeit->tm_mday, MONTH_DUT[zeit->tm_mon], 1900+zeit->tm_year);
      sprintf(lang.short_today, "%02d-%02d-%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
      break;

   case TODAN:     /* Daenisch */ /* V6.5.18 */
      sprintf(lang.today, "%d %s %d", zeit->tm_mday, MONTH_DAE[zeit->tm_mon], 1900+zeit->tm_year);
      sprintf(lang.short_today, "%02d-%02d-%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
      break;

   case TOCZE:     /* Czech */ /* v6.5.19 */
      sprintf(lang.today, "%d. %s %d", zeit->tm_mday, MONTH_CZE[zeit->tm_mon], 1900+zeit->tm_year);
      sprintf(lang.short_today, "%02d.%02d.%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
      break;

   default:        /* Deutsch ist default */
      sprintf(lang.today, "%d. %s %d", zeit->tm_mday, MONTH_GER[zeit->tm_mon], 1900+zeit->tm_year);
      sprintf(lang.short_today, "%02d.%02d.%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
   }


   uni2ascii(lang.today);

   old_charset = iCharset;          /* r6pl2: sonst wird M"arz falsch ausgegeben, */
   iCharset = SYSTEM_CHARSET;       /* falls man Latin1 fuer WinHelp benutzt. */

   auto_quote_chars(lang.today, TRUE);

   iCharset = old_charset;

}  /* init_lang_date */


/*      --------------------------------------------------------------
        init_lang() initialsisiert die von UDO benutzen Ausdrucke in
        der jeweiligen Sprache. Sonderzeichen muessen im Universal
        Charset angegeben werden.
        --------------------------------------------------------------  */
GLOBAL void init_lang ( void )
{
   memset(&lang, 0, sizeof(LANG));

   switch (destlang)       
   {
   case TODUT:     /* Rogier_Cobben@nextjk.stuyts.nl */
      strcpy(lang.preface,    "Voorwoord");
      strcpy(lang.chapter,    "Hoofdstuk");
      strcpy(lang.title,      "Titel");
      strcpy(lang.appendix,   "Bijlage");
      strcpy(lang.contents,   "Inhoud");
      strcpy(lang.listfigure, "Afbeeldingenlijst");
      strcpy(lang.listtable,  "Tabellenlijst");
      strcpy(lang.figure,     "Afbeelding");
      strcpy(lang.table,      "Tabel");
      strcpy(lang.index,      "Index");
      strcpy(lang.page,       "bladzijde");
      strcpy(lang.see,        "zie");
      strcpy(lang.also,       "zie ook");
      strcpy(lang.by,         "door");
      strcpy(lang.fur,        "for"); /* New in V6.5.2 [NHz] */
      strcpy(lang.up,         "&Omhoog");
      strcpy(lang.exit,       "Be i&ndigen");
      strcpy(lang.unknown,    "Onbekend");
      strcpy(lang.update,     "Last updated on");
      strcpy(lang.lcid,       "LCID=0x413 0x0 0x0 ;Dutch");   /* V6.5.18 */
      strcpy(lang.html_home,  "Home");
      strcpy(lang.html_up,    "Up");
      strcpy(lang.html_prev,  "Prev");
      strcpy(lang.html_next,  "Next");
      /* New in r6pl16 [NHz] */
      strcpy(lang.html_lang,  "nl");
      strcpy(lang.html_start, "Begin of the document");
      break;

   case TOENG:
      strcpy(lang.preface,    "Preface");
      strcpy(lang.chapter,    "Chapter");
      strcpy(lang.title,      "Title");
      strcpy(lang.appendix,   "Appendix");
      strcpy(lang.contents,   "Contents");
      strcpy(lang.listfigure, "List of Figures");
      strcpy(lang.listtable,  "List of Tables");
      strcpy(lang.figure,     "Figure");
      strcpy(lang.table,      "Table");
      strcpy(lang.index,      "Index");
      strcpy(lang.page,       "page");
      strcpy(lang.see,        "see");
      strcpy(lang.also,       "see also");
      strcpy(lang.by,         "by");
      strcpy(lang.fur,        "for"); /* New in V6.5.2 [NHz] */
      strcpy(lang.up,         "&Up");
      strcpy(lang.exit,       "E&xit");
      strcpy(lang.unknown,    "Unknown");
      strcpy(lang.update,     "Last updated on");
      strcpy(lang.lcid,       "LCID=0x409 0x0 0x0 ;English (USA)");
      strcpy(lang.html_home,  "Home");
      strcpy(lang.html_up,    "Up");
      strcpy(lang.html_prev,  "Prev");
      strcpy(lang.html_next,  "Next");
      /* New in r6pl16 [NHz] */
      strcpy(lang.html_lang,  "en");
      strcpy(lang.html_start, "Begin of the document");
      break;

   case TOFRA:             /* vergleiche german.sty von LaTeX */
      strcpy(lang.preface,    "Pr(!'e)face");
      strcpy(lang.chapter,    "Chapitre");
      strcpy(lang.title,      "Titre");
      strcpy(lang.appendix,   "Annexe");
      strcpy(lang.contents,   "Sommaire");    /* r6pl13: laut Didier Briel (ddc@imaginet.fr) */
      strcpy(lang.listfigure, "Table des figures");
      strcpy(lang.listtable,  "Liste des tableaux");
      strcpy(lang.figure,     "Figure");
      strcpy(lang.table,      "Tableau");
      strcpy(lang.index,      "Index");
      strcpy(lang.page,       "page");
      strcpy(lang.see,        "voir");
      strcpy(lang.also,       "voir aussi");
      strcpy(lang.by,         "de");
      strcpy(lang.fur,        "for"); /* New in V6.5.2 [NHz] */
      strcpy(lang.up,         "&Haut");
      strcpy(lang.exit,       "&Fin");
      strcpy(lang.unknown,    "Inconnu");
      strcpy(lang.update,     "Derni(!`e)re mise (!`a) jour le");             /* r6pl13: laut Didier Briel (ddc@imaginet.fr) */
      strcpy(lang.lcid,       "LCID=0x40c 0x0 0x0 ;Frensh (France)");
      strcpy(lang.html_home,  "Home");
      strcpy(lang.html_up,    "Up");
      strcpy(lang.html_prev,  "Prev");
      strcpy(lang.html_next,  "Next");
      /* New in r6pl16 [NHz] */
      strcpy(lang.html_lang,  "fr");
      strcpy(lang.html_start, "Begin of the document");

      /* Strings mit Sonderzeichen anpassen */
      uni2ascii(lang.preface);
     
      /* Changed in r6pl17 [NHz] */
      /* uni2ascii(lang.contents);*/
      uni2ascii(lang.update);
      break;

   case TOITA:                /* laut "g.morando@agora.stm.it" */
      strcpy(lang.preface,    "Prefazione");
      strcpy(lang.chapter,    "Capitolo");
      strcpy(lang.title,      "Titolo");
      strcpy(lang.appendix,   "Appendice");
      strcpy(lang.contents,   "Contenuto");
      strcpy(lang.listfigure, "Lista di Figure");
      strcpy(lang.listtable,  "Lista di Tabelle");
      strcpy(lang.figure,     "Figura");
      strcpy(lang.table,      "Tabella");
      strcpy(lang.index,      "Index");
      strcpy(lang.page,       "pagina");
      strcpy(lang.see,        "vedere");
      strcpy(lang.also,       "vedere anche");
      strcpy(lang.by,         "da");
      strcpy(lang.fur,        "for"); /* New in V6.5.2 [NHz] */
      strcpy(lang.up,         "S&u");
      strcpy(lang.exit,       "Uscita");
      strcpy(lang.unknown,    "Ignoto");
      strcpy(lang.update,     "Last updated on");
      strcpy(lang.lcid,       "LCID=0x410 0x0 0x0 ;Italian (Italy)");
      strcpy(lang.html_home,  "Home");
      strcpy(lang.html_up,    "Up");
      strcpy(lang.html_prev,  "Prev");
      strcpy(lang.html_next,  "Next");
      /* New in r6pl16 [NHz] */
      strcpy(lang.html_lang,  "it");
      strcpy(lang.html_start, "Begin of the document");
      break;

   case TOSPA:     /* Euro-Dictionary */
      strcpy(lang.preface,    "Prefacio");
      strcpy(lang.chapter,    "Cap(!`i)tulo");
      strcpy(lang.title,      "T(!`i)tulo");
      strcpy(lang.appendix,   "Ap(!`e)ndice");
      strcpy(lang.contents,   "Contenido");
      strcpy(lang.listfigure, "Lista de grabados");
      strcpy(lang.listtable,  "Lista de tablas");
      strcpy(lang.figure,     "Grabado");
      strcpy(lang.table,      "Tabla");
      strcpy(lang.index,      "(!`I)ndice");
      strcpy(lang.page,       "p(!`a)gina");
      strcpy(lang.see,        "ver");
      strcpy(lang.also,       "ver tambi(!`e)n");
      strcpy(lang.by,         "de");
      strcpy(lang.fur,        "for"); /* New in V6.5.2 [NHz] */
      strcpy(lang.up,         "Elevado");
      strcpy(lang.exit,       "Terminar");
      strcpy(lang.unknown,    "Desconocido");
      strcpy(lang.update,     "Last updated on");
      strcpy(lang.lcid,       "LCID=0x40a 0x0 0x0 ;Spanish (Traditional)");
      strcpy(lang.html_home,  "Home");
      strcpy(lang.html_up,    "Up");
      strcpy(lang.html_prev,  "Prev");
      strcpy(lang.html_next,  "Next");
      /* New in r6pl16 [NHz] */
      strcpy(lang.html_lang,  "es");
      strcpy(lang.html_start, "Begin of the document");
      
      /* Strings mit Sonderzeichen anpassen */
      uni2ascii(lang.chapter);
      uni2ascii(lang.title);
      uni2ascii(lang.appendix);
      uni2ascii(lang.index);
      uni2ascii(lang.page);
      uni2ascii(lang.also);
      break;
   
   case TOSWE:
      strcpy(lang.preface,    "F(!\"o)rord");
      strcpy(lang.chapter,    "Kapitel");
      strcpy(lang.title,      "Titel");
      strcpy(lang.appendix,   "Appendix");
      strcpy(lang.contents,   "Inneh(!.a)ll");
      strcpy(lang.listfigure, "Lista av Figurer");
      strcpy(lang.listtable,  "Lista av Tabeller");
      strcpy(lang.figure,     "Figurer");
      strcpy(lang.table,      "Tabeller");
      strcpy(lang.index,      "Index");
      strcpy(lang.page,       "Sida");
      strcpy(lang.see,        "se");
      strcpy(lang.also,       "se (!\"a)ven");
      strcpy(lang.by,         "av");
      strcpy(lang.fur,        "for"); /* New in V6.5.2 [NHz] */
      strcpy(lang.up,         "&Upp");
      strcpy(lang.exit,       "Avsluta");
      strcpy(lang.unknown,    "Unknown");
      strcpy(lang.update,     "Last updated on");
      strcpy(lang.lcid,       "LCID=0x41d 0x0 0x0 ;Swedish (Sweden)");
      strcpy(lang.html_home,  "Home");
      strcpy(lang.html_up,    "Up");
      strcpy(lang.html_prev,  "Prev");
      strcpy(lang.html_next,  "Next");
      /* New in r6pl16 [NHz] */
      strcpy(lang.html_lang,  "sv");
      strcpy(lang.html_start, "Begin of the document");
      
      /* Strings mit Sonderzeichen anpassen */
      uni2ascii(lang.preface);
      uni2ascii(lang.contents);
      uni2ascii(lang.also);
      break;
   
   case TODAN:                /* V6.5.18 */
      strcpy(lang.preface,    "Forord");
      strcpy(lang.chapter,    "Kapitel");
      strcpy(lang.title,      "Titel");
      strcpy(lang.appendix,   "Till(!&ae)g");
      strcpy(lang.contents,   "Indhold");
      strcpy(lang.listfigure, "Figur liste");
      strcpy(lang.listtable,  "Tabel liste");
      strcpy(lang.figure,     "Figur");
      strcpy(lang.table,      "Tabel");
      strcpy(lang.index,      "Indeks");
      strcpy(lang.page,       "Side");
      strcpy(lang.see,        "se");
      strcpy(lang.also,       "se ogs(!.a)");
      strcpy(lang.by,         "af");
      strcpy(lang.fur,        "for");
      strcpy(lang.up,         "Op");
      strcpy(lang.exit,       "Udgang");
      strcpy(lang.unknown,    "ukendt");
      strcpy(lang.update,     "sidst opdateret den");
      strcpy(lang.lcid,       "LCID=0x406 0x0 0x0 ;Danish)");
      strcpy(lang.html_home,  "Hjem");
      strcpy(lang.html_up,    "Op");
      strcpy(lang.html_prev,  "Tidligere");
      strcpy(lang.html_next,  "n(!&ae)ste");
      strcpy(lang.html_lang,  "da");
      strcpy(lang.html_start, "start af dokument");
      
      uni2ascii(lang.appendix);
      uni2ascii(lang.also);
      uni2ascii(lang.html_next);
      break;

   case TOCZE:
      strcpy(lang.preface,    "P(!\o)edmluva");
      strcpy(lang.chapter,    "Kapitola");
      strcpy(lang.title,      "Titul");
      strcpy(lang.appendix,   "P(!\o)(!'i)loha");
      strcpy(lang.contents,   "Obsah");
      strcpy(lang.listfigure, "Seznam obr(!'a)zk(!`u)");
      strcpy(lang.listtable,  "Seznam tabulek");
      strcpy(lang.figure,     "Obr(!'a)zek");
      strcpy(lang.table,      "Tabulka");
      strcpy(lang.index,      "Rejst(!\o)(!'i)k");
      strcpy(lang.page,       "strana");
      strcpy(lang.see,        "viz");
      strcpy(lang.also,       "viz t(!'e)ž");
      strcpy(lang.by,         "");
      strcpy(lang.fur,        "pro");
      strcpy(lang.up,         "Nahoru");
      strcpy(lang.exit,       "Odchod");
      strcpy(lang.unknown,    "Nen(!'i) zn(!'a)mo");
      strcpy(lang.update,     "Posledn(!'i) aktualizace");
      strcpy(lang.lcid,       "LCID=0x405 0x0 0x0 ;Czech");
      strcpy(lang.html_home,  "Dom(!`u)");
      strcpy(lang.html_up,    "Nahoru");
      strcpy(lang.html_prev,  "P(!\o)edchoz(!'i)");
      strcpy(lang.html_next,  "N(!'a)sleduj(!'i)c(!'i)");
      strcpy(lang.html_lang,  "cs");
      strcpy(lang.html_start, "Za(!`e)(!'a)tek dokumentu");

      uni2ascii(lang.preface);
      uni2ascii(lang.appendix);
      uni2ascii(lang.listfigure);
      uni2ascii(lang.figure);
      uni2ascii(lang.index);
      uni2ascii(lang.also);
      uni2ascii(lang.unknown);
      uni2ascii(lang.update);
      uni2ascii(lang.html_home);
      uni2ascii(lang.html_prev);
      uni2ascii(lang.html_next);
      uni2ascii(lang.html_start);
      break;

/* fd:20061122: x-mac-ce encoding temporarily faded
   case TOCZE:                     /* V6.5.18 */
      strcpy(lang.preface,    "PÞedmluva");
      strcpy(lang.chapter,    "Kapitola");
      strcpy(lang.title,      "Titul");
      strcpy(lang.appendix,   "PÞ’loha");
      strcpy(lang.contents,   "Obsah");
      strcpy(lang.listfigure, "Seznam obr‡zkó");
      strcpy(lang.listtable,  "Seznam tabulek");
      strcpy(lang.figure,     "Obr‡zek");
      strcpy(lang.table,      "Tabulka");
      strcpy(lang.index,      "RejstÞ’k");
      strcpy(lang.page,       "strana");
      strcpy(lang.see,        "viz");
      strcpy(lang.also,       "viz tŽì");
      strcpy(lang.by,         "");
      strcpy(lang.fur,        "pro"); /* New in V6.5.2 [NHz] */
      strcpy(lang.up,         "Nahoru");
      strcpy(lang.exit,       "Odchod");
      strcpy(lang.unknown,    "Nen’ zn‡mo");
      strcpy(lang.update,     "Posledn’ aktualizace");
      strcpy(lang.lcid,       "LCID=0x405 0x0 0x0 ;Czech");
      strcpy(lang.html_home,  "Domó");
      strcpy(lang.html_up,    "Nahoru");
      strcpy(lang.html_prev,  "PÞedchoz’");
      strcpy(lang.html_next,  "N‡sleduj’c’"); /* New in r6pl16 [NHz] */
      strcpy(lang.html_lang,  "cs");
      strcpy(lang.html_start, "Za‹‡tek dokumentu");
      break;
*/
   default:        /* Deutsch ist default */
      strcpy(lang.preface,    "Vorwort");
      strcpy(lang.chapter,    "Kapitel");
      strcpy(lang.title,      "Titel");
      strcpy(lang.appendix,   "Anhang");
      strcpy(lang.contents,   "Inhaltsverzeichnis");
      strcpy(lang.listfigure, "Abbildungsverzeichnis");
      strcpy(lang.listtable,  "Tabellenverzeichnis");
      strcpy(lang.figure,     "Abbildung");
      strcpy(lang.table,      "Tabelle");
      strcpy(lang.index,      "Index");
      strcpy(lang.page,       "Seite");
      strcpy(lang.see,        "siehe");
      strcpy(lang.also,       "siehe auch");
      strcpy(lang.by,         "von");
      strcpy(lang.fur,        "f(!\"u)r"); /* New in V6.5.2 [NHz] */
      strcpy(lang.up,         "&Hoch");
      strcpy(lang.exit,       "Bee&nden");
      strcpy(lang.unknown,    "Unbekannt");
      strcpy(lang.update,     "Letzte Aktualisierung am");    /*r6pl5: (!\"A)nderung */
      strcpy(lang.lcid,       "LCID=0x407 0x0 0x0 ;German (Germany)");
      strcpy(lang.html_home,  "Home");
      strcpy(lang.html_up,    "Up");
      strcpy(lang.html_prev,  "Prev");
      strcpy(lang.html_next,  "Next");
      /* New in r6pl16 [NHz] */
      strcpy(lang.html_lang,  "de");
      strcpy(lang.html_start, "Beginn des Dokumentes");
      
      uni2ascii(lang.fur); /* New in V6.5.2 [NHz] */
   }
   
   toc_init_lang();

}       /*init_lang*/

