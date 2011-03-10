@echo off
rem Launch MS VC with environment prepared for building OCCT

rem Use:
rem - first argument specifies version of Visual Studio (vc8, vc9, or vc10),
rem - second argument specifies mode (win32 or win64),
rem - third argument specifies path to solution to be loaded
rem - fourth argument is path to MS project solution
rem Default options are:
rem   vc8 win32 Debug adm\win32\vc8\OCCT.sln

rem Set build mode
set CASDEB=d
if not "%3" == "" (
    if /I "%3" == "Debug" (
        set CASDEB=d
    ) else if /I "%3" == "Release" (
        set CASDEB=
    ) else (
        echo Error: third argument ^(%3^) should specify build mode,
        echo one of: Debug or Release
        exit
    )
)

rem Set build environment 
call "%~dp0env_build.bat" %1 %2

rem Define path to project file
set "PRJFILE=%~dp0\adm\win%ARCH%\%VCVER%\OCCT.sln"
if not "%4" == "" (
    set "PRJFILE=%4"
)

rem Launch Visual Studio - either professional (devenv) or Express, as available
if exist "%DevEnvDir%\devenv.exe"  (
    start devenv.exe "%PRJFILE%" /useenv
) else if exist "%DevEnvDir%\VCExpress.exe"  (
    start VCExpress.exe "%PRJFILE%" /useenv
) else (
    echo Error: Could not find MS Visual Studio ^(%VCVER%^)
    echo Check relevant environment variable ^(e.g. VS80COMNTOOLS for vc8^)
)

