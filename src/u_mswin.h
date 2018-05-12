/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_mswin.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepages for Microsoft Windows codepage encodings:
*
*                 - u_CODE_CP1250[]: cp1250 ("Central European")
*                 - u_CODE_CP1251[]: cp1251 ("Russian")
*                 - u_CODE_CP1252[]: cp1252 ("Western")
*                 - u_CODE_CP1253[]: cp1253 ("Greek")
*                 - u_CODE_CP1254[]: cp1254 ("Turkish")
*                 - u_CODE_CP1255[]: cp1255 ("Hebrew")
*                 - u_CODE_CP1256[]: cp1256 ("Arabic")
*                 - u_CODE_CP1257[]: cp1257 ("Baltic")
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
*    fd  Feb 19: - file introduced (extracted from u_iso.h)
*                - CODE_CP1257 (Baltic)
*    fd  Feb 20: - CODE_CP1251 (Russian)
*    fd  Feb 22: - void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*                - CODE_CP1253 (Greek)
*    fd  Feb 23: CODE_LAT1 -> CODE_CP1252
*    fd  Feb 24: - CODE_CP1254 (Turkish)
*                - CODE_CP1255 (Hebrew)
*                - CODE_CP1256 (Arabic)
*                - CODE_CP1258 (Vietnamese)
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
*  u_CODE_CP1250[]:
*     Unicode named codepage for Microsoft Windows encoding codepage 1250
*
*  Name:             cp1250 to Unicode table
*  Unicode version:  2.0
*  Table version:    2.01
*  Table format:     Format A
*  Date:             1998-04-15
*  Contact:          Shawn.Steele@microsoft.com
*
******************************************|************************************/

static _UWORD const u_CODE_CP1250[] =          /* CODE_CP1250 */
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

   U_EuroSign,                            /* 0x80   0x20AC  EURO SIGN */
   U_NIL,                                 /* 0x81           UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A  SINGLE LOW-9 QUOTATION MARK */
   U_NIL,                                 /* 0x83           UNDEFINED */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E  DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026  HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020  DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021  DOUBLE DAGGER */
   U_NIL,                                 /* 0x88           UNDEFINED */
   U_PerMilleSign,                        /* 0x89   0x2030  PER MILLE SIGN */
   U_LatinCapitalLetterSWithCaron,        /* 0x8A   0x0160  LATIN CAPITAL LETTER S WITH CARON */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039  SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterSWithAcute,        /* 0x8C   0x015A  LATIN CAPITAL LETTER S WITH ACUTE */
   U_LatinCapitalLetterTWithCaron,        /* 0x8D   0x0164  LATIN CAPITAL LETTER T WITH CARON */
   U_LatinCapitalLetterZWithCaron,        /* 0x8E   0x017D  LATIN CAPITAL LETTER Z WITH CARON */
   U_LatinCapitalLetterZWithAcute,        /* 0x8F   0x0179  LATIN CAPITAL LETTER Z WITH ACUTE */
   U_NIL,                                 /* 0x90           UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018  LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019  RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C  LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D  RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022  BULLET */
   U_EnDash,                              /* 0x96   0x2013  EN DASH */
   U_EmDash,                              /* 0x97   0x2014  EM DASH */
   U_NIL,                                 /* 0x98           UNDEFINED */
   U_TradeMarkSign,                       /* 0x99   0x2122  TRADE MARK SIGN */
   U_LatinSmallLetterSWithCaron,          /* 0x9A   0x0161  LATIN SMALL LETTER S WITH CARON */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A  SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinSmallLetterSWithAcute,          /* 0x9C   0x015B  LATIN SMALL LETTER S WITH ACUTE */
   U_LatinSmallLetterTWithCaron,          /* 0x9D   0x0165  LATIN SMALL LETTER T WITH CARON */
   U_LatinSmallLetterZWithCaron,          /* 0x9E   0x017E  LATIN SMALL LETTER Z WITH CARON */
   U_LatinSmallLetterZWithAcute,          /* 0x9F   0x017A  LATIN SMALL LETTER Z WITH ACUTE */
   U_NB_SP,                               /* 0xA0   0x00A0  NO-BREAK SPACE */
   U_Caron,                               /* 0xA1   0x02C7  CARON */
   U_Breve,                               /* 0xA2   0x02D8  BREVE */
   U_LatinCapitalLetterLWithStroke,       /* 0xA3   0x0141  LATIN CAPITAL LETTER L WITH STROKE */
   U_CurrencySign,                        /* 0xA4   0x00A4  CURRENCY SIGN */
   U_LatinCapitalLetterAWithOgonek,       /* 0xA5   0x0104  LATIN CAPITAL LETTER A WITH OGONEK */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6  BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7  SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8  DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9  COPYRIGHT SIGN */
   U_LatinCapitalLetterSWithCedilla,      /* 0xAA   0x015E  LATIN CAPITAL LETTER S WITH CEDILLA */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB  LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC  NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD  SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE  REGISTERED SIGN */
   U_LatinCapitalLetterZWithDotAbove,     /* 0xAF   0x017B  LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_DegreeSign,                          /* 0xB0   0x00B0  DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1  PLUS-MINUS SIGN */
   U_Ogonek,                              /* 0xB2   0x02DB  OGONEK */
   U_LatinSmallLetterLWithStroke,         /* 0xB3   0x0142  LATIN SMALL LETTER L WITH STROKE */
   U_AcuteAccent,                         /* 0xB4   0x00B4  ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5  MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6  PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7  MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8  CEDILLA */
   U_LatinSmallLetterAWithOgonek,         /* 0xB9   0x0105  LATIN SMALL LETTER A WITH OGONEK */
   U_LatinSmallLetterSWithCedilla,        /* 0xBA   0x015F  LATIN SMALL LETTER S WITH CEDILLA */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB  RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LatinCapitalLetterLWithCaron,        /* 0xBC   0x013D  LATIN CAPITAL LETTER L WITH CARON */
   U_DoubleAcuteAccent,                   /* 0xBD   0x02DD  DOUBLE ACUTE ACCENT */
   U_LatinSmallLetterLWithCaron,          /* 0xBE   0x013E  LATIN SMALL LETTER L WITH CARON */
   U_LatinSmallLetterZWithDotAbove,       /* 0xBF   0x017C  LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterRWithAcute,        /* 0xC0   0x0154  LATIN CAPITAL LETTER R WITH ACUTE */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1  LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2  LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithBreve,        /* 0xC3   0x0102  LATIN CAPITAL LETTER A WITH BREVE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4  LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterLWithAcute,        /* 0xC5   0x0139  LATIN CAPITAL LETTER L WITH ACUTE */
   U_LatinCapitalLetterCWithAcute,        /* 0xC6   0x0106  LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xC7   0x00C7  LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterCWithCaron,        /* 0xC8   0x010C  LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9  LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithOgonek,       /* 0xCA   0x0118  LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB  LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterEWithCaron,        /* 0xCC   0x011A  LATIN CAPITAL LETTER E WITH CARON */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD  LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE  LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterDWithCaron,        /* 0xCF   0x010E  LATIN CAPITAL LETTER D WITH CARON */
   U_LatinCapitalLetterDWithStroke,       /* 0xD0   0x0110  LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterNWithAcute,        /* 0xD1   0x0143  LATIN CAPITAL LETTER N WITH ACUTE */
   U_LatinCapitalLetterNWithCaron,        /* 0xD2   0x0147  LATIN CAPITAL LETTER N WITH CARON */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3  LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4  LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithDoubleAcute,  /* 0xD5   0x0150  LATIN CAPITAL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6  LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7  MULTIPLICATION SIGN */
   U_LatinCapitalLetterRWithCaron,        /* 0xD8   0x0158  LATIN CAPITAL LETTER R WITH CARON */
   U_LatinCapitalLetterUWithRingAbove,    /* 0xD9   0x016E  LATIN CAPITAL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA  LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithDoubleAcute,  /* 0xDB   0x0170  LATIN CAPITAL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC  LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterYWithAcute,        /* 0xDD   0x00DD  LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterTWithCedilla,      /* 0xDE   0x0162  LATIN CAPITAL LETTER T WITH CEDILLA */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF  LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterRWithAcute,          /* 0xE0   0x0155  LATIN SMALL LETTER R WITH ACUTE */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1  LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2  LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithBreve,          /* 0xE3   0x0103  LATIN SMALL LETTER A WITH BREVE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4  LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterLWithAcute,          /* 0xE5   0x013A  LATIN SMALL LETTER L WITH ACUTE */
   U_LatinSmallLetterCWithAcute,          /* 0xE6   0x0107  LATIN SMALL LETTER C WITH ACUTE */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7  LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterCWithCaron,          /* 0xE8   0x010D  LATIN SMALL LETTER C WITH CARON */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9  LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithOgonek,         /* 0xEA   0x0119  LATIN SMALL LETTER E WITH OGONEK */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB  LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterEWithCaron,          /* 0xEC   0x011B  LATIN SMALL LETTER E WITH CARON */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED  LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE  LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterDWithCaron,          /* 0xEF   0x010F  LATIN SMALL LETTER D WITH CARON */
   U_LatinSmallLetterDWithStroke,         /* 0xF0   0x0111  LATIN SMALL LETTER D WITH STROKE */
   U_LatinSmallLetterNWithAcute,          /* 0xF1   0x0144  LATIN SMALL LETTER N WITH ACUTE */
   U_LatinSmallLetterNWithCaron,          /* 0xF2   0x0148  LATIN SMALL LETTER N WITH CARON */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3  LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4  LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithDoubleAcute,    /* 0xF5   0x0151  LATIN SMALL LETTER O WITH DOUBLE ACUTE */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6  LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7  DIVISION SIGN */
   U_LatinSmallLetterRWithCaron,          /* 0xF8   0x0159  LATIN SMALL LETTER R WITH CARON */
   U_LatinSmallLetterUWithRingAbove,      /* 0xF9   0x016F  LATIN SMALL LETTER U WITH RING ABOVE */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA  LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithDoubleAcute,    /* 0xFB   0x0171  LATIN SMALL LETTER U WITH DOUBLE ACUTE */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC  LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterYWithAcute,          /* 0xFD   0x00FD  LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinSmallLetterTWithCedilla,        /* 0xFE   0x0163  LATIN SMALL LETTER T WITH CEDILLA */
   U_DotAbove                             /* 0xFF   0x02D9  DOT ABOVE */
};





