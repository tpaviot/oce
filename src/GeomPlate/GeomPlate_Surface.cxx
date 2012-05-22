// Created on: 1996-11-21
// Created by: Joelle CHAUVET
// Copyright (c) 1996-1999 Matra Datavision
// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

// Modified:	Wed Mar  5 09:45:42 1997
//    by:	Joelle CHAUVET
//              G1134 : new methods RealBounds and Constraints
// Modified:	Mon Jun 16 15:22:41 1997
//    by:	Jerome LEMONIER
//              Correction de la methode D2 (faute de frappe dans le code)
//              Correction de la methode D1 (D0 inutile)


#include <GeomPlate_Surface.ixx>
#include <gp_XY.hxx>


//=======================================================================
//function : GeomPlate_Surface
//purpose  : 
//=======================================================================

GeomPlate_Surface::GeomPlate_Surface(const Handle(Geom_Surface)& Surfinit,const Plate_Plate& Surfinter) : mySurfinter(Surfinter),mySurfinit(Surfinit)
{
}

//=======================================================================
//function : UReverse
//purpose  : 
//=======================================================================

void GeomPlate_Surface::UReverse()
{
 //Standard_Failure::Raise("UReverse"); 
}


//=======================================================================
//function : UReversedParameter
//purpose  : 
//=======================================================================

Standard_Real GeomPlate_Surface::UReversedParameter(const Standard_Real U) const 
{ //Standard_Failure::Raise("UReversedParameter"); 
  return (-U);
}


//=======================================================================
//function : VReverse
//purpose  : 
//=======================================================================

void GeomPlate_Surface::VReverse()
{ //Standard_Failure::Raise("VReverse");
}


//=======================================================================
//function : VReversedParameter
//purpose  : 
//=======================================================================

Standard_Real GeomPlate_Surface::VReversedParameter(const Standard_Real V) const 
{ //Standard_Failure::Raise("VReversedParameter");
  return (-V);
}


//=======================================================================
//function : TransformParameters
//purpose  : 
//=======================================================================

//void GeomPlate_Surface::TransformParameters(Standard_Real& U, Standard_Real& V, const gp_Trsf& T) const 
void GeomPlate_Surface::TransformParameters(Standard_Real& , Standard_Real& , const gp_Trsf& ) const 
{//Standard_Failure::Raise("TransformParameters");
}


//=======================================================================
//function : ParametricTransformation
//purpose  : 
//=======================================================================

//gp_GTrsf2d GeomPlate_Surface::ParametricTransformation(const gp_Trsf& T) const 
gp_GTrsf2d GeomPlate_Surface::ParametricTransformation(const gp_Trsf& ) const 
{//Standard_Failure::Raise("ParametricTransformation");
  return gp_GTrsf2d();
}


//=======================================================================
//function : Bounds
//purpose  : 
//=======================================================================

void GeomPlate_Surface::Bounds(Standard_Real& U1, Standard_Real& U2, Standard_Real& V1, Standard_Real& V2) const 
{
  if (mySurfinit->DynamicType() == STANDARD_TYPE(GeomPlate_Surface))
    mySurfinit->Bounds(U1,U2,V1,V2);
  else
    {U1=myUmin;U2=myUmax;V1=myVmin;V2=myVmax;}
}


//=======================================================================
//function : IsUClosed
//purpose  : 
//=======================================================================

Standard_Boolean GeomPlate_Surface::IsUClosed() const 
{ //Standard_Failure::Raise("IsUClosed(");
  //return 1;
  return 0;
}


//=======================================================================
//function : IsVClosed
//purpose  : 
//=======================================================================

Standard_Boolean GeomPlate_Surface::IsVClosed() const 
{ //Standard_Failure::Raise("IsVClosed(");
  //return 1;
  return 0;
}


//=======================================================================
//function : IsUPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean GeomPlate_Surface::IsUPeriodic() const 
{
  return Standard_False;
}


//=======================================================================
//function : UPeriod
//purpose  : 
//=======================================================================

Standard_Real GeomPlate_Surface::UPeriod() const 
{ 
 return Standard_False;
}


//=======================================================================
//function : IsVPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean GeomPlate_Surface::IsVPeriodic() const 
{
  return  Standard_False;
}


//=======================================================================
//function : VPeriod
//purpose  : 
//=======================================================================

Standard_Real GeomPlate_Surface::VPeriod() const 
{ 
  return Standard_False;
}


//=======================================================================
//function : UIso
//purpose  : 
//=======================================================================

//Handle(Geom_Curve) GeomPlate_Surface::UIso(const Standard_Real U) const 
Handle(Geom_Curve) GeomPlate_Surface::UIso(const Standard_Real ) const 
{ //Standard_Failure::Raise("UIso");
  return Handle(Geom_Curve)();
}


//=======================================================================
//function : VIso
//purpose  : 
//=======================================================================

//Handle(Geom_Curve) GeomPlate_Surface::VIso(const Standard_Real V) const 
Handle(Geom_Curve) GeomPlate_Surface::VIso(const Standard_Real ) const 
{ //Standard_Failure::Raise("VIso");
  return Handle(Geom_Curve)();
}


//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

GeomAbs_Shape GeomPlate_Surface::Continuity() const 
{ //Standard_Failure::Raise("Continuity()");
  return GeomAbs_Shape();

}


//=======================================================================
//function : IsCNu
//purpose  : 
//=======================================================================

//Standard_Boolean GeomPlate_Surface::IsCNu(const Standard_Integer N) const 
Standard_Boolean GeomPlate_Surface::IsCNu(const Standard_Integer ) const 
{ Standard_Failure::Raise("IsCNu");
  return 1;
}


