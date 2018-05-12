/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : lang_utf.h
*  Symbol prefix: lang
*
*  Description  : This file handles all language-specific, localizable strings 
*                 used by UDO. Keep in mind that the localizable strings are 
*                 UTF-8 encoded since UDO v7. - Again:
*
*         --->    THIS FILE IS UTF-8 ENCODED !!!   <---
*         --->    THIS FILE IS UTF-8 ENCODED !!!   <---
*         --->    THIS FILE IS UTF-8 ENCODED !!!   <---
*
*  Copyright    : 1995-2001 Dirk Hagedorn
*  Open Source  : since 2001
*
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
*  Localizators : cs:  Petr Jandík, CZ-PRAHA
*                 da:  Henning Nymand, DK-NORRE ALSLEV
*                 de:  <various UDO developers>
*                 en:  <various UDO developers>
*                 es:  Manuel Angel Amaro Carmona, Venezuela (dassault.sis@gmail.com)
*                 fr:  corrections by Didier Briel (ddc@imaginet.fr)
*                 it:  - g.morando@agora.stm.it
*                      - Sergio Febo, IT
*                 ja:  Koichi MATSUMOTO
*                 lv:  Mārtiņš Zemzaris, LV
*                 nl:  - Rogier Cobben (rogier_cobben@nextjk.stuyts.nl)
*                      - Paul Pasveer, NL-LEEUWARDEN
*                      - Alexander Henket, NL-ROTTERDAM
*                 pl:  Dominik Siecinski, PL-LESZNO
*                 sv:  Karl-Johan Norén, SE-VÄRNAMO
*
*-------------------------------------------------------------------------------
*
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 19: file introduced (extracted from LANG.C)
*    fd  May 19: new: LANG.degree
*    fd  Sep 11: tiny adjustments to esp. better reflect multiple translators
*  2011:
*    fd  Aug 09: more nl strings adjusted
*    fd  Aug 29: more es strings adjusted by Angel Carmona
*  2012:
*    fd  Feb 01: html_home localized to Spanish
*  2013:
*    fd  Feb 15: Japanese added (Microsoft Translator; not verified yet)
*    fd  May 02: UDOSTRINGS resorted
*    fd  Jun 03: some Japanese strings updated (by Koichi MATSUMOTO)
*    fd  Jun 03: lang.html_up removed (unused so far)
*  2015:
*    fd  Feb 03: more Portuguese words added
*  2017:
*    fd  Feb 07: Russian added
*    fd  Feb 08: localized copyright string added
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "constant.h"                     /* TOGER, etc. */
#include "udo_type.h"                     /* LANG */




/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define MONTH_LEN  50                     /* Byte (!) length of localized month name */





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _udostrings
{
   int          lan;                      /* TOGER, etc. */
   const LANG   udostring;                /* localized UDO strings (UDO_TYPE.H) */
   const char *month[12];                 /* 12, of course ;-)) */
}  _UDOSTRINGS;





/*******************************************************************************
*
*     GLOBAL INITIALIZED CONSTANTS
*
******************************************|************************************/

/* for i in 01 02 03 04 05 06 07 08 09 10 11 12; do LANG=xx.utf8 date --date=2016-$i-01 +%B; done */

/*
 * English must be first the entry,
 * because it contains the strings marked for translation.
 * Everything else is looked up through the identifier field
 */
