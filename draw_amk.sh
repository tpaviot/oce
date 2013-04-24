#!/bin/bash

# go to the script directory
aScriptPath=${BASH_SOURCE%/*}; if [ -d "${aScriptPath}" ]; then cd "$aScriptPath"; fi; aScriptPath="$PWD";

source $aScriptPath/env_amk.sh "$1"

echo 'Hint: use "pload ALL" command to load standard commands'
DRAWEXE
