#!/bin/bash

export TARGET="cbp"

source ./env_cbp.sh "$TARGET" "$1"

export CSF_OPT_LIB64="$CSF_OPT_LIB64:/usr/X11/lib"
export CSF_OPT_LIB64D="$CSF_OPT_LIB64:/usr/X11/lib"

/Applications/CodeBlocks.app/Contents/MacOS/CodeBlocks ./adm/mac/cbp/OCCT.workspace
