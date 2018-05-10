/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : udosym.c
*  Symbol prefix: udosym
*
*  Description  : This file handles all language-specific, localizable strings 
*                 used by UDO. Keep in mind that the localizable strings are 
*                 UTF-8 encoded since UDO v7.
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
*  Co-Authors   : Ulf Dunkel (fd), Gerhard Stoll (ggs), Thorsten Otto (tho)
*  Write access : fd, ggs
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2004:
*    tho       : introduced
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
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>
#include "udoport.h"

#include "udo_type.h"
#include "msg.h"
#include "commands.h"
#include "udointl.h"
#include "udomem.h"

#include "export.h"
#include "udosym.h"     /* Symbole                          */


/*******************************************************************************
*
*     UNINITIALIZED LOCAL VARIABLES
*
******************************************|************************************/

LOCAL char     **udosymbol;
LOCAL _UWORD    udosymbol_counter;
LOCAL size_t   udosymbol_alloc;
LOCAL char     **udosymbol_cli;
LOCAL _UWORD    udosymbol_counter_cli;

/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/



/*******************************************************************************
*
*  del_udosymbol():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void del_udosymbol(

const char       *s)
{
   _BOOL        found = FALSE;
   register _UWORD i,
                  j;
   
   if (udosymbol_counter > 0 && s[0] != EOS)
   {
      for (i = 0; i < udosymbol_counter; )
      {
         if (strstr(s, udosymbol[i]) != NULL)
         {
            free(udosymbol[i]);
            udosymbol_counter--;
            for (j = i; j < udosymbol_counter; j++)
            {
               udosymbol[j] = udosymbol[j + 1];
            }
            found = TRUE;
         } else
         {
            i++;
         }
      }
   }
   
   if (!found)
   {
      error_message(_("symbol %s not set"), s);
   }
}





/*******************************************************************************
*
*  add_udosymbol():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void add_udosymbol(

const char  *s)
{
   char *p;
   char **new_symbols;
   
   if (s[0] != EOS)
   {
      if (udosymbol_counter >= udosymbol_alloc)
      {
         size_t new_alloc = udosymbol_alloc + 32;
         
         new_symbols = (char **)realloc(udosymbol, new_alloc * sizeof(char *));
         if (new_symbols == NULL)
         {
            return;
         }
         udosymbol = new_symbols;
         udosymbol_alloc = new_alloc;
      }
      p = (char *)malloc((strlen(s) + 1) * sizeof(*s));
      if (p == NULL)
      {
      } else
      {
         strcpy(p, s);
         udosymbol[udosymbol_counter] = p;
         udosymbol_counter++;
      }
   } else
   {
      error_missing_parameter(CMD_SET);
   }
}





/*******************************************************************************
*
*  udosymbol_set():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL _BOOL udosymbol_set(

const char       *s)
{
   register _UWORD i;
   
   for (i = 0; i < udosymbol_counter; i++)
   {
      if (strstr(s, udosymbol[i]) != NULL)
      {
         return TRUE;
      }
   }

   return FALSE;
}


/*******************************************************************************
*
*  init_udosymbol():
*     Initialize symbol definitions.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_udosymbol(void)
{
   /* Symbole leeren */
   udosymbol_counter = 0;
   udosymbol_counter_cli = 0;
   udosymbol_alloc = 0;
   udosymbol = NULL;
   udosymbol_cli = NULL;
}


/*******************************************************************************
*
*  init_udosymbol_pass1():
*     Save definitions passed on commandline for pass2()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_udosymbol_pass1(void)
{
   _UWORD i;
   
   if (udosymbol_counter != 0)
   {
      udosymbol_counter_cli = udosymbol_counter;
      udosymbol_cli = udosymbol;
      udosymbol_counter = 0;
      udosymbol_alloc = 0;
      udosymbol = NULL;
      for (i = 0; i < udosymbol_counter_cli; i++)
         add_udosymbol(udosymbol_cli[i]);
   }
}


/*******************************************************************************
*
*  init_udosymbol_pass2():
*     Reset definitions to those passed on commandline for pass2()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_udosymbol_pass2(void)
{
   _UWORD i;
   
   for (i = 0; i < udosymbol_counter; i++)
      free(udosymbol[i]);
   if (udosymbol != NULL)
   {
      free(udosymbol);
      udosymbol = NULL;
   }
   udosymbol_counter = 0;
   udosymbol_alloc = 0;
   for (i = 0; i < udosymbol_counter_cli; i++)
      add_udosymbol(udosymbol_cli[i]);
}


/*******************************************************************************
*
*  exit_udosymbol():
*     Free symbol definitions.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void exit_udosymbol(void)
{
   _UWORD i;
   
   for (i = 0; i < udosymbol_counter; i++)
      free(udosymbol[i]);
   if (udosymbol != NULL)
   {
      free(udosymbol);
      udosymbol = NULL;
   }
   udosymbol_counter = 0;
   udosymbol_alloc = 0;
   for (i = 0; i < udosymbol_counter_cli; i++)
      free(udosymbol_cli[i]);
   if (udosymbol_cli != NULL)
   {
      free(udosymbol_cli);
      udosymbol_cli = NULL;
   }
   udosymbol_counter_cli = 0;
}
