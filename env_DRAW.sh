#!/bin/sh -f

export CASROOT="LOCATION OF OCCT"
export OCCT3RDPARTY="LOCATION OF OCCT3RDPARTY"

export TCLHOME=$OCCT3RDPARTY/tcltk
export FTGLDIR=$OCCT3RDPARTY/ftgl
export GL2PSDIR=$OCCT3RDPARTY/gl2ps
export FREEIMAGEDIR=$OCCT3RDPARTY/freeimage
export TBBBIN=$OCCT3RDPARTY/tbb/bin
export TBBLIB=$OCCT3RDPARTY/tbb/lib

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
export CSF_GraphicShr=$CASROOT/lin/lib/libTKOpenGl.so
export CSF_UnitsLexicon=$CASROOT/src/UnitsAPI/Lexi_Expr.dat
export CSF_UnitsDefinition=$CASROOT/src/UnitsAPI/Units.dat
export CSF_IGESDefaults=$CASROOT/src/XSTEPResource
export CSF_STEPDefaults=$CASROOT/src/XSTEPResource
export CSF_XmlOcafResource=$CASROOT/src/XmlOcafResource
export CSF_MIGRATION_TYPES=$CASROOT/src/StdResource/MigrationSheet.txt

export TCL_LIBRARY=$TCLHOME/tcl8.5
export TK_LIBRARY=$TCLHOME/tk8.5
export TCLX_LIBRARY=$TCLHOME/tclx8.4
export TCLLIBPATH="$TCLHOME/bin $TCLHOME/lib $TCL_LIBRARY $TK_LIBRARY $TCLX_LIBRARY"

export PATH=$TCLHOME/bin:$FTGLDIR/bin:$GL2PSDIR/bin:$FREEIMAGEDIR/bin:$TBBBIN:$CASROOT/lin/bin:$PATH
export LD_LIBRARY_PATH=$TCLHOME/lib:$FTGLDIR/lib:$GL2PSDIR/lib:$FREEIMAGEDIR/lib:$TBBLIB:$CASROOT/lin/lib:$LD_LIBRARY_PATH