/******************************************************************************
*
*  CODE_CP1250_lig[]:
*     list of ligatures:
*
*  CODE_CP1250_lig[0] is the original ligature character
*  CODE_CP1250_lig[1] + CODE_CP1250_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CP1250_lig[][3] =     /* CODE_CP1250 character ligatures */
{
   { U_LatinCapitalLetterSWithCaron,      U_LatinCapitalLetterS, U_LatinCapitalLetterJ },   /* 0x8A   0x0160  LATIN CAPITAL LETTER S WITH CARON */
   { U_LatinCapitalLetterTWithCaron,      U_LatinCapitalLetterT, U_LatinCapitalLetterJ },   /* 0x8D   0x0164  LATIN CAPITAL LETTER T WITH CARON */
   { U_LatinCapitalLetterZWithCaron,      U_LatinCapitalLetterZ, U_LatinCapitalLetterJ },   /* 0x8E   0x017D  LATIN CAPITAL LETTER Z WITH CARON */
   { U_LatinSmallLetterSWithCaron,        U_LatinCapitalLetterS, U_LatinCapitalLetterJ },   /* 0x9A   0x0161  LATIN SMALL LETTER S WITH CARON */
   { U_LatinSmallLetterTWithCaron,        U_LatinCapitalLetterT, U_LatinCapitalLetterJ },   /* 0x9D   0x0165  LATIN SMALL LETTER T WITH CARON */
   { U_LatinSmallLetterZWithCaron,        U_LatinCapitalLetterZ, U_LatinCapitalLetterJ },   /* 0x9E   0x017E  LATIN SMALL LETTER Z WITH CARON */
   { U_LatinCapitalLetterLWithCaron,      U_LatinCapitalLetterL, U_LatinCapitalLetterJ },   /* 0xBC   0x013D  LATIN CAPITAL LETTER L WITH CARON */
   { U_LatinSmallLetterLWithCaron,        U_LatinCapitalLetterL, U_LatinCapitalLetterJ },   /* 0xBE   0x013E  LATIN SMALL LETTER L WITH CARON */
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE },   /* 0xC4   0x00C4  LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterCWithCaron,      U_LatinCapitalLetterC, U_LatinCapitalLetterJ },   /* 0xC8   0x010C  LATIN CAPITAL LETTER C WITH CARON */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE },   /* 0xCB   0x00CB  LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterEWithCaron,      U_LatinCapitalLetterE, U_LatinCapitalLetterJ },   /* 0xCC   0x011A  LATIN CAPITAL LETTER E WITH CARON */
   { U_LatinCapitalLetterDWithCaron,      U_LatinCapitalLetterD, U_LatinCapitalLetterJ },   /* 0xCF   0x010E  LATIN CAPITAL LETTER D WITH CARON */
   { U_LatinCapitalLetterNWithCaron,      U_LatinCapitalLetterN, U_LatinCapitalLetterJ },   /* 0xD2   0x0147  LATIN CAPITAL LETTER N WITH CARON */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE },   /* 0xD6   0x00D6  LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterRWithCaron,      U_LatinCapitalLetterR, U_LatinCapitalLetterJ },   /* 0xD8   0x0158  LATIN CAPITAL LETTER R WITH CARON */
   { U_LatinCapitalLetterUWithRingAbove,  U_LatinCapitalLetterU, U_LatinCapitalLetterO },   /* 0xD9   0x016E  LATIN CAPITAL LETTER U WITH RING ABOVE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },   /* 0xDC   0x00DC  LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS },   /* 0xDF   0x00DF  LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE },   /* 0xE4   0x00E4  LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterCWithCaron,        U_LatinCapitalLetterC, U_LatinCapitalLetterJ },   /* 0xE8   0x010D  LATIN SMALL LETTER C WITH CARON */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE },   /* 0xEB   0x00EB  LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterEWithCaron,        U_LatinCapitalLetterE, U_LatinCapitalLetterJ },   /* 0xEC   0x011B  LATIN SMALL LETTER E WITH CARON */
   { U_LatinSmallLetterDWithCaron,        U_LatinCapitalLetterD, U_LatinCapitalLetterJ },   /* 0xEF   0x010F  LATIN SMALL LETTER D WITH CARON */
   { U_LatinSmallLetterNWithCaron,        U_LatinCapitalLetterN, U_LatinCapitalLetterJ },   /* 0xF2   0x0148  LATIN SMALL LETTER N WITH CARON */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE },   /* 0xF6   0x00F6  LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterRWithCaron,        U_LatinCapitalLetterR, U_LatinCapitalLetterJ },   /* 0xF8   0x0159  LATIN SMALL LETTER R WITH CARON */
   { U_LatinSmallLetterUWithRingAbove,    U_LatinCapitalLetterU, U_LatinCapitalLetterO },   /* 0xF9   0x016F  LATIN SMALL LETTER U WITH RING ABOVE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE },   /* 0xFC   0x00FC  LATIN SMALL LETTER U WITH DIAERESIS */
   
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CP1250 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_CP1250[] =       /* CODE_CP1250 */
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

   U_EuroSign,                            /* 0x80   0x20AC  EURO SIGN */
   U_NIL,                                 /* 0x81           UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A  SINGLE LOW-9 QUOTATION MARK */
   U_NIL,                                 /* 0x83           UNDEFINED */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E  DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026  HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020  DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021  DOUBLE DAGGER */
   U_NIL,                                 /* 0x88           UNDEFINED */
   U_PerMilleSign,                        /* 0x89   0x2030  PER MILLE SIGN */
   U_LatinCapitalLetterS,                 /* 0x8A   0x0160  LATIN CAPITAL LETTER S WITH CARON */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039  SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterSWithAcute,        /* 0x8C   0x015A  LATIN CAPITAL LETTER S WITH ACUTE */
   U_LatinCapitalLetterT,                 /* 0x8D   0x0164  LATIN CAPITAL LETTER T WITH CARON */
   U_LatinCapitalLetterZ,                 /* 0x8E   0x017D  LATIN CAPITAL LETTER Z WITH CARON */
   U_LatinCapitalLetterZWithAcute,        /* 0x8F   0x0179  LATIN CAPITAL LETTER Z WITH ACUTE */
   U_NIL,                                 /* 0x90           UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018  LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019  RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C  LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D  RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022  BULLET */
   U_EnDash,                              /* 0x96   0x2013  EN DASH */
   U_EmDash,                              /* 0x97   0x2014  EM DASH */
   U_NIL,                                 /* 0x98           UNDEFINED */
   U_TradeMarkSign,                       /* 0x99   0x2122  TRADE MARK SIGN */
   U_LatinCapitalLetterS,                 /* 0x9A   0x0161  LATIN SMALL LETTER S WITH CARON */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A  SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterS,                 /* 0x9C   0x015B  LATIN SMALL LETTER S WITH ACUTE */
   U_LatinCapitalLetterT,                 /* 0x9D   0x0165  LATIN SMALL LETTER T WITH CARON */
   U_LatinCapitalLetterZ,                 /* 0x9E   0x017E  LATIN SMALL LETTER Z WITH CARON */
   U_LatinCapitalLetterZ,                 /* 0x9F   0x017A  LATIN SMALL LETTER Z WITH ACUTE */
   U_NB_SP,                               /* 0xA0   0x00A0  NO-BREAK SPACE */
   U_Caron,                               /* 0xA1   0x02C7  CARON */
   U_Breve,                               /* 0xA2   0x02D8  BREVE */
   U_LatinCapitalLetterL,                 /* 0xA3   0x0141  LATIN CAPITAL LETTER L WITH STROKE */
   U_CurrencySign,                        /* 0xA4   0x00A4  CURRENCY SIGN */
   U_LatinCapitalLetterA,                 /* 0xA5   0x0104  LATIN CAPITAL LETTER A WITH OGONEK */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6  BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7  SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8  DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9  COPYRIGHT SIGN */
   U_LatinCapitalLetterS,                 /* 0xAA   0x015E  LATIN CAPITAL LETTER S WITH CEDILLA */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB  LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC  NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD  SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE  REGISTERED SIGN */
   U_LatinCapitalLetterZ,                 /* 0xAF   0x017B  LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_DegreeSign,                          /* 0xB0   0x00B0  DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1  PLUS-MINUS SIGN */
   U_Ogonek,                              /* 0xB2   0x02DB  OGONEK */
   U_LatinSmallLetterL,                   /* 0xB3   0x0142  LATIN SMALL LETTER L WITH STROKE */
   U_AcuteAccent,                         /* 0xB4   0x00B4  ACUTE ACCENT */
   U_MicroSign,                           /* 0xB5   0x00B5  MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6  PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7  MIDDLE DOT */
   U_Cedilla,                             /* 0xB8   0x00B8  CEDILLA */
   U_LatinCapitalLetterA,                 /* 0xB9   0x0105  LATIN SMALL LETTER A WITH OGONEK */
   U_LatinCapitalLetterS,                 /* 0xBA   0x015F  LATIN SMALL LETTER S WITH CEDILLA */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB  RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LatinCapitalLetterL,                 /* 0xBC   0x013D  LATIN CAPITAL LETTER L WITH CARON */
   U_DoubleAcuteAccent,                   /* 0xBD   0x02DD  DOUBLE ACUTE ACCENT */
   U_LatinCapitalLetterL,                 /* 0xBE   0x013E  LATIN SMALL LETTER L WITH CARON */
   U_LatinCapitalLetterZ,                 /* 0xBF   0x017C  LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterR,                 /* 0xC0   0x0154  LATIN CAPITAL LETTER R WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1  LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2  LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x0102  LATIN CAPITAL LETTER A WITH BREVE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4  LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterL,                 /* 0xC5   0x0139  LATIN CAPITAL LETTER L WITH ACUTE */
   U_LatinCapitalLetterC,                 /* 0xC6   0x0106  LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinCapitalLetterC,                 /* 0xC7   0x00C7  LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterC,                 /* 0xC8   0x010C  LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9  LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x0118  LATIN CAPITAL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB  LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xCC   0x011A  LATIN CAPITAL LETTER E WITH CARON */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD  LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE  LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterD,                 /* 0xCF   0x010E  LATIN CAPITAL LETTER D WITH CARON */
   U_LatinCapitalLetterD,                 /* 0xD0   0x0110  LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xD1   0x0143  LATIN CAPITAL LETTER N WITH ACUTE */
   U_LatinCapitalLetterN,                 /* 0xD2   0x0147  LATIN CAPITAL LETTER N WITH CARON */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3  LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4  LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x0150  LATIN CAPITAL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6  LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7  MULTIPLICATION SIGN */
   U_LatinCapitalLetterR,                 /* 0xD8   0x0158  LATIN CAPITAL LETTER R WITH CARON */
   U_LatinCapitalLetterU,                 /* 0xD9   0x016E  LATIN CAPITAL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA  LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x0170  LATIN CAPITAL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC  LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xDD   0x00DD  LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterT,                 /* 0xDE   0x0162  LATIN CAPITAL LETTER T WITH CEDILLA */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF  LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterR,                 /* 0xE0   0x0155  LATIN SMALL LETTER R WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1  LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2  LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x0103  LATIN SMALL LETTER A WITH BREVE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4  LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterL,                 /* 0xE5   0x013A  LATIN SMALL LETTER L WITH ACUTE */
   U_LatinCapitalLetterC,                 /* 0xE6   0x0107  LATIN SMALL LETTER C WITH ACUTE */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7  LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterC,                 /* 0xE8   0x010D  LATIN SMALL LETTER C WITH CARON */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9  LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x0119  LATIN SMALL LETTER E WITH OGONEK */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB  LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xEC   0x011B  LATIN SMALL LETTER E WITH CARON */
   U_LatinCapitalLetterI,                 /* 0xED   0x00ED  LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE  LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterD,                 /* 0xEF   0x010F  LATIN SMALL LETTER D WITH CARON */
   U_LatinCapitalLetterD,                 /* 0xF0   0x0111  LATIN SMALL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xF1   0x0144  LATIN SMALL LETTER N WITH ACUTE */
   U_LatinCapitalLetterN,                 /* 0xF2   0x0148  LATIN SMALL LETTER N WITH CARON */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3  LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4  LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x0151  LATIN SMALL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6  LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7  DIVISION SIGN */
   U_LatinCapitalLetterR,                 /* 0xF8   0x0159  LATIN SMALL LETTER R WITH CARON */
   U_LatinCapitalLetterU,                 /* 0xF9   0x016F  LATIN SMALL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA  LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x0171  LATIN SMALL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC  LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 0xFD   0x00FD  LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterT,                 /* 0xFE   0x0163  LATIN SMALL LETTER T WITH CEDILLA */
   U_DotAbove                             /* 0xFF   0x02D9  DOT ABOVE */
};










/******************************************************************************
*
*  u_CODE_CP1251[]:
*     Unicode named codepage for Microsoft Windows encoding codepage 1251
*
*  Name:             cp1251 to Unicode table
*  Unicode version:  2.0
*  Table version:    2.01
*  Table format:     Format A
*  Date:             1998-04-15
*  Contact:          Shawn.Steele@microsoft.com
*
******************************************|************************************/

static _UWORD const u_CODE_CP1251[] =          /* CODE_CP1251 */
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

   U_CyrillicCapitalLetterDje,            /* 0x80   0x0402   CYRILLIC CAPITAL LETTER DJE */
   U_CyrillicCapitalLetterGje,            /* 0x81   0x0403   CYRILLIC CAPITAL LETTER GJE */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_CyrillicSmallLetterGje,              /* 0x83   0x0453   CYRILLIC SMALL LETTER GJE */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_EuroSign,                            /* 0x88   0x20AC   EURO SIGN */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_CyrillicCapitalLetterLje,            /* 0x8A   0x0409   CYRILLIC CAPITAL LETTER LJE */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_CyrillicCapitalLetterNje,            /* 0x8C   0x040A   CYRILLIC CAPITAL LETTER NJE */
   U_CyrillicCapitalLetterKje,            /* 0x8D   0x040C   CYRILLIC CAPITAL LETTER KJE */
   U_CyrillicCapitalLetterTshe,           /* 0x8E   0x040B   CYRILLIC CAPITAL LETTER TSHE */
   U_CyrillicCapitalLetterDzhe,           /* 0x8F   0x040F   CYRILLIC CAPITAL LETTER DZHE */
   U_CyrillicSmallLetterDje,              /* 0x90   0x0452   CYRILLIC SMALL LETTER DJE */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_NIL,                                 /* 0x98            UNDEFINED */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_CyrillicSmallLetterLje,              /* 0x9A   0x0459   CYRILLIC SMALL LETTER LJE */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_CyrillicSmallLetterNje,              /* 0x9C   0x045A   CYRILLIC SMALL LETTER NJE */
   U_CyrillicSmallLetterTshe,             /* 0x9D   0x045C   CYRILLIC SMALL LETTER KJE */
   U_CyrillicSmallLetterKje,              /* 0x9E   0x045B   CYRILLIC SMALL LETTER TSHE */
   U_CyrillicSmallLetterDzhe,             /* 0x9F   0x045F   CYRILLIC SMALL LETTER DZHE */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_CyrillicCapitalLetterShortU,         /* 0xA1   0x040E   CYRILLIC CAPITAL LETTER SHORT U */
   U_CyrillicSmallLetterShortU,           /* 0xA2   0x045E   CYRILLIC SMALL LETTER SHORT U */
   U_CyrillicCapitalLetterJe,             /* 0xA3   0x0408   CYRILLIC CAPITAL LETTER JE */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_CyrillicCapitalLetterGheWithUpturn,  /* 0xA5   0x0490   CYRILLIC CAPITAL LETTER GHE WITH UPTURN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_CyrillicCapitalLetterIo,             /* 0xA8   0x0401   CYRILLIC CAPITAL LETTER IO */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_CyrillicCapitalLetterUkrainianIe,    /* 0xAA   0x0404   CYRILLIC CAPITAL LETTER UKRAINIAN IE */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_CyrillicCapitalLetterYi,             /* 0xAF   0x0407   CYRILLIC CAPITAL LETTER YI */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
                                          /* 0xB2   0x0406   CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I */
   U_CyrillicCapitalLetterByelorussianUkrainianI,
                                          /* 0xB3   0x0456   CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I */
   U_CyrillicSmallLetterByelorussianUkrainianI,
   U_CyrillicSmallLetterGheWithUpturn,    /* 0xB4   0x0491   CYRILLIC SMALL LETTER GHE WITH UPTURN */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_CyrillicSmallLetterIo,               /* 0xB8   0x0451   CYRILLIC SMALL LETTER IO */
   U_NumeroSign,                          /* 0xB9   0x2116   NUMERO SIGN */
   U_CyrillicSmallLetterUkrainianIe,      /* 0xBA   0x0454   CYRILLIC SMALL LETTER UKRAINIAN IE */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_CyrillicSmallLetterJe,               /* 0xBC   0x0458   CYRILLIC SMALL LETTER JE */
   U_CyrillicCapitalLetterDze,            /* 0xBD   0x0405   CYRILLIC CAPITAL LETTER DZE */
   U_CyrillicSmallLetterDze,              /* 0xBE   0x0455   CYRILLIC SMALL LETTER DZE */
   U_CyrillicSmallLetterYi,               /* 0xBF   0x0457   CYRILLIC SMALL LETTER YI */
   U_CyrillicCapitalLetterA,              /* 0xC0   0x0410   CYRILLIC CAPITAL LETTER A */
   U_CyrillicCapitalLetterBe,             /* 0xC1   0x0411   CYRILLIC CAPITAL LETTER BE */
   U_CyrillicCapitalLetterVe,             /* 0xC2   0x0412   CYRILLIC CAPITAL LETTER VE */
   U_CyrillicCapitalLetterGhe,            /* 0xC3   0x0413   CYRILLIC CAPITAL LETTER GHE */
   U_CyrillicCapitalLetterDe,             /* 0xC4   0x0414   CYRILLIC CAPITAL LETTER DE */
   U_CyrillicCapitalLetterIe,             /* 0xC5   0x0415   CYRILLIC CAPITAL LETTER IE */
   U_CyrillicCapitalLetterZhe,            /* 0xC6   0x0416   CYRILLIC CAPITAL LETTER ZHE */
   U_CyrillicCapitalLetterZe,             /* 0xC7   0x0417   CYRILLIC CAPITAL LETTER ZE */
   U_CyrillicCapitalLetterI,              /* 0xC8   0x0418   CYRILLIC CAPITAL LETTER I */
   U_CyrillicCapitalLetterShortI,         /* 0xC9   0x0419   CYRILLIC CAPITAL LETTER SHORT I */
   U_CyrillicCapitalLetterKa,             /* 0xCA   0x041A   CYRILLIC CAPITAL LETTER KA */
   U_CyrillicCapitalLetterEl,             /* 0xCB   0x041B   CYRILLIC CAPITAL LETTER EL */
   U_CyrillicCapitalLetterEm,             /* 0xCC   0x041C   CYRILLIC CAPITAL LETTER EM */
   U_CyrillicCapitalLetterEn,             /* 0xCD   0x041D   CYRILLIC CAPITAL LETTER EN */
   U_CyrillicCapitalLetterO,              /* 0xCE   0x041E   CYRILLIC CAPITAL LETTER O */
   U_CyrillicCapitalLetterPe,             /* 0xCF   0x041F   CYRILLIC CAPITAL LETTER PE */
   U_CyrillicCapitalLetterEr,             /* 0xD0   0x0420   CYRILLIC CAPITAL LETTER ER */
   U_CyrillicCapitalLetterEs,             /* 0xD1   0x0421   CYRILLIC CAPITAL LETTER ES */
   U_CyrillicCapitalLetterTe,             /* 0xD2   0x0422   CYRILLIC CAPITAL LETTER TE */
   U_CyrillicCapitalLetterU,              /* 0xD3   0x0423   CYRILLIC CAPITAL LETTER U */
   U_CyrillicCapitalLetterEf,             /* 0xD4   0x0424   CYRILLIC CAPITAL LETTER EF */
   U_CyrillicCapitalLetterHa,             /* 0xD5   0x0425   CYRILLIC CAPITAL LETTER HA */
   U_CyrillicCapitalLetterTse,            /* 0xD6   0x0426   CYRILLIC CAPITAL LETTER TSE */
   U_CyrillicCapitalLetterChe,            /* 0xD7   0x0427   CYRILLIC CAPITAL LETTER CHE */
   U_CyrillicCapitalLetterSha,            /* 0xD8   0x0428   CYRILLIC CAPITAL LETTER SHA */
   U_CyrillicCapitalLetterShcha,          /* 0xD9   0x0429   CYRILLIC CAPITAL LETTER SHCHA */
   U_CyrillicCapitalLetterHardSign,       /* 0xDA   0x042A   CYRILLIC CAPITAL LETTER HARD SIGN */
   U_CyrillicCapitalLetterYeru,           /* 0xDB   0x042B   CYRILLIC CAPITAL LETTER YERU */
   U_CyrillicCapitalLetterSoftSign,       /* 0xDC   0x042C   CYRILLIC CAPITAL LETTER SOFT SIGN */
   U_CyrillicCapitalLetterE,              /* 0xDD   0x042D   CYRILLIC CAPITAL LETTER E */
   U_CyrillicCapitalLetterYu,             /* 0xDE   0x042E   CYRILLIC CAPITAL LETTER YU */
   U_CyrillicCapitalLetterYa,             /* 0xDF   0x042F   CYRILLIC CAPITAL LETTER YA */
   U_CyrillicSmallLetterA,                /* 0xE0   0x0430   CYRILLIC SMALL LETTER A */
   U_CyrillicSmallLetterBe,               /* 0xE1   0x0431   CYRILLIC SMALL LETTER BE */
   U_CyrillicSmallLetterVe,               /* 0xE2   0x0432   CYRILLIC SMALL LETTER VE */
   U_CyrillicSmallLetterGhe,              /* 0xE3   0x0433   CYRILLIC SMALL LETTER GHE */
   U_CyrillicSmallLetterDe,               /* 0xE4   0x0434   CYRILLIC SMALL LETTER DE */
   U_CyrillicSmallLetterIe,               /* 0xE5   0x0435   CYRILLIC SMALL LETTER IE */
   U_CyrillicSmallLetterZhe,              /* 0xE6   0x0436   CYRILLIC SMALL LETTER ZHE */
   U_CyrillicSmallLetterZe,               /* 0xE7   0x0437   CYRILLIC SMALL LETTER ZE */
   U_CyrillicSmallLetterI,                /* 0xE8   0x0438   CYRILLIC SMALL LETTER I */
   U_CyrillicSmallLetterShortI,           /* 0xE9   0x0439   CYRILLIC SMALL LETTER SHORT I */
   U_CyrillicSmallLetterKa,               /* 0xEA   0x043A   CYRILLIC SMALL LETTER KA */
   U_CyrillicSmallLetterEl,               /* 0xEB   0x043B   CYRILLIC SMALL LETTER EL */
   U_CyrillicSmallLetterEm,               /* 0xEC   0x043C   CYRILLIC SMALL LETTER EM */
   U_CyrillicSmallLetterEn,               /* 0xED   0x043D   CYRILLIC SMALL LETTER EN */
   U_CyrillicSmallLetterO,                /* 0xEE   0x043E   CYRILLIC SMALL LETTER O */
   U_CyrillicSmallLetterPe,               /* 0xEF   0x043F   CYRILLIC SMALL LETTER PE */
   U_CyrillicSmallLetterEr,               /* 0xF0   0x0440   CYRILLIC SMALL LETTER ER */
   U_CyrillicSmallLetterEs,               /* 0xF1   0x0441   CYRILLIC SMALL LETTER ES */
   U_CyrillicSmallLetterTe,               /* 0xF2   0x0442   CYRILLIC SMALL LETTER TE */
   U_CyrillicSmallLetterU,                /* 0xF3   0x0443   CYRILLIC SMALL LETTER U */
   U_CyrillicSmallLetterEf,               /* 0xF4   0x0444   CYRILLIC SMALL LETTER EF */
   U_CyrillicSmallLetterHa,               /* 0xF5   0x0445   CYRILLIC SMALL LETTER HA */
   U_CyrillicSmallLetterTse,              /* 0xF6   0x0446   CYRILLIC SMALL LETTER TSE */
   U_CyrillicSmallLetterChe,              /* 0xF7   0x0447   CYRILLIC SMALL LETTER CHE */
   U_CyrillicSmallLetterSha,              /* 0xF8   0x0448   CYRILLIC SMALL LETTER SHA */
   U_CyrillicSmallLetterShcha,            /* 0xF9   0x0449   CYRILLIC SMALL LETTER SHCHA */
   U_CyrillicSmallLetterHardSign,         /* 0xFA   0x044A   CYRILLIC SMALL LETTER HARD SIGN */
   U_CyrillicSmallLetterYeru,             /* 0xFB   0x044B   CYRILLIC SMALL LETTER YERU */
   U_CyrillicSmallLetterSoftSign,         /* 0xFC   0x044C   CYRILLIC SMALL LETTER SOFT SIGN */
   U_CyrillicSmallLetterE,                /* 0xFD   0x044D   CYRILLIC SMALL LETTER E */
   U_CyrillicSmallLetterYu,               /* 0xFE   0x044E   CYRILLIC SMALL LETTER YU */
   U_CyrillicSmallLetterYa                /* 0xFF   0x044F   CYRILLIC SMALL LETTER YA */
};





