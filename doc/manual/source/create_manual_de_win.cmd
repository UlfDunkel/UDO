@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das deutsche UDO-Handbuch nach WinHelp-Source
@REM this batch file for Win32 + OS/2 converts the german UDO Manual to WinHelp-Source
udo --win --verbose --force-long -D LANG_DE --tree -o ../win-de/manual-de.rtf manual.u %1 %2 %3 %4 %5 %6 %7 %8 %9