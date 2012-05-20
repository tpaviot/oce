// Created on: 2004-05-20
// Created by: Sergey ZARITCHNY
// Copyright (c) 2004-2012 OPEN CASCADE SAS
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



#include <BinTools_SurfaceSet.ixx>
#include <BinTools.hxx>

#include <BinTools_CurveSet.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <Geom_BezierSurface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_OffsetSurface.hxx>

#include <gp_Pln.hxx>
#include <gp_Cylinder.hxx>
#include <gp_Cone.hxx>
#include <gp_Sphere.hxx>
#include <gp_Torus.hxx>

#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <Standard_Failure.hxx>
#include <Standard_ErrorHandler.hxx>

#define PLANE           1
#define CYLINDER        2
#define CONE            3
#define SPHERE          4
#define TORUS           5
#define LINEAREXTRUSION 6
#define REVOLUTION      7
#define BEZIER          8
#define BSPLINE         9
#define RECTANGULAR     10
#define OFFSET          11

//=======================================================================
//function : BinTools_SurfaceSet
//purpose  : 
//=======================================================================

BinTools_SurfaceSet::BinTools_SurfaceSet() 
{
}


//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================

void  BinTools_SurfaceSet::Clear()
{
  myMap.Clear();
}


//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

Standard_Integer  BinTools_SurfaceSet::Add(const Handle(Geom_Surface)& S)
{
  return myMap.Add(S);
}


//=======================================================================
//function : Surface
//purpose  : 
//=======================================================================

Handle(Geom_Surface)  BinTools_SurfaceSet::Surface
       (const Standard_Integer I)const 
{
  return  Handle(Geom_Surface)::DownCast(myMap(I));
}


//=======================================================================
//function : Index
//purpose  : 
//=======================================================================

Standard_Integer  BinTools_SurfaceSet::Index
  (const Handle(Geom_Surface)& S)const 
{
  return myMap.FindIndex(S);
}

//=======================================================================
//function : operator << (gp_Pnt)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const gp_Pnt P)
{
  BinTools::PutReal(OS, P.X());
  BinTools::PutReal(OS, P.Y());
  BinTools::PutReal(OS, P.Z());
  return OS;
}

//=======================================================================
//function : operator << (gp_Dir)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const gp_Dir D)
{
  BinTools::PutReal(OS, D.X());
  BinTools::PutReal(OS, D.Y());
  BinTools::PutReal(OS, D.Z());
  return OS;
}


//=======================================================================
//function : operator <<(Geom_Plane)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_Plane)& S)
{
  OS << (Standard_Byte)PLANE;
  gp_Pln P = S->Pln();
  OS << P.Location();//Pnt
  OS << P.Axis().Direction();
  OS << P.XAxis().Direction();
  OS << P.YAxis().Direction();
  return OS;
}


//=======================================================================
//function : operator <<(Geom_CylindricalSurface)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_CylindricalSurface)& S)
{
  OS << (Standard_Byte)CYLINDER;
  gp_Cylinder P = S->Cylinder();
  OS << P.Location();//Pnt
  OS << P.Axis().Direction();
  OS << P.XAxis().Direction();
  OS << P.YAxis().Direction();
  BinTools::PutReal(OS, P.Radius());
  return OS;
}


//=======================================================================
//function : operator <<(Geom_ConicalSurface)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_ConicalSurface)& S)
{
  OS << (Standard_Byte)CONE;
  gp_Cone P = S->Cone();
  OS << P.Location();//Pnt
  OS << P.Axis().Direction();
  OS << P.XAxis().Direction();
  OS << P.YAxis().Direction();
  BinTools::PutReal(OS, P.RefRadius());
  BinTools::PutReal(OS, P.SemiAngle());
  return OS;
}


