# generated automatically by aclocal 1.7.3 -*- Autoconf -*-

# Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002
# Free Software Foundation, Inc.
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

#------------------------------------------------------------------------
# Check for TCL
# Options: --with-tcl=  :    Specify location of tclConfig.sh
#          --without-tcl=  : Skip check for TCL, assume not installed
# Defines:
#          HAVE_TCL : yes/no
#          Everything from tclConfig.sh
#------------------------------------------------------------------------
AC_DEFUN([SC_TCL_CFG], [
  AC_ARG_WITH(tcl, 
AC_HELP_STRING([--with-tcl=PATH],[Directory containing tclConfig.sh])
AC_HELP_STRING([--without-tcl],  [Assume no tcl libraries available]) , 
              [with_tcl="${withval}";require_tcl=yes],[with_tcl=yes;require_tcl=no])
  
  # If user requested disabling of tcl check
  if test "xno" = "x$with_tcl"; then
    HAVE_TCL=no
    require_tcl=no
  # Otherwise...
  else
    HAVE_TCL=no
    # Search for tclConfig.sh
    if test "xyes" != "x$with_tcl"; then
      # If user specified location
      . "${with_tcl}/tclConfig.sh" || AC_MSG_ERROR("Cannot read file: ${with_tcl}/tclConfig.sh")
      HAVE_TCL=yes
    else
      # Search for tclConfig.sh in usual spots
      tcl_cfg_file=
      AC_MSG_CHECKING([for tclConfig.sh])
      for i in /usr /usr/local ${prefix} /opt/sfw /usr/tcltk; do
        if test -d $i; then
          for j in $i/lib $i/lib/tcl $i/lib/tcl[[8-9]].[[0-9]] $i/lib/itcl; do
            if test -r "$j/tclConfig.sh"; then
              tcl_cfg_file="$j/tclConfig.sh"
              break
            fi
          done
        fi
        if test "x" != "x$tcl_cfg_file"; then
          break
        fi
      done
      AC_MSG_RESULT("$tcl_cfg_file")
      
      if test "x" != "x$tcl_cfg_file"; then
        . "$tcl_cfg_file" || AC_MSG_ERROR("Cannot read file: $tcl_cfg_file") 
        HAVE_TCL=yes

        # if TCL_INCLUDE_SPEC wasn't defined, try to define it using TCL_INC_DIR
        if test "x" = "x$TCL_INCLUDE_SPEC"; then
          inc_path=`expr "x$TCL_INC_DIR" : "x\(.*\)/tcl-private/generic"`
          if test "x" != "$inc_path"; then
            TCL_INCLUDE_SPEC="-I$inc_path"
          elif test "x" != "x$TCL_INC_DIR"; then
            TCL_INCLUDE_SPEC="-I$TCL_INC_DIR"
          fi
        fi
      else
        HAVE_TCL=no
      fi
    fi
    
    # Check for tcl.h
    AC_LANG_C
    save_CPPFLAGS="$CPPFLAGS"
    CPPFLAGS="$CPPFLAGS $TCL_INCLUDE_SPEC"
    AC_CHECK_HEADER([tcl.h],[],[HAVE_TCL=no])
    CPPFLAGS="$save_CPPFLAGS"
    
    if test "xyes" = "x$require_tcl"; then
      if test "xno" = "x$HAVE_TCL"; then
        AC_MSG_ERROR([TCL not found.])
      fi
    fi
  fi
])


#------------------------------------------------------------------------
# Check for Tk
# Options: --with-tk=  :    Specify location of Tk
#          --without-tk=  : Skip check for Tk, assume not installed
# Defines:
#          HAVE_TK : yes/no
#          Everything from tkConfig.sh
#------------------------------------------------------------------------
AC_DEFUN([SC_TK_CFG], [
  AC_ARG_WITH(tk, 
AC_HELP_STRING([--with-tk=PATH],[Directory containing tkConfig.sh])
AC_HELP_STRING([--without-tk],  [Assume no Tk libraries available]) , 
              [with_tk="${withval}";require_tk=yes],[with_tk=yes;require_tk=no])
  
  # If user requested disabling of Tk check
  if test "xno" = "x$with_tk"; then
    HAVE_TK=no
    require_tk=no
  # Otherwise...
  else
    HAVE_TK=no
    # Search for tkConfig.sh
    if test "xyes" != "x$with_tk"; then
      # If user specified location
      . "${with_tk}/tkConfig.sh" || AC_MSG_ERROR("Cannot read file: ${with_tk}/tkConfig.sh")
      HAVE_TK=yes
    else
      # Search for tkConfig.sh in usual spots
      tk_cfg_file=
      AC_MSG_CHECKING([for tkConfig.sh])
      for i in /usr /usr/local ${prefix} /opt/sfw /usr/tcltk; do
        if test -d $i; then
          for j in $i/lib $i/lib/tk $i/lib/tk[[8-9]].[[0-9]] $i/lib/itcl; do
            if test -r "$j/tkConfig.sh"; then
              tk_cfg_file="$j/tkConfig.sh"
              break
            fi
          done
        fi
        if test "x" != "x$tk_cfg_file"; then
          break
        fi
      done
      AC_MSG_RESULT("$tk_cfg_file")
      
      if test "x" != "x$tk_cfg_file"; then
        . "$tk_cfg_file" || AC_MSG_ERROR("Cannot read file: $tk_cfg_file") 
        HAVE_TK=yes

        # if TK_INCLUDE_SPEC wasn't defined, try to define it using TK_INC_DIR
        if test "x" = "x$TK_INCLUDE_SPEC"; then
          inc_path=`expr "x$TK_INC_DIR" : "x\(.*\)/tk-private/generic"`
          if test "x" != "$inc_path"; then
            TK_INCLUDE_SPEC="-I$inc_path"
          elif test "x" != "x$TK_INC_DIR"; then
            TK_INCLUDE_SPEC="-I$TK_INC_DIR"
          fi
        fi
      else
        HAVE_TK=no
      fi
    fi
    
    # Check for tk.h
    AC_LANG_C
    HAVE_TK=yes
    save_CPPFLAGS="$CPPFLAGS"
    CPPFLAGS="$CPPFLAGS $TCL_INCLUDE_SPEC $TK_INCLUDE_SPEC"
    AC_CHECK_HEADER([tk.h],[],[HAVE_TK=no])
    CPPFLAGS="$save_CPPFLAGS"
    
    if test "xyes" = "x$require_tk"; then
      if test "xno" = "x$HAVE_TK"; then
        AC_MSG_ERROR([Tk not found.])
      fi
    fi
  fi
])

#------------------------------------------------------------------------
# SC_ENABLE_GCC --
#
#	Allows the use of GCC if available
#
# Arguments:
#	none
#	
# Results:
#
#	Adds the following arguments to configure:
#		--enable-gcc
#
#	Sets the following vars:
#		CC	Command to use for the compiler
#------------------------------------------------------------------------

AC_DEFUN(SC_ENABLE_GCC, [
    AC_ARG_ENABLE(gcc, [  --enable-gcc            allow use of gcc if available [--disable-gcc]],
	[ok=$enableval], [ok=no])
    if test "$ok" = "yes"; then
	CC=gcc
	AC_PROG_CC
    else
	CC=${CC-cc}
    fi
])

#------------------------------------------------------------------------
# SC_ENABLE_SHARED --
#
#	Allows the building of shared libraries
#
# Arguments:
#	none
#	
# Results:
#
#	Adds the following arguments to configure:
#		--enable-shared=yes|no
#
#	Defines the following vars:
#		STATIC_BUILD	Used for building import/export libraries
#				on Windows.
#
#	Sets the following vars:
#		SHARED_BUILD	Value of 1 or 0
#------------------------------------------------------------------------

AC_DEFUN(SC_ENABLE_SHARED, [
    AC_MSG_CHECKING([how to build libraries])
    AC_ARG_ENABLE(shared,
	[  --enable-shared         build and link with shared libraries [--enable-shared]],
	[tcl_ok=$enableval], [tcl_ok=yes])

    if test "${enable_shared+set}" = set; then
	enableval="$enable_shared"
	tcl_ok=$enableval
    else
	tcl_ok=yes
    fi

    if test "$tcl_ok" = "yes" ; then
	AC_MSG_RESULT([shared])
	SHARED_BUILD=1
    else
	AC_MSG_RESULT([static])
	SHARED_BUILD=0
	AC_DEFINE(STATIC_BUILD)
    fi
])

#------------------------------------------------------------------------
# SC_ENABLE_THREADS --
#
#	Specify if thread support should be enabled
#
# Arguments:
#	none
#	
# Results:
#
#	Adds the following arguments to configure:
#		--enable-threads
#
#	Sets the following vars:
#		THREADS_LIBS	Thread library(s)
#
#	Defines the following vars:
#		TCL_THREADS
#		_REENTRANT
#		_THREAD_SAFE
#
#------------------------------------------------------------------------

AC_DEFUN(SC_ENABLE_THREADS, [
    AC_MSG_CHECKING(for building with threads)
    AC_ARG_ENABLE(threads, [  --enable-threads        build with threads],
	[tcl_ok=$enableval], [tcl_ok=no])

    if test "$tcl_ok" = "yes"; then
	AC_MSG_RESULT(yes)
	TCL_THREADS=1
	AC_DEFINE(TCL_THREADS)
	AC_DEFINE(_REENTRANT)
	AC_DEFINE(_THREAD_SAFE)
	AC_CHECK_LIB(pthread,pthread_mutex_init,tcl_ok=yes,tcl_ok=no)
	if test "$tcl_ok" = "no"; then
	    # Check a little harder for __pthread_mutex_init in the same
	    # library, as some systems hide it there until pthread.h is
	    # defined.  We could alternatively do an AC_TRY_COMPILE with
	    # pthread.h, but that will work with libpthread really doesn't
	    # exist, like AIX 4.2.  [Bug: 4359]
	    AC_CHECK_LIB(pthread,__pthread_mutex_init,tcl_ok=yes,tcl_ok=no)
	fi

	if test "$tcl_ok" = "yes"; then
	    # The space is needed
	    THREADS_LIBS=" -lpthread"
	else
	    AC_CHECK_LIB(pthreads,pthread_mutex_init,tcl_ok=yes,tcl_ok=no)
	    if test "$tcl_ok" = "yes"; then
		# The space is needed
		THREADS_LIBS=" -lpthreads"
	    else
		AC_CHECK_LIB(c,pthread_mutex_init,tcl_ok=yes,tcl_ok=no)
	    	if test "$tcl_ok" = "no"; then
	    	    TCL_THREADS=0
		    AC_MSG_WARN("Don t know how to find pthread lib on your system - you must disable thread support or edit the LIBS in the Makefile...")
	    	fi
	    fi
	fi

	# Does the pthread-implementation provide
	# 'pthread_attr_setstacksize' ?

	AC_CHECK_FUNCS(pthread_attr_setstacksize)
    else
	TCL_THREADS=0
	AC_MSG_RESULT([no (default)])
    fi
])

#------------------------------------------------------------------------
# SC_ENABLE_SYMBOLS --
#
#	Specify if debugging symbols should be used
#
# Arguments:
#	none
#	
#	Requires the following vars to be set:
#		CFLAGS_DEBUG
#		CFLAGS_OPTIMIZE
#		LDFLAGS_DEBUG
#		LDFLAGS_OPTIMIZE
#	
# Results:
#
#	Adds the following arguments to configure:
#		--enable-symbols
#
#	Defines the following vars:
#		CFLAGS_DEFAULT	Sets to CFLAGS_DEBUG if true
#				Sets to CFLAGS_OPTIMIZE if false
#		LDFLAGS_DEFAULT	Sets to LDFLAGS_DEBUG if true
#				Sets to LDFLAGS_OPTIMIZE if false
#		DBGX		Debug library extension
#
#------------------------------------------------------------------------

AC_DEFUN(SC_ENABLE_SYMBOLS, [
    AC_MSG_CHECKING([for build with symbols])
    AC_ARG_ENABLE(symbols, [  --enable-symbols        build with debugging symbols [--disable-symbols]],    [tcl_ok=$enableval], [tcl_ok=no])
    if test "$tcl_ok" = "yes"; then
	CFLAGS_DEFAULT="${CFLAGS_DEBUG}"
	LDFLAGS_DEFAULT="${LDFLAGS_DEBUG}"
	DBGX=g
	AC_MSG_RESULT([yes])
    else
	CFLAGS_DEFAULT="${CFLAGS_OPTIMIZE}"
	LDFLAGS_DEFAULT="${LDFLAGS_OPTIMIZE}"
	DBGX=""
	AC_MSG_RESULT([no])
    fi
])

#--------------------------------------------------------------------
# SC_CONFIG_CFLAGS
#
#	Try to determine the proper flags to pass to the compiler
#	for building shared libraries and other such nonsense.
#
# Arguments:
#	none
#
# Results:
#
#	Defines the following vars:
#
#       DL_OBJS -       Name of the object file that implements dynamic
#                       loading for Tcl on this system.
#       DL_LIBS -       Library file(s) to include in tclsh and other base
#                       applications in order for the "load" command to work.
#       LDFLAGS -      Flags to pass to the compiler when linking object
#                       files into an executable application binary such
#                       as tclsh.
#       LD_SEARCH_FLAGS-Flags to pass to ld, such as "-R /usr/local/tcl/lib",
#                       that tell the run-time dynamic linker where to look
#                       for shared libraries such as libtcl.so.  Depends on
#                       the variable LIB_RUNTIME_DIR in the Makefile.
#       MAKE_LIB -      Command to execute to build the Tcl library;
#                       differs depending on whether or not Tcl is being
#                       compiled as a shared library.
#       SHLIB_CFLAGS -  Flags to pass to cc when compiling the components
#                       of a shared library (may request position-independent
#                       code, among other things).
#       SHLIB_LD -      Base command to use for combining object files
#                       into a shared library.
#       SHLIB_LD_LIBS - Dependent libraries for the linker to scan when
#                       creating shared libraries.  This symbol typically
#                       goes at the end of the "ld" commands that build
#                       shared libraries. The value of the symbol is
#                       "${LIBS}" if all of the dependent libraries should
#                       be specified when creating a shared library.  If
#                       dependent libraries should not be specified (as on
#                       SunOS 4.x, where they cause the link to fail, or in
#                       general if Tcl and Tk aren't themselves shared
#                       libraries), then this symbol has an empty string
#                       as its value.
#       SHLIB_SUFFIX -  Suffix to use for the names of dynamically loadable
#                       extensions.  An empty string means we don't know how
#                       to use shared libraries on this platform.
#       TCL_LIB_FILE -  Name of the file that contains the Tcl library, such
#                       as libtcl7.8.so or libtcl7.8.a.
#       TCL_LIB_SUFFIX -Specifies everything that comes after the "libtcl"
#                       in the shared library name, using the $VERSION variable
#                       to put the version in the right place.  This is used
#                       by platforms that need non-standard library names.
#                       Examples:  ${VERSION}.so.1.1 on NetBSD, since it needs
#                       to have a version after the .so, and ${VERSION}.a
#                       on AIX, since the Tcl shared library needs to have
#                       a .a extension whereas shared objects for loadable
#                       extensions have a .so extension.  Defaults to
#                       ${VERSION}${SHLIB_SUFFIX}.
#       TCL_NEEDS_EXP_FILE -
#                       1 means that an export file is needed to link to a
#                       shared library.
#       TCL_EXP_FILE -  The name of the installed export / import file which
#                       should be used to link to the Tcl shared library.
#                       Empty if Tcl is unshared.
#       TCL_BUILD_EXP_FILE -
#                       The name of the built export / import file which
#                       should be used to link to the Tcl shared library.
#                       Empty if Tcl is unshared.
#	CFLAGS_DEBUG -
#			Flags used when running the compiler in debug mode
#	CFLAGS_OPTIMIZE -
#			Flags used when running the compiler in optimize mode
#
#	EXTRA_CFLAGS
#
#	Subst's the following vars:
#		DL_LIBS
#		CFLAGS_DEBUG
#		CFLAGS_OPTIMIZE
#--------------------------------------------------------------------

