/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : udo.h
*  Symbol prefix: udo
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
*-------------------------------------------------------------------------------
*
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Ulf Dunkel (fd), Gerhard Stoll (ggs)
*  Write access : fd, ggs
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - Fuer die ganzen Flags eine Struktur anlegen, was die Sache
*                   wesentlich uebersichtlicher macht! <???>
*
*-------------------------------------------------------------------------------
*  History:
*
*  1995:
*    DH  Jan xx: introduced
*  2001:
*    DH  Oct 02: last DH version
*  2010:
*    fd  Jan 20: new: html_quotes
*    fd  Jan 23: - file reformatted
*                - converted all German umlauts in comments into plain ASCII
*                - SHOW_VARAIABLE -> SHOW_VAR
*    fd  Feb 16: - more stuff globalized
*                - MAXCHARSET increased for CODE_CP1250
*    fd  Feb 19: - MAXCHARSET removed
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Mar 01: new: use_short_itemizes
*                     use_short_enumerates
*                     use_short_descriptions
*                     use_short_lists
*    ggs Apr 21: use_short_tocs -> use_compressed_tocs
*    fd  May 18: html_ignore_8bit_use_charset + html_ignore_8bit_charset no longer required
*  2014
*    ggs Apr 20: Add Node6
*
******************************************|************************************/

#ifndef __UDO_H__
#define __UDO_H__





/*******************************************************************************
*
*     EXTERNAL REFERENCES
*
******************************************|************************************/

extern char   compile_date[];
extern char   compile_time[];

extern UDOCOLOR const udocolor[];


/*******************************************************************************
*
*     GLOBAL UNINITIALIZED VARIABLES
*
******************************************|************************************/

GLOBAL MYFILE      udofile;

GLOBAL int         iUdopass;              /* PASS1 oder PASS2 */

GLOBAL _BOOL     bNopDetected;          /* Fuer Debugging-Zwecke */

GLOBAL int         desttype;              /* Ausgabeformat  (TOASC, ...) */
GLOBAL int         iCharset;              /* Eingabe-Zeichensatz */
GLOBAL int         iEncodingSource;       /* encoding of UDO source documents */
GLOBAL int         iEncodingTarget;       /* encoding of target document */

#if 0 /* for debugging */
#define iEncodingTarget get_encoding_target(__FILE__, __LINE__)
#endif
#define set_encoding_target(code) set_encoding_target(code, __FILE__, __LINE__)

GLOBAL int         iDateDay, 
                   iDateMonth, 
                   iDateYear;
GLOBAL int         iDateHour, 
                   iDateMin, 
                   iDateSec;

GLOBAL _BOOL     bNoLogfile;            /* Logfile anlegen? */
GLOBAL _BOOL     bNoHypfile;            /* Hyphenationfile anlegen? */
GLOBAL _BOOL     bNoIdxfile;            /* Indexfile anlegen? */
GLOBAL _BOOL     bBeQuiet;              /* Statusinfos nicht ausgeben? */
GLOBAL _BOOL     bCheckMisc;            /* diverse Ueberpruefungen? */
GLOBAL _BOOL     bVerbose;              /* langen Status ausgeben? */
GLOBAL _BOOL     bTestmode;             /* Testmodus? */
GLOBAL _BOOL     bUseTreefile;          /* Include-Baum listen? */
GLOBAL _BOOL     bUseUPRfile;           /* Project-File sichern? */
GLOBAL _BOOL     bUseIdMapFileC;        /* Jump-ID-File fuer HPJ? */
GLOBAL _BOOL     bUseIdMapFilePas;      /* Jump-ID-File fuer HPJ? */
GLOBAL _BOOL     bUseIdMapFileVB;       /* Jump-ID-File fuer HPJ? */
GLOBAL _BOOL     bUseIdMapFileGFA;      /* Jump-ID-File fuer HPJ? */
GLOBAL _BOOL     bNoWarnings;           /* Keine Warnungen ausgeben? */
GLOBAL _BOOL     bNoWarningsLines;      /* Keine Warnungen ausgeben, bei zu langen oder kurzen Zeilen */
GLOBAL _BOOL     bForceLong;            /* Immer lange Dateinamen? */
GLOBAL _BOOL     bForceShort;           /* Immer kurze Dateinamen? */
#if USE_KWSET
GLOBAL _BOOL     bNoFastAutoref;        /* use newer, faster version of autoreferencer? */
#endif