/******************************************************************************
*
*  CODE_CP1251_lig[]:
*     list of ligatures:
*
*  CODE_CP1251_lig[0] is the original ligature character
*  CODE_CP1251_lig[1] + CODE_CP1251_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CP1251_lig[][3] =     /* CODE_CP1251 character ligatures */
{
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CP1251 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_CP1251[] =       /* CODE_CP1251 */
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

   U_CyrillicCapitalLetterDje,            /* 0x80   0x0402   CYRILLIC CAPITAL LETTER DJE */
   U_CyrillicCapitalLetterGje,            /* 0x81   0x0403   CYRILLIC CAPITAL LETTER GJE */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_CyrillicCapitalLetterGje,            /* 0x83   0x0453   CYRILLIC SMALL LETTER GJE */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_EuroSign,                            /* 0x88   0x20AC   EURO SIGN */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_CyrillicCapitalLetterLje,            /* 0x8A   0x0409   CYRILLIC CAPITAL LETTER LJE */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_CyrillicCapitalLetterNje,            /* 0x8C   0x040A   CYRILLIC CAPITAL LETTER NJE */
   U_CyrillicCapitalLetterKje,            /* 0x8D   0x040C   CYRILLIC CAPITAL LETTER KJE */
   U_CyrillicCapitalLetterTshe,           /* 0x8E   0x040B   CYRILLIC CAPITAL LETTER TSHE */
   U_CyrillicCapitalLetterDzhe,           /* 0x8F   0x040F   CYRILLIC CAPITAL LETTER DZHE */
   U_CyrillicCapitalLetterDje,            /* 0x90   0x0452   CYRILLIC SMALL LETTER DJE */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_NIL,                                 /* 0x98            UNDEFINED */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_CyrillicCapitalLetterLje,            /* 0x9A   0x0459   CYRILLIC SMALL LETTER LJE */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_CyrillicCapitalLetterNje,            /* 0x9C   0x045A   CYRILLIC SMALL LETTER NJE */
   U_CyrillicCapitalLetterTshe,           /* 0x9D   0x045C   CYRILLIC SMALL LETTER KJE */
   U_CyrillicCapitalLetterKje,            /* 0x9E   0x045B   CYRILLIC SMALL LETTER TSHE */
   U_CyrillicCapitalLetterDzhe,           /* 0x9F   0x045F   CYRILLIC SMALL LETTER DZHE */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_CyrillicCapitalLetterU,              /* 0xA1   0x040E   CYRILLIC CAPITAL LETTER SHORT U */
   U_CyrillicCapitalLetterU,              /* 0xA2   0x045E   CYRILLIC SMALL LETTER SHORT U */
   U_CyrillicCapitalLetterJe,             /* 0xA3   0x0408   CYRILLIC CAPITAL LETTER JE */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_CyrillicCapitalLetterGhe,            /* 0xA5   0x0490   CYRILLIC CAPITAL LETTER GHE WITH UPTURN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_CyrillicCapitalLetterIo,             /* 0xA8   0x0401   CYRILLIC CAPITAL LETTER IO */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_CyrillicCapitalLetterIe,             /* 0xAA   0x0404   CYRILLIC CAPITAL LETTER UKRAINIAN IE */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_CyrillicCapitalLetterYi,             /* 0xAF   0x0407   CYRILLIC CAPITAL LETTER YI */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_CyrillicCapitalLetterI,              /* 0xB2   0x0406   CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I */
   U_CyrillicCapitalLetterI,              /* 0xB3   0x0456   CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I */
   U_CyrillicCapitalLetterGhe,            /* 0xB4   0x0491   CYRILLIC SMALL LETTER GHE WITH UPTURN */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
   U_MiddleDot,                           /* 0xB7   0x00B7   MIDDLE DOT */
   U_CyrillicCapitalLetterIo,             /* 0xB8   0x0451   CYRILLIC SMALL LETTER IO */
   U_NumeroSign,                          /* 0xB9   0x2116   NUMERO SIGN */
   U_CyrillicCapitalLetterIe,             /* 0xBA   0x0454   CYRILLIC SMALL LETTER UKRAINIAN IE */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_CyrillicCapitalLetterJe,             /* 0xBC   0x0458   CYRILLIC SMALL LETTER JE */
   U_CyrillicCapitalLetterDze,            /* 0xBD   0x0405   CYRILLIC CAPITAL LETTER DZE */
   U_CyrillicCapitalLetterDze,            /* 0xBE   0x0455   CYRILLIC SMALL LETTER DZE */
   U_CyrillicCapitalLetterYi,             /* 0xBF   0x0457   CYRILLIC SMALL LETTER YI */
   U_CyrillicCapitalLetterA,              /* 0xC0   0x0410   CYRILLIC CAPITAL LETTER A */
   U_CyrillicCapitalLetterBe,             /* 0xC1   0x0411   CYRILLIC CAPITAL LETTER BE */
   U_CyrillicCapitalLetterVe,             /* 0xC2   0x0412   CYRILLIC CAPITAL LETTER VE */
   U_CyrillicCapitalLetterGhe,            /* 0xC3   0x0413   CYRILLIC CAPITAL LETTER GHE */
   U_CyrillicCapitalLetterDe,             /* 0xC4   0x0414   CYRILLIC CAPITAL LETTER DE */
   U_CyrillicCapitalLetterIe,             /* 0xC5   0x0415   CYRILLIC CAPITAL LETTER IE */
   U_CyrillicCapitalLetterZhe,            /* 0xC6   0x0416   CYRILLIC CAPITAL LETTER ZHE */
   U_CyrillicCapitalLetterZe,             /* 0xC7   0x0417   CYRILLIC CAPITAL LETTER ZE */
   U_CyrillicCapitalLetterI,              /* 0xC8   0x0418   CYRILLIC CAPITAL LETTER I */
   U_CyrillicCapitalLetterI,              /* 0xC9   0x0419   CYRILLIC CAPITAL LETTER SHORT I */
   U_CyrillicCapitalLetterKa,             /* 0xCA   0x041A   CYRILLIC CAPITAL LETTER KA */
   U_CyrillicCapitalLetterEl,             /* 0xCB   0x041B   CYRILLIC CAPITAL LETTER EL */
   U_CyrillicCapitalLetterEm,             /* 0xCC   0x041C   CYRILLIC CAPITAL LETTER EM */
   U_CyrillicCapitalLetterEn,             /* 0xCD   0x041D   CYRILLIC CAPITAL LETTER EN */
   U_CyrillicCapitalLetterO,              /* 0xCE   0x041E   CYRILLIC CAPITAL LETTER O */
   U_CyrillicCapitalLetterPe,             /* 0xCF   0x041F   CYRILLIC CAPITAL LETTER PE */
   U_CyrillicCapitalLetterEr,             /* 0xD0   0x0420   CYRILLIC CAPITAL LETTER ER */
   U_CyrillicCapitalLetterEs,             /* 0xD1   0x0421   CYRILLIC CAPITAL LETTER ES */
   U_CyrillicCapitalLetterTe,             /* 0xD2   0x0422   CYRILLIC CAPITAL LETTER TE */
   U_CyrillicCapitalLetterU,              /* 0xD3   0x0423   CYRILLIC CAPITAL LETTER U */
   U_CyrillicCapitalLetterEf,             /* 0xD4   0x0424   CYRILLIC CAPITAL LETTER EF */
   U_CyrillicCapitalLetterHa,             /* 0xD5   0x0425   CYRILLIC CAPITAL LETTER HA */
   U_CyrillicCapitalLetterTse,            /* 0xD6   0x0426   CYRILLIC CAPITAL LETTER TSE */
   U_CyrillicCapitalLetterChe,            /* 0xD7   0x0427   CYRILLIC CAPITAL LETTER CHE */
   U_CyrillicCapitalLetterSha,            /* 0xD8   0x0428   CYRILLIC CAPITAL LETTER SHA */
   U_CyrillicCapitalLetterShcha,          /* 0xD9   0x0429   CYRILLIC CAPITAL LETTER SHCHA */
   U_CyrillicCapitalLetterHardSign,       /* 0xDA   0x042A   CYRILLIC CAPITAL LETTER HARD SIGN */
   U_CyrillicCapitalLetterYeru,           /* 0xDB   0x042B   CYRILLIC CAPITAL LETTER YERU */
   U_CyrillicCapitalLetterSoftSign,       /* 0xDC   0x042C   CYRILLIC CAPITAL LETTER SOFT SIGN */
   U_CyrillicCapitalLetterE,              /* 0xDD   0x042D   CYRILLIC CAPITAL LETTER E */
   U_CyrillicCapitalLetterYu,             /* 0xDE   0x042E   CYRILLIC CAPITAL LETTER YU */
   U_CyrillicCapitalLetterYa,             /* 0xDF   0x042F   CYRILLIC CAPITAL LETTER YA */
   U_CyrillicCapitalLetterA,              /* 0xE0   0x0430   CYRILLIC SMALL LETTER A */
   U_CyrillicCapitalLetterBe,             /* 0xE1   0x0431   CYRILLIC SMALL LETTER BE */
   U_CyrillicCapitalLetterVe,             /* 0xE2   0x0432   CYRILLIC SMALL LETTER VE */
   U_CyrillicCapitalLetterGhe,            /* 0xE3   0x0433   CYRILLIC SMALL LETTER GHE */
   U_CyrillicCapitalLetterDe,             /* 0xE4   0x0434   CYRILLIC SMALL LETTER DE */
   U_CyrillicCapitalLetterIe,             /* 0xE5   0x0435   CYRILLIC SMALL LETTER IE */
   U_CyrillicCapitalLetterZhe,            /* 0xE6   0x0436   CYRILLIC SMALL LETTER ZHE */
   U_CyrillicCapitalLetterZe,             /* 0xE7   0x0437   CYRILLIC SMALL LETTER ZE */
   U_CyrillicCapitalLetterI,              /* 0xE8   0x0438   CYRILLIC SMALL LETTER I */
   U_CyrillicCapitalLetterI,              /* 0xE9   0x0439   CYRILLIC SMALL LETTER SHORT I */
   U_CyrillicCapitalLetterKa,             /* 0xEA   0x043A   CYRILLIC SMALL LETTER KA */
   U_CyrillicCapitalLetterEl,             /* 0xEB   0x043B   CYRILLIC SMALL LETTER EL */
   U_CyrillicCapitalLetterEm,             /* 0xEC   0x043C   CYRILLIC SMALL LETTER EM */
   U_CyrillicCapitalLetterEn,             /* 0xED   0x043D   CYRILLIC SMALL LETTER EN */
   U_CyrillicCapitalLetterO,              /* 0xEE   0x043E   CYRILLIC SMALL LETTER O */
   U_CyrillicCapitalLetterPe,             /* 0xEF   0x043F   CYRILLIC SMALL LETTER PE */
   U_CyrillicCapitalLetterEr,             /* 0xF0   0x0440   CYRILLIC SMALL LETTER ER */
   U_CyrillicCapitalLetterEs,             /* 0xF1   0x0441   CYRILLIC SMALL LETTER ES */
   U_CyrillicCapitalLetterTe,             /* 0xF2   0x0442   CYRILLIC SMALL LETTER TE */
   U_CyrillicCapitalLetterU,              /* 0xF3   0x0443   CYRILLIC SMALL LETTER U */
   U_CyrillicCapitalLetterEf,             /* 0xF4   0x0444   CYRILLIC SMALL LETTER EF */
   U_CyrillicCapitalLetterHa,             /* 0xF5   0x0445   CYRILLIC SMALL LETTER HA */
   U_CyrillicCapitalLetterTse,            /* 0xF6   0x0446   CYRILLIC SMALL LETTER TSE */
   U_CyrillicCapitalLetterChe,            /* 0xF7   0x0447   CYRILLIC SMALL LETTER CHE */
   U_CyrillicCapitalLetterSha,            /* 0xF8   0x0448   CYRILLIC SMALL LETTER SHA */
   U_CyrillicCapitalLetterShcha,          /* 0xF9   0x0449   CYRILLIC SMALL LETTER SHCHA */
   U_CyrillicCapitalLetterHardSign,       /* 0xFA   0x044A   CYRILLIC SMALL LETTER HARD SIGN */
   U_CyrillicCapitalLetterYeru,           /* 0xFB   0x044B   CYRILLIC SMALL LETTER YERU */
   U_CyrillicCapitalLetterSoftSign,       /* 0xFC   0x044C   CYRILLIC SMALL LETTER SOFT SIGN */
   U_CyrillicCapitalLetterE,              /* 0xFD   0x044D   CYRILLIC SMALL LETTER E */
   U_CyrillicCapitalLetterYu,             /* 0xFE   0x044E   CYRILLIC SMALL LETTER YU */
   U_CyrillicCapitalLetterYa              /* 0xFF   0x044F   CYRILLIC SMALL LETTER YA */
};










