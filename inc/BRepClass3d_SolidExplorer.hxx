// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepClass3d_SolidExplorer_HeaderFile
#define _BRepClass3d_SolidExplorer_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Bnd_Box_HeaderFile
#include <Bnd_Box.hxx>
#endif
#ifndef _TopoDS_Shape_HeaderFile
#include <TopoDS_Shape.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _TopExp_Explorer_HeaderFile
#include <TopExp_Explorer.hxx>
#endif
#ifndef _BRepClass3d_MapOfInter_HeaderFile
#include <BRepClass3d_MapOfInter.hxx>
#endif
#ifndef _Handle_BRepAdaptor_HSurface_HeaderFile
#include <Handle_BRepAdaptor_HSurface.hxx>
#endif
#ifndef _TopAbs_State_HeaderFile
#include <TopAbs_State.hxx>
#endif
class TopoDS_Shape;
class gp_Pnt;
class TopoDS_Face;
class gp_Vec;
class BRepAdaptor_HSurface;
class TopoDS_Shell;
class gp_Lin;
class Bnd_Box;
class IntCurvesFace_Intersector;


//! Provide an   exploration of a  BRep Shape   for the <br>
//!          classification. <br>
class BRepClass3d_SolidExplorer  {
public:

  void* operator new(size_t,void* anAddress) 
  {
    return anAddress;
  }
  void* operator new(size_t size) 
  {
    return Standard::Allocate(size); 
  }
  void  operator delete(void *anAddress) 
  {
    if (anAddress) Standard::Free((Standard_Address&)anAddress); 
  }

  
  Standard_EXPORT   BRepClass3d_SolidExplorer();
  //! Raise if called. <br>
  Standard_EXPORT   BRepClass3d_SolidExplorer(const BRepClass3d_SolidExplorer& Oth);
  
  Standard_EXPORT   BRepClass3d_SolidExplorer(const TopoDS_Shape& S);
  
  Standard_EXPORT   virtual  void Delete() ;
Standard_EXPORT virtual ~BRepClass3d_SolidExplorer(){Destroy() ; }
  
  Standard_EXPORT     void InitShape(const TopoDS_Shape& S) ;
  //! Should return True if P outside of bounding vol. of the shape <br>
  Standard_EXPORT   virtual  Standard_Boolean Reject(const gp_Pnt& P) const;
  //! compute a point P in the face  F. Param is a Real in <br>
//!         ]0,1[ and   is  used to  initialise  the algorithm. For <br>
//!         different values , different points are returned. <br>
  Standard_EXPORT   static  Standard_Boolean FindAPointInTheFace(const TopoDS_Face& F,gp_Pnt& P,Standard_Real& Param) ;
  
  Standard_EXPORT   static  Standard_Boolean FindAPointInTheFace(const TopoDS_Face& F,gp_Pnt& P,Standard_Real& u,Standard_Real& v,Standard_Real& Param) ;
  
  Standard_EXPORT   static  Standard_Boolean FindAPointInTheFace(const TopoDS_Face& F,gp_Pnt& P,Standard_Real& u,Standard_Real& v,Standard_Real& Param,gp_Vec& theVecD1U,gp_Vec& theVecD1V) ;
  
  Standard_EXPORT   static  Standard_Boolean FindAPointInTheFace(const TopoDS_Face& F,gp_Pnt& P,Standard_Real& u,Standard_Real& v) ;
  
  Standard_EXPORT   static  Standard_Boolean FindAPointInTheFace(const TopoDS_Face& F,gp_Pnt& P) ;
  
  Standard_EXPORT   static  Standard_Boolean FindAPointInTheFace(const TopoDS_Face& F,Standard_Real& u,Standard_Real& v) ;
  
  Standard_EXPORT     Standard_Boolean PointInTheFace(const TopoDS_Face& F,gp_Pnt& P,Standard_Real& u,Standard_Real& v,Standard_Real& Param,Standard_Integer& Index) const;
  