AC_DEFUN(SC_CONFIG_CFLAGS, [

    # Step 0.a: Enable 64 bit support?

    AC_MSG_CHECKING([if 64bit support is requested])
    AC_ARG_ENABLE(64bit,[  --enable-64bit          enable 64bit support (where applicable)],,enableval="no")

    if test "$enableval" = "yes"; then
	do64bit=yes
    else
	do64bit=no
    fi
    AC_MSG_RESULT($do64bit)

    # Step 0.b: Enable Solaris 64 bit VIS support?

    AC_MSG_CHECKING([if 64bit Sparc VIS support is requested])
    AC_ARG_ENABLE(64bit-vis,[  --enable-64bit-vis      enable 64bit Sparc VIS support],,enableval="no")

    if test "$enableval" = "yes"; then
	# Force 64bit on with VIS
	do64bit=yes
	do64bitVIS=yes
    else
	do64bitVIS=no
    fi
    AC_MSG_RESULT($do64bitVIS)

    # Step 1: set the variable "system" to hold the name and version number
    # for the system.  This can usually be done via the "uname" command, but
    # there are a few systems, like Next, where this doesn't work.

    AC_MSG_CHECKING([system version (for dynamic loading)])
    if test -f /usr/lib/NextStep/software_version; then
	system=NEXTSTEP-`awk '/3/,/3/' /usr/lib/NextStep/software_version`
    else
	system=`uname -s`-`uname -r`
	if test "$?" -ne 0 ; then
	    AC_MSG_RESULT([unknown (can't find uname command)])
	    system=unknown
	else
	    # Special check for weird MP-RAS system (uname returns weird
	    # results, and the version is kept in special file).
	
	    if test -r /etc/.relid -a "X`uname -n`" = "X`uname -s`" ; then
		system=MP-RAS-`awk '{print $3}' /etc/.relid'`
	    fi
	    if test "`uname -s`" = "AIX" ; then
		system=AIX-`uname -v`.`uname -r`
	    fi
	    AC_MSG_RESULT($system)
	fi
    fi

    AC_MSG_CHECKING([if gcc is being used])
    if test "$CC" = "gcc" -o `$CC -v 2>&1 | grep -c gcc` != "0" ; then
	using_gcc="yes"
    else
	using_gcc="no"
    fi

    AC_MSG_RESULT([$using_gcc ($CC)])

    # Step 2: check for existence of -ldl library.  This is needed because
    # Linux can use either -ldl or -ldld for dynamic loading.

    AC_CHECK_LIB(dl, dlopen, have_dl=yes, have_dl=no)

    # Step 3: set configuration options based on system name and version.

    do64bit_ok=no
    fullSrcDir=`cd $srcdir; pwd`
    EXTRA_CFLAGS=""
    TCL_EXPORT_FILE_SUFFIX=""
    UNSHARED_LIB_SUFFIX=""
    TCL_TRIM_DOTS='`echo ${VERSION} | tr -d .`'
    ECHO_VERSION='`echo ${VERSION}`'
    TCL_LIB_VERSIONS_OK=ok
    CFLAGS_DEBUG=-g
    CFLAGS_OPTIMIZE=-O
    if test "$using_gcc" = "yes" ; then
	CFLAGS_WARNING="-Wall -Wconversion -Wno-implicit-int"
    else
	CFLAGS_WARNING=""
    fi
    TCL_NEEDS_EXP_FILE=0
    TCL_BUILD_EXP_FILE=""
    TCL_EXP_FILE=""
    STLIB_LD="ar cr"
    case $system in
	AIX-5.*)
	    if test "${TCL_THREADS}" = "1" -a "$using_gcc" = "no" ; then
		# AIX requires the _r compiler when gcc isn't being used
		if test "${CC}" != "cc_r" ; then
		    CC=${CC}_r
		fi
		AC_MSG_RESULT(Using $CC for compiling with threads)
	    fi
	    # AIX-5 uses ELF style dynamic libraries
	    SHLIB_CFLAGS=""
	    SHLIB_LD="/usr/ccs/bin/ld -G -z text"

	    # Note: need the LIBS below, otherwise Tk won't find Tcl's
	    # symbols when dynamically loaded into tclsh.

	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    # AIX-5 has dl* in libc.so
	    DL_LIBS=""
	    LDFLAGS=""
	    if test "$using_gcc" = "yes" ; then
		LD_SEARCH_FLAGS='-Wl,-R,${LIB_RUNTIME_DIR}'
	    else
		LD_SEARCH_FLAGS='-R${LIB_RUNTIME_DIR}'
	    fi

	    if test "$do64bit" = "yes" ; then
		if test "$using_gcc" = "no" ; then
		    do64bit_ok=yes
		    EXTRA_CFLAGS="-q64"
		    LDFLAGS="-q64"
		else 
		    AC_MSG_WARN("64bit mode not supported with GCC on $system")
		fi
	    fi
	    ;;
	AIX-*)
	    if test "${TCL_THREADS}" = "1" -a "$using_gcc" = "no" ; then
		# AIX requires the _r compiler when gcc isn't being used
		if test "${CC}" != "cc_r" ; then
		    CC=${CC}_r
		fi
		AC_MSG_RESULT(Using $CC for compiling with threads)
	    fi
	    SHLIB_CFLAGS=""
	    SHLIB_LD="$fullSrcDir/ldAix /bin/ld -bhalt:4 -bM:SRE -bE:lib.exp -H512 -T512 -bnoentry"
	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    LDFLAGS=""
	    LD_SEARCH_FLAGS='-L${LIB_RUNTIME_DIR}'
	    TCL_NEEDS_EXP_FILE=1
	    TCL_EXPORT_FILE_SUFFIX='${VERSION}\$\{DBGX\}.exp'

	    # AIX v<=4.1 has some different flags than 4.2+
	    if test "$system" = "AIX-4.1" -o "`uname -v`" -lt "4" ; then
		LIBOBJS="$LIBOBJS tclLoadAix.o"
		DL_LIBS="-lld"
	    fi

	    # On AIX <=v4 systems, libbsd.a has to be linked in to support
	    # non-blocking file IO.  This library has to be linked in after
	    # the MATH_LIBS or it breaks the pow() function.  The way to
	    # insure proper sequencing, is to add it to the tail of MATH_LIBS.
	    # This library also supplies gettimeofday.
	    #
	    # AIX does not have a timezone field in struct tm. When the AIX
	    # bsd library is used, the timezone global and the gettimeofday
	    # methods are to be avoided for timezone deduction instead, we
	    # deduce the timezone by comparing the localtime result on a
	    # known GMT value.

	    AC_CHECK_LIB(bsd, gettimeofday, libbsd=yes, libbsd=no)
	    if test $libbsd = yes; then
	    	MATH_LIBS="$MATH_LIBS -lbsd"
	    	AC_DEFINE(USE_DELTA_FOR_TZ)
	    fi
	    ;;
	BSD/OS-2.1*|BSD/OS-3*)
	    SHLIB_CFLAGS=""
	    SHLIB_LD="shlicc -r"
	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    LDFLAGS=""
	    LD_SEARCH_FLAGS=""
	    ;;
	BSD/OS-4.*)
	    SHLIB_CFLAGS="-export-dynamic -fPIC"
	    SHLIB_LD="cc -shared"
	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    LDFLAGS="-export-dynamic"
	    LD_SEARCH_FLAGS=""
	    ;;
	dgux*)
	    SHLIB_CFLAGS="-K PIC"
	    SHLIB_LD="cc -G"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    LDFLAGS=""
	    LD_SEARCH_FLAGS=""
	    ;;
	HP-UX-*.08.*|HP-UX-*.09.*|HP-UX-*.10.*|HP-UX-*.11.*)
	    SHLIB_SUFFIX=".sl"
	    AC_CHECK_LIB(dld, shl_load, tcl_ok=yes, tcl_ok=no)
	    if test "$tcl_ok" = yes; then
		SHLIB_CFLAGS="+z"
		SHLIB_LD="ld -b"
		SHLIB_LD_LIBS=""
		DL_OBJS="tclLoadShl.o"
		DL_LIBS="-ldld"
		LDFLAGS="-Wl,-E"
		LD_SEARCH_FLAGS='-Wl,+s,+b,${LIB_RUNTIME_DIR}:.'
	    fi
	    ;;
	IRIX-4.*)
	    SHLIB_CFLAGS="-G 0"
	    SHLIB_SUFFIX=".a"
	    SHLIB_LD="echo tclLdAout $CC \{$SHLIB_CFLAGS\} | `pwd`/tclsh -r -G 0"
	    SHLIB_LD_LIBS='${LIBS}'
	    DL_OBJS="tclLoadAout.o"
	    DL_LIBS=""
	    LDFLAGS="-Wl,-D,08000000"
	    LD_SEARCH_FLAGS='-L${LIB_RUNTIME_DIR}'
	    SHARED_LIB_SUFFIX='${VERSION}\$\{DBGX\}.a'
	    ;;
	IRIX-5.*)
	    SHLIB_CFLAGS=""
	    SHLIB_LD="ld -shared -rdata_shared"
	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS=""
	    LD_SEARCH_FLAGS='-Wl,-rpath,${LIB_RUNTIME_DIR}'
	    EXTRA_CFLAGS=""
	    LDFLAGS=""
	    ;;
	IRIX-6.*|IRIX64-6.5*)
	    SHLIB_CFLAGS=""
	    SHLIB_LD="ld -n32 -shared -rdata_shared"
	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS=""
	    LD_SEARCH_FLAGS='-Wl,-rpath,${LIB_RUNTIME_DIR}'
	    if test "$using_gcc" = "yes" ; then
		EXTRA_CFLAGS="-mabi=n32"
		LDFLAGS="-mabi=n32"
	    else
		case $system in
		    IRIX-6.3)
			# Use to build 6.2 compatible binaries on 6.3.
			EXTRA_CFLAGS="-n32 -D_OLD_TERMIOS"
			;;
		    *)
			EXTRA_CFLAGS="-n32"
			;;
		esac
		LDFLAGS="-n32"
	    fi
	    ;;
	IRIX64-6.*)
	    SHLIB_CFLAGS=""
	    SHLIB_LD="ld -32 -shared -rdata_shared"
	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS=""
	    LDFLAGS=""
	    LD_SEARCH_FLAGS='-Wl,-rpath,${LIB_RUNTIME_DIR}'
	    ;;
	Linux*)
	    SHLIB_CFLAGS="-fPIC"
	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"

	    # egcs-2.91.66 on Redhat Linux 6.0 generates lots of warnings 
	    # when you inline the string and math operations.  Turn this off to
	    # get rid of the warnings.

	    CFLAGS_OPTIMIZE="${CFLAGS_OPTIMIZE} -D__NO_STRING_INLINES -D__NO_MATH_INLINES"

	    if test "$have_dl" = yes; then
		SHLIB_LD="${CC} -shared"
		DL_OBJS="tclLoadDl.o"
		DL_LIBS="-ldl"
		LDFLAGS="-rdynamic"
		LD_SEARCH_FLAGS='-Wl,-rpath,${LIB_RUNTIME_DIR}'
	    else
		AC_CHECK_HEADER(dld.h, [
		    SHLIB_LD="ld -shared"
		    DL_OBJS="tclLoadDld.o"
		    DL_LIBS="-ldld"
		    LDFLAGS=""
		    LD_SEARCH_FLAGS=""])
	    fi
	    if test "`uname -m`" = "alpha" ; then
		EXTRA_CFLAGS="-mieee"
	    fi
	    ;;
	MP-RAS-02*)
	    SHLIB_CFLAGS="-K PIC"
	    SHLIB_LD="cc -G"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    LDFLAGS=""
	    LD_SEARCH_FLAGS=""
	    ;;
	MP-RAS-*)
	    SHLIB_CFLAGS="-K PIC"
	    SHLIB_LD="cc -G"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    LDFLAGS="-Wl,-Bexport"
	    LD_SEARCH_FLAGS=""
	    ;;
	NetBSD-*|FreeBSD-[[1-2]].*|OpenBSD-*)
	    # Not available on all versions:  check for include file.
	    AC_CHECK_HEADER(dlfcn.h, [
		# NetBSD/SPARC needs -fPIC, -fpic will not do.
		SHLIB_CFLAGS="-fPIC"
		SHLIB_LD="ld -Bshareable -x"
		SHLIB_LD_LIBS=""
		SHLIB_SUFFIX=".so"
		DL_OBJS="tclLoadDl.o"
		DL_LIBS=""
		LDFLAGS=""
		LD_SEARCH_FLAGS='-Wl,-rpath,${LIB_RUNTIME_DIR}'
		AC_MSG_CHECKING(for ELF)
		AC_EGREP_CPP(yes, [
#ifdef __ELF__
	yes
#endif
		],
		    AC_MSG_RESULT(yes)
		    SHARED_LIB_SUFFIX='${TCL_TRIM_DOTS}\$\{DBGX\}.so',
		    AC_MSG_RESULT(no)
		    SHARED_LIB_SUFFIX='${TCL_TRIM_DOTS}\$\{DBGX\}.so.1.0'
		)
	    ], [
		SHLIB_CFLAGS=""
		SHLIB_LD="echo tclLdAout $CC \{$SHLIB_CFLAGS\} | `pwd`/tclsh -r"
		SHLIB_LD_LIBS='${LIBS}'
		SHLIB_SUFFIX=".a"
		DL_OBJS="tclLoadAout.o"
		DL_LIBS=""
		LDFLAGS=""
		LD_SEARCH_FLAGS='-L${LIB_RUNTIME_DIR}'
		SHARED_LIB_SUFFIX='${TCL_TRIM_DOTS}\$\{DBGX\}.a'
	    ])

	    # FreeBSD doesn't handle version numbers with dots.

	    UNSHARED_LIB_SUFFIX='${TCL_TRIM_DOTS}\$\{DBGX\}.a'
	    TCL_LIB_VERSIONS_OK=nodots
	    ;;
	FreeBSD-*)
	    # FreeBSD 3.* and greater have ELF.
	    SHLIB_CFLAGS="-fPIC"
	    SHLIB_LD="ld -Bshareable -x"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS=""
	    LDFLAGS="-export-dynamic"
	    LD_SEARCH_FLAGS=""
	    ;;
	Rhapsody-*|Darwin-*)
	    SHLIB_CFLAGS="-fno-common"
	    SHLIB_LD="cc -dynamiclib \${LDFLAGS} -compatibility_version ${TCL_MAJOR_VERSION} -current_version \${VERSION} -install_name \${LIB_RUNTIME_DIR}/\${TCL_LIB_FILE}"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".dylib"
	    DL_OBJS="tclLoadDyld.o"
	    DL_LIBS=""
	    LDFLAGS=""
	    LD_SEARCH_FLAGS=""
	    CFLAGS_OPTIMIZE="-O3"
	    ;;
	NEXTSTEP-*)
	    SHLIB_CFLAGS=""
	    SHLIB_LD="cc -nostdlib -r"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadNext.o"
	    DL_LIBS=""
	    LDFLAGS=""
	    LD_SEARCH_FLAGS=""
	    ;;
	OS/390-*)
	    CFLAGS_OPTIMIZE=""      # Optimizer is buggy
	    AC_DEFINE(_OE_SOCKETS)  # needed in sys/socket.h
	    ;;      
	OSF1-1.0|OSF1-1.1|OSF1-1.2)
	    # OSF/1 1.[012] from OSF, and derivatives, including Paragon OSF/1
	    SHLIB_CFLAGS=""
	    # Hack: make package name same as library name
	    SHLIB_LD='ld -R -export $@:'
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadOSF.o"
	    DL_LIBS=""
	    LDFLAGS=""
	    LD_SEARCH_FLAGS=""
	    ;;
	OSF1-1.*)
	    # OSF/1 1.3 from OSF using ELF, and derivatives, including AD2
	    SHLIB_CFLAGS="-fPIC"
	    SHLIB_LD="ld -shared"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS=""
	    LDFLAGS=""
	    LD_SEARCH_FLAGS=""
	    ;;
	OSF1-V*)
	    # Digital OSF/1
	    SHLIB_CFLAGS=""
	    SHLIB_LD='ld -shared -expect_unresolved "*"'
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS=""
	    LDFLAGS=""
	    LD_SEARCH_FLAGS='-Wl,-rpath,${LIB_RUNTIME_DIR}'
	    if test "$using_gcc" = "no" ; then
		EXTRA_CFLAGS="-DHAVE_TZSET -std1"
	    fi
	    # see pthread_intro(3) for pthread support on osf1, k.furukawa
	    if test "${TCL_THREADS}" = "1" ; then
		EXTRA_CFLAGS="${EXTRA_CFLAGS} -DTCL_THREAD_STACK_MIN=PTHREAD_STACK_MIN*64"
		if test "$using_gcc" = "no" ; then
		    EXTRA_CFLAGS="${EXTRA_CFLAGS} -pthread"
		    LDFLAGS="-pthread"
		else
		    LIBS=`echo $LIBS | sed s/-lpthreads//`
		    LIBS="$LIBS -lpthread -lmach -lexc"
		fi
	    fi

	    ;;
	RISCos-*)
	    SHLIB_CFLAGS="-G 0"
	    SHLIB_LD="echo tclLdAout $CC \{$SHLIB_CFLAGS\} | `pwd`/tclsh -r -G 0"
	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".a"
	    DL_OBJS="tclLoadAout.o"
	    DL_LIBS=""
	    LDFLAGS="-Wl,-D,08000000"
	    LD_SEARCH_FLAGS='-L${LIB_RUNTIME_DIR}'
	    ;;
	SCO_SV-3.2*)
	    # Note, dlopen is available only on SCO 3.2.5 and greater. However,
	    # this test works, since "uname -s" was non-standard in 3.2.4 and
	    # below.
	    if test "$using_gcc" = "yes" ; then
	    	SHLIB_CFLAGS="-fPIC -melf"
	    	LDFLAGS="-melf -Wl,-Bexport"
	    else
	    	SHLIB_CFLAGS="-Kpic -belf"
	    	LDFLAGS="-belf -Wl,-Bexport"
	    fi
	    SHLIB_LD="ld -G"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS=""
	    LD_SEARCH_FLAGS=""
	    ;;
	SINIX*5.4*)
	    SHLIB_CFLAGS="-K PIC"
	    SHLIB_LD="cc -G"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    LDFLAGS=""
	    LD_SEARCH_FLAGS=""
	    ;;
	SunOS-4*)
	    SHLIB_CFLAGS="-PIC"
	    SHLIB_LD="ld"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    LDFLAGS=""
	    LD_SEARCH_FLAGS='-L${LIB_RUNTIME_DIR}'

	    # SunOS can't handle version numbers with dots in them in library
	    # specs, like -ltcl7.5, so use -ltcl75 instead.  Also, it
	    # requires an extra version number at the end of .so file names.
	    # So, the library has to have a name like libtcl75.so.1.0

	    SHARED_LIB_SUFFIX='${TCL_TRIM_DOTS}\$\{DBGX\}.so.1.0'
	    UNSHARED_LIB_SUFFIX='${TCL_TRIM_DOTS}\$\{DBGX\}.a'
	    TCL_LIB_VERSIONS_OK=nodots
	    ;;
	SunOS-5.[[0-6]]*)
	    SHLIB_CFLAGS="-KPIC"
	    SHLIB_LD="/usr/ccs/bin/ld -G -z text"

	    # Note: need the LIBS below, otherwise Tk won't find Tcl's
	    # symbols when dynamically loaded into tclsh.

	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    LDFLAGS=""
	    LD_SEARCH_FLAGS='-Wl,-R,${LIB_RUNTIME_DIR}'
	    ;;
	SunOS-5*)
	    SHLIB_CFLAGS="-KPIC"
	    SHLIB_LD="/usr/ccs/bin/ld -G -z text"
	    LDFLAGS=""
    
	    if test "$do64bit" = "yes" ; then
		arch=`isainfo`
		if test "$arch" = "sparcv9 sparc" ; then
			if test "$using_gcc" = "no" ; then
			    do64bit_ok=yes
			    if test "$do64bitVIS" = "yes" ; then
				EXTRA_CFLAGS="-xarch=v9a"
			    	LDFLAGS="-xarch=v9a"
			    else
				EXTRA_CFLAGS="-xarch=v9"
			    	LDFLAGS="-xarch=v9"
			    fi
			else 
			    AC_MSG_WARN("64bit mode not supported with GCC on $system")
			fi
		else
		    AC_MSG_WARN("64bit mode only supported sparcv9 system")
		fi
	    fi
	    
	    # Note: need the LIBS below, otherwise Tk won't find Tcl's
	    # symbols when dynamically loaded into tclsh.

	    SHLIB_LD_LIBS='${LIBS}'
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    if test "$using_gcc" = "yes" ; then
		LD_SEARCH_FLAGS='-Wl,-R,${LIB_RUNTIME_DIR}'
	    else
		LD_SEARCH_FLAGS='-R ${LIB_RUNTIME_DIR}'
	    fi
	    ;;
	ULTRIX-4.*)
	    SHLIB_CFLAGS="-G 0"
	    SHLIB_SUFFIX=".a"
	    SHLIB_LD="echo tclLdAout $CC \{$SHLIB_CFLAGS\} | `pwd`/tclsh -r -G 0"
	    SHLIB_LD_LIBS='${LIBS}'
	    DL_OBJS="tclLoadAout.o"
	    DL_LIBS=""
	    LDFLAGS="-Wl,-D,08000000"
	    LD_SEARCH_FLAGS='-L${LIB_RUNTIME_DIR}'
	    if test "$using_gcc" = "no" ; then
		EXTRA_CFLAGS="-DHAVE_TZSET -std1"
	    fi
	    ;;
	UNIX_SV* | UnixWare-5*)
	    SHLIB_CFLAGS="-KPIC"
	    SHLIB_LD="cc -G"
	    SHLIB_LD_LIBS=""
	    SHLIB_SUFFIX=".so"
	    DL_OBJS="tclLoadDl.o"
	    DL_LIBS="-ldl"
	    # Some UNIX_SV* systems (unixware 1.1.2 for example) have linkers
	    # that don't grok the -Bexport option.  Test that it does.
	    hold_ldflags=$LDFLAGS
	    AC_MSG_CHECKING(for ld accepts -Bexport flag)
	    LDFLAGS="${LDFLAGS} -Wl,-Bexport"
	    AC_TRY_LINK(, [int i;], found=yes, found=no)
	    LDFLAGS=$hold_ldflags
	    AC_MSG_RESULT($found)
	    if test $found = yes; then
	    LDFLAGS="-Wl,-Bexport"
	    else
	    LDFLAGS=""
	    fi
	    LD_SEARCH_FLAGS=""
	    ;;
    esac

    if test "$do64bit" = "yes" -a "$do64bit_ok" = "no" ; then
    AC_MSG_WARN("64bit support being disabled -- don\'t know magic for this platform")
    fi

    # Step 4: If pseudo-static linking is in use (see K. B. Kenny, "Dynamic
    # Loading for Tcl -- What Became of It?".  Proc. 2nd Tcl/Tk Workshop,
    # New Orleans, LA, Computerized Processes Unlimited, 1994), then we need
    # to determine which of several header files defines the a.out file
    # format (a.out.h, sys/exec.h, or sys/exec_aout.h).  At present, we
    # support only a file format that is more or less version-7-compatible. 
    # In particular,
    #	- a.out files must begin with `struct exec'.
    #	- the N_TXTOFF on the `struct exec' must compute the seek address
    #	  of the text segment
    #	- The `struct exec' must contain a_magic, a_text, a_data, a_bss
    #	  and a_entry fields.
    # The following compilation should succeed if and only if either sys/exec.h
    # or a.out.h is usable for the purpose.
    #
    # Note that the modified COFF format used on MIPS Ultrix 4.x is usable; the
    # `struct exec' includes a second header that contains information that
    # duplicates the v7 fields that are needed.

    if test "x$DL_OBJS" = "xtclLoadAout.o" ; then
	AC_MSG_CHECKING(sys/exec.h)
	AC_TRY_COMPILE([#include <sys/exec.h>],[
	    struct exec foo;
	    unsigned long seek;
	    int flag;
#if defined(__mips) || defined(mips)
	    seek = N_TXTOFF (foo.ex_f, foo.ex_o);
#else
	    seek = N_TXTOFF (foo);
#endif
	    flag = (foo.a_magic == OMAGIC);
	    return foo.a_text + foo.a_data + foo.a_bss + foo.a_entry;
    ], tcl_ok=usable, tcl_ok=unusable)
	AC_MSG_RESULT($tcl_ok)
	if test $tcl_ok = usable; then
	    AC_DEFINE(USE_SYS_EXEC_H)
	else
	    AC_MSG_CHECKING(a.out.h)
	    AC_TRY_COMPILE([#include <a.out.h>],[
		struct exec foo;
		unsigned long seek;
		int flag;
#if defined(__mips) || defined(mips)
		seek = N_TXTOFF (foo.ex_f, foo.ex_o);
#else
		seek = N_TXTOFF (foo);
#endif
		flag = (foo.a_magic == OMAGIC);
		return foo.a_text + foo.a_data + foo.a_bss + foo.a_entry;
	    ], tcl_ok=usable, tcl_ok=unusable)
	    AC_MSG_RESULT($tcl_ok)
	    if test $tcl_ok = usable; then
		AC_DEFINE(USE_A_OUT_H)
	    else
		AC_MSG_CHECKING(sys/exec_aout.h)
		AC_TRY_COMPILE([#include <sys/exec_aout.h>],[
		    struct exec foo;
		    unsigned long seek;
		    int flag;
#if defined(__mips) || defined(mips)
		    seek = N_TXTOFF (foo.ex_f, foo.ex_o);
#else
		    seek = N_TXTOFF (foo);
#endif
		    flag = (foo.a_midmag == OMAGIC);
		    return foo.a_text + foo.a_data + foo.a_bss + foo.a_entry;
		], tcl_ok=usable, tcl_ok=unusable)
		AC_MSG_RESULT($tcl_ok)
		if test $tcl_ok = usable; then
		    AC_DEFINE(USE_SYS_EXEC_AOUT_H)
		else
		    DL_OBJS=""
		fi
	    fi
	fi
    fi

    # Step 5: disable dynamic loading if requested via a command-line switch.

    AC_ARG_ENABLE(load, [  --disable-load          disallow dynamic loading and "load" command],
	[tcl_ok=$enableval], [tcl_ok=yes])
    if test "$tcl_ok" = "no"; then
	DL_OBJS=""
    fi

    if test "x$DL_OBJS" != "x" ; then
	BUILD_DLTEST="\$(DLTEST_TARGETS)"
    else
	echo "Can't figure out how to do dynamic loading or shared libraries"
	echo "on this system."
	SHLIB_CFLAGS=""
	SHLIB_LD=""
	SHLIB_SUFFIX=""
	DL_OBJS="tclLoadNone.o"
	DL_LIBS=""
	LDFLAGS=""
	LD_SEARCH_FLAGS=""
	BUILD_DLTEST=""
    fi

    # If we're running gcc, then change the C flags for compiling shared
    # libraries to the right flags for gcc, instead of those for the
    # standard manufacturer compiler.

    if test "$DL_OBJS" != "tclLoadNone.o" ; then
	if test "$using_gcc" = "yes" ; then
	    case $system in
		AIX-*)
		    ;;
		BSD/OS*)
		    ;;
		IRIX*)
		    ;;
		NetBSD-*|FreeBSD-*|OpenBSD-*)
		    ;;
		Rhapsody-*|Darwin-*)
		    ;;
		RISCos-*)
		    ;;
		SCO_SV-3.2*)
		    ;;
		ULTRIX-4.*)
		    ;;
		*)
		    SHLIB_CFLAGS="-fPIC"
		    ;;
	    esac
	fi
    fi

    if test "$SHARED_LIB_SUFFIX" = "" ; then
	SHARED_LIB_SUFFIX='${VERSION}\$\{DBGX\}${SHLIB_SUFFIX}'
    fi
    if test "$UNSHARED_LIB_SUFFIX" = "" ; then
	UNSHARED_LIB_SUFFIX='${VERSION}\$\{DBGX\}.a'
    fi

    AC_SUBST(DL_LIBS)
    AC_SUBST(CFLAGS_DEBUG)
    AC_SUBST(CFLAGS_OPTIMIZE)
    AC_SUBST(CFLAGS_WARNING)
])

#--------------------------------------------------------------------
# SC_SERIAL_PORT
#
#	Determine which interface to use to talk to the serial port.
#	Note that #include lines must begin in leftmost column for
#	some compilers to recognize them as preprocessor directives.
#
# Arguments:
#	none
#	
# Results:
#
#	Defines only one of the following vars:
#		USE_TERMIOS
#		USE_TERMIO
#		USE_SGTTY
#
#--------------------------------------------------------------------

AC_DEFUN(SC_SERIAL_PORT, [
    AC_MSG_CHECKING([termios vs. termio vs. sgtty])

    AC_TRY_RUN([
#include <termios.h>

main()
{
    struct termios t;
    if (tcgetattr(0, &t) == 0) {
	cfsetospeed(&t, 0);
	t.c_cflag |= PARENB | PARODD | CSIZE | CSTOPB;
	return 0;
    }
    return 1;
}], tk_ok=termios, tk_ok=no, tk_ok=no)

    if test $tk_ok = termios; then
	AC_DEFINE(USE_TERMIOS)
    else
	AC_TRY_RUN([
#include <termio.h>

main()
{
    struct termio t;
    if (ioctl(0, TCGETA, &t) == 0) {
	t.c_cflag |= CBAUD | PARENB | PARODD | CSIZE | CSTOPB;
	return 0;
    }
    return 1;
    }], tk_ok=termio, tk_ok=no, tk_ok=no)

    if test $tk_ok = termio; then
	AC_DEFINE(USE_TERMIO)
    else
	AC_TRY_RUN([
#include <sgtty.h>

main()
{
    struct sgttyb t;
    if (ioctl(0, TIOCGETP, &t) == 0) {
	t.sg_ospeed = 0;
	t.sg_flags |= ODDP | EVENP | RAW;
	return 0;
    }
    return 1;
}], tk_ok=sgtty, tk_ok=none, tk_ok=none)

    if test $tk_ok = sgtty; then
	AC_DEFINE(USE_SGTTY)
    else
	AC_TRY_RUN([
#include <termios.h>
#include <errno.h>

main()
{
    struct termios t;
    if (tcgetattr(0, &t) == 0
	|| errno == ENOTTY || errno == ENXIO || errno == EINVAL) {
	cfsetospeed(&t, 0);
	t.c_cflag |= PARENB | PARODD | CSIZE | CSTOPB;
	return 0;
    }
    return 1;
}], tk_ok=termios, tk_ok=no, tk_ok=no)

    if test $tk_ok = termios; then
	AC_DEFINE(USE_TERMIOS)
    else
	AC_TRY_RUN([
#include <termio.h>
#include <errno.h>

main()
{
    struct termio t;
    if (ioctl(0, TCGETA, &t) == 0
	|| errno == ENOTTY || errno == ENXIO || errno == EINVAL) {
	t.c_cflag |= CBAUD | PARENB | PARODD | CSIZE | CSTOPB;
	return 0;
    }
    return 1;
    }], tk_ok=termio, tk_ok=no, tk_ok=no)

    if test $tk_ok = termio; then
	AC_DEFINE(USE_TERMIO)
    else
	AC_TRY_RUN([
#include <sgtty.h>
#include <errno.h>

main()
{
    struct sgttyb t;
    if (ioctl(0, TIOCGETP, &t) == 0
	|| errno == ENOTTY || errno == ENXIO || errno == EINVAL) {
	t.sg_ospeed = 0;
	t.sg_flags |= ODDP | EVENP | RAW;
	return 0;
    }
    return 1;
}], tk_ok=sgtty, tk_ok=none, tk_ok=none)

    if test $tk_ok = sgtty; then
	AC_DEFINE(USE_SGTTY)
    fi
    fi
    fi
    fi
    fi
    fi
    AC_MSG_RESULT($tk_ok)
])

#--------------------------------------------------------------------
# SC_MISSING_POSIX_HEADERS
#
#	Supply substitutes for missing POSIX header files.  Special
#	notes:
#	    - stdlib.h doesn't define strtol, strtoul, or
#	      strtod insome versions of SunOS
#	    - some versions of string.h don't declare procedures such
#	      as strstr
#
# Arguments:
#	none
#	
# Results:
#
#	Defines some of the following vars:
#		NO_DIRENT_H
#		NO_ERRNO_H
#		NO_VALUES_H
#		NO_LIMITS_H
#		NO_STDLIB_H
#		NO_STRING_H
#		NO_SYS_WAIT_H
#		NO_DLFCN_H
#		HAVE_UNISTD_H
#		HAVE_SYS_PARAM_H
#
#		HAVE_STRING_H ?
#
#--------------------------------------------------------------------

AC_DEFUN(SC_MISSING_POSIX_HEADERS, [

    AC_MSG_CHECKING(dirent.h)
    AC_TRY_LINK([#include <sys/types.h>
#include <dirent.h>], [
#ifndef _POSIX_SOURCE
#   ifdef __Lynx__
	/*
	 * Generate compilation error to make the test fail:  Lynx headers
	 * are only valid if really in the POSIX environment.
	 */

	missing_procedure();
#   endif
#endif
DIR *d;
struct dirent *entryPtr;
char *p;
d = opendir("foobar");
entryPtr = readdir(d);
p = entryPtr->d_name;
closedir(d);
], tcl_ok=yes, tcl_ok=no)

    if test $tcl_ok = no; then
	AC_DEFINE(NO_DIRENT_H)
    fi

    AC_MSG_RESULT($tcl_ok)
    AC_CHECK_HEADER(errno.h, , [AC_DEFINE(NO_ERRNO_H)])
    AC_CHECK_HEADER(float.h, , [AC_DEFINE(NO_FLOAT_H)])
    AC_CHECK_HEADER(values.h, , [AC_DEFINE(NO_VALUES_H)])
    AC_CHECK_HEADER(limits.h, , [AC_DEFINE(NO_LIMITS_H)])
    AC_CHECK_HEADER(stdlib.h, tcl_ok=1, tcl_ok=0)
    AC_EGREP_HEADER(strtol, stdlib.h, , tcl_ok=0)
    AC_EGREP_HEADER(strtoul, stdlib.h, , tcl_ok=0)
    AC_EGREP_HEADER(strtod, stdlib.h, , tcl_ok=0)
    if test $tcl_ok = 0; then
	AC_DEFINE(NO_STDLIB_H)
    fi
    AC_CHECK_HEADER(string.h, tcl_ok=1, tcl_ok=0)
    AC_EGREP_HEADER(strstr, string.h, , tcl_ok=0)
    AC_EGREP_HEADER(strerror, string.h, , tcl_ok=0)

    # See also memmove check below for a place where NO_STRING_H can be
    # set and why.

    if test $tcl_ok = 0; then
	AC_DEFINE(NO_STRING_H)
    fi

    AC_CHECK_HEADER(sys/wait.h, , [AC_DEFINE(NO_SYS_WAIT_H)])
    AC_CHECK_HEADER(dlfcn.h, , [AC_DEFINE(NO_DLFCN_H)])

    # OS/390 lacks sys/param.h (and doesn't need it, by chance).

    AC_HAVE_HEADERS(unistd.h sys/param.h)

])

#--------------------------------------------------------------------
# SC_PATH_X
#
#	Locate the X11 header files and the X11 library archive.  Try
#	the ac_path_x macro first, but if it doesn't find the X stuff
#	(e.g. because there's no xmkmf program) then check through
#	a list of possible directories.  Under some conditions the
#	autoconf macro will return an include directory that contains
#	no include files, so double-check its result just to be safe.
#
# Arguments:
#	none
#	
# Results:
#
#	Sets the the following vars:
#		XINCLUDES
#		XLIBSW
#
#--------------------------------------------------------------------

