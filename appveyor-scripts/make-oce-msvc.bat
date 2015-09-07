cd C:\projects\oce
mkdir cmake-build
cd cmake-build
cmake -DOCE_VISUALISATION:BOOL=ON -DOCE_DATAEXCHANGE:BOOL=ON -DOCE_OCAF:BOOL=ON ^
      -DOCE_WITH_GL2PS:BOOL=OFF ^
      -DOCE_WITH_FREEIMAGE:BOOL=OFF ^
      -DOCE_TESTING:BOOL=OFF ^
      -DOCE_MULTITHREAD_LIBRARY=NONE ^
      -DOCE_INSTALL_PREFIX=C:\oce-%oce_version% ^
      -G "%generator%" ..
msbuild /m:4 /verbosity:quiet /p:Configuration=%configuration% oce.sln
msbuild /m:4 /verbosity:quiet /p:Configuration=%configuration% INSTALL.vcxproj
