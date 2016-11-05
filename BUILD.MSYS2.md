### NOTE: 
The process below should work just as well with Mingw32. 
The difference is that you need to replace x86_64 by i686 in the pacman commands, and open mingw32.exe instead of mingw64.exe for the actually compilation procedure. 
The MSYS2 and mingw32.exe may also be in a folder C:/msys32/ instead of C:/msys64/.

## MSYS2

Install MSYS2 by following the procedure at: http://msys2.github.io/


## QT5 and compilation tools


Open MSYS2 (MSYS2.exe, likely located in `C:/msys64/`), install cmake, git (sys/git), make (sys/make), toolchain (includes gcc):

    pacman -Sy git
    pacman -Sy make
    pacman -Sy cmake
    pacman -Sy ming-w64-x86_64-toolchain

Still in MSYS2, install qt5:

    pacman -Sy mingw-w64-x86_64-qt5


## OCE

#### Download

Still in MSYS2, continue by installing libraries that you will need: freeimage, gl2ps,freetype, libpng, tcl, tk. 
This list may be too extensive (I cannot recall if tcl and tk are actually necessary for compiling OCE).

    pacman -Sy mingw-w64-x86_64-freeimage
    pacman -Sy mingw-w64-x86_64-gl2ps
    pacman -Sy mingw-w64-x86_64-freetype
    pacman -Sy mingw-w64-x86_64-libpng
    
    pacman -Sy mingw-w64-x86_64-tcl
    pacman -Sy mingw-w64-x86_64-tk
    
Note that the libraries freetype and libpng should already be installed with qt5, but I added them just in case.

Now, close down MSYS2.exe and open mingw64.exe instead (likely located in `C:/msys64/`, like MSYS2.exe).

`cd` to the folder `C:/msys64/`, and download OCE using git:

    cd /c/msys64/
    git clone https://github.com/tpaviot/oce.git

#### Cmake

Once OCE is downloaded, follow the "Building" section at https://github.com/tpaviot/oce/wiki/Build-%28MinGW-w64%29 (I do this using `cmake-gui.exe`), taking into account the following:
* You don't need to use the Bundle as all those libraries are already available under MSYS2.
* You must add to `CMAKE_NEED_RESPONSE=YES` to Cmake before launching the Configure. If you correct this after the error has occured (it's a "linking error, argument list too long" error that happens after approx. 40% of the compilation), then compilation will restart from scratch. So, I recommend adding this upfront, and not wait for the error. Otherwise, you'll have wasted some hours.
* When you Configure, use MSYS Makefiles and set `CMAKE_MAKE_PROGRAM` to `C:/msys64/usr/bin/make.exe`. The rest should be straight-forward.
Once Configure is successful, run Generate and finally close cmake-gui.

#### Make

`cd` into your build directory and run `make`.
Remember that it's probably a good idea to use `-j4` (or more, if you have).

    make -j4

As usual, compilation takes forever, but it goes smoothly (only one of the tests failed at the very end for me; but was not important).
