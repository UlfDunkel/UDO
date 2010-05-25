@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das englische UDO-Handbuch nach GNU-texinfo
@REM this batch file for Win32 + OS/2 converts the english UDO Manual to GNU-texinfo
udo --info --verbose --force-long -D LANG_EN --tree -o manual-en.info manual.u %1 %2 %3 %4 %5 %6 %7 %8 %9