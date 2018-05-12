/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : img.c
*  Symbol prefix: img
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
*  Co-Authors   : Volker Jansen (vj), Martin Osaka (MO), Christof Schardt (CS),
*                 Ulf Dunkel (fd), Gerhard Stoll (ggs)
*  Write access : fd, ggs
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - check uc4ToInt(): seems to be incomplete!
*
*-------------------------------------------------------------------------------
*  History:
*
*  1995:
*    DH  Jan xx: introduced
*  2001:
*    DH  Oct 02: last DH version
*  2010:
*    ggs May 16: c_img_output(): ST-Guide doesn't need a line before/after limage command
*  2011:
*    fd  Jan 31: - file reformatted
*                - new: get_image_header(): replaces proprietary get_NNNheader() functions
*  2013:
*    fd  Oct 23: HTML output supports HTML5
*    tho Oct 29: Disabled the nonsense for HTML5 that only works on the UDO webpage
*    fd  Oct 31: - c_calc_pngsize() added
*                - c_gif_output() renamed: c_html_image_output()
*    fd  Nov 02: HTML5 output of <img> tags cleaned
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include "udoport.h"
#include "constant.h"
#include "udo_type.h"
#include "chr.h"
#include "env.h"
#include "file.h"
#include "msg.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"
#include "udomem.h"
#include "upr.h"
#include "lang.h"
#include "img_html.h"					/* graphic data for GIF (used in HTML) */
#include "img_win.h"					/* graphic data for BMP (used in WinHelp) */
#include "img_stg.h"					/* graphic data for IMG (used in ST-Guide) */
#include "img_eps.h"					/* graphic data for PS (used in PostScript) */
#include "img_png.h"					/* graphic data for PNG (used in PDFLaTex) */

#include "export.h"
#include "img.h"





/*******************************************************************************
*
*     UNINITIALIZED LOCAL VARIABLES
*
******************************************|************************************/

LOCAL int image_counter;



/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define IMAGEDEBUG   1



/*******************************************************************************
*
*     LOCAL PROCEDURES
*
******************************************|************************************/

/*******************************************************************************
*
*  save_one_html_gif():
*     create GIF file for HTML when it is not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_one_html_gif(FILE_ID fileid, const _UBYTE *buffer, size_t length, _BOOL *ret)
{
	FILE *giffile;

	const char *name = file_lookup(fileid);

	giffile = fopen(name, "rb");		/* try to read GIF file */

	if (!giffile)						/* doesn't exist here */
	{
		giffile = myFwbopen(name, FTGIF);	/* create new GIF file */

		if (giffile)
		{
			fwrite(buffer, 1, length, giffile);
			fclose(giffile);
			*ret = TRUE;
		} else
		{
			error_open_outfile(name);
		}
	} else								/* yes: GIF file exists already */
	{
		fclose(giffile);				/* just close it */
		*ret = TRUE;
	}

	save_upr_entry_image(name);
}





/*******************************************************************************
*
*  save_html_gifs():
*     create a bunch of GIF files for HTML when they are not available yet
*
*  Note:
*     GIFs are only created when the relevant files do not exist already!
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_html_gifs(void)
{
	if (bTestmode)						/* "--test" command used */
		return;							/* no output at all */

	if (!no_headlines || !no_bottomlines)	/* we're using headlines or bottomlines */
	{
		if (html_transparent_buttons)	/* TRANSPARENT navigation buttons */
		{
			save_one_html_gif(sGifHmFull, html_gif_hm_trans, sizeof(html_gif_hm_trans), &bGifHmSaved);
			save_one_html_gif(sGifNoHmFull, html_gif_nohm_trans, sizeof(html_gif_nohm_trans), &bGifNoHmSaved);

			if (!html_merge_node[TOC_NODE1])
			{
				save_one_html_gif(sGifUpFull, html_gif_up_trans, sizeof(html_gif_up_trans), &bGifUpSaved);
				save_one_html_gif(sGifLfFull, html_gif_lf_trans, sizeof(html_gif_lf_trans), &bGifLfSaved);
				save_one_html_gif(sGifRgFull, html_gif_rg_trans, sizeof(html_gif_rg_trans), &bGifRgSaved);
			}

			save_one_html_gif(sGifNoUpFull, html_gif_noup_trans, sizeof(html_gif_noup_trans), &bGifNoUpSaved);
			save_one_html_gif(sGifNoLfFull, html_gif_nolf_trans, sizeof(html_gif_nolf_trans), &bGifNoLfSaved);
			save_one_html_gif(sGifNoRgFull, html_gif_norg_trans, sizeof(html_gif_norg_trans), &bGifNoRgSaved);

			switch (iDocHtmlSwitchLanguage)
			{
			case TOGER:
				save_one_html_gif(sGifGerFull, html_gif_ger_trans, sizeof(html_gif_ger_trans), &bGifGerSaved);
				break;

			case TOENG:
				save_one_html_gif(sGifEngFull, html_gif_eng_trans, sizeof(html_gif_eng_trans), &bGifEngSaved);
				break;
			}
		} else							/* CLASSIC navigation buttons */
		{
			save_one_html_gif(sGifHmFull, html_gif_hm, sizeof(html_gif_hm), &bGifHmSaved);
			save_one_html_gif(sGifNoHmFull, html_gif_nohm, sizeof(html_gif_nohm), &bGifNoHmSaved);

			if (!html_merge_node[TOC_NODE1])
			{
				save_one_html_gif(sGifUpFull, html_gif_up, sizeof(html_gif_up), &bGifUpSaved);
				save_one_html_gif(sGifLfFull, html_gif_lf, sizeof(html_gif_lf), &bGifLfSaved);
				save_one_html_gif(sGifRgFull, html_gif_rg, sizeof(html_gif_rg), &bGifRgSaved);
			}

			save_one_html_gif(sGifNoUpFull, html_gif_noup, sizeof(html_gif_noup), &bGifNoUpSaved);
			save_one_html_gif(sGifNoLfFull, html_gif_nolf, sizeof(html_gif_nolf), &bGifNoLfSaved);
			save_one_html_gif(sGifNoRgFull, html_gif_norg, sizeof(html_gif_norg), &bGifNoRgSaved);

			switch (iDocHtmlSwitchLanguage)
			{
			case TOGER:
				save_one_html_gif(sGifGerFull, html_gif_ger, sizeof(html_gif_ger), &bGifGerSaved);
				break;

			case TOENG:
				save_one_html_gif(sGifEngFull, html_gif_eng, sizeof(html_gif_eng), &bGifEngSaved);
				break;
			}
		}
	}

	if (uses_udolink)
		save_one_html_gif(sGifMwFull, html_gif_mw, sizeof(html_gif_mw), &bGifMwSaved);

	if (uses_toplink)
		save_one_html_gif(sGifTpFull, html_gif_tp, sizeof(html_gif_tp), &bGifTpSaved);

	if (use_auto_toptocs)
	{
		save_one_html_gif(sGifFcFull, html_gif_fc, sizeof(html_gif_fc), &bGifFcSaved);
		save_one_html_gif(sGifFoFull, html_gif_fo, sizeof(html_gif_fo), &bGifFoSaved);
		save_one_html_gif(sGifFsFull, html_gif_fs, sizeof(html_gif_fs), &bGifFsSaved);
	}
}





