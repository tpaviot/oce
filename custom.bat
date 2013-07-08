@echo off

set VCVER=vc9
set ARCH=32
set "VCVARS=%VS90COMNTOOLS%..\..\VC\vcvarsall.bat"
set "PRODUCTS_PATH=%~dp0..\3rdparty"

rem Optional 3rd-parties switches
set HAVE_FREEIMAGE=true
set HAVE_GL2PS=true
set HAVE_TBB=true
set CHECK_QT4=true
set CHECK_JDK=true

rem Additional headers search paths
set "CSF_OPT_INC=%PRODUCTS_PATH%\tcltk-85-32\include;%PRODUCTS_PATH%\freetype-2.4.10-vc9-32\include;%PRODUCTS_PATH%\freeimage-vc9-32\include;%PRODUCTS_PATH%\gl2ps-1.3.5-vc9-32\include;%PRODUCTS_PATH%\tbb30_018oss\include;%PRODUCTS_PATH%\qt462-vc9-32\include;%PRODUCTS_PATH%\qt462-vc9-32\include\Qt;%PRODUCTS_PATH%\qt462-vc9-32\include\QtGui;%PRODUCTS_PATH%\qt462-vc9-32\include\QtCore;%PRODUCTS_PATH%\jdk1.6.0-32\include;%PRODUCTS_PATH%\jdk1.6.0-32\include\win32"

rem Additional libraries (32-bit) search paths
set "CSF_OPT_LIB32=%PRODUCTS_PATH%\tcltk-85-32\lib;%PRODUCTS_PATH%\freetype-2.4.10-vc9-32\lib;%PRODUCTS_PATH%\freeimage-vc9-32\lib;%PRODUCTS_PATH%\gl2ps-1.3.5-vc9-32\lib;%PRODUCTS_PATH%\tbb30_018oss\lib\ia32\vc9;%PRODUCTS_PATH%\qt462-vc9-32\lib"

rem Additional libraries (64-bit) search paths
set "CSF_OPT_LIB64=%PRODUCTS_PATH%\tcltk-85-64\lib;%PRODUCTS_PATH%\freetype-2.4.10-vc9-64\lib;%PRODUCTS_PATH%\freeimage-vc9-64\lib;%PRODUCTS_PATH%\gl2ps-1.3.5-vc9-64\lib;%PRODUCTS_PATH%\tbb30_018oss\lib\intel64\vc9;%PRODUCTS_PATH%\qt462-vc9-64\lib"

rem Additional (32-bit) search paths
set "CSF_OPT_BIN32=%PRODUCTS_PATH%\tcltk-85-32\bin;%PRODUCTS_PATH%\freetype-2.4.10-vc9-32\bin;%PRODUCTS_PATH%\freeimage-vc9-32\bin;%PRODUCTS_PATH%\gl2ps-1.3.5-vc9-32\bin;%PRODUCTS_PATH%\tbb30_018oss\bin\ia32\vc9;%PRODUCTS_PATH%\qt462-vc9-32\bin;%PRODUCTS_PATH%\jdk1.6.0-32\bin"

rem Additional (64-bit) search paths
set "CSF_OPT_BIN64=%PRODUCTS_PATH%\tcltk-85-64\bin;%PRODUCTS_PATH%\freetype-2.4.10-vc9-64\bin;%PRODUCTS_PATH%\freeimage-vc9-64\bin;%PRODUCTS_PATH%\gl2ps-1.3.5-vc9-64\bin;%PRODUCTS_PATH%\tbb30_018oss\bin\intel64\vc9;%PRODUCTS_PATH%\qt462-vc9-64\bin;%PRODUCTS_PATH%\jdk1.6.0-64\bin"
