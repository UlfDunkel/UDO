@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das englische UDO-Handbuch nach NROFF
@REM this batch file for Win32 + OS/2 converts the english UDO Manual to NROFF
udo --nroff --verbose --force-long -D LANG_EN manual.u -o manual-en.nroff %1 %2 %3 %4 %5 %6 %7 %8 %9