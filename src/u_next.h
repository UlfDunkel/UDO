/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_next.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepages for NeXTStep encoding,
*                 based on <http://www.kostis.net/charsets/nextstep.htm>
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
*    fd  Feb 16: file introduced
*    fd  Feb 17: CODE_NEXT_lig[] + sort_CODE_NEXT[] added
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
*  u_CODE_NEXT[]:
*     Unicode named codepage for NeXTStep encoding
*
******************************************|************************************/

static _UWORD const u_CODE_NEXT[] =            /* CODE_NEXT */
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

   U_NB_SP,                               /* 80 = 0x00A0: NO-BREAK SPACE */
   U_LatinCapitalLetterAWithGrave,        /* 81 = 0x00C0: LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterAWithAcute,        /* 82 = 0x00C1: LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 83 = 0x00C2: LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithTilde,        /* 84 = 0x00C3: LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 85 = 0x00C4: LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 86 = 0x00C5: LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterCWithCedilla,      /* 87 = 0x00C7: LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterEWithGrave,        /* 88 = 0x00C8: LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterEWithAcute,        /* 89 = 0x00C9: LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterEWithCircumflex,   /* 8A = 0x00CA: LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 8B = 0x00CB: LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterIWithGrave,        /* 8C = 0x00CC: LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterIWithAcute,        /* 8D = 0x00CD: LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 8E = 0x00CE: LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 8F = 0x00CF: LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 90 = 0x00D0: LATIN CAPITAL LETTER ETH */
   U_LatinCapitalLetterNWithTilde,        /* 91 = 0x00D1: LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterOWithGrave,        /* 92 = 0x00D2: LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterOWithAcute,        /* 93 = 0x00D3: LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 94 = 0x00D4: LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithTilde,        /* 95 = 0x00D5: LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterOWithDiaeresis,    /* 96 = 0x00D6: LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterUWithGrave,        /* 97 = 0x00D9: LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterUWithAcute,        /* 98 = 0x00DA: LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 99 = 0x00DB: LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithDiaeresis,    /* 9A = 0x00DC: LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterYWithAcute,        /* 9B = 0x00DD: LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 9C = 0x00DE: LATIN CAPITAL LETTER THORN */
   U_MicroSign,                           /* 9D = 0x00B5: MICRO SIGN */
   U_MultiplicationSign,                  /* 9E = 0x00D7: MULTIPLICATION SIGN */
   U_DivisionSign,                        /* 9F = 0x00F7: DIVISION SIGN */
   U_CopyrightSign,                       /* A0 = 0x00A9: COPYRIGHT SIGN */
   U_InvertedExclamationMark,             /* A1 = 0x00A1: INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* A2 = 0x00A2: CENT SIGN */
   U_PoundSign,                           /* A3 = 0x00A3: POUND SIGN */
   U_FractionSlash,                       /* A4 = 0x2044: FRACTION SLASH */
   U_YenSign,                             /* A5 = 0x00A5: YEN SIGN */
   U_LatinSmallLetterScriptF,             /* A6 = 0x0192: LATIN SMALL LETTER F WITH HOOK */
   U_SectionSign,                         /* A7 = 0x00A7: SECTION SIGN */
   U_CurrencySign,                        /* A8 = 0x00A4: CURRENCY SIGN */
   U_LeftDoubleQuotationMark,             /* AA = 0x201C: LEFT DOUBLE QUOTATION MARK */
   U_LeftPointingGuillemet,               /* AB = 0x00AB: LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LeftPointingSingleGuillemet,         /* AC = 0x2039: SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_RightPointingSingleGuillemet,        /* AD = 0x203A: SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinSmallLigatureFI,                /* AE = 0xFB01: LATIN SMALL LIGATURE FI */
   U_LatinSmallLigatureFL,                /* AF = 0xFB02: LATIN SMALL LIGATURE FL */
   U_RegisteredSign,                      /* B0 = 0x00AE: REGISTERED SIGN */
   U_EnDash,                              /* B1 = 0x2013: EN DASH */
   U_Dagger,                              /* B2 = 0x2020: DAGGER */
   U_DoubleDagger,                        /* B3 = 0x2021: DOUBLE DAGGER */
   U_MiddleDot,                           /* B4 = 0x00B7: MIDDLE DOT */
   U_BrokenVerticalBar,                   /* B5 = 0x00A6: BROKEN BAR */
   U_ParagraphSign,                       /* B6 = 0x00B6: PILCROW SIGN */
   U_Bullet,                              /* B7 = 0x2022: BULLET OPERATOR */
   U_SingleLow9QuotationMark,             /* B8 = 0x201A: SINGLE LOW-9 QUOTATION MARK */
   U_DoubleLow9QuotationMark,             /* B9 = 0x201E: DOUBLE LOW-9 QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* BA = 0x201D: RIGHT DOUBLE QUOTATION MARK */
   U_RightPointingGuillemet,              /* BB = 0x00BB: RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_HorizontalEllipsis,                  /* BC = 0x2026: MIDLINE HORIZONTAL ELLIPSIS */
   U_PerMilleSign,                        /* BD = 0x2030: PER MILLE SIGN */
   U_NotSign,                             /* BE = 0x00AC: NOT SIGN */
   U_InvertedQuestionMark,                /* BF = 0x00BF: INVERTED QUESTION MARK */
   U_SuperscriptOne,                      /* C0 = 0x00B9: SUPERSCRIPT ONE */
   U_CombiningGraveAccent,                /* C1 = 0x0300: COMBINING GRAVE ACCENT */
   U_AcuteAccent,                         /* C2 = 0x00B4: ACUTE ACCENT */
   U_CombiningCircumflexAccent,           /* C3 = 0x0302: COMBINING CIRCUMFLEX ACCENT */
   U_CombiningTilde,                      /* C4 = 0x0303: COMBINING TILDE */
   U_Macron,                              /* C5 = 0x00AF: MACRON */
   U_Breve,                               /* C6 = 0x02D8: BREVE */
   U_DotAbove,                            /* C7 = 0x02D9: DOT ABOVE */
   U_Diaeresis,                           /* C8 = 0x00A8: DIAERESIS */
   U_SuperscriptTwo,                      /* C9 = 0x00B2: SUPERSCRIPT TWO */
   U_DegreeSign,                          /* CA = 0x00B0: DEGREE SIGN */
   U_Cedilla,                             /* CB = 0x00B8: CEDILLA */
   U_SuperscriptThree,                    /* CC = 0x00B3: SUPERSCRIPT THREE */
   U_DoubleAcuteAccent,                   /* CD = 0x02DD: DOUBLE ACUTE ACCENT */
   U_Ogonek,                              /* CE = 0x02DB: OGONEK */
   U_Caron,                               /* CF = 0x02C7: CARON */
   U_EmDash,                              /* D0 = 0x2014: EM DASH */
   U_PlusMinusSign,                       /* D1 = 0x00B1: PLUS-MINUS SIGN */
   U_VulgarFractionOneQuarter,            /* D2 = 0x00BC: VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* D3 = 0x00BD: VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* D4 = 0x00BE: VULGAR FRACTION THREE QUARTERS */
   U_LatinSmallLetterAWithGrave,          /* D5 = 0x00E0: LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithAcute,          /* D6 = 0x00E1: LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* D7 = 0x00E2: LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithTilde,          /* D8 = 0x00E3: LATIN SMALL LETTER A WITH TILDE */
   U_LatinSmallLetterAWithDiaeresis,      /* D9 = 0x00E4: LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithRingAbove,      /* DA = 0x00E5: LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterCWithCedilla,        /* DB = 0x00E7: LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithGrave,          /* DC = 0x00E8: LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterEWithAcute,          /* DD = 0x00E9: LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterEWithCircumflex,     /* DE = 0x00EA: LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* DF = 0x00EB: LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterIWithGrave,          /* E0 = 0x00EC: LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLigatureAE,              /* E1 = 0x00C6: LATIN CAPITAL LETTER AE */
   U_LatinSmallLetterIWithAcute,          /* E2 = 0x00ED: LATIN SMALL LETTER I WITH ACUTE */
   U_FeminineOrdinalIndicator,            /* E3 = 0x00AA: FEMININE ORDINAL INDICATOR */
   U_LatinSmallLetterIWithCircumflex,     /* E4 = 0x00EE: LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithDiaeresis,      /* E5 = 0x00EF: LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterEth,                 /* E6 = 0x00F0: LATIN SMALL LETTER ETH */
   U_LatinSmallLetterNWithTilde,          /* E7 = 0x00F1: LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterLWithStroke,       /* E8 = 0x0141: LATIN CAPITAL LETTER L WITH STROKE */
   U_LatinCapitalLetterOSlash,            /* E9 = 0x00D8: LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLigatureOE,              /* EA = 0x0152: LATIN CAPITAL LIGATURE OE */
   U_MasculineOrdinalIndicator,           /* EB = 0x00BA: MASCULINE ORDINAL INDICATOR */
   U_LatinSmallLetterOWithGrave,          /* EC = 0x00F2: LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterOWithAcute,          /* ED = 0x00F3: LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterOWithCircumflex,     /* EE = 0x00F4: LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithTilde,          /* EF = 0x00F5: LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithDiaeresis,      /* F0 = 0x00F6: LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLigatureAE,                /* F1 = 0x00E6: LATIN SMALL LETTER AE */
   U_LatinSmallLetterUWithGrave,          /* F2 = 0x00F9: LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterUWithAcute,          /* F3 = 0x00FA: LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithCircumflex,     /* F4 = 0x00FB: LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterDotlessI,            /* F5 = 0x0131: LATIN SMALL LETTER DOTLESS I */
   U_LatinSmallLetterUWithDiaeresis,      /* F6 = 0x00FC: LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterYWithAcute,          /* F7 = 0x00FD: LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinSmallLetterLWithStroke,         /* F8 = 0x0142: LATIN SMALL LETTER L WITH STROKE */
   U_LatinSmallLetterOSlash,              /* F9 = 0x00F8: LATIN SMALL LETTER O WITH STROKE */
   U_LatinSmallLigatureOE,                /* FA = 0x0153: LATIN SMALL LIGATURE OE */
   U_LatinSmallLetterSharpS,              /* FB = 0x00DF: LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterThorn,               /* FC = 0x00FE: LATIN SMALL LETTER THORN */
   U_LatinSmallLetterYWithDiaeresis,      /* FD = 0x00FF: LATIN SMALL LETTER Y WITH DIAERESIS */
   U_NIL,                                 /* FE */
   U_NIL                                  /* FF */
};





