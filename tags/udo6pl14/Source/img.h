/*	############################################################
	# @(#) img.h
	# @(#)
	# @(#) Copyright (c) 1995-2001 by Dirk Hagedorn
	# @(#) Dirk Hagedorn (udo@dirk-hagedorn.de)
	#
	# This program is free software; you can redistribute it and/or
	# modify it under the terms of the GNU General Public License
	# as published by the Free Software Foundation; either version 2
	# of the License, or (at your option) any later version.
	# 
	# This program is distributed in the hope that it will be useful,
	# but WITHOUT ANY WARRANTY; without even the implied warranty of
	# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	# GNU General Public License for more details.
	# 
	# You should have received a copy of the GNU General Public License
	# along with this program; if not, write to the Free Software
	# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
	# 
	############################################################	*/

/*	############################################################
	# Typen
	############################################################	*/

#ifndef UDO_IMG_H
#define	UDO_IMG_H

typedef struct
{
	unsigned char	im_version[2];
	unsigned char	im_headerlength[2]; /* Laenge des Headers in Words */
	unsigned char	im_nplanes[2];      /* Anzahl Planes */
	unsigned char	im_patlen[2];
	unsigned char	im_pixwidth_hi;     /* Breites eines Pixels in mm/1000 */
	unsigned char	im_pixwidth_lo;
	unsigned char	im_pixheight_hi;    /* Hoehe eines Pixels in mm/1000 */
	unsigned char	im_pixheight_lo;
	unsigned char	im_scanwidth_hi;    /* Breite in Pixeln */
	unsigned char	im_scanwidth_lo;
	unsigned char	im_nlines_hi;       /* Hoehe in Pixeln */
	unsigned char	im_nlines_lo;
} IMGHEADER;


typedef struct
{
	unsigned char	bfType[2];			/*  0 */	/* File ID ('BM') */
	unsigned char	bfSize[4];			/*  2 */	/* File size */
	unsigned char	reserved1[2];		/*  6 */
	unsigned char	reserved2[2];		/*  8 */
	unsigned char	bfOffs[4];			/* 10 */
	unsigned char	biSize[4];			/* 14 */	/* Laenge BITMAP_INFO-Header */
	unsigned char	biWidth[4];			/* 18 */	/* Breite (4 bytes)*/
	unsigned char	biHeight[4];		/* 22 */	/* Hoehe (4 bytes) */
	unsigned char	biPlanes[2];		/* 26 */	/* Farbebenen */
	unsigned char	biBitCnt[2];		/* 28 */	/* Zahl der Bits pro Pixel */
	unsigned char	biCompr[4];			/* 30 */	/* Typ der Komprimierung */
	unsigned char	biSizeIm[4];		/* 34 */	/* Bildgroesse in Bytes */
	unsigned char	biXPels[4];			/* 38 */	/* horizontale Aufloesung */
	unsigned char	biYPels[4];			/* 42 */	/* vertikale Aufloesung */
	unsigned char	biClrUsed[4];		/* 46 */	/* Zahl der benutzten Farben */
	unsigned char	biClrImp[4];		/* 50 */	/* Zahl der wichtigen Farben */
} BMPHEADER;


typedef struct
{
	unsigned char	msp_res[4];		/*  0 */	/* Magic 'LinS' */
	unsigned char	msp_width_lo;	/*  4 */	/* Breite */
	unsigned char	msp_width_hi;
	unsigned char	msp_height_lo;	/*  6 */	/* Hoehe */
	unsigned char	msp_height_hi;
} MSPHEADER;


typedef struct
{
	unsigned char	pcx_res[4];		/*  0 */
	unsigned char	pcx_left_lo;	unsigned char	pcx_left_hi;
	unsigned char	pcx_upper_lo;	unsigned char	pcx_upper_hi;
	unsigned char	pcx_right_lo;	unsigned char	pcx_right_hi;
	unsigned char	pcx_lower_lo;	unsigned char	pcx_lower_hi;
} PCXHEADER;


typedef struct
{
	unsigned char	gif_signature[3];	/* GIF */
	unsigned char	gif_version[3];		/* 87a oder 89a */
	unsigned char	gif_width_lo;		/* Breite Low-Byte */
	unsigned char	gif_width_hi;		/*        High-Byte */
	unsigned char	gif_height_lo;		/* Hoehe Low-Byte */
	unsigned char	gif_height_hi;		/*       High-Byte */
} GIFHEADER;


typedef struct
{
	unsigned char	jpg_unknown[2];		/* ??? */
} JPGHEADER;


typedef struct
{
	unsigned char	png_res1[1];		/* 0x89 */
	unsigned char	png_signature[3];	/* PNG */
	unsigned char	png_res2[12];		/* <???> */
	unsigned char	png_res3[2];		/* Fuer groessere Bilder? */
	unsigned char	png_width_hi;		/* Breite Low-Byte */
	unsigned char	png_width_lo;		/*        High-Byte */
	unsigned char	png_res4[2];		/* Fuer groessere Bilder? */
	unsigned char	png_height_hi;		/* Hoehe Low-Byte */
	unsigned char	png_height_lo;		/*       High-Byte */
} PNGHEADER;

#endif	/* UDO_IMG_H */


/*	############################################################
	# Variablen
	############################################################	*/
