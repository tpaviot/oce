// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IntPatch_TheIWalking_HeaderFile
#define _IntPatch_TheIWalking_HeaderFile

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
#ifndef _IntSurf_SequenceOfPathPoint_HeaderFile
#include <IntSurf_SequenceOfPathPoint.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _math_Vector_HeaderFile
#include <math_Vector.hxx>
#endif
#ifndef _TColStd_SequenceOfReal_HeaderFile
#include <TColStd_SequenceOfReal.hxx>
#endif
#ifndef _TColStd_SequenceOfInteger_HeaderFile
#include <TColStd_SequenceOfInteger.hxx>
#endif
#ifndef _IntSurf_PntOn2S_HeaderFile
#include <IntSurf_PntOn2S.hxx>
#endif
#ifndef _gp_Vec_HeaderFile
#include <gp_Vec.hxx>
#endif
#ifndef _gp_Dir2d_HeaderFile
#include <gp_Dir2d.hxx>
#endif
#ifndef _IntPatch_SequenceOfIWLineOfTheIWalking_HeaderFile
#include <IntPatch_SequenceOfIWLineOfTheIWalking.hxx>
#endif
#ifndef _Handle_Adaptor3d_HSurface_HeaderFile
#include <Handle_Adaptor3d_HSurface.hxx>
#endif
#ifndef _Handle_IntPatch_TheIWLineOfTheIWalking_HeaderFile
#include <Handle_IntPatch_TheIWLineOfTheIWalking.hxx>
#endif
#ifndef _Handle_IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking_HeaderFile
#include <Handle_IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _IntWalk_StatusDeflection_HeaderFile
#include <IntWalk_StatusDeflection.hxx>
#endif
class StdFail_NotDone;
class Standard_OutOfRange;
class IntSurf_PathPoint;
class IntSurf_PathPointTool;
class IntSurf_SequenceOfPathPoint;
class IntSurf_InteriorPoint;
class IntSurf_InteriorPointTool;
class IntSurf_SequenceOfInteriorPoint;
class Adaptor3d_HSurface;
class Adaptor3d_HSurfaceTool;
class IntPatch_TheSurfFunction;
class IntPatch_TheIWLineOfTheIWalking;
class IntPatch_SequenceOfIWLineOfTheIWalking;
class IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking;
class math_Vector;
class TColStd_SequenceOfReal;
class IntSurf_PntOn2S;



class IntPatch_TheIWalking  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   IntPatch_TheIWalking();
  
  Standard_EXPORT   IntPatch_TheIWalking(const Standard_Real Epsilon,const Standard_Real Deflection,const Standard_Real Step);
  
        void SetTolerance(const Standard_Real Epsilon,const Standard_Real Deflection,const Standard_Real Step) ;
  
  Standard_EXPORT     void Perform(const IntSurf_SequenceOfPathPoint& Pnts1,const IntSurf_SequenceOfInteriorPoint& Pnts2,IntPatch_TheSurfFunction& Func,const Handle(Adaptor3d_HSurface)& S,const Standard_Boolean Reversed = Standard_False) ;
  
  Standard_EXPORT     void Perform(const IntSurf_SequenceOfPathPoint& Pnts1,IntPatch_TheSurfFunction& Func,const Handle(Adaptor3d_HSurface)& S,const Standard_Boolean Reversed = Standard_False) ;
  
        Standard_Boolean IsDone() const;
  
        Standard_Integer NbLines() const;
  
       const Handle_IntPatch_TheIWLineOfTheIWalking& Value(const Standard_Integer Index) const;
  
        Standard_Integer NbSinglePnts() const;
  
       const IntSurf_PathPoint& SinglePnt(const Standard_Integer Index) const;





