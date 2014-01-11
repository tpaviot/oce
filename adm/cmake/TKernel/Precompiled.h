#pragma once

#include <string>
#include <iostream>
#include <math.h>

#include "Standard.hxx"
#include "Standard_PrimitiveTypes.hxx"
#include "Standard_Stream.hxx"
#include "Standard_Failure.hxx"
#include "Standard_Transient.hxx"

#ifdef USE_STL_STREAM
#include <sstream>
#else /* USE_STL_STREAM */
#ifdef WNT
#include <strstrea.h>
#else
#include <strstream.h>
#endif
#endif