GLOBAL BOOLEAN	bGifHmSaved, bGifNoHmSaved;
GLOBAL BOOLEAN	bGifUpSaved, bGifNoUpSaved;
GLOBAL BOOLEAN	bGifLfSaved, bGifNoLfSaved;
GLOBAL BOOLEAN	bGifRgSaved, bGifNoRgSaved;
GLOBAL BOOLEAN	bGifTpSaved;
GLOBAL BOOLEAN	bGifFoSaved;
GLOBAL BOOLEAN	bGifFcSaved;
GLOBAL BOOLEAN	bGifFsSaved;
GLOBAL BOOLEAN	bGifMwSaved;
GLOBAL BOOLEAN	bGifGerSaved, bGifEngSaved;

GLOBAL char		sGifHmFull[512], sGifNoHmFull[512];	/* Homepage					*/
GLOBAL char		sGifUpFull[512], sGifNoUpFull[512];	/* Namen der GIFs fuer HTML	*/
GLOBAL char		sGifLfFull[512], sGifNoLfFull[512];	/* vorherige Seite			*/
GLOBAL char		sGifRgFull[512], sGifNoRgFull[512];	/* naechste Seite			*/
GLOBAL char		sGifTpFull[512];	/* Anfang der Seite			*/
GLOBAL char		sGifFoFull[512];	/* "Folder, opened"			*/
GLOBAL char		sGifFcFull[512];	/* "Folder, closed"			*/
GLOBAL char		sGifFsFull[512];	/* "Folder, spacer"			*/
GLOBAL char		sGifMwFull[512];	/* Logo: "Made with UDO"	*/
GLOBAL char		sGifGerFull[512];	/* Flagge "Deutsch"			*/
GLOBAL char		sGifEngFull[512];	/* Flagge "Englisch"		*/

GLOBAL unsigned int uiGifHmWidth, uiGifHmHeight, uiGifNoHmWidth, uiGifNoHmHeight;
GLOBAL unsigned int uiGifUpWidth, uiGifUpHeight, uiGifNoUpWidth, uiGifNoUpHeight;
GLOBAL unsigned int uiGifLfWidth, uiGifLfHeight, uiGifNoLfWidth, uiGifNoLfHeight;
GLOBAL unsigned int uiGifRgWidth, uiGifRgHeight, uiGifNoRgWidth, uiGifNoRgHeight;
GLOBAL unsigned int uiGifTpWidth, uiGifTpHeight;
GLOBAL unsigned int uiGifFoWidth, uiGifFoHeight;
GLOBAL unsigned int uiGifFcWidth, uiGifFcHeight;
GLOBAL unsigned int uiGifFsWidth, uiGifFsHeight;
GLOBAL unsigned int uiGifMwWidth, uiGifMwHeight;
GLOBAL unsigned int uiGifGerWidth, uiGifGerHeight;
GLOBAL unsigned int uiGifEngWidth, uiGifEngHeight;

GLOBAL BOOLEAN	bBmpFoSaved;
GLOBAL BOOLEAN	bBmpFcSaved;
GLOBAL BOOLEAN	bBmpMwSaved;

GLOBAL char		sBmpFoFull[512];	/* "Folder, opened"			*/
GLOBAL char		sBmpFcFull[512];	/* "Folder, closed"			*/
GLOBAL char		sBmpMwFull[512];	/* Logo: "Made with UDO"	*/

GLOBAL BOOLEAN	bImgFoSaved;
GLOBAL BOOLEAN	bImgFcSaved;
GLOBAL BOOLEAN	bImgMwSaved;

GLOBAL char		sImgFoFull[512];	/* "Folder, opened"			*/
GLOBAL char		sImgFcFull[512];	/* "Folder, closed"			*/
GLOBAL char		sImgMwFull[512];	/* Logo: "Made with UDO"	*/

/*	############################################################
	# Funktionen
	############################################################	*/
GLOBAL void save_win_bmps ( void );
GLOBAL void save_rtf_bmps ( void );
GLOBAL void save_html_gifs ( void );
GLOBAL void save_stg_imgs ( void );

GLOBAL BOOLEAN c_img_output ( const char *name, const char *caption, const BOOLEAN visible );
GLOBAL void c_gif_output ( const char *name, const char *caption, const char *suffix, const int border );
GLOBAL void c_bmp_output ( const char *name, const char *caption, const BOOLEAN visible );
GLOBAL BOOLEAN c_msp_output ( const char *name, const char *caption, const BOOLEAN visible );
GLOBAL BOOLEAN c_pcx_output ( const char *name, const char *caption, const BOOLEAN visible );
GLOBAL void c_eps_output ( const char *name, const char *caption, const char *suffix, const BOOLEAN visible );
GLOBAL void c_png_output ( const char *name, const char *caption, const char *suffix, const BOOLEAN visible );

GLOBAL void set_image_counter ( const int i );

GLOBAL void set_image_alignment ( void );

GLOBAL BOOLEAN get_gif_size ( const char *filename, unsigned int *uiW, unsigned int *uiH);
GLOBAL BOOLEAN get_jpg_size ( const char *filename, unsigned int *uiW, unsigned int *uiH);

GLOBAL void init_module_img_pass2 ( void );
GLOBAL void init_module_img ( void );

/*	############################################################
	# img.h
	############################################################	*/

