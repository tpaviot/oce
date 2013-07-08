// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _math_IntegerVector_HeaderFile
#define _math_IntegerVector_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _math_SingleTabOfInteger_HeaderFile
#include <math_SingleTabOfInteger.hxx>
#endif
#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_OStream_HeaderFile
#include <Standard_OStream.hxx>
#endif
class Standard_DimensionError;
class Standard_DivideByZero;
class Standard_RangeError;
class math_Matrix;



//! This class implements the real IntegerVector abstract data type. <br>
//! IntegerVectors can have an arbitrary range which must be define at <br>
//! the declaration and cannot be changed after this declaration. <br>
//! Example: math_IntegerVector V1(-3, 5); // an IntegerVector with <br>
//!  range [-3..5] <br>
//! <br>
//! IntegerVector is copied through assignement : <br>
//!    math_IntegerVector V2( 1, 9); <br>
//!    .... <br>
//!    V2 = V1; <br>
//!    V1(1) = 2.0; // the IntegerVector V2 will not be modified. <br>
//! <br>
//! The Exception RangeError is raised when trying to access outside <br>
//! the range of an IntegerVector : <br>
//!    V1(11) = 0 // --> will raise RangeError; <br>
//! <br>
//! The Exception DimensionError is raised when the dimensions of two <br>
//! IntegerVectors are not compatible : <br>
//!    math_IntegerVector V3(1, 2); <br>
//!    V3 = V1;    // --> will raise DimensionError; <br>
//!    V1.Add(V3)  // --> will raise DimensionError; <br>
class math_IntegerVector  {
public:

  DEFINE_STANDARD_ALLOC

