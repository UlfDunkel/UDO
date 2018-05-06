/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : img.h
*  Symbol prefix: img
*
*  Description  : ???
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
*  Co-Authors   : Gerhard Stoll (ggs), Ulf Dunkel
*  Write access : ggs, fd
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
*    fd  Feb 22: - header adjusted
*                - void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*  2011:
*    fd  Jan 31: - file reformatted
*                - IMGTYPE_... introduced; image header definitions resorted
*  2013:
*    fd  Oct 31: - get_png_size() added
*                - c_gif_output() renamed: c_html_image_output()
*
******************************************|************************************/

#ifndef UDO_IMG_H
#define UDO_IMG_H





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define IMGTYPE_BMP  0
#define IMGTYPE_GIF  1
#define IMGTYPE_IMG  2
#define IMGTYPE_JPG  3
#define IMGTYPE_MSP  4
#define IMGTYPE_PCX  5
#define IMGTYPE_PNG  6





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _bmpheader
{
   _UBYTE   bfType[2];          /*  0 */   /* File ID ('BM') */
   _UBYTE   bfSize[4];          /*  2 */   /* File size */
   _UBYTE   reserved1[2];       /*  6 */
   _UBYTE   reserved2[2];       /*  8 */
   _UBYTE   bfOffs[4];          /* 10 */
   _UBYTE   biSize[4];          /* 14 */   /* Laenge BITMAP_INFO-Header */
   _UBYTE   biWidth[4];         /* 18 */   /* Breite (4 bytes)*/
   _UBYTE   biHeight[4];        /* 22 */   /* Hoehe (4 bytes) */
   _UBYTE   biPlanes[2];        /* 26 */   /* Farbebenen */
   _UBYTE   biBitCnt[2];        /* 28 */   /* Zahl der Bits pro Pixel */
   _UBYTE   biCompr[4];         /* 30 */   /* Typ der Komprimierung */
   _UBYTE   biSizeIm[4];        /* 34 */   /* Bildgroesse in Bytes */
   _UBYTE   biXPels[4];         /* 38 */   /* horizontale Aufloesung */
   _UBYTE   biYPels[4];         /* 42 */   /* vertikale Aufloesung */
   _UBYTE   biClrUsed[4];       /* 46 */   /* Zahl der benutzten Farben */
   _UBYTE   biClrImp[4];        /* 50 */   /* Zahl der wichtigen Farben */
} BMPHEADER;


typedef struct _gifheader
{
   _UBYTE   gif_signature[3];              /* GIF */
   _UBYTE   gif_version[3];                /* 87a oder 89a */
   _UBYTE   gif_width_lo;                  /* Breite Low-Byte */
   _UBYTE   gif_width_hi;                  /*        High-Byte */
   _UBYTE   gif_height_lo;                 /* Hoehe Low-Byte */
   _UBYTE   gif_height_hi;                 /*       High-Byte */
   _UBYTE   flags;
   _UBYTE   gif_background;
   _UBYTE   gif_ratio;
} GIFHEADER;


typedef struct _imgheader
{
   _UBYTE   im_version[2];
   _UBYTE   im_headerlength[2];            /* header length in words */
   _UBYTE   im_nplanes[2];                 /* # of planes */
   _UBYTE   im_patlen[2];
   _UBYTE   im_pixwidth_hi;                /* pixel width  in mm/1000 */
   _UBYTE   im_pixwidth_lo;
   _UBYTE   im_pixheight_hi;               /* pixel height in mm/1000 */
   _UBYTE   im_pixheight_lo;
   _UBYTE   im_scanwidth_hi;               /* width in pixels */
   _UBYTE   im_scanwidth_lo;
   _UBYTE   im_nlines_hi;                  /* height in pixels */
   _UBYTE   im_nlines_lo;
} IMGHEADER;


