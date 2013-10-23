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
*                - VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*  2011:
*    fd  Jan 31: - file reformatted
*                - IMGTYPE_... introduced; image header definitions resorted
*
******************************************|************************************/

#ifndef UDO_IMG_H
#define   UDO_IMG_H





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
   UBYTE   bfType[2];          /*  0 */   /* File ID ('BM') */
   UBYTE   bfSize[4];          /*  2 */   /* File size */
   UBYTE   reserved1[2];       /*  6 */
   UBYTE   reserved2[2];       /*  8 */
   UBYTE   bfOffs[4];          /* 10 */
   UBYTE   biSize[4];          /* 14 */   /* Laenge BITMAP_INFO-Header */
   UBYTE   biWidth[4];         /* 18 */   /* Breite (4 bytes)*/
   UBYTE   biHeight[4];        /* 22 */   /* Hoehe (4 bytes) */
   UBYTE   biPlanes[2];        /* 26 */   /* Farbebenen */
   UBYTE   biBitCnt[2];        /* 28 */   /* Zahl der Bits pro Pixel */
   UBYTE   biCompr[4];         /* 30 */   /* Typ der Komprimierung */
   UBYTE   biSizeIm[4];        /* 34 */   /* Bildgroesse in Bytes */
   UBYTE   biXPels[4];         /* 38 */   /* horizontale Aufloesung */
   UBYTE   biYPels[4];         /* 42 */   /* vertikale Aufloesung */
   UBYTE   biClrUsed[4];       /* 46 */   /* Zahl der benutzten Farben */
   UBYTE   biClrImp[4];        /* 50 */   /* Zahl der wichtigen Farben */
   } BMPHEADER;


typedef struct _gifheader
   {
   UBYTE   gif_signature[3];              /* GIF */
   UBYTE   gif_version[3];                /* 87a oder 89a */
   UBYTE   gif_width_lo;                  /* Breite Low-Byte */
   UBYTE   gif_width_hi;                  /*        High-Byte */
   UBYTE   gif_height_lo;                 /* Hoehe Low-Byte */
   UBYTE   gif_height_hi;                 /*       High-Byte */
   } GIFHEADER;


typedef struct _imgheader
   {
   UBYTE   im_version[2];
   UBYTE   im_headerlength[2];            /* header length in words */
   UBYTE   im_nplanes[2];                 /* # of planes */
   UBYTE   im_patlen[2];
   UBYTE   im_pixwidth_hi;                /* pixel width  in mm/1000 */
   UBYTE   im_pixwidth_lo;
   UBYTE   im_pixheight_hi;               /* pixel height in mm/1000 */
   UBYTE   im_pixheight_lo;
   UBYTE   im_scanwidth_hi;               /* width in pixels */
   UBYTE   im_scanwidth_lo;
   UBYTE   im_nlines_hi;                  /* height in pixels */
   UBYTE   im_nlines_lo;
   } IMGHEADER;


typedef struct _jpgheader
   {
   UBYTE   jpg_unknown[2];                /* ??? */
   } JPGHEADER;


typedef struct _mspheader
   {
   UBYTE   msp_res[4];         /*  0 */   /* Magic 'LinS' */
   UBYTE   msp_width_lo;       /*  4 */   /* Breite */
   UBYTE   msp_width_hi;
   UBYTE   msp_height_lo;      /*  6 */   /* Hoehe */
   UBYTE   msp_height_hi;
   } MSPHEADER;


typedef struct _pcxheader
   {
   UBYTE   pcx_res[4];         /*  0 */
   UBYTE   pcx_left_lo;
   UBYTE   pcx_left_hi;
   UBYTE   pcx_upper_lo;
   UBYTE   pcx_upper_hi;
   UBYTE   pcx_right_lo;
   UBYTE   pcx_right_hi;
   UBYTE   pcx_lower_lo;
   UBYTE   pcx_lower_hi;
   } PCXHEADER;


typedef struct _pngheader
   {
   UBYTE   png_res1[1];                   /* 0x89 */
   UBYTE   png_signature[3];              /* PNG */
   UBYTE   png_res2[12];                  /* <???> */
   UBYTE   png_res3[2];                   /* Fuer groessere Bilder? */
   UBYTE   png_width_hi;                  /* Breite Low-Byte */
   UBYTE   png_width_lo;                  /*        High-Byte */
   UBYTE   png_res4[2];                   /* Fuer groessere Bilder? */
   UBYTE   png_height_hi;                 /* Hoehe Low-Byte */
   UBYTE   png_height_lo;                 /*       High-Byte */
   } PNGHEADER;

#endif   /* UDO_IMG_H */





/*******************************************************************************
*
*     GLOBAL VARIABLES
*
******************************************|************************************/

   /* --- UDO HTML navigation images flags --- */

GLOBAL BOOLEAN   bGifHmSaved, 
                 bGifNoHmSaved;
GLOBAL BOOLEAN   bGifUpSaved, 
                 bGifNoUpSaved;
GLOBAL BOOLEAN   bGifLfSaved, 
                 bGifNoLfSaved;
GLOBAL BOOLEAN   bGifRgSaved, 
                 bGifNoRgSaved;
