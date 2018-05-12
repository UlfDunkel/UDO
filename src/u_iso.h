/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_iso.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepages for ISO encodings:
*                 - u_CODE_LATIN1[]:   iso-8859-1,  Latin1, West European
*                 - u_CODE_LATIN2[]:   iso-8859-2,  Latin2, Middle European
*                 - u_CODE_LATIN3[]:   iso-8859-3,  Latin3, South European
*                 - u_CODE_LATIN4[]:   iso-8859-4,  Latin4, North European
*                 - u_CODE_CYRILLIC[]: iso-8859-5,  Cyrillic
*                 - u_CODE_ARABIC[]:   iso-8859-6,  Arabic
*                 - u_CODE_GREEK[]:    iso-8859-7,  Greek
*                 - u_CODE_HEBREW[]:   iso-8859-8,  Hebrew
*                 - u_CODE_TURKISH[]:  iso-8859-9,  Latin5, Turkish
*                 - u_CODE_NORDIC[]:   iso-8859-10, Latin6, Nordic
*                 - u_CODE_THAI[]:     iso-8859-11, Thai
*                 < There is no iso-8859-12 defined yet at www.unicode.org! >
*                 - u_CODE_BALTIC[]:   iso-8859-13, Latin7, Baltic
*                 - u_CODE_CELTIC[]:   iso-8859-14, Latin8, Celtic
*                 - u_CODE_LATIN9[]:   iso-8859-15, Latin9, West European
*                 - u_CODE_LATIN10[]:  iso-8859-16, Latin10, South East European
*
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
*  Author       : Ulf Dunkel (fd)
*  Co-Authors   : -
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
*    fd  Feb 15: file introduced
*    fd  Feb 16: - u_CODE_CP1250[] added
*                - ligatures and sorting tables moved from encoding.h
*                - CODE_CP1250_lig, sort_CODE_CP1250 added
*    fd  Feb 18: CODE_LAT2
*    fd  Feb 19: all Microsoft Windows codepage encodings moved to u_mswin.h
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 23: - tables adjusted
*                - CODE_LAT2 -> CODE_LATIN2
*                - CODE_LATIN1
*    fd  Mar 05: - CODE_LATIN3
*                - CODE_LATIN4
*                - CODE_CYRILLIC
*                - CODE_ARABIC
*                - CODE_GREEK
*                - CODE_HEBREW
*    fd  Mar 08: - CODE_TURKISH
*                - CODE_NORDIC
*                - CODE_THAI
*                - CODE_BALTIC
*                - CODE_CELTIC
*                - CODE_LATIN9
*                - CODE_LATIN10
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#include "udoport.h"
#include "unicode.h"





/******************************************************************************
*
*  u_CODE_LATIN1[]:
*     Unicode named codepage for ISO encoding Latin-1 (iso-8859-1)
*
*  Name:             ISO/IEC 8859-1:1998 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_LATIN1[] =          /* CODE_LATIN1 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_FeminineOrdinalIndicator,            /* 0xAA   0x00AA   FEMININE ORDINAL INDICATOR */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_MasculineOrdinalIndicator,           /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_LatinCapitalLetterAWithGrave,        /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithTilde,        /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLigatureAE,              /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterEWithGrave,        /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterIWithGrave,        /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 0xD0   0x00D0   LATIN CAPITAL LETTER ETH (Icelandic) */
   U_LatinCapitalLetterNWithTilde,        /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterOWithGrave,        /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithTilde,        /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterOSlash,            /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterUWithGrave,        /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterYWithAcute,        /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 0xDE   0x00DE   LATIN CAPITAL LETTER THORN (Icelandic) */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S (German) */
   U_LatinSmallLetterAWithGrave,          /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithTilde,          /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithRingAbove,      /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLigatureAE,                /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithGrave,          /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithCircumflex,     /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterIWithGrave,          /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterEth,                 /* 0xF0   0x00F0   LATIN SMALL LETTER ETH (Icelandic) */
   U_LatinSmallLetterNWithTilde,          /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinSmallLetterOWithGrave,          /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithTilde,          /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinSmallLetterOSlash,              /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinSmallLetterUWithGrave,          /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterYWithAcute,          /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinSmallLetterThorn,               /* 0xFE   0x00FE   LATIN SMALL LETTER THORN (Icelandic) */
   U_LatinSmallLetterYWithDiaeresis       /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};





/******************************************************************************
*
*  CODE_LATIN1_lig[]:
*     list of ligatures:
*
*  CODE_LATIN1_lig[0] is the original ligature character
*  CODE_LATIN1_lig[1] + CODE_LATIN1_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_LATIN1_lig[][3] =     /* CODE_LATIN1 character ligatures */
{
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S (German) */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterAWithRingAbove,    U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterYWithDiaeresis,    U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */

   {0x0000,                               U_NIL,                 U_NIL}                    /* list terminator */
};





/******************************************************************************
*
*  CODE_LATIN1 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_LATIN1[] =       /* CODE_LATIN1 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_FeminineOrdinalIndicator,            /* 0xAA   0x00AA   FEMININE ORDINAL INDICATOR */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_MasculineOrdinalIndicator,           /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_LatinCapitalLetterA,                 /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 0xD0   0x00D0   LATIN CAPITAL LETTER ETH (Icelandic) */
   U_LatinCapitalLetterN,                 /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterO,                 /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 0xDE   0x00DE   LATIN CAPITAL LETTER THORN (Icelandic) */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S (German) */
   U_LatinCapitalLetterA,                 /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 0xF0   0x00F0   LATIN SMALL LETTER ETH (Icelandic) */
   U_LatinCapitalLetterN,                 /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinCapitalLetterO,                 /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 0xFE   0x00FE   LATIN SMALL LETTER THORN (Icelandic) */
   U_LatinCapitalLetterY                  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};










/******************************************************************************
*
*  u_CODE_LATIN2[]:
*     Unicode named codepage for ISO encoding Latin-2 (iso-8859-2)
*
*  Name:             ISO 8859-2:1999 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_LATIN2[] =          /* CODE_LATIN2 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterAWithOgonek,       /* 0xA1   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_Breve,                               /* 0xA2   0x02D8   BREVE */
   U_LatinCapitalLetterLWithStroke,       /* 0xA3   0x0141   LATIN CAPITAL LETTER L WITH STROKE */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_LatinCapitalLetterLWithCaron,        /* 0xA5   0x013D   LATIN CAPITAL LETTER L WITH CARON */
   U_LatinCapitalLetterSWithAcute,        /* 0xA6   0x015A   LATIN CAPITAL LETTER S WITH ACUTE */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_LatinCapitalLetterSWithCaron,        /* 0xA9   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LatinCapitalLetterSWithCedilla,      /* 0xAA   0x015E   LATIN CAPITAL LETTER S WITH CEDILLA */
   U_LatinCapitalLetterTWithCaron,        /* 0xAB   0x0164   LATIN CAPITAL LETTER T WITH CARON */
   U_LatinCapitalLetterZWithAcute,        /* 0xAC   0x0179   LATIN CAPITAL LETTER Z WITH ACUTE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinCapitalLetterZWithCaron,        /* 0xAE   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_LatinCapitalLetterZWithDotAbove,     /* 0xAF   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_LatinSmallLetterAWithOgonek,         /* 0xB1   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_Ogonek,                              /* 0xB2   0x02DB   OGONEK */
   U_LatinSmallLetterLWithStroke,         /* 0xB3   0x0142   LATIN SMALL LETTER L WITH STROKE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_LatinSmallLetterLWithCaron,          /* 0xB5   0x013E   LATIN SMALL LETTER L WITH CARON */
   U_LatinSmallLetterSWithAcute,          /* 0xB6   0x015B   LATIN SMALL LETTER S WITH ACUTE */
   U_Caron,                               /* 0xB7   0x02C7   CARON */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_LatinSmallLetterSWithCaron,          /* 0xB9   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinSmallLetterSWithCedilla,        /* 0xBA   0x015F   LATIN SMALL LETTER S WITH CEDILLA */
   U_LatinSmallLetterTWithCaron,          /* 0xBB   0x0165   LATIN SMALL LETTER T WITH CARON */
   U_LatinSmallLetterZWithAcute,          /* 0xBC   0x017A   LATIN SMALL LETTER Z WITH ACUTE */
   U_DoubleAcuteAccent,                   /* 0xBD   0x02DD   DOUBLE ACUTE ACCENT */
   U_LatinSmallLetterZWithCaron,          /* 0xBE   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_LatinSmallLetterZWithDotAbove,       /* 0xBF   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterRWithAcute,        /* 0xC0   0x0154   LATIN CAPITAL LETTER R WITH ACUTE */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithBreve,        /* 0xC3   0x0102   LATIN CAPITAL LETTER A WITH BREVE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xC5   0x0139   LATIN CAPITAL LETTER L WITH ACUTE */
   U_LatinCapitalLetterCWithAcute,        /* 0xC6   0x0106   LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterCWithCaron,        /* 0xC8   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithOgonek,       /* 0xCA   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterEWithCaron,        /* 0xCC   0x011A   LATIN CAPITAL LETTER E WITH CARON */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterDWithCaron,        /* 0xCF   0x010E   LATIN CAPITAL LETTER D WITH CARON */
   U_LatinCapitalLetterDWithStroke,       /* 0xD0   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterNWithAcute,        /* 0xD1   0x0143   LATIN CAPITAL LETTER N WITH ACUTE */
   U_LatinCapitalLetterNWithCaron,        /* 0xD2   0x0147   LATIN CAPITAL LETTER N WITH CARON */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithDoubleAcute,  /* 0xD5   0x0150   LATIN CAPITAL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterRWithCaron,        /* 0xD8   0x0158   LATIN CAPITAL LETTER R WITH CARON */
   U_LatinCapitalLetterUWithRingAbove,    /* 0xD9   0x016E   LATIN CAPITAL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithDoubleAcute,  /* 0xDB   0x0170   LATIN CAPITAL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterYWithAcute,        /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterTWithCedilla,      /* 0xDE   0x0162   LATIN CAPITAL LETTER T WITH CEDILLA */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterRWithAcute,          /* 0xE0   0x0155   LATIN SMALL LETTER R WITH ACUTE */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithBreve,          /* 0xE3   0x0103   LATIN SMALL LETTER A WITH BREVE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterLWithAcute,          /* 0xE5   0x013A   LATIN SMALL LETTER L WITH ACUTE */
   U_LatinSmallLetterCWithAcute,          /* 0xE6   0x0107   LATIN SMALL LETTER C WITH ACUTE */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterCWithCaron,          /* 0xE8   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithOgonek,         /* 0xEA   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterEWithCaron,          /* 0xEC   0x011B   LATIN SMALL LETTER E WITH CARON */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterDWithCaron,          /* 0xEF   0x010F   LATIN SMALL LETTER D WITH CARON */
   U_LatinSmallLetterDWithStroke,         /* 0xF0   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinSmallLetterNWithAcute,          /* 0xF1   0x0144   LATIN SMALL LETTER N WITH ACUTE */
   U_LatinSmallLetterNWithCaron,          /* 0xF2   0x0148   LATIN SMALL LETTER N WITH CARON */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithDoubleAcute,    /* 0xF5   0x0151   LATIN SMALL LETTER O WITH DOUBLE ACUTE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinSmallLetterRWithCaron,          /* 0xF8   0x0159   LATIN SMALL LETTER R WITH CARON */
   U_LatinSmallLetterUWithRingAbove,      /* 0xF9   0x016F   LATIN SMALL LETTER U WITH RING ABOVE */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithDoubleAcute,    /* 0xFB   0x0171   LATIN SMALL LETTER U WITH DOUBLE ACUTE */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterYWithAcute,          /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinSmallLetterTWithCedilla,        /* 0xFE   0x0163   LATIN SMALL LETTER T WITH CEDILLA */
   U_DotAbove                             /* 0xFF   0x02D9   DOT ABOVE */
};





/******************************************************************************
*
*  CODE_LATIN2_lig[]:
*     list of ligatures:
*
*  CODE_LATIN2_lig[0] is the original ligature character
*  CODE_LATIN2_lig[1] + CODE_LATIN2_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_LATIN2_lig[][3] =     /* CODE_LATIN2 character ligatures */
{
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xC5   0x0139   LATIN CAPITAL LETTER L WITH ACUTE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterUWithRingAbove,  U_LatinCapitalLetterU, U_LatinCapitalLetterO },  /* 0xD9   0x016E   LATIN CAPITAL LETTER U WITH RING ABOVE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterUWithRingAbove,    U_LatinCapitalLetterU, U_LatinCapitalLetterO },  /* 0xF9   0x016F   LATIN SMALL LETTER U WITH RING ABOVE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */

   {0x0000,                               U_NIL,                 U_NIL}                    /* list terminator */
};





/******************************************************************************
*
*  CODE_LATIN2 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_LATIN2[] =       /* CODE_LATIN2 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterA,                 /* 0xA1   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_Breve,                               /* 0xA2   0x02D8   BREVE */
   U_LatinCapitalLetterL,                 /* 0xA3   0x0141   LATIN CAPITAL LETTER L WITH STROKE */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_LatinCapitalLetterL,                 /* 0xA5   0x013D   LATIN CAPITAL LETTER L WITH CARON */
   U_LatinCapitalLetterS,                 /* 0xA6   0x015A   LATIN CAPITAL LETTER S WITH ACUTE */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_LatinCapitalLetterS,                 /* 0xA9   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LatinCapitalLetterS,                 /* 0xAA   0x015E   LATIN CAPITAL LETTER S WITH CEDILLA */
   U_LatinCapitalLetterT,                 /* 0xAB   0x0164   LATIN CAPITAL LETTER T WITH CARON */
   U_LatinCapitalLetterZ,                 /* 0xAC   0x0179   LATIN CAPITAL LETTER Z WITH ACUTE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinCapitalLetterZ,                 /* 0xAE   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_LatinCapitalLetterZ,                 /* 0xAF   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_LatinCapitalLetterA,                 /* 0xB1   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_Ogonek,                              /* 0xB2   0x02DB   OGONEK */
   U_LatinCapitalLetterL,                 /* 0xB3   0x0142   LATIN SMALL LETTER L WITH STROKE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_LatinCapitalLetterL,                 /* 0xB5   0x013E   LATIN SMALL LETTER L WITH CARON */
   U_LatinCapitalLetterS,                 /* 0xB6   0x015B   LATIN SMALL LETTER S WITH ACUTE */
   U_Caron,                               /* 0xB7   0x02C7   CARON */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_LatinCapitalLetterS,                 /* 0xB9   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinCapitalLetterS,                 /* 0xBA   0x015F   LATIN SMALL LETTER S WITH CEDILLA */
   U_LatinCapitalLetterT,                 /* 0xBB   0x0165   LATIN SMALL LETTER T WITH CARON */
   U_LatinCapitalLetterZ,                 /* 0xBC   0x017A   LATIN SMALL LETTER Z WITH ACUTE */
   U_DoubleAcuteAccent,                   /* 0xBD   0x02DD   DOUBLE ACUTE ACCENT */
   U_LatinCapitalLetterZ,                 /* 0xBE   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_LatinCapitalLetterZ,                 /* 0xBF   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterR,                 /* 0xC0   0x0154   LATIN CAPITAL LETTER R WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x0102   LATIN CAPITAL LETTER A WITH BREVE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterL,                 /* 0xC5   0x0139   LATIN CAPITAL LETTER L WITH ACUTE */
   U_LatinCapitalLetterC,                 /* 0xC6   0x0106   LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinCapitalLetterC,                 /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterC,                 /* 0xC8   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xCC   0x011A   LATIN CAPITAL LETTER E WITH CARON */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterD,                 /* 0xCF   0x010E   LATIN CAPITAL LETTER D WITH CARON */
   U_LatinCapitalLetterD,                 /* 0xD0   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xD1   0x0143   LATIN CAPITAL LETTER N WITH ACUTE */
   U_LatinCapitalLetterN,                 /* 0xD2   0x0147   LATIN CAPITAL LETTER N WITH CARON */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x0150   LATIN CAPITAL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterR,                 /* 0xD8   0x0158   LATIN CAPITAL LETTER R WITH CARON */
   U_LatinCapitalLetterU,                 /* 0xD9   0x016E   LATIN CAPITAL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x0170   LATIN CAPITAL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterT,                 /* 0xDE   0x0162   LATIN CAPITAL LETTER T WITH CEDILLA */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterR,                 /* 0xE0   0x0155   LATIN SMALL LETTER R WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x0103   LATIN SMALL LETTER A WITH BREVE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterL,                 /* 0xE5   0x013A   LATIN SMALL LETTER L WITH ACUTE */
   U_LatinCapitalLetterC,                 /* 0xE6   0x0107   LATIN SMALL LETTER C WITH ACUTE */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterC,                 /* 0xE8   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xEC   0x011B   LATIN SMALL LETTER E WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterD,                 /* 0xEF   0x010F   LATIN SMALL LETTER D WITH CARON */
   U_LatinCapitalLetterD,                 /* 0xF0   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xF1   0x0144   LATIN SMALL LETTER N WITH ACUTE */
   U_LatinCapitalLetterN,                 /* 0xF2   0x0148   LATIN SMALL LETTER N WITH CARON */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x0151   LATIN SMALL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinCapitalLetterR,                 /* 0xF8   0x0159   LATIN SMALL LETTER R WITH CARON */
   U_LatinCapitalLetterU,                 /* 0xF9   0x016F   LATIN SMALL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x0171   LATIN SMALL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterT,                 /* 0xFE   0x0163   LATIN SMALL LETTER T WITH CEDILLA */
   U_DotAbove                             /* 0xFF   0x02D9   DOT ABOVE */
};










/******************************************************************************
*
*  u_CODE_LATIN3[]:
*     Unicode named codepage for ISO encoding Latin-3 (iso-8859-3)
*
*  Name:             ISO/IEC 8859-3:1999 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_LATIN3[] =          /* CODE_LATIN3 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterHWithStroke,       /* 0xA1   0x0126   LATIN CAPITAL LETTER H WITH STROKE */
   U_Breve,                               /* 0xA2   0x02D8   BREVE */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_LatinCapitalLetterHWithCircumflex,   /* 0xA6   0x0124   LATIN CAPITAL LETTER H WITH CIRCUMFLEX */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_LatinCapitalLetterIWithDotAbove,     /* 0xA9   0x0130   LATIN CAPITAL LETTER I WITH DOT ABOVE */
   U_LatinCapitalLetterSWithCedilla,      /* 0xAA   0x015E   LATIN CAPITAL LETTER S WITH CEDILLA */
   U_LatinCapitalLetterGWithBreve,        /* 0xAB   0x011E   LATIN CAPITAL LETTER G WITH BREVE */
   U_LatinCapitalLetterJWithCircumflex,   /* 0xAC   0x0134   LATIN CAPITAL LETTER J WITH CIRCUMFLEX */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinCapitalLetterZWithDotAbove,     /* 0xAF   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_LatinSmallLetterHWithStroke,         /* 0xB1   0x0127   LATIN SMALL LETTER H WITH STROKE */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_LatinSmallLetterHWithCircumflex,     /* 0xB6   0x0125   LATIN SMALL LETTER H WITH CIRCUMFLEX */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_LatinSmallLetterDotlessI,            /* 0xB9   0x0131   LATIN SMALL LETTER DOTLESS I */
   U_LatinSmallLetterSWithCedilla,        /* 0xBA   0x015F   LATIN SMALL LETTER S WITH CEDILLA */
   U_LatinSmallLetterGWithBreve,          /* 0xBB   0x011F   LATIN SMALL LETTER G WITH BREVE */
   U_LatinSmallLetterJWithCircumflex,     /* 0xBC   0x0135   LATIN SMALL LETTER J WITH CIRCUMFLEX */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_LatinSmallLetterZWithDotAbove,       /* 0xBF   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterAWithGrave,        /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterCWithDotAbove,     /* 0xC5   0x010A   LATIN CAPITAL LETTER C WITH DOT ABOVE */
   U_LatinCapitalLetterCWithCircumflex,   /* 0xC6   0x0108   LATIN CAPITAL LETTER C WITH CIRCUMFLEX */
   U_LatinCapitalLetterCWithCedilla,      /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterEWithGrave,        /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterIWithGrave,        /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterNWithTilde,        /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterOWithGrave,        /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterGWithDotAbove,     /* 0xD5   0x0120   LATIN CAPITAL LETTER G WITH DOT ABOVE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterGWithCircumflex,   /* 0xD8   0x011C   LATIN CAPITAL LETTER G WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithGrave,        /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterUWithBreve,        /* 0xDD   0x016C   LATIN CAPITAL LETTER U WITH BREVE */
   U_LatinCapitalLetterSWithCircumflex,   /* 0xDE   0x015C   LATIN CAPITAL LETTER S WITH CIRCUMFLEX */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterAWithGrave,          /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterCWithDotAbove,       /* 0xE5   0x010B   LATIN SMALL LETTER C WITH DOT ABOVE */
   U_LatinSmallLetterCWithCircumflex,     /* 0xE6   0x0109   LATIN SMALL LETTER C WITH CIRCUMFLEX */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithGrave,          /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithCircumflex,     /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterIWithGrave,          /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterNWithTilde,          /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinSmallLetterOWithGrave,          /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterGWithDotAbove,       /* 0xF5   0x0121   LATIN SMALL LETTER G WITH DOT ABOVE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinSmallLetterGWithCircumflex,     /* 0xF8   0x011D   LATIN SMALL LETTER G WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithGrave,          /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterUWithBreve,          /* 0xFD   0x016D   LATIN SMALL LETTER U WITH BREVE */
   U_LatinSmallLetterSWithCircumflex,     /* 0xFE   0x015D   LATIN SMALL LETTER S WITH CIRCUMFLEX */
   U_DotAbove                             /* 0xFF   0x02D9   DOT ABOVE */
};





/******************************************************************************
*
*  CODE_LATIN3_lig[]:
*     list of ligatures:
*
*  CODE_LATIN3_lig[0] is the original ligature character
*  CODE_LATIN3_lig[1] + CODE_LATIN3_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_LATIN3_lig[][3] =     /* CODE_LATIN3 character ligatures */
{
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */

   {0x0000,                               U_NIL,                 U_NIL}                    /* list terminator */
};





