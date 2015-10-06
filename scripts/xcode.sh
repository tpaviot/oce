#!/bin/bash

export TARGET="xcd"

source ./env.sh "$TARGET" "$1"

export CSF_OPT_LIB64="$CSF_OPT_LIB64:/usr/X11/lib"
export CSF_OPT_LIB64D="$CSF_OPT_LIB64:/usr/X11/lib"

open -a Xcode ./adm/mac/xcd/OCCT.xcworkspace
