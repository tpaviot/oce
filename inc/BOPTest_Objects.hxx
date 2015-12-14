// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BOPTest_Objects_HeaderFile
#define _BOPTest_Objects_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <BOPDS_PDS.hxx>
#include <BOPCol_ListOfShape.hxx>
#include <BOPAlgo_PBuilder.hxx>
#include <Standard_Boolean.hxx>
#include <Standard_Real.hxx>
class BOPAlgo_PaveFiller;
class BOPAlgo_Builder;
class BOPAlgo_BOP;
class BOPAlgo_Section;



class BOPTest_Objects 
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT static   BOPAlgo_PaveFiller& PaveFiller() ;
  
  Standard_EXPORT static   void Init() ;
  
  Standard_EXPORT static   void Clear() ;
  
  Standard_EXPORT static   BOPDS_PDS PDS() ;
  
  Standard_EXPORT static   BOPAlgo_Builder& Builder() ;
  
  Standard_EXPORT static   BOPAlgo_BOP& BOP() ;
  
  Standard_EXPORT static   BOPAlgo_Section& Section() ;
  
  Standard_EXPORT static   BOPCol_ListOfShape& Shapes() ;
  
  Standard_EXPORT static   BOPCol_ListOfShape& Tools() ;
  
  Standard_EXPORT static   void SetBuilder (const BOPAlgo_PBuilder& theBuilder) ;
  
  Standard_EXPORT static   void SetBuilderDefault() ;
  
  Standard_EXPORT static   void SetRunParallel (const Standard_Boolean theFlag) ;
  
  Standard_EXPORT static   Standard_Boolean RunParallel() ;
  
  Standard_EXPORT static   void SetFuzzyValue (const Standard_Real theValue) ;
  
  Standard_EXPORT static   Standard_Real FuzzyValue() ;




protected:





private:





};







#endif // _BOPTest_Objects_HeaderFile
