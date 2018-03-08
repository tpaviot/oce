#! /bin/sh
set -e


#  Default values
: "${BUILD_USE_PCH=ON} ${USE_TBB=OFF} ${USE_FFMPEG=OFF} ${USE_GL2PS=OFF} ${USE_FREEIMAGE=OFF} ${BUILD_Inspector=OFF}"

echo "Timestamp" && date
cmake -DBUILD_WITH_DEBUG:BOOL=OFF \
      -DCMAKE_BUILD_TYPE:STRING=Release \
      -DBUILD_MODULE_Draw:BOOL=OFF \
      -DBUILD_USE_PCH:BOOL="${BUILD_USE_PCH}" \
      -DBUILD_Inspector:BOOL="${BUILD_Inspector=OFF}" \
      -DUSE_GL2PS:BOOL="${USE_GL2PS=OFF}" \
      -DUSE_FREEIMAGE:BOOL="${USE_FREEIMAGE=OFF}" \
      -DUSE_TBB:BOOL="${USE_TBB}" \
      -DUSE_FFMPEG:BOOL="${USE_FFMPEG}" \
      -DUSE_VTK:BOOL=OFF \
      ..
echo ""
echo "Timestamp" && date
if test "$RUN_TESTS" = true; then
    # travis-ci truncates when there are more than 10,000 lines of output.
    # Builds generate around 9,000 lines of output, trim them to see test
    # results.
    make -j8 | grep Built

    # Run OCE tests
    echo "Timestamp" && date
    make test

    # Run OCCT tests, but overwrite DrawLaunchTests.draw to write
    # an XML summary file at a specified location
    cat > DrawLaunchTests.draw <<EOT
testgrid -outdir occt -xml summary.xml -refresh 300
exit
EOT

    echo "Timestamp" && date
    cmake -P DrawLaunchTests.cmake || true
else
    make -j8
fi

echo "Timestamp" && date