/*******************************************************************************
*
*  save_one_win_bmp():
*     create BMP file for WinHelp when it is not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_one_win_bmp(FILE_ID fileid, const _UBYTE * buffer, size_t length, _BOOL * ret)
{
	FILE *bmpfile;
	const char *name = file_lookup(fileid);

	bmpfile = fopen(name, "rb");		/* try to read BMP file */

	if (!bmpfile)						/* doesn't exist here */
	{
		bmpfile = myFwbopen(name, FTBMP);	/* create new BMP file */

		if (bmpfile)
		{
			fwrite(buffer, 1, length, bmpfile);
			fclose(bmpfile);
			*ret = TRUE;
		} else
		{
			error_open_outfile(name);
		}
	} else								/* yes: BMP file exists already */
	{
		fclose(bmpfile);				/* just close it */
		*ret = TRUE;
	}

	save_upr_entry_image(name);
}





/*******************************************************************************
*
*  save_win_bmps():
*     create a bunch of BMP files for WinHelp when they are not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_win_bmps(void)
{
	if (bTestmode)						/* "--test" command used */
		return;							/* no output at all */

	if (uses_udolink)
		save_one_win_bmp(sBmpMwFull, win_bmp_mw, sizeof(win_bmp_mw), &bBmpMwSaved);

	if (use_auto_toptocs)
	{
		save_one_win_bmp(sBmpFcFull, win_bmp_fc, sizeof(win_bmp_fc), &bBmpFcSaved);
		save_one_win_bmp(sBmpFoFull, win_bmp_fo, sizeof(win_bmp_fo), &bBmpFoSaved);
	}
}





/*******************************************************************************
*
*  save_rtf_bmps():
*     create (a bunch of) BMP file(s) for RTF when they are not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_rtf_bmps(void)
{
	if (bTestmode)						/* "--test" command used */
		return;							/* no output at all */

	if (uses_udolink)
	{
		if (!bBmpMwSaved)
			save_one_win_bmp(sBmpMwFull, win_bmp_mw, sizeof(win_bmp_mw), &bBmpMwSaved);
	}
}


/*******************************************************************************
*
*  save_ipf_bmps():
*     create a bunch of BMP files for IPF when they are not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_ipf_bmps(void)
{
	if (bTestmode)
		return;

	if (uses_udolink)
	{
		if (!bBmpMwSaved)
			save_one_win_bmp(sBmpMwFull, win_bmp_mw, sizeof(win_bmp_mw), &bBmpMwSaved);
	}
}





/*******************************************************************************
*
*  save_one_stg_img():
*     create IMG file for ST-Guide when it is not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_one_stg_img(FILE_ID fileid, const _UBYTE * buffer, size_t length, _BOOL * ret)
{
	FILE *imgfile;
	const char *name = file_lookup(fileid);

	imgfile = fopen(name, "rb");		/* try to read IMG file */

	if (!imgfile)						/* doesn't exist here */
	{
		imgfile = myFwbopen(name, FTIMG);	/* create new IMG file */

		if (imgfile)
		{
			fwrite(buffer, 1, length, imgfile);
			fclose(imgfile);
			*ret = TRUE;
		} else
		{
			error_open_outfile(name);
		}
	} else								/* yes: BMP file exists already */
	{
		fclose(imgfile);				/* just close it */
		*ret = TRUE;
	}

	save_upr_entry_image(name);
}





/*******************************************************************************
*
*  save_stg_imgs():
*     create a bunch of IMG files for ST-Guide when they are not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_stg_imgs(void)
{
	if (bTestmode)						/* "--test" command used */
		return;							/* no output at all */

	if (uses_udolink)
		save_one_stg_img(sImgMwFull, stg_img_mw, sizeof(stg_img_mw), &bImgMwSaved);

	if (use_auto_toptocs)
	{
		save_one_stg_img(sImgFcFull, stg_img_fc, sizeof(stg_img_fc), &bImgFcSaved);
		save_one_stg_img(sImgFoFull, stg_img_fo, sizeof(stg_img_fo), &bImgFoSaved);
	}
}


/*******************************************************************************
*
*  save_one_eps():
*     create EPS file for PostScript/LaTeX when it is not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_one_eps(FILE_ID fileid, const char *const *buffer, const size_t length, _BOOL * ret)
{
	FILE *epsfile;
	size_t i;
	const char *name = file_lookup(fileid);

	epsfile = fopen(name, "rb");
	if (epsfile == NULL)
	{
		epsfile = myFwopen(name, FTEPS);
		if (epsfile != NULL)
		{
			for (i = 0; i < length; i++)
			{
				fputs(buffer[i], epsfile);
				fputc('\n', epsfile);
			}
			fclose(epsfile);
			*ret = TRUE;
		} else
		{
			error_open_outfile(name);
		}
	} else
	{
		fclose(epsfile);
		*ret = TRUE;
	}

	save_upr_entry_image(name);
}


/*******************************************************************************
*
*  save_tex_epss():
*     create a bunch of EPS files for LaTeX when they are not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_tex_epss(void)
{
	if (bTestmode)
		return;

	if (uses_udolink)
	{
		if (!bEpsMwSaved)
			save_one_eps(sEpsMwFull, tex_eps_mw, ArraySize(tex_eps_mw), &bEpsMwSaved);
	}
}


/*******************************************************************************
*
*  save_one_png():
*     create PNG file for PDFLaTeX when it is not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_one_png(FILE_ID fileid, const unsigned char *buffer, const size_t length, _BOOL * ret)
{
	FILE *pngfile;
	const char *name = file_lookup(fileid);

	pngfile = fopen(name, "rb");
	if (!pngfile)
	{
		pngfile = myFwbopen(name, FTPNG);
		if (pngfile)
		{
			fwrite(buffer, 1, length, pngfile);
			fclose(pngfile);
			*ret = TRUE;
		} else
		{
			error_open_outfile(name);
		}
	} else
	{
		fclose(pngfile);
		*ret = TRUE;
	}

	save_upr_entry_image(name);
}



/*******************************************************************************
*
*  save_pdf_pngs():
*     create a bunch of PNG files for PDFLaTeX when they are not available yet
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_pdf_pngs(void)
{
	if (bTestmode)
		return;

	if (uses_udolink)
	{
		save_one_png(sPngMwFull, pdf_png_mw, sizeof(pdf_png_mw), &bPngMwSaved);
	}
}





/*******************************************************************************
*
*     LOCAL HELPER PROCEDURES
*
******************************************|************************************/

/*******************************************************************************
*
*  get_image_header():
*     get header information of an image file
*
*  Return:
*     IMGHEADER in *head
*
******************************************|************************************/

LOCAL _BOOL get_image_header(const char *datei, int type, void *head)
{
	FILE *file;
	size_t elem;
	size_t size = 0;

	file = fopen(datei, "rb");			/* try to read image file */

	if (file == NULL)
		return FALSE;					/* failed */

	switch (type)						/* get size of image type header */
	{
	case IMGTYPE_IMG:
		size = sizeof(IMGHEADER);
		break;

	case IMGTYPE_BMP:
		size = sizeof(BMPHEADER);
		break;

	case IMGTYPE_GIF:
		size = sizeof(GIFHEADER);
		break;

	case IMGTYPE_PNG:
		size = sizeof(PNGHEADER);
		break;

	case IMGTYPE_JPG:
		size = sizeof(JPGHEADER);
		break;

	case IMGTYPE_MSP:
		size = sizeof(MSPHEADER);
		break;

	case IMGTYPE_PCX:
		size = sizeof(PCXHEADER);
		break;
	}

	elem = fread(head, size, 1, file);	/* read image header data */

	fclose(file);

	return elem > 0;
}





