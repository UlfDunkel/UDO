/*	############################################################
	# @(#) abo.c
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
	# @(#) Start:   24.07.1996
	# @(#) Version: 02.01.1997
	############################################################	*/

#ifndef ID_CFG_C
#define ID_CFG_C
const char *id_cfg_c= "@(#) cfg.c       17.04.1998";
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "portab.h"
#include "version.h"
#include "constant.h"
#include "file.h"
#include "str.h"


#include "export.h"
#include "cfg.h"

/*	############################################################
	# lokale Variablen
	############################################################	*/

typedef struct
{	const char		key[32];
	const char		type;
	void			*val;	/* nicht const, da gecastet wird */
	const size_t	maxlen;
}	PROFILE;

LOCAL const PROFILE profile[]=
{
	{	"User.Name",			'c',	config.strUserName,			CFG_MAX_USER_LEN	},
	{	"User.Street",			'c',	config.strUserStreet,		CFG_MAX_USER_LEN	},
	{	"User.Town",			'c',	config.strUserTown,			CFG_MAX_USER_LEN	},
	{	"User.Key",				'c',	config.strUserKey,			CFG_MAX_USER_LEN	},

	{	"Show.Status",			'b',	&(config.bShowStatus),		0					},
	{	"Force.Long",			'b',	&(config.bForceLong),		0					},
	{	"Force.Short",			'b',	&(config.bForceShort),		0					},
	{	"Adjust.Destfile",		'b',	&(config.bDestAdjust),		0					},
	{	"Adjust.Destfile.All",	'b',	&(config.bDestAdjustAll),	0					},
	{	"Adjust.Destfile.Name",	'b',	&(config.bDestAdjustName),	0					},
	{	"Adjust.Destfile.Suff",	'b',	&(config.bDestAdjustSuff),	0					},
	{	"Adjust.Destfile.Low",	'b',	&(config.bDestLowerFile),	0					},
	{	"Adjust.Destpath.Low",	'b',	&(config.bDestLowerPath),	0					},
	{	"Save.Logfile",			'b',	&(config.bUseLogfile),		0					},
	{	"Save.Hypfile",			'b',	&(config.bUseHypfile),		0					},
	{	"Save.Treefile",		'b',	&(config.bUseTreefile),		0					},
	{	"Save.UPRfile",			'b',	&(config.bUseUPRfile),		0					},

#ifdef __TOS__
	{	"Source.File",			'c',	config.strSourcefile,		CFG_MAX_FILE_LEN	},
	{	"Dest.File",			'c',	config.strDestfile,			CFG_MAX_FILE_LEN	},
	{	"Dest.Format",			'i',	&(config.desttype),			0					},

	{	"Warn.Overwrite",		'b',	&(config.bWarnOver),		0					},
	{	"Warn.Quit",			'b',	&(config.bAskQuit),			0					},
	{	"View.Destfile",		'b',	&(config.bDestView),		0					},
	{	"No.Warnings",			'b',	&(config.bNoWarnings),		0					},
	{	"Use.Check",			'b',	&(config.bCheckMisc),		0					},

	{	"Symbol.1.Entry",		'c',	config.strSymbol[0],		CFG_MAX_SYMBOL_LEN	},
	{	"Symbol.1.Use",			'b',	&(config.bUseSymbol[0]),	0					},
	{	"Symbol.2.Entry",		'c',	config.strSymbol[1],		CFG_MAX_SYMBOL_LEN	},
	{	"Symbol.2.Use",			'b',	&(config.bUseSymbol[1]),	0					},
	{	"Symbol.3.Entry",		'c',	config.strSymbol[2],		CFG_MAX_SYMBOL_LEN	},
	{	"Symbol.3.Use",			'b',	&(config.bUseSymbol[2]),	0					},
	{	"Symbol.4.Entry",		'c',	config.strSymbol[3],		CFG_MAX_SYMBOL_LEN	},
	{	"Symbol.4.Use",			'b',	&(config.bUseSymbol[3]),	0					},
	{	"Symbol.5.Entry",		'c',	config.strSymbol[4],		CFG_MAX_SYMBOL_LEN	},
	{	"Symbol.5.Use",			'b',	&(config.bUseSymbol[4]),	0					},
	{	"Symbol.6.Entry",		'c',	config.strSymbol[5],		CFG_MAX_SYMBOL_LEN	},
	{	"Symbol.6.Use",			'b',	&(config.bUseSymbol[5]),	0					},
	{	"Symbol.7.Entry",		'c',	config.strSymbol[6],		CFG_MAX_SYMBOL_LEN	},
	{	"Symbol.7.Use",			'b',	&(config.bUseSymbol[6]),	0					},
	{	"Symbol.8.Entry",		'c',	config.strSymbol[7],		CFG_MAX_SYMBOL_LEN	},
	{	"Symbol.8.Use",			'b',	&(config.bUseSymbol[7]),	0					},

	{	"Source.Editor.App",	'c',	config.sedit.strApp,		CFG_MAX_FILE_LEN	},
	{	"Source.Editor.Opt",	'c',	config.sedit.strOpt,		CFG_MAX_FILE_LEN	},
	{	"Source.Editor.VA",		'b',	&(config.sedit.bVa),		0					},
	{	"Source.Editor.TOS",	'b',	&(config.sedit.bTos),		0					},

	{	"Source.Viewer.App",	'c',	config.sview.strApp,		CFG_MAX_FILE_LEN	},
	{	"Source.Viewer.Opt",	'c',	config.sview.strOpt,		CFG_MAX_FILE_LEN	},
	{	"Source.Viewer.VA",		'b',	&(config.sview.bVa),		0					},
	{	"Source.Viewer.TOS",	'b',	&(config.sview.bTos),		0					},

	{	"Dest.Editor.App",		'c',	config.dedit.strApp,		CFG_MAX_FILE_LEN	},
	{	"Dest.Editor.Opt",		'c',	config.dedit.strOpt,		CFG_MAX_FILE_LEN	},
	{	"Dest.Editor.VA",		'b',	&(config.dedit.bVa),		0					},
	{	"Dest.Editor.TOS",		'b',	&(config.dedit.bTos),		0					},

	{	"Dest.Viewer.App",		'c',	config.dview.strApp,		CFG_MAX_FILE_LEN	},
	{	"Dest.Viewer.Opt",		'c',	config.dview.strOpt,		CFG_MAX_FILE_LEN	},
	{	"Dest.Viewer.VA",		'b',	&(config.dview.bVa),		0					},
	{	"Dest.Viewer.TOS",		'b',	&(config.dview.bTos),		0					},

	{	"ASCII.App",			'c',	config.asc.strApp,			CFG_MAX_FILE_LEN	},
	{	"ASCII.Opt",			'c',	config.asc.strOpt,			CFG_MAX_FILE_LEN	},
	{	"ASCII.VA",				'b',	&(config.asc.bVa),			0					},
	{	"ASCII.TOS",			'b',	&(config.asc.bTos),			0					},

	{	"HTML.App",				'c',	config.htm.strApp,			CFG_MAX_FILE_LEN	},
	{	"HTML.Opt",				'c',	config.htm.strOpt,			CFG_MAX_FILE_LEN	},
	{	"HTML.VA",				'b',	&(config.htm.bVa),			0					},
	{	"HTML.TOS",				'b',	&(config.htm.bTos),			0					},

	{	"HH.App",				'c',	config.mhh.strApp,			CFG_MAX_FILE_LEN	},
	{	"HH.Opt",				'c',	config.mhh.strOpt,			CFG_MAX_FILE_LEN	},
	{	"HH.VA",				'b',	&(config.mhh.bVa),			0					},
	{	"HH.TOS",				'b',	&(config.mhh.bTos),			0					},

	{	"LaTeX.App",			'c',	config.tex.strApp,			CFG_MAX_FILE_LEN	},
	{	"LaTeX.Opt",			'c',	config.tex.strOpt,			CFG_MAX_FILE_LEN	},
	{	"LaTeX.VA",				'b',	&(config.tex.bVa),			0					},
	{	"LaTeX.TOS",			'b',	&(config.tex.bTos),			0					},

	{	"Linuxdoc.App",			'c',	config.lds.strApp,			CFG_MAX_FILE_LEN	},
	{	"Linuxdoc.Opt",			'c',	config.lds.strOpt,			CFG_MAX_FILE_LEN	},
	{	"Linuxdoc.VA",			'b',	&(config.lds.bVa),			0					},
	{	"Linuxdoc.TOS",			'b',	&(config.lds.bTos),			0					},

	{	"Helptag.App",			'c',	config.hph.strApp,			CFG_MAX_FILE_LEN	},
	{	"Helptag.Opt",			'c',	config.hph.strOpt,			CFG_MAX_FILE_LEN	},
	{	"Helptag.VA",			'b',	&(config.hph.bVa),			0					},
	{	"Helptag.TOS",			'b',	&(config.hph.bTos),			0					},

	{	"Manpage.App",			'c',	config.man.strApp,			CFG_MAX_FILE_LEN	},
	{	"Manpage.Opt",			'c',	config.man.strOpt,			CFG_MAX_FILE_LEN	},
	{	"Manpage.VA",			'b',	&(config.man.bVa),			0					},
	{	"Manpage.TOS",			'b',	&(config.man.bTos),			0					},

	{	"Pure-C.App",			'c',	config.pch.strApp,			CFG_MAX_FILE_LEN	},
	{	"Pure-C.Opt",			'c',	config.pch.strOpt,			CFG_MAX_FILE_LEN	},
	{	"Pure-C.VA",			'b',	&(config.pch.bVa),			0					},
	{	"Pure-C.TOS",			'b',	&(config.pch.bTos),			0					},

	{	"QuickView.App",		'c',	config.aqv.strApp,			CFG_MAX_FILE_LEN	},
	{	"QuickView.Opt",		'c',	config.aqv.strOpt,			CFG_MAX_FILE_LEN	},
	{	"QuickView.VA",			'b',	&(config.aqv.bVa),			0					},
	{	"QuickView.TOS",		'b',	&(config.aqv.bTos),			0					},

	{	"RTF.App",				'c',	config.rtf.strApp,			CFG_MAX_FILE_LEN	},
	{	"RTF.Opt",				'c',	config.rtf.strOpt,			CFG_MAX_FILE_LEN	},
	{	"RTF.VA",				'b',	&(config.rtf.bVa),			0					},
	{	"RTF.TOS",				'b',	&(config.rtf.bTos),			0					},

	{	"ST-Guide.App",			'c',	config.stg.strApp,			CFG_MAX_FILE_LEN	},
	{	"ST-Guide.Opt",			'c',	config.stg.strOpt,			CFG_MAX_FILE_LEN	},
	{	"ST-Guide.VA",			'b',	&(config.stg.bVa),			0					},
	{	"ST-Guide.TOS",			'b',	&(config.stg.bTos),			0					},

	{	"Texinfo.App",			'c',	config.inf.strApp,			CFG_MAX_FILE_LEN	},
	{	"Texinfo.Opt",			'c',	config.inf.strOpt,			CFG_MAX_FILE_LEN	},
	{	"Texinfo.VA",			'b',	&(config.inf.bVa),			0					},
	{	"Texinfo.TOS",			'b',	&(config.inf.bTos),			0					},

	{	"Turbo-Vision.App",		'c',	config.tvh.strApp,			CFG_MAX_FILE_LEN	},
	{	"Turbo-Vision.Opt",		'c',	config.tvh.strOpt,			CFG_MAX_FILE_LEN	},
	{	"Turbo-Vision.VA",		'b',	&(config.tvh.bVa),			0					},
	{	"Turbo-Vision.TOS",		'b',	&(config.tvh.bTos),			0					},

	{	"WinHelp.App",			'c',	config.win.strApp,			CFG_MAX_FILE_LEN	},
	{	"WinHelp.Opt",			'c',	config.win.strOpt,			CFG_MAX_FILE_LEN	},
	{	"WinHelp.VA",			'b',	&(config.win.bVa),			0					},
	{	"WinHelp.TOS",			'b',	&(config.win.bTos),			0					},

	{	"Nroff.App",			'c',	config.nro.strApp,			CFG_MAX_FILE_LEN	},
	{	"Nroff.Opt",			'c',	config.nro.strOpt,			CFG_MAX_FILE_LEN	},
	{	"Nroff.VA",				'b',	&(config.nro.bVa),			0					},
	{	"Nroff.TOS",			'b',	&(config.nro.bTos),			0					},

	{	"Lyx.App",				'c',	config.lyx.strApp,			CFG_MAX_FILE_LEN	},
	{	"Lyx.Opt",				'c',	config.lyx.strOpt,			CFG_MAX_FILE_LEN	},
	{	"Lyx.VA",				'b',	&(config.lyx.bVa),			0					},
	{	"Lyx.TOS",				'b',	&(config.lyx.bTos),			0					},

	{	"C.App",				'c',	config.src.strApp,			CFG_MAX_FILE_LEN	},
	{	"C.Opt",				'c',	config.src.strOpt,			CFG_MAX_FILE_LEN	},
	{	"C.VA",					'b',	&(config.src.bVa),			0					},
	{	"C.TOS",				'b',	&(config.src.bTos),			0					},

	{	"Pascal.App",			'c',	config.srp.strApp,			CFG_MAX_FILE_LEN	},
	{	"Pascal.Opt",			'c',	config.srp.strOpt,			CFG_MAX_FILE_LEN	},
	{	"Pascal.VA",			'b',	&(config.srp.bVa),			0					},
	{	"Pascal.TOS",			'b',	&(config.srp.bTos),			0					},

	{	"IPF.App",				'c',	config.ipf.strApp,			CFG_MAX_FILE_LEN	},
	{	"IPF.Opt",				'c',	config.ipf.strOpt,			CFG_MAX_FILE_LEN	},
	{	"IPF.VA",				'b',	&(config.ipf.bVa),			0					},
	{	"IPF.TOS",				'b',	&(config.ipf.bTos),			0					},

	{	"DRC.App",				'c',	config.drc.strApp,			CFG_MAX_FILE_LEN	},
	{	"DRC.Opt",				'c',	config.drc.strOpt,			CFG_MAX_FILE_LEN	},
	{	"DRC.VA",				'b',	&(config.drc.bVa),			0					},
	{	"DRC.TOS",				'b',	&(config.drc.bTos),			0					},

	{	"PDL.App",				'c',	config.pdl.strApp,			CFG_MAX_FILE_LEN	},
	{	"PDL.Opt",				'c',	config.pdl.strOpt,			CFG_MAX_FILE_LEN	},
	{	"PDL.VA",				'b',	&(config.pdl.bVa),			0					},
	{	"PDL.TOS",				'b',	&(config.pdl.bTos),			0					},

	{	"WH4.App",				'c',	config.wh4.strApp,			CFG_MAX_FILE_LEN	},
	{	"WH4.Opt",				'c',	config.wh4.strOpt,			CFG_MAX_FILE_LEN	},
	{	"WH4.VA",				'b',	&(config.wh4.bVa),			0					},
	{	"WH4.TOS",				'b',	&(config.wh4.bTos),			0					},

	{	"U2U.App",				'c',	config.u2u.strApp,			CFG_MAX_FILE_LEN	},
	{	"U2U.Opt",				'c',	config.u2u.strOpt,			CFG_MAX_FILE_LEN	},
	{	"U2U.VA",				'b',	&(config.u2u.bVa),			0					},
	{	"U2U.TOS",				'b',	&(config.u2u.bTos),			0					},

	{	"PS.App",				'c',	config.ps.strApp,			CFG_MAX_FILE_LEN	},
	{	"PS.Opt",				'c',	config.ps.strOpt,			CFG_MAX_FILE_LEN	},
	{	"PS.VA",				'b',	&(config.ps.bVa),			0					},
	{	"PS.TOS",				'b',	&(config.ps.bTos),			0					},
#endif /* __TOS__ */


	{	"",						'c',	NULL,						0					},

};