GLOBAL size_t      zDocParwidth;          /* max. Zeilenbreite */

GLOBAL int         iTexVersion;           /* Lindner-, Strunk-, emTex? */
GLOBAL int         iTexDPI;               /* Aufloesung fuer Images */
GLOBAL _BOOL     bTex2e;                /* LaTeX2e wird benutzt? */
GLOBAL char        cTexVerb;              /* Zeichen fuer \verb */

GLOBAL char        sSrcRemOn[8];          /* Kommentar ein */
GLOBAL char        sSrcRemOff[8];         /* Kommentar aus */

GLOBAL int         bDocTabwidth;          /* Tab-Width fuer verbatim-Umgebung */
GLOBAL int         iDocVerbatimSize;      /* Fontgroesse fuer verbatim-Umgebung */
GLOBAL int         iDocLinedrawSize;      /* Fontgroesse fuer linedraw-Umgebung */

GLOBAL char        sCurrFileName[MYFILE_FULL_LEN + 1];    /* Gerade aktive Datei */
GLOBAL FILE_LINENO uiCurrFileLine;        /* und die aktuelle Zeilen-Nr. */

GLOBAL _BOOL     b1stQuote;             /* flag for "real" double quotation marks */
GLOBAL _BOOL     b1stApost;             /* flag for 'real' single quotation marks */

GLOBAL char        tmp_driv[MYFILE_DRIV_LEN + 1];
GLOBAL char        tmp_path[MYFILE_PATH_LEN + 1];
GLOBAL char        tmp_name[MYFILE_NAME_LEN + 1];
GLOBAL char        tmp_suff[MYFILE_SUFF_LEN + 1];

GLOBAL MYFILE      outfile;
GLOBAL MYFILE      infile;
GLOBAL MYFILE      old_outfile;
GLOBAL _BOOL     bOutOpened;            /* File geoeffnet? */

GLOBAL FILE       *fLogfile;
GLOBAL FILE_ID sLogfull;
GLOBAL _BOOL     bLogopened;            /* Logfile geoeffnet? */

GLOBAL FILE       *fHypfile;
GLOBAL FILE_ID     sHypfull;
GLOBAL _BOOL     bHypopened;            /* Hyphenfile geoeffnet? */
GLOBAL _BOOL     bHypfailed;            /* Hypfile oeffnen gescheitert */

GLOBAL FILE       *fTreefile;
GLOBAL FILE_ID     sTreefull;
GLOBAL _BOOL     bTreeopened;           /* Treefile geoeffnet? */

GLOBAL FILE       *fIdxfile;
GLOBAL FILE_ID     sIdxfull;
GLOBAL _BOOL     bIdxopened;            /* Indexfile geoeffnet? */
GLOBAL _BOOL     bIdxfailed;            /* Indexfile oeffnen gescheitert*/

GLOBAL FILE       *fUPRfile;
GLOBAL FILE_ID     sUPRfull;
GLOBAL _BOOL     bUPRopened;            /* Logfile geoeffnet? */

GLOBAL FILE_ID     sCmdfull;              /* Name der CMD-Datei fuer PCH */
GLOBAL FILE_ID     sHpjfull;              /* Name der HPJ-Datei fuer Win */
GLOBAL FILE_ID     sCntfull;              /* Name der CNT-Datei fuer Win4 */
GLOBAL const char  *sMapNoSuff;           /* Name der Map-Datei fuer Win ohne Suffix */
GLOBAL FILE_ID     sHhpfull;              /* Name der HHP-Datei fuer HTML Help */
GLOBAL FILE_ID     sHhcfull;              /* Name der HHC-Datei fuer HTML Help */
GLOBAL FILE_ID     sHhkfull;              /* Name der HHK-Datei fuer HTML Help */

GLOBAL PASSFLAGS   pflag[3];              /* Flags fuer die Durchlaeufe */

