@echo off
rem This batch assembles the files needed for a release.

set dest="Release Package\Stuff"
set collect=call "Release Package\funx_collect"

rmdir /S /Q Stuff > nul
if ERRORLEVEL 1 goto try_again
mkdir "Stuff"
mkdir "Stuff\icons"
mkdir "Stuff\Tracer Example"
mkdir "Stuff\include"
mkdir "Stuff\include\BWDI"
mkdir "Stuff\Chaoslauncher"
cd ..

%collect% "Release\BWDIDriver.dll"
%collect% "Release\BWDI.dll"
%collect% "Release\NoQuestionsAskedInstaller.exe"
%collect% "Release\BWDI_ChaosLauncherInjector.bwl"
%collect% "NoQuestionsAskedInstaller\icons\*.ico" "icons"
%collect% "Release\Tracer.exe" "Tracer Example"
%collect% "Tracer\Tracer.cpp" "Tracer Example"
%collect% "BWDI.h" "include"
%collect% "BWDI.cpp" "include"
%collect% "BWDI\*.*" "include\BWDI"
%collect% "Release Package\Chaoslauncher\*.exe" "Chaoslauncher"
%collect% "Release Package\Chaoslauncher\*.bwl" "Chaoslauncher"
echo done
goto quit_now
:try_again
echo try again later
:quit_now
pause