LOCAL char	profilename[256], profilefull[256];
LOCAL char	homepath[256];
LOCAL char	programname[256];
LOCAL char	programos[256];



/*	############################################################
	# Einstellungen laden
	############################################################	*/
GLOBAL int read_profile ( void )
{
	FILE	*file;
	char	s[256], *ptr, prokey[32], proval[256];
	size_t	sl;
	int		i;
	BOOLEAN	found;

	if (profilefull[0]==EOS)
	{
		if (homepath[0]!=EOS)
		{	sprintf(profilefull, "%s%s", homepath, profilename);
		}
		else
		{	strcpy(profilefull, profilename);
		}
	}

	file= fopen(profilefull, "r");
	if (!file)
	{	return(CFG_READ_NOT_FOUND);
	}

	/*	--------------------------------------------------------------	*/
	/*	Struktur ausnullen, sprich alles auf FALSE, 0 bzw. "" setzen	*/
	/*	--------------------------------------------------------------	*/
	memset(&config, 0, sizeof(CONFIG));
	
	while (fgets(s, 256, file))
	{	while ( (sl=strlen(s))>0 && s[sl-1]<=32 )	s[sl-1]= EOS;

		if (s[0]!=';' && s[0]!='#' && s[0]!=EOS)
		{	ptr= strchr(s, '=');
			if (ptr!=NULL)
			{	ptr[0]= EOS;
				ptr++;
				while(ptr[0]==' ')	ptr++;
				while ( (sl=strlen(ptr))>0 && ptr[sl-1]<=32 )	ptr[sl-1]= EOS;
				strcpy(prokey, s);
				strcpy(proval, ptr);
				i= 0;
				found= FALSE;
				while ( !found && profile[i].val!=NULL )
				{
					if (my_stricmp(prokey, profile[i].key)==0)
					{	switch(profile[i].type)
						{	case 'c':
								*(char *) profile[i].val= 0;
								strncat((char *) profile[i].val, proval, profile[i].maxlen);
								break;
							case 'b':
								*(int *) profile[i].val= (my_stricmp(proval, "TRUE")==0);
								break;
							case 'i':
								*(int *) profile[i].val= atoi(proval);
								break;
						}
						found= TRUE;
					}
					i++;
				}
			}
		}
	}
	
	fclose(file);


	/* UDO is now Open Source and not limited by */
	/* any shareware registration fees anymore */
	/* thus config.bRegistered is always true */

	config.bRegistered= TRUE;

	if (!config.bDestAdjustAll && !config.bDestAdjustName
			&& !config.bDestAdjustSuff)
	{	config.bDestAdjustAll= TRUE;
	}

	return (CFG_READ_OK);
}	/* read_profile */