GLOBAL _BOOL     bFatalErrorDetected;   /* Fataler Fehler aufgetreten? */
GLOBAL _BOOL     bErrorDetected;        /* Fehler aufgetreten? */
GLOBAL _BOOL     bBreakHappened;        /* wuenscht User Abbruch */
GLOBAL _BOOL     bBreakInside;          /* !break gelesen */

GLOBAL _BOOL     uses_udolink;          /* Wird !udolink benutzt? */
GLOBAL _BOOL     uses_toplink;          /* Wird !toplink benutzt? */

GLOBAL char        token[MAX_TOKENS][MAX_TOKEN_LEN + 1];
GLOBAL int         token_counter;
GLOBAL _BOOL     tokens_contain_item;

GLOBAL _BOOL     use_auto_toptocs;      /* autom. Ueber-Toc's anlegen? */
GLOBAL _BOOL     no_auto_toptocs_icons; /* ... aber ohne Icons */
GLOBAL _BOOL     use_compressed_tocs;   /* Kurze Inhaltsverzeichnisse default? */

GLOBAL _BOOL     use_compressed_envs;   /* compress all supporting environments */
                                          /* compress all itemize environments only */
GLOBAL _BOOL     use_compressed_itemizes;
                                          /* compress all enumerate environments only */
GLOBAL _BOOL     use_compressed_enumerates;
                                          /* compress all description environments only */
GLOBAL _BOOL     use_compressed_descriptions;
GLOBAL _BOOL     use_compressed_lists;  /* compress all ?list environments only */

GLOBAL _BOOL     use_formfeed;          /* Formfeed verwenden? */
GLOBAL _BOOL     use_chapter_images;    /* Kapitelgrafiken verwenden? */
GLOBAL _BOOL     use_about_udo;
GLOBAL _BOOL     use_ansi_tables;       /* Tabellen mit ANSI-Grafiken umrahmen? */
GLOBAL _BOOL     use_style_book;        /* chapter oder sections? */
GLOBAL _BOOL     use_justification;     /* Blocksatz? */
GLOBAL _BOOL     use_nodes_inside_index;/* Kapitel in den Index uebernehmen? */
GLOBAL _BOOL     use_alias_inside_index;/* Aliase in den Index uebernehmen? */
GLOBAL _BOOL     use_label_inside_index;/* Labels in den Index uebernehmen? */
GLOBAL _BOOL     use_udo_index;         /* Soll UDO einen Index ausgeben? */
GLOBAL _BOOL     use_mirrored_indices;  /* !index I1 !! I2 auch spiegeln? */
GLOBAL _BOOL     use_comments;          /* Kommentare ausgeben (!rem [...]) */
GLOBAL _BOOL     use_auto_helpids;      /* HelpIDs automatisch generieren? */

GLOBAL _BOOL     no_umlaute;            /* Umlaute durch ae etc. ersetzen? */
GLOBAL _BOOL     no_headlines;          /* Keine Titelzeilen? */
GLOBAL _BOOL     no_bottomlines;        /* Keine Fusszeilen? */
GLOBAL _BOOL     no_popup_headlines;    /* In Popups nie eine Titelzeile? */
GLOBAL _BOOL     no_footers;            /* Keine speziellen Fusszeilen? */
GLOBAL _BOOL     no_effects;            /* Keine Effekte? */
GLOBAL _BOOL     no_numbers;            /* Kapitel mit Nummern ausgeben? */
GLOBAL _BOOL     no_quotes;             /* "unechte" Anfuehrungszeichnen? */
GLOBAL _BOOL     no_preamble;           /* preamble nicht ausgeben? */
GLOBAL _BOOL     no_index;              /* !index ignorieren und keinen Index? */
GLOBAL _BOOL     no_buttons;            /* Keine Knoepfe erzeugen (WinHelp) */
GLOBAL _BOOL     no_img_size;           /* Keine Ausmasse ermitteln? */
GLOBAL _BOOL     no_images;             /* Bilder verwenden? */
GLOBAL _BOOL     no_urls;               /* Keine URLs verwenden? */
GLOBAL _BOOL     no_xlinks;             /* Keine externen Links verwenden? */
GLOBAL _BOOL     no_links;              /* Keine Links verwenden? */
GLOBAL _BOOL     no_sourcecode;         /* Sourcecode-Umgebung nicht ausgeben? */
GLOBAL _BOOL     no_table_lines;        /* Tabellen ohne Linien ausgeben? */