LOCAL _UDOSTRINGS const UDOSTRINGS[] =              /* localized UDO strings */
{
   /*
    * Note: The comments here are LEFT to the values, because you may 
    * ----- want to see and edit this file in a 1-byte C sourcecode editor,
    *       which shows Unicode characters as various numbers of bytes
    */
    
   {
      TOENG,
      {
         /* preface     */    N_("Preface"),
         /* chapter     */    N_("Chapter"),
         /* title       */    N_("Title"),
         /* appendix    */    N_("Appendix"),
         /* contents    */    N_("Contents"),
         /* listfigure  */    N_("List of Figures"),
         /* listtable   */    N_("List of Tables"),
         /* figure      */    N_("Figure"),
         /* table       */    N_("Table"),
         /* index       */    N_("Index"),
         /* page        */    N_("page"),
         /* see         */    N_("see"),
         /* also        */    N_("see also"),
         /* by          */    N_("by"),
         /* fur         */    N_("for"),
         /* up          */    N_("&Up"),
         /* exit        */    N_("E&xit"),
         /* unknown     */    N_("Unknown"),
         /* update      */    N_("Last updated on"),
         /* lcid        */    N_("0x409"),
         /* html_home   */    N_("Home"),
         /* html_up     */    N_("Up"),
         /* html_prev   */    N_("Prev"),
         /* html_next   */    N_("Next"),
         /* html_lang   */    "en",
         /* html_start  */    N_("Begin of the document"),
         /* translator  */    N_("Translation:"),
         /* distributor */    N_("Distributor:"),
         /* tex_stylename */  NC_("tex_stylename", "english"),
         /* lyx_langname */   NC_("lyx_langname", "english"),
         /* degree      */    N_("degree"),
         /* copyright   */    N_("Copyright"),
         /*
          * 1st arg: year
          * 2nd arg: month name
          * 3rd arg: day of month
          */
         /* today       */    NC_("today", "%2$s %3$d, %1$d"),
         /*
          * 1st arg: year
          * 2nd arg: month
          * 3rd arg: day of month
          */
         /* short_today */    NC_("short_today", "%1$0d/%2$02d/%3$02d")
      },
      {
      	 N_("January"),
      	 N_("February"),
      	 N_("March"),
      	 N_("April"),
      	 N_("May"),
      	 N_("June"),
      	 N_("July"),
      	 N_("August"),
      	 N_("September"),
      	 N_("October"),
      	 N_("November"),
      	 N_("December")
      }
   },
   {
      TOCZE,                              /* Czech */
      {
         /* preface     */    "Předmluva",
         /* chapter     */    "Kapitola",
         /* title       */    "Titul",
         /* appendix    */    "Příloha",
         /* contents    */    "Obsah",
         /* listfigure  */    "Seznam obrázků",
         /* listtable   */    "Seznam tabulek",
         /* figure      */    "Obrázek",
         /* table       */    "Tabulka",
         /* index       */    "Rejstřík",
         /* page        */    "strana",
         /* see         */    "viz",
         /* also        */    "viz též",
         /* by          */    "o",
         /* fur         */    "pro",
         /* up          */    "Nahoru",
         /* exit        */    "Odchod",
         /* unknown     */    "Není známo",
         /* update      */    "Poslední aktualizace",
         /* lcid        */    "0x405",
         /* html_home   */    "Domů",
         /* html_up     */    "Nahoru",
         /* html_prev   */    "Předchozí",
         /* html_next   */    "Následující",
         /* html_lang   */    "cs",
         /* html_start  */    "Začátek dokumentu",
         /* translator  */    "Překládání:",
         /* distributor */    "Distributor:",
         /* tex_stylename */  "czech",
         /* lyx_langname */   "czech",
         /* degree      */    "stupeň",
         /* copyright   */    "Autorská práva",
         /* today       */    "%3$d. %2$s %1$d",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
      	 "leden",
      	 "únor",
      	 "březen",
      	 "duben",
      	 "květen",
      	 "červen",
      	 "červenec",
      	 "srpen",
      	 "září",
      	 "říjen",
      	 "listopad",
      	 "prosinec"
      }
   },
   {
      TODAN,                              /* Danish */
      {
         /* preface     */    "Forord",
         /* chapter     */    "Kapitel",
         /* title       */    "Titel",
         /* appendix    */    "Tillæg",
         /* contents    */    "Indhold",
         /* listfigure  */    "Figur liste",
         /* listtable   */    "Tabel liste",
         /* figure      */    "Figur",
         /* table       */    "Tabel",
         /* index       */    "Indeks",
         /* page        */    "Side",
         /* see         */    "se",
         /* also        */    "se også",
         /* by          */    "af",
         /* fur         */    "for",
         /* up          */    "&Op",
         /* exit        */    "&Udgang",
         /* unknown     */    "ukendt",
         /* update      */    "sidst opdateret den",
         /* lcid        */    "0x406",
         /* html_home   */    "Hjem",
         /* html_up     */    "Op",
         /* html_prev   */    "Tidligere",
         /* html_next   */    "næste",
         /* html_lang   */    "da",
         /* html_start  */    "start af dokument",
         /* translator  */    "Oversættelse:",
         /* distributor */    "Distributor:",
         /* tex_stylename */  "danish",
         /* lyx_langname */   "danish",
         /* degree      */    "grad",
         /* copyright   */    "Ophavsret",
         /* today       */    "%3$d %2$s %1$d",
         /* short_today */    "%3$02d-%2$02d-%1$d"
      },
      {
      	 "januar",
      	 "februar",
      	 "marts",
      	 "april",
      	 "maj",
      	 "juni",
      	 "juli",
      	 "august",
      	 "september",
      	 "oktober",
      	 "november",
      	 "december"
      }
   },
   {
      TODUT,                              /* Dutch */
      {
         /* preface     */    "Voorwoord",
         /* chapter     */    "Hoofdstuk",
         /* title       */    "Titel",
         /* appendix    */    "Bijlage",
         /* contents    */    "Inhoud",
         /* listfigure  */    "Afbeeldingenlijst",
         /* listtable   */    "Tabellenlijst",
         /* figure      */    "Afbeelding",
         /* table       */    "Tabel",
         /* index       */    "Index",
         /* page        */    "bladzijde",
         /* see         */    "zie",
         /* also        */    "ook",
         /* by          */    "door",
         /* fur         */    "voor",
         /* up          */    "&Omhoog",
         /* exit        */    "Beëi&ndigen",
         /* unknown     */    "Onbekend",
         /* update      */    "Laatst gewijzigd op",
         /* lcid        */    "0x413",
         /* html_home   */    "Start",
         /* html_up     */    "Omhoog",
         /* html_prev   */    "Vorige",
         /* html_next   */    "Volgende",
         /* html_lang   */    "nl",
         /* html_start  */    "Begin van het document",
         /* translator  */    "Vertaling:",
         /* distributor */    "Distributeur:",
         /* tex_stylename */  "dutch",
         /* lyx_langname */   "dutch",
         /* degree      */    "graad",
         /* copyright   */    "Auteursrechten",
         /* today       */    "%3$d %2$s %1$d",
         /* short_today */    "%3$02d-%2$02d-%1$d"
      },
      {
      	 "januari",
      	 "februari",
      	 "maart",
      	 "april",
      	 "mei",
      	 "juni",
      	 "juli",
      	 "augustus",
      	 "september",
      	 "oktober",
      	 "november",
      	 "december"
      }
   },
   {
      TOFIN,                              /* Finnish */
      {
         /* preface     */    "Esipuhe",
         /* chapter     */    "Luku",
         /* title       */    "Title",
         /* appendix    */    "Liite",
         /* contents    */    "Sisältö",
         /* listfigure  */    "Kuvat",
         /* listtable   */    "Taulukot",
         /* figure      */    "Kuva",
         /* table       */    "Taulukko",
         /* index       */    "Hakemisto",
         /* page        */    "Sivu",
         /* see         */    "katso",
         /* also        */    "katso myös",
         /* by          */    "by",
         /* fur         */    "for",
         /* up          */    "&Ylös",
         /* exit        */    "E&xit",
         /* unknown     */    "tuntematon",
         /* update      */    "viimeksi päivitetty",
         /* lcid        */    "0x40b",
         /* html_home   */    "Home",
         /* html_up     */    "Ylös",
         /* html_prev   */    "Edellinen",
         /* html_next   */    "Seuraava",
         /* html_lang   */    "fi",
         /* html_start  */    "aloittaa asiakirjan",
         /* translator  */    "Kääntäminen:",
         /* distributor */    "Distributor:",
         /* tex_stylename */  "finnish",
         /* lyx_langname */   "finnish",
         /* degree      */    "aste",
         /* copyright   */    "Tekijänoikeus",
         /* today       */    "%3$d. %2$s %1$d",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
      	 "tammikuu",
      	 "helmikuu",
      	 "maaliskuu",
      	 "huhtikuu",
      	 "toukokuu",
      	 "kesäkuu",
      	 "heinäkuu",
      	 "elokuu",
      	 "syyskuu",
      	 "lokakuu",
      	 "marraskuu",
      	 "joulukuu"
      }
   },
   {
      TOFRA,                              /* French */
      {
         /* preface     */    "Préface",
         /* chapter     */    "Chapitre",
         /* title       */    "Titre",
         /* appendix    */    "Annexe",
         /* contents    */    "Sommaire",
         /* listfigure  */    "Table des figures",
         /* listtable   */    "Liste des tableaux",
         /* figure      */    "Figure",
         /* table       */    "Tableau",
         /* index       */    "Index",
         /* page        */    "page",
         /* see         */    "voir",
         /* also        */    "voir aussi",
         /* by          */    "de",
         /* fur         */    "pour",
         /* up          */    "&Haut",
         /* exit        */    "&Fin",
         /* unknown     */    "Inconnu",
         /* update      */    "Dernière mise à jour le",
         /* lcid        */    "0x40c",
         /* html_home   */    "Home",
         /* html_up     */    "Haut",
         /* html_prev   */    "Précédent",
         /* html_next   */    "Suivant",
         /* html_lang   */    "fr",
         /* html_start  */    "commencer du document",
         /* translator  */    "Traduction :",
         /* distributor */    "Distribution :",
         /* tex_stylename */  "french",
         /* lyx_langname */   "french",
         /* degree      */    "degré",
         /* copyright   */    "Droit d’auteur",
         /* today       */    "%3$d %2$s %1$d",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
      	 "janvier",
      	 "février",
      	 "mars",
      	 "avril",
      	 "mai",
      	 "juin",
      	 "juillet",
      	 "août",
      	 "septembre",
      	 "octobre",
      	 "novembre",
      	 "décembre"
      }
   },
   {
      TOGER,                              /* German */
      {
         /* preface     */    "Vorwort",
         /* chapter     */    "Kapitel",
         /* title       */    "Titel",
         /* appendix    */    "Anhang",
         /* contents    */    "Inhaltsverzeichnis",
         /* listfigure  */    "Abbildungsverzeichnis",
         /* listtable   */    "Tabellenverzeichnis",
         /* figure      */    "Abbildung",
         /* table       */    "Tabelle",
         /* index       */    "Index",
         /* page        */    "Seite",
         /* see         */    "siehe",
         /* also        */    "siehe auch",
         /* by          */    "von",
         /* fur         */    "für",
         /* up          */    "&Hoch",
         /* exit        */    "Bee&nden",
         /* unknown     */    "Unbekannt",
         /* update      */    "Letzte Aktualisierung am",
         /* lcid        */    "0x407",
         /* html_home   */    "Home",
         /* html_up     */    "Hoch",
         /* html_prev   */    "Vorige",
         /* html_next   */    "Nächste",
         /* html_lang   */    "de",
         /* html_start  */    "Beginn des Dokumentes",
         /* translator  */    "Übersetzung:",
         /* distributor */    "Vertrieb:",
         /* tex_stylename */  "german,a4",
         /* lyx_langname */   "german",
         /* degree      */    "Grad",
         /* copyright   */    "Copyright",
         /* today       */    "%3$d. %2$s %1$d",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
      	 "Januar",
      	 "Februar",
      	 "März",
      	 "April",
      	 "Mai",
      	 "Juni",
      	 "Juli",
      	 "August",
      	 "September",
      	 "Oktober",
      	 "November",
      	 "Dezember"
      }
   },
   {
      TOITA,                              /* Italian */
      {
         /* preface     */    "Prefazione",
         /* chapter     */    "Capitolo",
         /* title       */    "Titolo",
         /* appendix    */    "Appendice",
         /* contents    */    "Contenuto",
         /* listfigure  */    "Lista di Figure",
         /* listtable   */    "Lista di Tabelle",
         /* figure      */    "Figura",
         /* table       */    "Tabella",
         /* index       */    "Indice",
         /* page        */    "pagina",
         /* see         */    "vedere",
         /* also        */    "vedere anche",
         /* by          */    "da",
         /* fur         */    "pro",
         /* up          */    "S&u",
         /* exit        */    "Uscita",
         /* unknown     */    "Ignoto",
         /* update      */    "Ultimo aggiornamento",
         /* lcid        */    "0x410",
         /* html_home   */    "Home",
         /* html_up     */    "Up",
         /* html_prev   */    "Precedente",
         /* html_next   */    "Seguente",
         /* html_lang   */    "it",
         /* html_start  */    "Inizio del documento",
         /* translator  */    "Traduzione:",
         /* distributor */    "Distribuzione:",
         /* tex_stylename */  "italian",
         /* lyx_langname */   "italian",
         /* degree      */    "grado",
         /* copyright   */    "Diritto d'autore",
         /* today       */    "%3$d. %2$s %1$d",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
      	 "Gennaio",
      	 "Febbraio",
      	 "Marzo",
      	 "Aprile",
      	 "Maggio",
      	 "Giugno",
      	 "Luglio",
      	 "Agosto",
      	 "Settembre",
      	 "Ottobre",
      	 "Novembre",
      	 "Dicembre"
      }
   },
   {
      TOJAP,                              /* Japanese */
      {
         /* preface     */    "序文",
         /* chapter     */    "章",
         /* title       */    "タイトル",
         /* appendix    */    "付録",
         /* contents    */    "目次",
         /* listfigure  */    "図一覧",
         /* listtable   */    "表の一覧",
         /* figure      */    "図",
         /* table       */    "表",
         /* index       */    "索引",
         /* page        */    "ページ",
         /* see         */    "参照してください",
         /* also        */    "参照してください",
         /* by          */    "作者",
         /* fur         */    "所属",
         /* up          */    "上へ",
         /* exit        */    "終了",
         /* unknown     */    "不明",
         /* update      */    "最終更新日",
         /* lcid        */    "0x411",
         /* html_home   */    "ホーム",
         /* html_up     */    "を",
         /* html_prev   */    "戻る",
         /* html_next   */    "進む",
         /* html_lang   */    "ja",
         /* html_start  */    "ドキュメントの開始",
         /* translator  */    "翻訳：",
         /* distributor */    "販売元：",
         /* tex_stylename */  "japanese",
         /* lyx_langname */   "japanese",
         /* degree      */    "度",
         /* copyright   */    "著作権",
         /* today       */    "%1$d年 %2$s %3$02d日",
         /* short_today */    "%1$d年%2$02d月%3$02d日"
      },
      {
      	  "1 月",
      	  "2 月",
      	  "3 月",
      	  "4 月",
      	  "5 月",
      	  "6 月",
      	  "7 月",
      	  "8 月",
      	  "9 月",
      	  "10 月",
      	  "11 月",
      	  "12 月"
      }
   },
   {
      TOLVA,                              /* Latvian */
      {
         /* preface     */    "Priekšvārds",
         /* chapter     */    "Nodaļa",
         /* title       */    "Nosaukums",
         /* appendix    */    "Pielikums",
         /* contents    */    "Saturs",
         /* listfigure  */    "Attēlu saraksts",
         /* listtable   */    "Tabulu saraksts",
         /* figure      */    "Attēls",
         /* table       */    "Tabula",
         /* index       */    "Alfabētiskais rādītājs",
         /* page        */    "lappuse",
         /* see         */    "skatīt",
         /* also        */    "skatīt arī",
         /* by          */    "pēc",
         /* fur         */    "ar",
         /* up          */    "Augšup",
         /* exit        */    "Iziet",
         /* unknown     */    "Nezināms",
         /* update      */    "Pēdējoreiz atjaunots",
         /* lcid        */    "0x426",
         /* html_home   */    "Sākums",
         /* html_up     */    "Augšup",
         /* html_prev   */    "Iepriekšējais",
         /* html_next   */    "Nākamais",
         /* html_lang   */    "lv",
         /* html_start  */    "Dokumenta sākums",
         /* translator  */    "Translation:",
         /* distributor */    "Izplatītājs:",
         /* tex_stylename */  "latvian",
         /* lyx_langname */   "latvian",
         /* degree      */    "degree",
         /* copyright   */    "Autortiesības",
         /* today       */    "%3$d. %2$s %1$d",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
      	 "Janvāris",
      	 "Februāris",
      	 "Marts",
      	 "Aprīlis",
      	 "Maijs",
      	 "Jūnijs",
      	 "Jūlijs",
      	 "Augusts",
      	 "Septembris",
      	 "Oktobris",
      	 "Novembris",
      	 "Decembris"
      }
   },
   {
      TONOR,                              /* Norwegian (Nynorsk)*/
      {
         /* preface     */    "Preface",
         /* chapter     */    "Chapter",
         /* title       */    "Title",
         /* appendix    */    "Appendix",
         /* contents    */    "Contents",
         /* listfigure  */    "List of Figures",
         /* listtable   */    "List of Tables",
         /* figure      */    "Figure",
         /* table       */    "Table",
         /* index       */    "Index",
         /* page        */    "page",
         /* see         */    "see",
         /* also        */    "see also",
         /* by          */    "by",
         /* fur         */    "for",
         /* up          */    "&Up",
         /* exit        */    "E&xit",
         /* unknown     */    "Unknown",
         /* update      */    "Sist oppdatert på",
         /* lcid        */    "0x414",
         /* html_home   */    "Home",
         /* html_up     */    "Up",
         /* html_prev   */    "Tidligere",
         /* html_next   */    "Neste",
         /* html_lang   */    "nn",
         /* html_start  */    "Begin of the document",
         /* translator  */    "Omsetjing:",
         /* distributor */    "Distributor:",
         /* tex_stylename */  "norsk",
         /* lyx_langname */   "norsk",
         /* degree      */    "grad",
         /* copyright   */    "Opphavsrett",
         /* today       */    "%3$d. %2$s %1$d",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
      	 "januar",
      	 "februar",
      	 "mars",
      	 "april",
      	 "mai",
      	 "juni",
      	 "juli",
      	 "august",
      	 "september",
      	 "oktober",
      	 "november",
      	 "desember"
      }
   },
   {
      TOPOL,                              /* Polish */
      {
         /* preface     */    "Preface",
         /* chapter     */    "Chapter",
         /* title       */    "Title",
         /* appendix    */    "Aneks",
         /* contents    */    "Zawartość",
         /* listfigure  */    "List of Figures",
         /* listtable   */    "List of Tables",
         /* figure      */    "Figure",
         /* table       */    "Table",
         /* index       */    "Indeks",
         /* page        */    "page",
         /* see         */    "see",
         /* also        */    "see also",
         /* by          */    "by",
         /* fur         */    "for",
         /* up          */    "Up",
         /* exit        */    "Exit",
         /* unknown     */    "Unknown",
         /* update      */    "Ostatnie zmiany",
         /* lcid        */    "0x415",
         /* html_home   */    "Główna",
         /* html_up     */    "Up",
         /* html_prev   */    "Prev",
         /* html_next   */    "Next",
         /* html_lang   */    "pl",
         /* html_start  */    "Begin of the document",
         /* translator  */    "Tłumaczenie:",
         /* distributor */    "Distributor:",
         /* tex_stylename */  "polish",
         /* lyx_langname */   "polish",
         /* degree      */    "stopień",
         /* copyright   */    "Prawo autorskie",
         /* today       */    "%3$d. %2$s %1$d",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
      	 "styczeń",
      	 "luty",
      	 "marzec",
      	 "kwiecień",
      	 "maj",
      	 "czerwiec",
      	 "lipiec",
      	 "sierpień",
      	 "wrzesień",
      	 "październik",
      	 "listopad",
      	 "grudzień"
      }
   },
   {
      TOPOR,                              /* Portuguese */
      {
         /* preface     */    "Prefácio",
         /* chapter     */    "Capítulo",
         /* title       */    "Título",
         /* appendix    */    "Apêndice",
         /* contents    */    "Conteúdo",
         /* listfigure  */    "Lista de figuras",
         /* listtable   */    "Lista de tabelas",
         /* figure      */    "Figura",
         /* table       */    "Tabela",
         /* index       */    "Índice",
         /* page        */    "página",
         /* see         */    "ver",
         /* also        */    "ver também",
         /* by          */    "por",
         /* fur         */    "para",
         /* up          */    "&Para cima",
         /* exit        */    "&Sair",
         /* unknown     */    "Desconhecido",
         /* update      */    "Actualizada em",
         /* lcid        */    "0x816",
         /* html_home   */    "Casa",
         /* html_up     */    "Para cima",
         /* html_prev   */    "Anterior",
         /* html_next   */    "Próximo",
         /* html_lang   */    "pt",
         /* html_start  */    "Início do documento",
         /* translator  */    "Tradução:",
         /* distributor */    "Distribuidor:",
         /* tex_stylename */  "portuges",
         /* lyx_langname */   "portuges",
         /* degree      */    "grau",
         /* copyright   */    "Direito autoral",
         /* today       */    "%3$d. %2$s %1$d",
         /* short_today */    "%3$02d-%2$02d-%1$d"
      },
      {
      	 "Janeiro",
      	 "Fevereiro",
      	 "Março",
      	 "Abril",
      	 "Maio",
      	 "Junho",
      	 "Julho",
      	 "Agosto",
      	 "Setembro",
      	 "Outubro",
      	 "Novembro",
      	 "Dezembro"
      }
   },
   {
      TORUS,                              /* Russian */
      {
         /* preface     */    "Предисловие",
         /* chapter     */    "Глава",
         /* title       */    "Название",
         /* appendix    */    "Приложение",
         /* contents    */    "Содержание",
         /* listfigure  */    "Список рисунков",
         /* listtable   */    "Список таблиц",
         /* figure      */    "Рисунок",
         /* table       */    "Таблица",
         /* index       */    "Индекс",
         /* page        */    "страница",
         /* see         */    "см.",
         /* also        */    "cмотрите также",
         /* by          */    "по",
         /* fur         */    "для",
         /* up          */    "Вверх",
         /* exit        */    "Выход",
         /* unknown     */    "Неизвестно",
         /* update      */    "Последнее обновление:",
         /* lcid        */    "0x419",
         /* html_home   */    "Главная",
         /* html_up     */    "Вверх",
         /* html_prev   */    "Предыдущий",
         /* html_next   */    "Следующая",
         /* html_lang   */    "ru",
         /* html_start  */    "Начало документа",
         /* translator  */    "Перевод:",
         /* distributor */    "Дистрибьютор:",
         /* tex_stylename */  "russian",
         /* lyx_langname */   "russian",
         /* degree      */    "степень",
         /* copyright   */    "Авторские права",
         /* today       */    "%3$d. %2$s %1$d r.",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
         "Январь",
         "Февраль",
         "Март",
         "Апрель",
         "Май",
         "Июнь",
         "Июль",
         "Август",
         "Сентябрь",
         "Октябрь",
         "Ноябрь",
         "Декабрь"
      }
   },
   {
      TOSPA,                              /* Spanish */
      {
         /* preface     */    "Prefacio",
         /* chapter     */    "Capìtulo",
         /* title       */    "Tìtulo",
         /* appendix    */    "Apéndice",
         /* contents    */    "Contenido",
         /* listfigure  */    "Lista de figuras",
         /* listtable   */    "Lista de tablas",
         /* figure      */    "Figura",
         /* table       */    "Tabla",
         /* index       */    "Índice",
         /* page        */    "Página",
         /* see         */    "Ver",
         /* also        */    "Además",
         /* by          */    "Por",
         /* fur         */    "Para",
         /* up          */    "Arriba",
         /* exit        */    "Salida",
         /* unknown     */    "desconocido",
         /* update      */    "Última actualización el",
         /* lcid        */    "0x40a",
         /* html_home   */    "Inicio",
         /* html_up     */    "Arriba",
         /* html_prev   */    "Anterior",
         /* html_next   */    "Siguiente",
         /* html_lang   */    "es",
         /* html_start  */    "Comienzo del documento",
         /* translator  */    "Traducción:",
         /* distributor */    "Distribuidor:",
         /* tex_stylename */  "spanish",
         /* lyx_langname */   "spanish",
         /* degree      */    "grado",
         /* copyright   */    "Derechos de autor",
         /* today       */    "%3$d. %2$s %1$d",
         /* short_today */    "%3$02d.%2$02d.%1$d"
      },
      {
      	 "Enero",
      	 "Febrero",
      	 "Marzo",
      	 "Abril",
      	 "Mayo",
      	 "Junio",
      	 "Julio",
      	 "Agosto",
      	 "Septiembre",
      	 "Octubre",
      	 "Noviembre",
      	 "Diciembre"
      }
   },
   {
      TOSWE,                              /* Swedish */
      {
         /* preface     */    "Förord",
         /* chapter     */    "Kapitel",
         /* title       */    "Titel",
         /* appendix    */    "Appendix",
         /* contents    */    "Innehållsförteckning",
         /* listfigure  */    "Figurer",
         /* listtable   */    "Tabeller",
         /* figure      */    "Figur",
         /* table       */    "Tabell",
         /* index       */    "Index",
         /* page        */    "Sida",
         /* see         */    "se",
         /* also        */    "se även",
         /* by          */    "av",
         /* fur         */    "för",
         /* up          */    "&Upp",
         /* exit        */    "Avsluta",
         /* unknown     */    "Okänd",
         /* update      */    "Senast uppdaterad",
         /* lcid        */    "0x41d",
         /* html_home   */    "Home",
         /* html_up     */    "Up",
         /* html_prev   */    "Prev",
         /* html_next   */    "Next",
         /* html_lang   */    "sv",
         /* html_start  */    "Dokumentets början",
         /* translator  */    "Översättning:",
         /* distributor */    "Distributör:",
         /* tex_stylename */  "swedish",
         /* lyx_langname */   "swedish",
         /* degree      */    "grad",
         /* copyright   */    "Upphovsrätt",
         /* today       */    "%3$d %2$s %1$d",
         /* short_today */    "%1$0d-%2$02d-%3$02d"
      },
      {
      	 "januari",
      	 "februari",
      	 "mars",
      	 "april",
      	 "maj",
      	 "juni",
      	 "juli",
      	 "augusti",
      	 "september",
      	 "oktober",
      	 "november",
      	 "december"
      }
   },
   
   {  -1, { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" },
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
   }
};