//=======================================================================
//function : operator <<(Geom_SphericalSurface)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_SphericalSurface)& S)
{
  OS << (Standard_Byte)SPHERE;
  gp_Sphere P = S->Sphere();
  OS << P.Location();//Pnt
  OS << P.Position().Axis().Direction();
  OS << P.XAxis().Direction();
  OS << P.YAxis().Direction();
  BinTools::PutReal(OS, P.Radius());
  return OS;
}


//=======================================================================
//function : operator <<(Geom_ToroidalSurface)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_ToroidalSurface)& S)
{
  OS << (Standard_Byte)TORUS;
  gp_Torus P = S->Torus();
  OS << P.Location();//Pnt
  OS << P.Axis().Direction();
  OS << P.XAxis().Direction();
  OS << P.YAxis().Direction();
  BinTools::PutReal(OS, P.MajorRadius());
  BinTools::PutReal(OS, P.MinorRadius());
  return OS;
}


//=======================================================================
//function : operator <<(Geom_SurfaceOfLinearExtrusion)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_SurfaceOfLinearExtrusion)& S)
{
  OS << (Standard_Byte)LINEAREXTRUSION;
  OS << S->Direction();
  BinTools_CurveSet::WriteCurve(S->BasisCurve(),OS);
  return OS;
}


//=======================================================================
//function : operator <<(Geom_SurfaceOfRevolution)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_SurfaceOfRevolution)& S)
{
  OS << (Standard_Byte)REVOLUTION;
  OS << S->Location();
  OS << S->Direction();
  BinTools_CurveSet::WriteCurve(S->BasisCurve(),OS);
  return OS;
}


//=======================================================================
//function : operator <<(Geom_BezierSurface)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_BezierSurface)& S)
{
  OS << (Standard_Byte)BEZIER;
  Standard_Boolean urational = S->IsURational() ? 1:0;
  Standard_Boolean vrational = S->IsVRational() ? 1:0;
  BinTools::PutBool(OS, urational); //rational
  BinTools::PutBool(OS, vrational);
//  cout << "Bezier Surface:"<< endl;
//  cout << "\turational = "<<urational<<" vrational = " <<vrational<<endl;

// poles and weights
  Standard_Integer i,j,udegree,vdegree;
  udegree = S->UDegree();
  vdegree = S->VDegree();
#ifdef DEB
//  cout << "\tudegree  = " << udegree << ", vdegree = "<< vdegree<<endl;
#endif
  BinTools::PutExtChar(OS, (Standard_ExtCharacter)udegree);
  BinTools::PutExtChar(OS, (Standard_ExtCharacter)vdegree);
  for (i = 1; i <= udegree+1; i++) {
    for (j = 1; j <= vdegree+1; j++) {
      OS << S->Pole(i,j); //Pnt
#ifdef DEB
//      cout << "Bezier Surface: Pole Pnt: X = " << S->Pole(i,j).X()<< " Y = " << S->Pole(i,j).Y()<<" Z = " << S->Pole(i,j).Z()<<endl;
#endif      
      if (urational || vrational) {
	BinTools::PutReal(OS, S->Weight(i,j));//Real
#ifdef DEB
//	cout << "Bezier Surface: Put Real" << endl;
#endif
      }
    }
  }
#ifdef DEB
//  const Standard_Integer aPos = OS.tellp();
//  cout << "\tEnd of Bezier surface pos = " << aPos << endl;
#endif
  return OS;
}


