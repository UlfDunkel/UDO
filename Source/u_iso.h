/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_iso.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepages for ISO encodings:
*                 - u_CODE_LATIN1[]: iso-8859-1
*                 - u_CODE_LATIN2[]: iso-8859-2
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
*  Things to do : - add more codepages
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
*    fd  Feb 22: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 23: - tables adjusted
*                - CODE_LAT2 -> CODE_LATIN2
*                - CODE_LATIN1
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#include "portab.h"
#include "unicode.h"





/******************************************************************************
*
*  u_CODE_LATIN1[]:
*     Unicode named codepage for ISO encoding Latin-1 (iso-8859-1)
*
******************************************|************************************/

static UWORD   u_CODE_LATIN1[] =          /* CODE_LATIN1 */
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

static UWORD   CODE_LATIN1_lig[][3] =     /* CODE_LATIN1 character ligatures */
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

static UWORD   sort_CODE_LATIN1[] =       /* CODE_LATIN1 */
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
******************************************|************************************/

static UWORD   u_CODE_LATIN2[] =          /* CODE_LATIN2 */
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

static UWORD   CODE_LATIN2_lig[][3] =     /* CODE_LATIN2 character ligatures */
{
   { U_LatinCapitalLetterAWithDiaeresis, U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove, U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0xC5   0x0139   LATIN CAPITAL LETTER L WITH ACUTE */
   { U_LatinCapitalLetterEWithDiaeresis, U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis, U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterUWithRingAbove, U_LatinCapitalLetterU, U_LatinCapitalLetterO },  /* 0xD9   0x016E   LATIN CAPITAL LETTER U WITH RING ABOVE */
   { U_LatinCapitalLetterUWithDiaeresis, U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,           U_LatinCapitalLetterS, U_LatinCapitalLetterS },  /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,   U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterEWithDiaeresis,   U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,   U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterUWithRingAbove,   U_LatinCapitalLetterU, U_LatinCapitalLetterO },  /* 0xF9   0x016F   LATIN SMALL LETTER U WITH RING ABOVE */
   { U_LatinSmallLetterUWithDiaeresis,   U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */

   {0x0000,                              U_NIL,                 U_NIL}                   /* list terminator */
};





/******************************************************************************
*
*  CODE_LATIN2 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static UWORD   sort_CODE_LATIN2[] =       /* CODE_LATIN2 */
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


/* +++ EOF +++ */