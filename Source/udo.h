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
*    fd  Feb 22: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Mar 01: new: use_short_itemizes
*                     use_short_enumerates
*                     use_short_descriptions
*                     use_short_lists
*    ggs Apr 21: use_short_tocs -> use_compressed_tocs
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





/*******************************************************************************
*
*     GLOBAL UNINITIALIZED VARIABLES
*
******************************************|************************************/

GLOBAL MYFILE      udofile;               /* */

GLOBAL int         iUdopass;              /* PASS1 oder PASS2 */

GLOBAL BOOLEAN     bNopDetected;          /* Fuer Debugging-Zwecke */

GLOBAL int         desttype;              /* Ausgabeformat  (TOASC, ...) */
GLOBAL int         destlang;              /* Ausgabesprache (TOENG, ...) */
GLOBAL int         iCharset;              /* Eingabe-Zeichensatz */
GLOBAL int         iEncodingSource;       /* encoding of UDO source documents */
GLOBAL int         iEncodingTarget;       /* encoding of target document */

GLOBAL int         iDateDay, 
                   iDateMonth, 
                   iDateYear;
GLOBAL int         iDateHour, 
                   iDateMin, 
                   iDateSec;

GLOBAL BOOLEAN     bNoLogfile;            /* Logfile anlegen? */
GLOBAL BOOLEAN     bNoHypfile;            /* Hyphenationfile anlegen? */
GLOBAL BOOLEAN     bNoIdxfile;            /* Indexfile anlegen? */
GLOBAL BOOLEAN     bBeQuiet;              /* Statusinfos nicht ausgeben? */
GLOBAL BOOLEAN     bCheckMisc;            /* diverse Ueberpruefungen? */
GLOBAL BOOLEAN     bVerbose;              /* langen Status ausgeben? */
GLOBAL BOOLEAN     bTestmode;             /* Testmodus? */
GLOBAL BOOLEAN     bUseTreefile;          /* Include-Baum listen? */
GLOBAL BOOLEAN     bUseUPRfile;           /* Project-File sichern? */
GLOBAL BOOLEAN     bUseIdMapFileC;        /* Jump-ID-File fuer HPJ? */
GLOBAL BOOLEAN     bUseIdMapFilePas;      /* Jump-ID-File fuer HPJ? */
GLOBAL BOOLEAN     bUseIdMapFileVB;       /* Jump-ID-File fuer HPJ? */
GLOBAL BOOLEAN     bUseIdMapFileGFA;      /* Jump-ID-File fuer HPJ? */
GLOBAL BOOLEAN     bNoWarnings;           /* Keine Warnungen ausgeben? */
GLOBAL BOOLEAN     bNoWarningsLines;      /* Keine Warnungen ausgeben, bei zu langen oder kurzen Zeilen */
GLOBAL BOOLEAN     bForceLong;            /* Immer lange Dateinamen? */
GLOBAL BOOLEAN     bForceShort;           /* Immer kurze Dateinamen? */

GLOBAL size_t      zDocParwidth;          /* PL6: max. Zeilenbreite */

GLOBAL int         iTexVersion;           /* Lindner-, Strunk-, emTex? */   
GLOBAL int         iTexDPI;               /* Aufloesung fuer Images */
GLOBAL BOOLEAN     bTex2e;                /* LaTeX2e wird benutzt? */
GLOBAL char        cTexVerb;              /* Zeichen fuer \verb */

GLOBAL char        sSrcRemOn[8];          /* Kommentar ein */
GLOBAL char        sSrcRemOff[8];         /* Kommentar aus */

GLOBAL int         bDocTabwidth;          /* Tab-Width fuer verbatim-Umgebung */
GLOBAL int         iDocVerbatimSize;      /* Fontgroesse fuer verbatim-Umgebung */
GLOBAL int         iDocLinedrawSize;      /* Fontgroesse fuer linedraw-Umgebung */

GLOBAL char        sCurrFileName[512];    /* Gerade aktive Datei */
GLOBAL UWORD       uiCurrFileLine;        /* und die aktuelle Zeilen-Nr. */
GLOBAL UWORD       uiMultiLines;          /* Anzahl zusammengefuegter Zeilen (0=nicht zusammengefuegt, 1=eine Zeile angehaengt) */

