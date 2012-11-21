// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepFeat_MakeRevolutionForm_HeaderFile
#define _BRepFeat_MakeRevolutionForm_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _gp_Ax1_HeaderFile
#include <gp_Ax1.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_Geom_Plane_HeaderFile
#include <Handle_Geom_Plane.hxx>
#endif
#ifndef _TopTools_DataMapOfShapeListOfShape_HeaderFile
#include <TopTools_DataMapOfShapeListOfShape.hxx>
#endif
#ifndef _TopTools_ListOfShape_HeaderFile
#include <TopTools_ListOfShape.hxx>
#endif
#ifndef _BRepFeat_RibSlot_HeaderFile
#include <BRepFeat_RibSlot.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Geom_Plane;
class Standard_ConstructionError;
class TopoDS_Shape;
class TopoDS_Wire;
class gp_Ax1;
class TopoDS_Edge;
class TopoDS_Face;
class TopTools_ListOfShape;
class gp_Pnt;


//! MakeRevolutionForm Generates a surface of <br>
//! revolution in the feature as it slides along a <br>
//! revolved face in the basis shape. <br>
//! The semantics of mechanical features is built <br>
//! around giving thickness to a contour. This <br>
//! thickness can either be unilateral - on one side <br>
//! of the contour - or bilateral - on both sides. As <br>
//! in the semantics of form features, the thickness <br>
//! is defined by construction of shapes in specific contexts. <br>
//! The development contexts differ, however,in <br>
//! case of mechanical features. Here they include extrusion: <br>
//! -   to a limiting face of the basis shape <br>
//! -   to or from a limiting plane <br>
//! -   to a height. <br>
class BRepFeat_MakeRevolutionForm  : public BRepFeat_RibSlot {
public:

  DEFINE_STANDARD_ALLOC

  //! initializes the linear form class. <br>
      BRepFeat_MakeRevolutionForm();
  //! a contour W, a shape Sbase and a plane P are initialized to serve as <br>
//!   the basic elements in the construction of the rib or groove. The axis Axis of the <br>
//!   revolved surface in the basis shape defines the feature's axis of revolution. <br>
//!   Height1 and Height2 may be used as limits to the construction of the feature. <br>
//! Fuse offers a choice between: <br>
//! -   removing matter with a Boolean cut using the setting 0 in case of the groove <br>
//! -   adding matter with Boolean fusion using the setting 1 in case of the rib. <br>
      BRepFeat_MakeRevolutionForm(const TopoDS_Shape& Sbase,const TopoDS_Wire& W,const Handle(Geom_Plane)& Plane,const gp_Ax1& Axis,const Standard_Real Height1,const Standard_Real Height2,const Standard_Integer Fuse,Standard_Boolean& Sliding);
  //! Initializes this construction algorithm <br>
//! A contour W, a shape Sbase and a plane P are initialized to serve as the basic elements <br>
//! in the construction of the rib or groove. The axis Axis of the revolved surface in the basis <br>
//! shape defines the feature's axis of revolution. Height1 and Height2 may be <br>
//! used as limits to the construction of the feature. <br>
//! Fuse offers a choice between: <br>
//! -   removing matter with a Boolean cut using the setting 0 in case of the groove <br>
//! -   adding matter with Boolean fusion using the setting 1 in case of the rib. <br>
  Standard_EXPORT     void Init(const TopoDS_Shape& Sbase,const TopoDS_Wire& W,const Handle(Geom_Plane)& Plane,const gp_Ax1& Axis,const Standard_Real Height1,const Standard_Real Height2,const Standard_Integer Fuse,Standard_Boolean& Sliding) ;
  //! Indicates that the edge <E> will slide on the face <br>
//! <OnFace>. Raises ConstructionError  if the  face does not belong to the <br>
//! basis shape, or the edge to the prismed shape. <br>
  Standard_EXPORT     void Add(const TopoDS_Edge& E,const TopoDS_Face& OnFace) ;
  //! Performs a prism from the wire to the plane <br>
//! along the basis shape S. Reconstructs the feature topologically. <br>
  Standard_EXPORT     void Perform() ;
  
  Standard_EXPORT     Standard_Boolean Propagate(TopTools_ListOfShape& L,const TopoDS_Face& F,const gp_Pnt& FPoint,const gp_Pnt& LPoint,Standard_Boolean& falseside) ;





protected:





private:



gp_Ax1 myAxe;
Standard_Real myHeight1;
Standard_Real myHeight2;
Standard_Boolean mySliding;
Handle_Geom_Plane myPln;
Standard_Real myBnd;
TopTools_DataMapOfShapeListOfShape mySlface;
TopTools_ListOfShape myListOfEdges;
Standard_Real myTol;
Standard_Real myAngle1;
Standard_Real myAngle2;


};


#include <BRepFeat_MakeRevolutionForm.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
