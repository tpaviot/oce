dnl Process this file with autoconf to produce a configure script.
AC_INIT([OpenCASCADE], [6.5.0oce1], [oce-dev@googlegroups.com])
AC_PREREQ([2.60])
AC_CONFIG_AUX_DIR([make])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/Standard/Standard.cxx])
AM_INIT_AUTOMAKE([foreign 1.9])

AC_CANONICAL_HOST

dnl AM_MAINTAINER_MODE

dnl Checks for programs.
AC_USE_SYSTEM_EXTENSIONS

LT_INIT([disable-static])

AC_PROG_CC
AC_PROG_CXX

AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_YACC
AC_PROG_MAKE_SET

AC_SEARCH_LIBS([strerror],[cposix])
AC_C_BIGENDIAN

dnl Checks for header files.

AC_HEADER_STDC
AC_LANG([C])
AC_MSG_CHECKING([ for C header files ])
AC_CHECK_HEADERS([dlfcn.h dl.h ieeefp.h time.h sys/time.h pwd.h])
AC_CHECK_HEADERS([sys/statvfs.h sys/vfs.h sys/param.h osfcn.h netdb.h])
AC_CHECK_HEADERS([sys/ioctl.h net/if.h sys/systeminfo.h sys/utsname.h])
AC_CHECK_HEADERS([sysent.h unistd.h sys/unistd.h sys/socket.h])
AC_CHECK_HEADERS([ndir.h sys/ndir.h sys/dir.h signal.h sys/signal.h])
AC_CHECK_HEADERS([sigfpe.h floatingpoint.h sys/machsig.h sys/siginfo.h])
AC_CHECK_HEADERS([malloc.h strings.h sys/stat.h sys/sem.h sys/ipc.h])
AC_CHECK_HEADERS([sys/times.h dirent.h])


AC_LANG([C++])
AC_MSG_CHECKING([ for C++ header files ])
AC_CHECK_HEADERS([istream ostream fstream ios iomanip iostream])
AC_CHECK_HEADERS([fstream.h stdlib.h ios.h iostream.h])
AC_CHECK_HEADERS([iomanip.h limits.h values.h])
AC_CHECK_HEADERS([siginfo.h sys/types.h sys/select.h])
AC_CHECK_HEADERS([X11/extensions/transovl.h X11/extensions/readdisplay.h])
AC_CHECK_HEADERS([X11/extensions/multibuf.h], [], [], [#include <X11/Xlib.h>])
AC_CHECK_HEADERS([sys/filio.h sys/mman.h libc.h])

#-----------------------------------------------------------------------------
# Posix threads library is required on Unix
#-----------------------------------------------------------------------------
case "x$host" in
  *msvc) ;;
  *)
    AC_CHECK_HEADER([pthread.h],[],[AC_MSG_ERROR([Posix threads required])])
    AC_CHECK_LIB([pthread],[pthread_create],[],[AC_MSG_ERROR([Posix threads required])])
    CSF_ThreadLibs_LIB=-lpthread
    AC_SUBST(CSF_ThreadLibs_LIB)
    ;;
esac

#-----------------------------------------------------------------------------
# dl library is required on Unix
#-----------------------------------------------------------------------------
case "x$host" in
  *msvc) ;;
  *)
    AC_CHECK_LIB([dl],[dlopen],[],[AC_MSG_ERROR([dl library is required])])
    CSF_SOCKETLibs_LIB=-ldl
    ;;
esac

#------------------------------------------------------------------------------
# Get Tcl and TK configuration information from tclConfig.sh.
#------------------------------------------------------------------------------

SC_TCL_CFG
SC_TK_CFG
HAVE_TCLTK=no
if test "xyes" = "x$HAVE_TCL"; then
  if test "xyes" = "x$HAVE_TK"; then
    HAVE_TCLTK=yes
    CSF_TclLibs_INCLUDES="${TCL_INCLUDE_SPEC}"
    CSF_TclTkLibs_INCLUDES="${TK_INCLUDE_SPEC}"
    CSF_TclLibs_LIB="${TCL_LIB_SPEC}"
    CSF_TclTkLibs_LIB="${TK_LIB_SPEC}"
  fi
fi
AC_SUBST([TCL_VERSION])
AC_SUBST([TK_VERSION])
AC_SUBST([CSF_TclLibs_INCLUDES])
AC_SUBST([CSF_TclTkLibs_INCLUDES])
AC_SUBST([CSF_TclLibs_LIB])
AC_SUBST([CSF_TclTkLibs_LIB])

dnl Make sure CSFDB is defined in CXXFLAGS and CFLAGS
CXXFLAGS="$CXXFLAGS -DCSFDB -DOCC_CONVERT_SIGNALS"
CFLAGS="$CFLAGS -DCSFDB -DOCC_CONVERT_SIGNALS"