//=======================================================================
//function : operator <<(Geom_BSplineSurface)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_BSplineSurface)& S)
{
  OS << (Standard_Byte)BSPLINE;
  Standard_Boolean urational = S->IsURational() ? 1:0;
  Standard_Boolean vrational = S->IsVRational() ? 1:0;
  Standard_Boolean uperiodic = S->IsUPeriodic() ? 1:0;
  Standard_Boolean vperiodic = S->IsVPeriodic() ? 1:0;
  BinTools::PutBool(OS, urational); 
  BinTools::PutBool(OS, vrational); 
  BinTools::PutBool(OS, uperiodic); 
  BinTools::PutBool(OS, vperiodic); 

// poles and weights
  Standard_Integer i,j,udegree,vdegree,nbupoles,nbvpoles,nbuknots,nbvknots;
  udegree  = S->UDegree();
  vdegree  = S->VDegree();
  nbupoles = S->NbUPoles();
  nbvpoles = S->NbVPoles();
  nbuknots = S->NbUKnots();
  nbvknots = S->NbVKnots();
  BinTools::PutExtChar(OS, (Standard_ExtCharacter) udegree);
  BinTools::PutExtChar(OS, (Standard_ExtCharacter) vdegree);
  BinTools::PutInteger(OS, nbupoles);
  BinTools::PutInteger(OS, nbvpoles);
  BinTools::PutInteger(OS, nbuknots);
  BinTools::PutInteger(OS, nbvknots);
  for (i = 1; i <= nbupoles; i++) {
    for (j = 1; j <= nbvpoles; j++) {
      OS << S->Pole(i,j); //Pnt
      if (urational || vrational)
	BinTools::PutReal(OS, S->Weight(i,j));//Real	
    }
  }

  for (i = 1; i <= nbuknots; i++) {
    BinTools::PutReal(OS,S->UKnot(i));
    BinTools::PutInteger(OS, S->UMultiplicity(i));
  }

  for (i = 1; i <= nbvknots; i++) {
    BinTools::PutReal(OS,S->VKnot(i));
    BinTools::PutInteger(OS, S->VMultiplicity(i));
  }
  return OS;
}


//=======================================================================
//function :  operator <<(Geom_RectangularTrimmedSurface)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_RectangularTrimmedSurface)& S)
{
  OS << (Standard_Byte)RECTANGULAR;
  Standard_Real U1,U2,V1,V2;
  S->Bounds(U1,U2,V1,V2);
  BinTools::PutReal(OS, U1);
  BinTools::PutReal(OS, U2);
  BinTools::PutReal(OS, V1);
  BinTools::PutReal(OS, V2);
  BinTools_SurfaceSet::WriteSurface(S->BasisSurface(),OS);
  return OS;
}


//=======================================================================
//function : operator <<(Geom_OffsetSurface)
//purpose  : 
//=======================================================================

static Standard_OStream& operator <<(Standard_OStream& OS, const Handle(Geom_OffsetSurface)& S)
{
  OS << (Standard_Byte)OFFSET;
  BinTools::PutReal(OS, S->Offset());
  BinTools_SurfaceSet::WriteSurface(S->BasisSurface(),OS);
  return OS;
}


//=======================================================================
//function : WriteSurface
//purpose  : 
//=======================================================================

void BinTools_SurfaceSet::WriteSurface(const Handle(Geom_Surface)& S,
					Standard_OStream& OS)
{
  Standard_SStream aMsg;
  Handle(Standard_Type) TheType = S->DynamicType();
  try {
    OCC_CATCH_SIGNALS
    if ( TheType ==  STANDARD_TYPE(Geom_Plane)) {
      OS << Handle(Geom_Plane)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_CylindricalSurface)) {
      OS << Handle(Geom_CylindricalSurface)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_ConicalSurface)) {
      OS << Handle(Geom_ConicalSurface)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_SphericalSurface)) {
      OS << Handle(Geom_SphericalSurface)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_ToroidalSurface)) {
      OS << Handle(Geom_ToroidalSurface)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)) {
      OS << Handle(Geom_SurfaceOfLinearExtrusion)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_SurfaceOfRevolution)) {
      OS << Handle(Geom_SurfaceOfRevolution)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_BezierSurface)) {
      OS << Handle(Geom_BezierSurface)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_BSplineSurface)) {
      OS << Handle(Geom_BSplineSurface)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_RectangularTrimmedSurface)) {
      OS << Handle(Geom_RectangularTrimmedSurface)::DownCast(S);
    }
    else if ( TheType ==  STANDARD_TYPE(Geom_OffsetSurface)) {
      OS << Handle(Geom_OffsetSurface)::DownCast(S);
    }
    else {
      aMsg <<"UNKNOWN SURFACE TYPE" <<endl;
      Standard_Failure::Raise(aMsg);
    }
  }
   catch(Standard_Failure) {
    aMsg << "EXCEPTION in BinTools_SurfaceSet::WriteSurface(..)" << endl;
    Handle(Standard_Failure) anExc = Standard_Failure::Caught();
    aMsg << anExc << endl;
    Standard_Failure::Raise(aMsg);
  }  
}