GLOBAL BOOLEAN     b1stQuote;             /* flag for "real" double quotation marks */
GLOBAL BOOLEAN     b1stApost;             /* flag for 'real' single quotation marks */

GLOBAL char        tmp_driv[MYFILE_DRIV_LEN + 1];
GLOBAL char        tmp_path[MYFILE_PATH_LEN + 1];
GLOBAL char        tmp_name[MYFILE_NAME_LEN + 1];
GLOBAL char        tmp_suff[MYFILE_SUFF_LEN + 1];

GLOBAL MYFILE      outfile;
GLOBAL MYFILE      infile;
GLOBAL MYFILE      old_outfile;
GLOBAL BOOLEAN     bOutOpened;            /* File geoeffnet? */

GLOBAL FILE       *fLogfile;
GLOBAL char        sLogfull[MYFILE_FULL_LEN + 1];
GLOBAL BOOLEAN     bLogopened;            /* Logfile geoeffnet? */

GLOBAL FILE       *fHypfile;
GLOBAL char        sHypfull[MYFILE_FULL_LEN + 1];
GLOBAL BOOLEAN     bHypopened;            /* Hyphenfile geoeffnet? */
GLOBAL BOOLEAN     bHypfailed;            /* Hypfile oeffnen gescheitert */

GLOBAL FILE       *fTreefile;
GLOBAL char        sTreefull[MYFILE_FULL_LEN + 1];
GLOBAL BOOLEAN     bTreeopened;           /* Treefile geoeffnet? */

GLOBAL FILE       *fIdxfile;
GLOBAL char        sIdxfull[MYFILE_FULL_LEN + 1];
GLOBAL BOOLEAN     bIdxopened;            /* Indexfile geoeffnet? */
GLOBAL BOOLEAN     bIdxfailed;            /* Indexfile oeffnen gescheitert*/

GLOBAL FILE       *fUPRfile;
GLOBAL char        sUPRfull[MYFILE_FULL_LEN + 1];
GLOBAL BOOLEAN     bUPRopened;            /* Logfile geoeffnet? */

GLOBAL char        sInfMsg[256];          /* Zur Information */

GLOBAL char        sCmdfull[512];         /* Name der CMD-Datei fuer PCH */
GLOBAL char        sHpjfull[512];         /* Name der HPJ-Datei fuer Win */
GLOBAL char        sCntfull[512];         /* Name der CNT-Datei fuer Win4 */
GLOBAL char        sMapNoSuff[512];       /* Name der Map-Datei fuer Win ohne Suffix */
GLOBAL char        sHhpfull[512];         /* Name der HHP-Datei fuer HTML Help */
GLOBAL char        sHhcfull[512];         /* Name der HHC-Datei fuer HTML Help */
GLOBAL char        sHhkfull[512];         /* Name der HHK-Datei fuer HTML Help */

GLOBAL PASSFLAGS   pflag[3];              /* Flags fuer die Durchlaeufe */

GLOBAL BOOLEAN     bFatalErrorDetected;   /* Fataler Fehler aufgetreten? */
GLOBAL BOOLEAN     bErrorDetected;        /* Fehler aufgetreten? */
GLOBAL BOOLEAN     bBreakHappened;        /* wuenscht User Abbruch */
GLOBAL BOOLEAN     bBreakInside;          /* !break gelesen */

GLOBAL BOOLEAN     udo_running;           /* Ist UDO gerade am werkeln? */
GLOBAL BOOLEAN     uses_udolink;          /* Wird !udolink benutzt? */
GLOBAL BOOLEAN     uses_toplink;          /* Wird !toplink benutzt? */

GLOBAL LANG        lang;                  /* Spracheinstellungen */

GLOBAL char        token[MAX_TOKENS][MAX_TOKEN_LEN + 1];
GLOBAL int         token_counter;
GLOBAL BOOLEAN     tokens_contain_item;

GLOBAL char        udosymbol[MAX_UDOSYMBOLS][MAX_UDOSYMBOL_LEN + 1];
GLOBAL int         udosymbol_counter;