GLOBAL BOOLEAN   bGifTpSaved;
GLOBAL BOOLEAN   bGifFoSaved;
GLOBAL BOOLEAN   bGifFcSaved;
GLOBAL BOOLEAN   bGifFsSaved;
GLOBAL BOOLEAN   bGifMwSaved;
GLOBAL BOOLEAN   bGifGerSaved, 
                  bGifEngSaved;

   /* --- UDO HTML navigation images names --- */
   
GLOBAL char   sGifHmFull[512],            /* go to homepage */
              sGifNoHmFull[512];
GLOBAL char   sGifUpFull[512],            /* go up one chapter */
              sGifNoUpFull[512];
GLOBAL char   sGifLfFull[512],            /* go to previous page */
              sGifNoLfFull[512];
GLOBAL char   sGifRgFull[512],            /* go to next page */
              sGifNoRgFull[512];
GLOBAL char   sGifTpFull[512];            /* Anfang der Seite */
GLOBAL char   sGifFoFull[512];            /* "Folder, opened" */
GLOBAL char   sGifFcFull[512];            /* "Folder, closed" */
GLOBAL char   sGifFsFull[512];            /* "Folder, spacer" */
GLOBAL char   sGifMwFull[512];            /* Logo: "Made with UDO" */
GLOBAL char   sGifGerFull[512];           /* Flagge "Deutsch" */
GLOBAL char   sGifEngFull[512];           /* Flagge "Englisch" */


   /* --- UDO HTML navigation images sizes --- */

GLOBAL UWORD   uiGifHmWidth,  uiGifHmHeight, uiGifNoHmWidth, uiGifNoHmHeight;
GLOBAL UWORD   uiGifUpWidth,  uiGifUpHeight, uiGifNoUpWidth, uiGifNoUpHeight;
GLOBAL UWORD   uiGifLfWidth,  uiGifLfHeight, uiGifNoLfWidth, uiGifNoLfHeight;
GLOBAL UWORD   uiGifRgWidth,  uiGifRgHeight, uiGifNoRgWidth, uiGifNoRgHeight;
GLOBAL UWORD   uiGifTpWidth,  uiGifTpHeight;
GLOBAL UWORD   uiGifFoWidth,  uiGifFoHeight;
GLOBAL UWORD   uiGifFcWidth,  uiGifFcHeight;
GLOBAL UWORD   uiGifFsWidth,  uiGifFsHeight;
GLOBAL UWORD   uiGifMwWidth,  uiGifMwHeight;
GLOBAL UWORD   uiGifGerWidth, uiGifGerHeight;
GLOBAL UWORD   uiGifEngWidth, uiGifEngHeight;





   /* --- UDO BMP navigation images flags --- */

GLOBAL BOOLEAN   bBmpFoSaved;
GLOBAL BOOLEAN   bBmpFcSaved;
GLOBAL BOOLEAN   bBmpMwSaved;

   /* --- UDO BMP navigation images names --- */
   
GLOBAL char   sBmpFoFull[512];            /* "Folder, opened" */
GLOBAL char   sBmpFcFull[512];            /* "Folder, closed" */
GLOBAL char   sBmpMwFull[512];            /* Logo: "Made with UDO" */





   /* --- UDO ST-Guide navigation images flags --- */

GLOBAL BOOLEAN   bImgFoSaved;
GLOBAL BOOLEAN   bImgFcSaved;
GLOBAL BOOLEAN   bImgMwSaved;

   /* --- UDO ST-Guide navigation images names --- */

GLOBAL char   sImgFoFull[512];            /* "Folder, opened" */
GLOBAL char   sImgFcFull[512];            /* "Folder, closed" */
GLOBAL char   sImgMwFull[512];            /* Logo: "Made with UDO" */





/*******************************************************************************
*
*     GLOBAL FUNCTION PROTOTYPES
*
******************************************|************************************/

GLOBAL void save_win_bmps(void);
GLOBAL void save_rtf_bmps(void);
GLOBAL void save_html_gifs(void);
GLOBAL void save_stg_imgs(void);

GLOBAL BOOLEAN c_img_output(const char *name, const char *caption, const BOOLEAN visible);
GLOBAL void c_gif_output(const char *name, const char *caption, const char *suffix, const int border);
GLOBAL void c_bmp_output(const char *name, const char *caption, const BOOLEAN visible);
GLOBAL BOOLEAN c_msp_output(const char *name, const char *caption, const BOOLEAN visible);
GLOBAL BOOLEAN c_pcx_output(const char *name, const char *caption, const BOOLEAN visible);
GLOBAL void c_eps_output(const char *name, const char *caption, const char *suffix, const BOOLEAN visible);
GLOBAL void c_png_output(const char *name, const char *caption, const char *suffix, const BOOLEAN visible);

GLOBAL void set_image_counter(const int i);

GLOBAL void set_image_alignment(void);

GLOBAL BOOLEAN get_gif_size(const char *filename, UWORD *uiW, UWORD *uiH);
GLOBAL BOOLEAN get_jpg_size(const char *filename, UWORD *uiW, UWORD *uiH);

GLOBAL void init_module_img_pass2(void);
GLOBAL void init_module_img(void);


/* +++ EOF +++ */
