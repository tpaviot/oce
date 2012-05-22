// Created on: 1992-06-10
// Created by: Laurent BUCHARD
// Copyright (c) 1992-1999 Matra Datavision
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




#include <IntImpParGen.ixx>
#include <IntRes2d_Domain.hxx>
#include <IntRes2d_Position.hxx>
#include <IntRes2d_Transition.hxx>
#include <gp_Vec2d.hxx>
#include <gp_Pnt2d.hxx>




#include <IntImpParGen_Tool.hxx>
#include <gp.hxx>


#define TOLERANCE_ANGULAIRE     0.00000001
#define DERIVEE_PREMIERE_NULLE  0.000000000001
//----------------------------------------------------------------------
Standard_Real IntImpParGen::NormalizeOnDomain(Standard_Real& Param,
					      const IntRes2d_Domain& TheDomain) {
  Standard_Real modParam = Param;
  if(TheDomain.IsClosed()) {
    Standard_Real Periode,t;
    TheDomain.EquivalentParameters(t,Periode);
    Periode-=t;
    while(   modParam<TheDomain.FirstParameter()
	  && modParam+Periode < TheDomain.LastParameter()) {
      modParam+=Periode;
    }
    while(   modParam>TheDomain.LastParameter()
	  && modParam-Periode > TheDomain.FirstParameter()) {
      modParam-=Periode;
    }
  }  
  return(modParam);
}
//----------------------------------------------------------------------
void IntImpParGen::DeterminePosition(IntRes2d_Position& Pos1,
				     const IntRes2d_Domain& TheDomain,
				     const gp_Pnt2d& Pnt1,
				     const Standard_Real Param1) {
  
  Pos1=IntRes2d_Middle;

  if(TheDomain.HasFirstPoint()) { 
    if(Pnt1.Distance(TheDomain.FirstPoint()) 
       <= TheDomain.FirstTolerance()) {
      Pos1=IntRes2d_Head; 	
    }
  }
   
  if(TheDomain.HasLastPoint()) {
    if(Pnt1.Distance(TheDomain.LastPoint()) 
       <= TheDomain.LastTolerance()) {
      if(Pos1==IntRes2d_Head) {
	if(Abs(Param1-TheDomain.LastParameter())
	   < Abs(Param1-TheDomain.FirstParameter()))
	  Pos1=IntRes2d_End; 	
      }
      else {
	Pos1=IntRes2d_End; 
      }
    } 
  }
}   
//----------------------------------------------------------------------
void IntImpParGen::DetermineTransition(const IntRes2d_Position    Pos1,
				       gp_Vec2d&                  Tan1,
				       const gp_Vec2d&            Norm1,
				       IntRes2d_Transition&       T1,
				       const IntRes2d_Position    Pos2,
				       gp_Vec2d&                  Tan2,
				       const gp_Vec2d&            Norm2,
				       IntRes2d_Transition&       T2,
				       const Standard_Real        ) {
  
  Standard_Boolean courbure1=Standard_True;
  Standard_Boolean courbure2=Standard_True;
  Standard_Boolean decide=Standard_True;
      
  T1.SetPosition(Pos1);
  T2.SetPosition(Pos2);


  if (Tan1.SquareMagnitude()<=DERIVEE_PREMIERE_NULLE) {
    Tan1=Norm1;
    courbure1=Standard_False;
    if (Tan1.SquareMagnitude()<=DERIVEE_PREMIERE_NULLE) {    // transition undecided
      decide=Standard_False;
    }
  }
  
  if (Tan2.SquareMagnitude()<=DERIVEE_PREMIERE_NULLE) {
    Tan2=Norm2;
    courbure2=Standard_False;
    if (Tan2.SquareMagnitude()<=DERIVEE_PREMIERE_NULLE) {    // transition undecided
      decide=Standard_False;
    }
  }
  
  if (!decide) {
    T1.SetValue(Pos1);
    T2.SetValue(Pos2);
  }
  else {
    Standard_Real sgn=Tan1.Crossed(Tan2);
    Standard_Real norm=Tan1.Magnitude()*Tan2.Magnitude();

    if (Abs(sgn)<=TOLERANCE_ANGULAIRE*norm) {   // Transition TOUCH #########
      Standard_Boolean opos=(Tan1.Dot(Tan2))<0;
      if (!(courbure1||courbure2)) {
	T1.SetValue(Standard_True,Pos1,IntRes2d_Unknown,opos);
	T2.SetValue(Standard_True,Pos2,IntRes2d_Unknown,opos);
      }
      else {
	gp_Vec2d Norm;
	Tan1.Normalized();
	Norm.SetCoord(-Tan1.Y(),Tan1.X());
	Standard_Real Val1,Val2;
	if (!courbure1) {
	  Val1=0.0;
	}
	else {
	  Val1=Norm.Dot(Norm1);
	}
	if (!courbure2) {
	  Val2=0.0;
	}
	else {
	  Val2=Norm.Dot(Norm2);
	}
	
	if (Abs(Val1-Val2) <= TOLERANCE_ANGULAIRE) {
	  T1.SetValue(Standard_True,Pos1,IntRes2d_Unknown,opos);
	  T2.SetValue(Standard_True,Pos2,IntRes2d_Unknown,opos);
	}
	else if (Val2 > Val1) {
	  T2.SetValue(Standard_True,Pos2,IntRes2d_Inside,opos);
	  if (opos) {
	    T1.SetValue(Standard_True,Pos1,IntRes2d_Inside,opos);
	  }
	  else {
	    T1.SetValue(Standard_True,Pos1,IntRes2d_Outside,opos);
	  }
	}
	else {         // Val1 > Val2
	  T2.SetValue(Standard_True,Pos2,IntRes2d_Outside,opos);
	  if (opos) {
	    T1.SetValue(Standard_True,Pos1,IntRes2d_Outside,opos);
	  }
	  else {
	    T1.SetValue(Standard_True,Pos1,IntRes2d_Inside,opos);
	  }
	}
      }
    }
    else if (sgn<0) {
      T1.SetValue(Standard_False,Pos1,IntRes2d_In);
      T2.SetValue(Standard_False,Pos2,IntRes2d_Out);
    }
    else {     // sgn>0
      T1.SetValue(Standard_False,Pos1,IntRes2d_Out);
      T2.SetValue(Standard_False,Pos2,IntRes2d_In);
    }
  }
}

