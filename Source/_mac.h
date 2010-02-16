/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_mac.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepage for Apple Mac encoding (Mac OS Roman)
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
*  u_CODE_MAC[]:
*     Unicode named codepage for Apple Mac encoding (Mac OS Roman)
*
*  This character set is used for at least the following Mac OS localizations: 
*  U.S., British, Canadian French, French, Swiss French, German, Swiss German, 
*  Italian, Swiss Italian, Dutch, Swedish, Norwegian, Danish, Finnish, Spanish, 
*  Catalan, Portuguese, Brazilian, and the default International system.
*
*  Notes:
*     The following corporate zone Unicode character is used in this mapping:
*
*        0xF8FF   Apple logo
*
*     The graphic image associated with the Apple logo characteris not
*     authorized for use without permission of Apple, and unauthorized use might 
*     constitute trademark infringement. (Thus we map this characterto U_NIL here!)
*
******************************************|************************************/

static unsigned   u_CODE_MAC[] =          /* CODE_MAC */
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
   U_NIL,                                 /* 0x7F  --- UNDEFINED --- */

   U_LatinCapitalLetterAWithDiaeresis,    /* 0x80  U_LatinCapitalLetterAWithDiaeresis */
   U_LatinCapitalLetterAWithRingAbove,    /* 0x81  U_LatinCapitalLetterAWithRingAbove */
   U_LatinCapitalLetterCWithCedilla,      /* 0x82  U_LatinCapitalLetterCWithCedilla */
   U_LatinCapitalLetterEWithAcute,        /* 0x83  U_LatinCapitalLetterEWithAcute */
   U_LatinCapitalLetterNWithTilde,        /* 0x84  U_LatinCapitalLetterNWithTilde */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0x85  U_LatinCapitalLetterOWithDiaeresis */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0x86  U_LatinCapitalLetterUWithDiaeresis */
   U_LatinSmallLetterAWithAcute,          /* 0x87  U_LatinSmallLetterAWithAcute */
   U_LatinSmallLetterAWithGrave,          /* 0x88  U_LatinSmallLetterAWithGrave */
   U_LatinSmallLetterAWithCircumflex,     /* 0x89  U_LatinSmallLetterAWithCircumflex */
   U_LatinSmallLetterAWithDiaeresis,      /* 0x8a  U_LatinSmallLetterAWithDiaeresis */
   U_LatinSmallLetterAWithTilde,          /* 0x8b  U_LatinSmallLetterAWithTilde */
   U_LatinSmallLetterAWithRingAbove,      /* 0x8c  U_LatinSmallLetterAWithRingAbove */
   U_LatinSmallLetterCWithCedilla,        /* 0x8d  U_LatinSmallLetterCWithCedilla */
   U_LatinSmallLetterEWithAcute,          /* 0x8e  U_LatinSmallLetterEWithAcute */
   U_LatinSmallLetterEWithGrave,          /* 0x8f  U_LatinSmallLetterEWithGrave */
                                          
   U_LatinSmallLetterEWithCircumflex,     /* 0x90  U_LatinSmallLetterEWithCircumflex */
   U_LatinSmallLetterEWithDiaeresis,      /* 0x91  U_LatinSmallLetterEWithDiaeresis */
   U_LatinSmallLetterIWithAcute,          /* 0x92  U_LatinSmallLetterIWithAcute */
   U_LatinSmallLetterIWithGrave,          /* 0x93  U_LatinSmallLetterIWithGrave */
   U_LatinSmallLetterIWithCircumflex,     /* 0x94  U_LatinSmallLetterIWithCircumflex */
   U_LatinSmallLetterIWithDiaeresis,      /* 0x95  U_LatinSmallLetterIWithDiaeresis */
   U_LatinSmallLetterNWithTilde,          /* 0x96  U_LatinSmallLetterNWithTilde */
   U_LatinSmallLetterOWithAcute,          /* 0x97  U_LatinSmallLetterOWithAcute */
   U_LatinSmallLetterOWithGrave,          /* 0x98  U_LatinSmallLetterOWithGrave */
   U_LatinSmallLetterOWithCircumflex,     /* 0x99  U_LatinSmallLetterOWithCircumflex */
   U_LatinSmallLetterOWithDiaeresis,      /* 0x9a  U_LatinSmallLetterOWithDiaeresis */
   U_LatinSmallLetterOWithTilde,          /* 0x9b  U_LatinSmallLetterOWithTilde */
   U_LatinSmallLetterUWithAcute,          /* 0x9c  U_LatinSmallLetterUWithAcute */
   U_LatinSmallLetterUWithGrave,          /* 0x9d  U_LatinSmallLetterUWithGrave */
   U_LatinSmallLetterUWithCircumflex,     /* 0x9e  U_LatinSmallLetterUWithCircumflex */
   U_LatinSmallLetterUWithDiaeresis,      /* 0x9f  U_LatinSmallLetterUWithDiaeresis */
                                          
   U_Dagger,                              /* 0xa0  U_Dagger */
   U_DegreeSign,                          /* 0xa1  U_DegreeSign */
   U_CentSign,                            /* 0xa2  U_CentSign */
   U_PoundSign,                           /* 0xa3  U_PoundSign */
   U_SectionSign,                         /* 0xa4  U_SectionSign */
   U_Bullet,                              /* 0xa5  U_Bullet */
   U_ParagraphSign,                       /* 0xa6  U_ParagraphSign (aka: pilcrow sign) */
   U_LatinSmallLetterSharpS,              /* 0xa7  U_LatinSmallLetterSharpS */
   U_RegisteredSign,                      /* 0xa8  U_RegisteredSign */
   U_CopyrightSign,                       /* 0xa9  U_CopyrightSign */
   U_TradeMarkSign,                       /* 0xaa  U_TradeMarkSign */
   U_AcuteAccent,                         /* 0xab  U_AcuteAccent */
   U_Diaeresis,                           /* 0xac  U_Diaeresis */
   U_NotEqualTo,                          /* 0xad  U_NotEqualTo */
   U_LatinCapitalLigatureAE,              /* 0xae  U_LatinCapitalLigatureAE */
   U_LatinCapitalLetterOSlash,            /* 0xaf  U_LatinCapitalLetterOSlash */
   
   U_Infinity,                            /* 0xb0  U_Infinity */
   U_PlusMinusSign,                       /* 0xb1  U_PlusMinusSign */
   U_LessThanOrEqualTo,                   /* 0xb2  U_LessThanOrEqualTo */
   U_GreaterThanOrEqualTo,                /* 0xb3  U_GreaterThanOrEqualTo */
   U_YenSign,                             /* 0xb4  U_YenSign */
   U_MicroSign,                           /* 0xb5  U_MicroSign */
   U_PartialDifferential,                 /* 0xb6  U_PartialDifferential */
   U_NArySummation,                       /* 0xb7  U_NArySummation */
   U_NAryProduct,                         /* 0xb8  U_NAryProduct */
   U_GreekSmallLetterPi,                  /* 0xb9  U_GreekSmallLetterPi */
   U_Integral,                            /* 0xba  U_Integral */
   U_FeminineOrdinalIndicator,            /* 0xbb  U_FeminineOrdinalIndicator */
   U_MasculineOrdinalIndicator,           /* 0xbc  U_MasculineOrdinalIndicator */
   U_GreekCapitalLetterOmega,             /* 0xbd  U_GreekCapitalLetterOmega */
   U_LatinSmallLigatureAE,                /* 0xbe  U_LatinSmallLigatureAE */
   U_LatinSmallLetterOSlash,              /* 0xbf  U_LatinSmallLetterOSlash */
                                          
   U_InvertedQuestionMark,                /* 0xc0  U_InvertedQuestionMark */
   U_InvertedExclamationMark,             /* 0xc1  U_InvertedExclamationMark */
   U_NotSign,                             /* 0xc2  U_NotSign */
   U_SquareRoot,                          /* 0xc3  U_SquareRoot */
   U_LatinSmallLetterScriptF,             /* 0xc4  U_LatinSmallLetterScriptF */
   U_AlmostEqualTo,                       /* 0xc5  U_AlmostEqualTo */
   U_Increment,                           /* 0xc6  U_Increment */
   U_LeftPointingGuillemet,               /* 0xc7  U_LeftPointingGuillemet */
   U_RightPointingGuillemet,              /* 0xc8  U_RightPointingGuillemet */
   U_HorizontalEllipsis,                  /* 0xc9  U_HorizontalEllipsis */
   U_NB_SP,                               /* 0xca  U_NB_SP */
   U_LatinCapitalLetterAWithGrave,        /* 0xcb  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterAWithTilde,        /* 0xcc  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterOWithTilde,        /* 0xcd  U_LatinCapitalLetterOWithTilde */
   U_LatinCapitalLigatureOE,              /* 0xce  U_LatinCapitalLigatureOE */
   U_LatinSmallLigatureOE,                /* 0xcf  U_LatinSmallLigatureOE */
                                          
   U_EnDash,                              /* 0xd0  U_EnDash */
   U_EmDash,                              /* 0xd1  U_EmDash */
   U_LeftDoubleQuotationMark,             /* 0xd2  U_LeftDoubleQuotationMark */
   U_RightDoubleQuotationMark,            /* 0xd3  U_RightDoubleQuotationMark */
   U_LeftSingleQuotationMark,             /* 0xd4  U_LeftSingleQuotationMark */
   U_RightSingleQuotationMark,            /* 0xd5  U_RightSingleQuotationMark */
   U_DivisionSign,                        /* 0xd6  U_DivisionSign */
   U_Lozenge,                             /* 0xd7  U_Lozenge */
   U_LatinSmallLetterYWithDiaeresis,      /* 0xd8  U_LatinSmallLetterYWithDiaeresis */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0xd9  U_LatinCapitalLetterYWithDiaeresis */
   U_FractionSlash,                       /* 0xda  U_FractionSlash */
   U_EuroSign,                            /* 0xdb  U_EuroSign */
   U_LeftPointingSingleGuillemet,         /* 0xdc  U_LeftPointingSingleGuillemet */
   U_RightPointingSingleGuillemet,        /* 0xdd  U_RightPointingSingleGuillemet */
   U_LatinSmallLigatureFI,                /* 0xde  U_LatinSmallLigatureFI */
   U_LatinSmallLigatureFL,                /* 0xdf  U_LatinSmallLigatureFL */
                                          
   U_DoubleDagger,                        /* 0xe0  U_DoubleDagger */
   U_MiddleDot,                           /* 0xe1  U_MiddleDot */
   U_SingleLow9QuotationMark,             /* 0xe2  U_SingleLow9QuotationMark */
   U_DoubleLow9QuotationMark,             /* 0xe3  U_DoubleLow9QuotationMark */
   U_PerMilleSign,                        /* 0xe4  U_PerMilleSign */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xe5  U_LatinCapitalLetterAWithCircumflex */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xe6  U_LatinCapitalLetterEWithCircumflex */
   U_LatinCapitalLetterAWithAcute,        /* 0xe7  U_LatinCapitalLetterAWithAcute */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xe8  U_LatinCapitalLetterEWithDiaeresis */
   U_LatinCapitalLetterEWithGrave,        /* 0xe9  U_LatinCapitalLetterEWithGrave */
   U_LatinCapitalLetterIWithAcute,        /* 0xea  U_LatinCapitalLetterIWithAcute */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xeb  U_LatinCapitalLetterIWithCircumflex */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xec  U_LatinCapitalLetterIWithDiaeresis */
   U_LatinCapitalLetterIWithGrave,        /* 0xed  U_LatinCapitalLetterIWithGrave */
   U_LatinCapitalLetterOWithAcute,        /* 0xee  U_LatinCapitalLetterOWithAcute */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xef  U_LatinCapitalLetterOWithCircumflex */
                                          
   U_NIL,                                 /* 0xf0  -- (Apple logo: 0xF8FF) -- */
   U_LatinCapitalLetterOWithGrave,        /* 0xf1  U_LatinCapitalLetterOWithGrave */
   U_LatinCapitalLetterUWithAcute,        /* 0xf2  U_LatinCapitalLetterUWithAcute */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xf3  U_LatinCapitalLetterUWithCircumflex */
   U_LatinCapitalLetterUWithGrave,        /* 0xf4  U_LatinCapitalLetterUWithGrave */
   U_LatinSmallLetterDotlessI,            /* 0xf5  U_LatinSmallLetterDotlessI */
   U_ModifierLetterCircumflexAccent,      /* 0xf6  U_ModifierLetterCircumflexAccent */
   U_SmallTilde,                          /* 0xf7  U_SmallTilde */
   U_Macron,                              /* 0xf8  U_Macron */
   U_Breve,                               /* 0xf9  U_Breve */
   U_DotAbove,                            /* 0xfa  U_DotAbove */
   U_RingAbove,                           /* 0xfb  U_RingAbove */
   U_Cedilla,                             /* 0xfc  U_Cedilla */
   U_DoubleAcuteAccent,                   /* 0xfd  U_DoubleAcuteAccent */
   U_Ogonek,                              /* 0xfe  U_Ogonek */
   U_Caron                                /* 0xff  U_Caron */
};


/* +++ EOF +++ */