AC_DEFUN(SC_PATH_X, [
    AC_PATH_X
    not_really_there=""
    if test "$no_x" = ""; then
	if test "$x_includes" = ""; then
	    AC_TRY_CPP([#include <X11/XIntrinsic.h>], , not_really_there="yes")
	else
	    if test ! -r $x_includes/X11/Intrinsic.h; then
		not_really_there="yes"
	    fi
	fi
    fi
    if test "$no_x" = "yes" -o "$not_really_there" = "yes"; then
	AC_MSG_CHECKING(for X11 header files)
	XINCLUDES="# no special path needed"
	AC_TRY_CPP([#include <X11/Intrinsic.h>], , XINCLUDES="nope")
	if test "$XINCLUDES" = nope; then
	    dirs="/usr/unsupported/include /usr/local/include /usr/X386/include /usr/X11R6/include /usr/X11R5/include /usr/include/X11R5 /usr/include/X11R4 /usr/openwin/include /usr/X11/include /usr/sww/include"
	    for i in $dirs ; do
		if test -r $i/X11/Intrinsic.h; then
		    AC_MSG_RESULT($i)
		    XINCLUDES=" -I$i"
		    break
		fi
	    done
	fi
    else
	if test "$x_includes" != ""; then
	    XINCLUDES=-I$x_includes
	else
	    XINCLUDES="# no special path needed"
	fi
    fi
    if test "$XINCLUDES" = nope; then
	AC_MSG_RESULT(couldn't find any!)
	XINCLUDES="# no include files found"
    fi

    if test "$no_x" = yes; then
	AC_MSG_CHECKING(for X11 libraries)
	XLIBSW=nope
	dirs="/usr/unsupported/lib /usr/local/lib /usr/X386/lib /usr/X11R6/lib /usr/X11R5/lib /usr/lib/X11R5 /usr/lib/X11R4 /usr/openwin/lib /usr/X11/lib /usr/sww/X11/lib"
	for i in $dirs ; do
	    if test -r $i/libX11.a -o -r $i/libX11.so -o -r $i/libX11.sl; then
		AC_MSG_RESULT($i)
		XLIBSW="-L$i -lX11"
		x_libraries="$i"
		break
	    fi
	done
    else
	if test "$x_libraries" = ""; then
	    XLIBSW=-lX11
	else
	    XLIBSW="-L$x_libraries -lX11"
	fi
    fi
    if test "$XLIBSW" = nope ; then
	AC_CHECK_LIB(Xwindow, XCreateWindow, XLIBSW=-lXwindow)
    fi
    if test "$XLIBSW" = nope ; then
	AC_MSG_RESULT(couldn't find any!  Using -lX11.)
	XLIBSW=-lX11
    fi
])
#--------------------------------------------------------------------
# SC_BLOCKING_STYLE
#
#	The statements below check for systems where POSIX-style
#	non-blocking I/O (O_NONBLOCK) doesn't work or is unimplemented. 
#	On these systems (mostly older ones), use the old BSD-style
#	FIONBIO approach instead.
#
# Arguments:
#	none
#	
# Results:
#
#	Defines some of the following vars:
#		HAVE_SYS_IOCTL_H
#		HAVE_SYS_FILIO_H
#		USE_FIONBIO
#		O_NONBLOCK
#
#--------------------------------------------------------------------

AC_DEFUN(SC_BLOCKING_STYLE, [
    AC_CHECK_HEADERS(sys/ioctl.h)
    AC_CHECK_HEADERS(sys/filio.h)
    AC_MSG_CHECKING([FIONBIO vs. O_NONBLOCK for nonblocking I/O])
    if test -f /usr/lib/NextStep/software_version; then
	system=NEXTSTEP-`awk '/3/,/3/' /usr/lib/NextStep/software_version`
    else
	system=`uname -s`-`uname -r`
	if test "$?" -ne 0 ; then
	    system=unknown
	else
	    # Special check for weird MP-RAS system (uname returns weird
	    # results, and the version is kept in special file).
	
	    if test -r /etc/.relid -a "X`uname -n`" = "X`uname -s`" ; then
		system=MP-RAS-`awk '{print $3}' /etc/.relid'`
	    fi
	    if test "`uname -s`" = "AIX" ; then
		system=AIX-`uname -v`.`uname -r`
	    fi
	fi
    fi
    case $system in
	# There used to be code here to use FIONBIO under AIX.  However, it
	# was reported that FIONBIO doesn't work under AIX 3.2.5.  Since
	# using O_NONBLOCK seems fine under AIX 4.*, I removed the FIONBIO
	# code (JO, 5/31/97).

	OSF*)
	    AC_DEFINE(USE_FIONBIO)
	    AC_MSG_RESULT(FIONBIO)
	    ;;
	SunOS-4*)
	    AC_DEFINE(USE_FIONBIO)
	    AC_MSG_RESULT(FIONBIO)
	    ;;
	ULTRIX-4.*)
	    AC_DEFINE(USE_FIONBIO)
	    AC_MSG_RESULT(FIONBIO)
	    ;;
	*)
	    AC_MSG_RESULT(O_NONBLOCK)
	    ;;
    esac
])

#--------------------------------------------------------------------
# SC_TIME_HANLDER
#
#	Checks how the system deals with time.h, what time structures
#	are used on the system, and what fields the structures have.
#
# Arguments:
#	none
#	
# Results:
#
#	Defines some of the following vars:
#		USE_DELTA_FOR_TZ
#		HAVE_TM_GMTOFF
#		HAVE_TM_TZADJ
#		HAVE_TIMEZONE_VAR
#
#--------------------------------------------------------------------

AC_DEFUN(SC_TIME_HANDLER, [
    AC_CHECK_HEADERS(sys/time.h)
    AC_HEADER_TIME
    AC_STRUCT_TIMEZONE

    AC_MSG_CHECKING([tm_tzadj in struct tm])
    AC_TRY_COMPILE([#include <time.h>], [struct tm tm; tm.tm_tzadj;],
	    [AC_DEFINE(HAVE_TM_TZADJ)
	    AC_MSG_RESULT(yes)],
	    AC_MSG_RESULT(no))

    AC_MSG_CHECKING([tm_gmtoff in struct tm])
    AC_TRY_COMPILE([#include <time.h>], [struct tm tm; tm.tm_gmtoff;],
	    [AC_DEFINE(HAVE_TM_GMTOFF)
	    AC_MSG_RESULT(yes)],
	    AC_MSG_RESULT(no))

    #
    # Its important to include time.h in this check, as some systems
    # (like convex) have timezone functions, etc.
    #
    have_timezone=no
    AC_MSG_CHECKING([long timezone variable])
    AC_TRY_COMPILE([#include <time.h>],
	    [extern long timezone;
	    timezone += 1;
	    exit (0);],
	    [have_timezone=yes
	    AC_DEFINE(HAVE_TIMEZONE_VAR)
	    AC_MSG_RESULT(yes)],
	    AC_MSG_RESULT(no))

    #
    # On some systems (eg IRIX 6.2), timezone is a time_t and not a long.
    #
    if test "$have_timezone" = no; then
    AC_MSG_CHECKING([time_t timezone variable])
    AC_TRY_COMPILE([#include <time.h>],
	    [extern time_t timezone;
	    timezone += 1;
	    exit (0);],
	    [AC_DEFINE(HAVE_TIMEZONE_VAR)
	    AC_MSG_RESULT(yes)],
	    AC_MSG_RESULT(no))
    fi

])

#--------------------------------------------------------------------
# SC_BUGGY_STRTOD
#
#	Under Solaris 2.4, strtod returns the wrong value for the
#	terminating character under some conditions.  Check for this
#	and if the problem exists use a substitute procedure
#	"fixstrtod" (provided by Tcl) that corrects the error.
#	Also, on Compaq's Tru64 Unix 5.0,
#	strtod(" ") returns 0.0 instead of a failure to convert.
#
# Arguments:
#	none
#	
# Results:
#
#	Might defines some of the following vars:
#		strtod (=fixstrtod)
#
#--------------------------------------------------------------------

AC_DEFUN(SC_BUGGY_STRTOD, [
    AC_CHECK_FUNC(strtod, tcl_strtod=1, tcl_strtod=0)
    if test "$tcl_strtod" = 1; then
	AC_MSG_CHECKING([for Solaris2.4/Tru64 strtod bugs])
	AC_TRY_RUN([
	    extern double strtod();
	    int main()
	    {
		char *string = "NaN", *spaceString = " ";
		char *term;
		double value;
		value = strtod(string, &term);
		if ((term != string) && (term[-1] == 0)) {
		    exit(1);
		}
		value = strtod(spaceString, &term);
		if (term == (spaceString+1)) {
		    exit(1);
		}
		exit(0);
	    }], tcl_ok=1, tcl_ok=0, tcl_ok=0)
	if test "$tcl_ok" = 1; then
	    AC_MSG_RESULT(ok)
	else
	    AC_MSG_RESULT(buggy)
	    LIBOBJS="$LIBOBJS fixstrtod.o"
	    AC_DEFINE(strtod, fixstrtod)
	fi
    fi
])

#--------------------------------------------------------------------
# SC_TCL_LINK_LIBS
#
#	Search for the libraries needed to link the Tcl shell.
#	Things like the math library (-lm) and socket stuff (-lsocket vs.
#	-lnsl) are dealt with here.
#
# Arguments:
#	Requires the following vars to be set in the Makefile:
#		DL_LIBS
#		LIBS
#		MATH_LIBS
#	
# Results:
#
#	Subst's the following var:
#		TCL_LIBS
#		MATH_LIBS
#
#	Might append to the following vars:
#		LIBS
#
#	Might define the following vars:
#		HAVE_NET_ERRNO_H
#
#--------------------------------------------------------------------

AC_DEFUN(SC_TCL_LINK_LIBS, [
    #--------------------------------------------------------------------
    # On a few very rare systems, all of the libm.a stuff is
    # already in libc.a.  Set compiler flags accordingly.
    # Also, Linux requires the "ieee" library for math to work
    # right (and it must appear before "-lm").
    #--------------------------------------------------------------------

    AC_CHECK_FUNC(sin, MATH_LIBS="", MATH_LIBS="-lm")
    AC_CHECK_LIB(ieee, main, [MATH_LIBS="-lieee $MATH_LIBS"])

    #--------------------------------------------------------------------
    # Interactive UNIX requires -linet instead of -lsocket, plus it
    # needs net/errno.h to define the socket-related error codes.
    #--------------------------------------------------------------------

    AC_CHECK_LIB(inet, main, [LIBS="$LIBS -linet"])
    AC_CHECK_HEADER(net/errno.h, [AC_DEFINE(HAVE_NET_ERRNO_H)])

    #--------------------------------------------------------------------
    #	Check for the existence of the -lsocket and -lnsl libraries.
    #	The order here is important, so that they end up in the right
    #	order in the command line generated by make.  Here are some
    #	special considerations:
    #	1. Use "connect" and "accept" to check for -lsocket, and
    #	   "gethostbyname" to check for -lnsl.
    #	2. Use each function name only once:  can't redo a check because
    #	   autoconf caches the results of the last check and won't redo it.
    #	3. Use -lnsl and -lsocket only if they supply procedures that
    #	   aren't already present in the normal libraries.  This is because
    #	   IRIX 5.2 has libraries, but they aren't needed and they're
    #	   bogus:  they goof up name resolution if used.
    #	4. On some SVR4 systems, can't use -lsocket without -lnsl too.
    #	   To get around this problem, check for both libraries together
    #	   if -lsocket doesn't work by itself.
    #--------------------------------------------------------------------

    tcl_checkBoth=0
    AC_CHECK_FUNC(connect, tcl_checkSocket=0, tcl_checkSocket=1)
    if test "$tcl_checkSocket" = 1; then
	AC_CHECK_FUNC(setsockopt, , [AC_CHECK_LIB(socket, setsockopt,
	    LIBS="$LIBS -lsocket", tcl_checkBoth=1)])
    fi
    if test "$tcl_checkBoth" = 1; then
	tk_oldLibs=$LIBS
	LIBS="$LIBS -lsocket -lnsl"
	AC_CHECK_FUNC(accept, tcl_checkNsl=0, [LIBS=$tk_oldLibs])
    fi
    AC_CHECK_FUNC(gethostbyname, , [AC_CHECK_LIB(nsl, gethostbyname,
	    [LIBS="$LIBS -lnsl"])])
    
    # Don't perform the eval of the libraries here because DL_LIBS
    # won't be set until we call SC_CONFIG_CFLAGS

    TCL_LIBS='${DL_LIBS} ${LIBS} ${MATH_LIBS}'
    AC_SUBST(TCL_LIBS)
    AC_SUBST(MATH_LIBS)
])

# Do all the work for Automake.                            -*- Autoconf -*-

# This macro actually does too much some checks are only needed if
# your package does certain things.  But this isn't really a big deal.

# Copyright 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003
# Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 9

# There are a few dirty hacks below to avoid letting `AC_PROG_CC' be
# written in clear, in which case automake, when reading aclocal.m4,
# will think it sees a *use*, and therefore will trigger all it's
# C support machinery.  Also note that it means that autoscan, seeing
# CC etc. in the Makefile, will ask for an AC_PROG_CC use...


AC_PREREQ([2.54])

# Autoconf 2.50 wants to disallow AM_ names.  We explicitly allow
# the ones we care about.
m4_pattern_allow([^AM_[A-Z]+FLAGS$])dnl

# AM_INIT_AUTOMAKE(PACKAGE, VERSION, [NO-DEFINE])
# AM_INIT_AUTOMAKE([OPTIONS])
# -----------------------------------------------
# The call with PACKAGE and VERSION arguments is the old style
# call (pre autoconf-2.50), which is being phased out.  PACKAGE
# and VERSION should now be passed to AC_INIT and removed from
# the call to AM_INIT_AUTOMAKE.
# We support both call styles for the transition.  After
# the next Automake release, Autoconf can make the AC_INIT
# arguments mandatory, and then we can depend on a new Autoconf
# release and drop the old call support.
AC_DEFUN([AM_INIT_AUTOMAKE],
[AC_REQUIRE([AM_SET_CURRENT_AUTOMAKE_VERSION])dnl
 AC_REQUIRE([AC_PROG_INSTALL])dnl
# test to see if srcdir already configured
if test "`cd $srcdir && pwd`" != "`pwd`" &&
   test -f $srcdir/config.status; then
  AC_MSG_ERROR([source directory already configured; run "make distclean" there first])
fi

# test whether we have cygpath
if test -z "$CYGPATH_W"; then
  if (cygpath --version) >/dev/null 2>/dev/null; then
    CYGPATH_W='cygpath -w'
  else
    CYGPATH_W=echo
  fi
fi
AC_SUBST([CYGPATH_W])

# Define the identity of the package.
dnl Distinguish between old-style and new-style calls.
m4_ifval([$2],
[m4_ifval([$3], [_AM_SET_OPTION([no-define])])dnl
 AC_SUBST([PACKAGE], [$1])dnl
 AC_SUBST([VERSION], [$2])],
[_AM_SET_OPTIONS([$1])dnl
 AC_SUBST([PACKAGE], ['AC_PACKAGE_TARNAME'])dnl
 AC_SUBST([VERSION], ['AC_PACKAGE_VERSION'])])dnl

_AM_IF_OPTION([no-define],,
[AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
 AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version number of package])])dnl

# Some tools Automake needs.
AC_REQUIRE([AM_SANITY_CHECK])dnl
AC_REQUIRE([AC_ARG_PROGRAM])dnl
AM_MISSING_PROG(ACLOCAL, aclocal-${am__api_version})
AM_MISSING_PROG(AUTOCONF, autoconf)
AM_MISSING_PROG(AUTOMAKE, automake-${am__api_version})
AM_MISSING_PROG(AUTOHEADER, autoheader)
AM_MISSING_PROG(MAKEINFO, makeinfo)
AM_MISSING_PROG(AMTAR, tar)
AM_PROG_INSTALL_SH
AM_PROG_INSTALL_STRIP
# We need awk for the "check" target.  The system "awk" is bad on
# some platforms.
AC_REQUIRE([AC_PROG_AWK])dnl
AC_REQUIRE([AC_PROG_MAKE_SET])dnl
AC_REQUIRE([AM_SET_LEADING_DOT])dnl

_AM_IF_OPTION([no-dependencies],,
[AC_PROVIDE_IFELSE([AC_PROG_CC],
                  [_AM_DEPENDENCIES(CC)],
                  [define([AC_PROG_CC],
                          defn([AC_PROG_CC])[_AM_DEPENDENCIES(CC)])])dnl
AC_PROVIDE_IFELSE([AC_PROG_CXX],
                  [_AM_DEPENDENCIES(CXX)],
                  [define([AC_PROG_CXX],
                          defn([AC_PROG_CXX])[_AM_DEPENDENCIES(CXX)])])dnl
])
])


# When config.status generates a header, we must update the stamp-h file.
# This file resides in the same directory as the config header
# that is generated.  The stamp files are numbered to have different names.

# Autoconf calls _AC_AM_CONFIG_HEADER_HOOK (when defined) in the
# loop where config.status creates the headers, so we can generate
# our stamp files there.
AC_DEFUN([_AC_AM_CONFIG_HEADER_HOOK],
[# Compute $1's index in $config_headers.
_am_stamp_count=1
for _am_header in $config_headers :; do
  case $_am_header in
    $1 | $1:* )
      break ;;
    * )
      _am_stamp_count=`expr $_am_stamp_count + 1` ;;
  esac
done
echo "timestamp for $1" >`AS_DIRNAME([$1])`/stamp-h[]$_am_stamp_count])

# Copyright 2002  Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA

# AM_AUTOMAKE_VERSION(VERSION)
# ----------------------------
# Automake X.Y traces this macro to ensure aclocal.m4 has been
# generated from the m4 files accompanying Automake X.Y.
AC_DEFUN([AM_AUTOMAKE_VERSION],[am__api_version="1.7"])

# AM_SET_CURRENT_AUTOMAKE_VERSION
# -------------------------------
# Call AM_AUTOMAKE_VERSION so it can be traced.
# This function is AC_REQUIREd by AC_INIT_AUTOMAKE.
AC_DEFUN([AM_SET_CURRENT_AUTOMAKE_VERSION],
	 [AM_AUTOMAKE_VERSION([1.7.3])])

# Helper functions for option handling.                    -*- Autoconf -*-

# Copyright 2001, 2002  Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 2

# _AM_MANGLE_OPTION(NAME)
# -----------------------
AC_DEFUN([_AM_MANGLE_OPTION],
[[_AM_OPTION_]m4_bpatsubst($1, [[^a-zA-Z0-9_]], [_])])

# _AM_SET_OPTION(NAME)
# ------------------------------
# Set option NAME.  Presently that only means defining a flag for this option.
AC_DEFUN([_AM_SET_OPTION],
[m4_define(_AM_MANGLE_OPTION([$1]), 1)])

# _AM_SET_OPTIONS(OPTIONS)
# ----------------------------------
# OPTIONS is a space-separated list of Automake options.
AC_DEFUN([_AM_SET_OPTIONS],
[AC_FOREACH([_AM_Option], [$1], [_AM_SET_OPTION(_AM_Option)])])

# _AM_IF_OPTION(OPTION, IF-SET, [IF-NOT-SET])
# -------------------------------------------
# Execute IF-SET if OPTION is set, IF-NOT-SET otherwise.
AC_DEFUN([_AM_IF_OPTION],
[m4_ifset(_AM_MANGLE_OPTION([$1]), [$2], [$3])])

#
# Check to make sure that the build environment is sane.
#

# Copyright 1996, 1997, 2000, 2001 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 3

# AM_SANITY_CHECK
# ---------------
AC_DEFUN([AM_SANITY_CHECK],
[AC_MSG_CHECKING([whether build environment is sane])
# Just in case
sleep 1
echo timestamp > conftest.file
# Do `set' in a subshell so we don't clobber the current shell's
# arguments.  Must try -L first in case configure is actually a
# symlink; some systems play weird games with the mod time of symlinks
# (eg FreeBSD returns the mod time of the symlink's containing
# directory).
if (
   set X `ls -Lt $srcdir/configure conftest.file 2> /dev/null`
   if test "$[*]" = "X"; then
      # -L didn't work.
      set X `ls -t $srcdir/configure conftest.file`
   fi
   rm -f conftest.file
   if test "$[*]" != "X $srcdir/configure conftest.file" \
      && test "$[*]" != "X conftest.file $srcdir/configure"; then

      # If neither matched, then we have a broken ls.  This can happen
      # if, for instance, CONFIG_SHELL is bash and it inherits a
      # broken ls alias from the environment.  This has actually
      # happened.  Such a system could not be considered "sane".
      AC_MSG_ERROR([ls -t appears to fail.  Make sure there is not a broken
alias in your environment])
   fi

   test "$[2]" = conftest.file
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly created file is older than distributed files!
Check your system clock])
fi
AC_MSG_RESULT(yes)])

#  -*- Autoconf -*-


# Copyright 1997, 1999, 2000, 2001 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 3

# AM_MISSING_PROG(NAME, PROGRAM)
# ------------------------------
AC_DEFUN([AM_MISSING_PROG],
[AC_REQUIRE([AM_MISSING_HAS_RUN])
$1=${$1-"${am_missing_run}$2"}
AC_SUBST($1)])


# AM_MISSING_HAS_RUN
# ------------------
# Define MISSING if not defined so far and test if it supports --run.
# If it does, set am_missing_run to use it, otherwise, to nothing.
AC_DEFUN([AM_MISSING_HAS_RUN],
[AC_REQUIRE([AM_AUX_DIR_EXPAND])dnl
test x"${MISSING+set}" = xset || MISSING="\${SHELL} $am_aux_dir/missing"
# Use eval to expand $SHELL
if eval "$MISSING --run true"; then
  am_missing_run="$MISSING --run "
else
  am_missing_run=
  AC_MSG_WARN([`missing' script is too old or missing])
fi
])

# AM_AUX_DIR_EXPAND

# Copyright 2001 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# For projects using AC_CONFIG_AUX_DIR([foo]), Autoconf sets
# $ac_aux_dir to `$srcdir/foo'.  In other projects, it is set to
# `$srcdir', `$srcdir/..', or `$srcdir/../..'.
#
# Of course, Automake must honor this variable whenever it calls a
# tool from the auxiliary directory.  The problem is that $srcdir (and
# therefore $ac_aux_dir as well) can be either absolute or relative,
# depending on how configure is run.  This is pretty annoying, since
# it makes $ac_aux_dir quite unusable in subdirectories: in the top
# source directory, any form will work fine, but in subdirectories a
# relative path needs to be adjusted first.
#
# $ac_aux_dir/missing
#    fails when called from a subdirectory if $ac_aux_dir is relative
# $top_srcdir/$ac_aux_dir/missing
#    fails if $ac_aux_dir is absolute,
#    fails when called from a subdirectory in a VPATH build with
#          a relative $ac_aux_dir
#
# The reason of the latter failure is that $top_srcdir and $ac_aux_dir
# are both prefixed by $srcdir.  In an in-source build this is usually
# harmless because $srcdir is `.', but things will broke when you
# start a VPATH build or use an absolute $srcdir.
#
# So we could use something similar to $top_srcdir/$ac_aux_dir/missing,
# iff we strip the leading $srcdir from $ac_aux_dir.  That would be:
#   am_aux_dir='\$(top_srcdir)/'`expr "$ac_aux_dir" : "$srcdir//*\(.*\)"`
# and then we would define $MISSING as
#   MISSING="\${SHELL} $am_aux_dir/missing"
# This will work as long as MISSING is not called from configure, because
# unfortunately $(top_srcdir) has no meaning in configure.
# However there are other variables, like CC, which are often used in
# configure, and could therefore not use this "fixed" $ac_aux_dir.
#
# Another solution, used here, is to always expand $ac_aux_dir to an
# absolute PATH.  The drawback is that using absolute paths prevent a
# configured tree to be moved without reconfiguration.

# Rely on autoconf to set up CDPATH properly.
AC_PREREQ([2.50])

AC_DEFUN([AM_AUX_DIR_EXPAND], [
# expand $ac_aux_dir to an absolute path
am_aux_dir=`cd $ac_aux_dir && pwd`
])

# AM_PROG_INSTALL_SH
# ------------------
# Define $install_sh.

# Copyright 2001 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

AC_DEFUN([AM_PROG_INSTALL_SH],
[AC_REQUIRE([AM_AUX_DIR_EXPAND])dnl
install_sh=${install_sh-"$am_aux_dir/install-sh"}
AC_SUBST(install_sh)])

# AM_PROG_INSTALL_STRIP

# Copyright 2001 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# One issue with vendor `install' (even GNU) is that you can't
# specify the program used to strip binaries.  This is especially
# annoying in cross-compiling environments, where the build's strip
# is unlikely to handle the host's binaries.
# Fortunately install-sh will honor a STRIPPROG variable, so we
# always use install-sh in `make install-strip', and initialize
# STRIPPROG with the value of the STRIP variable (set by the user).
AC_DEFUN([AM_PROG_INSTALL_STRIP],
[AC_REQUIRE([AM_PROG_INSTALL_SH])dnl
# Installed binaries are usually stripped using `strip' when the user
# run `make install-strip'.  However `strip' might not be the right
# tool to use in cross-compilation environments, therefore Automake
# will honor the `STRIP' environment variable to overrule this program.
dnl Don't test for $cross_compiling = yes, because it might be `maybe'.
if test "$cross_compiling" != no; then
  AC_CHECK_TOOL([STRIP], [strip], :)
fi
INSTALL_STRIP_PROGRAM="\${SHELL} \$(install_sh) -c -s"
AC_SUBST([INSTALL_STRIP_PROGRAM])])

#                                                          -*- Autoconf -*-
# Copyright (C) 2003  Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 1

# Check whether the underlying file-system supports filenames
# with a leading dot.  For instance MS-DOS doesn't.
AC_DEFUN([AM_SET_LEADING_DOT],
[rm -rf .tst 2>/dev/null
mkdir .tst 2>/dev/null
if test -d .tst; then
  am__leading_dot=.
else
  am__leading_dot=_
fi
rmdir .tst 2>/dev/null
AC_SUBST([am__leading_dot])])

# serial 5						-*- Autoconf -*-

# Copyright (C) 1999, 2000, 2001, 2002, 2003  Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.


# There are a few dirty hacks below to avoid letting `AC_PROG_CC' be
# written in clear, in which case automake, when reading aclocal.m4,
# will think it sees a *use*, and therefore will trigger all it's
# C support machinery.  Also note that it means that autoscan, seeing
# CC etc. in the Makefile, will ask for an AC_PROG_CC use...



# _AM_DEPENDENCIES(NAME)
# ----------------------
# See how the compiler implements dependency checking.
# NAME is "CC", "CXX", "GCJ", or "OBJC".
# We try a few techniques and use that to set a single cache variable.
#
# We don't AC_REQUIRE the corresponding AC_PROG_CC since the latter was
# modified to invoke _AM_DEPENDENCIES(CC); we would have a circular
# dependency, and given that the user is not expected to run this macro,
# just rely on AC_PROG_CC.
AC_DEFUN([_AM_DEPENDENCIES],
[AC_REQUIRE([AM_SET_DEPDIR])dnl
AC_REQUIRE([AM_OUTPUT_DEPENDENCY_COMMANDS])dnl
AC_REQUIRE([AM_MAKE_INCLUDE])dnl
AC_REQUIRE([AM_DEP_TRACK])dnl

ifelse([$1], CC,   [depcc="$CC"   am_compiler_list=],
       [$1], CXX,  [depcc="$CXX"  am_compiler_list=],
       [$1], OBJC, [depcc="$OBJC" am_compiler_list='gcc3 gcc'],
       [$1], GCJ,  [depcc="$GCJ"  am_compiler_list='gcc3 gcc'],
                   [depcc="$$1"   am_compiler_list=])

AC_CACHE_CHECK([dependency style of $depcc],
               [am_cv_$1_dependencies_compiler_type],
[if test -z "$AMDEP_TRUE" && test -f "$am_depcomp"; then
  # We make a subdir and do the tests there.  Otherwise we can end up
  # making bogus files that we don't know about and never remove.  For
  # instance it was reported that on HP-UX the gcc test will end up
  # making a dummy file named `D' -- because `-MD' means `put the output
  # in D'.
  mkdir conftest.dir
  # Copy depcomp to subdir because otherwise we won't find it if we're
  # using a relative directory.
  cp "$am_depcomp" conftest.dir
  cd conftest.dir

  am_cv_$1_dependencies_compiler_type=none
  if test "$am_compiler_list" = ""; then
     am_compiler_list=`sed -n ['s/^#*\([a-zA-Z0-9]*\))$/\1/p'] < ./depcomp`
  fi
  for depmode in $am_compiler_list; do
    # We need to recreate these files for each test, as the compiler may
    # overwrite some of them when testing with obscure command lines.
    # This happens at least with the AIX C compiler.
    echo '#include "conftest.h"' > conftest.c
    echo 'int i;' > conftest.h
    echo "${am__include} ${am__quote}conftest.Po${am__quote}" > confmf

    case $depmode in
    nosideeffect)
      # after this tag, mechanisms are not by side-effect, so they'll
      # only be used when explicitly requested
      if test "x$enable_dependency_tracking" = xyes; then
	continue
      else
	break
      fi
      ;;
    none) break ;;
    esac
    # We check with `-c' and `-o' for the sake of the "dashmstdout"
    # mode.  It turns out that the SunPro C++ compiler does not properly
    # handle `-M -o', and we need to detect this.
    if depmode=$depmode \
       source=conftest.c object=conftest.o \
       depfile=conftest.Po tmpdepfile=conftest.TPo \
       $SHELL ./depcomp $depcc -c -o conftest.o conftest.c \
         >/dev/null 2>conftest.err &&
       grep conftest.h conftest.Po > /dev/null 2>&1 &&
       ${MAKE-make} -s -f confmf > /dev/null 2>&1; then
      # icc doesn't choke on unknown options, it will just issue warnings
      # (even with -Werror).  So we grep stderr for any message
      # that says an option was ignored.
      if grep 'ignoring option' conftest.err >/dev/null 2>&1; then :; else
        am_cv_$1_dependencies_compiler_type=$depmode
        break
      fi
    fi
  done

  cd ..
  rm -rf conftest.dir
else
  am_cv_$1_dependencies_compiler_type=none
fi
])
AC_SUBST([$1DEPMODE], [depmode=$am_cv_$1_dependencies_compiler_type])
AM_CONDITIONAL([am__fastdep$1], [
  test "x$enable_dependency_tracking" != xno \
  && test "$am_cv_$1_dependencies_compiler_type" = gcc3])
])


# AM_SET_DEPDIR
# -------------
# Choose a directory name for dependency files.
# This macro is AC_REQUIREd in _AM_DEPENDENCIES
AC_DEFUN([AM_SET_DEPDIR],
[AC_REQUIRE([AM_SET_LEADING_DOT])dnl
AC_SUBST([DEPDIR], ["${am__leading_dot}deps"])dnl
])


# AM_DEP_TRACK
# ------------
AC_DEFUN([AM_DEP_TRACK],
[AC_ARG_ENABLE(dependency-tracking,
[  --disable-dependency-tracking Speeds up one-time builds
  --enable-dependency-tracking  Do not reject slow dependency extractors])
if test "x$enable_dependency_tracking" != xno; then
  am_depcomp="$ac_aux_dir/depcomp"
  AMDEPBACKSLASH='\'
fi
AM_CONDITIONAL([AMDEP], [test "x$enable_dependency_tracking" != xno])
AC_SUBST([AMDEPBACKSLASH])
])

# Generate code to set up dependency tracking.   -*- Autoconf -*-

# Copyright 1999, 2000, 2001, 2002 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

#serial 2

# _AM_OUTPUT_DEPENDENCY_COMMANDS
# ------------------------------
AC_DEFUN([_AM_OUTPUT_DEPENDENCY_COMMANDS],
[for mf in $CONFIG_FILES; do
  # Strip MF so we end up with the name of the file.
  mf=`echo "$mf" | sed -e 's/:.*$//'`
  # Check whether this is an Automake generated Makefile or not.
  # We used to match only the files named `Makefile.in', but
  # some people rename them; so instead we look at the file content.
  # Grep'ing the first line is not enough: some people post-process
  # each Makefile.in and add a new line on top of each file to say so.
  # So let's grep whole file.
  if grep '^#.*generated by automake' $mf > /dev/null 2>&1; then
    dirpart=`AS_DIRNAME("$mf")`
  else
    continue
  fi
  grep '^DEP_FILES *= *[[^ @%:@]]' < "$mf" > /dev/null || continue
  # Extract the definition of DEP_FILES from the Makefile without
  # running `make'.
  DEPDIR=`sed -n -e '/^DEPDIR = / s///p' < "$mf"`
  test -z "$DEPDIR" && continue
  # When using ansi2knr, U may be empty or an underscore; expand it
  U=`sed -n -e '/^U = / s///p' < "$mf"`
  test -d "$dirpart/$DEPDIR" || mkdir "$dirpart/$DEPDIR"
  # We invoke sed twice because it is the simplest approach to
  # changing $(DEPDIR) to its actual value in the expansion.
  for file in `sed -n -e '
    /^DEP_FILES = .*\\\\$/ {
      s/^DEP_FILES = //
      :loop
	s/\\\\$//
	p
	n
	/\\\\$/ b loop
      p
    }
    /^DEP_FILES = / s/^DEP_FILES = //p' < "$mf" | \
       sed -e 's/\$(DEPDIR)/'"$DEPDIR"'/g' -e 's/\$U/'"$U"'/g'`; do
    # Make sure the directory exists.
    test -f "$dirpart/$file" && continue
    fdir=`AS_DIRNAME(["$file"])`
    AS_MKDIR_P([$dirpart/$fdir])
    # echo "creating $dirpart/$file"
    echo '# dummy' > "$dirpart/$file"
  done
done
])# _AM_OUTPUT_DEPENDENCY_COMMANDS


# AM_OUTPUT_DEPENDENCY_COMMANDS
# -----------------------------
# This macro should only be invoked once -- use via AC_REQUIRE.
#
# This code is only required when automatic dependency tracking
# is enabled.  FIXME.  This creates each `.P' file that we will
# need in order to bootstrap the dependency handling code.
AC_DEFUN([AM_OUTPUT_DEPENDENCY_COMMANDS],
[AC_CONFIG_COMMANDS([depfiles],
     [test x"$AMDEP_TRUE" != x"" || _AM_OUTPUT_DEPENDENCY_COMMANDS],
     [AMDEP_TRUE="$AMDEP_TRUE" ac_aux_dir="$ac_aux_dir"])
])

# Check to see how 'make' treats includes.	-*- Autoconf -*-

# Copyright (C) 2001, 2002 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 2

# AM_MAKE_INCLUDE()
# -----------------
# Check to see how make treats includes.
AC_DEFUN([AM_MAKE_INCLUDE],
[am_make=${MAKE-make}
cat > confinc << 'END'
doit:
	@echo done
END
# If we don't find an include directive, just comment out the code.
AC_MSG_CHECKING([for style of include used by $am_make])
am__include="#"
am__quote=
_am_result=none
# First try GNU make style include.
echo "include confinc" > confmf
# We grep out `Entering directory' and `Leaving directory'
# messages which can occur if `w' ends up in MAKEFLAGS.
# In particular we don't look at `^make:' because GNU make might
# be invoked under some other name (usually "gmake"), in which
# case it prints its new name instead of `make'.
if test "`$am_make -s -f confmf 2> /dev/null | grep -v 'ing directory'`" = "done"; then
   am__include=include
   am__quote=
   _am_result=GNU
fi
# Now try BSD make style include.
if test "$am__include" = "#"; then
   echo '.include "confinc"' > confmf
   if test "`$am_make -s -f confmf 2> /dev/null`" = "done"; then
      am__include=.include
      am__quote="\""
      _am_result=BSD
   fi
fi
AC_SUBST(am__include)
AC_SUBST(am__quote)
AC_MSG_RESULT($_am_result)
rm -f confinc confmf
])

# AM_CONDITIONAL                                              -*- Autoconf -*-

# Copyright 1997, 2000, 2001 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 5

AC_PREREQ(2.52)

# AM_CONDITIONAL(NAME, SHELL-CONDITION)
# -------------------------------------
# Define a conditional.
AC_DEFUN([AM_CONDITIONAL],
[ifelse([$1], [TRUE],  [AC_FATAL([$0: invalid condition: $1])],
        [$1], [FALSE], [AC_FATAL([$0: invalid condition: $1])])dnl
AC_SUBST([$1_TRUE])
AC_SUBST([$1_FALSE])
if $2; then
  $1_TRUE=
  $1_FALSE='#'
else
  $1_TRUE='#'
  $1_FALSE=
fi
AC_CONFIG_COMMANDS_PRE(
[if test -z "${$1_TRUE}" && test -z "${$1_FALSE}"; then
  AC_MSG_ERROR([conditional "$1" was never defined.
Usually this means the macro was only invoked conditionally.])
fi])])

# Like AC_CONFIG_HEADER, but automatically create stamp file. -*- Autoconf -*-

# Copyright 1996, 1997, 2000, 2001 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

AC_PREREQ([2.52])

# serial 6

# AM_CONFIG_HEADER is obsolete.  It has been replaced by AC_CONFIG_HEADERS.
AU_DEFUN([AM_CONFIG_HEADER], [AC_CONFIG_HEADERS($@)])

# libtool.m4 - Configure libtool for the host system. -*-Shell-script-*-

# serial 46 AC_PROG_LIBTOOL

AC_DEFUN([AC_PROG_LIBTOOL],
[AC_REQUIRE([AC_LIBTOOL_SETUP])dnl

# This can be used to rebuild libtool when needed
LIBTOOL_DEPS="$ac_aux_dir/ltmain.sh"

# Always use our own libtool.
LIBTOOL='$(SHELL) $(top_builddir)/libtool'
AC_SUBST(LIBTOOL)dnl

# Prevent multiple expansion
define([AC_PROG_LIBTOOL], [])
])

AC_DEFUN([AC_LIBTOOL_SETUP],
[AC_PREREQ(2.13)dnl
AC_REQUIRE([AC_ENABLE_SHARED])dnl
AC_REQUIRE([AC_ENABLE_STATIC])dnl
AC_REQUIRE([AC_ENABLE_FAST_INSTALL])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_LD])dnl
AC_REQUIRE([AC_PROG_LD_RELOAD_FLAG])dnl
AC_REQUIRE([AC_PROG_NM])dnl
AC_REQUIRE([LT_AC_PROG_SED])dnl

AC_REQUIRE([AC_PROG_LN_S])dnl
AC_REQUIRE([AC_DEPLIBS_CHECK_METHOD])dnl
AC_REQUIRE([AC_OBJEXT])dnl
AC_REQUIRE([AC_EXEEXT])dnl
dnl

_LT_AC_PROG_ECHO_BACKSLASH
# Only perform the check for file, if the check method requires it
case $deplibs_check_method in
file_magic*)
  if test "$file_magic_cmd" = '$MAGIC_CMD'; then
    AC_PATH_MAGIC
  fi
  ;;
esac

AC_CHECK_TOOL(RANLIB, ranlib, :)
AC_CHECK_TOOL(STRIP, strip, :)

ifdef([AC_PROVIDE_AC_LIBTOOL_DLOPEN], enable_dlopen=yes, enable_dlopen=no)
ifdef([AC_PROVIDE_AC_LIBTOOL_WIN32_DLL],
enable_win32_dll=yes, enable_win32_dll=no)

AC_ARG_ENABLE(libtool-lock,
  [  --disable-libtool-lock  avoid locking (might break parallel builds)])
test "x$enable_libtool_lock" != xno && enable_libtool_lock=yes

# Some flags need to be propagated to the compiler or linker for good
# libtool support.
case $host in
*-*-irix6*)
  # Find out which ABI we are using.
  echo '[#]line __oline__ "configure"' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case `/usr/bin/file conftest.$ac_objext` in
    *32-bit*)
      LD="${LD-ld} -32"
      ;;
    *N32*)
      LD="${LD-ld} -n32"
      ;;
    *64-bit*)
      LD="${LD-ld} -64"
      ;;
    esac
  fi
  rm -rf conftest*
  ;;