//=======================================================================
//function : Write
//purpose  : 
//=======================================================================

void  BinTools_SurfaceSet::Write(Standard_OStream& OS)const 
{

  Standard_Integer i, nbsurf = myMap.Extent();
  OS << "Surfaces "<< nbsurf << "\n";
  for (i = 1; i <= nbsurf; i++) {
    WriteSurface(Handle(Geom_Surface)::DownCast(myMap(i)),OS);
  }

}


//=======================================================================
//function : ReadPnt
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS, gp_Pnt& P)
{
  Standard_Real X=0.,Y=0.,Z=0.;
  BinTools::GetReal(IS, X);
  BinTools::GetReal(IS, Y);
  BinTools::GetReal(IS, Z);
  P.SetCoord(X,Y,Z);
  return IS;
}

//=======================================================================
//function : ReadDir
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS, gp_Dir& D)
{
  Standard_Real X=0.,Y=0.,Z=0.;
  BinTools::GetReal(IS, X);
  BinTools::GetReal(IS, Y);
  BinTools::GetReal(IS, Z);
  D.SetCoord(X,Y,Z);
  return IS;
}

//=======================================================================
//function : ReadAx3
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS, gp_Ax3& A3)
{
  gp_Pnt P(0.,0.,0.);
  gp_Dir A(1.,0.,0.),AX(1.,0.,0.),AY(1.,0.,0.);
  IS >> P >> A >> AX >> AY;
  gp_Ax3 ax3(P,A,AX);
  if (AY.DotCross(A,AX) < 0)
    ax3.YReverse();
  A3 = ax3;
  return IS;
}


