// Created on: 1993-06-23
// Created by: Jean Yves LEBEY
// Copyright (c) 1993-1999 Matra Datavision
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




#include <TopOpeBRepDS_Curve.ixx>
#include <TopOpeBRepDS_SurfaceCurveInterference.hxx>
#include <TopOpeBRepDS_Dumper.hxx>
#include <Precision.hxx>


//=======================================================================
//function : TopOpeBRepDS_Curve
//purpose  : 
//=======================================================================

TopOpeBRepDS_Curve::TopOpeBRepDS_Curve() :
myFirst(0.0), myLast(0.0),
myRangeDefined(Standard_False),
myTolerance(Precision::Confusion()),
myIsWalk(Standard_False),
myKeep(Standard_True),
myMother(0),
myDSIndex(0)
{
}

//=======================================================================
//function : TopOpeBRepDS_Curve
//purpose  : 
//=======================================================================

TopOpeBRepDS_Curve::TopOpeBRepDS_Curve
(const Handle(Geom_Curve)& C, 
 const Standard_Real T,
 const Standard_Boolean IsWalk) :
 myFirst(0.0), myLast(0.0),
 myRangeDefined(Standard_False),
 myKeep(Standard_True),
 myMother(0),
 myDSIndex(0)
{
  DefineCurve(C,T,IsWalk);
}

//=======================================================================
//function : DefineCurve
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::DefineCurve
(const Handle(Geom_Curve)& C,
 const Standard_Real T,
 const Standard_Boolean IsWalk)
{
  myCurve = C;
  myTolerance = T;
  myIsWalk = IsWalk;
}

//=======================================================================
//function : Tolerance
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::Tolerance(const Standard_Real T)
{
  myTolerance = T;
}

//=======================================================================
//function : SetSCI
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::SetSCI(const Handle(TopOpeBRepDS_Interference)& SCI1,
				const Handle(TopOpeBRepDS_Interference)& SCI2)
{
  mySCI1 = SCI1;
  mySCI2 = SCI2;
}

//=======================================================================
//function : GetSCI
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::GetSCI(Handle(TopOpeBRepDS_Interference)& SCI1,
			        Handle(TopOpeBRepDS_Interference)& SCI2) const
{
  SCI1 = mySCI1;  
  SCI2 = mySCI2;
}

//=======================================================================
//function : GetSCI1
//purpose  : 
//=======================================================================

const Handle(TopOpeBRepDS_Interference)& TopOpeBRepDS_Curve::GetSCI1() const
{
  return mySCI1;
}

//=======================================================================
//function : GetSCI2
//purpose  : 
//=======================================================================

const Handle(TopOpeBRepDS_Interference)& TopOpeBRepDS_Curve::GetSCI2() const
{
  return mySCI2;
}

//=======================================================================
//function : SetShapes
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::SetShapes(const TopoDS_Shape& S1,
				   const TopoDS_Shape& S2)
{
  myS1 = S1; 
  myS2 = S2;
}

//=======================================================================
//function : GetShapes
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::GetShapes(TopoDS_Shape& S1,
				   TopoDS_Shape& S2) const
{
  S1 = myS1; 
  S2 = myS2;
}

//=======================================================================
//function : Shape1
//purpose  : 
//=======================================================================

const TopoDS_Shape& TopOpeBRepDS_Curve::Shape1() const
{
  return myS1;
}

//=======================================================================
//function : ChangeShape1
//purpose  : 
//=======================================================================

TopoDS_Shape& TopOpeBRepDS_Curve::ChangeShape1()
{
  return myS1;
}

//=======================================================================
//function : Shape2
//purpose  : 
//=======================================================================

const TopoDS_Shape& TopOpeBRepDS_Curve::Shape2() const
{
  return myS2;
}

//=======================================================================
//function : ChangeShape2
//purpose  : 
//=======================================================================

TopoDS_Shape& TopOpeBRepDS_Curve::ChangeShape2()
{
  return myS2;
}

//=======================================================================
//function : ChangeCurve
//purpose  : 
//=======================================================================

Handle(Geom_Curve)& TopOpeBRepDS_Curve::ChangeCurve()
{
  return myCurve;
}

//=======================================================================
//function : Curve
//purpose  : 
//=======================================================================

const Handle(Geom_Curve)&  TopOpeBRepDS_Curve::Curve()const 
{
  return myCurve;
}

//=======================================================================
//function : SetRange
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::SetRange(const Standard_Real First,
				  const Standard_Real Last)
{
  myFirst = First;
  myLast = Last;
  myRangeDefined = Standard_True;
}


//=======================================================================
//function : Range
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRepDS_Curve::Range(Standard_Real& First,
					   Standard_Real& Last) const
{
  if (myRangeDefined) {
    First = myFirst;
    Last = myLast;
  }
  return myRangeDefined;
}
    

