// Created on: 2013-01-17
// Created by: Kirill GAVRILOV
// Copyright (c) 2013-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _Standard_CLocaleSentry_H__
#define _Standard_CLocaleSentry_H__

#include <Standard_Macro.hxx>

#include <locale.h>

#ifdef HAVE_XLOCALE_H
  #include <xlocale.h>
#endif

#if !defined(__ANDROID__)

//! This class intended to temporary switch C locale and logically equivalent to setlocale(LC_ALL, "C").
//! It is intended to format text regardless of user locale settings (for import/export functionality).
//! Thus following calls to sprintf, atoi and other functions will use "C" locale.
//! Destructor of this class will return original locale.
//!
//! Notice that this functionality is platfrom dependent and intended only to workaround alien code
//! that doesn't setup locale correctly.
//!
//! Internally you should prefer more portable C++ locale interfaces
//! or OCCT wrappers to some C functions like Sprintf, Atof, Strtod.
class Standard_CLocaleSentry
{
public:

  //! Setup current C locale to "C".
  Standard_EXPORT Standard_CLocaleSentry();

  //! Restore previous locale.
  Standard_EXPORT ~Standard_CLocaleSentry();

public:

#ifdef HAVE_XLOCALE_H
  typedef  locale_t clocale_t;
#elif defined(_WIN32) && !defined(__BORLANDC__) && !defined(__MINGW32__)
  typedef _locale_t clocale_t;
#else
  typedef void*     clocale_t;
#endif

  //! @return locale "C" instance (locale_t within xlocale or _locale_t within Windows)
  //! to be used for _l functions with locale argument.
  static Standard_EXPORT clocale_t GetCLocale();

private:

  void* myPrevLocale;       //!< previous locale, platform-dependent pointer!
#if defined(_WIN32) && !defined(__BORLANDC__) && !defined(__MINGW32__)
  int   myPrevTLocaleState; //!< previous thread-locale state, MSVCRT-specific
#endif

private:

  //! Copying disallowed
  Standard_CLocaleSentry            (const Standard_CLocaleSentry& );
  Standard_CLocaleSentry& operator= (const Standard_CLocaleSentry& );

};

#else

//! C/C++ runtime on Android currently supports only C-locale, no need to call anything.
class Standard_CLocaleSentry
{
public:
  Standard_CLocaleSentry() {}
  typedef void* clocale_t;
  static clocale_t GetCLocale() { return 0; }
};

#endif // __ANDROID__

#endif // _Standard_CLocaleSentry_H__