*-*-sco3.2v5*)
  # On SCO OpenServer 5, we need -belf to get full-featured binaries.
  SAVE_CFLAGS="$CFLAGS"
  CFLAGS="$CFLAGS -belf"
  AC_CACHE_CHECK([whether the C compiler needs -belf], lt_cv_cc_needs_belf,
    [AC_LANG_SAVE
     AC_LANG_C
     AC_TRY_LINK([],[],[lt_cv_cc_needs_belf=yes],[lt_cv_cc_needs_belf=no])
     AC_LANG_RESTORE])
  if test x"$lt_cv_cc_needs_belf" != x"yes"; then
    # this is probably gcc 2.8.0, egcs 1.0 or newer; no need for -belf
    CFLAGS="$SAVE_CFLAGS"
  fi
  ;;

ifdef([AC_PROVIDE_AC_LIBTOOL_WIN32_DLL],
[*-*-cygwin* | *-*-mingw* | *-*-pw32*)
  AC_CHECK_TOOL(DLLTOOL, dlltool, false)
  AC_CHECK_TOOL(AS, as, false)
  AC_CHECK_TOOL(OBJDUMP, objdump, false)

  # recent cygwin and mingw systems supply a stub DllMain which the user
  # can override, but on older systems we have to supply one
  AC_CACHE_CHECK([if libtool should supply DllMain function], lt_cv_need_dllmain,
    [AC_TRY_LINK([],
      [extern int __attribute__((__stdcall__)) DllMain(void*, int, void*);
      DllMain (0, 0, 0);],
      [lt_cv_need_dllmain=no],[lt_cv_need_dllmain=yes])])

  case $host/$CC in
  *-*-cygwin*/gcc*-mno-cygwin*|*-*-mingw*)
    # old mingw systems require "-dll" to link a DLL, while more recent ones
    # require "-mdll"
    SAVE_CFLAGS="$CFLAGS"
    CFLAGS="$CFLAGS -mdll"
    AC_CACHE_CHECK([how to link DLLs], lt_cv_cc_dll_switch,
      [AC_TRY_LINK([], [], [lt_cv_cc_dll_switch=-mdll],[lt_cv_cc_dll_switch=-dll])])
    CFLAGS="$SAVE_CFLAGS" ;;
  *-*-cygwin* | *-*-pw32*)
    # cygwin systems need to pass --dll to the linker, and not link
    # crt.o which will require a WinMain@16 definition.
    lt_cv_cc_dll_switch="-Wl,--dll -nostartfiles" ;;
  esac
  ;;
  ])
esac

_LT_AC_LTCONFIG_HACK

])

# AC_LIBTOOL_HEADER_ASSERT
# ------------------------
AC_DEFUN([AC_LIBTOOL_HEADER_ASSERT],
[AC_CACHE_CHECK([whether $CC supports assert without backlinking],
    [lt_cv_func_assert_works],
    [case $host in
    *-*-solaris*)
      if test "$GCC" = yes && test "$with_gnu_ld" != yes; then
        case `$CC --version 2>/dev/null` in
        [[12]].*) lt_cv_func_assert_works=no ;;
        *)        lt_cv_func_assert_works=yes ;;
        esac
      fi
      ;;
    esac])

if test "x$lt_cv_func_assert_works" = xyes; then
  AC_CHECK_HEADERS(assert.h)
fi
])# AC_LIBTOOL_HEADER_ASSERT

# _LT_AC_CHECK_DLFCN
# --------------------
AC_DEFUN([_LT_AC_CHECK_DLFCN],
[AC_CHECK_HEADERS(dlfcn.h)
])# _LT_AC_CHECK_DLFCN

# AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE
# ---------------------------------
AC_DEFUN([AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE],
[AC_REQUIRE([AC_CANONICAL_HOST])
AC_REQUIRE([AC_PROG_NM])
AC_REQUIRE([AC_OBJEXT])
# Check for command to grab the raw symbol name followed by C symbol from nm.
AC_MSG_CHECKING([command to parse $NM output])
AC_CACHE_VAL([lt_cv_sys_global_symbol_pipe], [dnl

# These are sane defaults that work on at least a few old systems.
# [They come from Ultrix.  What could be older than Ultrix?!! ;)]

# Character class describing NM global symbol codes.
symcode='[[BCDEGRST]]'

# Regexp to match symbols that can be accessed directly from C.
sympat='\([[_A-Za-z]][[_A-Za-z0-9]]*\)'

# Transform the above into a raw symbol and a C symbol.
symxfrm='\1 \2\3 \3'

# Transform an extracted symbol line into a proper C declaration
lt_cv_global_symbol_to_cdecl="sed -n -e 's/^. .* \(.*\)$/extern char \1;/p'"

# Transform an extracted symbol line into symbol name and symbol address
lt_cv_global_symbol_to_c_name_address="sed -n -e 's/^: \([[^ ]]*\) $/  {\\\"\1\\\", (lt_ptr) 0},/p' -e 's/^$symcode \([[^ ]]*\) \([[^ ]]*\)$/  {\"\2\", (lt_ptr) \&\2},/p'"

# Define system-specific variables.
case $host_os in
aix*)
  symcode='[[BCDT]]'
  ;;
cygwin* | mingw* | pw32*)
  symcode='[[ABCDGISTW]]'
  ;;
hpux*) # Its linker distinguishes data from code symbols
  lt_cv_global_symbol_to_cdecl="sed -n -e 's/^T .* \(.*\)$/extern char \1();/p' -e 's/^$symcode* .* \(.*\)$/extern char \1;/p'"
  lt_cv_global_symbol_to_c_name_address="sed -n -e 's/^: \([[^ ]]*\) $/  {\\\"\1\\\", (lt_ptr) 0},/p' -e 's/^$symcode* \([[^ ]]*\) \([[^ ]]*\)$/  {\"\2\", (lt_ptr) \&\2},/p'"
  ;;
irix* | nonstopux*)
  symcode='[[BCDEGRST]]'
  ;;
osf*)
  symcode='[[BCDEGQRST]]'
  ;;
solaris* | sysv5*)
  symcode='[[BDT]]'
  ;;
sysv4)
  symcode='[[DFNSTU]]'
  ;;
esac

# Handle CRLF in mingw tool chain
opt_cr=
case $host_os in
mingw*)
  opt_cr=`echo 'x\{0,1\}' | tr x '\015'` # option cr in regexp
  ;;
esac

# If we're using GNU nm, then use its standard symbol codes.
if $NM -V 2>&1 | egrep '(GNU|with BFD)' > /dev/null; then
  symcode='[[ABCDGISTW]]'
fi

# Try without a prefix undercore, then with it.
for ac_symprfx in "" "_"; do

  # Write the raw and C identifiers.
lt_cv_sys_global_symbol_pipe="sed -n -e 's/^.*[[ 	]]\($symcode$symcode*\)[[ 	]][[ 	]]*\($ac_symprfx\)$sympat$opt_cr$/$symxfrm/p'"

  # Check to see that the pipe works correctly.
  pipe_works=no
  rm -f conftest*
  cat > conftest.$ac_ext <<EOF
#ifdef __cplusplus
extern "C" {
#endif
char nm_test_var;
void nm_test_func(){}
#ifdef __cplusplus
}
#endif
int main(){nm_test_var='a';nm_test_func();return(0);}
EOF

  if AC_TRY_EVAL(ac_compile); then
    # Now try to grab the symbols.
    nlist=conftest.nm
    if AC_TRY_EVAL(NM conftest.$ac_objext \| $lt_cv_sys_global_symbol_pipe \> $nlist) && test -s "$nlist"; then
      # Try sorting and uniquifying the output.
      if sort "$nlist" | uniq > "$nlist"T; then
	mv -f "$nlist"T "$nlist"
      else
	rm -f "$nlist"T
      fi

      # Make sure that we snagged all the symbols we need.
      if egrep ' nm_test_var$' "$nlist" >/dev/null; then
	if egrep ' nm_test_func$' "$nlist" >/dev/null; then
	  cat <<EOF > conftest.$ac_ext
#ifdef __cplusplus
extern "C" {
#endif

EOF
	  # Now generate the symbol file.
	  eval "$lt_cv_global_symbol_to_cdecl"' < "$nlist" >> conftest.$ac_ext'

	  cat <<EOF >> conftest.$ac_ext
#if defined (__STDC__) && __STDC__
# define lt_ptr void *
#else
# define lt_ptr char *
# define const
#endif

/* The mapping between symbol names and symbols. */
const struct {
  const char *name;
  lt_ptr address;
}
lt_preloaded_symbols[[]] =
{
EOF
	  sed "s/^$symcode$symcode* \(.*\) \(.*\)$/  {\"\2\", (lt_ptr) \&\2},/" < "$nlist" >> conftest.$ac_ext
	  cat <<\EOF >> conftest.$ac_ext
  {0, (lt_ptr) 0}
};

#ifdef __cplusplus
}
#endif
EOF
	  # Now try linking the two files.
	  mv conftest.$ac_objext conftstm.$ac_objext
	  save_LIBS="$LIBS"
	  save_CFLAGS="$CFLAGS"
	  LIBS="conftstm.$ac_objext"
	  CFLAGS="$CFLAGS$no_builtin_flag"
	  if AC_TRY_EVAL(ac_link) && test -s conftest$ac_exeext; then
	    pipe_works=yes
	  fi
	  LIBS="$save_LIBS"
	  CFLAGS="$save_CFLAGS"
	else
	  echo "cannot find nm_test_func in $nlist" >&AC_FD_CC
	fi
      else
	echo "cannot find nm_test_var in $nlist" >&AC_FD_CC
      fi
    else
      echo "cannot run $lt_cv_sys_global_symbol_pipe" >&AC_FD_CC
    fi
  else
    echo "$progname: failed program was:" >&AC_FD_CC
    cat conftest.$ac_ext >&5
  fi
  rm -f conftest* conftst*

  # Do not use the global_symbol_pipe unless it works.
  if test "$pipe_works" = yes; then
    break
  else
    lt_cv_sys_global_symbol_pipe=
  fi
done
])
global_symbol_pipe="$lt_cv_sys_global_symbol_pipe"
if test -z "$lt_cv_sys_global_symbol_pipe"; then
  global_symbol_to_cdecl=
  global_symbol_to_c_name_address=
else
  global_symbol_to_cdecl="$lt_cv_global_symbol_to_cdecl"
  global_symbol_to_c_name_address="$lt_cv_global_symbol_to_c_name_address"
fi
if test -z "$global_symbol_pipe$global_symbol_to_cdec$global_symbol_to_c_name_address";
then
  AC_MSG_RESULT(failed)
else
  AC_MSG_RESULT(ok)
fi
]) # AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE

# _LT_AC_LIBTOOL_SYS_PATH_SEPARATOR
# ---------------------------------
AC_DEFUN([_LT_AC_LIBTOOL_SYS_PATH_SEPARATOR],
[# Find the correct PATH separator.  Usually this is `:', but
# DJGPP uses `;' like DOS.
if test "X${PATH_SEPARATOR+set}" != Xset; then
  UNAME=${UNAME-`uname 2>/dev/null`}
  case X$UNAME in
    *-DOS) lt_cv_sys_path_separator=';' ;;
    *)     lt_cv_sys_path_separator=':' ;;
  esac
  PATH_SEPARATOR=$lt_cv_sys_path_separator
fi
])# _LT_AC_LIBTOOL_SYS_PATH_SEPARATOR

# _LT_AC_PROG_ECHO_BACKSLASH
# --------------------------
# Add some code to the start of the generated configure script which
# will find an echo command which doesn't interpret backslashes.
AC_DEFUN([_LT_AC_PROG_ECHO_BACKSLASH],
[ifdef([AC_DIVERSION_NOTICE], [AC_DIVERT_PUSH(AC_DIVERSION_NOTICE)],
			      [AC_DIVERT_PUSH(NOTICE)])
_LT_AC_LIBTOOL_SYS_PATH_SEPARATOR

# Check that we are running under the correct shell.
SHELL=${CONFIG_SHELL-/bin/sh}

case X$ECHO in
X*--fallback-echo)
  # Remove one level of quotation (which was required for Make).
  ECHO=`echo "$ECHO" | sed 's,\\\\\[$]\\[$]0,'[$]0','`
  ;;
esac

echo=${ECHO-echo}
if test "X[$]1" = X--no-reexec; then
  # Discard the --no-reexec flag, and continue.
  shift
elif test "X[$]1" = X--fallback-echo; then
  # Avoid inline document here, it may be left over
  :
elif test "X`($echo '\t') 2>/dev/null`" = 'X\t'; then
  # Yippee, $echo works!
  :
else
  # Restart under the correct shell.
  exec $SHELL "[$]0" --no-reexec ${1+"[$]@"}
fi

if test "X[$]1" = X--fallback-echo; then
  # used as fallback echo
  shift
  cat <<EOF
$*
EOF
  exit 0
fi

# The HP-UX ksh and POSIX shell print the target directory to stdout
# if CDPATH is set.
if test "X${CDPATH+set}" = Xset; then CDPATH=:; export CDPATH; fi

if test -z "$ECHO"; then
if test "X${echo_test_string+set}" != Xset; then
# find a string as large as possible, as long as the shell can cope with it
  for cmd in 'sed 50q "[$]0"' 'sed 20q "[$]0"' 'sed 10q "[$]0"' 'sed 2q "[$]0"' 'echo test'; do
    # expected sizes: less than 2Kb, 1Kb, 512 bytes, 16 bytes, ...
    if (echo_test_string="`eval $cmd`") 2>/dev/null &&
       echo_test_string="`eval $cmd`" &&
       (test "X$echo_test_string" = "X$echo_test_string") 2>/dev/null
    then
      break
    fi
  done
fi

if test "X`($echo '\t') 2>/dev/null`" = 'X\t' &&
   echo_testing_string=`($echo "$echo_test_string") 2>/dev/null` &&
   test "X$echo_testing_string" = "X$echo_test_string"; then
  :
else
  # The Solaris, AIX, and Digital Unix default echo programs unquote
  # backslashes.  This makes it impossible to quote backslashes using
  #   echo "$something" | sed 's/\\/\\\\/g'
  #
  # So, first we look for a working echo in the user's PATH.

  IFS="${IFS= 	}"; save_ifs="$IFS"; IFS=$PATH_SEPARATOR
  for dir in $PATH /usr/ucb; do
    if (test -f $dir/echo || test -f $dir/echo$ac_exeext) &&
       test "X`($dir/echo '\t') 2>/dev/null`" = 'X\t' &&
       echo_testing_string=`($dir/echo "$echo_test_string") 2>/dev/null` &&
       test "X$echo_testing_string" = "X$echo_test_string"; then
      echo="$dir/echo"
      break
    fi
  done
  IFS="$save_ifs"

  if test "X$echo" = Xecho; then
    # We didn't find a better echo, so look for alternatives.
    if test "X`(print -r '\t') 2>/dev/null`" = 'X\t' &&
       echo_testing_string=`(print -r "$echo_test_string") 2>/dev/null` &&
       test "X$echo_testing_string" = "X$echo_test_string"; then
      # This shell has a builtin print -r that does the trick.
      echo='print -r'
    elif (test -f /bin/ksh || test -f /bin/ksh$ac_exeext) &&
	 test "X$CONFIG_SHELL" != X/bin/ksh; then
      # If we have ksh, try running configure again with it.
      ORIGINAL_CONFIG_SHELL=${CONFIG_SHELL-/bin/sh}
      export ORIGINAL_CONFIG_SHELL
      CONFIG_SHELL=/bin/ksh
      export CONFIG_SHELL
      exec $CONFIG_SHELL "[$]0" --no-reexec ${1+"[$]@"}
    else
      # Try using printf.
      echo='printf %s\n'
      if test "X`($echo '\t') 2>/dev/null`" = 'X\t' &&
	 echo_testing_string=`($echo "$echo_test_string") 2>/dev/null` &&
	 test "X$echo_testing_string" = "X$echo_test_string"; then
	# Cool, printf works
	:
      elif echo_testing_string=`($ORIGINAL_CONFIG_SHELL "[$]0" --fallback-echo '\t') 2>/dev/null` &&
	   test "X$echo_testing_string" = 'X\t' &&
	   echo_testing_string=`($ORIGINAL_CONFIG_SHELL "[$]0" --fallback-echo "$echo_test_string") 2>/dev/null` &&
	   test "X$echo_testing_string" = "X$echo_test_string"; then
	CONFIG_SHELL=$ORIGINAL_CONFIG_SHELL
	export CONFIG_SHELL
	SHELL="$CONFIG_SHELL"
	export SHELL
	echo="$CONFIG_SHELL [$]0 --fallback-echo"
      elif echo_testing_string=`($CONFIG_SHELL "[$]0" --fallback-echo '\t') 2>/dev/null` &&
	   test "X$echo_testing_string" = 'X\t' &&
	   echo_testing_string=`($CONFIG_SHELL "[$]0" --fallback-echo "$echo_test_string") 2>/dev/null` &&
	   test "X$echo_testing_string" = "X$echo_test_string"; then
	echo="$CONFIG_SHELL [$]0 --fallback-echo"
      else
	# maybe with a smaller string...
	prev=:

	for cmd in 'echo test' 'sed 2q "[$]0"' 'sed 10q "[$]0"' 'sed 20q "[$]0"' 'sed 50q "[$]0"'; do
	  if (test "X$echo_test_string" = "X`eval $cmd`") 2>/dev/null
	  then
	    break
	  fi
	  prev="$cmd"
	done

	if test "$prev" != 'sed 50q "[$]0"'; then
	  echo_test_string=`eval $prev`
	  export echo_test_string
	  exec ${ORIGINAL_CONFIG_SHELL-${CONFIG_SHELL-/bin/sh}} "[$]0" ${1+"[$]@"}
	else
	  # Oops.  We lost completely, so just stick with echo.
	  echo=echo
	fi
      fi
    fi
  fi
fi
fi

# Copy echo and quote the copy suitably for passing to libtool from
# the Makefile, instead of quoting the original, which is used later.
ECHO=$echo
if test "X$ECHO" = "X$CONFIG_SHELL [$]0 --fallback-echo"; then
   ECHO="$CONFIG_SHELL \\\$\[$]0 --fallback-echo"
fi

AC_SUBST(ECHO)
AC_DIVERT_POP
])# _LT_AC_PROG_ECHO_BACKSLASH

# _LT_AC_TRY_DLOPEN_SELF (ACTION-IF-TRUE, ACTION-IF-TRUE-W-USCORE,
#                           ACTION-IF-FALSE, ACTION-IF-CROSS-COMPILING)
# ------------------------------------------------------------------
AC_DEFUN([_LT_AC_TRY_DLOPEN_SELF],
[if test "$cross_compiling" = yes; then :
  [$4]
else
  AC_REQUIRE([_LT_AC_CHECK_DLFCN])dnl
  lt_dlunknown=0; lt_dlno_uscore=1; lt_dlneed_uscore=2
  lt_status=$lt_dlunknown
  cat > conftest.$ac_ext <<EOF
[#line __oline__ "configure"
#include "confdefs.h"

#if HAVE_DLFCN_H
#include <dlfcn.h>
#endif

#include <stdio.h>

#ifdef RTLD_GLOBAL
#  define LT_DLGLOBAL		RTLD_GLOBAL
#else
#  ifdef DL_GLOBAL
#    define LT_DLGLOBAL		DL_GLOBAL
#  else
#    define LT_DLGLOBAL		0
#  endif
#endif

/* We may have to define LT_DLLAZY_OR_NOW in the command line if we
   find out it does not work in some platform. */
#ifndef LT_DLLAZY_OR_NOW
#  ifdef RTLD_LAZY
#    define LT_DLLAZY_OR_NOW		RTLD_LAZY
#  else
#    ifdef DL_LAZY
#      define LT_DLLAZY_OR_NOW		DL_LAZY
#    else
#      ifdef RTLD_NOW
#        define LT_DLLAZY_OR_NOW	RTLD_NOW
#      else
#        ifdef DL_NOW
#          define LT_DLLAZY_OR_NOW	DL_NOW
#        else
#          define LT_DLLAZY_OR_NOW	0
#        endif
#      endif
#    endif
#  endif
#endif

#ifdef __cplusplus
extern "C" void exit (int);
#endif

void fnord() { int i=42;}
int main ()
{
  void *self = dlopen (0, LT_DLGLOBAL|LT_DLLAZY_OR_NOW);
  int status = $lt_dlunknown;

  if (self)
    {
      if (dlsym (self,"fnord"))       status = $lt_dlno_uscore;
      else if (dlsym( self,"_fnord")) status = $lt_dlneed_uscore;
      /* dlclose (self); */
    }

    exit (status);
}]
EOF
  if AC_TRY_EVAL(ac_link) && test -s conftest${ac_exeext} 2>/dev/null; then
    (./conftest; exit; ) 2>/dev/null
    lt_status=$?
    case x$lt_status in
      x$lt_dlno_uscore) $1 ;;
      x$lt_dlneed_uscore) $2 ;;
      x$lt_unknown|x*) $3 ;;
    esac
  else :
    # compilation failed
    $3
  fi
fi
rm -fr conftest*
])# _LT_AC_TRY_DLOPEN_SELF

# AC_LIBTOOL_DLOPEN_SELF
# -------------------
AC_DEFUN([AC_LIBTOOL_DLOPEN_SELF],
[if test "x$enable_dlopen" != xyes; then
  enable_dlopen=unknown
  enable_dlopen_self=unknown
  enable_dlopen_self_static=unknown
else
  lt_cv_dlopen=no
  lt_cv_dlopen_libs=

  case $host_os in
  beos*)
    lt_cv_dlopen="load_add_on"
    lt_cv_dlopen_libs=
    lt_cv_dlopen_self=yes
    ;;

  cygwin* | mingw* | pw32*)
    lt_cv_dlopen="LoadLibrary"
    lt_cv_dlopen_libs=
   ;;

  *)
    AC_CHECK_FUNC([shl_load],
          [lt_cv_dlopen="shl_load"],
      [AC_CHECK_LIB([dld], [shl_load],
            [lt_cv_dlopen="shl_load" lt_cv_dlopen_libs="-dld"],
	[AC_CHECK_FUNC([dlopen],
	      [lt_cv_dlopen="dlopen"],
	  [AC_CHECK_LIB([dl], [dlopen],
	        [lt_cv_dlopen="dlopen" lt_cv_dlopen_libs="-ldl"],
	    [AC_CHECK_LIB([svld], [dlopen],
	          [lt_cv_dlopen="dlopen" lt_cv_dlopen_libs="-lsvld"],
	      [AC_CHECK_LIB([dld], [dld_link],
	            [lt_cv_dlopen="dld_link" lt_cv_dlopen_libs="-dld"])
	      ])
	    ])
	  ])
	])
      ])
    ;;
  esac

  if test "x$lt_cv_dlopen" != xno; then
    enable_dlopen=yes
  else
    enable_dlopen=no
  fi

  case $lt_cv_dlopen in
  dlopen)
    save_CPPFLAGS="$CPPFLAGS"
    AC_REQUIRE([_LT_AC_CHECK_DLFCN])dnl
    test "x$ac_cv_header_dlfcn_h" = xyes && CPPFLAGS="$CPPFLAGS -DHAVE_DLFCN_H"

    save_LDFLAGS="$LDFLAGS"
    eval LDFLAGS=\"\$LDFLAGS $export_dynamic_flag_spec\"

    save_LIBS="$LIBS"
    LIBS="$lt_cv_dlopen_libs $LIBS"

    AC_CACHE_CHECK([whether a program can dlopen itself],
	  lt_cv_dlopen_self, [dnl
	  _LT_AC_TRY_DLOPEN_SELF(
	    lt_cv_dlopen_self=yes, lt_cv_dlopen_self=yes,
	    lt_cv_dlopen_self=no, lt_cv_dlopen_self=cross)
    ])

    if test "x$lt_cv_dlopen_self" = xyes; then
      LDFLAGS="$LDFLAGS $link_static_flag"
      AC_CACHE_CHECK([whether a statically linked program can dlopen itself],
    	  lt_cv_dlopen_self_static, [dnl
	  _LT_AC_TRY_DLOPEN_SELF(
	    lt_cv_dlopen_self_static=yes, lt_cv_dlopen_self_static=yes,
	    lt_cv_dlopen_self_static=no,  lt_cv_dlopen_self_static=cross)
      ])
    fi

    CPPFLAGS="$save_CPPFLAGS"
    LDFLAGS="$save_LDFLAGS"
    LIBS="$save_LIBS"
    ;;
  esac

  case $lt_cv_dlopen_self in
  yes|no) enable_dlopen_self=$lt_cv_dlopen_self ;;
  *) enable_dlopen_self=unknown ;;
  esac

  case $lt_cv_dlopen_self_static in
  yes|no) enable_dlopen_self_static=$lt_cv_dlopen_self_static ;;
  *) enable_dlopen_self_static=unknown ;;
  esac
fi
])# AC_LIBTOOL_DLOPEN_SELF

AC_DEFUN([_LT_AC_LTCONFIG_HACK],
[AC_REQUIRE([AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE])dnl
# Sed substitution that helps us do robust quoting.  It backslashifies
# metacharacters that are still active within double-quoted strings.
Xsed='sed -e s/^X//'
sed_quote_subst='s/\([[\\"\\`$\\\\]]\)/\\\1/g'

# Same as above, but do not quote variable references.
double_quote_subst='s/\([[\\"\\`\\\\]]\)/\\\1/g'

# Sed substitution to delay expansion of an escaped shell variable in a
# double_quote_subst'ed string.
delay_variable_subst='s/\\\\\\\\\\\$/\\\\\\$/g'

# Constants:
rm="rm -f"

# Global variables:
default_ofile=libtool
can_build_shared=yes

# All known linkers require a `.a' archive for static linking (except M$VC,
# which needs '.lib').
libext=a
ltmain="$ac_aux_dir/ltmain.sh"
ofile="$default_ofile"
with_gnu_ld="$lt_cv_prog_gnu_ld"
need_locks="$enable_libtool_lock"

old_CC="$CC"
old_CFLAGS="$CFLAGS"

# Set sane defaults for various variables
test -z "$AR" && AR=ar
test -z "$AR_FLAGS" && AR_FLAGS=cru
test -z "$AS" && AS=as
test -z "$CC" && CC=cc
test -z "$DLLTOOL" && DLLTOOL=dlltool
test -z "$LD" && LD=ld
test -z "$LN_S" && LN_S="ln -s"
test -z "$MAGIC_CMD" && MAGIC_CMD=file
test -z "$NM" && NM=nm
test -z "$OBJDUMP" && OBJDUMP=objdump
test -z "$RANLIB" && RANLIB=:
test -z "$STRIP" && STRIP=:
test -z "$ac_objext" && ac_objext=o

if test x"$host" != x"$build"; then
  ac_tool_prefix=${host_alias}-
else
  ac_tool_prefix=
fi

# Transform linux* to *-*-linux-gnu*, to support old configure scripts.
case $host_os in
linux-gnu*) ;;
linux*) host=`echo $host | sed 's/^\(.*-.*-linux\)\(.*\)$/\1-gnu\2/'`
esac

