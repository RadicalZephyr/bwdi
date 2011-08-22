@echo off
if not exist svnrev.h (
echo #define SVN_REV 0 >> svnrev.h
echo #define SVN_REV_STR "0" >> svnrev.h
echo. >> svnrev.h
echo #ifdef _DEBUG >> svnrev.h
echo   #define _IS__DEBUG 1 >> svnrev.h
echo   #define _BUILD_STR "DEBUG" >> svnrev.h
echo #else >> svnrev.h
echo   #define _IS_DEBUG 0 >> svnrev.h
echo   #define _BUILD_STR "RELEASE" >> svnrev.h
echo #endif >> svnrev.h
echo. >> svnrev.h
echo #define STARCRAFT_VERSION "1.16.1" >> svnrev.h

echo stub generated

pause

) else (
echo svnrev.h already exists, nothing to do here
pause
)