/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_utf.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepage for UTF encoding
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
*    fd  Feb 18: file introduced
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
*  CODE_UTF_lig[]:
*     list of ligatures:
*
*  CODE_UTF_lig[0] is the original ligature character
*  CODE_UTF_lig[1] + CODE_UTF_lig[2] are the resolved ligature characters
*
******************************************|************************************/

static unsigned   CODE_UTF_lig[][3] =     /* CODE_UTF character ligatures */
{
   { U_LatinCapitalLetterAWithDiaeresis,          U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0x00C4 */
   { U_LatinCapitalLetterAWithRingAbove,          U_LatinCapitalLetterA, U_LatinCapitalLetterO },  /* 0x00C5 */
   { U_LatinCapitalLigatureAE,                    U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0x00C6 */
   { U_LatinCapitalLetterEWithDiaeresis,          U_LatinCapitalLetterE, U_LatinCapitalLetterE },  /* 0x00CB */
   { U_LatinCapitalLetterIWithDiaeresis,          U_LatinCapitalLetterI, U_LatinCapitalLetterE },  /* 0x00CF */
   { U_LatinCapitalLetterOWithDiaeresis,          U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0x00D6 */
   { U_LatinCapitalLetterOSlash,                  U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0x00D8 */
   { U_LatinCapitalLetterUWithDiaeresis,          U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0x00DC */
   { U_LatinSmallLetterSharpS,                    U_LatinSmallLetterS,   U_LatinSmallLetterS   },  /* 0x00DF */
   { U_LatinSmallLetterAWithDiaeresis,            U_LatinSmallLetterA,   U_LatinSmallLetterE   },  /* 0x00E4 */
   { U_LatinSmallLetterAWithRingAbove,            U_LatinSmallLetterA,   U_LatinSmallLetterO   },  /* 0x00E5 */
   { U_LatinSmallLigatureAE,                      U_LatinSmallLetterA,   U_LatinSmallLetterE   },  /* 0x00E6 */
   { U_LatinSmallLetterEWithDiaeresis,            U_LatinSmallLetterE,   U_LatinSmallLetterE   },  /* 0x00EB */
   { U_LatinSmallLetterIWithDiaeresis,            U_LatinSmallLetterI,   U_LatinSmallLetterE   },  /* 0x00EF */
   { U_LatinSmallLetterOWithDiaeresis,            U_LatinSmallLetterO,   U_LatinSmallLetterE   },  /* 0x00F6 */
   { U_LatinSmallLetterOSlash,                    U_LatinSmallLetterO,   U_LatinSmallLetterE   },  /* 0x00F8 */
   { U_LatinSmallLetterUWithDiaeresis,            U_LatinSmallLetterU,   U_LatinSmallLetterE   },  /* 0x00FC */
   { U_LatinSmallLetterYWithDiaeresis,            U_LatinSmallLetterY,   U_LatinSmallLetterE   },  /* 0x00FF */
   { U_LatinCapitalLigatureIJ,                    U_LatinCapitalLetterI, U_LatinCapitalLetterJ },  /* 0x0132 */
   { U_LatinSmallLigatureIJ,                      U_LatinSmallLetterI,   U_LatinSmallLetterJ   },  /* 0x0133 */
   { U_LatinCapitalLigatureOE,                    U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0x0152 */
   { U_LatinSmallLigatureOE,                      U_LatinSmallLetterO,   U_LatinSmallLetterE   },  /* 0x0153 */
   { U_LatinCapitalLetterUWithRingAbove,          U_LatinCapitalLetterU, U_LatinCapitalLetterO },  /* 0x016E */
   { U_LatinSmallLetterUWithRingAbove,            U_LatinSmallLetterU,   U_LatinSmallLetterO   },  /* 0x016F */
   { U_LatinCapitalLetterYWithDiaeresis,          U_LatinCapitalLetterY, U_LatinCapitalLetterE },  /* 0x0178 */
   { U_LatinSmallLetterHV,                        U_LatinSmallLetterH,   U_LatinSmallLetterV   },  /* 0x0195 */
   { U_LatinCapitalLetterOI,                      U_LatinCapitalLetterO, U_LatinCapitalLetterI },  /* 0x01A2 */
   { U_LatinSmallLetterOI,                        U_LatinSmallLetterO,   U_LatinSmallLetterI   },  /* 0x01A3 */
   { U_LatinLetterYR,                             U_LatinSmallLetterY,   U_LatinCapitalLetterR },  /* 0x01A6 */
   { U_LatinCapitalLetterLJ,                      U_LatinCapitalLetterL, U_LatinCapitalLetterJ },  /* 0x01C7 */
   { U_LatinCapitalLetterLWithSmallLetterJ,       U_LatinCapitalLetterL, U_LatinSmallLetterJ   },  /* 0x01C8 */
   { U_LatinSmallLetterLJ,                        U_LatinSmallLetterL,   U_LatinSmallLetterJ   },  /* 0x01C9 */
   { U_LatinCapitalLetterNJ,                      U_LatinCapitalLetterN, U_LatinCapitalLetterJ },  /* 0x01CA */
   { U_LatinCapitalLetterNWithSmallLetterJ,       U_LatinCapitalLetterN, U_LatinSmallLetterJ   },  /* 0x01CB */
   { U_LatinSmallLetterNJ,                        U_LatinSmallLetterN,   U_LatinSmallLetterJ   },  /* 0x01CC */
   { U_LatinCapitalLetterUWithDiaeresisAndMacron, U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0x01D5 */
   { U_LatinSmallLetterUWithDiaeresisAndMacron,   U_LatinSmallLetterU,   U_LatinSmallLetterE   },  /* 0x01D6 */
   { U_LatinCapitalLetterUWithDiaeresisAndCaron,  U_LatinCapitalLetterU, U_LatinCapitalLetterE },  /* 0x01D9 */
   { U_LatinSmallLetterUWithDiaeresisAndCaron,    U_LatinSmallLetterU,   U_LatinSmallLetterE   },  /* 0x01DA */
   { U_LatinCapitalLetterAWithDiaeresisAndMacron, U_LatinCapitalLetterA, U_LatinCapitalLetterE },  /* 0x01DE */
   { U_LatinSmallLetterAWithDiaeresisAndMacron,   U_LatinSmallLetterA,   U_LatinSmallLetterE   },  /* 0x01DF */
   { U_LatinCapitalLetterDZ,                      U_LatinCapitalLetterD, U_LatinCapitalLetterZ },  /* 0x01F1 */
   { U_LatinCapitalLetterDWithSmallLetterZ,       U_LatinCapitalLetterD, U_LatinSmallLetterZ   },  /* 0x01F2 */
   { U_LatinSmallLetterDZ,                        U_LatinSmallLetterD,   U_LatinSmallLetterZ   },  /* 0x01F3 */
   { U_LatinCapitalLetterOU,                      U_LatinCapitalLetterO, U_LatinCapitalLetterU },  /* 0x0222 */
   { U_LatinSmallLetterOU,                        U_LatinSmallLetterO,   U_LatinSmallLetterU   },  /* 0x0223 */
   { U_LatinCapitalLetterOWithDiaeresisAndMacron, U_LatinCapitalLetterO, U_LatinCapitalLetterE },  /* 0x022A */
   { U_LatinSmallLetterOWithDiaeresisAndMacron,   U_LatinSmallLetterO,   U_LatinSmallLetterE   },  /* 0x022B */
   { 0x0000,                                      U_NIL,                 U_NIL}                    /* list terminator */
};





/******************************************************************************
*
*  CODE_UTF sorting table:
*
*  table format: sortingCharacter, (ANSI hex value  |  Original character)
*  
*
******************************************|************************************/

static unsigned   sort_CODE_UTF[][2] =    /* CODE_UTF */
{
   { U_LatinCapitalLetterAWithGrave                , U_LatinCapitalLetterA }, /* 0x00C0 */
   { U_LatinCapitalLetterAWithAcute                , U_LatinCapitalLetterA }, /* 0x00C1 */
   { U_LatinCapitalLetterAWithCircumflex           , U_LatinCapitalLetterA }, /* 0x00C2 */
   { U_LatinCapitalLetterAWithTilde                , U_LatinCapitalLetterA }, /* 0x00C3 */
   { U_LatinCapitalLetterAWithDiaeresis            , U_LatinCapitalLetterA }, /* 0x00C4 */
   { U_LatinCapitalLetterAWithRingAbove            , U_LatinCapitalLetterA }, /* 0x00C5 */
   { U_LatinCapitalLigatureAE                      , U_LatinCapitalLetterA }, /* 0x00C6 */
   { U_LatinCapitalLetterCWithCedilla              , U_LatinCapitalLetterC }, /* 0x00C7 */
   { U_LatinCapitalLetterEWithGrave                , U_LatinCapitalLetterE }, /* 0x00C8 */
   { U_LatinCapitalLetterEWithAcute                , U_LatinCapitalLetterE }, /* 0x00C9 */
   { U_LatinCapitalLetterEWithCircumflex           , U_LatinCapitalLetterE }, /* 0x00CA */
   { U_LatinCapitalLetterEWithDiaeresis            , U_LatinCapitalLetterE }, /* 0x00CB */
   { U_LatinCapitalLetterIWithGrave                , U_LatinCapitalLetterI }, /* 0x00CC */
   { U_LatinCapitalLetterIWithAcute                , U_LatinCapitalLetterI }, /* 0x00CD */
   { U_LatinCapitalLetterIWithCircumflex           , U_LatinCapitalLetterI }, /* 0x00CE */
   { U_LatinCapitalLetterIWithDiaeresis            , U_LatinCapitalLetterI }, /* 0x00CF */
   { U_LatinCapitalLetterNWithTilde                , U_LatinCapitalLetterN }, /* 0x00D1 */
   { U_LatinCapitalLetterOWithGrave                , U_LatinCapitalLetterO }, /* 0x00D2 */
   { U_LatinCapitalLetterOWithAcute                , U_LatinCapitalLetterO }, /* 0x00D3 */
   { U_LatinCapitalLetterOWithCircumflex           , U_LatinCapitalLetterO }, /* 0x00D4 */
   { U_LatinCapitalLetterOWithTilde                , U_LatinCapitalLetterO }, /* 0x00D5 */
   { U_LatinCapitalLetterOWithDiaeresis            , U_LatinCapitalLetterO }, /* 0x00D6 */
   { U_LatinCapitalLetterOSlash                    , U_LatinCapitalLetterO }, /* 0x00D8 */
   { U_LatinCapitalLetterUWithGrave                , U_LatinCapitalLetterU }, /* 0x00D9 */
   { U_LatinCapitalLetterUWithAcute                , U_LatinCapitalLetterU }, /* 0x00DA */
   { U_LatinCapitalLetterUWithCircumflex           , U_LatinCapitalLetterU }, /* 0x00DB */
   { U_LatinCapitalLetterUWithDiaeresis            , U_LatinCapitalLetterU }, /* 0x00DC */
   { U_LatinCapitalLetterYWithAcute                , U_LatinCapitalLetterY }, /* 0x00DD */
   { U_LatinSmallLetterSharpS                      , U_LatinSmallLetterS   }, /* 0x00DF */
   { U_LatinSmallLetterAWithGrave                  , U_LatinSmallLetterA   }, /* 0x00E0 */
   { U_LatinSmallLetterAWithAcute                  , U_LatinSmallLetterA   }, /* 0x00E1 */
   { U_LatinSmallLetterAWithCircumflex             , U_LatinSmallLetterA   }, /* 0x00E2 */
   { U_LatinSmallLetterAWithTilde                  , U_LatinSmallLetterA   }, /* 0x00E3 */
   { U_LatinSmallLetterAWithDiaeresis              , U_LatinSmallLetterA   }, /* 0x00E4 */
   { U_LatinSmallLetterAWithRingAbove              , U_LatinSmallLetterA   }, /* 0x00E5 */
   { U_LatinSmallLigatureAE                        , U_LatinSmallLetterA   }, /* 0x00E6 */
   { U_LatinSmallLetterCWithCedilla                , U_LatinSmallLetterC   }, /* 0x00E7 */
   { U_LatinSmallLetterEWithGrave                  , U_LatinSmallLetterE   }, /* 0x00E8 */
   { U_LatinSmallLetterEWithAcute                  , U_LatinSmallLetterE   }, /* 0x00E9 */
   { U_LatinSmallLetterEWithCircumflex             , U_LatinSmallLetterE   }, /* 0x00EA */
   { U_LatinSmallLetterEWithDiaeresis              , U_LatinSmallLetterE   }, /* 0x00EB */
   { U_LatinSmallLetterIWithGrave                  , U_LatinSmallLetterI   }, /* 0x00EC */
   { U_LatinSmallLetterIWithAcute                  , U_LatinSmallLetterI   }, /* 0x00ED */
   { U_LatinSmallLetterIWithCircumflex             , U_LatinSmallLetterI   }, /* 0x00EE */
   { U_LatinSmallLetterIWithDiaeresis              , U_LatinSmallLetterI   }, /* 0x00EF */
   { U_LatinSmallLetterNWithTilde                  , U_LatinSmallLetterN   }, /* 0x00F1 */
   { U_LatinSmallLetterOWithGrave                  , U_LatinSmallLetterO   }, /* 0x00F2 */
   { U_LatinSmallLetterOWithAcute                  , U_LatinSmallLetterO   }, /* 0x00F3 */
   { U_LatinSmallLetterOWithCircumflex             , U_LatinSmallLetterO   }, /* 0x00F4 */
   { U_LatinSmallLetterOWithTilde                  , U_LatinSmallLetterO   }, /* 0x00F5 */
   { U_LatinSmallLetterOWithDiaeresis              , U_LatinSmallLetterO   }, /* 0x00F6 */
   { U_LatinSmallLetterOSlash                      , U_LatinSmallLetterO   }, /* 0x00F8 */
   { U_LatinSmallLetterUWithGrave                  , U_LatinSmallLetterU   }, /* 0x00F9 */
   { U_LatinSmallLetterUWithAcute                  , U_LatinSmallLetterU   }, /* 0x00FA */
   { U_LatinSmallLetterUWithCircumflex             , U_LatinSmallLetterU   }, /* 0x00FB */
   { U_LatinSmallLetterUWithDiaeresis              , U_LatinSmallLetterU   }, /* 0x00FC */
   { U_LatinSmallLetterYWithAcute                  , U_LatinSmallLetterY   }, /* 0x00FD */
   { U_LatinSmallLetterYWithDiaeresis              , U_LatinSmallLetterY   }, /* 0x00FF */

   { U_LatinCapitalLetterAWithMacron               , U_LatinCapitalLetterA }, /* 0x0100 */
   { U_LatinSmallLetterAWithMacron                 , U_LatinSmallLetterA   }, /* 0x0101 */
   { U_LatinCapitalLetterAWithBreve                , U_LatinCapitalLetterA }, /* 0x0102 */
   { U_LatinSmallLetterAWithBreve                  , U_LatinSmallLetterA   }, /* 0x0103 */
   { U_LatinCapitalLetterAWithOgonek               , U_LatinCapitalLetterA }, /* 0x0104 */
   { U_LatinSmallLetterAWithOgonek                 , U_LatinSmallLetterA   }, /* 0x0105 */
   { U_LatinCapitalLetterCWithAcute                , U_LatinCapitalLetterC }, /* 0x0106 */
   { U_LatinSmallLetterCWithAcute                  , U_LatinSmallLetterC   }, /* 0x0107 */
   { U_LatinCapitalLetterCWithCircumflex           , U_LatinCapitalLetterC }, /* 0x0108 */
   { U_LatinSmallLetterCWithCircumflex             , U_LatinSmallLetterC   }, /* 0x0109 */
   { U_LatinCapitalLetterCWithDotAbove             , U_LatinCapitalLetterC }, /* 0x010A */
   { U_LatinSmallLetterCWithDotAbove               , U_LatinSmallLetterC   }, /* 0x010B */
   { U_LatinCapitalLetterCWithCaron                , U_LatinCapitalLetterC }, /* 0x010C */
   { U_LatinSmallLetterCWithCaron                  , U_LatinSmallLetterC   }, /* 0x010D */
   { U_LatinCapitalLetterDWithCaron                , U_LatinCapitalLetterD }, /* 0x010E */
   { U_LatinSmallLetterDWithCaron                  , U_LatinSmallLetterD   }, /* 0x010F */
   { U_LatinCapitalLetterDWithStroke               , U_LatinCapitalLetterD }, /* 0x0110 */
   { U_LatinSmallLetterDWithStroke                 , U_LatinSmallLetterD   }, /* 0x0111 */
   { U_LatinCapitalLetterEWithMacron               , U_LatinCapitalLetterE }, /* 0x0112 */
   { U_LatinSmallLetterEWithMacron                 , U_LatinSmallLetterE   }, /* 0x0113 */
   { U_LatinCapitalLetterEWithBreve                , U_LatinCapitalLetterE }, /* 0x0114 */
   { U_LatinSmallLetterEWithBreve                  , U_LatinSmallLetterE   }, /* 0x0115 */
   { U_LatinCapitalLetterEWithDotAbove             , U_LatinCapitalLetterE }, /* 0x0116 */
   { U_LatinSmallLetterEWithDotAbove               , U_LatinSmallLetterE   }, /* 0x0117 */
   { U_LatinCapitalLetterEWithOgonek               , U_LatinCapitalLetterE }, /* 0x0118 */
   { U_LatinSmallLetterEWithOgonek                 , U_LatinSmallLetterE   }, /* 0x0119 */
   { U_LatinCapitalLetterEWithCaron                , U_LatinCapitalLetterE }, /* 0x011A */
   { U_LatinSmallLetterEWithCaron                  , U_LatinSmallLetterE   }, /* 0x011B */
   { U_LatinCapitalLetterGWithCircumflex           , U_LatinCapitalLetterG }, /* 0x011C */
   { U_LatinSmallLetterGWithCircumflex             , U_LatinSmallLetterG   }, /* 0x011D */
   { U_LatinCapitalLetterGWithBreve                , U_LatinCapitalLetterG }, /* 0x011E */
   { U_LatinSmallLetterGWithBreve                  , U_LatinSmallLetterG   }, /* 0x011F */
   { U_LatinCapitalLetterGWithDotAbove             , U_LatinCapitalLetterG }, /* 0x0120 */
   { U_LatinSmallLetterGWithDotAbove               , U_LatinSmallLetterG   }, /* 0x0121 */
   { U_LatinCapitalLetterGWithCedilla              , U_LatinCapitalLetterG }, /* 0x0122 */
   { U_LatinSmallLetterGWithCedilla                , U_LatinSmallLetterG   }, /* 0x0123 */
   { U_LatinCapitalLetterHWithCircumflex           , U_LatinCapitalLetterH }, /* 0x0124 */
   { U_LatinSmallLetterHWithCircumflex             , U_LatinSmallLetterH   }, /* 0x0125 */
   { U_LatinCapitalLetterHWithStroke               , U_LatinCapitalLetterH }, /* 0x0126 */
   { U_LatinSmallLetterHWithStroke                 , U_LatinSmallLetterH   }, /* 0x0127 */
   { U_LatinCapitalLetterIWithTilde                , U_LatinCapitalLetterI }, /* 0x0128 */
   { U_LatinSmallLetterIWithTilde                  , U_LatinSmallLetterI   }, /* 0x0129 */
   { U_LatinCapitalLetterIWithMacron               , U_LatinCapitalLetterI }, /* 0x012A */
   { U_LatinSmallLetterIWithMacron                 , U_LatinSmallLetterI   }, /* 0x012B */
   { U_LatinCapitalLetterIWithBreve                , U_LatinCapitalLetterI }, /* 0x012C */
   { U_LatinSmallLetterIWithBreve                  , U_LatinSmallLetterI   }, /* 0x012D */
   { U_LatinCapitalLetterIWithOgonek               , U_LatinCapitalLetterI }, /* 0x012E */
   { U_LatinSmallLetterIWithOgonek                 , U_LatinSmallLetterI   }, /* 0x012F */
   { U_LatinCapitalLetterIWithDotAbove             , U_LatinCapitalLetterI }, /* 0x0130 */
   { U_LatinSmallLetterDotlessI                    , U_LatinSmallLetterI   }, /* 0x0131 */
   { U_LatinCapitalLigatureIJ                      , U_LatinCapitalLetterI }, /* 0x0132 */
   { U_LatinSmallLigatureIJ                        , U_LatinSmallLetterI   }, /* 0x0133 */
   { U_LatinCapitalLetterJWithCircumflex           , U_LatinCapitalLetterJ }, /* 0x0134 */
   { U_LatinSmallLetterJWithCircumflex             , U_LatinSmallLetterJ   }, /* 0x0135 */
   { U_LatinCapitalLetterKWithCedilla              , U_LatinCapitalLetterK }, /* 0x0136 */
   { U_LatinSmallLetterKWithCedilla                , U_LatinSmallLetterK   }, /* 0x0137 */
   { U_LatinCapitalLetterLWithAcute                , U_LatinCapitalLetterL }, /* 0x0139 */
   { U_LatinSmallLetterLWithAcute                  , U_LatinSmallLetterL   }, /* 0x013A */
   { U_LatinCapitalLetterLWithCedilla              , U_LatinCapitalLetterL }, /* 0x013B */
   { U_LatinSmallLetterLWithCedilla                , U_LatinSmallLetterL   }, /* 0x013C */
   { U_LatinCapitalLetterLWithCaron                , U_LatinCapitalLetterL }, /* 0x013D */
   { U_LatinSmallLetterLWithCaron                  , U_LatinSmallLetterL   }, /* 0x013E */
   { U_LatinCapitalLetterLWithMiddleDot            , U_LatinCapitalLetterL }, /* 0x013F */
   { U_LatinSmallLetterLWithMiddleDot              , U_LatinSmallLetterL   }, /* 0x0140 */
   { U_LatinCapitalLetterLWithStroke               , U_LatinCapitalLetterL }, /* 0x0141 */
   { U_LatinSmallLetterLWithStroke                 , U_LatinSmallLetterL   }, /* 0x0142 */
   { U_LatinCapitalLetterNWithAcute                , U_LatinCapitalLetterN }, /* 0x0143 */
   { U_LatinSmallLetterNWithAcute                  , U_LatinSmallLetterN   }, /* 0x0144 */
   { U_LatinCapitalLetterNWithCedilla              , U_LatinCapitalLetterN }, /* 0x0145 */
   { U_LatinSmallLetterNWithCedilla                , U_LatinSmallLetterN   }, /* 0x0146 */
   { U_LatinCapitalLetterNWithCaron                , U_LatinCapitalLetterN }, /* 0x0147 */
   { U_LatinSmallLetterNWithCaron                  , U_LatinSmallLetterN   }, /* 0x0148 */
   { U_LatinSmallLetterApostropheN                 , U_LatinSmallLetterN   }, /* 0x0149 */
   { U_LatinCapitalLetterOWithMacron               , U_LatinCapitalLetterO }, /* 0x014C */
   { U_LatinSmallLetterOWithMacron                 , U_LatinSmallLetterO   }, /* 0x014D */
   { U_LatinCapitalLetterOWithBreve                , U_LatinCapitalLetterO }, /* 0x014E */
   { U_LatinSmallLetterOWithBreve                  , U_LatinSmallLetterO   }, /* 0x014F */
   { U_LatinCapitalLetterOWithDoubleAcute          , U_LatinCapitalLetterO }, /* 0x0150 */
   { U_LatinSmallLetterOWithDoubleAcute            , U_LatinSmallLetterO   }, /* 0x0151 */
   { U_LatinCapitalLigatureOE                      , U_LatinCapitalLetterO }, /* 0x0152 */
   { U_LatinSmallLigatureOE                        , U_LatinSmallLetterO   }, /* 0x0153 */
   { U_LatinCapitalLetterRWithAcute                , U_LatinCapitalLetterR }, /* 0x0154 */
   { U_LatinSmallLetterRWithAcute                  , U_LatinSmallLetterR   }, /* 0x0155 */
   { U_LatinCapitalLetterRWithCedilla              , U_LatinCapitalLetterR }, /* 0x0156 */
   { U_LatinSmallLetterRWithCedilla                , U_LatinSmallLetterR   }, /* 0x0157 */
   { U_LatinCapitalLetterRWithCaron                , U_LatinCapitalLetterR }, /* 0x0158 */
   { U_LatinSmallLetterRWithCaron                  , U_LatinSmallLetterR   }, /* 0x0159 */
   { U_LatinCapitalLetterSWithAcute                , U_LatinCapitalLetterS }, /* 0x015A */
   { U_LatinSmallLetterSWithAcute                  , U_LatinSmallLetterS   }, /* 0x015B */
   { U_LatinCapitalLetterSWithCircumflex           , U_LatinCapitalLetterS }, /* 0x015C */
   { U_LatinSmallLetterSWithCircumflex             , U_LatinSmallLetterS   }, /* 0x015D */
   { U_LatinCapitalLetterSWithCedilla              , U_LatinCapitalLetterS }, /* 0x015E */
   { U_LatinSmallLetterSWithCedilla                , U_LatinSmallLetterS   }, /* 0x015F */
   { U_LatinCapitalLetterSWithCaron                , U_LatinCapitalLetterS }, /* 0x0160 */
   { U_LatinSmallLetterSWithCaron                  , U_LatinSmallLetterS   }, /* 0x0161 */
   { U_LatinCapitalLetterTWithCedilla              , U_LatinCapitalLetterT }, /* 0x0162 */
   { U_LatinSmallLetterTWithCedilla                , U_LatinSmallLetterT   }, /* 0x0163 */
   { U_LatinCapitalLetterTWithCaron                , U_LatinCapitalLetterT }, /* 0x0164 */
   { U_LatinSmallLetterTWithCaron                  , U_LatinSmallLetterT   }, /* 0x0165 */
   { U_LatinCapitalLetterTWithStroke               , U_LatinCapitalLetterT }, /* 0x0166 */
   { U_LatinSmallLetterTWithStroke                 , U_LatinSmallLetterT   }, /* 0x0167 */
   { U_LatinCapitalLetterUWithTilde                , U_LatinCapitalLetterU }, /* 0x0168 */
   { U_LatinSmallLetterUWithTilde                  , U_LatinSmallLetterU   }, /* 0x0169 */
   { U_LatinCapitalLetterUWithMacron               , U_LatinCapitalLetterU }, /* 0x016A */
   { U_LatinSmallLetterUWithMacron                 , U_LatinSmallLetterU   }, /* 0x016B */
   { U_LatinCapitalLetterUWithBreve                , U_LatinCapitalLetterU }, /* 0x016C */
   { U_LatinSmallLetterUWithBreve                  , U_LatinSmallLetterU   }, /* 0x016D */
   { U_LatinCapitalLetterUWithRingAbove            , U_LatinCapitalLetterU }, /* 0x016E */
   { U_LatinSmallLetterUWithRingAbove              , U_LatinSmallLetterU   }, /* 0x016F */
   { U_LatinCapitalLetterUWithDoubleAcute          , U_LatinCapitalLetterU }, /* 0x0170 */
   { U_LatinSmallLetterUWithDoubleAcute            , U_LatinSmallLetterU   }, /* 0x0171 */
   { U_LatinCapitalLetterUWithOgonek               , U_LatinCapitalLetterU }, /* 0x0172 */
   { U_LatinSmallLetterUWithOgonek                 , U_LatinSmallLetterU   }, /* 0x0173 */
   { U_LatinCapitalLetterWWithCircumflex           , U_LatinCapitalLetterW }, /* 0x0174 */
   { U_LatinSmallLetterWWithCircumflex             , U_LatinSmallLetterW   }, /* 0x0175 */
   { U_LatinCapitalLetterYWithCircumflex           , U_LatinCapitalLetterY }, /* 0x0176 */
   { U_LatinSmallLetterYWithCircumflex             , U_LatinSmallLetterY   }, /* 0x0177 */
   { U_LatinCapitalLetterYWithDiaeresis            , U_LatinCapitalLetterY }, /* 0x0178 */
   { U_LatinCapitalLetterZWithAcute                , U_LatinCapitalLetterZ }, /* 0x0179 */
   { U_LatinSmallLetterZWithAcute                  , U_LatinSmallLetterZ   }, /* 0x017A */
   { U_LatinCapitalLetterZWithDotAbove             , U_LatinCapitalLetterZ }, /* 0x017B */
   { U_LatinSmallLetterZWithDotAbove               , U_LatinSmallLetterZ   }, /* 0x017C */
   { U_LatinCapitalLetterZWithCaron                , U_LatinCapitalLetterZ }, /* 0x017D */
   { U_LatinSmallLetterZWithCaron                  , U_LatinSmallLetterZ   }, /* 0x017E */
   { U_LatinSmallLetterLongS                       , U_LatinSmallLetterS   }, /* 0x017F */

   { U_LatinSmallLetterBWithStroke                 , U_LatinSmallLetterB   }, /* 0x0180 */
   { U_LatinCapitalLetterBWithHook                 , U_LatinCapitalLetterB }, /* 0x0181 */
   { U_LatinCapitalLetterBWithTopbar               , U_LatinCapitalLetterB }, /* 0x0182 */
   { U_LatinSmallLetterBWithTopbar                 , U_LatinSmallLetterB   }, /* 0x0183 */
   { U_LatinCapitalLetterOpenO                     , U_LatinCapitalLetterO }, /* 0x0186 */
   { U_LatinCapitalLetterCWithHook                 , U_LatinCapitalLetterC }, /* 0x0187 */
   { U_LatinSmallLetterCWithHook                   , U_LatinSmallLetterC   }, /* 0x0188 */
   { U_LatinCapitalLetterAfricanD                  , U_LatinCapitalLetterD }, /* 0x0189 */
   { U_LatinCapitalLetterDWithHook                 , U_LatinCapitalLetterD }, /* 0x018A */
   { U_LatinCapitalLetterDWithTopbar               , U_LatinCapitalLetterD }, /* 0x018B */
   { U_LatinSmallLetterDWithTopbar                 , U_LatinSmallLetterD   }, /* 0x018C */
   { U_LatinSmallLetterTurnedDelta                 , U_LatinSmallLetterD   }, /* 0x018D */
   { U_LatinCapitalLetterReversedE                 , U_LatinCapitalLetterE }, /* 0x018E */
   { U_LatinCapitalLetterSchwa                     , U_LatinCapitalLetterE }, /* 0x018F */
   { U_LatinCapitalLetterEpsilon                   , U_LatinCapitalLetterE }, /* 0x0190 */
   { U_LatinCapitalLetterFWithHook                 , U_LatinCapitalLetterF }, /* 0x0191 */
   { U_LatinSmallLetterScriptF                     , U_LatinCapitalLetterF }, /* 0x0192 LATIN SMALL LETTER F WITH HOOK, florijn */
   { U_LatinCapitalLetterGWithHook                 , U_LatinCapitalLetterG }, /* 0x0193 */
   { U_LatinCapitalLetterGamma                     , U_LatinCapitalLetterG }, /* 0x0194 */
   { U_LatinSmallLetterHV                          , U_LatinSmallLetterH   }, /* 0x0195 */
   { U_LatinCapitalLetterIota                      , U_LatinCapitalLetterI }, /* 0x0196 */
   { U_LatinCapitalLetterIWithStroke               , U_LatinCapitalLetterI }, /* 0x0197 */
   { U_LatinCapitalLetterKWithHook                 , U_LatinCapitalLetterK }, /* 0x0198 */
   { U_LatinSmallLetterKWithHook                   , U_LatinSmallLetterK   }, /* 0x0199 */
   { U_LatinSmallLetterLWithBar                    , U_LatinSmallLetterL   }, /* 0x019A */
   { U_LatinSmallLetterLambdaWithStroke            , U_LatinSmallLetterL   }, /* 0x019B */
   { U_LatinCapitalLetterTurnedM                   , U_LatinCapitalLetterM }, /* 0x019C */
   { U_LatinCapitalLetterNWithLeftHook             , U_LatinCapitalLetterN }, /* 0x019D */
   { U_LatinSmallLetterNWithLongRightLeg           , U_LatinSmallLetterN   }, /* 0x019E */
   { U_LatinCapitalLetterOWithMiddleTilde          , U_LatinCapitalLetterO }, /* 0x019F */
   { U_LatinCapitalLetterOWithHorn                 , U_LatinCapitalLetterO }, /* 0x01A0 */
   { U_LatinSmallLetterOWithHorn                   , U_LatinSmallLetterO   }, /* 0x01A1 */
   { U_LatinCapitalLetterOI                        , U_LatinCapitalLetterO }, /* 0x01A2 */
   { U_LatinSmallLetterOI                          , U_LatinSmallLetterO   }, /* 0x01A3 */
   { U_LatinCapitalLetterPWithHook                 , U_LatinCapitalLetterP }, /* 0x01A4 */
   { U_LatinSmallLetterPWithHook                   , U_LatinSmallLetterP   }, /* 0x01A5 */
   { U_LatinLetterYR                               , U_LatinCapitalLetterY }, /* 0x01A6 */
   { U_LatinSmallLetterTWithPalatalHook            , U_LatinCapitalLetterT }, /* 0x01AB */
   { U_LatinCapitalLetterTWithHook                 , U_LatinCapitalLetterT }, /* 0x01AC */
   { U_LatinSmallLetterTWithHook                   , U_LatinSmallLetterT   }, /* 0x01AD */
   
   { U_LatinCapitalLetterTWithRetroflexHook        , U_LatinCapitalLetterT }, /* 0x01AE */
   { U_LatinCapitalLetterUWithHorn                 , U_LatinCapitalLetterU }, /* 0x01AF */
   { U_LatinSmallLetterUWithHorn                   , U_LatinSmallLetterU   }, /* 0x01B0 */
   { U_LatinCapitalLetterUpsilon                   , U_LatinCapitalLetterU }, /* 0x01B1 */
   { U_LatinCapitalLetterScriptV                   , U_LatinCapitalLetterV }, /* 0x01B2 */
   { U_LatinCapitalLetterYWithHook                 , U_LatinCapitalLetterY }, /* 0x01B3 */
   { U_LatinSmallLetterYWithHook                   , U_LatinSmallLetterY   }, /* 0x01B4 */
   { U_LatinCapitalLetterZWithStroke               , U_LatinCapitalLetterZ }, /* 0x01B5 */
   { U_LatinSmallLetterZWithStroke                 , U_LatinSmallLetterZ   }, /* 0x01B6 */

   { U_LatinCapitalLetterDZWithCaron               , U_LatinCapitalLetterD }, /* 0x01C4 */
   { U_LatinCapitalLetterDWithSmallLetterZWithCaron, U_LatinCapitalLetterD }, /* 0x01C5 */
   { U_LatinSmallLetterDZWithCaron                 , U_LatinSmallLetterD   }, /* 0x01C6 */
   { U_LatinCapitalLetterLJ                        , U_LatinCapitalLetterL }, /* 0x01C7 */
   { U_LatinCapitalLetterLWithSmallLetterJ         , U_LatinCapitalLetterL }, /* 0x01C8 */
   { U_LatinSmallLetterLJ                          , U_LatinSmallLetterL   }, /* 0x01C9 */
   { U_LatinCapitalLetterNJ                        , U_LatinCapitalLetterN }, /* 0x01CA */
   { U_LatinCapitalLetterNWithSmallLetterJ         , U_LatinCapitalLetterN }, /* 0x01CB */
   { U_LatinSmallLetterNJ                          , U_LatinSmallLetterN   }, /* 0x01CC */

   { U_LatinCapitalLetterAWithCaron                , U_LatinCapitalLetterA }, /* 0x01CD */
   { U_LatinSmallLetterAWithCaron                  , U_LatinSmallLetterA   }, /* 0x01CE */
   { U_LatinCapitalLetterIWithCaron                , U_LatinCapitalLetterI }, /* 0x01CF */
   { U_LatinSmallLetterIWithCaron                  , U_LatinSmallLetterI   }, /* 0x01D0 */
   { U_LatinCapitalLetterOWithCaron                , U_LatinCapitalLetterO }, /* 0x01D1 */
   { U_LatinSmallLetterOWithCaron                  , U_LatinSmallLetterO   }, /* 0x01D2 */
   { U_LatinCapitalLetterUWithCaron                , U_LatinCapitalLetterU }, /* 0x01D3 */
   { U_LatinSmallLetterUWithCaron                  , U_LatinSmallLetterU   }, /* 0x01D4 */
   { U_LatinCapitalLetterUWithDiaeresisAndMacron   , U_LatinCapitalLetterU }, /* 0x01D5 */
   { U_LatinSmallLetterUWithDiaeresisAndMacron     , U_LatinSmallLetterU   }, /* 0x01D6 */
   { U_LatinCapitalLetterUWithDiaeresisAndAcute    , U_LatinCapitalLetterU }, /* 0x01D7 */
   { U_LatinSmallLetterUWithDiaeresisAndAcute      , U_LatinSmallLetterU   }, /* 0x01D8 */
   { U_LatinCapitalLetterUWithDiaeresisAndCaron    , U_LatinCapitalLetterU }, /* 0x01D9 */
   { U_LatinSmallLetterUWithDiaeresisAndCaron      , U_LatinSmallLetterU   }, /* 0x01DA */
   { U_LatinCapitalLetterUWithDiaeresisAndGrave    , U_LatinCapitalLetterU }, /* 0x01DB */
   { U_LatinSmallLetterUWithDiaeresisAndGrave      , U_LatinSmallLetterU   }, /* 0x01DC */

   { U_LatinSmallLetterTurnedE                     , U_LatinSmallLetterE   }, /* 0x01DD */
   { U_LatinCapitalLetterAWithDiaeresisAndMacron   , U_LatinCapitalLetterA }, /* 0x01DE */
   { U_LatinSmallLetterAWithDiaeresisAndMacron     , U_LatinSmallLetterA   }, /* 0x01DF */
   { U_LatinCapitalLetterAWithDotAboveAndMacron    , U_LatinCapitalLetterA }, /* 0x01E0 */
   { U_LatinSmallLetterAWithDotAboveAndMacron      , U_LatinSmallLetterA   }, /* 0x01E1 */
   { U_LatinCapitalLetterAEWithMacron              , U_LatinCapitalLetterA }, /* 0x01E2 */
   { U_LatinSmallLetterAEWithMacron                , U_LatinSmallLetterA   }, /* 0x01E3 */
   { U_LatinCapitalLetterGWithStroke               , U_LatinCapitalLetterG }, /* 0x01E4 */
   { U_LatinSmallLetterGWithStroke                 , U_LatinSmallLetterG   }, /* 0x01E5 */
   { U_LatinCapitalLetterGWithCaron                , U_LatinCapitalLetterG }, /* 0x01E6 */
   { U_LatinSmallLetterGWithCaron                  , U_LatinSmallLetterG   }, /* 0x01E7 */
   { U_LatinCapitalLetterKWithCaron                , U_LatinCapitalLetterK }, /* 0x01E8 */
   { U_LatinSmallLetterKWithCaron                  , U_LatinSmallLetterK   }, /* 0x01E9 */
   { U_LatinCapitalLetterOWithOgonek               , U_LatinCapitalLetterO }, /* 0x01EA */
   { U_LatinSmallLetterOWithOgonek                 , U_LatinSmallLetterO   }, /* 0x01EB */
   { U_LatinCapitalLetterOWithOgonekAndMacron      , U_LatinCapitalLetterO }, /* 0x01EC */
   { U_LatinSmallLetterOWithOgonekAndMacron        , U_LatinSmallLetterO   }, /* 0x01ED */
   { U_LatinSmallLetterJWithCaron                  , U_LatinSmallLetterJ   }, /* 0x01F0 */
   { U_LatinCapitalLetterDZ                        , U_LatinCapitalLetterD }, /* 0x01F1 */
   { U_LatinCapitalLetterDWithSmallLetterZ         , U_LatinCapitalLetterD }, /* 0x01F2 */
   { U_LatinSmallLetterDZ                          , U_LatinSmallLetterD   }, /* 0x01F3 */
   { U_LatinCapitalLetterGWithAcute                , U_LatinCapitalLetterG }, /* 0x01F4 */
   { U_LatinSmallLetterGWithAcute                  , U_LatinSmallLetterG   }, /* 0x01F5 */
   { U_LatinCapitalLetterNWithGrave                , U_LatinCapitalLetterN }, /* 0x01F8 */
   { U_LatinSmallLetterNWithGrave                  , U_LatinSmallLetterN   }, /* 0x01F9 */
   { U_LatinCapitalLetterAWithRingAboveAndAcute    , U_LatinCapitalLetterA }, /* 0x01FA */
   { U_LatinSmallLetterAWithRingAboveAndAcute      , U_LatinSmallLetterA   }, /* 0x01FB */
   { U_LatinCapitalLetterAEWithAcute               , U_LatinCapitalLetterA }, /* 0x01FC */
   { U_LatinSmallLetterAEWithAcute                 , U_LatinSmallLetterA   }, /* 0x01FD */
   { U_LatinCapitalLetterOWithStrokeAndAcute       , U_LatinCapitalLetterO }, /* 0x01FE */
   { U_LatinSmallLetterOWithStrokeAndAcute         , U_LatinSmallLetterO   }, /* 0x01FF */

   { U_LatinCapitalLetterAWithDoubleGrave          , U_LatinCapitalLetterA }, /* 0x0200 */
   { U_LatinSmallLetterAWithDoubleGrave            , U_LatinSmallLetterA   }, /* 0x0201 */
   { U_LatinCapitalLetterAWithInvertedBreve        , U_LatinCapitalLetterA }, /* 0x0202 */
   { U_LatinSmallLetterAWithInvertedBreve          , U_LatinSmallLetterA   }, /* 0x0203 */
   { U_LatinCapitalLetterEWithDoubleGrave          , U_LatinCapitalLetterE }, /* 0x0204 */
   { U_LatinSmallLetterEWithDoubleGrave            , U_LatinSmallLetterE   }, /* 0x0205 */
   { U_LatinCapitalLetterEWithInvertedBreve        , U_LatinCapitalLetterE }, /* 0x0206 */
   { U_LatinSmallLetterEWithInvertedBreve          , U_LatinSmallLetterE   }, /* 0x0207 */
   { U_LatinCapitalLetterIWithDoubleGrave          , U_LatinCapitalLetterI }, /* 0x0208 */
   { U_LatinSmallLetterIWithDoubleGrave            , U_LatinSmallLetterI   }, /* 0x0209 */
   { U_LatinCapitalLetterIWithInvertedBreve        , U_LatinCapitalLetterI }, /* 0x020A */
   { U_LatinSmallLetterIWithInvertedBreve          , U_LatinSmallLetterI   }, /* 0x020B */
   { U_LatinCapitalLetterOWithDoubleGrave          , U_LatinCapitalLetterO }, /* 0x020C */
   { U_LatinSmallLetterOWithDoubleGrave            , U_LatinSmallLetterO   }, /* 0x020D */
   { U_LatinCapitalLetterOWithInvertedBreve        , U_LatinCapitalLetterO }, /* 0x020E */
   { U_LatinSmallLetterOWithInvertedBreve          , U_LatinSmallLetterO   }, /* 0x020F */
   { U_LatinCapitalLetterRWithDoubleGrave          , U_LatinCapitalLetterR }, /* 0x0210 */
   { U_LatinSmallLetterRWithDoubleGrave            , U_LatinSmallLetterR   }, /* 0x0211 */
   { U_LatinCapitalLetterRWithInvertedBreve        , U_LatinCapitalLetterR }, /* 0x0212 */
   { U_LatinSmallLetterRWithInvertedBreve          , U_LatinSmallLetterR   }, /* 0x0213 */
   { U_LatinCapitalLetterUWithDoubleGrave          , U_LatinCapitalLetterU }, /* 0x0214 */
   { U_LatinSmallLetterUWithDoubleGrave            , U_LatinSmallLetterU   }, /* 0x0215 */
   { U_LatinCapitalLetterUWithInvertedBreve        , U_LatinCapitalLetterU }, /* 0x0216 */
   { U_LatinSmallLetterUWithInvertedBreve          , U_LatinSmallLetterU   }, /* 0x0217 */

   { U_LatinCapitalLetterSWithCommaBelow           , U_LatinCapitalLetterS }, /* 0x0218 */
   { U_LatinSmallLetterSWithCommaBelow             , U_LatinSmallLetterS   }, /* 0x0219 */
   { U_LatinCapitalLetterTWithCommaBelow           , U_LatinCapitalLetterT }, /* 0x021A */
   { U_LatinSmallLetterTWithCommaBelow             , U_LatinSmallLetterT   }, /* 0x021B */

   { U_LatinCapitalLetterYogh                      , U_LatinCapitalLetterY }, /* 0x021C */
   { U_LatinSmallLetterYogh                        , U_LatinSmallLetterY   }, /* 0x021D */
   { U_LatinCapitalLetterHWithCaron                , U_LatinCapitalLetterH }, /* 0x021E */
   { U_LatinSmallLetterHWithCaron                  , U_LatinSmallLetterH   }, /* 0x021F */
   { U_LatinCapitalLetterNWithLongRightLeg         , U_LatinCapitalLetterN }, /* 0x0220 */
   { U_LatinCapitalLetterOU                        , U_LatinCapitalLetterO }, /* 0x0222 */
   { U_LatinSmallLetterOU                          , U_LatinSmallLetterO   }, /* 0x0223 */
   { U_LatinCapitalLetterZWithHook                 , U_LatinCapitalLetterZ }, /* 0x0224 */
   { U_LatinSmallLetterZWithHook                   , U_LatinSmallLetterZ   }, /* 0x0225 */
   { U_LatinCapitalLetterAWithDotAbove             , U_LatinCapitalLetterA }, /* 0x0226 */
   { U_LatinSmallLetterAWithDotAbove               , U_LatinSmallLetterA   }, /* 0x0227 */
   { U_LatinCapitalLetterEWithCedilla              , U_LatinCapitalLetterE }, /* 0x0228 */
   { U_LatinSmallLetterEWithCedilla                , U_LatinSmallLetterE   }, /* 0x0229 */

   { U_LatinCapitalLetterOWithDiaeresisAndMacron   , U_LatinCapitalLetterO }, /* 0x022A */
   { U_LatinSmallLetterOWithDiaeresisAndMacron     , U_LatinSmallLetterO   }, /* 0x022B */
   { U_LatinCapitalLetterOWithTildeAndMacron       , U_LatinCapitalLetterO }, /* 0x022C */
   { U_LatinSmallLetterOWithTildeAndMacron         , U_LatinSmallLetterO   }, /* 0x022D */
   { U_LatinCapitalLetterOWithDotAbove             , U_LatinCapitalLetterO }, /* 0x022E */
   { U_LatinSmallLetterOWithDotAbove               , U_LatinSmallLetterO   }, /* 0x022F */
   { U_LatinCapitalLetterOWithDotAboveAndMacron    , U_LatinCapitalLetterO }, /* 0x0230 */
   { U_LatinSmallLetterOWithDotAboveAndMacron      , U_LatinSmallLetterO   }, /* 0x0231 */
   { U_LatinCapitalLetterYWithMacron               , U_LatinCapitalLetterY }, /* 0x0232 */
   { U_LatinSmallLetterYWithMacron                 , U_LatinSmallLetterY   }, /* 0x0233 */
   { 0x0000                                        , U_NIL                 }  /* list terminator */
};


/* +++ EOF +++ */
