# Microsoft Developer Studio Project File - Name="UDO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=UDO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UDO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UDO.mak" CFG="UDO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UDO - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "UDO - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UDO - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "UDO - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "UDO - Win32 Release"
# Name "UDO - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\abo.c
# End Source File
# Begin Source File

SOURCE=..\cfg.c
# End Source File
# Begin Source File

SOURCE=..\chr.c
# End Source File
# Begin Source File

SOURCE=..\cli.c
# End Source File
# Begin Source File

SOURCE=..\env.c
# End Source File
# Begin Source File

SOURCE=..\file.c
# End Source File
# Begin Source File

SOURCE=..\img.c
# End Source File
# Begin Source File

SOURCE=..\msg.c
# End Source File
# Begin Source File

SOURCE=..\par.c
# End Source File
# Begin Source File

SOURCE=..\str.c
# End Source File
# Begin Source File

SOURCE=..\sty.c
# End Source File
# Begin Source File

SOURCE=..\tab.c
# End Source File
# Begin Source File

SOURCE=..\toc.c
# End Source File
# Begin Source File

SOURCE=..\tp.c
# End Source File
# Begin Source File

SOURCE=..\udo.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\437iso.h
# End Source File
# Begin Source File

SOURCE=..\850iso.h
# End Source File
# Begin Source File

SOURCE=..\abo.h
# End Source File
# Begin Source File

SOURCE=..\ansi2dos.h
# End Source File
# Begin Source File

SOURCE=..\ansi_raw.h
# End Source File
# Begin Source File

SOURCE=..\cfg.h
# End Source File
# Begin Source File

SOURCE=..\chr.h
# End Source File
# Begin Source File

SOURCE=..\chr_437.h
# End Source File
# Begin Source File

SOURCE=..\chr_850.h
# End Source File
# Begin Source File

SOURCE=..\chr_all.h
# End Source File
# Begin Source File

SOURCE=..\chr_dos.h
# End Source File
# Begin Source File

SOURCE=..\chr_hp8.h
# End Source File
# Begin Source File

SOURCE=..\chr_iso.h
# End Source File
# Begin Source File

SOURCE=..\chr_mac.h
# End Source File
# Begin Source File

SOURCE=..\chr_next.h
# End Source File
# Begin Source File

SOURCE=..\chr_raw.h
# End Source File
# Begin Source File

SOURCE=..\chr_tos.h
# End Source File
# Begin Source File

SOURCE=..\chr_ttf.h
# End Source File
# Begin Source File

SOURCE=..\commands.h
# End Source File
# Begin Source File

SOURCE=..\constant.h
# End Source File
# Begin Source File

SOURCE=..\env.h
# End Source File
# Begin Source File

SOURCE=..\export.h
# End Source File
# Begin Source File

SOURCE=..\file.h
# End Source File
# Begin Source File

SOURCE=..\gui.h
# End Source File
# Begin Source File

SOURCE=..\hp82iso.h
# End Source File
# Begin Source File

SOURCE=..\img.h
# End Source File
# Begin Source File

SOURCE=..\img_html.h
# End Source File
# Begin Source File

SOURCE=..\img_stg.h
# End Source File
# Begin Source File

SOURCE=..\img_win.h
# End Source File
# Begin Source File

SOURCE=..\import.h
# End Source File
# Begin Source File

SOURCE=..\mac2iso.h
# End Source File
# Begin Source File

SOURCE=..\msg.h
# End Source File
# Begin Source File

SOURCE=..\next2iso.h
# End Source File
# Begin Source File

SOURCE=..\par.h
# End Source File
# Begin Source File

SOURCE=..\portab.h
# End Source File
# Begin Source File

SOURCE=..\raw2iso.h
# End Source File
# Begin Source File

SOURCE=..\str.h
# End Source File
# Begin Source File

SOURCE=..\sty.h
# End Source File
# Begin Source File

SOURCE=..\tab.h
# End Source File
# Begin Source File

SOURCE=..\toc.h
# End Source File
# Begin Source File

SOURCE=..\tos2iso.h
# End Source File
# Begin Source File

SOURCE=..\tp.h
# End Source File
# Begin Source File

SOURCE=..\udo.h
# End Source File
# Begin Source File

SOURCE=..\udo2ps.h
# End Source File
# Begin Source File

SOURCE=..\udo_type.h
# End Source File
# Begin Source File

SOURCE=..\udocmd.h
# End Source File
# Begin Source File

SOURCE=..\udolocal.h
# End Source File
# Begin Source File

SOURCE=..\utf82iso.h
# End Source File
# Begin Source File

SOURCE=..\version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
