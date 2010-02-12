/*******************************************************************************
*
*  Project name : UDO
*  Module name  : iso2tos.h
*  Symbol prefix: iso2tos
*
*  Description  : ISO-Zeichensatz in System-Zeichensatz (TOS) umsetzen
*
*  Copyright    : 1995-2001 Dirk Hagedorn
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
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Ulf Dunkel (fd), Gerhard Stoll (ggs)
*  Write access : fd, ggs
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  History:
*
*  2009:
*    ggs May 18: introduced
*  2010:
*    fd  Feb 12: all octal chars converted into decimal values
*
******************************************|************************************/


/*******************************************************************************
*
*     CONSTANTS
*
******************************************|************************************/

#ifndef ID_ISO2TOS_H
#define ID_ISO2TOS_H
const char  *id_iso2tos_h = "@(#) iso2tos.h   $date$";
#endif

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "portab.h"


typedef struct _iso2tos
{
   unsigned char   iso;                   /* */
   unsigned char   charsys;               /* */
}  ISO2TOS;


LOCAL const ISO2TOS   iso2tos_item[128] =
{
   {128,   0},                            /* null*//* !!!! */
   {129,   0},                            /* null*//* !!!! */
   {130,   0},                            /* '' (9u)*//* !!!! */
   {131, 159},                            /* #f*/
   {132,   0},                            /* "" (99u)*//* !!!! */
   {133,   0},                            /* !..*//* !!!! */
   {134, 187},                            /* #dag*/
   {135,   0},                            /* 2x#dag*//* !!!! */
   {136, 222},                            /* #circ*/
   {137,   0},                            /* #promill*/
   {138, 'S'},                            /* vS*//* !!!! */
   {139, '<'},                            /* <*//* !!!! */
   {140, 181},                            /* &OE*/
   {141,   0},                            /* null*/
   {142,   0},                            /* null*/
   {143,   0},                            /* null*/
   {144,   0},                            /* null*/
   {145,   0},                            /* '' (6o)*//* !!!! */
   {146,   0},                            /* '' (9o)*//* !!!! */
   {147,   0},                            /* "" (66o)*//* !!!! */
   {148,   0},                            /* "" (99u)*//* !!!! */
   {149, 249},                            /* #bullet*/
   {150, '-'},                            /* --*//* !!!! */
   {151, '-'},                            /* ---*//* !!!! */
   {152, '~'},                            /* !~*//* !!!! */
   {153, 191},                            /* #tm*/
   {154, 's'},                            /* vs*/
   {155, '>'},                            /* >*/
   {156, 180},                            /* &oe*/
   {157,   0},                            /* null*/
   {158,   0},                            /* null*/
   {159, 'Y'},                            /* "Y*//* !!!! */
   {150,   0},                            /* null*/
   {161, 173},                            /* #!*/
   {162, 155},                            /* #cent*/
   {163, 156},                            /* #pound*/
   {164,   0},                            /* general currency*/
   {165, 157},                            /* #yen*/
   {166, '|'},                            /* broken dash*//* !!!! */
   {167, 221},                            /* #sect*/
   {168, 185},                            /* #"*/
   {169, 189},                            /* #copy*/
   {170, 166},                            /* _a*/
   {171, 174},                            /* #<*/
   {172, 170},                            /* #neg*/
   {173,   0},                            /* strich*//* !!!! */
   {174, 190},                            /* #reg*/
   {175,   0},                            /* #macron*//* !!!! */
   {176, 248},                            /* #degree*/
   {177, 241},                            /* #pm*/
   {178, 253},                            /* #^2*/
   {179, 254},                            /* #^3*/
   {180, 186},                            /* #'*/
   {181, 230},                            /* #mu*/
   {182, 188},                            /* #p*/
   {183, 250},                            /* #cdot*/
   {184,   0},                            /* cedille*//* !!!! */
   {185,   0},                            /* #^1*//* !!!! */
   {186, 167},                            /* _o*/
   {187, 175},                            /* #>*/
   {188, 172},                            /* #1/4*/
   {189, 171},                            /* #1/2*/
   {190,   0},                            /* #3/4*//* !!!! */
   {191, 168},                            /* #?*/
   {192, 182},                            /* `A*/
   {193, 'A'},                            /* 'A*//* !!!! */
   {194, 'A'},                            /* ^A*//* !!!! */
   {195, 183},                            /* ~A*/
   {196, 142},                            /* "A*/
   {197, 143},                            /* .A*/
   {198, 146},                            /* &AE*/
   {199, 128},                            /* ,C*/
   {200, 'E'},                            /* `E*//* !!!! */
   {201, 'E'},                            /* 'E*//* !!!! */
   {202, 'E'},                            /* ^E*//* !!!! */
   {203, 'E'},                            /* "E*//* !!!! */
   {204, 'I'},                            /* `I*//* !!!! */
   {205, 'I'},                            /* 'I*//* !!!! */
   {206, 'I'},                            /* ^I*//* !!!! */
   {207, 'I'},                            /* "I*//* !!!! */
   {208,   0},                            /* -D*/
   {209, 165},                            /* ~N*/
   {210, 'O'},                            /* `O*//* !!!! */
   {211, 'O'},                            /* 'O*//* !!!! */
   {212, 'O'},                            /* ^O*//* !!!! */
   {213, 184},                            /* ~O*/
   {214, 153},                            /* "O*/
   {215, 'x'},                            /* #times*//* !!!! */
   {216, 178},                            /* /O*/
   {217, 'U'},                            /* `U*//* !!!! */
   {218, 'U'},                            /* 'U*//* !!!! */
   {219, 'U'},                            /* ^U*//* !!!! */
   {220, 154},                            /* "U*/
   {221, 'Y'},                            /* 'Y*//* !!!! */
   {222,   0},                            /* |b*/
   {223, 158},                            /* "s (sz)*//* r6pl12: vorher \341 (beta) */
   {224, 133},                            /* `a*/
   {225, 160},                            /* 'a*/
   {226, 131},                            /* ^a*/
   {227, 176},                            /* ~a*/
   {228, 132},                            /* "a*/
   {229, 134},                            /* .a*/
   {230, 145},                            /* &ae*/
   {231, 135},                            /* ,c*/
   {232, 138},                            /* `e*/
   {233, 130},                            /* 'e*/
   {234, 136},                            /* ^e*/
   {235, 137},                            /* "e*/
   {236, 141},                            /* `i*/
   {237, 161},                            /* 'i*/
   {238, 140},                            /* ^i*/
   {239, 139},                            /* "i*/
   {240,   0},                            /* o|''*//* !!!! */
   {241, 164},                            /* ~n*/
   {242, 149},                            /* `o*/
   {243, 162},                            /* 'o*/
   {244, 147},                            /* ^o*/
   {245, 177},                            /* ~o*/
   {246, 148},                            /* "o*/
   {247, 222},                            /* #div*/
   {248, 179},                            /* /o*/
   {249, 151},                            /* `u*/
   {250, 163},                            /* 'u*/
   {251, 150},                            /* ^u*/
   {252, 129},                            /* "u*/
   {253, 'y'},                            /* 'y*//* !!!! */
   {254,   0},                            /* |B*//* !!!! */
   {255, 152}                             /* "y*/
};


/* +++ EOF +++ */
