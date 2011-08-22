rem --- helper function for the "assemble" cmd

copy /Y %1 %dest%\%2\ > nul
if ERRORLEVEL 1 goto eerr
goto eend
:eerr
echo --- Failed to copy %1
:eend
