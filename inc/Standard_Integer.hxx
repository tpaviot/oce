// Copyright (c) 1998-1999 Matra Datavision
// Copyright (c) 1999-2013 OPEN CASCADE SAS
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

#ifndef _Standard_Integer_HeaderFile
#define _Standard_Integer_HeaderFile

#include <Standard_TypeDef.hxx>
#include <Standard_values.h>

#include <oce-config.h>

#ifdef __BORLANDC__
#define OCE_IS_DUPLICATE_UINT32_T
#endif

// ===============
// Inline methods
// ===============

// ------------------------------------------------------------------
// Abs : Returns the absolute value of an Integer
// ------------------------------------------------------------------
inline  Standard_Integer Abs (const Standard_Integer Value) 
{ 
  return Value >= 0 ? Value : -Value;
}

// ------------------------------------------------------------------
// Hascode : Computes a hascoding value for a given Integer
// ------------------------------------------------------------------
inline Standard_Integer HashCode (const Standard_Integer theMe,
                                  const Standard_Integer theUpper)
{
  //return (Abs (theMe) % theUpper) + 1;
  return ((theMe & 0x7fffffff ) % theUpper) + 1;
}

// ------------------------------------------------------------------
// IsEqual : Returns Standard_True if two integers are equal
// ------------------------------------------------------------------
inline Standard_Boolean IsEqual (const Standard_Integer theOne,
                                 const Standard_Integer theTwo)
{
  return theOne == theTwo;
}

#ifndef OCE_IS_DUPLICATE_UINT32_T
// ------------------------------------------------------------------
// Hascode : Computes a hascoding value for a given unsigned integer
// ------------------------------------------------------------------
inline Standard_Integer HashCode (const Standard_Utf32Char theMe,
                                  const Standard_Integer   theUpper)
{
  return ((theMe & 0x7fffffff ) % theUpper) + 1;
}

// ------------------------------------------------------------------
// IsEqual : Returns Standard_True if two integers are equal
// ------------------------------------------------------------------
inline Standard_Boolean IsEqual (const Standard_Utf32Char theOne,
                                 const Standard_Utf32Char theTwo)
{
  return theOne == theTwo;
}
#endif  /* !OCE_IS_DUPLICATE_UINT32_T */

// ------------------------------------------------------------------
// IsSimilar : Returns Standard_True if two integers are equal
// ------------------------------------------------------------------
inline Standard_Boolean IsSimilar (const Standard_Integer One, 
				   const Standard_Integer Two)
{ return One == Two; }


// ------------------------------------------------------------------
// IsEven : Returns Standard_True if an integer is even
// ------------------------------------------------------------------
inline Standard_Boolean IsEven (const Standard_Integer Value) 
{ return Value % 2 == 0; }


// ------------------------------------------------------------------
// IsOdd : Returns Standard_True if an integer is odd
// ------------------------------------------------------------------
inline Standard_Boolean IsOdd (const Standard_Integer Value) 
{ return Value % 2 == 1; }

// ------------------------------------------------------------------
// Max : Returns the maximum integer between two integers
// ------------------------------------------------------------------
inline Standard_Integer  Max (const Standard_Integer Val1,
			      const Standard_Integer Val2) 
{
  return Val1 >= Val2 ? Val1 : Val2;
}

// ------------------------------------------------------------------
// Min : Returns the minimum integer between two integers
// ------------------------------------------------------------------
inline Standard_Integer  Min (const Standard_Integer Val1, 
			      const Standard_Integer Val2) 
{
  return Val1 <= Val2 ? Val1 : Val2;
}

// ------------------------------------------------------------------
// Modulus : Returns the remainder of division between two integers
// ------------------------------------------------------------------
inline Standard_Integer  Modulus (const Standard_Integer Value, 
				  const Standard_Integer Divisor) 
{ return Value % Divisor; }

// ------------------------------------------------------------------
// Square : Returns the square of an integer
// ------------------------------------------------------------------
inline Standard_Integer Square(const Standard_Integer Value) 
{ return Value * Value; }

// ------------------------------------------------------------------
// IntegerFirst : Returns the minimum value of an integer
// ------------------------------------------------------------------
inline Standard_Integer  IntegerFirst()     
{ return INT_MIN; }

// ------------------------------------------------------------------
// IntegerLast : Returns the maximum value of an integer
// ------------------------------------------------------------------
inline Standard_Integer  IntegerLast()     
{ return INT_MAX; }

// ------------------------------------------------------------------
// IntegerSize : Returns the size in digits of an integer
// ------------------------------------------------------------------
inline Standard_Integer  IntegerSize()     
{ return BITS(Standard_Integer); }

#endif 
