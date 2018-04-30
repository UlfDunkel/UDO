   /* --- commandline symbol manager --- */

   /* ? */
GLOBAL void del_udosymbol(const char *s);
   /* ? */
GLOBAL void add_udosymbol(const char *s);
   /* ? */
GLOBAL _BOOL udosymbol_set(const char *s);
GLOBAL void init_udosymbol(void);
GLOBAL void exit_udosymbol(void);
GLOBAL void init_udosymbol_pass1(void);
GLOBAL void init_udosymbol_pass2(void);
