@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das deutsche UDO-Handbuch nach NROFF
@REM this batch file for Win32 + OS/2 converts the german UDO Manual to NROFF
udo --nroff --verbose --force-long -D LANG_DE manual.u -o manual-de.nroff %1 %2 %3 %4 %5 %6 %7 %8 %9