case $host_os in
aix3*)
  # AIX sometimes has problems with the GCC collect2 program.  For some
  # reason, if we set the COLLECT_NAMES environment variable, the problems
  # vanish in a puff of smoke.
  if test "X${COLLECT_NAMES+set}" != Xset; then
    COLLECT_NAMES=
    export COLLECT_NAMES
  fi
  ;;
esac

# Determine commands to create old-style static archives.
old_archive_cmds='$AR $AR_FLAGS $oldlib$oldobjs$old_deplibs'
old_postinstall_cmds='chmod 644 $oldlib'
old_postuninstall_cmds=

if test -n "$RANLIB"; then
  case $host_os in
  openbsd*)
    old_postinstall_cmds="\$RANLIB -t \$oldlib~$old_postinstall_cmds"
    ;;
  *)
    old_postinstall_cmds="\$RANLIB \$oldlib~$old_postinstall_cmds"
    ;;
  esac
  old_archive_cmds="$old_archive_cmds~\$RANLIB \$oldlib"
fi

# Allow CC to be a program name with arguments.
set dummy $CC
compiler="[$]2"

AC_MSG_CHECKING([for objdir])
rm -f .libs 2>/dev/null
mkdir .libs 2>/dev/null
if test -d .libs; then
  objdir=.libs
else
  # MS-DOS does not allow filenames that begin with a dot.
  objdir=_libs
fi
rmdir .libs 2>/dev/null
AC_MSG_RESULT($objdir)


AC_ARG_WITH(pic,
[  --with-pic              try to use only PIC/non-PIC objects [default=use both]],
pic_mode="$withval", pic_mode=default)
test -z "$pic_mode" && pic_mode=default

# We assume here that the value for lt_cv_prog_cc_pic will not be cached
# in isolation, and that seeing it set (from the cache) indicates that
# the associated values are set (in the cache) correctly too.
AC_MSG_CHECKING([for $compiler option to produce PIC])
AC_CACHE_VAL(lt_cv_prog_cc_pic,
[ lt_cv_prog_cc_pic=
  lt_cv_prog_cc_shlib=
  lt_cv_prog_cc_wl=
  lt_cv_prog_cc_static=
  lt_cv_prog_cc_no_builtin=
  lt_cv_prog_cc_can_build_shared=$can_build_shared

  if test "$GCC" = yes; then
    lt_cv_prog_cc_wl='-Wl,'
    lt_cv_prog_cc_static='-static'

    case $host_os in
    aix*)
      # Below there is a dirty hack to force normal static linking with -ldl
      # The problem is because libdl dynamically linked with both libc and
      # libC (AIX C++ library), which obviously doesn't included in libraries
      # list by gcc. This cause undefined symbols with -static flags.
      # This hack allows C programs to be linked with "-static -ldl", but
      # not sure about C++ programs.
      lt_cv_prog_cc_static="$lt_cv_prog_cc_static ${lt_cv_prog_cc_wl}-lC"
      ;;
    amigaos*)
      # FIXME: we need at least 68020 code to build shared libraries, but
      # adding the `-m68020' flag to GCC prevents building anything better,
      # like `-m68040'.
      lt_cv_prog_cc_pic='-m68020 -resident32 -malways-restore-a4'
      ;;
    beos* | irix5* | irix6* | nonstopux* | osf3* | osf4* | osf5*)
      # PIC is the default for these OSes.
      ;;
    darwin* | rhapsody*)
      # PIC is the default on this platform
      # Common symbols not allowed in MH_DYLIB files
      lt_cv_prog_cc_pic='-fno-common'
      ;;
    cygwin* | mingw* | pw32* | os2*)
      # This hack is so that the source file can tell whether it is being
      # built for inclusion in a dll (and should export symbols for example).
      lt_cv_prog_cc_pic='-DDLL_EXPORT'
      ;;
    sysv4*MP*)
      if test -d /usr/nec; then
	 lt_cv_prog_cc_pic=-Kconform_pic
      fi
      ;;
    *)
      lt_cv_prog_cc_pic='-fPIC'
      ;;
    esac
  else
    # PORTME Check for PIC flags for the system compiler.
    case $host_os in
    aix3* | aix4* | aix5*)
      lt_cv_prog_cc_wl='-Wl,'
      # All AIX code is PIC.
      if test "$host_cpu" = ia64; then
	# AIX 5 now supports IA64 processor
	lt_cv_prog_cc_static='-Bstatic'
      else
	lt_cv_prog_cc_static='-bnso -bI:/lib/syscalls.exp'
      fi
      ;;

    hpux9* | hpux10* | hpux11*)
      # Is there a better lt_cv_prog_cc_static that works with the bundled CC?
      lt_cv_prog_cc_wl='-Wl,'
      lt_cv_prog_cc_static="${lt_cv_prog_cc_wl}-a ${lt_cv_prog_cc_wl}archive"
      lt_cv_prog_cc_pic='+Z'
      ;;

    irix5* | irix6* | nonstopux*)
      lt_cv_prog_cc_wl='-Wl,'
      lt_cv_prog_cc_static='-non_shared'
      # PIC (with -KPIC) is the default.
      ;;

    cygwin* | mingw* | pw32* | os2*)
      # This hack is so that the source file can tell whether it is being
      # built for inclusion in a dll (and should export symbols for example).
      lt_cv_prog_cc_pic='-DDLL_EXPORT'
      ;;

    newsos6)
      lt_cv_prog_cc_pic='-KPIC'
      lt_cv_prog_cc_static='-Bstatic'
      ;;

    osf3* | osf4* | osf5*)
      # All OSF/1 code is PIC.
      lt_cv_prog_cc_wl='-Wl,'
      lt_cv_prog_cc_static='-non_shared'
      ;;

    sco3.2v5*)
      lt_cv_prog_cc_pic='-Kpic'
      lt_cv_prog_cc_static='-dn'
      lt_cv_prog_cc_shlib='-belf'
      ;;

    solaris*)
      lt_cv_prog_cc_pic='-KPIC'
      lt_cv_prog_cc_static='-Bstatic'
      lt_cv_prog_cc_wl='-Wl,'
      ;;

    sunos4*)
      lt_cv_prog_cc_pic='-PIC'
      lt_cv_prog_cc_static='-Bstatic'
      lt_cv_prog_cc_wl='-Qoption ld '
      ;;

    sysv4 | sysv4.2uw2* | sysv4.3* | sysv5*)
      lt_cv_prog_cc_pic='-KPIC'
      lt_cv_prog_cc_static='-Bstatic'
      lt_cv_prog_cc_wl='-Wl,'
      ;;

    uts4*)
      lt_cv_prog_cc_pic='-pic'
      lt_cv_prog_cc_static='-Bstatic'
      ;;

    sysv4*MP*)
      if test -d /usr/nec ;then
	lt_cv_prog_cc_pic='-Kconform_pic'
	lt_cv_prog_cc_static='-Bstatic'
      fi
      ;;

    *)
      lt_cv_prog_cc_can_build_shared=no
      ;;
    esac
  fi
])
if test -z "$lt_cv_prog_cc_pic"; then
  AC_MSG_RESULT([none])
else
  AC_MSG_RESULT([$lt_cv_prog_cc_pic])

  # Check to make sure the pic_flag actually works.
  AC_MSG_CHECKING([if $compiler PIC flag $lt_cv_prog_cc_pic works])
  AC_CACHE_VAL(lt_cv_prog_cc_pic_works, [dnl
    save_CFLAGS="$CFLAGS"
    CFLAGS="$CFLAGS $lt_cv_prog_cc_pic -DPIC"
    AC_TRY_COMPILE([], [], [dnl
      case $host_os in
      hpux9* | hpux10* | hpux11*)
	# On HP-UX, both CC and GCC only warn that PIC is supported... then
	# they create non-PIC objects.  So, if there were any warnings, we
	# assume that PIC is not supported.
	if test -s conftest.err; then
	  lt_cv_prog_cc_pic_works=no
	else
	  lt_cv_prog_cc_pic_works=yes
	fi
	;;
      *)
	lt_cv_prog_cc_pic_works=yes
	;;
      esac
    ], [dnl
      lt_cv_prog_cc_pic_works=no
    ])
    CFLAGS="$save_CFLAGS"
  ])

  if test "X$lt_cv_prog_cc_pic_works" = Xno; then
    lt_cv_prog_cc_pic=
    lt_cv_prog_cc_can_build_shared=no
  else
    lt_cv_prog_cc_pic=" $lt_cv_prog_cc_pic"
  fi

  AC_MSG_RESULT([$lt_cv_prog_cc_pic_works])
fi

# Check for any special shared library compilation flags.
if test -n "$lt_cv_prog_cc_shlib"; then
  AC_MSG_WARN([\`$CC' requires \`$lt_cv_prog_cc_shlib' to build shared libraries])
  if echo "$old_CC $old_CFLAGS " | egrep -e "[[ 	]]$lt_cv_prog_cc_shlib[[ 	]]" >/dev/null; then :
  else
   AC_MSG_WARN([add \`$lt_cv_prog_cc_shlib' to the CC or CFLAGS env variable and reconfigure])
    lt_cv_prog_cc_can_build_shared=no
  fi
fi

AC_MSG_CHECKING([if $compiler static flag $lt_cv_prog_cc_static works])
AC_CACHE_VAL([lt_cv_prog_cc_static_works], [dnl
  lt_cv_prog_cc_static_works=no
  save_LDFLAGS="$LDFLAGS"
  LDFLAGS="$LDFLAGS $lt_cv_prog_cc_static"
  AC_TRY_LINK([], [], [lt_cv_prog_cc_static_works=yes])
  LDFLAGS="$save_LDFLAGS"
])

# Belt *and* braces to stop my trousers falling down:
test "X$lt_cv_prog_cc_static_works" = Xno && lt_cv_prog_cc_static=
AC_MSG_RESULT([$lt_cv_prog_cc_static_works])

pic_flag="$lt_cv_prog_cc_pic"
special_shlib_compile_flags="$lt_cv_prog_cc_shlib"
wl="$lt_cv_prog_cc_wl"
link_static_flag="$lt_cv_prog_cc_static"
no_builtin_flag="$lt_cv_prog_cc_no_builtin"
can_build_shared="$lt_cv_prog_cc_can_build_shared"


# Check to see if options -o and -c are simultaneously supported by compiler
AC_MSG_CHECKING([if $compiler supports -c -o file.$ac_objext])
AC_CACHE_VAL([lt_cv_compiler_c_o], [
$rm -r conftest 2>/dev/null
mkdir conftest
cd conftest
echo "int some_variable = 0;" > conftest.$ac_ext
mkdir out
# According to Tom Tromey, Ian Lance Taylor reported there are C compilers
# that will create temporary files in the current directory regardless of
# the output directory.  Thus, making CWD read-only will cause this test
# to fail, enabling locking or at least warning the user not to do parallel
# builds.
chmod -w .
save_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS -o out/conftest2.$ac_objext"
compiler_c_o=no
if { (eval echo configure:__oline__: \"$ac_compile\") 1>&5; (eval $ac_compile) 2>out/conftest.err; } && test -s out/conftest2.$ac_objext; then
  # The compiler can only warn and ignore the option if not recognized
  # So say no if there are warnings
  if test -s out/conftest.err; then
    lt_cv_compiler_c_o=no
  else
    lt_cv_compiler_c_o=yes
  fi
else
  # Append any errors to the config.log.
  cat out/conftest.err 1>&AC_FD_CC
  lt_cv_compiler_c_o=no
fi
CFLAGS="$save_CFLAGS"
chmod u+w .
$rm conftest* out/*
rmdir out
cd ..
rmdir conftest
$rm -r conftest 2>/dev/null
])
compiler_c_o=$lt_cv_compiler_c_o
AC_MSG_RESULT([$compiler_c_o])

if test x"$compiler_c_o" = x"yes"; then
  # Check to see if we can write to a .lo
  AC_MSG_CHECKING([if $compiler supports -c -o file.lo])
  AC_CACHE_VAL([lt_cv_compiler_o_lo], [
  lt_cv_compiler_o_lo=no
  save_CFLAGS="$CFLAGS"
  CFLAGS="$CFLAGS -c -o conftest.lo"
  save_objext="$ac_objext"
  ac_objext=lo
  AC_TRY_COMPILE([], [int some_variable = 0;], [dnl
    # The compiler can only warn and ignore the option if not recognized
    # So say no if there are warnings
    if test -s conftest.err; then
      lt_cv_compiler_o_lo=no
    else
      lt_cv_compiler_o_lo=yes
    fi
  ])
  ac_objext="$save_objext"
  CFLAGS="$save_CFLAGS"
  ])
  compiler_o_lo=$lt_cv_compiler_o_lo
  AC_MSG_RESULT([$compiler_o_lo])
else
  compiler_o_lo=no
fi

# Check to see if we can do hard links to lock some files if needed
hard_links="nottested"
if test "$compiler_c_o" = no && test "$need_locks" != no; then
  # do not overwrite the value of need_locks provided by the user
  AC_MSG_CHECKING([if we can lock with hard links])
  hard_links=yes
  $rm conftest*
  ln conftest.a conftest.b 2>/dev/null && hard_links=no
  touch conftest.a
  ln conftest.a conftest.b 2>&5 || hard_links=no
  ln conftest.a conftest.b 2>/dev/null && hard_links=no
  AC_MSG_RESULT([$hard_links])
  if test "$hard_links" = no; then
    AC_MSG_WARN([\`$CC' does not support \`-c -o', so \`make -j' may be unsafe])
    need_locks=warn
  fi
else
  need_locks=no
fi

if test "$GCC" = yes; then
  # Check to see if options -fno-rtti -fno-exceptions are supported by compiler
  AC_MSG_CHECKING([if $compiler supports -fno-rtti -fno-exceptions])
  echo "int some_variable = 0;" > conftest.$ac_ext
  save_CFLAGS="$CFLAGS"
  CFLAGS="$CFLAGS -fno-rtti -fno-exceptions -c conftest.$ac_ext"
  compiler_rtti_exceptions=no
  AC_TRY_COMPILE([], [int some_variable = 0;], [dnl
    # The compiler can only warn and ignore the option if not recognized
    # So say no if there are warnings
    if test -s conftest.err; then
      compiler_rtti_exceptions=no
    else
      compiler_rtti_exceptions=yes
    fi
  ])
  CFLAGS="$save_CFLAGS"
  AC_MSG_RESULT([$compiler_rtti_exceptions])

  if test "$compiler_rtti_exceptions" = "yes"; then
    no_builtin_flag=' -fno-builtin -fno-rtti -fno-exceptions'
  else
    no_builtin_flag=' -fno-builtin'
  fi
fi

# See if the linker supports building shared libraries.
AC_MSG_CHECKING([whether the linker ($LD) supports shared libraries])

allow_undefined_flag=
no_undefined_flag=
need_lib_prefix=unknown
need_version=unknown
# when you set need_version to no, make sure it does not cause -set_version
# flags to be left without arguments
archive_cmds=
archive_expsym_cmds=
old_archive_from_new_cmds=
old_archive_from_expsyms_cmds=
export_dynamic_flag_spec=
whole_archive_flag_spec=
thread_safe_flag_spec=
hardcode_into_libs=no
hardcode_libdir_flag_spec=
hardcode_libdir_separator=
hardcode_direct=no
hardcode_minus_L=no
hardcode_shlibpath_var=unsupported
runpath_var=
link_all_deplibs=unknown
always_export_symbols=no
export_symbols_cmds='$NM $libobjs $convenience | $global_symbol_pipe | sed '\''s/.* //'\'' | sort | uniq > $export_symbols'
# include_expsyms should be a list of space-separated symbols to be *always*
# included in the symbol list
include_expsyms=
# exclude_expsyms can be an egrep regular expression of symbols to exclude
# it will be wrapped by ` (' and `)$', so one must not match beginning or
# end of line.  Example: `a|bc|.*d.*' will exclude the symbols `a' and `bc',
# as well as any symbol that contains `d'.
exclude_expsyms="_GLOBAL_OFFSET_TABLE_"
# Although _GLOBAL_OFFSET_TABLE_ is a valid symbol C name, most a.out
# platforms (ab)use it in PIC code, but their linkers get confused if
# the symbol is explicitly referenced.  Since portable code cannot
# rely on this symbol name, it's probably fine to never include it in
# preloaded symbol tables.
extract_expsyms_cmds=

case $host_os in
cygwin* | mingw* | pw32*)
  # FIXME: the MSVC++ port hasn't been tested in a loooong time
  # When not using gcc, we currently assume that we are using
  # Microsoft Visual C++.
  if test "$GCC" != yes; then
    with_gnu_ld=no
  fi
  ;;
openbsd*)
  with_gnu_ld=no
  ;;
esac

ld_shlibs=yes
if test "$with_gnu_ld" = yes; then
  # If archive_cmds runs LD, not CC, wlarc should be empty
  wlarc='${wl}'

  # See if GNU ld supports shared libraries.
  case $host_os in
  aix3* | aix4* | aix5*)
    # On AIX, the GNU linker is very broken
    # Note:Check GNU linker on AIX 5-IA64 when/if it becomes available.
    ld_shlibs=no
    cat <<EOF 1>&2

*** Warning: the GNU linker, at least up to release 2.9.1, is reported
*** to be unable to reliably create shared libraries on AIX.
*** Therefore, libtool is disabling shared libraries support.  If you
*** really care for shared libraries, you may want to modify your PATH
*** so that a non-GNU linker is found, and then restart.

EOF
    ;;

  amigaos*)
    archive_cmds='$rm $output_objdir/a2ixlibrary.data~$echo "#define NAME $libname" > $output_objdir/a2ixlibrary.data~$echo "#define LIBRARY_ID 1" >> $output_objdir/a2ixlibrary.data~$echo "#define VERSION $major" >> $output_objdir/a2ixlibrary.data~$echo "#define REVISION $revision" >> $output_objdir/a2ixlibrary.data~$AR $AR_FLAGS $lib $libobjs~$RANLIB $lib~(cd $output_objdir && a2ixlibrary -32)'
    hardcode_libdir_flag_spec='-L$libdir'
    hardcode_minus_L=yes

    # Samuel A. Falvo II <kc5tja@dolphin.openprojects.net> reports
    # that the semantics of dynamic libraries on AmigaOS, at least up
    # to version 4, is to share data among multiple programs linked
    # with the same dynamic library.  Since this doesn't match the
    # behavior of shared libraries on other platforms, we can use
    # them.
    ld_shlibs=no
    ;;

  beos*)
    if $LD --help 2>&1 | egrep ': supported targets:.* elf' > /dev/null; then
      allow_undefined_flag=unsupported
      # Joseph Beckenbach <jrb3@best.com> says some releases of gcc
      # support --undefined.  This deserves some investigation.  FIXME
      archive_cmds='$CC -nostart $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
    else
      ld_shlibs=no
    fi
    ;;

  cygwin* | mingw* | pw32*)
    # hardcode_libdir_flag_spec is actually meaningless, as there is
    # no search path for DLLs.
    hardcode_libdir_flag_spec='-L$libdir'
    allow_undefined_flag=unsupported
    always_export_symbols=yes

    extract_expsyms_cmds='test -f $output_objdir/impgen.c || \
      sed -e "/^# \/\* impgen\.c starts here \*\//,/^# \/\* impgen.c ends here \*\// { s/^# //;s/^# *$//; p; }" -e d < $''0 > $output_objdir/impgen.c~
      test -f $output_objdir/impgen.exe || (cd $output_objdir && \
      if test "x$HOST_CC" != "x" ; then $HOST_CC -o impgen impgen.c ; \
      else $CC -o impgen impgen.c ; fi)~
      $output_objdir/impgen $dir/$soroot > $output_objdir/$soname-def'

    old_archive_from_expsyms_cmds='$DLLTOOL --as=$AS --dllname $soname --def $output_objdir/$soname-def --output-lib $output_objdir/$newlib'

    # cygwin and mingw dlls have different entry points and sets of symbols
    # to exclude.
    # FIXME: what about values for MSVC?
    dll_entry=__cygwin_dll_entry@12
    dll_exclude_symbols=DllMain@12,_cygwin_dll_entry@12,_cygwin_noncygwin_dll_entry@12~
    case $host_os in
    mingw*)
      # mingw values
      dll_entry=_DllMainCRTStartup@12
      dll_exclude_symbols=DllMain@12,DllMainCRTStartup@12,DllEntryPoint@12~
      ;;
    esac

    # mingw and cygwin differ, and it's simplest to just exclude the union
    # of the two symbol sets.
    dll_exclude_symbols=DllMain@12,_cygwin_dll_entry@12,_cygwin_noncygwin_dll_entry@12,DllMainCRTStartup@12,DllEntryPoint@12

    # recent cygwin and mingw systems supply a stub DllMain which the user
    # can override, but on older systems we have to supply one (in ltdll.c)
    if test "x$lt_cv_need_dllmain" = "xyes"; then
      ltdll_obj='$output_objdir/$soname-ltdll.'"$ac_objext "
      ltdll_cmds='test -f $output_objdir/$soname-ltdll.c || sed -e "/^# \/\* ltdll\.c starts here \*\//,/^# \/\* ltdll.c ends here \*\// { s/^# //; p; }" -e d < $''0 > $output_objdir/$soname-ltdll.c~
	test -f $output_objdir/$soname-ltdll.$ac_objext || (cd $output_objdir && $CC -c $soname-ltdll.c)~'
    else
      ltdll_obj=
      ltdll_cmds=
    fi

    # Extract the symbol export list from an `--export-all' def file,
    # then regenerate the def file from the symbol export list, so that
    # the compiled dll only exports the symbol export list.
    # Be careful not to strip the DATA tag left be newer dlltools.
    export_symbols_cmds="$ltdll_cmds"'
      $DLLTOOL --export-all --exclude-symbols '$dll_exclude_symbols' --output-def $output_objdir/$soname-def '$ltdll_obj'$libobjs $convenience~
      sed -e "1,/EXPORTS/d" -e "s/ @ [[0-9]]*//" -e "s/ *;.*$//" < $output_objdir/$soname-def > $export_symbols'

    # If the export-symbols file already is a .def file (1st line
    # is EXPORTS), use it as is.
    # If DATA tags from a recent dlltool are present, honour them!
    archive_expsym_cmds='if test "x`sed 1q $export_symbols`" = xEXPORTS; then
	cp $export_symbols $output_objdir/$soname-def;
      else
	echo EXPORTS > $output_objdir/$soname-def;
	_lt_hint=1;
	cat $export_symbols | while read symbol; do
	 set dummy \$symbol;
	 case \[$]# in
	   2) echo "   \[$]2 @ \$_lt_hint ; " >> $output_objdir/$soname-def;;
	   4) echo "   \[$]2 \[$]3 \[$]4 ; " >> $output_objdir/$soname-def; _lt_hint=`expr \$_lt_hint - 1`;;
	   *) echo "     \[$]2 @ \$_lt_hint \[$]3 ; " >> $output_objdir/$soname-def;;
	 esac;
	 _lt_hint=`expr 1 + \$_lt_hint`;
	done;
      fi~
      '"$ltdll_cmds"'
      $CC -Wl,--base-file,$output_objdir/$soname-base '$lt_cv_cc_dll_switch' -Wl,-e,'$dll_entry' -o $output_objdir/$soname '$ltdll_obj'$libobjs $deplibs $compiler_flags~
      $DLLTOOL --as=$AS --dllname $soname --exclude-symbols '$dll_exclude_symbols' --def $output_objdir/$soname-def --base-file $output_objdir/$soname-base --output-exp $output_objdir/$soname-exp~
      $CC -Wl,--base-file,$output_objdir/$soname-base $output_objdir/$soname-exp '$lt_cv_cc_dll_switch' -Wl,-e,'$dll_entry' -o $output_objdir/$soname '$ltdll_obj'$libobjs $deplibs $compiler_flags~
      $DLLTOOL --as=$AS --dllname $soname --exclude-symbols '$dll_exclude_symbols' --def $output_objdir/$soname-def --base-file $output_objdir/$soname-base --output-exp $output_objdir/$soname-exp --output-lib $output_objdir/$libname.dll.a~
      $CC $output_objdir/$soname-exp '$lt_cv_cc_dll_switch' -Wl,-e,'$dll_entry' -o $output_objdir/$soname '$ltdll_obj'$libobjs $deplibs $compiler_flags'
    ;;

  netbsd*)
    if echo __ELF__ | $CC -E - | grep __ELF__ >/dev/null; then
      archive_cmds='$LD -Bshareable $libobjs $deplibs $linker_flags -o $lib'
      wlarc=
    else
      archive_cmds='$CC -shared -nodefaultlibs $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
      archive_expsym_cmds='$CC -shared -nodefaultlibs $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
    fi
    ;;

  solaris* | sysv5*)
    if $LD -v 2>&1 | egrep 'BFD 2\.8' > /dev/null; then
      ld_shlibs=no
      cat <<EOF 1>&2

*** Warning: The releases 2.8.* of the GNU linker cannot reliably
*** create shared libraries on Solaris systems.  Therefore, libtool
*** is disabling shared libraries support.  We urge you to upgrade GNU
*** binutils to release 2.9.1 or newer.  Another option is to modify
*** your PATH or compiler configuration so that the native linker is
*** used, and then restart.

EOF
    elif $LD --help 2>&1 | egrep ': supported targets:.* elf' > /dev/null; then
      archive_cmds='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
      archive_expsym_cmds='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
    else
      ld_shlibs=no
    fi
    ;;

  sunos4*)
    archive_cmds='$LD -assert pure-text -Bshareable -o $lib $libobjs $deplibs $linker_flags'
    wlarc=
    hardcode_direct=yes
    hardcode_shlibpath_var=no
    ;;

  *)
    if $LD --help 2>&1 | egrep ': supported targets:.* elf' > /dev/null; then
      archive_cmds='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
      archive_expsym_cmds='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
    else
      ld_shlibs=no
    fi
    ;;
  esac

  if test "$ld_shlibs" = yes; then
    runpath_var=LD_RUN_PATH
    hardcode_libdir_flag_spec='${wl}--rpath ${wl}$libdir'
    export_dynamic_flag_spec='${wl}--export-dynamic'
    case $host_os in
    cygwin* | mingw* | pw32*)
      # dlltool doesn't understand --whole-archive et. al.
      whole_archive_flag_spec=
      ;;
    *)
      # ancient GNU ld didn't support --whole-archive et. al.
      if $LD --help 2>&1 | egrep 'no-whole-archive' > /dev/null; then
	whole_archive_flag_spec="$wlarc"'--whole-archive$convenience '"$wlarc"'--no-whole-archive'
      else
	whole_archive_flag_spec=
      fi
      ;;
    esac
  fi