/******************************************************************************
*
*  CODE_LATIN3 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_LATIN3[] =       /* CODE_LATIN3 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterH,                 /* 0xA1   0x0126   LATIN CAPITAL LETTER H WITH STROKE */
   U_Breve,                               /* 0xA2   0x02D8   BREVE */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_LatinCapitalLetterH,                 /* 0xA6   0x0124   LATIN CAPITAL LETTER H WITH CIRCUMFLEX */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xA9   0x0130   LATIN CAPITAL LETTER I WITH DOT ABOVE */
   U_LatinCapitalLetterS,                 /* 0xAA   0x015E   LATIN CAPITAL LETTER S WITH CEDILLA */
   U_LatinCapitalLetterG,                 /* 0xAB   0x011E   LATIN CAPITAL LETTER G WITH BREVE */
   U_LatinCapitalLetterJ,                 /* 0xAC   0x0134   LATIN CAPITAL LETTER J WITH CIRCUMFLEX */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinCapitalLetterZ,                 /* 0xAF   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_LatinCapitalLetterH,                 /* 0xB1   0x0127   LATIN SMALL LETTER H WITH STROKE */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_LatinCapitalLetterH,                 /* 0xB6   0x0125   LATIN SMALL LETTER H WITH CIRCUMFLEX */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_LatinCapitalLetterI,                 /* 0xB9   0x0131   LATIN SMALL LETTER DOTLESS I */
   U_LatinCapitalLetterS,                 /* 0xBA   0x015F   LATIN SMALL LETTER S WITH CEDILLA */
   U_LatinCapitalLetterG,                 /* 0xBB   0x011F   LATIN SMALL LETTER G WITH BREVE */
   U_LatinCapitalLetterJ,                 /* 0xBC   0x0135   LATIN SMALL LETTER J WITH CIRCUMFLEX */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_LatinCapitalLetterZ,                 /* 0xBF   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterC,                 /* 0xC5   0x010A   LATIN CAPITAL LETTER C WITH DOT ABOVE */
   U_LatinCapitalLetterC,                 /* 0xC6   0x0108   LATIN CAPITAL LETTER C WITH CIRCUMFLEX */
   U_LatinCapitalLetterC,                 /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterN,                 /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterG,                 /* 0xD5   0x0120   LATIN CAPITAL LETTER G WITH DOT ABOVE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterG,                 /* 0xD8   0x011C   LATIN CAPITAL LETTER G WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xDD   0x016C   LATIN CAPITAL LETTER U WITH BREVE */
   U_LatinCapitalLetterS,                 /* 0xDE   0x015C   LATIN CAPITAL LETTER S WITH CIRCUMFLEX */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterA,                 /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterC,                 /* 0xE5   0x010B   LATIN SMALL LETTER C WITH DOT ABOVE */
   U_LatinCapitalLetterC,                 /* 0xE6   0x0109   LATIN SMALL LETTER C WITH CIRCUMFLEX */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterN,                 /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterG,                 /* 0xF5   0x0121   LATIN SMALL LETTER G WITH DOT ABOVE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinCapitalLetterG,                 /* 0xF8   0x011D   LATIN SMALL LETTER G WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xFD   0x016D   LATIN SMALL LETTER U WITH BREVE */
   U_LatinCapitalLetterS,                 /* 0xFE   0x015D   LATIN SMALL LETTER S WITH CIRCUMFLEX */
   U_DotAbove                             /* 0xFF   0x02D9   DOT ABOVE */
};










/******************************************************************************
*
*  u_CODE_LATIN4[]:
*     Unicode named codepage for ISO encoding Latin-4 (iso-8859-4)
*
*  Name:             ISO/IEC 8859-4:1998 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_LATIN4[] =          /* CODE_LATIN4 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterAWithOgonek,       /* 0xA1   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinSmallLetterKra,                 /* 0xA2   0x0138   LATIN SMALL LETTER KRA */
   U_LatinCapitalLetterRWithCedilla,      /* 0xA3   0x0156   LATIN CAPITAL LETTER R WITH CEDILLA */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_LatinCapitalLetterIWithTilde,        /* 0xA5   0x0128   LATIN CAPITAL LETTER I WITH TILDE */
   U_LatinCapitalLetterLWithCedilla,      /* 0xA6   0x013B   LATIN CAPITAL LETTER L WITH CEDILLA */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_LatinCapitalLetterSWithCaron,        /* 0xA9   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LatinCapitalLetterEWithMacron,       /* 0xAA   0x0112   LATIN CAPITAL LETTER E WITH MACRON */
   U_LatinCapitalLetterGWithCedilla,      /* 0xAB   0x0122   LATIN CAPITAL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterTWithStroke,       /* 0xAC   0x0166   LATIN CAPITAL LETTER T WITH STROKE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinCapitalLetterZWithCaron,        /* 0xAE   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_LatinSmallLetterAWithOgonek,         /* 0xB1   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_Ogonek,                              /* 0xB2   0x02DB   OGONEK */
   U_LatinSmallLetterRWithCedilla,        /* 0xB3   0x0157   LATIN SMALL LETTER R WITH CEDILLA */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_LatinSmallLetterIWithTilde,          /* 0xB5   0x0129   LATIN SMALL LETTER I WITH TILDE */
   U_LatinSmallLetterLWithCedilla,        /* 0xB6   0x013C   LATIN SMALL LETTER L WITH CEDILLA */
   U_Caron,                               /* 0xB7   0x02C7   CARON */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_LatinSmallLetterSWithCaron,          /* 0xB9   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinSmallLetterEWithMacron,         /* 0xBA   0x0113   LATIN SMALL LETTER E WITH MACRON */
   U_LatinSmallLetterGWithCedilla,        /* 0xBB   0x0123   LATIN SMALL LETTER G WITH CEDILLA */
   U_LatinSmallLetterTWithStroke,         /* 0xBC   0x0167   LATIN SMALL LETTER T WITH STROKE */
   U_LatinCapitalLetterEng,               /* 0xBD   0x014A   LATIN CAPITAL LETTER ENG */
   U_LatinSmallLetterZWithCaron,          /* 0xBE   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_LatinSmallLetterEng,                 /* 0xBF   0x014B   LATIN SMALL LETTER ENG */
   U_LatinCapitalLetterAWithMacron,       /* 0xC0   0x0100   LATIN CAPITAL LETTER A WITH MACRON */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithTilde,        /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLigatureAE,              /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterIWithOgonek,       /* 0xC7   0x012E   LATIN CAPITAL LETTER I WITH OGONEK */
   U_LatinCapitalLetterCWithCaron,        /* 0xC8   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithOgonek,       /* 0xCA   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterEWithDotAbove,     /* 0xCC   0x0116   LATIN CAPITAL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithMacron,       /* 0xCF   0x012A   LATIN CAPITAL LETTER I WITH MACRON */
   U_LatinCapitalLetterDWithStroke,       /* 0xD0   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterNWithCedilla,      /* 0xD1   0x0145   LATIN CAPITAL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterOWithMacron,       /* 0xD2   0x014C   LATIN CAPITAL LETTER O WITH MACRON */
   U_LatinCapitalLetterKWithCedilla,      /* 0xD3   0x0136   LATIN CAPITAL LETTER K WITH CEDILLA */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithTilde,        /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterOSlash,            /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterUWithOgonek,       /* 0xD9   0x0172   LATIN CAPITAL LETTER U WITH OGONEK */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterUWithTilde,        /* 0xDD   0x0168   LATIN CAPITAL LETTER U WITH TILDE */
   U_LatinCapitalLetterUWithMacron,       /* 0xDE   0x016A   LATIN CAPITAL LETTER U WITH MACRON */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterAWithMacron,         /* 0xE0   0x0101   LATIN SMALL LETTER A WITH MACRON */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithTilde,          /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithRingAbove,      /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLigatureAE,                /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinSmallLetterIWithOgonek,         /* 0xE7   0x012F   LATIN SMALL LETTER I WITH OGONEK */
   U_LatinSmallLetterCWithCaron,          /* 0xE8   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithOgonek,         /* 0xEA   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterEWithDotAbove,       /* 0xEC   0x0117   LATIN SMALL LETTER E WITH DOT ABOVE */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithMacron,         /* 0xEF   0x012B   LATIN SMALL LETTER I WITH MACRON */
   U_LatinSmallLetterDWithStroke,         /* 0xF0   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinSmallLetterNWithCedilla,        /* 0xF1   0x0146   LATIN SMALL LETTER N WITH CEDILLA */
   U_LatinSmallLetterOWithMacron,         /* 0xF2   0x014D   LATIN SMALL LETTER O WITH MACRON */
   U_LatinSmallLetterKWithCedilla,        /* 0xF3   0x0137   LATIN SMALL LETTER K WITH CEDILLA */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithTilde,          /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinSmallLetterOSlash,              /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinSmallLetterUWithOgonek,         /* 0xF9   0x0173   LATIN SMALL LETTER U WITH OGONEK */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterUWithTilde,          /* 0xFD   0x0169   LATIN SMALL LETTER U WITH TILDE */
   U_LatinSmallLetterUWithMacron,         /* 0xFE   0x016B   LATIN SMALL LETTER U WITH MACRON */
   U_DotAbove                             /* 0xFF   0x02D9   DOT ABOVE */
};





/******************************************************************************
*
*  CODE_LATIN4_lig[]:
*     list of ligatures:
*
*  CODE_LATIN4_lig[0] is the original ligature character
*  CODE_LATIN4_lig[1] + CODE_LATIN4_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_LATIN4_lig[][3] =     /* CODE_LATIN4 character ligatures */
{
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterAWithRingAbove,    U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */

   {0x0000,                               U_NIL,                 U_NIL}                    /* list terminator */
};





/******************************************************************************
*
*  CODE_LATIN4 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_LATIN4[] =       /* CODE_LATIN4 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterA,                 /* 0xA1   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinSmallLetterKra,                 /* 0xA2   0x0138   LATIN SMALL LETTER KRA */
   U_LatinCapitalLetterR,                 /* 0xA3   0x0156   LATIN CAPITAL LETTER R WITH CEDILLA */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_LatinCapitalLetterI,                 /* 0xA5   0x0128   LATIN CAPITAL LETTER I WITH TILDE */
   U_LatinCapitalLetterL,                 /* 0xA6   0x013B   LATIN CAPITAL LETTER L WITH CEDILLA */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_LatinCapitalLetterS,                 /* 0xA9   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xAA   0x0112   LATIN CAPITAL LETTER E WITH MACRON */
   U_LatinCapitalLetterG,                 /* 0xAB   0x0122   LATIN CAPITAL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterT,                 /* 0xAC   0x0166   LATIN CAPITAL LETTER T WITH STROKE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinCapitalLetterZ,                 /* 0xAE   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_LatinCapitalLetterA,                 /* 0xB1   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_Ogonek,                              /* 0xB2   0x02DB   OGONEK */
   U_LatinCapitalLetterR,                 /* 0xB3   0x0157   LATIN SMALL LETTER R WITH CEDILLA */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_LatinCapitalLetterI,                 /* 0xB5   0x0129   LATIN SMALL LETTER I WITH TILDE */
   U_LatinCapitalLetterL,                 /* 0xB6   0x013C   LATIN SMALL LETTER L WITH CEDILLA */
   U_Caron,                               /* 0xB7   0x02C7   CARON */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_LatinCapitalLetterS,                 /* 0xB9   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xBA   0x0113   LATIN SMALL LETTER E WITH MACRON */
   U_LatinCapitalLetterG,                 /* 0xBB   0x0123   LATIN SMALL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterT,                 /* 0xBC   0x0167   LATIN SMALL LETTER T WITH STROKE */
   U_LatinCapitalLetterEng,               /* 0xBD   0x014A   LATIN CAPITAL LETTER ENG */
   U_LatinCapitalLetterZ,                 /* 0xBE   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_LatinCapitalLetterEng,               /* 0xBF   0x014B   LATIN SMALL LETTER ENG */
   U_LatinCapitalLetterA,                 /* 0xC0   0x0100   LATIN CAPITAL LETTER A WITH MACRON */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterI,                 /* 0xC7   0x012E   LATIN CAPITAL LETTER I WITH OGONEK */
   U_LatinCapitalLetterC,                 /* 0xC8   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xCC   0x0116   LATIN CAPITAL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterE,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xCF   0x012A   LATIN CAPITAL LETTER I WITH MACRON */
   U_LatinCapitalLetterD,                 /* 0xD0   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xD1   0x0145   LATIN CAPITAL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterO,                 /* 0xD2   0x014C   LATIN CAPITAL LETTER O WITH MACRON */
   U_LatinCapitalLetterK,                 /* 0xD3   0x0136   LATIN CAPITAL LETTER K WITH CEDILLA */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterO,                 /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xD9   0x0172   LATIN CAPITAL LETTER U WITH OGONEK */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xDD   0x0168   LATIN CAPITAL LETTER U WITH TILDE */
   U_LatinCapitalLetterU,                 /* 0xDE   0x016A   LATIN CAPITAL LETTER U WITH MACRON */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterA,                 /* 0xE0   0x0101   LATIN SMALL LETTER A WITH MACRON */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterE,                 /* 0xE7   0x012F   LATIN SMALL LETTER I WITH OGONEK */
   U_LatinCapitalLetterC,                 /* 0xE8   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xEC   0x0117   LATIN SMALL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterE,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xEF   0x012B   LATIN SMALL LETTER I WITH MACRON */
   U_LatinCapitalLetterD,                 /* 0xF0   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xF1   0x0146   LATIN SMALL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterO,                 /* 0xF2   0x014D   LATIN SMALL LETTER O WITH MACRON */
   U_LatinCapitalLetterK,                 /* 0xF3   0x0137   LATIN SMALL LETTER K WITH CEDILLA */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinCapitalLetterO,                 /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xF9   0x0173   LATIN SMALL LETTER U WITH OGONEK */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xFD   0x0169   LATIN SMALL LETTER U WITH TILDE */
   U_LatinCapitalLetterU,                 /* 0xFE   0x016B   LATIN SMALL LETTER U WITH MACRON */
   U_DotAbove                             /* 0xFF   0x02D9   DOT ABOVE */
};










/******************************************************************************
*
*  u_CODE_CYRILLIC[]:
*     Unicode named codepage for ISO encoding Cyrillic (iso-8859-5)
*
*  Name:             ISO 8859-5:1999 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_CYRILLIC[] =        /* CODE_CYRILLIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_CyrillicCapitalLetterIo,             /* 0xA1   0x0401   CYRILLIC CAPITAL LETTER IO */
   U_CyrillicCapitalLetterDje,            /* 0xA2   0x0402   CYRILLIC CAPITAL LETTER DJE */
   U_CyrillicCapitalLetterGje,            /* 0xA3   0x0403   CYRILLIC CAPITAL LETTER GJE */
   U_CyrillicCapitalLetterUkrainianIe,    /* 0xA4   0x0404   CYRILLIC CAPITAL LETTER UKRAINIAN IE */
   U_CyrillicCapitalLetterDze,            /* 0xA5   0x0405   CYRILLIC CAPITAL LETTER DZE */
                                          /* 0xA6   0x0406   CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I */
   U_CyrillicCapitalLetterByelorussianUkrainianI,
   U_CyrillicCapitalLetterYi,             /* 0xA7   0x0407   CYRILLIC CAPITAL LETTER YI */
   U_CyrillicCapitalLetterJe,             /* 0xA8   0x0408   CYRILLIC CAPITAL LETTER JE */
   U_CyrillicCapitalLetterLje,            /* 0xA9   0x0409   CYRILLIC CAPITAL LETTER LJE */
   U_CyrillicCapitalLetterNje,            /* 0xAA   0x040A   CYRILLIC CAPITAL LETTER NJE */
   U_CyrillicCapitalLetterTshe,           /* 0xAB   0x040B   CYRILLIC CAPITAL LETTER TSHE */
   U_CyrillicCapitalLetterKje,            /* 0xAC   0x040C   CYRILLIC CAPITAL LETTER KJE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_CyrillicCapitalLetterShortU,         /* 0xAE   0x040E   CYRILLIC CAPITAL LETTER SHORT U */
   U_CyrillicCapitalLetterDzhe,           /* 0xAF   0x040F   CYRILLIC CAPITAL LETTER DZHE */
   U_CyrillicCapitalLetterA,              /* 0xB0   0x0410   CYRILLIC CAPITAL LETTER A */
   U_CyrillicCapitalLetterBe,             /* 0xB1   0x0411   CYRILLIC CAPITAL LETTER BE */
   U_CyrillicCapitalLetterVe,             /* 0xB2   0x0412   CYRILLIC CAPITAL LETTER VE */
   U_CyrillicCapitalLetterGhe,            /* 0xB3   0x0413   CYRILLIC CAPITAL LETTER GHE */
   U_CyrillicCapitalLetterDe,             /* 0xB4   0x0414   CYRILLIC CAPITAL LETTER DE */
   U_CyrillicCapitalLetterIe,             /* 0xB5   0x0415   CYRILLIC CAPITAL LETTER IE */
   U_CyrillicCapitalLetterZhe,            /* 0xB6   0x0416   CYRILLIC CAPITAL LETTER ZHE */
   U_CyrillicCapitalLetterZe,             /* 0xB7   0x0417   CYRILLIC CAPITAL LETTER ZE */
   U_CyrillicCapitalLetterI,              /* 0xB8   0x0418   CYRILLIC CAPITAL LETTER I */
   U_CyrillicCapitalLetterShortI,         /* 0xB9   0x0419   CYRILLIC CAPITAL LETTER SHORT I */
   U_CyrillicCapitalLetterKa,             /* 0xBA   0x041A   CYRILLIC CAPITAL LETTER KA */
   U_CyrillicCapitalLetterEl,             /* 0xBB   0x041B   CYRILLIC CAPITAL LETTER EL */
   U_CyrillicCapitalLetterEm,             /* 0xBC   0x041C   CYRILLIC CAPITAL LETTER EM */
   U_CyrillicCapitalLetterEn,             /* 0xBD   0x041D   CYRILLIC CAPITAL LETTER EN */
   U_CyrillicCapitalLetterO,              /* 0xBE   0x041E   CYRILLIC CAPITAL LETTER O */
   U_CyrillicCapitalLetterPe,             /* 0xBF   0x041F   CYRILLIC CAPITAL LETTER PE */
   U_CyrillicCapitalLetterEr,             /* 0xC0   0x0420   CYRILLIC CAPITAL LETTER ER */
   U_CyrillicCapitalLetterEs,             /* 0xC1   0x0421   CYRILLIC CAPITAL LETTER ES */
   U_CyrillicCapitalLetterTe,             /* 0xC2   0x0422   CYRILLIC CAPITAL LETTER TE */
   U_CyrillicCapitalLetterU,              /* 0xC3   0x0423   CYRILLIC CAPITAL LETTER U */
   U_CyrillicCapitalLetterEf,             /* 0xC4   0x0424   CYRILLIC CAPITAL LETTER EF */
   U_CyrillicCapitalLetterHa,             /* 0xC5   0x0425   CYRILLIC CAPITAL LETTER HA */
   U_CyrillicCapitalLetterTse,            /* 0xC6   0x0426   CYRILLIC CAPITAL LETTER TSE */
   U_CyrillicCapitalLetterChe,            /* 0xC7   0x0427   CYRILLIC CAPITAL LETTER CHE */
   U_CyrillicCapitalLetterSha,            /* 0xC8   0x0428   CYRILLIC CAPITAL LETTER SHA */
   U_CyrillicCapitalLetterShcha,          /* 0xC9   0x0429   CYRILLIC CAPITAL LETTER SHCHA */
   U_CyrillicCapitalLetterHardSign,       /* 0xCA   0x042A   CYRILLIC CAPITAL LETTER HARD SIGN */
   U_CyrillicCapitalLetterYeru,           /* 0xCB   0x042B   CYRILLIC CAPITAL LETTER YERU */
   U_CyrillicCapitalLetterSoftSign,       /* 0xCC   0x042C   CYRILLIC CAPITAL LETTER SOFT SIGN */
   U_CyrillicCapitalLetterE,              /* 0xCD   0x042D   CYRILLIC CAPITAL LETTER E */
   U_CyrillicCapitalLetterYu,             /* 0xCE   0x042E   CYRILLIC CAPITAL LETTER YU */
   U_CyrillicCapitalLetterYa,             /* 0xCF   0x042F   CYRILLIC CAPITAL LETTER YA */
   U_CyrillicSmallLetterA,                /* 0xD0   0x0430   CYRILLIC SMALL LETTER A */
   U_CyrillicSmallLetterBe,               /* 0xD1   0x0431   CYRILLIC SMALL LETTER BE */
   U_CyrillicSmallLetterVe,               /* 0xD2   0x0432   CYRILLIC SMALL LETTER VE */
   U_CyrillicSmallLetterGhe,              /* 0xD3   0x0433   CYRILLIC SMALL LETTER GHE */
   U_CyrillicSmallLetterDe,               /* 0xD4   0x0434   CYRILLIC SMALL LETTER DE */
   U_CyrillicSmallLetterIe,               /* 0xD5   0x0435   CYRILLIC SMALL LETTER IE */
   U_CyrillicSmallLetterZhe,              /* 0xD6   0x0436   CYRILLIC SMALL LETTER ZHE */
   U_CyrillicSmallLetterZe,               /* 0xD7   0x0437   CYRILLIC SMALL LETTER ZE */
   U_CyrillicSmallLetterI,                /* 0xD8   0x0438   CYRILLIC SMALL LETTER I */
   U_CyrillicSmallLetterShortI,           /* 0xD9   0x0439   CYRILLIC SMALL LETTER SHORT I */
   U_CyrillicSmallLetterKa,               /* 0xDA   0x043A   CYRILLIC SMALL LETTER KA */
   U_CyrillicSmallLetterEl,               /* 0xDB   0x043B   CYRILLIC SMALL LETTER EL */
   U_CyrillicSmallLetterEm,               /* 0xDC   0x043C   CYRILLIC SMALL LETTER EM */
   U_CyrillicSmallLetterEn,               /* 0xDD   0x043D   CYRILLIC SMALL LETTER EN */
   U_CyrillicSmallLetterO,                /* 0xDE   0x043E   CYRILLIC SMALL LETTER O */
   U_CyrillicSmallLetterPe,               /* 0xDF   0x043F   CYRILLIC SMALL LETTER PE */
   U_CyrillicSmallLetterEr,               /* 0xE0   0x0440   CYRILLIC SMALL LETTER ER */
   U_CyrillicSmallLetterEs,               /* 0xE1   0x0441   CYRILLIC SMALL LETTER ES */
   U_CyrillicSmallLetterTe,               /* 0xE2   0x0442   CYRILLIC SMALL LETTER TE */
   U_CyrillicSmallLetterU,                /* 0xE3   0x0443   CYRILLIC SMALL LETTER U */
   U_CyrillicSmallLetterEf,               /* 0xE4   0x0444   CYRILLIC SMALL LETTER EF */
   U_CyrillicSmallLetterHa,               /* 0xE5   0x0445   CYRILLIC SMALL LETTER HA */
   U_CyrillicSmallLetterTse,              /* 0xE6   0x0446   CYRILLIC SMALL LETTER TSE */
   U_CyrillicSmallLetterChe,              /* 0xE7   0x0447   CYRILLIC SMALL LETTER CHE */
   U_CyrillicSmallLetterSha,              /* 0xE8   0x0448   CYRILLIC SMALL LETTER SHA */
   U_CyrillicSmallLetterShcha,            /* 0xE9   0x0449   CYRILLIC SMALL LETTER SHCHA */
   U_CyrillicSmallLetterHardSign,         /* 0xEA   0x044A   CYRILLIC SMALL LETTER HARD SIGN */
   U_CyrillicSmallLetterYeru,             /* 0xEB   0x044B   CYRILLIC SMALL LETTER YERU */
   U_CyrillicSmallLetterSoftSign,         /* 0xEC   0x044C   CYRILLIC SMALL LETTER SOFT SIGN */
   U_CyrillicSmallLetterE,                /* 0xED   0x044D   CYRILLIC SMALL LETTER E */
   U_CyrillicSmallLetterYu,               /* 0xEE   0x044E   CYRILLIC SMALL LETTER YU */
   U_CyrillicSmallLetterYa,               /* 0xEF   0x044F   CYRILLIC SMALL LETTER YA */
   U_NumeroSign,                          /* 0xF0   0x2116   NUMERO SIGN */
   U_CyrillicSmallLetterIo,               /* 0xF1   0x0451   CYRILLIC SMALL LETTER IO */
   U_CyrillicSmallLetterDje,              /* 0xF2   0x0452   CYRILLIC SMALL LETTER DJE */
   U_CyrillicSmallLetterGje,              /* 0xF3   0x0453   CYRILLIC SMALL LETTER GJE */
   U_CyrillicSmallLetterUkrainianIe,      /* 0xF4   0x0454   CYRILLIC SMALL LETTER UKRAINIAN IE */
   U_CyrillicSmallLetterDze,              /* 0xF5   0x0455   CYRILLIC SMALL LETTER DZE */
                                          /* 0xF6   0x0456   CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I */
   U_CyrillicSmallLetterByelorussianUkrainianI,
   U_CyrillicSmallLetterYi,               /* 0xF7   0x0457   CYRILLIC SMALL LETTER YI */
   U_CyrillicSmallLetterJe,               /* 0xF8   0x0458   CYRILLIC SMALL LETTER JE */
   U_CyrillicSmallLetterLje,              /* 0xF9   0x0459   CYRILLIC SMALL LETTER LJE */
   U_CyrillicSmallLetterNje,              /* 0xFA   0x045A   CYRILLIC SMALL LETTER NJE */
   U_CyrillicSmallLetterTshe,             /* 0xFB   0x045B   CYRILLIC SMALL LETTER TSHE */
   U_CyrillicSmallLetterKje,              /* 0xFC   0x045C   CYRILLIC SMALL LETTER KJE */
   U_SectionSign,                         /* 0xFD   0x00A7   SECTION SIGN */
   U_CyrillicSmallLetterShortU,           /* 0xFE   0x045E   CYRILLIC SMALL LETTER SHORT U */
   U_CyrillicSmallLetterDzhe              /* 0xFF   0x045F   CYRILLIC SMALL LETTER DZHE */
};