//=======================================================================
//function : IsCNv
//purpose  : 
//=======================================================================

//Standard_Boolean GeomPlate_Surface::IsCNv(const Standard_Integer N) const 
Standard_Boolean GeomPlate_Surface::IsCNv(const Standard_Integer ) const 
{ Standard_Failure::Raise("IsCNv");
 return 1;
}


//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

void GeomPlate_Surface::D0(const Standard_Real U, const Standard_Real V, gp_Pnt& P) const 
{
  gp_XY P1(U,V);
  gp_Pnt P2;
  mySurfinit->D0(U,V,P2);
  gp_XYZ P3;//=mySurfinter.Evaluate(P1);
 P3=mySurfinter.Evaluate(P1);
 for (Standard_Integer i=1; i<=3; i++)
    {
      P.SetCoord(i,P3.Coord(i)+P2.Coord(i));
    }
}


//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

void GeomPlate_Surface::D1(const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V) const 
{
  gp_XY P1(U,V);
  gp_Pnt P2;
  D0(U,V,P);
  gp_Vec V1U,V1V;
  mySurfinit->D1(U,V,P2,V1U,V1V);
  gp_XYZ V2U=mySurfinter.EvaluateDerivative(P1,1,0);
  gp_XYZ V2V=mySurfinter.EvaluateDerivative(P1,0,1);
  for (Standard_Integer i=1; i<=3; i++)
    {
      D1U.SetCoord(i,V1U.Coord(i)+V2U.Coord(i));
      D1V.SetCoord(i,V1V.Coord(i)+V2V.Coord(i));
    }
}


//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

void GeomPlate_Surface::D2(const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV) const 
{
  gp_XY P1(U,V);
  gp_Pnt P2;
  
  gp_Vec V1U,V1V,V1UV,vv,v;
  D1(U,V,P,D1U,D1V);
  mySurfinit->D2(U,V,P2,vv,v,V1U,V1V,V1UV);
  gp_XYZ V2U=mySurfinter.EvaluateDerivative(P1,2,0);
  gp_XYZ V2V=mySurfinter.EvaluateDerivative(P1,0,2);
  gp_XYZ V2UV=mySurfinter.EvaluateDerivative(P1,1,1);
  for (Standard_Integer i=1; i<=3; i++)
    {
      D2U.SetCoord(i,V1U.Coord(i)+V2U.Coord(i));
      D2V.SetCoord(i,V1V.Coord(i)+V2V.Coord(i));
      D2UV.SetCoord(i,V1UV.Coord(i)+V2UV.Coord(i));
    }
}


//=======================================================================
//function : D3
//purpose  : 
//=======================================================================

//void GeomPlate_Surface::D3(const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV, gp_Vec& D3U, gp_Vec& D3V, gp_Vec& D3UUV, gp_Vec& D3UVV) const 
void GeomPlate_Surface::D3(const Standard_Real , const Standard_Real , gp_Pnt& , gp_Vec& , gp_Vec& , gp_Vec& , gp_Vec& , gp_Vec& , gp_Vec& , gp_Vec& , gp_Vec& , gp_Vec& ) const 
{ Standard_Failure::Raise("D3");
}


//=======================================================================
//function : DN
//purpose  : 
//=======================================================================

//gp_Vec GeomPlate_Surface::DN(const Standard_Real U, const Standard_Real V, const Standard_Integer Nu, const Standard_Integer Nv) const 
gp_Vec GeomPlate_Surface::DN(const Standard_Real , const Standard_Real , const Standard_Integer , const Standard_Integer ) const 
{ Standard_Failure::Raise("DN");
  return gp_Vec();
}


//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

Handle(Geom_Geometry) GeomPlate_Surface::Copy() const 
{
  Handle(GeomPlate_Surface) GPS 
    = new  GeomPlate_Surface(mySurfinit,mySurfinter);
  return GPS;
}


//=======================================================================
//function : Transform
//purpose  : 
//=======================================================================

//void GeomPlate_Surface::Transform(const gp_Trsf& T)
void GeomPlate_Surface::Transform(const gp_Trsf& )
{ //Standard_Failure::Raise("Transform");
}

//=======================================================================
//function : CallSurfinit
//purpose  : 
//=======================================================================

Handle(Geom_Surface) GeomPlate_Surface::CallSurfinit() const

{
  return mySurfinit;
}


//=======================================================================
//function : SetBounds
//purpose  : 
//=======================================================================

void GeomPlate_Surface::SetBounds(const Standard_Real Umin, const Standard_Real Umax, const Standard_Real Vmin, const Standard_Real Vmax)
{
  if ((Umin>Umax) || (Vmin>Vmax)) Standard_Failure::Raise("Bounds haven't the good sense");
  else
    myUmin=Umin;myUmax=Umax;myVmin=Vmin;myVmax=Vmax;
  if ((Umin==Umax) || (Vmin==Vmax)) Standard_Failure::Raise("Bounds are equal");

}


//=======================================================================
//function : RealBounds
//purpose  : 
//=======================================================================

void GeomPlate_Surface::RealBounds(Standard_Real& U1, Standard_Real& U2, Standard_Real& V1, Standard_Real& V2) const 
{
  mySurfinter.UVBox(U1,U2,V1,V2);
}


//=======================================================================
//function : Constraints
//purpose  : 
//=======================================================================

void GeomPlate_Surface::Constraints(TColgp_SequenceOfXY& Seq) const 
{
  mySurfinter.UVConstraints(Seq);
}
