// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _MAT2d_Mat2d_HeaderFile
#define _MAT2d_Mat2d_HeaderFile

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
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_MAT_ListOfEdge_HeaderFile
#include <Handle_MAT_ListOfEdge.hxx>
#endif
#ifndef _TColStd_DataMapOfIntegerInteger_HeaderFile
#include <TColStd_DataMapOfIntegerInteger.hxx>
#endif
#ifndef _MAT_DataMapOfIntegerBisector_HeaderFile
#include <MAT_DataMapOfIntegerBisector.hxx>
#endif
#ifndef _Handle_MAT_ListOfBisector_HeaderFile
#include <Handle_MAT_ListOfBisector.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Handle_MAT_Bisector_HeaderFile
#include <Handle_MAT_Bisector.hxx>
#endif
class MAT_ListOfEdge;
class MAT_ListOfBisector;
class MAT2d_Tool2d;
class MAT_Bisector;



class MAT2d_Mat2d  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   MAT2d_Mat2d();
  
  Standard_EXPORT     void CreateMat(MAT2d_Tool2d& aTool) ;
  
  Standard_EXPORT     Standard_Boolean IsDone() const;
  
  Standard_EXPORT     void Init() ;
  
  Standard_EXPORT     Standard_Boolean More() const;
  
  Standard_EXPORT     void Next() ;
  
  Standard_EXPORT     Handle_MAT_Bisector Bisector() const;
  
  Standard_EXPORT     Standard_Boolean SemiInfinite() const;
  
  Standard_EXPORT     Standard_Integer NumberOfBisectors() const;





protected:





private:

  
  Standard_EXPORT     void LoadBisectorsToRemove(Standard_Integer& noofbisectorstoremove,const Standard_Real distance1,const Standard_Real distance2,const Handle(MAT_Bisector)& bisector1,const Handle(MAT_Bisector)& bisector2,const Handle(MAT_Bisector)& bisector3,const Handle(MAT_Bisector)& bisector4) ;
  
  Standard_EXPORT     void Intersect(MAT2d_Tool2d& atool,const Standard_Integer aside,Standard_Integer& noofbisectorstoremove,const Handle(MAT_Bisector)& bisector1,const Handle(MAT_Bisector)& bisector2) ;


Standard_Integer thenumberofbisectors;
Standard_Integer thenumberofedges;
Standard_Boolean semiInfinite;
Handle_MAT_ListOfEdge theedgelist;
TColStd_DataMapOfIntegerInteger typeofbisectortoremove;
MAT_DataMapOfIntegerBisector bisectoronetoremove;
MAT_DataMapOfIntegerBisector bisectortwotoremove;
MAT_DataMapOfIntegerBisector bisectormap;
Handle_MAT_ListOfBisector roots;
Standard_Integer thecurrentindex;
Standard_Boolean isDone;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
