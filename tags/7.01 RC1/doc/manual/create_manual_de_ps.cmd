@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das deutsche UDO-Handbuch nach PostScript
@REM this batch file for Win32 + OS/2 converts the german UDO Manual to PostScript
udo --ps --verbose --force-long -D LANG_DE --tree -o manual-de.ps manual.u %1 %2 %3 %4 %5 %6 %7 %8 %9