/******************************************************************************
*
*  CODE_CYRILLIC_lig[]:
*     list of ligatures:
*
*  CODE_CYRILLIC_lig[0] is the original ligature character
*  CODE_CYRILLIC_lig[1] + CODE_CYRILLIC_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CYRILLIC_lig[][3] =   /* CODE_CYRILLIC character ligatures */
{
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CYRILLIC sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_CYRILLIC[] =     /* CODE_CYRILLIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_CyrillicCapitalLetterIo,             /* 0xA1   0x0401   CYRILLIC CAPITAL LETTER IO */
   U_CyrillicCapitalLetterDje,            /* 0xA2   0x0402   CYRILLIC CAPITAL LETTER DJE */
   U_CyrillicCapitalLetterGje,            /* 0xA3   0x0403   CYRILLIC CAPITAL LETTER GJE */
   U_CyrillicCapitalLetterIe,             /* 0xA4   0x0404   CYRILLIC CAPITAL LETTER UKRAINIAN IE */
   U_CyrillicCapitalLetterDze,            /* 0xA5   0x0405   CYRILLIC CAPITAL LETTER DZE */
   U_CyrillicCapitalLetterI,              /* 0xA6   0x0406   CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I */
   U_CyrillicCapitalLetterYi,             /* 0xA7   0x0407   CYRILLIC CAPITAL LETTER YI */
   U_CyrillicCapitalLetterJe,             /* 0xA8   0x0408   CYRILLIC CAPITAL LETTER JE */
   U_CyrillicCapitalLetterLje,            /* 0xA9   0x0409   CYRILLIC CAPITAL LETTER LJE */
   U_CyrillicCapitalLetterNje,            /* 0xAA   0x040A   CYRILLIC CAPITAL LETTER NJE */
   U_CyrillicCapitalLetterTshe,           /* 0xAB   0x040B   CYRILLIC CAPITAL LETTER TSHE */
   U_CyrillicCapitalLetterKje,            /* 0xAC   0x040C   CYRILLIC CAPITAL LETTER KJE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_CyrillicCapitalLetterU,              /* 0xAE   0x040E   CYRILLIC CAPITAL LETTER SHORT U */
   U_CyrillicCapitalLetterDzhe,           /* 0xAF   0x040F   CYRILLIC CAPITAL LETTER DZHE */
   U_CyrillicCapitalLetterA,              /* 0xB0   0x0410   CYRILLIC CAPITAL LETTER A */
   U_CyrillicCapitalLetterBe,             /* 0xB1   0x0411   CYRILLIC CAPITAL LETTER BE */
   U_CyrillicCapitalLetterVe,             /* 0xB2   0x0412   CYRILLIC CAPITAL LETTER VE */
   U_CyrillicCapitalLetterGhe,            /* 0xB3   0x0413   CYRILLIC CAPITAL LETTER GHE */
   U_CyrillicCapitalLetterDe,             /* 0xB4   0x0414   CYRILLIC CAPITAL LETTER DE */
   U_CyrillicCapitalLetterIe,             /* 0xB5   0x0415   CYRILLIC CAPITAL LETTER IE */
   U_CyrillicCapitalLetterZhe,            /* 0xB6   0x0416   CYRILLIC CAPITAL LETTER ZHE */
   U_CyrillicCapitalLetterZe,             /* 0xB7   0x0417   CYRILLIC CAPITAL LETTER ZE */
   U_CyrillicCapitalLetterI,              /* 0xB8   0x0418   CYRILLIC CAPITAL LETTER I */
   U_CyrillicCapitalLetterI,              /* 0xB9   0x0419   CYRILLIC CAPITAL LETTER SHORT I */
   U_CyrillicCapitalLetterKa,             /* 0xBA   0x041A   CYRILLIC CAPITAL LETTER KA */
   U_CyrillicCapitalLetterEl,             /* 0xBB   0x041B   CYRILLIC CAPITAL LETTER EL */
   U_CyrillicCapitalLetterEm,             /* 0xBC   0x041C   CYRILLIC CAPITAL LETTER EM */
   U_CyrillicCapitalLetterEn,             /* 0xBD   0x041D   CYRILLIC CAPITAL LETTER EN */
   U_CyrillicCapitalLetterO,              /* 0xBE   0x041E   CYRILLIC CAPITAL LETTER O */
   U_CyrillicCapitalLetterPe,             /* 0xBF   0x041F   CYRILLIC CAPITAL LETTER PE */
   U_CyrillicCapitalLetterEr,             /* 0xC0   0x0420   CYRILLIC CAPITAL LETTER ER */
   U_CyrillicCapitalLetterEs,             /* 0xC1   0x0421   CYRILLIC CAPITAL LETTER ES */
   U_CyrillicCapitalLetterTe,             /* 0xC2   0x0422   CYRILLIC CAPITAL LETTER TE */
   U_CyrillicCapitalLetterU,              /* 0xC3   0x0423   CYRILLIC CAPITAL LETTER U */
   U_CyrillicCapitalLetterEf,             /* 0xC4   0x0424   CYRILLIC CAPITAL LETTER EF */
   U_CyrillicCapitalLetterHa,             /* 0xC5   0x0425   CYRILLIC CAPITAL LETTER HA */
   U_CyrillicCapitalLetterTse,            /* 0xC6   0x0426   CYRILLIC CAPITAL LETTER TSE */
   U_CyrillicCapitalLetterChe,            /* 0xC7   0x0427   CYRILLIC CAPITAL LETTER CHE */
   U_CyrillicCapitalLetterSha,            /* 0xC8   0x0428   CYRILLIC CAPITAL LETTER SHA */
   U_CyrillicCapitalLetterShcha,          /* 0xC9   0x0429   CYRILLIC CAPITAL LETTER SHCHA */
   U_CyrillicCapitalLetterHardSign,       /* 0xCA   0x042A   CYRILLIC CAPITAL LETTER HARD SIGN */
   U_CyrillicCapitalLetterYeru,           /* 0xCB   0x042B   CYRILLIC CAPITAL LETTER YERU */
   U_CyrillicCapitalLetterSoftSign,       /* 0xCC   0x042C   CYRILLIC CAPITAL LETTER SOFT SIGN */
   U_CyrillicCapitalLetterE,              /* 0xCD   0x042D   CYRILLIC CAPITAL LETTER E */
   U_CyrillicCapitalLetterYu,             /* 0xCE   0x042E   CYRILLIC CAPITAL LETTER YU */
   U_CyrillicCapitalLetterYa,             /* 0xCF   0x042F   CYRILLIC CAPITAL LETTER YA */
   U_CyrillicCapitalLetterA,              /* 0xD0   0x0430   CYRILLIC SMALL LETTER A */
   U_CyrillicCapitalLetterBe,             /* 0xD1   0x0431   CYRILLIC SMALL LETTER BE */
   U_CyrillicCapitalLetterVe,             /* 0xD2   0x0432   CYRILLIC SMALL LETTER VE */
   U_CyrillicCapitalLetterGhe,            /* 0xD3   0x0433   CYRILLIC SMALL LETTER GHE */
   U_CyrillicCapitalLetterDe,             /* 0xD4   0x0434   CYRILLIC SMALL LETTER DE */
   U_CyrillicCapitalLetterIe,             /* 0xD5   0x0435   CYRILLIC SMALL LETTER IE */
   U_CyrillicCapitalLetterZhe,            /* 0xD6   0x0436   CYRILLIC SMALL LETTER ZHE */
   U_CyrillicCapitalLetterZe,             /* 0xD7   0x0437   CYRILLIC SMALL LETTER ZE */
   U_CyrillicCapitalLetterI,              /* 0xD8   0x0438   CYRILLIC SMALL LETTER I */
   U_CyrillicCapitalLetterI,              /* 0xD9   0x0439   CYRILLIC SMALL LETTER SHORT I */
   U_CyrillicCapitalLetterKa,             /* 0xDA   0x043A   CYRILLIC SMALL LETTER KA */
   U_CyrillicCapitalLetterEl,             /* 0xDB   0x043B   CYRILLIC SMALL LETTER EL */
   U_CyrillicCapitalLetterEm,             /* 0xDC   0x043C   CYRILLIC SMALL LETTER EM */
   U_CyrillicCapitalLetterEn,             /* 0xDD   0x043D   CYRILLIC SMALL LETTER EN */
   U_CyrillicCapitalLetterO,              /* 0xDE   0x043E   CYRILLIC SMALL LETTER O */
   U_CyrillicCapitalLetterPe,             /* 0xDF   0x043F   CYRILLIC SMALL LETTER PE */
   U_CyrillicCapitalLetterEr,             /* 0xE0   0x0440   CYRILLIC SMALL LETTER ER */
   U_CyrillicCapitalLetterEs,             /* 0xE1   0x0441   CYRILLIC SMALL LETTER ES */
   U_CyrillicCapitalLetterTe,             /* 0xE2   0x0442   CYRILLIC SMALL LETTER TE */
   U_CyrillicCapitalLetterU,              /* 0xE3   0x0443   CYRILLIC SMALL LETTER U */
   U_CyrillicCapitalLetterEf,             /* 0xE4   0x0444   CYRILLIC SMALL LETTER EF */
   U_CyrillicCapitalLetterHa,             /* 0xE5   0x0445   CYRILLIC SMALL LETTER HA */
   U_CyrillicCapitalLetterTse,            /* 0xE6   0x0446   CYRILLIC SMALL LETTER TSE */
   U_CyrillicCapitalLetterChe,            /* 0xE7   0x0447   CYRILLIC SMALL LETTER CHE */
   U_CyrillicCapitalLetterSha,            /* 0xE8   0x0448   CYRILLIC SMALL LETTER SHA */
   U_CyrillicCapitalLetterShcha,          /* 0xE9   0x0449   CYRILLIC SMALL LETTER SHCHA */
   U_CyrillicCapitalLetterHardSign,       /* 0xEA   0x044A   CYRILLIC SMALL LETTER HARD SIGN */
   U_CyrillicCapitalLetterYeru,           /* 0xEB   0x044B   CYRILLIC SMALL LETTER YERU */
   U_CyrillicCapitalLetterSoftSign,       /* 0xEC   0x044C   CYRILLIC SMALL LETTER SOFT SIGN */
   U_CyrillicCapitalLetterE,              /* 0xED   0x044D   CYRILLIC SMALL LETTER E */
   U_CyrillicCapitalLetterYu,             /* 0xEE   0x044E   CYRILLIC SMALL LETTER YU */
   U_CyrillicCapitalLetterYa,             /* 0xEF   0x044F   CYRILLIC SMALL LETTER YA */
   U_NumeroSign,                          /* 0xF0   0x2116   NUMERO SIGN */
   U_CyrillicCapitalLetterIo,             /* 0xF1   0x0451   CYRILLIC SMALL LETTER IO */
   U_CyrillicCapitalLetterDje,            /* 0xF2   0x0452   CYRILLIC SMALL LETTER DJE */
   U_CyrillicCapitalLetterGje,            /* 0xF3   0x0453   CYRILLIC SMALL LETTER GJE */
   U_CyrillicCapitalLetterIe,             /* 0xF4   0x0454   CYRILLIC SMALL LETTER UKRAINIAN IE */
   U_CyrillicCapitalLetterDze,            /* 0xF5   0x0455   CYRILLIC SMALL LETTER DZE */
   U_CyrillicCapitalLetterI,              /* 0xF6   0x0456   CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I */
   U_CyrillicCapitalLetterYi,             /* 0xF7   0x0457   CYRILLIC SMALL LETTER YI */
   U_CyrillicCapitalLetterJe,             /* 0xF8   0x0458   CYRILLIC SMALL LETTER JE */
   U_CyrillicCapitalLetterLje,            /* 0xF9   0x0459   CYRILLIC SMALL LETTER LJE */
   U_CyrillicCapitalLetterNje,            /* 0xFA   0x045A   CYRILLIC SMALL LETTER NJE */
   U_CyrillicCapitalLetterTshe,           /* 0xFB   0x045B   CYRILLIC SMALL LETTER TSHE */
   U_CyrillicCapitalLetterKje,            /* 0xFC   0x045C   CYRILLIC SMALL LETTER KJE */
   U_SectionSign,                         /* 0xFD   0x00A7   SECTION SIGN */
   U_CyrillicCapitalLetterU,              /* 0xFE   0x045E   CYRILLIC SMALL LETTER SHORT U */
   U_CyrillicCapitalLetterDzhe            /* 0xFF   0x045F   CYRILLIC SMALL LETTER DZHE */
};










/******************************************************************************
*
*  u_CODE_ARABIC[]:
*     Unicode named codepage for ISO encoding Arabic (iso-8859-6)
*
*  Name:             ISO 8859-6:1999 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_ARABIC[] =          /* CODE_ARABIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_NIL,                                 /* 0xA1            <undefined> */
   U_NIL,                                 /* 0xA2            <undefined> */
   U_NIL,                                 /* 0xA3            <undefined> */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_NIL,                                 /* 0xA4            <undefined> */
   U_NIL,                                 /* 0xA5            <undefined> */
   U_NIL,                                 /* 0xA6            <undefined> */
   U_NIL,                                 /* 0xA7            <undefined> */
   U_NIL,                                 /* 0xA8            <undefined> */
   U_NIL,                                 /* 0xA9            <undefined> */
   U_NIL,                                 /* 0xAA            <undefined> */
   U_NIL,                                 /* 0xAB            <undefined> */
   U_ArabicComma,                         /* 0xAC   0x060C   ARABIC COMMA */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_NIL,                                 /* 0xAE            <undefined> */
   U_NIL,                                 /* 0xAF            <undefined> */
   U_NIL,                                 /* 0xB0            <undefined> */
   U_NIL,                                 /* 0xB1            <undefined> */
   U_NIL,                                 /* 0xB2            <undefined> */
   U_NIL,                                 /* 0xB3            <undefined> */
   U_NIL,                                 /* 0xB4            <undefined> */
   U_NIL,                                 /* 0xB5            <undefined> */
   U_NIL,                                 /* 0xB6            <undefined> */
   U_NIL,                                 /* 0xB7            <undefined> */
   U_NIL,                                 /* 0xB8            <undefined> */
   U_NIL,                                 /* 0xB9            <undefined> */
   U_NIL,                                 /* 0xBA            <undefined> */
   U_ArabicSemicolon,                     /* 0xBB   0x061B   ARABIC SEMICOLON */
   U_NIL,                                 /* 0xBC            <undefined> */
   U_NIL,                                 /* 0xBD            <undefined> */
   U_NIL,                                 /* 0xBE            <undefined> */
   U_ArabicQuestionMark,                  /* 0xBF   0x061F   ARABIC QUESTION MARK */
   U_NIL,                                 /* 0xC0            <undefined> */
   U_ArabicLetterHamza,                   /* 0xC1   0x0621   ARABIC LETTER HAMZA */
   U_ArabicLetterAlefWithMaddaAbove,      /* 0xC2   0x0622   ARABIC LETTER ALEF WITH MADDA ABOVE */
   U_ArabicLetterAlefWithHamzaAbove,      /* 0xC3   0x0623   ARABIC LETTER ALEF WITH HAMZA ABOVE */
   U_ArabicLetterWawWithHamzaAbove,       /* 0xC4   0x0624   ARABIC LETTER WAW WITH HAMZA ABOVE */
   U_ArabicLetterAlefWithHamzaBelow,      /* 0xC5   0x0625   ARABIC LETTER ALEF WITH HAMZA BELOW */
   U_ArabicLetterYehWithHamzaAbove,       /* 0xC6   0x0626   ARABIC LETTER YEH WITH HAMZA ABOVE */
   U_ArabicLetterAlef,                    /* 0xC7   0x0627   ARABIC LETTER ALEF */
   U_ArabicLetterBeh,                     /* 0xC8   0x0628   ARABIC LETTER BEH */
   U_ArabicLetterTehMarbuta,              /* 0xC9   0x0629   ARABIC LETTER TEH MARBUTA */
   U_ArabicLetterTeh,                     /* 0xCA   0x062A   ARABIC LETTER TEH */
   U_ArabicLetterTheh,                    /* 0xCB   0x062B   ARABIC LETTER THEH */
   U_ArabicLetterJeem,                    /* 0xCC   0x062C   ARABIC LETTER JEEM */
   U_ArabicLetterHah,                     /* 0xCD   0x062D   ARABIC LETTER HAH */
   U_ArabicLetterKhah,                    /* 0xCE   0x062E   ARABIC LETTER KHAH */
   U_ArabicLetterDal,                     /* 0xCF   0x062F   ARABIC LETTER DAL */
   U_ArabicLetterThal,                    /* 0xD0   0x0630   ARABIC LETTER THAL */
   U_ArabicLetterReh,                     /* 0xD1   0x0631   ARABIC LETTER REH */
   U_ArabicLetterZain,                    /* 0xD2   0x0632   ARABIC LETTER ZAIN */
   U_ArabicLetterSeen,                    /* 0xD3   0x0633   ARABIC LETTER SEEN */
   U_ArabicLetterSheen,                   /* 0xD4   0x0634   ARABIC LETTER SHEEN */
   U_ArabicLetterSad,                     /* 0xD5   0x0635   ARABIC LETTER SAD */
   U_ArabicLetterDad,                     /* 0xD6   0x0636   ARABIC LETTER DAD */
   U_ArabicLetterTah,                     /* 0xD7   0x0637   ARABIC LETTER TAH */
   U_ArabicLetterZah,                     /* 0xD8   0x0638   ARABIC LETTER ZAH */
   U_ArabicLetterAin,                     /* 0xD9   0x0639   ARABIC LETTER AIN */
   U_ArabicLetterGhain,                   /* 0xDA   0x063A   ARABIC LETTER GHAIN */
   U_NIL,                                 /* 0xDB            <undefined> */
   U_NIL,                                 /* 0xDC            <undefined> */
   U_NIL,                                 /* 0xDD            <undefined> */
   U_NIL,                                 /* 0xDE            <undefined> */
   U_NIL,                                 /* 0xDF            <undefined> */
   U_ArabicTatweel,                       /* 0xE0   0x0640   ARABIC TATWEEL */
   U_ArabicLetterFeh,                     /* 0xE1   0x0641   ARABIC LETTER FEH */
   U_ArabicLetterQaf,                     /* 0xE2   0x0642   ARABIC LETTER QAF */
   U_ArabicLetterKaf,                     /* 0xE3   0x0643   ARABIC LETTER KAF */
   U_ArabicLetterLam,                     /* 0xE4   0x0644   ARABIC LETTER LAM */
   U_ArabicLetterMeem,                    /* 0xE5   0x0645   ARABIC LETTER MEEM */
   U_ArabicLetterNoon,                    /* 0xE6   0x0646   ARABIC LETTER NOON */
   U_ArabicLetterHeh,                     /* 0xE7   0x0647   ARABIC LETTER HEH */
   U_ArabicLetterWaw,                     /* 0xE8   0x0648   ARABIC LETTER WAW */
   U_ArabicLetterAlefMaksura,             /* 0xE9   0x0649   ARABIC LETTER ALEF MAKSURA */
   U_ArabicLetterYeh,                     /* 0xEA   0x064A   ARABIC LETTER YEH */
   U_ArabicFathatan,                      /* 0xEB   0x064B   ARABIC FATHATAN */
   U_ArabicDammatan,                      /* 0xEC   0x064C   ARABIC DAMMATAN */
   U_ArabicKasratan,                      /* 0xED   0x064D   ARABIC KASRATAN */
   U_ArabicFatha,                         /* 0xEE   0x064E   ARABIC FATHA */
   U_ArabicDamma,                         /* 0xEF   0x064F   ARABIC DAMMA */
   U_ArabicKasra,                         /* 0xF0   0x0650   ARABIC KASRA */
   U_ArabicShadda,                        /* 0xF1   0x0651   ARABIC SHADDA */
   U_ArabicSukun,                         /* 0xF2   0x0652   ARABIC SUKUN */
   U_NIL,                                 /* 0xF3            <undefined> */
   U_NIL,                                 /* 0xF4            <undefined> */
   U_NIL,                                 /* 0xF5            <undefined> */
   U_NIL,                                 /* 0xF6            <undefined> */
   U_NIL,                                 /* 0xF7            <undefined> */
   U_NIL,                                 /* 0xF8            <undefined> */
   U_NIL,                                 /* 0xF9            <undefined> */
   U_NIL,                                 /* 0xFA            <undefined> */
   U_NIL,                                 /* 0xFB            <undefined> */
   U_NIL,                                 /* 0xFC            <undefined> */
   U_NIL,                                 /* 0xFD            <undefined> */
   U_NIL,                                 /* 0xFE            <undefined> */
   U_NIL                                  /* 0xFF            <undefined> */
};





