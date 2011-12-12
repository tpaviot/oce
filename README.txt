Open CASCADE Technology (OCCT) building on Linux with autoconf, automake and libtool scripts.

On Linux OCCT can be built from source files using scripts based on 
GNU autoconf, automake and libtool. 

Unpack OpenCASCADE652.tar.gz archive to some folder - ${DISTRIBUTIVE_DIR}.
for example DISTRIBUTIVE_DIR=/tmp/OpenCASCADE6.5.2

OCCT building
---------------------

Use OCCT_building_in_details_Linux.pdf document for building third-party products and OCCT itself.

OCCT Draw Test Harness
------------------------------

You can launch OCCT Draw Test Harness in order to experiment with the latter.

Before DRAW launching:

Edit env_DRAW.sh file in order to define $CASROOT and $OCCT3RDPARTY variable.
load $CASROOT/env_DRAW.sh file to set all necessary system variables.
Launch DRAWEXE executable from $CASROOT/bin folder.
Print 
> pload ALL 
in order to load DRAW commands