GLOBAL BOOLEAN     use_auto_subtocs;      /* create sub TOCs automatically? */
GLOBAL BOOLEAN     use_auto_subsubtocs;
GLOBAL BOOLEAN     use_auto_subsubsubtocs;
GLOBAL BOOLEAN     use_auto_subsubsubsubtocs;

GLOBAL BOOLEAN     use_auto_toptocs;      /* autom. Ueber-Toc's anlegen? */
GLOBAL BOOLEAN     no_auto_toptocs_icons; /* ... aber ohne Icons */   /*r6pl13*/
GLOBAL BOOLEAN     use_compressed_tocs;   /* Kurze Inhaltsverzeichnisse default? */

GLOBAL BOOLEAN     use_compressed_envs;   /* compress all supporting environments */
                                          /* compress all itemize environments only */
GLOBAL BOOLEAN     use_compressed_itemizes;
                                          /* compress all enumerate environments only */
GLOBAL BOOLEAN     use_compressed_enumerates;
                                          /* compress all description environments only */
GLOBAL BOOLEAN     use_compressed_descriptions;
GLOBAL BOOLEAN     use_compressed_lists;  /* compress all ?list environments only */

GLOBAL BOOLEAN     use_formfeed;          /* Formfeed verwenden? */
GLOBAL BOOLEAN     use_chapter_images;    /* Kapitelgrafiken verwenden? */
GLOBAL BOOLEAN     use_about_udo;
GLOBAL BOOLEAN     use_ansi_tables;       /* Tabellen mit ANSI-Grafiken umrahmen? */
GLOBAL BOOLEAN     use_style_book;        /* chapter oder sections? */
GLOBAL BOOLEAN     use_justification;     /* Blocksatz? */
GLOBAL BOOLEAN     use_nodes_inside_index;/* Kapitel in den Index uebernehmen? */
GLOBAL BOOLEAN     use_alias_inside_index;/* Aliase in den Index uebernehmen? */
GLOBAL BOOLEAN     use_label_inside_index;/* Labels in den Index uebernehmen? */
GLOBAL BOOLEAN     use_udo_index;         /* Soll UDO einen Index ausgeben? */
GLOBAL BOOLEAN     use_mirrored_indices;  /* !index I1 !! I2 auch spiegeln? */
GLOBAL BOOLEAN     use_comments;          /* Kommentare ausgeben (!rem [...]) */
GLOBAL BOOLEAN     use_auto_helpids;      /* HelpIDs automatisch generieren? */      /* r6pl13 */

GLOBAL BOOLEAN     no_umlaute;            /* Umlaute durch ae etc. ersetzen? */
GLOBAL BOOLEAN     no_headlines;          /* Keine Titelzeilen? */
GLOBAL BOOLEAN     no_titles;             /* Keine Ueberschriften? */
GLOBAL BOOLEAN     no_bottomlines;        /* Keine Fusszeilen? */
GLOBAL BOOLEAN     no_popup_headlines;    /* In Popups nie eine Titelzeile? */
GLOBAL BOOLEAN     no_footers;            /* Keine speziellen Fusszeilen? */
GLOBAL BOOLEAN     no_effects;            /* Keine Effekte? */
GLOBAL BOOLEAN     no_numbers;            /* Kapitel mit Nummern ausgeben? */
GLOBAL BOOLEAN     no_quotes;             /* "unechte" Anfuehrungszeichnen? */
GLOBAL BOOLEAN     no_preamble;           /* preamble nicht ausgeben? */
GLOBAL BOOLEAN     no_index;              /* !index ignorieren und keinen Index? */
GLOBAL BOOLEAN     no_buttons;            /* Keine Knoepfe erzeugen (WinHelp) */
GLOBAL BOOLEAN     no_img_size;           /* Keine Ausmasse ermitteln? */
GLOBAL BOOLEAN     no_images;             /* Bilder verwenden? */
GLOBAL BOOLEAN     no_urls;               /* Keine URLs verwenden? */
GLOBAL BOOLEAN     no_xlinks;             /* Keine externen Links verwenden? */
GLOBAL BOOLEAN     no_links;              /* Keine Links verwenden? */
GLOBAL BOOLEAN     no_sourcecode;         /* Sourcecode-Umgebung nicht ausgeben? */
GLOBAL BOOLEAN     no_table_lines;        /* Tabellen ohne Linien ausgeben? */