/******************************************************************************
*
*  CODE_ARABIC_lig[]:
*     list of ligatures:
*
*  CODE_ARABIC_lig[0] is the original ligature character
*  CODE_ARABIC_lig[1] + CODE_ARABIC_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_ARABIC_lig[][3] =     /* CODE_ARABIC character ligatures */
{
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_ARABIC sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_ARABIC[] =       /* CODE_ARABIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_NIL,                                 /* 0xA1            <undefined> */
   U_NIL,                                 /* 0xA2            <undefined> */
   U_NIL,                                 /* 0xA3            <undefined> */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_NIL,                                 /* 0xA4            <undefined> */
   U_NIL,                                 /* 0xA5            <undefined> */
   U_NIL,                                 /* 0xA6            <undefined> */
   U_NIL,                                 /* 0xA7            <undefined> */
   U_NIL,                                 /* 0xA8            <undefined> */
   U_NIL,                                 /* 0xA9            <undefined> */
   U_NIL,                                 /* 0xAA            <undefined> */
   U_NIL,                                 /* 0xAB            <undefined> */
   U_ArabicComma,                         /* 0xAC   0x060C   ARABIC COMMA */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_NIL,                                 /* 0xAE            <undefined> */
   U_NIL,                                 /* 0xAF            <undefined> */
   U_NIL,                                 /* 0xB0            <undefined> */
   U_NIL,                                 /* 0xB1            <undefined> */
   U_NIL,                                 /* 0xB2            <undefined> */
   U_NIL,                                 /* 0xB3            <undefined> */
   U_NIL,                                 /* 0xB4            <undefined> */
   U_NIL,                                 /* 0xB5            <undefined> */
   U_NIL,                                 /* 0xB6            <undefined> */
   U_NIL,                                 /* 0xB7            <undefined> */
   U_NIL,                                 /* 0xB8            <undefined> */
   U_NIL,                                 /* 0xB9            <undefined> */
   U_NIL,                                 /* 0xBA            <undefined> */
   U_ArabicSemicolon,                     /* 0xBB   0x061B   ARABIC SEMICOLON */
   U_NIL,                                 /* 0xBC            <undefined> */
   U_NIL,                                 /* 0xBD            <undefined> */
   U_NIL,                                 /* 0xBE            <undefined> */
   U_ArabicQuestionMark,                  /* 0xBF   0x061F   ARABIC QUESTION MARK */
   U_NIL,                                 /* 0xC0            <undefined> */
   U_ArabicLetterHamza,                   /* 0xC1   0x0621   ARABIC LETTER HAMZA */
   U_ArabicLetterAlef,                    /* 0xC2   0x0622   ARABIC LETTER ALEF WITH MADDA ABOVE */
   U_ArabicLetterAlef,                    /* 0xC3   0x0623   ARABIC LETTER ALEF WITH HAMZA ABOVE */
   U_ArabicLetterWaw,                     /* 0xC4   0x0624   ARABIC LETTER WAW WITH HAMZA ABOVE */
   U_ArabicLetterAlef,                    /* 0xC5   0x0625   ARABIC LETTER ALEF WITH HAMZA BELOW */
   U_ArabicLetterYeh,                     /* 0xC6   0x0626   ARABIC LETTER YEH WITH HAMZA ABOVE */
   U_ArabicLetterAlef,                    /* 0xC7   0x0627   ARABIC LETTER ALEF */
   U_ArabicLetterBeh,                     /* 0xC8   0x0628   ARABIC LETTER BEH */
   U_ArabicLetterTeh,                     /* 0xC9   0x0629   ARABIC LETTER TEH MARBUTA */
   U_ArabicLetterTeh,                     /* 0xCA   0x062A   ARABIC LETTER TEH */
   U_ArabicLetterTheh,                    /* 0xCB   0x062B   ARABIC LETTER THEH */
   U_ArabicLetterJeem,                    /* 0xCC   0x062C   ARABIC LETTER JEEM */
   U_ArabicLetterHah,                     /* 0xCD   0x062D   ARABIC LETTER HAH */
   U_ArabicLetterKhah,                    /* 0xCE   0x062E   ARABIC LETTER KHAH */
   U_ArabicLetterDal,                     /* 0xCF   0x062F   ARABIC LETTER DAL */
   U_ArabicLetterThal,                    /* 0xD0   0x0630   ARABIC LETTER THAL */
   U_ArabicLetterReh,                     /* 0xD1   0x0631   ARABIC LETTER REH */
   U_ArabicLetterZain,                    /* 0xD2   0x0632   ARABIC LETTER ZAIN */
   U_ArabicLetterSeen,                    /* 0xD3   0x0633   ARABIC LETTER SEEN */
   U_ArabicLetterSheen,                   /* 0xD4   0x0634   ARABIC LETTER SHEEN */
   U_ArabicLetterSad,                     /* 0xD5   0x0635   ARABIC LETTER SAD */
   U_ArabicLetterDad,                     /* 0xD6   0x0636   ARABIC LETTER DAD */
   U_ArabicLetterTah,                     /* 0xD7   0x0637   ARABIC LETTER TAH */
   U_ArabicLetterZah,                     /* 0xD8   0x0638   ARABIC LETTER ZAH */
   U_ArabicLetterAin,                     /* 0xD9   0x0639   ARABIC LETTER AIN */
   U_ArabicLetterGhain,                   /* 0xDA   0x063A   ARABIC LETTER GHAIN */
   U_NIL,                                 /* 0xDB            <undefined> */
   U_NIL,                                 /* 0xDC            <undefined> */
   U_NIL,                                 /* 0xDD            <undefined> */
   U_NIL,                                 /* 0xDE            <undefined> */
   U_NIL,                                 /* 0xDF            <undefined> */
   U_ArabicTatweel,                       /* 0xE0   0x0640   ARABIC TATWEEL */
   U_ArabicLetterFeh,                     /* 0xE1   0x0641   ARABIC LETTER FEH */
   U_ArabicLetterQaf,                     /* 0xE2   0x0642   ARABIC LETTER QAF */
   U_ArabicLetterKaf,                     /* 0xE3   0x0643   ARABIC LETTER KAF */
   U_ArabicLetterLam,                     /* 0xE4   0x0644   ARABIC LETTER LAM */
   U_ArabicLetterMeem,                    /* 0xE5   0x0645   ARABIC LETTER MEEM */
   U_ArabicLetterNoon,                    /* 0xE6   0x0646   ARABIC LETTER NOON */
   U_ArabicLetterHeh,                     /* 0xE7   0x0647   ARABIC LETTER HEH */
   U_ArabicLetterWaw,                     /* 0xE8   0x0648   ARABIC LETTER WAW */
   U_ArabicLetterAlef,                    /* 0xE9   0x0649   ARABIC LETTER ALEF MAKSURA */
   U_ArabicLetterYeh,                     /* 0xEA   0x064A   ARABIC LETTER YEH */
   U_ArabicFathatan,                      /* 0xEB   0x064B   ARABIC FATHATAN */
   U_ArabicDammatan,                      /* 0xEC   0x064C   ARABIC DAMMATAN */
   U_ArabicKasratan,                      /* 0xED   0x064D   ARABIC KASRATAN */
   U_ArabicFatha,                         /* 0xEE   0x064E   ARABIC FATHA */
   U_ArabicDamma,                         /* 0xEF   0x064F   ARABIC DAMMA */
   U_ArabicKasra,                         /* 0xF0   0x0650   ARABIC KASRA */
   U_ArabicShadda,                        /* 0xF1   0x0651   ARABIC SHADDA */
   U_ArabicSukun,                         /* 0xF2   0x0652   ARABIC SUKUN */
   U_NIL,                                 /* 0xF3            <undefined> */
   U_NIL,                                 /* 0xF4            <undefined> */
   U_NIL,                                 /* 0xF5            <undefined> */
   U_NIL,                                 /* 0xF6            <undefined> */
   U_NIL,                                 /* 0xF7            <undefined> */
   U_NIL,                                 /* 0xF8            <undefined> */
   U_NIL,                                 /* 0xF9            <undefined> */
   U_NIL,                                 /* 0xFA            <undefined> */
   U_NIL,                                 /* 0xFB            <undefined> */
   U_NIL,                                 /* 0xFC            <undefined> */
   U_NIL,                                 /* 0xFD            <undefined> */
   U_NIL,                                 /* 0xFE            <undefined> */
   U_NIL                                  /* 0xFF            <undefined> */
};










/******************************************************************************
*
*  u_CODE_GREEK[]:
*     Unicode named codepage for ISO encoding Greek (iso-8859-7)
*
*  Name:             ISO 8859-7:2003 to Unicode
*  Unicode version:  4.0
*  Table version:    2.0
*  Table format:     Format A
*  Date:             2003-Nov-12
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_GREEK[] =           /* CODE_GREEK */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LeftSingleQuotationMark,             /* 0xA1   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0xA2   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_EuroSign,                            /* 0xA4   0x20AC   EURO SIGN */
   U_DrachmaSign,                         /* 0xA5   0x20AF   DRACHMA SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_GreekYpogegrammeni,                  /* 0xAA   0x037A   GREEK YPOGEGRAMMENI */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_NIL,                                 /* 0xAE            <undefined> */
   U_HorizontalBar,                       /* 0xAF   0x2015   HORIZONTAL BAR */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_GreekTonus,                          /* 0xB4   0x0384   GREEK TONOS */
   U_GreekDialytikaTonos,                 /* 0xB5   0x0385   GREEK DIALYTIKA TONOS */
   U_GreekCapitalLetterAlphaWithTonos,    /* 0xB6   0x0386   GREEK CAPITAL LETTER ALPHA WITH TONOS */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_GreekCapitalLetterEpsilonWithTonos,  /* 0xB8   0x0388   GREEK CAPITAL LETTER EPSILON WITH TONOS */
   U_GreekCapitalLetterEtaWithTonos,      /* 0xB9   0x0389   GREEK CAPITAL LETTER ETA WITH TONOS */
   U_GreekCapitalLetterIotaWithTonos,     /* 0xBA   0x038A   GREEK CAPITAL LETTER IOTA WITH TONOS */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_GreekCapitalLetterOmicronWithTonos,  /* 0xBC   0x038C   GREEK CAPITAL LETTER OMICRON WITH TONOS */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_GreekCapitalLetterUpsilonWithTonos,  /* 0xBE   0x038E   GREEK CAPITAL LETTER UPSILON WITH TONOS */
   U_GreekCapitalLetterOmegaWithTonos,    /* 0xBF   0x038F   GREEK CAPITAL LETTER OMEGA WITH TONOS */
                                          /* 0xC0   0x0390   GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS */
   U_GreekSmallLetterIotaWithDialytikaAndTonos,
   U_GreekCapitalLetterAlpha,             /* 0xC1   0x0391   GREEK CAPITAL LETTER ALPHA */
   U_GreekCapitalLetterBeta,              /* 0xC2   0x0392   GREEK CAPITAL LETTER BETA */
   U_GreekCapitalLetterGamma,             /* 0xC3   0x0393   GREEK CAPITAL LETTER GAMMA */
   U_GreekCapitalLetterDelta,             /* 0xC4   0x0394   GREEK CAPITAL LETTER DELTA */
   U_GreekCapitalLetterEpsilon,           /* 0xC5   0x0395   GREEK CAPITAL LETTER EPSILON */
   U_GreekCapitalLetterZeta,              /* 0xC6   0x0396   GREEK CAPITAL LETTER ZETA */
   U_GreekCapitalLetterEta,               /* 0xC7   0x0397   GREEK CAPITAL LETTER ETA */
   U_GreekCapitalLetterTheta,             /* 0xC8   0x0398   GREEK CAPITAL LETTER THETA */
   U_GreekCapitalLetterIota,              /* 0xC9   0x0399   GREEK CAPITAL LETTER IOTA */
   U_GreekCapitalLetterKappa,             /* 0xCA   0x039A   GREEK CAPITAL LETTER KAPPA */
   U_GreekCapitalLetterLambda,            /* 0xCB   0x039B   GREEK CAPITAL LETTER LAMBDA */
   U_GreekCapitalLetterMu,                /* 0xCC   0x039C   GREEK CAPITAL LETTER MU */
   U_GreekCapitalLetterNu,                /* 0xCD   0x039D   GREEK CAPITAL LETTER NU */
   U_GreekCapitalLetterXi,                /* 0xCE   0x039E   GREEK CAPITAL LETTER XI */
   U_GreekCapitalLetterOmicron,           /* 0xCF   0x039F   GREEK CAPITAL LETTER OMICRON */
   U_GreekCapitalLetterPi,                /* 0xD0   0x03A0   GREEK CAPITAL LETTER PI */
   U_GreekCapitalLetterRho,               /* 0xD1   0x03A1   GREEK CAPITAL LETTER RHO */
   U_NIL,                                 /* 0xD2            <undefined> */
   U_GreekCapitalLetterSigma,             /* 0xD3   0x03A3   GREEK CAPITAL LETTER SIGMA */
   U_GreekCapitalLetterTau,               /* 0xD4   0x03A4   GREEK CAPITAL LETTER TAU */
   U_GreekCapitalLetterUpsilon,           /* 0xD5   0x03A5   GREEK CAPITAL LETTER UPSILON */
   U_GreekCapitalLetterPhi,               /* 0xD6   0x03A6   GREEK CAPITAL LETTER PHI */
   U_GreekCapitalLetterChi,               /* 0xD7   0x03A7   GREEK CAPITAL LETTER CHI */
   U_GreekCapitalLetterPsi,               /* 0xD8   0x03A8   GREEK CAPITAL LETTER PSI */
   U_GreekCapitalLetterOmega,             /* 0xD9   0x03A9   GREEK CAPITAL LETTER OMEGA */
   U_GreekCapitalLetterIotaWithDialytika, /* 0xDA   0x03AA   GREEK CAPITAL LETTER IOTA WITH DIALYTIKA */
                                          /* 0xDB   0x03AB   GREEK CAPITAL LETTER UPSILON WITH DIALYTIKA */
   U_GreekCapitalLetterUpsilonWithDialytika,
   U_GreekSmallLetterAlphaWithTonos,      /* 0xDC   0x03AC   GREEK SMALL LETTER ALPHA WITH TONOS */
   U_GreekSmallLetterEpsilonWithTonos,    /* 0xDD   0x03AD   GREEK SMALL LETTER EPSILON WITH TONOS */
   U_GreekSmallLetterEtaWithTonos,        /* 0xDE   0x03AE   GREEK SMALL LETTER ETA WITH TONOS */
   U_GreekSmallLetterIotaWithTonos,       /* 0xDF   0x03AF   GREEK SMALL LETTER IOTA WITH TONOS */
                                          /* 0xE0   0x03B0   GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS */
   U_GreekSmallLetterUpsilonWithDialytikaAndTonos,
   U_GreekSmallLetterAlpha,               /* 0xE1   0x03B1   GREEK SMALL LETTER ALPHA */
   U_GreekSmallLetterBeta,                /* 0xE2   0x03B2   GREEK SMALL LETTER BETA */
   U_GreekSmallLetterGamma,               /* 0xE3   0x03B3   GREEK SMALL LETTER GAMMA */
   U_GreekSmallLetterDelta,               /* 0xE4   0x03B4   GREEK SMALL LETTER DELTA */
   U_GreekSmallLetterEpsilon,             /* 0xE5   0x03B5   GREEK SMALL LETTER EPSILON */
   U_GreekSmallLetterZeta,                /* 0xE6   0x03B6   GREEK SMALL LETTER ZETA */
   U_GreekSmallLetterEta,                 /* 0xE7   0x03B7   GREEK SMALL LETTER ETA */
   U_GreekSmallLetterTheta,               /* 0xE8   0x03B8   GREEK SMALL LETTER THETA */
   U_GreekSmallLetterIota,                /* 0xE9   0x03B9   GREEK SMALL LETTER IOTA */
   U_GreekSmallLetterKappa,               /* 0xEA   0x03BA   GREEK SMALL LETTER KAPPA */
   U_GreekSmallLetterLambda,              /* 0xEB   0x03BB   GREEK SMALL LETTER LAMBDA */
   U_GreekSmallLetterMu,                  /* 0xEC   0x03BC   GREEK SMALL LETTER MU */
   U_GreekSmallLetterNu,                  /* 0xED   0x03BD   GREEK SMALL LETTER NU */
   U_GreekSmallLetterXi,                  /* 0xEE   0x03BE   GREEK SMALL LETTER XI */
   U_GreekSmallLetterOmicron,             /* 0xEF   0x03BF   GREEK SMALL LETTER OMICRON */
   U_GreekSmallLetterPi,                  /* 0xF0   0x03C0   GREEK SMALL LETTER PI */
   U_GreekSmallLetterRho,                 /* 0xF1   0x03C1   GREEK SMALL LETTER RHO */
   U_GreekSmallLetterFinalSigma,          /* 0xF2   0x03C2   GREEK SMALL LETTER FINAL SIGMA */
   U_GreekSmallLetterSigma,               /* 0xF3   0x03C3   GREEK SMALL LETTER SIGMA */
   U_GreekSmallLetterTau,                 /* 0xF4   0x03C4   GREEK SMALL LETTER TAU */
   U_GreekSmallLetterUpsilon,             /* 0xF5   0x03C5   GREEK SMALL LETTER UPSILON */
   U_GreekSmallLetterPhi,                 /* 0xF6   0x03C6   GREEK SMALL LETTER PHI */
   U_GreekSmallLetterChi,                 /* 0xF7   0x03C7   GREEK SMALL LETTER CHI */
   U_GreekSmallLetterPsi,                 /* 0xF8   0x03C8   GREEK SMALL LETTER PSI */
   U_GreekSmallLetterOmega,               /* 0xF9   0x03C9   GREEK SMALL LETTER OMEGA */
   U_GreekSmallLetterIotaWithDialytika,   /* 0xFA   0x03CA   GREEK SMALL LETTER IOTA WITH DIALYTIKA */
   U_GreekSmallLetterUpsilonWithDialytika,/* 0xFB   0x03CB   GREEK SMALL LETTER UPSILON WITH DIALYTIKA */
   U_GreekSmallLetterOmicronWithTonos,    /* 0xFC   0x03CC   GREEK SMALL LETTER OMICRON WITH TONOS */
   U_GreekSmallLetterUpsilonWithTonos,    /* 0xFD   0x03CD   GREEK SMALL LETTER UPSILON WITH TONOS */
   U_GreekSmallLetterOmegaWithTonos,      /* 0xFE   0x03CE   GREEK SMALL LETTER OMEGA WITH TONOS */
   U_NIL,                                 /* 0xFF            <undefined> */
};





/******************************************************************************
*
*  CODE_GREEK_lig[]:
*     list of ligatures:
*
*  CODE_GREEK_lig[0] is the original ligature character
*  CODE_GREEK_lig[1] + CODE_GREEK_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_GREEK_lig[][3] =      /* CODE_GREEK character ligatures */
{
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_GREEK sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_GREEK[] =        /* CODE_GREEK */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LeftSingleQuotationMark,             /* 0xA1   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0xA2   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_EuroSign,                            /* 0xA4   0x20AC   EURO SIGN */
   U_DrachmaSign,                         /* 0xA5   0x20AF   DRACHMA SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_GreekYpogegrammeni,                  /* 0xAA   0x037A   GREEK YPOGEGRAMMENI */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_NIL,                                 /* 0xAE            <undefined> */
   U_HorizontalBar,                       /* 0xAF   0x2015   HORIZONTAL BAR */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_GreekTonus,                          /* 0xB4   0x0384   GREEK TONOS */
   U_GreekDialytikaTonos,                 /* 0xB5   0x0385   GREEK DIALYTIKA TONOS */
   U_GreekCapitalLetterAlpha,             /* 0xB6   0x0386   GREEK CAPITAL LETTER ALPHA WITH TONOS */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_GreekCapitalLetterEpsilon,           /* 0xB8   0x0388   GREEK CAPITAL LETTER EPSILON WITH TONOS */
   U_GreekCapitalLetterEta,               /* 0xB9   0x0389   GREEK CAPITAL LETTER ETA WITH TONOS */
   U_GreekCapitalLetterIota,              /* 0xBA   0x038A   GREEK CAPITAL LETTER IOTA WITH TONOS */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_GreekCapitalLetterOmicron,           /* 0xBC   0x038C   GREEK CAPITAL LETTER OMICRON WITH TONOS */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_GreekCapitalLetterUpsilon,           /* 0xBE   0x038E   GREEK CAPITAL LETTER UPSILON WITH TONOS */
   U_GreekCapitalLetterOmega,             /* 0xBF   0x038F   GREEK CAPITAL LETTER OMEGA WITH TONOS */
   U_GreekCapitalLetterIota,              /* 0xC0   0x0390   GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS */
   U_GreekCapitalLetterAlpha,             /* 0xC1   0x0391   GREEK CAPITAL LETTER ALPHA */
   U_GreekCapitalLetterBeta,              /* 0xC2   0x0392   GREEK CAPITAL LETTER BETA */
   U_GreekCapitalLetterGamma,             /* 0xC3   0x0393   GREEK CAPITAL LETTER GAMMA */
   U_GreekCapitalLetterDelta,             /* 0xC4   0x0394   GREEK CAPITAL LETTER DELTA */
   U_GreekCapitalLetterEpsilon,           /* 0xC5   0x0395   GREEK CAPITAL LETTER EPSILON */
   U_GreekCapitalLetterZeta,              /* 0xC6   0x0396   GREEK CAPITAL LETTER ZETA */
   U_GreekCapitalLetterEta,               /* 0xC7   0x0397   GREEK CAPITAL LETTER ETA */
   U_GreekCapitalLetterTheta,             /* 0xC8   0x0398   GREEK CAPITAL LETTER THETA */
   U_GreekCapitalLetterIota,              /* 0xC9   0x0399   GREEK CAPITAL LETTER IOTA */
   U_GreekCapitalLetterKappa,             /* 0xCA   0x039A   GREEK CAPITAL LETTER KAPPA */
   U_GreekCapitalLetterLambda,            /* 0xCB   0x039B   GREEK CAPITAL LETTER LAMBDA */
   U_GreekCapitalLetterMu,                /* 0xCC   0x039C   GREEK CAPITAL LETTER MU */
   U_GreekCapitalLetterNu,                /* 0xCD   0x039D   GREEK CAPITAL LETTER NU */
   U_GreekCapitalLetterXi,                /* 0xCE   0x039E   GREEK CAPITAL LETTER XI */
   U_GreekCapitalLetterOmicron,           /* 0xCF   0x039F   GREEK CAPITAL LETTER OMICRON */
   U_GreekCapitalLetterPi,                /* 0xD0   0x03A0   GREEK CAPITAL LETTER PI */
   U_GreekCapitalLetterRho,               /* 0xD1   0x03A1   GREEK CAPITAL LETTER RHO */
   U_NIL,                                 /* 0xD2            <undefined> */
   U_GreekCapitalLetterSigma,             /* 0xD3   0x03A3   GREEK CAPITAL LETTER SIGMA */
   U_GreekCapitalLetterTau,               /* 0xD4   0x03A4   GREEK CAPITAL LETTER TAU */
   U_GreekCapitalLetterUpsilon,           /* 0xD5   0x03A5   GREEK CAPITAL LETTER UPSILON */
   U_GreekCapitalLetterPhi,               /* 0xD6   0x03A6   GREEK CAPITAL LETTER PHI */
   U_GreekCapitalLetterChi,               /* 0xD7   0x03A7   GREEK CAPITAL LETTER CHI */
   U_GreekCapitalLetterPsi,               /* 0xD8   0x03A8   GREEK CAPITAL LETTER PSI */
   U_GreekCapitalLetterOmega,             /* 0xD9   0x03A9   GREEK CAPITAL LETTER OMEGA */
   U_GreekCapitalLetterIota,              /* 0xDA   0x03AA   GREEK CAPITAL LETTER IOTA WITH DIALYTIKA */
   U_GreekCapitalLetterUpsilon,           /* 0xDB   0x03AB   GREEK CAPITAL LETTER UPSILON WITH DIALYTIKA */
   U_GreekCapitalLetterAlpha,             /* 0xDC   0x03AC   GREEK SMALL LETTER ALPHA WITH TONOS */
   U_GreekCapitalLetterEpsilon,           /* 0xDD   0x03AD   GREEK SMALL LETTER EPSILON WITH TONOS */
   U_GreekCapitalLetterEta,               /* 0xDE   0x03AE   GREEK SMALL LETTER ETA WITH TONOS */
   U_GreekCapitalLetterIota,              /* 0xDF   0x03AF   GREEK SMALL LETTER IOTA WITH TONOS */
   U_GreekCapitalLetterUpsilon,           /* 0xE0   0x03B0   GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS */
   U_GreekCapitalLetterAlpha,             /* 0xE1   0x03B1   GREEK SMALL LETTER ALPHA */
   U_GreekCapitalLetterBeta,              /* 0xE2   0x03B2   GREEK SMALL LETTER BETA */
   U_GreekCapitalLetterGamma,             /* 0xE3   0x03B3   GREEK SMALL LETTER GAMMA */
   U_GreekCapitalLetterDelta,             /* 0xE4   0x03B4   GREEK SMALL LETTER DELTA */
   U_GreekCapitalLetterEpsilon,           /* 0xE5   0x03B5   GREEK SMALL LETTER EPSILON */
   U_GreekCapitalLetterZeta,              /* 0xE6   0x03B6   GREEK SMALL LETTER ZETA */
   U_GreekCapitalLetterEta,               /* 0xE7   0x03B7   GREEK SMALL LETTER ETA */
   U_GreekCapitalLetterTheta,             /* 0xE8   0x03B8   GREEK SMALL LETTER THETA */
   U_GreekCapitalLetterIota,              /* 0xE9   0x03B9   GREEK SMALL LETTER IOTA */
   U_GreekCapitalLetterKappa,             /* 0xEA   0x03BA   GREEK SMALL LETTER KAPPA */
   U_GreekCapitalLetterLambda,            /* 0xEB   0x03BB   GREEK SMALL LETTER LAMBDA */
   U_GreekCapitalLetterMu,                /* 0xEC   0x03BC   GREEK SMALL LETTER MU */
   U_GreekCapitalLetterNu,                /* 0xED   0x03BD   GREEK SMALL LETTER NU */
   U_GreekCapitalLetterXi,                /* 0xEE   0x03BE   GREEK SMALL LETTER XI */
   U_GreekCapitalLetterOmicron,           /* 0xEF   0x03BF   GREEK SMALL LETTER OMICRON */
   U_GreekCapitalLetterPi,                /* 0xF0   0x03C0   GREEK SMALL LETTER PI */
   U_GreekCapitalLetterRho,               /* 0xF1   0x03C1   GREEK SMALL LETTER RHO */
   U_GreekCapitalLetterSigma,             /* 0xF2   0x03C2   GREEK SMALL LETTER FINAL SIGMA */
   U_GreekCapitalLetterSigma,             /* 0xF3   0x03C3   GREEK SMALL LETTER SIGMA */
   U_GreekCapitalLetterTau,               /* 0xF4   0x03C4   GREEK SMALL LETTER TAU */
   U_GreekCapitalLetterUpsilon,           /* 0xF5   0x03C5   GREEK SMALL LETTER UPSILON */
   U_GreekCapitalLetterPhi,               /* 0xF6   0x03C6   GREEK SMALL LETTER PHI */
   U_GreekCapitalLetterChi,               /* 0xF7   0x03C7   GREEK SMALL LETTER CHI */
   U_GreekCapitalLetterPsi,               /* 0xF8   0x03C8   GREEK SMALL LETTER PSI */
   U_GreekCapitalLetterOmega,             /* 0xF9   0x03C9   GREEK SMALL LETTER OMEGA */
   U_GreekCapitalLetterIota,              /* 0xFA   0x03CA   GREEK SMALL LETTER IOTA WITH DIALYTIKA */
   U_GreekCapitalLetterUpsilon,           /* 0xFB   0x03CB   GREEK SMALL LETTER UPSILON WITH DIALYTIKA */
   U_GreekCapitalLetterOmicron,           /* 0xFC   0x03CC   GREEK SMALL LETTER OMICRON WITH TONOS */
   U_GreekCapitalLetterUpsilon,           /* 0xFD   0x03CD   GREEK SMALL LETTER UPSILON WITH TONOS */
   U_GreekCapitalLetterOmega,             /* 0xFE   0x03CE   GREEK SMALL LETTER OMEGA WITH TONOS */
   U_NIL,                                 /* 0xFF            <undefined> */
};