GLOBAL _BOOL     bDocAutorefOff;        /* Nicht autom. referenzieren? */
GLOBAL _BOOL     bStgLimage;            /* use @limage for !image */
GLOBAL _BOOL     bDocAutorefItemsOff;   /* Items nicht autom. referenzieren? */
GLOBAL _BOOL     bDocUniversalCharsetOn;/* Universellen Zeichensatz benutzen? */
GLOBAL _BOOL     bDocRtfKeepTablesOn;   /* Tabellen zusammenhalten? */
GLOBAL _BOOL     bDocWinOldKeywords;    /* Alte Keywords benutzen? */
GLOBAL _BOOL     bDocSortHyphenFile;    /* *.uh? sortieren */

GLOBAL _BOOL     html_no_xlist;         /* xlist- durch description-Umgebung ersetzen? */
GLOBAL _BOOL     html_ignore_8bit;      /* ae nicht in &auml; wandeln? */
GLOBAL _BOOL     html_modern_layout;    /* Modernes 2-Spalten-Layout? */
GLOBAL _BOOL     html_frames_layout;    /* Frames fuer HTML benutzen? */
GLOBAL _BOOL     html_frames_noresize;
GLOBAL _BOOL     html_frames_noborder;
GLOBAL _BOOL     html_frames_noscroll;
GLOBAL _BOOL     html_use_folders;      /* Ordnerstruktur erzeugen? */
                                          /* Transparente Buttons benutzen? */
GLOBAL _BOOL     html_transparent_buttons;

GLOBAL SHOW_VAR    show_variable;

GLOBAL _BOOL     html_navigation_line;  /* TRUE: show navigation levels in one line without folder symbols */
                                          /* string which separates navigation levels (default: '&gt; ') */
GLOBAL char        html_navigation_separator[20];
GLOBAL _BOOL     html_navigation_image; /* TRUE: show (folder) symbol */
                                          /* fspec to userdef (folder equivalent) symbol */
GLOBAL char        html_navigation_image_fspec[128];

                                          /* Links zum Wechseln? */
GLOBAL char        sDocHtmlSwitchLanguage[256];
GLOBAL int         iDocHtmlSwitchLanguage;/* ... und der Wert der Sprache */
GLOBAL FILE_ID     sCounterCommand;       /* CounterCommand for all files */

GLOBAL int         html_nodesize;         /* Default: 1 -> <H1> */
GLOBAL char        sDocHtmlBackpage[512]; /* Ruecksprung im Index */
                                          /* <font face="..."> */
GLOBAL char        sDocHtmlPropfontName[64];
                                          /* <font size="..."> */
GLOBAL char        sDocHtmlPropfontSize[16];
GLOBAL int         iDocHtmlPropfontSize;
                                          /* <font face="..."> */
GLOBAL char        sDocHtmlMonofontName[64];
                                          /* <font size="..."> */
GLOBAL char        sDocHtmlMonofontSize[16];
GLOBAL int         iDocHtmlMonofontSize;
GLOBAL char        sDocHtmlIndexudo[512];
GLOBAL char        html_modern_width[16]; /* Breite der linken Spalte */
GLOBAL int         html_modern_alignment; /* Ausrichtung linke Spalte */
                                          /* background color of left column */
GLOBAL struct rgb  html_modern_backcolor;
                                          /* Image der linken Spalte */
GLOBAL FILE_ID     html_modern_backimage;
GLOBAL char        html_frames_width[16]; /* Breite des linken Frames */
GLOBAL char        html_frames_height[16];/* Breite des oberen Frames */
GLOBAL int         html_frames_position;  /* Position des Frames */
GLOBAL int         html_frames_alignment; /* Ausrichtung linker Frame */
                                          /* Backfarbe des linken Frames */
GLOBAL struct rgb  html_frames_backcolor;
                                          /* Textfarbe des linken Frames */