GLOBAL BOOLEAN     bDocAutorefOff;        /* Nicht autom. referenzieren? */
GLOBAL BOOLEAN     bDocAutorefItemsOff;   /* Items nicht autom. referenzieren? */
GLOBAL BOOLEAN     bDocUniversalCharsetOn;/* Universellen Zeichensatz benutzen? */
GLOBAL BOOLEAN     bDocRtfKeepTablesOn;   /* Tabellen zusammenhalten? */
GLOBAL BOOLEAN     bDocWinOldKeywords;    /* Alte Keywords benutzen? */
GLOBAL BOOLEAN     bDocSortHyphenFile;    /* *.uh? sortieren */

GLOBAL BOOLEAN     html_merge_node1;      /* Nodes nicht splitten? */
GLOBAL BOOLEAN     html_merge_node2;      /* Subnodes nicht splitten? */
GLOBAL BOOLEAN     html_merge_node3;      /* Subsubnodes nicht splitten? */
GLOBAL BOOLEAN     html_merge_node4;      /* Subsubsubnodes nicht splitten? */
GLOBAL BOOLEAN     html_merge_node5;      /* Subsubsubsubnodes nicht splitten? */
GLOBAL BOOLEAN     html_no_xlist;         /* xlist- durch description-Umgebung ersetzen? */
GLOBAL BOOLEAN     html_ignore_8bit;      /* ae nicht in &auml; wandeln? */
GLOBAL BOOLEAN     html_modern_layout;    /* Modernes 2-Spalten-Layout? */
GLOBAL BOOLEAN     html_frames_layout;    /* Frames fuer HTML benutzen? */
GLOBAL BOOLEAN     html_frames_noresize;
GLOBAL BOOLEAN     html_frames_noborder;
GLOBAL BOOLEAN     html_frames_noscroll;
GLOBAL BOOLEAN     html_use_folders;      /* Ordnerstruktur erzeugen? */
                                          /* Transparente Buttons benutzen? */
GLOBAL BOOLEAN     html_transparent_buttons;

GLOBAL SHOW_VAR    show_variable;         /* New in V6.5.19 */

GLOBAL BOOLEAN     html_navigation_line;  /* v6.5.19[fd] TRUE: show navigation levels in one line without folder symbols */
                                          /* v6.5.19[fd] string which separates navigation levels (default: '&gt; ') */
GLOBAL char        html_navigation_separator[20];
GLOBAL BOOLEAN     html_navigation_image; /* v6.5.19[fd] TRUE: show (folder) symbol */
                                          /* v6.5.19[fd] fspec to userdef (folder equivalent) symbol */
GLOBAL char        html_navigation_image_fspec[128];

                                          /* v6.5.0[vj] Use extra charset for meta http-equiv="Content-Type"? This flag is used just for speedup reasons */
GLOBAL BOOLEAN     html_ignore_8bit_use_charset;
                                          /* v6.5.0[vj] Charset for html_ignore_8bit that should be used in meta http-equiv="Content-Type" */
GLOBAL char        html_ignore_8bit_charset[20];

                                          /* Links zum Wechseln? */
GLOBAL char        sDocHtmlSwitchLanguage[256];
GLOBAL int         iDocHtmlSwitchLanguage;/* ... und der Wert der Sprache */
GLOBAL char        sCounterCommand[512];  /* CounterCommand for all files V6.5.9 */

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
GLOBAL char        html_modern_width[16]; /* Breite der linken Spalte */
GLOBAL int         html_modern_alignment; /* Ausrichtung linke Spalte */
                                          /* background color of left column */
GLOBAL char        html_modern_backcolor[16];
                                          /* Image der linken Spalte */
GLOBAL char        html_modern_backimage[512];
GLOBAL char        html_frames_width[16]; /* Breite des linken Frames */
GLOBAL char        html_frames_height[16];/* Breite des oberen Frames */
GLOBAL int         html_frames_position;  /* Position des Frames */
GLOBAL int         html_frames_alignment; /* Ausrichtung linker Frame */
                                          /* Backfarbe des linken Frames */