/******************************************************************************
*
*  u_CODE_CP1252[]:
*     Unicode named codepage for Microsoft Windows encoding codepage 1252
*
*  Name:             cp1252 to Unicode table
*  Unicode version:  2.0
*  Table version:    2.01
*  Table format:     Format A
*  Date:             1998-04-15
*  Contact:          Shawn.Steele@microsoft.com
*
******************************************|************************************/

static _UWORD const u_CODE_CP1252[] =          /* CODE_CP1252 */
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

   U_EuroSign,                            /* 0x80  U_EuroSign */
   U_NIL,                                 /* 0x81  --- UNDEFINED --- */
   U_SingleLow9QuotationMark,             /* 0x82  U_SingleLow9QuotationMark */
   U_LatinSmallLetterScriptF,             /* 0x83  U_LatinSmallLetterScriptF */
   U_DoubleLow9QuotationMark,             /* 0x84  U_DoubleLow9QuotationMark */
   U_HorizontalEllipsis,                  /* 0x85  U_HorizontalEllipsis */
   U_Dagger,                              /* 0x86  U_Dagger */
   U_DoubleDagger,                        /* 0x87  U_DoubleDagger */
   U_ModifierLetterCircumflexAccent,      /* 0x88  U_ModifierLetterCircumflexAccent */
   U_PerMilleSign,                        /* 0x89  U_PerMilleSign */
   U_LatinCapitalLetterSWithCaron,        /* 0x8a  U_LatinCapitalLetterSWithCaron */
   U_LeftPointingSingleGuillemet,         /* 0x8b  U_LeftPointingSingleGuillemet */
   U_LatinCapitalLigatureOE,              /* 0x8c  U_LatinCapitalLigatureOE */
   U_NIL,                                 /* 0x8d  --- UNDEFINED --- */
   U_LatinCapitalLetterZWithCaron,        /* 0x8e  U_LatinCapitalLetterZWithCaron */
   U_NIL,                                 /* 0x8f  --- UNDEFINED --- */
                                          
   U_NIL,                                 /* 0x90  --- UNDEFINED --- */
   U_LeftSingleQuotationMark,             /* 0x91  U_LeftSingleQuotationMark */
   U_RightSingleQuotationMark,            /* 0x92  U_RightSingleQuotationMark */
   U_LeftDoubleQuotationMark,             /* 0x93  U_LeftDoubleQuotationMark */
   U_RightDoubleQuotationMark,            /* 0x94  U_RightDoubleQuotationMark */
   U_Bullet,                              /* 0x95  U_Bullet */
   U_EnDash,                              /* 0x96  U_EnDash */
   U_EmDash,                              /* 0x97  U_EmDash */
   U_SmallTilde,                          /* 0x98  U_SmallTilde */
   U_TradeMarkSign,                       /* 0x99  U_TradeMarkSign */
   U_LatinSmallLetterSWithCaron,          /* 0x9a  U_LatinSmallLetterSWithCaron */
   U_RightPointingSingleGuillemet,        /* 0x9b  U_RightPointingSingleGuillemet */
   U_LatinSmallLigatureOE,                /* 0x9c  U_LatinSmallLigatureOE */
   U_NIL,                                 /* 0x9d  --- UNDEFINED --- */
   U_LatinSmallLetterZWithCaron,          /* 0x9e  U_LatinSmallLetterZWithCaron */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0x9f  U_LatinCapitalLetterYWithDiaeresis */
                                          
   U_NB_SP,                               /* 0xa0  U_NB_SP */
   U_InvertedExclamationMark,             /* 0xa1  U_InvertedExclamationMark */
   U_CentSign,                            /* 0xa2  U_CentSign */
   U_PoundSign,                           /* 0xa3  U_PoundSign */
   U_CurrencySign,                        /* 0xa4  U_CurrencySign */
   U_YenSign,                             /* 0xa5  U_YenSign */
   U_BrokenVerticalBar,                   /* 0xa6  U_BrokenVerticalBar */
   U_SectionSign,                         /* 0xa7  U_SectionSign */
   U_Diaeresis,                           /* 0xa8  U_Diaeresis */
   U_CopyrightSign,                       /* 0xa9  U_CopyrightSign */
   U_FeminineOrdinalIndicator,            /* 0xaa  U_FeminineOrdinalIndicator */
   U_LeftPointingGuillemet,               /* 0xab  U_LeftPointingGuillemet */
   U_NotSign,                             /* 0xac  U_NotSign */
   U_SoftHyphen,                          /* 0xad  U_SoftHyphen */
   U_RegisteredSign,                      /* 0xae  U_RegisteredSign */
   U_Macron,                              /* 0xaf  U_Macron */
   
   U_DegreeSign,                          /* 0xb0  U_DegreeSign */
   U_PlusMinusSign,                       /* 0xb1  U_PlusMinusSign */
   U_SuperscriptTwo,                      /* 0xb2  U_SuperscriptTwo */
   U_SuperscriptThree,                    /* 0xb3  U_SuperscriptThree */
   U_AcuteAccent,                         /* 0xb4  U_AcuteAccent */
   U_MicroSign,                           /* 0xb5  U_MicroSign */
   U_ParagraphSign,                       /* 0xb6  U_ParagraphSign */
   U_MiddleDot,                           /* 0xb7  U_MiddleDot */
   U_Cedilla,                             /* 0xb8  U_Cedilla */
   U_SuperscriptOne,                      /* 0xb9  U_SuperscriptOne */
   U_MasculineOrdinalIndicator,           /* 0xba  U_MasculineOrdinalIndicator */
   U_RightPointingGuillemet,              /* 0xbb  U_RightPointingGuillemet */
   U_VulgarFractionOneQuarter,            /* 0xbc  U_VulgarFractionOneQuarter */
   U_VulgarFractionOneHalf,               /* 0xbd  U_VulgarFractionOneHalf */
   U_VulgarFractionThreeQuarters,         /* 0xbe  U_VulgarFractionThreeQuarters */
   U_InvertedQuestionMark,                /* 0xbf  U_InvertedQuestionMark */
                                          
   U_LatinCapitalLetterAWithGrave,        /* 0xc0  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterAWithAcute,        /* 0xc1  U_LatinCapitalLetterAWithAcute */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xc2  U_LatinCapitalLetterAWithCircumflex */
   U_LatinCapitalLetterAWithTilde,        /* 0xc3  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xc4  U_LatinCapitalLetterAWithDiaeresis */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xc5  U_LatinCapitalLetterAWithRingAbove */
   U_LatinCapitalLigatureAE,              /* 0xc6  U_LatinCapitalLigatureAE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xc7  U_LatinCapitalLetterCWithCedilla */
   U_LatinCapitalLetterEWithGrave,        /* 0xc8  U_LatinCapitalLetterEWithGrave */
   U_LatinCapitalLetterEWithAcute,        /* 0xc9  U_LatinCapitalLetterEWithAcute */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xca  U_LatinCapitalLetterEWithCircumflex */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xcb  U_LatinCapitalLetterEWithDiaeresis */
   U_LatinCapitalLetterIWithGrave,        /* 0xcc  U_LatinCapitalLetterIWithGrave */
   U_LatinCapitalLetterIWithAcute,        /* 0xcd  U_LatinCapitalLetterIWithAcute */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xce  U_LatinCapitalLetterIWithCircumflex */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xcf  U_LatinCapitalLetterIWithDiaeresis */
                                          
   U_LatinCapitalLetterEth,               /* 0xd0  U_LatinCapitalLetterEth */
   U_LatinCapitalLetterNWithTilde,        /* 0xd1  U_LatinCapitalLetterNWithTilde */
   U_LatinCapitalLetterOWithGrave,        /* 0xd2  U_LatinCapitalLetterOWithGrave */
   U_LatinCapitalLetterOWithAcute,        /* 0xd3  U_LatinCapitalLetterOWithAcute */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xd4  U_LatinCapitalLetterOWithCircumflex */
   U_LatinCapitalLetterOWithTilde,        /* 0xd5  U_LatinCapitalLetterOWithTilde */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xd6  U_LatinCapitalLetterOWithDiaeresis */
   U_MultiplicationSign,                  /* 0xd7  U_MultiplicationSign */
   U_LatinCapitalLetterOSlash,            /* 0xd8  U_LatinCapitalLetterOSlash */
   U_LatinCapitalLetterUWithGrave,        /* 0xd9  U_LatinCapitalLetterUWithGrave */
   U_LatinCapitalLetterUWithAcute,        /* 0xda  U_LatinCapitalLetterUWithAcute */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xdb  U_LatinCapitalLetterUWithCircumflex */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xdc  U_LatinCapitalLetterUWithDiaeresis */
   U_LatinCapitalLetterYWithAcute,        /* 0xdd  U_LatinCapitalLetterYWithAcute */
   U_LatinCapitalLetterThorn,             /* 0xde  U_LatinCapitalLetterThorn */
   U_LatinSmallLetterSharpS,              /* 0xdf  U_LatinSmallLetterSharpS */
                                          
   U_LatinSmallLetterAWithGrave,          /* 0xe0  U_LatinSmallLetterAWithGrave */
   U_LatinSmallLetterAWithAcute,          /* 0xe1  U_LatinSmallLetterAWithAcute */
   U_LatinSmallLetterAWithCircumflex,     /* 0xe2  U_LatinSmallLetterAWithCircumflex */
   U_LatinSmallLetterAWithTilde,          /* 0xe3  U_LatinSmallLetterAWithTilde */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xe4  U_LatinSmallLetterAWithDiaeresis */
   U_LatinSmallLetterAWithRingAbove,      /* 0xe5  U_LatinSmallLetterAWithRingAbove */
   U_LatinSmallLigatureAE,                /* 0xe6  U_LatinSmallLigatureAE */
   U_LatinSmallLetterCWithCedilla,        /* 0xe7  U_LatinSmallLetterCWithCedilla */
   U_LatinSmallLetterEWithGrave,          /* 0xe8  U_LatinSmallLetterEWithGrave */
   U_LatinSmallLetterEWithAcute,          /* 0xe9  U_LatinSmallLetterEWithAcute */
   U_LatinSmallLetterEWithCircumflex,     /* 0xea  U_LatinSmallLetterEWithCircumflex */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xeb  U_LatinSmallLetterEWithDiaeresis */
   U_LatinSmallLetterIWithGrave,          /* 0xec  U_LatinSmallLetterIWithGrave */
   U_LatinSmallLetterIWithAcute,          /* 0xed  U_LatinSmallLetterIWithAcute */
   U_LatinSmallLetterIWithCircumflex,     /* 0xee  U_LatinSmallLetterIWithCircumflex */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xef  U_LatinSmallLetterIWithDiaeresis */
                                          
   U_LatinSmallLetterEth,                 /* 0xf0  U_LatinSmallLetterEth */
   U_LatinSmallLetterNWithTilde,          /* 0xf1  U_LatinSmallLetterNWithTilde */
   U_LatinSmallLetterOWithGrave,          /* 0xf2  U_LatinSmallLetterOWithGrave */
   U_LatinSmallLetterOWithAcute,          /* 0xf3  U_LatinSmallLetterOWithAcute */
   U_LatinSmallLetterOWithCircumflex,     /* 0xf4  U_LatinSmallLetterOWithCircumflex */
   U_LatinSmallLetterOWithTilde,          /* 0xf5  U_LatinSmallLetterOWithTilde */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xf6  U_LatinSmallLetterOWithDiaeresis */
   U_DivisionSign,                        /* 0xf7  U_DivisionSign */
   U_LatinSmallLetterOSlash,              /* 0xf8  U_LatinSmallLetterOSlash */
   U_LatinSmallLetterUWithGrave,          /* 0xf9  U_LatinSmallLetterUWithGrave */
   U_LatinSmallLetterUWithAcute,          /* 0xfa  U_LatinSmallLetterUWithAcute */
   U_LatinSmallLetterUWithCircumflex,     /* 0xfb  U_LatinSmallLetterUWithCircumflex */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xfc  U_LatinSmallLetterUWithDiaeresis */
   U_LatinSmallLetterYWithAcute,          /* 0xfd  U_LatinSmallLetterYWithAcute */
   U_LatinSmallLetterThorn,               /* 0xfe  U_LatinSmallLetterThorn */
   U_LatinSmallLetterYWithDiaeresis       /* 0xff  U_LatinSmallLetterYWithDiaeresis */
};





/******************************************************************************
*
*  CODE_CP1252_lig[]:
*     list of ligatures:
*
*  CODE_CP1252_lig[0] is the original ligature character
*  CODE_CP1252_lig[1] + CODE_CP1252_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CP1252_lig[][3] =     /* CODE_CP1252 character ligatures */
{
   { U_LatinCapitalLigatureOE,            U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x008c  U_LatinCapitalLigatureOE */
   { U_LatinSmallLigatureOE,              U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x009c  U_LatinSmallLigatureOE */
   { U_LatinCapitalLetterYWithDiaeresis,  U_LatinCapitalLetterY, U_LatinCapitalLetterE},    /* 0x009f  U_LatinCapitalLetterYWithDiaeresis */
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00c4  U_LatinCapitalLetterAWithDiaeresis */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00c6  U_LatinCapitalLigatureAE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE},    /* 0x00cb  U_LatinCapitalLetterEWithDiaeresis */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE},    /* 0x00cf  U_LatinCapitalLetterIWithDiaeresis */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00d6  U_LatinCapitalLetterOWithDiaeresis */
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00d8  U_LatinCapitalLetterOSlash */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x00dc  U_LatinCapitalLetterUWithDiaeresis */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS},    /* 0x00df  U_LatinSmallLetterSharpS */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00e4  U_LatinSmallLetterAWithDiaeresis */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00e6  U_LatinSmallLigatureAE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE},    /* 0x00eb  U_LatinSmallLetterEWithDiaeresis */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE},    /* 0x00ef  U_LatinSmallLetterIWithDiaeresis */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00f6  U_LatinSmallLetterOWithDiaeresis */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00f8  U_LatinSmallLetterOSlash */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x00fc  U_LatinSmallLetterUWithDiaeresis */
   { U_LatinSmallLetterYWithDiaeresis,    U_LatinCapitalLetterY, U_LatinCapitalLetterE},    /* 0x00ff  U_LatinSmallLetterYWithDiaeresis */
   
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CP1252 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*
******************************************|************************************/

