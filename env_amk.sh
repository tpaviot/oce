#!/bin/bash

# go to the script directory
aScriptPath=${BASH_SOURCE%/*}; if [ -d "${aScriptPath}" ]; then cd "$aScriptPath"; fi; aScriptPath="$PWD";

export CASROOT="$aScriptPath"

# Reset values
export CASDEB=""
export HAVE_TBB="false";
export HAVE_FREEIMAGE="false";
export HAVE_GL2PS="false";
export MACOSX_USE_GLX="false";
export CSF_OPT_INC=""
export CSF_OPT_LIB32=""
export CSF_OPT_LIB64=""
export CSF_OPT_BIN32=""
export CSF_OPT_BIN64=""

# ----- Set local settings -----
if [ -e "${aScriptPath}/custom_amk.sh" ]; then source "${aScriptPath}/custom_amk.sh"; fi

# Read script arguments
shopt -s nocasematch
if [[ "$1" == "debug" ]]; then export CASDEB="d"; fi
if [[ "$1" == "d" ]]; then export CASDEB="d"; fi
shopt -u nocasematch

export CSF_OPT_INC="${CSF_OPT_INC}:."
export CSF_OPT_LIB32="${CSF_OPT_LIB32}:."
export CSF_OPT_LIB64="${CSF_OPT_LIB64}:"
export CSF_OPT_LIB32D=""
export CSF_OPT_LIB64D=""

# ----- Setup Environment Variables -----
anArch=`uname -m`
if [ "$anArch" != "x86_64" ] && [ "$anArch" != "ia64" ]; then
  export ARCH="32";
else
  export ARCH="64";
fi

aSystem=`uname -s`
if [ "$aSystem" == "Darwin" ]; then
  export WOKSTATION="mac";
  export ARCH="64";
else
  export WOKSTATION="lin";
fi

export CASBIN=""

export CSF_OPT_CMPL=""

# Optiona 3rd-parties should be enabled by HAVE macros
if [ "$HAVE_TBB" == "true" ]; then
  export CSF_OPT_CMPL="${CSF_OPT_CMPL} -DHAVE_TBB"
fi
if [ "$HAVE_FREEIMAGE" == "true" ]; then
  export CSF_OPT_CMPL="${CSF_OPT_CMPL} -DHAVE_FREEIMAGE"
fi
if [ "$HAVE_GL2PS" == "true" ]; then
  export CSF_OPT_CMPL="${CSF_OPT_CMPL} -DHAVE_GL2PS"
fi

# Option to compile OCCT with X11 libs on Mac OS X
if [ "$MACOSX_USE_GLX" == "true" ]; then
  export CSF_OPT_CMPL="${CSF_OPT_CMPL} -DMACOSX_USE_GLX"
fi

# To split string into array
aDelimBack=$IFS
IFS=":"

# 3rd-parties additional include paths
set -- "$CSF_OPT_INC"
declare -a aPartiesIncs=($*)
for anItem in ${aPartiesIncs[*]}
do
  export CSF_OPT_CMPL="${CSF_OPT_CMPL} -I${anItem}";
done

# Append 3rd-parties to LD_LIBRARY_PATH
if [ "$ARCH" == "32" ]; then
  set -- "$CSF_OPT_LIB32"
  declare -a aPartiesLibs=($*)
else
  set -- "$CSF_OPT_LIB64"
  declare -a aPartiesLibs=($*)
fi

# Turn back value
IFS=$aDelimBack

OPT_LINKER_OPTIONS=""
for anItem in ${aPartiesLibs[*]}
do
  if [ "${LD_LIBRARY_PATH}" == "" ]; then
    export LD_LIBRARY_PATH="${anItem}"
  else
    export LD_LIBRARY_PATH="${anItem}:${LD_LIBRARY_PATH}"
  fi
  OPT_LINKER_OPTIONS="${OPT_LINKER_OPTIONS} -L${anItem}"
done

if [ "$ARCH" == "64" ]; then
  export CSF_OPT_LNK64="$OPT_LINKER_OPTIONS"
  export CSF_OPT_LNK64D="$OPT_LINKER_OPTIONS"
else
  export CSF_OPT_LNK32="$OPT_LINKER_OPTIONS"
  export CSF_OPT_LNK32D="$OPT_LINKER_OPTIONS"
fi

export PATH="${CASROOT}/${CASBIN}bin${CASDEB}:${PATH}"
export LD_LIBRARY_PATH="${CASROOT}/${CASBIN}lib${CASDEB}:${LD_LIBRARY_PATH}"
if [ "$WOKSTATION" == "mac" ]; then
  export DYLD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${DYLD_LIBRARY_PATH}"
fi

# Set envoronment variables used by OCCT
export CSF_LANGUAGE="us"
export MMGT_CLEAR="1"
export CSF_EXCEPTION_PROMPT="1"
export CSF_SHMessage="${CASROOT}/src/SHMessage"
export CSF_MDTVTexturesDirectory="${CASROOT}/src/Textures"
export CSF_XSMessage="${CASROOT}/src/XSMessage"
export CSF_TObjMessage="${CASROOT}/src/TObj"
export CSF_StandardDefaults="${CASROOT}/src/StdResource"
export CSF_PluginDefaults="${CASROOT}/src/StdResource"
export CSF_XCAFDefaults="${CASROOT}/src/StdResource"
export CSF_TObjDefaults="${CASROOT}/src/StdResource"
export CSF_StandardLiteDefaults="${CASROOT}/src/StdResource"
if [ "$WOKSTATION" == "mac" ]; then
  export CSF_GraphicShr="libTKOpenGl.dylib"
else
  export CSF_GraphicShr="libTKOpenGl.so"
fi
export CSF_UnitsLexicon="${CASROOT}/src/UnitsAPI/Lexi_Expr.dat"
export CSF_UnitsDefinition="${CASROOT}/src/UnitsAPI/Units.dat"
export CSF_IGESDefaults="${CASROOT}/src/XSTEPResource"
export CSF_STEPDefaults="${CASROOT}/src/XSTEPResource"
export CSF_XmlOcafResource="${CASROOT}/src/XmlOcafResource"
export CSF_MIGRATION_TYPES="${CASROOT}/src/StdResource/MigrationSheet.txt"

# Draw Harness special stuff
if [ -e "${CASROOT}/src/DrawResources" ]; then
  export DRAWHOME="${CASROOT}/src/DrawResources"
  export CSF_DrawPluginDefaults="${DRAWHOME}"
fi
if [ -e "${aScriptPath}/src/DrawResourcesProducts" ]; then
  export CSF_DrawPluginProductsDefaults="${aScriptPath}/src/DrawResourcesProducts"
fi
