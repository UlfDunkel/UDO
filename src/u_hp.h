/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_hp.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepages for Hewlett Packard encoding HP-roman8
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
*    fd  Feb 16: file introduced
*    fd  Feb 17: CODE_HP8_lig[] + sort_CODE_HP8[] added
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
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
*  u_CODE_HP8[]:
*     Unicode named codepage for HP-roman8 encoding (original name = ibm-1051)
*
******************************************|************************************/

static _UWORD const u_CODE_HP8[] =             /* CODE_HP8 */
{
   U_NIL,                                 /* 0x00  NULl */
   U_NIL,                                 /* 0x01  Start Of Heading */
   U_NIL,                                 /* 0x02  Start of TeXt */
   U_NIL,                                 /* 0x03  End of TeXt */
   U_NIL,                                 /* 0x04  End Of Transmission */
   U_NIL,                                 /* 0x05  ENQuiry */
   U_NIL,                                 /* 0x06  ACKnowledge */
   U_NIL,                                 /* 0x07  BELl */
   U_NIL,                                 /* 0x08  BackSpace */
   U_NIL,                                 /* 0x09  Horizontal Tabulation */
   U_NIL,                                 /* 0x0a  Line Feed */
   U_NIL,                                 /* 0x0b  Vertical Tabulation */
   U_NIL,                                 /* 0x0c  Form Feed */
   U_NIL,                                 /* 0x0d  Carriage Return */
   U_NIL,                                 /* 0x0e  Shift Out */
   U_NIL,                                 /* 0x0f  Shift In */
   U_NIL,                                 /* 0x10  Data Link Escape */
   U_NIL,                                 /* 0x11  Device Control 1 */
   U_NIL,                                 /* 0x12  Device Control 2 */
   U_NIL,                                 /* 0x13  Device Control 3 */
   U_NIL,                                 /* 0x14  Device Control 4 */
   U_NIL,                                 /* 0x15  Negative AcKnowledge */
   U_NIL,                                 /* 0x16  SYNchronous idle */
   U_NIL,                                 /* 0x17  End of Transmission Block */
   U_NIL,                                 /* 0x18  CANcel */
   U_NIL,                                 /* 0x19  End of Medium */
   U_NIL,                                 /* 0x1a  SUBstitute */
   U_NIL,                                 /* 0x1b  ESCape */
   U_NIL,                                 /* 0x1c  File Separator */
   U_NIL,                                 /* 0x1d  Group Separator */
   U_NIL,                                 /* 0x1e  Record Separator */
   U_NIL,                                 /* 0x1f  Unit Separator */

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

   U_NIL,                                 /* 0x80  */
   U_NIL,                                 /* 0x81  */
   U_NIL,                                 /* 0x82  */
   U_NIL,                                 /* 0x83  */
   U_NIL,                                 /* 0x84  */
   U_NIL,                                 /* 0x85  */
   U_NIL,                                 /* 0x86  */
   U_NIL,                                 /* 0x87  */
   U_NIL,                                 /* 0x88  */
   U_NIL,                                 /* 0x89  */
   U_NIL,                                 /* 0x8a  */
   U_NIL,                                 /* 0x8b  */
   U_NIL,                                 /* 0x8c  */
   U_NIL,                                 /* 0x8d  */
   U_NIL,                                 /* 0x8e  */
   U_NIL,                                 /* 0x8f  */
   U_NIL,                                 /* 0x90  */
   U_NIL,                                 /* 0x91  */
   U_NIL,                                 /* 0x92  */
   U_NIL,                                 /* 0x93  */
   U_NIL,                                 /* 0x94  */
   U_NIL,                                 /* 0x95  */
   U_NIL,                                 /* 0x96  */
   U_NIL,                                 /* 0x97  */
   U_NIL,                                 /* 0x98  */
   U_NIL,                                 /* 0x99  */
   U_NIL,                                 /* 0x9a  */
   U_NIL,                                 /* 0x9b  */
   U_NIL,                                 /* 0x9c  */
   U_NIL,                                 /* 0x9d  */
   U_NIL,                                 /* 0x9e  */
   U_NIL,                                 /* 0x9f  */
   U_NIL,                                 /* 0xa0  */
   U_LatinCapitalLetterAWithGrave,        /* 0xa1 = 0x00C0: LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xa2 = 0x00C2: LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithGrave,        /* 0xa3 = 0x00C8: LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xa4 = 0x00CA: LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xa5 = 0x00CB: LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xa6 = 0x00CE: LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xa7 = 0x00CF: LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_AcuteAccent,                         /* 0xa8 = 0x00B4: ACUTE ACCENT */
   U_GraveAccent,                         /* 0xa9 = 0x0060: GRAVE ACCENT */
   U_CircumflexAccent,                    /* 0xaa = 0x005E: CIRCUMFLEX ACCENT */
   U_Diaeresis,                           /* 0xab = 0x00A8: DIAERESIS */
   U_Tilde,                               /* 0xac = 0x007E: TILDE */
   U_LatinCapitalLetterUWithGrave,        /* 0xad = 0x00D9: LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xae = 0x00DB: LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LiraSign,                            /* 0xaf = 0x20A4: LIRA SIGN */
   U_Macron,                              /* 0xb0 = 0x00AF: MACRON */
   U_LatinCapitalLetterYWithAcute,        /* 0xb1 = 0x00DD: LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinSmallLetterYWithAcute,          /* 0xb2 = 0x00FD: LATIN SMALL LETTER Y WITH ACUTE */
   U_DegreeSign,                          /* 0xb3 = 0x00B0: DEGREE SIGN */
   U_LatinCapitalLetterCWithCedilla,      /* 0xb4 = 0x00C7: LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinSmallLetterCWithCedilla,        /* 0xb5 = 0x00E7: LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterNWithTilde,        /* 0xb6 = 0x00D1: LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinSmallLetterNWithTilde,          /* 0xb7 = 0x00F1: LATIN SMALL LETTER N WITH TILDE */
   U_InvertedExclamationMark,             /* 0xb8 = 0x00A1: INVERTED EXCLAMATION MARK */
   U_InvertedQuestionMark,                /* 0xb9 = 0x00BF: INVERTED QUESTION MARK */
   U_CurrencySign,                        /* 0xba = 0x00A4: CURRENCY SIGN */
   U_PoundSign,                           /* 0xbb = 0x00A3: POUND SIGN */
   U_YenSign,                             /* 0xbc = 0x00A5: YEN SIGN */
   U_SectionSign,                         /* 0xbd = 0x00A7: SECTION SIGN */
   U_LatinSmallLetterScriptF,             /* 0xbe = 0x0192: LATIN SMALL LETTER F WITH HOOK */
   U_CentSign,                            /* 0xbf = 0x00A2: CENT SIGN */
   U_LatinSmallLetterAWithCircumflex,     /* 0xc0 = 0x00E2: LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithCircumflex,     /* 0xc1 = 0x00EA: LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithCircumflex,     /* 0xc2 = 0x00F4: LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithCircumflex,     /* 0xc3 = 0x00FB: LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithAcute,          /* 0xc4 = 0x00E1: LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterEWithAcute,          /* 0xc5 = 0x00E9: LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterOWithAcute,          /* 0xc6 = 0x00F3: LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterUWithAcute,          /* 0xc7 = 0x00FA: LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterAWithGrave,          /* 0xc8 = 0x00E0: LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterEWithGrave,          /* 0xc9 = 0x00E8: LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterOWithGrave,          /* 0xca = 0x00F2: LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterUWithGrave,          /* 0xcb = 0x00F9: LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xcc = 0x00E4: LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xcd = 0x00EB: LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xce = 0x00F6: LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xcf = 0x00FC: LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xd0 = 0x00C5: LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterIWithCircumflex,     /* 0xd1 = 0x00EE: LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterOSlash,            /* 0xd2 = 0x00D8: LATIN CAPITAL LETTER O SLASH */
   U_LatinCapitalLigatureAE,              /* 0xd3 = 0x00C6: LATIN CAPITAL LIGATURE AE */
   U_LatinSmallLetterAWithRingAbove,      /* 0xd4 = 0x00E5: LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterIWithAcute,          /* 0xd5 = 0x00ED: LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterOSlash,              /* 0xd6 = 0x00F8: LATIN SMALL LETTER O SLASH */
   U_LatinSmallLigatureAE,                /* 0xd7 = 0x00E6: LATIN SMALL LIGATURE AE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xd8 = 0x00C4: LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterIWithGrave,          /* 0xd9 = 0x00EC: LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xda = 0x00D6: LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xdb = 0x00DC: LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterEWithAcute,        /* 0xdc = 0x00C9: LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xdd = 0x00EF: LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterSharpS,              /* 0xde = 0x00DF: LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xdf = 0x00D4: LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithAcute,        /* 0xe0 = 0x00C1: LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithTilde,        /* 0xe1 = 0x00C3: LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinSmallLetterAWithTilde,          /* 0xe2 = 0x00E3: LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterEth,               /* 0xe3 = 0x00D0: LATIN CAPITAL LETTER ETH */
   U_LatinSmallLetterEth,                 /* 0xe4 = 0x00F0: LATIN SMALL LETTER ETH */
   U_LatinCapitalLetterIWithAcute,        /* 0xe5 = 0x00CD: LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithGrave,        /* 0xe6 = 0x00CC: LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterOWithAcute,        /* 0xe7 = 0x00D3: LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithGrave,        /* 0xe8 = 0x00D2: LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterOWithTilde,        /* 0xe9 = 0x00D5: LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithTilde,          /* 0xea = 0x00F5: LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterSWithCaron,        /* 0xeb = 0x0160: LATIN CAPITAL LETTER S WITH CARON */
   U_LatinSmallLetterSWithCaron,          /* 0xec = 0x0161: LATIN SMALL LETTER S WITH CARON */
   U_LatinCapitalLetterUWithAcute,        /* 0xed = 0x00DA: LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0xee = 0x0178: LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_LatinSmallLetterYWithDiaeresis,      /* 0xef = 0x00FF: LATIN SMALL LETTER Y WITH DIAERESIS */
   U_LatinCapitalLetterThorn,             /* 0xf0 = 0x00DE: LATIN CAPITAL LETTER THORN */
   U_LatinSmallLetterThorn,               /* 0xf1 = 0x00FE: LATIN SMALL LETTER THORN */
   U_MiddleDot,                           /* 0xf2 = 0x00B7: MIDDLE DOT */
   U_MicroSign,                           /* 0xf3 = 0x00B5: MICRO SIGN */
   U_ParagraphSign,                       /* 0xf4 = 0x00B6: PARAGRAPH SIGN (PILCROW SIGN) */
   U_VulgarFractionThreeQuarters,         /* 0xf5 = 0x00BE: VULGAR FRACTION THREE QUARTERS */
   U_HyphenMinus,                         /* 0xf6 = 0x002D: HYPHEN-MINUS */
   U_VulgarFractionOneQuarter,            /* 0xf7 = 0x00BC: VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xf8 = 0x00BD: VULGAR FRACTION ONE HALF */
   U_FeminineOrdinalIndicator,            /* 0xf9 = 0x00AA: FEMININE ORDINAL INDICATOR */
   U_MasculineOrdinalIndicator,           /* 0xfa = 0x00BA: MASCULINE ORDINAL INDICATOR */
   U_LeftPointingGuillemet,               /* 0xfb = 0x00AB: LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_FullBlock,                           /* 0xfc = 0x2588: FULL BLOCK */
   U_RightPointingGuillemet,              /* 0xfd = 0x00BB: RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_PlusMinusSign,                       /* 0xfe = 0x00B1: PLUS-MINUS SIGN */
   U_NIL                                  /* 0xff  */
};





