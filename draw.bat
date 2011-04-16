@echo off
rem Launch DRAW

rem Use:
rem - first argument specifies version of Visual Studio (vc8, vc9, or vc10),
rem - second argument specifies architecture (win32 or win64),
rem - third argument specifies build mode (Debug or Release)
rem - fourth argument is path to MS project solution
rem Default options are:
rem   vc8 win32 Release

rem Set build mode
set CASDEB=
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
if "%1" == "" (
    call "%~dp0env.bat"
) else (
    call "%~dp0env_build.bat" %1 %2
)

echo Hint: use "pload ALL" command to load standard commands
DRAWEXE.exe