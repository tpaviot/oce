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

VPATH = @srcdir@ /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk: \
/misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKernel: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKMath: \
/misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKG2d: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKG3d: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKGeomBase: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKBRep: \
/misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKGeomAlgo: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKTopAlgo: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKPrim: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKHLR: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKMesh: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKShHealing: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKBO: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXMesh: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKBool: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKFillet: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKFeat: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKOffset: \
/misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKService: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKV3d: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKOpenGl: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKMeshVS: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKNIS: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKVoxel: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKIVtk: \
/misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKCDF: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/PTKernel: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKLCAF: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/FWOSPlugin: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKPShape: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKCAF: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKBinL: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXmlL: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKPLCAF: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKTObj: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKShapeSchema: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKBin: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXml: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKPCAF: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKBinTObj: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXmlTObj: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKStdLSchema: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKStdSchema: \
/misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKVRML: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXCAF: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKSTL: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXSBase: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXCAFSchema: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXmlXCAF: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKBinXCAF: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKSTEPBase: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKIGES: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKSTEPAttr: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKSTEP209: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXDEIGES: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKSTEP: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXDESTEP: \
/misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKDraw: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKTopTest: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKIVtkDraw: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKViewerTest: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXSDRAW: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKDCAF: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKXDEDRAW: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKTObjDRAW: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/TKQADraw: /misc/dn61/LocalWOK/wok_entities/LOC/dev/IR-2015-05-07-IR-2015-05-07-occt-64/adm/lin/amk/DRAWEXE: 

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