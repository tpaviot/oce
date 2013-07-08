// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _STEPConstruct_ValidationProps_HeaderFile
#define _STEPConstruct_ValidationProps_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _StepBasic_Unit_HeaderFile
#include <StepBasic_Unit.hxx>
#endif
#ifndef _Handle_StepBasic_ProductDefinition_HeaderFile
#include <Handle_StepBasic_ProductDefinition.hxx>
#endif
#ifndef _STEPConstruct_Tool_HeaderFile
#include <STEPConstruct_Tool.hxx>
#endif
#ifndef _Handle_XSControl_WorkSession_HeaderFile
#include <Handle_XSControl_WorkSession.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_StepRepr_RepresentationItem_HeaderFile
#include <Handle_StepRepr_RepresentationItem.hxx>
#endif
#ifndef _Standard_CString_HeaderFile
#include <Standard_CString.hxx>
#endif
#ifndef _Handle_StepRepr_RepresentationContext_HeaderFile
#include <Handle_StepRepr_RepresentationContext.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Handle_StepRepr_NextAssemblyUsageOccurrence_HeaderFile
#include <Handle_StepRepr_NextAssemblyUsageOccurrence.hxx>
#endif
#ifndef _Handle_StepRepr_PropertyDefinition_HeaderFile
#include <Handle_StepRepr_PropertyDefinition.hxx>
#endif
class StepBasic_ProductDefinition;
class XSControl_WorkSession;
class TopoDS_Shape;
class StepRepr_RepresentationItem;
class StepRepr_CharacterizedDefinition;
class StepRepr_RepresentationContext;
class gp_Pnt;
class TColStd_SequenceOfTransient;
class StepRepr_NextAssemblyUsageOccurrence;
class StepRepr_PropertyDefinition;


//! This class provides tools for access (write and read) <br>
//!          the validation properties on shapes in the STEP file. <br>
//!          These are surface area, solid volume and centroid. <br>
class STEPConstruct_ValidationProps  : public STEPConstruct_Tool {
public:

  DEFINE_STANDARD_ALLOC

  //! Creates an empty tool <br>
  Standard_EXPORT   STEPConstruct_ValidationProps();
  //! Creates a tool and loads it with worksession <br>
  Standard_EXPORT   STEPConstruct_ValidationProps(const Handle(XSControl_WorkSession)& WS);
  //! Load worksession; returns True if succeeded <br>
  Standard_EXPORT     Standard_Boolean Init(const Handle(XSControl_WorkSession)& WS) ;
  //! General method for adding (writing) a validation property <br>
//!          for shape which should be already mapped on writing itself. <br>
//!          It uses FindTarget() to find target STEP entity <br>
//!          resulting from given shape, and associated context <br>
//!          Returns True if success, False in case of fail <br>
  Standard_EXPORT     Standard_Boolean AddProp(const TopoDS_Shape& Shape,const Handle(StepRepr_RepresentationItem)& Prop,const Standard_CString Descr,const Standard_Boolean instance = Standard_False) ;
  //! General method for adding (writing) a validation property <br>
//!          for shape which should be already mapped on writing itself. <br>
//!          It takes target and Context entities which correspond to shape <br>
//!          Returns True if success, False in case of fail <br>
  Standard_EXPORT     Standard_Boolean AddProp(const StepRepr_CharacterizedDefinition& target,const Handle(StepRepr_RepresentationContext)& Context,const Handle(StepRepr_RepresentationItem)& Prop,const Standard_CString Descr) ;
  //! Adds surface area property for given shape (already mapped). <br>
//!          Returns True if success, False in case of fail <br>
  Standard_EXPORT     Standard_Boolean AddArea(const TopoDS_Shape& Shape,const Standard_Real Area) ;
  //! Adds volume property for given shape (already mapped). <br>
//!          Returns True if success, False in case of fail <br>
  Standard_EXPORT     Standard_Boolean AddVolume(const TopoDS_Shape& Shape,const Standard_Real Vol) ;
  //! Adds centroid property for given shape (already mapped). <br>
//!          Returns True if success, False in case of fail <br>
//!          If instance is True, then centroid is assigned to <br>
//!          an instance of component in assembly <br>
  Standard_EXPORT     Standard_Boolean AddCentroid(const TopoDS_Shape& Shape,const gp_Pnt& Pnt,const Standard_Boolean instance = Standard_False) ;
  //! Finds target STEP entity to which validation props should <br>
//!          be assigned, and corresponding context, starting from shape <br>
//!          Returns True if success, False in case of fail <br>
  Standard_EXPORT     Standard_Boolean FindTarget(const TopoDS_Shape& S,StepRepr_CharacterizedDefinition& target,Handle(StepRepr_RepresentationContext)& Context,const Standard_Boolean instance = Standard_False) ;
  //! Searches for entities of the type PropertyDefinitionRepresentation <br>
//!          in the model and fills the sequence by them <br>
  Standard_EXPORT     Standard_Boolean LoadProps(TColStd_SequenceOfTransient& seq) const;
  //! Returns CDSR associated with given PpD or NULL if not found <br>
//!          (when, try GetPropSDR) <br>
  Standard_EXPORT     Handle_StepRepr_NextAssemblyUsageOccurrence GetPropNAUO(const Handle(StepRepr_PropertyDefinition)& PD) const;
  //! Returns SDR associated with given PpD or NULL if not found <br>
//!          (when, try GetPropCDSR) <br>
  Standard_EXPORT     Handle_StepBasic_ProductDefinition GetPropPD(const Handle(StepRepr_PropertyDefinition)& PD) const;
  //! Returns Shape associated with given SDR or Null Shape <br>
//!          if not found <br>
  Standard_EXPORT     TopoDS_Shape GetPropShape(const Handle(StepBasic_ProductDefinition)& ProdDef) const;
  //! Returns Shape associated with given PpD or Null Shape <br>
//!          if not found <br>
  Standard_EXPORT     TopoDS_Shape GetPropShape(const Handle(StepRepr_PropertyDefinition)& PD) const;
  //! Returns value of Real-Valued property (Area or Volume) <br>
//!          If Property is neither Area nor Volume, returns False <br>
//!          Else returns True and isArea indicates whether property <br>
//!          is area or volume <br>
  Standard_EXPORT     Standard_Boolean GetPropReal(const Handle(StepRepr_RepresentationItem)& item,Standard_Real& Val,Standard_Boolean& isArea) const;
  //! Returns value of Centriod property (or False if it is not) <br>
  Standard_EXPORT     Standard_Boolean GetPropPnt(const Handle(StepRepr_RepresentationItem)& item,const Handle(StepRepr_RepresentationContext)& Context,gp_Pnt& Pnt) const;
  //! Sets current assembly shape SDR (for FindCDSR calls) <br>
  Standard_EXPORT     void SetAssemblyShape(const TopoDS_Shape& shape) ;





protected:





private:



StepBasic_Unit areaUnit;
StepBasic_Unit volUnit;
Handle_StepBasic_ProductDefinition myAssemblyPD;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