case $host in
  *msvc)
    CPPFLAGS="$CPPFLAGS -DWNT -D__MATH_WNT_H -DHAVE_NO_DLL"
    CSF_SOCKETLibs_LIB='-lwinspool -lws2_32'
    CSF_wsock32_LIB='-lws2_32'
    CSF_gdi32_LIB='-lgdi32'
    CSF_comdlg32_LIB='-lcomdlg32'
    LDFLAGS="$LDFLAGS -no-undefined -shared -Wl,--enable-auto-import -Wl,--enable-runtime-pseudo-reloc -Wl,-export-all-symbols"
    platform=win32
    ;;
  *)
    platform=`uname -s`
    case $platform in
      Linux*)
        CXXFLAGS="$CXXFLAGS -DLIN -DLININTEL -D_GNU_SOURCE=1"
        CFLAGS="$CFLAGS -DLIN -DLININTEL -fexceptions"
        LDFLAGS="$LDFLAGS -lstdc++ -lrt"
        ;;
      SunOS*)
        CXXFLAGS="$CXXFLAGS -Usun -DSOLARIS -instances=static"
        CFLAGS="$CFLAGS -Usun -DSOLARIS -instances=static"
        LDFLAGS="$LDFLAGS -instances=static"
        CSF_SOCKETLibs_LIB="-lnsl ${CSF_SOCKETLibs_LIB}"
        ;;
      OSF1*)
        CXXFLAGS="$CXXFLAGS -DDECOSF1 -D__USE_STD_IOSTREAM -D_RWSTD_NO_EXCEPTIONS" 
        CFLAGS="$CFLAGS -std1 -DDECOSF1"
        LD=$CXX
        ;;
      *) ;;
    esac
esac
AC_SUBST([CSF_SOCKETLibs_LIB])

AM_CONDITIONAL( [IS_WINDOWS], [test "xwin32" = "x$platform" || test "xwin64" = "x$platform" ] )

AC_SUBST([platform])
AC_LANG([C++])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_STRUCT_TM

dnl Checks for library functions.
AC_CHECK_FUNCS([gethostname putenv re_comp regcomp strcspn strdup strtol])
AC_CHECK_FUNCS([statfs statvfs])


AC_CACHE_CHECK([if it is OK to define stream input and output],
  [occ_cv_def_ios_ok],
  [AC_LANG([C++])
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <stream.h>
static const int input = (ios::in) | (ios::nocreate);
static const int output= (ios::out);]], [[return 0;]])],
     [occ_cv_def_ios_ok=yes],
     [occ_cv_def_ios_ok=no])])
if test "$occ_cv_def_ios_ok" = yes; then
  AC_DEFINE([DEF_IOS_OK],,[define if the compiler allows redefinition of stream input and output])
fi

AC_CACHE_CHECK([if class ostream has member function form],
  [occ_cv_ostream_form_ok],
  [AC_LANG([C++])
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <iostream.h>
]], [[cout << cout.form("%9.3e", 3.14159627e-4) << endl; return 0;]])],
     [occ_cv_ostream_form_ok=yes],
     [occ_cv_ostream_form_ok=no])])
if test "$occ_cv_ostream_form_ok" = yes; then
  AC_DEFINE([OSTREAM_FORM_OK],,[define if the class ostream has member function form])
fi


dnl Checks for typedefs, structures, and compiler characteristics.

# if the following code compiles then the union semun is
# defined in the header <sys/sem.h>

AC_CACHE_CHECK([if union semun is defined in <sys/sem.h>],
  [occ_cv_semun_defined],
  [AC_LANG([C])
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <sys/time.h>
#include <sys/sem.h>
]], [[union semun c;]])],
     [occ_cv_semun_defined=yes],
     [occ_cv_semun_defined=no])])
if test "$occ_cv_semun_defined" = yes; then
  AC_DEFINE([SEMUN_DEFINED],,[define if the union semun is in sys/sem.h])
fi

# if the following code compiles then the union semun has
# the member __buf

if test "$occ_cv_semun_defined" = yes; then
  AC_CACHE_CHECK([if union semun has member __buf],
    [occ_cv_semun_buf_defined],
    [AC_LANG([C])
     AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <sys/sem.h>
]], [[ union semun c; c.__buf = 0;]])],
      [occ_cv_semun_buf_defined=yes],
      [occ_cv_semun_buf_defined=no])])
  if test "$sumun_buf_defined" = yes; then
    AC_DEFINE([SEMUN_BUF_DEFINED],,[define if semun has member __buf])
  fi
fi


AC_CACHE_CHECK([if function semop takes a value],
  [occ_cv_semop_no_reference],
  [AC_LANG([C])
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <sys/sem.h>
static struct sembuf event_flag ;]], [[
 int status;
 int *semid;
 status = semop(*semid,event_flag,1);
]])],
     [occ_cv_semop_no_reference=yes],
     [occ_cv_semop_no_reference=no])])
if test "$occ_cv_semop_no_reference" = yes; then
  AC_DEFINE([SEMOP_NO_REFERENCE],,[define if the function semop takes a value])
fi


AC_CACHE_CHECK([if function semctl takes a value],
  [occ_cv_semctl_no_reference],
  [AC_LANG([C])
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <sys/sem.h>
int get_semaphore(semid,event,value)
 int *semid, *event, *value;
{
 int status;
 status = semctl((*semid),*event,GETVAL,value);
 return 0;
}
int *a,*b,*c;]], [[if(get_semaphore(a,b,c)) exit 0;]])],
     [occ_cv_semctl_no_reference=yes],
     [occ_cv_semctl_no_reference=no])])
if test "$occ_cv_semctl_no_reference" = yes; then
  AC_DEFINE([SEMCTL_NO_REFERENCE],,[define if the function semctl takes a value])
fi

AC_CHECK_LIB([malloc],[mallinfo],[
  AC_DEFINE([HAVE_MALLINFO],,[Define if we have a function called "mallinfo" in -lmalloc.])
  LIBS="$LIBS -lmalloc"
])