GLOBAL struct rgb  html_frames_textcolor;
                                          /* Linkfarbe der linken Spalte */
GLOBAL struct rgb  html_frames_linkcolor;
                                          /* Linkfarbe der linken Spalte */
GLOBAL struct rgb  html_frames_alinkcolor;
                                          /* Linkfarbe der linken Spalte */
GLOBAL struct rgb  html_frames_vlinkcolor;
                                          /* Image des linken Frames */
GLOBAL FILE_ID     html_frames_backimage;
GLOBAL int         html_button_alignment; /* Ausrichtung der Buttons */
GLOBAL int         html_quotes;           /* define HTML formatting of quotes */
GLOBAL char        html_name_prefix[512]; /* Prefix fuer HTML-Dateinamen */

GLOBAL _BOOL     html_use_hyphenation;  /* Lange Woerter sollen durch (!-) getrennt werden */
GLOBAL int         html_doctype;          /* Welche DTD soll benutzt werden? */
GLOBAL const char *xhtml_closer;
GLOBAL const char *xhtml_id_attr;
GLOBAL const char *xhtml_br;
GLOBAL const char *xhtml_hr;

GLOBAL _BOOL     html_header_date;      /* Ausgabe des Datums im Element <meta> */
                                          /* date zone */
GLOBAL char        html_header_date_zone[10];

GLOBAL int         html_header_links;     /* Ausgabe der Daten im Element <link> */
                                          /* Welche Links sollen ausgegeben werden? */
#define HTML_HEADER_LINKS_CHAPTER    0x01
#define HTML_HEADER_LINKS_NAVIGATION 0x02

GLOBAL int         image_alignment;       /* Ausrichtung der Bilder */
GLOBAL int         table_alignment;       /* Ausrichtung der Tabellen */

GLOBAL char        sDocWinPrefixID[64];   /* Prefix fuer autom. Help-IDs */
GLOBAL char        sDocWinButtonName[MAX_WIN_BUTTONS][64];
GLOBAL char        sDocWinButtonText[MAX_WIN_BUTTONS][64];
GLOBAL int         iNumWinButtons;

GLOBAL char        sDrcBcolor[3];         /* DRC-Farbe fuer bold */
GLOBAL char        sDrcIcolor[3];         /* DRC-Farbe fuer italic */
GLOBAL char        sDrcUcolor[3];         /* DRC-Farbe fuer underlined */
GLOBAL int         iDrcFlags;             /* DRC-Flags fuer EDIT, SAVE, PRINT, ... */

GLOBAL int         iManPageLines;         /* ausgegebene Zeilen pro Seite */
GLOBAL int         iManPagePages;         /* bereits ausgegebene Seiten */
GLOBAL int         iManPageLength;        /* maximale Zeilen pro Seite */
GLOBAL char        sDocManType[32];       /* Typ (1), (C), ... */
GLOBAL char        sDocNroffType[32];     /* dito fuer nroff */

GLOBAL char        sDocImgSuffix[32];     /* gif, jpg, jpeg, ... */
GLOBAL FILE_ID     sDocBackImage;
GLOBAL SCRIPTLIST  sDocScript;
GLOBAL STYLELIST   sDocStyle;
GLOBAL FILE_ID     sDocFavIcon;
GLOBAL struct rgb_and_color sDocBackColor;
GLOBAL struct rgb_and_color sDocTextColor;
GLOBAL struct rgb_and_color sDocLinkColor;
GLOBAL struct rgb_and_color sDocAlinkColor;
GLOBAL struct rgb_and_color sDocVlinkColor;
GLOBAL struct rgb_and_color sDocVerbatimBackColor;

GLOBAL FILE_ID     sDocRawHeaderFilename;
GLOBAL FILE_ID     sDocRawFooterFilename;

GLOBAL _BOOL     bDocInlineBitmaps;     /* {bmcwd statt {bmc verwenden? */
GLOBAL _BOOL     bDocHighCompression;
GLOBAL _BOOL     bDocMediumCompression;

GLOBAL int         iDocCharwidth;         /* Zeichenbreiten-Konstanten */

