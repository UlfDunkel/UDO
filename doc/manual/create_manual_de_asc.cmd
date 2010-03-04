@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das deutsche UDO-Handbuch nach ASCII (text)
@REM this batch file for Win32 + OS/2  converts the german UDO Manual to ASCII (text format)
udo --asc --verbose --force-long -D LANG_DE manual.u -o manual-de.txt