//=======================================================================
//function : Tolerance
//purpose  : 
//=======================================================================

Standard_Real  TopOpeBRepDS_Curve::Tolerance()const 
{
  return myTolerance;
}

//=======================================================================
//function : Curve
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::Curve(const Handle(Geom_Curve)& C3D,
			       const Standard_Real Tol)
{
  myCurve = C3D;
  myTolerance = Tol;
}


//=======================================================================
//function : Curve1
//purpose  : 
//=======================================================================

const Handle(Geom2d_Curve)&  TopOpeBRepDS_Curve::Curve1()const 
{
  if ( ! mySCI1.IsNull() ) {
    return 
      (*((Handle(TopOpeBRepDS_SurfaceCurveInterference)*)&mySCI1))->PCurve();
  }
  else {
    static Handle(Geom2d_Curve) STALOC_Geom2dCurveNull1;
    return STALOC_Geom2dCurveNull1;
  }
}

//=======================================================================
//function : Curve1
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::Curve1(const Handle(Geom2d_Curve)& PC1)
{
  if ( ! mySCI1.IsNull() ) {
    (*((Handle(TopOpeBRepDS_SurfaceCurveInterference)*)&mySCI1))->PCurve(PC1);
  }
}


//=======================================================================
//function : Curve2
//purpose  : 
//=======================================================================

const Handle(Geom2d_Curve)&  TopOpeBRepDS_Curve::Curve2()const 
{
  if ( ! mySCI2.IsNull() ) {
    return 
      (*((Handle(TopOpeBRepDS_SurfaceCurveInterference)*)&mySCI2))->PCurve();
  }
  else {
    static Handle(Geom2d_Curve) STALOC_Geom2dCurveNull2;
    return STALOC_Geom2dCurveNull2;
  }
}

//=======================================================================
//function : Curve2
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::Curve2(const Handle(Geom2d_Curve)& PC2)
{
  if ( ! mySCI2.IsNull() ) {
    (*((Handle(TopOpeBRepDS_SurfaceCurveInterference)*)&mySCI2))->PCurve(PC2);
  }
}


//=======================================================================
//function : IsWalk
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRepDS_Curve::IsWalk() const
{
  return myIsWalk;
}

//=======================================================================
//function : ChangeIsWalk
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::ChangeIsWalk(const Standard_Boolean B)
{
  myIsWalk = B;
}


//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

Standard_OStream& TopOpeBRepDS_Curve::Dump(Standard_OStream& OS,
					   const Standard_Integer index,
					   const Standard_Boolean compact)const
{
#ifdef DEB
  OS<<"Curve : "; if (index != 0) OS<<index<<" ";
  if (!Curve().IsNull()) {
    TopOpeBRepDS_Dumper::Print(Curve(),OS,compact);
    Standard_Real f,l;
    if (Range(f,l)) OS<<"has range of "<<f<<","<<l<<endl;
    else            OS<<"has no range defined"<<endl;
  }
  else OS<<" is null";
  OS<<endl;
  
#define DSCI(tut) (*((Handle(TopOpeBRepDS_SurfaceCurveInterference)*)&(tut)))

  Handle(TopOpeBRepDS_Interference) I1,I2; 
  GetSCI(I1,I2);

  OS<<"SCI1 : ";
  if (!I1.IsNull()) DSCI(I1)->DumpPCurve(OS,compact);
  else OS<<" is null";
  OS<<endl;
  
  OS<<"SCI2 : ";
  if (!I2.IsNull()) DSCI(I2)->DumpPCurve(OS,compact);
  else OS<<" is null";
  OS<<endl;
#endif

  return OS;
}


//=======================================================================
//function : Keep
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRepDS_Curve::Keep() const
{
  return myKeep;
}


//=======================================================================
//function : ChangeKeep
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::ChangeKeep(const Standard_Boolean b)
{
  myKeep = b;
}


//=======================================================================
//function : Mother
//purpose  : 
//=======================================================================

Standard_Integer TopOpeBRepDS_Curve::Mother() const
{
  return myMother;
}


//=======================================================================
//function : ChangeMother
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::ChangeMother(const Standard_Integer b)
{
  myMother = b;
}

//=======================================================================
//function : DSIndex
//purpose  : 
//=======================================================================

Standard_Integer TopOpeBRepDS_Curve::DSIndex() const
{
  return myDSIndex;
}


//=======================================================================
//function : ChangeDSIndex
//purpose  : 
//=======================================================================

void TopOpeBRepDS_Curve::ChangeDSIndex(const Standard_Integer b)
{
  myDSIndex = b;
}
