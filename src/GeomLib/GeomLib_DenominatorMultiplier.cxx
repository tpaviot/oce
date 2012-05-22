// Created on: 1997-05-13
// Created by: Stagiaire Francois DUMONT
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



#include <GeomLib_DenominatorMultiplier.ixx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <BSplSLib.hxx>
#include <math_Matrix.hxx>

//=======================================================================
//function :GeomLib_DenominatorMultiplier 
//purpose  : 
//=======================================================================

GeomLib_DenominatorMultiplier::GeomLib_DenominatorMultiplier
       (const Handle(Geom_BSplineSurface) & Surface,
        const TColStd_Array1OfReal &        KnotVector):mySurface(Surface),
                                                        myKnotFlatVector(1,KnotVector.Length())
{Standard_Integer i;
 for (i=1;i<=KnotVector.Length();i++)
   myKnotFlatVector.SetValue(i,KnotVector(i));
}

//=======================================================================
//function : value
//purpose  : give the value of a(UParameter,VParameter) 
//=======================================================================

Standard_Real GeomLib_DenominatorMultiplier::Value(const Standard_Real  UParameter,
						   const Standard_Real  VParameter)const

{Standard_Real  Dumaxv,Duminv,dDduumaxv,dDduuminv,
                Dv,Buv=0.0;
// gp_Pnt         HermPnt;
 gp_Pnt         N;
 gp_Vec         Nu,Nv;
 TColgp_Array2OfPnt        surface_poles(1,mySurface->NbUPoles(),
					 1,mySurface->NbVPoles()) ;
 TColStd_Array2OfReal      surface_weights(1,mySurface->NbUPoles(),
					   1,mySurface->NbVPoles()) ;
 TColStd_Array1OfReal      surface_u_knots(1,mySurface->NbUKnots()) ;
 TColStd_Array1OfInteger   surface_u_mults(1,mySurface->NbUKnots()) ;
 
 TColStd_Array1OfReal      surface_v_knots(1,mySurface->NbVKnots()) ;
 TColStd_Array1OfInteger   surface_v_mults(1,mySurface->NbVKnots()) ;
 Standard_Integer          udegree,vdegree;

 mySurface->UKnots(surface_u_knots) ;
 mySurface->UMultiplicities(surface_u_mults) ;
 mySurface->Poles(surface_poles) ;
 mySurface->Weights(surface_weights) ;
 mySurface->VKnots(surface_v_knots) ;
 mySurface->VMultiplicities(surface_v_mults) ;
 udegree=mySurface->UDegree();
 vdegree=mySurface->VDegree();

 BSplSLib::HomogeneousD1(mySurface->UKnot(mySurface->LastUKnotIndex()),VParameter,
			 0,0,
			 surface_poles,
			 surface_weights,
			 surface_u_knots,surface_v_knots,
			 surface_u_mults,surface_v_mults,
			 udegree,vdegree,
			 mySurface->IsURational(),mySurface->IsVRational(),
			 mySurface->IsUPeriodic(),mySurface->IsVPeriodic(),
			 N,Nu,Nv,
			 Dumaxv,
			 dDduumaxv,
			 Dv);
 BSplSLib::HomogeneousD1(mySurface->UKnot(1),VParameter,
			 0,0,
			 surface_poles,
			 surface_weights,
			 surface_u_knots,surface_v_knots,
			 surface_u_mults,surface_v_mults,
			 udegree,vdegree,
			 mySurface->IsURational(),mySurface->IsVRational(),
			 mySurface->IsUPeriodic(),mySurface->IsVPeriodic(),
			 N,Nu,Nv,
			 Duminv,
			 dDduuminv,
			 Dv);

 math_Matrix             BSplineBasisDeriv(1,2,1,4,0.0);
 Standard_Real           B1prim0,Bprelastprim1,
                         lambda=(mySurface->Weight(1,1)/mySurface->Weight(mySurface->NbUPoles(),1));
 Standard_Integer        index,i;

 BSplCLib::EvalBsplineBasis(1,
			    1,
			    4,
			    myKnotFlatVector,
			    0.0,
			    index,
			    BSplineBasisDeriv);
 B1prim0=BSplineBasisDeriv(2,2);
 
 BSplCLib::EvalBsplineBasis(1,
			    1,
			    4,
			    myKnotFlatVector,
			    1.0,
			    index,
			    BSplineBasisDeriv);
 Bprelastprim1=BSplineBasisDeriv(2,3);

 math_Matrix             BSplineBasisValue(1,1,1,4,0.0);
 BSplCLib::EvalBsplineBasis(1,
			    0,
			    4,
			    myKnotFlatVector,
			    UParameter,
			    index,
			    BSplineBasisValue);

 TColStd_Array1OfReal       value(0,5);
 TColStd_Array1OfReal       Polesenv(0,5);                          //poles of a(u,v)

 for (i=0;i<=5;i++)
   Polesenv(i)=0.0;
 Polesenv(0)=Duminv;
 Polesenv(1)=Duminv-dDduuminv/B1prim0;
 Polesenv(4)=lambda*lambda*(Dumaxv-dDduumaxv/Bprelastprim1);
 Polesenv(5)=lambda*lambda*Dumaxv;

 if (myKnotFlatVector.Length()==8){
   value(0)=BSplineBasisValue(1,1);                                //values of the basic functions
   value(1)=BSplineBasisValue(1,2);
   value(2)=0.0;
   value(3)=0.0;
   value(4)=BSplineBasisValue(1,3);
   value(5)=BSplineBasisValue(1,4);
 }
 if (myKnotFlatVector.Length()==9){
   if (index==1){
     value(0)=BSplineBasisValue(1,1);
     value(1)=BSplineBasisValue(1,2);
     value(2)=BSplineBasisValue(1,3);
     value(3)=0.0;
     value(4)=BSplineBasisValue(1,4);
     value(5)=0.0;
   }
   else{
     value(0)=0.0;
     value(1)=BSplineBasisValue(1,1);
     value(2)=BSplineBasisValue(1,2);
     value(3)=0.0;
     value(4)=BSplineBasisValue(1,3);
     value(5)=BSplineBasisValue(1,4);
   }
   Polesenv(2)=(0.5*(Polesenv(0)+Polesenv(5)));
 }
 if (myKnotFlatVector.Length()==10){
   if (index==1){
     value(0)=BSplineBasisValue(1,1);
     value(1)=BSplineBasisValue(1,2);
     value(2)=BSplineBasisValue(1,3);
     value(3)=BSplineBasisValue(1,4);
     value(4)=0.0;
     value(5)=0.0;
   }
   if (index==2){
     value(0)=0.0;
     value(1)=BSplineBasisValue(1,1);
     value(2)=BSplineBasisValue(1,2);
     value(3)=BSplineBasisValue(1,3);
     value(4)=BSplineBasisValue(1,4);
     value(5)=0.0;
   }
   if (index==3){
     value(0)=0.0;
     value(1)=0.0;
     value(2)=BSplineBasisValue(1,1);
     value(3)=BSplineBasisValue(1,2);
     value(4)=BSplineBasisValue(1,3);
     value(5)=BSplineBasisValue(1,4);
   }
   Polesenv(2)=(0.5*(Polesenv(0)+Polesenv(5)));
   Polesenv(3)=Polesenv(2);
 }
 for (i=0;i<=5;i++)
   Buv+=Polesenv(i)*value(i);
 return Buv;
}