//----------------------------------------------------------------------
Standard_Boolean  IntImpParGen::DetermineTransition(const IntRes2d_Position    Pos1,
						    gp_Vec2d&                  Tan1,
						    IntRes2d_Transition&       T1,
						    const IntRes2d_Position    Pos2,
						    gp_Vec2d&                  Tan2,
						    IntRes2d_Transition&       T2,
						    const Standard_Real        ) {

  T1.SetPosition(Pos1);
  T2.SetPosition(Pos2);

  Standard_Real Tan1Magnitude = Tan1.Magnitude();
  if (Tan1Magnitude<=DERIVEE_PREMIERE_NULLE) {
    return(Standard_False);
  }

  Standard_Real Tan2Magnitude = Tan2.Magnitude();  
  if (Tan2Magnitude<=DERIVEE_PREMIERE_NULLE) {
    return(Standard_False);
  }

  Standard_Real sgn=Tan1.Crossed(Tan2);
  Standard_Real norm=Tan1Magnitude*Tan2Magnitude;
  
  if (Abs(sgn)<=TOLERANCE_ANGULAIRE*norm) {   // Transition TOUCH #########
    return(Standard_False);
  }
  else if (sgn<0) {
    T1.SetValue(Standard_False,Pos1,IntRes2d_In);
    T2.SetValue(Standard_False,Pos2,IntRes2d_Out);
  }
  else {     // sgn>0
    T1.SetValue(Standard_False,Pos1,IntRes2d_Out);
    T2.SetValue(Standard_False,Pos2,IntRes2d_In);
  }
  return(Standard_True);
}









