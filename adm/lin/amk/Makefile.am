srcdir = @srcdir@

FoundationClasses_PKGS = TKernel TKMath

if ENABLE_FOC
  FoundationClasses_DIRS = $(FoundationClasses_PKGS)
else
  FoundationClasses_DIRS = 
endif

ModelingData_PKGS = TKG2d TKG3d TKGeomBase TKBRep

if ENABLE_DATA
  ModelingData_DIRS = $(ModelingData_PKGS)
else
  ModelingData_DIRS = 
endif

ModelingAlgorithms_PKGS = TKGeomAlgo TKTopAlgo TKPrim TKHLR TKMesh TKShHealing TKBO TKXMesh TKBool TKFillet TKFeat TKOffset

if ENABLE_ALGO
  ModelingAlgorithms_DIRS = $(ModelingAlgorithms_PKGS)
else
  ModelingAlgorithms_DIRS = 
endif

Visualization_PKGS = TKService TKV3d TKOpenGl TKMeshVS TKNIS TKVoxel TKIVtk

if ENABLE_VIS
  Visualization_DIRS = $(Visualization_PKGS)
else
  Visualization_DIRS = 
endif

ApplicationFramework_PKGS = TKCDF PTKernel TKLCAF FWOSPlugin TKPShape TKCAF TKBinL TKXmlL TKPLCAF TKTObj TKShapeSchema TKBin TKXml TKPCAF TKBinTObj TKXmlTObj TKStdLSchema TKStdSchema

if ENABLE_CAF
  ApplicationFramework_DIRS = $(ApplicationFramework_PKGS)
else
  ApplicationFramework_DIRS = 
endif

DataExchange_PKGS = TKVRML TKXCAF TKSTL TKXSBase TKXCAFSchema TKXmlXCAF TKBinXCAF TKSTEPBase TKIGES TKSTEPAttr TKSTEP209 TKXDEIGES TKSTEP TKXDESTEP

if ENABLE_DXE
  DataExchange_DIRS = $(DataExchange_PKGS)
else
  DataExchange_DIRS = 
endif

Draw_PKGS = TKDraw TKTopTest TKIVtkDraw TKViewerTest TKXSDRAW TKDCAF TKXDEDRAW TKTObjDRAW TKQADraw DRAWEXE

if ENABLE_DRAW
  Draw_DIRS = $(Draw_PKGS)
else
  Draw_DIRS = 
endif

SUBDIRS = $(FoundationClasses_DIRS) $(ModelingData_DIRS) $(ModelingAlgorithms_DIRS) $(Visualization_DIRS) $(ApplicationFramework_DIRS) $(DataExchange_DIRS) $(Draw_DIRS)

VPATH = @srcdir@ /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk: \
/misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKernel: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKMath: \
/misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKG2d: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKG3d: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKGeomBase: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKBRep: \
/misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKGeomAlgo: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKTopAlgo: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKPrim: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKHLR: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKMesh: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKShHealing: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKBO: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXMesh: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKBool: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKFillet: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKFeat: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKOffset: \
/misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKService: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKV3d: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKOpenGl: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKMeshVS: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKNIS: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKVoxel: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKIVtk: \
/misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKCDF: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/PTKernel: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKLCAF: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/FWOSPlugin: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKPShape: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKCAF: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKBinL: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXmlL: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKPLCAF: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKTObj: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKShapeSchema: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKBin: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXml: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKPCAF: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKBinTObj: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXmlTObj: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKStdLSchema: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKStdSchema: \
/misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKVRML: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXCAF: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKSTL: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXSBase: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXCAFSchema: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXmlXCAF: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKBinXCAF: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKSTEPBase: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKIGES: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKSTEPAttr: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKSTEP209: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXDEIGES: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKSTEP: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXDESTEP: \
/misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKDraw: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKTopTest: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKIVtkDraw: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKViewerTest: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXSDRAW: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKDCAF: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKXDEDRAW: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKTObjDRAW: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/TKQADraw: /misc/dn63/LocalWOK/wok_entities/LOC/dev/IR-2014-10-10-IR-2014-10-09-occt/adm/lin/amk/DRAWEXE: 

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