AC_CHECK_LIB([sunmath],[ieee_handler],[
  AC_DEFINE([HAVE_SUNMATH],,[Define if we have a function called "ieee_handler" in -lsunmath.])
  LIBS="$LIBS -lsunmath"
])

AC_CHECK_LIB([m],[finite],[
  AC_DEFINE([HAVE_FINITE],,[Define if we have a function called "finite" in -lm.])
])

CFLAGS_save="$CFLAGS"
CXXFLAGS_save="$CXXFLAGS"
CPPFLAGS_save="$CPPFLAGS"
LDFLAGS_save="$LDFLAGS"
LIBS_save="$LIBS"

#---------------------------------------------------------------------
#
# Configure X11 and check for utility library
#
#---------------------------------------------------------------------
AC_LANG([C])

AC_PATH_X
HAVE_X11=no
X_INCLUDE=""
X_LIBS=""
CSF_XmuLibs_INCLUDES=""
CSF_XmuLibs_LIB=""
if test "xyes" != "x$no_x"; then
  HAVE_X11=yes
  if test "x" != "x$x_includes"; then
    X_INCLUDE="-I$x_includes"
    CSF_XmuLibs_INCLUDES="$X_INCLUDE"
    CXXFLAGS="$CXXFLAGS -I$x_includes"
  fi
  if test "x" != "x$x_libraries"; then
    X_LIBS="-L$x_libraries"
    CSF_XmuLibs_LIB="$X_LIBS"
    LDFLAGS="$LDFLAGS -L$x_libraries"
  fi
fi
if test "xyes" = "x$HAVE_X11"; then
  AC_CHECK_HEADER( [X11/Xmu/Xmu.h], [], [HAVE_X11=no] )
fi
if test "xyes" = "x$HAVE_X11"; then
  AC_CHECK_LIB( [X11], [XCreateWindow], [X_LIBS="${X_LIBS} -lXt -lX11"], [HAVE_X11=no] )
fi
if test "xyes" = "x$HAVE_X11"; then
  AC_CHECK_LIB( [Xmu], [XmuLookupStandardColormap], [CSF_XmuLibs_LIB="$CSF_XmuLibs_LIB -lXmu"], [HAVE_X11=no], [-lXt -lX11] )
fi
AM_CONDITIONAL( [HAVE_X11], [test "xyes" = "x$HAVE_X11"] )

#---------------------------------------------------------------------
#
# Check for OpenGL Libraries
#  
#  
#---------------------------------------------------------------------
CSF_OpenGlLibs_INCLUDES="$X_INCLUDE"
CSF_OpenGlLibs_LIB="$X_LIBS"
if test "xyes" = "x$HAVE_X11"; then
  AC_LANG([C])
  AC_CHECK_HEADER( [GL/gl.h], [AC_CHECK_HEADER([GL/glu.h],[HAVE_GL=yes],[HAVE_GL=no])], [HAVE_GL=no] )
  if test "xno" = "x$HAVE_GL"; then
    AC_MSG_NOTICE([Specify CPPFLAGS=-I<opengl_inc_dir> to enable OpenGL support])
  fi
