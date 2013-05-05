// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _GeomInt_LineConstructor_HeaderFile
#define _GeomInt_LineConstructor_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _TColStd_SequenceOfReal_HeaderFile
#include <TColStd_SequenceOfReal.hxx>
#endif
#ifndef _Handle_Adaptor3d_TopolTool_HeaderFile
#include <Handle_Adaptor3d_TopolTool.hxx>
#endif
#ifndef _Handle_GeomAdaptor_HSurface_HeaderFile
#include <Handle_GeomAdaptor_HSurface.hxx>
#endif
#ifndef _Handle_IntPatch_Line_HeaderFile
#include <Handle_IntPatch_Line.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
class Adaptor3d_TopolTool;
class GeomAdaptor_HSurface;
class StdFail_NotDone;
class Standard_OutOfRange;
class IntPatch_Line;


//! Splits given Line. <br>
class GeomInt_LineConstructor  {
public:

  DEFINE_STANDARD_ALLOC

  
//! Empty constructor <br>
//! <br>
      GeomInt_LineConstructor();
  
//! Initializes me by two surfaces and corresponding <br>
//! tools which represent boundaries of surfaces <br>
//! <br>
        void Load(const Handle(Adaptor3d_TopolTool)& D1,const Handle(Adaptor3d_TopolTool)& D2,const Handle(GeomAdaptor_HSurface)& S1,const Handle(GeomAdaptor_HSurface)& S2) ;
  
//! Splits line <br>
//! <br>
  Standard_EXPORT     void Perform(const Handle(IntPatch_Line)& L) ;
  
//! Returns True if splitting was successful <br>
//! <br>
        Standard_Boolean IsDone() const;
  
//! Returns number of splits <br>
//! <br>
        Standard_Integer NbParts() const;
  
//! Return first and last parameters <br>
//! for given index of split <br>
//! <br>
        void Part(const Standard_Integer I,Standard_Real& WFirst,Standard_Real& WLast) const;





protected:





private:

  
  Standard_EXPORT     void PeriodicLine(const Handle(IntPatch_Line)& L) const;


Standard_Boolean done;
TColStd_SequenceOfReal seqp;
Handle_Adaptor3d_TopolTool myDom1;
Handle_Adaptor3d_TopolTool myDom2;
Handle_GeomAdaptor_HSurface myHS1;
Handle_GeomAdaptor_HSurface myHS2;


};


#include <GeomInt_LineConstructor.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