/******************************************************************************
*
*  u_CODE_HEBREW[]:
*     Unicode named codepage for ISO encoding Hebrew (iso-8859-8)
*
*  Name:             ISO/IEC 8859-8:1999 to Unicode
*  Unicode version:  3.0
*  Table version:    1.1
*  Table format:     Format A
*  Date:             2000-Jan-03
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_HEBREW[] =          /* CODE_HEBREW */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_NIL,                                 /* 0xA1            <undefined> */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_MultiplicationSign,                  /* 0xAA   0x00D7   MULTIPLICATION SIGN */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_DivisionSign,                        /* 0xBA   0x00F7   DIVISION SIGN */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_NIL,                                 /* 0xBF            <undefined> */
   U_NIL,                                 /* 0xC0            <undefined> */
   U_NIL,                                 /* 0xC1            <undefined> */
   U_NIL,                                 /* 0xC2            <undefined> */
   U_NIL,                                 /* 0xC3            <undefined> */
   U_NIL,                                 /* 0xC4            <undefined> */
   U_NIL,                                 /* 0xC5            <undefined> */
   U_NIL,                                 /* 0xC6            <undefined> */
   U_NIL,                                 /* 0xC7            <undefined> */
   U_NIL,                                 /* 0xC8            <undefined> */
   U_NIL,                                 /* 0xC9            <undefined> */
   U_NIL,                                 /* 0xCA            <undefined> */
   U_NIL,                                 /* 0xCB            <undefined> */
   U_NIL,                                 /* 0xCC            <undefined> */
   U_NIL,                                 /* 0xCD            <undefined> */
   U_NIL,                                 /* 0xCE            <undefined> */
   U_NIL,                                 /* 0xCF            <undefined> */
   U_NIL,                                 /* 0xD0            <undefined> */
   U_NIL,                                 /* 0xD1            <undefined> */
   U_NIL,                                 /* 0xD2            <undefined> */
   U_NIL,                                 /* 0xD3            <undefined> */
   U_NIL,                                 /* 0xD4            <undefined> */
   U_NIL,                                 /* 0xD5            <undefined> */
   U_NIL,                                 /* 0xD6            <undefined> */
   U_NIL,                                 /* 0xD7            <undefined> */
   U_NIL,                                 /* 0xD8            <undefined> */
   U_NIL,                                 /* 0xD9            <undefined> */
   U_NIL,                                 /* 0xDA            <undefined> */
   U_NIL,                                 /* 0xDB            <undefined> */
   U_NIL,                                 /* 0xDC            <undefined> */
   U_NIL,                                 /* 0xDD            <undefined> */
   U_NIL,                                 /* 0xDE            <undefined> */
   U_DoubleLowLine,                       /* 0xDF   0x2017   DOUBLE LOW LINE */
   U_HebrewLetterAlef,                    /* 0xE0   0x05D0   HEBREW LETTER ALEF */
   U_HebrewLetterBet,                     /* 0xE1   0x05D1   HEBREW LETTER BET */
   U_HebrewLetterGimel,                   /* 0xE2   0x05D2   HEBREW LETTER GIMEL */
   U_HebrewLetterDalet,                   /* 0xE3   0x05D3   HEBREW LETTER DALET */
   U_HebrewLetterHe,                      /* 0xE4   0x05D4   HEBREW LETTER HE */
   U_HebrewLetterVav,                     /* 0xE5   0x05D5   HEBREW LETTER VAV */
   U_HebrewLetterZayin,                   /* 0xE6   0x05D6   HEBREW LETTER ZAYIN */
   U_HebrewLetterHet,                     /* 0xE7   0x05D7   HEBREW LETTER HET */
   U_HebrewLetterTet,                     /* 0xE8   0x05D8   HEBREW LETTER TET */
   U_HebrewLetterYod,                     /* 0xE9   0x05D9   HEBREW LETTER YOD */
   U_HebrewLetterFinalKaf,                /* 0xEA   0x05DA   HEBREW LETTER FINAL KAF */
   U_HebrewLetterKaf,                     /* 0xEB   0x05DB   HEBREW LETTER KAF */
   U_HebrewLetterLamed,                   /* 0xEC   0x05DC   HEBREW LETTER LAMED */
   U_HebrewLetterFinalMem,                /* 0xED   0x05DD   HEBREW LETTER FINAL MEM */
   U_HebrewLetterMem,                     /* 0xEE   0x05DE   HEBREW LETTER MEM */
   U_HebrewLetterFinalNun,                /* 0xEF   0x05DF   HEBREW LETTER FINAL NUN */
   U_HebrewLetterNun,                     /* 0xF0   0x05E0   HEBREW LETTER NUN */
   U_HebrewLetterSamekh,                  /* 0xF1   0x05E1   HEBREW LETTER SAMEKH */
   U_HebrewLetterAyin,                    /* 0xF2   0x05E2   HEBREW LETTER AYIN */
   U_HebrewLetterFinalPe,                 /* 0xF3   0x05E3   HEBREW LETTER FINAL PE */
   U_HebrewLetterPe,                      /* 0xF4   0x05E4   HEBREW LETTER PE */
   U_HebrewLetterFinalTsadi,              /* 0xF5   0x05E5   HEBREW LETTER FINAL TSADI */
   U_HebrewLetterTsadi,                   /* 0xF6   0x05E6   HEBREW LETTER TSADI */
   U_HebrewLetterQof,                     /* 0xF7   0x05E7   HEBREW LETTER QOF */
   U_HebrewLetterResh,                    /* 0xF8   0x05E8   HEBREW LETTER RESH */
   U_HebrewLetterShin,                    /* 0xF9   0x05E9   HEBREW LETTER SHIN */
   U_HebrewLetterTav,                     /* 0xFA   0x05EA   HEBREW LETTER TAV */
   U_NIL,                                 /* 0xFB            <undefined> */
   U_NIL,                                 /* 0xFC            <undefined> */
   U_LeftToRightMark,                     /* 0xFD   0x200E   LEFT-TO-RIGHT MARK */
   U_RightToLeftMark,                     /* 0xFE   0x200F   RIGHT-TO-LEFT MARK */
   U_NIL                                  /* 0xFF            <undefined> */
};





/******************************************************************************
*
*  CODE_HEBREW_lig[]:
*     list of ligatures:
*
*  CODE_HEBREW_lig[0] is the original ligature character
*  CODE_HEBREW_lig[1] + CODE_HEBREW_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_HEBREW_lig[][3] =     /* CODE_HEBREW character ligatures */
{
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_HEBREW sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_HEBREW[] =       /* CODE_HEBREW */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_NIL,                                 /* 0xA1            <undefined> */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_MultiplicationSign,                  /* 0xAA   0x00D7   MULTIPLICATION SIGN */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_DivisionSign,                        /* 0xBA   0x00F7   DIVISION SIGN */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_NIL,                                 /* 0xBF            <undefined> */
   U_NIL,                                 /* 0xC0            <undefined> */
   U_NIL,                                 /* 0xC1            <undefined> */
   U_NIL,                                 /* 0xC2            <undefined> */
   U_NIL,                                 /* 0xC3            <undefined> */
   U_NIL,                                 /* 0xC4            <undefined> */
   U_NIL,                                 /* 0xC5            <undefined> */
   U_NIL,                                 /* 0xC6            <undefined> */
   U_NIL,                                 /* 0xC7            <undefined> */
   U_NIL,                                 /* 0xC8            <undefined> */
   U_NIL,                                 /* 0xC9            <undefined> */
   U_NIL,                                 /* 0xCA            <undefined> */
   U_NIL,                                 /* 0xCB            <undefined> */
   U_NIL,                                 /* 0xCC            <undefined> */
   U_NIL,                                 /* 0xCD            <undefined> */
   U_NIL,                                 /* 0xCE            <undefined> */
   U_NIL,                                 /* 0xCF            <undefined> */
   U_NIL,                                 /* 0xD0            <undefined> */
   U_NIL,                                 /* 0xD1            <undefined> */
   U_NIL,                                 /* 0xD2            <undefined> */
   U_NIL,                                 /* 0xD3            <undefined> */
   U_NIL,                                 /* 0xD4            <undefined> */
   U_NIL,                                 /* 0xD5            <undefined> */
   U_NIL,                                 /* 0xD6            <undefined> */
   U_NIL,                                 /* 0xD7            <undefined> */
   U_NIL,                                 /* 0xD8            <undefined> */
   U_NIL,                                 /* 0xD9            <undefined> */
   U_NIL,                                 /* 0xDA            <undefined> */
   U_NIL,                                 /* 0xDB            <undefined> */
   U_NIL,                                 /* 0xDC            <undefined> */
   U_NIL,                                 /* 0xDD            <undefined> */
   U_NIL,                                 /* 0xDE            <undefined> */
   U_DoubleLowLine,                       /* 0xDF   0x2017   DOUBLE LOW LINE */
   U_HebrewLetterAlef,                    /* 0xE0   0x05D0   HEBREW LETTER ALEF */
   U_HebrewLetterBet,                     /* 0xE1   0x05D1   HEBREW LETTER BET */
   U_HebrewLetterGimel,                   /* 0xE2   0x05D2   HEBREW LETTER GIMEL */
   U_HebrewLetterDalet,                   /* 0xE3   0x05D3   HEBREW LETTER DALET */
   U_HebrewLetterHe,                      /* 0xE4   0x05D4   HEBREW LETTER HE */
   U_HebrewLetterVav,                     /* 0xE5   0x05D5   HEBREW LETTER VAV */
   U_HebrewLetterZayin,                   /* 0xE6   0x05D6   HEBREW LETTER ZAYIN */
   U_HebrewLetterHet,                     /* 0xE7   0x05D7   HEBREW LETTER HET */
   U_HebrewLetterTet,                     /* 0xE8   0x05D8   HEBREW LETTER TET */
   U_HebrewLetterYod,                     /* 0xE9   0x05D9   HEBREW LETTER YOD */
   U_HebrewLetterKaf,                     /* 0xEA   0x05DA   HEBREW LETTER FINAL KAF */
   U_HebrewLetterKaf,                     /* 0xEB   0x05DB   HEBREW LETTER KAF */
   U_HebrewLetterLamed,                   /* 0xEC   0x05DC   HEBREW LETTER LAMED */
   U_HebrewLetterMem,                     /* 0xED   0x05DD   HEBREW LETTER FINAL MEM */
   U_HebrewLetterMem,                     /* 0xEE   0x05DE   HEBREW LETTER MEM */
   U_HebrewLetterNun,                     /* 0xEF   0x05DF   HEBREW LETTER FINAL NUN */
   U_HebrewLetterNun,                     /* 0xF0   0x05E0   HEBREW LETTER NUN */
   U_HebrewLetterSamekh,                  /* 0xF1   0x05E1   HEBREW LETTER SAMEKH */
   U_HebrewLetterAyin,                    /* 0xF2   0x05E2   HEBREW LETTER AYIN */
   U_HebrewLetterPe,                      /* 0xF3   0x05E3   HEBREW LETTER FINAL PE */
   U_HebrewLetterPe,                      /* 0xF4   0x05E4   HEBREW LETTER PE */
   U_HebrewLetterTsadi,                   /* 0xF5   0x05E5   HEBREW LETTER FINAL TSADI */
   U_HebrewLetterTsadi,                   /* 0xF6   0x05E6   HEBREW LETTER TSADI */
   U_HebrewLetterQof,                     /* 0xF7   0x05E7   HEBREW LETTER QOF */
   U_HebrewLetterResh,                    /* 0xF8   0x05E8   HEBREW LETTER RESH */
   U_HebrewLetterShin,                    /* 0xF9   0x05E9   HEBREW LETTER SHIN */
   U_HebrewLetterTav,                     /* 0xFA   0x05EA   HEBREW LETTER TAV */
   U_NIL,                                 /* 0xFB            <undefined> */
   U_NIL,                                 /* 0xFC            <undefined> */
   U_LeftToRightMark,                     /* 0xFD   0x200E   LEFT-TO-RIGHT MARK */
   U_RightToLeftMark,                     /* 0xFE   0x200F   RIGHT-TO-LEFT MARK */
   U_NIL                                  /* 0xFF            <undefined> */
};










/******************************************************************************
*
*  u_CODE_TURKISH[]:
*     Unicode named codepage for ISO encoding Latin-5 (iso-8859-9) "Turkish"
*
*  Name:             ISO/IEC 8859-9:1999 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_TURKISH[] =         /* CODE_TURKISH */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_FeminineOrdinalIndicator,            /* 0xAA   0x00AA   FEMININE ORDINAL INDICATOR */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_MasculineOrdinalIndicator,           /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_LatinCapitalLetterAWithGrave,        /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithTilde,        /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLigatureAE,              /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterEWithGrave,        /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterIWithGrave,        /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterGWithBreve,        /* 0xD0   0x011E   LATIN CAPITAL LETTER G WITH BREVE */
   U_LatinCapitalLetterNWithTilde,        /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterOWithGrave,        /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithTilde,        /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterOSlash,            /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterUWithGrave,        /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterIWithDotAbove,     /* 0xDD   0x0130   LATIN CAPITAL LETTER I WITH DOT ABOVE */
   U_LatinCapitalLetterSWithCedilla,      /* 0xDE   0x015E   LATIN CAPITAL LETTER S WITH CEDILLA */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterAWithGrave,          /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithTilde,          /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithRingAbove,      /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLigatureAE,                /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithGrave,          /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithCircumflex,     /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterIWithGrave,          /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterGWithBreve,          /* 0xF0   0x011F   LATIN SMALL LETTER G WITH BREVE */
   U_LatinSmallLetterNWithTilde,          /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinSmallLetterOWithGrave,          /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithTilde,          /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinSmallLetterOSlash,              /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinSmallLetterUWithGrave,          /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterDotlessI,            /* 0xFD   0x0131   LATIN SMALL LETTER DOTLESS I */
   U_LatinSmallLetterSWithCedilla,        /* 0xFE   0x015F   LATIN SMALL LETTER S WITH CEDILLA */
   U_LatinSmallLetterYWithDiaeresis       /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};





/******************************************************************************
*
*  CODE_TURKISH_lig[]:
*     list of ligatures:
*
*  CODE_TURKISH_lig[0] is the original ligature character
*  CODE_TURKISH_lig[1] + CODE_TURKISH_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_TURKISH_lig[][3] =    /* CODE_TURKISH character ligatures */
{
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterAWithRingAbove,    U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterYWithDiaeresis,    U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */

   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_TURKISH sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_TURKISH[] =      /* CODE_TURKISH */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_FeminineOrdinalIndicator,            /* 0xAA   0x00AA   FEMININE ORDINAL INDICATOR */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8   CEDILLA */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_MasculineOrdinalIndicator,           /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_LatinCapitalLetterA,                 /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterG,                 /* 0xD0   0x011E   LATIN CAPITAL LETTER G WITH BREVE */
   U_LatinCapitalLetterN,                 /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterO,                 /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xDD   0x0130   LATIN CAPITAL LETTER I WITH DOT ABOVE */
   U_LatinCapitalLetterS,                 /* 0xDE   0x015E   LATIN CAPITAL LETTER S WITH CEDILLA */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterA,                 /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterG,                 /* 0xF0   0x011F   LATIN SMALL LETTER G WITH BREVE */
   U_LatinCapitalLetterN,                 /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinCapitalLetterO,                 /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xFD   0x0131   LATIN SMALL LETTER DOTLESS I */
   U_LatinCapitalLetterS,                 /* 0xFE   0x015F   LATIN SMALL LETTER S WITH CEDILLA */
   U_LatinCapitalLetterY                  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};










/******************************************************************************
*
*  u_CODE_NORDIC[]:
*     Unicode named codepage for ISO encoding Latin-6 (iso-8859-10) "Nordic"
*
*  Name:             ISO/IEC 8859-10:1998 to Unicode
*  Unicode version:  3.0
*  Table version:    1.1
*  Table format:     Format A
*  Date:             1999 October 11
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_NORDIC[] =          /* CODE_NORDIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterAWithOgonek,       /* 0xA1   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinCapitalLetterEWithMacron,       /* 0xA2   0x0112   LATIN CAPITAL LETTER E WITH MACRON */
   U_LatinCapitalLetterGWithCedilla,      /* 0xA3   0x0122   LATIN CAPITAL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterIWithMacron,       /* 0xA4   0x012A   LATIN CAPITAL LETTER I WITH MACRON */
   U_LatinCapitalLetterIWithTilde,        /* 0xA5   0x0128   LATIN CAPITAL LETTER I WITH TILDE */
   U_LatinCapitalLetterKWithCedilla,      /* 0xA6   0x0136   LATIN CAPITAL LETTER K WITH CEDILLA */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinCapitalLetterLWithCedilla,      /* 0xA8   0x013B   LATIN CAPITAL LETTER L WITH CEDILLA */
   U_LatinCapitalLetterDWithStroke,       /* 0xA9   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterSWithCaron,        /* 0xAA   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LatinCapitalLetterTWithStroke,       /* 0xAB   0x0166   LATIN CAPITAL LETTER T WITH STROKE */
   U_LatinCapitalLetterZWithCaron,        /* 0xAC   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinCapitalLetterUWithMacron,       /* 0xAE   0x016A   LATIN CAPITAL LETTER U WITH MACRON */
   U_LatinCapitalLetterEng,               /* 0xAF   0x014A   LATIN CAPITAL LETTER ENG */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_LatinSmallLetterAWithOgonek,         /* 0xB1   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_LatinSmallLetterEWithMacron,         /* 0xB2   0x0113   LATIN SMALL LETTER E WITH MACRON */
   U_LatinSmallLetterGWithCedilla,        /* 0xB3   0x0123   LATIN SMALL LETTER G WITH CEDILLA */
   U_LatinSmallLetterIWithMacron,         /* 0xB4   0x012B   LATIN SMALL LETTER I WITH MACRON */
   U_LatinSmallLetterIWithTilde,          /* 0xB5   0x0129   LATIN SMALL LETTER I WITH TILDE */
   U_LatinSmallLetterKWithCedilla,        /* 0xB6   0x0137   LATIN SMALL LETTER K WITH CEDILLA */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_LatinSmallLetterLWithCedilla,        /* 0xB8   0x013C   LATIN SMALL LETTER L WITH CEDILLA */
   U_LatinSmallLetterDWithStroke,         /* 0xB9   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinSmallLetterSWithCaron,          /* 0xBA   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinSmallLetterTWithStroke,         /* 0xBB   0x0167   LATIN SMALL LETTER T WITH STROKE */
   U_LatinSmallLetterZWithCaron,          /* 0xBC   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_HorizontalBar,                       /* 0xBD   0x2015   HORIZONTAL BAR */
   U_LatinSmallLetterUWithMacron,         /* 0xBE   0x016B   LATIN SMALL LETTER U WITH MACRON */
   U_LatinSmallLetterEng,                 /* 0xBF   0x014B   LATIN SMALL LETTER ENG */
   U_LatinCapitalLetterAWithMacron,       /* 0xC0   0x0100   LATIN CAPITAL LETTER A WITH MACRON */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithTilde,        /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLigatureAE,              /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterIWithOgonek,       /* 0xC7   0x012E   LATIN CAPITAL LETTER I WITH OGONEK */
   U_LatinCapitalLetterCWithCaron,        /* 0xC8   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithOgonek,       /* 0xCA   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterEWithDotAbove,     /* 0xCC   0x0116   LATIN CAPITAL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 0xD0   0x00D0   LATIN CAPITAL LETTER ETH (Icelandic) */
   U_LatinCapitalLetterNWithCedilla,      /* 0xD1   0x0145   LATIN CAPITAL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterOWithMacron,       /* 0xD2   0x014C   LATIN CAPITAL LETTER O WITH MACRON */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithTilde,        /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterUWithTilde,        /* 0xD7   0x0168   LATIN CAPITAL LETTER U WITH TILDE */
   U_LatinCapitalLetterOSlash,            /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterUWithOgonek,       /* 0xD9   0x0172   LATIN CAPITAL LETTER U WITH OGONEK */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterYWithAcute,        /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 0xDE   0x00DE   LATIN CAPITAL LETTER THORN (Icelandic) */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S (German) */
   U_LatinSmallLetterAWithMacron,         /* 0xE0   0x0101   LATIN SMALL LETTER A WITH MACRON */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithTilde,          /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithRingAbove,      /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLigatureAE,                /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinSmallLetterAWithMacron,         /* 0xE7   0x012F   LATIN SMALL LETTER I WITH OGONEK */
   U_LatinSmallLetterCWithCaron,          /* 0xE8   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithOgonek,         /* 0xEA   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterEWithDotAbove,       /* 0xEC   0x0117   LATIN SMALL LETTER E WITH DOT ABOVE */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterEth,                 /* 0xF0   0x00F0   LATIN SMALL LETTER ETH (Icelandic) */
   U_LatinSmallLetterNWithCedilla,        /* 0xF1   0x0146   LATIN SMALL LETTER N WITH CEDILLA */
   U_LatinSmallLetterOWithMacron,         /* 0xF2   0x014D   LATIN SMALL LETTER O WITH MACRON */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithTilde,          /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterUWithTilde,          /* 0xF7   0x0169   LATIN SMALL LETTER U WITH TILDE */
   U_LatinSmallLetterOSlash,              /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinSmallLetterUWithOgonek,         /* 0xF9   0x0173   LATIN SMALL LETTER U WITH OGONEK */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterYWithAcute,          /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinSmallLetterThorn,               /* 0xFE   0x00FE   LATIN SMALL LETTER THORN (Icelandic) */
   U_LatinSmallLetterKra                  /* 0xFF   0x0138   LATIN SMALL LETTER KRA */
};





