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
msbuild /m:4 /verbosity:quiet /p:Configuration=%configuration% oce.sln
msbuild /m:4 /verbosity:quiet /p:Configuration=%configuration% INSTALL.vcxproj
cd ..
