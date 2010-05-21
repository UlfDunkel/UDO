@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das englische UDO-Handbuch nach LaTeX
@REM this batch file for Win32 + OS/2 converts the english UDO Manual to LaTeX
udo --tex --verbose --force-long -D LANG_EN manual.u -o manual-en.tex %1 %2 %3 %4 %5 %6 %7 %8 %9