static _UWORD const sort_CODE_CP1252[] =      /* CODE_CP1252 */
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

   U_EuroSign,                            /* 0x80  U_EuroSign */
   U_NIL,                                 /* 0x81  --- UNDEFINED --- */
   U_SingleLow9QuotationMark,             /* 0x82  U_SingleLow9QuotationMark */
   U_LatinCapitalLetterF,                 /* 0x83  U_LatinSmallLetterScriptF */
   U_DoubleLow9QuotationMark,             /* 0x84  U_DoubleLow9QuotationMark */
   U_HorizontalEllipsis,                  /* 0x85  U_HorizontalEllipsis */
   U_Dagger,                              /* 0x86  U_Dagger */
   U_DoubleDagger,                        /* 0x87  U_DoubleDagger */
   U_ModifierLetterCircumflexAccent,      /* 0x88  U_ModifierLetterCircumflexAccent */
   U_PerMilleSign,                        /* 0x89  U_PerMilleSign */
   U_LatinCapitalLetterS,                 /* 0x8a  U_LatinCapitalLetterSWithCaron */
   U_LeftPointingSingleGuillemet,         /* 0x8b  U_LeftPointingSingleGuillemet */
   U_LatinCapitalLetterO,                 /* 0x8c  U_LatinCapitalLigatureOE */
   U_NIL,                                 /* 0x8d  --- UNDEFINED --- */
   U_LatinCapitalLetterZ,                 /* 0x8e  U_LatinCapitalLetterZWithCaron */
   U_NIL,                                 /* 0x8f  --- UNDEFINED --- */
                                          
   U_NIL,                                 /* 0x90  --- UNDEFINED --- */
   U_LeftSingleQuotationMark,             /* 0x91  U_LeftSingleQuotationMark */
   U_RightSingleQuotationMark,            /* 0x92  U_RightSingleQuotationMark */
   U_LeftDoubleQuotationMark,             /* 0x93  U_LeftDoubleQuotationMark */
   U_RightDoubleQuotationMark,            /* 0x94  U_RightDoubleQuotationMark */
   U_Bullet,                              /* 0x95  U_Bullet */
   U_EnDash,                              /* 0x96  U_EnDash */
   U_EmDash,                              /* 0x97  U_EmDash */
   U_SmallTilde,                          /* 0x98  U_SmallTilde */
   U_TradeMarkSign,                       /* 0x99  U_TradeMarkSign */
   U_LatinCapitalLetterS,                 /* 0x9a  U_LatinSmallLetterSWithCaron */
   U_RightPointingSingleGuillemet,        /* 0x9b  U_RightPointingSingleGuillemet */
   U_LatinCapitalLetterO,                 /* 0x9c  U_LatinSmallLigatureOE */
   U_NIL,                                 /* 0x9d  --- UNDEFINED --- */
   U_LatinCapitalLetterZ,                 /* 0x9e  U_LatinSmallLetterZWithCaron */
   U_LatinCapitalLetterY,                 /* 0x9f  U_LatinCapitalLetterYWithDiaeresis */
                                          
   U_NB_SP,                               /* 0xa0  U_NB_SP */
   U_InvertedExclamationMark,             /* 0xa1  U_InvertedExclamationMark */
   U_CentSign,                            /* 0xa2  U_CentSign */
   U_PoundSign,                           /* 0xa3  U_PoundSign */
   U_CurrencySign,                        /* 0xa4  U_CurrencySign */
   U_YenSign,                             /* 0xa5  U_YenSign */
   U_BrokenVerticalBar,                   /* 0xa6  U_BrokenVerticalBar */
   U_SectionSign,                         /* 0xa7  U_SectionSign */
   U_Diaeresis,                           /* 0xa8  U_Diaeresis */
   U_CopyrightSign,                       /* 0xa9  U_CopyrightSign */
   U_FeminineOrdinalIndicator,            /* 0xaa  U_FeminineOrdinalIndicator */
   U_LeftPointingGuillemet,               /* 0xab  U_LeftPointingGuillemet */
   U_NotSign,                             /* 0xac  U_NotSign */
   U_SoftHyphen,                          /* 0xad  U_SoftHyphen */
   U_RegisteredSign,                      /* 0xae  U_RegisteredSign */
   U_Macron,                              /* 0xaf  U_Macron */
   
   U_DegreeSign,                          /* 0xb0  U_DegreeSign */
   U_PlusMinusSign,                       /* 0xb1  U_PlusMinusSign */
   U_SuperscriptTwo,                      /* 0xb2  U_SuperscriptTwo */
   U_SuperscriptThree,                    /* 0xb3  U_SuperscriptThree */
   U_AcuteAccent,                         /* 0xb4  U_AcuteAccent */
   U_MicroSign,                           /* 0xb5  U_MicroSign */
   U_ParagraphSign,                       /* 0xb6  U_ParagraphSign */
   U_MiddleDot,                           /* 0xb7  U_MiddleDot */
   U_Cedilla,                             /* 0xb8  U_Cedilla */
   U_SuperscriptOne,                      /* 0xb9  U_SuperscriptOne */
   U_MasculineOrdinalIndicator,           /* 0xba  U_MasculineOrdinalIndicator */
   U_RightPointingGuillemet,              /* 0xbb  U_RightPointingGuillemet */
   U_VulgarFractionOneQuarter,            /* 0xbc  U_VulgarFractionOneQuarter */
   U_VulgarFractionOneHalf,               /* 0xbd  U_VulgarFractionOneHalf */
   U_VulgarFractionThreeQuarters,         /* 0xbe  U_VulgarFractionThreeQuarters */
   U_InvertedQuestionMark,                /* 0xbf  U_InvertedQuestionMark */
                                          
   U_LatinCapitalLetterA,                 /* 0xc0  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterA,                 /* 0xc1  U_LatinCapitalLetterAWithAcute */
   U_LatinCapitalLetterA,                 /* 0xc2  U_LatinCapitalLetterAWithCircumflex */
   U_LatinCapitalLetterA,                 /* 0xc3  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterA,                 /* 0xc4  U_LatinCapitalLetterAWithDiaeresis */
   U_LatinCapitalLetterA,                 /* 0xc5  U_LatinCapitalLetterAWithRingAbove */
   U_LatinCapitalLetterA,                 /* 0xc6  U_LatinCapitalLigatureAE */
   U_LatinCapitalLetterC,                 /* 0xc7  U_LatinCapitalLetterCWithCedilla */
   U_LatinCapitalLetterE,                 /* 0xc8  U_LatinCapitalLetterEWithGrave */
   U_LatinCapitalLetterE,                 /* 0xc9  U_LatinCapitalLetterEWithAcute */
   U_LatinCapitalLetterE,                 /* 0xca  U_LatinCapitalLetterEWithCircumflex */
   U_LatinCapitalLetterE,                 /* 0xcb  U_LatinCapitalLetterEWithDiaeresis */
   U_LatinCapitalLetterI,                 /* 0xcc  U_LatinCapitalLetterIWithGrave */
   U_LatinCapitalLetterI,                 /* 0xcd  U_LatinCapitalLetterIWithAcute */
   U_LatinCapitalLetterI,                 /* 0xce  U_LatinCapitalLetterIWithCircumflex */
   U_LatinCapitalLetterI,                 /* 0xcf  U_LatinCapitalLetterIWithDiaeresis */
                                          
   U_LatinCapitalLetterEth,               /* 0xd0  U_LatinCapitalLetterEth */
   U_LatinCapitalLetterN,                 /* 0xd1  U_LatinCapitalLetterNWithTilde */
   U_LatinCapitalLetterO,                 /* 0xd2  U_LatinCapitalLetterOWithGrave */
   U_LatinCapitalLetterO,                 /* 0xd3  U_LatinCapitalLetterOWithAcute */
   U_LatinCapitalLetterO,                 /* 0xd4  U_LatinCapitalLetterOWithCircumflex */
   U_LatinCapitalLetterO,                 /* 0xd5  U_LatinCapitalLetterOWithTilde */
   U_LatinCapitalLetterO,                 /* 0xd6  U_LatinCapitalLetterOWithDiaeresis */
   U_MultiplicationSign,                  /* 0xd7  U_MultiplicationSign */
   U_LatinCapitalLetterO,                 /* 0xd8  U_LatinCapitalLetterOSlash */
   U_LatinCapitalLetterU,                 /* 0xd9  U_LatinCapitalLetterUWithGrave */
   U_LatinCapitalLetterU,                 /* 0xda  U_LatinCapitalLetterUWithAcute */
   U_LatinCapitalLetterU,                 /* 0xdb  U_LatinCapitalLetterUWithCircumflex */
   U_LatinCapitalLetterU,                 /* 0xdc  U_LatinCapitalLetterUWithDiaeresis */
   U_LatinCapitalLetterY,                 /* 0xdd  U_LatinCapitalLetterYWithAcute */
   U_LatinCapitalLetterThorn,             /* 0xde  U_LatinCapitalLetterThorn */
   U_LatinCapitalLetterS,                 /* 0xdf  U_LatinSmallLetterSharpS */
                                          
   U_LatinCapitalLetterA,                 /* 0xe0  U_LatinSmallLetterAWithGrave */
   U_LatinCapitalLetterA,                 /* 0xe1  U_LatinSmallLetterAWithAcute */
   U_LatinCapitalLetterA,                 /* 0xe2  U_LatinSmallLetterAWithCircumflex */
   U_LatinCapitalLetterA,                 /* 0xe3  U_LatinSmallLetterAWithTilde */
   U_LatinCapitalLetterA,                 /* 0xe4  U_LatinSmallLetterAWithDiaeresis */
   U_LatinCapitalLetterA,                 /* 0xe5  U_LatinSmallLetterAWithRingAbove */
   U_LatinCapitalLetterA,                 /* 0xe6  U_LatinSmallLigatureAE */
   U_LatinCapitalLetterC,                 /* 0xe7  U_LatinSmallLetterCWithCedilla */
   U_LatinCapitalLetterE,                 /* 0xe8  U_LatinSmallLetterEWithGrave */
   U_LatinCapitalLetterE,                 /* 0xe9  U_LatinSmallLetterEWithAcute */
   U_LatinCapitalLetterE,                 /* 0xea  U_LatinSmallLetterEWithCircumflex */
   U_LatinCapitalLetterE,                 /* 0xeb  U_LatinSmallLetterEWithDiaeresis */
   U_LatinCapitalLetterI,                 /* 0xec  U_LatinSmallLetterIWithGrave */
   U_LatinCapitalLetterI,                 /* 0xed  U_LatinSmallLetterIWithAcute */
   U_LatinCapitalLetterI,                 /* 0xee  U_LatinSmallLetterIWithCircumflex */
   U_LatinCapitalLetterI,                 /* 0xef  U_LatinSmallLetterIWithDiaeresis */
                                          
   U_LatinSmallLetterEth,                 /* 0xf0  U_LatinSmallLetterEth */
   U_LatinCapitalLetterN,                 /* 0xf1  U_LatinSmallLetterNWithTilde */
   U_LatinCapitalLetterO,                 /* 0xf2  U_LatinSmallLetterOWithGrave */
   U_LatinCapitalLetterO,                 /* 0xf3  U_LatinSmallLetterOWithAcute */
   U_LatinCapitalLetterO,                 /* 0xf4  U_LatinSmallLetterOWithCircumflex */
   U_LatinCapitalLetterO,                 /* 0xf5  U_LatinSmallLetterOWithTilde */
   U_LatinCapitalLetterO,                 /* 0xf6  U_LatinSmallLetterOWithDiaeresis */
   U_DivisionSign,                        /* 0xf7  U_DivisionSign */
   U_LatinCapitalLetterO,                 /* 0xf8  U_LatinSmallLetterOSlash */
   U_LatinCapitalLetterU,                 /* 0xf9  U_LatinSmallLetterUWithGrave */
   U_LatinCapitalLetterU,                 /* 0xfa  U_LatinSmallLetterUWithAcute */
   U_LatinCapitalLetterU,                 /* 0xfb  U_LatinSmallLetterUWithCircumflex */
   U_LatinCapitalLetterU,                 /* 0xfc  U_LatinSmallLetterUWithDiaeresis */
   U_LatinCapitalLetterY,                 /* 0xfd  U_LatinSmallLetterYWithAcute */
   U_LatinSmallLetterThorn,               /* 0xfe  U_LatinSmallLetterThorn */
   U_LatinCapitalLetterY                  /* 0xff  U_LatinSmallLetterYWithDiaeresis */
};










/******************************************************************************
*
*  u_CODE_CP1253[]:
*     Unicode named codepage for Microsoft Windows encoding codepage 1253 ("Greek")
*
*  Name:             cp1253 to Unicode table
*  Unicode version:  2.0
*  Table version:    2.01
*  Table format:     Format A
*  Date:             1998-04-15
*  Contact:          Shawn.Steele@microsoft.com
*
******************************************|************************************/

static _UWORD const u_CODE_CP1253[] =          /* CODE_CP1253 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_LatinSmallLetterScriptF,             /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_NIL,                                 /* 0x88            UNDEFINED */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_NIL,                                 /* 0x8A            UNDEFINED */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x8C            UNDEFINED */
   U_NIL,                                 /* 0x8D            UNDEFINED */
   U_NIL,                                 /* 0x8E            UNDEFINED */
   U_NIL,                                 /* 0x8F            UNDEFINED */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_NIL,                                 /* 0x98            UNDEFINED */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_NIL,                                 /* 0x9A            UNDEFINED */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x9C            UNDEFINED */
   U_NIL,                                 /* 0x9D            UNDEFINED */
   U_NIL,                                 /* 0x9E            UNDEFINED */
   U_NIL,                                 /* 0x9F            UNDEFINED */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_GreekDialytikaTonos,                 /* 0xA1   0x0385   GREEK DIALYTIKA TONOS */
   U_GreekCapitalLetterAlphaWithTonos,    /* 0xA2   0x0386   GREEK CAPITAL LETTER ALPHA WITH TONOS */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_SectionSign,                         /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_NIL,                                 /* 0xAA            UNDEFINED */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_HorizontalBar,                       /* 0xAF   0x2015   HORIZONTAL BAR */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_GreekTonus,                          /* 0xB4   0x0384   GREEK TONOS */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
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
   U_NIL,                                 /* 0xD2            UNDEFINED */
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
   U_NIL,                                 /* 0xFF            UNDEFINED */
};





