/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_dos.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepages for DOS encoding:
*                 - codepage 437 (cp437) = LatinUS
*                 - codepage 850 (cp850) = Latin1
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
*    fd  Feb 16: CODE_437_lig[] + sort_CODE_437[] added
*    fd  Feb 17: CODE_850_lig[] + sort_CODE_850[] added
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
*  u_CODE_437[]:
*     Unicode named codepage for DOS encoding (codepage 437)
*
******************************************|************************************/

static _UWORD const u_CODE_437[] =             /* CODE_437 */
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

   U_LatinCapitalLetterCWithCedilla,      /* 0x80  - 0x00c7:  LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinSmallLetterUWithDiaeresis,      /* 0x81  - 0x00fc:  LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterEWithAcute,          /* 0x82  - 0x00e9:  LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0x83  - 0x00e2:  LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithDiaeresis,      /* 0x84  - 0x00e4:  LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithGrave,          /* 0x85  - 0x00e0:  LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithRingAbove,      /* 0x86  - 0x00e5:  LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterCWithCedilla,        /* 0x87  - 0x00e7:  LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithCircumflex,     /* 0x88  - 0x00ea:  LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0x89  - 0x00eb:  LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterEWithGrave,          /* 0x8a  - 0x00e8:  LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterIWithDiaeresis,      /* 0x8b  - 0x00ef:  LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterIWithCircumflex,     /* 0x8c  - 0x00ee:  LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithGrave,          /* 0x8d  - 0x00ec:  LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0x8e  - 0x00c4:  LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0x8f  - 0x00c5:  LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterEWithAcute,        /* 0x90  - 0x00c9:  LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinSmallLigatureAE,                /* 0x91  - 0x00e6:  LATIN SMALL LIGATURE AE */
   U_LatinCapitalLigatureAE,              /* 0x92  - 0x00c6:  LATIN CAPITAL LIGATURE AE */
   U_LatinSmallLetterOWithCircumflex,     /* 0x93  - 0x00f4:  LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithDiaeresis,      /* 0x94  - 0x00f6:  LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterOWithGrave,          /* 0x95  - 0x00f2:  LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterUWithCircumflex,     /* 0x96  - 0x00fb:  LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithGrave,          /* 0x97  - 0x00f9:  LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterYWithDiaeresis,      /* 0x98  - 0x00ff:  LATIN SMALL LETTER Y WITH DIAERESIS */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0x99  - 0x00d6:  LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0x9a  - 0x00dc:  LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_CentSign,                            /* 0x9b  - 0x00a2:  CENT SIGN */
   U_PoundSign,                           /* 0x9c  - 0x00a3:  POUND SIGN */
   U_YenSign,                             /* 0x9d  - 0x00a5:  YEN SIGN */
   U_PesetaSign,                          /* 0x9e  - 0x20a7:  PESETA SIGN */
   U_LatinSmallLetterScriptF,             /* 0x9f  - 0x0192:  LATIN SMALL LETTER F WITH HOOK */
   U_LatinSmallLetterAWithAcute,          /* 0xa0  - 0x00e1:  LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterIWithAcute,          /* 0xa1  - 0x00ed:  LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterOWithAcute,          /* 0xa2  - 0x00f3:  LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterUWithAcute,          /* 0xa3  - 0x00fa:  LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterNWithTilde,          /* 0xa4  - 0x00f1:  LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterNWithTilde,        /* 0xa5  - 0x00d1:  LATIN CAPITAL LETTER N WITH TILDE */
   U_FeminineOrdinalIndicator,            /* 0xa6  - 0x00aa:  FEMININE ORDINAL INDICATOR */
   U_MasculineOrdinalIndicator,           /* 0xa7  - 0x00ba:  MASCULINE ORDINAL INDICATOR */
   U_InvertedQuestionMark,                /* 0xa8  - 0x00bf:  INVERTED QUESTION MARK */
   U_ReversedNotSign,                     /* 0xa9  - 0x2310:  REVERSED NOT SIGN */
   U_NotSign,                             /* 0xaa  - 0x00ac:  NOT SIGN */
   U_VulgarFractionOneHalf,               /* 0xab  - 0x00bd:  VULGAR FRACTION ONE HALF */
   U_VulgarFractionOneQuarter,            /* 0xac  - 0x00bc:  VULGAR FRACTION ONE QUARTER */
   U_InvertedExclamationMark,             /* 0xad  - 0x00a1:  INVERTED EXCLAMATION MARK */
   U_LeftPointingGuillemet,               /* 0xae  - 0x00ab:  LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_RightPointingGuillemet,              /* 0xaf  - 0x00bb:  RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LightShade,                          /* 0xb0  - 0x2591:  LIGHT SHADE */
   U_MediumShade,                         /* 0xb1  - 0x2592:  MEDIUM SHADE */
   U_DarkShade,                           /* 0xb2  - 0x2593:  DARK SHADE */
   U_BoxDrawingsLightVertical,            /* 0xb3  - 0x2502:  BOX DRAWINGS LIGHT VERTICAL */
   U_BoxDrawingsLightVerticalAndLeft,     /* 0xb4  - 0x2524:  BOX DRAWINGS LIGHT VERTICAL AND LEFT */
                                          /* 0xb5  - 0x2561:  BOX DRAWINGS VERTICAL SINGLE AND LEFT DOUBLE */
   U_BoxDrawingsVerticalSingleAndLeftDouble,
                                          /* 0xb6  - 0x2562:  BOX DRAWINGS VERTICAL DOUBLE AND LEFT SINGLE */
   U_BoxDrawingsVerticalDoubleAndLeftSingle,
   U_BoxDrawingsDownDoubleAndLeftSingle,  /* 0xb7  - 0x2556:  BOX DRAWINGS DOWN DOUBLE AND LEFT SINGLE */
   U_BoxDrawingsDownSingleAndLeftDouble,  /* 0xb8  - 0x2555:  BOX DRAWINGS DOWN SINGLE AND LEFT DOUBLE */
   U_BoxDrawingsDoubleVerticalAndLeft,    /* 0xb9  - 0x2563:  BOX DRAWINGS DOUBLE VERTICAL AND LEFT */
   U_BoxDrawingsDoubleVertical,           /* 0xba  - 0x2551:  BOX DRAWINGS DOUBLE VERTICAL */
   U_BoxDrawingsDoubleDownAndLeft,        /* 0xbb  - 0x2557:  BOX DRAWINGS DOUBLE DOWN AND LEFT */
   U_BoxDrawingsDoubleUpAndLeft,          /* 0xbc  - 0x255d:  BOX DRAWINGS DOUBLE UP AND LEFT */
   U_BoxDrawingsUpDoubleAndLeftSingle,    /* 0xbd  - 0x255c:  BOX DRAWINGS UP DOUBLE AND LEFT SINGLE */
   U_BoxDrawingsUpSingleAndLeftDouble,    /* 0xbe  - 0x255b:  BOX DRAWINGS UP SINGLE AND LEFT DOUBLE */
   U_BoxDrawingsLightDownAndLeft,         /* 0xbf  - 0x2510:  BOX DRAWINGS LIGHT DOWN AND LEFT */
   U_BoxDrawingsLightUpAndRight,          /* 0xc0  - 0x2514:  BOX DRAWINGS LIGHT UP AND RIGHT */
   U_BoxDrawingsLightUpAndHorizontal,     /* 0xc1  - 0x2534:  BOX DRAWINGS LIGHT UP AND HORIZONTAL */
   U_BoxDrawingsLightDownAndHorizontal,   /* 0xc2  - 0x252c:  BOX DRAWINGS LIGHT DOWN AND HORIZONTAL */
   U_BoxDrawingsLightVerticalAndRight,    /* 0xc3  - 0x251c:  BOX DRAWINGS LIGHT VERTICAL AND RIGHT */
   U_BoxDrawingsLightHorizontal,          /* 0xc4  - 0x2500:  BOX DRAWINGS LIGHT HORIZONTAL */
                                          /* 0xc5  - 0x253c:  BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL */
   U_BoxDrawingsLightVerticalAndHorizontal,
                                          /* 0xc6  - 0x255e:  BOX DRAWINGS VERTICAL SINGLE AND RIGHT DOUBLE */
   U_BoxDrawingsVerticalSingleAndRightDouble,
                                          /* 0xc7  - 0x255f:  BOX DRAWINGS VERTICAL DOUBLE AND RIGHT SINGLE */
   U_BoxDrawingsVerticalDoubleAndRightSingle,
   U_BoxDrawingsDoubleUpAndRight,         /* 0xc8  - 0x255a:  BOX DRAWINGS DOUBLE UP AND RIGHT */
   U_BoxDrawingsDoubleDownAndRight,       /* 0xc9  - 0x2554:  BOX DRAWINGS DOUBLE DOWN AND RIGHT */
   U_BoxDrawingsDoubleUpAndHorizontal,    /* 0xca  - 0x2569:  BOX DRAWINGS DOUBLE UP AND HORIZONTAL */
   U_BoxDrawingsDoubleDownAndHorizontal,  /* 0xcb  - 0x2566:  BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL */
   U_BoxDrawingsDoubleVerticalAndRight,   /* 0xcc  - 0x2560:  BOX DRAWINGS DOUBLE VERTICAL AND RIGHT */
   U_BoxDrawingsDoubleHorizontal,         /* 0xcd  - 0x2550:  BOX DRAWINGS DOUBLE HORIZONTAL */
                                          /* 0xce  - 0x256c:  BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL */
   U_BoxDrawingsDoubleVerticalAndHorizontal,
                                          /* 0xcf  - 0x2567:  BOX DRAWINGS UP SINGLE AND HORIZONTAL DOUBLE */
   U_BoxDrawingsUpSingleAndHorizontalDouble,
                                          /* 0xd0  - 0x2568:  BOX DRAWINGS UP DOUBLE AND HORIZONTAL SINGLE */
   U_BoxDrawingsUpDoubleAndHorizontalSingle,
                                          /* 0xd1  - 0x2564:  BOX DRAWINGS DOWN SINGLE AND HORIZONTAL DOUBLE */
   U_BoxDrawingsDownSingleAndHorizontalDouble,
                                          /* 0xd2  - 0x2565:  BOX DRAWINGS DOWN DOUBLE AND HORIZONTAL SINGLE */
   U_BoxDrawingsDownDoubleAndHorizontalSingle,
   U_BoxDrawingsUpDoubleAndRightSingle,   /* 0xd3  - 0x2559:  BOX DRAWINGS UP DOUBLE AND RIGHT SINGLE */
   U_BoxDrawingsUpSingleAndRightDouble,   /* 0xd4  - 0x2558:  BOX DRAWINGS UP SINGLE AND RIGHT DOUBLE */
   U_BoxDrawingsDownSingleAndRightDouble, /* 0xd5  - 0x2552:  BOX DRAWINGS DOWN SINGLE AND RIGHT DOUBLE */
   U_BoxDrawingsDownDoubleAndRightSingle, /* 0xd6  - 0x2553:  BOX DRAWINGS DOWN DOUBLE AND RIGHT SINGLE */
                                          /* 0xd7  - 0x256b:  BOX DRAWINGS VERTICAL DOUBLE AND HORIZONTAL SINGLE */
   U_BoxDrawingsVerticalDoubleAndHorizontalSingle,
                                          /* 0xd8  - 0x256a:  BOX DRAWINGS VERTICAL SINGLE AND HORIZONTAL DOUBLE */
   U_BoxDrawingsVerticalSingleAndHorizontalDouble,
   U_BoxDrawingsLightUpAndLeft,           /* 0xd9  - 0x2518:  BOX DRAWINGS LIGHT UP AND LEFT */
   U_BoxDrawingsLightDownAndRight,        /* 0xda  - 0x250c:  BOX DRAWINGS LIGHT DOWN AND RIGHT */
   U_FullBlock,                           /* 0xdb  - 0x2588:  FULL BLOCK */
   U_LowerHalfBlock,                      /* 0xdc  - 0x2584:  LOWER HALF BLOCK */
   U_LeftHalfBlock,                       /* 0xdd  - 0x258c:  LEFT HALF BLOCK */
   U_RightHalfBlock,                      /* 0xde  - 0x2590:  RIGHT HALF BLOCK */
   U_UpperHalfBlock,                      /* 0xdf  - 0x2580:  UPPER HALF BLOCK */
   U_GreekSmallLetterAlpha,               /* 0xe0  - 0x03b1:  GREEK SMALL LETTER ALPHA */
   U_LatinSmallLetterSharpS,              /* 0xe1  - 0x00df:  LATIN SMALL LETTER SHARP S */
   U_GreekCapitalLetterGamma,             /* 0xe2  - 0x0393:  GREEK CAPITAL LETTER GAMMA */
   U_GreekSmallLetterPi,                  /* 0xe3  - 0x03c0:  GREEK SMALL LETTER PI */
   U_GreekCapitalLetterSigma,             /* 0xe4  - 0x03a3:  GREEK CAPITAL LETTER SIGMA */
   U_GreekSmallLetterSigma,               /* 0xe5  - 0x03c3:  GREEK SMALL LETTER SIGMA */
   U_MicroSign,                           /* 0xe6  - 0x00b5:  MICRO SIGN */
   U_GreekSmallLetterTau,                 /* 0xe7  - 0x03c4:  GREEK SMALL LETTER TAU */
   U_GreekCapitalLetterPhi,               /* 0xe8  - 0x03a6:  GREEK CAPITAL LETTER PHI */
   U_GreekCapitalLetterTheta,             /* 0xe9  - 0x0398:  GREEK CAPITAL LETTER THETA */
   U_GreekCapitalLetterOmega,             /* 0xea  - 0x03a9:  GREEK CAPITAL LETTER OMEGA */
   U_GreekSmallLetterDelta,               /* 0xeb  - 0x03b4:  GREEK SMALL LETTER DELTA */
   U_Infinity,                            /* 0xec  - 0x221e:  INFINITY */
   U_GreekSmallLetterPhi,                 /* 0xed  - 0x03c6:  GREEK SMALL LETTER PHI */
   U_GreekSmallLetterEpsilon,             /* 0xee  - 0x03b5:  GREEK SMALL LETTER EPSILON */
   U_Intersection,                        /* 0xef  - 0x2229:  INTERSECTION */
   U_IdenticalTo,                         /* 0xf0  - 0x2261:  IDENTICAL TO */
   U_PlusMinusSign,                       /* 0xf1  - 0x00b1:  PLUS-MINUS SIGN */
   U_GreaterThanOrEqualTo,                /* 0xf2  - 0x2265:  GREATER-THAN OR EQUAL TO */
   U_LessThanOrEqualTo,                   /* 0xf3  - 0x2264:  LESS-THAN OR EQUAL TO */
   U_TopHalfIntegral,                     /* 0xf4  - 0x2320:  TOP HALF INTEGRAL */
   U_BottomHalfIntegral,                  /* 0xf5  - 0x2321:  BOTTOM HALF INTEGRAL */
   U_DivisionSign,                        /* 0xf6  - 0x00f7:  DIVISION SIGN */
   U_AlmostEqualTo,                       /* 0xf7  - 0x2248:  ALMOST EQUAL TO */
   U_DegreeSign,                          /* 0xf8  - 0x00b0:  DEGREE SIGN */
   U_BulletOperator,                      /* 0xf9  - 0x2219:  BULLET OPERATOR */
   U_MiddleDot,                           /* 0xfa  - 0x00b7:  MIDDLE DOT */
   U_SquareRoot,                          /* 0xfb  - 0x221a:  SQUARE ROOT */
   U_SuperscriptLatinSmallLetterN,        /* 0xfc  - 0x207f:  SUPERSCRIPT LATIN SMALL LETTER N */
   U_SuperscriptTwo,                      /* 0xfd  - 0x00b2:  SUPERSCRIPT TWO */
   U_BlackSquare,                         /* 0xfe  - 0x25a0:  BLACK SQUARE */
   U_NB_SP                                /* 0xff  - 0x00a0:  NO-BREAK SPACE */
};





