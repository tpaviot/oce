// File:      VrmlData_ShapeConvert.hxx
// Created:   04.08.07 09:48
// Author:    Alexander GRIGORIEV
// Copyright: Open Cascade 2007


#ifndef VrmlData_ShapeConvert_HeaderFile
#define VrmlData_ShapeConvert_HeaderFile

#include <VrmlData_Geometry.hxx>
#include <VrmlData_Appearance.hxx>
#include <NCollection_List.hxx>
#include <TopoDS_Shape.hxx>

class VrmlData_Scene;
class TopoDS_Face;
class Handle_Poly_Triangulation;
class Handle_Poly_Polygon3D;
class Handle_VrmlData_Coordinate;
/**
 * Algorithm converting one shape or a set of shapes to VrmlData_Scene.
 */

class VrmlData_ShapeConvert 
{
  // Note : This operator must be implemented on first use. It is currently defined to avoid compiler warnings
  VrmlData_ShapeConvert & operator = (const VrmlData_ShapeConvert &) { return *this; }

public:

  typedef struct {
    TCollection_AsciiString Name;
    TopoDS_Shape            Shape;
    Handle(VrmlData_Node)   Node;
  } ShapeData;

  // ---------- PUBLIC METHODS ----------


  /**
   * Constructor.
   * @param theScene
   *   Scene receiving all Vrml data.
   * @param theScale
   *   Scale factor, considering that VRML standard specifies coordinates in
   *   meters. So if your data are in mm, you should provide theScale=0.001
   */
  inline VrmlData_ShapeConvert (VrmlData_Scene&     theScene,
                                const Standard_Real theScale = 1.)
    : myScene (theScene),
      myScale (theScale)
  {}

  /**
   * Add one shape to the internal list, may be called several times with
   * different shapes.
   */
  Standard_EXPORT void AddShape (const TopoDS_Shape& theShape,
                                 const char *        theName = 0L);

  /**
   * Convert all accumulated shapes and store them in myScene.
   * The internal data structures are cleared in the end of convertion.
   * @param theExtractFaces
   *   If True,  converter extracst faces from the shapes. 
   * @param theExtractEdges
   *   If True,  converter extracts edges from the shapes.
   * @param theDeflection 
   *   Deflection for tessellation of geometrical lines/surfaces. Existing mesh
   *   is used if its deflection is smaller than the one given by this
   *   parameter.
   * @param theDeflAngle 
   *   Angular deflection for tessellation of geometrical lines. 
   */
  Standard_EXPORT void Convert (const Standard_Boolean theExtractFaces,
				const Standard_Boolean theExtractEdges,
                                const Standard_Real    theDeflection = 0.01,
				const Standard_Real    theDeflAngle = 20.*PI/180.);
                                //this value of theDeflAngle is used by default 
                                //for tesselation while shading (Drawer->HLRAngle())
  
 protected:
  // ---------- PROTECTED METHODS ----------

  Handle_VrmlData_Geometry triToIndexedFaceSet
                                (const Handle_Poly_Triangulation&,
                                 const TopoDS_Face&,
                                 const Handle_VrmlData_Coordinate&);

  Handle_VrmlData_Geometry polToIndexedLineSet
                                (const Handle_Poly_Polygon3D&);

  Handle_VrmlData_Appearance defaultMaterialFace () const;

  Handle_VrmlData_Appearance defaultMaterialEdge () const;

 private:
  // ---------- PRIVATE FIELDS ----------

  VrmlData_Scene&                       myScene;
  Standard_Real                         myScale;
  NCollection_List <ShapeData>          myShapes;
};

#endif