/******************************************************************************
*
*  CODE_NORDIC_lig[]:
*     list of ligatures:
*
*  CODE_NORDIC_lig[0] is the original ligature character
*  CODE_NORDIC_lig[1] + CODE_NORDIC_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_NORDIC_lig[][3] =     /* CODE_NORDIC character ligatures */
{
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S (German) */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterAWithRingAbove,    U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */

   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_NORDIC sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_NORDIC[] =       /* CODE_NORDIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterA,                 /* 0xA1   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xA2   0x0112   LATIN CAPITAL LETTER E WITH MACRON */
   U_LatinCapitalLetterG,                 /* 0xA3   0x0122   LATIN CAPITAL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterI,                 /* 0xA4   0x012A   LATIN CAPITAL LETTER I WITH MACRON */
   U_LatinCapitalLetterI,                 /* 0xA5   0x0128   LATIN CAPITAL LETTER I WITH TILDE */
   U_LatinCapitalLetterK,                 /* 0xA6   0x0136   LATIN CAPITAL LETTER K WITH CEDILLA */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinCapitalLetterL,                 /* 0xA8   0x013B   LATIN CAPITAL LETTER L WITH CEDILLA */
   U_LatinCapitalLetterD,                 /* 0xA9   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterS,                 /* 0xAA   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LatinCapitalLetterT,                 /* 0xAB   0x0166   LATIN CAPITAL LETTER T WITH STROKE */
   U_LatinCapitalLetterZ,                 /* 0xAC   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinCapitalLetterU,                 /* 0xAE   0x016A   LATIN CAPITAL LETTER U WITH MACRON */
   U_LatinCapitalLetterEng,               /* 0xAF   0x014A   LATIN CAPITAL LETTER ENG */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_LatinCapitalLetterA,                 /* 0xB1   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xB2   0x0113   LATIN SMALL LETTER E WITH MACRON */
   U_LatinCapitalLetterG,                 /* 0xB3   0x0123   LATIN SMALL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterI,                 /* 0xB4   0x012B   LATIN SMALL LETTER I WITH MACRON */
   U_LatinCapitalLetterI,                 /* 0xB5   0x0129   LATIN SMALL LETTER I WITH TILDE */
   U_LatinCapitalLetterK,                 /* 0xB6   0x0137   LATIN SMALL LETTER K WITH CEDILLA */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_LatinCapitalLetterL,                 /* 0xB8   0x013C   LATIN SMALL LETTER L WITH CEDILLA */
   U_LatinCapitalLetterD,                 /* 0xB9   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinCapitalLetterD,                 /* 0xBA   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinCapitalLetterT,                 /* 0xBB   0x0167   LATIN SMALL LETTER T WITH STROKE */
   U_LatinCapitalLetterZ,                 /* 0xBC   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_HorizontalBar,                       /* 0xBD   0x2015   HORIZONTAL BAR */
   U_LatinCapitalLetterU,                 /* 0xBE   0x016B   LATIN SMALL LETTER U WITH MACRON */
   U_LatinCapitalLetterEng,               /* 0xBF   0x014B   LATIN SMALL LETTER ENG */
   U_LatinCapitalLetterA,                 /* 0xC0   0x0100   LATIN CAPITAL LETTER A WITH MACRON */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterI,                 /* 0xC7   0x012E   LATIN CAPITAL LETTER I WITH OGONEK */
   U_LatinCapitalLetterC,                 /* 0xC8   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xCC   0x0116   LATIN CAPITAL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 0xD0   0x00D0   LATIN CAPITAL LETTER ETH (Icelandic) */
   U_LatinCapitalLetterN,                 /* 0xD1   0x0145   LATIN CAPITAL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterO,                 /* 0xD2   0x014C   LATIN CAPITAL LETTER O WITH MACRON */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xD7   0x0168   LATIN CAPITAL LETTER U WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xD9   0x0172   LATIN CAPITAL LETTER U WITH OGONEK */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 0xDE   0x00DE   LATIN CAPITAL LETTER THORN (Icelandic) */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S (German) */
   U_LatinCapitalLetterA,                 /* 0xE0   0x0101   LATIN SMALL LETTER A WITH MACRON */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterA,                 /* 0xE7   0x012F   LATIN SMALL LETTER I WITH OGONEK */
   U_LatinCapitalLetterC,                 /* 0xE8   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xEC   0x0117   LATIN SMALL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterI,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 0xF0   0x00F0   LATIN SMALL LETTER ETH (Icelandic) */
   U_LatinCapitalLetterN,                 /* 0xF1   0x0146   LATIN SMALL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterO,                 /* 0xF2   0x014D   LATIN SMALL LETTER O WITH MACRON */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xF7   0x0169   LATIN SMALL LETTER U WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xF9   0x0173   LATIN SMALL LETTER U WITH OGONEK */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 0xFE   0x00FE   LATIN SMALL LETTER THORN (Icelandic) */
   U_LatinSmallLetterKra                  /* 0xFF   0x0138   LATIN SMALL LETTER KRA */
};










/******************************************************************************
*
*  u_CODE_THAI[]:
*     Unicode named codepage for ISO encoding Thai (iso-8859-11)
*
*  Name:             ISO/IEC 8859-11:2001 to Unicode
*  Unicode version:  3.2
*  Table version:    1.0
*  Table format:     Format A
*  Date:             2002 October 7
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_THAI[] =            /* CODE_THAI */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_ThaiCharacterKoKai,                  /* 0xA1   0x0E01   THAI CHARACTER KO KAI */
   U_ThaiCharacterKhoKhai,                /* 0xA2   0x0E02   THAI CHARACTER KHO KHAI */
   U_ThaiCharacterKhoKhuat,               /* 0xA3   0x0E03   THAI CHARACTER KHO KHUAT */
   U_ThaiCharacterKhoKhwai,               /* 0xA4   0x0E04   THAI CHARACTER KHO KHWAI */
   U_ThaiCharacterKhoKhon,                /* 0xA5   0x0E05   THAI CHARACTER KHO KHON */
   U_ThaiCharacterKhoRakhang,             /* 0xA6   0x0E06   THAI CHARACTER KHO RAKHANG */
   U_ThaiCharacterNgoNgu,                 /* 0xA7   0x0E07   THAI CHARACTER NGO NGU */
   U_ThaiCharacterChoChan,                /* 0xA8   0x0E08   THAI CHARACTER CHO CHAN */
   U_ThaiCharacterChoChing,               /* 0xA9   0x0E09   THAI CHARACTER CHO CHING */
   U_ThaiCharacterChoChang,               /* 0xAA   0x0E0A   THAI CHARACTER CHO CHANG */
   U_ThaiCharacterSoSo,                   /* 0xAB   0x0E0B   THAI CHARACTER SO SO */
   U_ThaiCharacterChoChoe,                /* 0xAC   0x0E0C   THAI CHARACTER CHO CHOE */
   U_ThaiCharacterYoYing,                 /* 0xAD   0x0E0D   THAI CHARACTER YO YING */
   U_ThaiCharacterDoChada,                /* 0xAE   0x0E0E   THAI CHARACTER DO CHADA */
   U_ThaiCharacterToPatak,                /* 0xAF   0x0E0F   THAI CHARACTER TO PATAK */
   U_ThaiCharacterThoThan,                /* 0xB0   0x0E10   THAI CHARACTER THO THAN */
   U_ThaiCharacterThoNangmontho,          /* 0xB1   0x0E11   THAI CHARACTER THO NANGMONTHO */
   U_ThaiCharacterThoPhuthao,             /* 0xB2   0x0E12   THAI CHARACTER THO PHUTHAO */
   U_ThaiCharacterNoNen,                  /* 0xB3   0x0E13   THAI CHARACTER NO NEN */
   U_ThaiCharacterDoDek,                  /* 0xB4   0x0E14   THAI CHARACTER DO DEK */
   U_ThaiCharacterToTao,                  /* 0xB5   0x0E15   THAI CHARACTER TO TAO */
   U_ThaiCharacterThoThung,               /* 0xB6   0x0E16   THAI CHARACTER THO THUNG */
   U_ThaiCharacterThoThahan,              /* 0xB7   0x0E17   THAI CHARACTER THO THAHAN */
   U_ThaiCharacterThoThong,               /* 0xB8   0x0E18   THAI CHARACTER THO THONG */
   U_ThaiCharacterNoNu,                   /* 0xB9   0x0E19   THAI CHARACTER NO NU */
   U_ThaiCharacterBoBaimai,               /* 0xBA   0x0E1A   THAI CHARACTER BO BAIMAI */
   U_ThaiCharacterPoPla,                  /* 0xBB   0x0E1B   THAI CHARACTER PO PLA */
   U_ThaiCharacterPhoPhung,               /* 0xBC   0x0E1C   THAI CHARACTER PHO PHUNG */
   U_ThaiCharacterFoFa,                   /* 0xBD   0x0E1D   THAI CHARACTER FO FA */
   U_ThaiCharacterPhoPhan,                /* 0xBE   0x0E1E   THAI CHARACTER PHO PHAN */
   U_ThaiCharacterFoFan,                  /* 0xBF   0x0E1F   THAI CHARACTER FO FAN */
   U_ThaiCharacterPhoSamphao,             /* 0xC0   0x0E20   THAI CHARACTER PHO SAMPHAO */
   U_ThaiCharacterMoMa,                   /* 0xC1   0x0E21   THAI CHARACTER MO MA */
   U_ThaiCharacterYoYak,                  /* 0xC2   0x0E22   THAI CHARACTER YO YAK */
   U_ThaiCharacterRoRua,                  /* 0xC3   0x0E23   THAI CHARACTER RO RUA */
   U_ThaiCharacterRu,                     /* 0xC4   0x0E24   THAI CHARACTER RU */
   U_ThaiCharacterLoLing,                 /* 0xC5   0x0E25   THAI CHARACTER LO LING */
   U_ThaiCharacterLu,                     /* 0xC6   0x0E26   THAI CHARACTER LU */
   U_ThaiCharacterWoWaen,                 /* 0xC7   0x0E27   THAI CHARACTER WO WAEN */
   U_ThaiCharacterSoSala,                 /* 0xC8   0x0E28   THAI CHARACTER SO SALA */
   U_ThaiCharacterSoRusi,                 /* 0xC9   0x0E29   THAI CHARACTER SO RUSI */
   U_ThaiCharacterSoSua,                  /* 0xCA   0x0E2A   THAI CHARACTER SO SUA */
   U_ThaiCharacterHoHip,                  /* 0xCB   0x0E2B   THAI CHARACTER HO HIP */
   U_ThaiCharacterLoChula,                /* 0xCC   0x0E2C   THAI CHARACTER LO CHULA */
   U_ThaiCharacterOAng,                   /* 0xCD   0x0E2D   THAI CHARACTER O ANG */
   U_ThaiCharacterHoNokhuk,               /* 0xCE   0x0E2E   THAI CHARACTER HO NOKHUK */
   U_ThaiCharacterPaiyannoi,              /* 0xCF   0x0E2F   THAI CHARACTER PAIYANNOI */
   U_ThaiCharacterSaraA,                  /* 0xD0   0x0E30   THAI CHARACTER SARA A */
   U_ThaiCharacterMaiHanAkat,             /* 0xD1   0x0E31   THAI CHARACTER MAI HAN-AKAT */
   U_ThaiCharacterSaraAa,                 /* 0xD2   0x0E32   THAI CHARACTER SARA AA */
   U_ThaiCharacterSaraAm,                 /* 0xD3   0x0E33   THAI CHARACTER SARA AM */
   U_ThaiCharacterSaraI,                  /* 0xD4   0x0E34   THAI CHARACTER SARA I */
   U_ThaiCharacterSaraIi,                 /* 0xD5   0x0E35   THAI CHARACTER SARA II */
   U_ThaiCharacterSaraUe,                 /* 0xD6   0x0E36   THAI CHARACTER SARA UE */
   U_ThaiCharacterSaraUee,                /* 0xD7   0x0E37   THAI CHARACTER SARA UEE */
   U_ThaiCharacterSaraU,                  /* 0xD8   0x0E38   THAI CHARACTER SARA U */
   U_ThaiCharacterSaraUu,                 /* 0xD9   0x0E39   THAI CHARACTER SARA UU */
   U_ThaiCharacterPhinthu,                /* 0xDA   0x0E3A   THAI CHARACTER PHINTHU */
   U_NIL,                                 /* 0xDB            <undefined> */
   U_NIL,                                 /* 0xDC            <undefined> */
   U_NIL,                                 /* 0xDD            <undefined> */
   U_NIL,                                 /* 0xDE            <undefined> */
   U_ThaiCurrencySymbolBaht,              /* 0xDF   0x0E3F   THAI CURRENCY SYMBOL BAHT */
   U_ThaiCharacterSaraE,                  /* 0xE0   0x0E40   THAI CHARACTER SARA E */
   U_ThaiCharacterSaraAe,                 /* 0xE1   0x0E41   THAI CHARACTER SARA AE */
   U_ThaiCharacterSaraO,                  /* 0xE2   0x0E42   THAI CHARACTER SARA O */
   U_ThaiCharacterSaraAiMaimuan,          /* 0xE3   0x0E43   THAI CHARACTER SARA AI MAIMUAN */
   U_ThaiCharacterSaraAiMaimalai,         /* 0xE4   0x0E44   THAI CHARACTER SARA AI MAIMALAI */
   U_ThaiCharacterLakkhangyao,            /* 0xE5   0x0E45   THAI CHARACTER LAKKHANGYAO */
   U_ThaiCharacterMaiyamok,               /* 0xE6   0x0E46   THAI CHARACTER MAIYAMOK */
   U_ThaiCharacterMaitaikhu,              /* 0xE7   0x0E47   THAI CHARACTER MAITAIKHU */
   U_ThaiCharacterMaiEk,                  /* 0xE8   0x0E48   THAI CHARACTER MAI EK */
   U_ThaiCharacterMaiTho,                 /* 0xE9   0x0E49   THAI CHARACTER MAI THO */
   U_ThaiCharacterMaiTri,                 /* 0xEA   0x0E4A   THAI CHARACTER MAI TRI */
   U_ThaiCharacterMaiChattawa,            /* 0xEB   0x0E4B   THAI CHARACTER MAI CHATTAWA */
   U_ThaiCharacterThanthakhat,            /* 0xEC   0x0E4C   THAI CHARACTER THANTHAKHAT */
   U_ThaiCharacterNikhahit,               /* 0xED   0x0E4D   THAI CHARACTER NIKHAHIT */
   U_ThaiCharacterYamakkan,               /* 0xEE   0x0E4E   THAI CHARACTER YAMAKKAN */
   U_ThaiCharacterFongman,                /* 0xEF   0x0E4F   THAI CHARACTER FONGMAN */
   U_ThaiDigitZero,                       /* 0xF0   0x0E50   THAI DIGIT ZERO */
   U_ThaiDigitOne,                        /* 0xF1   0x0E51   THAI DIGIT ONE */
   U_ThaiDigitTwo,                        /* 0xF2   0x0E52   THAI DIGIT TWO */
   U_ThaiDigitThree,                      /* 0xF3   0x0E53   THAI DIGIT THREE */
   U_ThaiDigitFour,                       /* 0xF4   0x0E54   THAI DIGIT FOUR */
   U_ThaiDigitFive,                       /* 0xF5   0x0E55   THAI DIGIT FIVE */
   U_ThaiDigitSix,                        /* 0xF6   0x0E56   THAI DIGIT SIX */
   U_ThaiDigitSeven,                      /* 0xF7   0x0E57   THAI DIGIT SEVEN */
   U_ThaiDigitEight,                      /* 0xF8   0x0E58   THAI DIGIT EIGHT */
   U_ThaiDigitNine,                       /* 0xF9   0x0E59   THAI DIGIT NINE */
   U_ThaiCharacterAngkhankhu,             /* 0xFA   0x0E5A   THAI CHARACTER ANGKHANKHU */
   U_ThaiCharacterKhomut,                 /* 0xFB   0x0E5B   THAI CHARACTER KHOMUT */
   U_NIL,                                 /* 0xFC            <undefined> */
   U_NIL,                                 /* 0xFD            <undefined> */
   U_NIL,                                 /* 0xFE            <undefined> */
   U_NIL                                  /* 0xFF            <undefined> */
};