/******************************************************************************
*
*  CODE_CP1253_lig[]:
*     list of ligatures:
*
*  CODE_CP1253_lig[0] is the original ligature character
*  CODE_CP1253_lig[1] + CODE_CP1253_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CP1253_lig[][3] =     /* CODE_CP1253 character ligatures */
{
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CP1253 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_CP1253[] =       /* CODE_CP1253 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_LatinCapitalLetterF,                 /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_NIL,                                 /* 0x88            UNDEFINED */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_NIL,                                 /* 0x8A            UNDEFINED */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x8C            UNDEFINED */
   U_NIL,                                 /* 0x8D            UNDEFINED */
   U_NIL,                                 /* 0x8E            UNDEFINED */
   U_NIL,                                 /* 0x8F            UNDEFINED */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_NIL,                                 /* 0x98            UNDEFINED */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_NIL,                                 /* 0x9A            UNDEFINED */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x9C            UNDEFINED */
   U_NIL,                                 /* 0x9D            UNDEFINED */
   U_NIL,                                 /* 0x9E            UNDEFINED */
   U_NIL,                                 /* 0x9F            UNDEFINED */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_GreekDialytikaTonos,                 /* 0xA1   0x0385   GREEK DIALYTIKA TONOS */
   U_GreekCapitalLetterAlpha,             /* 0xA2   0x0386   GREEK CAPITAL LETTER ALPHA WITH TONOS */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_SectionSign,                         /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_NIL,                                 /* 0xAA            UNDEFINED */
   U_LeftPointingGuillemet,               /* 0xAB   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_NotSign,                             /* 0xAC   0x00AC   NOT SIGN */
   U_SoftHyphen,                          /* 0xAD   0x00AD   SOFT HYPHEN */
   U_RegisteredSign,                      /* 0xAE   0x00AE   REGISTERED SIGN */
   U_HorizontalBar,                       /* 0xAF   0x2015   HORIZONTAL BAR */
   U_DegreeSign,                          /* 0xB0   0x00B0   DEGREE SIGN */
   U_PlusMinusSign,                       /* 0xB1   0x00B1   PLUS-MINUS SIGN */
   U_SuperscriptTwo,                      /* 0xB2   0x00B2   SUPERSCRIPT TWO */
   U_SuperscriptThree,                    /* 0xB3   0x00B3   SUPERSCRIPT THREE */
   U_GreekTonus,                          /* 0xB4   0x0384   GREEK TONOS */
   U_MicroSign,                           /* 0xB5   0x00B5   MICRO SIGN */
   U_ParagraphSign,                       /* 0xB6   0x00B6   PILCROW SIGN */
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
   U_NIL,                                 /* 0xD2            UNDEFINED */
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
   U_NIL,                                 /* 0xFF            UNDEFINED */
};










/******************************************************************************
*
*  u_CODE_CP1254[]:
*     Unicode named codepage for Microsoft Windows encoding codepage 1254 ("Turkish")
*
*  Name:             cp1254 to Unicode table
*  Unicode version:  2.0
*  Table version:    2.01
*  Table format:     Format A
*  Date:             1998-04-15
*  Contact:          Shawn.Steele@microsoft.com
*
******************************************|************************************/

static _UWORD const u_CODE_CP1254[] =          /* CODE_CP1254 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_LatinSmallLetterScriptF,             /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_ModifierLetterCircumflexAccent,      /* 0x88   0x02C6   MODIFIER LETTER CIRCUMFLEX ACCENT */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_LatinCapitalLetterSWithCaron,        /* 0x8A   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLigatureOE,              /* 0x8C   0x0152   LATIN CAPITAL LIGATURE OE */
   U_NIL,                                 /* 0x8D            UNDEFINED */
   U_NIL,                                 /* 0x8E            UNDEFINED */
   U_NIL,                                 /* 0x8F            UNDEFINED */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_SmallTilde,                          /* 0x98   0x02DC   SMALL TILDE */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_LatinSmallLetterSWithCaron,          /* 0x9A   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinSmallLigatureOE,                /* 0x9C   0x0153   LATIN SMALL LIGATURE OE */
   U_NIL,                                 /* 0x9D            UNDEFINED */
   U_NIL,                                 /* 0x9E            UNDEFINED */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0x9F   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_YenSign,                             /* 0xA6   0x00A6   BROKEN BAR */
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
   U_SuperscriptOne,                      /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneQuarter,            /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
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
*  CODE_CP1254_lig[]:
*     list of ligatures:
*
*  CODE_CP1254_lig[0] is the original ligature character
*  CODE_CP1254_lig[1] + CODE_CP1254_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CP1254_lig[][3] =     /* CODE_CP1254 character ligatures */
{
   { U_LatinCapitalLigatureOE,            U_LatinCapitalLetterO, U_LatinCapitalLetterE }, /* 0x8C   0x0152   LATIN CAPITAL LIGATURE OE */
   { U_LatinSmallLigatureOE,              U_LatinCapitalLetterO, U_LatinCapitalLetterE }, /* 0x9C   0x0153   LATIN SMALL LIGATURE OE */
   { U_LatinCapitalLetterYWithDiaeresis,  U_LatinCapitalLetterY, U_LatinCapitalLetterE }, /* 0x9F   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE }, /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO }, /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE }, /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE }, /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE }, /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE }, /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE }, /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE }, /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS }, /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE }, /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterAWithRingAbove,    U_LatinCapitalLetterA, U_LatinCapitalLetterO }, /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE }, /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE }, /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE }, /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE }, /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE }, /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE }, /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterYWithDiaeresis,    U_LatinCapitalLetterY, U_LatinCapitalLetterE }, /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
   
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CP1254 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_CP1254[] =       /* CODE_CP1254 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_LatinCapitalLetterF,                 /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_ModifierLetterCircumflexAccent,      /* 0x88   0x02C6   MODIFIER LETTER CIRCUMFLEX ACCENT */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_LatinCapitalLetterS,                 /* 0x8A   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterO,                 /* 0x8C   0x0152   LATIN CAPITAL LIGATURE OE */
   U_NIL,                                 /* 0x8D            UNDEFINED */
   U_NIL,                                 /* 0x8E            UNDEFINED */
   U_NIL,                                 /* 0x8F            UNDEFINED */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_SmallTilde,                          /* 0x98   0x02DC   SMALL TILDE */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_LatinCapitalLetterS,                 /* 0x9A   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterO,                 /* 0x9C   0x0153   LATIN SMALL LIGATURE OE */
   U_NIL,                                 /* 0x9D            UNDEFINED */
   U_NIL,                                 /* 0x9E            UNDEFINED */
   U_LatinCapitalLetterY,                 /* 0x9F   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_YenSign,                             /* 0xA6   0x00A6   BROKEN BAR */
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
   U_SuperscriptOne,                      /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneQuarter,            /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
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
   U_LatinCapitalLetterI,                 /* 0xDD   0x0130   LATIN CAPITAL LETTER I WITH DOT ABOVE */
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
*  u_CODE_CP1255[]:
*     Unicode named codepage for Microsoft Windows encoding codepage 1255 ("Hebrew")
*
*  Name:             cp1255 to Unicode table
*  Unicode version:  2.0
*  Table version:    2.01
*  Table format:     Format A
*  Date:             1998-04-15
*  Contact:          Shawn.Steele@microsoft.com
*
******************************************|************************************/

static _UWORD const u_CODE_CP1255[] =          /* CODE_CP1255 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_NIL,                                 /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_ModifierLetterCircumflexAccent,      /* 0x88   0x02C6   MODIFIER LETTER CIRCUMFLEX ACCENT */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_NIL,                                 /* 0x8A            UNDEFINED */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x8C            UNDEFINED */
   U_NIL,                                 /* 0x8D            UNDEFINED */
   U_NIL,                                 /* 0x8E            UNDEFINED */
   U_NIL,                                 /* 0x8F            UNDEFINED */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_SmallTilde,                          /* 0x98   0x02DC   SMALL TILDE */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_NIL,                                 /* 0x9A            UNDEFINED */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x9C            UNDEFINED */
   U_NIL,                                 /* 0x9D            UNDEFINED */
   U_NIL,                                 /* 0x9E            UNDEFINED */
   U_NIL,                                 /* 0x9F            UNDEFINED */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_NewShequelSign,                      /* 0xA4   0x20AA   NEW SHEQEL SIGN */
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
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_HebrewPointSheva,                    /* 0xC0   0x05B0   HEBREW POINT SHEVA */
   U_HebrewPointHatafSegol,               /* 0xC1   0x05B1   HEBREW POINT HATAF SEGOL */
   U_HebrewPointHatafPatah,               /* 0xC2   0x05B2   HEBREW POINT HATAF PATAH */
   U_HebrewPointHatafQamats,              /* 0xC3   0x05B3   HEBREW POINT HATAF QAMATS */
   U_HebrewPointHiriq,                    /* 0xC4   0x05B4   HEBREW POINT HIRIQ */
   U_HebrewPointTsere,                    /* 0xC5   0x05B5   HEBREW POINT TSERE */
   U_HebrewPointSegol,                    /* 0xC6   0x05B6   HEBREW POINT SEGOL */
   U_HebrewPointPatah,                    /* 0xC7   0x05B7   HEBREW POINT PATAH */
   U_HebrewPointQamats,                   /* 0xC8   0x05B8   HEBREW POINT QAMATS */
   U_HebrewPointHolam,                    /* 0xC9   0x05B9   HEBREW POINT HOLAM */
   U_NIL,                                 /* 0xCA      UNDEFINED */
   U_HebrewPointQubuts,                   /* 0xCB   0x05BB   HEBREW POINT QUBUTS */
   U_HebrewPointDageshOrMapiq,            /* 0xCC   0x05BC   HEBREW POINT DAGESH OR MAPIQ */
   U_HebrewPointMeteg,                    /* 0xCD   0x05BD   HEBREW POINT METEG */
   U_HebrewPunctuationMaqaf,              /* 0xCE   0x05BE   HEBREW PUNCTUATION MAQAF */
   U_HebrewPointRafe,                     /* 0xCF   0x05BF   HEBREW POINT RAFE */
   U_HebrewPunctuationPaseq,              /* 0xD0   0x05C0   HEBREW PUNCTUATION PASEQ */
   U_HebrewPointShinDot,                  /* 0xD1   0x05C1   HEBREW POINT SHIN DOT */
   U_HebrewPointSinDot,                   /* 0xD2   0x05C2   HEBREW POINT SIN DOT */
   U_HebrewPunctuationSofPasuq,           /* 0xD3   0x05C3   HEBREW PUNCTUATION SOF PASUQ */
   U_HebrewLigatureYiddishDoubleVav,      /* 0xD4   0x05F0   HEBREW LIGATURE YIDDISH DOUBLE VAV */
   U_HebrewLigatureYiddishVavYod,         /* 0xD5   0x05F1   HEBREW LIGATURE YIDDISH VAV YOD */
   U_HebrewLigatureYiddishDoubleYod,      /* 0xD6   0x05F2   HEBREW LIGATURE YIDDISH DOUBLE YOD */
   U_HebrewPunctuationGeresh,             /* 0xD7   0x05F3   HEBREW PUNCTUATION GERESH */
   U_HebrewPunctuationGershayim,          /* 0xD8   0x05F4   HEBREW PUNCTUATION GERSHAYIM */
   U_NIL,                                 /* 0xD9            UNDEFINED */
   U_NIL,                                 /* 0xDA            UNDEFINED */
   U_NIL,                                 /* 0xDB            UNDEFINED */
   U_NIL,                                 /* 0xDC            UNDEFINED */
   U_NIL,                                 /* 0xDD            UNDEFINED */
   U_NIL,                                 /* 0xDE            UNDEFINED */
   U_NIL,                                 /* 0xDF            UNDEFINED */
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
   U_NIL,                                 /* 0xFB            UNDEFINED */
   U_NIL,                                 /* 0xFC            UNDEFINED */
   U_LeftToRightMark,                     /* 0xFD   0x200E   LEFT-TO-RIGHT MARK */
   U_RightToLeftMark,                     /* 0xFE   0x200F   RIGHT-TO-LEFT MARK */
   U_NIL                                  /* 0xFF            UNDEFINED */
};





/******************************************************************************
*
*  CODE_CP1255_lig[]:
*     list of ligatures:
*
*  CODE_CP1255_lig[0] is the original ligature character
*  CODE_CP1255_lig[1] + CODE_CP1255_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CP1255_lig[][3] =     /* CODE_CP1255 character ligatures */
{
   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CP1255 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_CP1255[] =       /* CODE_CP1255 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_NIL,                                 /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_ModifierLetterCircumflexAccent,      /* 0x88   0x02C6   MODIFIER LETTER CIRCUMFLEX ACCENT */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_NIL,                                 /* 0x8A            UNDEFINED */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x8C            UNDEFINED */
   U_NIL,                                 /* 0x8D            UNDEFINED */
   U_NIL,                                 /* 0x8E            UNDEFINED */
   U_NIL,                                 /* 0x8F            UNDEFINED */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_SmallTilde,                          /* 0x98   0x02DC   SMALL TILDE */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_NIL,                                 /* 0x9A            UNDEFINED */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x9C            UNDEFINED */
   U_NIL,                                 /* 0x9D            UNDEFINED */
   U_NIL,                                 /* 0x9E            UNDEFINED */
   U_NIL,                                 /* 0x9F            UNDEFINED */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_InvertedExclamationMark,             /* 0xA1   0x00A1   INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_NewShequelSign,                      /* 0xA4   0x20AA   NEW SHEQEL SIGN */
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
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_HebrewPointSheva,                    /* 0xC0   0x05B0   HEBREW POINT SHEVA */
   U_HebrewPointHatafSegol,               /* 0xC1   0x05B1   HEBREW POINT HATAF SEGOL */
   U_HebrewPointHatafPatah,               /* 0xC2   0x05B2   HEBREW POINT HATAF PATAH */
   U_HebrewPointHatafQamats,              /* 0xC3   0x05B3   HEBREW POINT HATAF QAMATS */
   U_HebrewPointHiriq,                    /* 0xC4   0x05B4   HEBREW POINT HIRIQ */
   U_HebrewPointTsere,                    /* 0xC5   0x05B5   HEBREW POINT TSERE */
   U_HebrewPointSegol,                    /* 0xC6   0x05B6   HEBREW POINT SEGOL */
   U_HebrewPointPatah,                    /* 0xC7   0x05B7   HEBREW POINT PATAH */
   U_HebrewPointQamats,                   /* 0xC8   0x05B8   HEBREW POINT QAMATS */
   U_HebrewPointHolam,                    /* 0xC9   0x05B9   HEBREW POINT HOLAM */
   U_NIL,                                 /* 0xCA      UNDEFINED */
   U_HebrewPointQubuts,                   /* 0xCB   0x05BB   HEBREW POINT QUBUTS */
   U_HebrewPointDageshOrMapiq,            /* 0xCC   0x05BC   HEBREW POINT DAGESH OR MAPIQ */
   U_HebrewPointMeteg,                    /* 0xCD   0x05BD   HEBREW POINT METEG */
   U_HebrewPunctuationMaqaf,              /* 0xCE   0x05BE   HEBREW PUNCTUATION MAQAF */
   U_HebrewPointRafe,                     /* 0xCF   0x05BF   HEBREW POINT RAFE */
   U_HebrewPunctuationPaseq,              /* 0xD0   0x05C0   HEBREW PUNCTUATION PASEQ */
   U_HebrewPointShinDot,                  /* 0xD1   0x05C1   HEBREW POINT SHIN DOT */
   U_HebrewPointSinDot,                   /* 0xD2   0x05C2   HEBREW POINT SIN DOT */
   U_HebrewPunctuationSofPasuq,           /* 0xD3   0x05C3   HEBREW PUNCTUATION SOF PASUQ */
   U_HebrewLigatureYiddishDoubleVav,      /* 0xD4   0x05F0   HEBREW LIGATURE YIDDISH DOUBLE VAV */
   U_HebrewLigatureYiddishVavYod,         /* 0xD5   0x05F1   HEBREW LIGATURE YIDDISH VAV YOD */
   U_HebrewLigatureYiddishDoubleYod,      /* 0xD6   0x05F2   HEBREW LIGATURE YIDDISH DOUBLE YOD */
   U_HebrewPunctuationGeresh,             /* 0xD7   0x05F3   HEBREW PUNCTUATION GERESH */
   U_HebrewPunctuationGershayim,          /* 0xD8   0x05F4   HEBREW PUNCTUATION GERSHAYIM */
   U_NIL,                                 /* 0xD9            UNDEFINED */
   U_NIL,                                 /* 0xDA            UNDEFINED */
   U_NIL,                                 /* 0xDB            UNDEFINED */
   U_NIL,                                 /* 0xDC            UNDEFINED */
   U_NIL,                                 /* 0xDD            UNDEFINED */
   U_NIL,                                 /* 0xDE            UNDEFINED */
   U_NIL,                                 /* 0xDF            UNDEFINED */
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
   U_NIL,                                 /* 0xFB            UNDEFINED */
   U_NIL,                                 /* 0xFC            UNDEFINED */
   U_LeftToRightMark,                     /* 0xFD   0x200E   LEFT-TO-RIGHT MARK */
   U_RightToLeftMark,                     /* 0xFE   0x200F   RIGHT-TO-LEFT MARK */
   U_NIL                                  /* 0xFF            UNDEFINED */
};










