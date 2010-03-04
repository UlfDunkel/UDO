@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das deutsche UDO-Handbuch nach HTML-Help-Source
@REM this batch file converts the german UDO Manual to HTML-help-source
udo -hh --verbose --force-long -D LANG_DE --tree -o ../hh-de/index.html manual.u %1 %2 %3 %4 %5 %6 %7 %8 %9
copy ../hh-de/index.ulh ../manual-de-hh.ulh
copy ../hh-de/index.uth ../manual-de-hh.uth
del ../hh-de/index.ulh
del ../hh-de/index.uth