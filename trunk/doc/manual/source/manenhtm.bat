@rem dieses Batchfile fuer DOS konvertiert das UDO-Handbuch in Englisch nach HTML
@rem this batch file for DOS converts the english UDO manual to HTML
udo --html --verbose -D LANG_EN --tree -o ../html-en/index.html ./manual.u %1 %2 %3 %4 %5 %6 %8 %8 %9
copy ..\html-en\index.ulh ..\manual-en.ulh
copy ..\html-en\index.uth ..\manual-en.uth
del ..\html-en\index.ulh
del ..\html-en\index.uth