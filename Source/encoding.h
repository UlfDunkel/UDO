/*******************************************************************************
*
*  Project name : UDO
*  Module name  : encoding.h
*  Symbol prefix: encoding
*
*  Open Source  : since 2010
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
*  Description  : sorting tables for all supported encodings
*
*                 The tables have a size of 256 size_t slots. Each of these slots
*                 corresponds to the relevant ANSI character value, while the table 
*                 slots may contain the Unicode of another characte value.
*                 These assigned Unicode characters will be used for index sorting.
*
*  Redundance   : In fact, the first 128 characters from Unicode 0x0001 to 0x007f
*                 should always be identical, as they represent the basic ASCII set.
*                 The defined sorting tables might only contain the High ASCII sets,
*                 but the additional offset calculations may slow down the sorting.
*
*  Example      : sort_CODE_LAT1[0xd1] = U_LatinCapitalLetterN;
*
*                 The original Latin1 character at 0xd1 is U_LatinCapitalLetterNWithTilde
*                 (as indicated in the source comment).
*
*                 Each U_LatinCapitalLetterNWithTilde character will be sorted 
*                 as if it was a U_LatinCapitalLetterN character instead.
*                 
*  Implemented  : - sort_CODE_LAT1[] for CODE_LAT1 (0)
*                 - sort_CODE_TOS[]  for CODE_TOS  (2)
*                 - sort_CODE_MAC[]  for CODE_MAC  (4)
*
*-------------------------------------------------------------------------------
*
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - support all encodings
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Jan 25: file introduced
*    fd  Feb 09: tables changed from size_t to unsigned (int)
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "unicode.h"                      /* Unicode character names */




