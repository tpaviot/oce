### Version 0.18.2 - August 2017

This version is binary compatible with OCE 0.18.x

* Fix issue of raise exception when sweep along with cornered line

* osx ifx: Visualization, Font_FontMgr - do not look for fonts.dir on OS X

* fix external linkage error in BRepBuilderAPI_Copy

Users who contributed to this release:
  @heropan (yingxiong_pan@sina.cn), Martin Müllenhaupt, Thomas Paviot

### Version 0.18.1 - May 2017

This version is binary compatible with OCE 0.18

* Added missing ErrorStatus function in BRepLib_CheckCurveOnSurface

* Install Shaders directory to resource folder

* Fix normals of generated VTK polydata

* prevent DRAWEXE from being added to OCE_LIBRARIES (issue #660)

* Fix warnings with VTK 7.1

* Fix missin include and other minor header issues

* Fix clockget_time detection on osx

Users who contributed to this release:
  Luis Manuel Alvarez Tapia, @cfcohen, Florian Chevassu, Thomas Paviot,
  Janus Weil, Simon Wells

### Version 0.18 - January 2017

This version is not binary compatible with OCE 0.17.x, OCE_ABI_SOVERSION
was incremented.

* Upgraded to OCCT 6.9.1
  https://www.opencascade.com/sites/default/files/documents/Release_Notes_6.9.1.pdf
* Support VTK OpenGL2 backend

* 0027385: assertion in static initializer in a Windows GUI application

* Removed outdated OpenCL option

*  Fix null pointer access in BRepMesh_EdgeTessellator

Users who contributed to this release:
  blobfish, Florian Chevassu, Julien Finet, Thomas Paviot

### Version 0.18 - January 2017

This version is not binary compatible with OCE 0.17.x, OCE_ABI_SOVERSION
was incremented.

* Upgraded to OCCT 6.9.1
  http://www.opencascade.com/pub/doc/Release_Notes_6.7.0.pdf
* Support VTK OpenGL2 backend

* 0027385: assertion in static initializer in a Windows GUI application

* Removed outdated OpenCL option

*  Fix null pointer access in BRepMesh_EdgeTessellator

Users who contributed to this release:
  blobfish, Florian Chevassu, Julien Finet, Thomas Paviot

### Version 0.17.2 - May 2016

This version is binary compatible with 0CE 0.17 and OCE 0.17.1

* Fix VTK6.2 support

* Fixed typo in BRepGProp_Sinert wich leads to wrong inertia matrix
computationOCE_USE_STATIC_MSVC_RUNTIME advanced option to use static version of the

* Workaround clang optimizations for null references

* IntCurveSurface_Polygon::Init() improvement

* Check distance between points before line creation

* Replace obsolete vtkFloatingPointType typedef/define with double

* Fixed crash on OS X due to clang compiler errors

Users who contributed to this release:
  Jacob Abel, Julien Finet, Thomas Paviot, Martin Siggel

### Version 0.17.1 - January 2016

This version is binary compatible with 0CE 0.17.

* Mingw64 (5.2.0) and Mingw32 (4.8.1, 4.9.3) fixes

* OCE_USE_STATIC_MSVC_RUNTIME advanced option to use static version of the
MSVC run-time library

* Revert change in HLR inverted flag

* Fix nmake build

* Patch from setting correct tolerance.

* Replace gp_Ax1 reference with direct value. Fixes #559

* VS2015 fix

* Fix for static building on MSVC

* New oce-win-bundle handling

* ppc64le fix

* Build OCE and run tests on appveyor.com service.

Users who contributed to this release:
  Jacob Abel, Ali Kämäräinen, Denis Barbier, Benjamin Bilher,
  Rajeev Jain, Sergio L. Pascual, Thomas Paviot, QbProg,
  Jeremy Wright

### Version 0.17 - March 2015

This version is not binary compatible with OCE 0.16, OCE_ABI_SOVERSION
was incremented.

* Upgraded to OCCT 6.8.0

* Build system changes
  - Remove OCE_DISABLE_BSPLINE_MESHER option, OCCT improved meshing
    in recent releases.

Users who contributed to this release:
  Denis Barbier, Mario Lang, blobfish, QbProg

### Version 0.16.1 - November 2014

This version is binary compatible with 0CE 0.16.

* cppcheck fixes (memory leaks and parse errors)

* Fix LDOMBasicString assignment operator

* Mingw fixes (OpenGl compilation)

* Fix build failures with Mesa 10.3.1

Users who contributed to this release:
  Denis Barbier, Jacob Abel, Benjamin Bihler

### Version 0.16 - July 2014

This version is not binary compatible with OCE 0.15, OCE_ABI_SOVERSION
was incremented.

* Upgraded to OCCT 6.7.1
  http://www.opencascade.com/pub/doc/Release_Notes_6.7.1.pdf

* Fix a numerical bug in ApproxAFunc2Var due to compiler optimization.

* Speed improvements in BOPTools_AlgoTools2D.

* Many bug and warning fixes detected by static analysis and compilers.

* Force 8 byte alignment in NCollection_IncAllocator to fix bus errors
  reported on RISC architectures.

* Build system improvements and additions
  - Readd OCE_DISABLE_TKSERVICE_FONT option, a solution has been found
    to build TKService without freetype.
  - Fix Standard_Construction_Error exception in BOP
  - Fix RPATH issues reported on openSUSE
  - Fix gl2ps libraries installation
  - Build improvements and fixes with Mingw
  - Fix compatibility with CMake 3.0
  - Enable support for OpenCL
  - New OCE_COPY_HEADERS_BUILD option to copy header files when building,
    to get rid of the long list of include directories on command line

Users who contributed to this release:
  Denis Barbier, Jacob Abel, David Sankel, Jerome Robert, Johannes Obermayr,
  Conrad Poelman, Peter Lama, He Yuqi, Thomas Paviot

### Version 0.15 - February 2014

This version is not binary compatible with OCE 0.14.1, OCE_ABI_SOVERSION
was incremented.

* Upgraded to OCCT 6.7.0
  http://www.opencascade.com/pub/doc/Release_Notes_6.7.0.pdf

* Relicensed to LGPL 2.1.

* Many bug and warning fixes detected by static analysis and compilers.

* Add support for OCCT tests.

* Build OCE and run tests on travis-ci.org service.

* Build system improvements and additions
  - Added multithreaded build option for MSVC.
  - Build improvements and fixes with MSVC and Mingw.
  - Fix build failures with Borland compiler.
  - Fix build failures with Mesa 10.
  - Various CMake improvements when compiling with bundle.
  - Removed OCE_DISABLE_TKSERVICE_FONT option, it is no more possible
    to build TKService without freetype.

Users who contributed to this release:
  Denis Barbier, Thomas Paviot, QbProg, Fotios Sioutis, Johannes Obermayr,
  Jacob Abel, Benjamin Bihler

### Version 0.14.1 - January 2014

This version is binary compatible with 0CE 0.14.

* Fix Debug build on MSVC.

Users who contributed to this release:
  Denis Barbier


### Version 0.14 - December 2013

This version is binary compatible with 0CE 0.13.

* mingw64 port.

* Intel Compiler support.

* HPUX 11iv1 and 11iv3 ia64 and parisc architecture port.

* Apple OSX 10.9 Maverick support.

* Reduced compiler warnings on gcc, clang, icc and MinGW.

* Fix writing of XML CAF documents

* additional fixes to the CMake build system
  - Removed lib path string from OCE_DEFAULT_CSF_GraphicShr variable for
  MinGw.
  - Add custom build step to set up integrated build include directory.
  - Made OCE_BUILD_TYPE initialize to CMAKE_BUILD_TYPE if available.
  - Break header file installation into individual install commands.
  - CMake RPATH support for TKernel.
  - Take CSF_GraphicShr environment variable into account.
  - Remove Xmu dependency.
  - Fix libTKOpenGL versioning name on Apple.

Users who contributed to this release:
  Jacob Abel, Greg Allen, Denis Barbier, Benjamin Bihler, Johannes Obermayr,
  Thomas Paviot, David Sankel, Fotios Sioutis, Daniel Somer


### Version 0.13 - September 2013

This version is not binary compatible with OCE 0.12, OCE_ABI_SOVERSION
was incremented.

* Upgraded to OCCT 6.6.0
  http://www.opencascade.com/pub/doc/Release_Notes_6.6.0.pdf

* Fix handling of paths containing non-ASCII characters in DRAWEXE.

* Define Standard_Boolean as a bool, and no more as a Standard_Integer
  as is done in OCCT.

* Make myFMMgr member of Standard_MMgrFactory class private, it does not
  have to be public.

* Build system improvements and additions
  - Fix build failures on Hurd, mingw-w64 and Mac OSX 10.5.
  - Fix build with gcc when using -std=c++11 flag.
  - Fix build failures with Borland compiler.
  - Move duplicate header files from inc/ into src/.
  - Build QADraw module only if OCE_TESTING is set.
  - Improve bundle usage to allow running tests.
  - Reorganize top-level source directory: move *.bat and *.sh scripts
    into a scripts/ directory, and move CMake files into adm/cmake/config/.
  - Add a CMake option to allow building TKService without font support,
    if visualization is not needed.
  - Let CMake GUI display OCE_BUILD_TYPE as a combo box.

* Several warning fixes detected by static analysis and compilers

Users who contributed to this release:
  Thomas Paviot, QbProg, Jake, Fotios Sioutis, Denis Barbier, David Sankel


### Version 0.12 - March 2013

This version is not binary compatible with OCE 0.11.x, OCE_ABI_SOVERSION
was incremented.

* Build system improvements and additions
  - oce-win-bundle is improved to allow integration into superprojects.
    Structure of the bundle has also been modified, all libraries are now
    put into the bin directory.
  - installation paths are written into a separate file so that only few
    files have to be recompiled when changing installation path.

* Backport upstream changes to provide a native Cocoa interface on OSX.

* Backport geometry bugfixes from upstream.

* When face normal cannot be computed during meshing, a loop was performed
  until machine precision is reached.  Limit the number of iterations to
  avoid very slow meshing on such surfaces.

* Make boolean operations faster.

* On non-Windows, FreeImagePlus library is unused, only FreeImage functions
  are called.  Link against this library to avoid errors on Fedora.

Users who contributed to this release:
  Fotis Sioutis, QbProg, Denis Barbier, Jerome Robert, Conrad Poelman,
  Thomas Paviot, rainman110, Richard Shaw


### Version 0.11 - December 2012

This version is not binary compatible with OCE 0.10.x, OCE_ABI_SOVERSION
was incremented.

* Upgraded to OCCT 6.5.4
  http://www.opencascade.com/pub/doc/Release_Notes_6.5.4.pdf

* Build system improvements and additions
  - added support for Visual C++ 2012
  - mingw32 compatibility fixes
  - mingw64 support for Kernel and Modeling
  - fixes for static build configuration
  - support for GCC precompiled headers
  - wrapped new module TKQADraw
  - various RPATH fixes for unix systems

* Many bug and warning fixes detected by static analysis and compilers

Users who contributed to this release: Denis Barbier, Johannes Obermayr,
Massimo Del Fedele, QbProg, Thomas Paviot,salajkav-dlubalcz


### Version 0.10 - June 2012

This version is not binary compatible with OCE 0.9.x, OCE_ABI_SOVERSION 
was incremented.

* Upgraded to OCCT 6.5.3 
  http://www.opencascade.com/pub/doc/Release_Notes_6.5.3.pdf

* Improved compiler support for the new OCCT version
  - Fix build failures on Alpha
  - bcc v5.6.4 port (builder 6)
  - mingw64 linux build
  - OSX OpenGL Support
  - gcc 4.7

* Many cppcheck, clang and msvc warning fixes  

* Build system and packaging fixes and improvements

* Bugfix: Fix memory leak in OSD_FontMgr.cxx

* Bugfix: Points swapped in BRepExtrema_DistanceSS

Users who contributed to this release:
  Denis Barbier, Fotios Sioutis, Jerome Robert,
  QbProg, Thomas Paviot.


### Version 0.9.1 - January 2012

This is a bugfix release.

* Fixed regressions in the TKOpenGl toolkit.


### Version 0.9.0 - January 2012

* Upgraded to OCCT 6.5.2
  http://www.opencascade.com/pub/doc/Release_Notes_6.5.2.pdf

* Added support for CMake uninstall feature. make uninstall is now possible

* Many cppcheck QA and gcc warning fixes

* bugfixes: Standard_Error is not raised in Poly_CoherentTriangulation.cxx,
  out of bound error in XCAFPrs/XCAFPrs_AISObject.cxx, many else clause
  applies to the wrong statement, std::streamsize replacement for int in
  std::streambuf::xsputn.

* Added support for Standard_Time in OCE to make OCE changes portable to 
  WOK system.

* Many fixes and CMake support for embarcadero compilers (v6.20 and up)

* Let a mingw64 TKernel works in Wine

* Compile and run tests only if the needed components have been compiled

* Fixed TBB support in debug/msvc

* Geom_BSplineCurve.cxx: Add explicit exception message in case of error

* Other compilation and build fixes

Users who contributed to this release:
  Denis Barbier, Davy Wouters, Fotios Sioutis, Jerome Robert,
  Massimo Del Fedele, Simon Floery, Thomas Paviot.


### Version 0.8.0 - December 2011

* Added more unit tests 

* Help building on systems without cmake, in particular with WOK

* Removed deprecated bcc32 project files

* bcc32 and bcc xe edition support

* Fixes to allow building with cmake 2.6 - cmake 2.8 is stricly required only
  when running unit tests

* Added Standard_StdAllocator class + UnitTest

* Added an option to disable the bspline mesher, and reverts to OFF 
  (not disabled) the default behavoir

* Correctly set DEB,_DEBUG and NDEBUG defines. Enabling DEB (additional 
  debug code) is now an option

* Macro fixes in Draw package

* Solves a copy-paste bug in TDataXtd_PatternStd (bug #195)

* Add support installing libraries into lib64

* Ensure that GLU is found when checking for OpenGL

* Fixed opengl (ftgl) font issue

* Strip system paths from RPATH.

* Add few missing resource files (UnitsAPI support)

Users who contributed to this release:
  Denis Barbier,Fotios Sioutis,Thomas Paviot,QbProg


### Version 0.7.0 - October 2011

* Updated build and install instructions

* Allow changing default values of MMGT_* variables  
  The following macros can be set when compiling to override
  default settings:
    MMGT_OPT_DEFAULT  
    MMGT_CLEAR_DEFAULT  
    MMGT_MMAP_DEFAULT  
    MMGT_CELLSIZE_DEFAULT  
    MMGT_NBPAGES_DEFAULT  
    MMGT_THRESHOLD_DEFAULT  
    MMGT_REENTRANT_DEFAULT  

* Allow building unversioned libraries : 
  Third-party applications which embed OCE may find convenient
  to drop version numbers from libraries.  
  With this commit, one can call cmake -DOCE_NO_LIBRARY_VERSION=ON.  
  This is based on a similar feature found in VTK.

* Disabled the BSpline mesher, since it generates over-refined meshes. 
  The generic one will be used instead.

* Removed src/FontMFT/*.mft files

* More tests added : Step import and mesher

* Win32 specific changes :
  - Install Debug and Release libraries into the same directory
  - Automatically define WNT depending on compiler predefined macros
  - Auto-install TBB dlls
  - Export the target informations in Win32. This allows to find OCE from 
    cmake projects even win 32.
  - Fixed mingw64 compilation

* Some additional GCC warning removals

* Other minor fixes

Users who contributed to this release:
  Denis Barbier,He Yuqi,Jerome Robert,QbProg,Thomas Paviot

### Version 0.6.0 - September 2011

 *   Cmake 2.8 is explicitly required to build OCE.

 *   Removed many X11 dependencies. Now it is possible to build a large part of
     OCE (with the exception of visualisation) without depending on X11 (using
     OCE_DISABLE_X11 option).

 *   Cmake support : Cmake users will be able to correctly find OCE using
     FIND_PACKAGE(OCE). Several examples are added to show how to use it in
     end-user programs. It is now possible to detect/request single toolkits.

 *   Packaging : change installation paths; we do no more install files at the
     same location as OpenCascade, but adopted more standard paths.

 *   Tests : integrated gtest 1.6.0 and added other unit tests, which helped in
     fixing some bugs. Added MSVC support to the testsuite.

 *   Win32/MSVC improvements:
     + Enabled configuration files in Win32 platforms
     + Plugins and TKOpenGL are correctly found in debug builds
     + TKOpenGL works when building static libraries

 *   Modify tcl scripts to not require $env(CASROOT).

 *   Many small changes, bug fixes and warning removals.
     + Improvements to OSD_Process::SystemDate()
     + TKernel : add dependency against -ldl.
     + Bugfix : Work around a cmake bug that prevented building Win64+MSVC+static libs
     + Bugfix : add missing include in BRepBlend_BlendTool.lxx.
     + Bugfix : fix mismatch new/delete in Standard_Failure.cxx
     + Fixed compiler warnings in OpenGl_TextureBox.cxx
     + Whitespace cleanup
     + In module TKOpenGL, fixed the two remaining GCC warnings of the form :
       "comparison between ‘enum texStatus’ and ‘enum texDataStatus’"
     + Added missing include in BRepBlend_BlendTool.lxx
     + Fix capitalization of include file
     + pass NULL for timezone pointer to gettimeofday()
     + eliminate bad cast by copying to local variable
     + use localtime_r if available
     + Do not redefine memmove as an alias for memcpy
     + Workaround GCC (< 4.3) bugs in gp_Mat, gp_XYZ, gp_Mat2d and gp_XY.
     + Fix HashCode, it could segault when MMGT_OPT is not set to 1.

Users who contributed to this release:
  Denis Barbier, Thomas Paviot, Hugues Delorme, QbProg,
  Matthew Dempsky, Massimo Del Fedele

### Version 0.5.0 - August 2011

This released integrated OCCT 6.5.1, continued on the warning cleanup, and
fixed some bugs. This a ABI breaking release, due to the warning fixes
and the new OCCT version.
Programs compiled with OCCT 6.5.1 will compile untouched with OCE 0.5.0

 *   OCCT 6.5.1 : aligned to the lasted OpenCascade Tecnology release,
     while mantaining all the patches previously applyed.

 *   Breaking changes : to allow the removal of many compiler warnings, we
     did some breaking changes in some of the headers, mainly related to the
     type of private class fields. Existing code will still compile untouched.

 *   Warning removal and code cleanup : we removed many other warnings and
     cleaned up some functions. Some cppcheck warnings were also fixed.

 *   Added TBB support in memory allocation : OCE builds compiled with the
     TBB option on will benefit from it's multithreaded memory allocator.

 *   Bug fixes : some bugs were spotted during the cleanup process, and
     were fixed and reported. Other bugs were noticed from the forum and
     fixed.

 *   Installing version information : Programs using CMake will allow to find
     OCE with a specific version string.

 *   Program using OCE won't require to compile with -DHAVE_OCE_CONFIG anymore.

Users who contributed to this release:
     Thomas Paviot, Denis Barbier, QbProg, Hugues Delorme, Muellni,
     Philippe Carret

### Version 0.4.0 - July 2011

This release focused on improving code quality and the cmake build system.

 *   CPack support : including DEB,RPM and MacOsX package generation

 *   CTest support : initial infrastructure to develop unit tests using
     googletest and CTest. Actually working in Linux and MacOsX.

 *   CDash support : http://my.cdash.org/index.php?project=OCE to see the
     status of the tests on various platforms

 *   Fixed many compiler warnings: this allows to have a cleaner compilation
     and helped in finding some bugs. Probably many of the annoying MSVC CRT
     debug error windows are also gone.
     Some warnings may still be present, and will be fixed in successive versions.

 *   Added NMake support
 *   Drastically reduced MSVC compilation time, using precompiled headers

 *   Added version information in Win32 DLLs: this information will be useful
     for installers and packaging systems.

 *   Let OCEConfig.cmake use relative paths in order to allow moving
     install tree (related to Linux and MacOsX)

Users who contributed to this release:
     Thomas Paviot , Mark Pictor, Muellni,Denis Barbier, Hugh Sorby, QbProg

### Version 0.3.0 - June 2011

  * Make CMake work with MSVC.  This generator is special,
    it generates both Debug and Release configurations.
    [QbProg]

  * Add an option to enable maximum warning levels
    [QbProg]

  * Improve handling of CMake options
    [Hugh Sorby]

  * Fix build failures with g++ 4.6
    [Denis Barbier]

  * Clean up CMakeLists.txt, remove unused macros.
    [Mark Pictor]

  * Create two config files, one is used during compilation,
    another one is used when linking against OCE.  The latter
    contains fewer macros, and they are prefixed by OCE_ to
    prevent name clashes.
    [Mark Pictor]

  * Start fixing compiler warnings.
    [QbProg, Thomas Paviot]

  * Create a bundle for MSVC
    [QbProg]

  * Fix cross compilation with Mingw.  We were not able to
    build visualization stuff previously.
    [Muellni]

  * Install an OCEConfig.cmake file so that programs can use
    FIND_PACKAGE(OCE) to set variables to link against OCE.
    [Muellni]

  * Undefine Convex before it is used by OCE as a method or
    function, this may be a macro defined by X11.h
    [Thomas Paviot]

  * Remove -DLIN from compiler flags.  It still works on Linux,
    and this causes crashes on Mac OSX.
    [Thomas Paviot]

  * Delete inc/TopOpeBRep_tools.hxx, this file is unused, and it
    includes TopOpeBRepDS_tools.hxx which does not exist.
    [Denis Barbier]

  * Remove Autotools files for Unix and MSVC, CMake build system
    works fine on these platforms.  We keep Borland project
    files for now, this IDE is not supported by CMake.
    [Thomas Paviot]

### Version 0.2.0 - May 2011

  * Add CMake build files, based on the opencascade-cmake project
      http://code.google.com/p/opencascade-cmake/
    Works fine on Linux, needs more testing on Mac OSX and Windows.
    [Hugh Sorby, Thomas Paviot, Mark Pictor, Denis Barbier, QbProg]

  * Let CMake generate env.sh and env.csh scripts with
    accurate variables.
    [Denis Barbier]

  * Fix lines in Visual3d_Layer class.
    [Fotis Sioutis]

  * Changes required to build OCE on some non-x86 architectures
    on Unix.
    [Denis Barbier]

  * Add OpenMP support, users can choose between OpenMP and TBB.
    [Denis Barbier]

  * When building with CMake, paths are set at compile time so that
    everything works without having to set environment variables.
    [Denis Barbier]

### Version 0.1.0 - April 2011

  * Import OCC 6.5.0
    [Thomas Paviot]

  * Add instructions for cloning/pulling with git and for
    building from sources.
    [Thomas Paviot]

  * Replace Abs(foo < bar) by Abs(foo) < bar.
    These bugs have been reported on the opencascade forum:
      http://www.opencascade.org/org/forum/thread_20187/
      BugID=OCC22324
    [Fotis Sioutis]

  * Rename guards for MSVC specific pragmas from WNT to _MSC_VER.
    These are mainly #pragma warnings or MSVCRT specific things.
    [QbProg]

  * Fix build failures with Borland compiler.
    [Fotis Sioutis]

  * Add project files for Borland Developer Studio 10.
    [Fotis Sioutis]

  * Fix build failures with Mingw.
    [Jérôme Robert]

  * Add new Automake conditionals: HAVE_X11 and IS_WINDOWS.
    When X11 is not found, do not compile sources from Xw and
    ImageUtility. On Windows, compile files from ros/src/WNT.
    [Denis Barbier]

  * Improve Autools usage.
    [Denis Barbier]

  * Assume /usr when --with-gl2ps/--with-freeimage configure
    options are specified without arguments.
    Submitted upstream:
      http://www.opencascade.org/org/forum/thread_20231/
      BugID=OCC22335
    [Mark Pictor]

  * New --with-ftgl212 to declare FTGL 2.1.2 location.
    Fix sources to also work with newer FTGL versions.
    Submitted upstream:
      http://www.opencascade.org/org/forum/thread_20128/
      BugID = OCC22328
    [Denis Barbier]

  * Add missing clock_gettime implementation in MacOSX.
    [Thomas Paviot]

  * Remove duplicate header files.
    [Fotis Sioutis]

  * Fix build failure with tcl 8.6.
    Submitted upstream:
      http://www.opencascade.org/org/forum/thread_20125/
      BugID = OCC22327
    [Denis Barbier]

  * Bug fix: text doesn't get displayed in 6.5.
    Submitted upstream:
      http://www.opencascade.org/org/forum/thread_20101/
    [Venugopal Gudimetla]

  * Fix building with FreeImage on Unix.
    Submitted upstream:
      http://www.opencascade.org/org/forum/thread_20043/
    [Denis Barbier]

  * Add -version-info 0:0:0 libtool flag on Unix.
    [Denis Barbier]

  * Rename config.h into oce-config.h.
    [Denis Barbier]