/******************************************************************************
*
*  CODE_437_lig[]:
*     list of ligatures:
*
*  CODE_437_lig[0] is the original ligature character
*  CODE_437_lig[1] + CODE_437_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_437_lig[][3] =     /* CODE_437 character ligatures */
{
   {0x00fc, U_LatinSmallLetterU,   U_LatinSmallLetterE},      /* 0x81  - 0x00fc:  LATIN SMALL LETTER U WITH DIAERESIS */
   {0x00e4, U_LatinSmallLetterA,   U_LatinSmallLetterE},      /* 0x84  - 0x00e4:  LATIN SMALL LETTER A WITH DIAERESIS */
   {0x00e5, U_LatinSmallLetterA,   U_LatinSmallLetterO},      /* 0x86  - 0x00e5:  LATIN SMALL LETTER A WITH RING ABOVE */
   {0x00eb, U_LatinSmallLetterE,   U_LatinSmallLetterE},      /* 0x89  - 0x00eb:  LATIN SMALL LETTER E WITH DIAERESIS */
   {0x00ef, U_LatinSmallLetterI,   U_LatinSmallLetterE},      /* 0x8b  - 0x00ef:  LATIN SMALL LETTER I WITH DIAERESIS */
   {0x00c4, U_LatinCapitalLetterA, U_LatinSmallLetterE},      /* 0x8e  - 0x00c4:  LATIN CAPITAL LETTER A WITH DIAERESIS */
   {0x00c5, U_LatinCapitalLetterA, U_LatinSmallLetterO},      /* 0x8f  - 0x00c5:  LATIN CAPITAL LETTER A WITH RING ABOVE */
   {0x00e6, U_LatinSmallLetterA,   U_LatinSmallLetterE},      /* 0x91  - 0x00e6:  LATIN SMALL LIGATURE AE */
   {0x00c6, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x92  - 0x00c6:  LATIN CAPITAL LIGATURE AE */
   {0x00f6, U_LatinSmallLetterO,   U_LatinSmallLetterE},      /* 0x94  - 0x00f6:  LATIN SMALL LETTER O WITH DIAERESIS */
   {0x00ff, U_LatinSmallLetterY,   U_LatinSmallLetterE},      /* 0x98  - 0x00ff:  LATIN SMALL LETTER Y WITH DIAERESIS */
   {0x00d6, U_LatinCapitalLetterO, U_LatinSmallLetterE},      /* 0x99  - 0x00d6:  LATIN CAPITAL LETTER O WITH DIAERESIS */
   {0x00dc, U_LatinCapitalLetterU, U_LatinSmallLetterE},      /* 0x9a  - 0x00dc:  LATIN CAPITAL LETTER U WITH DIAERESIS */
   {0x00df, U_LatinSmallLetterS,   U_LatinSmallLetterS},      /* 0xe1  - 0x00df:  LATIN SMALL LETTER SHARP S */
   {0x0000, U_NIL                , U_NIL}                     /* list terminator */
};





/******************************************************************************
*
*  CODE_437 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_437[] =          /* CODE_437 */
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

   U_LatinCapitalLetterC,                 /* 0x80  - 0x00c7:  LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinSmallLetterU,                   /* 0x81  - 0x00fc:  LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterE,                   /* 0x82  - 0x00e9:  LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterA,                   /* 0x83  - 0x00e2:  LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterA,                   /* 0x84  - 0x00e4:  LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterA,                   /* 0x85  - 0x00e0:  LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterA,                   /* 0x86  - 0x00e5:  LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterC,                   /* 0x87  - 0x00e7:  LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterE,                   /* 0x88  - 0x00ea:  LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterE,                   /* 0x89  - 0x00eb:  LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterE,                   /* 0x8a  - 0x00e8:  LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterI,                   /* 0x8b  - 0x00ef:  LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterI,                   /* 0x8c  - 0x00ee:  LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterI,                   /* 0x8d  - 0x00ec:  LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0x8e  - 0x00c4:  LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0x8f  - 0x00c5:  LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterE,                 /* 0x90  - 0x00c9:  LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinSmallLigatureAE,                /* 0x91  - 0x00e6:  LATIN SMALL LIGATURE AE */
   U_LatinCapitalLigatureAE,              /* 0x92  - 0x00c6:  LATIN CAPITAL LIGATURE AE */
   U_LatinSmallLetterO,                   /* 0x93  - 0x00f4:  LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterO,                   /* 0x94  - 0x00f6:  LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterO,                   /* 0x95  - 0x00f2:  LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterU,                   /* 0x96  - 0x00fb:  LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterU,                   /* 0x97  - 0x00f9:  LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterY,                   /* 0x98  - 0x00ff:  LATIN SMALL LETTER Y WITH DIAERESIS */
   U_LatinCapitalLetterO,                 /* 0x99  - 0x00d6:  LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0x9a  - 0x00dc:  LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_CentSign,                            /* 0x9b  - 0x00a2:  CENT SIGN */
   U_PoundSign,                           /* 0x9c  - 0x00a3:  POUND SIGN */
   U_YenSign,                             /* 0x9d  - 0x00a5:  YEN SIGN */
   U_PesetaSign,                          /* 0x9e  - 0x20a7:  PESETA SIGN */
   U_LatinSmallLetterF,                   /* 0x9f  - 0x0192:  LATIN SMALL LETTER F WITH HOOK */
   U_LatinSmallLetterA,                   /* 0xa0  - 0x00e1:  LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterI,                   /* 0xa1  - 0x00ed:  LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterO,                   /* 0xa2  - 0x00f3:  LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterU,                   /* 0xa3  - 0x00fa:  LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterN,                   /* 0xa4  - 0x00f1:  LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterN,                 /* 0xa5  - 0x00d1:  LATIN CAPITAL LETTER N WITH TILDE */
   U_FeminineOrdinalIndicator,            /* 0xa6  - 0x00aa:  FEMININE ORDINAL INDICATOR */
   U_MasculineOrdinalIndicator,           /* 0xa7  - 0x00ba:  MASCULINE ORDINAL INDICATOR */
   U_InvertedQuestionMark,                /* 0xa8  - 0x00bf:  INVERTED QUESTION MARK */
   U_ReversedNotSign,                     /* 0xa9  - 0x2310:  REVERSED NOT SIGN */
   U_NotSign,                             /* 0xaa  - 0x00ac:  NOT SIGN */
   U_VulgarFractionOneHalf,               /* 0xab  - 0x00bd:  VULGAR FRACTION ONE HALF */
   U_VulgarFractionOneQuarter,            /* 0xac  - 0x00bc:  VULGAR FRACTION ONE QUARTER */
   U_InvertedExclamationMark,             /* 0xad  - 0x00a1:  INVERTED EXCLAMATION MARK */
   U_LeftPointingGuillemet,               /* 0xae  - 0x00ab:  LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_RightPointingGuillemet,              /* 0xaf  - 0x00bb:  RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LightShade,                          /* 0xb0  - 0x2591:  LIGHT SHADE */
   U_MediumShade,                         /* 0xb1  - 0x2592:  MEDIUM SHADE */
   U_DarkShade,                           /* 0xb2  - 0x2593:  DARK SHADE */
   U_BoxDrawingsLightVertical,            /* 0xb3  - 0x2502:  BOX DRAWINGS LIGHT VERTICAL */
   U_BoxDrawingsLightVerticalAndLeft,     /* 0xb4  - 0x2524:  BOX DRAWINGS LIGHT VERTICAL AND LEFT */
                                          /* 0xb5  - 0x2561:  BOX DRAWINGS VERTICAL SINGLE AND LEFT DOUBLE */
   U_BoxDrawingsVerticalSingleAndLeftDouble,
                                          /* 0xb6  - 0x2562:  BOX DRAWINGS VERTICAL DOUBLE AND LEFT SINGLE */
   U_BoxDrawingsVerticalDoubleAndLeftSingle,
   U_BoxDrawingsDownDoubleAndLeftSingle,  /* 0xb7  - 0x2556:  BOX DRAWINGS DOWN DOUBLE AND LEFT SINGLE */
   U_BoxDrawingsDownSingleAndLeftDouble,  /* 0xb8  - 0x2555:  BOX DRAWINGS DOWN SINGLE AND LEFT DOUBLE */
   U_BoxDrawingsDoubleVerticalAndLeft,    /* 0xb9  - 0x2563:  BOX DRAWINGS DOUBLE VERTICAL AND LEFT */
   U_BoxDrawingsDoubleVertical,           /* 0xba  - 0x2551:  BOX DRAWINGS DOUBLE VERTICAL */
   U_BoxDrawingsDoubleDownAndLeft,        /* 0xbb  - 0x2557:  BOX DRAWINGS DOUBLE DOWN AND LEFT */
   U_BoxDrawingsDoubleUpAndLeft,          /* 0xbc  - 0x255d:  BOX DRAWINGS DOUBLE UP AND LEFT */
   U_BoxDrawingsUpDoubleAndLeftSingle,    /* 0xbd  - 0x255c:  BOX DRAWINGS UP DOUBLE AND LEFT SINGLE */
   U_BoxDrawingsUpSingleAndLeftDouble,    /* 0xbe  - 0x255b:  BOX DRAWINGS UP SINGLE AND LEFT DOUBLE */
   U_BoxDrawingsLightDownAndLeft,         /* 0xbf  - 0x2510:  BOX DRAWINGS LIGHT DOWN AND LEFT */
   U_BoxDrawingsLightUpAndRight,          /* 0xc0  - 0x2514:  BOX DRAWINGS LIGHT UP AND RIGHT */
   U_BoxDrawingsLightUpAndHorizontal,     /* 0xc1  - 0x2534:  BOX DRAWINGS LIGHT UP AND HORIZONTAL */
   U_BoxDrawingsLightDownAndHorizontal,   /* 0xc2  - 0x252c:  BOX DRAWINGS LIGHT DOWN AND HORIZONTAL */
   U_BoxDrawingsLightVerticalAndRight,    /* 0xc3  - 0x251c:  BOX DRAWINGS LIGHT VERTICAL AND RIGHT */
   U_BoxDrawingsLightHorizontal,          /* 0xc4  - 0x2500:  BOX DRAWINGS LIGHT HORIZONTAL */
                                          /* 0xc5  - 0x253c:  BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL */
   U_BoxDrawingsLightVerticalAndHorizontal,
                                          /* 0xc6  - 0x255e:  BOX DRAWINGS VERTICAL SINGLE AND RIGHT DOUBLE */
   U_BoxDrawingsVerticalSingleAndRightDouble,
                                          /* 0xc7  - 0x255f:  BOX DRAWINGS VERTICAL DOUBLE AND RIGHT SINGLE */
   U_BoxDrawingsVerticalDoubleAndRightSingle,
   U_BoxDrawingsDoubleUpAndRight,         /* 0xc8  - 0x255a:  BOX DRAWINGS DOUBLE UP AND RIGHT */
   U_BoxDrawingsDoubleDownAndRight,       /* 0xc9  - 0x2554:  BOX DRAWINGS DOUBLE DOWN AND RIGHT */
   U_BoxDrawingsDoubleUpAndHorizontal,    /* 0xca  - 0x2569:  BOX DRAWINGS DOUBLE UP AND HORIZONTAL */
   U_BoxDrawingsDoubleDownAndHorizontal,  /* 0xcb  - 0x2566:  BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL */
   U_BoxDrawingsDoubleVerticalAndRight,   /* 0xcc  - 0x2560:  BOX DRAWINGS DOUBLE VERTICAL AND RIGHT */
   U_BoxDrawingsDoubleHorizontal,         /* 0xcd  - 0x2550:  BOX DRAWINGS DOUBLE HORIZONTAL */
                                          /* 0xce  - 0x256c:  BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL */
   U_BoxDrawingsDoubleVerticalAndHorizontal,
                                          /* 0xcf  - 0x2567:  BOX DRAWINGS UP SINGLE AND HORIZONTAL DOUBLE */
   U_BoxDrawingsUpSingleAndHorizontalDouble,
                                          /* 0xd0  - 0x2568:  BOX DRAWINGS UP DOUBLE AND HORIZONTAL SINGLE */
   U_BoxDrawingsUpDoubleAndHorizontalSingle,
                                          /* 0xd1  - 0x2564:  BOX DRAWINGS DOWN SINGLE AND HORIZONTAL DOUBLE */
   U_BoxDrawingsDownSingleAndHorizontalDouble,
                                          /* 0xd2  - 0x2565:  BOX DRAWINGS DOWN DOUBLE AND HORIZONTAL SINGLE */
   U_BoxDrawingsDownDoubleAndHorizontalSingle,
   U_BoxDrawingsUpDoubleAndRightSingle,   /* 0xd3  - 0x2559:  BOX DRAWINGS UP DOUBLE AND RIGHT SINGLE */
   U_BoxDrawingsUpSingleAndRightDouble,   /* 0xd4  - 0x2558:  BOX DRAWINGS UP SINGLE AND RIGHT DOUBLE */
   U_BoxDrawingsDownSingleAndRightDouble, /* 0xd5  - 0x2552:  BOX DRAWINGS DOWN SINGLE AND RIGHT DOUBLE */
   U_BoxDrawingsDownDoubleAndRightSingle, /* 0xd6  - 0x2553:  BOX DRAWINGS DOWN DOUBLE AND RIGHT SINGLE */
                                          /* 0xd7  - 0x256b:  BOX DRAWINGS VERTICAL DOUBLE AND HORIZONTAL SINGLE */
   U_BoxDrawingsVerticalDoubleAndHorizontalSingle,
                                          /* 0xd8  - 0x256a:  BOX DRAWINGS VERTICAL SINGLE AND HORIZONTAL DOUBLE */
   U_BoxDrawingsVerticalSingleAndHorizontalDouble,
   U_BoxDrawingsLightUpAndLeft,           /* 0xd9  - 0x2518:  BOX DRAWINGS LIGHT UP AND LEFT */
   U_BoxDrawingsLightDownAndRight,        /* 0xda  - 0x250c:  BOX DRAWINGS LIGHT DOWN AND RIGHT */
   U_FullBlock,                           /* 0xdb  - 0x2588:  FULL BLOCK */
   U_LowerHalfBlock,                      /* 0xdc  - 0x2584:  LOWER HALF BLOCK */
   U_LeftHalfBlock,                       /* 0xdd  - 0x258c:  LEFT HALF BLOCK */
   U_RightHalfBlock,                      /* 0xde  - 0x2590:  RIGHT HALF BLOCK */
   U_UpperHalfBlock,                      /* 0xdf  - 0x2580:  UPPER HALF BLOCK */
   U_GreekSmallLetterAlpha,               /* 0xe0  - 0x03b1:  GREEK SMALL LETTER ALPHA */
   U_LatinSmallLetterSharpS,              /* 0xe1  - 0x00df:  LATIN SMALL LETTER SHARP S */
   U_GreekCapitalLetterGamma,             /* 0xe2  - 0x0393:  GREEK CAPITAL LETTER GAMMA */
   U_GreekSmallLetterPi,                  /* 0xe3  - 0x03c0:  GREEK SMALL LETTER PI */
   U_GreekCapitalLetterSigma,             /* 0xe4  - 0x03a3:  GREEK CAPITAL LETTER SIGMA */
   U_GreekSmallLetterSigma,               /* 0xe5  - 0x03c3:  GREEK SMALL LETTER SIGMA */
   U_MicroSign,                           /* 0xe6  - 0x00b5:  MICRO SIGN */
   U_GreekSmallLetterTau,                 /* 0xe7  - 0x03c4:  GREEK SMALL LETTER TAU */
   U_GreekCapitalLetterPhi,               /* 0xe8  - 0x03a6:  GREEK CAPITAL LETTER PHI */
   U_GreekCapitalLetterTheta,             /* 0xe9  - 0x0398:  GREEK CAPITAL LETTER THETA */
   U_GreekCapitalLetterOmega,             /* 0xea  - 0x03a9:  GREEK CAPITAL LETTER OMEGA */
   U_GreekSmallLetterDelta,               /* 0xeb  - 0x03b4:  GREEK SMALL LETTER DELTA */
   U_Infinity,                            /* 0xec  - 0x221e:  INFINITY */
   U_GreekSmallLetterPhi,                 /* 0xed  - 0x03c6:  GREEK SMALL LETTER PHI */
   U_GreekSmallLetterEpsilon,             /* 0xee  - 0x03b5:  GREEK SMALL LETTER EPSILON */
   U_Intersection,                        /* 0xef  - 0x2229:  INTERSECTION */
   U_IdenticalTo,                         /* 0xf0  - 0x2261:  IDENTICAL TO */
   U_PlusMinusSign,                       /* 0xf1  - 0x00b1:  PLUS-MINUS SIGN */
   U_GreaterThanOrEqualTo,                /* 0xf2  - 0x2265:  GREATER-THAN OR EQUAL TO */
   U_LessThanOrEqualTo,                   /* 0xf3  - 0x2264:  LESS-THAN OR EQUAL TO */
   U_TopHalfIntegral,                     /* 0xf4  - 0x2320:  TOP HALF INTEGRAL */
   U_BottomHalfIntegral,                  /* 0xf5  - 0x2321:  BOTTOM HALF INTEGRAL */
   U_DivisionSign,                        /* 0xf6  - 0x00f7:  DIVISION SIGN */
   U_AlmostEqualTo,                       /* 0xf7  - 0x2248:  ALMOST EQUAL TO */
   U_DegreeSign,                          /* 0xf8  - 0x00b0:  DEGREE SIGN */
   U_BulletOperator,                      /* 0xf9  - 0x2219:  BULLET OPERATOR */
   U_MiddleDot,                           /* 0xfa  - 0x00b7:  MIDDLE DOT */
   U_SquareRoot,                          /* 0xfb  - 0x221a:  SQUARE ROOT */
   U_SuperscriptLatinSmallLetterN,        /* 0xfc  - 0x207f:  SUPERSCRIPT LATIN SMALL LETTER N */
   U_SuperscriptTwo,                      /* 0xfd  - 0x00b2:  SUPERSCRIPT TWO */
   U_BlackSquare,                         /* 0xfe  - 0x25a0:  BLACK SQUARE */
   U_NB_SP                                /* 0xff  - 0x00a0:  NO-BREAK SPACE */
};















