// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _SelectBasics_SortAlgo_HeaderFile
#define _SelectBasics_SortAlgo_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Bnd_Box2d_HeaderFile
#include <Bnd_Box2d.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Bnd_BoundSortBox2d_HeaderFile
#include <Bnd_BoundSortBox2d.hxx>
#endif
#ifndef _TColStd_MapOfInteger_HeaderFile
#include <TColStd_MapOfInteger.hxx>
#endif
#ifndef _TColStd_MapIteratorOfMapOfInteger_HeaderFile
#include <TColStd_MapIteratorOfMapOfInteger.hxx>
#endif
#ifndef _Handle_Bnd_HArray1OfBox2d_HeaderFile
#include <Handle_Bnd_HArray1OfBox2d.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Bnd_Box2d;
class Bnd_HArray1OfBox2d;


//! Quickly selection of a rectangle in a set of rectangles <br>
class SelectBasics_SortAlgo  {
public:

  DEFINE_STANDARD_ALLOC

  //! Empty rectangle selector. <br>
  Standard_EXPORT   SelectBasics_SortAlgo();
  //! Creates a initialized selector. <br>
  Standard_EXPORT   SelectBasics_SortAlgo(const Bnd_Box2d& ClippingRectangle,const Standard_Real sizeOfSensitiveArea,const Handle(Bnd_HArray1OfBox2d)& theRectangles);
  //! Clears and initializes the selector. <br>
  Standard_EXPORT     void Initialize(const Bnd_Box2d& ClippingRectangle,const Standard_Real sizeOfSensitiveArea,const Handle(Bnd_HArray1OfBox2d)& theRectangles) ;
  //! Searchs the items on this position. <br>
  Standard_EXPORT     void InitSelect(const Standard_Real x,const Standard_Real y) ;
  //! Searchs the items in this rectangle. <br>
  Standard_EXPORT     void InitSelect(const Bnd_Box2d& rect) ;
  //! Returns true if there is something selected. <br>
  Standard_EXPORT     Standard_Boolean More() const;
  //! Sets value on the next selected item. <br>
  Standard_EXPORT     void Next() ;
  //! Returns the index of the selected rectangle. <br>
  Standard_EXPORT     Standard_Integer Value() const;





protected:





private:



Bnd_Box2d clipRect;
Standard_Real sizeArea;
Bnd_BoundSortBox2d sortedRect;
TColStd_MapOfInteger myMap;
TColStd_MapIteratorOfMapOfInteger curResult;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