/*******************************************************************************
*
*  get_img_size():
*     get Dimensions of IMG file
*
*  Return:
*
******************************************|************************************/

LOCAL int get_img_size(FILE * file, _UWORD * w, _UWORD * h, _UWORD * bitcnt)
{
	size_t elem;
	IMGHEADER imghead;

	elem = fread(&imghead, sizeof(IMGHEADER), 1, file);

	if (elem > 0)
	{
		*w = imghead.im_pixwidth_hi * 256 + imghead.im_pixwidth_lo;
		*h = imghead.im_pixheight_hi * 256 + imghead.im_pixheight_lo;
		*bitcnt = imghead.im_nplanes[0] * 256 + imghead.im_nplanes[1];
		return TRUE;
	}
	return FALSE;
}



/*******************************************************************************
*
*  set_imgheader():
*     set header information of IMG file
*
*  Return:
*     IMGHEADER in *head
*
******************************************|************************************/

LOCAL int set_imgheader(const char *datei, IMGHEADER * head)
{
	FILE *file;
	size_t elem;

	file = fopen(datei, "r+");			/* open IMG file */

	if (file == NULL)
		return FALSE;
	/* write IMG header data */
	elem = fwrite(head, sizeof(IMGHEADER), 1, file);

	fclose(file);

	return elem > 0;
}



/*******************************************************************************
*
*  uc2ToInt():
*     convert 2 unsigned chars to integer
*
*  Return:
*     return value
*
******************************************|************************************/

LOCAL void uc2ToInt(const unsigned char *uc, _UWORD * i)
{
	*i = uc[0] + 256 * uc[1];
}





/*******************************************************************************
*
*  uc4ToInt():
*     convert 4 unsigned chars to integer (long???)
*
*  Return:
*     return value
*
******************************************|************************************/

LOCAL void uc4ToInt(const unsigned char *uc, _ULONG * i)
{
	*i = (_ULONG) uc[0] + ((_ULONG) uc[1] << 8) + ((_ULONG) uc[2] << 16) + ((_ULONG) uc[3] << 24);
}


/* ############################################################
   # Windows-Bitmaps
   ############################################################   */
LOCAL int get_bmp_size(FILE * file, _UWORD * w, _UWORD * h, _UWORD * bitcnt)
{
	BMPHEADER head;
	size_t elem;

	elem = fread(&head, sizeof(BMPHEADER), 1, file);

	if (elem > 0)
	{
		_ULONG lw,
		 lh;

		uc4ToInt(head.biWidth, &lw);
		uc4ToInt(head.biHeight, &lh);
		*w = (_UWORD) lw;
		*h = (_UWORD) lh;
		uc2ToInt(head.biBitCnt, bitcnt);
		return TRUE;
	}
	return FALSE;
}


LOCAL int get_msp_size(FILE * file, _UWORD * w, _UWORD * h)
{
	MSPHEADER mspheader;

	size_t elem;

	elem = fread(&mspheader, sizeof(MSPHEADER), 1, file);

	if (elem > 0)
	{
		*w = mspheader.msp_width_hi * 256 + mspheader.msp_width_lo;
		*h = mspheader.msp_height_hi * 256 + mspheader.msp_height_lo;
		return TRUE;
	}
	return FALSE;
}



/* ############################################################
   # Windows-PCX
   ############################################################   */
LOCAL int get_pcx_size(FILE * file, _UWORD * w, _UWORD * h, _UWORD * bitcnt)
{
	size_t elem;
	int left, right, upper, lower;
	PCXHEADER pcxheader;
	_UWORD planes, bpp;

	elem = fread(&pcxheader, sizeof(PCXHEADER), 1, file);

	if (elem > 0)
	{
		left = pcxheader.pcx_left_hi * 256 + pcxheader.pcx_left_lo;
		right = pcxheader.pcx_right_hi * 256 + pcxheader.pcx_right_lo;
		upper = pcxheader.pcx_upper_hi * 256 + pcxheader.pcx_upper_lo;
		lower = pcxheader.pcx_lower_hi * 256 + pcxheader.pcx_lower_lo;
		*w = right - left + 1;
		*h = lower - upper + 1;
		uc2ToInt(pcxheader.planes, &planes);
		uc2ToInt(pcxheader.bitsperpixel, &bpp);
		*bitcnt = planes * bpp;
		return TRUE;
	}
	return FALSE;
}


/* ############################################################
   # GIFs
   ############################################################   */
LOCAL _BOOL get_gifheader(FILE * file, GIFHEADER * gh)
{
	size_t elem;

	elem = fread(gh, sizeof(GIFHEADER), 1, file);
	return elem > 0;
}



/*******************************************************************************
*
*  calc_gifsize():
*     calculate size of GIF file
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void calc_gifsize(_UWORD * w, _UWORD * h, _UWORD * bitcnt, GIFHEADER * head)
{
	*w = (head->gif_width_hi * 256 + head->gif_width_lo);
	*h = (head->gif_height_hi * 256 + head->gif_height_lo);
	*bitcnt = (head->flags & 0x07) + 1;
}


/*******************************************************************************
*
*  get_gif_size():
*     get size of GIF image
*
*  return:
*      TRUE: everything is okay
*     FALSE: something went wrong
*
******************************************|************************************/

LOCAL _BOOL get_gif_size(FILE * file, _UWORD * w, _UWORD * h, _UWORD * bitcnt)
{
	GIFHEADER head;

	if (get_gifheader(file, &head))
	{
		calc_gifsize(w, h, bitcnt, &head);
		return TRUE;
	}
	return FALSE;
}




/* ############################################################
   # JPGs
   ############################################################   */

/*******************************************************************************
*
*  get_jpg_size():
*     calculate size of JPEG file
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL int get_jpg_size(FILE * file, _UWORD * w, _UWORD * h, _UWORD * bitcnt)
{
	UNUSED(file);
	UNUSED(w);
	UNUSED(h);
	UNUSED(bitcnt);
	return TRUE;
}




LOCAL void get_image_alignment(_BOOL * inside_left, _BOOL * inside_center, _BOOL * inside_right)
{
	*inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
	*inside_right = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);
	*inside_left = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_LEFT);

	if (!(*inside_center) && !(*inside_right) && !(*inside_left))
	{
		switch (image_alignment)
		{
		case ALIGN_CENT:
			*inside_center = TRUE;
			break;

		case ALIGN_RIGH:
			*inside_right = TRUE;
			break;
		}
	}
}


/*******************************************************************************
*
*     GLOBAL PROCEDURES
*
******************************************|************************************/

/*******************************************************************************
*
*  c_img_output():
*     IMG output
*
*  Return:
*      TRUE: OK
*     FALSE: Something is wrong with the picture
*
******************************************|************************************/