/******************************************************************************
*
*  u_CODE_850[]:
*     Unicode named codepage for DOS encoding (codepage 850)
*
******************************************|************************************/

static _UWORD const u_CODE_850[] =             /* CODE_850 */
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

   U_LatinCapitalLetterCWithCedilla,      /* 0x80  - 0x00c7:  LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinSmallLetterUWithDiaeresis,      /* 0x81  - 0x00fc:  LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterEWithAcute,          /* 0x82  - 0x00e9:  LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterAWithCircumflex,     /* 0x83  - 0x00e2:  LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterAWithDiaeresis,      /* 0x84  - 0x00e4:  LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterAWithGrave,          /* 0x85  - 0x00e0:  LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterAWithRingAbove,      /* 0x86  - 0x00e5:  LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterCWithCedilla,        /* 0x87  - 0x00e7:  LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterEWithCircumflex,     /* 0x88  - 0x00ea:  LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterEWithDiaeresis,      /* 0x89  - 0x00eb:  LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterEWithGrave,          /* 0x8a  - 0x00e8:  LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterIWithDiaeresis,      /* 0x8b  - 0x00ef:  LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterIWithCircumflex,     /* 0x8c  - 0x00ee:  LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterIWithGrave,          /* 0x8d  - 0x00ec:  LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0x8e  - 0x00c4:  LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithRingAbove,    /* 0x8f  - 0x00c5:  LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterEWithAcute,        /* 0x90  - 0x00c9:  LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinSmallLigatureAE,                /* 0x91  - 0x00e6:  LATIN SMALL LIGATURE AE */
   U_LatinCapitalLigatureAE,              /* 0x92  - 0x00c6:  LATIN CAPITAL LIGATURE AE */
   U_LatinSmallLetterOWithCircumflex,     /* 0x93  - 0x00f4:  LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithDiaeresis,      /* 0x94  - 0x00f6:  LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterOWithGrave,          /* 0x95  - 0x00f2:  LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterUWithCircumflex,     /* 0x96  - 0x00fb:  LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithGrave,          /* 0x97  - 0x00f9:  LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterYWithDiaeresis,      /* 0x98  - 0x00ff:  LATIN SMALL LETTER Y WITH DIAERESIS */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0x99  - 0x00d6:  LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0x9a  - 0x00dc:  LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterOSlash,              /* 0x9b  - 0x00f8:  LATIN SMALL LETTER O WITH STROKE */
   U_PoundSign,                           /* 0x9c  - 0x00a3:  POUND SIGN */
   U_LatinCapitalLetterOSlash,            /* 0x9d  - 0x00d8:  LATIN CAPITAL LETTER O WITH STROKE */
   U_MultiplicationSign,                  /* 0x9e  - 0x00d7:  MULTIPLICATION SIGN */
   U_LatinSmallLetterScriptF,             /* 0x9f  - 0x0192:  LATIN SMALL LETTER F WITH HOOK */
   U_LatinSmallLetterAWithAcute,          /* 0xa0  - 0x00e1:  LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterIWithAcute,          /* 0xa1  - 0x00ed:  LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterOWithAcute,          /* 0xa2  - 0x00f3:  LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterUWithAcute,          /* 0xa3  - 0x00fa:  LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterNWithTilde,          /* 0xa4  - 0x00f1:  LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterNWithTilde,        /* 0xa5  - 0x00d1:  LATIN CAPITAL LETTER N WITH TILDE */
   U_FeminineOrdinalIndicator,            /* 0xa6  - 0x00aa:  FEMININE ORDINAL INDICATOR */
   U_MasculineOrdinalIndicator,           /* 0xa7  - 0x00ba:  MASCULINE ORDINAL INDICATOR */
   U_InvertedQuestionMark,                /* 0xa8  - 0x00bf:  INVERTED QUESTION MARK */
   U_RegisteredSign,                      /* 0xa9  - 0x00ae:  REGISTERED SIGN */
   U_NotSign,                             /* 0xaa  - 0x00ac:  NOT SIGN */
   U_VulgarFractionOneHalf,               /* 0xab  - 0x00bd:  VULGAR FRACTION ONE HALF */
   U_VulgarFractionOneQuarter,            /* 0xac  - 0x00bc:  VULGAR FRACTION ONE QUARTER */
   U_InvertedExclamationMark,             /* 0xad  - 0x00a1:  INVERTED EXCLAMATION MARK */
   U_LeftPointingGuillemet,               /* 0xae  - 0x00ab:  LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_RightPointingGuillemet,              /* 0xaf  - 0x00bb:  RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LightShade,                          /* 0xb0  - 0x2591:  LIGHT SHADE */
   U_MediumShade,                         /* 0xb1  - 0x2592:  MEDIUM SHADE */
   U_DarkShade,                           /* 0xb2  - 0x2593:  DARK SHADE */
   U_BoxDrawingsLightVertical,            /* 0xb3  - 0x2502:  BOX DRAWINGS LIGHT VERTICAL */
   U_BoxDrawingsLightVerticalAndLeft,     /* 0xb4  - 0x2524:  BOX DRAWINGS LIGHT VERTICAL AND LEFT */
   U_LatinCapitalLetterAWithAcute,        /* 0xb5  - 0x00c1:  LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xb6  - 0x00c2:  LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterAWithGrave,        /* 0xb7  - 0x00c0:  LATIN CAPITAL LETTER A WITH GRAVE */
   U_CopyrightSign,                       /* 0xb8  - 0x00a9:  COPYRIGHT SIGN */
   U_BoxDrawingsDoubleVerticalAndLeft,    /* 0xb9  - 0x2563:  BOX DRAWINGS DOUBLE VERTICAL AND LEFT */
   U_BoxDrawingsDoubleVertical,           /* 0xba  - 0x2551:  BOX DRAWINGS DOUBLE VERTICAL */
   U_BoxDrawingsDoubleDownAndLeft,        /* 0xbb  - 0x2557:  BOX DRAWINGS DOUBLE DOWN AND LEFT */
   U_BoxDrawingsDoubleUpAndLeft,          /* 0xbc  - 0x255d:  BOX DRAWINGS DOUBLE UP AND LEFT */
   U_CentSign,                            /* 0xbd  - 0x00a2:  CENT SIGN */
   U_YenSign,                             /* 0xbe  - 0x00a5:  YEN SIGN */
   U_BoxDrawingsLightDownAndLeft,         /* 0xbf  - 0x2510:  BOX DRAWINGS LIGHT DOWN AND LEFT */
   U_BoxDrawingsLightUpAndRight,          /* 0xc0  - 0x2514:  BOX DRAWINGS LIGHT UP AND RIGHT */
   U_BoxDrawingsLightUpAndHorizontal,     /* 0xc1  - 0x2534:  BOX DRAWINGS LIGHT UP AND HORIZONTAL */
   U_BoxDrawingsLightDownAndHorizontal,   /* 0xc2  - 0x252c:  BOX DRAWINGS LIGHT DOWN AND HORIZONTAL */
   U_BoxDrawingsLightVerticalAndRight,    /* 0xc3  - 0x251c:  BOX DRAWINGS LIGHT VERTICAL AND RIGHT */
   U_BoxDrawingsLightHorizontal,          /* 0xc4  - 0x2500:  BOX DRAWINGS LIGHT HORIZONTAL */
                                          /* 0xc5  - 0x253c:  BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL */
   U_BoxDrawingsLightVerticalAndHorizontal,
   U_LatinSmallLetterAWithTilde,          /* 0xc6  - 0x00e3:  LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterAWithTilde,        /* 0xc7  - 0x00c3:  LATIN CAPITAL LETTER A WITH TILDE */
   U_BoxDrawingsDoubleUpAndRight,         /* 0xc8  - 0x255a:  BOX DRAWINGS DOUBLE UP AND RIGHT */
   U_BoxDrawingsDoubleDownAndRight,       /* 0xc9  - 0x2554:  BOX DRAWINGS DOUBLE DOWN AND RIGHT */
   U_BoxDrawingsDoubleUpAndHorizontal,    /* 0xca  - 0x2569:  BOX DRAWINGS DOUBLE UP AND HORIZONTAL */
   U_BoxDrawingsDoubleDownAndHorizontal,  /* 0xcb  - 0x2566:  BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL */
   U_BoxDrawingsDoubleVerticalAndRight,   /* 0xcc  - 0x2560:  BOX DRAWINGS DOUBLE VERTICAL AND RIGHT */
   U_BoxDrawingsDoubleHorizontal,         /* 0xcd  - 0x2550:  BOX DRAWINGS DOUBLE HORIZONTAL */
                                          /* 0xce  - 0x256c:  BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL */
   U_BoxDrawingsDoubleVerticalAndHorizontal,
   U_CurrencySign,                        /* 0xcf  - 0x00a4:  CURRENCY SIGN */
   U_LatinSmallLetterEth,                 /* 0xd0  - 0x00f0:  LATIN SMALL LETTER ETH */
   U_LatinCapitalLetterEth,               /* 0xd1  - 0x00d0:  LATIN CAPITAL LETTER ETH */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xd2  - 0x00ca:  LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xd3  - 0x00cb:  LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterEWithGrave,        /* 0xd4  - 0x00c8:  LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinSmallLetterDotlessI,            /* 0xd5  - 0x0131:  LATIN SMALL LETTER DOTLESS I */
   U_LatinCapitalLetterIWithAcute,        /* 0xd6  - 0x00cd:  LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xd7  - 0x00ce:  LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xd8  - 0x00cf:  LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_BoxDrawingsLightUpAndLeft,           /* 0xd9  - 0x2518:  BOX DRAWINGS LIGHT UP AND LEFT */
   U_BoxDrawingsLightDownAndRight,        /* 0xda  - 0x250c:  BOX DRAWINGS LIGHT DOWN AND RIGHT */
   U_FullBlock,                           /* 0xdb  - 0x2588:  FULL BLOCK */
   U_LowerHalfBlock,                      /* 0xdc  - 0x2584:  LOWER HALF BLOCK */
   U_BrokenVerticalBar,                   /* 0xdd  - 0x00a6:  BROKEN BAR */
   U_LatinCapitalLetterIWithGrave,        /* 0xde  - 0x00cc:  LATIN CAPITAL LETTER I WITH GRAVE */
   U_UpperHalfBlock,                      /* 0xdf  - 0x2580:  UPPER HALF BLOCK */
   U_LatinCapitalLetterOWithAcute,        /* 0xe0  - 0x00d3:  LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinSmallLetterSharpS,              /* 0xe1  - 0x00df:  LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xe2  - 0x00d4:  LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterOWithGrave,        /* 0xe3  - 0x00d2:  LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinSmallLetterOWithTilde,          /* 0xe4  - 0x00f5:  LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterOWithTilde,        /* 0xe5  - 0x00d5:  LATIN CAPITAL LETTER O WITH TILDE */
   U_MicroSign,                           /* 0xe6  - 0x00b5:  MICRO SIGN */
   U_LatinSmallLetterThorn,               /* 0xe7  - 0x00fe:  LATIN SMALL LETTER THORN */
   U_LatinCapitalLetterThorn,             /* 0xe8  - 0x00de:  LATIN CAPITAL LETTER THORN */
   U_LatinCapitalLetterUWithAcute,        /* 0xe9  - 0x00da:  LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xea  - 0x00db:  LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterUWithGrave,        /* 0xeb  - 0x00d9:  LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinSmallLetterYWithAcute,          /* 0xec  - 0x00fd:  LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterYWithAcute,        /* 0xed  - 0x00dd:  LATIN CAPITAL LETTER Y WITH ACUTE */
   U_Macron,                              /* 0xee  - 0x00af:  MACRON */
   U_AcuteAccent,                         /* 0xef  - 0x00b4:  ACUTE ACCENT */
   U_SoftHyphen,                          /* 0xf0  - 0x00ad:  SOFT HYPHEN */
   U_PlusMinusSign,                       /* 0xf1  - 0x00b1:  PLUS-MINUS SIGN */
   U_DoubleLowLine,                       /* 0xf2  - 0x2017:  DOUBLE LOW LINE */
   U_VulgarFractionThreeQuarters,         /* 0xf3  - 0x00be:  VULGAR FRACTION THREE QUARTERS */
   U_ParagraphSign,                       /* 0xf4  - 0x00b6:  PILCROW SIGN */
   U_SectionSign,                         /* 0xf5  - 0x00a7:  SECTION SIGN */
   U_DivisionSign,                        /* 0xf6  - 0x00f7:  DIVISION SIGN */
   U_Cedilla,                             /* 0xf7  - 0x00b8:  CEDILLA */
   U_DegreeSign,                          /* 0xf8  - 0x00b0:  DEGREE SIGN */
   U_Diaeresis,                           /* 0xf9  - 0x00a8:  DIAERESIS */
   U_MiddleDot,                           /* 0xfa  - 0x00b7:  MIDDLE DOT */
   U_SuperscriptOne,                      /* 0xfb  - 0x00b9:  SUPERSCRIPT ONE */
   U_SuperscriptThree,                    /* 0xfc  - 0x00b3:  SUPERSCRIPT THREE */
   U_SuperscriptTwo,                      /* 0xfd  - 0x00b2:  SUPERSCRIPT TWO */
   U_BlackSquare,                         /* 0xfe  - 0x25a0:  BLACK SQUARE */
   U_NB_SP                                /* 0xff  - 0x00a0:  NO-BREAK SPACE */
};





