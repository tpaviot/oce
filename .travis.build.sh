#! /bin/sh
set -e

ncpus=1
if test -x /usr/bin/getconf; then
    ncpus=$(/usr/bin/getconf _NPROCESSORS_ONLN)
fi
cmake -DOCE_ENABLE_DEB_FLAG:BOOL=OFF \
      -DCMAKE_BUILD_TYPE:STRING=Debug \
      -DOCE_USE_TCL_TEST_FRAMEWORK:BOOL=ON \
      -DOCE_TESTING:BOOL=ON \
      -DOCE_DRAW:BOOL=ON \
      -DOCE_VISUALISATION:BOOL=ON \
      -DOCE_OCAF:BOOL=ON \
      -DOCE_DATAEXCHANGE:BOOL=ON \
      -DOCE_USE_PCH:BOOL=ON \
      -DOCE_WITH_GL2PS:BOOL=ON \
      -DOCE_MULTITHREAD_LIBRARY:STRING=NONE \
      ..
echo ""
echo "Starting build with -j$ncpus ...";
make -j$ncpus

# Run OCE tests
make test

# Run OCCT tests, but overwrite DrawLaunchTests.draw to write
# an XML summary file at a specified location
sed -i -e 's/^testgrid$/testgrid -outdir occt -xml summary.xml -refresh 300/' DrawLaunchTests.draw

head -n -1 DrawLaunchTests.*
cmake -P DrawLaunchTests.cmake || true