GLOBAL _BOOL c_img_output(const char *name, const char *caption, _BOOL visible, _BOOL limage)
{
	IMGHEADER imghead;					/* IMG file header */
	char n[256];
	char datei[MYFILE_FULL_LEN];
	char found[MYFILE_FULL_LEN];

	int img_xoff;						/* X offset in chars (for ST-Guide) */
	int img_cw;							/* char width        (for ST-Guide) */

	_UWORD width, height, bitcnt;
	int scanwidth, nlines;

	double tex_wmm;						/* image width  in mm (for TeX) */
	double tex_hmm;						/* image height in mm (for TeX) */

	double pix_wmm, pix_hmm;

	int indent;							/* indentation */
	int max_width;							/* maximum available width */

	_BOOL inside_center, inside_right, inside_left;

	if (no_images)
		return TRUE;

	strcpy(datei, name);
	change_sep_suffix(datei, ".img");

	if (!get_picture_size(datei, found, &width, &height, &bitcnt) || !get_image_header(found, IMGTYPE_IMG, &imghead))
	{
		return FALSE;
	}

	save_upr_entry_image(datei);

	width = imghead.im_pixwidth_hi * 256 + imghead.im_pixwidth_lo;
	height = imghead.im_pixheight_hi * 256 + imghead.im_pixheight_lo;
	scanwidth = imghead.im_scanwidth_hi * 256 + imghead.im_scanwidth_lo;
	nlines = imghead.im_nlines_hi * 256 + imghead.im_nlines_lo;

	get_image_alignment(&inside_left, &inside_center, &inside_right);
	switch (desttype)
	{
	case TOTEX:
		if (iTexVersion == TEX_LINDNER || iTexVersion == TEX_STRUNK)
		{
			if (caption[0] != EOS)
				outln("\\begin{figure}[hbt]");

			/* FIXME: bad idea to write a input file here */
			if (((int) width != 25400 / iTexDPI) || ((int) height != 25400 / iTexDPI))
			{
				width = 25400 / iTexDPI;
				height = 25400 / iTexDPI;

				imghead.im_pixwidth_hi = (_UBYTE) (width / 256);
				imghead.im_pixwidth_lo = (_UBYTE) (width - imghead.im_pixwidth_hi * 256);

				imghead.im_pixheight_hi = (_UBYTE) (height / 256);
				imghead.im_pixheight_lo = (_UBYTE) (height - imghead.im_pixheight_hi * 256);

				if (!set_imgheader(datei, &imghead))
				{
					error_write_img(datei);
					bErrorDetected = TRUE;
				}
			}

			pix_wmm = width / 1000.0;
			pix_hmm = height / 1000.0;

			tex_wmm = scanwidth * pix_wmm;
			tex_hmm = nlines * pix_hmm;

			outln("");
			outln("\\newdimen\\grwd \\newdimen\\grht");

			replace_char(datei, '\\', '/');

			sprintf(n, "\\centerline{\\hbox to %.2f mm{\\vbox to %.2f mm{\\vfil\\special{graphic img %s}}\\hfil}}",
					tex_wmm, tex_hmm, datei);

			outln(n);

			if (caption[0] != EOS)
			{
				out("\\caption{");
				out(caption);
				outln("}");
				outln("");
				outln("\\end{figure}");
				outln("");
			}
		}
		break;

	case TOSTG:
	case TOAMG:
#ifdef __MACOS__
		if (*datei == ':')
			datei++;

		replace_char(datei, ':', '\\');	/* MO: solange HypC nicht existiert */
#endif
		replace_char(datei, '\\', '/');

		img_cw = scanwidth / 8;

		indent = strlen_indent();

		max_width = (int) zDocParwidth - indent;

		img_xoff = indent + 1;

		if (inside_center)
		{
			/* Keine Umgebung offen, dann den ST-Guide zentrieren */
			/* lassen, ansonsten das Bild durch UDO zentrieren */

			if (indent == 0)
			{
				img_xoff = 0;			/* ab ST-Guide Rel. 15 */
			} else
			{
				img_xoff = (img_cw <= max_width) ? indent + 1 + (max_width - img_cw) / 2 : indent + 1;
			}
		}

		if (inside_right)
			img_xoff = (int) zDocParwidth - img_cw + 1;


		outln("");
		sprintf(n, "%s \"%s\" %d", limage ? "@limage" : "@image", datei, img_xoff);
		outln(n);

		if (caption[0] != EOS)
		{
			image_counter++;
			strcpy_indent(n);
			indent2space(n);
			out(n);

			if (visible)
				sprintf(n, "(%s %d:%s)", get_lang()->figure, image_counter, caption);
			else
				sprintf(n, "(%s)", caption);

			if (inside_center)
				strcenter(n, max_width);

			if (inside_right)
				strright(n, max_width);

			outln(n);
		}
		break;							/* TOSTG */
	}

	return TRUE;
}





/*******************************************************************************
*
*  c_html_image_output():
*     outputs image tag (HTML only)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_html_image_output(const char *name, const char *caption)
{
	char *n;
	char datei[MYFILE_FULL_LEN];
	char align[64];
	char sGifSize[64];
	_UWORD uiWidth, uiHeight, bitcnt;

	_BOOL inside_center, inside_right, inside_left;

	if (no_images)
		return;

	strcpy(datei, name);

	sGifSize[0] = EOS;

	/* change_sep_suffix(datei, sDocImgSuffix); */

	save_upr_entry_image(datei);

#ifdef __MACOS__
	if (*datei == ':')
		datei++;
	replace_char(datei, ':', '/');
#endif
	replace_char(datei, '\\', '/');

	get_image_alignment(&inside_left, &inside_center, &inside_right);

	strcpy(align, "<p>");

	if (inside_center)					/* Bild in einer center-Umgebung */
	{
#if 0
		if (html_doctype == HTML5)
		{
			strcpy(align, "<p class=\"UDO_p_align_center\">");
		} else
#endif
		{
			strcpy(align, "<p align=\"center\">");
		}
	}

	if (inside_right)					/* Bild in einer flushright-Umgebung */
	{
#if 0
		if (html_doctype == HTML5)
		{
			strcpy(align, "<p class=\"UDO_p_align_right\">");
		} else
#endif
		{
			strcpy(align, "<p align=\"right\">");
		}
	}

	if (!no_img_size && get_picture_size(datei, NULL, &uiWidth, &uiHeight, &bitcnt))
	{
		sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiWidth, uiHeight);
	}

	if (caption[0] != EOS)
		image_counter++;
	n = um_strdup_printf("%s<img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s>",
			align, datei, caption, caption, sGifSize, xhtml_closer);
	out(n);
	free(n);
	outln("</p>");
}