else
  # PORTME fill in a description of your system's linker (not GNU ld)
  case $host_os in
  aix3*)
    allow_undefined_flag=unsupported
    always_export_symbols=yes
    archive_expsym_cmds='$LD -o $output_objdir/$soname $libobjs $deplibs $linker_flags -bE:$export_symbols -T512 -H512 -bM:SRE~$AR $AR_FLAGS $lib $output_objdir/$soname'
    # Note: this linker hardcodes the directories in LIBPATH if there
    # are no directories specified by -L.
    hardcode_minus_L=yes
    if test "$GCC" = yes && test -z "$link_static_flag"; then
      # Neither direct hardcoding nor static linking is supported with a
      # broken collect2.
      hardcode_direct=unsupported
    fi
    ;;

  aix4* | aix5*)
    if test "$host_cpu" = ia64; then
      # On IA64, the linker does run time linking by default, so we don't
      # have to do anything special.
      aix_use_runtimelinking=no
      exp_sym_flag='-Bexport'
      no_entry_flag=""
    else
      aix_use_runtimelinking=no

      # Test if we are trying to use run time linking or normal
      # AIX style linking. If -brtl is somewhere in LDFLAGS, we
      # need to do runtime linking.
      case $host_os in aix4.[[23]]|aix4.[[23]].*|aix5*)
	for ld_flag in $LDFLAGS; do
	  case $ld_flag in
	  *-brtl*)
	    aix_use_runtimelinking=yes
	    break
	  ;;
	  esac
	done
      esac

      exp_sym_flag='-bexport'
      no_entry_flag='-bnoentry'
    fi

    # When large executables or shared objects are built, AIX ld can
    # have problems creating the table of contents.  If linking a library
    # or program results in "error TOC overflow" add -mminimal-toc to
    # CXXFLAGS/CFLAGS for g++/gcc.  In the cases where that is not
    # enough to fix the problem, add -Wl,-bbigtoc to LDFLAGS.

    hardcode_direct=yes
    archive_cmds=''
    hardcode_libdir_separator=':'
    if test "$GCC" = yes; then
      case $host_os in aix4.[[012]]|aix4.[[012]].*)
	collect2name=`${CC} -print-prog-name=collect2`
	if test -f "$collect2name" && \
	  strings "$collect2name" | grep resolve_lib_name >/dev/null
	then
	  # We have reworked collect2
	  hardcode_direct=yes
	else
	  # We have old collect2
	  hardcode_direct=unsupported
	  # It fails to find uninstalled libraries when the uninstalled
	  # path is not listed in the libpath.  Setting hardcode_minus_L
	  # to unsupported forces relinking
	  hardcode_minus_L=yes
	  hardcode_libdir_flag_spec='-L$libdir'
	  hardcode_libdir_separator=
	fi
      esac

      shared_flag='-shared'
    else
      # not using gcc
      if test "$host_cpu" = ia64; then
	shared_flag='${wl}-G'
      else
	if test "$aix_use_runtimelinking" = yes; then
	  shared_flag='${wl}-G'
	else
	  shared_flag='${wl}-bM:SRE'
	fi
      fi
    fi

    # It seems that -bexpall can do strange things, so it is better to
    # generate a list of symbols to export.
    always_export_symbols=yes
    if test "$aix_use_runtimelinking" = yes; then
      # Warning - without using the other runtime loading flags (-brtl),
      # -berok will link without error, but may produce a broken library.
      allow_undefined_flag='-berok'
      hardcode_libdir_flag_spec='${wl}-blibpath:$libdir:/usr/lib:/lib'
      archive_expsym_cmds="\$CC"' -o $output_objdir/$soname $libobjs $deplibs $compiler_flags `if test "x${allow_undefined_flag}" != "x"; then echo "${wl}${allow_undefined_flag}"; else :; fi` '"\${wl}$no_entry_flag \${wl}$exp_sym_flag:\$export_symbols $shared_flag"
    else
      if test "$host_cpu" = ia64; then
	hardcode_libdir_flag_spec='${wl}-R $libdir:/usr/lib:/lib'
	allow_undefined_flag="-z nodefs"
	archive_expsym_cmds="\$CC $shared_flag"' -o $output_objdir/$soname ${wl}-h$soname $libobjs $deplibs $compiler_flags ${wl}${allow_undefined_flag} '"\${wl}$no_entry_flag \${wl}$exp_sym_flag:\$export_symbols"
      else
	hardcode_libdir_flag_spec='${wl}-bnolibpath ${wl}-blibpath:$libdir:/usr/lib:/lib'
	# Warning - without using the other run time loading flags,
	# -berok will link without error, but may produce a broken library.
	allow_undefined_flag='${wl}-berok'
	# This is a bit strange, but is similar to how AIX traditionally builds
	# it's shared libraries.
	archive_expsym_cmds="\$CC $shared_flag"' -o $output_objdir/$soname $libobjs $deplibs $compiler_flags ${allow_undefined_flag} '"\${wl}$no_entry_flag \${wl}$exp_sym_flag:\$export_symbols"' ~$AR -crlo $objdir/$libname$release.a $objdir/$soname'
      fi
    fi
    ;;

  amigaos*)
    archive_cmds='$rm $output_objdir/a2ixlibrary.data~$echo "#define NAME $libname" > $output_objdir/a2ixlibrary.data~$echo "#define LIBRARY_ID 1" >> $output_objdir/a2ixlibrary.data~$echo "#define VERSION $major" >> $output_objdir/a2ixlibrary.data~$echo "#define REVISION $revision" >> $output_objdir/a2ixlibrary.data~$AR $AR_FLAGS $lib $libobjs~$RANLIB $lib~(cd $output_objdir && a2ixlibrary -32)'
    hardcode_libdir_flag_spec='-L$libdir'
    hardcode_minus_L=yes
    # see comment about different semantics on the GNU ld section
    ld_shlibs=no
    ;;

  cygwin* | mingw* | pw32*)
    # When not using gcc, we currently assume that we are using
    # Microsoft Visual C++.
    # hardcode_libdir_flag_spec is actually meaningless, as there is
    # no search path for DLLs.
    hardcode_libdir_flag_spec=' '
    allow_undefined_flag=unsupported
    # Tell ltmain to make .lib files, not .a files.
    libext=lib
    # FIXME: Setting linknames here is a bad hack.
    archive_cmds='$CC -o $lib $libobjs $compiler_flags `echo "$deplibs" | sed -e '\''s/ -lc$//'\''` -link -dll~linknames='
    # The linker will automatically build a .lib file if we build a DLL.
    old_archive_from_new_cmds='true'
    # FIXME: Should let the user specify the lib program.
    old_archive_cmds='lib /OUT:$oldlib$oldobjs$old_deplibs'
    fix_srcfile_path='`cygpath -w "$srcfile"`'
    ;;

  darwin* | rhapsody*)
    case "$host_os" in
    rhapsody* | darwin1.[[012]])
      allow_undefined_flag='-undefined suppress'
      ;;
    *) # Darwin 1.3 on
      allow_undefined_flag='-flat_namespace -undefined suppress'
      ;;
    esac
    # FIXME: Relying on posixy $() will cause problems for
    #        cross-compilation, but unfortunately the echo tests do not
    #        yet detect zsh echo's removal of \ escapes.  Also zsh mangles
    #	     `"' quotes if we put them in here... so don't!
    archive_cmds='$CC -r -keep_private_externs -nostdlib -o ${lib}-master.o $libobjs && $CC $(test .$module = .yes && echo -bundle || echo -dynamiclib) $allow_undefined_flag -o $lib ${lib}-master.o $deplibs$linker_flags $(test .$module != .yes && echo -install_name $rpath/$soname $verstring)'
    # We need to add '_' to the symbols in $export_symbols first
    #archive_expsym_cmds="$archive_cmds"' && strip -s $export_symbols'
    hardcode_direct=yes
    hardcode_shlibpath_var=no
    whole_archive_flag_spec='-all_load $convenience'
    ;;

  freebsd1*)
    ld_shlibs=no
    ;;

  # FreeBSD 2.2.[012] allows us to include c++rt0.o to get C++ constructor
  # support.  Future versions do this automatically, but an explicit c++rt0.o
  # does not break anything, and helps significantly (at the cost of a little
  # extra space).
  freebsd2.2*)
    archive_cmds='$LD -Bshareable -o $lib $libobjs $deplibs $linker_flags /usr/lib/c++rt0.o'
    hardcode_libdir_flag_spec='-R$libdir'
    hardcode_direct=yes
    hardcode_shlibpath_var=no
    ;;

  # Unfortunately, older versions of FreeBSD 2 do not have this feature.
  freebsd2*)
    archive_cmds='$LD -Bshareable -o $lib $libobjs $deplibs $linker_flags'
    hardcode_direct=yes
    hardcode_minus_L=yes
    hardcode_shlibpath_var=no
    ;;

  # FreeBSD 3 and greater uses gcc -shared to do shared libraries.
  freebsd*)
    archive_cmds='$CC -shared -o $lib $libobjs $deplibs $compiler_flags'
    hardcode_libdir_flag_spec='-R$libdir'
    hardcode_direct=yes
    hardcode_shlibpath_var=no
    ;;

  hpux9* | hpux10* | hpux11*)
    case $host_os in
    hpux9*) archive_cmds='$rm $output_objdir/$soname~$LD -b +b $install_libdir -o $output_objdir/$soname $libobjs $deplibs $linker_flags~test $output_objdir/$soname = $lib || mv $output_objdir/$soname $lib' ;;
    *) archive_cmds='$LD -b +h $soname +b $install_libdir -o $lib $libobjs $deplibs $linker_flags' ;;
    esac
    hardcode_libdir_flag_spec='${wl}+b ${wl}$libdir'
    hardcode_libdir_separator=:
    hardcode_direct=yes
    hardcode_minus_L=yes # Not in the search PATH, but as the default
			 # location of the library.
    export_dynamic_flag_spec='${wl}-E'
    ;;

  irix5* | irix6* | nonstopux*)
    if test "$GCC" = yes; then
      archive_cmds='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname ${wl}$soname `test -n "$verstring" && echo ${wl}-set_version ${wl}$verstring` ${wl}-update_registry ${wl}${output_objdir}/so_locations -o $lib'
      hardcode_libdir_flag_spec='${wl}-rpath ${wl}$libdir'
    else
      archive_cmds='$LD -shared $libobjs $deplibs $linker_flags -soname $soname `test -n "$verstring" && echo -set_version $verstring` -update_registry ${output_objdir}/so_locations -o $lib'
      hardcode_libdir_flag_spec='-rpath $libdir'
    fi
    hardcode_libdir_separator=:
    link_all_deplibs=yes
    ;;

  netbsd*)
    if echo __ELF__ | $CC -E - | grep __ELF__ >/dev/null; then
      archive_cmds='$LD -Bshareable -o $lib $libobjs $deplibs $linker_flags'  # a.out
    else
      archive_cmds='$LD -shared -o $lib $libobjs $deplibs $linker_flags'      # ELF
    fi
    hardcode_libdir_flag_spec='-R$libdir'
    hardcode_direct=yes
    hardcode_shlibpath_var=no
    ;;

  newsos6)
    archive_cmds='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
    hardcode_direct=yes
    hardcode_libdir_flag_spec='${wl}-rpath ${wl}$libdir'
    hardcode_libdir_separator=:
    hardcode_shlibpath_var=no
    ;;

  openbsd*)
    hardcode_direct=yes
    hardcode_shlibpath_var=no
    if test -z "`echo __ELF__ | $CC -E - | grep __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powerpc"; then
      archive_cmds='$CC -shared $pic_flag -o $lib $libobjs $deplibs $compiler_flags'
      hardcode_libdir_flag_spec='${wl}-rpath,$libdir'
      export_dynamic_flag_spec='${wl}-E'
    else
      case "$host_os" in
      openbsd[[01]].* | openbsd2.[[0-7]] | openbsd2.[[0-7]].*)
	archive_cmds='$LD -Bshareable -o $lib $libobjs $deplibs $linker_flags'
	hardcode_libdir_flag_spec='-R$libdir'
        ;;
      *)
        archive_cmds='$CC -shared $pic_flag -o $lib $libobjs $deplibs $compiler_flags'
        hardcode_libdir_flag_spec='${wl}-rpath,$libdir'
        ;;
      esac
    fi
    ;;

  os2*)
    hardcode_libdir_flag_spec='-L$libdir'
    hardcode_minus_L=yes
    allow_undefined_flag=unsupported
    archive_cmds='$echo "LIBRARY $libname INITINSTANCE" > $output_objdir/$libname.def~$echo "DESCRIPTION \"$libname\"" >> $output_objdir/$libname.def~$echo DATA >> $output_objdir/$libname.def~$echo " SINGLE NONSHARED" >> $output_objdir/$libname.def~$echo EXPORTS >> $output_objdir/$libname.def~emxexp $libobjs >> $output_objdir/$libname.def~$CC -Zdll -Zcrtdll -o $lib $libobjs $deplibs $compiler_flags $output_objdir/$libname.def'
    old_archive_from_new_cmds='emximp -o $output_objdir/$libname.a $output_objdir/$libname.def'
    ;;

  osf3*)
    if test "$GCC" = yes; then
      allow_undefined_flag=' ${wl}-expect_unresolved ${wl}\*'
      archive_cmds='$CC -shared${allow_undefined_flag} $libobjs $deplibs $compiler_flags ${wl}-soname ${wl}$soname `test -n "$verstring" && echo ${wl}-set_version ${wl}$verstring` ${wl}-update_registry ${wl}${output_objdir}/so_locations -o $lib'
    else
      allow_undefined_flag=' -expect_unresolved \*'
      archive_cmds='$LD -shared${allow_undefined_flag} $libobjs $deplibs $linker_flags -soname $soname `test -n "$verstring" && echo -set_version $verstring` -update_registry ${output_objdir}/so_locations -o $lib'
    fi
    hardcode_libdir_flag_spec='${wl}-rpath ${wl}$libdir'
    hardcode_libdir_separator=:
    ;;

  osf4* | osf5*)	# as osf3* with the addition of -msym flag
    if test "$GCC" = yes; then
      allow_undefined_flag=' ${wl}-expect_unresolved ${wl}\*'
      archive_cmds='$CC -shared${allow_undefined_flag} $libobjs $deplibs $compiler_flags ${wl}-msym ${wl}-soname ${wl}$soname `test -n "$verstring" && echo ${wl}-set_version ${wl}$verstring` ${wl}-update_registry ${wl}${output_objdir}/so_locations -o $lib'
      hardcode_libdir_flag_spec='${wl}-rpath ${wl}$libdir'
    else
      allow_undefined_flag=' -expect_unresolved \*'
      archive_cmds='$LD -shared${allow_undefined_flag} $libobjs $deplibs $linker_flags -msym -soname $soname `test -n "$verstring" && echo -set_version $verstring` -update_registry ${output_objdir}/so_locations -o $lib'
      archive_expsym_cmds='for i in `cat $export_symbols`; do printf "-exported_symbol " >> $lib.exp; echo "\$i" >> $lib.exp; done; echo "-hidden">> $lib.exp~
      $LD -shared${allow_undefined_flag} -input $lib.exp $linker_flags $libobjs $deplibs -soname $soname `test -n "$verstring" && echo -set_version $verstring` -update_registry ${objdir}/so_locations -o $lib~$rm $lib.exp'

      #Both c and cxx compiler support -rpath directly
      hardcode_libdir_flag_spec='-rpath $libdir'
    fi
    hardcode_libdir_separator=:
    ;;

  sco3.2v5*)
    archive_cmds='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
    hardcode_shlibpath_var=no
    runpath_var=LD_RUN_PATH
    hardcode_runpath_var=yes
    export_dynamic_flag_spec='${wl}-Bexport'
    ;;

  solaris*)
    # gcc --version < 3.0 without binutils cannot create self contained
    # shared libraries reliably, requiring libgcc.a to resolve some of
    # the object symbols generated in some cases.  Libraries that use
    # assert need libgcc.a to resolve __eprintf, for example.  Linking
    # a copy of libgcc.a into every shared library to guarantee resolving
    # such symbols causes other problems:  According to Tim Van Holder
    # <tim.van.holder@pandora.be>, C++ libraries end up with a separate
    # (to the application) exception stack for one thing.
    no_undefined_flag=' -z defs'
    if test "$GCC" = yes; then
      case `$CC --version 2>/dev/null` in
      [[12]].*)
	cat <<EOF 1>&2

*** Warning: Releases of GCC earlier than version 3.0 cannot reliably
*** create self contained shared libraries on Solaris systems, without
*** introducing a dependency on libgcc.a.  Therefore, libtool is disabling
*** -no-undefined support, which will at least allow you to build shared
*** libraries.  However, you may find that when you link such libraries
*** into an application without using GCC, you have to manually add
*** \`gcc --print-libgcc-file-name\` to the link command.  We urge you to
*** upgrade to a newer version of GCC.  Another option is to rebuild your
*** current GCC to use the GNU linker from GNU binutils 2.9.1 or newer.

EOF
        no_undefined_flag=
	;;
      esac
    fi
    # $CC -shared without GNU ld will not create a library from C++
    # object files and a static libstdc++, better avoid it by now
    archive_cmds='$LD -G${allow_undefined_flag} -h $soname -o $lib $libobjs $deplibs $linker_flags'
    archive_expsym_cmds='$echo "{ global:" > $lib.exp~cat $export_symbols | sed -e "s/\(.*\)/\1;/" >> $lib.exp~$echo "local: *; };" >> $lib.exp~
		$LD -G${allow_undefined_flag} -M $lib.exp -h $soname -o $lib $libobjs $deplibs $linker_flags~$rm $lib.exp'
    hardcode_libdir_flag_spec='-R$libdir'
    hardcode_shlibpath_var=no
    case $host_os in
    solaris2.[[0-5]] | solaris2.[[0-5]].*) ;;
    *) # Supported since Solaris 2.6 (maybe 2.5.1?)
      whole_archive_flag_spec='-z allextract$convenience -z defaultextract' ;;
    esac
    link_all_deplibs=yes
    ;;

  sunos4*)
    if test "x$host_vendor" = xsequent; then
      # Use $CC to link under sequent, because it throws in some extra .o
      # files that make .init and .fini sections work.
      archive_cmds='$CC -G ${wl}-h $soname -o $lib $libobjs $deplibs $compiler_flags'
    else
      archive_cmds='$LD -assert pure-text -Bstatic -o $lib $libobjs $deplibs $linker_flags'
    fi
    hardcode_libdir_flag_spec='-L$libdir'
    hardcode_direct=yes
    hardcode_minus_L=yes
    hardcode_shlibpath_var=no
    ;;

  sysv4)
    case $host_vendor in
      sni)
        archive_cmds='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
        hardcode_direct=yes # is this really true???
        ;;
      siemens)
        ## LD is ld it makes a PLAMLIB
        ## CC just makes a GrossModule.
        archive_cmds='$LD -G -o $lib $libobjs $deplibs $linker_flags'
        reload_cmds='$CC -r -o $output$reload_objs'
        hardcode_direct=no
        ;;
      motorola)
        archive_cmds='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
        hardcode_direct=no #Motorola manual says yes, but my tests say they lie
        ;;
    esac
    runpath_var='LD_RUN_PATH'
    hardcode_shlibpath_var=no
    ;;

  sysv4.3*)
    archive_cmds='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
    hardcode_shlibpath_var=no
    export_dynamic_flag_spec='-Bexport'
    ;;

  sysv5*)
    no_undefined_flag=' -z text'
    # $CC -shared without GNU ld will not create a library from C++
    # object files and a static libstdc++, better avoid it by now
    archive_cmds='$LD -G${allow_undefined_flag} -h $soname -o $lib $libobjs $deplibs $linker_flags'
    archive_expsym_cmds='$echo "{ global:" > $lib.exp~cat $export_symbols | sed -e "s/\(.*\)/\1;/" >> $lib.exp~$echo "local: *; };" >> $lib.exp~
		$LD -G${allow_undefined_flag} -M $lib.exp -h $soname -o $lib $libobjs $deplibs $linker_flags~$rm $lib.exp'
    hardcode_libdir_flag_spec=
    hardcode_shlibpath_var=no
    runpath_var='LD_RUN_PATH'
    ;;

  uts4*)
    archive_cmds='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
    hardcode_libdir_flag_spec='-L$libdir'
    hardcode_shlibpath_var=no
    ;;

  dgux*)
    archive_cmds='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
    hardcode_libdir_flag_spec='-L$libdir'
    hardcode_shlibpath_var=no
    ;;

  sysv4*MP*)
    if test -d /usr/nec; then
      archive_cmds='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
      hardcode_shlibpath_var=no
      runpath_var=LD_RUN_PATH
      hardcode_runpath_var=yes
      ld_shlibs=yes
    fi
    ;;

  sysv4.2uw2*)
    archive_cmds='$LD -G -o $lib $libobjs $deplibs $linker_flags'
    hardcode_direct=yes
    hardcode_minus_L=no
    hardcode_shlibpath_var=no
    hardcode_runpath_var=yes
    runpath_var=LD_RUN_PATH
    ;;

  sysv5uw7* | unixware7*)
    no_undefined_flag='${wl}-z ${wl}text'
    if test "$GCC" = yes; then
      archive_cmds='$CC -shared ${wl}-h ${wl}$soname -o $lib $libobjs $deplibs $compiler_flags'
    else
      archive_cmds='$CC -G ${wl}-h ${wl}$soname -o $lib $libobjs $deplibs $compiler_flags'
    fi
    runpath_var='LD_RUN_PATH'
    hardcode_shlibpath_var=no
    ;;

  *)
    ld_shlibs=no
    ;;
  esac
fi
AC_MSG_RESULT([$ld_shlibs])
test "$ld_shlibs" = no && can_build_shared=no

# Check hardcoding attributes.
AC_MSG_CHECKING([how to hardcode library paths into programs])
hardcode_action=
if test -n "$hardcode_libdir_flag_spec" || \
   test -n "$runpath_var"; then

  # We can hardcode non-existant directories.
  if test "$hardcode_direct" != no &&
     # If the only mechanism to avoid hardcoding is shlibpath_var, we
     # have to relink, otherwise we might link with an installed library
     # when we should be linking with a yet-to-be-installed one
     ## test "$hardcode_shlibpath_var" != no &&
     test "$hardcode_minus_L" != no; then
    # Linking always hardcodes the temporary library directory.
    hardcode_action=relink
  else
    # We can link without hardcoding, and we can hardcode nonexisting dirs.
    hardcode_action=immediate
  fi
else
  # We cannot hardcode anything, or else we can only hardcode existing
  # directories.
  hardcode_action=unsupported
fi
AC_MSG_RESULT([$hardcode_action])

striplib=
old_striplib=
AC_MSG_CHECKING([whether stripping libraries is possible])
if test -n "$STRIP" && $STRIP -V 2>&1 | grep "GNU strip" >/dev/null; then
  test -z "$old_striplib" && old_striplib="$STRIP --strip-debug"
  test -z "$striplib" && striplib="$STRIP --strip-unneeded"
  AC_MSG_RESULT([yes])
else
  AC_MSG_RESULT([no])
fi

reload_cmds='$LD$reload_flag -o $output$reload_objs'
test -z "$deplibs_check_method" && deplibs_check_method=unknown

# PORTME Fill in your ld.so characteristics
AC_MSG_CHECKING([dynamic linker characteristics])
library_names_spec=
libname_spec='lib$name'
soname_spec=
postinstall_cmds=
postuninstall_cmds=
finish_cmds=
finish_eval=
shlibpath_var=
shlibpath_overrides_runpath=unknown
version_type=none
dynamic_linker="$host_os ld.so"
sys_lib_dlsearch_path_spec="/lib /usr/lib"
sys_lib_search_path_spec="/lib /usr/lib /usr/local/lib"

case $host_os in
aix3*)
  version_type=linux
  library_names_spec='${libname}${release}.so$versuffix $libname.a'
  shlibpath_var=LIBPATH

  # AIX has no versioning support, so we append a major version to the name.
  soname_spec='${libname}${release}.so$major'
  ;;

aix4* | aix5*)
  version_type=linux
  need_lib_prefix=no
  need_version=no
  hardcode_into_libs=yes
  if test "$host_cpu" = ia64; then
    # AIX 5 supports IA64
    library_names_spec='${libname}${release}.so$major ${libname}${release}.so$versuffix $libname.so'
    shlibpath_var=LD_LIBRARY_PATH
  else
    # With GCC up to 2.95.x, collect2 would create an import file
    # for dependence libraries.  The import file would start with
    # the line `#! .'.  This would cause the generated library to
    # depend on `.', always an invalid library.  This was fixed in
    # development snapshots of GCC prior to 3.0.
    case $host_os in
      aix4 | aix4.[[01]] | aix4.[[01]].*)
	if { echo '#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 97)'
	     echo ' yes '
	     echo '#endif'; } | ${CC} -E - | grep yes > /dev/null; then
	  :
	else
	  can_build_shared=no
	fi
	;;
    esac
    # AIX (on Power*) has no versioning support, so currently we can
    # not hardcode correct soname into executable. Probably we can
    # add versioning support to collect2, so additional links can
    # be useful in future.
    if test "$aix_use_runtimelinking" = yes; then
      # If using run time linking (on AIX 4.2 or later) use lib<name>.so
      # instead of lib<name>.a to let people know that these are not
      # typical AIX shared libraries.
      library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
    else
      # We preserve .a as extension for shared libraries through AIX4.2
      # and later when we are not doing run time linking.
      library_names_spec='${libname}${release}.a $libname.a'
      soname_spec='${libname}${release}.so$major'
    fi
    shlibpath_var=LIBPATH
  fi
  hardcode_into_libs=yes
  ;;

amigaos*)
  library_names_spec='$libname.ixlibrary $libname.a'
  # Create ${libname}_ixlibrary.a entries in /sys/libs.
  finish_eval='for lib in `ls $libdir/*.ixlibrary 2>/dev/null`; do libname=`$echo "X$lib" | $Xsed -e '\''s%^.*/\([[^/]]*\)\.ixlibrary$%\1%'\''`; test $rm /sys/libs/${libname}_ixlibrary.a; $show "(cd /sys/libs && $LN_S $lib ${libname}_ixlibrary.a)"; (cd /sys/libs && $LN_S $lib ${libname}_ixlibrary.a) || exit 1; done'
  ;;

beos*)
  library_names_spec='${libname}.so'
  dynamic_linker="$host_os ld.so"
  shlibpath_var=LIBRARY_PATH
  ;;

bsdi4*)
  version_type=linux
  need_version=no
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
  soname_spec='${libname}${release}.so$major'
  finish_cmds='PATH="\$PATH:/sbin" ldconfig $libdir'
  shlibpath_var=LD_LIBRARY_PATH
  sys_lib_search_path_spec="/shlib /usr/lib /usr/X11/lib /usr/contrib/lib /lib /usr/local/lib"
  sys_lib_dlsearch_path_spec="/shlib /usr/lib /usr/local/lib"
  export_dynamic_flag_spec=-rdynamic
  # the default ld.so.conf also contains /usr/contrib/lib and
  # /usr/X11R6/lib (/usr/X11 is a link to /usr/X11R6), but let us allow
  # libtool to hard-code these into programs
  ;;

cygwin* | mingw* | pw32*)
  version_type=windows
  need_version=no
  need_lib_prefix=no
  case $GCC,$host_os in
  yes,cygwin*)
    library_names_spec='$libname.dll.a'
    soname_spec='`echo ${libname} | sed -e 's/^lib/cyg/'``echo ${release} | sed -e 's/[[.]]/-/g'`${versuffix}.dll'
    postinstall_cmds='dlpath=`bash 2>&1 -c '\''. $dir/${file}i;echo \$dlname'\''`~
      dldir=$destdir/`dirname \$dlpath`~
      test -d \$dldir || mkdir -p \$dldir~
      $install_prog .libs/$dlname \$dldir/$dlname'
    postuninstall_cmds='dldll=`bash 2>&1 -c '\''. $file; echo \$dlname'\''`~
      dlpath=$dir/\$dldll~
       $rm \$dlpath'
    ;;
  yes,mingw*)
    library_names_spec='${libname}`echo ${release} | sed -e 's/[[.]]/-/g'`${versuffix}.dll'
    sys_lib_search_path_spec=`$CC -print-search-dirs | grep "^libraries:" | sed -e "s/^libraries://" -e "s/;/ /g" -e "s,=/,/,g"`
    ;;
  yes,pw32*)
    library_names_spec='`echo ${libname} | sed -e 's/^lib/pw/'``echo ${release} | sed -e 's/[.]/-/g'`${versuffix}.dll'
    ;;
  *)
    library_names_spec='${libname}`echo ${release} | sed -e 's/[[.]]/-/g'`${versuffix}.dll $libname.lib'
    ;;
  esac
  dynamic_linker='Win32 ld.exe'
  # FIXME: first we should search . and the directory the executable is in
  shlibpath_var=PATH
  ;;

darwin* | rhapsody*)
  dynamic_linker="$host_os dyld"
  version_type=darwin
  need_lib_prefix=no
  need_version=no
  # FIXME: Relying on posixy $() will cause problems for
  #        cross-compilation, but unfortunately the echo tests do not
  #        yet detect zsh echo's removal of \ escapes.
  library_names_spec='${libname}${release}${versuffix}.$(test .$module = .yes && echo so || echo dylib) ${libname}${release}${major}.$(test .$module = .yes && echo so || echo dylib) ${libname}.$(test .$module = .yes && echo so || echo dylib)'
  soname_spec='${libname}${release}${major}.$(test .$module = .yes && echo so || echo dylib)'
  shlibpath_overrides_runpath=yes
  shlibpath_var=DYLD_LIBRARY_PATH
  ;;

freebsd1*)
  dynamic_linker=no
  ;;

freebsd*)
  objformat=`test -x /usr/bin/objformat && /usr/bin/objformat || echo aout`
  version_type=freebsd-$objformat
  case $version_type in
    freebsd-elf*)
      library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so $libname.so'
      need_version=no
      need_lib_prefix=no
      ;;
    freebsd-*)
      library_names_spec='${libname}${release}.so$versuffix $libname.so$versuffix'
      need_version=yes
      ;;
  esac
  shlibpath_var=LD_LIBRARY_PATH
  case $host_os in
  freebsd2*)
    shlibpath_overrides_runpath=yes
    ;;
  *)
    shlibpath_overrides_runpath=no
    hardcode_into_libs=yes
    ;;
  esac
  ;;

gnu*)
  version_type=linux
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so${major} ${libname}.so'
  soname_spec='${libname}${release}.so$major'
  shlibpath_var=LD_LIBRARY_PATH
  hardcode_into_libs=yes
  ;;

hpux9* | hpux10* | hpux11*)
  # Give a soname corresponding to the major version so that dld.sl refuses to
  # link against other versions.
  dynamic_linker="$host_os dld.sl"
  version_type=sunos
  need_lib_prefix=no
  need_version=no
  shlibpath_var=SHLIB_PATH
  shlibpath_overrides_runpath=no # +s is required to enable SHLIB_PATH
  library_names_spec='${libname}${release}.sl$versuffix ${libname}${release}.sl$major $libname.sl'
  soname_spec='${libname}${release}.sl$major'
  # HP-UX runs *really* slowly unless shared libraries are mode 555.
  postinstall_cmds='chmod 555 $lib'
  ;;

irix5* | irix6* | nonstopux*)
  case $host_os in
    nonstopux*) version_type=nonstopux ;;
    *)          version_type=irix ;;
  esac
  need_lib_prefix=no
  need_version=no
  soname_spec='${libname}${release}.so$major'
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major ${libname}${release}.so $libname.so'
  case $host_os in
  irix5* | nonstopux*)
    libsuff= shlibsuff=
    ;;
  *)
    case $LD in # libtool.m4 will add one of these switches to LD
    *-32|*"-32 ") libsuff= shlibsuff= libmagic=32-bit;;
    *-n32|*"-n32 ") libsuff=32 shlibsuff=N32 libmagic=N32;;
    *-64|*"-64 ") libsuff=64 shlibsuff=64 libmagic=64-bit;;
    *) libsuff= shlibsuff= libmagic=never-match;;
    esac
    ;;
  esac
  shlibpath_var=LD_LIBRARY${shlibsuff}_PATH
  shlibpath_overrides_runpath=no
  sys_lib_search_path_spec="/usr/lib${libsuff} /lib${libsuff} /usr/local/lib${libsuff}"
  sys_lib_dlsearch_path_spec="/usr/lib${libsuff} /lib${libsuff}"
  ;;

# No shared lib support for Linux oldld, aout, or coff.
linux-gnuoldld* | linux-gnuaout* | linux-gnucoff*)
  dynamic_linker=no
  ;;

# This must be Linux ELF.
linux-gnu*)
  version_type=linux
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
  soname_spec='${libname}${release}.so$major'
  finish_cmds='PATH="\$PATH:/sbin" ldconfig -n $libdir'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=no
  # This implies no fast_install, which is unacceptable.
  # Some rework will be needed to allow for fast_install
  # before this can be enabled.
  hardcode_into_libs=yes

  # We used to test for /lib/ld.so.1 and disable shared libraries on
  # powerpc, because MkLinux only supported shared libraries with the
  # GNU dynamic linker.  Since this was broken with cross compilers,
  # most powerpc-linux boxes support dynamic linking these days and
  # people can always --disable-shared, the test was removed, and we
  # assume the GNU/Linux dynamic linker is in use.
  dynamic_linker='GNU/Linux ld.so'
  ;;

netbsd*)
  version_type=sunos
  need_lib_prefix=no
  need_version=no
  if echo __ELF__ | $CC -E - | grep __ELF__ >/dev/null; then
    library_names_spec='${libname}${release}.so$versuffix ${libname}.so$versuffix'
    finish_cmds='PATH="\$PATH:/sbin" ldconfig -m $libdir'
    dynamic_linker='NetBSD (a.out) ld.so'
  else
    library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major ${libname}${release}.so ${libname}.so'
    soname_spec='${libname}${release}.so$major'
    dynamic_linker='NetBSD ld.elf_so'
  fi
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  hardcode_into_libs=yes
  ;;

newsos6)
  version_type=linux
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  ;;

openbsd*)
  version_type=sunos
  need_lib_prefix=no
  need_version=no
  if test -z "`echo __ELF__ | $CC -E - | grep __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powerpc"; then
    case "$host_os" in
    openbsd2.[[89]] | openbsd2.[[89]].*)
      shlibpath_overrides_runpath=no
      ;;
    *)
      shlibpath_overrides_runpath=yes
      ;;
    esac
  else
    shlibpath_overrides_runpath=yes
  fi
  library_names_spec='${libname}${release}.so$versuffix ${libname}.so$versuffix'
  finish_cmds='PATH="\$PATH:/sbin" ldconfig -m $libdir'
  shlibpath_var=LD_LIBRARY_PATH
  ;;

