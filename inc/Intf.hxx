// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Intf_HeaderFile
#define _Intf_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class gp_Pnt;
class gp_XYZ;
class Intf_Polygon2d;
class Intf_ToolPolyhedron;
class Intf_Array1OfLin;
class Intf_SectionPoint;
class Intf_SeqOfSectionPoint;
class Intf_SectionLine;
class Intf_SeqOfSectionLine;
class Intf_TangentZone;
class Intf_SeqOfTangentZone;
class Intf_Interference;
class Intf_Tool;
class Intf_InterferencePolygon2d;
class Intf_InterferencePolygon3d;
class Intf_InterferencePolygonPolyhedron;
class Intf_InterferencePolyhedron;
class Intf_SequenceNodeOfSeqOfSectionPoint;
class Intf_SequenceNodeOfSeqOfTangentZone;
class Intf_SequenceNodeOfSeqOfSectionLine;


//! Interference computation  between polygons, lines  and <br>
//!          polyhedra with only  triangular  facets. These objects <br>
//!          are polygonal  representations of complex   curves and <br>
//!          triangulated representations of complex surfaces. <br>
class Intf  {
public:

  DEFINE_STANDARD_ALLOC

  //! Give the plane equation of the triangle <P1> <P2> <P3>. <br>
  Standard_EXPORT   static  void PlaneEquation(const gp_Pnt& P1,const gp_Pnt& P2,const gp_Pnt& P3,gp_XYZ& NormalVector,Standard_Real& PolarDistance) ;
  //! Compute if the triangle <P1> <P2> <P3> contain <ThePnt>. <br>
  Standard_EXPORT   static  Standard_Boolean Contain(const gp_Pnt& P1,const gp_Pnt& P2,const gp_Pnt& P3,const gp_Pnt& ThePnt) ;





protected:





private:




friend class Intf_Polygon2d;
friend class Intf_ToolPolyhedron;
friend class Intf_Array1OfLin;
friend class Intf_SectionPoint;
friend class Intf_SeqOfSectionPoint;
friend class Intf_SectionLine;
friend class Intf_SeqOfSectionLine;
friend class Intf_TangentZone;
friend class Intf_SeqOfTangentZone;
friend class Intf_Interference;
friend class Intf_Tool;
friend class Intf_InterferencePolygon2d;
friend class Intf_InterferencePolygon3d;
friend class Intf_InterferencePolygonPolyhedron;
friend class Intf_InterferencePolyhedron;
friend class Intf_SequenceNodeOfSeqOfSectionPoint;
friend class Intf_SequenceNodeOfSeqOfTangentZone;
friend class Intf_SequenceNodeOfSeqOfSectionLine;

};





// other Inline functions and methods (like "C++: function call" methods)


#endif