/*******************************************************************************
*
*  c_bmp_output():
*     BMP output (for WinHelp and emTeX)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_bmp_output(const char *name, const char *caption, _BOOL visible)
{
	FILE *file;
	char n[256];
	char datei[MYFILE_FULL_LEN];
	char filename[MYFILE_FULL_LEN];
	char alignOn[128];
	char alignOff[128];
	int xsize, ysize, xorg, yorg, counter;
	_UWORD width, height, bitcnt;
	int indent;
	char li[32];
	_UBYTE onebyte;
	_BOOL inside_center, inside_right, inside_left;

	if (no_images)
		return;

	strcpy(datei, name);

	change_sep_suffix(datei, ".bmp");

	get_image_alignment(&inside_left, &inside_center, &inside_right);

	save_upr_entry_image(datei);

	switch (desttype)
	{
	case TORTF:
		if (!get_picture_size(datei, filename, &width, &height, &bitcnt))
		{
			return;
		}

		file = fopen(filename, "rb");

		if (file == NULL)
			return;

		strcpy(alignOn, "ql");

		if (inside_center)
			strcpy(alignOn, "qc");

		if (inside_right)
			strcpy(alignOn, "qr");

		voutlnf("\\li%d", strlen_indent());	/* Now indent for pictures in environments too */

		voutlnf("{\\%s{\\apoanchor\\pard\\phmrg\\posxc\\pvpara\\posyc\\nowrap", alignOn);
		out("{\\pict\\dibitmap\\picscalex100\\picscaley100");
		voutlnf("\\wbmwidthbytes%d\\wbmbitspixel%d\\wbmplanes1\\picw%d\\pich%d",
				((width + 15) / 16) * 2, bitcnt, width, height);

		if (fseek(file, 14, SEEK_CUR) == 0)
		{
			counter = 0;

			while (fread(&onebyte, sizeof(char), 1, file) > 0)
			{
				voutf("%02x", onebyte);
				counter++;

				if (counter >= 64)
				{
					outln("");
					counter = 0;
				}
			}
		}

		fclose(file);

		outln("}}\\par\\par\\pard}");

		if (caption[0] != EOS)
		{
			image_counter++;

			alignOn[0] = EOS;

			if (inside_center)
				strcpy(alignOn, "\\qc ");

			if (inside_right)
				strcpy(alignOn, "\\qr ");

			if (visible)
			{
				/* sprintf(n, "%s %d: %s", get_lang()->figure, image_counter, caption); */

				sprintf(n,
						"{{\\*\\bkmkstart _tocimg%d}%s }{\\field{\\*\\fldinst {SEQ %s \\\\* ARABIC }}{\\fldrslt %d}}: %s{\\*\\bkmkend _Tocimg%d}",
						image_counter, get_lang()->figure, get_lang()->figure, image_counter, caption, image_counter);
			} else
			{
				sprintf(n, "%s", caption);
			}

			voutlnf("%s%s\\par\\pard\\par", alignOn, n);
		}
		break;

	case TOTEX:
		if (!get_picture_size(datei, NULL, &width, &height, &bitcnt))
			return;

		/* Hier muessen noch die Breite und Hoehe des Bildes in pt(!) */
		/* eingetragen werden */

		if (iTexVersion == TEX_EMTEX || iTexVersion == TEX_MIKTEX)
		{
			replace_char(datei, '\\', '/');
			outln("");

			voutlnf("%% Bitmap: %s", datei);
			voutlnf("%%  width: %d", width);
			voutlnf("%% height: %d", height);
			outln("");

			outln("%% Die folgenden Werte passen nur (fast) bei");
			outln("%% Screenshots, die bei 300 dpi ausgegeben werden!");
			outln("%% Es handelt sich nur um experimentelle Werte!");
			outln("%% \\caption{} fehlt auch noch!");

			xsize = width / 4;
			ysize = height / 4;
			xorg = 0;
			yorg = ysize;

			if (inside_center)
				outln("\\begin{center}");

			if (inside_right)
				outln("\\begin{flushright}");

			voutlnf("\\begin{picture}(%d,%d)", xsize, ysize);
			voutlnf("    \\put(%d,%d){\\special{em:graph %s}}", xorg, yorg, datei);
			outln("\\end{picture}");

			if (inside_center)
				outln("\\end{center}");

			if (inside_right)
				outln("\\end{flushright}");

			outln("");
		}
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		replace_char(datei, '\\', '/');

		/* Bilder umgebungsabhaengig positionieren */
		alignOn[0] = EOS;
		alignOff[0] = EOS;

		li[0] = EOS;
		indent = strlen_indent();

		if (indent > 0)
			sprintf(li, "\\li%d", indent);

		if (inside_center)				/* Bild in einer center-Umgebung */
		{
			strcpy(alignOn, "\\qc{");
			strcpy(alignOff, "}");
		}

		if (inside_right)				/* Bild in einer flushright-Umgebung */
		{
			strcpy(alignOn, "\\qr{");
			strcpy(alignOff, "}");
		}

		if (bDocInlineBitmaps)
			voutlnf("%s%s\\{bmcwd %s\\}%s\\par\\pard\\par", li, alignOn, datei, alignOff);
		else
			voutlnf("%s%s\\{bmc %s\\}%s\\par\\pard\\par", li, alignOn, datei, alignOff);

		if (caption[0] != EOS)
		{
			image_counter++;

			if (visible)
			{
				voutlnf("%s%s(%s %d: %s)%s\\par\\pard\\par",
						li, alignOn, get_lang()->figure, image_counter, caption, alignOff);
			} else
			{
				voutlnf("%s%s(%s)%s\\par\\pard\\par", li, alignOn, caption, alignOff);
			}
		}
		break;

	case TOIPF:
		if (inside_center)
			strcpy(n, " align=center ");
		else if (inside_right)
			strcpy(n, " align=right ");
		else
			strcpy(n, " align=left ");

		voutlnf(":artwork%sname='%s'.", n, datei);
		break;
	}
}





/*******************************************************************************
*
*  c_msp_output():
*     MSP output (emTeX)
*
*  return:
*      TRUE: OK
*     FALSE: Something is wrong with the picture
*
******************************************|************************************/

GLOBAL _BOOL c_msp_output(const char *name, const char *caption, _BOOL visible)
{
	char n[256];
	char datei[MYFILE_FULL_LEN];
	int xsize, ysize, xorg, yorg;
	_UWORD width, height, bitcnt;
	_BOOL inside_center, inside_right, inside_left;

	if (no_images)
		return FALSE;

	strcpy(datei, name);

	change_sep_suffix(datei, ".msp");
	get_image_alignment(&inside_left, &inside_center, &inside_right);
	save_upr_entry_image(datei);

	switch (desttype)
	{
	case TOTEX:
		if (iTexVersion == TEX_EMTEX || iTexVersion == TEX_MIKTEX)
		{
			if (!get_picture_size(datei, NULL, &width, &height, &bitcnt))
			{
				return FALSE;
			}

			replace_char(datei, '\\', '/');
			outln("");

#if IMAGEDEBUG
			voutlnf("%% Bitmap: %s", datei);
			voutlnf("%%  width: %u", width);
			voutlnf("%% height: %u", height);
			outln("");
#endif

			xsize = width * 72 / iTexDPI;
			ysize = height * 72 / iTexDPI;

			xorg = 0;
			yorg = ysize;

			voutlnf("\\setlength{\\unitlength}{%fmm}", 25.4 / iTexDPI);
			outln("\\begin{figure}[htb]");

			if (inside_center)
				outln("\\begin{center}");

			if (inside_right)
				outln("\\begin{flushright}");

			sprintf(n, "\\begin{picture}(%d,%d)", xsize, ysize);
			outln(n);

			sprintf(n, "    \\put(%d,%d){\\special{em:graph %s}}", xorg, yorg, datei);
			outln(n);

			outln("\\end{picture}");

			if (inside_center)
				outln("\\end{center}");

			if (inside_right)
				outln("\\end{flushright}");

			if (caption[0] != EOS)
			{
				sprintf(n, "\\caption{%s}", caption);
				outln(n);
			}
			outln("\\end{figure}");
			outln("");
		}
		break;
	}

	UNUSED(visible);

	return TRUE;
}





/*******************************************************************************
*
*  c_pcx_output():
*     PCX output (emTeX)
*
*  return:
*      TRUE: OK
*     FALSE: Something is wrong with the picture
*
******************************************|************************************/

