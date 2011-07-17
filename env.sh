#!/bin/sh -f

export CASROOT="Open CASCADE location/ros"

OS_NAME=`uname`

export OCCT3RDPARTY="3rdparty products for building and launching Open CASCADE Technology and samples"

#Please define carefully listed below environment variables
if [ ! -n $TCLHOME ]; then export TCLHOME=$OCCT3RDPARTY/tcltk ; fi
if [ ! -n $QTDIR ]; then export QTDIR=$OCCT3RDPARTY/qt ; fi
if [ ! -n $FTGLDIR ]; then export FTGLDIR=$OCCT3RDPARTY/ftgl ; fi
if [ ! -n $GL2PSDIR ]; then export GL2PSDIR=$OCCT3RDPARTY/gl2ps ; fi
if [ ! -n $FREEIMAGEDIR ]; then export FREEIMAGEDIR=$OCCT3RDPARTY/freeimage ; fi
if [ ! -n $TBBBIN ]; then export TBBBIN=$OCCT3RDPARTY/tbb/bin ; fi
if [ ! -n $TBBLIB ]; then export TBBLIB=$OCCT3RDPARTY/tbb/lib ; fi

if [ -z "PATH" ];
then export PATH=$TCLHOME/bin:$QTDIR/bin:$FTGLDIR/bin:$GL2PSDIR/bin:$FREEIMAGEDIR/bin:$TBBBIN:$CASROOT/$OS_NAME/bin;
else export PATH=$TCLHOME/bin:$QTDIR/bin:$FTGLDIR/bin:$GL2PSDIR/bin:$FREEIMAGEDIR/bin:$TBBBIN:$CASROOT/$OS_NAME/bin:$PATH;
fi

if [ -z "LD_LIBRARY_PATH" ];
then export LD_LIBRARY_PATH=$TCLHOME/lib:$QTDIR/lib:$FTGLDIR/lib:$FREEIMAGEDIR/lib:$GL2PSDIR/lib:$TBBLIB:$CASROOT/$OS_NAME/lib;
else export LD_LIBRARY_PATH=$TCLHOME/lib:$QTDIR/lib:$FTGLDIR/lib:$FREEIMAGEDIR/lib:$GL2PSDIR/lib:$TBBLIB:$CASROOT/$OS_NAME/lib:$LD_LIBRARY_PATH;
fi

export CSF_MDTVFontDirectory=$CASROOT/src/FontMFT
export CSF_LANGUAGE=us
export MMGT_CLEAR=1
export CSF_EXCEPTION_PROMPT=1
export CSF_SHMessage=$CASROOT/src/SHMessage
export CSF_MDTVTexturesDirectory=$CASROOT/src/Textures
export CSF_XSMessage=$CASROOT/src/XSMessage
export CSF_StandardDefaults=$CASROOT/src/StdResource
export CSF_PluginDefaults=$CASROOT/src/StdResource
export CSF_XCAFDefaults=$CASROOT/src/StdResource
export CSF_StandardLiteDefaults=$CASROOT/src/StdResource
export CSF_GraphicShr=$CASROOT/$OS_NAME/lib/libTKOpenGl.so
export CSF_UnitsLexicon=$CASROOT/src/UnitsAPI/Lexi_Expr.dat
export CSF_UnitsDefinition=$CASROOT/src/UnitsAPI/Units.dat
export CSF_IGESDefaults=$CASROOT/src/XSTEPResource
export CSF_STEPDefaults=$CASROOT/src/XSTEPResource
export CSF_XmlOcafResource=$CASROOT/src/XmlOcafResource
export CSF_MIGRATION_TYPES=$CASROOT/src/StdResource/MigrationSheet.txt

export TCLLIBPATH=$TCLHOME/lib

export TCLLIBPATH=$TCLHOME/lib
export TCL_LIBRARY=$TCLLIBPATH/tcl8.5
export TK_LIBRARY=$TCLLIBPATH/tk8.5
export TCLX_LIBRARY=$TCLLIBPATH/tclx8.4
export TCLLIBPATH="$TCLHOME/bin $TCLHOME/lib $TCL_LIBRARY $TK_LIBRARY $TCLX_LIBRARY"
