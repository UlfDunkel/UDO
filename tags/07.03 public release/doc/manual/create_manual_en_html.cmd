@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das englische UDO-Handbuch nach HTML
@REM this batch file for Win32 + OS/2 converts the english UDO manual to HTML
udo --html --verbose -D LANG_EN --tree -o ../html-en/index.htm ./manual.u %1 %2 %3 %4 %5 %6 %8 %8 %9
@REM copy ..\html-en\index.ulh ..\manual-en.ulh
@REM copy ..\html-en\index.uth ..\manual-en.uth
@REM del ..\html-en\index.ulh
@REM del ..\html-en\index.uth
pause