/******************************************************************************
*
*  CODE_HP8_lig[]:
*     list of ligatures:
*
*  CODE_HP8_lig[0] is the original ligature character
*  CODE_HP8_lig[1] + CODE_HP8_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_HP8_lig[][3] =        /* CODE_HP8 character ligatures */
{
   {0x00CB, U_LatinCapitalLetterE, U_LatinSmallLetterE},      /* 0xa5 = 0x00CB: LATIN CAPITAL LETTER E WITH DIAERESIS */
   {0x00CF, U_LatinCapitalLetterI, U_LatinSmallLetterE},      /* 0xa7 = 0x00CF: LATIN CAPITAL LETTER I WITH DIAERESIS */
   {0x00E4, U_LatinSmallLetterA,   U_LatinSmallLetterE},      /* 0xcc = 0x00E4: LATIN SMALL LETTER A WITH DIAERESIS */
   {0x00EB, U_LatinSmallLetterE,   U_LatinSmallLetterE},      /* 0xcd = 0x00EB: LATIN SMALL LETTER E WITH DIAERESIS */
   {0x00F6, U_LatinSmallLetterO,   U_LatinSmallLetterE},      /* 0xce = 0x00F6: LATIN SMALL LETTER O WITH DIAERESIS */
   {0x00FC, U_LatinSmallLetterU,   U_LatinSmallLetterE},      /* 0xcf = 0x00FC: LATIN SMALL LETTER U WITH DIAERESIS */
   {0x00C5, U_LatinCapitalLetterA, U_LatinSmallLetterO},      /* 0xd0 = 0x00C5: LATIN CAPITAL LETTER A WITH RING ABOVE */
   {0x00D8, U_LatinCapitalLetterO, U_LatinSmallLetterE},      /* 0xd2 = 0x00D8: LATIN CAPITAL LETTER O SLASH */
   {0x00C6, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0xd3 = 0x00C6: LATIN CAPITAL LIGATURE AE */
   {0x00E5, U_LatinSmallLetterA,   U_LatinSmallLetterO},      /* 0xd4 = 0x00E5: LATIN SMALL LETTER A WITH RING ABOVE */
   {0x00F8, U_LatinSmallLetterO,   U_LatinSmallLetterE},      /* 0xd6 = 0x00F8: LATIN SMALL LETTER O SLASH */
   {0x00E6, U_LatinSmallLetterA,   U_LatinSmallLetterE},      /* 0xd7 = 0x00E6: LATIN SMALL LIGATURE AE */
   {0x00C4, U_LatinCapitalLetterA, U_LatinSmallLetterE},      /* 0xd8 = 0x00C4: LATIN CAPITAL LETTER A WITH DIAERESIS */
   {0x00D6, U_LatinCapitalLetterO, U_LatinSmallLetterE},      /* 0xda = 0x00D6: LATIN CAPITAL LETTER O WITH DIAERESIS */
   {0x00DC, U_LatinCapitalLetterU, U_LatinSmallLetterE},      /* 0xdb = 0x00DC: LATIN CAPITAL LETTER U WITH DIAERESIS */
   {0x00EF, U_LatinSmallLetterI,   U_LatinSmallLetterE},      /* 0xdd = 0x00EF: LATIN SMALL LETTER I WITH DIAERESIS */
   {0x00DF, U_LatinSmallLetterS,   U_LatinSmallLetterS},      /* 0xde = 0x00DF: LATIN SMALL LETTER SHARP S */
   {0x0160, U_LatinCapitalLetterS, U_LatinSmallLetterJ},      /* 0xeb = 0x0160: LATIN CAPITAL LETTER S WITH CARON */
   {0x0161, U_LatinSmallLetterS,   U_LatinSmallLetterJ},      /* 0xec = 0x0161: LATIN SMALL LETTER S WITH CARON */
   {0x0178, U_LatinCapitalLetterY, U_LatinSmallLetterE},      /* 0xee = 0x0178: LATIN CAPITAL LETTER Y WITH DIAERESIS */
   {0x00FF, U_LatinSmallLetterY,   U_LatinSmallLetterE},      /* 0xef = 0x00FF: LATIN SMALL LETTER Y WITH DIAERESIS */
   {0x0000, U_NIL                , U_NIL}                     /* list terminator */
};





/******************************************************************************
*
*  CODE_HP8 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_HP8[] =          /* CODE_HP8 */
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

   U_NIL,                                 /* 0x80  */
   U_NIL,                                 /* 0x81  */
   U_NIL,                                 /* 0x82  */
   U_NIL,                                 /* 0x83  */
   U_NIL,                                 /* 0x84  */
   U_NIL,                                 /* 0x85  */
   U_NIL,                                 /* 0x86  */
   U_NIL,                                 /* 0x87  */
   U_NIL,                                 /* 0x88  */
   U_NIL,                                 /* 0x89  */
   U_NIL,                                 /* 0x8a  */
   U_NIL,                                 /* 0x8b  */
   U_NIL,                                 /* 0x8c  */
   U_NIL,                                 /* 0x8d  */
   U_NIL,                                 /* 0x8e  */
   U_NIL,                                 /* 0x8f  */
   U_NIL,                                 /* 0x90  */
   U_NIL,                                 /* 0x91  */
   U_NIL,                                 /* 0x92  */
   U_NIL,                                 /* 0x93  */
   U_NIL,                                 /* 0x94  */
   U_NIL,                                 /* 0x95  */
   U_NIL,                                 /* 0x96  */
   U_NIL,                                 /* 0x97  */
   U_NIL,                                 /* 0x98  */
   U_NIL,                                 /* 0x99  */
   U_NIL,                                 /* 0x9a  */
   U_NIL,                                 /* 0x9b  */
   U_NIL,                                 /* 0x9c  */
   U_NIL,                                 /* 0x9d  */
   U_NIL,                                 /* 0x9e  */
   U_NIL,                                 /* 0x9f  */
   U_NIL,                                 /* 0xa0  */
   U_LatinCapitalLetterA,                 /* 0xa1 = 0x00C0: LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0xa2 = 0x00C2: LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xa3 = 0x00C8: LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 0xa4 = 0x00CA: LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xa5 = 0x00CB: LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 0xa6 = 0x00CE: LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xa7 = 0x00CF: LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_AcuteAccent,                         /* 0xa8 = 0x00B4: ACUTE ACCENT */
   U_GraveAccent,                         /* 0xa9 = 0x0060: GRAVE ACCENT */
   U_CircumflexAccent,                    /* 0xaa = 0x005E: CIRCUMFLEX ACCENT */
   U_Diaeresis,                           /* 0xab = 0x00A8: DIAERESIS */
   U_Tilde,                               /* 0xac = 0x007E: TILDE */
   U_LatinCapitalLetterU,                 /* 0xad = 0x00D9: LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 0xae = 0x00DB: LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LiraSign,                            /* 0xaf = 0x20A4: LIRA SIGN */
   U_Macron,                              /* 0xb0 = 0x00AF: MACRON */
   U_LatinCapitalLetterY,                 /* 0xb1 = 0x00DD: LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinSmallLetterY,                   /* 0xb2 = 0x00FD: LATIN SMALL LETTER Y WITH ACUTE */
   U_DegreeSign,                          /* 0xb3 = 0x00B0: DEGREE SIGN */
   U_LatinCapitalLetterC,                 /* 0xb4 = 0x00C7: LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinSmallLetterC,                   /* 0xb5 = 0x00E7: LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterN,                 /* 0xb6 = 0x00D1: LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinSmallLetterN,                   /* 0xb7 = 0x00F1: LATIN SMALL LETTER N WITH TILDE */
   U_InvertedExclamationMark,             /* 0xb8 = 0x00A1: INVERTED EXCLAMATION MARK */
   U_InvertedQuestionMark,                /* 0xb9 = 0x00BF: INVERTED QUESTION MARK */
   U_CurrencySign,                        /* 0xba = 0x00A4: CURRENCY SIGN */
   U_PoundSign,                           /* 0xbb = 0x00A3: POUND SIGN */
   U_YenSign,                             /* 0xbc = 0x00A5: YEN SIGN */
   U_SectionSign,                         /* 0xbd = 0x00A7: SECTION SIGN */
   U_LatinSmallLetterF,                   /* 0xbe = 0x0192: LATIN SMALL LETTER F WITH HOOK */
   U_CentSign,                            /* 0xbf = 0x00A2: CENT SIGN */
   U_LatinSmallLetterA,                   /* 0xc0 = 0x00E2: LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterE,                   /* 0xc1 = 0x00EA: LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterO,                   /* 0xc2 = 0x00F4: LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterU,                   /* 0xc3 = 0x00FB: LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterA,                   /* 0xc4 = 0x00E1: LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterE,                   /* 0xc5 = 0x00E9: LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterO,                   /* 0xc6 = 0x00F3: LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterU,                   /* 0xc7 = 0x00FA: LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterA,                   /* 0xc8 = 0x00E0: LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterE,                   /* 0xc9 = 0x00E8: LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterO,                   /* 0xca = 0x00F2: LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterU,                   /* 0xcb = 0x00F9: LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterA,                   /* 0xcc = 0x00E4: LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterE,                   /* 0xcd = 0x00EB: LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterO,                   /* 0xce = 0x00F6: LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterU,                   /* 0xcf = 0x00FC: LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0xd0 = 0x00C5: LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterI,                   /* 0xd1 = 0x00EE: LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterOSlash,            /* 0xd2 = 0x00D8: LATIN CAPITAL LETTER O SLASH */
   U_LatinCapitalLigatureAE,              /* 0xd3 = 0x00C6: LATIN CAPITAL LIGATURE AE */
   U_LatinSmallLetterA,                   /* 0xd4 = 0x00E5: LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterI,                   /* 0xd5 = 0x00ED: LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterOSlash,              /* 0xd6 = 0x00F8: LATIN SMALL LETTER O SLASH */
   U_LatinSmallLigatureAE,                /* 0xd7 = 0x00E6: LATIN SMALL LIGATURE AE */
   U_LatinCapitalLetterA,                 /* 0xd8 = 0x00C4: LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterI,                   /* 0xd9 = 0x00EC: LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xda = 0x00D6: LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0xdb = 0x00DC: LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xdc = 0x00C9: LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinSmallLetterI,                   /* 0xdd = 0x00EF: LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterSharpS,              /* 0xde = 0x00DF: LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterO,                 /* 0xdf = 0x00D4: LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xe0 = 0x00C1: LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xe1 = 0x00C3: LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinSmallLetterA,                   /* 0xe2 = 0x00E3: LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterEth,               /* 0xe3 = 0x00D0: LATIN CAPITAL LETTER ETH */
   U_LatinSmallLetterEth,                 /* 0xe4 = 0x00F0: LATIN SMALL LETTER ETH */
   U_LatinCapitalLetterI,                 /* 0xe5 = 0x00CD: LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xe6 = 0x00CC: LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xe7 = 0x00D3: LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xe8 = 0x00D2: LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 0xe9 = 0x00D5: LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinSmallLetterO,                   /* 0xea = 0x00F5: LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterS,                 /* 0xeb = 0x0160: LATIN CAPITAL LETTER S WITH CARON */
   U_LatinSmallLetterS,                   /* 0xec = 0x0161: LATIN SMALL LETTER S WITH CARON */
   U_LatinCapitalLetterU,                 /* 0xed = 0x00DA: LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterY,                 /* 0xee = 0x0178: LATIN CAPITAL LETTER Y WITH DIAERESIS */
   U_LatinSmallLetterY,                   /* 0xef = 0x00FF: LATIN SMALL LETTER Y WITH DIAERESIS */
   U_LatinCapitalLetterThorn,             /* 0xf0 = 0x00DE: LATIN CAPITAL LETTER THORN */
   U_LatinSmallLetterThorn,               /* 0xf1 = 0x00FE: LATIN SMALL LETTER THORN */
   U_MiddleDot,                           /* 0xf2 = 0x00B7: MIDDLE DOT */
   U_MicroSign,                           /* 0xf3 = 0x00B5: MICRO SIGN */
   U_ParagraphSign,                       /* 0xf4 = 0x00B6: PARAGRAPH SIGN (PILCROW SIGN) */
   U_VulgarFractionThreeQuarters,         /* 0xf5 = 0x00BE: VULGAR FRACTION THREE QUARTERS */
   U_HyphenMinus,                         /* 0xf6 = 0x002D: HYPHEN-MINUS */
   U_VulgarFractionOneQuarter,            /* 0xf7 = 0x00BC: VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* 0xf8 = 0x00BD: VULGAR FRACTION ONE HALF */
   U_FeminineOrdinalIndicator,            /* 0xf9 = 0x00AA: FEMININE ORDINAL INDICATOR */
   U_MasculineOrdinalIndicator,           /* 0xfa = 0x00BA: MASCULINE ORDINAL INDICATOR */
   U_LeftPointingGuillemet,               /* 0xfb = 0x00AB: LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_FullBlock,                           /* 0xfc = 0x2588: FULL BLOCK */
   U_RightPointingGuillemet,              /* 0xfd = 0x00BB: RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_PlusMinusSign,                       /* 0xfe = 0x00B1: PLUS-MINUS SIGN */
   U_NIL                                  /* 0xff  */
};