  Standard_EXPORT     Standard_Boolean PointInTheFace(const TopoDS_Face& F,gp_Pnt& P,Standard_Real& u,Standard_Real& v,Standard_Real& Param,Standard_Integer& Index,const Handle(BRepAdaptor_HSurface)& surf,const Standard_Real u1,const Standard_Real v1,const Standard_Real u2,const Standard_Real v2) const;
  //! <Index> gives point index  to  search from and returns <br>
//!          point index of succeseful search <br>
  Standard_EXPORT     Standard_Boolean PointInTheFace(const TopoDS_Face& F,gp_Pnt& P,Standard_Real& u,Standard_Real& v,Standard_Real& Param,Standard_Integer& Index,const Handle(BRepAdaptor_HSurface)& surf,const Standard_Real u1,const Standard_Real v1,const Standard_Real u2,const Standard_Real v2,gp_Vec& theVecD1U,gp_Vec& theVecD1V) const;
  //! Starts an exploration of the shells. <br>
  Standard_EXPORT     void InitShell() ;
  //! Returns True if there is a current shell. <br>
  Standard_EXPORT     Standard_Boolean MoreShell() const;
  //! Sets the explorer to the next shell. <br>
  Standard_EXPORT     void NextShell() ;
  //! Returns the current shell. <br>
  Standard_EXPORT     TopoDS_Shell CurrentShell() const;
  //! Returns True if the Shell is rejected. <br>
  Standard_EXPORT   virtual  Standard_Boolean RejectShell(const gp_Lin& L) const;
  //! Starts an exploration of the faces of the current shell. <br>
  Standard_EXPORT     void InitFace() ;
  //! Returns True if current face in current shell. <br>
  Standard_EXPORT     Standard_Boolean MoreFace() const;
  //! Sets the explorer to the next Face of the current shell. <br>
  Standard_EXPORT     void NextFace() ;
  //! Returns the current face. <br>
  Standard_EXPORT     TopoDS_Face CurrentFace() const;
  //! returns True if the face is rejected. <br>
  Standard_EXPORT   virtual  Standard_Boolean RejectFace(const gp_Lin& L) const;
  //! Returns  in <L>, <Par>  a segment having at least <br>
//!          one  intersection  with  the  shape  boundary  to <br>
//!          compute  intersections. <br>
//! <br>
  Standard_EXPORT     Standard_Integer Segment(const gp_Pnt& P,gp_Lin& L,Standard_Real& Par) ;
  //! Returns  in <L>, <Par>  a segment having at least <br>
//!          one  intersection  with  the  shape  boundary  to <br>
//!          compute  intersections. <br>
//! <br>
//!          The First Call to this method returns a line which <br>
//!          point to a point of the first face of the shape. <br>
//!          The Second Call provide a line to the second face <br>
//!          and so on. <br>
//! <br>
  Standard_EXPORT     Standard_Integer OtherSegment(const gp_Pnt& P,gp_Lin& L,Standard_Real& Par) ;
  //! Returns the index of face for which <br>
//!          last segment is calculated. <br>
  Standard_EXPORT     Standard_Integer GetFaceSegmentIndex() const;
  
  Standard_EXPORT   virtual  void DumpSegment(const gp_Pnt& P,const gp_Lin& L,const Standard_Real Par,const TopAbs_State S) const;
  
  Standard_EXPORT    const Bnd_Box& Box() const;
  
  Standard_EXPORT     IntCurvesFace_Intersector& Intersector(const TopoDS_Face& F) const;
  
  Standard_EXPORT     void Destroy() ;





protected:





private:



Bnd_Box myBox;
TopoDS_Shape myShape;
Standard_Boolean myReject;
Standard_Integer myFirstFace;
Standard_Real myParamOnEdge;
TopExp_Explorer myShellExplorer;
TopExp_Explorer myFaceExplorer;
BRepClass3d_MapOfInter myMapOfInter;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
