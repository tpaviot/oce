srcdir = @srcdir@
FoundationClasses_PKGS = TKernel TKMath TKAdvTools 

FoundationClasses_DIRS = $(FoundationClasses_PKGS)

ModelingData_PKGS = TKG2d TKG3d TKGeomBase TKBRep 

if ENABLE_MODEL
  ModelingData_DIRS = $(ModelingData_PKGS)
else
  ModelingData_DIRS = 
endif

ModelingAlgorithms_PKGS = TKGeomAlgo TKTopAlgo TKPrim TKBO TKHLR TKMesh TKShHealing TKXMesh TKBool TKFillet TKFeat TKOffset 

if ENABLE_MODEL
  ModelingAlgorithms_DIRS = $(ModelingAlgorithms_PKGS)
else
  ModelingAlgorithms_DIRS = 
endif

Visualization_PKGS = TKService TKV2d TKV3d

if HAVE_X11
Visualization_PKGS += TKOpenGl TKMeshVS TKNIS TKVoxel
endif

if ENABLE_VIS
  Visualization_DIRS = $(Visualization_PKGS)
else
  Visualization_DIRS = 
endif

ApplicationFramework_PKGS = TKCDF PTKernel TKLCAF FWOSPlugin TKPShape TKCAF TKBinL TKXmlL TKPLCAF TKTObj TKShapeSchema TKBin TKXml TKPCAF TKBinTObj TKXmlTObj TKStdLSchema TKStdSchema 

if ENABLE_OCAF
  ApplicationFramework_DIRS = $(ApplicationFramework_PKGS)
else
  ApplicationFramework_DIRS = 
endif

DataExchange_PKGS = TKVRML TKXCAF TKSTL TKXSBase TKXCAFSchema TKXmlXCAF TKBinXCAF TKSTEPBase TKIGES TKSTEPAttr TKSTEP209 TKXDEIGES TKSTEP TKXDESTEP 

if ENABLE_DE
  DataExchange_DIRS = $(DataExchange_PKGS)
else
  DataExchange_DIRS = 
endif

Draw_PKGS = TKDraw TKTopTest TKViewerTest TKXSDRAW TKDCAF TKXDEDRAW TKTObjDRAW DRAWEXE 

if ENABLE_DRAW
  Draw_DIRS = $(Draw_PKGS)
else
  Draw_DIRS = 
endif

SUBDIRS = $(FoundationClasses_DIRS) $(ModelingData_DIRS) $(ModelingAlgorithms_DIRS) $(Visualization_DIRS) $(ApplicationFramework_DIRS) $(DataExchange_DIRS) $(Draw_DIRS) 


VPATH = @srcdir@ @top_srcdir@/adm/make: \
@top_srcdir@/adm/make/TKernel: @top_srcdir@/adm/make/TKMath: @top_srcdir@/adm/make/TKAdvTools: \
@top_srcdir@/adm/make/TKG2d: @top_srcdir@/adm/make/TKG3d: @top_srcdir@/adm/make/TKGeomBase: @top_srcdir@/adm/make/TKBRep: \
@top_srcdir@/adm/make/TKGeomAlgo: @top_srcdir@/adm/make/TKTopAlgo: @top_srcdir@/adm/make/TKPrim: @top_srcdir@/adm/make/TKBO: @top_srcdir@/adm/make/TKHLR: @top_srcdir@/adm/make/TKMesh: @top_srcdir@/adm/make/TKShHealing: @top_srcdir@/adm/make/TKXMesh: @top_srcdir@/adm/make/TKBool: @top_srcdir@/adm/make/TKFillet: @top_srcdir@/adm/make/TKFeat: @top_srcdir@/adm/make/TKOffset: \
@top_srcdir@/adm/make/TKService: @top_srcdir@/adm/make/TKV2d: @top_srcdir@/adm/make/TKV3d: @top_srcdir@/adm/make/TKOpenGl: @top_srcdir@/adm/make/TKMeshVS: @top_srcdir@/adm/make/TKNIS: @top_srcdir@/adm/make/TKVoxel: \
@top_srcdir@/adm/make/TKCDF: @top_srcdir@/adm/make/PTKernel: @top_srcdir@/adm/make/TKLCAF: @top_srcdir@/adm/make/FWOSPlugin: @top_srcdir@/adm/make/TKPShape: @top_srcdir@/adm/make/TKCAF: @top_srcdir@/adm/make/TKBinL: @top_srcdir@/adm/make/TKXmlL: @top_srcdir@/adm/make/TKPLCAF: @top_srcdir@/adm/make/TKTObj: @top_srcdir@/adm/make/TKShapeSchema: @top_srcdir@/adm/make/TKBin: @top_srcdir@/adm/make/TKXml: @top_srcdir@/adm/make/TKPCAF: @top_srcdir@/adm/make/TKBinTObj: @top_srcdir@/adm/make/TKXmlTObj: @top_srcdir@/adm/make/TKStdLSchema: @top_srcdir@/adm/make/TKStdSchema: \
@top_srcdir@/adm/make/TKVRML: @top_srcdir@/adm/make/TKXCAF: @top_srcdir@/adm/make/TKSTL: @top_srcdir@/adm/make/TKXSBase: @top_srcdir@/adm/make/TKXCAFSchema: @top_srcdir@/adm/make/TKXmlXCAF: @top_srcdir@/adm/make/TKBinXCAF: @top_srcdir@/adm/make/TKSTEPBase: @top_srcdir@/adm/make/TKIGES: @top_srcdir@/adm/make/TKSTEPAttr: @top_srcdir@/adm/make/TKSTEP209: @top_srcdir@/adm/make/TKXDEIGES: @top_srcdir@/adm/make/TKSTEP: @top_srcdir@/adm/make/TKXDESTEP: \
@top_srcdir@/adm/make/TKDraw: @top_srcdir@/adm/make/TKTopTest: @top_srcdir@/adm/make/TKViewerTest: @top_srcdir@/adm/make/TKXSDRAW: @top_srcdir@/adm/make/TKDCAF: @top_srcdir@/adm/make/TKXDEDRAW: @top_srcdir@/adm/make/TKTObjDRAW: @top_srcdir@/adm/make/DRAWEXE: 

FoundationClasses:
	for d in $(FoundationClasses_PKGS); do \
		cd $$d; $(MAKE) $(AM_MAKEFLAGS) lib$$d.la; cd ..; \
	done

ModelingData:
	for d in $(ModelingData_PKGS); do \
		cd $$d; $(MAKE) $(AM_MAKEFLAGS) lib$$d.la; cd ..; \
	done

ModelingAlgorithms:
	for d in $(ModelingAlgorithms_PKGS); do \
		cd $$d; $(MAKE) $(AM_MAKEFLAGS) lib$$d.la; cd ..; \
	done

Visualization:
	for d in $(Visualization_PKGS); do \
		cd $$d; $(MAKE) $(AM_MAKEFLAGS) lib$$d.la; cd ..; \
	done

ApplicationFramework:
	for d in $(ApplicationFramework_PKGS); do \
		cd $$d; $(MAKE) $(AM_MAKEFLAGS) lib$$d.la; cd ..; \
	done

DataExchange:
	for d in $(DataExchange_PKGS); do \
		cd $$d; $(MAKE) $(AM_MAKEFLAGS) lib$$d.la; cd ..; \
	done

Draw:
	for d in $(Draw_PKGS); do \
		cd $$d; $(MAKE) $(AM_MAKEFLAGS) lib$$d.la; cd ..; \
	done


.PHONY: FoundationClasses ModelingData ModelingAlgorithms Visualization ApplicationFramework DataExchange Draw