/******************************************************************************
*
*  CODE_THAI_lig[]:
*     list of ligatures:
*
*  CODE_THAI_lig[0] is the original ligature character
*  CODE_THAI_lig[1] + CODE_THAI_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_THAI_lig[][3] =       /* CODE_THAI character ligatures */
{
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_THAI sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_THAI[] =         /* CODE_THAI */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_ThaiCharacterKoKai,                  /* 0xA1   0x0E01   THAI CHARACTER KO KAI */
   U_ThaiCharacterKhoKhai,                /* 0xA2   0x0E02   THAI CHARACTER KHO KHAI */
   U_ThaiCharacterKhoKhuat,               /* 0xA3   0x0E03   THAI CHARACTER KHO KHUAT */
   U_ThaiCharacterKhoKhwai,               /* 0xA4   0x0E04   THAI CHARACTER KHO KHWAI */
   U_ThaiCharacterKhoKhon,                /* 0xA5   0x0E05   THAI CHARACTER KHO KHON */
   U_ThaiCharacterKhoRakhang,             /* 0xA6   0x0E06   THAI CHARACTER KHO RAKHANG */
   U_ThaiCharacterNgoNgu,                 /* 0xA7   0x0E07   THAI CHARACTER NGO NGU */
   U_ThaiCharacterChoChan,                /* 0xA8   0x0E08   THAI CHARACTER CHO CHAN */
   U_ThaiCharacterChoChing,               /* 0xA9   0x0E09   THAI CHARACTER CHO CHING */
   U_ThaiCharacterChoChang,               /* 0xAA   0x0E0A   THAI CHARACTER CHO CHANG */
   U_ThaiCharacterSoSo,                   /* 0xAB   0x0E0B   THAI CHARACTER SO SO */
   U_ThaiCharacterChoChoe,                /* 0xAC   0x0E0C   THAI CHARACTER CHO CHOE */
   U_ThaiCharacterYoYing,                 /* 0xAD   0x0E0D   THAI CHARACTER YO YING */
   U_ThaiCharacterDoChada,                /* 0xAE   0x0E0E   THAI CHARACTER DO CHADA */
   U_ThaiCharacterToPatak,                /* 0xAF   0x0E0F   THAI CHARACTER TO PATAK */
   U_ThaiCharacterThoThan,                /* 0xB0   0x0E10   THAI CHARACTER THO THAN */
   U_ThaiCharacterThoNangmontho,          /* 0xB1   0x0E11   THAI CHARACTER THO NANGMONTHO */
   U_ThaiCharacterThoPhuthao,             /* 0xB2   0x0E12   THAI CHARACTER THO PHUTHAO */
   U_ThaiCharacterNoNen,                  /* 0xB3   0x0E13   THAI CHARACTER NO NEN */
   U_ThaiCharacterDoDek,                  /* 0xB4   0x0E14   THAI CHARACTER DO DEK */
   U_ThaiCharacterToTao,                  /* 0xB5   0x0E15   THAI CHARACTER TO TAO */
   U_ThaiCharacterThoThung,               /* 0xB6   0x0E16   THAI CHARACTER THO THUNG */
   U_ThaiCharacterThoThahan,              /* 0xB7   0x0E17   THAI CHARACTER THO THAHAN */
   U_ThaiCharacterThoThong,               /* 0xB8   0x0E18   THAI CHARACTER THO THONG */
   U_ThaiCharacterNoNu,                   /* 0xB9   0x0E19   THAI CHARACTER NO NU */
   U_ThaiCharacterBoBaimai,               /* 0xBA   0x0E1A   THAI CHARACTER BO BAIMAI */
   U_ThaiCharacterPoPla,                  /* 0xBB   0x0E1B   THAI CHARACTER PO PLA */
   U_ThaiCharacterPhoPhung,               /* 0xBC   0x0E1C   THAI CHARACTER PHO PHUNG */
   U_ThaiCharacterFoFa,                   /* 0xBD   0x0E1D   THAI CHARACTER FO FA */
   U_ThaiCharacterPhoPhan,                /* 0xBE   0x0E1E   THAI CHARACTER PHO PHAN */
   U_ThaiCharacterFoFan,                  /* 0xBF   0x0E1F   THAI CHARACTER FO FAN */
   U_ThaiCharacterPhoSamphao,             /* 0xC0   0x0E20   THAI CHARACTER PHO SAMPHAO */
   U_ThaiCharacterMoMa,                   /* 0xC1   0x0E21   THAI CHARACTER MO MA */
   U_ThaiCharacterYoYak,                  /* 0xC2   0x0E22   THAI CHARACTER YO YAK */
   U_ThaiCharacterRoRua,                  /* 0xC3   0x0E23   THAI CHARACTER RO RUA */
   U_ThaiCharacterRu,                     /* 0xC4   0x0E24   THAI CHARACTER RU */
   U_ThaiCharacterLoLing,                 /* 0xC5   0x0E25   THAI CHARACTER LO LING */
   U_ThaiCharacterLu,                     /* 0xC6   0x0E26   THAI CHARACTER LU */
   U_ThaiCharacterWoWaen,                 /* 0xC7   0x0E27   THAI CHARACTER WO WAEN */
   U_ThaiCharacterSoSala,                 /* 0xC8   0x0E28   THAI CHARACTER SO SALA */
   U_ThaiCharacterSoRusi,                 /* 0xC9   0x0E29   THAI CHARACTER SO RUSI */
   U_ThaiCharacterSoSua,                  /* 0xCA   0x0E2A   THAI CHARACTER SO SUA */
   U_ThaiCharacterHoHip,                  /* 0xCB   0x0E2B   THAI CHARACTER HO HIP */
   U_ThaiCharacterLoChula,                /* 0xCC   0x0E2C   THAI CHARACTER LO CHULA */
   U_ThaiCharacterOAng,                   /* 0xCD   0x0E2D   THAI CHARACTER O ANG */
   U_ThaiCharacterHoNokhuk,               /* 0xCE   0x0E2E   THAI CHARACTER HO NOKHUK */
   U_ThaiCharacterPaiyannoi,              /* 0xCF   0x0E2F   THAI CHARACTER PAIYANNOI */
   U_ThaiCharacterSaraA,                  /* 0xD0   0x0E30   THAI CHARACTER SARA A */
   U_ThaiCharacterMaiHanAkat,             /* 0xD1   0x0E31   THAI CHARACTER MAI HAN-AKAT */
   U_ThaiCharacterSaraAa,                 /* 0xD2   0x0E32   THAI CHARACTER SARA AA */
   U_ThaiCharacterSaraAm,                 /* 0xD3   0x0E33   THAI CHARACTER SARA AM */
   U_ThaiCharacterSaraI,                  /* 0xD4   0x0E34   THAI CHARACTER SARA I */
   U_ThaiCharacterSaraIi,                 /* 0xD5   0x0E35   THAI CHARACTER SARA II */
   U_ThaiCharacterSaraUe,                 /* 0xD6   0x0E36   THAI CHARACTER SARA UE */
   U_ThaiCharacterSaraUee,                /* 0xD7   0x0E37   THAI CHARACTER SARA UEE */
   U_ThaiCharacterSaraU,                  /* 0xD8   0x0E38   THAI CHARACTER SARA U */
   U_ThaiCharacterSaraUu,                 /* 0xD9   0x0E39   THAI CHARACTER SARA UU */
   U_ThaiCharacterPhinthu,                /* 0xDA   0x0E3A   THAI CHARACTER PHINTHU */
   U_NIL,                                 /* 0xDB            <undefined> */
   U_NIL,                                 /* 0xDC            <undefined> */
   U_NIL,                                 /* 0xDD            <undefined> */
   U_NIL,                                 /* 0xDE            <undefined> */
   U_ThaiCurrencySymbolBaht,              /* 0xDF   0x0E3F   THAI CURRENCY SYMBOL BAHT */
   U_ThaiCharacterSaraE,                  /* 0xE0   0x0E40   THAI CHARACTER SARA E */
   U_ThaiCharacterSaraAe,                 /* 0xE1   0x0E41   THAI CHARACTER SARA AE */
   U_ThaiCharacterSaraO,                  /* 0xE2   0x0E42   THAI CHARACTER SARA O */
   U_ThaiCharacterSaraAiMaimuan,          /* 0xE3   0x0E43   THAI CHARACTER SARA AI MAIMUAN */
   U_ThaiCharacterSaraAiMaimalai,         /* 0xE4   0x0E44   THAI CHARACTER SARA AI MAIMALAI */
   U_ThaiCharacterLakkhangyao,            /* 0xE5   0x0E45   THAI CHARACTER LAKKHANGYAO */
   U_ThaiCharacterMaiyamok,               /* 0xE6   0x0E46   THAI CHARACTER MAIYAMOK */
   U_ThaiCharacterMaitaikhu,              /* 0xE7   0x0E47   THAI CHARACTER MAITAIKHU */
   U_ThaiCharacterMaiEk,                  /* 0xE8   0x0E48   THAI CHARACTER MAI EK */
   U_ThaiCharacterMaiTho,                 /* 0xE9   0x0E49   THAI CHARACTER MAI THO */
   U_ThaiCharacterMaiTri,                 /* 0xEA   0x0E4A   THAI CHARACTER MAI TRI */
   U_ThaiCharacterMaiChattawa,            /* 0xEB   0x0E4B   THAI CHARACTER MAI CHATTAWA */
   U_ThaiCharacterThanthakhat,            /* 0xEC   0x0E4C   THAI CHARACTER THANTHAKHAT */
   U_ThaiCharacterNikhahit,               /* 0xED   0x0E4D   THAI CHARACTER NIKHAHIT */
   U_ThaiCharacterYamakkan,               /* 0xEE   0x0E4E   THAI CHARACTER YAMAKKAN */
   U_ThaiCharacterFongman,                /* 0xEF   0x0E4F   THAI CHARACTER FONGMAN */
   U_ThaiDigitZero,                       /* 0xF0   0x0E50   THAI DIGIT ZERO */
   U_ThaiDigitOne,                        /* 0xF1   0x0E51   THAI DIGIT ONE */
   U_ThaiDigitTwo,                        /* 0xF2   0x0E52   THAI DIGIT TWO */
   U_ThaiDigitThree,                      /* 0xF3   0x0E53   THAI DIGIT THREE */
   U_ThaiDigitFour,                       /* 0xF4   0x0E54   THAI DIGIT FOUR */
   U_ThaiDigitFive,                       /* 0xF5   0x0E55   THAI DIGIT FIVE */
   U_ThaiDigitSix,                        /* 0xF6   0x0E56   THAI DIGIT SIX */
   U_ThaiDigitSeven,                      /* 0xF7   0x0E57   THAI DIGIT SEVEN */
   U_ThaiDigitEight,                      /* 0xF8   0x0E58   THAI DIGIT EIGHT */
   U_ThaiDigitNine,                       /* 0xF9   0x0E59   THAI DIGIT NINE */
   U_ThaiCharacterAngkhankhu,             /* 0xFA   0x0E5A   THAI CHARACTER ANGKHANKHU */
   U_ThaiCharacterKhomut,                 /* 0xFB   0x0E5B   THAI CHARACTER KHOMUT */
   U_NIL,                                 /* 0xFC            <undefined> */
   U_NIL,                                 /* 0xFD            <undefined> */
   U_NIL,                                 /* 0xFE            <undefined> */
   U_NIL                                  /* 0xFF            <undefined> */
};










/******************************************************************************
*
*  u_CODE_BALTIC[]:
*     Unicode named codepage for ISO encoding Latin-7 (iso-8859-13) "Baltic"
*
*  Name:             ISO/IEC 8859-13:1998  to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_BALTIC[] =          /* CODE_BALTIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_RightDoubleQuotationMark,            /* 0xA1   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_DoubleLow9QuotationMark,             /* 0xA5   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinCapitalLetterOSlash,            /* 0xA8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_LatinCapitalLetterRWithCedilla,      /* 0xAA   0x0156   LATIN CAPITAL LETTER R WITH CEDILLA */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_LatinCapitalLigatureAE,              /* 0xAF   0x00C6   LATIN CAPITAL LETTER AE */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_LeftDoubleQuotationMark,             /* 0xB4   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_LatinSmallLetterOSlash,              /* 0xB8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_LatinSmallLetterRWithCedilla,        /* 0xBA   0x0157   LATIN SMALL LETTER R WITH CEDILLA */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_LatinSmallLigatureAE,                /* 0xBF   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterAWithOgonek,       /* 0xC0   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinCapitalLetterIWithOgonek,       /* 0xC1   0x012E   LATIN CAPITAL LETTER I WITH OGONEK */
   U_LatinCapitalLetterAWithMacron,       /* 0xC2   0x0100   LATIN CAPITAL LETTER A WITH MACRON */
   U_LatinCapitalLetterCWithAcute,        /* 0xC3   0x0106   LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterEWithOgonek,       /* 0xC6   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterEWithMacron,       /* 0xC7   0x0112   LATIN CAPITAL LETTER E WITH MACRON */
   U_LatinCapitalLetterCWithCaron,        /* 0xC8   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterZWithAcute,        /* 0xCA   0x0179   LATIN CAPITAL LETTER Z WITH ACUTE */
   U_LatinCapitalLetterEWithDotAbove,     /* 0xCB   0x0116   LATIN CAPITAL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterGWithCedilla,      /* 0xCC   0x0122   LATIN CAPITAL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterKWithCedilla,      /* 0xCD   0x0136   LATIN CAPITAL LETTER K WITH CEDILLA */
   U_LatinCapitalLetterIWithMacron,       /* 0xCE   0x012A   LATIN CAPITAL LETTER I WITH MACRON */
   U_LatinCapitalLetterLWithCedilla,      /* 0xCF   0x013B   LATIN CAPITAL LETTER L WITH CEDILLA */
   U_LatinCapitalLetterSWithCaron,        /* 0xD0   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LatinCapitalLetterNWithAcute,        /* 0xD1   0x0143   LATIN CAPITAL LETTER N WITH ACUTE */
   U_LatinCapitalLetterNWithCedilla,      /* 0xD2   0x0145   LATIN CAPITAL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithMacron,       /* 0xD4   0x014C   LATIN CAPITAL LETTER O WITH MACRON */
   U_LatinCapitalLetterOWithTilde,        /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterUWithOgonek,       /* 0xD8   0x0172   LATIN CAPITAL LETTER U WITH OGONEK */
   U_LatinCapitalLetterLWithStroke,       /* 0xD9   0x0141   LATIN CAPITAL LETTER L WITH STROKE */
   U_LatinCapitalLetterSWithAcute,        /* 0xDA   0x015A   LATIN CAPITAL LETTER S WITH ACUTE */
   U_LatinCapitalLetterUWithMacron,       /* 0xDB   0x016A   LATIN CAPITAL LETTER U WITH MACRON */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterZWithDotAbove,     /* 0xDD   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterZWithCaron,        /* 0xDE   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S (German) */
   U_LatinSmallLetterAWithOgonek,         /* 0xE0   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_LatinSmallLetterIWithOgonek,         /* 0xE1   0x012F   LATIN SMALL LETTER I WITH OGONEK */
   U_LatinSmallLetterAWithMacron,         /* 0xE2   0x0101   LATIN SMALL LETTER A WITH MACRON */
   U_LatinSmallLetterCWithAcute,          /* 0xE3   0x0107   LATIN SMALL LETTER C WITH ACUTE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithRingAbove,      /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterEWithOgonek,         /* 0xE6   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinSmallLetterEWithMacron,         /* 0xE7   0x0113   LATIN SMALL LETTER E WITH MACRON */
   U_LatinSmallLetterCWithCaron,          /* 0xE8   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterZWithAcute,          /* 0xEA   0x017A   LATIN SMALL LETTER Z WITH ACUTE */
   U_LatinSmallLetterEWithDotAbove,       /* 0xEB   0x0117   LATIN SMALL LETTER E WITH DOT ABOVE */
   U_LatinSmallLetterGWithCedilla,        /* 0xEC   0x0123   LATIN SMALL LETTER G WITH CEDILLA */
   U_LatinSmallLetterKWithCedilla,        /* 0xED   0x0137   LATIN SMALL LETTER K WITH CEDILLA */
   U_LatinSmallLetterIWithMacron,         /* 0xEE   0x012B   LATIN SMALL LETTER I WITH MACRON */
   U_LatinSmallLetterLWithCedilla,        /* 0xEF   0x013C   LATIN SMALL LETTER L WITH CEDILLA */
   U_LatinSmallLetterSWithCaron,          /* 0xF0   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinSmallLetterNWithAcute,          /* 0xF1   0x0144   LATIN SMALL LETTER N WITH ACUTE */
   U_LatinSmallLetterNWithCedilla,        /* 0xF2   0x0146   LATIN SMALL LETTER N WITH CEDILLA */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithMacron,         /* 0xF4   0x014D   LATIN SMALL LETTER O WITH MACRON */
   U_LatinSmallLetterOWithTilde,          /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinSmallLetterUWithOgonek,         /* 0xF8   0x0173   LATIN SMALL LETTER U WITH OGONEK */
   U_LatinSmallLetterLWithStroke,         /* 0xF9   0x0142   LATIN SMALL LETTER L WITH STROKE */
   U_LatinSmallLetterSWithAcute,          /* 0xFA   0x015B   LATIN SMALL LETTER S WITH ACUTE */
   U_LatinSmallLetterUWithMacron,         /* 0xFB   0x016B   LATIN SMALL LETTER U WITH MACRON */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterZWithDotAbove,       /* 0xFD   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinSmallLetterZWithCaron,          /* 0xFE   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_RightSingleQuotationMark             /* 0xFF   0x2019   RIGHT SINGLE QUOTATION MARK */
};





/******************************************************************************
*
*  CODE_BALTIC_lig[]:
*     list of ligatures:
*
*  CODE_BALTIC_lig[0] is the original ligature character
*  CODE_BALTIC_lig[1] + CODE_BALTIC_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_BALTIC_lig[][3] =     /* CODE_BALTIC character ligatures */
{
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xA8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xAF   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xB8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xBF   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S (German) */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterAWithRingAbove,    U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */

   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_BALTIC sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_BALTIC[] =       /* CODE_BALTIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_RightDoubleQuotationMark,            /* 0xA1   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_DoubleLow9QuotationMark,             /* 0xA5   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinCapitalLetterO,                 /* 0xA8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_LatinCapitalLetterR,                 /* 0xAA   0x0156   LATIN CAPITAL LETTER R WITH CEDILLA */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_LatinCapitalLetterA,                 /* 0xAF   0x00C6   LATIN CAPITAL LETTER AE */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_LeftDoubleQuotationMark,             /* 0xB4   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_LatinCapitalLetterO,                 /* 0xB8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_LatinCapitalLetterR,                 /* 0xBA   0x0157   LATIN SMALL LETTER R WITH CEDILLA */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_LatinCapitalLetterA,                 /* 0xBF   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterA,                 /* 0xC0   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinCapitalLetterI,                 /* 0xC1   0x012E   LATIN CAPITAL LETTER I WITH OGONEK */
   U_LatinCapitalLetterA,                 /* 0xC2   0x0100   LATIN CAPITAL LETTER A WITH MACRON */
   U_LatinCapitalLetterC,                 /* 0xC3   0x0106   LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterE,                 /* 0xC6   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xC7   0x0112   LATIN CAPITAL LETTER E WITH MACRON */
   U_LatinCapitalLetterC,                 /* 0xC8   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterZ,                 /* 0xCA   0x0179   LATIN CAPITAL LETTER Z WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCB   0x0116   LATIN CAPITAL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterG,                 /* 0xCC   0x0122   LATIN CAPITAL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterK,                 /* 0xCD   0x0136   LATIN CAPITAL LETTER K WITH CEDILLA */
   U_LatinCapitalLetterI,                 /* 0xCE   0x012A   LATIN CAPITAL LETTER I WITH MACRON */
   U_LatinCapitalLetterL,                 /* 0xCF   0x013B   LATIN CAPITAL LETTER L WITH CEDILLA */
   U_LatinCapitalLetterS,                 /* 0xD0   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LatinCapitalLetterN,                 /* 0xD1   0x0143   LATIN CAPITAL LETTER N WITH ACUTE */
   U_LatinCapitalLetterN,                 /* 0xD2   0x0145   LATIN CAPITAL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x014C   LATIN CAPITAL LETTER O WITH MACRON */
   U_LatinCapitalLetterO,                 /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterU,                 /* 0xD8   0x0172   LATIN CAPITAL LETTER U WITH OGONEK */
   U_LatinCapitalLetterL,                 /* 0xD9   0x0141   LATIN CAPITAL LETTER L WITH STROKE */
   U_LatinCapitalLetterS,                 /* 0xDA   0x015A   LATIN CAPITAL LETTER S WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x016A   LATIN CAPITAL LETTER U WITH MACRON */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterZ,                 /* 0xDD   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterZ,                 /* 0xDE   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S (German) */
   U_LatinCapitalLetterA,                 /* 0xE0   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_LatinCapitalLetterI,                 /* 0xE1   0x012F   LATIN SMALL LETTER I WITH OGONEK */
   U_LatinCapitalLetterA,                 /* 0xE2   0x0101   LATIN SMALL LETTER A WITH MACRON */
   U_LatinCapitalLetterC,                 /* 0xE3   0x0107   LATIN SMALL LETTER C WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterE,                 /* 0xE6   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xE7   0x0113   LATIN SMALL LETTER E WITH MACRON */
   U_LatinCapitalLetterC,                 /* 0xE8   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterZ,                 /* 0xEA   0x017A   LATIN SMALL LETTER Z WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEB   0x0117   LATIN SMALL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterG,                 /* 0xEC   0x0123   LATIN SMALL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterK,                 /* 0xED   0x0137   LATIN SMALL LETTER K WITH CEDILLA */
   U_LatinCapitalLetterI,                 /* 0xEE   0x012B   LATIN SMALL LETTER I WITH MACRON */
   U_LatinCapitalLetterL,                 /* 0xEF   0x013C   LATIN SMALL LETTER L WITH CEDILLA */
   U_LatinCapitalLetterS,                 /* 0xF0   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinCapitalLetterN,                 /* 0xF1   0x0144   LATIN SMALL LETTER N WITH ACUTE */
   U_LatinCapitalLetterN,                 /* 0xF2   0x0146   LATIN SMALL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x014D   LATIN SMALL LETTER O WITH MACRON */
   U_LatinCapitalLetterO,                 /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinCapitalLetterU,                 /* 0xF8   0x0173   LATIN SMALL LETTER U WITH OGONEK */
   U_LatinCapitalLetterL,                 /* 0xF9   0x0142   LATIN SMALL LETTER L WITH STROKE */
   U_LatinCapitalLetterS,                 /* 0xFA   0x015B   LATIN SMALL LETTER S WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x016B   LATIN SMALL LETTER U WITH MACRON */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterZ,                 /* 0xFD   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterZ,                 /* 0xFE   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_RightSingleQuotationMark             /* 0xFF   0x2019   RIGHT SINGLE QUOTATION MARK */
};










/******************************************************************************
*
*  u_CODE_CELTIC[]:
*     Unicode named codepage for ISO encoding Latin-8 (iso-8859-14) "Celtic"
*
*  Name:             ISO/IEC 8859-14:1998 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Markus Kuhn <http://www.cl.cam.ac.uk/~mgk25/>
*                    Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_CELTIC[] =          /* CODE_CELTIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterBWithDotAbove,     /* 0xA1   0x1E02   LATIN CAPITAL LETTER B WITH DOT ABOVE */
   U_LatinSmallLetterBWithDotAbove,       /* 0xA2   0x1E03   LATIN SMALL LETTER B WITH DOT ABOVE */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_LatinCapitalLetterCWithDotAbove,     /* 0xA4   0x010A   LATIN CAPITAL LETTER C WITH DOT ABOVE */
   U_LatinSmallLetterCWithDotAbove,       /* 0xA5   0x010B   LATIN SMALL LETTER C WITH DOT ABOVE */
   U_LatinCapitalLetterDWithDotAbove,     /* 0xA6   0x1E0A   LATIN CAPITAL LETTER D WITH DOT ABOVE */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinCapitalLetterWWithGrave,        /* 0xA8   0x1E80   LATIN CAPITAL LETTER W WITH GRAVE */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_LatinCapitalLetterWWithAcute,        /* 0xAA   0x1E82   LATIN CAPITAL LETTER W WITH ACUTE */
   U_LatinSmallLetterDWithDotAbove,       /* 0xAB   0x1E0B   LATIN SMALL LETTER D WITH DOT ABOVE */
   U_LatinCapitalLetterYWithGrave,        /* 0xAC   0x1EF2   LATIN CAPITAL LETTER Y WITH GRAVE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0xAF   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_LatinCapitalLetterFWithDotAbove,     /* 0xB0   0x1E1E   LATIN CAPITAL LETTER F WITH DOT ABOVE */
   U_LatinSmallLetterFWithDotAbove,       /* 0xB1   0x1E1F   LATIN SMALL LETTER F WITH DOT ABOVE */
   U_LatinCapitalLetterGWithDotAbove,     /* 0xB2   0x0120   LATIN CAPITAL LETTER G WITH DOT ABOVE */
   U_LatinSmallLetterGWithDotAbove,       /* 0xB3   0x0121   LATIN SMALL LETTER G WITH DOT ABOVE */
   U_LatinCapitalLetterMWithDotAbove,     /* 0xB4   0x1E40   LATIN CAPITAL LETTER M WITH DOT ABOVE */
   U_LatinSmallLetterMWithDotAbove,       /* 0xB5   0x1E41   LATIN SMALL LETTER M WITH DOT ABOVE */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_LatinCapitalLetterPWithDotAbove,     /* 0xB7   0x1E56   LATIN CAPITAL LETTER P WITH DOT ABOVE */
   U_LatinSmallLetterWWithGrave,          /* 0xB8   0x1E81   LATIN SMALL LETTER W WITH GRAVE */
   U_LatinSmallLetterPWithDotAbove,       /* 0xB9   0x1E57   LATIN SMALL LETTER P WITH DOT ABOVE */
   U_LatinSmallLetterWWithAcute,          /* 0xBA   0x1E83   LATIN SMALL LETTER W WITH ACUTE */
   U_LatinCapitalLetterSWithDotAbove,     /* 0xBB   0x1E60   LATIN CAPITAL LETTER S WITH DOT ABOVE */
   U_LatinSmallLetterYWithGrave,          /* 0xBC   0x1EF3   LATIN SMALL LETTER Y WITH GRAVE */
   U_LatinCapitalLetterWWithDiaeresis,    /* 0xBD   0x1E84   LATIN CAPITAL LETTER W WITH DIAERESIS */
   U_LatinSmallLetterWWithDiaeresis,      /* 0xBE   0x1E85   LATIN SMALL LETTER W WITH DIAERESIS */
   U_LatinSmallLetterSWithDotAbove,       /* 0xBF   0x1E61   LATIN SMALL LETTER S WITH DOT ABOVE */
   U_LatinCapitalLetterAWithGrave,        /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithTilde,        /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLigatureAE,              /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterEWithGrave,        /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterIWithGrave,        /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterWWithCircumflex,   /* 0xD0   0x0174   LATIN CAPITAL LETTER W WITH CIRCUMFLEX */
   U_LatinCapitalLetterNWithTilde,        /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterOWithGrave,        /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithTilde,        /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterTWithDotAbove,     /* 0xD7   0x1E6A   LATIN CAPITAL LETTER T WITH DOT ABOVE */
   U_LatinCapitalLetterOSlash,            /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterUWithGrave,        /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterYWithCircumflex,   /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterYWithCircumflex,   /* 0xDE   0x0176   LATIN CAPITAL LETTER Y WITH CIRCUMFLEX */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterAWithGrave,          /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithTilde,          /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithRingAbove,      /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLigatureAE,                /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithGrave,          /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithCircumflex,     /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterIWithGrave,          /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterWWithCircumflex,     /* 0xF0   0x0175   LATIN SMALL LETTER W WITH CIRCUMFLEX */
   U_LatinSmallLetterNWithTilde,          /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinSmallLetterOWithGrave,          /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithTilde,          /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterTWithDotAbove,       /* 0xF7   0x1E6B   LATIN SMALL LETTER T WITH DOT ABOVE */
   U_LatinSmallLetterOSlash,              /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinSmallLetterUWithGrave,          /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterYWithAcute,          /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinSmallLetterYWithCircumflex,     /* 0xFE   0x0177   LATIN SMALL LETTER Y WITH CIRCUMFLEX */
   U_LatinSmallLetterYWithDiaeresis       /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};