protected:

  
  Standard_EXPORT     Standard_Boolean Cadrage(math_Vector& BornInf,math_Vector& BornSup,math_Vector& UVap,Standard_Real& Step,const Standard_Integer StepSign) const;
  
  Standard_EXPORT     Standard_Boolean TestArretPassage(const TColStd_SequenceOfReal& Umult,const TColStd_SequenceOfReal& Vmult,IntPatch_TheSurfFunction& Section,math_Vector& UV,Standard_Integer& Irang) ;
  
  Standard_EXPORT     Standard_Boolean TestArretPassage(const TColStd_SequenceOfReal& Umult,const TColStd_SequenceOfReal& Vmult,const math_Vector& UV,const Standard_Integer Index,Standard_Integer& Irang) ;
  
  Standard_EXPORT     Standard_Boolean TestArretAjout(IntPatch_TheSurfFunction& Section,math_Vector& UV,Standard_Integer& Irang,IntSurf_PntOn2S& PSol) ;
  
  Standard_EXPORT     void TestArretCadre(const TColStd_SequenceOfReal& Umult,const TColStd_SequenceOfReal& Vmult,const Handle(IntPatch_TheIWLineOfTheIWalking)& Line,IntPatch_TheSurfFunction& Section,math_Vector& UV,Standard_Integer& Irang) ;
  
  Standard_EXPORT     IntWalk_StatusDeflection TestDeflection(IntPatch_TheSurfFunction& Section,const Standard_Boolean Finished,const math_Vector& UV,const IntWalk_StatusDeflection StatusPrecedent,Standard_Integer& NbDivision,Standard_Real& Step,const Standard_Integer StepSign) ;
  
  Standard_EXPORT     void ComputeOpenLine(const TColStd_SequenceOfReal& Umult,const TColStd_SequenceOfReal& Vmult,const IntSurf_SequenceOfPathPoint& Pnts1,IntPatch_TheSurfFunction& Section,Standard_Boolean& Rajout) ;
  
  Standard_EXPORT     void OpenLine(const Standard_Integer N,const IntSurf_PntOn2S& Psol,const IntSurf_SequenceOfPathPoint& Pnts1,IntPatch_TheSurfFunction& Section,const Handle(IntPatch_TheIWLineOfTheIWalking)& Line) ;
  
  Standard_EXPORT     void ComputeCloseLine(const TColStd_SequenceOfReal& Umult,const TColStd_SequenceOfReal& Vmult,const IntSurf_SequenceOfPathPoint& Pnts1,const IntSurf_SequenceOfInteriorPoint& Pnts2,IntPatch_TheSurfFunction& Section,Standard_Boolean& Rajout) ;
  
  Standard_EXPORT     void AddPointInCurrentLine(const Standard_Integer N,const IntSurf_PathPoint& PathPnt,const Handle(IntPatch_TheIWLineOfTheIWalking)& CurrentLine) const;
  
  Standard_EXPORT     void MakeWalkingPoint(const Standard_Integer Case,const Standard_Real U,const Standard_Real V,IntPatch_TheSurfFunction& Section,IntSurf_PntOn2S& Psol) ;




private:



Standard_Boolean done;
IntSurf_SequenceOfPathPoint seqSingle;
Standard_Real fleche;
Standard_Real pas;
math_Vector tolerance;
Standard_Real epsilon;
Standard_Boolean reversed;
TColStd_SequenceOfReal ustart1;
TColStd_SequenceOfReal vstart1;
TColStd_SequenceOfInteger nbMultiplicities;
TColStd_SequenceOfInteger etat1;
TColStd_SequenceOfReal ustart2;
TColStd_SequenceOfReal vstart2;
TColStd_SequenceOfInteger etat2;
Standard_Real Um;
Standard_Real UM;
Standard_Real Vm;
Standard_Real VM;
IntSurf_PntOn2S previousPoint;
Standard_Boolean prevtg;
gp_Vec previousd3d;
gp_Dir2d previousd2d;
TColStd_SequenceOfInteger seqAjout;
IntPatch_SequenceOfIWLineOfTheIWalking lines;


};

