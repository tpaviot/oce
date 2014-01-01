@echo off

set VCVER=vc9
set ARCH=32
set "VCVARS=%VS90COMNTOOLS%..\..\VC\vcvarsall.bat"
set "PRODUCTS_PATH=%~dp0.."

rem Optional 3rd-parties switches
set HAVE_FREEIMAGE=true
set HAVE_GL2PS=true
set HAVE_TBB=true
set HAVE_OPENCL=true
set CHECK_QT4=true
set CHECK_JDK=true

rem Additional headers search paths
set "CSF_OPT_INC=%PRODUCTS_PATH%\opencl-icd-1.2.11.0-%ARCH%\include;%PRODUCTS_PATH%\tcltk-86-%ARCH%\include;%PRODUCTS_PATH%\freetype-2.4.11-%VCVER%-%ARCH%\include;%PRODUCTS_PATH%\freeimage-3.15.4-%VCVER%-%ARCH%\include;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-%ARCH%\include;%PRODUCTS_PATH%\tbb30_018oss\include;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\include;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\include\Qt;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\include\QtGui;%PRODUCTS_PATH%\qt462-%VCVER%-%ARCH%\include\QtCore;%PRODUCTS_PATH%\jdk1.6.0-%ARCH%\include;%PRODUCTS_PATH%\jdk1.6.0-%ARCH%\include\win32"

rem Additional libraries (32-bit) search paths
set "CSF_OPT_LIB32=%PRODUCTS_PATH%\opencl-icd-1.2.11.0-32\lib;%PRODUCTS_PATH%\tcltk-86-32\lib;%PRODUCTS_PATH%\freetype-2.4.11-%VCVER%-32\lib;%PRODUCTS_PATH%\freeimage-3.15.4-%VCVER%-32\lib;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-32\lib;%PRODUCTS_PATH%\tbb30_018oss\lib\ia32\%VCVER%;%PRODUCTS_PATH%\qt462-%VCVER%-32\lib"

rem Additional libraries (64-bit) search paths
set "CSF_OPT_LIB64=%PRODUCTS_PATH%\opencl-icd-1.2.11.0-64\lib;%PRODUCTS_PATH%\tcltk-86-64\lib;%PRODUCTS_PATH%\freetype-2.4.11-%VCVER%-64\lib;%PRODUCTS_PATH%\freeimage-3.15.4-%VCVER%-64\lib;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-64\lib;%PRODUCTS_PATH%\tbb30_018oss\lib\intel64\%VCVER%;%PRODUCTS_PATH%\qt462-%VCVER%-64\lib"

rem Additional (32-bit) search paths
set "CSF_OPT_BIN32=%PRODUCTS_PATH%\opencl-icd-1.2.11.0-32\bin;%PRODUCTS_PATH%\tcltk-86-32\bin;%PRODUCTS_PATH%\freetype-2.4.11-%VCVER%-32\bin;%PRODUCTS_PATH%\freeimage-3.15.4-%VCVER%-32\bin;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-32\bin;%PRODUCTS_PATH%\tbb30_018oss\bin\ia32\%VCVER%;%PRODUCTS_PATH%\qt462-%VCVER%-32\bin;%PRODUCTS_PATH%\jdk1.6.0-32\bin"

rem Additional (64-bit) search paths
set "CSF_OPT_BIN64=%PRODUCTS_PATH%\opencl-icd-1.2.11.0-64\bin;%PRODUCTS_PATH%\tcltk-86-64\bin;%PRODUCTS_PATH%\freetype-2.4.11-%VCVER%-64\bin;%PRODUCTS_PATH%\freeimage-3.15.4-%VCVER%-64\bin;%PRODUCTS_PATH%\gl2ps-1.3.8-%VCVER%-64\bin;%PRODUCTS_PATH%\tbb30_018oss\bin\intel64\%VCVER%;%PRODUCTS_PATH%\qt462-%VCVER%-64\bin;%PRODUCTS_PATH%\jdk1.6.0-64\bin"
