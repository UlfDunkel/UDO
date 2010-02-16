/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_437.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepage for ISO encoding (cp1252)
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
*  u_CODE_ISO[]:
*     Unicode named codepage for ISO encoding (cp1252)
*
******************************************|************************************/

static unsigned   u_CODE_ISO[] =          /* CODE_ISO */
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
   U_LatinCapitalLetterIWithCircumflex,   /* 0xcf  U_LatinCapitalLetterIWithDiaeresis */
                                          
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