//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_Plane)& S)
{
  gp_Ax3 A;
  IS >> A;
  S = new Geom_Plane(A);
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_CylindricalSurface)& S)
{
  gp_Ax3 A;
  Standard_Real R=0.;
  IS >> A;
  BinTools::GetReal(IS, R);
  S = new Geom_CylindricalSurface(A,R);
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_ConicalSurface)& S)
{
  gp_Ax3 A;
  Standard_Real R=0.,Ang=0.;
  IS >> A;
  BinTools::GetReal(IS, R);
  BinTools::GetReal(IS, Ang);
  S = new Geom_ConicalSurface(A,Ang,R);
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_SphericalSurface)& S)
{
  gp_Ax3 A;
  Standard_Real R=0.;
  IS >> A;
  BinTools::GetReal(IS, R);
  S = new Geom_SphericalSurface(A,R);
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_ToroidalSurface)& S)
{
  gp_Ax3 A;
  Standard_Real R1=0.,R2=0.;
  IS >> A;
  BinTools::GetReal(IS, R1);
  BinTools::GetReal(IS, R2);
  S = new Geom_ToroidalSurface(A,R1,R2);
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_SurfaceOfLinearExtrusion)& S)
{
  gp_Dir D(1.,0.,0.);
  Handle(Geom_Curve) C;
  IS >> D;
  BinTools_CurveSet::ReadCurve(IS,C);
  S = new Geom_SurfaceOfLinearExtrusion(C,D);
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_SurfaceOfRevolution)& S)
{
  gp_Pnt P(0.,0.,0.);
  gp_Dir D(1.,0.,0.);
  Handle(Geom_Curve) C;
  IS >> P >> D;
  BinTools_CurveSet::ReadCurve(IS, C);
  S = new Geom_SurfaceOfRevolution(C,gp_Ax1(P,D));
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_BezierSurface)& S)
{
//  cout << "BezierSurface:" <<endl;
  Standard_Boolean urational=Standard_False, vrational=Standard_False;
  BinTools::GetBool(IS, urational);
  BinTools::GetBool(IS, vrational);

//  cout << "\turational = " << urational << " vrational = " << vrational<<endl;
  Standard_Integer udegree=0, vdegree=0;
  Standard_ExtCharacter aVal='\0';
  BinTools::GetExtChar(IS, aVal);
  
  udegree = (Standard_Integer)aVal;
  BinTools::GetExtChar(IS, aVal);
  vdegree = (Standard_Integer)aVal;
//  cout << "\ttudegree  = " << udegree << ", vdegree = " << vdegree << endl;

  TColgp_Array2OfPnt poles(1,udegree+1,1,vdegree+1);
  TColStd_Array2OfReal weights(1,udegree+1,1,vdegree+1);
  
  Standard_Integer i,j;
  for (i = 1; i <= udegree+1; i++) {
    for (j = 1; j <= vdegree+1; j++) {
      IS >> poles(i,j);//Pnt
//      cout <<"Pole X = " <<poles(i,j).X()<< " Y = " <<poles(i,j).Y()<< " Z = " << poles(i,j).Z()<<endl;
      if (urational || vrational)
	BinTools::GetReal(IS, weights(i,j));
    }
  }

  if (urational || vrational)
    S = new Geom_BezierSurface(poles,weights);
  else
    S = new Geom_BezierSurface(poles);
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_BSplineSurface)& S)
{
  Standard_Boolean urational=Standard_False, vrational=Standard_False,
                   uperiodic=Standard_False, vperiodic=Standard_False;
  BinTools::GetBool(IS, urational); 
  BinTools::GetBool(IS, vrational); 
  BinTools::GetBool(IS, uperiodic);
  BinTools::GetBool(IS, vperiodic);

  Standard_Integer udegree=0, vdegree=0,nbupoles=0,nbvpoles=0,nbuknots=0,nbvknots=0;
  Standard_ExtCharacter aVal='\0';
  BinTools::GetExtChar(IS, aVal);
  udegree = (Standard_Integer)aVal;
  BinTools::GetExtChar(IS, aVal);
  vdegree = (Standard_Integer)aVal;
  BinTools::GetInteger(IS, nbupoles);
  BinTools::GetInteger(IS, nbvpoles);
  BinTools::GetInteger(IS, nbuknots);
  BinTools::GetInteger(IS, nbvknots);

  TColgp_Array2OfPnt poles(1,nbupoles,1,nbvpoles);
  TColStd_Array2OfReal weights(1,nbupoles,1,nbvpoles);
  
  Standard_Integer i,j;
  for (i = 1; i <= nbupoles; i++) {
    for (j = 1; j <= nbvpoles; j++) {
      IS >> poles(i,j);//Pnt
      if (urational || vrational)
	BinTools::GetReal(IS, weights(i,j)); 
    }
  }

  TColStd_Array1OfReal uknots(1,nbuknots);
  TColStd_Array1OfInteger umults(1,nbuknots);
  for (i = 1; i <= nbuknots; i++) {
    BinTools::GetReal(IS, uknots(i));
    BinTools::GetInteger(IS, umults(i));
  }

  TColStd_Array1OfReal vknots(1,nbvknots);
  TColStd_Array1OfInteger vmults(1,nbvknots);
  for (i = 1; i <= nbvknots; i++) {
    BinTools::GetReal(IS, vknots(i));
    BinTools::GetInteger(IS, vmults(i));
  }

  if (urational || vrational)
    S = new Geom_BSplineSurface(poles,weights,uknots,vknots,umults,vmults,
				udegree,vdegree,uperiodic,vperiodic);
  else
    S = new Geom_BSplineSurface(poles,uknots,vknots,umults,vmults,
				udegree,vdegree,uperiodic,vperiodic);
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_RectangularTrimmedSurface)& S)
{
  Standard_Real U1=0.,U2=0.,V1=0.,V2=0.;
  BinTools::GetReal(IS, U1);
  BinTools::GetReal(IS, U2);
  BinTools::GetReal(IS, V1);
  BinTools::GetReal(IS, V2);
  Handle(Geom_Surface) BS;
  BinTools_SurfaceSet::ReadSurface(IS, BS);
  S = new Geom_RectangularTrimmedSurface(BS,U1,U2,V1,V2);
  return IS;
}

