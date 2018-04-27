/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : udomem.c
*  Symbol prefix: udo
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
*  Description  : New UDO Memory-Layer (new in 6.3.3)
*                 Written by vj
*
*                 Use
*                 - um_malloc()  instead of malloc()
*                 - um_realloc() instead of realloc() 
*                 - um_free()    instead of free()
*
*                 Again: Please don't use malloc(), realloc() or free() in UDO!
*
*-------------------------------------------------------------------------------
*
*  Author       : Volker Jansen (vj)
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : vj, fd
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
*    fd  Jan 23: - converted all German umlauts in comments into plain ASCII
*
******************************************|************************************/

#ifndef ID_UDOMEM_C
#define ID_UDOMEM_C
const char *id_udomem_c= "@(#) udomem.c       $Date$";
#endif





/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "import.h"
#include "udoport.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

#include "export.h"
#include "udomem.h"                       /* memory management */





/*******************************************************************************
*
*     UNINITIALIZED GLOBALS
*
******************************************|************************************/

long      um_malloc_count;                /* */
long      um_free_count;                  /* */
long      um_free_error_count;            /* */
long      um_free_endbroken_count;        /* */
int       memory_error;                   /* */
char      endstring[] = UM_END_STRING;    /* */
size_t    endstring_len;                  /* */
MEMLIST  *anker;                          /* this is the anchor of our memory-usage list */





/*******************************************************************************
*
*     GLOBAL PROCEDURES
*
******************************************|************************************/

/*******************************************************************************
*
*  init_um():
*     sets up the memory layer
*
*  Notes:
*     Initialize Counters, anchor for memory-usage list, memory error indicator
*     and length of the ending string
*
*  Return:
*     -
*
******************************************|************************************/
 
GLOBAL void init_um(void)
{
   um_malloc_count         = 0;
   um_free_count           = 0;
   um_free_error_count     = 0;
   um_free_endbroken_count = 0;
   anker                   = NULL;
   memory_error            = 0;
   
   endstring_len = strlen(endstring) + 1; /* plus 1 for the ending null-byte! */
}





/*******************************************************************************
*
*  exit_um():
*     frees all memory alocated by um_mallocs and makes consistency
*     checks on the memory blocks.
*
*  Return:
*     -
*
******************************************|************************************/
 
GLOBAL void exit_um(void)
{
#ifdef UM_DEBUG_SHOW_STATS
                                          /* Added Debug information of Memory Management */
#ifdef UM_PRINTF_USE_LD
   printf("Memory statistic: %ld malloc, %ld free, %ld bad checks, %ld bad ends\n", 
      um_malloc_count, 
      um_free_count, 
      um_free_error_count, 
      um_free_endbroken_count);
#else
   printf("Memory statistic: %d malloc, %d free, %d bad checks, %d bad ends\n", 
      um_malloc_count, 
      um_free_count, 
      um_free_error_count, 
      um_free_endbroken_count);
#endif

#endif

   if (anker != NULL)                     /* Falls es jetzt noch belegten Speicher gibt, raeumen wir den auf */
   {
                                          /* Hier wird die Speicherliste entlang gelaufen */
#ifdef UM_DEBUG_SHOW_MSGS
      printf("exit_um: Cleaning up\n");
#endif

      while ( (memory_error == 0) && (anker != NULL) )
      {
         um_free(anker->block);           /* Wir geben den in der Liste gefundenen Speicherblock frei */
      }
      
#ifdef UM_DEBUG_SHOW_MSGS
      printf("exit_um: done\n");
#endif
   }
}





/*******************************************************************************
*
*  um_malloc2():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/
 
GLOBAL void *um_malloc2(

size_t       size,    /* */
char        *file,    /* */
int          line)    /* */
{
   void     *buffer;  /* */
   MEMLIST  *mptr;    /* */
   
   
   buffer = NULL;

   size += endstring_len;                 /* we need to allocate more memory... */

   buffer = malloc(size);                 /* allocate memory */
   if (buffer != NULL)                    /* success? */
   {
      mptr = malloc(sizeof(MEMLIST));     /* Speicher fuer Verwaltungsinformationen anfordern */
      
      if (mptr != NULL)
      {
         char   drive[3],      /* */
                path[512],     /* */
                filename[30],  /* */
                suffix[5];     /* */
         
         
         um_malloc_count++;               /* Okay, we got our management unit */
         
         mptr->check   = UM_LONG_CHECK;   /* Checksumme initialisieren */
         mptr->block   = buffer;          /* Dieser Puffer gehoert zu unserer Verwaltungseinheit */
         mptr->endmark = (char *)buffer + size - endstring_len;
         
         fsplit(file, drive, path, filename, suffix);

         strncpy(mptr->file, filename, 29);

         mptr->file[29] = '\0';           /* close C string! */
         mptr->line     = line;
         
         strcpy(mptr->endmark, endstring);/* copy ending string for checks */

         mptr->next = anker;              /* Wir haengen uns vorne an die Liste an */
         anker = mptr;
         
#ifdef UM_DEBUG_SHOW_CALLS
         printf("1 MEMLIST node created: %d\n", mptr->check, UM_LONG_CHECK);
#endif
      }
      else
      {
         /* Konnte keinen Speicher fuer Verwaltungsinformationen anlegen */
         
         free(buffer);                    /* buffer wieder freigeben */
         buffer = NULL;                   /* Wir melden keinen freien Speicher zurueck */
      }
   }
   
   return buffer;
}





