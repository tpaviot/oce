cd C:\projects\oce
mkdir cmake-build
cd cmake-build
cmake -DBUILD_WITH_DEBUG:BOOL=OFF ^
      -DCMAKE_BUILD_TYPE:STRING=Release ^
      -DBUILD_Inspector:BOOL=OFF ^
      -DUSE_TCL:BOOL=OFF ^
      -DUSE_GL2PS:BOOL=OFF ^
      -DUSE_FREEIMAGE:BOOL=OFF ^
      -DUSE_TBB:BOOL=OFF ^
      -DUSE_FFMPEG:BOOL=OFF ^
      -DUSE_VTK:BOOL=OFF ^
      -DOCE_INSTALL_PREFIX=C:\oce-%oce_version% ^
      -G "%generator%" ..
mingw32-make -j5
mingw32-make install
dir
dir C:\oce-0.18.3
set PATH=%PATH%;C:\oce-0.18.3\bin
mingw32-make test
cd ..