/******************************************************************************
*
*  CODE_LAT1_lig[]:
*     list of ligatures:
*
*  CODE_LAT1_lig[0] is the original ligature character
*  CODE_LAT1_lig[1] + CODE_LAT1_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static unsigned   CODE_LAT1_lig[][3] =    /* CODE_LAT1 character ligatures */
{
   {0x008c, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x008c  U_LatinCapitalLigatureOE */
   {0x009c, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x009c  U_LatinSmallLigatureOE */
   {0x009f, U_LatinCapitalLetterY, U_LatinCapitalLetterE},    /* 0x009f  U_LatinCapitalLetterYWithDiaeresis */
   {0x00c4, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00c4  U_LatinCapitalLetterAWithDiaeresis */
   {0x00c6, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00c6  U_LatinCapitalLigatureAE */
   {0x00cb, U_LatinCapitalLetterE, U_LatinCapitalLetterE},    /* 0x00cb  U_LatinCapitalLetterEWithDiaeresis */
   {0x00cf, U_LatinCapitalLetterI, U_LatinCapitalLetterE},    /* 0x00cf  U_LatinCapitalLetterIWithDiaeresis */
   {0x00d6, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00d6  U_LatinCapitalLetterOWithDiaeresis */
   {0x00d8, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00d8  U_LatinCapitalLetterOSlash */
   {0x00dc, U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x00dc  U_LatinCapitalLetterUWithDiaeresis */
   {0x00df, U_LatinCapitalLetterS, U_LatinCapitalLetterS},    /* 0x00df  U_LatinSmallLetterSharpS */
   {0x00e4, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00e4  U_LatinSmallLetterAWithDiaeresis */
   {0x00e6, U_LatinCapitalLetterA, U_LatinCapitalLetterE},    /* 0x00e6  U_LatinSmallLigatureAE */
   {0x00eb, U_LatinCapitalLetterE, U_LatinCapitalLetterE},    /* 0x00eb  U_LatinSmallLetterEWithDiaeresis */
   {0x00ef, U_LatinCapitalLetterI, U_LatinCapitalLetterE},    /* 0x00ef  U_LatinSmallLetterIWithDiaeresis */
   {0x00f6, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00f6  U_LatinSmallLetterOWithDiaeresis */
   {0x00f8, U_LatinCapitalLetterO, U_LatinCapitalLetterE},    /* 0x00f8  U_LatinSmallLetterOSlash */
   {0x00fc, U_LatinCapitalLetterU, U_LatinCapitalLetterE},    /* 0x00fc  U_LatinSmallLetterUWithDiaeresis */
   {0x00ff, U_LatinCapitalLetterY, U_LatinCapitalLetterE},    /* 0x00ff  U_LatinSmallLetterYWithDiaeresis */
   {0x0000, U_NIL                , U_NIL}                     /* list terminator */
};





/******************************************************************************
*
*  CODE_LAT1 sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static unsigned   sort_CODE_LAT1[] =      /* CODE_LAT1 */
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

   0x0080,                                /* 0x80  U_EuroSign */
   0x0081,                                /* 0x81  --- UNDEFINED --- */
   0x0082,                                /* 0x82  U_SingleLow9QuotationMark */
   U_LatinCapitalLetterF,                 /* 0x83  U_LatinSmallLetterScriptF */
   0x0084,                                /* 0x84  U_DoubleLow9QuotationMark */
   0x0085,                                /* 0x85  U_HorizontalEllipsis */
   0x0086,                                /* 0x86  U_Dagger */
   0x0087,                                /* 0x87  U_DoubleDagger */
   0x0088,                                /* 0x88  U_ModifierLetterCircumflexAccent */
   0x0089,                                /* 0x89  U_PerMilleSign */
   U_LatinCapitalLetterE,                 /* 0x8a  U_LatinCapitalLetterSWithCaron */
   0x008b,                                /* 0x8b  U_LeftPointingSingleGuillemet */
   U_LatinCapitalLetterO,                 /* 0x8c  U_LatinCapitalLigatureOE */
   0x008d,                                /* 0x8d  --- UNDEFINED --- */
   U_LatinCapitalLetterZ,                 /* 0x8e  U_LatinCapitalLetterZWithCaron */
   0x008f,                                /* 0x8f  --- UNDEFINED --- */
                                          
   0x0090,                                /* 0x90  --- UNDEFINED --- */
   0x0091,                                /* 0x91  U_LeftSingleQuotationMark */
   0x0092,                                /* 0x92  U_RightSingleQuotationMark */
   0x0093,                                /* 0x93  U_LeftDoubleQuotationMark */
   0x0094,                                /* 0x94  U_RightDoubleQuotationMark */
   0x0095,                                /* 0x95  U_Bullet */
   0x0096,                                /* 0x96  U_EnDash */
   0x0097,                                /* 0x97  U_EmDash */
   0x0098,                                /* 0x98  U_SmallTilde */
   0x0099,                                /* 0x99  U_TradeMarkSign */
   U_LatinCapitalLetterS,                 /* 0x9a  U_LatinSmallLetterSWithCaron */
   0x009b,                                /* 0x9b  U_RightPointingSingleGuillemet */
   U_LatinCapitalLetterO,                 /* 0x9c  U_LatinSmallLigatureOE */
   0x009d,                                /* 0x9d  --- UNDEFINED --- */
   U_LatinCapitalLetterZ,                 /* 0x9e  U_LatinSmallLetterZWithCaron */
   U_LatinCapitalLetterY,                 /* 0x9f  U_LatinCapitalLetterYWithDiaeresis */
                                          
   U_SP,                                  /* 0xa0  U_NB_SP */
   U_ExclamationMark,                     /* 0xa1  U_InvertedExclamationMark */
   0x00a2,                                /* 0xa2  U_CentSign */
   0x00a3,                                /* 0xa3  U_PoundSign */
   0x00a4,                                /* 0xa4  U_CurrencySign */
   0x00a5,                                /* 0xa5  U_YenSign */
   0x00a6,                                /* 0xa6  U_BrokenVerticalBar */
   0x00a7,                                /* 0xa7  U_SectionSign */
   0x00a8,                                /* 0xa8  U_Diaeresis */
   0x00a9,                                /* 0xa9  U_CopyrightSign */
   0x00aa,                                /* 0xaa  U_FeminineOrdinalIndicator */
   0x00ab,                                /* 0xab  U_LeftPointingGuillemet */
   0x00ac,                                /* 0xac  U_NotSign */
   U_HyphenMinus,                         /* 0xad  U_SoftHyphen */
   0x00ae,                                /* 0xae  U_RegisteredSign */
   0x00af,                                /* 0xaf  U_Macron */
   
   0x00b0,                                /* 0xb0  U_DegreeSign */
   0x00b1,                                /* 0xb1  U_PlusMinusSign */
   0x00b2,                                /* 0xb2  U_SuperscriptTwo */
   0x00b3,                                /* 0xb3  U_SuperscriptThree */
   0x00b4,                                /* 0xb4  U_AcuteAccent */
   0x00b5,                                /* 0xb5  U_MicroSign */
   0x00b6,                                /* 0xb6  U_ParagraphSign */
   0x00b7,                                /* 0xb7  U_MiddleDot */
   0x00b8,                                /* 0xb8  U_Cedilla */
   0x00b9,                                /* 0xb9  U_SuperscriptOne */
   0x00ba,                                /* 0xba  U_MasculineOrdinalIndicator */
   0x00bb,                                /* 0xbb  U_RightPointingGuillemet */
   0x00bc,                                /* 0xbc  U_VulgarFractionOneQuarter */
   0x00bd,                                /* 0xbd  U_VulgarFractionOneHalf */
   0x00be,                                /* 0xbe  U_VulgarFractionThreeQuarters */
   0x00bf,                                /* 0xbf  U_InvertedQuestionMark */
                                          
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
                                          
   0x00d0,                                /* 0xd0  U_LatinCapitalLetterEth */
   U_LatinCapitalLetterN,                 /* 0xd1  U_LatinCapitalLetterNWithTilde */
   U_LatinCapitalLetterO,                 /* 0xd2  U_LatinCapitalLetterOWithGrave */
   U_LatinCapitalLetterO,                 /* 0xd3  U_LatinCapitalLetterOWithAcute */
   U_LatinCapitalLetterO,                 /* 0xd4  U_LatinCapitalLetterOWithCircumflex */
   U_LatinCapitalLetterO,                 /* 0xd5  U_LatinCapitalLetterOWithTilde */
   U_LatinCapitalLetterO,                 /* 0xd6  U_LatinCapitalLetterOWithDiaeresis */
   0x00d7,                                /* 0xd7  U_MultiplicationSign */
   U_LatinCapitalLetterO,                 /* 0xd8  U_LatinCapitalLetterOSlash */
   U_LatinCapitalLetterU,                 /* 0xd9  U_LatinCapitalLetterUWithGrave */
   U_LatinCapitalLetterU,                 /* 0xda  U_LatinCapitalLetterUWithAcute */
   U_LatinCapitalLetterU,                 /* 0xdb  U_LatinCapitalLetterUWithCircumflex */
   U_LatinCapitalLetterU,                 /* 0xdc  U_LatinCapitalLetterUWithDiaeresis */
   U_LatinCapitalLetterY,                 /* 0xdd  U_LatinCapitalLetterYWithAcute */
   0x00de,                                /* 0xde  U_LatinCapitalLetterThorn */
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
                                          
   0x00f0,                                /* 0xf0  U_LatinSmallLetterEth */
   U_LatinCapitalLetterN,                 /* 0xf1  U_LatinSmallLetterNWithTilde */
   U_LatinCapitalLetterO,                 /* 0xf2  U_LatinSmallLetterOWithGrave */
   U_LatinCapitalLetterO,                 /* 0xf3  U_LatinSmallLetterOWithAcute */
   U_LatinCapitalLetterO,                 /* 0xf4  U_LatinSmallLetterOWithCircumflex */
   U_LatinCapitalLetterO,                 /* 0xf5  U_LatinSmallLetterOWithTilde */
   U_LatinCapitalLetterO,                 /* 0xf6  U_LatinSmallLetterOWithDiaeresis */
   0x00f7,                                /* 0xf7  U_DivisionSign */
   U_LatinCapitalLetterO,                 /* 0xf8  U_LatinSmallLetterOSlash */
   U_LatinCapitalLetterU,                 /* 0xf9  U_LatinSmallLetterUWithGrave */
   U_LatinCapitalLetterU,                 /* 0xfa  U_LatinSmallLetterUWithAcute */
   U_LatinCapitalLetterU,                 /* 0xfb  U_LatinSmallLetterUWithCircumflex */
   U_LatinCapitalLetterU,                 /* 0xfc  U_LatinSmallLetterUWithDiaeresis */
   U_LatinCapitalLetterY,                 /* 0xfd  U_LatinSmallLetterYWithAcute */
   0x00fe,                                /* 0xfe  U_LatinSmallLetterThorn */
   U_LatinCapitalLetterY                  /* 0xff  U_LatinSmallLetterYWithDiaeresis */
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

static unsigned   CODE_TOS_lig[][3] =     /* CODE_TOS character ligatures */
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

static unsigned   sort_CODE_TOS[] =       /* CODE_TOS */
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










/******************************************************************************
*
*  CODE_MAC_lig[]:
*     list of ligatures:
*
*  CODE_MAC_lig[0] is the original ligature character
*  CODE_MAC_lig[1] + CODE_MAC_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static unsigned   CODE_MAC_lig[][3] =     /* CODE_MAC character ligatures */
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

static unsigned   sort_CODE_MAC[] =       /* CODE_MAC */
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
                                          
   0x00a0,                                /* 0xa0  U_Dagger */
   0x00a0,                                /* 0xa1  U_DegreeSign */
   0x00a2,                                /* 0xa2  U_CentSign */
   0x00a3,                                /* 0xa3  U_PoundSign */
   0x00a4,                                /* 0xa4  U_SectionSign */
   0x00a5,                                /* 0xa5  U_Bullet */
   0x00a6,                                /* 0xa6  U_ParagraphSign */
   U_LatinCapitalLetterS,                 /* 0xa7  U_LatinSmallLetterSharpS */
   0x00a8,                                /* 0xa8  U_RegisteredSign */
   0x00a9,                                /* 0xa9  U_CopyrightSign */
   0x00aa,                                /* 0xaa  U_TradeMarkSign */
   0x00ab,                                /* 0xab  U_AcuteAccent */
   0x00ac,                                /* 0xac  U_Diaeresis */
   0x00ad,                                /* 0xad  U_NotEqualTo */
   U_LatinCapitalLetterA,                 /* 0xae  U_LatinCapitalLigatureAE */
   U_LatinCapitalLetterO,                 /* 0xaf  U_LatinCapitalLetterOSlash */
   
   0x00b0,                                /* 0xb0  U_Infinity */
   0x00b1,                                /* 0xb1  U_PlusMinusSign */
   0x00b2,                                /* 0xb2  U_LessThanOrEqualTo */
   0x00b3,                                /* 0xb3  U_GreaterThanOrEqualTo */
   0x00b4,                                /* 0xb4  U_YenSign */
   0x00b5,                                /* 0xb5  U_MicroSign */
   0x00b6,                                /* 0xb6  U_PartialDifferential */
   0x00b7,                                /* 0xb7  U_NArySummation */
   0x00b8,                                /* 0xb8  U_NAryProduct */
   0x00b9,                                /* 0xb9  U_GreekSmallLetterPi */
   0x00ba,                                /* 0xba  U_Integral */
   0x00bb,                                /* 0xbb  U_FeminineOrdinalIndicator */
   0x00bc,                                /* 0xbc  U_MasculineOrdinalIndicator */
   0x00bd,                                /* 0xbd  U_GreekCapitalLetterOmega */
   U_LatinCapitalLetterA,                 /* 0xbe  U_LatinSmallLigatureAE */
   U_LatinCapitalLetterO,                 /* 0xbf  U_LatinSmallLetterOSlash */
                                          
   U_QuestionMark,                        /* 0xc0  U_InvertedQuestionMark */
   U_ExclamationMark,                     /* 0xc1  U_InvertedExclamationMark */
   0x00c2,                                /* 0xc2  U_NotSign */
   0x00c2,                                /* 0xc3  U_SquareRoot */
   U_LatinCapitalLetterF,                 /* 0xc4  U_LatinSmallLetterScriptF */
   0x00c2,                                /* 0xc5  U_AlmostEqualTo */
   0x00c2,                                /* 0xc6  U_Increment */
   0x00c2,                                /* 0xc7  U_LeftPointingGuillemet */
   0x00c2,                                /* 0xc8  U_RightPointingGuillemet */
   0x00c2,                                /* 0xc9  U_HorizontalEllipsis */
   U_SP,                                  /* 0xca  U_NB_SP */
   U_LatinCapitalLetterA,                 /* 0xcb  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterA,                 /* 0xcc  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterO,                 /* 0xcd  U_LatinCapitalLetterOWithTilde */
   U_LatinCapitalLetterO,                 /* 0xce  U_LatinCapitalLigatureOE */
   U_LatinCapitalLetterO,                 /* 0xcf  U_LatinSmallLigatureOE */
                                          
   0x00d0,                                /* 0xd0  U_EnDash */
   0x00d1,                                /* 0xd1  U_EmDash */
   0x00d2,                                /* 0xd2  U_LeftDoubleQuotationMark */
   0x00d3,                                /* 0xd3  U_RightDoubleQuotationMark */
   0x00d4,                                /* 0xd4  U_LeftSingleQuotationMark */
   0x00d5,                                /* 0xd5  U_RightSingleQuotationMark */
   0x00d6,                                /* 0xd6  U_DivisionSign */
   0x00d7,                                /* 0xd7  U_Lozenge */
   U_LatinCapitalLetterY,                 /* 0xd8  U_LatinSmallLetterYWithDiaeresis */
   U_LatinCapitalLetterY,                 /* 0xd9  U_LatinCapitalLetterYWithDiaeresis */
   0x00da,                                /* 0xda  U_FractionSlash */
   0x00db,                                /* 0xdb  U_EuroSign */
   0x00dc,                                /* 0xdc  U_LeftPointingSingleGuillemet */
   0x00dd,                                /* 0xdd  U_RightPointingSingleGuillemet */
   U_LatinCapitalLetterF,                 /* 0xde  U_LatinSmallLigatureFI */
   U_LatinCapitalLetterF,                 /* 0xdf  U_LatinSmallLigatureFL */
                                          
   0x00e0,                                /* 0xe0  U_DoubleDagger */
   0x00e1,                                /* 0xe1  U_MiddleDot */
   0x00e2,                                /* 0xe2  U_SingleLow9QuotationMark */
   0x00e3,                                /* 0xe3  U_DoubleLow9QuotationMark */
   0x00e4,                                /* 0xe4  U_PerMilleSign */
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
                                          
   0x00f0,                                /* 0xf0  -- (Apple logo: ) -- */
   U_LatinCapitalLetterO,                 /* 0xf1  U_LatinCapitalLetterOWithGrave */
   U_LatinCapitalLetterU,                 /* 0xf2  U_LatinCapitalLetterUWithAcute */
   U_LatinCapitalLetterU,                 /* 0xf3  U_LatinCapitalLetterUWithCircumflex */
   U_LatinCapitalLetterU,                 /* 0xf4  U_LatinCapitalLetterUWithGrave */
   U_LatinCapitalLetterI,                 /* 0xf5  U_LatinSmallLetterDotlessI */
   0x00f6,                                /* 0xf6  U_ModifierLetterCircumflexAccent */
   0x00f7,                                /* 0xf7  U_SmallTilde */
   0x00f8,                                /* 0xf8  U_Macron */
   0x00f9,                                /* 0xf9  U_Breve */
   0x00fa,                                /* 0xfa  U_DotAbove */
   0x00fb,                                /* 0xfb  U_RingAbove */
   0x00fc,                                /* 0xfc  U_Cedilla */
   0x00fd,                                /* 0xfd  U_DoubleAcuteAccent */
   0x00fe,                                /* 0xfe  U_Ogonek */
   0x00ff                                 /* 0xff  U_Caron */
};


/* +++ EOF +++ */
