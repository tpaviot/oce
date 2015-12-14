// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _AIS_PerpendicularRelation_HeaderFile
#define _AIS_PerpendicularRelation_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_AIS_PerpendicularRelation.hxx>

#include <gp_Pnt.hxx>
#include <AIS_Relation.hxx>
#include <Handle_Geom_Plane.hxx>
#include <PrsMgr_PresentationManager3d.hxx>
#include <Handle_Prs3d_Presentation.hxx>
#include <Standard_Integer.hxx>
#include <Handle_Prs3d_Projector.hxx>
#include <Handle_Geom_Transformation.hxx>
#include <SelectMgr_Selection.hxx>
class TopoDS_Shape;
class Geom_Plane;
class Prs3d_Presentation;
class Prs3d_Projector;
class Geom_Transformation;


//! A framework to display constraints of perpendicularity
//! between two or more interactive datums. These
//! datums can be edges or faces.
class AIS_PerpendicularRelation : public AIS_Relation
{

public:

  
  //! Constructs an object to display constraints of
  //! perpendicularity on shapes.
  //! This object is defined by a first shape aFShape, a
  //! second shape aSShape, and a plane aPlane.
  //! aPlane is the plane of reference to show and test the
  //! perpendicular relation between two shapes, at least
  //! one of which has a revolved surface.
  Standard_EXPORT AIS_PerpendicularRelation(const TopoDS_Shape& aFShape, const TopoDS_Shape& aSShape, const Handle(Geom_Plane)& aPlane);
  
  //! Constructs an object to display constraints of
  //! perpendicularity on shapes.
  //! This object is defined by a first shape aFShape and a
  //! second shape aSShape.
  Standard_EXPORT AIS_PerpendicularRelation(const TopoDS_Shape& aFShape, const TopoDS_Shape& aSShape);
  
  //! computes the presentation according to a point of view
  //! given by <aProjector>.
  //! To be Used when the associated degenerated Presentations
  //! have been transformed by <aTrsf> which is not a Pure
  //! Translation. The HLR Prs can't be deducted automatically
  //! WARNING :<aTrsf> must be applied
  //! to the object to display before computation  !!!
  Standard_EXPORT virtual   void Compute (const Handle(Prs3d_Projector)& aProjector, const Handle(Geom_Transformation)& aTrsf, const Handle(Prs3d_Presentation)& aPresentation) ;




  DEFINE_STANDARD_RTTI(AIS_PerpendicularRelation)

protected:




private: 

  
  Standard_EXPORT   void Compute (const Handle(PrsMgr_PresentationManager3d)& aPresentationManager, const Handle(Prs3d_Presentation)& aPresentation, const Standard_Integer aMode = 0) ;
  
  Standard_EXPORT   void Compute (const Handle(Prs3d_Projector)& aProjector, const Handle(Prs3d_Presentation)& aPresentation) ;
  
  Standard_EXPORT   void ComputeSelection (const Handle(SelectMgr_Selection)& aSelection, const Standard_Integer aMode) ;
  
  Standard_EXPORT   void ComputeTwoFacesPerpendicular (const Handle(Prs3d_Presentation)& aPresentation) ;
  
  Standard_EXPORT   void ComputeTwoEdgesPerpendicular (const Handle(Prs3d_Presentation)& aPresentation) ;

  gp_Pnt myFAttach;
  gp_Pnt mySAttach;


};







#endif // _AIS_PerpendicularRelation_HeaderFile
