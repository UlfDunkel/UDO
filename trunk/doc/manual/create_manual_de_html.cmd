@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das deutsche UDO-Handbuch nach HTML
@REM this batch file for Win32 + OS/2 converts the german UDO manual to HTML
@REM udo --html --verbose --force-long -D LANG_DE --tree -o ../html-de/index.html manual.u %1 %2 %3 %4 %5 %6 %8 %8 %9
udo --html --verbose -D LANG_DE --tree -o ../html-de/index.htm manual.u %1 %2 %3 %4 %5 %6 %8 %8 %9
@REM copy ..\html-de\index.ulh ..\manual-de.ulh
@REM copy ..\html-de\index.uth ..\manual-de.uth
@REM del ..\html-de\index.ulh
@REM del ..\html-de\index.uth
pause