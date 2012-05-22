// Created on: 1997-12-05
// Created by: Philippe MANGIN
// Copyright (c) 1997-1999 Matra Datavision
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



#include <GeomFill_CurveAndTrihedron.ixx>
#include <GeomLib.hxx>
#include <gp_Circ.hxx>
#include <TColStd_SequenceOfReal.hxx> 
#include <Precision.hxx>

//==================================================================
//Function: Create
//Purpose :
//==================================================================

GeomFill_CurveAndTrihedron::GeomFill_CurveAndTrihedron(
       const Handle(GeomFill_TrihedronLaw)& Trihedron )
{
  myLaw = Trihedron;
  myCurve.Nullify();
  Trans.SetIdentity();
  WithTrans = Standard_False;
}

//==================================================================
//Function: Copy
//Purpose :
//==================================================================
Handle(GeomFill_LocationLaw) GeomFill_CurveAndTrihedron::Copy() const
{
  Handle(GeomFill_TrihedronLaw) law;
  law = myLaw->Copy();
  Handle(GeomFill_CurveAndTrihedron) copy = 
    new (GeomFill_CurveAndTrihedron) (myLaw->Copy());
  copy->SetCurve(myCurve);
  copy->SetTrsf(Trans);
  return copy;
}

//==================================================================
//Function: SetCurve
//Purpose :
//==================================================================
 void GeomFill_CurveAndTrihedron::SetCurve(const Handle(Adaptor3d_HCurve)& C) 
{
  myCurve = C;
  myTrimmed = C;
  myLaw->SetCurve(C); 
}

 const Handle(Adaptor3d_HCurve)& GeomFill_CurveAndTrihedron::GetCurve() const
{
  return myCurve;
}


//==================================================================
//Function: SetTrsf
//Purpose :
//==================================================================
 void GeomFill_CurveAndTrihedron::SetTrsf(const gp_Mat& Transfo) 
{
  Trans = Transfo;
  gp_Mat Aux;
  Aux.SetIdentity();
  Aux -= Trans;
  WithTrans = Standard_False; // Au cas ou Trans = I
  for (Standard_Integer ii=1; ii<=3 && !WithTrans ; ii++)
    for (Standard_Integer jj=1; jj<=3 && !WithTrans; jj++)
      if (Abs(Aux.Value(ii, jj)) > 1.e-14)  WithTrans = Standard_True;
}

//==================================================================
//Function: D0
//Purpose :
//==================================================================
 Standard_Boolean GeomFill_CurveAndTrihedron::D0(const Standard_Real Param,
						 gp_Mat& M,
						 gp_Vec& V) 
{
  Standard_Boolean Ok;
  myTrimmed->D0(Param, Point);
  V.SetXYZ(Point.XYZ());
   
  Ok = myLaw->D0(Param, V1, V2, V3);
  M.SetCols(V2.XYZ(), V3.XYZ(), V1.XYZ());

  if (WithTrans) {
    M *= Trans;
  }
  return Ok;
}

//==================================================================
//Function: D0
//Purpose :
//==================================================================
 Standard_Boolean GeomFill_CurveAndTrihedron::D0(const Standard_Real Param,
						 gp_Mat& M,
						 gp_Vec& V,
						 TColgp_Array1OfPnt2d&) 
{
  Standard_Boolean Ok;
  myTrimmed->D0(Param, Point);
  V.SetXYZ(Point.XYZ());
   
  Ok = myLaw->D0(Param, V1, V2, V3);
  M.SetCols(V2.XYZ(), V3.XYZ(), V1.XYZ());

  if (WithTrans) {
    M *= Trans;
  }
  return Ok;
}

//==================================================================
//Function:
//Purpose :
//==================================================================
 Standard_Boolean GeomFill_CurveAndTrihedron::D1(const Standard_Real Param,
						 gp_Mat& M,
						 gp_Vec& V,
						 gp_Mat& DM,
						 gp_Vec& DV,
						 TColgp_Array1OfPnt2d& ,
						 TColgp_Array1OfVec2d& ) 
{
  Standard_Boolean Ok;
  myTrimmed->D1(Param, Point, DV);
  V.SetXYZ(Point.XYZ());
   
  gp_Vec DV1, DV2, DV3;
  Ok = myLaw->D1(Param, 
		 V1, DV1,
		 V2, DV2,
                 V3, DV3);
  M.SetCols( V2.XYZ(),  V3.XYZ(),  V1.XYZ());
  DM.SetCols(DV2.XYZ(), DV3.XYZ(), DV1.XYZ());

  if (WithTrans) {
    M *= Trans;
    DM *= Trans;
  }

  return Ok;
}

//==================================================================
//Function:
//Purpose :
//==================================================================
 Standard_Boolean GeomFill_CurveAndTrihedron::D2(const Standard_Real Param,
						 gp_Mat& M,
						 gp_Vec& V,
						 gp_Mat& DM,
						 gp_Vec& DV, 
						 gp_Mat& D2M,
						 gp_Vec& D2V,
						 TColgp_Array1OfPnt2d&,
						 TColgp_Array1OfVec2d&,
						 TColgp_Array1OfVec2d&) 
{
 Standard_Boolean Ok;
 myTrimmed->D2(Param, Point, DV, D2V);
 V.SetXYZ(Point.XYZ());
   
 gp_Vec DV1, DV2, DV3;
 gp_Vec D2V1, D2V2, D2V3;
 Ok = myLaw->D2(Param, 
                V1, DV1, D2V1,
		V2,DV2,  D2V2,
		V3, DV3, D2V3);

 M.  SetCols(V2.XYZ(),   V3.XYZ(),   V1.XYZ());
 DM. SetCols(DV2.XYZ(),  DV3.XYZ(),  DV1.XYZ());
 D2M.SetCols(D2V2.XYZ(), D2V3.XYZ(), D2V1.XYZ());

  if (WithTrans) {
    M *= Trans;
    DM *= Trans;
    D2M *= Trans;
  }

 return Ok;
}

