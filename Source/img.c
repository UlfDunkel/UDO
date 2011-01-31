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
*    fd  Jan 31: file reformatted
*
******************************************|************************************/

/*******************************************************************************
*
*     CONSTANTS
*
******************************************|************************************/

#ifndef ID_IMG_C
#define ID_IMG_C
const char *id_img_c= "@(#) img.c       22.04.1999";
#endif





/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "import.h"
#include <stdio.h>
#include <string.h>
#include "portab.h"
#include "constant.h"
#include "udo_type.h"
#include "chr.h"
#include "env.h"
#include "file.h"
#include "msg.h"
#include "str.h"
#include "sty.h"
#include "udo.h"
#include "img_html.h"                     /* graphic data for GIF (used in HTML) */
#include "img_win.h"                      /* graphic data for BMP (used in WinHelp) */
#include "img_stg.h"                      /* graphic data for IMG (used in ST-Guide) */

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
*     LOCAL PROTOTYPES
*
******************************************|************************************/

LOCAL void save_one_html_gif(const char *name, const UBYTE *buffer, const size_t length, BOOLEAN *ret);
LOCAL void save_one_win_bmp(const char *name, const UBYTE *buffer, const size_t length, BOOLEAN *ret);
LOCAL void save_one_stg_img(const char *name, const UBYTE *buffer, const size_t length, BOOLEAN *ret);


LOCAL int get_imgheader(const char *datei, IMGHEADER *head);
LOCAL int set_imgheader(const char *datei, IMGHEADER *head);
LOCAL int get_bmpheader(const char *datei, BMPHEADER *head);
LOCAL int get_mspheader(const char *datei, MSPHEADER *head);
LOCAL int get_pcxheader(const char *datei, PCXHEADER *head);
LOCAL int get_gifheader(const char *datei, GIFHEADER *head);
LOCAL int get_jpgheader(const char *datei, JPGHEADER *head);
LOCAL int get_pngheader(const char *datei, PNGHEADER *head);

LOCAL void calc_gifsize(UWORD *w, UWORD *h, GIFHEADER *head);
LOCAL void calc_jpgsize(UWORD *w, UWORD *h, JPGHEADER *head);

LOCAL int uc2ToInt(UBYTE *uc, int *i);
LOCAL int uc4ToInt(UBYTE *uc, int *i);











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