os2*)
  libname_spec='$name'
  need_lib_prefix=no
  library_names_spec='$libname.dll $libname.a'
  dynamic_linker='OS/2 ld.exe'
  shlibpath_var=LIBPATH
  ;;

osf3* | osf4* | osf5*)
  version_type=osf
  need_version=no
  soname_spec='${libname}${release}.so$major'
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
  shlibpath_var=LD_LIBRARY_PATH
  sys_lib_search_path_spec="/usr/shlib /usr/ccs/lib /usr/lib/cmplrs/cc /usr/lib /usr/local/lib /var/shlib"
  sys_lib_dlsearch_path_spec="$sys_lib_search_path_spec"
  hardcode_into_libs=yes
  ;;

sco3.2v5*)
  version_type=osf
  soname_spec='${libname}${release}.so$major'
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
  shlibpath_var=LD_LIBRARY_PATH
  ;;

solaris*)
  version_type=linux
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
  soname_spec='${libname}${release}.so$major'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  hardcode_into_libs=yes
  # ldd complains unless libraries are executable
  postinstall_cmds='chmod +x $lib'
  ;;

sunos4*)
  version_type=sunos
  library_names_spec='${libname}${release}.so$versuffix ${libname}.so$versuffix'
  finish_cmds='PATH="\$PATH:/usr/etc" ldconfig $libdir'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  if test "$with_gnu_ld" = yes; then
    need_lib_prefix=no
  fi
  need_version=yes
  ;;

sysv4 | sysv4.2uw2* | sysv4.3* | sysv5*)
  version_type=linux
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
  soname_spec='${libname}${release}.so$major'
  shlibpath_var=LD_LIBRARY_PATH
  case $host_vendor in
    sni)
      shlibpath_overrides_runpath=no
      need_lib_prefix=no
      export_dynamic_flag_spec='${wl}-Blargedynsym'
      runpath_var=LD_RUN_PATH
      ;;
    siemens)
      need_lib_prefix=no
      ;;
    motorola)
      need_lib_prefix=no
      need_version=no
      shlibpath_overrides_runpath=no
      sys_lib_search_path_spec='/lib /usr/lib /usr/ccs/lib'
      ;;
  esac
  ;;

uts4*)
  version_type=linux
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
  soname_spec='${libname}${release}.so$major'
  shlibpath_var=LD_LIBRARY_PATH
  ;;

dgux*)
  version_type=linux
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}.so$versuffix ${libname}${release}.so$major $libname.so'
  soname_spec='${libname}${release}.so$major'
  shlibpath_var=LD_LIBRARY_PATH
  ;;

sysv4*MP*)
  if test -d /usr/nec ;then
    version_type=linux
    library_names_spec='$libname.so.$versuffix $libname.so.$major $libname.so'
    soname_spec='$libname.so.$major'
    shlibpath_var=LD_LIBRARY_PATH
  fi
  ;;

*)
  dynamic_linker=no
  ;;
esac
AC_MSG_RESULT([$dynamic_linker])
test "$dynamic_linker" = no && can_build_shared=no

# Report the final consequences.
AC_MSG_CHECKING([if libtool supports shared libraries])
AC_MSG_RESULT([$can_build_shared])

AC_MSG_CHECKING([whether to build shared libraries])
test "$can_build_shared" = "no" && enable_shared=no

# On AIX, shared libraries and static libraries use the same namespace, and
# are all built from PIC.
case "$host_os" in
aix3*)
  test "$enable_shared" = yes && enable_static=no
  if test -n "$RANLIB"; then
    archive_cmds="$archive_cmds~\$RANLIB \$lib"
    postinstall_cmds='$RANLIB $lib'
  fi
  ;;

aix4*)
  if test "$host_cpu" != ia64 && test "$aix_use_runtimelinking" = no ; then
    test "$enable_shared" = yes && enable_static=no
  fi
  ;;
esac
AC_MSG_RESULT([$enable_shared])

AC_MSG_CHECKING([whether to build static libraries])
# Make sure either enable_shared or enable_static is yes.
test "$enable_shared" = yes || enable_static=yes
AC_MSG_RESULT([$enable_static])

if test "$hardcode_action" = relink; then
  # Fast installation is not supported
  enable_fast_install=no
elif test "$shlibpath_overrides_runpath" = yes ||
     test "$enable_shared" = no; then
  # Fast installation is not necessary
  enable_fast_install=needless
fi

variables_saved_for_relink="PATH $shlibpath_var $runpath_var"
if test "$GCC" = yes; then
  variables_saved_for_relink="$variables_saved_for_relink GCC_EXEC_PREFIX COMPILER_PATH LIBRARY_PATH"
fi

AC_LIBTOOL_DLOPEN_SELF

if test "$enable_shared" = yes && test "$GCC" = yes; then
  case $archive_cmds in
  *'~'*)
    # FIXME: we may have to deal with multi-command sequences.
    ;;
  '$CC '*)
    # Test whether the compiler implicitly links with -lc since on some
    # systems, -lgcc has to come before -lc. If gcc already passes -lc
    # to ld, don't add -lc before -lgcc.
    AC_MSG_CHECKING([whether -lc should be explicitly linked in])
    AC_CACHE_VAL([lt_cv_archive_cmds_need_lc],
    [$rm conftest*
    echo 'static int dummy;' > conftest.$ac_ext

    if AC_TRY_EVAL(ac_compile); then
      soname=conftest
      lib=conftest
      libobjs=conftest.$ac_objext
      deplibs=
      wl=$lt_cv_prog_cc_wl
      compiler_flags=-v
      linker_flags=-v
      verstring=
      output_objdir=.
      libname=conftest
      save_allow_undefined_flag=$allow_undefined_flag
      allow_undefined_flag=
      if AC_TRY_EVAL(archive_cmds 2\>\&1 \| grep \" -lc \" \>/dev/null 2\>\&1)
      then
	lt_cv_archive_cmds_need_lc=no
      else
	lt_cv_archive_cmds_need_lc=yes
      fi
      allow_undefined_flag=$save_allow_undefined_flag
    else
      cat conftest.err 1>&5
    fi])
    AC_MSG_RESULT([$lt_cv_archive_cmds_need_lc])
    ;;
  esac
fi
need_lc=${lt_cv_archive_cmds_need_lc-yes}

# The second clause should only fire when bootstrapping the
# libtool distribution, otherwise you forgot to ship ltmain.sh
# with your package, and you will get complaints that there are
# no rules to generate ltmain.sh.
if test -f "$ltmain"; then
  :
else
  # If there is no Makefile yet, we rely on a make rule to execute
  # `config.status --recheck' to rerun these tests and create the
  # libtool script then.
  test -f Makefile && make "$ltmain"
fi

if test -f "$ltmain"; then
  trap "$rm \"${ofile}T\"; exit 1" 1 2 15
  $rm -f "${ofile}T"

  echo creating $ofile

  # Now quote all the things that may contain metacharacters while being
  # careful not to overquote the AC_SUBSTed values.  We take copies of the
  # variables and quote the copies for generation of the libtool script.
  for var in echo old_CC old_CFLAGS SED \
    AR AR_FLAGS CC LD LN_S NM SHELL \
    reload_flag reload_cmds wl \
    pic_flag link_static_flag no_builtin_flag export_dynamic_flag_spec \
    thread_safe_flag_spec whole_archive_flag_spec libname_spec \
    library_names_spec soname_spec \
    RANLIB old_archive_cmds old_archive_from_new_cmds old_postinstall_cmds \
    old_postuninstall_cmds archive_cmds archive_expsym_cmds postinstall_cmds \
    postuninstall_cmds extract_expsyms_cmds old_archive_from_expsyms_cmds \
    old_striplib striplib file_magic_cmd export_symbols_cmds \
    deplibs_check_method allow_undefined_flag no_undefined_flag \
    finish_cmds finish_eval global_symbol_pipe global_symbol_to_cdecl \
    global_symbol_to_c_name_address \
    hardcode_libdir_flag_spec hardcode_libdir_separator  \
    sys_lib_search_path_spec sys_lib_dlsearch_path_spec \
    compiler_c_o compiler_o_lo need_locks exclude_expsyms include_expsyms; do

    case $var in
    reload_cmds | old_archive_cmds | old_archive_from_new_cmds | \
    old_postinstall_cmds | old_postuninstall_cmds | \
    export_symbols_cmds | archive_cmds | archive_expsym_cmds | \
    extract_expsyms_cmds | old_archive_from_expsyms_cmds | \
    postinstall_cmds | postuninstall_cmds | \
    finish_cmds | sys_lib_search_path_spec | sys_lib_dlsearch_path_spec)
      # Double-quote double-evaled strings.
      eval "lt_$var=\\\"\`\$echo \"X\$$var\" | \$Xsed -e \"\$double_quote_subst\" -e \"\$sed_quote_subst\" -e \"\$delay_variable_subst\"\`\\\""
      ;;
    *)
      eval "lt_$var=\\\"\`\$echo \"X\$$var\" | \$Xsed -e \"\$sed_quote_subst\"\`\\\""
      ;;
    esac
  done

  cat <<__EOF__ > "${ofile}T"
#! $SHELL

# `$echo "$ofile" | sed 's%^.*/%%'` - Provide generalized library-building support services.
# Generated automatically by $PROGRAM (GNU $PACKAGE $VERSION$TIMESTAMP)
# NOTE: Changes made to this file will be lost: look at ltmain.sh.
#
# Copyright (C) 1996-2000 Free Software Foundation, Inc.
# Originally by Gordon Matzigkeit <gord@gnu.ai.mit.edu>, 1996
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#
# As a special exception to the GNU General Public License, if you
# distribute this file as part of a program that contains a
# configuration script generated by Autoconf, you may include it under
# the same distribution terms that you use for the rest of that program.

# A sed that does not truncate output.
SED=$lt_SED

# Sed that helps us avoid accidentally triggering echo(1) options like -n.
Xsed="${SED} -e s/^X//"

# The HP-UX ksh and POSIX shell print the target directory to stdout
# if CDPATH is set.
if test "X\${CDPATH+set}" = Xset; then CDPATH=:; export CDPATH; fi

# ### BEGIN LIBTOOL CONFIG

# Libtool was configured on host `(hostname || uname -n) 2>/dev/null | sed 1q`:

# Shell to use when invoking shell scripts.
SHELL=$lt_SHELL

# Whether or not to build shared libraries.
build_libtool_libs=$enable_shared

# Whether or not to build static libraries.
build_old_libs=$enable_static

# Whether or not to add -lc for building shared libraries.
build_libtool_need_lc=$need_lc

# Whether or not to optimize for fast installation.
fast_install=$enable_fast_install

# The host system.
host_alias=$host_alias
host=$host

# An echo program that does not interpret backslashes.
echo=$lt_echo

# The archiver.
AR=$lt_AR
AR_FLAGS=$lt_AR_FLAGS

# The default C compiler.
CC=$lt_CC

# Is the compiler the GNU C compiler?
with_gcc=$GCC

# The linker used to build libraries.
LD=$lt_LD

# Whether we need hard or soft links.
LN_S=$lt_LN_S

# A BSD-compatible nm program.
NM=$lt_NM

# A symbol stripping program
STRIP=$STRIP

# Used to examine libraries when file_magic_cmd begins "file"
MAGIC_CMD=$MAGIC_CMD

# Used on cygwin: DLL creation program.
DLLTOOL="$DLLTOOL"

# Used on cygwin: object dumper.
OBJDUMP="$OBJDUMP"

# Used on cygwin: assembler.
AS="$AS"

# The name of the directory that contains temporary libtool files.
objdir=$objdir

# How to create reloadable object files.
reload_flag=$lt_reload_flag
reload_cmds=$lt_reload_cmds

# How to pass a linker flag through the compiler.
wl=$lt_wl

# Object file suffix (normally "o").
objext="$ac_objext"

# Old archive suffix (normally "a").
libext="$libext"

# Executable file suffix (normally "").
exeext="$exeext"

# Additional compiler flags for building library objects.
pic_flag=$lt_pic_flag
pic_mode=$pic_mode

# Does compiler simultaneously support -c and -o options?
compiler_c_o=$lt_compiler_c_o

# Can we write directly to a .lo ?
compiler_o_lo=$lt_compiler_o_lo

# Must we lock files when doing compilation ?
need_locks=$lt_need_locks

# Do we need the lib prefix for modules?
need_lib_prefix=$need_lib_prefix

# Do we need a version for libraries?
need_version=$need_version

# Whether dlopen is supported.
dlopen_support=$enable_dlopen

# Whether dlopen of programs is supported.
dlopen_self=$enable_dlopen_self

# Whether dlopen of statically linked programs is supported.
dlopen_self_static=$enable_dlopen_self_static

# Compiler flag to prevent dynamic linking.
link_static_flag=$lt_link_static_flag

# Compiler flag to turn off builtin functions.
no_builtin_flag=$lt_no_builtin_flag

# Compiler flag to allow reflexive dlopens.
export_dynamic_flag_spec=$lt_export_dynamic_flag_spec

# Compiler flag to generate shared objects directly from archives.
whole_archive_flag_spec=$lt_whole_archive_flag_spec

# Compiler flag to generate thread-safe objects.
thread_safe_flag_spec=$lt_thread_safe_flag_spec

# Library versioning type.
version_type=$version_type

# Format of library name prefix.
libname_spec=$lt_libname_spec

# List of archive names.  First name is the real one, the rest are links.
# The last name is the one that the linker finds with -lNAME.
library_names_spec=$lt_library_names_spec

# The coded name of the library, if different from the real name.
soname_spec=$lt_soname_spec

# Commands used to build and install an old-style archive.
RANLIB=$lt_RANLIB
old_archive_cmds=$lt_old_archive_cmds
old_postinstall_cmds=$lt_old_postinstall_cmds
old_postuninstall_cmds=$lt_old_postuninstall_cmds

# Create an old-style archive from a shared archive.
old_archive_from_new_cmds=$lt_old_archive_from_new_cmds

# Create a temporary old-style archive to link instead of a shared archive.
old_archive_from_expsyms_cmds=$lt_old_archive_from_expsyms_cmds

# Commands used to build and install a shared archive.
archive_cmds=$lt_archive_cmds
archive_expsym_cmds=$lt_archive_expsym_cmds
postinstall_cmds=$lt_postinstall_cmds
postuninstall_cmds=$lt_postuninstall_cmds

# Commands to strip libraries.
old_striplib=$lt_old_striplib
striplib=$lt_striplib

# Method to check whether dependent libraries are shared objects.
deplibs_check_method=$lt_deplibs_check_method

# Command to use when deplibs_check_method == file_magic.
file_magic_cmd=$lt_file_magic_cmd

# Flag that allows shared libraries with undefined symbols to be built.
allow_undefined_flag=$lt_allow_undefined_flag

# Flag that forces no undefined symbols.
no_undefined_flag=$lt_no_undefined_flag

# Commands used to finish a libtool library installation in a directory.
finish_cmds=$lt_finish_cmds

# Same as above, but a single script fragment to be evaled but not shown.
finish_eval=$lt_finish_eval

# Take the output of nm and produce a listing of raw symbols and C names.
global_symbol_pipe=$lt_global_symbol_pipe

# Transform the output of nm in a proper C declaration
global_symbol_to_cdecl=$lt_global_symbol_to_cdecl

# Transform the output of nm in a C name address pair
global_symbol_to_c_name_address=$lt_global_symbol_to_c_name_address

# This is the shared library runtime path variable.
runpath_var=$runpath_var

# This is the shared library path variable.
shlibpath_var=$shlibpath_var

# Is shlibpath searched before the hard-coded library search path?
shlibpath_overrides_runpath=$shlibpath_overrides_runpath

# How to hardcode a shared library path into an executable.
hardcode_action=$hardcode_action

# Whether we should hardcode library paths into libraries.
hardcode_into_libs=$hardcode_into_libs

# Flag to hardcode \$libdir into a binary during linking.
# This must work even if \$libdir does not exist.
hardcode_libdir_flag_spec=$lt_hardcode_libdir_flag_spec

# Whether we need a single -rpath flag with a separated argument.
hardcode_libdir_separator=$lt_hardcode_libdir_separator

# Set to yes if using DIR/libNAME.so during linking hardcodes DIR into the
# resulting binary.
hardcode_direct=$hardcode_direct

# Set to yes if using the -LDIR flag during linking hardcodes DIR into the
# resulting binary.
hardcode_minus_L=$hardcode_minus_L

# Set to yes if using SHLIBPATH_VAR=DIR during linking hardcodes DIR into
# the resulting binary.
hardcode_shlibpath_var=$hardcode_shlibpath_var

# Variables whose values should be saved in libtool wrapper scripts and
# restored at relink time.
variables_saved_for_relink="$variables_saved_for_relink"

# Whether libtool must link a program against all its dependency libraries.
link_all_deplibs=$link_all_deplibs

# Compile-time system search path for libraries
sys_lib_search_path_spec=$lt_sys_lib_search_path_spec

# Run-time system search path for libraries
sys_lib_dlsearch_path_spec=$lt_sys_lib_dlsearch_path_spec

# Fix the shell variable \$srcfile for the compiler.
fix_srcfile_path="$fix_srcfile_path"

# Set to yes if exported symbols are required.
always_export_symbols=$always_export_symbols

# The commands to list exported symbols.
export_symbols_cmds=$lt_export_symbols_cmds

# The commands to extract the exported symbol list from a shared archive.
extract_expsyms_cmds=$lt_extract_expsyms_cmds

# Symbols that should not be listed in the preloaded symbols.
exclude_expsyms=$lt_exclude_expsyms

# Symbols that must always be exported.
include_expsyms=$lt_include_expsyms

# ### END LIBTOOL CONFIG

__EOF__

  case $host_os in
  aix3*)
    cat <<\EOF >> "${ofile}T"

# AIX sometimes has problems with the GCC collect2 program.  For some
# reason, if we set the COLLECT_NAMES environment variable, the problems
# vanish in a puff of smoke.
if test "X${COLLECT_NAMES+set}" != Xset; then
  COLLECT_NAMES=
  export COLLECT_NAMES
fi
EOF
    ;;
  esac

  case $host_os in
  cygwin* | mingw* | pw32* | os2*)
    cat <<'EOF' >> "${ofile}T"
      # This is a source program that is used to create dlls on Windows
      # Don't remove nor modify the starting and closing comments
# /* ltdll.c starts here */
# #define WIN32_LEAN_AND_MEAN
# #include <windows.h>
# #undef WIN32_LEAN_AND_MEAN
# #include <stdio.h>
#
# #ifndef __CYGWIN__
# #  ifdef __CYGWIN32__
# #    define __CYGWIN__ __CYGWIN32__
# #  endif
# #endif
#
# #ifdef __cplusplus
# extern "C" {
# #endif
# BOOL APIENTRY DllMain (HINSTANCE hInst, DWORD reason, LPVOID reserved);
# #ifdef __cplusplus
# }
# #endif
#
# #ifdef __CYGWIN__
# #include <cygwin/cygwin_dll.h>
# DECLARE_CYGWIN_DLL( DllMain );
# #endif
# HINSTANCE __hDllInstance_base;
#
# BOOL APIENTRY
# DllMain (HINSTANCE hInst, DWORD reason, LPVOID reserved)
# {
#   __hDllInstance_base = hInst;
#   return TRUE;
# }
# /* ltdll.c ends here */
	# This is a source program that is used to create import libraries
	# on Windows for dlls which lack them. Don't remove nor modify the
	# starting and closing comments
# /* impgen.c starts here */
# /*   Copyright (C) 1999-2000 Free Software Foundation, Inc.
#
#  This file is part of GNU libtool.
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#  */
#
# #include <stdio.h>		/* for printf() */
# #include <unistd.h>		/* for open(), lseek(), read() */
# #include <fcntl.h>		/* for O_RDONLY, O_BINARY */
# #include <string.h>		/* for strdup() */
#
# /* O_BINARY isn't required (or even defined sometimes) under Unix */
# #ifndef O_BINARY
# #define O_BINARY 0
# #endif
#
# static unsigned int
# pe_get16 (fd, offset)
#      int fd;
#      int offset;
# {
#   unsigned char b[2];
#   lseek (fd, offset, SEEK_SET);
#   read (fd, b, 2);
#   return b[0] + (b[1]<<8);
# }
#
# static unsigned int
# pe_get32 (fd, offset)
#     int fd;
#     int offset;
# {
#   unsigned char b[4];
#   lseek (fd, offset, SEEK_SET);
#   read (fd, b, 4);
#   return b[0] + (b[1]<<8) + (b[2]<<16) + (b[3]<<24);
# }
#
# static unsigned int
# pe_as32 (ptr)
#      void *ptr;
# {
#   unsigned char *b = ptr;
#   return b[0] + (b[1]<<8) + (b[2]<<16) + (b[3]<<24);
# }
#
# int
# main (argc, argv)
#     int argc;
#     char *argv[];
# {
#     int dll;
#     unsigned long pe_header_offset, opthdr_ofs, num_entries, i;
#     unsigned long export_rva, export_size, nsections, secptr, expptr;
#     unsigned long name_rvas, nexp;
#     unsigned char *expdata, *erva;
#     char *filename, *dll_name;
#
#     filename = argv[1];
#
#     dll = open(filename, O_RDONLY|O_BINARY);
#     if (dll < 1)
# 	return 1;
#
#     dll_name = filename;
#
#     for (i=0; filename[i]; i++)
# 	if (filename[i] == '/' || filename[i] == '\\'  || filename[i] == ':')
# 	    dll_name = filename + i +1;
#
#     pe_header_offset = pe_get32 (dll, 0x3c);
#     opthdr_ofs = pe_header_offset + 4 + 20;
#     num_entries = pe_get32 (dll, opthdr_ofs + 92);
#
#     if (num_entries < 1) /* no exports */
# 	return 1;
#
#     export_rva = pe_get32 (dll, opthdr_ofs + 96);
#     export_size = pe_get32 (dll, opthdr_ofs + 100);
#     nsections = pe_get16 (dll, pe_header_offset + 4 +2);
#     secptr = (pe_header_offset + 4 + 20 +
# 	      pe_get16 (dll, pe_header_offset + 4 + 16));
#
#     expptr = 0;
#     for (i = 0; i < nsections; i++)
#     {
# 	char sname[8];
# 	unsigned long secptr1 = secptr + 40 * i;
# 	unsigned long vaddr = pe_get32 (dll, secptr1 + 12);
# 	unsigned long vsize = pe_get32 (dll, secptr1 + 16);
# 	unsigned long fptr = pe_get32 (dll, secptr1 + 20);
# 	lseek(dll, secptr1, SEEK_SET);
# 	read(dll, sname, 8);
# 	if (vaddr <= export_rva && vaddr+vsize > export_rva)
# 	{
# 	    expptr = fptr + (export_rva - vaddr);
# 	    if (export_rva + export_size > vaddr + vsize)
# 		export_size = vsize - (export_rva - vaddr);
# 	    break;
# 	}
#     }
#
#     expdata = (unsigned char*)malloc(export_size);
#     lseek (dll, expptr, SEEK_SET);
#     read (dll, expdata, export_size);
#     erva = expdata - export_rva;
#
#     nexp = pe_as32 (expdata+24);
#     name_rvas = pe_as32 (expdata+32);
#
#     printf ("EXPORTS\n");
#     for (i = 0; i<nexp; i++)
#     {
# 	unsigned long name_rva = pe_as32 (erva+name_rvas+i*4);
# 	printf ("\t%s @ %ld ;\n", erva+name_rva, 1+ i);
#     }
#
#     return 0;
# }
# /* impgen.c ends here */

EOF
    ;;
  esac

  # We use sed instead of cat because bash on DJGPP gets confused if
  # if finds mixed CR/LF and LF-only lines.  Since sed operates in
  # text mode, it properly converts lines to CR/LF.  This bash problem
  # is reportedly fixed, but why not run on old versions too?
  sed '$q' "$ltmain" >> "${ofile}T" || (rm -f "${ofile}T"; exit 1)

  mv -f "${ofile}T" "$ofile" || \
    (rm -f "$ofile" && cp "${ofile}T" "$ofile" && rm -f "${ofile}T")
  chmod +x "$ofile"
fi

])# _LT_AC_LTCONFIG_HACK

# AC_LIBTOOL_DLOPEN - enable checks for dlopen support
AC_DEFUN([AC_LIBTOOL_DLOPEN], [AC_BEFORE([$0],[AC_LIBTOOL_SETUP])])

# AC_LIBTOOL_WIN32_DLL - declare package support for building win32 dll's
AC_DEFUN([AC_LIBTOOL_WIN32_DLL], [AC_BEFORE([$0], [AC_LIBTOOL_SETUP])])

# AC_ENABLE_SHARED - implement the --enable-shared flag
# Usage: AC_ENABLE_SHARED[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN([AC_ENABLE_SHARED],
[define([AC_ENABLE_SHARED_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(shared,
changequote(<<, >>)dnl
<<  --enable-shared[=PKGS]  build shared libraries [default=>>AC_ENABLE_SHARED_DEFAULT],
changequote([, ])dnl
[p=${PACKAGE-default}
case $enableval in
yes) enable_shared=yes ;;
no) enable_shared=no ;;
*)
  enable_shared=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_shared=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_shared=AC_ENABLE_SHARED_DEFAULT)dnl
])

# AC_DISABLE_SHARED - set the default shared flag to --disable-shared
AC_DEFUN([AC_DISABLE_SHARED],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
AC_ENABLE_SHARED(no)])

# AC_ENABLE_STATIC - implement the --enable-static flag
# Usage: AC_ENABLE_STATIC[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN([AC_ENABLE_STATIC],
[define([AC_ENABLE_STATIC_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(static,
changequote(<<, >>)dnl
<<  --enable-static[=PKGS]  build static libraries [default=>>AC_ENABLE_STATIC_DEFAULT],
changequote([, ])dnl
[p=${PACKAGE-default}
case $enableval in
yes) enable_static=yes ;;
no) enable_static=no ;;
*)
  enable_static=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_static=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_static=AC_ENABLE_STATIC_DEFAULT)dnl
])

# AC_DISABLE_STATIC - set the default static flag to --disable-static
AC_DEFUN([AC_DISABLE_STATIC],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
AC_ENABLE_STATIC(no)])


# AC_ENABLE_FAST_INSTALL - implement the --enable-fast-install flag
# Usage: AC_ENABLE_FAST_INSTALL[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN([AC_ENABLE_FAST_INSTALL],
[define([AC_ENABLE_FAST_INSTALL_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(fast-install,
changequote(<<, >>)dnl
<<  --enable-fast-install[=PKGS]  optimize for fast installation [default=>>AC_ENABLE_FAST_INSTALL_DEFAULT],
changequote([, ])dnl
[p=${PACKAGE-default}
case $enableval in
yes) enable_fast_install=yes ;;
no) enable_fast_install=no ;;
*)
  enable_fast_install=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_fast_install=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_fast_install=AC_ENABLE_FAST_INSTALL_DEFAULT)dnl
])