fi
if test "xyes" = "x$HAVE_GL"; then
  AC_CHECK_TYPE([_GLUfuncptr], [], [CSF_OpenGlLibs_INCLUDES="$CSF_OpenGlLibs_INCLUDES -DNOGLUfuncptr=1"], [#include <GL/glu.h>])
fi
if test "xyes" = "x$HAVE_GL"; then
  CPPFLAGS="$CSF_OpenGlLibs_INCLUDES $CPPFLAGS"
  AC_CHECK_LIB( [GL], [glClear],
    [AC_CHECK_LIB([GLU],[gluSphere],[CSF_OpenGlLibs_LIB="$CSF_OpenGlLibs_LIB -lGLU -lGL"],[HAVE_GL=no],[-lGL])],
    [HAVE_GL=no] )
  if test "xno" = "x$HAVE_GL"; then
    AC_MSG_NOTICE([Specify LDFLAGS=-L<opengl_lib_dir> to enable OpenGL support])
  fi
fi

#---------------------------------------------------------------------
#
# Check for FREETYPE Libraries
#  
#  
#---------------------------------------------------------------------
AC_ARG_WITH([freetype],
  [AS_HELP_STRING([--with-freetype=DIR],[Location of FREETYPE])],
  [freetype="${withval}"],[freetype=])

CSF_FREETYPE_INCLUDES=""

if test "xyes" = "x$HAVE_GL" && test "xno" != "x$freetype"; then
  AC_LANG([C++])
  CPPFLAGS="-I$freetype/include -I$freetype/include/freetype2 $CPPFLAGS"
  AC_CHECK_HEADER( [ft2build.h], [], [AC_MSG_FAILURE([could not find ft2build.h])] )
  AC_CHECK_LIB([freetype], [FT_New_Face],
    [HAVE_FREETYPE=yes],
    [AC_MSG_FAILURE([could not link against freetype])],
    [$CSF_OpenGlLibs_LIB])
  CSF_FREETYPE_INCLUDES="-I$freetype/include -I$freetype/include/freetype2"
fi

#---------------------------------------------------------------------
#
# Check for FTGL Libraries
#  
#  
#---------------------------------------------------------------------
HAVE_FTGL_NEWER212=no
ftgl=
AC_ARG_WITH([ftgl212],
  [AS_HELP_STRING([--with-ftgl212=DIR],[Location of FTGL 2.1.2])],
  [ftgl="${withval}"])
AC_ARG_WITH([ftgl],
  [AS_HELP_STRING([--with-ftgl=DIR],[Location of FTGL])],
  [ftgl="${withval}"
   HAVE_FTGL_NEWER212=yes],[ftgl=])

CSF_FTGL_INCLUDES=
CSF_FTGL_LIB=

if test "xyes" = "x$HAVE_FREETYPE"; then
  AC_LANG([C++])
  HAVE_FTGL=yes
  CPPFLAGS_sv=$CPPFLAGS
  CPPFLAGS="-I$ftgl/include $CSF_FREETYPE_INCLUDES"
  if test "x$HAVE_FTGL_NEWER212" = xyes; then
    AC_CHECK_HEADER([FTGL/ftgl.h],
      [AC_DEFINE([HAVE_FTGL_NEWER212], 1, [Define if we use ftgl > 2.1.2.])],
      [AC_MSG_FAILURE([could not find FTGL/ftgl.h])])
  else
    AC_CHECK_HEADER([FTGL/FTGL.h], [], [AC_MSG_FAILURE([could not find FTGL/FTGL.h])])
  fi
  AC_MSG_CHECKING([for FTGLTextureFont in -lftgl])
  CSF_FTGL_LIB="-L$ftgl/lib -lftgl -L$freetype/lib -lfreetype"
  CSF_FTGL_INCLUDES="-I$ftgl/include"
  LDFLAGS="-L$ftgl/lib $LDFLAGS"
  LIBS_sv=$LIBS
  LIBS="$CSF_FTGL_LIB $CSF_OpenGlLibs_LIB $LIBS"
  if test "x$HAVE_FTGL_NEWER212" = xyes; then
    AC_LINK_IFELSE([AC_LANG_PROGRAM([
#include <FTGL/ftgl.h>
], [FTGLTextureFont font("");])],
      [AC_MSG_RESULT(yes)],
      [AC_MSG_FAILURE([could not link against ftgl])])
  else
    AC_LINK_IFELSE([AC_LANG_PROGRAM([
#include <FTGL/FTGL.h>
#include <FTGL/FTGLTextureFont.h>
], [FTGLTextureFont font("");])],
      [AC_MSG_RESULT(yes)],
      [AC_MSG_FAILURE([could not link against ftgl])])
  fi
  CPPFLAGS=$CPPFLAGS_sv
  LIBS=$LIBS_sv
fi

#---------------------------------------------------------------------
#
# Check for GL2PS Libraries
#  
#  
#---------------------------------------------------------------------
AC_ARG_WITH([gl2ps],
  [AS_HELP_STRING([--with-gl2ps=DIR],[Location of GL2PS])],
  [gl2ps="${withval}"],[gl2ps=])

if test "xno" = "x$gl2ps"; then
  # user specified --without-gl2ps
  HAVE_GL2PS=no
  ENABLE_GL2PS=no
  DISABLE_GL2PS_REASON="(--with-gl2ps=DIR option was not defined)"
elif test "xyes" = "x$gl2ps"; then
  # user specified --with-gl2ps, without =DIR
  AC_MSG_NOTICE([--with-gl2ps=DIR: DIR not specified, assuming /usr])
  gl2ps="/usr"
fi

CSF_GL2PS_INCLUDES=
CSF_GL2PS_LIB=

if test "xyes" = "x$HAVE_GL" && test "xno" != "x$gl2ps"; then
  AC_LANG([C++])
  ENABLE_GL2PS=yes
  CPPFLAGS="-I$gl2ps/include $CPPFLAGS";
  AC_CHECK_HEADER( [gl2ps.h], [HAVE_GL2PS=yes], [HAVE_GL2PS=no] )
  if test "xyes" = "x$HAVE_GL2PS"; then
    CSF_GL2PS_INCLUDES="-I$gl2ps/include"
    LDFLAGS="-L$gl2ps/lib $LDFLAGS"
    LIBS="$CSF_OpenGlLibs_LIB $LIBS"
    AC_CHECK_LIB( [gl2ps], [gl2psEndPage], [CSF_GL2PS_LIB="-L$gl2ps/lib -lgl2ps"], [HAVE_GL2PS=no] )
  fi
fi
if test "xyes" = "x$HAVE_GL2PS"; then
  AC_DEFINE([HAVE_GL2PS],,[define when building with gl2ps])
else
  CSF_GL2PS_INCLUDES=
  CSF_GL2PS_LIB=
fi

#---------------------------------------------------------------------
#
# Check for FREEIMAGE Libraries and Includes
#  
#  
#---------------------------------------------------------------------
AC_ARG_WITH([freeimage],
  [AS_HELP_STRING([--with-freeimage=DIR],[Location of freeimage])],
  [freeimage="${withval}"],[freeimage=])

if test "xno" = "x$freeimage"; then
  # user specified --without-freeimage
  HAVE_FREEIMAGE=no
  ENABLE_FREEIMAGE=no
  DISABLE_FREEIMAGE_REASON="(--with-freeimage=DIR option was not defined)"
elif test "xyes" = "x$freeimage"; then
  # user specified --with-freeimage, without =DIR
  AC_MSG_NOTICE([--with-freeimage=DIR: DIR not specified, assuming /usr])
  freeimage="/usr"
fi

CSF_FreeImagePlus_INCLUDES=
CSF_FreeImagePlus_LIB=

if test "xno" != "x$freeimage"; then
  ENABLE_FREEIMAGE=yes

  AC_LANG([C++])
  CPPFLAGS="-I$freeimage/include $CPPFLAGS";
  AC_CHECK_HEADER( [FreeImage.h], [HAVE_FREEIMAGE=yes], [HAVE_FREEIMAGE=no] )
  if test "xyes" = "x$HAVE_FREEIMAGE"; then
    CSF_FreeImagePlus_INCLUDES="-I$freeimage/include"
    LDFLAGS="-L$freeimage/lib $LDFLAGS"
    LIBS="$CSF_FreeImagePlus_LIB $LIBS"
    AC_CHECK_LIB( [freeimageplus], [FreeImage_OpenMemory], [CSF_FreeImagePlus_LIB="-L$freeimage/lib -lfreeimageplus"], [HAVE_FREEIMAGE=no] )
  fi
fi
if test "xyes" = "x$HAVE_FREEIMAGE"; then
  AC_DEFINE([HAVE_FREEIMAGE],,[define when building with freeimage])
else
  CSF_FreeImagePlus_INCLUDES=
  CSF_FreeImagePlus_LIB=
fi
AM_CONDITIONAL( HAVE_FREEIMAGE, [test "xyes" = "x$HAVE_FREEIMAGE"] )

#---------------------------------------------------------------------
#
# Check for TBB Includes
#  
#  
#---------------------------------------------------------------------
AC_ARG_WITH([tbb-include],
  [AS_HELP_STRING([--with-tbb-include=DIR],[Location of Intel Threading Building Blocks includes])],
  [tbb_inc="${withval}"],[tbb_inc=])

if test "xno" = "x$tbb_inc"; then
  # user specified --without-tbb-include
  HAVE_TBB=no
  ENABLE_TBB_INC=no
  DISABLE_TBB_REASON_INC="(--with-tbb-include=DIR option was not defined)"
elif test "xyes" = "x$tbb_inc"; then
  # user specified --with-tbb-include, without =DIR
  AC_MSG_NOTICE([--with-tbb-include=DIR: DIR not specified])
fi

CSF_TBB_INCLUDES=""

if test "xno" != "x$tbb_inc"; then
  ENABLE_TBB_INC=yes
  AC_LANG([C++])
  if test "xyes" != "x$tbb_inc"; then
    CPPFLAGS="-I$tbb_inc $CPPFLAGS";
  fi
  AC_CHECK_HEADER( [tbb/tbb.h], [HAVE_TBB=yes], [HAVE_TBB=no] )
  if test "x$HAVE_TBB" != "xyes"; then
    AC_MSG_NOTICE([Specify --with-tbb-include to enable TBB support])
  fi
fi

#---------------------------------------------------------------------
#
# Check for TBB Libraries
#  
#  
#---------------------------------------------------------------------
AC_ARG_WITH([tbb-library],
  [AS_HELP_STRING([--with-tbb-library=DIR],[Location of Intel Threading Building Blocks libraries])],
  [tbb_lib="${withval}"],[tbb_lib=])

if test "xno" = "xno$tbb_lib"; then
  # user specified --without-tbb
  HAVE_TBB=no
  ENABLE_TBB_LIB=no
  DISABLE_TBB_REASON_LIB="(--with-tbb-library=DIR option was not defined)"
elif test "xyes" = "x$tbb_lib"; then
  # user specified --with-tbb-library, without =DIR
  AC_MSG_NOTICE([--with-tbb-library=DIR: DIR not specified])
fi

ENABLE_TBB_LIB=yes
CSF_TBB_LIB=""

if test "xno" != "x$HAVE_TBB"; then
  if test "xyes" != "x$tbb_lib"; then
    LDFLAGS="-L$tbb_lib $LDFLAGS"
  fi
  AC_CHECK_LIB([tbb], [TBB_runtime_interface_version], [], [HAVE_TBB=no])
  if test "xno" = "x$HAVE_TBB"; then
    AC_MSG_NOTICE([Specify --with-tbb-library to enable TBB support])
  fi
fi

if test "xno" != "x$HAVE_TBB"; then
  if test "x$tbb_inc" != "xyes"; then
    CSF_TBB_INCLUDES="-I$tbb_inc"
  fi
  if test "x$tbb_lib" != "xyes"; then
    CSF_TBB_LIB="-L$tbb_lib -ltbb -ltbbmalloc"
  fi
fi
if test "xyes" = "x$HAVE_TBB"; then
  AC_DEFINE([HAVE_TBB],,[define when building with TBB])
else
  CSF_TBB_INCLUDES=
  CSF_TBB_LIB=
fi


#---------------------------------------------------------------------
#
# Check for QT Libraries
#  
#  
#---------------------------------------------------------------------
AC_ARG_WITH([qt],
  [AS_HELP_STRING([--with-qt=QTDIR],[Location of QT])],
  [qt="${withval}"],[qt=])

CSF_QT_INCLUDES=
CSF_QT_LIB=

if test "xyes" = "x$HAVE_GL" && test "xno" != "x$qt"; then
  AC_LANG([C++])
  if test "x$qt" != "xyes"; then
    CPPFLAGS="-I$qt/include/QtGui -I$qt/include/QtCore -I$qt/include/Qt -I$qt/include $CPPFLAGS";
  else
    AC_MSG_NOTICE([--with-qt key is not defined])
  fi
  AC_CHECK_HEADER( [Qt/qpixmap.h], [HAVE_QT=yes], [HAVE_QT=no] )
fi
if test "xno" != "x$HAVE_QT"; then
  CSF_QT_INCLUDES="-I$qt/include/QtGui -I$qt/include/QtCore -I$qt/include/Qt -I$qt/include"
  AC_MSG_CHECKING([for connect in -lQtGui])
  LDFLAGS="-L$qt/lib $LDFLAGS"
  LIBS="$CSF_OpenGlLibs_LIB $LIBS"
  AC_CHECK_LIB( [QtGui], [connect], [CSF_QT_LIB="-L$qt/lib -lQtGui -lQtCore"], [HAVE_QT=no] )
  if test "xno" = "x$HAVE_QT"; then
    AC_MSG_NOTICE([Specify --with-qt to enable QT support])
  fi
fi
if test "xno" = "x$HAVE_QT"; then
  CSF_QT_INCLUDES=
  CSF_QT_LIB=
fi

AC_LANG([C])

CFLAGS="$CFLAGS_save"
CXXFLAGS="$CXXFLAGS_save"
CPPFLAGS="$CPPFLAGS_save"
LDFLAGS="$LDFLAGS_save"
LIBS="$LIBS_save"

#---------------------------------------------------------------------
#
# Test for 64-bit platforms
#  
#  
#---------------------------------------------------------------------
AC_MSG_CHECKING([if platform is 64-bit])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[int array[((int)sizeof(void*))-6];]])],[AC_MSG_RESULT([yes]); CPPFLAGS="$CPPFLAGS -D_OCC64"; case $platform in Linux*) CPPFLAGS="$CPPFLAGS -m64";; esac],[AC_MSG_RESULT([no]) ])