//==================================================================
//Function:
//Purpose :
//==================================================================
 Standard_Integer GeomFill_CurveAndTrihedron::NbIntervals(const GeomAbs_Shape S) const
{
  Standard_Integer Nb_Sec, Nb_Law;
  Nb_Sec  =  myTrimmed->NbIntervals(S);
  Nb_Law  =  myLaw->NbIntervals(S);

  if  (Nb_Sec==1) {
    return Nb_Law;
  }
  else if (Nb_Law==1) {
    return Nb_Sec;
  }

  TColStd_Array1OfReal IntC(1, Nb_Sec+1);
  TColStd_Array1OfReal IntL(1, Nb_Law+1);
  TColStd_SequenceOfReal    Inter;
  myTrimmed->Intervals(IntC, S);
  myLaw->Intervals(IntL, S);

  GeomLib::FuseIntervals( IntC, IntL, Inter, Precision::PConfusion()*0.99);
  return Inter.Length()-1;  
}
//==================================================================
//Function:
//Purpose :
//==================================================================
 void GeomFill_CurveAndTrihedron::Intervals(TColStd_Array1OfReal& T,
					    const GeomAbs_Shape S) const
{
  Standard_Integer Nb_Sec, Nb_Law;
  Nb_Sec  =  myTrimmed->NbIntervals(S);
  Nb_Law  =  myLaw->NbIntervals(S);

  if  (Nb_Sec==1) {
    myLaw->Intervals(T, S);
    return;
  }
  else if (Nb_Law==1) {
    myTrimmed->Intervals(T, S);
    return;
  }

  TColStd_Array1OfReal IntC(1, Nb_Sec+1);
  TColStd_Array1OfReal IntL(1, Nb_Law+1);
  TColStd_SequenceOfReal    Inter;
  myTrimmed->Intervals(IntC, S);
  myLaw->Intervals(IntL, S);

  GeomLib::FuseIntervals(IntC, IntL, Inter, Precision::PConfusion()*0.99);
  for (Standard_Integer ii=1; ii<=Inter.Length(); ii++)
    T(ii) = Inter(ii);
}
//==================================================================
//Function:
//Purpose :
//==================================================================
 void GeomFill_CurveAndTrihedron::SetInterval(const Standard_Real First,
					      const Standard_Real Last) 
{
  myLaw->SetInterval( First, Last);
  myTrimmed = myCurve->Trim( First, Last, 0);
}
//==================================================================
//Function: GetInterval
//Purpose :
//==================================================================
 void GeomFill_CurveAndTrihedron::GetInterval(Standard_Real& First,
					      Standard_Real& Last) const
{
  First =  myTrimmed->FirstParameter();
  Last =   myTrimmed->LastParameter();
}

//==================================================================
//Function: GetDomain
//Purpose :
//==================================================================
 void GeomFill_CurveAndTrihedron::GetDomain(Standard_Real& First,
					    Standard_Real& Last) const
{
  First =  myCurve->FirstParameter();
  Last =   myCurve->LastParameter();
}

//==================================================================
//Function:
//Purpose : GetMaximalNorm
//          On suppose les triedre normee => return 1
//==================================================================
 Standard_Real GeomFill_CurveAndTrihedron::GetMaximalNorm() 
{
  return 1.;
}
//==================================================================
//Function:
//Purpose :
//==================================================================
 void GeomFill_CurveAndTrihedron::GetAverageLaw(gp_Mat& AM,
						gp_Vec& AV) 
{
  Standard_Integer ii;
  Standard_Real U, delta;
  gp_Vec V;
  
  myLaw->GetAverageLaw(V1, V2, V3);
  AM.SetCols(V1.XYZ(), V2.XYZ(), V3.XYZ());

  AV.SetCoord(0., 0., 0.);
  delta = (myTrimmed->LastParameter() - myTrimmed->FirstParameter())/10;
  U=  myTrimmed->FirstParameter(); 
  for (ii=0; ii<=10; ii++, U+=delta) {
    V.SetXYZ( myTrimmed->Value(U).XYZ() );
    AV += V;
  }
  AV /= 11;   
}


//==================================================================
//Function : IsTranslation
//Purpose : 
//==================================================================
 Standard_Boolean GeomFill_CurveAndTrihedron::IsTranslation(Standard_Real& Error) const
{
  GeomAbs_CurveType Type;
  Error = 0;
  Type = myCurve->GetType();
  if (Type == GeomAbs_Line) {
    return (myLaw->IsConstant() || myLaw->IsOnlyBy3dCurve());
  }
  return Standard_False;
}


//==================================================================
//Function : IsRotation
//Purpose : 
//==================================================================
 Standard_Boolean GeomFill_CurveAndTrihedron::IsRotation(Standard_Real& Error)  const
{
  GeomAbs_CurveType Type;
  Error = 0;
  Type = myCurve->GetType();
  if (Type == GeomAbs_Circle) {
    return myLaw->IsOnlyBy3dCurve();
  }
  return Standard_False;  
}

//==================================================================
//Function : Rotation
//Purpose : 
//==================================================================
 void GeomFill_CurveAndTrihedron::Rotation(gp_Pnt& Centre)  const
{
//  GeomAbs_CurveType Type;
//  Type = myCurve->GetType();
  Centre =  myCurve->Circle().Location();
}
