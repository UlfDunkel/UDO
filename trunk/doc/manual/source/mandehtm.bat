@rem dieses Batchfile fuer DOS konvertiert das UDO-Handbuch in Deutsch nach HTML
@rem this batch file for DOS converts the german UDO manual to HTML
udo --html --verbose -D LANG_DE --tree -o d:\udotest\index.html manual.u
copy ..\html-de\index.ulh ..\manual-de.ulh
copy ..\html-de\index.uth ..\manual-de.uth
del ..\html-de\index.ulh
del ..\html-de\index.uth