/*******************************************************************************
*
*  um_realloc():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/
 
GLOBAL void *um_realloc(

void        *block,     /* */
size_t       size)      /* */
{
   int       lauf = 1;  /* */
   void     *buffer;    /* */
   MEMLIST  *tanker;    /* */
   
   
   buffer = NULL;

   tanker = anker;                        /* Laufvariable initialisieren */

   size += endstring_len;                 /* we need more memory for the ending string */

   if ( (tanker != NULL) && (memory_error == 0) )
   {
      do
      {
         if (tanker->check != UM_LONG_CHECK)
         {
                                          /* Speicherfehler: unsere Checksumme wurde ueberschrieben! */
            lauf = 0;                     /* Abbrechen, wenn die Zeiger ueberschrieben sind, koennte es krachen */
            memory_error = 42;            /* Speicherfehler-Flag setzen */

#ifdef UM_PRINTF_USE_LD
            printf("Fatal error: um_realloc failed: checksum broken: %ld != %ld\n", tanker->check, UM_LONG_CHECK);
#else
            printf("Fatal error: um_realloc failed: checksum broken: %d != %d\n", tanker->check, UM_LONG_CHECK);
#endif
         }
         else
         {
            if (tanker->block == block)   /* v6.3.6: checken, ob das aktuelle Element der gesuchte Block ist [vj] */
            {
                                          /* reallocate memory */
               buffer = realloc(tanker->block, size);

               if (buffer != NULL)        /* success? */
               {
                                          /* We need to save the new buffer */
                  tanker->block   = buffer;
                  tanker->endmark = (char *)buffer + size - endstring_len;

                                          /* Copy ending string */
                  strcpy(tanker->endmark, endstring);
               }
               
               lauf = 0;                  /* exit loop */
            }
            else
            {
               tanker = tanker->next;     /* v6.3.12 [vj] Of course, we need this! */
            }
         }
      } while ( (tanker != NULL) && (lauf == 1) );

   }
   
   return buffer;   
}





/*******************************************************************************
*
*  um_free():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/
 
GLOBAL void um_free(

void        *memblock)        /* */
{
   int       lauf = 1;        /* */
   MEMLIST  *tanker = anker;  /* */
   MEMLIST  *last = NULL;     /* */

   
   if ( (tanker != NULL) && (memory_error == 0) )
   {
      do
      {
         if (tanker->check != UM_LONG_CHECK)
         {
                                          /* Speicherfehler: unsere Checksumme wurde ueberschrieben! */
            lauf = 0;                     /* Abbrechen, wenn die Zeiger ueberschrieben sind, koennte es krachen */
            memory_error = 42;            /* Speicherfehler-Flag setzen */

            if (um_free_error_count == 0)
            {
#ifdef UM_PRINTF_USE_LD
               printf("Fatal error: um_free failed: checksum broken: %ld != %ld\n", tanker->check, UM_LONG_CHECK);
#else
               printf("Fatal error: um_free failed: checksum broken: %d != %d\n", tanker->check, UM_LONG_CHECK);
#endif
            }
            
            um_free_error_count++;
         }
         else
         {
                                          /* Soll der aktuelle Eintrag freigegeben werden? */
            if (memblock == tanker->block)
            {
               if (strcmp(tanker->endmark, endstring) != 0)
               {
                  if (um_free_endbroken_count == 0)
                  {
                     printf("Warning: um_free: memory block end check broken\n");
#ifdef UM_DEBUG_SHOW_BUFFER_ON_FREE_ERROR
                     printf("Bufferstart: \"%s\"\n", (char *)tanker->block);
                     printf("Bufferende : \"%s\"\n", tanker->endmark);
                     printf("Filename: %s; Line: %d\n", tanker->file, tanker->line );
#endif
                  }
                  
                  um_free_endbroken_count++;
               }
               
               um_free_count++;
               
               free(tanker->block);       /* Speicher freigeben */

               if (last == NULL)          /* Verwaltungselement aus der Kette aushaengen */
               {
                  anker = tanker->next;   /* Wurzel neu setzen, da wir das erste Element der Liste freigeben */
               }
               else
               {
                                          /* Beim Vorgaenger setzen wir nun den Next-Pointer auf unseren Nachfolger */
                  last->next = tanker->next;
               }
               
               free(tanker);              /* Verwaltungsobjekt freigeben */
               lauf = 0;                  /* exit loop */
            }
            else
            {
               last = tanker;
               tanker = tanker->next;
            }
         }
      } while ( (tanker != NULL) && (lauf == 1) );
   }
}

/* +++ EOF +++ */