typedef struct _jpgheader
{
   _UBYTE   SOI[2];                        /* Start of Image (SOI) Marker */
   _UBYTE   APP0[2];                       /* Applicaion (APP0) Marker    */
   _UBYTE   APPO_lenght[2];
   _UBYTE   APP0_ID[5];
   _UBYTE   APP0_Version[2];
   _UBYTE   APP0_Units[1];
   _UBYTE   APP0_X_Density[2];
   _UBYTE   APP0_Y_Density[2];
} JPGHEADER;


typedef struct _mspheader
{
   _UBYTE   msp_res[4];         /*  0 */   /* Magic 'LinS' */
   _UBYTE   msp_width_lo;       /*  4 */   /* Breite */
   _UBYTE   msp_width_hi;
   _UBYTE   msp_height_lo;      /*  6 */   /* Hoehe */
   _UBYTE   msp_height_hi;
} MSPHEADER;


typedef struct _pcxheader
{
   _UBYTE   pcx_res[4];         /*  0 */
   _UBYTE   pcx_left_lo;
   _UBYTE   pcx_left_hi;
   _UBYTE   pcx_upper_lo;
   _UBYTE   pcx_upper_hi;
   _UBYTE   pcx_right_lo;
   _UBYTE   pcx_right_hi;
   _UBYTE   pcx_lower_lo;
   _UBYTE   pcx_lower_hi;
   _UBYTE   encoding[2];
   _UBYTE   planes[2];
   _UBYTE   bitsperpixel[2];
} PCXHEADER;


typedef struct _pngheader
{
   _UBYTE   png_res1[1];                   /* 0x89 */
   _UBYTE   png_signature[3];              /* PNG */
   _UBYTE   png_res2[12];                  /* <???> */
   _UBYTE   png_res3[2];                   /* Fuer groessere Bilder? */
   _UBYTE   png_width_hi;                  /* Breite Low-Byte */
   _UBYTE   png_width_lo;                  /*        High-Byte */
   _UBYTE   png_res4[2];                   /* Fuer groessere Bilder? */
   _UBYTE   png_height_hi;                 /* Hoehe Low-Byte */
   _UBYTE   png_height_lo;                 /*       High-Byte */
} PNGHEADER;



/*******************************************************************************
*
*     GLOBAL VARIABLES
*
******************************************|************************************/

   /* --- UDO HTML navigation images flags --- */

GLOBAL _BOOL   bGifHmSaved,
                 bGifNoHmSaved;
GLOBAL _BOOL   bGifUpSaved,
                 bGifNoUpSaved;
GLOBAL _BOOL   bGifLfSaved,
                 bGifNoLfSaved;
GLOBAL _BOOL   bGifRgSaved,
                 bGifNoRgSaved;
GLOBAL _BOOL   bGifTpSaved;
GLOBAL _BOOL   bGifFoSaved;
GLOBAL _BOOL   bGifFcSaved;
GLOBAL _BOOL   bGifFsSaved;
GLOBAL _BOOL   bGifMwSaved;
GLOBAL _BOOL   bGifGerSaved,
                 bGifEngSaved;

   /* --- UDO HTML navigation images names --- */
   
GLOBAL FILE_ID sGifHmFull;                /* go to homepage */
GLOBAL FILE_ID sGifNoHmFull;
GLOBAL FILE_ID sGifUpFull;                /* go up one chapter */
GLOBAL FILE_ID sGifNoUpFull;
GLOBAL FILE_ID sGifLfFull;                /* go to previous page */
GLOBAL FILE_ID sGifNoLfFull;
GLOBAL FILE_ID sGifRgFull;                /* go to next page */
GLOBAL FILE_ID sGifNoRgFull;
GLOBAL FILE_ID sGifTpFull;                /* top of page */
GLOBAL FILE_ID sGifFoFull;                /* "Folder, opened" */
GLOBAL FILE_ID sGifFcFull;                /* "Folder, closed" */
GLOBAL FILE_ID sGifFsFull;                /* "Folder, spacer" */
GLOBAL FILE_ID sGifMwFull;                /* Logo: "Made with UDO" */
GLOBAL FILE_ID sGifGerFull;               /* Flag "German" */
GLOBAL FILE_ID sGifEngFull;               /* Flag "English" */


   /* --- UDO HTML navigation images sizes --- */