GLOBAL char        html_frames_backcolor[16];
                                          /* Textfarbe des linken Frames */
GLOBAL char        html_frames_textcolor[16];
                                          /* Linkfarbe der linken Spalte */
GLOBAL char        html_frames_linkcolor[16];
                                          /* Linkfarbe der linken Spalte */
GLOBAL char        html_frames_alinkcolor[16];
                                          /* Linkfarbe der linken Spalte */
GLOBAL char        html_frames_vlinkcolor[16];
                                          /* Image des linken Frames */
GLOBAL char        html_frames_backimage[512];
GLOBAL int         html_button_alignment; /* Ausrichtung der Buttons */
GLOBAL int         html_quotes;           /* define HTML formatting of quotes */
GLOBAL char        html_name_prefix[512]; /* Prefix fuer HTML-Dateinamen */

/* New in r6pl16 [NHz] */
GLOBAL BOOLEAN     html_use_hyphenation;  /* Lange Woerter sollen durch (!-) getrennt werden */
GLOBAL int         html_doctype;          /* Welche DTD soll benutzt werden? */

/* New feature #0000054 in V6.5.2 [NHz] */
GLOBAL BOOLEAN     html_header_date;      /* Ausgabe des Datums im Element <meta> */
                                          /* date zone */
GLOBAL char        html_header_date_zone[10];

/* New feature #0000053 in V6.5.2 [NHz] */
GLOBAL BOOLEAN     html_header_links;     /* Ausgabe der Daten im Element <link> */
                                          /* Welche Links sollen ausgegeben werden? */
GLOBAL char        html_header_links_kind[50];

GLOBAL int         image_alignment;       /* Ausrichtung der Bilder */
GLOBAL int         table_alignment;       /* Ausrichtung der Tabellen */

GLOBAL char        sDocWinPrefixID[64];   /* Prefix fuer autom. Help-IDs */

GLOBAL char        sDrcBcolor[3];         /* DRC-Farbe fuer bold r6pl5 */
GLOBAL char        sDrcIcolor[3];         /* DRC-Farbe fuer italic r6pl5 */
GLOBAL char        sDrcUcolor[3];         /* DRC-Farbe fuer underlined r6pl5 */
GLOBAL int         iDrcFlags;             /* DRC-Flags fuer EDIT, SAVE, PRINT, ... */

GLOBAL int         iManPageLines;         /* ausgegebene Zeilen pro Seite */
GLOBAL int         iManPagePages;         /* bereits ausgegebene Seiten */
GLOBAL int         iManPageLength;        /* maximale Zeilen pro Seite */
GLOBAL char        sDocManType[32];       /* Typ (1), (C), ... */
GLOBAL char        sDocNroffType[32];     /* dito fuer nroff */

GLOBAL char        sDocImgSuffix[32];     /* gif, jpg, jpeg, ... */
GLOBAL char        sDocBackImage[128];    /*r6pl5*/
GLOBAL char        sDocStyle[128];        /* r6pl15 [NHz] */
GLOBAL char        sDocScript[128];       /* r6pl15 [NHz] */
GLOBAL char        sDocFavIcon[128];      /* r6pl15 [NHz] */
GLOBAL char        sDocBackColor[32];
GLOBAL char        sDocTextColor[32];
GLOBAL char        sDocLinkColor[32];
GLOBAL char        sDocAlinkColor[32];
GLOBAL char        sDocVlinkColor[32];
GLOBAL char        sDocVerbatimBackColor[32];

GLOBAL char        sDocRawHeaderFilename[512];     /*r6pl10*/
GLOBAL char        sDocRawFooterFilename[512];     /*r6pl10*/

GLOBAL BOOLEAN     bDocInlineBitmaps;     /* {bmcwd statt {bmc verwenden? */
GLOBAL BOOLEAN     bDocHighCompression;
GLOBAL BOOLEAN     bDocMediumCompression;

GLOBAL int         iDocCharwidth;         /* Zeichenbreiten-Konstanten */

/* New in V6.5.9 [NHz] */
GLOBAL char        sDocColour[512];       /* additional colors for RTF */
                                          /* Proportional- und Monospacedfont */
GLOBAL char        sDocPropfont[MAXZEILE + 1];
                                          /* fuer den RTF-Header */
