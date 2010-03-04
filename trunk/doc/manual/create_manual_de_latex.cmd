@REM Dieses Batchfile fuer Win32 + OS/2 konvertiert das deutsche UDO-Handbuch nach LaTeX
@REM this batch file for Win32 + OS/2 converts the german UDO Manual to LaTeX
udo --tex --verbose --force-long -D LANG_DE manual.u -o manual-de.tex %1 %2 %3 %4 %5 %6 %7 %8 %9