/*	############################################################
	# Einstellungen sichern
	############################################################	*/
GLOBAL int write_profile ( void )
{
	FILE	*file;
	int		i;

	if (profilefull[0]==EOS)
	{
		if (homepath[0]!=EOS)
		{	sprintf(profilefull, "%s%s", homepath, profilename);
		}
		else
		{	strcpy(profilefull, profilename);
		}
	}

	file= myFwopen(profilefull, TOASC);

	if (file == NULL)
	{	return(CFG_WRITE_NOT_SAVED);
	}
	
	i= 0;
	
	while (profile[i].val!=NULL)
	{
		switch(profile[i].type)
		{	case 'b':
				if ( *(int *) profile[i].val )
				{	fprintf(file, "%s=TRUE\n", profile[i].key);
				}
				break;
			case 'c':
				if ( *(char *) profile[i].val!=0 )
				{	fprintf(file, "%s=%s\n", profile[i].key, (char *) profile[i].val);
				}
				break;
			case 'i':
				fprintf(file, "%s=%d\n", profile[i].key, *(int *) profile[i].val);
				break;
			case '-':
				fprintf(file, "\n");
				break;
		}
		i++;
	}

	fclose(file);
	
	return (CFG_WRITE_OK);
}	/* write_profile */



/*	############################################################
	# Modulinit
	############################################################	*/