/******************************************************************************
*
*  CODE_NEXT_lig[]:
*     list of ligatures:
*
*  CODE_NEXT_lig[0] is the original ligature character
*  CODE_NEXT_lig[1] + CODE_NEXT_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_NEXT_lig[][3] =       /* CODE_NEXT character ligatures */
{
   {0x00C4, U_LatinCapitalLetterA, U_LatinSmallLetterE},      /* 85 = 0x00C4: LATIN CAPITAL LETTER A WITH DIAERESIS */
   {0x00C5, U_LatinCapitalLetterA, U_LatinSmallLetterO},      /* 86 = 0x00C5: LATIN CAPITAL LETTER A WITH RING ABOVE */
   {0x00CB, U_LatinCapitalLetterE, U_LatinSmallLetterE},      /* 8B = 0x00CB: LATIN CAPITAL LETTER E WITH DIAERESIS */
   {0x00CF, U_LatinCapitalLetterI, U_LatinSmallLetterE},      /* 8F = 0x00CF: LATIN CAPITAL LETTER I WITH DIAERESIS */
   {0x00D6, U_LatinCapitalLetterO, U_LatinSmallLetterE},      /* 96 = 0x00D6: LATIN CAPITAL LETTER O WITH DIAERESIS */
   {0x00DC, U_LatinCapitalLetterO, U_LatinSmallLetterE},      /* 9A = 0x00DC: LATIN CAPITAL LETTER U WITH DIAERESIS */
   {0xFB01, U_LatinSmallLetterF,   U_LatinSmallLetterI},      /* AE = 0xFB01: LATIN SMALL LIGATURE FI */
   {0xFB02, U_LatinSmallLetterF,   U_LatinSmallLetterL},      /* AF = 0xFB02: LATIN SMALL LIGATURE FL */
   {0x00E4, U_LatinSmallLetterA,   U_LatinSmallLetterE},      /* D9 = 0x00E4: LATIN SMALL LETTER A WITH DIAERESIS */
   {0x00E5, U_LatinSmallLetterA,   U_LatinSmallLetterO},      /* DA = 0x00E5: LATIN SMALL LETTER A WITH RING ABOVE */
   {0x00EB, U_LatinSmallLetterE,   U_LatinSmallLetterE},      /* DF = 0x00EB: LATIN SMALL LETTER E WITH DIAERESIS */
   {0x00C6, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* E1 = 0x00C6: LATIN CAPITAL LETTER AE */
   {0x00EF, U_LatinSmallLetterI,   U_LatinSmallLetterE},      /* E5 = 0x00EF: LATIN SMALL LETTER I WITH DIAERESIS */
   {0x00D8, U_LatinCapitalLetterO, U_LatinSmallLetterE},      /* E9 = 0x00D8: LATIN CAPITAL LETTER O WITH STROKE */
   {0x0152, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* EA = 0x0152: LATIN CAPITAL LIGATURE OE */
   {0x00F6, U_LatinSmallLetterO,   U_LatinSmallLetterE},      /* F0 = 0x00F6: LATIN SMALL LETTER O WITH DIAERESIS */
   {0x00E6, U_LatinSmallLetterA,   U_LatinSmallLetterE},      /* F1 = 0x00E6: LATIN SMALL LETTER AE */
   {0x00FC, U_LatinSmallLetterU,   U_LatinSmallLetterE},      /* F6 = 0x00FC: LATIN SMALL LETTER U WITH DIAERESIS */
   {0x00F8, U_LatinSmallLetterO,   U_LatinSmallLetterE},      /* F9 = 0x00F8: LATIN SMALL LETTER O WITH STROKE */
   {0x0153, U_LatinSmallLetterO,   U_LatinSmallLetterE},      /* FA = 0x0153: LATIN SMALL LIGATURE OE */
   {0x00DF, U_LatinSmallLetterS,   U_LatinSmallLetterS},      /* FB = 0x00DF: LATIN SMALL LETTER SHARP S */
};





/******************************************************************************
*
*  CODE_NEXT sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_NEXT[] =         /* CODE_NEXT */
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

   U_NB_SP,                               /* 80 = 0x00A0: NO-BREAK SPACE */
   U_LatinCapitalLetterA,                 /* 81 = 0x00C0: LATIN CAPITAL LETTER A WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 82 = 0x00C1: LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 83 = 0x00C2: LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 84 = 0x00C3: LATIN CAPITAL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 85 = 0x00C4: LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 86 = 0x00C5: LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterC,                 /* 87 = 0x00C7: LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinCapitalLetterE,                 /* 88 = 0x00C8: LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinCapitalLetterE,                 /* 89 = 0x00C9: LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 8A = 0x00CA: LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 8B = 0x00CB: LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterI,                 /* 8C = 0x00CC: LATIN CAPITAL LETTER I WITH GRAVE */
   U_LatinCapitalLetterI,                 /* 8D = 0x00CD: LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 8E = 0x00CE: LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 8F = 0x00CF: LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_LatinCapitalLetterEth,               /* 90 = 0x00D0: LATIN CAPITAL LETTER ETH */
   U_LatinCapitalLetterN,                 /* 91 = 0x00D1: LATIN CAPITAL LETTER N WITH TILDE */
   U_LatinCapitalLetterO,                 /* 92 = 0x00D2: LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinCapitalLetterO,                 /* 93 = 0x00D3: LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 94 = 0x00D4: LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 95 = 0x00D5: LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 96 = 0x00D6: LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 97 = 0x00D9: LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinCapitalLetterU,                 /* 98 = 0x00DA: LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 99 = 0x00DB: LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 9A = 0x00DC: LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterY,                 /* 9B = 0x00DD: LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterThorn,             /* 9C = 0x00DE: LATIN CAPITAL LETTER THORN */
   U_MicroSign,                           /* 9D = 0x00B5: MICRO SIGN */
   U_MultiplicationSign,                  /* 9E = 0x00D7: MULTIPLICATION SIGN */
   U_DivisionSign,                        /* 9F = 0x00F7: DIVISION SIGN */
   U_CopyrightSign,                       /* A0 = 0x00A9: COPYRIGHT SIGN */
   U_InvertedExclamationMark,             /* A1 = 0x00A1: INVERTED EXCLAMATION MARK */
   U_CentSign,                            /* A2 = 0x00A2: CENT SIGN */
   U_PoundSign,                           /* A3 = 0x00A3: POUND SIGN */
   U_FractionSlash,                       /* A4 = 0x2044: FRACTION SLASH */
   U_YenSign,                             /* A5 = 0x00A5: YEN SIGN */
   U_LatinSmallLetterF,                   /* A6 = 0x0192: LATIN SMALL LETTER F WITH HOOK */
   U_SectionSign,                         /* A7 = 0x00A7: SECTION SIGN */
   U_CurrencySign,                        /* A8 = 0x00A4: CURRENCY SIGN */
   U_LeftDoubleQuotationMark,             /* AA = 0x201C: LEFT DOUBLE QUOTATION MARK */
   U_LeftPointingGuillemet,               /* AB = 0x00AB: LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LeftPointingSingleGuillemet,         /* AC = 0x2039: SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_RightPointingSingleGuillemet,        /* AD = 0x203A: SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinSmallLigatureFI,                /* AE = 0xFB01: LATIN SMALL LIGATURE FI */
   U_LatinSmallLigatureFL,                /* AF = 0xFB02: LATIN SMALL LIGATURE FL */
   U_RegisteredSign,                      /* B0 = 0x00AE: REGISTERED SIGN */
   U_EnDash,                              /* B1 = 0x2013: EN DASH */
   U_Dagger,                              /* B2 = 0x2020: DAGGER */
   U_DoubleDagger,                        /* B3 = 0x2021: DOUBLE DAGGER */
   U_MiddleDot,                           /* B4 = 0x00B7: MIDDLE DOT */
   U_BrokenVerticalBar,                   /* B5 = 0x00A6: BROKEN BAR */
   U_ParagraphSign,                       /* B6 = 0x00B6: PILCROW SIGN */
   U_Bullet,                              /* B7 = 0x2022: BULLET OPERATOR */
   U_SingleLow9QuotationMark,             /* B8 = 0x201A: SINGLE LOW-9 QUOTATION MARK */
   U_DoubleLow9QuotationMark,             /* B9 = 0x201E: DOUBLE LOW-9 QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* BA = 0x201D: RIGHT DOUBLE QUOTATION MARK */
   U_RightPointingGuillemet,              /* BB = 0x00BB: RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_HorizontalEllipsis,                  /* BC = 0x2026: MIDLINE HORIZONTAL ELLIPSIS */
   U_PerMilleSign,                        /* BD = 0x2030: PER MILLE SIGN */
   U_NotSign,                             /* BE = 0x00AC: NOT SIGN */
   U_InvertedQuestionMark,                /* BF = 0x00BF: INVERTED QUESTION MARK */
   U_SuperscriptOne,                      /* C0 = 0x00B9: SUPERSCRIPT ONE */
   U_CombiningGraveAccent,                /* C1 = 0x0300: COMBINING GRAVE ACCENT */
   U_AcuteAccent,                         /* C2 = 0x00B4: ACUTE ACCENT */
   U_CombiningCircumflexAccent,           /* C3 = 0x0302: COMBINING CIRCUMFLEX ACCENT */
   U_CombiningTilde,                      /* C4 = 0x0303: COMBINING TILDE */
   U_Macron,                              /* C5 = 0x00AF: MACRON */
   U_Breve,                               /* C6 = 0x02D8: BREVE */
   U_DotAbove,                            /* C7 = 0x02D9: DOT ABOVE */
   U_Diaeresis,                           /* C8 = 0x00A8: DIAERESIS */
   U_SuperscriptTwo,                      /* C9 = 0x00B2: SUPERSCRIPT TWO */
   U_DegreeSign,                          /* CA = 0x00B0: DEGREE SIGN */
   U_Cedilla,                             /* CB = 0x00B8: CEDILLA */
   U_SuperscriptThree,                    /* CC = 0x00B3: SUPERSCRIPT THREE */
   U_DoubleAcuteAccent,                   /* CD = 0x02DD: DOUBLE ACUTE ACCENT */
   U_Ogonek,                              /* CE = 0x02DB: OGONEK */
   U_Caron,                               /* CF = 0x02C7: CARON */
   U_EmDash,                              /* D0 = 0x2014: EM DASH */
   U_PlusMinusSign,                       /* D1 = 0x00B1: PLUS-MINUS SIGN */
   U_VulgarFractionOneQuarter,            /* D2 = 0x00BC: VULGAR FRACTION ONE QUARTER */
   U_VulgarFractionOneHalf,               /* D3 = 0x00BD: VULGAR FRACTION ONE HALF */
   U_VulgarFractionThreeQuarters,         /* D4 = 0x00BE: VULGAR FRACTION THREE QUARTERS */
   U_LatinSmallLetterA,                   /* D5 = 0x00E0: LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterA,                   /* D6 = 0x00E1: LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterA,                   /* D7 = 0x00E2: LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterA,                   /* D8 = 0x00E3: LATIN SMALL LETTER A WITH TILDE */
   U_LatinSmallLetterA,                   /* D9 = 0x00E4: LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterA,                   /* DA = 0x00E5: LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterC,                   /* DB = 0x00E7: LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterE,                   /* DC = 0x00E8: LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterE,                   /* DD = 0x00E9: LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterE,                   /* DE = 0x00EA: LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterE,                   /* DF = 0x00EB: LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterI,                   /* E0 = 0x00EC: LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLigatureAE,              /* E1 = 0x00C6: LATIN CAPITAL LETTER AE */
   U_LatinSmallLetterI,                   /* E2 = 0x00ED: LATIN SMALL LETTER I WITH ACUTE */
   U_FeminineOrdinalIndicator,            /* E3 = 0x00AA: FEMININE ORDINAL INDICATOR */
   U_LatinSmallLetterI,                   /* E4 = 0x00EE: LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterI,                   /* E5 = 0x00EF: LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterEth,                 /* E6 = 0x00F0: LATIN SMALL LETTER ETH */
   U_LatinSmallLetterN,                   /* E7 = 0x00F1: LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterL,                 /* E8 = 0x0141: LATIN CAPITAL LETTER L WITH STROKE */
   U_LatinCapitalLetterOSlash,            /* E9 = 0x00D8: LATIN CAPITAL LETTER O WITH STROKE */
   U_LatinCapitalLigatureOE,              /* EA = 0x0152: LATIN CAPITAL LIGATURE OE */
   U_MasculineOrdinalIndicator,           /* EB = 0x00BA: MASCULINE ORDINAL INDICATOR */
   U_LatinSmallLetterO,                   /* EC = 0x00F2: LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterO,                   /* ED = 0x00F3: LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterO,                   /* EE = 0x00F4: LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterO,                   /* EF = 0x00F5: LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterO,                   /* F0 = 0x00F6: LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLigatureAE,                /* F1 = 0x00E6: LATIN SMALL LETTER AE */
   U_LatinSmallLetterU,                   /* F2 = 0x00F9: LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterU,                   /* F3 = 0x00FA: LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterU,                   /* F4 = 0x00FB: LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterI,                   /* F5 = 0x0131: LATIN SMALL LETTER DOTLESS I */
   U_LatinSmallLetterU,                   /* F6 = 0x00FC: LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterY,                   /* F7 = 0x00FD: LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinSmallLetterL,                   /* F8 = 0x0142: LATIN SMALL LETTER L WITH STROKE */
   U_LatinSmallLetterOSlash,              /* F9 = 0x00F8: LATIN SMALL LETTER O WITH STROKE */
   U_LatinSmallLigatureOE,                /* FA = 0x0153: LATIN SMALL LIGATURE OE */
   U_LatinSmallLetterSharpS,              /* FB = 0x00DF: LATIN SMALL LETTER SHARP S */
   U_LatinSmallLetterThorn,               /* FC = 0x00FE: LATIN SMALL LETTER THORN */
   U_LatinSmallLetterY,                   /* FD = 0x00FF: LATIN SMALL LETTER Y WITH DIAERESIS */
   U_NIL,                                 /* FE */
   U_NIL                                  /* FF */
};