GLOBAL _BOOL c_pcx_output(const char *name, const char *caption, _BOOL visible)
{
	char n[256];
	char datei[MYFILE_FULL_LEN];
	int xsize, ysize, xorg, yorg;
	_UWORD width, height, bitcnt;
	_BOOL inside_center, inside_right, inside_left;

	if (no_images)
		return FALSE;

	strcpy(datei, name);

	change_sep_suffix(datei, ".pcx");

	get_image_alignment(&inside_left, &inside_center, &inside_right);

	save_upr_entry_image(datei);

	switch (desttype)
	{
	case TOTEX:
		if (iTexVersion == TEX_EMTEX || iTexVersion == TEX_MIKTEX)
		{
			if (!get_picture_size(datei, NULL, &width, &height, &bitcnt))
			{
				return FALSE;
			}

			replace_char(datei, '\\', '/');
			outln("");

#if IMAGEDEBUG
			voutlnf("%% Bitmap: %s", datei);
			voutlnf("%%  width: %u", width);
			voutlnf("%% height: %u", height);
			outln("");
#endif
			xsize = width * 72 / iTexDPI;
			ysize = height * 72 / iTexDPI;

			xorg = 0;
			yorg = ysize;

			voutlnf("\\setlength{\\unitlength}{%fmm}", 25.4 / iTexDPI);
			outln("\\begin{figure}[htb]");

			if (inside_center)
				outln("\\begin{center}");

			if (inside_right)
				outln("\\begin{flushright}");

			sprintf(n, "\\begin{picture}(%d,%d)", xsize, ysize);
			outln(n);

			sprintf(n, "    \\put(%d,%d){\\special{em:graph %s}}", xorg, yorg, datei);
			outln(n);

			outln("\\end{picture}");

			if (inside_center)
				outln("\\end{center}");

			if (inside_right)
				outln("\\end{flushright}");

			if (caption[0] != EOS)
			{
				sprintf(n, "\\caption{%s}", caption);
				outln(n);
			}

			outln("\\end{figure}");
			outln("");
		}
		break;
	}

	UNUSED(visible);

	return TRUE;
}





/*******************************************************************************
*
*  c_eps_output():
*     EPS output (LyX, TeX & PDFLaTeX)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_eps_output(const char *name, const char *caption, _BOOL visible)
{
	char datei[MYFILE_FULL_LEN];
	_BOOL inside_center, inside_right, inside_left;

	UNUSED(visible);

	if (no_images)
		return;

	strcpy(datei, name);

	change_sep_suffix(datei, ".eps");
	get_image_alignment(&inside_left, &inside_center, &inside_right);
	save_upr_entry_image(datei);

#ifdef __MACOS__
	if (*datei == ':')
		datei++;
	replace_char(datei, ':', '/');
#endif
	replace_char(datei, '\\', '/');

	switch (desttype)
	{
	case TOLYX:
		outln("\\begin_inset Graphics");
		voutlnf("\tfilename %s", datei);
		outln("");
		outln("\\end_inset");
		outln("");
		if (caption[0] != EOS)
		{
			outln("\\begin_inset Float figure");
			outln("wide false");
			outln("collapsed false");
			outln("");
			outln("\\layout Caption");
			outln("");
			outln(caption);
			outln("\\end_inset");
			outln("");
		}
		break;

	case TOTEX:
	case TOPDL:
		if (caption[0] != EOS)
			outln("\\begin{figure}[hbt]");

		if (inside_center)
			outln("\\begin{center}");

		if (inside_right)
			outln("\\begin{flushright}");

		voutlnf("\\includegraphics{%s}", datei);

		if (caption[0] != EOS)
		{
			image_counter++;
			voutlnf("\\caption{%s}", caption);
		}
		if (inside_center)
			outln("\\end{center}");

		if (inside_right)
			outln("\\end{flushright}");

		if (caption[0] != EOS)
			outln("\\end{figure}");
		break;
	}
}





/*******************************************************************************
*
*  c_png_output():
*     PNG output (PDFLaTeX only)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_png_output(const char *name, const char *caption, _BOOL visible)
{
	char datei[MYFILE_FULL_LEN];
	_UWORD uiWidth, uiHeight, bitcnt;
	_BOOL inside_center, inside_right, inside_left;

	if (no_images)
		return;

	strcpy(datei, name);

	change_sep_suffix(datei, ".png");

	save_upr_entry_image(datei);

	get_image_alignment(&inside_left, &inside_center, &inside_right);

	if (caption[0] != EOS)
		outln("\\begin{figure}[hbt]");

	if (inside_center)
		outln("\\begin{center}");

	if (inside_right)
		outln("\\begin{flushright}");

	get_picture_size(datei, NULL, &uiWidth, &uiHeight, &bitcnt);
#if IMAGEDEBUG
	voutlnf("%% PNG information of %s", datei);
	voutlnf("%%     width:  %u", uiWidth);
	voutlnf("%%     height: %u", uiHeight);
	voutlnf("%%     bitcnt: %u", bitcnt);
#endif

#ifdef __MACOS__
	if (*datei == ':')
		datei++;
	replace_char(datei, ':', '/');
#endif
	replace_char(datei, '\\', '/');

	outln("\\mbox{");
	/* Rechne Zielbreite in mm aus : */
	/* uiWidth sind Pixel. 90 dpi. Verkleinere so, dass 180 dpi. Dann auf mm */
	/* umrechnen, also: uiWidth / 180 * 25.4                                 */

	voutlnf("\\pdfximage width %umm {%s}\\pdfrefximage\\pdflastximage", uiWidth * 254 / 1800, datei);

/* old:
   voutlnf("\\pdfximage{%s}\\pdfrefximage\\pdflastximage", datei);
*/

	outln("}");

	if (caption[0] != EOS)
	{
		image_counter++;
		voutlnf("\\caption{%s}", caption);
	}

	if (inside_center)
		outln("\\end{center}");

	if (inside_right)
		outln("\\end{flushright}");

	if (caption[0] != EOS)
		outln("\\end{figure}");

	UNUSED(visible);
}





/*******************************************************************************
*
*  set_image_alignment():
*     set image alignment
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void set_image_alignment(void)
{
	char s[256];

	tokcpy2(s, 256);

	if (strstr(s, "center") != NULL)
	{
		image_alignment = ALIGN_CENT;
		return;
	}

	if (strstr(s, "left") != NULL)
	{
		image_alignment = ALIGN_LEFT;
		return;
	}

	if (strstr(s, "right") != NULL)
	{
		image_alignment = ALIGN_RIGH;
		return;
	}
}





/*******************************************************************************
*
*  set_image_counter():
*     change image counter
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void set_image_counter(const int i)
{
	image_counter = i - 1;

	if (image_counter < 0)
		image_counter = 0;
}



/*******************************************************************************
*
*  get_png_size():
*     get size of PNG image
*
*  return:
*      TRUE: everything is okay
*     FALSE: something went wrong
*
******************************************|************************************/

LOCAL unsigned long png_get_uint_32(unsigned char *buf)
{
	unsigned long i = ((unsigned long) (*buf) << 24) +
		((unsigned long) (*(buf + 1)) << 16) +
		((unsigned long) (*(buf + 2)) << 8) +
		(unsigned long) (*(buf + 3));
	return i;
}

