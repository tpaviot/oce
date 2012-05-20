@echo off

rem Setup environment
call "%~dp0env.bat" %1 %2 %3

rem Define path to project file
set "PRJFILE=%~dp0\adm\msvc\%VCVER%\OCCT.sln"
if not exist "%PRJFILE%" set "PRJFILE=%~dp0\adm\msvc\%VCVER%\Products.sln"
if not "%4" == "" (
  set "PRJFILE=%4"
)

if "%VCVER%" == "vc8" (
  set "DevEnvDir=%VS80COMNTOOLS%..\IDE"
) else if "%VCVER%" == "vc9" (
  set "DevEnvDir=%VS90COMNTOOLS%..\IDE"
) else if "%VCVER%" == "vc10" (
  set "DevEnvDir=%VS100COMNTOOLS%..\IDE"
) else (
  echo Error: wrong VS identifier
  exit /B
)

rem Launch Visual Studio - either professional (devenv) or Express, as available
if exist "%DevEnvDir%\devenv.exe"  (
  start "%DevEnvDir%\devenv.exe" "%PRJFILE%"
) else if exist "%DevEnvDir%\VCExpress.exe"  (
  start "%DevEnvDir%\VCExpress.exe" "%PRJFILE%"
) else (
  echo Error: Could not find MS Visual Studio ^(%VCVER%^)
  echo Check relevant environment variable ^(e.g. VS80COMNTOOLS for vc8^)
)
