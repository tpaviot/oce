cd C:\projects\oce-win-bundle
mkdir cmake-build
cd cmake-build
cmake -DBUNDLE_BUILD_FREEIMAGE:BOOL=OFF ^
      -DBUNDLE_BUILD_FREETYPE:BOOL=ON ^
      -DBUNDLE_BUILD_GL2PS:BOOL=OFF ^
      -DBUNDLE_SHARED_LIBRARIES:BOOL=ON ^
      -DOCE_WIN_BUNDLE_INSTALL_DIR=C:\oce-win-bundle ^
      -G "%generator%" ..
msbuild /m:4 /verbosity:quiet /clp:ErrorsOnly /p:Configuration=Release oce-win-bundle.sln
msbuild /m:4 /verbosity:quiet /clp:ErrorsOnly /p:Configuration=Release INSTALL.vcxproj

cd C:\projects\oce
mkdir cmake-build
cd cmake-build
cmake -DOCE_VISUALISATION:BOOL=ON -DOCE_DATAEXCHANGE:BOOL=ON -DOCE_OCAF:BOOL=ON ^
      -DOCE_WITH_GL2PS:BOOL=OFF ^
      -DOCE_WITH_FREEIMAGE:BOOL=OFF ^
      -DOCE_TESTING:BOOL=OFF ^
      -DOCE_MULTITHREAD_LIBRARY=NONE ^
      -DFREETYPE_INCLUDE_DIR_freetype2=C:\oce-win-bundle\include\freetype ^
      -DFREETYPE_INCLUDE_DIR_ft2build=C:\oce-win-bundle\include\freetype ^
      -DFREETYPE_LIBRARY=C:\oce-win-bundle\%ARCH%\lib\freetype.lib ^
      -DFREEIMAGE_INCLUDE_DIR=C:\oce-win-bundle\include\FreeImage ^
      -DFREEIMAGE_LIBRARY=C:\oce-win-bundle\%ARCH%\lib\FreeImage.lib ^
      -DFREEIMAGEPLUS_LIBRARY=C:\oce-win-bundle\%ARCH%\lib\FreeImagePlus.lib ^
      -DOCE_INSTALL_PREFIX=C:\oce-%oce_version% ^
      -G "%generator%" ..
msbuild /m:4 /verbosity:quiet /p:Configuration=%configuration% oce.sln
msbuild /m:4 /verbosity:quiet /p:Configuration=%configuration% INSTALL.vcxproj