GLOBAL char        sDocColour[512];       /* additional colors for RTF */
                                          /* Proportional- und Monospacedfont */
GLOBAL char        sDocPropfont[MAXZEILE + 1];
                                          /* fuer den RTF-Header */
GLOBAL char        sDocMonofont[MAXZEILE + 1];
GLOBAL char        sDocPropfontSize[16];
GLOBAL int         iDocPropfontSize;
GLOBAL char        sDocMonofontSize[16];
GLOBAL int         iDocMonofontSize;
GLOBAL _BOOL     bDocNoTables;          /* Keine echten RTF-Tabellen anlegen? */

GLOBAL _BOOL     bCalledIndex;          /* !index ignorieren und keinen Index? */

GLOBAL int footnote_cnt;  		        /* footnote counter for current node */
GLOBAL int global_footnote_cnt;  		/* footnote counter for document */
struct footnote {
	int number;
	int global_number;
	struct footnote *next;
	size_t len;
	char *str;
};
GLOBAL struct footnote *footnotes;

extern FILE_LINENO outlines;




/*******************************************************************************
*
*     GLOBAL PROTOTYPES
*
******************************************|************************************/

   /* --- output routines --- */

   /* ? */
GLOBAL void outln(const char *s);
   /* ? */
GLOBAL void out(const char *s);
   /* ? */
GLOBAL void voutlnf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
   /* ? */
GLOBAL void voutf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
   /* output horizontal lines */
GLOBAL void c_hline(void);
   /* output newpage */
GLOBAL void c_newpage(void);



   /* --- string manipulation --- */

   /* ? */
GLOBAL void stringcenter(char *string, size_t length);
   /* ? */
GLOBAL void strcenter(char *string, size_t length);
   /* ? */
GLOBAL void outlncenter(const char *s);
   /* ? */
GLOBAL void outlncenterfill(const char *s);
   /* ? */
GLOBAL void strright(char *string, size_t length);
   /* ? */
GLOBAL void output_ascii_line(const char *c, const size_t len);


   /* --- check if command is available for language/format --- */

   /* ? */
GLOBAL int str_for_desttype(const char *s, _BOOL warn);
   /* ? */
GLOBAL _BOOL is_for_desttype(_BOOL *schalter, const char *cmd, _BOOL WARN);


   /* --- colors --- */

   /* ? */
GLOBAL _BOOL get_html_color(const char *s, struct rgb_and_color *rgb);
GLOBAL _BOOL get_html_color_or_rgb(const char *s, struct rgb_and_color *rgb);
const char *html_color_string(const struct rgb *color);


   /* --- index and TOC manager --- */

   /* ? */
GLOBAL _BOOL add_idxlist_item(const char *x1, const char *x2, const char *x3);
   /* ? */
GLOBAL void print_index(void);
   /* ? */
GLOBAL void output_htmlhelp_index(const int count, const char *x0, const char *x1, const char *x2);


   /* --- include --- */

   /* ? */
GLOBAL void c_include(void);


   /* --- token manager --- */

   /* ? */
GLOBAL void str2tok(const char *s);
   /* ? */
GLOBAL size_t toklen(const char *s);
   /* ? */
GLOBAL void tokcat(char *s, size_t maxlen);
   /* ? */
GLOBAL void tokcpy2(char *s, size_t maxlen);
   /* ? */
GLOBAL void token_reset(void);
   /* ? */
GLOBAL void token_output(_BOOL reset_internals, _BOOL with_para);
   /* ? */
GLOBAL void tokenize(char *s);


   /* --- path separator and suffix control --- */

   /* ? */
GLOBAL void change_sep_suffix(char *full, const char *suff);
   /* ? */
GLOBAL void dest_special_adjust(void);
   /* ? */
GLOBAL void dest_adjust(void);


   /* --- file name composition --- */
   /* ? */
GLOBAL void build_include_filename(char *d, const char *relto, const char *suff);
   /* ? */
GLOBAL void build_image_filename(char *d, const char *suff);


   /* --- main routines --- */

GLOBAL _BOOL udo (const char *datei);

GLOBAL void init_udo_vars(void);
void exit_udo_vars(void);


#endif  /* __UDO_H__ */
