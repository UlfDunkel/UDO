@rem dieses Batchfile fuer Win32 + OS/2 konvertiert das UDO-Handbuch in Englisch nach HTML
@rem this batch file for Win32 + OS/2 converts the english UDO manual to HTML
udo --html --verbose --force-long -D LANG_EN --tree -o ../html-en/index.html ./manual.u
copy ..\html-en\index.ulh ..\manual-en.ulh
copy ..\html-en\index.uth ..\manual-en.uth
del ..\html-en\index.ulh
del ..\html-en\index.uth