/******************************************************************************
*
*  u_CODE_CP1256[]:
*     Unicode named codepage for Microsoft Windows encoding codepage 1256 ("Arabic")
*
*  Name:             cp1256 to Unicode table
*  Unicode version:  2.0
*  Table version:    2.01
*  Table format:     Format A
*  Date:             1999-05-01
*  Contact:          Shawn.Steele@microsoft.com
*
******************************************|************************************/

static _UWORD const u_CODE_CP1256[] =          /* CODE_CP1256 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_ArabicLetterPeh,                     /* 0x81   0x067E   ARABIC LETTER PEH */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_LatinSmallLetterScriptF,             /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_ModifierLetterCircumflexAccent,      /* 0x88   0x02C6   MODIFIER LETTER CIRCUMFLEX ACCENT */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_ArabicLetterTteh,                    /* 0x8A   0x0679   ARABIC LETTER TTEH */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLigatureOE,              /* 0x8C   0x0152   LATIN CAPITAL LIGATURE OE */
   U_ArabicLetterTcheh,                   /* 0x8D   0x0686   ARABIC LETTER TCHEH */
   U_ArabicLetterJeh,                     /* 0x8E   0x0698   ARABIC LETTER JEH */
   U_ArabicLetterDdal,                    /* 0x8F   0x0688   ARABIC LETTER DDAL */
   U_ArabicLetterGaf,                     /* 0x90   0x06AF   ARABIC LETTER GAF */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_ArabicLetterKeheh,                   /* 0x98   0x06A9   ARABIC LETTER KEHEH */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_ArabicLetterRreh,                    /* 0x9A   0x0691   ARABIC LETTER RREH */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinSmallLigatureOE,                /* 0x9C   0x0153   LATIN SMALL LIGATURE OE */
   U_ZeroWidthNonJoiner,                  /* 0x9D   0x200C   ZERO WIDTH NON-JOINER */
   U_ZeroWidthJoiner,                     /* 0x9E   0x200D   ZERO WIDTH JOINER */
   U_ArabicLetterNoonGhunna,              /* 0x9F   0x06BA   ARABIC LETTER NOON GHUNNA */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_ArabicComma,                         /* 0xA1   0x060C   ARABIC COMMA */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_ArabicLetterHehDoachashmee,          /* 0xAA   0x06BE   ARABIC LETTER HEH DOACHASHMEE */
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
   U_ArabicSemicolon,                     /* 0xBA   0x061B   ARABIC SEMICOLON */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_ArabicQuestionMark,                  /* 0xBF   0x061F   ARABIC QUESTION MARK */
   U_ArabicLetterHehGoal,                 /* 0xC0   0x06C1   ARABIC LETTER HEH GOAL */
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
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_ArabicLetterTah,                     /* 0xD8   0x0637   ARABIC LETTER TAH */
   U_ArabicLetterZah,                     /* 0xD9   0x0638   ARABIC LETTER ZAH */
   U_ArabicLetterAin,                     /* 0xDA   0x0639   ARABIC LETTER AIN */
   U_ArabicLetterGhain,                   /* 0xDB   0x063A   ARABIC LETTER GHAIN */
   U_ArabicTatweel,                       /* 0xDC   0x0640   ARABIC TATWEEL */
   U_ArabicLetterFeh,                     /* 0xDD   0x0641   ARABIC LETTER FEH */
   U_ArabicLetterQaf,                     /* 0xDE   0x0642   ARABIC LETTER QAF */
   U_ArabicLetterKaf,                     /* 0xDF   0x0643   ARABIC LETTER KAF */
   U_LatinSmallLetterAWithGrave,          /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_ArabicLetterLam,                     /* 0xE1   0x0644   ARABIC LETTER LAM */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_ArabicLetterMeem,                    /* 0xE3   0x0645   ARABIC LETTER MEEM */
   U_ArabicLetterNoon,                    /* 0xE4   0x0646   ARABIC LETTER NOON */
   U_ArabicLetterHeh,                     /* 0xE5   0x0647   ARABIC LETTER HEH */
   U_ArabicLetterWaw,                     /* 0xE6   0x0648   ARABIC LETTER WAW */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithGrave,          /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithCircumflex,     /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_ArabicLetterAlefMaksura,             /* 0xEC   0x0649   ARABIC LETTER ALEF MAKSURA */
   U_ArabicLetterYeh,                     /* 0xED   0x064A   ARABIC LETTER YEH */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_ArabicFathatan,                      /* 0xF0   0x064B   ARABIC FATHATAN */
   U_ArabicDammatan,                      /* 0xF1   0x064C   ARABIC DAMMATAN */
   U_ArabicKasratan,                      /* 0xF2   0x064D   ARABIC KASRATAN */
   U_ArabicFatha,                         /* 0xF3   0x064E   ARABIC FATHA */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_ArabicDamma,                         /* 0xF5   0x064F   ARABIC DAMMA */
   U_ArabicKasra,                         /* 0xF6   0x0650   ARABIC KASRA */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_ArabicShadda,                        /* 0xF8   0x0651   ARABIC SHADDA */
   U_LatinSmallLetterUWithGrave,          /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_ArabicSukun,                         /* 0xFA   0x0652   ARABIC SUKUN */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LeftToRightMark,                     /* 0xFD   0x200E   LEFT-TO-RIGHT MARK */
   U_RightToLeftMark,                     /* 0xFE   0x200F   RIGHT-TO-LEFT MARK */
   U_ArabicLetterYehBarree                /* 0xFF   0x06D2   ARABIC LETTER YEH BARREE */
};





/******************************************************************************
*
*  CODE_CP1256_lig[]:
*     list of ligatures:
*
*  CODE_CP1256_lig[0] is the original ligature character
*  CODE_CP1256_lig[1] + CODE_CP1256_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CP1256_lig[][3] =     /* CODE_CP1256 character ligatures */
{
   { U_LatinCapitalLigatureOE,         U_LatinCapitalLetterO, U_LatinCapitalLetterE },   /* 0x8C   0x0152   LATIN CAPITAL LIGATURE OE */
   { U_LatinSmallLigatureOE,           U_LatinCapitalLetterO, U_LatinCapitalLetterE },   /* 0x9C   0x0153   LATIN SMALL LIGATURE OE */
   { U_LatinSmallLetterEWithDiaeresis, U_LatinCapitalLetterE, U_LatinCapitalLetterE },   /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis, U_LatinCapitalLetterI, U_LatinCapitalLetterE },   /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterUWithDiaeresis, U_LatinCapitalLetterU, U_LatinCapitalLetterE },   /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */

   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CP1256 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_CP1256[] =       /* CODE_CP1256 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_ArabicLetterPeh,                     /* 0x81   0x067E   ARABIC LETTER PEH */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_LatinCapitalLetterF,                 /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_ModifierLetterCircumflexAccent,      /* 0x88   0x02C6   MODIFIER LETTER CIRCUMFLEX ACCENT */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_ArabicLetterTteh,                    /* 0x8A   0x0679   ARABIC LETTER TTEH */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterO,                 /* 0x8C   0x0152   LATIN CAPITAL LIGATURE OE */
   U_ArabicLetterTcheh,                   /* 0x8D   0x0686   ARABIC LETTER TCHEH */
   U_ArabicLetterJeh,                     /* 0x8E   0x0698   ARABIC LETTER JEH */
   U_ArabicLetterDdal,                    /* 0x8F   0x0688   ARABIC LETTER DDAL */
   U_ArabicLetterGaf,                     /* 0x90   0x06AF   ARABIC LETTER GAF */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_ArabicLetterKeheh,                   /* 0x98   0x06A9   ARABIC LETTER KEHEH */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_ArabicLetterRreh,                    /* 0x9A   0x0691   ARABIC LETTER RREH */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterO,                 /* 0x9C   0x0153   LATIN SMALL LIGATURE OE */
   U_ZeroWidthNonJoiner,                  /* 0x9D   0x200C   ZERO WIDTH NON-JOINER */
   U_ZeroWidthJoiner,                     /* 0x9E   0x200D   ZERO WIDTH JOINER */
   U_ArabicLetterNoon,                    /* 0x9F   0x06BA   ARABIC LETTER NOON GHUNNA */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_ArabicComma,                         /* 0xA1   0x060C   ARABIC COMMA */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_YenSign,                             /* 0xA5   0x00A5   YEN SIGN */
   U_BrokenVerticalBar,                   /* 0xA6   0x00A6   BROKEN BAR */
   U_SectionSign,                         /* 0xA7   0x00A7   SECTION SIGN */
   U_Diaeresis,                           /* 0xA8   0x00A8   DIAERESIS */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_ArabicLetterHeh,                     /* 0xAA   0x06BE   ARABIC LETTER HEH DOACHASHMEE */
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
   U_ArabicSemicolon,                     /* 0xBA   0x061B   ARABIC SEMICOLON */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_ArabicQuestionMark,                  /* 0xBF   0x061F   ARABIC QUESTION MARK */
   U_ArabicLetterHeh,                     /* 0xC0   0x06C1   ARABIC LETTER HEH GOAL */
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
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_ArabicLetterTah,                     /* 0xD8   0x0637   ARABIC LETTER TAH */
   U_ArabicLetterZah,                     /* 0xD9   0x0638   ARABIC LETTER ZAH */
   U_ArabicLetterAin,                     /* 0xDA   0x0639   ARABIC LETTER AIN */
   U_ArabicLetterGhain,                   /* 0xDB   0x063A   ARABIC LETTER GHAIN */
   U_ArabicTatweel,                       /* 0xDC   0x0640   ARABIC TATWEEL */
   U_ArabicLetterFeh,                     /* 0xDD   0x0641   ARABIC LETTER FEH */
   U_ArabicLetterQaf,                     /* 0xDE   0x0642   ARABIC LETTER QAF */
   U_ArabicLetterKaf,                     /* 0xDF   0x0643   ARABIC LETTER KAF */
   U_LatinCapitalLetterA,                 /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_ArabicLetterLam,                     /* 0xE1   0x0644   ARABIC LETTER LAM */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_ArabicLetterMeem,                    /* 0xE3   0x0645   ARABIC LETTER MEEM */
   U_ArabicLetterNoon,                    /* 0xE4   0x0646   ARABIC LETTER NOON */
   U_ArabicLetterHeh,                     /* 0xE5   0x0647   ARABIC LETTER HEH */
   U_ArabicLetterWaw,                     /* 0xE6   0x0648   ARABIC LETTER WAW */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_ArabicLetterAlef,                    /* 0xEC   0x0649   ARABIC LETTER ALEF MAKSURA */
   U_ArabicLetterYeh,                     /* 0xED   0x064A   ARABIC LETTER YEH */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_ArabicFathatan,                      /* 0xF0   0x064B   ARABIC FATHATAN */
   U_ArabicDammatan,                      /* 0xF1   0x064C   ARABIC DAMMATAN */
   U_ArabicKasratan,                      /* 0xF2   0x064D   ARABIC KASRATAN */
   U_ArabicFatha,                         /* 0xF3   0x064E   ARABIC FATHA */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_ArabicDamma,                         /* 0xF5   0x064F   ARABIC DAMMA */
   U_ArabicKasra,                         /* 0xF6   0x0650   ARABIC KASRA */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_ArabicShadda,                        /* 0xF8   0x0651   ARABIC SHADDA */
   U_LatinCapitalLetterU,                 /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_ArabicSukun,                         /* 0xFA   0x0652   ARABIC SUKUN */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LeftToRightMark,                     /* 0xFD   0x200E   LEFT-TO-RIGHT MARK */
   U_RightToLeftMark,                     /* 0xFE   0x200F   RIGHT-TO-LEFT MARK */
   U_ArabicLetterYeh                      /* 0xFF   0x06D2   ARABIC LETTER YEH BARREE */
};










/******************************************************************************
*
*  u_CODE_CP1257[]:
*     Unicode named codepage for Microsoft Windows encoding codepage 1257 ("Baltic")
*
*  Name:             cp1257 to Unicode table
*  Unicode version:  2.0
*  Table version:    2.01
*  Table format:     Format A
*  Date:             1998-04-15
*  Contact:          Shawn.Steele@microsoft.com
*
******************************************|************************************/

static _UWORD const u_CODE_CP1257[] =          /* CODE_CP1257 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_NIL,                                 /* 0x83            UNDEFINED */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_NIL,                                 /* 0x88            UNDEFINED */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_NIL,                                 /* 0x8A            UNDEFINED */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x8C            UNDEFINED */
   U_Diaeresis,                           /* 0x8D   0x00A8   DIAERESIS */
   U_Caron,                               /* 0x8E   0x02C7   CARON */
   U_Cedilla,                             /* 0x8F   0x00B8   CEDILLA */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_NIL,                                 /* 0x98            UNDEFINED */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_NIL,                                 /* 0x9A            UNDEFINED */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x9C            UNDEFINED */
   U_Macron,                              /* 0x9D   0x00AF   MACRON */
   U_Ogonek,                              /* 0x9E   0x02DB   OGONEK */
   U_NIL,                                 /* 0x9F            UNDEFINED */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_NIL,                                 /* 0xA1            UNDEFINED */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_NIL,                                 /* 0xA5            UNDEFINED */
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
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
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
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
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
   U_DotAbove                             /* 0xFF   0x02D9   DOT ABOVE */
};





/******************************************************************************
*
*  CODE_CP1257_lig[]:
*     list of ligatures:
*
*  CODE_CP1257_lig[0] is the original ligature character
*  CODE_CP1257_lig[1] + CODE_CP1257_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CP1257_lig[][3] =     /* CODE_CP1257 character ligatures */
{
   {U_LatinCapitalLetterOSlash,         U_LatinCapitalLetterO, U_LatinCapitalLetterE}, /* 0xA8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   {U_LatinCapitalLigatureAE,           U_LatinCapitalLetterA, U_LatinCapitalLetterE}, /* 0xAF   0x00C6   LATIN CAPITAL LETTER AE */
   {U_LatinSmallLetterOSlash,           U_LatinCapitalLetterO, U_LatinCapitalLetterE}, /* 0xB8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   {U_LatinSmallLigatureAE,             U_LatinCapitalLetterA, U_LatinCapitalLetterE}, /* 0xBF   0x00E6   LATIN SMALL LETTER AE */
   {U_LatinCapitalLetterAWithDiaeresis, U_LatinCapitalLetterA, U_LatinCapitalLetterE}, /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   {U_LatinCapitalLetterAWithRingAbove, U_LatinCapitalLetterA, U_LatinCapitalLetterO}, /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   {U_LatinCapitalLetterOWithDiaeresis, U_LatinCapitalLetterO, U_LatinCapitalLetterE}, /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   {U_LatinCapitalLetterUWithDiaeresis, U_LatinCapitalLetterU, U_LatinCapitalLetterE}, /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   {U_LatinSmallLetterSharpS,           U_LatinCapitalLetterS, U_LatinCapitalLetterS}, /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   {U_LatinSmallLetterAWithDiaeresis,   U_LatinCapitalLetterA, U_LatinCapitalLetterE}, /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   {U_LatinSmallLetterAWithRingAbove,   U_LatinCapitalLetterA, U_LatinCapitalLetterO}, /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   {U_LatinSmallLetterOWithDiaeresis,   U_LatinCapitalLetterO, U_LatinCapitalLetterE}, /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   {U_LatinSmallLetterUWithDiaeresis,   U_LatinCapitalLetterU, U_LatinCapitalLetterE}, /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */

   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CP1257 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*
******************************************|************************************/

static _UWORD const sort_CODE_CP1257[] =       /* CODE_CP1257 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_NIL,                                 /* 0x83            UNDEFINED */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_NIL,                                 /* 0x88            UNDEFINED */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_NIL,                                 /* 0x8A            UNDEFINED */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x8C            UNDEFINED */
   U_Diaeresis,                           /* 0x8D   0x00A8   DIAERESIS */
   U_Caron,                               /* 0x8E   0x02C7   CARON */
   U_Cedilla,                             /* 0x8F   0x00B8   CEDILLA */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_NIL,                                 /* 0x98            UNDEFINED */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_NIL,                                 /* 0x9A            UNDEFINED */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_NIL,                                 /* 0x9C            UNDEFINED */
   U_Macron,                              /* 0x9D   0x00AF   MACRON */
   U_Ogonek,                              /* 0x9E   0x02DB   OGONEK */
   U_NIL,                                 /* 0x9F            UNDEFINED */
   U_NB_SP,                               /* 0xA0   0x00A0   NO-BREAK SPACE */
   U_NIL,                                 /* 0xA1            UNDEFINED */
   U_CentSign,                            /* 0xA2   0x00A2   CENT SIGN */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_CurrencySign,                        /* 0xA4   0x00A4   CURRENCY SIGN */
   U_NIL,                                 /* 0xA5            UNDEFINED */
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
   U_AcuteAccent,                         /* 0xB4   0x00B4   ACUTE ACCENT */
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
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
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
   U_DotAbove                             /* 0xFF   0x02D9   DOT ABOVE */
};










