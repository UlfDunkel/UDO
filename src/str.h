/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : str.h
*  Symbol prefix: str
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
*
******************************************|************************************/

/* ############################################################
   # Typen
   ############################################################   */

struct size_brackets
{
   size_t format;
   size_t content;
};

/* ############################################################
   # Variablen
   ############################################################   */

/* ############################################################
   # Funktionen
   ############################################################   */

GLOBAL char *chrcat (char *dest, const char c);
GLOBAL char *strinsert ( char *string, const char *insert);

GLOBAL void replace_char ( char *string, const char replace, const char by );

GLOBAL int replace_once ( char *source, const char *replace, const char *by);
GLOBAL int replace_last ( char *source, const char *replace, const char *by);
GLOBAL int replace_all ( char *source, const char *replace, const char *by);

GLOBAL int qreplace_once ( char *source, const char *replace, const size_t rlen, const char *by, const size_t blen);
GLOBAL int qreplace_last ( char *source, const char *replace, const size_t rlen, const char *by, const size_t blen);
GLOBAL int qreplace_all ( char *source, const char *replace, const size_t rlen, const char *by, const size_t blen);

GLOBAL int delete_once ( char *source, const char *to_delete );
GLOBAL int delete_last ( char *source, const char *to_delete );
GLOBAL int delete_all ( char *source, const char *to_delete );

GLOBAL int qdelete_once ( char *source, const char *to_delete, const size_t dlen );
GLOBAL int qdelete_last ( char *source, const char *to_delete, const size_t dlen );
GLOBAL int qdelete_all ( char *source, const char *to_delete, const size_t dlen );


GLOBAL void del_right_spaces(char *s);
GLOBAL void del_whitespaces ( char *s);

GLOBAL size_t get_brackets_ptr ( char *s, char **cont, char **data );
GLOBAL struct size_brackets get_two_brackets_ptr ( char *s, char **cont_format, char **cont_content, char **data );
GLOBAL char *get_8bit_ptr(char *s);
GLOBAL char *get_section_ptr(char *s);
GLOBAL char *get_1stchar_ptr(char *s);

GLOBAL void tabs2spaces (char *s, const int tw);
GLOBAL char *itoroman ( int value, char *string );
GLOBAL void my_strupr ( char *string );
GLOBAL void my_strlwr ( char *string );

GLOBAL _UWORD str_flatten(char *zeile);
GLOBAL int str_UTF_sort_cmp(char *s1, char *s2);
GLOBAL int str_sort_flatten_cmp(char *s1, char *s2);   /* New V6.5.20 [gs] */
GLOBAL int str_sort_cmp(char *s1, char *s2);   /* New V6.5.20 [gs] */

GLOBAL int my_stricmp ( const char *s1, const char *s2 );
GLOBAL int my_strnicmp ( const char *s1, const char *s2, size_t len );

GLOBAL char *um_strcpy(char *dest, const char *src, size_t max, const char *place);
GLOBAL char *um_strncpy(char *dest, const char *src, size_t n, size_t max, const char *place);
GLOBAL char *um_strcat(char *dest, const char *src, size_t max, const char *place);
GLOBAL char *um_strncat(char *dest, const char *src, size_t n, size_t max, const char *place);

GLOBAL char *um_physical_strcpy(const char *src, size_t morealloc, const char *place);
