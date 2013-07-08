// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StepToTopoDS_HeaderFile
#define _StepToTopoDS_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_TCollection_HAsciiString_HeaderFile
#include <Handle_TCollection_HAsciiString.hxx>
#endif
#ifndef _StepToTopoDS_BuilderError_HeaderFile
#include <StepToTopoDS_BuilderError.hxx>
#endif
#ifndef _StepToTopoDS_TranslateShellError_HeaderFile
#include <StepToTopoDS_TranslateShellError.hxx>
#endif
#ifndef _StepToTopoDS_TranslateFaceError_HeaderFile
#include <StepToTopoDS_TranslateFaceError.hxx>
#endif
#ifndef _StepToTopoDS_TranslateEdgeError_HeaderFile
#include <StepToTopoDS_TranslateEdgeError.hxx>
#endif
#ifndef _StepToTopoDS_TranslateVertexError_HeaderFile
#include <StepToTopoDS_TranslateVertexError.hxx>
#endif
#ifndef _StepToTopoDS_TranslateVertexLoopError_HeaderFile
#include <StepToTopoDS_TranslateVertexLoopError.hxx>
#endif
#ifndef _StepToTopoDS_TranslatePolyLoopError_HeaderFile
#include <StepToTopoDS_TranslatePolyLoopError.hxx>
#endif
#ifndef _Standard_CString_HeaderFile
#include <Standard_CString.hxx>
#endif
#ifndef _StepToTopoDS_GeometricToolError_HeaderFile
#include <StepToTopoDS_GeometricToolError.hxx>
#endif
class TCollection_HAsciiString;
class StepToTopoDS_Root;
class StepToTopoDS_TranslateShell;
class StepToTopoDS_TranslateFace;
class StepToTopoDS_TranslateEdgeLoop;
class StepToTopoDS_TranslateEdge;
class StepToTopoDS_TranslateVertex;
class StepToTopoDS_TranslatePolyLoop;
class StepToTopoDS_TranslateVertexLoop;
class StepToTopoDS_TranslateCompositeCurve;
class StepToTopoDS_TranslateCurveBoundedSurface;
class StepToTopoDS_Builder;
class StepToTopoDS_MakeTransformed;
class StepToTopoDS_GeometricTool;
class StepToTopoDS_Tool;
class StepToTopoDS_CartesianPointHasher;
class StepToTopoDS_PointPair;
class StepToTopoDS_PointPairHasher;
class StepToTopoDS_NMTool;
class StepToTopoDS_DataMapOfRI;
class StepToTopoDS_DataMapOfRINames;
class StepToTopoDS_DataMapOfTRI;
class StepToTopoDS_PointEdgeMap;
class StepToTopoDS_PointVertexMap;
class StepToTopoDS_DataMapNodeOfDataMapOfRI;
class StepToTopoDS_DataMapIteratorOfDataMapOfRI;
class StepToTopoDS_DataMapNodeOfDataMapOfRINames;
class StepToTopoDS_DataMapIteratorOfDataMapOfRINames;
class StepToTopoDS_DataMapNodeOfDataMapOfTRI;
class StepToTopoDS_DataMapIteratorOfDataMapOfTRI;
class StepToTopoDS_DataMapNodeOfPointEdgeMap;
class StepToTopoDS_DataMapIteratorOfPointEdgeMap;
class StepToTopoDS_DataMapNodeOfPointVertexMap;
class StepToTopoDS_DataMapIteratorOfPointVertexMap;


//! This package implements the mapping between AP214 <br>
//!  Shape representation and  CAS.CAD Shape Representation. <br>
//!  The source schema is Part42 (which is included in AP214) <br>
class StepToTopoDS  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   static  Handle_TCollection_HAsciiString DecodeBuilderError(const StepToTopoDS_BuilderError Error) ;
  
  Standard_EXPORT   static  Handle_TCollection_HAsciiString DecodeShellError(const StepToTopoDS_TranslateShellError Error) ;
  
  Standard_EXPORT   static  Handle_TCollection_HAsciiString DecodeFaceError(const StepToTopoDS_TranslateFaceError Error) ;
  
  Standard_EXPORT   static  Handle_TCollection_HAsciiString DecodeEdgeError(const StepToTopoDS_TranslateEdgeError Error) ;
  
  Standard_EXPORT   static  Handle_TCollection_HAsciiString DecodeVertexError(const StepToTopoDS_TranslateVertexError Error) ;
  
  Standard_EXPORT   static  Handle_TCollection_HAsciiString DecodeVertexLoopError(const StepToTopoDS_TranslateVertexLoopError Error) ;
  
  Standard_EXPORT   static  Handle_TCollection_HAsciiString DecodePolyLoopError(const StepToTopoDS_TranslatePolyLoopError Error) ;
  
  Standard_EXPORT   static  Standard_CString DecodeGeometricToolError(const StepToTopoDS_GeometricToolError Error) ;





protected:





private:




friend class StepToTopoDS_Root;
friend class StepToTopoDS_TranslateShell;
friend class StepToTopoDS_TranslateFace;
friend class StepToTopoDS_TranslateEdgeLoop;
friend class StepToTopoDS_TranslateEdge;
friend class StepToTopoDS_TranslateVertex;
friend class StepToTopoDS_TranslatePolyLoop;
friend class StepToTopoDS_TranslateVertexLoop;
friend class StepToTopoDS_TranslateCompositeCurve;
friend class StepToTopoDS_TranslateCurveBoundedSurface;
friend class StepToTopoDS_Builder;
friend class StepToTopoDS_MakeTransformed;
friend class StepToTopoDS_GeometricTool;
friend class StepToTopoDS_Tool;
friend class StepToTopoDS_CartesianPointHasher;
friend class StepToTopoDS_PointPair;
friend class StepToTopoDS_PointPairHasher;
friend class StepToTopoDS_NMTool;
friend class StepToTopoDS_DataMapOfRI;
friend class StepToTopoDS_DataMapOfRINames;
friend class StepToTopoDS_DataMapOfTRI;
friend class StepToTopoDS_PointEdgeMap;
friend class StepToTopoDS_PointVertexMap;
friend class StepToTopoDS_DataMapNodeOfDataMapOfRI;
friend class StepToTopoDS_DataMapIteratorOfDataMapOfRI;
friend class StepToTopoDS_DataMapNodeOfDataMapOfRINames;
friend class StepToTopoDS_DataMapIteratorOfDataMapOfRINames;
friend class StepToTopoDS_DataMapNodeOfDataMapOfTRI;
friend class StepToTopoDS_DataMapIteratorOfDataMapOfTRI;
friend class StepToTopoDS_DataMapNodeOfPointEdgeMap;
friend class StepToTopoDS_DataMapIteratorOfPointEdgeMap;
friend class StepToTopoDS_DataMapNodeOfPointVertexMap;
friend class StepToTopoDS_DataMapIteratorOfPointVertexMap;

};





// other Inline functions and methods (like "C++: function call" methods)


#endif