#define ThePointOfPath IntSurf_PathPoint
#define ThePointOfPath_hxx <IntSurf_PathPoint.hxx>
#define ThePointOfPathTool IntSurf_PathPointTool
#define ThePointOfPathTool_hxx <IntSurf_PathPointTool.hxx>
#define ThePOPIterator IntSurf_SequenceOfPathPoint
#define ThePOPIterator_hxx <IntSurf_SequenceOfPathPoint.hxx>
#define ThePointOfLoop IntSurf_InteriorPoint
#define ThePointOfLoop_hxx <IntSurf_InteriorPoint.hxx>
#define ThePointOfLoopTool IntSurf_InteriorPointTool
#define ThePointOfLoopTool_hxx <IntSurf_InteriorPointTool.hxx>
#define ThePOLIterator IntSurf_SequenceOfInteriorPoint
#define ThePOLIterator_hxx <IntSurf_SequenceOfInteriorPoint.hxx>
#define ThePSurface Handle_Adaptor3d_HSurface
#define ThePSurface_hxx <Adaptor3d_HSurface.hxx>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hxx>
#define TheIWFunction IntPatch_TheSurfFunction
#define TheIWFunction_hxx <IntPatch_TheSurfFunction.hxx>
#define IntWalk_TheIWLine IntPatch_TheIWLineOfTheIWalking
#define IntWalk_TheIWLine_hxx <IntPatch_TheIWLineOfTheIWalking.hxx>
#define IntWalk_SequenceOfIWLine IntPatch_SequenceOfIWLineOfTheIWalking
#define IntWalk_SequenceOfIWLine_hxx <IntPatch_SequenceOfIWLineOfTheIWalking.hxx>
#define IntWalk_SequenceNodeOfSequenceOfIWLine IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking
#define IntWalk_SequenceNodeOfSequenceOfIWLine_hxx <IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking.hxx>
#define IntWalk_SequenceNodeOfSequenceOfIWLine IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking
#define IntWalk_SequenceNodeOfSequenceOfIWLine_hxx <IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking.hxx>
#define Handle_IntWalk_TheIWLine Handle_IntPatch_TheIWLineOfTheIWalking
#define IntWalk_TheIWLine_Type_() IntPatch_TheIWLineOfTheIWalking_Type_()
#define Handle_IntWalk_SequenceNodeOfSequenceOfIWLine Handle_IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking
#define IntWalk_SequenceNodeOfSequenceOfIWLine_Type_() IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking_Type_()
#define Handle_IntWalk_SequenceNodeOfSequenceOfIWLine Handle_IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking
#define IntWalk_SequenceNodeOfSequenceOfIWLine_Type_() IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking_Type_()
#define IntWalk_IWalking IntPatch_TheIWalking
#define IntWalk_IWalking_hxx <IntPatch_TheIWalking.hxx>

#include <IntWalk_IWalking.lxx>

#undef ThePointOfPath
#undef ThePointOfPath_hxx
#undef ThePointOfPathTool
#undef ThePointOfPathTool_hxx
#undef ThePOPIterator
#undef ThePOPIterator_hxx
#undef ThePointOfLoop
#undef ThePointOfLoop_hxx
#undef ThePointOfLoopTool
#undef ThePointOfLoopTool_hxx
#undef ThePOLIterator
#undef ThePOLIterator_hxx
#undef ThePSurface
#undef ThePSurface_hxx
#undef ThePSurfaceTool
#undef ThePSurfaceTool_hxx
#undef TheIWFunction
#undef TheIWFunction_hxx
#undef IntWalk_TheIWLine
#undef IntWalk_TheIWLine_hxx
#undef IntWalk_SequenceOfIWLine
#undef IntWalk_SequenceOfIWLine_hxx
#undef IntWalk_SequenceNodeOfSequenceOfIWLine
#undef IntWalk_SequenceNodeOfSequenceOfIWLine_hxx
#undef IntWalk_SequenceNodeOfSequenceOfIWLine
#undef IntWalk_SequenceNodeOfSequenceOfIWLine_hxx
#undef Handle_IntWalk_TheIWLine
#undef IntWalk_TheIWLine_Type_
#undef Handle_IntWalk_SequenceNodeOfSequenceOfIWLine
#undef IntWalk_SequenceNodeOfSequenceOfIWLine_Type_
#undef Handle_IntWalk_SequenceNodeOfSequenceOfIWLine
#undef IntWalk_SequenceNodeOfSequenceOfIWLine_Type_
#undef IntWalk_IWalking
#undef IntWalk_IWalking_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
