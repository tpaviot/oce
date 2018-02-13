cd C:\projects\oce
mkdir cmake-build
cd cmake-build
cmake -DOCE_VISUALISATION:BOOL=ON ^
      -DOCE_DATAEXCHANGE:BOOL=OFF ^
      -DOCE_OCAF:BOOL=OFF ^
      -DOCE_WITH_GL2PS:BOOL=ON ^
      -DOCE_WITH_FREEIMAGE:BOOL=OFF ^
      -DOCE_TESTING:BOOL=ON ^
      -DOCE_COPY_HEADERS_BUILD:BOOL=ON ^
      -DOCE_INSTALL_PREFIX=C:\oce-0.18.3 ^
      -G "%generator%" ..
mingw32-make -j5
mingw32-make install
dir
dir C:\oce-0.18.3
set PATH=%PATH%;C:\oce-0.18.3\bin
mingw32-make test
cd ..
