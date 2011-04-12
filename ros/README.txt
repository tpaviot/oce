On Linux or MacOSX, OCE can be built from source files using scripts
based on GNU autoconf, automake and libtool. 

The installation workflow is to:
1. Download/extract the OCExxxxx.tar.gz archive to any directory
2. ./configure
3 make/make install
4. Test installation

1. Content extraction
=====================

Unpack OCExxxx.tar.gz to some folder - ${DISTRIBUTIVE_DIR}.
for example DISTRIBUTIVE_DIR=/tmp/OCE-0.1
$tar -zxvf OCExxxx.tar.gz
then
$cd  ${DISTRIBUTIVE_DIR}/ros

2. Configure step
=================
The ./configure must be executed with the flags as described below.

2.1 Defining flags
==================
flags=""
flags="$flags --with-tcl=${TCLHOME}/lib"
flags="$flags --with-tk=${TCLHOME}/lib "
flags="$flags --with-freetype=/opt/freetype-2.3.7"
flags="$flags --with-ftgl=/opt/ftgl-2.1.3-rc5"
flags="$flags --disable-debug --enable-production" 

where:
--enable-debug=yes/no - building in debug mode (yes: set -g key of compiler). 
--enable-production=yes/no - building in optimize mode. (yes: set -O key of
compiler).

2.2 FTGL note:
==============
OCE supports either ftgl-2.1.2 or the latest ftgl-2.1.3-rc5. If you wish to
build OCE over ftgl-2.1.2, use the compilation flag '--with-ftgl212'.
For instance,
flags="$flags --with-ftg212=/opt/ftgl-2.1.2"
The '--with-ftgl' flag assumes you use a newer version.

2.3 Additional flags:
=====================
flags="$flags --with-tbb-include =/usr/include/tbb" - for compilation with tbb
flags="$flags --with-tbb-library=/usr/lib" - for compilation with tbb
flags="$flags --with-gl2ps=/opt/gl2ps-1.3.5" - for compilation with gl2ps
flags="$flags --with-freeimage=/opt/freeimage-3.14.1" - for compil with freeimage


2.4 Running ./configure
=======================

$export CASROOT=${DISTRIBUTIVE_DIR}

$./configure $flags --prefix=${INSTALL_DIR}

where ${INSTALL_DIR} is folder to which OCE will be installed.

3. Make step
============
If configure exits successfully, you can then build of the whole OCE
by running the following commands:
 
$make
$make install


4. Test installation: OCE Draw Test Harness
============================================
You can launch Draw Test Harness in order to experiment with OCE.

Before DRAW launching, take care to:
$export CASROOT=${INSTALL_DIR}
$load $CASROOT/env_DRAW.sh file to set all necessary system variables.

Launch DRAWEXE executable from $CASROOT/bin folder.
Print 
> pload ALL 
in order to load DRAW commands

Installation is succesfull. Enjoy!