LOCAL _BOOL get_png_size(FILE *file, _UWORD *uiW, _UWORD *uiH, _UWORD *bitcnt)
{
	char magic[8];
	unsigned char chunk_length[4];
	unsigned char chunk_name[4];

	unsigned char crc_bytes[4];
	unsigned char png_signature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
	unsigned char png_IHDR[4] = { 73, 72, 68, 82 };
	unsigned char ihdr_chunk[13];

	int size;
	_BOOL retV;
	unsigned long clength;
	unsigned char color_type, bit_depth;

	retV = FALSE;
	size = (int) fread(magic, 1, (int) sizeof(magic), file);
	if (size == sizeof(magic) && memcmp(magic, png_signature, 8) == 0)
	{
		for (;;)
		{
			if (fread(chunk_length, 1, 4, file) != 4 || fread(chunk_name, 1, 4, file) != 4)
				break;
			if (memcmp(chunk_name, png_IHDR, 4) == 0)
			{
				if (fread(ihdr_chunk, 1, sizeof(ihdr_chunk), file) == sizeof(ihdr_chunk))
				{
					*uiW = (_UWORD) png_get_uint_32(ihdr_chunk);
					*uiH = (_UWORD) png_get_uint_32(ihdr_chunk + 4);
					bit_depth = ihdr_chunk[8];
					color_type = ihdr_chunk[9];
					switch (color_type)
					{
					case 0:
						*bitcnt = bit_depth;
						break;			/* PNG_COLOR_TYPE_GRAY */
					case 3:
						*bitcnt = bit_depth;
						break;			/* PNG_COLOR_TYPE_PALETTE */
					case 4:
						*bitcnt = 2 * bit_depth;
						break;			/* PNG_TYPE_GRAY_ALPHA */
					case 2:
						*bitcnt = 3 * bit_depth;
						break;			/* PNG_TYPE_RGB */
					case 6:
						*bitcnt = 4 * bit_depth;
						break;			/* PNG_TYPE_RGB_ALPHA */
					}
					retV = TRUE;
				}
				break;
			}
			clength = png_get_uint_32(chunk_length);
			fseek(file, clength, SEEK_CUR);
			if (fread(crc_bytes, 1, 4, file) != 4)
				break;
		}
	}

	return retV;
}


/*******************************************************************************
*
*  get_picture_size():
*     get size of an image
*
*  return:
*      TRUE: everything is okay
*     FALSE: something went wrong
*
******************************************|************************************/

GLOBAL _BOOL get_picture_size(const char *name, char *found, _UWORD * uiW, _UWORD * uiH, _UWORD * bitcnt)
{
	char *p;
	char filename[MYFILE_FULL_LEN];
	FILE *fp;
	_BOOL flag;
	void (*error) (const char *name);

	*uiW = *uiH = 0;
	*bitcnt = 1;
	if (no_img_size)
		return TRUE;

	strcpy(filename, name);
	strinsert(filename, old_outfile.path);
	strinsert(filename, old_outfile.driv);
	path_adjust_separator(filename);
	flag = TRUE;
	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		strcpy(filename, name);
		build_image_filename(filename, "");
		path_adjust_separator(filename);
		fp = fopen(filename, "rb");
		if (fp == NULL)
			flag = FALSE;
	}
	if (flag && found != NULL)
		strcpy(found, filename);

	error = NULL;
	p = strrchr(filename, '.');
	if (p != NULL)
	{
		if (my_stricmp(p, ".gif") == 0)
		{
			error = error_read_gif;
			if (flag && !get_gif_size(fp, uiW, uiH, bitcnt))
				flag = FALSE;
		}
		if (my_stricmp(p, ".jpg") == 0 || my_stricmp(p, ".jpeg") == 0 || my_stricmp(p, ".jpe") == 0)
		{
			error = error_read_jpeg;
			if (flag && !get_jpg_size(fp, uiW, uiH, bitcnt))
				flag = FALSE;
		}
		if (my_stricmp(p, ".png") == 0)
		{
			error = error_read_png;
			if (flag && !get_png_size(fp, uiW, uiH, bitcnt))
				flag = FALSE;
		}
		if (my_stricmp(p, ".bmp") == 0)
		{
			error = error_read_bmp;
			if (flag && !get_bmp_size(fp, uiW, uiH, bitcnt))
				flag = FALSE;
		}
		if (my_stricmp(p, ".img") == 0)
		{
			error = error_read_img;
			if (flag && !get_img_size(fp, uiW, uiH, bitcnt))
				flag = FALSE;
		}
		if (my_stricmp(p, ".pcx") == 0)
		{
			error = error_read_pcx;
			if (flag && !get_pcx_size(fp, uiW, uiH, bitcnt))
				flag = FALSE;
		}
		if (my_stricmp(p, ".msp") == 0)
		{
			error = error_read_msp;
			if (flag && !get_msp_size(fp, uiW, uiH))
				flag = FALSE;
		}
	}
	if (fp != NULL)
		fclose(fp);
	if (!flag && error != NULL)
		(*error) (name);

	return flag;
}






