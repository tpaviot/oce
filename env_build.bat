@echo off
rem Set environment for building OCCT or derived projects (e.g. samples)
rem (to be called before env.bat)

rem Use first argument to specify version of Visual Studio (vc8, vc9, or vc10),
rem second argument specifies architecture) (win32 or win64)
rem Default is vc8 win32

set VCVER=vc8
set "VCVARS=%VS80COMNTOOLS%..\..\VC\vcvarsall.bat"
set "DevEnvDir=%VS80COMNTOOLS%..\IDE"
if not "%1" == "" (
    if /I "%1" == "vc8" (
        set VCVER=vc8
        set "VCVARS=%VS80COMNTOOLS%..\..\VC\vcvarsall.bat"
        set "DevEnvDir=%VS80COMNTOOLS%..\IDE"
    ) else if /I "%1" == "vc9" (
        set VCVER=vc9
        set "VCVARS=%VS90COMNTOOLS%..\..\VC\vcvarsall.bat"
        set "DevEnvDir=%VS90COMNTOOLS%..\IDE"
    ) else if /I "%1" == "vc10" (
        set VCVER=vc10
        set "VCVARS=%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"
        set "DevEnvDir=%VS100COMNTOOLS%..\IDE"
    ) else (
        echo Error: first argument ^(%1^) should specify supported version of Visual C++,
        echo one of: vc8 ^(VS 2005 SP1^), vc9 ^(VS 2008 SP1^), or vc10 ^(VS 2010^)
        exit
    )
)

set ARCH=32
set TBBARCH=ia32
set VCARCH=x86
if not "%2" == "" (
    if /I "%2" == "win32" (
        set ARCH=32
        set TBBARCH=ia32
        set VCARCH=x86
    ) else if /I "%2" == "win64" (
        set ARCH=64
        set TBBARCH=intel64
        set VCARCH=amd64
    ) else (
        echo Error: second argument ^(%2^) should specify supported architecture,
        echo one of: win32 or win64
        exit
    )
)

rem Use variable CSF_DEFINES to specify additional compiler macros if necessary
rem (list separated by semicolons, or just semicolon if empty):
rem HAVE_TBB - use if you want to build OCCT with Intel TBB
rem HAVE_FREEIMAGE - use if you want to build OCCT with FreeImage
rem HAVE_GL2PS - use if you want to build OCCT with gl2ps

set CSF_DEFINES=HAVE_TBB;HAVE_FREEIMAGE;HAVE_GL2PS

rem Modify the line below according to actual location of the third-party 
rem components installed with headers and lib files; also check the following
rem settings. By default third-party tools are expected to be unpacked 
rem to subfolder 3rdparty from pre-built packages distributed with OCCT

set "PRODUCTS_PATH=%~dp0..\3rdparty"

set "TCLHOME=%PRODUCTS_PATH%\tcltk-85-%ARCH%"
set "QTDIR=%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%"
set "FTDIR=%PRODUCTS_PATH%\freetype-2.3.7-%VCVER%-%ARCH%"
set "FTGLDIR=%PRODUCTS_PATH%\ftgl-2.1.2-%VCVER%-%ARCH%"
set "GL2PSDIR=%PRODUCTS_PATH%\gl2ps-1.3.5-%VCVER%-%ARCH%"
set "FREEIMAGEDIR=%PRODUCTS_PATH%\freeimage-%VCVER%-%ARCH%"

set "TBBDIR=%PRODUCTS_PATH%\tbb30_018oss"
set "TBBBIN=%TBBDIR%\bin\%TBBARCH%\%VCVER%"

set "INCLUDE=%FREEIMAGEDIR%\include;%TBBDIR%\include;%TCLHOME%\include;%FTDIR%\include;%FTDIR%\include\freetype;%FTGLDIR%\include;%GL2PSDIR%\include;%QTDIR%\include\QtGui;%QTDIR%\include\QtCore;%QTDIR%\include\Qt;%QTDIR%\include;%INCLUDE%"
set "LIB=%FREEIMAGEDIR%\lib;%TCLHOME%\lib;%FTGLDIR%\lib;%GL2PSDIR%\lib;%QTDIR%\lib;%TBBDIR%\lib\%TBBARCH%\%VCVER%;%LIB%"

rem Call env.bat to set launch environment
set "CASBIN=win%ARCH%\%VCVER%"
call "%~dp0env.bat"

rem Set standard environment for selected version of Visual C++
if exist "%VCVARS%" (
    call "%VCVARS%" %VCARCH% 
) else (
    echo Error: could not find requested version of Visual C++ ^(%VCVER%^) installed!
    echo Check relevant environment variable ^(e.g. VS80COMNTOOLS for vc8^)
)

rem Workaround for problems of building by VS2010 in 64 bit mode
if /I "%VCVER%" == "vc10" (
    if "%ARCH%" == "64" (
        set "PATH=%VS100COMNTOOLS%..\..\VC\bin\x86_amd64;%PATH%"
    )
    echo Attention: If you get problem during compilation with embedding manifests 
    echo            ^(mt.exe^), try building ^(not rebuilding^) for the second time 
)