/******************************************************************************
*
*  u_CODE_CP1258[]:
*     Unicode named codepage for Microsoft Windows encoding codepage 1258 ("Vietnamese")
*
*  Name:             cp1258 to Unicode table
*  Unicode version:  2.0
*  Table version:    2.01
*  Table format:     Format A
*  Date:             1998-04-15
*  Contact:          Shawn.Steele@microsoft.com
*
******************************************|************************************/

static _UWORD const u_CODE_CP1258[] =          /* CODE_CP1258 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_LatinSmallLetterScriptF,             /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_ModifierLetterCircumflexAccent,      /* 0x88   0x02C6   MODIFIER LETTER CIRCUMFLEX ACCENT */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_NIL,                                 /* 0x8A            UNDEFINED */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLigatureOE,              /* 0x8C   0x0152   LATIN CAPITAL LIGATURE OE */
   U_NIL,                                 /* 0x8D            UNDEFINED */
   U_NIL,                                 /* 0x8E            UNDEFINED */
   U_NIL,                                 /* 0x8F            UNDEFINED */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_SmallTilde,                          /* 0x98   0x02DC   SMALL TILDE */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_NIL,                                 /* 0x9A            UNDEFINED */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinSmallLigatureOE,                /* 0x9C   0x0153   LATIN SMALL LIGATURE OE */
   U_NIL,                                 /* 0x9D            UNDEFINED */
   U_NIL,                                 /* 0x9E            UNDEFINED */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0x9F   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
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
   U_SuperscriptOne,                      /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneQuarter,            /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_LatinCapitalLetterAWithGrave,        /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterAWithAcute,        /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithBreve,        /* 0xC3   0x0102   LATIN CAPITAL LETTER A WITH BREVE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLigatureAE,              /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterEWithGrave,        /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterEWithAcute,        /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_CombiningGraveAccent,                /* 0xCC   0x0300   COMBINING GRAVE ACCENT */
   U_LatinCapitalLetterIWithAcute,        /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterDWithStroke,       /* 0xD0   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterNWithTilde,        /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_CombiningHookAbove,                  /* 0xD2   0x0309   COMBINING HOOK ABOVE */
   U_LatinCapitalLetterOWithAcute,        /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithHorn,         /* 0xD5   0x01A0   LATIN CAPITAL LETTER O WITH HORN */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterOSlash,            /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterUWithGrave,        /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterUWithHorn,         /* 0xDD   0x01AF   LATIN CAPITAL LETTER U WITH HORN */
   U_CombiningTilde,                      /* 0xDE   0x0303   COMBINING TILDE */
   U_LatinSmallLetterSharpS,              /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterAWithGrave,          /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithAcute,          /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithBreve,          /* 0xE3   0x0103   LATIN SMALL LETTER A WITH BREVE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithRingAbove,      /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLigatureAE,                /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinSmallLetterCWithCedilla,        /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithGrave,          /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterEWithAcute,          /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithCircumflex,     /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_CombiningAcuteAccent,                /* 0xEC   0x0301   COMBINING ACUTE ACCENT */
   U_LatinSmallLetterIWithAcute,          /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterDWithStroke,         /* 0xF0   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinSmallLetterNWithTilde,          /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_CombiningDotBelow,                   /* 0xF2   0x0323   COMBINING DOT BELOW */
   U_LatinSmallLetterOWithAcute,          /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithHorn,           /* 0xF5   0x01A1   LATIN SMALL LETTER O WITH HORN */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinSmallLetterOSlash,              /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinSmallLetterUWithGrave,          /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterUWithAcute,          /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterUWithHorn,           /* 0xFD   0x01B0   LATIN SMALL LETTER U WITH HORN */
   U_DongSign,                            /* 0xFE   0x20AB   DONG SIGN */
   U_LatinSmallLetterYWithDiaeresis       /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};





/******************************************************************************
*
*  CODE_CP1258_lig[]:
*     list of ligatures:
*
*  CODE_CP1258_lig[0] is the original ligature character
*  CODE_CP1258_lig[1] + CODE_CP1258_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_CP1258_lig[][3] =     /* CODE_CP1258 character ligatures */
{
   { U_LatinCapitalLigatureOE,            U_LatinCapitalLetterO, U_LatinCapitalLetterE},   /* 0x8C   0x0152   LATIN CAPITAL LIGATURE OE */
   { U_LatinSmallLigatureOE,              U_LatinCapitalLetterO, U_LatinCapitalLetterE},   /* 0x9C   0x0153   LATIN SMALL LIGATURE OE */
   { U_LatinCapitalLetterYWithDiaeresis,  U_LatinCapitalLetterY, U_LatinCapitalLetterE},   /* 0x9F   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
   { U_LatinCapitalLetterAWithDiaeresis,  U_LatinCapitalLetterA, U_LatinCapitalLetterE},   /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   { U_LatinCapitalLetterAWithRingAbove,  U_LatinCapitalLetterA, U_LatinCapitalLetterO},   /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   { U_LatinCapitalLigatureAE,            U_LatinCapitalLetterA, U_LatinCapitalLetterE},   /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   { U_LatinCapitalLetterEWithDiaeresis,  U_LatinCapitalLetterE, U_LatinCapitalLetterE},   /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   { U_LatinCapitalLetterIWithDiaeresis,  U_LatinCapitalLetterI, U_LatinCapitalLetterE},   /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   { U_LatinCapitalLetterOWithDiaeresis,  U_LatinCapitalLetterO, U_LatinCapitalLetterE},   /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   { U_LatinCapitalLetterOSlash,          U_LatinCapitalLetterO, U_LatinCapitalLetterE},   /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   { U_LatinCapitalLetterUWithDiaeresis,  U_LatinCapitalLetterU, U_LatinCapitalLetterE},   /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterSharpS,            U_LatinCapitalLetterS, U_LatinCapitalLetterS},   /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   { U_LatinSmallLetterAWithDiaeresis,    U_LatinCapitalLetterA, U_LatinCapitalLetterE},   /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   { U_LatinSmallLetterAWithRingAbove,    U_LatinCapitalLetterA, U_LatinCapitalLetterO},   /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   { U_LatinSmallLigatureAE,              U_LatinCapitalLetterA, U_LatinCapitalLetterE},   /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   { U_LatinSmallLetterEWithDiaeresis,    U_LatinCapitalLetterE, U_LatinCapitalLetterE},   /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   { U_LatinSmallLetterIWithDiaeresis,    U_LatinCapitalLetterI, U_LatinCapitalLetterE},   /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   { U_LatinSmallLetterOWithDiaeresis,    U_LatinCapitalLetterO, U_LatinCapitalLetterE},   /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   { U_LatinSmallLetterOSlash,            U_LatinCapitalLetterO, U_LatinCapitalLetterE},   /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   { U_LatinSmallLetterUWithDiaeresis,    U_LatinCapitalLetterU, U_LatinCapitalLetterE},   /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   { U_LatinSmallLetterYWithDiaeresis,    U_LatinCapitalLetterY, U_LatinCapitalLetterE},   /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */

   {0x0000, U_NIL, U_NIL}                 /* list terminator */
};





/******************************************************************************
*
*  CODE_CP1258 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*
******************************************|************************************/

static _UWORD const sort_CODE_CP1258[] =       /* CODE_CP1258 */
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

   U_EuroSign,                            /* 0x80   0x20AC   EURO SIGN */
   U_NIL,                                 /* 0x81            UNDEFINED */
   U_SingleLow9QuotationMark,             /* 0x82   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_LatinCapitalLetterF,                 /* 0x83   0x0192   LATIN SMALL LETTER F WITH HOOK */
   U_DoubleLow9QuotationMark,             /* 0x84   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0x85   0x2026   HORIZONTAL ELLIPSIS */
   U_Dagger,                              /* 0x86   0x2020   DAGGER */
   U_DoubleDagger,                        /* 0x87   0x2021   DOUBLE DAGGER */
   U_ModifierLetterCircumflexAccent,      /* 0x88   0x02C6   MODIFIER LETTER CIRCUMFLEX ACCENT */
   U_PerMilleSign,                        /* 0x89   0x2030   PER MILLE SIGN */
   U_NIL,                                 /* 0x8A            UNDEFINED */
   U_LeftPointingSingleGuillemet,         /* 0x8B   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterO,                 /* 0x8C   0x0152   LATIN CAPITAL LIGATURE OE */
   U_NIL,                                 /* 0x8D            UNDEFINED */
   U_NIL,                                 /* 0x8E            UNDEFINED */
   U_NIL,                                 /* 0x8F            UNDEFINED */
   U_NIL,                                 /* 0x90            UNDEFINED */
   U_LeftSingleQuotationMark,             /* 0x91   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0x92   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_LeftDoubleQuotationMark,             /* 0x93   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0x94   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_Bullet,                              /* 0x95   0x2022   BULLET */
   U_EnDash,                              /* 0x96   0x2013   EN DASH */
   U_EmDash,                              /* 0x97   0x2014   EM DASH */
   U_SmallTilde,                          /* 0x98   0x02DC   SMALL TILDE */
   U_TradeMarkSign,                       /* 0x99   0x2122   TRADE MARK SIGN */
   U_NIL,                                 /* 0x9A            UNDEFINED */
   U_RightPointingSingleGuillemet,        /* 0x9B   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterO,                 /* 0x9C   0x0153   LATIN SMALL LIGATURE OE */
   U_NIL,                                 /* 0x9D            UNDEFINED */
   U_NIL,                                 /* 0x9E            UNDEFINED */
   U_LatinCapitalLetterY,                 /* 0x9F   0x0178   LATIN CAPITAL LETTER Y WITH DIAERESIS */
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
   U_SuperscriptOne,                      /* 0xBA   0x00BA   MASCULINE ORDINAL INDICATOR */
   U_RightPointingGuillemet,              /* 0xBB   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_VulgarFractionOneQuarter,            /* 0xBC   0x00BC   VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneQuarter,            /* 0xBD   0x00BD   VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* 0xBE   0x00BE   VULGAR FRACTION THREE QUARTERS */
   U_InvertedQuestionMark,                /* 0xBF   0x00BF   INVERTED QUESTION MARK */
   U_LatinCapitalLetterA,                 /* 0xC0   0x00C0   LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xC1   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xC2   0x00C2   LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xC3   0x0102   LATIN CAPITAL LETTER A WITH BREVE */
   U_LatinCapitalLetterA,                 /* 0xC4   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xC5   0x00C5   LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xC6   0x00C6   LATIN CAPITAL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xC7   0x00C7   LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xC8   0x00C8   LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xC9   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xCA   0x00CA   LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xCB   0x00CB   LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_CombiningGraveAccent,                /* 0xCC   0x0300   COMBINING GRAVE ACCENT */
   U_LatinCapitalLetterI,                 /* 0xCD   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xCE   0x00CE   LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xCF   0x00CF   LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterD,                 /* 0xD0   0x0110   LATIN CAPITAL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xD1   0x00D1   LATIN CAPITAL LETTER N WITH TILDE */
   U_CombiningHookAbove,                  /* 0xD2   0x0309   COMBINING HOOK ABOVE */
   U_LatinCapitalLetterO,                 /* 0xD3   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xD4   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xD5   0x01A0   LATIN CAPITAL LETTER O WITH HORN */
   U_LatinCapitalLetterO,                 /* 0xD6   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_MultiplicationSign,                  /* 0xD7   0x00D7   MULTIPLICATION SIGN */
   U_LatinCapitalLetterO,                 /* 0xD8   0x00D8   LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xD9   0x00D9   LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xDA   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xDB   0x00DB   LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xDC   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xDD   0x01AF   LATIN CAPITAL LETTER U WITH HORN */
   U_CombiningTilde,                      /* 0xDE   0x0303   COMBINING TILDE */
   U_LatinCapitalLetterS,                 /* 0xDF   0x00DF   LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterA,                 /* 0xE0   0x00E0   LATIN SMALL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xE1   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE2   0x00E2   LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xE3   0x0103   LATIN SMALL LETTER A WITH BREVE */
   U_LatinCapitalLetterA,                 /* 0xE4   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xE5   0x00E5   LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterA,                 /* 0xE6   0x00E6   LATIN SMALL LETTER AE */
   U_LatinCapitalLetterC,                 /* 0xE7   0x00E7   LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 0xE8   0x00E8   LATIN SMALL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xE9   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0xEA   0x00EA   LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xEB   0x00EB   LATIN SMALL LETTER E WITH DIAERESIS */
   U_CombiningAcuteAccent,                /* 0xEC   0x0301   COMBINING ACUTE ACCENT */
   U_LatinCapitalLetterI,                 /* 0xED   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xEE   0x00EE   LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xEF   0x00EF   LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterD,                 /* 0xF0   0x0111   LATIN SMALL LETTER D WITH STROKE */
   U_LatinCapitalLetterN,                 /* 0xF1   0x00F1   LATIN SMALL LETTER N WITH TILDE */
   U_CombiningDotBelow,                   /* 0xF2   0x0323   COMBINING DOT BELOW */
   U_LatinCapitalLetterO,                 /* 0xF3   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xF4   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xF5   0x01A1   LATIN SMALL LETTER O WITH HORN */
   U_LatinCapitalLetterO,                 /* 0xF6   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_DivisionSign,                        /* 0xF7   0x00F7   DIVISION SIGN */
   U_LatinCapitalLetterO,                 /* 0xF8   0x00F8   LATIN SMALL LETTER O WITH STROKE */
   U_LatinCapitalLetterU,                 /* 0xF9   0x00F9   LATIN SMALL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xFA   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xFB   0x00FB   LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xFC   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xFD   0x01B0   LATIN SMALL LETTER U WITH HORN */
   U_DongSign,                            /* 0xFE   0x20AB   DONG SIGN */
   U_LatinCapitalLetterY                  /* 0xFF   0x00FF   LATIN SMALL LETTER Y WITH DIAERESIS */
};
