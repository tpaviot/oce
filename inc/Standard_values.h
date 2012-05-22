/*
 Copyright (c) 1991-1999 Matra Datavision
 Copyright (c) 1999-2012 OPEN CASCADE SAS

 The content of this file is subject to the Open CASCADE Technology Public
 License Version 6.5 (the "License"). You may not use the content of this file
 except in compliance with the License. Please obtain a copy of the License
 at http://www.opencascade.org and read it completely before using this file.

 The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
 main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.

 The Original Code and all software distributed under the License is
 distributed on an "AS IS" basis, without warranty of any kind, and the
 Initial Developer hereby disclaims all such warranties, including without
 limitation, any warranties of merchantability, fitness for a particular
 purpose or non-infringement. Please see the License for the specific terms
 and conditions governing the rights and limitations under the License.

*/

#ifndef _Standard_values_HeaderFile
# define _Standard_values_HeaderFile

#if (defined(_MSC_VER) || defined(__BORLANDC__)) && !defined(WNT)
#error "Wrong compiler options has been detected. Add /DWNT option for proper compilation!!!!!"
#endif

#include <oce-config.h>

#ifndef WNT
# ifdef OCE_HAVE_CLIMITS
#  include <climits>
# elif defined (OCE_HAVE_LIMITS)
#  include <limits>
# elif defined (OCE_HAVE_LIMITS_H)
#  include <limits.h>
# else
#  error "check oce-config.h file or compilation options: OCE_HAVE_CLIMITS, OCE_HAVE_LIMITS, or OCE_HAVE_LIMITS_H should be defined"
# endif
#endif


#ifdef WNT
# include <limits>
#endif

#ifdef __MINGW32__
# include <limits.h>
#endif

#if defined (__hpux) || defined (HPUX)
# ifdef MAXINT
#  undef MAXINT
# endif
#endif

#ifndef BITSPERBYTE
# define BITSPERBYTE	CHAR_BIT
#endif
#ifndef BITS
# define BITS(type)	(BITSPERBYTE * sizeof(type))
#endif

#endif

