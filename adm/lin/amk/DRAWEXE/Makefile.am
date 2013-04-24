# Makefile.am for executable DRAWEXE
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/src/DRAWEXE

INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_TclLibs_INCLUDES) $(CSF_TclTkLibs_INCLUDES) $(CSF_gdi32_INCLUDES) $(CSF_advapi32_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_TBB_INCLUDES) $(CSF_objc_INCLUDES) $(CSF_Appkit_INCLUDES) $(CSF_IOKit_INCLUDES) $(CSF_SOCKETLibs_INCLUDES) $(CSF_FPELibs_INCLUDES) $(CSF_ThreadLibs_INCLUDES) $(CSF_kernel32_INCLUDES) $(CSF_OpenGlLibs_INCLUDES) $(CSF_XwLibs_INCLUDES) $(CSF_dpsLibs_INCLUDES) $(CSF_XmuLibs_INCLUDES) $(CSF_FreeImagePlus_INCLUDES) $(CSF_FREETYPE_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/src/DRAWEXE

 
bin_PROGRAMS= DRAWEXE
 DRAWEXE_SOURCES = @top_srcdir@/src/DRAWEXE/DRAWEXE.cxx 
 DRAWEXE_LDADD =  \
../TKDraw/libTKDraw.la \
../TKMesh/libTKMesh.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKHLR/libTKHLR.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKGeomBase/libTKGeomBase.la \
../TKG2d/libTKG2d.la \
../TKBRep/libTKBRep.la \
../TKMath/libTKMath.la \
../TKG3d/libTKG3d.la \
../TKernel/libTKernel.la \
../TKService/libTKService.la $(STLPort_LIB) $(CSF_TclLibs_LIB) $(CSF_TclTkLibs_LIB) $(CSF_gdi32_LIB) $(CSF_advapi32_LIB) $(CSF_user32_LIB) $(CSF_TBB_LIB) $(CSF_objc_LIB) $(CSF_Appkit_LIB) $(CSF_IOKit_LIB) $(CSF_SOCKETLibs_LIB) $(CSF_FPELibs_LIB) $(CSF_ThreadLibs_LIB) $(CSF_kernel32_LIB) $(CSF_OpenGlLibs_LIB) $(CSF_XwLibs_LIB) $(CSF_dpsLibs_LIB) $(CSF_XmuLibs_LIB) $(CSF_FreeImagePlus_LIB) $(CSF_FREETYPE_LIB)  
