@REM dieses Batchfile fuer Win32 + OS/2 konvertiert das englische UDO-Handbuch nach WinHelp4-Source
@REM this batch file for Win32 + OS/2 converts the english UDO Manual to WinHelp4-Source
udo --win4 --verbose --force-long -D LANG_EN --tree -o ../wh4-en/manual-en.rtf manual.u %1 %2 %3 %4 %5 %6 %7 %8 %9