LOCAL void save_one_html_gif(

const char    *name,     /* */
const UBYTE   *buffer,   /* */
const size_t   length,   /* */
BOOLEAN       *ret)      /* TRUE: file has been saved */
{
   FILE       *giffile;  /* */
   

   giffile = fopen(name, "rb");           /* try to read GIF file */
   
   if (!giffile)                          /* doesn't exist here */
   {
      giffile = myFwbopen(name, FTGIF);   /* create new GIF file */
      
      if (giffile)
      {
         fwrite(buffer, 1, length, giffile);
         fclose(giffile);
         *ret = TRUE;
      }
      else
         error_open_outfile(name);
   }
   else                                    /* yes: GIF file exists already */
      fclose(giffile);                     /* just close it */

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

GLOBAL void save_html_gifs(void)
{
   if (bTestmode)                         /* "--test" command used */
      return;                             /* no output at all */
   

   if (!no_headlines || !no_bottomlines)  /* we're using headlines or bottomlines */
   {
      if (html_transparent_buttons)       /* TRANSPARENT navigation buttons */
      {
         save_one_html_gif(sGifHmFull,   html_gif_hm_trans,   sizeof(html_gif_hm_trans),   &bGifHmSaved);
         save_one_html_gif(sGifNoHmFull, html_gif_nohm_trans, sizeof(html_gif_nohm_trans), &bGifNoHmSaved);
      
         if (!html_merge_node1)
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
         }
      }
      else                                /* CLASSIC navigation buttons */
      {
         save_one_html_gif(sGifHmFull,   html_gif_hm,   sizeof(html_gif_hm),   &bGifHmSaved);
         save_one_html_gif(sGifNoHmFull, html_gif_nohm, sizeof(html_gif_nohm), &bGifNoHmSaved);
      
         if (!html_merge_node1)
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

LOCAL void save_one_win_bmp(

const char    *name,     /* */
const UBYTE   *buffer,   /* */
const size_t   length,   /* */
BOOLEAN       *ret)      /* */
{
   FILE       *bmpfile;  /* */
   

   bmpfile = fopen(name, "rb");           /* try to read BMP file */
   
   if (!bmpfile)                          /* doesn't exist here */
   {
      bmpfile = myFwbopen(name, FTBMP);   /* create new BMP file */
      
      if (bmpfile)
      {
         fwrite(buffer, 1, length, bmpfile);
         fclose(bmpfile);
         *ret = TRUE;
      }
      else
         error_open_outfile(name);
   }
   else                                    /* yes: BMP file exists already */
      fclose(bmpfile);                     /* just close it */

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

GLOBAL void save_win_bmps(void)
{
   if (bTestmode)                         /* "--test" command used */
      return;                             /* no output at all */
   

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

GLOBAL void save_rtf_bmps(void)
{
   if (bTestmode)                         /* "--test" command used */
      return;                             /* no output at all */
   

   if (uses_udolink)
      save_one_win_bmp(sBmpMwFull, win_bmp_mw, sizeof(win_bmp_mw), &bBmpMwSaved);
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

LOCAL void save_one_stg_img(

const char    *name,     /* */
const UBYTE   *buffer,   /* */
const size_t   length,   /* */
BOOLEAN       *ret)      /* */
{
   FILE       *imgfile;  /* */
   

   imgfile = fopen(name, "rb");           /* try to read IMG file */
   
   if (!imgfile)                          /* doesn't exist here */
   {
      imgfile = myFwbopen(name, FTIMG);   /* create new IMG file */
      
      if (imgfile)
      {
         fwrite(buffer, 1, length, imgfile);
         fclose(imgfile);
         *ret = TRUE;
      }
      else
         error_open_outfile(name);
      
   }
   else                                    /* yes: BMP file exists already */
      fclose(imgfile);                     /* just close it */
   
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

GLOBAL void save_stg_imgs(void)
{
   if (bTestmode)                         /* "--test" command used */
      return;                             /* no output at all */
   

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
*     LOCAL HELPER PROCEDURES
*
******************************************|************************************/

/*******************************************************************************
*
*  get_imgheader():
*     get header information of IMG file
*
*  Return:
*     IMGHEADER in *head
*
******************************************|************************************/

LOCAL int get_imgheader(

const char  *datei,  /* */
IMGHEADER   *head)   /* */
{
   FILE     *file;   /* */
   size_t    elem;   /* */
   
   
   file = fopen(datei, "rb");             /* try to read image file */
   
   if (!file)
      return 0;
   
                                          /* read IMG header data */
   elem = fread(head, sizeof(IMGHEADER), 1, file);

   fclose(file);

   return (elem > 0);
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

LOCAL int set_imgheader(

const char  *datei,  /* */
IMGHEADER   *head)   /* */
{
   FILE     *file;   /* */
   size_t    elem;   /* */
   
   
   file= fopen(datei, "r+");              /* open IMG file */
   
   if (!file)
      return 0;
                                          /* write IMG header data */
   elem = fwrite(head, sizeof(IMGHEADER), 1, file);

   fclose(file);

   return (elem > 0);
}





/*******************************************************************************
*
*  get_bmpheader():
*     get header information of BMP file
*
*  Return:
*     BMPHEADER in *head
*
******************************************|************************************/

LOCAL int get_bmpheader(

const char  *datei,  /* */
BMPHEADER   *head)   /* */
{
   FILE     *file;   /* */
   size_t    elem;   /* */
   
   
   file = fopen(datei, "rb");             /* try to read image file */
   
   if (!file)
      return 0;
                                          /* read BMP header data */
   elem = fread(head, sizeof(BMPHEADER), 1, file);

   fclose(file);

   return (elem > 0);
}





/*******************************************************************************
*
*  get_mspheader():
*     set header information of MSP file
*
*  Return:
*     MSPHEADER in *head
*
******************************************|************************************/

LOCAL int get_mspheader(

const char  *datei,  /* */
MSPHEADER   *head)   /* */
{
   FILE     *file;   /* */
   size_t    elem;   /* */
   
   
   file = fopen(datei, "rb");             /* try to read image file */
   
   if (!file)
      return 0;
   
                                          /* read MSP header data */
   elem = fread(head, sizeof(MSPHEADER), 1, file);

   fclose(file);

   return (elem > 0);
}





/*******************************************************************************
*
*  get_mspheader():
*     set header information of Windows PCX file
*
*  Return:
*     PCXHEADER in *head
*
******************************************|************************************/

LOCAL int get_pcxheader(

const char  *datei,  /* */
PCXHEADER   *head)   /* */
{
   FILE     *file;   /* */
   size_t    elem;   /* */
   
   
   file = fopen(datei, "rb");             /* try to read image file */
   
   if (!file)
      return 0;
   
                                          /* read PCX header data */
   elem = fread(head, sizeof(PCXHEADER), 1, file);

   fclose(file);

   return (elem > 0);
}





/*******************************************************************************
*
*  get_gifheader():
*     set header information of GIF file
*
*  Return:
*     GIFHEADER in *head
*
******************************************|************************************/

LOCAL int get_gifheader(

const char  *datei,  /* */
GIFHEADER   *head)   /* */
{
   FILE     *file;   /* */
   size_t    elem;   /* */
   
   file = fopen(datei, "rb");             /* try to read image file */
   
   if (!file)
      return 0;
   
                                          /* read GIF header data */
   elem = fread(head, sizeof(GIFHEADER), 1, file);

   fclose(file);

   return (elem > 0);
}





/*******************************************************************************
*
*  get_jpgheader():
*     set header information of JPEG file
*
*  Return:
*     JPGHEADER in *head
*
******************************************|************************************/

LOCAL int get_jpgheader(

const char  *datei,  /* */
JPGHEADER   *head)   /* */
{
   FILE     *file;   /* */
   size_t    elem;   /* */
   
   
   file = fopen(datei, "rb");             /* try to read image file */
   
   if (!file)
      return 0;
   
                                          /* read JPEG header data */
   elem = fread(head, sizeof(JPGHEADER), 1, file);

   fclose(file);

   return (elem > 0);
}





/*******************************************************************************
*
*  get_pngheader():
*     set header information of PNG file
*
*  Return:
*     PNGHEADER in *head
*
******************************************|************************************/

LOCAL int get_pngheader(

const char  *datei,  /* */
PNGHEADER   *head)   /* */
{
   FILE     *file;   /* */
   size_t    elem;   /* */
   
   
   file = fopen(datei, "rb");             /* try to read image file */
   
   if (!file)
      return 0;
   
                                          /* read PNG header data */
   elem = fread(head, sizeof(PNGHEADER), 1, file);

   fclose(file);

   return (elem > 0);
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

LOCAL void calc_gifsize(

UWORD      *w,     /* */
UWORD      *h,     /* */
GIFHEADER  *head)  /* */
{
   *w = (head->gif_width_hi  * 256 + head->gif_width_lo);
   *h = (head->gif_height_hi * 256 + head->gif_height_lo);
}





/*******************************************************************************
*
*  calc_jpgsize():
*     calculate size of JPEG file
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void calc_jpgsize(

UWORD      *w,     /* */
UWORD      *h,     /* */
JPGHEADER  *head)  /* */
{
   /* <???> Hier fehlt noch viel */
   *w = 0;
   *h = 0;
   UNUSED(head);
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

LOCAL int uc2ToInt(

UBYTE  *uc,  /* */
int    *i)   /* */
{
   *i = uc[0] + 256 * uc[1];

   return *i;
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

LOCAL int uc4ToInt (

UBYTE  *uc,  /* */
int    *i)   /* */
{
   *i = uc[0] + 256 * uc[1];

   return *i;
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

GLOBAL BOOLEAN c_img_output(
const char     *name,           /* filename */
const char     *caption,        /* */
const BOOLEAN   visible)        /* */
{
   IMGHEADER    imghead;        /* IMG file header */
   char         n[256],         /* */
                datei[512],     /* */
                imgdatei[512];  /* */
   int          img_xoff,       /* X offset in chars (for ST-Guide) */
                img_cw;         /* char width        (for ST-Guide) */
   int          width,          /* */
                height,         /* */
                scanwidth,      /* */
                nlines;         /* */
   double       tex_wmm,        /* image width  in mm (for TeX) */
                tex_hmm;        /* image height in mm (for TeX) */
   double       pix_wmm,        /* */
                pix_hmm;        /* */
   int          indent,         /* indentation */
                max_width;      /* maximum available width */
   BOOLEAN      inside_center,  /* flags */
                inside_right,   /* */
                inside_left,    /* */
                flag;           /* */


   if (no_images)                         /* nothing to do here! */
      return TRUE;

   strcpy(datei, name);
   change_sep_suffix(datei, ".img");
   
   strcpy(imgdatei, datei);
   strinsert(imgdatei, outfile.path);
   strinsert(imgdatei, outfile.driv);
   path_adjust_separator(imgdatei);
   
   flag = get_imgheader(imgdatei, &imghead);

   if (!flag)
   {
      build_image_filename(datei, ".img");
      
      flag = get_imgheader(datei, &imghead);
      
      if (!flag)
      {
         error_read_img(datei);
         bErrorDetected = TRUE;
         return FALSE;
      }
   }

   save_upr_entry_image(datei);

   width     = imghead.im_pixwidth_hi  * 256 + imghead.im_pixwidth_lo;
   height    = imghead.im_pixheight_hi * 256 + imghead.im_pixheight_lo;
   scanwidth = imghead.im_scanwidth_hi * 256 + imghead.im_scanwidth_lo;
   nlines    = imghead.im_nlines_hi    * 256 + imghead.im_nlines_lo;

   inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
   inside_right  = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);
   inside_left   = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_LEFT);

   if (!inside_center && !inside_right && !inside_left)
   {
      switch (image_alignment)
      {
      case ALIGN_CENT:
         inside_center = TRUE;
         break;
         
      case ALIGN_RIGH:
         inside_right = TRUE;
      }
   }
   

   switch (desttype)
   {
   case TOTEX:
      if ( (iTexVersion == TEX_LINDNER) || (iTexVersion == TEX_STRUNK) )
      {   
         if (caption[0] != EOS)
            outln("\\begin{figure}[hbt]");
         

         if ( (width != 25400 / iTexDPI) || (height != 25400 / iTexDPI) )   
         {
            width  = 25400 / iTexDPI;
            height = 25400 / iTexDPI;

            imghead.im_pixwidth_hi  = (UBYTE)(width  / 256);
            imghead.im_pixwidth_lo  = (UBYTE)(width  - imghead.im_pixwidth_hi  * 256);

            imghead.im_pixheight_hi = (UBYTE)(height / 256);
            imghead.im_pixheight_lo = (UBYTE)(height - imghead.im_pixheight_hi * 256);

            if ( !set_imgheader(datei, &imghead) )
            {
               error_write_img(datei);
               bErrorDetected = TRUE;
            }
         }

         pix_wmm = width  / 1000.0;
         pix_hmm = height / 1000.0;
         
         tex_wmm = scanwidth * pix_wmm;
         tex_hmm = nlines    * pix_hmm;
      
         outln("");
         outln("\\newdimen\\grwd \\newdimen\\grht");
         
         replace_char(datei, "\\", "/");
         
         sprintf(n, "\\centerline{\\hbox to %.2f mm{\\vbox to %.2f mm{\\vfil\\special{graphic img %s}}\\hfil}}",
            tex_wmm,
            tex_hmm,
            datei);
            
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
#if __MACOS__
      if (*datei == ':')
         datei++;
         
      replace_char(datei, ":", "\\");     /* MO: solange HypC nicht existiert */
#endif

      img_cw = scanwidth / 8;

      indent = strlen_indent();

      max_width = (int)zDocParwidth - indent;

      img_xoff = indent + 1;
      
      if (inside_center)
      {
         /* Keine Umgebung offen, dann den ST-Guide zentrieren */
         /* lassen, ansonsten das Bild durch UDO zentrieren */
         
         if (indent == 0)
            img_xoff = 0;                 /* ab ST-Guide Rel. 15 */
         
         else
         {
            img_xoff = (img_cw <= max_width) 
               ?   indent + 1 + (max_width - img_cw) / 2
               :   indent + 1;
         }
      }
      
      if (inside_right)
         img_xoff = (int)zDocParwidth - img_cw + 1;
      

      sprintf(n, "@limage %s %d", datei, img_xoff);
      outln(n);

      if (caption[0] != EOS)
      {
         image_counter++;
         strcpy_indent(n);
         indent2space(n);
         out(n);
         
         if (visible)
            sprintf(n, "(%s %d:%s)", lang.figure, image_counter, caption);
         else
            sprintf(n, "(%s)", caption);
         
         if (inside_center)
            strcenter(n, max_width);
            
         if (inside_right)
            strright(n, max_width);
            
         outln(n);
      }
   }
   
   return TRUE;
}





/*******************************************************************************
*
*  c_gif_output():
*     outputs GIF image tag (HTML only)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_gif_output(

const char    *name,              /* */
const char    *caption,           /* */
const char    *suffix,            /* */
const int      border)            /* */
{
   char        n[512],            /* */
               datei[512],        /* */
               gifdatei[512];     /* */
   char        align[64];         /* */
   char        sWidth[32],        /* */
               sHeight[32];       /* */
   UWORD       uiWidth,           /* */
               uiHeight;          /* */
   BOOLEAN     inside_center,     /* */
               inside_right,      /* */
               inside_left,       /* */
               flag;              /* */
   GIFHEADER   gifhead;           /* */
/* JPGHEADER   jpghead; */        /* */
   char        closer[8] = "\0";  /* tag closer in XHTML */

   
   if (no_images)                         /* nothing to do here */
      return;                             /* bye ... */

   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");

   strcpy(datei, name);                   /*r6pl3*/
   
   sWidth[0]  = EOS;                      /*r6pl7*/
   sHeight[0] = EOS;                      /*r6pl7*/
   
   change_sep_suffix(datei, suffix);      /* PL6 */

   save_upr_entry_image(datei);

#if __MACOS__
   if (*datei == ':')
      datei++;
   
   replace_char(datei, ":", "/");
#else
   replace_char(datei, "\\", "/");
#endif

   inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
   inside_right  = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);
   inside_left   = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_LEFT);

   if (!inside_center && !inside_right && !inside_left)
   {
      switch (image_alignment)            /*r6pl9*/
      {
      case ALIGN_CENT:
         inside_center = TRUE;
         break;
      case ALIGN_RIGH:
         inside_right = TRUE;
      }
   }

   strcpy(align, "<p>");

   if (inside_center)                     /* Bild in einer center-Umgebung */
   {
      strcpy(align, "<p align=\"center\">");
   }

   if (inside_right)                      /* Bild in einer flushright-Umgebung */
   {
      strcpy(align, "<p align=\"right\">");
   }

   if (!no_img_size)
   {
      if (my_stricmp(suffix, ".gif") == 0)
      {
         strcpy(gifdatei, datei);
         strinsert(gifdatei, old_outfile.path);
         strinsert(gifdatei, old_outfile.driv);
         path_adjust_separator(gifdatei);
         flag = get_gifheader(gifdatei, &gifhead);

         if (!flag)
         {
            build_image_filename(gifdatei, suffix);
            flag = get_gifheader(gifdatei, &gifhead);

            if (!flag)
            {
               sWidth[0] = EOS;
               error_read_gif(gifdatei);
            }
         }

         if (flag)
         {
            calc_gifsize(&uiWidth, &uiHeight, &gifhead);
            sprintf(sWidth, " width=\"%u\"", uiWidth);
            sprintf(sHeight, " height=\"%u\"", uiHeight);
         }
      }
   }
   
   if (caption[0] == EOS)                 /* no image alt / title text available */
   {
                                          /* output empty alt + title contents for valid HTML */
      sprintf(n, "%s<img src=\"%s\" alt=\"\" title=\"\" border=\"%d\"%s%s%s></p>", 
         align, datei, border, sWidth, sHeight, closer);
      outln(n);
   }
   else                                   /* image alt / title text available */
   {
      image_counter++;
      sprintf(n, "%s<img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"%d\"%s%s%s></p>",
         align, datei, caption, caption, border, sWidth, sHeight, closer);
      outln(n);
   }
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

GLOBAL void c_bmp_output(

const char     *name, 
const char     *caption, 
const BOOLEAN   visible)
{
   FILE        *file;
   BMPHEADER    bmpheader;
   char         n[256], 
                datei[512], 
                alignOn[128], 
                alignOff[128];
   int          xsize, 
                ysize, 
                xorg, 
                yorg, 
                counter, 
                width, 
                height, 
                bitcnt, 
                planes;
   int          indent;
   char         li[32], 
                dump[32];
   UBYTE        onebyte;
   BOOLEAN      inside_center, 
                inside_right, 
                inside_left;

   if (no_images)                         /* nothing to do here */
      return;                             /* bye ... */

   strcpy(datei, name);

   change_sep_suffix(datei, ".bmp");

   inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
   inside_right  = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);
   inside_left   = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_LEFT);

   if (!inside_center && !inside_right && !inside_left)
   {
      switch (image_alignment)
      {
      case ALIGN_CENT:
         inside_center = TRUE;
         break;
         
      case ALIGN_RIGH:
         inside_right = TRUE;
      }
   }

   save_upr_entry_image(datei);

   switch (desttype)
   {
   case TORTF:
      if ( !get_bmpheader(datei, &bmpheader) )
      {                                   /* Fixed bug #0000017 in V6.5.2 [NHz] */
         if(strstr(datei, BMP_MW_NAME) != NULL)
            error_read_bmp(BMP_MW_NAME);
         else
            error_read_bmp(datei);

         bErrorDetected = TRUE;
         return;
      }

      file = fopen(datei, "rb");

      if (!file)
         return;

      uc4ToInt(bmpheader.biWidth,  &width);
                                          /* Fixed bug #0000056 in V6.5.2 [NHz] */
      uc4ToInt(bmpheader.biHeight, &height);
      uc2ToInt(bmpheader.biBitCnt, &bitcnt);
      uc2ToInt(bmpheader.biPlanes, &planes);


#if 1
      strcpy(alignOn, "ql");
      
      if (inside_center)
         strcpy(alignOn, "qc");
         
      if (inside_right)
         strcpy(alignOn, "qr");

      voutlnf("\\li%d", strlen_indent()); /* Now indent for pictures in environments too */

      voutlnf("{\\%s{\\apoanchor\\pard\\phmrg\\posxc\\pvpara\\posyc\\nowrap", alignOn);
      out("{\\pict\\dibitmap\\picscalex100\\picscaley100");
      voutlnf("\\wbmwidthbytes2\\wbmbitspixel%d\\wbmplanes%d\\picw%d\\pich%d",
            bitcnt, planes, width, height);
#else
      if (inside_center)
         out("{\\qc{\\plain");
         
      if (inside_right)
         out("{\\qr{\\plain");

      /* New in r6pl16 */
      voutlnf("\\li%d", strlen_indent()); /* Now indent for pictures in environments too */

      outln("{\\pict\\dibitmap\\picscalex100\\picscaley100");
      voutlnf("\\wbmwidthbytes2\\wbmbitspixel%d\\wbmplanes%d\\picw%d\\pich%d",
            bitcnt, planes, width, height);
#endif


                                          /* <???> byteweises Lesen ist langsam! */
      if (fread(dump, sizeof(char), 14, file) == 14)
      {
         counter = 0;
         
         while (fread(&onebyte, sizeof(char), 1, file) > 0)
         {
            sprintf(dump, "%02x", onebyte);
            out(dump);
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

         alignOn[0]= EOS;
         
         if (inside_center)
            strcpy(alignOn, "\\qc ");
            
         if (inside_right)
            strcpy(alignOn, "\\qr ");

         if (visible)
         {
            /* sprintf(n, "%s %d: %s", lang.figure, image_counter, caption); */

                                          /* Fixed bug #0000056 in V6.5.2 [NHz] */
            sprintf(n, "{{\\*\\bkmkstart _tocimg%d}%s }{\\field{\\*\\fldinst {SEQ %s \\\\* ARABIC }}{\\fldrslt %d}}: %s{\\*\\bkmkend _Tocimg%d}", image_counter, lang.figure, lang.figure, image_counter, caption, image_counter);
         }
         else
         {
            sprintf(n, "%s", caption);
         }

         voutlnf("%s%s\\par\\pard\\par", alignOn, n);
      }

      break;


   case TOTEX:
      if ( !get_bmpheader(datei, &bmpheader) )
      {
         error_read_bmp(datei);
         bErrorDetected = TRUE;
         return;
      }

      /* Hier muessen noch die Breite und Hoehe des Bildes in pt(!) */
      /* eingetragen werden */
      
      if (iTexVersion == TEX_EMTEX || iTexVersion == TEX_MIKTEX)
      {   
         replace_char(datei, "\\", "/");
         outln("");

         uc4ToInt(bmpheader.biWidth,  &width);
         uc4ToInt(bmpheader.biHeight, &height);

         sprintf(n, "%% Bitmap: %s", datei);
         outln(n);
         
         sprintf(n, "%%  width: %d", width);
         outln(n);
         
         sprintf(n, "%% height: %d", height);
         outln(n);
         
         outln("");
         
         outln("%% Die folgenden Werte passen nur (fast) bei");
         outln("%% Screenshots, die bei 300 dpi ausgegeben werden!");
         outln("%% Es handelt sich nur um experimentelle Werte!");
         outln("%% \\caption{} fehlt auch noch!");
         
         xsize=width  / 4;
         ysize=height / 4;
         xorg= 0;
         yorg= ysize;
         
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
            
         outln("");
      }
      
      break;



   case TOWIN:
   case TOWH4:
   case TOAQV:
      replace_char(datei, "\\", "/");

                                          /* PL12: Bilder umgebungsabhaengig positionieren */
      alignOn[0]  = EOS;
      alignOff[0] = EOS;
      
      li[0]  = EOS;
      indent = strlen_indent();
      
      if (indent > 0)
         sprintf(li, "\\li%d", indent);
      

      if (inside_center)                  /* Bild in einer center-Umgebung */
      {
         strcpy(alignOn, "\\qc{");
         strcpy(alignOff, "}");
      }
      
      if (inside_right)                   /* Bild in einer flushright-Umgebung */
      {
         strcpy(alignOn, "\\qr{");
         strcpy(alignOff, "}");
      }

      if (bDocInlineBitmaps)
         sprintf(n, "%s%s\\{bmcwd %s\\}%s\\par\\pard\n\\par", li, alignOn, datei, alignOff);
      else
         sprintf(n, "%s%s\\{bmc %s\\}%s\\par\\pard\n\\par", li, alignOn, datei, alignOff);
      

      outln(n);

      if (caption[0] != EOS)
      {
         image_counter++;
         
         if (visible)
         {   sprintf(n, "%s%s(%s %d: %s)%s\\par\\pard\n\\par",
                     li, alignOn, lang.figure, image_counter, caption, alignOff);
         }
         else
         {   sprintf(n, "%s%s(%s)%s\\par\\pard\n\\par",
                     li, alignOn, caption, alignOff);
         }
         
         outln(n);
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

GLOBAL BOOLEAN c_msp_output(

const char     *name,           /* */
const char     *caption,        /* */
const BOOLEAN   visible)        /* */
{
   MSPHEADER    mspheader;      /* */
   char         n[256],         /* */
                datei[512];     /* */
   int          xsize,          /* */
                ysize,          /* */
                xorg,           /* */
                yorg,           /* */
                width,          /* */
                height;         /* */
   BOOLEAN      inside_center,  /* */
                inside_right,   /* */
                inside_left;    /* */
                

   if (no_images)                         /* nothing to do here */
      return FALSE;
   

   strcpy(datei, name);

   change_sep_suffix(datei, ".msp");
   

   inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
   inside_right  = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);
   inside_left   = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_LEFT);

   if (!inside_center && !inside_right && !inside_left)
   {
      switch (image_alignment)
      {
      case ALIGN_CENT:
         inside_center = TRUE;
         break;
         
      case ALIGN_RIGH:
         inside_right = TRUE;
      }
   }

   save_upr_entry_image(datei);

   switch (desttype)
   {
   case TOTEX:
      if (iTexVersion == TEX_EMTEX || iTexVersion == TEX_MIKTEX)
      {
         if ( !get_mspheader(datei, &mspheader) )
         {
            error_read_msp(datei);
            bErrorDetected = TRUE;
            return(FALSE);
         }

         width  = mspheader.msp_width_hi  * 256 + mspheader.msp_width_lo;
         height = mspheader.msp_height_hi * 256 + mspheader.msp_height_lo;

         replace_char(datei, "\\", "/");
         outln("");
         
#if IMAGEDEBUG
         voutlnf("%% Bitmap: %s", datei);
         voutlnf("%%  width: %d", width);
         voutlnf("%% height: %d", height);
         outln("");
#endif
         
         xsize = width  * 72 / iTexDPI;
         ysize = height * 72 / iTexDPI;
         
         xorg  = 0;
         yorg  = ysize;

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

GLOBAL BOOLEAN c_pcx_output(

const char     *name,           /* */
const char     *caption,        /* */
const BOOLEAN   visible)        /* */
{
   PCXHEADER    pcxheader;      /* */
   char         n[256],         /* */
                datei[512];     /* */
   int          xsize,          /* */
                ysize,          /* */
                xorg,           /* */
                yorg,           /* */
                left,           /* */
                right,          /* */
                upper,          /* */
                lower,          /* */
                width,          /* */
                height;         /* */
   BOOLEAN      inside_center,  /* */
                inside_right,   /* */
                inside_left;    /* */
                

   if (no_images)                         /* nothing to do here */
      return FALSE;

   
   strcpy(datei, name);
   
   change_sep_suffix(datei, ".pcx");

   inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
   inside_right  = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);
   inside_left   = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_LEFT);

   if (!inside_center && !inside_right && !inside_left)
   {
      switch (image_alignment)
      {
         case ALIGN_CENT:
            inside_center = TRUE;
            break;
            
         case ALIGN_RIGH:
            inside_right = TRUE;
      }
   }

   save_upr_entry_image(datei);

   switch (desttype)
   {
   case TOTEX:
      if (iTexVersion == TEX_EMTEX || iTexVersion == TEX_MIKTEX)
      {
         if ( !get_pcxheader(datei, &pcxheader) )
         {
            error_read_pcx(datei);
            bErrorDetected = TRUE;
            return(FALSE);
         }

         replace_char(datei, "\\", "/");
         outln("");

         left  = pcxheader.pcx_left_hi  * 256 + pcxheader.pcx_left_lo;
         right = pcxheader.pcx_right_hi * 256 + pcxheader.pcx_right_lo;
         upper = pcxheader.pcx_upper_hi * 256 + pcxheader.pcx_upper_lo;
         lower = pcxheader.pcx_lower_hi * 256 + pcxheader.pcx_lower_lo;

#if IMAGEDEBUG
         voutlnf("%% Bitmap: %s", datei);
         voutlnf("%%   left: %d", left);
         voutlnf("%%  upper: %d", upper);
         voutlnf("%%  right: %d", right);
         voutlnf("%%  lower: %d", lower);
         outln("");
#endif
         
         width  = right - left  + 1;
         height = lower - upper + 1;
         
         xsize = width  * 72 / iTexDPI;
         ysize = height * 72 / iTexDPI;

         xorg  = 0;
         yorg  = ysize;

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
   }
   
   UNUSED(visible);

   return TRUE;
}





/*******************************************************************************
*
*  c_eps_output():
*     EPS output (LyX)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_eps_output(

const char     *name,           /* */
const char     *caption,        /* */
const char     *suffix,         /* */
const BOOLEAN   visible)        /* */
{
#if 0
   char         n[256];         /* */
   char         align[64];      /* */
   BOOLEAN      inside_center,  /* */
                inside_right;   /* */
#endif
   char         datei[512];     /* */


   if (no_images)                         /* nothing to do here */
      return;

   
   strcpy(datei, name);

   change_sep_suffix(datei, suffix);

   save_upr_entry_image(datei);
   
#if __MACOS__
   if (*datei == ':') datei++;
      replace_char(datei, ":", "/");
#else
   replace_char(datei, "\\", "/");
#endif

   switch (desttype)
   {
   case TOLYX:
      outln("\\begin_float fig");
      outln("\\layout LaTeX");
      outln("\\align center");
      outln("");
      
      outln("\\begin_inset Latex \\epsfig{");
      outln("");   
      
      outln("\\end_inset");
      outln("");
      
      voutlnf("file=%s", datei);
      outln("\\begin_inset Latex }");
      outln("");
      
      outln("\\end_inset");
      outln("");
      outln("");
      
      if (caption[0]!=EOS)
      {
         outln("\\layout Caption");
         outln("");
         
         outln(caption);
         outln("");
      }
      
      outln("\\end_float");
      outln("");
      break;
      
      
   case TOTEX:
      voutlnf("\\includegraphics{%s}", datei);
      
      if (caption[0] != EOS)
         voutlnf("\\caption{%s}", caption);
   }
   
   UNUSED(visible);
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

GLOBAL void c_png_output(

const char     *name,           /* */
const char     *caption,        /* */
const char     *suffix,         /* */
const BOOLEAN   visible)        /* */
{
   char         datei[512],     /* */
                pngdatei[512];  /* */
   UWORD        uiWidth,        /* */
                uiHeight;       /* */
   BOOLEAN      inside_center,  /* */
                inside_right,   /* */
                inside_left,    /* */
                flag;           /* */
   PNGHEADER    pnghead;        /* */

   if (no_images)                         /* nothing to do here */
      return;

   
   strcpy(datei, name);

   change_sep_suffix(datei, suffix);

   save_upr_entry_image(datei);

   inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
   inside_right  = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);
   inside_left   = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_LEFT);

   if (!inside_center && !inside_right && !inside_left)
   {
      switch (image_alignment)
      {
      case ALIGN_CENT:
         inside_center = TRUE;
         break;
         
      case ALIGN_RIGH:
         inside_right = TRUE;
      }
   }

   if (caption[0] != EOS)
      outln("\\begin{figure}[hbt]");

   if (inside_center)
      outln("\\begin{center}");
      
   if (inside_right)
      outln("\\begin{flushright}");

#if IMAGEDEBUG
   uiWidth = uiHeight= 0;
   
   if (my_stricmp(suffix, ".png") == 0)
   {
      strcpy(pngdatei, datei);
      
      path_adjust_separator(pngdatei);
      
      flag = get_pngheader(pngdatei, &pnghead);
      
      if (!flag)
      {
         build_image_filename(pngdatei, suffix);
         
         flag = get_pngheader(pngdatei, &pnghead);
         
         if (!flag)
            error_read_png(pngdatei);
      }

      if (flag)
      {
         uiWidth  = (pnghead.png_width_hi  * 256 + pnghead.png_width_lo);
         uiHeight = (pnghead.png_height_hi * 256 + pnghead.png_height_lo);
      }

   }
   
   voutlnf("%% PNG information of %s", datei);
   voutlnf("%%     width:  %u", uiWidth);
   voutlnf("%%     height: %u", uiHeight);
#endif

#if __MACOS__
   if (*datei == ':') datei++;
      replace_char(datei, ":", "/");
#else
   replace_char(datei, "\\", "/");
#endif

   outln("\\mbox{");
                                          /* Changed in V6.5.7 [NHz] */
                                          /* New V6.5.20 [CS] */
   /* Rechne Zielbreite in mm aus : */
   /* uiWidth sind Pixel. 90 dpi. Verkleinere so, dass 180 dpi. Dann auf mm */
   /* umrechnen, also: uiWidth / 180 * 25.4                                 */
   
   voutlnf("\\pdfximage width %umm {%s}\\pdfrefximage\\pdflastximage", uiWidth * 254 / 1800, datei);

/* old:
   voutlnf("\\pdfximage{%s}\\pdfrefximage\\pdflastximage", datei);
*/

   outln("}");

   if ( caption[0] != EOS)
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
   char   s[256];  /* */
   

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

GLOBAL void set_image_counter(

const int   i)  /* */
{
   image_counter = i - 1;
   
   if (image_counter < 0)
      image_counter = 0;
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

GLOBAL BOOLEAN get_gif_size(

const char    *filename,  /* */
UWORD         *uiW,       /* */
UWORD         *uiH)       /* */
{
   BOOLEAN     flag;      /* TRUE: GIF header could be read successfully */
   GIFHEADER   gh;        /* */
   

   *uiW = *uiH = 0;

   if (!no_img_size)                      /* we don't want to ignore image sizes */
   {
      flag = get_gifheader(filename, &gh);
      
      if (!flag)
         return FALSE;

      calc_gifsize(uiW, uiH, &gh);
   }

   return TRUE;
}





/*******************************************************************************
*
*  get_jpg_size():
*     get size of JPEG image
*
*  return:
*      TRUE: everything is okay
*     FALSE: something went wrong
*
******************************************|************************************/

GLOBAL BOOLEAN get_jpg_size(

const char    *filename,  /* */
UWORD         *uiW,       /* */
UWORD         *uiH)       /* */
{
   BOOLEAN     flag;      /* TRUE: JPEG header could be read successfully */
   JPGHEADER   jh;        /* */

   *uiW = *uiH = 0;

   if (!no_img_size)                      /* we don't want to ignore image sizes */
   {
      flag = get_jpgheader(filename, &jh);
      
      if (!flag)
         return FALSE;
      

      calc_jpgsize(uiW, uiH, &jh);
   }

   return TRUE;
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

LOCAL void init_gif_size(

const char    *filename,  /* */
const UBYTE   *def,       /* */
UWORD         *uiW,       /* */
UWORD         *uiH)       /* */
{
   BOOLEAN     flag;      /* TRUE: GIF header could be read successfully */
   GIFHEADER   gh;        /* */


   *uiW = *uiH = 0;

   flag = get_gifheader(filename, &gh);
   
   if (!flag)
      memcpy(&gh, def, sizeof(GIFHEADER));

   calc_gifsize(uiW, uiH, &gh);
}





/*******************************************************************************
*
*  init_gif_size():
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
         init_gif_size(sGifUpFull,   html_gif_up_trans,   &uiGifUpWidth,   &uiGifUpHeight);
         init_gif_size(sGifLfFull,   html_gif_lf_trans,   &uiGifLfWidth,   &uiGifLfHeight);
         init_gif_size(sGifRgFull,   html_gif_rg_trans,   &uiGifRgWidth,   &uiGifRgHeight);
         init_gif_size(sGifHmFull,   html_gif_hm_trans,   &uiGifHmWidth,   &uiGifHmHeight);
         init_gif_size(sGifNoUpFull, html_gif_noup_trans, &uiGifNoUpWidth, &uiGifNoUpHeight);
         init_gif_size(sGifNoLfFull, html_gif_nolf_trans, &uiGifNoLfWidth, &uiGifNoLfHeight);
         init_gif_size(sGifNoRgFull, html_gif_norg_trans, &uiGifNoRgWidth, &uiGifNoRgHeight);
         init_gif_size(sGifNoHmFull, html_gif_nohm_trans, &uiGifNoHmWidth, &uiGifNoHmHeight);
         init_gif_size(sGifGerFull,  html_gif_ger_trans,  &uiGifGerWidth,  &uiGifGerHeight);
         init_gif_size(sGifEngFull,  html_gif_eng_trans,  &uiGifEngWidth,  &uiGifEngHeight);
      }
      else
      {
         init_gif_size(sGifUpFull,   html_gif_up,   &uiGifUpWidth,   &uiGifUpHeight);
         init_gif_size(sGifLfFull,   html_gif_lf,   &uiGifLfWidth,   &uiGifLfHeight);
         init_gif_size(sGifRgFull,   html_gif_rg,   &uiGifRgWidth,   &uiGifRgHeight);
         init_gif_size(sGifHmFull,   html_gif_hm,   &uiGifHmWidth,   &uiGifHmHeight);
         init_gif_size(sGifNoUpFull, html_gif_noup, &uiGifNoUpWidth, &uiGifNoUpHeight);
         init_gif_size(sGifNoLfFull, html_gif_nolf, &uiGifNoLfWidth, &uiGifNoLfHeight);
         init_gif_size(sGifNoRgFull, html_gif_norg, &uiGifNoRgWidth, &uiGifNoRgHeight);
         init_gif_size(sGifNoHmFull, html_gif_nohm, &uiGifNoHmWidth, &uiGifNoHmHeight);
         init_gif_size(sGifGerFull,  html_gif_ger,  &uiGifGerWidth,  &uiGifGerHeight);
         init_gif_size(sGifEngFull,  html_gif_eng,  &uiGifEngWidth,  &uiGifEngHeight);
      }
      
      init_gif_size(sGifFoFull, html_gif_fo, &uiGifFoWidth, &uiGifFoHeight);
      init_gif_size(sGifFcFull, html_gif_fc, &uiGifFcWidth, &uiGifFcHeight);
      init_gif_size(sGifFsFull, html_gif_fs, &uiGifFsWidth, &uiGifFsHeight);
      init_gif_size(sGifMwFull, html_gif_mw, &uiGifMwWidth, &uiGifMwHeight);
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
}


/* +++ EOF +++ */