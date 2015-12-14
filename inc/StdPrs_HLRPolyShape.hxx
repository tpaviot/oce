// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StdPrs_HLRPolyShape_HeaderFile
#define _StdPrs_HLRPolyShape_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Prs3d_Root.hxx>
#include <Handle_Prs3d_Presentation.hxx>
#include <Prs3d_Drawer.hxx>
#include <Handle_Prs3d_Projector.hxx>
class Prs3d_Presentation;
class TopoDS_Shape;
class Prs3d_Projector;


//! Instantiates Prs3d_PolyHLRShape to define a
//! display of a shape where hidden and visible lines are
//! identified with respect to a given projection.
//! StdPrs_HLRPolyShape works with a polyhedral
//! simplification of the shape whereas
//! StdPrs_HLRShape takes the shape itself into
//! account. When you use StdPrs_HLRShape, you
//! obtain an exact result, whereas, when you use
//! StdPrs_HLRPolyShape, you reduce computation
//! time but obtain polygonal segments.
//! The polygonal algorithm is used.
class StdPrs_HLRPolyShape  : public Prs3d_Root
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Defines the hidden line removal display of the
  //! topology aShape in the projection defined by
  //! aProjector. The shape and the projection are added
  //! to the display aPresentation, and the attributes of the
  //! elements present in the aPresentation are defined by
  //! the attribute manager aDrawer.
  Standard_EXPORT static   void Add (const Handle(Prs3d_Presentation)& aPresentation, const TopoDS_Shape& aShape, const Handle(Prs3d_Drawer)& aDrawer, const Handle(Prs3d_Projector)& aProjector) ;




protected:





private:





};







#endif // _StdPrs_HLRPolyShape_HeaderFile
