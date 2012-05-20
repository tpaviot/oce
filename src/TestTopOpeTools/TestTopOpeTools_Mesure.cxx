// Created on: 1997-03-17
// Created by: Prestataire Mary FABIEN
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


#include <TestTopOpeTools_Mesure.ixx>
#include <TestTopOpeTools_Mesure.hxx>

#include <TColStd_HArray1OfInteger.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <Handle_Geom_BSplineCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <gp_Pnt.hxx>

//=======================================================================
//function : TestTopOpeTools_Mesure
//purpose  : 
//=======================================================================

TestTopOpeTools_Mesure::TestTopOpeTools_Mesure()
:myPnts(new TColgp_HArray1OfPnt(1,100)),myNPnts(0){}

//=======================================================================
//function : TestTopOpeTools_Mesure
//purpose  : 
//=======================================================================

TestTopOpeTools_Mesure::TestTopOpeTools_Mesure
(const TCollection_AsciiString& Name)
: myName(Name),myPnts(new TColgp_HArray1OfPnt(1,100)),myNPnts(0)
{
  myNPnts = 1;
  myPnts->SetValue(myNPnts,gp_Pnt(0.,0.,0.));
}

//=======================================================================
//function : TestTopOpeTools_Mesure
//purpose  : 
//=======================================================================

TestTopOpeTools_Mesure::TestTopOpeTools_Mesure
(const Handle(TColgp_HArray1OfPnt)& P)
: myName(""),myPnts(new TColgp_HArray1OfPnt(1,100)),myNPnts(0)
{
  myPnts = P;
  myNPnts = myPnts->Length();
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void TestTopOpeTools_Mesure::Add(const Standard_Integer n,
				 const Standard_Real t)
{
  if (myPnts.IsNull()) return;
  if (myNPnts+1 > myPnts->Upper()) {
    Handle(TColgp_HArray1OfPnt) Ploc = new TColgp_HArray1OfPnt(1,10*myNPnts);
    for(Standard_Integer i = 1;i <= myNPnts;i++)
      Ploc->SetValue(i,myPnts->Value(i));
    myPnts->ChangeArray1() = Ploc->Array1();
  }
  myNPnts++;
  myPnts->SetValue(myNPnts,gp_Pnt((Standard_Real)n,t,0.));
}

//=======================================================================
//function : Name
//purpose  : 
//=======================================================================

const TCollection_AsciiString& TestTopOpeTools_Mesure::Name() const 
{
  return myName; 
}

//=======================================================================
//function : Name
//purpose  : 
//=======================================================================

void TestTopOpeTools_Mesure::SetName(const TCollection_AsciiString& Name) 
{
  myName = Name; 
}

//=======================================================================
//function : Pnts
//purpose  : 
//=======================================================================

const TColgp_Array1OfPnt& TestTopOpeTools_Mesure::Pnts() const
{
  return myPnts->Array1();
}

//=======================================================================
//function : Pnt
//purpose  : 
//=======================================================================

const gp_Pnt& TestTopOpeTools_Mesure::Pnt(const Standard_Integer I) const
{
  return myPnts->Value(I);
}

//=======================================================================
//function : NPnts
//purpose  : 
//=======================================================================

Standard_Integer TestTopOpeTools_Mesure::NPnts() const
{
  return myNPnts; 
}

//=======================================================================
//function : Clear
//purpose : 
//=======================================================================

void TestTopOpeTools_Mesure::Clear()
{
  myNPnts = 0;
}