/*******************************************************************************
*
*  init_gif_size():
*     ???
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void init_gif_size(FILE_ID fileid, const _UBYTE * def, _UWORD * uiW, _UWORD * uiH)
{
	GIFHEADER gh;
	_UWORD bitcnt;
	FILE *fp;
	const char *filename = file_lookup(fileid);

	*uiW = *uiH = 0;

	fp = fopen(filename, "rb");
	if (fp != NULL)
	{
		if (!get_gifheader(fp, &gh))
			memcpy(&gh, def, sizeof(GIFHEADER));
		fclose(fp);
	} else
	{
		memcpy(&gh, def, sizeof(GIFHEADER));
	}

	calc_gifsize(uiW, uiH, &bitcnt, &gh);
}




/*******************************************************************************
*
*  dump_all_images():
*     dump out all internal images
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void dump_all_images(void)
{
	_BOOL saved;

	saved = FALSE;
	save_one_html_gif(file_listadd(GIF_HM_NAME), html_gif_hm, sizeof(html_gif_hm), &saved);
	save_one_html_gif(file_listadd(GIF_NOHM_NAME), html_gif_nohm, sizeof(html_gif_nohm), &saved);
	save_one_html_gif(file_listadd(GIF_UP_NAME), html_gif_up, sizeof(html_gif_up), &saved);
	save_one_html_gif(file_listadd(GIF_NOUP_NAME), html_gif_noup, sizeof(html_gif_noup), &saved);
	save_one_html_gif(file_listadd(GIF_LF_NAME), html_gif_lf, sizeof(html_gif_lf), &saved);
	save_one_html_gif(file_listadd(GIF_NOLF_NAME), html_gif_nolf, sizeof(html_gif_nolf), &saved);
	save_one_html_gif(file_listadd(GIF_RG_NAME), html_gif_rg, sizeof(html_gif_rg), &saved);
	save_one_html_gif(file_listadd(GIF_NORG_NAME), html_gif_norg, sizeof(html_gif_norg), &saved);
	save_one_html_gif(file_listadd(GIF_GER_NAME), html_gif_ger, sizeof(html_gif_ger), &saved);
	save_one_html_gif(file_listadd(GIF_ENG_NAME), html_gif_eng, sizeof(html_gif_eng), &saved);

	save_one_html_gif(file_listadd("udo_hm_trans.gif"), html_gif_hm_trans, sizeof(html_gif_hm_trans), &saved);
	save_one_html_gif(file_listadd("udo_nohm_trans.gif"), html_gif_nohm_trans, sizeof(html_gif_nohm_trans), &saved);
	save_one_html_gif(file_listadd("udo_up_trans.gif"), html_gif_up_trans, sizeof(html_gif_up_trans), &saved);
	save_one_html_gif(file_listadd("udo_noup_trans.gif"), html_gif_noup_trans, sizeof(html_gif_noup_trans), &saved);
	save_one_html_gif(file_listadd("udo_lf_trans.gif"), html_gif_lf_trans, sizeof(html_gif_lf_trans), &saved);
	save_one_html_gif(file_listadd("udo_nolf_trans.gif"), html_gif_nolf_trans, sizeof(html_gif_nolf_trans), &saved);
	save_one_html_gif(file_listadd("udo_rg_trans.gif"), html_gif_rg_trans, sizeof(html_gif_rg_trans), &saved);
	save_one_html_gif(file_listadd("udo_norg_trans.gif"), html_gif_norg_trans, sizeof(html_gif_norg_trans), &saved);
	save_one_html_gif(file_listadd("udo_ger_trans.gif"), html_gif_ger_trans, sizeof(html_gif_ger_trans), &saved);
	save_one_html_gif(file_listadd("udo_eng_trans.gif"), html_gif_eng_trans, sizeof(html_gif_eng_trans), &saved);

	save_one_html_gif(file_listadd(GIF_MW_NAME), html_gif_mw, sizeof(html_gif_mw), &saved);
	save_one_html_gif(file_listadd(GIF_TP_NAME), html_gif_tp, sizeof(html_gif_tp), &saved);
	save_one_html_gif(file_listadd(GIF_FC_NAME), html_gif_fc, sizeof(html_gif_fc), &saved);
	save_one_html_gif(file_listadd(GIF_FO_NAME), html_gif_fo, sizeof(html_gif_fo), &saved);
	save_one_html_gif(file_listadd(GIF_FS_NAME), html_gif_fs, sizeof(html_gif_fs), &saved);

	save_one_win_bmp(file_listadd(BMP_MW_NAME), win_bmp_mw, sizeof(win_bmp_mw), &saved);
	save_one_win_bmp(file_listadd(BMP_FC_NAME), win_bmp_fc, sizeof(win_bmp_fc), &saved);
	save_one_win_bmp(file_listadd(BMP_FO_NAME), win_bmp_fo, sizeof(win_bmp_fo), &saved);

	save_one_stg_img(file_listadd(IMG_MW_NAME), stg_img_mw, sizeof(stg_img_mw), &saved);
	save_one_stg_img(file_listadd(IMG_FC_NAME), stg_img_fc, sizeof(stg_img_fc), &saved);
	save_one_stg_img(file_listadd(IMG_FO_NAME), stg_img_fo, sizeof(stg_img_fo), &saved);

	save_one_eps(file_listadd(EPS_MW_NAME), tex_eps_mw, ArraySize(tex_eps_mw), &saved);
	save_one_png(file_listadd(PNG_MW_NAME), pdf_png_mw, ArraySize(pdf_png_mw), &saved);
}



/*******************************************************************************
*
*  init_module_img_pass2():
*     find image sizes of UDO navigation GIFs
*
*  Notes:
*     Da init_module_img() vor pass1() aufgerufen wird, werden
*     die Ausmasse der internen GIFs benutzt, sofern noch keine
*     GIFs vorhanden sind. Sind welche vorhanden, so werden deren
*     Ausmasse verwendet. Es ist ja erlaubt, dass jemand die von
*     UDO erzeugten GIFs durch eigene ersetzt und die Ausmasse
*     muessen auch fuer die benutzerdefinierten Bilder korrekt sein.
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_img_pass2(void)
{
	switch (desttype)
	{
	case TOHTM:
	case TOMHH:
	case TOHAH:
		save_html_gifs();

		if (html_transparent_buttons)
		{
			init_gif_size(sGifUpFull, html_gif_up_trans, &uiGifUpWidth, &uiGifUpHeight);
			init_gif_size(sGifLfFull, html_gif_lf_trans, &uiGifLfWidth, &uiGifLfHeight);
			init_gif_size(sGifRgFull, html_gif_rg_trans, &uiGifRgWidth, &uiGifRgHeight);
			init_gif_size(sGifHmFull, html_gif_hm_trans, &uiGifHmWidth, &uiGifHmHeight);
			init_gif_size(sGifNoUpFull, html_gif_noup_trans, &uiGifNoUpWidth, &uiGifNoUpHeight);
			init_gif_size(sGifNoLfFull, html_gif_nolf_trans, &uiGifNoLfWidth, &uiGifNoLfHeight);
			init_gif_size(sGifNoRgFull, html_gif_norg_trans, &uiGifNoRgWidth, &uiGifNoRgHeight);
			init_gif_size(sGifNoHmFull, html_gif_nohm_trans, &uiGifNoHmWidth, &uiGifNoHmHeight);
			init_gif_size(sGifGerFull, html_gif_ger_trans, &uiGifGerWidth, &uiGifGerHeight);
			init_gif_size(sGifEngFull, html_gif_eng_trans, &uiGifEngWidth, &uiGifEngHeight);
		} else
		{
			init_gif_size(sGifUpFull, html_gif_up, &uiGifUpWidth, &uiGifUpHeight);
			init_gif_size(sGifLfFull, html_gif_lf, &uiGifLfWidth, &uiGifLfHeight);
			init_gif_size(sGifRgFull, html_gif_rg, &uiGifRgWidth, &uiGifRgHeight);
			init_gif_size(sGifHmFull, html_gif_hm, &uiGifHmWidth, &uiGifHmHeight);
			init_gif_size(sGifNoUpFull, html_gif_noup, &uiGifNoUpWidth, &uiGifNoUpHeight);
			init_gif_size(sGifNoLfFull, html_gif_nolf, &uiGifNoLfWidth, &uiGifNoLfHeight);
			init_gif_size(sGifNoRgFull, html_gif_norg, &uiGifNoRgWidth, &uiGifNoRgHeight);
			init_gif_size(sGifNoHmFull, html_gif_nohm, &uiGifNoHmWidth, &uiGifNoHmHeight);
			init_gif_size(sGifGerFull, html_gif_ger, &uiGifGerWidth, &uiGifGerHeight);
			init_gif_size(sGifEngFull, html_gif_eng, &uiGifEngWidth, &uiGifEngHeight);
		}

		init_gif_size(sGifFoFull, html_gif_fo, &uiGifFoWidth, &uiGifFoHeight);
		init_gif_size(sGifFcFull, html_gif_fc, &uiGifFcWidth, &uiGifFcHeight);
		init_gif_size(sGifFsFull, html_gif_fs, &uiGifFsWidth, &uiGifFsHeight);
		init_gif_size(sGifMwFull, html_gif_mw, &uiGifMwWidth, &uiGifMwHeight);
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		save_win_bmps();
		break;

	case TOSTG:
	case TOAMG:
		save_stg_imgs();
		break;

	case TORTF:
		save_rtf_bmps();
		break;

	case TOLYX:
		save_tex_epss();
		break;

	case TOPDL:
		save_pdf_pngs();
		break;

	case TOTEX:
		save_tex_epss();
		break;

	case TOIPF:
		save_ipf_bmps();
		break;
	}
}





/*******************************************************************************
*
*  init_module_img():
*     initialize UDO's IMG module
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_img(void)
{
	image_counter = 0;

	bGifUpSaved = FALSE;
	bGifLfSaved = FALSE;
	bGifRgSaved = FALSE;
	bGifHmSaved = FALSE;
	bGifFoSaved = FALSE;
	bGifFcSaved = FALSE;
	bGifFsSaved = FALSE;
	bGifMwSaved = FALSE;

	bBmpFoSaved = FALSE;
	bBmpFcSaved = FALSE;
	bBmpMwSaved = FALSE;

	bImgFoSaved = FALSE;
	bImgFcSaved = FALSE;
	bImgMwSaved = FALSE;
	bEpsMwSaved = FALSE;
	bPngMwSaved = FALSE;
}
