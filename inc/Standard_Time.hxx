// File    : Standard_Time.hxx
// Created : Fri Jan 13 2012 for OpenCascade Community edition
// Author  : Fotis Sioutis <sfotis at gmail dot com>
// Purpose : This file is intented to provide inclusion of 'time' 
//           variable in a CDL consistent way.

/* time.h is well standardised across various platforms */
#include <time.h>

#if defined( _MSC_VER ) && defined ( _TIME64_T_DEFINED )
#define Standard_Time __time64_t
#else 
#define Standard_Time time_t
#endif
