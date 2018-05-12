/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_tos.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepage for TOS encoding
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
*    fd  Feb 16: - table adjusted, based on <http://www.kostis.net/charsets/atarist.htm>
*                - ligatures and sorting tables moved from encoding.h
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
*  u_CODE_TOS[]:
*     Unicode named codepage for TOS encoding
*
******************************************|************************************/

static _UWORD const u_CODE_TOS[] =             /* CODE_TOS */
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

   U_LatinCapitalLetterCWithCedilla,      /* 0x80  U_LatinCapitalLetterCWithCedilla */
   U_LatinSmallLetterUWithDiaeresis,      /* 0x81  U_LatinSmallLetterUWithDiaeresis */
   U_LatinSmallLetterEWithAcute,          /* 0x82  U_LatinSmallLetterEWithAcute */
   U_LatinSmallLetterAWithCircumflex,     /* 0x83  U_LatinSmallLetterAWithCircumflex */
   U_LatinSmallLetterAWithDiaeresis,      /* 0x84  U_LatinSmallLetterAWithDiaeresis */
   U_LatinSmallLetterAWithGrave,          /* 0x85  U_LatinSmallLetterAWithGrave */
   U_LatinSmallLetterAWithRingAbove,      /* 0x86  U_LatinSmallLetterAWithRingAbove */
   U_LatinSmallLetterCWithCedilla,        /* 0x87  U_LatinSmallLetterCWithCedilla */
   U_LatinSmallLetterEWithCircumflex,     /* 0x88  U_LatinSmallLetterEWithCircumflex */
   U_LatinSmallLetterEWithDiaeresis,      /* 0x89  U_LatinSmallLetterEWithDiaeresis */
   U_LatinSmallLetterEWithGrave,          /* 0x8a  U_LatinSmallLetterEWithGrave */
   U_LatinSmallLetterIWithDiaeresis,      /* 0x8b  U_LatinSmallLetterIWithDiaeresis */
   U_LatinSmallLetterIWithCircumflex,     /* 0x8c  U_LatinSmallLetterIWithCircumflex */
   U_LatinSmallLetterIWithGrave,          /* 0x8d  U_LatinSmallLetterIWithGrave */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0x8e  U_LatinCapitalLetterAWithDiaeresis */
   U_LatinCapitalLetterAWithRingAbove,    /* 0x8f  U_LatinCapitalLetterAWithRingAbove */
                                          
   U_LatinCapitalLetterEWithAcute,        /* 0x90  U_LatinCapitalLetterEWithAcute */
   U_LatinSmallLigatureAE,                /* 0x91  U_LatinSmallLigatureAE */
   U_LatinCapitalLigatureAE,              /* 0x92  U_LatinCapitalLigatureAE */
   U_LatinSmallLetterOWithCircumflex,     /* 0x93  U_LatinSmallLetterOWithCircumflex */
   U_LatinSmallLetterOWithDiaeresis,      /* 0x94  U_LatinSmallLetterOWithDiaeresis */
   U_LatinSmallLetterOWithGrave,          /* 0x95  U_LatinSmallLetterOWithGrave */
   U_LatinSmallLetterUWithCircumflex,     /* 0x96  U_LatinSmallLetterUWithCircumflex */
   U_LatinSmallLetterUWithGrave,          /* 0x97  U_LatinSmallLetterUWithGrave */
   U_LatinSmallLetterYWithDiaeresis,      /* 0x98  U_LatinSmallLetterYWithDiaeresis */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0x99  U_LatinCapitalLetterOWithDiaeresis */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0x9a  U_LatinCapitalLetterUWithDiaeresis */
   U_CentSign,                            /* 0x9b  U_CentSign */
   U_PoundSign,                           /* 0x9c  U_PoundSign */
   U_YenSign,                             /* 0x9d  U_YenSign */
   U_LatinSmallLetterSharpS,              /* 0x9e  U_LatinSmallLetterSharpS */
   U_LatinSmallLetterScriptF,             /* 0x9f  U_LatinSmallLetterScriptF */
                                          
   U_LatinSmallLetterAWithAcute,          /* 0xa0  U_LatinSmallLetterAWithAcute */
   U_LatinSmallLetterIWithAcute,          /* 0xa1  U_LatinSmallLetterIWithAcute */
   U_LatinSmallLetterOWithAcute,          /* 0xa2  U_LatinSmallLetterOWithAcute */
   U_LatinSmallLetterUWithAcute,          /* 0xa3  U_LatinSmallLetterUWithAcute */
   U_LatinSmallLetterNWithTilde,          /* 0xa4  U_LatinSmallLetterNWithTilde */
   U_LatinCapitalLetterNWithTilde,        /* 0xa5  U_LatinCapitalLetterNWithTilde */
   U_FeminineOrdinalIndicator,            /* 0xa6  U_FeminineOrdinalIndicator */
   U_MasculineOrdinalIndicator,           /* 0xa7  U_MasculineOrdinalIndicator */
   U_InvertedQuestionMark,                /* 0xa8  U_InvertedQuestionMark */
   U_ReversedNotSign,                     /* 0xa9  U_ReversedNotSign */
   U_NotSign,                             /* 0xaa  U_NotSign */
   U_VulgarFractionOneHalf,               /* 0xab  U_VulgarFractionOneHalf */
   U_VulgarFractionOneQuarter,            /* 0xac  U_VulgarFractionOneQuarter */
   U_InvertedExclamationMark,             /* 0xad  U_InvertedExclamationMark */
   U_LeftPointingGuillemet,               /* 0xae  U_LeftPointingGuillemet */
   U_RightPointingGuillemet,              /* 0xaf  U_RightPointingGuillemet */
                                          
   U_LatinSmallLetterAWithTilde,          /* 0xb0  U_LatinSmallLetterAWithTilde */
   U_LatinSmallLetterOWithTilde,          /* 0xb1  U_LatinSmallLetterOWithTilde */
   U_LatinCapitalLetterOSlash,            /* 0xb2  U_LatinCapitalLetterOSlash */
   U_LatinSmallLetterOSlash,              /* 0xb3  U_LatinSmallLetterOSlash */
   U_LatinSmallLigatureOE,                /* 0xb4  U_LatinSmallLigatureOE */
   U_LatinCapitalLigatureOE,              /* 0xb5  U_LatinCapitalLigatureOE */
   U_LatinCapitalLetterAWithGrave,        /* 0xb6  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterAWithTilde,        /* 0xb7  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterOWithTilde,        /* 0xb8  U_LatinCapitalLetterOWithTilde */
   U_Diaeresis,                           /* 0xb9  U_Diaeresis */
   U_AcuteAccent,                         /* 0xba  U_AcuteAccent */
   U_Dagger,                              /* 0xbb  U_Dagger */
   U_ParagraphSign,                       /* 0xbc  U_ParagraphSign */
   U_CopyrightSign,                       /* 0xbd  U_CopyrightSign */
   U_RegisteredSign,                      /* 0xbe  U_RegisteredSign */
   U_TradeMarkSign,                       /* 0xbf  U_TradeMarkSign */
                                          
   U_LatinSmallLigatureIJ,                /* 0xc0  U_LatinSmallLigatureIJ */
   U_LatinCapitalLigatureIJ,              /* 0xc1  U_LatinCapitalLigatureIJ */
   U_HebrewLetterAlef,                    /* 0xc2  U_HebrewLetterAlef */
   U_HebrewLetterBet,                     /* 0xc3  U_HebrewLetterBet */
   U_HebrewLetterGimel,                   /* 0xc4  U_HebrewLetterGimel */
   U_HebrewLetterDalet,                   /* 0xc5  U_HebrewLetterDalet */
   U_HebrewLetterHe,                      /* 0xc6  U_HebrewLetterHe */
   U_HebrewLetterVav,                     /* 0xc7  U_HebrewLetterVav */
   U_HebrewLetterZayin,                   /* 0xc8  U_HebrewLetterZayin */
   U_HebrewLetterHet,                     /* 0xc9  U_HebrewLetterHet */
   U_HebrewLetterTet,                     /* 0xca  U_HebrewLetterTet */
   U_HebrewLetterYod,                     /* 0xcb  U_HebrewLetterYod */
   U_HebrewLetterKaf,                     /* 0xcc  U_HebrewLetterKaf */
   U_HebrewLetterLamed,                   /* 0xcd  U_HebrewLetterLamed */
   U_HebrewLetterMem,                     /* 0xce  U_HebrewLetterMem */
   U_HebrewLetterNun,                     /* 0xcf  U_HebrewLetterNun */
                                          
   U_HebrewLetterSamekh,                  /* 0xd0  U_HebrewLetterSamekh */
   U_HebrewLetterAyin,                    /* 0xd1  U_HebrewLetterAyin */
   U_HebrewLetterPe,                      /* 0xd2  U_HebrewLetterPe */
   U_HebrewLetterTsadi,                   /* 0xd3  U_HebrewLetterTsadi */
   U_HebrewLetterQof,                     /* 0xd4  U_HebrewLetterQof */
   U_HebrewLetterResh,                    /* 0xd5  U_HebrewLetterResh */
   U_HebrewLetterShin,                    /* 0xd6  U_HebrewLetterShin */
   U_HebrewLetterTav,                     /* 0xd7  U_HebrewLetterTav */
   U_HebrewLetterFinalNun,                /* 0xd8  U_HebrewLetterFinalNun */
   U_HebrewLetterFinalKaf,                /* 0xd9  U_HebrewLetterFinalKaf */
   U_HebrewLetterFinalMem,                /* 0xda  U_HebrewLetterFinalMem */
   U_HebrewLetterFinalPe,                 /* 0xdb  U_HebrewLetterFinalPe */
   U_HebrewLetterFinalTsadi,              /* 0xdc  U_HebrewLetterFinalTsadi */
   U_SectionSign,                         /* 0xdd  U_SectionSign */
   U_LogicalAnd,                          /* 0xde  LOGICAL AND */
   U_Infinity,                            /* 0xdf  U_Infinity */
                                          
   U_GreekSmallLetterAlpha,               /* 0xe0  U_GreekSmallLetterAlpha */
   U_GreekSmallLetterBeta,                /* 0xe1  U_GreekSmallLetterBeta */
   U_GreekCapitalLetterGamma,             /* 0xe2  U_GreekCapitalLetterGamma */
   U_GreekSmallLetterPi,                  /* 0xe3  U_GreekSmallLetterPi */
   U_GreekCapitalLetterSigma,             /* 0xe4  U_GreekCapitalLetterSigma */
   U_GreekSmallLetterSigma,               /* 0xe5  U_GreekSmallLetterSigma */
   U_MicroSign,                           /* 0xe6  U_MicroSign */
   U_GreekSmallLetterTau,                 /* 0xe7  U_GreekSmallLetterTau */
   U_GreekCapitalLetterPhi,               /* 0xe8  GREEK CAPITAL LETTER PHI */
   U_GreekCapitalLetterTheta,             /* 0xe9  GREEK CAPITAL LETTER THETA */
   U_GreekCapitalLetterOmega,             /* 0xea  U_GreekCapitalLetterOmega */
   U_GreekSmallLetterDelta,               /* 0xeb  U_GreekSmallLetterDelta */
   U_ContourIntegral,                     /* 0xec  U_ContourIntegral */
   U_GreekSmallLetterPhi,                 /* 0xed  GREEK SMALL LETTER PHI */
   U_ElementOf,                           /* 0xee  U_ElementOf */
   U_Intersection,                        /* 0xef  U_Intersection */
                                          
   U_IdenticalTo,                         /* 0xf0  U_IdenticalTo */
   U_PlusMinusSign,                       /* 0xf1  U_PlusMinusSign */
   U_GreaterThanOrEqualTo,                /* 0xf2  U_GreaterThanOrEqualTo */
   U_LessThanOrEqualTo,                   /* 0xf3  U_LessThanOrEqualTo */
   U_TopHalfIntegral,                     /* 0xf4  U_Integral (upper half) */
   U_BottomHalfIntegral,                  /* 0xf5  U_Integral (lower half) */
   U_DivisionSign,                        /* 0xf6  U_DivisionSign */
   U_AlmostEqualTo,                       /* 0xf7  U_AlmostEqualTo */
   U_DegreeSign,                          /* 0xf8  U_DegreeSign */
   U_Bullet,                              /* 0xf9  U_Bullet */ /* not quite right; should be 0x2219 = U_BulletOperator */
   U_MiddleDot,                           /* 0xfa  U_MiddleDot */
   U_SquareRoot,                          /* 0xfb  U_SquareRoot */
   U_SuperscriptLatinSmallLetterN,        /* 0xfc  U_SuperscriptLatinSmallLetterN */
   U_SuperscriptTwo,                      /* 0xfd  U_SuperscriptTwo */
   U_SuperscriptThree,                    /* 0xfe  U_SuperscriptThree */
   U_Macron                               /* 0xff  U_Macron */
};





