#!/bin/csh -f

setenv CASROOT "Open CASCADE location/ros"

setenv OS_NAME `uname`

setenv OCCT3RDPARTY "3rdparty products for building and launching Open CASCADE Technology and samples"

#Please define carefully listed below environment variables
if (! $?TCLHOME ) then 
    setenv TCLHOME $OCCT3RDPARTY/tcltk 
endif
if (! $?QTDIR ) then 
    setenv QTDIR $OCCT3RDPARTY/qt 
endif
if (! $?FTGLDIR ) then 
    setenv FTGLDIR $OCCT3RDPARTY/ftgl 
endif
if (! $?GL2PSDIR ) then 
    setenv GL2PSDIR $OCCT3RDPARTY/gl2ps 
endif
if (! $?FREEIMAGEDIR ) then 
    setenv FREEIMAGEDIR $OCCT3RDPARTY/freeimage
endif
if (! $?TBBBIN ) then 
    setenv TBBBIN $OCCT3RDPARTY/tbb/bin 
endif
if (! $?TBBLIB ) then 
    setenv TBBLIB $OCCT3RDPARTY/tbb/lib 
endif

if ( $?PATH ) then
      setenv PATH "$TCLHOME/bin:$QTDIR/bin:$FTGLDIR/bin:$GL2PSDIR/bin:$FREEIMAGEDIR/bin:$TBBBIN:$CASROOT/$OS_NAME/bin:$PATH"
else 
      setenv PATH "$TCLHOME/bin:$QTDIR/bin:$FTGLDIR/bin:$GL2PSDIR/bin:$FREEIMAGEDIR/bin:$TBBBIN:$CASROOT/$OS_NAME/bin"
endif

if ( $?LD_LIBRARY_PATH ) then
      setenv LD_LIBRARY_PATH "$TCLHOME/lib:$QTDIR/lib:$FTGLDIR/lib:$GL2PSDIR/lib:$FREEIMAGEDIR/lib:$TBBLIB:$CASROOT/$OS_NAME/lib:$LD_LIBRARY_PATH"
else
      setenv LD_LIBRARY_PATH "$TCLHOME/lib:$QTDIR/lib:$FTGLDIR/lib:$GL2PSDIR/lib:$FREEIMAGEDIR/lib:$TBBLIB:$CASROOT/$OS_NAME/lib"
endif

setenv CSF_MDTVFontDirectory $CASROOT/src/FontMFT
setenv CSF_LANGUAGE us
setenv MMGT_CLEAR 1
setenv CSF_EXCEPTION_PROMPT 1
setenv CSF_SHMessage $CASROOT/src/SHMessage
setenv CSF_MDTVTexturesDirectory $CASROOT/src/Textures
setenv CSF_XSMessage $CASROOT/src/XSMessage
setenv CSF_StandardDefaults $CASROOT/src/StdResource
setenv CSF_PluginDefaults $CASROOT/src/StdResource
setenv CSF_XCAFDefaults $CASROOT/src/StdResource
setenv CSF_StandardLiteDefaults $CASROOT/src/StdResource
setenv CSF_GraphicShr $CASROOT/$OS_NAME/lib/libTKOpenGl.so
setenv CSF_UnitsLexicon $CASROOT/src/UnitsAPI/Lexi_Expr.dat
setenv CSF_UnitsDefinition $CASROOT/src/UnitsAPI/Units.dat
setenv CSF_IGESDefaults $CASROOT/src/XSTEPResource
setenv CSF_STEPDefaults $CASROOT/src/XSTEPResource
setenv CSF_XmlOcafResource $CASROOT/src/XmlOcafResource
setenv CSF_MIGRATION_TYPES $CASROOT/src/StdResource/MigrationSheet.txt

setenv TCLLIBPATH $TCLHOME/lib

setenv TCLLIBPATH $TCLHOME/lib
setenv TCL_LIBRARY $TCLLIBPATH/tcl8.5
setenv TK_LIBRARY $TCLLIBPATH/tk8.5
setenv TCLX_LIBRARY $TCLLIBPATH/tclx8.4
setenv TCLLIBPATH "$TCLHOME/bin $TCLHOME/lib $TCL_LIBRARY $TK_LIBRARY $TCLX_LIBRARY"
