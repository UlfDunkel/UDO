@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das englische UDO-Handbuch nach HTML-Help-Source
@REM this batch file converts the english UDO Manual to HTML-help-source
udo -hh --verbose --force-long -D LANG_EN --tree -o ../hh-en/index.html manual.u %1 %2 %3 %4 %5 %6 %7 %8 %9
copy ../hh-en/index.ulh ../manual-en-hh.ulh
copy ../hh-en/index.uth ../manual-en-hh.uth
del ../hh-en/index.ulh
del ../hh-en/index.uth