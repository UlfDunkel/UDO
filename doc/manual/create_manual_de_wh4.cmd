@REM dieses bash-Skript konvertiert das deutsche UDO-Handbuch nach WinHelp4-Source
@REM this bash script converts the german UDO Manual to WinHelp4-Source
udo --win4 --verbose --force-long -D LANG_DE --tree -o ../wh4-de/manual-de.rtf manual.u %1 %2 %3 %4 %5 %6 %7 %8 %9