/******************************************************************************
*
*  CODE_850_lig[]:
*     list of ligatures:
*
*  CODE_850_lig[0] is the original ligature character
*  CODE_850_lig[1] + CODE_850_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_850_lig[][3] =        /* CODE_850 character ligatures */
{
   {0x00fc, U_LatinSmallLetterU,   U_LatinSmallLetterE},      /* 0x81  - 0x00fc:  LATIN SMALL LETTER U WITH DIAERESIS */
   {0x00e4, U_LatinSmallLetterA,   U_LatinSmallLetterE},      /* 0x84  - 0x00e4:  LATIN SMALL LETTER A WITH DIAERESIS */
   {0x00e5, U_LatinSmallLetterA,   U_LatinSmallLetterO},      /* 0x86  - 0x00e5:  LATIN SMALL LETTER A WITH RING ABOVE */
   {0x00eb, U_LatinSmallLetterE,   U_LatinSmallLetterE},      /* 0x89  - 0x00eb:  LATIN SMALL LETTER E WITH DIAERESIS */
   {0x00ef, U_LatinSmallLetterI,   U_LatinSmallLetterE},      /* 0x8b  - 0x00ef:  LATIN SMALL LETTER I WITH DIAERESIS */
   {0x00c4, U_LatinCapitalLetterA, U_LatinSmallLetterE},      /* 0x8e  - 0x00c4:  LATIN CAPITAL LETTER A WITH DIAERESIS */
   {0x00c5, U_LatinCapitalLetterA, U_LatinSmallLetterO},      /* 0x8f  - 0x00c5:  LATIN CAPITAL LETTER A WITH RING ABOVE */
   {0x00e6, U_LatinSmallLetterA,   U_LatinSmallLetterE},      /* 0x91  - 0x00e6:  LATIN SMALL LIGATURE AE */
   {0x00c6, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x92  - 0x00c6:  LATIN CAPITAL LIGATURE AE */
   {0x00f6, U_LatinSmallLetterO,   U_LatinSmallLetterE},      /* 0x94  - 0x00f6:  LATIN SMALL LETTER O WITH DIAERESIS */
   {0x00ff, U_LatinSmallLetterY,   U_LatinSmallLetterE},      /* 0x98  - 0x00ff:  LATIN SMALL LETTER Y WITH DIAERESIS */
   {0x00d6, U_LatinCapitalLetterO, U_LatinSmallLetterE},      /* 0x99  - 0x00d6:  LATIN CAPITAL LETTER O WITH DIAERESIS */
   {0x00dc, U_LatinCapitalLetterU, U_LatinSmallLetterE},      /* 0x9a  - 0x00dc:  LATIN CAPITAL LETTER U WITH DIAERESIS */
   {0x00f8, U_LatinSmallLetterO,   U_LatinSmallLetterE},      /* 0x9b  - 0x00f8:  LATIN SMALL LETTER O WITH STROKE */
   {0x00d8, U_LatinCapitalLetterO, U_LatinSmallLetterE},      /* 0x9d  - 0x00d8:  LATIN CAPITAL LETTER O WITH STROKE */
   {0x00cb, U_LatinCapitalLetterE, U_LatinSmallLetterE},      /* 0xd3  - 0x00cb:  LATIN CAPITAL LETTER E WITH DIAERESIS */
   {0x00cf, U_LatinCapitalLetterI, U_LatinSmallLetterE},      /* 0xd8  - 0x00cf:  LATIN CAPITAL LETTER I WITH DIAERESIS */
   {0x00df, U_LatinSmallLetterS,   U_LatinSmallLetterS},      /* 0xe1  - 0x00df:  LATIN SMALL LETTER SHARP S */
   {0x0000, U_NIL                , U_NIL}                     /* list terminator */
};





/******************************************************************************
*
*  CODE_850 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_850[] =          /* CODE_850 */
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

   U_LatinCapitalLetterC,                 /* 0x80  - 0x00c7:  LATIN CAPITAL LETTER C WITH CEDILLA */
   U_LatinSmallLetterU,                   /* 0x81  - 0x00fc:  LATIN SMALL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterE,                   /* 0x82  - 0x00e9:  LATIN SMALL LETTER E WITH ACUTE */
   U_LatinSmallLetterA,                   /* 0x83  - 0x00e2:  LATIN SMALL LETTER A WITH CIRCUMFLEX */
   U_LatinSmallLetterA,                   /* 0x84  - 0x00e4:  LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterA,                   /* 0x85  - 0x00e0:  LATIN SMALL LETTER A WITH GRAVE */
   U_LatinSmallLetterA,                   /* 0x86  - 0x00e5:  LATIN SMALL LETTER A WITH RING ABOVE */
   U_LatinSmallLetterC,                   /* 0x87  - 0x00e7:  LATIN SMALL LETTER C WITH CEDILLA */
   U_LatinSmallLetterE,                   /* 0x88  - 0x00ea:  LATIN SMALL LETTER E WITH CIRCUMFLEX */
   U_LatinSmallLetterE,                   /* 0x89  - 0x00eb:  LATIN SMALL LETTER E WITH DIAERESIS */
   U_LatinSmallLetterE,                   /* 0x8a  - 0x00e8:  LATIN SMALL LETTER E WITH GRAVE */
   U_LatinSmallLetterI,                   /* 0x8b  - 0x00ef:  LATIN SMALL LETTER I WITH DIAERESIS */
   U_LatinSmallLetterI,                   /* 0x8c  - 0x00ee:  LATIN SMALL LETTER I WITH CIRCUMFLEX */
   U_LatinSmallLetterI,                   /* 0x8d  - 0x00ec:  LATIN SMALL LETTER I WITH GRAVE */
   U_LatinCapitalLetterA,                 /* 0x8e  - 0x00c4:  LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0x8f  - 0x00c5:  LATIN CAPITAL LETTER A WITH RING ABOVE */
   U_LatinCapitalLetterE,                 /* 0x90  - 0x00c9:  LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinSmallLigatureAE,                /* 0x91  - 0x00e6:  LATIN SMALL LIGATURE AE */
   U_LatinCapitalLigatureAE,              /* 0x92  - 0x00c6:  LATIN CAPITAL LIGATURE AE */
   U_LatinSmallLetterO,                   /* 0x93  - 0x00f4:  LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterO,                   /* 0x94  - 0x00f6:  LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterO,                   /* 0x95  - 0x00f2:  LATIN SMALL LETTER O WITH GRAVE */
   U_LatinSmallLetterU,                   /* 0x96  - 0x00fb:  LATIN SMALL LETTER U WITH CIRCUMFLEX */
   U_LatinSmallLetterU,                   /* 0x97  - 0x00f9:  LATIN SMALL LETTER U WITH GRAVE */
   U_LatinSmallLetterY,                   /* 0x98  - 0x00ff:  LATIN SMALL LETTER Y WITH DIAERESIS */
   U_LatinCapitalLetterO,                 /* 0x99  - 0x00d6:  LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0x9a  - 0x00dc:  LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterOSlash,              /* 0x9b  - 0x00f8:  LATIN SMALL LETTER O WITH STROKE */
   U_PoundSign,                           /* 0x9c  - 0x00a3:  POUND SIGN */
   U_LatinCapitalLetterOSlash,            /* 0x9d  - 0x00d8:  LATIN CAPITAL LETTER O WITH STROKE */
   U_MultiplicationSign,                  /* 0x9e  - 0x00d7:  MULTIPLICATION SIGN */
   U_LatinSmallLetterF,                   /* 0x9f  - 0x0192:  LATIN SMALL LETTER F WITH HOOK */
   U_LatinSmallLetterA,                   /* 0xa0  - 0x00e1:  LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterI,                   /* 0xa1  - 0x00ed:  LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterO,                   /* 0xa2  - 0x00f3:  LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterU,                   /* 0xa3  - 0x00fa:  LATIN SMALL LETTER U WITH ACUTE */
   U_LatinSmallLetterN,                   /* 0xa4  - 0x00f1:  LATIN SMALL LETTER N WITH TILDE */
   U_LatinCapitalLetterN,                 /* 0xa5  - 0x00d1:  LATIN CAPITAL LETTER N WITH TILDE */
   U_FeminineOrdinalIndicator,            /* 0xa6  - 0x00aa:  FEMININE ORDINAL INDICATOR */
   U_MasculineOrdinalIndicator,           /* 0xa7  - 0x00ba:  MASCULINE ORDINAL INDICATOR */
   U_InvertedQuestionMark,                /* 0xa8  - 0x00bf:  INVERTED QUESTION MARK */
   U_RegisteredSign,                      /* 0xa9  - 0x00ae:  REGISTERED SIGN */
   U_NotSign,                             /* 0xaa  - 0x00ac:  NOT SIGN */
   U_VulgarFractionOneHalf,               /* 0xab  - 0x00bd:  VULGAR FRACTION ONE HALF */
   U_VulgarFractionOneQuarter,            /* 0xac  - 0x00bc:  VULGAR FRACTION ONE QUARTER */
   U_InvertedExclamationMark,             /* 0xad  - 0x00a1:  INVERTED EXCLAMATION MARK */
   U_LeftPointingGuillemet,               /* 0xae  - 0x00ab:  LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_RightPointingGuillemet,              /* 0xaf  - 0x00bb:  RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_LightShade,                          /* 0xb0  - 0x2591:  LIGHT SHADE */
   U_MediumShade,                         /* 0xb1  - 0x2592:  MEDIUM SHADE */
   U_DarkShade,                           /* 0xb2  - 0x2593:  DARK SHADE */
   U_BoxDrawingsLightVertical,            /* 0xb3  - 0x2502:  BOX DRAWINGS LIGHT VERTICAL */
   U_BoxDrawingsLightVerticalAndLeft,     /* 0xb4  - 0x2524:  BOX DRAWINGS LIGHT VERTICAL AND LEFT */
   U_LatinCapitalLetterA,                 /* 0xb5  - 0x00c1:  LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xb6  - 0x00c2:  LATIN CAPITAL LETTER A WITH CIRCUMFLEX */
   U_LatinCapitalLetterA,                 /* 0xb7  - 0x00c0:  LATIN CAPITAL LETTER A WITH GRAVE */
   U_CopyrightSign,                       /* 0xb8  - 0x00a9:  COPYRIGHT SIGN */
   U_BoxDrawingsDoubleVerticalAndLeft,    /* 0xb9  - 0x2563:  BOX DRAWINGS DOUBLE VERTICAL AND LEFT */
   U_BoxDrawingsDoubleVertical,           /* 0xba  - 0x2551:  BOX DRAWINGS DOUBLE VERTICAL */
   U_BoxDrawingsDoubleDownAndLeft,        /* 0xbb  - 0x2557:  BOX DRAWINGS DOUBLE DOWN AND LEFT */
   U_BoxDrawingsDoubleUpAndLeft,          /* 0xbc  - 0x255d:  BOX DRAWINGS DOUBLE UP AND LEFT */
   U_CentSign,                            /* 0xbd  - 0x00a2:  CENT SIGN */
   U_YenSign,                             /* 0xbe  - 0x00a5:  YEN SIGN */
   U_BoxDrawingsLightDownAndLeft,         /* 0xbf  - 0x2510:  BOX DRAWINGS LIGHT DOWN AND LEFT */
   U_BoxDrawingsLightUpAndRight,          /* 0xc0  - 0x2514:  BOX DRAWINGS LIGHT UP AND RIGHT */
   U_BoxDrawingsLightUpAndHorizontal,     /* 0xc1  - 0x2534:  BOX DRAWINGS LIGHT UP AND HORIZONTAL */
   U_BoxDrawingsLightDownAndHorizontal,   /* 0xc2  - 0x252c:  BOX DRAWINGS LIGHT DOWN AND HORIZONTAL */
   U_BoxDrawingsLightVerticalAndRight,    /* 0xc3  - 0x251c:  BOX DRAWINGS LIGHT VERTICAL AND RIGHT */
   U_BoxDrawingsLightHorizontal,          /* 0xc4  - 0x2500:  BOX DRAWINGS LIGHT HORIZONTAL */
                                          /* 0xc5  - 0x253c:  BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL */
   U_BoxDrawingsLightVerticalAndHorizontal,
   U_LatinSmallLetterA,                   /* 0xc6  - 0x00e3:  LATIN SMALL LETTER A WITH TILDE */
   U_LatinCapitalLetterA,                 /* 0xc7  - 0x00c3:  LATIN CAPITAL LETTER A WITH TILDE */
   U_BoxDrawingsDoubleUpAndRight,         /* 0xc8  - 0x255a:  BOX DRAWINGS DOUBLE UP AND RIGHT */
   U_BoxDrawingsDoubleDownAndRight,       /* 0xc9  - 0x2554:  BOX DRAWINGS DOUBLE DOWN AND RIGHT */
   U_BoxDrawingsDoubleUpAndHorizontal,    /* 0xca  - 0x2569:  BOX DRAWINGS DOUBLE UP AND HORIZONTAL */
   U_BoxDrawingsDoubleDownAndHorizontal,  /* 0xcb  - 0x2566:  BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL */
   U_BoxDrawingsDoubleVerticalAndRight,   /* 0xcc  - 0x2560:  BOX DRAWINGS DOUBLE VERTICAL AND RIGHT */
   U_BoxDrawingsDoubleHorizontal,         /* 0xcd  - 0x2550:  BOX DRAWINGS DOUBLE HORIZONTAL */
                                          /* 0xce  - 0x256c:  BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL */
   U_BoxDrawingsDoubleVerticalAndHorizontal,
   U_CurrencySign,                        /* 0xcf  - 0x00a4:  CURRENCY SIGN */
   U_LatinSmallLetterEth,                 /* 0xd0  - 0x00f0:  LATIN SMALL LETTER ETH */
   U_LatinCapitalLetterEth,               /* 0xd1  - 0x00d0:  LATIN CAPITAL LETTER ETH */
   U_LatinCapitalLetterE,                 /* 0xd2  - 0x00ca:  LATIN CAPITAL LETTER E WITH CIRCUMFLEX */
   U_LatinCapitalLetterE,                 /* 0xd3  - 0x00cb:  LATIN CAPITAL LETTER E WITH DIAERESIS */
   U_LatinCapitalLetterE,                 /* 0xd4  - 0x00c8:  LATIN CAPITAL LETTER E WITH GRAVE */
   U_LatinSmallLetterI,                   /* 0xd5  - 0x0131:  LATIN SMALL LETTER DOTLESS I */
   U_LatinCapitalLetterI,                 /* 0xd6  - 0x00cd:  LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterI,                 /* 0xd7  - 0x00ce:  LATIN CAPITAL LETTER I WITH CIRCUMFLEX */
   U_LatinCapitalLetterI,                 /* 0xd8  - 0x00cf:  LATIN CAPITAL LETTER I WITH DIAERESIS */
   U_BoxDrawingsLightUpAndLeft,           /* 0xd9  - 0x2518:  BOX DRAWINGS LIGHT UP AND LEFT */
   U_BoxDrawingsLightDownAndRight,        /* 0xda  - 0x250c:  BOX DRAWINGS LIGHT DOWN AND RIGHT */
   U_FullBlock,                           /* 0xdb  - 0x2588:  FULL BLOCK */
   U_LowerHalfBlock,                      /* 0xdc  - 0x2584:  LOWER HALF BLOCK */
   U_BrokenVerticalBar,                   /* 0xdd  - 0x00a6:  BROKEN BAR */
   U_LatinCapitalLetterI,                 /* 0xde  - 0x00cc:  LATIN CAPITAL LETTER I WITH GRAVE */
   U_UpperHalfBlock,                      /* 0xdf  - 0x2580:  UPPER HALF BLOCK */
   U_LatinCapitalLetterO,                 /* 0xe0  - 0x00d3:  LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinSmallLetterS,                   /* 0xe1  - 0x00df:  LATIN SMALL LETTER SHARP S */
   U_LatinCapitalLetterO,                 /* 0xe2  - 0x00d4:  LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0xe3  - 0x00d2:  LATIN CAPITAL LETTER O WITH GRAVE */
   U_LatinSmallLetterO,                   /* 0xe4  - 0x00f5:  LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xe5  - 0x00d5:  LATIN CAPITAL LETTER O WITH TILDE */
   U_MicroSign,                           /* 0xe6  - 0x00b5:  MICRO SIGN */
   U_LatinSmallLetterThorn,               /* 0xe7  - 0x00fe:  LATIN SMALL LETTER THORN */
   U_LatinCapitalLetterThorn,             /* 0xe8  - 0x00de:  LATIN CAPITAL LETTER THORN */
   U_LatinCapitalLetterU,                 /* 0xe9  - 0x00da:  LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xea  - 0x00db:  LATIN CAPITAL LETTER U WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xeb  - 0x00d9:  LATIN CAPITAL LETTER U WITH GRAVE */
   U_LatinSmallLetterY,                   /* 0xec  - 0x00fd:  LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterY,                 /* 0xed  - 0x00dd:  LATIN CAPITAL LETTER Y WITH ACUTE */
   U_Macron,                              /* 0xee  - 0x00af:  MACRON */
   U_AcuteAccent,                         /* 0xef  - 0x00b4:  ACUTE ACCENT */
   U_SoftHyphen,                          /* 0xf0  - 0x00ad:  SOFT HYPHEN */
   U_PlusMinusSign,                       /* 0xf1  - 0x00b1:  PLUS-MINUS SIGN */
   U_DoubleLowLine,                       /* 0xf2  - 0x2017:  DOUBLE LOW LINE */
   U_VulgarFractionThreeQuarters,         /* 0xf3  - 0x00be:  VULGAR FRACTION THREE QUARTERS */
   U_ParagraphSign,                       /* 0xf4  - 0x00b6:  PILCROW SIGN */
   U_SectionSign,                         /* 0xf5  - 0x00a7:  SECTION SIGN */
   U_DivisionSign,                        /* 0xf6  - 0x00f7:  DIVISION SIGN */
   U_Cedilla,                             /* 0xf7  - 0x00b8:  CEDILLA */
   U_DegreeSign,                          /* 0xf8  - 0x00b0:  DEGREE SIGN */
   U_Diaeresis,                           /* 0xf9  - 0x00a8:  DIAERESIS */
   U_MiddleDot,                           /* 0xfa  - 0x00b7:  MIDDLE DOT */
   U_SuperscriptOne,                      /* 0xfb  - 0x00b9:  SUPERSCRIPT ONE */
   U_SuperscriptThree,                    /* 0xfc  - 0x00b3:  SUPERSCRIPT THREE */
   U_SuperscriptTwo,                      /* 0xfd  - 0x00b2:  SUPERSCRIPT TWO */
   U_BlackSquare,                         /* 0xfe  - 0x25a0:  BLACK SQUARE */
   U_NB_SP                                /* 0xff  - 0x00a0:  NO-BREAK SPACE */
};