# AC_DISABLE_FAST_INSTALL - set the default to --disable-fast-install
AC_DEFUN([AC_DISABLE_FAST_INSTALL],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
AC_ENABLE_FAST_INSTALL(no)])

# AC_LIBTOOL_PICMODE - implement the --with-pic flag
# Usage: AC_LIBTOOL_PICMODE[(MODE)]
#   Where MODE is either `yes' or `no'.  If omitted, it defaults to
#   `both'.
AC_DEFUN([AC_LIBTOOL_PICMODE],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
pic_mode=ifelse($#,1,$1,default)])


# AC_PATH_TOOL_PREFIX - find a file program which can recognise shared library
AC_DEFUN([AC_PATH_TOOL_PREFIX],
[AC_MSG_CHECKING([for $1])
AC_CACHE_VAL(lt_cv_path_MAGIC_CMD,
[case $MAGIC_CMD in
  /*)
  lt_cv_path_MAGIC_CMD="$MAGIC_CMD" # Let the user override the test with a path.
  ;;
  ?:/*)
  lt_cv_path_MAGIC_CMD="$MAGIC_CMD" # Let the user override the test with a dos path.
  ;;
  *)
  ac_save_MAGIC_CMD="$MAGIC_CMD"
  IFS="${IFS=   }"; ac_save_ifs="$IFS"; IFS=":"
dnl $ac_dummy forces splitting on constant user-supplied paths.
dnl POSIX.2 word splitting is done only on the output of word expansions,
dnl not every word.  This closes a longstanding sh security hole.
  ac_dummy="ifelse([$2], , $PATH, [$2])"
  for ac_dir in $ac_dummy; do
    test -z "$ac_dir" && ac_dir=.
    if test -f $ac_dir/$1; then
      lt_cv_path_MAGIC_CMD="$ac_dir/$1"
      if test -n "$file_magic_test_file"; then
	case $deplibs_check_method in
	"file_magic "*)
	  file_magic_regex="`expr \"$deplibs_check_method\" : \"file_magic \(.*\)\"`"
	  MAGIC_CMD="$lt_cv_path_MAGIC_CMD"
	  if eval $file_magic_cmd \$file_magic_test_file 2> /dev/null |
	    egrep "$file_magic_regex" > /dev/null; then
	    :
	  else
	    cat <<EOF 1>&2

*** Warning: the command libtool uses to detect shared libraries,
*** $file_magic_cmd, produces output that libtool cannot recognize.
*** The result is that libtool may fail to recognize shared libraries
*** as such.  This will affect the creation of libtool libraries that
*** depend on shared libraries, but programs linked with such libtool
*** libraries will work regardless of this problem.  Nevertheless, you
*** may want to report the problem to your system manager and/or to
*** bug-libtool@gnu.org

EOF
	  fi ;;
	esac
      fi
      break
    fi
  done
  IFS="$ac_save_ifs"
  MAGIC_CMD="$ac_save_MAGIC_CMD"
  ;;
esac])
MAGIC_CMD="$lt_cv_path_MAGIC_CMD"
if test -n "$MAGIC_CMD"; then
  AC_MSG_RESULT($MAGIC_CMD)
else
  AC_MSG_RESULT(no)
fi
])


# AC_PATH_MAGIC - find a file program which can recognise a shared library
AC_DEFUN([AC_PATH_MAGIC],
[AC_REQUIRE([AC_CHECK_TOOL_PREFIX])dnl
AC_PATH_TOOL_PREFIX(${ac_tool_prefix}file, /usr/bin:$PATH)
if test -z "$lt_cv_path_MAGIC_CMD"; then
  if test -n "$ac_tool_prefix"; then
    AC_PATH_TOOL_PREFIX(file, /usr/bin:$PATH)
  else
    MAGIC_CMD=:
  fi
fi
])


# AC_PROG_LD - find the path to the GNU or non-GNU linker
AC_DEFUN([AC_PROG_LD],
[AC_ARG_WITH(gnu-ld,
[  --with-gnu-ld           assume the C compiler uses GNU ld [default=no]],
test "$withval" = no || with_gnu_ld=yes, with_gnu_ld=no)
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
AC_REQUIRE([_LT_AC_LIBTOOL_SYS_PATH_SEPARATOR])dnl
ac_prog=ld
if test "$GCC" = yes; then
  # Check if gcc -print-prog-name=ld gives a path.
  AC_MSG_CHECKING([for ld used by GCC])
  case $host in
  *-*-mingw*)
    # gcc leaves a trailing carriage return which upsets mingw
    ac_prog=`($CC -print-prog-name=ld) 2>&5 | tr -d '\015'` ;;
  *)
    ac_prog=`($CC -print-prog-name=ld) 2>&5` ;;
  esac
  case $ac_prog in
    # Accept absolute paths.
    [[\\/]]* | [[A-Za-z]]:[[\\/]]*)
      re_direlt='/[[^/]][[^/]]*/\.\./'
      # Canonicalize the path of ld
      ac_prog=`echo $ac_prog| sed 's%\\\\%/%g'`
      while echo $ac_prog | grep "$re_direlt" > /dev/null 2>&1; do
	ac_prog=`echo $ac_prog| sed "s%$re_direlt%/%"`
      done
      test -z "$LD" && LD="$ac_prog"
      ;;
  "")
    # If it fails, then pretend we aren't using GCC.
    ac_prog=ld
    ;;
  *)
    # If it is relative, then search for the first ld in PATH.
    with_gnu_ld=unknown
    ;;
  esac
elif test "$with_gnu_ld" = yes; then
  AC_MSG_CHECKING([for GNU ld])
else
  AC_MSG_CHECKING([for non-GNU ld])
fi
AC_CACHE_VAL(lt_cv_path_LD,
[if test -z "$LD"; then
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS=$PATH_SEPARATOR
  for ac_dir in $PATH; do
    test -z "$ac_dir" && ac_dir=.
    if test -f "$ac_dir/$ac_prog" || test -f "$ac_dir/$ac_prog$ac_exeext"; then
      lt_cv_path_LD="$ac_dir/$ac_prog"
      # Check to see if the program is GNU ld.  I'd rather use --version,
      # but apparently some GNU ld's only accept -v.
      # Break only if it was the GNU/non-GNU ld that we prefer.
      if "$lt_cv_path_LD" -v 2>&1 < /dev/null | egrep '(GNU|with BFD)' > /dev/null; then
	test "$with_gnu_ld" != no && break
      else
	test "$with_gnu_ld" != yes && break
      fi
    fi
  done
  IFS="$ac_save_ifs"
else
  lt_cv_path_LD="$LD" # Let the user override the test with a path.
fi])
LD="$lt_cv_path_LD"
if test -n "$LD"; then
  AC_MSG_RESULT($LD)
else
  AC_MSG_RESULT(no)
fi
test -z "$LD" && AC_MSG_ERROR([no acceptable ld found in \$PATH])
AC_PROG_LD_GNU
])

# AC_PROG_LD_GNU -
AC_DEFUN([AC_PROG_LD_GNU],
[AC_CACHE_CHECK([if the linker ($LD) is GNU ld], lt_cv_prog_gnu_ld,
[# I'd rather use --version here, but apparently some GNU ld's only accept -v.
if $LD -v 2>&1 </dev/null | egrep '(GNU|with BFD)' 1>&5; then
  lt_cv_prog_gnu_ld=yes
else
  lt_cv_prog_gnu_ld=no
fi])
with_gnu_ld=$lt_cv_prog_gnu_ld
])

# AC_PROG_LD_RELOAD_FLAG - find reload flag for linker
#   -- PORTME Some linkers may need a different reload flag.
AC_DEFUN([AC_PROG_LD_RELOAD_FLAG],
[AC_CACHE_CHECK([for $LD option to reload object files], lt_cv_ld_reload_flag,
[lt_cv_ld_reload_flag='-r'])
reload_flag=$lt_cv_ld_reload_flag
test -n "$reload_flag" && reload_flag=" $reload_flag"
])

# AC_DEPLIBS_CHECK_METHOD - how to check for library dependencies
#  -- PORTME fill in with the dynamic library characteristics
AC_DEFUN([AC_DEPLIBS_CHECK_METHOD],
[AC_CACHE_CHECK([how to recognise dependent libraries],
lt_cv_deplibs_check_method,
[lt_cv_file_magic_cmd='$MAGIC_CMD'
lt_cv_file_magic_test_file=
lt_cv_deplibs_check_method='unknown'
# Need to set the preceding variable on all platforms that support
# interlibrary dependencies.
# 'none' -- dependencies not supported.
# `unknown' -- same as none, but documents that we really don't know.
# 'pass_all' -- all dependencies passed with no checks.
# 'test_compile' -- check by making test program.
# 'file_magic [[regex]]' -- check by looking for files in library path
# which responds to the $file_magic_cmd with a given egrep regex.
# If you have `file' or equivalent on your system and you're not sure
# whether `pass_all' will *always* work, you probably want this one.

case $host_os in
aix4* | aix5*)
  lt_cv_deplibs_check_method=pass_all
  ;;

beos*)
  lt_cv_deplibs_check_method=pass_all
  ;;

bsdi4*)
  lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[ML]]SB (shared object|dynamic lib)'
  lt_cv_file_magic_cmd='/usr/bin/file -L'
  lt_cv_file_magic_test_file=/shlib/libc.so
  ;;

cygwin* | mingw* | pw32*)
  lt_cv_deplibs_check_method='file_magic file format pei*-i386(.*architecture: i386)?'
  lt_cv_file_magic_cmd='$OBJDUMP -f'
  ;;

darwin* | rhapsody*)
  lt_cv_deplibs_check_method='file_magic Mach-O dynamically linked shared library'
  lt_cv_file_magic_cmd='/usr/bin/file -L'
  case "$host_os" in
  rhapsody* | darwin1.[[012]])
    lt_cv_file_magic_test_file=`echo /System/Library/Frameworks/System.framework/Versions/*/System | head -1`
    ;;
  *) # Darwin 1.3 on
    lt_cv_file_magic_test_file='/usr/lib/libSystem.dylib'
    ;;
  esac
  ;;

freebsd*)
  if echo __ELF__ | $CC -E - | grep __ELF__ > /dev/null; then
    case $host_cpu in
    i*86 )
      # Not sure whether the presence of OpenBSD here was a mistake.
      # Let's accept both of them until this is cleared up.
      lt_cv_deplibs_check_method='file_magic (FreeBSD|OpenBSD)/i[[3-9]]86 (compact )?demand paged shared library'
      lt_cv_file_magic_cmd=/usr/bin/file
      lt_cv_file_magic_test_file=`echo /usr/lib/libc.so.*`
      ;;
    esac
  else
    lt_cv_deplibs_check_method=pass_all
  fi
  ;;

gnu*)
  lt_cv_deplibs_check_method=pass_all
  ;;

hpux10.20*|hpux11*)
  lt_cv_deplibs_check_method='file_magic (s[[0-9]][[0-9]][[0-9]]|PA-RISC[[0-9]].[[0-9]]) shared library'
  lt_cv_file_magic_cmd=/usr/bin/file
  lt_cv_file_magic_test_file=/usr/lib/libc.sl
  ;;

irix5* | irix6* | nonstopux*)
  case $host_os in
  irix5* | nonstopux*)
    # this will be overridden with pass_all, but let us keep it just in case
    lt_cv_deplibs_check_method="file_magic ELF 32-bit MSB dynamic lib MIPS - version 1"
    ;;
  *)
    case $LD in
    *-32|*"-32 ") libmagic=32-bit;;
    *-n32|*"-n32 ") libmagic=N32;;
    *-64|*"-64 ") libmagic=64-bit;;
    *) libmagic=never-match;;
    esac
    # this will be overridden with pass_all, but let us keep it just in case
    lt_cv_deplibs_check_method="file_magic ELF ${libmagic} MSB mips-[[1234]] dynamic lib MIPS - version 1"
    ;;
  esac
  lt_cv_file_magic_test_file=`echo /lib${libsuff}/libc.so*`
  lt_cv_deplibs_check_method=pass_all
  ;;

# This must be Linux ELF.
linux-gnu*)
  case $host_cpu in
  alpha* | hppa* | i*86 | mips | mipsel | powerpc* | sparc* | ia64*)
    lt_cv_deplibs_check_method=pass_all ;;
  *)
    # glibc up to 2.1.1 does not perform some relocations on ARM
    lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[LM]]SB (shared object|dynamic lib )' ;;
  esac
  lt_cv_file_magic_test_file=`echo /lib/libc.so* /lib/libc-*.so`
  ;;

netbsd*)
  if echo __ELF__ | $CC -E - | grep __ELF__ > /dev/null; then
    lt_cv_deplibs_check_method='match_pattern /lib[[^/\.]]+\.so\.[[0-9]]+\.[[0-9]]+$'
  else
    lt_cv_deplibs_check_method='match_pattern /lib[[^/\.]]+\.so$'
  fi
  ;;

newos6*)
  lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[ML]]SB (executable|dynamic lib)'
  lt_cv_file_magic_cmd=/usr/bin/file
  lt_cv_file_magic_test_file=/usr/lib/libnls.so
  ;;

openbsd*)
  lt_cv_file_magic_cmd=/usr/bin/file
  lt_cv_file_magic_test_file=`echo /usr/lib/libc.so.*`
  if test -z "`echo __ELF__ | $CC -E - | grep __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powerpc"; then
    lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[LM]]SB shared object'
  else
    lt_cv_deplibs_check_method='file_magic OpenBSD.* shared library'
  fi
  ;;

osf3* | osf4* | osf5*)
  # this will be overridden with pass_all, but let us keep it just in case
  lt_cv_deplibs_check_method='file_magic COFF format alpha shared library'
  lt_cv_file_magic_test_file=/shlib/libc.so
  lt_cv_deplibs_check_method=pass_all
  ;;

sco3.2v5*)
  lt_cv_deplibs_check_method=pass_all
  ;;

solaris*)
  lt_cv_deplibs_check_method=pass_all
  lt_cv_file_magic_test_file=/lib/libc.so
  ;;

sysv5uw[[78]]* | sysv4*uw2*)
  lt_cv_deplibs_check_method=pass_all
  ;;

sysv4 | sysv4.2uw2* | sysv4.3* | sysv5*)
  case $host_vendor in
  motorola)
    lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[ML]]SB (shared object|dynamic lib) M[[0-9]][[0-9]]* Version [[0-9]]'
    lt_cv_file_magic_test_file=`echo /usr/lib/libc.so*`
    ;;
  ncr)
    lt_cv_deplibs_check_method=pass_all
    ;;
  sequent)
    lt_cv_file_magic_cmd='/bin/file'
    lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[LM]]SB (shared object|dynamic lib )'
    ;;
  sni)
    lt_cv_file_magic_cmd='/bin/file'
    lt_cv_deplibs_check_method="file_magic ELF [[0-9]][[0-9]]*-bit [[LM]]SB dynamic lib"
    lt_cv_file_magic_test_file=/lib/libc.so
    ;;
  siemens)
    lt_cv_deplibs_check_method=pass_all
    ;;
  esac
  ;;
esac
])
file_magic_cmd=$lt_cv_file_magic_cmd
deplibs_check_method=$lt_cv_deplibs_check_method
])


# AC_PROG_NM - find the path to a BSD-compatible name lister
AC_DEFUN([AC_PROG_NM],
[AC_REQUIRE([_LT_AC_LIBTOOL_SYS_PATH_SEPARATOR])dnl
AC_MSG_CHECKING([for BSD-compatible nm])
AC_CACHE_VAL(lt_cv_path_NM,
[if test -n "$NM"; then
  # Let the user override the test.
  lt_cv_path_NM="$NM"
else
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS=$PATH_SEPARATOR
  for ac_dir in $PATH /usr/ccs/bin /usr/ucb /bin; do
    test -z "$ac_dir" && ac_dir=.
    tmp_nm=$ac_dir/${ac_tool_prefix}nm
    if test -f $tmp_nm || test -f $tmp_nm$ac_exeext ; then
      # Check to see if the nm accepts a BSD-compat flag.
      # Adding the `sed 1q' prevents false positives on HP-UX, which says:
      #   nm: unknown option "B" ignored
      # Tru64's nm complains that /dev/null is an invalid object file
      if ($tmp_nm -B /dev/null 2>&1 | sed '1q'; exit 0) | egrep '(/dev/null|Invalid file or object type)' >/dev/null; then
	lt_cv_path_NM="$tmp_nm -B"
	break
      elif ($tmp_nm -p /dev/null 2>&1 | sed '1q'; exit 0) | egrep /dev/null >/dev/null; then
	lt_cv_path_NM="$tmp_nm -p"
	break
      else
	lt_cv_path_NM=${lt_cv_path_NM="$tmp_nm"} # keep the first match, but
	continue # so that we can try to find one that supports BSD flags
      fi
    fi
  done
  IFS="$ac_save_ifs"
  test -z "$lt_cv_path_NM" && lt_cv_path_NM=nm
fi])
NM="$lt_cv_path_NM"
AC_MSG_RESULT([$NM])
])

# AC_CHECK_LIBM - check for math library
AC_DEFUN([AC_CHECK_LIBM],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
LIBM=
case $host in
*-*-beos* | *-*-cygwin* | *-*-pw32*)
  # These system don't have libm
  ;;
*-ncr-sysv4.3*)
  AC_CHECK_LIB(mw, _mwvalidcheckl, LIBM="-lmw")
  AC_CHECK_LIB(m, main, LIBM="$LIBM -lm")
  ;;
*)
  AC_CHECK_LIB(m, main, LIBM="-lm")
  ;;
esac
])

# AC_LIBLTDL_CONVENIENCE[(dir)] - sets LIBLTDL to the link flags for
# the libltdl convenience library and LTDLINCL to the include flags for
# the libltdl header and adds --enable-ltdl-convenience to the
# configure arguments.  Note that LIBLTDL and LTDLINCL are not
# AC_SUBSTed, nor is AC_CONFIG_SUBDIRS called.  If DIR is not
# provided, it is assumed to be `libltdl'.  LIBLTDL will be prefixed
# with '${top_builddir}/' and LTDLINCL will be prefixed with
# '${top_srcdir}/' (note the single quotes!).  If your package is not
# flat and you're not using automake, define top_builddir and
# top_srcdir appropriately in the Makefiles.
AC_DEFUN([AC_LIBLTDL_CONVENIENCE],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
  case $enable_ltdl_convenience in
  no) AC_MSG_ERROR([this package needs a convenience libltdl]) ;;
  "") enable_ltdl_convenience=yes
      ac_configure_args="$ac_configure_args --enable-ltdl-convenience" ;;
  esac
  LIBLTDL='${top_builddir}/'ifelse($#,1,[$1],['libltdl'])/libltdlc.la
  LTDLINCL='-I${top_srcdir}/'ifelse($#,1,[$1],['libltdl'])
  # For backwards non-gettext consistent compatibility...
  INCLTDL="$LTDLINCL"
])

# AC_LIBLTDL_INSTALLABLE[(dir)] - sets LIBLTDL to the link flags for
# the libltdl installable library and LTDLINCL to the include flags for
# the libltdl header and adds --enable-ltdl-install to the configure
# arguments.  Note that LIBLTDL and LTDLINCL are not AC_SUBSTed, nor is
# AC_CONFIG_SUBDIRS called.  If DIR is not provided and an installed
# libltdl is not found, it is assumed to be `libltdl'.  LIBLTDL will
# be prefixed with '${top_builddir}/' and LTDLINCL will be prefixed
# with '${top_srcdir}/' (note the single quotes!).  If your package is
# not flat and you're not using automake, define top_builddir and
# top_srcdir appropriately in the Makefiles.
# In the future, this macro may have to be called after AC_PROG_LIBTOOL.
AC_DEFUN([AC_LIBLTDL_INSTALLABLE],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
  AC_CHECK_LIB(ltdl, main,
  [test x"$enable_ltdl_install" != xyes && enable_ltdl_install=no],
  [if test x"$enable_ltdl_install" = xno; then
     AC_MSG_WARN([libltdl not installed, but installation disabled])
   else
     enable_ltdl_install=yes
   fi
  ])
  if test x"$enable_ltdl_install" = x"yes"; then
    ac_configure_args="$ac_configure_args --enable-ltdl-install"
    LIBLTDL='${top_builddir}/'ifelse($#,1,[$1],['libltdl'])/libltdl.la
    LTDLINCL='-I${top_srcdir}/'ifelse($#,1,[$1],['libltdl'])
  else
    ac_configure_args="$ac_configure_args --enable-ltdl-install=no"
    LIBLTDL="-lltdl"
    LTDLINCL=
  fi
  # For backwards non-gettext consistent compatibility...
  INCLTDL="$LTDLINCL"
])

# old names
AC_DEFUN([AM_PROG_LIBTOOL],   [AC_PROG_LIBTOOL])
AC_DEFUN([AM_ENABLE_SHARED],  [AC_ENABLE_SHARED($@)])
AC_DEFUN([AM_ENABLE_STATIC],  [AC_ENABLE_STATIC($@)])
AC_DEFUN([AM_DISABLE_SHARED], [AC_DISABLE_SHARED($@)])
AC_DEFUN([AM_DISABLE_STATIC], [AC_DISABLE_STATIC($@)])
AC_DEFUN([AM_PROG_LD],        [AC_PROG_LD])
AC_DEFUN([AM_PROG_NM],        [AC_PROG_NM])

# This is just to silence aclocal about the macro not being used
ifelse([AC_DISABLE_FAST_INSTALL])

# NOTE: This macro has been submitted for inclusion into   #
#  GNU Autoconf as AC_PROG_SED.  When it is available in   #
#  a released version of Autoconf we should remove this    #
#  macro and use it instead.                               #
# LT_AC_PROG_SED
# --------------
# Check for a fully-functional sed program, that truncates
# as few characters as possible.  Prefer GNU sed if found.
AC_DEFUN([LT_AC_PROG_SED],
[AC_MSG_CHECKING([for a sed that does not truncate output])
AC_CACHE_VAL(lt_cv_path_SED,
[# Loop through the user's path and test for sed and gsed.
# Then use that list of sed's as ones to test for truncation.
as_executable_p="test -f"
as_save_IFS=$IFS; IFS=$PATH_SEPARATOR
for as_dir in $PATH
do
  IFS=$as_save_IFS
  test -z "$as_dir" && as_dir=.
  for ac_prog in sed gsed; do
    for ac_exec_ext in '' $ac_executable_extensions; do
      if $as_executable_p "$as_dir/$ac_prog$ac_exec_ext"; then
        _sed_list="$_sed_list $as_dir/$ac_prog$ac_exec_ext"
      fi
    done
  done
done

  # Create a temporary directory, and hook for its removal unless debugging.
$debug ||
{
  trap 'exit_status=$?; rm -rf $tmp && exit $exit_status' 0
  trap '{ (exit 1); exit 1; }' 1 2 13 15
}

# Create a (secure) tmp directory for tmp files.
: ${TMPDIR=/tmp}
{
  tmp=`(umask 077 && mktemp -d -q "$TMPDIR/sedXXXXXX") 2>/dev/null` &&
  test -n "$tmp" && test -d "$tmp"
}  ||
{
  tmp=$TMPDIR/sed$$-$RANDOM
  (umask 077 && mkdir $tmp)
} ||
{
   echo "$me: cannot create a temporary directory in $TMPDIR" >&2
   { (exit 1); exit 1; }
}
  _max=0
  _count=0
  # Add /usr/xpg4/bin/sed as it is typically found on Solaris
  # along with /bin/sed that truncates output.
  for _sed in $_sed_list /usr/xpg4/bin/sed; do
    test ! -f ${_sed} && break
    cat /dev/null > "$tmp/sed.in"
    _count=0
    echo ${ECHO_N-$ac_n} "0123456789${ECHO_C-$ac_c}" >"$tmp/sed.in"
    # Check for GNU sed and select it if it is found.
    if "${_sed}" --version 2>&1 < /dev/null | egrep '(GNU)' > /dev/null; then
      lt_cv_path_SED=${_sed}
      break
    fi
    while true; do
      cat "$tmp/sed.in" "$tmp/sed.in" >"$tmp/sed.tmp"
      mv "$tmp/sed.tmp" "$tmp/sed.in"
      cp "$tmp/sed.in" "$tmp/sed.nl"
      echo >>"$tmp/sed.nl"
      ${_sed} -e 's/a$//' < "$tmp/sed.nl" >"$tmp/sed.out" || break
      cmp -s "$tmp/sed.out" "$tmp/sed.nl" || break
      # 40000 chars as input seems more than enough
      test $_count -gt 10 && break
      _count=`expr $_count + 1`
      if test $_count -gt $_max; then
        _max=$_count
        lt_cv_path_SED=$_sed
      fi
    done
  done
  rm -rf "$tmp"
])
if test "X$SED" != "X"; then
  lt_cv_path_SED=$SED
else
  SED=$lt_cv_path_SED
fi
AC_MSG_RESULT([$SED])
])


# Copyright 1996, 1997, 1998, 2000, 2001, 2002  Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 2

AC_DEFUN([AM_C_PROTOTYPES],
[AC_REQUIRE([AM_PROG_CC_STDC])
AC_REQUIRE([AC_PROG_CPP])
AC_MSG_CHECKING([for function prototypes])
if test "$am_cv_prog_cc_stdc" != no; then
  AC_MSG_RESULT(yes)
  AC_DEFINE(PROTOTYPES,1,[Define if compiler has function prototypes])
  U= ANSI2KNR=
else
  AC_MSG_RESULT(no)
  U=_ ANSI2KNR=./ansi2knr
fi
# Ensure some checks needed by ansi2knr itself.
AC_HEADER_STDC
AC_CHECK_HEADERS(string.h)
AC_SUBST(U)dnl
AC_SUBST(ANSI2KNR)dnl
])

AU_DEFUN([fp_C_PROTOTYPES], [AM_C_PROTOTYPES])


# Copyright 1996, 1997, 1999, 2000, 2001, 2002  Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 2

# @defmac AC_PROG_CC_STDC
# @maindex PROG_CC_STDC
# @ovindex CC
# If the C compiler in not in ANSI C mode by default, try to add an option
# to output variable @code{CC} to make it so.  This macro tries various
# options that select ANSI C on some system or another.  It considers the
# compiler to be in ANSI C mode if it handles function prototypes correctly.
#
# If you use this macro, you should check after calling it whether the C
# compiler has been set to accept ANSI C; if not, the shell variable
# @code{am_cv_prog_cc_stdc} is set to @samp{no}.  If you wrote your source
# code in ANSI C, you can make an un-ANSIfied copy of it by using the
# program @code{ansi2knr}, which comes with Ghostscript.
# @end defmac

AC_DEFUN([AM_PROG_CC_STDC],
[AC_REQUIRE([AC_PROG_CC])
AC_BEFORE([$0], [AC_C_INLINE])
AC_BEFORE([$0], [AC_C_CONST])
dnl Force this before AC_PROG_CPP.  Some cpp's, eg on HPUX, require
dnl a magic option to avoid problems with ANSI preprocessor commands
dnl like #elif.
dnl FIXME: can't do this because then AC_AIX won't work due to a
dnl circular dependency.
dnl AC_BEFORE([$0], [AC_PROG_CPP])
AC_MSG_CHECKING([for ${CC-cc} option to accept ANSI C])
AC_CACHE_VAL(am_cv_prog_cc_stdc,
[am_cv_prog_cc_stdc=no
ac_save_CC="$CC"
# Don't try gcc -ansi; that turns off useful extensions and
# breaks some systems' header files.
# AIX			-qlanglvl=ansi
# Ultrix and OSF/1	-std1
# HP-UX 10.20 and later	-Ae
# HP-UX older versions	-Aa -D_HPUX_SOURCE
# SVR4			-Xc -D__EXTENSIONS__
for ac_arg in "" -qlanglvl=ansi -std1 -Ae "-Aa -D_HPUX_SOURCE" "-Xc -D__EXTENSIONS__"
do
  CC="$ac_save_CC $ac_arg"
  AC_TRY_COMPILE(
[#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
/* Most of the following tests are stolen from RCS 5.7's src/conf.sh.  */
struct buf { int x; };
FILE * (*rcsopen) (struct buf *, struct stat *, int);
static char *e (p, i)
     char **p;
     int i;
{
  return p[i];
}
static char *f (char * (*g) (char **, int), char **p, ...)
{
  char *s;
  va_list v;
  va_start (v,p);
  s = g (p, va_arg (v,int));
  va_end (v);
  return s;
}
int test (int i, double x);
struct s1 {int (*f) (int a);};
struct s2 {int (*f) (double a);};
int pairnames (int, char **, FILE *(*)(struct buf *, struct stat *, int), int, int);
int argc;
char **argv;
], [
return f (e, argv, 0) != argv[0]  ||  f (e, argv, 1) != argv[1];
],
[am_cv_prog_cc_stdc="$ac_arg"; break])
done
CC="$ac_save_CC"
])
if test -z "$am_cv_prog_cc_stdc"; then
  AC_MSG_RESULT([none needed])
else
  AC_MSG_RESULT([$am_cv_prog_cc_stdc])
fi
case "x$am_cv_prog_cc_stdc" in
  x|xno) ;;
  *) CC="$CC $am_cv_prog_cc_stdc" ;;
esac
])

AU_DEFUN([fp_PROG_CC_STDC], [AM_PROG_CC_STDC])