AC_ARG_ENABLE([debug],
              [AS_HELP_STRING([--enable-debug],[Debug Symbols])],
              [enable_debug=${enableval}],[enable_debug=no])
AC_ARG_ENABLE([production],
              [AS_HELP_STRING([--enable-production],[Optimized build (default)])],
              [enable_prod=${enableval}],[enable_prod=])

# Enable production unless enable-default was specified
if test "x$enable_prod" = "x"; then
  if test "x$enable_debug" != "xyes"; then
    enable_prod=yes
  fi
fi

if test "x$enable_prod" = "xyes"; then
  CFLAGS="$CFLAGS -O2"
  CXXFLAGS="$CXXFLAGS -O2"
fi
if test "x$enable_debug" = "xyes"; then
  CFLAGS="$CFLAGS -g"
  CXXFLAGS="$CXXFLAGS -g"
  CPPFLAGS="$CPPFLAGS -DDEB -D_DEBUG"
else
  CPPFLAGS="$CPPFLAGS -DNDEBUG  -DNo_Exception"
fi

#----------------------------------------------------------------------
#
# Enable/Disable Modules
#
#----------------------------------------------------------------------

AC_ARG_ENABLE([model],
  [AS_HELP_STRING([--disable-model],[Disable model components])],
  [ENABLE_MODEL=${enableval}],[ENABLE_MODEL=yes])
