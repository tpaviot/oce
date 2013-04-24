srcdir = @srcdir@

FoundationClasses_PKGS = TKernel TKMath TKAdvTools

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

ModelingAlgorithms_PKGS = TKGeomAlgo TKTopAlgo TKPrim TKBO TKHLR TKMesh TKShHealing TKXMesh TKBool TKFillet TKFeat TKOffset

if ENABLE_ALGO
  ModelingAlgorithms_DIRS = $(ModelingAlgorithms_PKGS)
else
  ModelingAlgorithms_DIRS = 
endif

Visualization_PKGS = TKService TKV3d TKOpenGl TKMeshVS TKNIS TKVoxel

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

Draw_PKGS = TKDraw TKTopTest TKViewerTest TKXSDRAW TKDCAF TKXDEDRAW TKTObjDRAW TKQADraw DRAWEXE

if ENABLE_DRAW
  Draw_DIRS = $(Draw_PKGS)
else
  Draw_DIRS = 
endif

SUBDIRS = $(FoundationClasses_DIRS) $(ModelingData_DIRS) $(ModelingAlgorithms_DIRS) $(Visualization_DIRS) $(ApplicationFramework_DIRS) $(DataExchange_DIRS) $(Draw_DIRS)

VPATH = @srcdir@ /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk: \
/misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKernel: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKMath: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKAdvTools: \
/misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKG2d: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKG3d: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKGeomBase: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKBRep: \
/misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKGeomAlgo: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKTopAlgo: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKPrim: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKBO: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKHLR: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKMesh: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKShHealing: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXMesh: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKBool: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKFillet: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKFeat: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKOffset: \
/misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKService: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKV3d: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKOpenGl: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKMeshVS: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKNIS: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKVoxel: \
/misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKCDF: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/PTKernel: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKLCAF: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/FWOSPlugin: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKPShape: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKCAF: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKBinL: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXmlL: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKPLCAF: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKTObj: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKShapeSchema: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKBin: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXml: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKPCAF: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKBinTObj: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXmlTObj: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKStdLSchema: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKStdSchema: \
/misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKVRML: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXCAF: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKSTL: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXSBase: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXCAFSchema: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXmlXCAF: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKBinXCAF: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKSTEPBase: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKIGES: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKSTEPAttr: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKSTEP209: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXDEIGES: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKSTEP: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXDESTEP: \
/misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKDraw: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKTopTest: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKViewerTest: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXSDRAW: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKDCAF: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKXDEDRAW: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKTObjDRAW: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/TKQADraw: /misc/dn47/KAS/builds/inv/LocalWOK/wok_entities/LOC/dev/inv-IR-2013-04-18-master-OCCT/adm/lin/amk/DRAWEXE: 

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