/******************************************************************************
*
*  CODE_TOS_lig[]:
*     list of ligatures:
*
*  CODE_TOS_lig[0] is the original ligature character
*  CODE_TOS_lig[1] + CODE_TOS_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_TOS_lig[][3] =        /* CODE_TOS character ligatures */
{
   {0x0081, U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x0081  U_LatinSmallLetterUWithDiaeresis */
   {0x0084, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x0084  U_LatinSmallLetterAWithDiaeresis */
   {0x0089, U_LatinCapitalLetterE, U_LatinCapitalLetterE},    /* 0x0089  U_LatinSmallLetterEWithDiaeresis */
   {0x008e, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x008e  U_LatinCapitalLetterAWithDiaeresis */
   {0x0091, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x0091  U_LatinSmallLigatureAE */
   {0x0092, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x0092  U_LatinCapitalLigatureAE */
   {0x0094, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x0094  U_LatinSmallLetterOWithDiaeresis */
   {0x0098, U_LatinCapitalLetterY, U_LatinCapitalLetterE},    /* 0x0098  U_LatinSmallLetterYWithDiaeresis */
   {0x0099, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x0099  U_LatinCapitalLetterOWithDiaeresis */
   {0x009a, U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x009a  U_LatinCapitalLetterUWithDiaeresis */
   {0x009e, U_LatinCapitalLetterS, U_LatinCapitalLetterS},    /* 0x009e  U_LatinSmallLetterSharpS */
   {0x00b2, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00b2  U_LatinCapitalLetterOSlash */
   {0x00b3, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00b3  U_LatinSmallLetterOSlash */
   {0x00b4, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00b4  U_LatinSmallLigatureOE */
   {0x00b5, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00b5  U_LatinCapitalLigatureOE */
   {0x00c0, U_LatinCapitalLetterI, U_LatinCapitalLetterJ},    /* 0x00c0  U_LatinSmallLigatureIJ */
   {0x00c1, U_LatinCapitalLetterI, U_LatinCapitalLetterJ},    /* 0x00c1  U_LatinCapitalLigatureIJ */
   {0x0000, U_NIL                , U_NIL}                     /* list terminator */
};





/******************************************************************************
*
*  CODE_TOS sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_TOS[] =          /* CODE_TOS */
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

   U_LatinCapitalLetterC,                 /* 0x80  U_LatinCapitalLetterCWithCedilla */
   U_LatinCapitalLetterU,                 /* 0x81  U_LatinSmallLetterUWithDiaeresis */
   U_LatinCapitalLetterE,                 /* 0x82  U_LatinSmallLetterEWithAcute */
   U_LatinCapitalLetterA,                 /* 0x83  U_LatinSmallLetterAWithCircumflex */
   U_LatinCapitalLetterA,                 /* 0x84  U_LatinSmallLetterAWithDiaeresis */
   U_LatinCapitalLetterA,                 /* 0x85  U_LatinSmallLetterAWithGrave */
   U_LatinCapitalLetterA,                 /* 0x86  U_LatinSmallLetterAWithRingAbove */
   U_LatinCapitalLetterC,                 /* 0x87  U_LatinSmallLetterCWithCedilla */
   U_LatinCapitalLetterE,                 /* 0x88  U_LatinSmallLetterEWithCircumflex */
   U_LatinCapitalLetterE,                 /* 0x89  U_LatinSmallLetterEWithDiaeresis */
   U_LatinCapitalLetterE,                 /* 0x8a  U_LatinSmallLetterEWithGrave */
   U_LatinCapitalLetterI,                 /* 0x8b  U_LatinSmallLetterIWithDiaeresis */
   U_LatinCapitalLetterI,                 /* 0x8c  U_LatinSmallLetterIWithCircumflex */
   U_LatinCapitalLetterI,                 /* 0x8d  U_LatinSmallLetterIWithGrave */
   U_LatinCapitalLetterA,                 /* 0x8e  U_LatinCapitalLetterAWithDiaeresis */
   U_LatinCapitalLetterA,                 /* 0x8f  U_LatinCapitalLetterAWithRingAbove */
                                          
   U_LatinCapitalLetterE,                 /* 0x90  U_LatinCapitalLetterEWithAcute */
   U_LatinCapitalLetterA,                 /* 0x91  U_LatinSmallLigatureAE */
   U_LatinCapitalLetterA,                 /* 0x92  U_LatinCapitalLigatureAE */
   U_LatinCapitalLetterO,                 /* 0x93  U_LatinSmallLetterOWithCircumflex */
   U_LatinCapitalLetterO,                 /* 0x94  U_LatinSmallLetterOWithDiaeresis */
   U_LatinCapitalLetterO,                 /* 0x95  U_LatinSmallLetterOWithGrave */
   U_LatinCapitalLetterU,                 /* 0x96  U_LatinSmallLetterUWithCircumflex */
   U_LatinCapitalLetterU,                 /* 0x97  U_LatinSmallLetterUWithGrave */
   U_LatinCapitalLetterY,                 /* 0x98  U_LatinSmallLetterYWithDiaeresis */
   U_LatinCapitalLetterO,                 /* 0x99  U_LatinCapitalLetterOWithDiaeresis */
   U_LatinCapitalLetterU,                 /* 0x9a  U_LatinCapitalLetterUWithDiaeresis */
   0x009b,                                /* 0x9b  U_CentSign */
   0x009c,                                /* 0x9c  U_PoundSign */
   0x009d,                                /* 0x9d  U_YenSign */
   U_LatinCapitalLetterS,                 /* 0x9e  U_LatinSmallLetterSharpS */
   U_LatinCapitalLetterF,                 /* 0x9f  U_LatinSmallLetterScriptF */
                                          
   U_LatinCapitalLetterA,                 /* 0xa0  U_LatinSmallLetterAWithAcute */
   U_LatinCapitalLetterI,                 /* 0xa1  U_LatinSmallLetterIWithAcute */
   U_LatinCapitalLetterO,                 /* 0xa2  U_LatinSmallLetterOWithAcute */
   U_LatinCapitalLetterU,                 /* 0xa3  U_LatinSmallLetterUWithAcute */
   U_LatinCapitalLetterN,                 /* 0xa4  U_LatinSmallLetterNWithTilde */
   U_LatinCapitalLetterN,                 /* 0xa5  U_LatinCapitalLetterNWithTilde */
   0x00a6,                                /* 0xa6  U_FeminineOrdinalIndicator */
   0x00a7,                                /* 0xa7  U_MasculineOrdinalIndicator */
   U_QuestionMark,                        /* 0xa8  U_InvertedQuestionMark */
   0x00a9,                                /* 0xa9  U_ReversedNotSign */
   0x00aa,                                /* 0xaa  U_NotSign */
   0x00ab,                                /* 0xab  U_VulgarFractionOneHalf */
   0x00ac,                                /* 0xac  U_VulgarFractionOneQuarter */
   U_ExclamationMark,                     /* 0xad  U_InvertedExclamationMark */
   0x00ae,                                /* 0xae  U_LeftPointingGuillemet */
   0x00af,                                /* 0xaf  U_RightPointingGuillemet */
                                          
   U_LatinCapitalLetterA,                 /* 0xb0  U_LatinSmallLetterAWithTilde */
   U_LatinCapitalLetterO,                 /* 0xb1  U_LatinSmallLetterOWithTilde */
   U_LatinCapitalLetterO,                 /* 0xb2  U_LatinCapitalLetterOSlash */
   U_LatinCapitalLetterO,                 /* 0xb3  U_LatinSmallLetterOSlash */
   U_LatinCapitalLetterO,                 /* 0xb4  U_LatinSmallLigatureOE */
   U_LatinCapitalLetterO,                 /* 0xb5  U_LatinCapitalLigatureOE */
   U_LatinCapitalLetterA,                 /* 0xb6  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterA,                 /* 0xb7  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterO,                 /* 0xb8  U_LatinCapitalLetterOWithTilde */
   0x00b9,                                /* 0xb9  U_Diaeresis */
   0x00ba,                                /* 0xba  U_AcuteAccent */
   0x00bb,                                /* 0xbb  U_Dagger */
   0x00bc,                                /* 0xbc  U_ParagraphSign */
   0x00bd,                                /* 0xbd  U_CopyrightSign */
   0x00be,                                /* 0xbe  U_RegisteredSign */
   0x00bf,                                /* 0xbf  U_TradeMarkSign */
                                          
   U_LatinCapitalLetterI,                 /* 0xc0  U_LatinSmallLigatureIJ */
   U_LatinCapitalLetterI,                 /* 0xc1  U_LatinCapitalLigatureIJ */
   0x00c2,                                /* 0xc2  U_HebrewLetterAlef */
   0x00c3,                                /* 0xc3  U_HebrewLetterBet */
   0x00c4,                                /* 0xc4  U_HebrewLetterGimel */
   0x00c5,                                /* 0xc5  U_HebrewLetterDalet */
   0x00c6,                                /* 0xc6  U_HebrewLetterHe */
   0x00c7,                                /* 0xc7  U_HebrewLetterVav */
   0x00c8,                                /* 0xc8  U_HebrewLetterZayin */
   0x00c9,                                /* 0xc9  U_HebrewLetterHet */
   0x00ca,                                /* 0xca  U_HebrewLetterTet */
   0x00cb,                                /* 0xcb  U_HebrewLetterYod */
   0x00cc,                                /* 0xcc  U_HebrewLetterKaf */
   0x00cd,                                /* 0xcd  U_HebrewLetterLamed */
   0x00ce,                                /* 0xce  U_HebrewLetterMem */
   0x00cf,                                /* 0xcf  U_HebrewLetterNun */
                                          
   0x00d0,                                /* 0xd0  U_HebrewLetterSamekh */
   0x00d1,                                /* 0xd1  U_HebrewLetterAyin */
   0x00d2,                                /* 0xd2  U_HebrewLetterPe */
   0x00d3,                                /* 0xd3  U_HebrewLetterTsadi */
   0x00d4,                                /* 0xd4  U_HebrewLetterQof */
   0x00d5,                                /* 0xd5  U_HebrewLetterResh */
   0x00d6,                                /* 0xd6  U_HebrewLetterShin */
   0x00d7,                                /* 0xd7  U_HebrewLetterTav */
   0x00d8,                                /* 0xd8  U_HebrewLetterNun */
   0x00d9,                                /* 0xd9  U_HebrewLetterFinalKaf */
   0x00da,                                /* 0xda  U_HebrewLetterFinalMem */
   0x00db,                                /* 0xdb  U_HebrewLetterFinalPe */
   0x00dc,                                /* 0xdc  U_HebrewLetterFinalTsadi */
   0x00dd,                                /* 0xdd  U_SectionSign */
   0x00de,                                /* 0xde  U_ModifierLetterCircumflexAccent */
   0x00df,                                /* 0xdf  U_Infinity */
                                          
   0x00e0,                                /* 0xe0  U_GreekSmallLetterAlpha */
   0x00e1,                                /* 0xe1  U_GreekSmallLetterBeta */
   0x00e2,                                /* 0xe2  U_GreekCapitalLetterGamma */
   0x00e3,                                /* 0xe3  U_GreekSmallLetterPi */
   0x00e4,                                /* 0xe4  U_GreekCapitalLetterSigma */
   0x00e5,                                /* 0xe5  U_GreekSmallLetterSigma */
   0x00e6,                                /* 0xe6  U_GreekSmallLetterMu */
   0x00e7,                                /* 0xe7  U_GreekSmallLetterTau */
   0x00e8,                                /* 0xe8  ??? */
   0x00e9,                                /* 0xe9  ??? */
   0x00ea,                                /* 0xea  U_GreekCapitalLetterOmega */
   0x00eb,                                /* 0xeb  U_GreekSmallLetterDelta */
   0x00ec,                                /* 0xec  U_ContourIntegral */
   0x00ed,                                /* 0xed  ??? */
   0x00ee,                                /* 0xee  U_ElementOf */
   0x00ef,                                /* 0xef  U_Intersection */
                                          
   0x00f0,                                /* 0xf0  U_IdenticalTo */
   0x00f1,                                /* 0xf1  U_PlusMinusSign */
   0x00f2,                                /* 0xf2  U_GreaterThanOrEqualTo */
   0x00f3,                                /* 0xf3  U_LessThanOrEqualTo */
   0x00f4,                                /* 0xf4  U_Integral (upper half) */
   0x00f5,                                /* 0xf5  U_Integral (lower half) */
   0x00f6,                                /* 0xf6  U_DivisionSign */
   0x00f7,                                /* 0xf7  U_AlmostEqualTo */
   0x00f8,                                /* 0xf8  U_DegreeSign */
   0x00f9,                                /* 0xf9  U_Bullet */
   0x00fa,                                /* 0xfa  U_MiddleDot */
   0x00fb,                                /* 0xfb  U_SquareRoot */
   0x00fc,                                /* 0xfc  U_SuperscriptLatinSmallLetterN */
   0x00fd,                                /* 0xfd  U_SuperscriptTwo */
   0x00fe,                                /* 0xfe  U_SuperscriptThree */
   0x00ff                                 /* 0xff  U_Macron */
};
