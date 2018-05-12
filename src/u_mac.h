/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_mac.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepages for Apple Mac encodings:
*
*                 - u_CODE_MAC    = Mac OS Roman
*                 - u_CODE_MAC_CE = Mac OS Central Europe
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
*    fd  Feb 16: ligatures and sorting tables moved from encoding.h
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 23: - sort_CODE_MAC[] adjusted
*                - CODE_MAC_CE
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

static _UWORD const u_CODE_MAC[] =             /* CODE_MAC */
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





/******************************************************************************
*
*  CODE_MAC_lig[]:
*     list of ligatures:
*
*  CODE_MAC_lig[0] is the original ligature character
*  CODE_MAC_lig[1] + CODE_MAC_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_MAC_lig[][3] =        /* CODE_MAC character ligatures */
{
   {0x0080, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x0080  U_LatinCapitalLetterAWithDiaeresis */
   {0x0085, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x0085  U_LatinCapitalLetterOWithDiaeresis */
   {0x0086, U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x0086  U_LatinCapitalLetterUWithDiaeresis */
   {0x008a, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x008a  U_LatinSmallLetterAWithDiaeresis */
   {0x0091, U_LatinCapitalLetterE, U_LatinCapitalLetterE},    /* 0x0091  U_LatinSmallLetterEWithDiaeresis */
   {0x0095, U_LatinCapitalLetterI, U_LatinCapitalLetterE},    /* 0x0095  U_LatinSmallLetterIWithDiaeresis */
   {0x009a, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x009a  U_LatinSmallLetterOWithDiaeresis */
   {0x009f, U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x009f  U_LatinSmallLetterUWithDiaeresis */
   {0x00a7, U_LatinCapitalLetterS, U_LatinCapitalLetterS},    /* 0x00a7  U_LatinSmallLetterSharpS */
   {0x00ae, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00ae  U_LatinCapitalLigatureAE */
   {0x00af, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00af  U_LatinCapitalLetterOSlash */
   {0x00be, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00be  U_LatinSmallLigatureAE */
   {0x00bf, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00bf  U_LatinSmallLetterOSlash */
   {0x00ce, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00ce  U_LatinCapitalLigatureOE */
   {0x00cf, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00cf  U_LatinSmallLigatureOE */
   {0x00d8, U_LatinCapitalLetterY, U_LatinCapitalLetterE},    /* 0x00d8  U_LatinSmallLetterYWithDiaeresis */
   {0x00d9, U_LatinCapitalLetterY, U_LatinCapitalLetterE},    /* 0x00d9  U_LatinCapitalLetterYWithDiaeresis */
   {0x00de, U_LatinCapitalLetterF, U_LatinCapitalLetterI},    /* 0x00de  U_LatinSmallLigatureFI */
   {0x00df, U_LatinCapitalLetterF, U_LatinCapitalLetterL},    /* 0x00df  U_LatinSmallLigatureFL */
   {0x00e8, U_LatinCapitalLetterE, U_LatinCapitalLetterE},    /* 0x00e8  U_LatinCapitalLetterEWithDiaeresis */
   {0x00ec, U_LatinCapitalLetterI, U_LatinCapitalLetterE},    /* 0x00ec  U_LatinCapitalLetterIWithDiaeresis */
   {0x00f5, U_LatinCapitalLetterI, U_LatinCapitalLetterI},    /* 0x00f5  U_LatinSmallLetterDotlessI */
   {0x0000, U_NIL                , U_NIL}                     /* list terminator */
};





/******************************************************************************
*
*  CODE_MAC sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_MAC[] =          /* CODE_MAC */
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
   0x007f,                                /* 0x7F  --- UNDEFINED --- */

   U_LatinCapitalLetterA,                 /* 0x80  U_LatinCapitalLetterAWithDiaeresis */
   U_LatinCapitalLetterA,                 /* 0x81  U_LatinCapitalLetterAWithRingAbove */
   U_LatinCapitalLetterC,                 /* 0x82  U_LatinCapitalLetterCWithCedilla */
   U_LatinCapitalLetterE,                 /* 0x83  U_LatinCapitalLetterEWithAcute */
   U_LatinCapitalLetterN,                 /* 0x84  U_LatinCapitalLetterNWithTilde */
   U_LatinCapitalLetterO,                 /* 0x85  U_LatinCapitalLetterOWithDiaeresis */
   U_LatinCapitalLetterU,                 /* 0x86  U_LatinCapitalLetterUWithDiaeresis */
   U_LatinCapitalLetterA,                 /* 0x87  U_LatinSmallLetterAWithAcute */
   U_LatinCapitalLetterA,                 /* 0x88  U_LatinSmallLetterAWithGrave */
   U_LatinCapitalLetterA,                 /* 0x89  U_LatinSmallLetterAWithCircumflex */
   U_LatinCapitalLetterA,                 /* 0x8a  U_LatinSmallLetterAWithDiaeresis */
   U_LatinCapitalLetterA,                 /* 0x8b  U_LatinSmallLetterAWithTilde */
   U_LatinCapitalLetterA,                 /* 0x8c  U_LatinSmallLetterAWithRingAbove */
   U_LatinCapitalLetterC,                 /* 0x8d  U_LatinSmallLetterCWithCedilla */
   U_LatinCapitalLetterE,                 /* 0x8e  U_LatinSmallLetterEWithAcute */
   U_LatinCapitalLetterE,                 /* 0x8f  U_LatinSmallLetterEWithGrave */
   
   U_LatinCapitalLetterE,                 /* 0x90  U_LatinSmallLetterEWithCircumflex */
   U_LatinCapitalLetterE,                 /* 0x91  U_LatinSmallLetterEWithDiaeresis */
   U_LatinCapitalLetterI,                 /* 0x92  U_LatinSmallLetterIWithAcute */
   U_LatinCapitalLetterI,                 /* 0x93  U_LatinSmallLetterIWithGrave */
   U_LatinCapitalLetterI,                 /* 0x94  U_LatinSmallLetterIWithCircumflex */
   U_LatinCapitalLetterI,                 /* 0x95  U_LatinSmallLetterIWithDiaeresis */
   U_LatinCapitalLetterN,                 /* 0x96  U_LatinSmallLetterNWithTilde */
   U_LatinCapitalLetterO,                 /* 0x97  U_LatinSmallLetterOWithAcute */
   U_LatinCapitalLetterO,                 /* 0x98  U_LatinSmallLetterOWithGrave */
   U_LatinCapitalLetterO,                 /* 0x99  U_LatinSmallLetterOWithCircumflex */
   U_LatinCapitalLetterO,                 /* 0x9a  U_LatinSmallLetterOWithDiaeresis */
   U_LatinCapitalLetterO,                 /* 0x9b  U_LatinSmallLetterOWithTilde */
   U_LatinCapitalLetterU,                 /* 0x9c  U_LatinSmallLetterUWithAcute */
   U_LatinCapitalLetterU,                 /* 0x9d  U_LatinSmallLetterUWithGrave */
   U_LatinCapitalLetterU,                 /* 0x9e  U_LatinSmallLetterUWithCircumflex */
   U_LatinCapitalLetterU,                 /* 0x9f  U_LatinSmallLetterUWithDiaeresis */
                                          
   U_Dagger,                              /* 0xa0  U_Dagger */
   U_DegreeSign,                          /* 0xa1  U_DegreeSign */
   U_CentSign,                            /* 0xa2  U_CentSign */
   U_PoundSign,                           /* 0xa3  U_PoundSign */
   U_SectionSign,                         /* 0xa4  U_SectionSign */
   U_Bullet,                              /* 0xa5  U_Bullet */
   U_ParagraphSign,                       /* 0xa6  U_ParagraphSign (aka: pilcrow sign) */
   U_LatinCapitalLetterS,                 /* 0xa7  U_LatinSmallLetterSharpS */
   U_RegisteredSign,                      /* 0xa8  U_RegisteredSign */
   U_CopyrightSign,                       /* 0xa9  U_CopyrightSign */
   U_TradeMarkSign,                       /* 0xaa  U_TradeMarkSign */
   U_AcuteAccent,                         /* 0xab  U_AcuteAccent */
   U_Diaeresis,                           /* 0xac  U_Diaeresis */
   U_NotEqualTo,                          /* 0xad  U_NotEqualTo */
   U_LatinCapitalLetterA,                 /* 0xae  U_LatinCapitalLigatureAE */
   U_LatinCapitalLetterO,                 /* 0xaf  U_LatinCapitalLetterOSlash */
   
   U_Infinity,                            /* 0xb0  U_Infinity */
   U_PlusMinusSign,                       /* 0xb1  U_PlusMinusSign */
   U_LessThanOrEqualTo,                   /* 0xb2  U_LessThanOrEqualTo */
   U_GreaterThanOrEqualTo,                /* 0xb3  U_GreaterThanOrEqualTo */
   U_YenSign,                             /* 0xb4  U_YenSign */
   U_MicroSign,                           /* 0xb5  U_MicroSign */
   U_PartialDifferential,                 /* 0xb6  U_PartialDifferential */
   U_NArySummation,                       /* 0xb7  U_NArySummation */
   U_NAryProduct,                         /* 0xb8  U_NAryProduct */
   U_GreekCapitalLetterPi,                /* 0xb9  U_GreekSmallLetterPi */
   U_Integral,                            /* 0xba  U_Integral */
   U_FeminineOrdinalIndicator,            /* 0xbb  U_FeminineOrdinalIndicator */
   U_MasculineOrdinalIndicator,           /* 0xbc  U_MasculineOrdinalIndicator */
   U_GreekCapitalLetterOmega,             /* 0xbd  U_GreekCapitalLetterOmega */
   U_LatinCapitalLetterA,                 /* 0xbe  U_LatinSmallLigatureAE */
   U_LatinCapitalLetterO,                 /* 0xbf  U_LatinSmallLetterOSlash */
                                          
   U_InvertedQuestionMark,                /* 0xc0  U_InvertedQuestionMark */
   U_InvertedExclamationMark,             /* 0xc1  U_InvertedExclamationMark */
   U_NotSign,                             /* 0xc2  U_NotSign */
   U_SquareRoot,                          /* 0xc3  U_SquareRoot */
   U_LatinCapitalLetterF,                 /* 0xc4  U_LatinSmallLetterScriptF */
   U_AlmostEqualTo,                       /* 0xc5  U_AlmostEqualTo */
   U_Increment,                           /* 0xc6  U_Increment */
   U_LeftPointingGuillemet,               /* 0xc7  U_LeftPointingGuillemet */
   U_RightPointingGuillemet,              /* 0xc8  U_RightPointingGuillemet */
   U_HorizontalEllipsis,                  /* 0xc9  U_HorizontalEllipsis */
   U_NB_SP,                               /* 0xca  U_NB_SP */
   U_LatinCapitalLetterA,                 /* 0xcb  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterA,                 /* 0xcc  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterO,                 /* 0xcd  U_LatinCapitalLetterOWithTilde */
   U_LatinCapitalLetterO,                 /* 0xce  U_LatinCapitalLigatureOE */
   U_LatinCapitalLetterO,                 /* 0xcf  U_LatinSmallLigatureOE */
                                          
   U_EnDash,                              /* 0xd0  U_EnDash */
   U_EmDash,                              /* 0xd1  U_EmDash */
   U_LeftDoubleQuotationMark,             /* 0xd2  U_LeftDoubleQuotationMark */
   U_RightDoubleQuotationMark,            /* 0xd3  U_RightDoubleQuotationMark */
   U_LeftSingleQuotationMark,             /* 0xd4  U_LeftSingleQuotationMark */
   U_RightSingleQuotationMark,            /* 0xd5  U_RightSingleQuotationMark */
   U_DivisionSign,                        /* 0xd6  U_DivisionSign */
   U_Lozenge,                             /* 0xd7  U_Lozenge */
   U_LatinCapitalLetterY,                 /* 0xd8  U_LatinSmallLetterYWithDiaeresis */
   U_LatinCapitalLetterY,                 /* 0xd9  U_LatinCapitalLetterYWithDiaeresis */
   U_FractionSlash,                       /* 0xda  U_FractionSlash */
   U_EuroSign,                            /* 0xdb  U_EuroSign */
   U_LeftPointingSingleGuillemet,         /* 0xdc  U_LeftPointingSingleGuillemet */
   U_RightPointingSingleGuillemet,        /* 0xdd  U_RightPointingSingleGuillemet */
   U_LatinCapitalLetterF,                 /* 0xde  U_LatinSmallLigatureFI */
   U_LatinCapitalLetterF,                 /* 0xdf  U_LatinSmallLigatureFL */
                                          
   U_DoubleDagger,                        /* 0xe0  U_DoubleDagger */
   U_MiddleDot,                           /* 0xe1  U_MiddleDot */
   U_SingleLow9QuotationMark,             /* 0xe2  U_SingleLow9QuotationMark */
   U_DoubleLow9QuotationMark,             /* 0xe3  U_DoubleLow9QuotationMark */
   U_PerMilleSign,                        /* 0xe4  U_PerMilleSign */
   U_LatinCapitalLetterA,                 /* 0xe5  U_LatinCapitalLetterAWithCircumflex */
   U_LatinCapitalLetterE,                 /* 0xe6  U_LatinCapitalLetterEWithCircumflex */
   U_LatinCapitalLetterA,                 /* 0xe7  U_LatinCapitalLetterAWithAcute */
   U_LatinCapitalLetterE,                 /* 0xe8  U_LatinCapitalLetterEWithDiaeresis */
   U_LatinCapitalLetterE,                 /* 0xe9  U_LatinCapitalLetterEWithGrave */
   U_LatinCapitalLetterI,                 /* 0xea  U_LatinCapitalLetterIWithAcute */
   U_LatinCapitalLetterI,                 /* 0xeb  U_LatinCapitalLetterIWithCircumflex */
   U_LatinCapitalLetterI,                 /* 0xec  U_LatinCapitalLetterIWithDiaeresis */
   U_LatinCapitalLetterI,                 /* 0xed  U_LatinCapitalLetterIWithGrave */
   U_LatinCapitalLetterO,                 /* 0xee  U_LatinCapitalLetterOWithAcute */
   U_LatinCapitalLetterO,                 /* 0xef  U_LatinCapitalLetterOWithCircumflex */
                                          
   U_NIL,                                 /* 0xf0  -- (Apple logo: 0xF8FF) -- */
   U_LatinCapitalLetterO,                 /* 0xf1  U_LatinCapitalLetterOWithGrave */
   U_LatinCapitalLetterU,                 /* 0xf2  U_LatinCapitalLetterUWithAcute */
   U_LatinCapitalLetterU,                 /* 0xf3  U_LatinCapitalLetterUWithCircumflex */
   U_LatinCapitalLetterU,                 /* 0xf4  U_LatinCapitalLetterUWithGrave */
   U_LatinCapitalLetterI,                 /* 0xf5  U_LatinSmallLetterDotlessI */
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










/******************************************************************************
*
*  u_CODE_MAC_CE[]:
*     Unicode named codepage for Apple Mac encoding (Mac OS Central Europe)
*
*  This character set is intended to cover the following languages:
*  Polish, Czech, Slovak, Hungarian, Estonian, Latvian, Lithuanian
*
******************************************|************************************/

static _UWORD const u_CODE_MAC_CE[] =          /* CODE_MAC_CE */
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

   U_LatinCapitalLetterAWithDiaeresis,    /* 0x80   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterAWithMacron,       /* 0x81   0x0100   LATIN CAPITAL LETTER A WITH MACRON */
   U_LatinSmallLetterAWithMacron,         /* 0x82   0x0101   LATIN SMALL LETTER A WITH MACRON */
   U_LatinCapitalLetterEWithAcute,        /* 0x83   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterAWithOgonek,       /* 0x84   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0x85   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0x86   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinSmallLetterAWithAcute,          /* 0x87   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinSmallLetterAWithOgonek,         /* 0x88   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_LatinCapitalLetterCWithCaron,        /* 0x89   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinSmallLetterAWithDiaeresis,      /* 0x8A   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinSmallLetterCWithCaron,          /* 0x8B   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinCapitalLetterCWithAcute,        /* 0x8C   0x0106   LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinSmallLetterCWithAcute,          /* 0x8D   0x0107   LATIN SMALL LETTER C WITH ACUTE */
   U_LatinSmallLetterEWithAcute,          /* 0x8E   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterZWithAcute,        /* 0x8F   0x0179   LATIN CAPITAL LETTER Z WITH ACUTE */
   U_LatinSmallLetterZWithAcute,          /* 0x90   0x017A   LATIN SMALL LETTER Z WITH ACUTE */
   U_LatinCapitalLetterDWithCaron,        /* 0x91   0x010E   LATIN CAPITAL LETTER D WITH CARON */
   U_LatinSmallLetterIWithAcute,          /* 0x92   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinSmallLetterDWithCaron,          /* 0x93   0x010F   LATIN SMALL LETTER D WITH CARON */
   U_LatinCapitalLetterEWithMacron,       /* 0x94   0x0112   LATIN CAPITAL LETTER E WITH MACRON */
   U_LatinSmallLetterEWithMacron,         /* 0x95   0x0113   LATIN SMALL LETTER E WITH MACRON */
   U_LatinCapitalLetterEWithDotAbove,     /* 0x96   0x0116   LATIN CAPITAL LETTER E WITH DOT ABOVE */
   U_LatinSmallLetterOWithAcute,          /* 0x97   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinSmallLetterEWithDotAbove,       /* 0x98   0x0117   LATIN SMALL LETTER E WITH DOT ABOVE */
   U_LatinSmallLetterOWithCircumflex,     /* 0x99   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterOWithDiaeresis,      /* 0x9A   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinSmallLetterOWithTilde,          /* 0x9B   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinSmallLetterUWithAcute,          /* 0x9C   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterEWithCaron,        /* 0x9D   0x011A   LATIN CAPITAL LETTER E WITH CARON */
   U_LatinSmallLetterEWithCaron,          /* 0x9E   0x011B   LATIN SMALL LETTER E WITH CARON */
   U_LatinSmallLetterUWithDiaeresis,      /* 0x9F   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_Dagger,                              /* 0xA0   0x2020   DAGGER */
   U_DegreeSign,                          /* 0xA1   0x00B0   DEGREE SIGN */
   U_LatinCapitalLetterEWithOgonek,       /* 0xA2   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_SectionSign,                         /* 0xA4   0x00A7   SECTION SIGN */
   U_Bullet,                              /* 0xA5   0x2022   BULLET */
   U_ParagraphSign,                       /* 0xA6   0x00B6   PILCROW SIGN */
   U_LatinSmallLetterSharpS,              /* 0xA7   0x00DF   LATIN SMALL LETTER SHARP S */
   U_RegisteredSign,                      /* 0xA8   0x00AE   REGISTERED SIGN */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_TradeMarkSign,                       /* 0xAA   0x2122   TRADE MARK SIGN */
   U_LatinSmallLetterEWithOgonek,         /* 0xAB   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_Diaeresis,                           /* 0xAC   0x00A8   DIAERESIS */
   U_NotEqualTo,                          /* 0xAD   0x2260   NOT EQUAL TO */
   U_LatinSmallLetterGWithCedilla,        /* 0xAE   0x0123   LATIN SMALL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterIWithOgonek,       /* 0xAF   0x012E   LATIN CAPITAL LETTER I WITH OGONEK */
   U_LatinSmallLetterIWithOgonek,         /* 0xB0   0x012F   LATIN SMALL LETTER I WITH OGONEK */
   U_LatinCapitalLetterIWithMacron,       /* 0xB1   0x012A   LATIN CAPITAL LETTER I WITH MACRON */
   U_LessThanOrEqualTo,                   /* 0xB2   0x2264   LESS-THAN OR EQUAL TO */
   U_GreaterThanOrEqualTo,                /* 0xB3   0x2265   GREATER-THAN OR EQUAL TO */
   U_LatinSmallLetterIWithMacron,         /* 0xB4   0x012B   LATIN SMALL LETTER I WITH MACRON */
   U_LatinCapitalLetterKWithCedilla,      /* 0xB5   0x0136   LATIN CAPITAL LETTER K WITH CEDILLA */
   U_PartialDifferential,                 /* 0xB6   0x2202   PARTIAL DIFFERENTIAL */
   U_NArySummation,                       /* 0xB7   0x2211   N-ARY SUMMATION */
   U_LatinSmallLetterLWithStroke,         /* 0xB8   0x0142   LATIN SMALL LETTER L WITH STROKE */
   U_LatinCapitalLetterLWithCedilla,      /* 0xB9   0x013B   LATIN CAPITAL LETTER L WITH CEDILLA */
   U_LatinSmallLetterLWithCedilla,        /* 0xBA   0x013C   LATIN SMALL LETTER L WITH CEDILLA */
   U_LatinCapitalLetterLWithCaron,        /* 0xBB   0x013D   LATIN CAPITAL LETTER L WITH CARON */
   U_LatinSmallLetterLWithCaron,          /* 0xBC   0x013E   LATIN SMALL LETTER L WITH CARON */
   U_LatinCapitalLetterLWithAcute,        /* 0xBD   0x0139   LATIN CAPITAL LETTER L WITH ACUTE */
   U_LatinSmallLetterLWithAcute,          /* 0xBE   0x013A   LATIN SMALL LETTER L WITH ACUTE */
   U_LatinCapitalLetterNWithCedilla,      /* 0xBF   0x0145   LATIN CAPITAL LETTER N WITH CEDILLA */
   U_LatinSmallLetterNWithCedilla,        /* 0xC0   0x0146   LATIN SMALL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterNWithAcute,        /* 0xC1   0x0143   LATIN CAPITAL LETTER N WITH ACUTE */
   U_NotSign,                             /* 0xC2   0x00AC   NOT SIGN */
   U_SquareRoot,                          /* 0xC3   0x221A   SQUARE ROOT */
   U_LatinSmallLetterNWithAcute,          /* 0xC4   0x0144   LATIN SMALL LETTER N WITH ACUTE */
   U_LatinCapitalLetterNWithCaron,        /* 0xC5   0x0147   LATIN CAPITAL LETTER N WITH CARON */
   U_Increment,                           /* 0xC6   0x2206   INCREMENT */
   U_LeftPointingGuillemet,               /* 0xC7   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_RightPointingGuillemet,              /* 0xC8   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0xC9   0x2026   HORIZONTAL ELLIPSIS */
   U_NB_SP,                               /* 0xCA   0x00A0   NO-BREAK SPACE */
   U_LatinSmallLetterNWithCaron,          /* 0xCB   0x0148   LATIN SMALL LETTER N WITH CARON */
   U_LatinCapitalLetterOWithDoubleAcute,  /* 0xCC   0x0150   LATIN CAPITAL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterOWithTilde,        /* 0xCD   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinSmallLetterOWithDoubleAcute,    /* 0xCE   0x0151   LATIN SMALL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterOWithMacron,       /* 0xCF   0x014C   LATIN CAPITAL LETTER O WITH MACRON */
   U_EnDash,                              /* 0xD0   0x2013   EN DASH */
   U_EmDash,                              /* 0xD1   0x2014   EM DASH */
   U_LeftDoubleQuotationMark,             /* 0xD2   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0xD3   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_LeftSingleQuotationMark,             /* 0xD4   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0xD5   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_DivisionSign,                        /* 0xD6   0x00F7   DIVISION SIGN */
   U_Lozenge,                             /* 0xD7   0x25CA   LOZENGE */
   U_LatinSmallLetterOWithMacron,         /* 0xD8   0x014D   LATIN SMALL LETTER O WITH MACRON */
   U_LatinCapitalLetterRWithAcute,        /* 0xD9   0x0154   LATIN CAPITAL LETTER R WITH ACUTE */
   U_LatinSmallLetterRWithAcute,          /* 0xDA   0x0155   LATIN SMALL LETTER R WITH ACUTE */
   U_LatinCapitalLetterRWithCaron,        /* 0xDB   0x0158   LATIN CAPITAL LETTER R WITH CARON */
   U_LeftPointingSingleGuillemet,         /* 0xDC   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_RightPointingSingleGuillemet,        /* 0xDD   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinSmallLetterRWithCaron,          /* 0xDE   0x0159   LATIN SMALL LETTER R WITH CARON */
   U_LatinCapitalLetterRWithCedilla,      /* 0xDF   0x0156   LATIN CAPITAL LETTER R WITH CEDILLA */
   U_LatinSmallLetterRWithCedilla,        /* 0xE0   0x0157   LATIN SMALL LETTER R WITH CEDILLA */
   U_LatinCapitalLetterSWithCaron,        /* 0xE1   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_SingleLow9QuotationMark,             /* 0xE2   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_DoubleLow9QuotationMark,             /* 0xE3   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_LatinSmallLetterSWithCaron,          /* 0xE4   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinCapitalLetterSWithAcute,        /* 0xE5   0x015A   LATIN CAPITAL LETTER S WITH ACUTE */
   U_LatinSmallLetterSWithAcute,          /* 0xE6   0x015B   LATIN SMALL LETTER S WITH ACUTE */
   U_LatinCapitalLetterAWithAcute,        /* 0xE7   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterTWithCaron,        /* 0xE8   0x0164   LATIN CAPITAL LETTER T WITH CARON */
   U_LatinSmallLetterTWithCaron,          /* 0xE9   0x0165   LATIN SMALL LETTER T WITH CARON */
   U_LatinCapitalLetterIWithAcute,        /* 0xEA   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterZWithCaron,        /* 0xEB   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_LatinSmallLetterZWithCaron,          /* 0xEC   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_LatinCapitalLetterUWithMacron,       /* 0xED   0x016A   LATIN CAPITAL LETTER U WITH MACRON */
   U_LatinCapitalLetterOWithAcute,        /* 0xEE   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xEF   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinSmallLetterUWithMacron,         /* 0xF0   0x016B   LATIN SMALL LETTER U WITH MACRON */
   U_LatinCapitalLetterUWithRingAbove,    /* 0xF1   0x016E   LATIN CAPITAL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterUWithAcute,        /* 0xF2   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinSmallLetterUWithRingAbove,      /* 0xF3   0x016F   LATIN SMALL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterUWithDoubleAcute,  /* 0xF4   0x0170   LATIN CAPITAL LETTER U WITH DOUBLE ACUTE */
   U_LatinSmallLetterUWithDoubleAcute,    /* 0xF5   0x0171   LATIN SMALL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterUWithOgonek,       /* 0xF6   0x0172   LATIN CAPITAL LETTER U WITH OGONEK */
   U_LatinSmallLetterUWithOgonek,         /* 0xF7   0x0173   LATIN SMALL LETTER U WITH OGONEK */
   U_LatinCapitalLetterYWithAcute,        /* 0xF8   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinSmallLetterYWithAcute,          /* 0xF9   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinSmallLetterKWithCedilla,        /* 0xFA   0x0137   LATIN SMALL LETTER K WITH CEDILLA */
   U_LatinCapitalLetterZWithDotAbove,     /* 0xFB   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterLWithStroke,       /* 0xFC   0x0141   LATIN CAPITAL LETTER L WITH STROKE */
   U_LatinSmallLetterZWithDotAbove,       /* 0xFD   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterGWithCedilla,      /* 0xFE   0x0122   LATIN CAPITAL LETTER G WITH CEDILLA */
   U_Caron                                /* 0xFF   0x02C7   CARON */
};





/******************************************************************************
*
*  CODE_MAC_CE_lig[]:
*     list of ligatures:
*
*  CODE_MAC_CE_lig[0] is the original ligature character
*  CODE_MAC_CE_lig[1] + CODE_MAC_CE_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static _UWORD const CODE_MAC_CE_lig[][3] =     /* CODE_MAC_CE character ligatures */
{
   {0x00C4, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x80   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   {0x00D6, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x85   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   {0x00DC, U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x86   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   {0x00E4, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x8A   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   {0x00F6, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x9A   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   {0x00FC, U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x9F   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   {0x00DF, U_LatinCapitalLetterS, U_LatinCapitalLetterS},    /* 0xA7   0x00DF   LATIN SMALL LETTER SHARP S */

   {0x0000, U_NIL                , U_NIL}                     /* list terminator */
};





/******************************************************************************
*
*  CODE_MAC_CE sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static _UWORD const sort_CODE_MAC_CE[] =       /* CODE_MAC_CE */
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
   0x007f,                                /* 0x7F  --- UNDEFINED --- */

   U_LatinCapitalLetterA,                 /* 0x80   0x00C4   LATIN CAPITAL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0x81   0x0100   LATIN CAPITAL LETTER A WITH MACRON */
   U_LatinCapitalLetterA,                 /* 0x82   0x0101   LATIN SMALL LETTER A WITH MACRON */
   U_LatinCapitalLetterE,                 /* 0x83   0x00C9   LATIN CAPITAL LETTER E WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0x84   0x0104   LATIN CAPITAL LETTER A WITH OGONEK */
   U_LatinCapitalLetterO,                 /* 0x85   0x00D6   LATIN CAPITAL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterU,                 /* 0x86   0x00DC   LATIN CAPITAL LETTER U WITH DIAERESIS */
   U_LatinCapitalLetterA,                 /* 0x87   0x00E1   LATIN SMALL LETTER A WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0x88   0x0105   LATIN SMALL LETTER A WITH OGONEK */
   U_LatinCapitalLetterC,                 /* 0x89   0x010C   LATIN CAPITAL LETTER C WITH CARON */
   U_LatinCapitalLetterA,                 /* 0x8A   0x00E4   LATIN SMALL LETTER A WITH DIAERESIS */
   U_LatinCapitalLetterC,                 /* 0x8B   0x010D   LATIN SMALL LETTER C WITH CARON */
   U_LatinCapitalLetterC,                 /* 0x8C   0x0106   LATIN CAPITAL LETTER C WITH ACUTE */
   U_LatinCapitalLetterC,                 /* 0x8D   0x0107   LATIN SMALL LETTER C WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0x8E   0x00E9   LATIN SMALL LETTER E WITH ACUTE */
   U_LatinCapitalLetterZ,                 /* 0x8F   0x0179   LATIN CAPITAL LETTER Z WITH ACUTE */
   U_LatinCapitalLetterZ,                 /* 0x90   0x017A   LATIN SMALL LETTER Z WITH ACUTE */
   U_LatinCapitalLetterD,                 /* 0x91   0x010E   LATIN CAPITAL LETTER D WITH CARON */
   U_LatinCapitalLetterI,                 /* 0x92   0x00ED   LATIN SMALL LETTER I WITH ACUTE */
   U_LatinCapitalLetterD,                 /* 0x93   0x010F   LATIN SMALL LETTER D WITH CARON */
   U_LatinCapitalLetterE,                 /* 0x94   0x0112   LATIN CAPITAL LETTER E WITH MACRON */
   U_LatinCapitalLetterE,                 /* 0x95   0x0113   LATIN SMALL LETTER E WITH MACRON */
   U_LatinCapitalLetterE,                 /* 0x96   0x0116   LATIN CAPITAL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterO,                 /* 0x97   0x00F3   LATIN SMALL LETTER O WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0x98   0x0117   LATIN SMALL LETTER E WITH DOT ABOVE */
   U_LatinCapitalLetterO,                 /* 0x99   0x00F4   LATIN SMALL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterO,                 /* 0x9A   0x00F6   LATIN SMALL LETTER O WITH DIAERESIS */
   U_LatinCapitalLetterO,                 /* 0x9B   0x00F5   LATIN SMALL LETTER O WITH TILDE */
   U_LatinCapitalLetterU,                 /* 0x9C   0x00FA   LATIN SMALL LETTER U WITH ACUTE */
   U_LatinCapitalLetterE,                 /* 0x9D   0x011A   LATIN CAPITAL LETTER E WITH CARON */
   U_LatinCapitalLetterE,                 /* 0x9E   0x011B   LATIN SMALL LETTER E WITH CARON */
   U_LatinCapitalLetterU,                 /* 0x9F   0x00FC   LATIN SMALL LETTER U WITH DIAERESIS */
   U_Dagger,                              /* 0xA0   0x2020   DAGGER */
   U_DegreeSign,                          /* 0xA1   0x00B0   DEGREE SIGN */
   U_LatinCapitalLetterE,                 /* 0xA2   0x0118   LATIN CAPITAL LETTER E WITH OGONEK */
   U_PoundSign,                           /* 0xA3   0x00A3   POUND SIGN */
   U_SectionSign,                         /* 0xA4   0x00A7   SECTION SIGN */
   U_Bullet,                              /* 0xA5   0x2022   BULLET */
   U_ParagraphSign,                       /* 0xA6   0x00B6   PILCROW SIGN */
   U_LatinCapitalLetterS,                 /* 0xA7   0x00DF   LATIN SMALL LETTER SHARP S */
   U_RegisteredSign,                      /* 0xA8   0x00AE   REGISTERED SIGN */
   U_CopyrightSign,                       /* 0xA9   0x00A9   COPYRIGHT SIGN */
   U_TradeMarkSign,                       /* 0xAA   0x2122   TRADE MARK SIGN */
   U_LatinCapitalLetterE,                 /* 0xAB   0x0119   LATIN SMALL LETTER E WITH OGONEK */
   U_Diaeresis,                           /* 0xAC   0x00A8   DIAERESIS */
   U_NotEqualTo,                          /* 0xAD   0x2260   NOT EQUAL TO */
   U_LatinCapitalLetterG,                 /* 0xAE   0x0123   LATIN SMALL LETTER G WITH CEDILLA */
   U_LatinCapitalLetterI,                 /* 0xAF   0x012E   LATIN CAPITAL LETTER I WITH OGONEK */
   U_LatinCapitalLetterI,                 /* 0xB0   0x012F   LATIN SMALL LETTER I WITH OGONEK */
   U_LatinCapitalLetterI,                 /* 0xB1   0x012A   LATIN CAPITAL LETTER I WITH MACRON */
   U_LessThanOrEqualTo,                   /* 0xB2   0x2264   LESS-THAN OR EQUAL TO */
   U_GreaterThanOrEqualTo,                /* 0xB3   0x2265   GREATER-THAN OR EQUAL TO */
   U_LatinCapitalLetterI,                 /* 0xB4   0x012B   LATIN SMALL LETTER I WITH MACRON */
   U_LatinCapitalLetterK,                 /* 0xB5   0x0136   LATIN CAPITAL LETTER K WITH CEDILLA */
   U_PartialDifferential,                 /* 0xB6   0x2202   PARTIAL DIFFERENTIAL */
   U_NArySummation,                       /* 0xB7   0x2211   N-ARY SUMMATION */
   U_LatinCapitalLetterL,                 /* 0xB8   0x0142   LATIN SMALL LETTER L WITH STROKE */
   U_LatinCapitalLetterL,                 /* 0xB9   0x013B   LATIN CAPITAL LETTER L WITH CEDILLA */
   U_LatinCapitalLetterL,                 /* 0xBA   0x013C   LATIN SMALL LETTER L WITH CEDILLA */
   U_LatinCapitalLetterL,                 /* 0xBB   0x013D   LATIN CAPITAL LETTER L WITH CARON */
   U_LatinCapitalLetterL,                 /* 0xBC   0x013E   LATIN SMALL LETTER L WITH CARON */
   U_LatinCapitalLetterL,                 /* 0xBD   0x0139   LATIN CAPITAL LETTER L WITH ACUTE */
   U_LatinCapitalLetterL,                 /* 0xBE   0x013A   LATIN SMALL LETTER L WITH ACUTE */
   U_LatinCapitalLetterN,                 /* 0xBF   0x0145   LATIN CAPITAL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterN,                 /* 0xC0   0x0146   LATIN SMALL LETTER N WITH CEDILLA */
   U_LatinCapitalLetterN,                 /* 0xC1   0x0143   LATIN CAPITAL LETTER N WITH ACUTE */
   U_NotSign,                             /* 0xC2   0x00AC   NOT SIGN */
   U_SquareRoot,                          /* 0xC3   0x221A   SQUARE ROOT */
   U_LatinCapitalLetterN,                 /* 0xC4   0x0144   LATIN SMALL LETTER N WITH ACUTE */
   U_LatinCapitalLetterN,                 /* 0xC5   0x0147   LATIN CAPITAL LETTER N WITH CARON */
   U_Increment,                           /* 0xC6   0x2206   INCREMENT */
   U_LeftPointingGuillemet,               /* 0xC7   0x00AB   LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_RightPointingGuillemet,              /* 0xC8   0x00BB   RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
   U_HorizontalEllipsis,                  /* 0xC9   0x2026   HORIZONTAL ELLIPSIS */
   U_NB_SP,                               /* 0xCA   0x00A0   NO-BREAK SPACE */
   U_LatinCapitalLetterN,                 /* 0xCB   0x0148   LATIN SMALL LETTER N WITH CARON */
   U_LatinCapitalLetterO,                 /* 0xCC   0x0150   LATIN CAPITAL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterO,                 /* 0xCD   0x00D5   LATIN CAPITAL LETTER O WITH TILDE */
   U_LatinCapitalLetterO,                 /* 0xCE   0x0151   LATIN SMALL LETTER O WITH DOUBLE ACUTE */
   U_LatinCapitalLetterO,                 /* 0xCF   0x014C   LATIN CAPITAL LETTER O WITH MACRON */
   U_EnDash,                              /* 0xD0   0x2013   EN DASH */
   U_EmDash,                              /* 0xD1   0x2014   EM DASH */
   U_LeftDoubleQuotationMark,             /* 0xD2   0x201C   LEFT DOUBLE QUOTATION MARK */
   U_RightDoubleQuotationMark,            /* 0xD3   0x201D   RIGHT DOUBLE QUOTATION MARK */
   U_LeftSingleQuotationMark,             /* 0xD4   0x2018   LEFT SINGLE QUOTATION MARK */
   U_RightSingleQuotationMark,            /* 0xD5   0x2019   RIGHT SINGLE QUOTATION MARK */
   U_DivisionSign,                        /* 0xD6   0x00F7   DIVISION SIGN */
   U_Lozenge,                             /* 0xD7   0x25CA   LOZENGE */
   U_LatinCapitalLetterO,                 /* 0xD8   0x014D   LATIN SMALL LETTER O WITH MACRON */
   U_LatinCapitalLetterR,                 /* 0xD9   0x0154   LATIN CAPITAL LETTER R WITH ACUTE */
   U_LatinCapitalLetterR,                 /* 0xDA   0x0155   LATIN SMALL LETTER R WITH ACUTE */
   U_LatinCapitalLetterR,                 /* 0xDB   0x0158   LATIN CAPITAL LETTER R WITH CARON */
   U_LeftPointingSingleGuillemet,         /* 0xDC   0x2039   SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
   U_RightPointingSingleGuillemet,        /* 0xDD   0x203A   SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
   U_LatinCapitalLetterR,                 /* 0xDE   0x0159   LATIN SMALL LETTER R WITH CARON */
   U_LatinCapitalLetterR,                 /* 0xDF   0x0156   LATIN CAPITAL LETTER R WITH CEDILLA */
   U_LatinCapitalLetterR,                 /* 0xE0   0x0157   LATIN SMALL LETTER R WITH CEDILLA */
   U_LatinCapitalLetterS,                 /* 0xE1   0x0160   LATIN CAPITAL LETTER S WITH CARON */
   U_SingleLow9QuotationMark,             /* 0xE2   0x201A   SINGLE LOW-9 QUOTATION MARK */
   U_DoubleLow9QuotationMark,             /* 0xE3   0x201E   DOUBLE LOW-9 QUOTATION MARK */
   U_LatinCapitalLetterS,                 /* 0xE4   0x0161   LATIN SMALL LETTER S WITH CARON */
   U_LatinCapitalLetterS,                 /* 0xE5   0x015A   LATIN CAPITAL LETTER S WITH ACUTE */
   U_LatinCapitalLetterS,                 /* 0xE6   0x015B   LATIN SMALL LETTER S WITH ACUTE */
   U_LatinCapitalLetterA,                 /* 0xE7   0x00C1   LATIN CAPITAL LETTER A WITH ACUTE */
   U_LatinCapitalLetterT,                 /* 0xE8   0x0164   LATIN CAPITAL LETTER T WITH CARON */
   U_LatinCapitalLetterT,                 /* 0xE9   0x0165   LATIN SMALL LETTER T WITH CARON */
   U_LatinCapitalLetterI,                 /* 0xEA   0x00CD   LATIN CAPITAL LETTER I WITH ACUTE */
   U_LatinCapitalLetterZ,                 /* 0xEB   0x017D   LATIN CAPITAL LETTER Z WITH CARON */
   U_LatinCapitalLetterZ,                 /* 0xEC   0x017E   LATIN SMALL LETTER Z WITH CARON */
   U_LatinCapitalLetterU,                 /* 0xED   0x016A   LATIN CAPITAL LETTER U WITH MACRON */
   U_LatinCapitalLetterO,                 /* 0xEE   0x00D3   LATIN CAPITAL LETTER O WITH ACUTE */
   U_LatinCapitalLetterO,                 /* 0xEF   0x00D4   LATIN CAPITAL LETTER O WITH CIRCUMFLEX */
   U_LatinCapitalLetterU,                 /* 0xF0   0x016B   LATIN SMALL LETTER U WITH MACRON */
   U_LatinCapitalLetterU,                 /* 0xF1   0x016E   LATIN CAPITAL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterU,                 /* 0xF2   0x00DA   LATIN CAPITAL LETTER U WITH ACUTE */
   U_LatinCapitalLetterU,                 /* 0xF3   0x016F   LATIN SMALL LETTER U WITH RING ABOVE */
   U_LatinCapitalLetterU,                 /* 0xF4   0x0170   LATIN CAPITAL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterU,                 /* 0xF5   0x0171   LATIN SMALL LETTER U WITH DOUBLE ACUTE */
   U_LatinCapitalLetterU,                 /* 0xF6   0x0172   LATIN CAPITAL LETTER U WITH OGONEK */
   U_LatinCapitalLetterU,                 /* 0xF7   0x0173   LATIN SMALL LETTER U WITH OGONEK */
   U_LatinCapitalLetterY,                 /* 0xF8   0x00DD   LATIN CAPITAL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterY,                 /* 0xF9   0x00FD   LATIN SMALL LETTER Y WITH ACUTE */
   U_LatinCapitalLetterK,                 /* 0xFA   0x0137   LATIN SMALL LETTER K WITH CEDILLA */
   U_LatinCapitalLetterZ,                 /* 0xFB   0x017B   LATIN CAPITAL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterL,                 /* 0xFC   0x0141   LATIN CAPITAL LETTER L WITH STROKE */
   U_LatinCapitalLetterZ,                 /* 0xFD   0x017C   LATIN SMALL LETTER Z WITH DOT ABOVE */
   U_LatinCapitalLetterG,                 /* 0xFE   0x0122   LATIN CAPITAL LETTER G WITH CEDILLA */
   U_Caron                                /* 0xFF   0x02C7   CARON */
};
