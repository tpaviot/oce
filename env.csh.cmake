#!/bin/csh

setenv CASROOT @OCE_INSTALL_DATA_DIR@

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
setenv CSF_GraphicShr @OCE_DEFAULT_CSF_GraphicShr@
setenv CSF_UnitsLexicon $CASROOT/src/UnitsAPI/Lexi_Expr.dat
setenv CSF_UnitsDefinition $CASROOT/src/UnitsAPI/Units.dat
setenv CSF_IGESDefaults $CASROOT/src/XSTEPResource
setenv CSF_STEPDefaults $CASROOT/src/XSTEPResource
setenv CSF_XmlOcafResource $CASROOT/src/XmlOcafResource
setenv CSF_MIGRATION_TYPES $CASROOT/src/StdResource/MigrationSheet.txt