GLOBAL _UWORD   uiGifHmWidth,  uiGifHmHeight, uiGifNoHmWidth, uiGifNoHmHeight;
GLOBAL _UWORD   uiGifUpWidth,  uiGifUpHeight, uiGifNoUpWidth, uiGifNoUpHeight;
GLOBAL _UWORD   uiGifLfWidth,  uiGifLfHeight, uiGifNoLfWidth, uiGifNoLfHeight;
GLOBAL _UWORD   uiGifRgWidth,  uiGifRgHeight, uiGifNoRgWidth, uiGifNoRgHeight;
GLOBAL _UWORD   uiGifTpWidth,  uiGifTpHeight;
GLOBAL _UWORD   uiGifFoWidth,  uiGifFoHeight;
GLOBAL _UWORD   uiGifFcWidth,  uiGifFcHeight;
GLOBAL _UWORD   uiGifFsWidth,  uiGifFsHeight;
GLOBAL _UWORD   uiGifMwWidth,  uiGifMwHeight;
GLOBAL _UWORD   uiGifGerWidth, uiGifGerHeight;
GLOBAL _UWORD   uiGifEngWidth, uiGifEngHeight;





   /* --- UDO BMP navigation images flags --- */

GLOBAL _BOOL   bBmpFoSaved;
GLOBAL _BOOL   bBmpFcSaved;
GLOBAL _BOOL   bBmpMwSaved;

   /* --- UDO BMP navigation images names --- */
   
GLOBAL FILE_ID sBmpFoFull;            /* "Folder, opened" */
GLOBAL FILE_ID sBmpFcFull;            /* "Folder, closed" */
GLOBAL FILE_ID sBmpMwFull;            /* Logo: "Made with UDO" */





   /* --- UDO ST-Guide navigation images flags --- */

GLOBAL _BOOL   bImgFoSaved;
GLOBAL _BOOL   bImgFcSaved;
GLOBAL _BOOL   bImgMwSaved;

   /* --- UDO ST-Guide navigation images names --- */

GLOBAL FILE_ID sImgFoFull;                /* "Folder, opened" */
GLOBAL FILE_ID sImgFcFull;                /* "Folder, closed" */
GLOBAL FILE_ID sImgMwFull;                /* Logo: "Made with UDO" */



GLOBAL FILE_ID sEpsMwFull;                /* Logo: "Made with UDO" */
GLOBAL _BOOL bEpsMwSaved;

GLOBAL FILE_ID sPngMwFull;                /* Logo: "Made with UDO" */
GLOBAL _BOOL bPngMwSaved;



/*******************************************************************************
*
*     GLOBAL FUNCTION PROTOTYPES
*
******************************************|************************************/

GLOBAL void dump_all_images(void);

GLOBAL _BOOL c_img_output(const char *name, const char *caption, _BOOL visible, _BOOL limage);
GLOBAL void c_html_image_output(const char *name, const char *caption);
GLOBAL void c_bmp_output(const char *name, const char *caption, _BOOL visible);
GLOBAL _BOOL c_msp_output(const char *name, const char *caption, _BOOL visible);
GLOBAL _BOOL c_pcx_output(const char *name, const char *caption, _BOOL visible);
GLOBAL void c_eps_output(const char *name, const char *caption, _BOOL visible);
GLOBAL void c_png_output(const char *name, const char *caption, _BOOL visible);

GLOBAL void set_image_counter(const int i);

GLOBAL void set_image_alignment(void);

GLOBAL _BOOL get_picture_size(const char *name, char *found, _UWORD *uiW, _UWORD *uiH, _UWORD *bitcnt);

GLOBAL void init_module_img_pass2(void);
GLOBAL void init_module_img(void);

#endif   /* UDO_IMG_H */
