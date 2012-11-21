// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ShapeAnalysis_DataMapIteratorOfDataMapOfShapeListOfReal_HeaderFile
#define _ShapeAnalysis_DataMapIteratorOfDataMapOfShapeListOfReal_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_BasicMapIterator_HeaderFile
#include <TCollection_BasicMapIterator.hxx>
#endif
#ifndef _Handle_ShapeAnalysis_DataMapNodeOfDataMapOfShapeListOfReal_HeaderFile
#include <Handle_ShapeAnalysis_DataMapNodeOfDataMapOfShapeListOfReal.hxx>
#endif
class Standard_NoSuchObject;
class TopoDS_Shape;
class TColStd_ListOfReal;
class TopTools_ShapeMapHasher;
class ShapeAnalysis_DataMapOfShapeListOfReal;
class ShapeAnalysis_DataMapNodeOfDataMapOfShapeListOfReal;



class ShapeAnalysis_DataMapIteratorOfDataMapOfShapeListOfReal  : public TCollection_BasicMapIterator {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   ShapeAnalysis_DataMapIteratorOfDataMapOfShapeListOfReal();
  
  Standard_EXPORT   ShapeAnalysis_DataMapIteratorOfDataMapOfShapeListOfReal(const ShapeAnalysis_DataMapOfShapeListOfReal& aMap);
  
  Standard_EXPORT     void Initialize(const ShapeAnalysis_DataMapOfShapeListOfReal& aMap) ;
  
  Standard_EXPORT    const TopoDS_Shape& Key() const;
  
  Standard_EXPORT    const TColStd_ListOfReal& Value() const;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