GLOBAL void init_module_config ( const char *pfname, const char *prgname, const char *prgos )
{
	FILE	*file;
	char	*tmp, path[256];
	char	sep[2];
	size_t	sl;

	
	/*	--------------------------------------------------------------	*/
	/*	Programmnamen sichern											*/
	/*	--------------------------------------------------------------	*/
	strcpy(profilename, pfname);
	if (profilename[0]=='\0')		/*r6pl4*/
	{	strcpy(profilename, "udo.ini");
	}
	strcpy(programname, prgname);
	strcpy(programos, prgos);
	
	
	/*	--------------------------------------------------------------	*/
	/*	Pfadtrenner setzen												*/
	/*	--------------------------------------------------------------	*/
#if USE_SLASH
	strcpy(sep, "/");
#else
	strcpy(sep, "\\");
#endif

	/*	--------------------------------------------------------------	*/
	/*	Struktur ausnullen, sprich alles auf FALSE, 0 bzw. "" setzen	*/
	/*	--------------------------------------------------------------	*/
	memset(&config, 0, sizeof(CONFIG));


	/*	--------------------------------------------------------------	*/
	/*	Defaulteinstellungen setzen										*/
	/*	--------------------------------------------------------------	*/
	config.bDestAdjust= TRUE;
	config.bDestAdjustAll= TRUE;
	config.bDestAdjustName= FALSE;
	config.bDestAdjustSuff= FALSE;

	config.bUseLogfile= TRUE;
	config.bUseHypfile= TRUE;
	config.bUseTreefile= FALSE;
	config.bUseUPRfile= FALSE;
	config.bShowStatus= TRUE;
	config.bForceLong= FALSE;
	config.bForceShort= FALSE;

#ifdef __TOS__
	config.bDestView= TRUE;
	config.strSourcefile[0]= EOS;
	config.strDestfile[0]= EOS;
#endif

	/*	--------------------------------------------------------------	*/
	/*	Profile finden, zuerst im aktuellen Verzeichnis, dann in		*/
	/*	$UDOPATH, dann in $HOME/defaults (nur TOS), dann in $HOME		*/
	/*	--------------------------------------------------------------	*/
	strcpy(profilefull, profilename);

	file=fopen(profilefull, "r");
	if (file)
	{	fclose(file);
		return;
	}

	tmp= getenv("UDOPATH");
	if (tmp!=NULL)
	{	strcpy(path, tmp);
		sl= strlen(path);
		if (path[sl-1]=='\\' || path[sl-1]=='/')
		{	path[sl-1]= EOS;
		}
		sprintf(homepath, "%s%s", path, sep);
		sprintf(profilefull, "%s%s%s", path, sep, profilename);
		file= fopen(profilefull, "r");
		if (file)
		{	fclose(file);
			return;
		}
	}

#ifdef __TOS__
	tmp= getenv("HOME");
	if (tmp!=NULL && *tmp!=EOS)
	{	strcpy(path, tmp);
		sl= strlen(path);
		if (path[sl-1]=='\\' || path[sl-1]=='/')
		{	path[sl-1]= EOS;
		}
		sprintf(homepath, "%s%s", path, sep);
		sprintf(profilefull, "%s%sdefaults%s%s", path, sep, sep, profilename);
		file= fopen(profilefull, "r");
		if (file)
		{	sprintf(homepath, "%s%sdefaults%s", path, sep, sep);
			fclose(file);
			return;
		}
	}
#endif

	tmp= getenv("HOME");
	if (tmp!=NULL && *tmp!=EOS)
	{	strcpy(path, tmp);
		sl= strlen(path);
		if (path[sl-1]=='\\' || path[sl-1]=='/')
		{	path[sl-1]= EOS;
		}
		sprintf(homepath, "%s%s", path, sep);
		sprintf(profilefull, "%s%s%s", path, sep, profilename);
		file= fopen(profilefull, "r");
		if (file)
		{	fclose(file);
			return;
		}
	}

/* PL14: Bei TOS und MS-DOS auch C:\udo.ini suchen, da einige Leute */
/*       es einfach nicht gebacken bekommen, $HOME zu setzen.       */

#if defined(__TOS__) || defined(__MSDOS__) || defined(__WIN32__)
		sprintf(profilefull, "C:\\%s", profilename);
		file= fopen(profilefull, "r");
		if (file)
		{	fclose(file);
			strcpy(homepath, "C:\\");
			return;
		}
#endif

	profilefull[0]= EOS;

}	/* init_module_config */


/*	############################################################
	# cfg.c
	############################################################	*/