//=======================================================================
//function : operator>>
//purpose  : 
//=======================================================================

static Standard_IStream& operator>>(Standard_IStream& IS,
				    Handle(Geom_OffsetSurface)& S)
{
  Standard_Real O=0.;
  BinTools::GetReal(IS, O);
  Handle(Geom_Surface) BS;
  BinTools_SurfaceSet::ReadSurface(IS, BS);
  S = new Geom_OffsetSurface(BS,O);
  return IS;
}


//=======================================================================
//function : ReadSurface
//purpose  : 
//=======================================================================

Standard_IStream& BinTools_SurfaceSet::ReadSurface(Standard_IStream& IS,
						    Handle(Geom_Surface)& S)
{
  Standard_SStream aMsg;
  try {
    OCC_CATCH_SIGNALS
    const Standard_Byte stype = (Standard_Byte) IS.get();
#ifdef DEB
//    cout << "ReadSurface: Surface type = " << (Standard_Integer)stype <<endl;
#endif
    switch (stype) {

    case PLANE :
      {
        Handle(Geom_Plane) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case CYLINDER :
      {
        Handle(Geom_CylindricalSurface) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case CONE :
      {
        Handle(Geom_ConicalSurface) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case SPHERE :
      {
        Handle(Geom_SphericalSurface) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case TORUS :
      {
        Handle(Geom_ToroidalSurface) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case LINEAREXTRUSION :
      {
        Handle(Geom_SurfaceOfLinearExtrusion) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case REVOLUTION :
      {
        Handle(Geom_SurfaceOfRevolution) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case BEZIER :
      {
        Handle(Geom_BezierSurface) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case BSPLINE :
      {
        Handle(Geom_BSplineSurface) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case RECTANGULAR :
      {
        Handle(Geom_RectangularTrimmedSurface) SS;
        IS >> SS;
        S = SS;
      }
      break;

    case OFFSET :
      {
        Handle(Geom_OffsetSurface) SS;
        IS >> SS;
        S = SS;
      }
      break;
      
    default :
      {
	S = NULL;
	aMsg << "UNKNOWN SURFACE TYPE" << endl;
	Standard_Failure::Raise(aMsg);        
      }
      break;
    }
  }
  catch(Standard_Failure) {
    S = NULL;
    aMsg << "EXCEPTION in BinTools_SurfaceSet::ReadSurface(..)" << endl;
    Handle(Standard_Failure) anExc = Standard_Failure::Caught();
    aMsg << anExc << endl;
    Standard_Failure::Raise(aMsg);
  }
  return IS;
}

//=======================================================================
//function : Read
//purpose  : 
//=======================================================================

void  BinTools_SurfaceSet::Read(Standard_IStream& IS)
{
  char buffer[255];
  IS >> buffer;
  if (IS.fail() || strcmp(buffer,"Surfaces")) {
    Standard_SStream aMsg;
    aMsg << "BinTools_SurfaceSet::Read:  Not a surface table"<<endl;
#ifdef DEB
    cout <<"SurfaceSet buffer: " << buffer << endl;
#endif
    Standard_Failure::Raise(aMsg);
    return;
  }

  Handle(Geom_Surface) S;
  Standard_Integer i, nbsurf;
  IS >> nbsurf;
  IS.get ();//remove <lf>
  for (i = 1; i <= nbsurf; i++) {
    BinTools_SurfaceSet::ReadSurface(IS,S);
    myMap.Add(S);
  }
}