GLOBAL char        sDocMonofont[MAXZEILE + 1];
GLOBAL char        sDocPropfontSize[16];
GLOBAL int         iDocPropfontSize;
GLOBAL char        sDocMonofontSize[16];
GLOBAL int         iDocMonofontSize;
GLOBAL BOOLEAN     bDocNoTables;          /* Keine echten RTF-Tabellen anlegen? */

GLOBAL BOOLEAN     bCalledIndex;          /* !index ignorieren und keinen Index? */





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
GLOBAL void outlncenter(char *s);
   /* ? */
GLOBAL void outlncenterfill(char *s);
   /* ? */
GLOBAL void strright(char *string, size_t length);
   /* ? */
GLOBAL void output_ascii_line(const char *c, const size_t len);


   /* --- check if command is available for language/format --- */

   /* ? */
GLOBAL BOOLEAN str_for_desttype(const char *s);
   /* ? */
GLOBAL BOOLEAN is_for_desttype(BOOLEAN *schalter, const char *cmd);


   /* --- colors --- */

   /* ? */
GLOBAL BOOLEAN get_html_color(const char *s, char *h);


   /* --- commandline symbol manager --- */

   /* ? */
GLOBAL void del_udosymbol(const char *s);
   /* ? */
GLOBAL void add_udosymbol(const char *s);
   /* ? */
GLOBAL BOOLEAN udosymbol_set(const char *s);


   /* --- index and TOC manager --- */

   /* ? */
GLOBAL BOOLEAN add_idxlist_item(const char *x1, const char *x2, const char *x3);
   /* ? */
GLOBAL void print_index(void);
   /* ? */
GLOBAL void output_htmlhelp_index(const int count, const char *x0, const char *x1, const char *x2);


   /* --- miscellaneous --- */

   /* ? */
GLOBAL void c_debug(void);
   /* ? */
GLOBAL void c_udolink(void);
   /* ? */
GLOBAL void c_toplink(void);



   /* --- include --- */

   /* ? */
GLOBAL void c_include(void);


   /* --- token manager --- */

   /* ? */
GLOBAL void str2tok(char *s);
   /* ? */
GLOBAL size_t toklen(char *s);
   /* ? */
GLOBAL void tokcat(char *s, size_t maxlen);
   /* ? */
GLOBAL void tokcpy2(char *s, size_t maxlen);
   /* ? */
GLOBAL void token_reset(void);
   /* ? */
GLOBAL void token_output(BOOLEAN reset_internals);
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
GLOBAL void build_search_file(char *d, const char *suff);
   /* ? */
GLOBAL void build_search_file_output(char *d, const char *suff);
   /* ? */
GLOBAL void build_include_filename(char *d, const char *suff);
   /* ? */
GLOBAL void build_image_filename(char *d, const char *suff);


   /* --- main routines --- */

   /* ? */
GLOBAL BOOLEAN udo (char *datei);
   /* ? */
GLOBAL BOOLEAN udo2udo (char *datei);
   /* ? */
GLOBAL void init_vars(void);


   /* --- project file entry manager --- */

   /* ? */
GLOBAL void save_upr_entry_infile(const char *filename);
   /* ? */
GLOBAL void save_upr_entry_outfile(const char *filename);
   /* ? */
GLOBAL void save_upr_entry_image(const char *filename);

/* Changed in r6pl15 [NHz] */
/* Extra parameter line */
   /* ? */
GLOBAL void save_upr_entry_node(const int level, const char *filename, const char *title, const long line);
   /* ? */
GLOBAL void save_upr_entry_heading(const int level, const char *filename, const char *title, const long line ); /* New in r6pl15 [NHz] */
   /* ? */
GLOBAL void save_upr_entry_alias(const char *filename, const char *title, const long line ); /* New in r6pl15 [NHz] */
   /* ? */
GLOBAL void save_upr_entry_label(const char *filename, const char *title, const long line ); /* New in r6pl15 [NHz] */
   /* ? */
GLOBAL void save_upr_entry_index(const int level, const char *filename, const char *title, const long line ); /* New in r6pl15 [NHz] */


#endif  /* __UDO_H__ */


/* +++ EOF +++ */
