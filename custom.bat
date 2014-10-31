@echo off

set VCVER=vc10
set ARCH=32
set "VCVARS=%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"
set "PRODUCTS_PATH=%~dp0.."

rem Optional 3rd-parties switches
set HAVE_FREEIMAGE=true
set HAVE_GL2PS=true
set HAVE_TBB=true
set HAVE_VTK=true
set CHECK_QT4=true
set CHECK_JDK=true

rem Additional headers search paths
set "CSF_OPT_INC=%PRODUCTS_PATH%\VTK-6.1.0-vc10-%ARCH%\include\vtk-6.1;%PRODUCTS_PATH%\tcltk-86-%ARCH%\include;%PRODUCTS_PATH%\freetype-2.5.3-%VCVER%-%ARCH%\include;%PRODUCTS_PATH%\freeimage-3.16.0-%VCVER%-%ARCH%\include;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-%ARCH%\include;%PRODUCTS_PATH%\tbb30_018oss\include;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\include;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\include\Qt;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\include\QtGui;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\include\QtCore;%PRODUCTS_PATH%\jdk1.6.0-%ARCH%\include;%PRODUCTS_PATH%\jdk1.6.0-%ARCH%\include\win32"

rem Additional libraries (32-bit) search paths
set "CSF_OPT_LIB32=%PRODUCTS_PATH%\VTK-6.1.0-vc10-%ARCH%\lib;%PRODUCTS_PATH%\tcltk-86-%ARCH%\lib;%PRODUCTS_PATH%\freetype-2.5.3-%VCVER%-%ARCH%\lib;%PRODUCTS_PATH%\freeimage-3.16.0-%VCVER%-%ARCH%\lib;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-%ARCH%\lib;%PRODUCTS_PATH%\tbb30_018oss\lib\ia32\%VCVER%;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\lib"

rem Additional libraries (64-bit) search paths
set "CSF_OPT_LIB64=%PRODUCTS_PATH%\VTK-6.1.0-vc10-%ARCH%\lib;%PRODUCTS_PATH%\tcltk-86-%ARCH%\lib;%PRODUCTS_PATH%\freetype-2.5.3-%VCVER%-%ARCH%\lib;%PRODUCTS_PATH%\freeimage-3.16.0-%VCVER%-%ARCH%\lib;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-%ARCH%\lib;%PRODUCTS_PATH%\tbb30_018oss\lib\intel64\%VCVER%;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\lib"

rem Additional (32-bit) search paths
set "CSF_OPT_BIN32=%PRODUCTS_PATH%\VTK-6.1.0-vc10-%ARCH%\bin;%PRODUCTS_PATH%\tcltk-86-%ARCH%\bin;%PRODUCTS_PATH%\freetype-2.5.3-%VCVER%-%ARCH%\bin;%PRODUCTS_PATH%\freeimage-3.16.0-%VCVER%-%ARCH%\bin;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-%ARCH%\bin;%PRODUCTS_PATH%\tbb30_018oss\bin\ia32\%VCVER%;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\bin;%PRODUCTS_PATH%\jdk1.6.0-%ARCH%\bin"

rem Additional (64-bit) search paths
set "CSF_OPT_BIN64=%PRODUCTS_PATH%\VTK-6.1.0-vc10-%ARCH%\bin;%PRODUCTS_PATH%\tcltk-86-%ARCH%\bin;%PRODUCTS_PATH%\freetype-2.5.3-%VCVER%-%ARCH%\bin;%PRODUCTS_PATH%\freeimage-3.16.0-%VCVER%-%ARCH%\bin;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-%ARCH%\bin;%PRODUCTS_PATH%\tbb30_018oss\bin\intel64\%VCVER%;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\bin;%PRODUCTS_PATH%\jdk1.6.0-%ARCH%\bin"
