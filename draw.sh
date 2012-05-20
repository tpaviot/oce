#!/bin/bash

# go to the script directory
aScriptPath=${BASH_SOURCE%/*}; if [ -d "${aScriptPath}" ]; then cd "$aScriptPath"; fi; aScriptPath="$PWD";

source $aScriptPath/env.sh

echo 'Hint: use "pload ALL" command to load standard commands'
DRAWEXE