/******************************************************************************
*
*  CODE_CELTIC_lig[]:
*     list of ligatures:
*
*  CODE_CELTIC_lig[0] is the original ligature character
*  CODE_CELTIC_lig[1] + CODE_CELTIC_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CELTIC_lig[][3] =     /* CODE_CELTIC character ligatures */
{
   { U_LatinCapitalLetterYWithDiaeresis,  U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0xAF   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   { U_LatinCapitalLetterWWithDiaeresis,  U_LatinCapitalLetterW, U_LatinCapitalLetterE },  /* 0xBD   0x1E84   LATIN CAPITAL LETTER W WITH DIAERESIS */
   { U_LatinSmallLetterWWithDiaeresis,    U_LatinCapitalLetterW, U_LatinCapitalLetterE },  /* 0xBE   0x1E85   LATIN SMALL LETTER W WITH DIAERESIS */
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterAWithRingAbove,    U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterYWithDiaeresis,    U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */

   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CELTIC sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_CELTIC[] =       /* CODE_CELTIC */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterB,                 /* 0xA1   0x1E02   LATIN CAPITAL LETTER B WITH DOT ABOVE */
   U_LatinCapitalLetterB,                 /* 0xA2   0x1E03   LATIN SMALL LETTER B WITH DOT ABOVE */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_LatinCapitalLetterC,                 /* 0xA4   0x010A   LATIN CAPITAL LETTER C WITH DOT ABOVE */
   U_LatinCapitalLetterC,                 /* 0xA5   0x010B   LATIN SMALL LETTER C WITH DOT ABOVE */
   U_LatinCapitalLetterD,                 /* 0xA6   0x1E0A   LATIN CAPITAL LETTER D WITH DOT ABOVE */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinCapitalLetterW,                 /* 0xA8   0x1E80   LATIN CAPITAL LETTER W WITH GRAVE */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_LatinCapitalLetterW,                 /* 0xAA   0x1E82   LATIN CAPITAL LETTER W WITH ACUTE */
   U_LatinCapitalLetterD,                 /* 0xAB   0x1E0B   LATIN SMALL LETTER D WITH DOT ABOVE */
   U_LatinCapitalLetterY,                 /* 0xAC   0x1EF2   LATIN CAPITAL LETTER Y WITH GRAVE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_LatinCapitalLetterY,                 /* 0xAF   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_LatinCapitalLetterF,                 /* 0xB0   0x1E1E   LATIN CAPITAL LETTER F WITH DOT ABOVE */
   U_LatinCapitalLetterF,                 /* 0xB1   0x1E1F   LATIN SMALL LETTER F WITH DOT ABOVE */
   U_LatinCapitalLetterG,                 /* 0xB2   0x0120   LATIN CAPITAL LETTER G WITH DOT ABOVE */
   U_LatinCapitalLetterG,                 /* 0xB3   0x0121   LATIN SMALL LETTER G WITH DOT ABOVE */
   U_LatinCapitalLetterM,                 /* 0xB4   0x1E40   LATIN CAPITAL LETTER M WITH DOT ABOVE */
   U_LatinCapitalLetterM,                 /* 0xB5   0x1E41   LATIN SMALL LETTER M WITH DOT ABOVE */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_LatinCapitalLetterP,                 /* 0xB7   0x1E56   LATIN CAPITAL LETTER P WITH DOT ABOVE */
   U_LatinCapitalLetterW,                 /* 0xB8   0x1E81   LATIN SMALL LETTER W WITH GRAVE */
   U_LatinCapitalLetterP,                 /* 0xB9   0x1E57   LATIN SMALL LETTER P WITH DOT ABOVE */
   U_LatinCapitalLetterW,                 /* 0xBA   0x1E83   LATIN SMALL LETTER W WITH ACUTE */
   U_LatinCapitalLetterS,                 /* 0xBB   0x1E60   LATIN CAPITAL LETTER S WITH DOT ABOVE */
   U_LatinCapitalLetterY,                 /* 0xBC   0x1EF3   LATIN SMALL LETTER Y WITH GRAVE */
   U_LatinCapitalLetterW,                 /* 0xBD   0x1E84   LATIN CAPITAL LETTER W WITH DIAERESIS */
   U_LatinCapitalLetterW,                 /* 0xBE   0x1E85   LATIN SMALL LETTER W WITH DIAERESIS */
   U_LatinCapitalLetterS,                 /* 0xBF   0x1E61   LATIN SMALL LETTER S WITH DOT ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterW,                 /* 0xD0   0x0174   LATIN CAPITAL LETTER W WITH CIRCUMFLEX */
   U_LatinCapitalLetterN,                 /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterT,                 /* 0xD7   0x1E6A   LATIN CAPITAL LETTER T WITH DOT ABOVE */
   U_LatinCapitalLetterO,                 /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterY,                 /* 0xDE   0x0176   LATIN CAPITAL LETTER Y WITH CIRCUMFLEX */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterA,                 /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterW,                 /* 0xF0   0x0175   LATIN SMALL LETTER W WITH CIRCUMFLEX */
   U_LatinCapitalLetterN,                 /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterT,                 /* 0xF7   0x1E6B   LATIN SMALL LETTER T WITH DOT ABOVE */
   U_LatinCapitalLetterO,                 /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterY,                 /* 0xFE   0x0177   LATIN SMALL LETTER Y WITH CIRCUMFLEX */
   U_LatinCapitalLetterY                  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};










/******************************************************************************
*
*  u_CODE_LATIN9[]:
*     Unicode named codepage for ISO encoding Latin-9 (iso-8859-15) "West European"
*
*  Name:             ISO/IEC 8859-15:1999 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             1999 July 27
*  Authors:          Markus Kuhn <http://www.cl.cam.ac.uk/~mgk25/>
*                    Ken Whistler <kenw@sybase.com>
*
******************************************|************************************/

static _UWORD const u_CODE_LATIN9[] =          /* CODE_LATIN9 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_EuroSign,                            /* 0xA4   0x20AC   EURO SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_LatinCapitalLetterSWithCaron,        /* 0xA6   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinSmallLetterSWithCaron,          /* 0xA8   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_FeminineOrdinalIndicator,            /* 0xAA   0x00AA   FEMININE ORDINAL INDICATOR */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_LatinCapitalLetterZWithCaron,        /* 0xB4   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_LatinSmallLetterZWithCaron,          /* 0xB8   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_MasculineOrdinalIndicator,           /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LatinCapitalLigatureOE,              /* 0xBC   0x0152   LATIN CAPITAL LIGATURE OE */
   U_LatinSmallLigatureOE,                /* 0xBD   0x0153   LATIN SMALL LIGATURE OE */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0xBE   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_LatinCapitalLetterAWithGrave,        /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithTilde,        /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLigatureAE,              /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterEWithGrave,        /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterIWithGrave,        /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 0xD0   0x00D0   LATIN CAPITAL LETTER ETH */
   U_LatinCapitalLetterNWithTilde,        /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterOWithGrave,        /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithTilde,        /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterOSlash,            /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterUWithGrave,        /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterYWithAcute,        /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 0xDE   0x00DE   LATIN CAPITAL LETTER THORN */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterAWithGrave,          /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithTilde,          /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithRingAbove,      /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLigatureAE,                /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithGrave,          /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithCircumflex,     /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterIWithGrave,          /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterEth,                 /* 0xF0   0x00F0   LATIN SMALL LETTER ETH */
   U_LatinSmallLetterNWithTilde,          /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinSmallLetterOWithGrave,          /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithTilde,          /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinSmallLetterOSlash,              /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinSmallLetterUWithGrave,          /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterYWithAcute,          /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinSmallLetterThorn,               /* 0xFE   0x00FE   LATIN SMALL LETTER THORN */
   U_LatinSmallLetterYWithDiaeresis       /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};





/******************************************************************************
*
*  CODE_LATIN9_lig[]:
*     list of ligatures:
*
*  CODE_LATIN9_lig[0] is the original ligature character
*  CODE_LATIN9_lig[1] + CODE_LATIN9_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_LATIN9_lig[][3] =     /* CODE_LATIN9 character ligatures */
{
   { U_LatinCapitalLigatureOE,            U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xBC   0x0152   LATIN CAPITAL LIGATURE OE */
   { U_LatinSmallLigatureOE,              U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xBD   0x0153   LATIN SMALL LIGATURE OE */
   { U_LatinCapitalLetterYWithDiaeresis,  U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0xBE   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterAWithRingAbove,    U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterYWithDiaeresis,    U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */

   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_LATIN9 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_LATIN9[] =       /* CODE_LATIN9 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_EuroSign,                            /* 0xA4   0x20AC   EURO SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_LatinCapitalLetterS,                 /* 0xA6   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinCapitalLetterS,                 /* 0xA8   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_FeminineOrdinalIndicator,            /* 0xAA   0x00AA   FEMININE ORDINAL INDICATOR */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_Macron,                              /* 0xAF   0x00AF   MACRON */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_LatinCapitalLetterZ,                 /* 0xB4   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_LatinCapitalLetterZ,                 /* 0xB8   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_SuperscriptOne,                      /* 0xB9   0x00B9   SUPERSCRIPT ONE */
   U_MasculineOrdinalIndicator,           /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LatinCapitalLetterO,                 /* 0xBC   0x0152   LATIN CAPITAL LIGATURE OE */
   U_LatinCapitalLetterO,                 /* 0xBD   0x0153   LATIN SMALL LIGATURE OE */
   U_LatinCapitalLetterY,                 /* 0xBE   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_LatinCapitalLetterA,                 /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x00C3   LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 0xD0   0x00D0   LATIN CAPITAL LETTER ETH */
   U_LatinCapitalLetterN,                 /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterO,                 /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xDD   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 0xDE   0x00DE   LATIN CAPITAL LETTER THORN */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterA,                 /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x00E3   LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 0xF0   0x00F0   LATIN SMALL LETTER ETH */
   U_LatinCapitalLetterN,                 /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinCapitalLetterO,                 /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xFD   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 0xFE   0x00FE   LATIN SMALL LETTER THORN */
   U_LatinCapitalLetterY                  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};










/******************************************************************************
*
*  u_CODE_LATIN10[]:
*     Unicode named codepage for ISO encoding Latin-10 (iso-8859-16) "South East European"
*
*  Name:             ISO/IEC 8859-16:2001 to Unicode
*  Unicode version:  3.0
*  Table version:    1.0
*  Table format:     Format A
*  Date:             2001 July 26
*  Authors:          Markus Kuhn <http://www.cl.cam.ac.uk/~mgk25/>
*
******************************************|************************************/

static _UWORD const u_CODE_LATIN10[] =         /* CODE_LATIN10 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinSmallLetterA,                   /* 0x61  a */
   U_LatinSmallLetterB,                   /* 0x62  b */
   U_LatinSmallLetterC,                   /* 0x63  c */
   U_LatinSmallLetterD,                   /* 0x64  d */
   U_LatinSmallLetterE,                   /* 0x65  e */
   U_LatinSmallLetterF,                   /* 0x66  f */
   U_LatinSmallLetterG,                   /* 0x67  g */
   U_LatinSmallLetterH,                   /* 0x68  h */
   U_LatinSmallLetterI,                   /* 0x69  i */
   U_LatinSmallLetterJ,                   /* 0x6A  j */
   U_LatinSmallLetterK,                   /* 0x6B  k */
   U_LatinSmallLetterL,                   /* 0x6C  l */
   U_LatinSmallLetterM,                   /* 0x6D  m */
   U_LatinSmallLetterN,                   /* 0x6E  n */
   U_LatinSmallLetterO,                   /* 0x6F  o */
   U_LatinSmallLetterP,                   /* 0x70  p */
   U_LatinSmallLetterQ,                   /* 0x71  q */
   U_LatinSmallLetterR,                   /* 0x72  r */
   U_LatinSmallLetterS,                   /* 0x73  s */
   U_LatinSmallLetterT,                   /* 0x74  t */
   U_LatinSmallLetterU,                   /* 0x75  u */
   U_LatinSmallLetterV,                   /* 0x76  v */
   U_LatinSmallLetterW,                   /* 0x77  w */
   U_LatinSmallLetterX,                   /* 0x78  x */
   U_LatinSmallLetterY,                   /* 0x79  y */
   U_LatinSmallLetterZ,                   /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterAWithOgonek,       /* 0xA1   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinSmallLetterAWithOgonek,         /* 0xA2   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_LatinCapitalLetterLWithStroke,       /* 0xA3   0x0141   LATIN CAPITAL LETTER L WITH STROKE */
   U_EuroSign,                            /* 0xA4   0x20AC   EURO SIGN */
   U_DoubleLow9QuotationMark,             /* 0xA5   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_LatinCapitalLetterSWithCaron,        /* 0xA6   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinSmallLetterSWithCaron,          /* 0xA8   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_LatinCapitalLetterSWithCommaBelow,   /* 0xAA   0x0218   LATIN CAPITAL LETTER S WITH COMMA BELOW */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LatinCapitalLetterZWithAcute,        /* 0xAC   0x0179   LATIN CAPITAL LETTER Z WITH ACUTE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinSmallLetterZWithAcute,          /* 0xAE   0x017A   LATIN SMALL LETTER Z WITH ACUTE */
   U_LatinCapitalLetterZWithDotAbove,     /* 0xAF   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_LatinCapitalLetterCWithCaron,        /* 0xB2   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinSmallLetterLWithStroke,         /* 0xB3   0x0142   LATIN SMALL LETTER L WITH STROKE */
   U_LatinCapitalLetterZWithCaron,        /* 0xB4   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_RightDoubleQuotationMark,            /* 0xB5   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_LatinSmallLetterZWithCaron,          /* 0xB8   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_LatinSmallLetterCWithCaron,          /* 0xB9   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinSmallLetterSWithCommaBelow,     /* 0xBA   0x0219   LATIN SMALL LETTER S WITH COMMA BELOW */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LatinCapitalLigatureOE,              /* 0xBC   0x0152   LATIN CAPITAL LIGATURE OE */
   U_LatinSmallLigatureOE,                /* 0xBD   0x0153   LATIN SMALL LIGATURE OE */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0xBE   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_LatinSmallLetterZWithDotAbove,       /* 0xBF   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterAWithGrave,        /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithBreve,        /* 0xC3   0x0102   LATIN CAPITAL LETTER A WITH BREVE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterCWithAcute,        /* 0xC5   0x0106   LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinCapitalLigatureAE,              /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterEWithGrave,        /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterIWithGrave,        /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterDWithStroke,       /* 0xD0   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterNWithAcute,        /* 0xD1   0x0143   LATIN CAPITAL LETTER N WITH ACUTE */
   U_LatinCapitalLetterOWithGrave,        /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithDoubleAcute,  /* 0xD5   0x0150   LATIN CAPITAL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterSWithAcute,        /* 0xD7   0x015A   LATIN CAPITAL LETTER S WITH ACUTE */
   U_LatinCapitalLetterUWithDoubleAcute,  /* 0xD8   0x0170   LATIN CAPITAL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterUWithGrave,        /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterEWithOgonek,       /* 0xDD   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterTWithCommaBelow,   /* 0xDE   0x021A   LATIN CAPITAL LETTER T WITH COMMA BELOW */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterAWithGrave,          /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithBreve,          /* 0xE3   0x0103   LATIN SMALL LETTER A WITH BREVE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterCWithAcute,          /* 0xE5   0x0107   LATIN SMALL LETTER C WITH ACUTE */
   U_LatinSmallLigatureAE,                /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithGrave,          /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithCircumflex,     /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterIWithGrave,          /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterDWithStroke,         /* 0xF0   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinSmallLetterNWithAcute,          /* 0xF1   0x0144   LATIN SMALL LETTER N WITH ACUTE */
   U_LatinSmallLetterOWithGrave,          /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithDoubleAcute,    /* 0xF5   0x0151   LATIN SMALL LETTER O WITH DOUBLE ACUTE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterSWithAcute,          /* 0xF7   0x015B   LATIN SMALL LETTER S WITH ACUTE */
   U_LatinSmallLetterUWithDoubleAcute,    /* 0xF8   0x0171   LATIN SMALL LETTER U WITH DOUBLE ACUTE */
   U_LatinSmallLetterUWithGrave,          /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterEWithOgonek,         /* 0xFD   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinSmallLetterTWithCommaBelow,     /* 0xFE   0x021B   LATIN SMALL LETTER T WITH COMMA BELOW */
   U_LatinSmallLetterYWithDiaeresis       /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};





/******************************************************************************
*
*  CODE_LATIN10_lig[]:
*     list of ligatures:
*
*  CODE_LATIN10_lig[0] is the original ligature character
*  CODE_LATIN10_lig[1] + CODE_LATIN10_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_LATIN10_lig[][3] =    /* CODE_LATIN10 character ligatures */
{
   { U_LatinCapitalLigatureOE,            U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xBC   0x0152   LATIN CAPITAL LIGATURE OE */
   { U_LatinSmallLigatureOE,              U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xBD   0x0153   LATIN SMALL LIGATURE OE */
   { U_LatinCapitalLetterYWithDiaeresis,  U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0xBE   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterYWithDiaeresis,    U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */

   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_LATIN10 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_LATIN10[] =      /* CODE_LATIN10 */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_NIL,                                 /* 0x80   0x0080   <control> */
   U_NIL,                                 /* 0x81   0x0081   <control> */
   U_NIL,                                 /* 0x82   0x0082   <control> */
   U_NIL,                                 /* 0x83   0x0083   <control> */
   U_NIL,                                 /* 0x84   0x0084   <control> */
   U_NIL,                                 /* 0x85   0x0085   <control> */
   U_NIL,                                 /* 0x86   0x0086   <control> */
   U_NIL,                                 /* 0x87   0x0087   <control> */
   U_NIL,                                 /* 0x88   0x0088   <control> */
   U_NIL,                                 /* 0x89   0x0089   <control> */
   U_NIL,                                 /* 0x8A   0x008A   <control> */
   U_NIL,                                 /* 0x8B   0x008B   <control> */
   U_NIL,                                 /* 0x8C   0x008C   <control> */
   U_NIL,                                 /* 0x8D   0x008D   <control> */
   U_NIL,                                 /* 0x8E   0x008E   <control> */
   U_NIL,                                 /* 0x8F   0x008F   <control> */
   U_NIL,                                 /* 0x90   0x0090   <control> */
   U_NIL,                                 /* 0x91   0x0091   <control> */
   U_NIL,                                 /* 0x92   0x0092   <control> */
   U_NIL,                                 /* 0x93   0x0093   <control> */
   U_NIL,                                 /* 0x94   0x0094   <control> */
   U_NIL,                                 /* 0x95   0x0095   <control> */
   U_NIL,                                 /* 0x96   0x0096   <control> */
   U_NIL,                                 /* 0x97   0x0097   <control> */
   U_NIL,                                 /* 0x98   0x0098   <control> */
   U_NIL,                                 /* 0x99   0x0099   <control> */
   U_NIL,                                 /* 0x9A   0x009A   <control> */
   U_NIL,                                 /* 0x9B   0x009B   <control> */
   U_NIL,                                 /* 0x9C   0x009C   <control> */
   U_NIL,                                 /* 0x9D   0x009D   <control> */
   U_NIL,                                 /* 0x9E   0x009E   <control> */
   U_NIL,                                 /* 0x9F   0x009F   <control> */
   
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterA,                 /* 0xA1   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinCapitalLetterA,                 /* 0xA2   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_LatinCapitalLetterL,                 /* 0xA3   0x0141   LATIN CAPITAL LETTER L WITH STROKE */
   U_EuroSign,                            /* 0xA4   0x20AC   EURO SIGN */
   U_DoubleLow9QuotationMark,             /* 0xA5   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_LatinCapitalLetterS,                 /* 0xA6   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_LatinCapitalLetterS,                 /* 0xA8   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_LatinCapitalLetterS,                 /* 0xAA   0x0218   LATIN CAPITAL LETTER S WITH COMMA BELOW */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LatinCapitalLetterZ,                 /* 0xAC   0x0179   LATIN CAPITAL LETTER Z WITH ACUTE */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_LatinCapitalLetterZ,                 /* 0xAE   0x017A   LATIN SMALL LETTER Z WITH ACUTE */
   U_LatinCapitalLetterZ,                 /* 0xAF   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_LatinCapitalLetterC,                 /* 0xB2   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterL,                 /* 0xB3   0x0142   LATIN SMALL LETTER L WITH STROKE */
   U_LatinCapitalLetterZ,                 /* 0xB4   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_RightDoubleQuotationMark,            /* 0xB5   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_LatinCapitalLetterZ,                 /* 0xB8   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_LatinCapitalLetterC,                 /* 0xB9   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinCapitalLetterS,                 /* 0xBA   0x0219   LATIN SMALL LETTER S WITH COMMA BELOW */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LatinCapitalLetterO,                 /* 0xBC   0x0152   LATIN CAPITAL LIGATURE OE */
   U_LatinCapitalLetterO,                 /* 0xBD   0x0153   LATIN SMALL LIGATURE OE */
   U_LatinCapitalLetterY,                 /* 0xBE   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_LatinCapitalLetterZ,                 /* 0xBF   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x0102   LATIN CAPITAL LETTER A WITH BREVE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xC5   0x0106   LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xCC   0x00CC   LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterD,                 /* 0xD0   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xD1   0x0143   LATIN CAPITAL LETTER N WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD2   0x00D2   LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x0150   LATIN CAPITAL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterS,                 /* 0xD7   0x015A   LATIN CAPITAL LETTER S WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xD8   0x0170   LATIN CAPITAL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterU,                 /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xDD   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterT,                 /* 0xDE   0x021A   LATIN CAPITAL LETTER T WITH COMMA BELOW */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterA,                 /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x0103   LATIN SMALL LETTER A WITH BREVE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterC,                 /* 0xE5   0x0107   LATIN SMALL LETTER C WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xEC   0x00EC   LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterD,                 /* 0xF0   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xF1   0x0144   LATIN SMALL LETTER N WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF2   0x00F2   LATIN SMALL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x0151   LATIN SMALL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterS,                 /* 0xF7   0x015B   LATIN SMALL LETTER S WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xF8   0x0171   LATIN SMALL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterU,                 /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xFD   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_LatinCapitalLetterT,                 /* 0xFE   0x021B   LATIN SMALL LETTER T WITH COMMA BELOW */
   U_LatinCapitalLetterY                  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};
