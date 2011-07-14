This file describes how to build OCE from sources on Linux or MacOSX.

Since the OCE release 0.3, the dev team definitely dropped the autotools
support and adopted the CMake build system. First ensure you have installed
CMake 2.6 or higher (http://www.cmake.org) before going further in the
compilation process.

The installation procedure detailed below is:
 1. Download/extract the OCE-xxxxx.tar.gz archive to any directory
 2. Configure
 3. make/make install
 4. Test installation

1. Content extraction
=====================

Unpack OCE-xxxx.tar.gz to some folder - ${DISTRIBUTIVE_DIR}.
For example DISTRIBUTIVE_DIR=/tmp/OCE-0.3
 tar -zxvf OCE-xxxx.tar.gz
then
 cd  ${DISTRIBUTIVE_DIR}

2. Configure step
=================
It is a good practice to build in a separate directory:
 mkdir build
 cd build

CMake can be configured either by a user interface (Qt and ncurses interfaces
are available) or directly by running
 cmake ..
and editing the generated CMakeCache.txt file.

In the former case, the most common options can be defined from the
main window, and expert options can be modified in selecting "Advanced"
mode.
In the latter case, it is also possible to define options on the
command line.  If you edit CMakeCache.txt by hand, do not forget to
rerun cmake after modifying this file.

2.1 Defining flags
==================

Here are default flags on Unix
 OCE_BUILD_SHARED_LIB        ON
 OCE_DATAEXCHANGE            ON
 OCE_DRAW                    OFF
 OCE_INSTALL_PREFIX          /usr/local
 OCE_MODEL                   ON
 OCE_MULTITHREAD_LIBRARY     NONE
 OCE_OCAF                    ON
 OCE_VISUALISATION           ON
 OCE_WITH_FREEIMAGE          OFF
 OCE_WITH_GL2PS              OFF

In order to modify installation path and build DRAWEXE, one
can run these commands:

 flags=""
 flags="$flags -DOCE_INSTALL_PREFIX:PATH=$HOME/oce"
 flags="$flags -DOCE_DRAW:BOOL=ON"
 cmake $flags ..

2.2 Expert options
==================
More expert options can be defined in the "Advanced mode".

2.2.1 Additional flags:
=====================
OCE can be compiled with TBB or OpenMP in order to support parallel meshing.
By default, this support is disabled.  Enable it with
 flags="$flags -DOCE_MULTITHREAD_LIBRARY:STRING=TBB"
or
 flags="$flags -DOCE_MULTITHREAD_LIBRARY:STRING=OPENMP"

There are many more options, see CMakeCache.txt for a full list.

3. Make step
============
If configure exits successfully, you can then build the whole OCE
by running the following commands:

 make
 make install/strip

If you have more than one (for instance 2) cores on your machine, you can use
 make -j2
to enable multiprocessed compilation and speedup the whole compilation
process.

If you enabled tests when configuring by passing -DOCE_TESTING:BOOL=ON
flag to CMake, you can now run our battery of tests:

 make test

All tests should pass except BRepMeshTestSuite.testMeshTorus, this test
exhibits a bug which has not been fixed yet.

4. Test installation: OCE Draw Test Harness
===========================================
You can launch Draw Test Harness in order to experiment with OCE.
With OCE you normally do not have to set any environment variable.

Launch $INSTALL_DIR/bin/DRAWEXE executable; on prompt, type
 > pload ALL
In order to load DRAW commands, you can then run demos
 > source $INSTALL_DIR/src/DrawResources/ModelingDemo.tcl
 > source $INSTALL_DIR/src/DrawResources/VisualizationDemo.tcl

Installation is succesful. Enjoy!
