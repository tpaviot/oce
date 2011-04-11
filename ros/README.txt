Open CASCADE rebuilding on Linux with autoconf, automake and libtool scripts.

On Linux Open CASCADE can be built from source files using scripts based on 
GNU autoconf, automake and libtool. 

Unpack CAS-6.5.tar.gz to some folder - ${DISTRIBUTIVE_DIR}.
for example DISTRIBUTIVE_DIR=/tmp/CAS-6.5

cd  ${DISTRIBUTIVE_DIR}

Configure step 

The ./configure must be executed with the flags as described below.

flags=""
flags="$flags --with-tcl=${TCLHOME}/lib"
flags="$flags --with-tk=${TCLHOME}/lib "
flags="$flags --with-freetype=/opt/freetype-2.3.7"
flags="$flags --with-ftgl=/opt/ftgl-2.1.3-rc5"
flags="$flags --disable-debug --enable-production" 

where:
--enable-debug=yes/no - building in debug mode (yes: set -g key of compiler). 
--enable-production=yes/no - building in optimize mode. (yes: set -O key of compiler).

FTGL note:
==========
OCE supports either ftgl-2.1.2 or the latest ftgl-2.1.3-rc5. If you wish to
build OCE over ftgl-2.1.2, use the compilation flag '--with-ftgl212'.
For instance,
flags="$flags --with-ftg212=/opt/ftgl-2.1.2"
The '--with-ftgl' flag assumes you use a newer version.

Additional flags
flags="$flags --with-tbb-include =/usr/include/tbb" - for compilation with tbb
flags="$flags --with-tbb-library=/usr/lib" - for compilation with tbb
flags="$flags --with-gl2ps=/opt/gl2ps-1.3.5" - for compilation with gl2ps
flags="$flags --with-freeimage=/opt/freeimage-3.14.1" - for compilation with freeimage

Additional information :
WOK and Wrappers (jcas) modules were removed from OCCT. So flags --enabled-wok and --enabled-wrappers were removed too.

export CASROOT=${DISTRIBUTIVE_DIR}

./configure $flags --prefix=${INSTALL_DIR}
where ${INSTALL_DIR} is folder to which Open CASCADE will be installed.

Make step

If configure exits successfully, you can then build of the whole Open CASCADE
by running the following commands:
  make
  make install

Usage

When built in such way, Open CASCADE can be used for building and launching Salome. 

Open CASCADE Draw Test Harness

You can launch Open CASCADE Draw Test Harness in order to experiment with Open CASCADE.

Before DRAW launching:

export CASROOT=${INSTALL_DIR}
load $CASROOT/env_DRAW.sh file to set all necessary system variables.
Launch DRAWEXE executable from $CASROOT/bin folder.
Print 
> pload ALL 
in order to load DRAW commands

