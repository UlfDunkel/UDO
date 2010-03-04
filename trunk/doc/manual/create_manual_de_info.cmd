@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das deutsche UDO-Handbuch nach GNU-texinfo
@rem this batch file for Win32 + OS/2 converts the german UDO Manual to GNU-texinfo
udo --info --verbose --force-long -D LANG_DE --tree -o manual-de.info manual.u %1 %2 %3 %4 %5 %6 %7 %8 %8