AC_ARG_ENABLE([vis],
  [AS_HELP_STRING([--disable-vis],[Don't build visualization component])],
  [ENABLE_VIS=${enableval}],[ENABLE_VIS=])
AC_ARG_ENABLE([ocaf],
  [AS_HELP_STRING([--disable-ocaf],[Don't build application framework])],
  [ENABLE_OCAF=${enableval}],[ENABLE_OCAF=])
AC_ARG_ENABLE([de],
  [AS_HELP_STRING([--disable-de],[Don't build data exchange])],
  [ENABLE_DE=${enableval}],[ENABLE_DE=])
AC_ARG_ENABLE([draw],
  [AS_HELP_STRING([--disable-draw],[Don't build test harness])],
  [ENABLE_DRAW=${enableval}],[ENABLE_DRAW=])

# Process options from above.  The behavior we want is:
#
# ENABLE_X = yes : User specified --enable-x 
#                  print informative error and exit if it cannot be built
#
# ENABLE_X = no :  User specified --disable-x (or --enable-x=no)
#                  silently disable building of component
#
# ENABLE_X =     : User didn't specify either way
#                  Build if possible.  Warn if it cannot be build
#                  because of some missing system requirement.  Inform
#                  if disabled because some other required component 
#                  was disabled.

# Visualization Component: requires model component, X11, and optionally OpenGL
ENABLE_VIS_X11=no
if test "x" = "x$ENABLE_VIS"; then
  ENABLE_VIS=yes
  ENABLE_VIS_X11=yes
  if test "xno" = "x$ENABLE_MODEL"; then
    AC_MSG_NOTICE([Disabling visualization component: not building model component])
    DISABLE_VIS_REASON="(Model Component Disabled)"
    ENABLE_VIS=no
  elif test "xyes" != "x$HAVE_X11"; then
    AC_MSG_WARN( [Disabling X11 portion of visualization component: X not found] )
    ENABLE_VIS_X11=no
  elif test "xyes" != "x$HAVE_GL"; then
    AC_MSG_WARN( [Disabling X11 portion of visualization component: GL not found] )
    ENABLE_VIS_X11=no
  elif test "xyes" != "x$HAVE_FREETYPE"; then
    AC_MSG_WARN( [Disabling X11 portion of visualization component: Freetype not found] )
    ENABLE_VIS_X11=no
  elif test "xyes" != "x$HAVE_FTGL"; then
    AC_MSG_WARN( [Disabling X11 portion of visualization component: FTGL not found] )
    ENABLE_VIS_X11=no
  fi
elif test "xno" != "x$ENABLE_VIS"; then
  if test "xno" = "x$ENABLE_MODEL"; then
    AC_MSG_ERROR([Visualization requires model component.])
  fi
fi  

# Lightwieght Application Framework: requires Visualization component
if test "x" = "x$ENABLE_OCAF"; then
  if test "xno" = "x$ENABLE_VIS"; then
    AC_MSG_NOTICE([Disabling application framework: not building visualization component])
    DISABLE_OCAF_REASON="(Visualization Component Disabled)"
    ENABLE_OCAF=no
  else
    ENABLE_OCAF=yes
  fi
elif test "xno" != "x$ENABLE_OCAF"; then
  if test "xno" = "x$ENABLE_VIS"; then
    AC_MSG_ERROR([Application framework requires visualization component.])
  fi
fi

# Data Exchange Component: requires OCAF
if test "x" = "x$ENABLE_DE"; then
  if test "xno" = "x$ENABLE_OCAF"; then
    AC_MSG_NOTICE([Disabling data exchange component: not building OCAF])
    DISABLE_DE_REASON="(Application Framework Component Disabled)"
    ENABLE_DE=no
  else
    ENABLE_DE=yes
  fi
elif test "xno" != "x$ENABLE_DE"; then
  if test "xno" = "x$ENABLE_OCAF"; then
    AC_MSG_ERROR([Data exchange requires application framework component.])
  fi
fi

# Test Harness: requires most components and Tck/TK
if test "x" = "x$ENABLE_DRAW"; then
  if test "xno" = "x$ENABLE_VIS"; then
    AC_MSG_NOTICE([Disabling test harness because visualization component will not be build.])
    DISABLE_DRAW_REASON="(Visualiziation Component Disabled)"
    ENABLE_DRAW=no
  elif test "xno" = "x$ENABLE_OCAF"; then
    AC_MSG_NOTICE([Disabling test harness because OCAF component will not be build.])
    DISABLE_DRAW_REASON="(Application Framework Disabled)"
    ENABLE_DRAW=no
  elif test "xno" = "x$ENABLE_DE"; then
    AC_MSG_NOTICE([Disabling test harness because DE component will not be build.])
    DISABLE_DRAW_REASON="(Data Exchange Disabled)"
    ENABLE_DRAW=no
  elif test "xyes" != "x$HAVE_TCLTK"; then
    AC_MSG_WARN([Disabling test harness: Tcl/TK not found.])
    DISABLE_DRAW_REASON="(Tcl/Tk Not Found)"
    ENABLE_DRAW=no
  else
    ENABLE_DRAW=yes
  fi
elif test "xno" != "x$ENABLE_DRAW"; then
  if test "xno" = "x$ENABLE_VIS"; then
    AC_MSG_ERROR([Test harness requires visualization component.])
  elif test "xno" = "x$ENABLE_OCAF"; then
    AC_MSG_ERROR([Test harness requires OCAF component.])
  elif test "xno" = "x$ENABLE_DE"; then
    AC_MSG_ERROR([Test harness requires DE component.])
  elif test "xyes" != "x$HAVE_TCLTK"; then
    AC_MSG_ERROR([Test harness requires Tcl/Tk.])
  fi
fi

# Convert to automake conditional values
AM_CONDITIONAL([ENABLE_MODEL], [test "xno" != "x$ENABLE_MODEL"])
AM_CONDITIONAL([ENABLE_VIS],   [test "xno" != "x$ENABLE_VIS"])
AM_CONDITIONAL([ENABLE_VIS_X11], [test "xno" != "x$ENABLE_VIS_X11"])
AM_CONDITIONAL([ENABLE_OCAF],  [test "xno" != "x$ENABLE_OCAF"])
AM_CONDITIONAL([ENABLE_DE],    [test "xno" != "x$ENABLE_DE"])
AM_CONDITIONAL([ENABLE_DRAW],  [test "xno" != "x$ENABLE_DRAW"])



#----------------------------------------------------------------------
#
# Write Output Files
#
#----------------------------------------------------------------------


AC_SUBST([CPPFLAGS])
CXXCPPFLAGS="$CPPFLAGS"
AC_SUBST([CXXCPPFLAGS])
AC_SUBST([CFLAGS])
AC_SUBST([CXXFLAGS])
AC_SUBST([LIBS])
AC_SUBST([LDFLAGS])


CSF_XwLibs_LIB="$X_LIBS"
CSF_MotifLibs_LIB="$X_LIBS"

AC_SUBST([CSF_SOCKETLibs_LIB])
AC_SUBST([CSF_FPELibs_LIB])
AC_SUBST([CSF_OpenGlLibs_INCLUDES])
AC_SUBST([CSF_OpenGlLibs_LIB])
AC_SUBST([CSF_FREETYPE_INCLUDES])
AC_SUBST([CSF_FTGL_INCLUDES])
AC_SUBST([CSF_FTGL_LIB])
AC_SUBST([CSF_GL2PS_INCLUDES])
AC_SUBST([CSF_GL2PS_LIB])
AC_SUBST([CSF_FreeImagePlus_INCLUDES])
AC_SUBST([CSF_FreeImagePlus_LIB])
AC_SUBST([CSF_advapi32_LIB])
AC_SUBST([CSF_gdi32_LIB])
AC_SUBST([CSF_user32_LIB])
AC_SUBST([CSF_wsock32_LIB])
AC_SUBST([CSF_comdlg32_LIB])
AC_SUBST([CSF_XwLibs_LIB])
AC_SUBST([CSF_MotifLibs_LIB])
AC_SUBST([CSF_XmuLibs_LIB])
AC_SUBST([CSF_XmuLibs_INCLUDES])
AC_SUBST([CSF_TBB_INCLUDES])
AC_SUBST([CSF_TBB_LIB])
AC_SUBST([CSF_QT_INCLUDES])
AC_SUBST([CSF_QT_LIB])


echo
echo "CC       = $CC"
echo "CXX      = $CXX"
echo "CFLAGS   = $CFLAGS"
echo "CXXFLAGS = $CXXFLAGS"
echo "CPPFLAGS = $CPPFLAGS"
echo "LDFLAGS  = $LDFLAGS"
echo 
echo "3rdparty optional products       "
echo "---------------------------------"
echo "gl2ps         : $ENABLE_GL2PS $DISABLE_GL2PS_REASON"
echo "freeimage     : $ENABLE_FREEIMAGE $DISABLE_FREEIMAGE_REASON"
echo "tbb includes  : $ENABLE_TBB_INC $DISABLE_TBB_REASON_INC"
echo "tbb libraries : $ENABLE_TBB_LIB $DISABLE_TBB_REASON_LIB"
echo
echo "Component                   Build"
echo "--------------------------  -----"
echo "Model data & algorithms     $ENABLE_MODEL $DISABLE_MODEL_REASON"
echo "Visualization               $ENABLE_VIS $DISABLE_VIS_REASON"
echo "Data Exchange               $ENABLE_DE $DISABLE_DE_REASON"
echo "Application Framework       $ENABLE_OCAF $DISABLE_OCAF_REASON"
echo "Test Harness (DRAW)         $ENABLE_DRAW $DISABLE_DRAW_REASON"
echo


AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile adm/make/Makefile \
adm/make/TKernel/Makefile \
adm/make/TKMath/Makefile \
adm/make/TKAdvTools/Makefile \
adm/make/TKG2d/Makefile \
adm/make/TKG3d/Makefile \
adm/make/TKGeomBase/Makefile \
adm/make/TKBRep/Makefile \
adm/make/TKGeomAlgo/Makefile \
adm/make/TKTopAlgo/Makefile \
adm/make/TKPrim/Makefile \
adm/make/TKBO/Makefile \
adm/make/TKHLR/Makefile \
adm/make/TKMesh/Makefile \
adm/make/TKShHealing/Makefile \
adm/make/TKXMesh/Makefile \
adm/make/TKBool/Makefile \
adm/make/TKFillet/Makefile \
adm/make/TKFeat/Makefile \
adm/make/TKOffset/Makefile \
adm/make/TKService/Makefile \
adm/make/TKV2d/Makefile \
adm/make/TKV3d/Makefile \
adm/make/TKOpenGl/Makefile \
adm/make/TKMeshVS/Makefile \
adm/make/TKNIS/Makefile \
adm/make/TKVoxel/Makefile \
adm/make/TKCDF/Makefile \
adm/make/PTKernel/Makefile \
adm/make/TKLCAF/Makefile \
adm/make/FWOSPlugin/Makefile \
adm/make/TKPShape/Makefile \
adm/make/TKCAF/Makefile \
adm/make/TKBinL/Makefile \
adm/make/TKXmlL/Makefile \
adm/make/TKPLCAF/Makefile \
adm/make/TKTObj/Makefile \
adm/make/TKShapeSchema/Makefile \
adm/make/TKBin/Makefile \
adm/make/TKXml/Makefile \
adm/make/TKPCAF/Makefile \
adm/make/TKBinTObj/Makefile \
adm/make/TKXmlTObj/Makefile \
adm/make/TKStdLSchema/Makefile \
adm/make/TKStdSchema/Makefile \
adm/make/TKVRML/Makefile \
adm/make/TKXCAF/Makefile \
adm/make/TKSTL/Makefile \
adm/make/TKXSBase/Makefile \
adm/make/TKXCAFSchema/Makefile \
adm/make/TKXmlXCAF/Makefile \
adm/make/TKBinXCAF/Makefile \
adm/make/TKSTEPBase/Makefile \
adm/make/TKIGES/Makefile \
adm/make/TKSTEPAttr/Makefile \
adm/make/TKSTEP209/Makefile \
adm/make/TKXDEIGES/Makefile \
adm/make/TKSTEP/Makefile \
adm/make/TKXDESTEP/Makefile \
adm/make/TKDraw/Makefile \
adm/make/TKTopTest/Makefile \
adm/make/TKViewerTest/Makefile \
adm/make/TKXSDRAW/Makefile \
adm/make/TKDCAF/Makefile \
adm/make/TKXDEDRAW/Makefile \
adm/make/TKTObjDRAW/Makefile \
adm/make/DRAWEXE/Makefile \
])
AC_OUTPUT
