@echo off
rem Use this script to configure Open CASCADE Technology environment before
rem launching your applications that use it. 
rem
rem Settings can be additionally configured by pre-defining some variables:
rem 
rem - Variable CASDEB can be defined to add a suffix to OCCT bin directory 
rem   names (typically 'd' for Debug)
rem 
rem - CASBIN variable can be used to specify different subdirectory for binary 
rem   files (by default win32); this is useful when builds on different 
rem   platforms (e.g. win64) or compilers are used
rem
rem - TCLHOME variable can be set to specify location of TCL installation if
rem   it should be used instead of the one provided with OCCT 

set "CASROOT=%~dp0"
rem Remove tailing backslash
set "CASROOT=%CASROOT:~0,-1%"

set "OCCT3RDPARTY=%CASROOT%\..\3rdparty\win32"

if ["%CASDEB%"] == [""] set CASDEB=
if ["%CASBIN%"] == [""] set CASBIN=win32\vc8
rem Automatically use win64 binaries on x86_64 Windows
rem if ["%PROCESSOR_ARCHITECTURE%"] == ["AMD64"] set CASBIN=win64
rem if ["%PROCESSOR_ARCHITEW6432%"] == ["AMD64"] set CASBIN=win64

rem Paths to third-party tools are set by default to locations as created
rem by installer if binaries are installed
if ["%TCLHOME%"]  == [""] set "TCLHOME=%OCCT3RDPARTY%\tcltk"
if ["%QTDIR%"]    == [""] set "QTDIR=%OCCT3RDPARTY%\qt"
if ["%FTGLDIR%"]  == [""] set "FTGLDIR=%OCCT3RDPARTY%\ftgl"
if ["%GL2PSDIR%"] == [""] set "GL2PSDIR=%OCCT3RDPARTY%\gl2ps"
if ["%FREEIMAGEDIR%"] == [""] set "FREEIMAGEDIR=%OCCT3RDPARTY%\freeimage"
if ["%TBBBIN%"]   == [""] set "TBBBIN=%OCCT3RDPARTY%\tbb\bin"

rem Set path to 3rd party and OCCT libraries
set "PATH=%CASROOT%\%CASBIN%\bin%CASDEB%;%PATH%"

set "PATH=%PATH%;%FTGLDIR%\bin;%GL2PSDIR%\bin;%FREEIMAGEDIR%\bin;%TBBBIN%;%TCLHOME%\bin;"

rem Set envoronment variables used by OCCT
set "CSF_MDTVFontDirectory=%CASROOT%\src\FontMFT"
set CSF_LANGUAGE=us
set MMGT_CLEAR=1
set CSF_EXCEPTION_PROMPT=1
set "CSF_SHMessage=%CASROOT%\src\SHMessage"
set "CSF_MDTVTexturesDirectory=%CASROOT%\src\Textures"
set "CSF_XSMessage=%CASROOT%\src\XSMessage"
set "CSF_TObjMessage=%CASROOT%\src\TObj"
set "CSF_StandardDefaults=%CASROOT%\src\StdResource"
set "CSF_PluginDefaults=%CASROOT%\src\StdResource"
set "CSF_XCAFDefaults=%CASROOT%\src\StdResource"
set "CSF_TObjDefaults=%CASROOT%\src\StdResource"
set "CSF_StandardLiteDefaults=%CASROOT%\src\StdResource"
set "CSF_GraphicShr=TKOpenGl.dll"
set "CSF_UnitsLexicon=%CASROOT%\src\UnitsAPI\Lexi_Expr.dat"
set "CSF_UnitsDefinition=%CASROOT%\src\UnitsAPI\Units.dat"
set "CSF_IGESDefaults=%CASROOT%\src\XSTEPResource"
set "CSF_STEPDefaults=%CASROOT%\src\XSTEPResource"
set "CSF_XmlOcafResource=%CASROOT%\src\XmlOcafResource"
set "CSF_MIGRATION_TYPES=%CASROOT%\src\StdResource\MigrationSheet.txt"

rem Set paths to Tcl 
set "TCLLIBPATH=%TCLHOME%\lib"
set "TCL_LIBRARY=%TCLLIBPATH%\tcl8.5"
set "TK_LIBRARY=%TCLLIBPATH%\tk8.5"
set "TCLX_LIBRARY=%TCLLIBPATH%\teapot\package\win32-ix86\lib\Tclx8.4"
set "TCLLIBPATH=%TCLHOME%/bin %TCLHOME%/lib %TCL_LIBRARY% %TK_LIBRARY% %TCLX_LIBRARY%"
