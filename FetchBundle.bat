@echo off
if "%1"=="/help" goto help
if "%1"=="--help" goto help
git clone http://github.com/QbProg/oce-win-bundle
if "%1"=="" goto end
cd oce-win-bundle
git checkout oce-win-bundle-%1
cd ..
goto end
:help
echo "Usage : FetchBundle.bat <version>"
:end