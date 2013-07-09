#!/bin/bash

aScriptPath=${BASH_SOURCE%/*}; if [ -d "${aScriptPath}" ]; then cd "$aScriptPath"; fi; aScriptPath="$PWD";

source "${aScriptPath}/env_cbp.sh" "$1" "$2"

echo 'Hint: use "pload ALL" command to load standard commands'
DRAWEXE
