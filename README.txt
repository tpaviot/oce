Open CASCADE rebuilding on Linux with autoconf, automake and libtool scripts.

On Linux Open CASCADE can be built from source files using scripts based on 
GNU autoconf, automake and libtool. 

Unpack CAS-6.5.tar.gz to some folder - ${DISTRIBUTIVE_DIR}.
for example DISTRIBUTIVE_DIR=/tmp/CAS-6.5

cd  ${DISTRIBUTIVE_DIR}

Configure step 

The ./configure must be executed with the flags as described below.

flags="--with-gl-include=/usr/include --with-gl-library=/usr/lib"
flags="$flags --with-xmu-include=/usr/X11R6/include/X11"
flags="$flags --with-xmu-library=/usr/X11R6/lib"
flags="$flags --with-tcl=${TCLHOME}/lib"
flags="$flags --with-tk=${TCLHOME}/lib "
flags="$flags --with-freetype=/usr/freetype-2.3.7"
flags="$flags --with-ftgl=/usr/ftgl-2.1.2"
flags="$flags --disable-debug --enable-production" 

where:
--enable-debug=yes/no - building in debug mode (yes: set -g key of compiler). 
--enable-production=yes/no - building in optimize mode. (yes: set -O key of compiler).

Additional flags
flags="$flags --with-tbb-include =/usr/tbb/include" - for compilation with tbb
flags="$flags --with-tbb-library=/usr/tbb/lib" - for compilation with tbb
flags="$flags --with-gl2ps=/usr/gl2ps-1.3.5" - for compilation with gl2ps
flags="$flags --with-freeimage=/usr/freeimage-3.14.1" - for compilation with freeimage

Additional information :
WOK and Wrappers (jcas) modules were removed from OCCT. So flags --enabled-wok and --enabled-wrappers were removed too.

export CASROOT=${DISTRIBUTIVE_DIR}

./configure $flags --prefix=${INSTALL_DIR}
where ${INSTALL_DIR} is folder to which Open CASCADE will be installed.

Make step

If configure exits successfully, you can then build of the whole Open CASCADE with 
the ./make and then ./make install command.

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