  //! contructs an IntegerVector in the range [Lower..Upper] <br>
  Standard_EXPORT   math_IntegerVector(const Standard_Integer First,const Standard_Integer Last);
  //! contructs an IntegerVector in the range [Lower..Upper] <br>
//!          with all the elements set to InitialValue. <br>
  Standard_EXPORT   math_IntegerVector(const Standard_Integer First,const Standard_Integer Last,const Standard_Integer InitialValue);
  //! Initialize an IntegerVector with all the elements <br>
//!          set to InitialValue. <br>
  Standard_EXPORT     void Init(const Standard_Integer InitialValue) ;
  //! constructs an IntegerVector in the range [Lower..Upper] <br>
//!          which share the "c array" Tab. <br>
  Standard_EXPORT   math_IntegerVector(const Standard_Address Tab,const Standard_Integer First,const Standard_Integer Last);
  //! constructs a copy for initialization. <br>
//!          An exception is raised if the lengths of the IntegerVectors <br>
//!          are different. <br>
  Standard_EXPORT   math_IntegerVector(const math_IntegerVector& Other);
  //! returns the length of an IntegerVector <br>
        Standard_Integer Length() const;
  //! returns the value of the Lower index of an IntegerVector. <br>
        Standard_Integer Lower() const;
  //! returns the value of the Upper index of an IntegerVector. <br>
        Standard_Integer Upper() const;
  //! returns the value of the norm of an IntegerVector. <br>
  Standard_EXPORT     Standard_Real Norm() const;
  //! returns the value of the square of the norm of an <br>
//!          IntegerVector. <br>
  Standard_EXPORT     Standard_Real Norm2() const;
  //! returns the value of the Index of the maximum element of <br>
//!           an IntegerVector. <br>
  Standard_EXPORT     Standard_Integer Max() const;
  //! returns the value of the Index of the minimum element <br>
//!          of an IntegerVector. <br>
  Standard_EXPORT     Standard_Integer Min() const;
  //! inverses an IntegerVector. <br>
  Standard_EXPORT     void Invert() ;
  //! returns the inverse IntegerVector of an IntegerVector. <br>
  Standard_EXPORT     math_IntegerVector Inverse() const;
  //! sets an IntegerVector from <I1> to <I2> to the <br>
//!          IntegerVector <V>; <br>
//! An exception is raised if I1<LowerIndex or I2>UpperIndex or I1>I2. <br>
//! An exception is raised if I2-I1+1 is different from the Length of V. <br>
  Standard_EXPORT     void Set(const Standard_Integer I1,const Standard_Integer I2,const math_IntegerVector& V) ;
  //! slices the values of the IntegerVector between <I1> and <br>
//!          <I2>: <br>
//! Example: [2, 1, 2, 3, 4, 5] becomes [2, 4, 3, 2, 1, 5] between 2 and 5. <br>
//! An exception is raised if I1<LowerIndex or I2>UpperIndex. <br>
  Standard_EXPORT     math_IntegerVector Slice(const Standard_Integer I1,const Standard_Integer I2) const;
  //! returns the product of an IntegerVector by an integer value. <br>
  Standard_EXPORT     void Multiply(const Standard_Integer Right) ;
    void operator *=(const Standard_Integer Right) 
{
  Multiply(Right);
}
  //! returns the product of an IntegerVector by an integer value. <br>
  Standard_EXPORT     math_IntegerVector Multiplied(const Standard_Integer Right) const;
    math_IntegerVector operator*(const Standard_Integer Right) const
{
  return Multiplied(Right);
}
  //! returns the product of a vector and a real value. <br>
  Standard_EXPORT     math_IntegerVector TMultiplied(const Standard_Integer Right) const;
friend math_IntegerVector operator *(const Standard_Integer Left,const math_IntegerVector& Right);
  //! adds the IntegerVector <Right> to an IntegerVector. <br>
//! An exception is raised if the IntegerVectors have not the same <br>
//! length. <br>
//! An exception is raised if the lengths are not equal. <br>
  Standard_EXPORT     void Add(const math_IntegerVector& Right) ;
    void operator +=(const math_IntegerVector& Right) 
{
  Add(Right);
}
  //! adds the IntegerVector <Right> to an IntegerVector. <br>
//! An exception is raised if the IntegerVectors have not the same <br>
//! length. <br>
//! An exception is raised if the lengths are not equal. <br>
  Standard_EXPORT     math_IntegerVector Added(const math_IntegerVector& Right) const;
    math_IntegerVector operator+(const math_IntegerVector& Right) const
{
  return Added(Right);
}
  //! sets an IntegerVector to the sum of the IntegerVector <br>
//!          <Left> and the IntegerVector <Right>. <br>
//! An exception is raised if the lengths are different. <br>
  Standard_EXPORT     void Add(const math_IntegerVector& Left,const math_IntegerVector& Right) ;
  //! sets an IntegerVector to the substraction of <br>
//!          <Right> from <Left>. <br>
//! An exception is raised if the IntegerVectors have not the same <br>
//! length. <br>
  Standard_EXPORT     void Subtract(const math_IntegerVector& Left,const math_IntegerVector& Right) ;
  //! accesses (in read or write mode) the value of index Num of <br>
//!          an IntegerVector. <br>
        Standard_Integer& Value(const Standard_Integer Num) const;
      Standard_Integer& operator()(const Standard_Integer Num) const
{
  return Value(Num);
}
  //! Initialises an IntegerVector by copying <Other>. <br>
//!          An exception is raised if the Lengths are different. <br>
  Standard_EXPORT     math_IntegerVector& Initialized(const math_IntegerVector& Other) ;
    math_IntegerVector& operator=(const math_IntegerVector& Other) 
{
  return Initialized(Other);
}
  //! returns the inner product of 2 IntegerVectors. <br>
//! An exception is raised if the lengths are not equal. <br>
  Standard_EXPORT     Standard_Integer Multiplied(const math_IntegerVector& Right) const;
    Standard_Integer operator*(const math_IntegerVector& Right) const
{
  return Multiplied(Right);
}
  //! returns the opposite of an IntegerVector. <br>
  Standard_EXPORT     math_IntegerVector Opposite() ;
    math_IntegerVector operator-() 
{
  return Opposite();
}
  //! returns the subtraction of <Right> from <me>. <br>
//! An exception is raised if the IntegerVectors have not the same length. <br>
  Standard_EXPORT     void Subtract(const math_IntegerVector& Right) ;
    void operator-=(const math_IntegerVector& Right) 
{
  Subtract(Right);
}
  //! returns the subtraction of  <Right> from <me>. <br>
//! An exception is raised if the IntegerVectors have not the same length. <br>
  Standard_EXPORT     math_IntegerVector Subtracted(const math_IntegerVector& Right) const;
    math_IntegerVector operator-(const math_IntegerVector& Right) const
{
  return Subtracted(Right);
}
  //! returns the multiplication of an integer by an <br>
//!          IntegerVector. <br>
  Standard_EXPORT     void Multiply(const Standard_Integer Left,const math_IntegerVector& Right) ;
  //! Prints on the stream o information on the current state <br>
//!          of the object. <br>
//!          Is used to redefine the operator <<. <br>
  Standard_EXPORT     void Dump(Standard_OStream& o) const;


friend class math_Matrix;



protected:

  //! is used internally to set the Lower value of the <br>
//!          IntegerVector. <br>
  Standard_EXPORT     void SetFirst(const Standard_Integer First) ;




private:



Standard_Integer FirstIndex;
Standard_Integer LastIndex;
math_SingleTabOfInteger Array;


};


#include <math_IntegerVector.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
