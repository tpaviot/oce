// Created on: 1997-04-17
// Created by: Christophe MARION
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


#ifndef No_Exception
#define No_Exception
#endif
#include <HLRBRep_EdgeIList.ixx>

#include <TopCnx_EdgeFaceTransition.hxx>
#include <HLRAlgo_ListIteratorOfInterferenceList.hxx>

//=======================================================================
//function : AddInterference
//purpose  : insert an interference in a sorted list
//=======================================================================

void  HLRBRep_EdgeIList::
AddInterference(HLRAlgo_InterferenceList& IL,
		const HLRAlgo_Interference& I,
		const HLRBRep_EdgeInterferenceTool& T)
{
  HLRAlgo_ListIteratorOfInterferenceList It(IL);
  Standard_Real p = T.ParameterOfInterference(I);
  while (It.More()) {
    if (p < T.ParameterOfInterference(It.Value())) {
      IL.InsertBefore(I,It);
      return;
    }
    It.Next();
  }
  IL.Append(I);
}

//=======================================================================
//function : ProcessComplex
//purpose  : 
//=======================================================================
void  HLRBRep_EdgeIList::
ProcessComplex(HLRAlgo_InterferenceList& IL,
	       const HLRBRep_EdgeInterferenceTool& T)
{
  TopCnx_EdgeFaceTransition transTool;
  gp_Dir TgtE, NormE, TgtI, NormI;
  const Standard_Real TolAng = 0.0001;
  Standard_Real CurvE, CurvI;
  HLRAlgo_ListIteratorOfInterferenceList It1(IL);

  while (It1.More()) {
    HLRAlgo_ListIteratorOfInterferenceList It2(It1);
    It2.Next();
    if (It2.More()) {
      if (T.SameInterferences(It1.Value(),It2.Value())/* || 
	  SimilarInterference(It1.Value(),It2.Value())*/) {

	T.EdgeGeometry(T.ParameterOfInterference(It1.Value()),
		       TgtE, NormE, CurvE);
	transTool.Reset(TgtE,NormE,CurvE);
	T.InterferenceBoundaryGeometry(It1.Value(),TgtI,NormI,CurvI);
	transTool.AddInterference(TolAng,
				  TgtI,NormI,CurvI,
				  It1.Value().Orientation(),
				  It1.Value().Transition(),
				  It1.Value().BoundaryTransition());

	while (It2.More()) {
	  if (!(T.SameInterferences(It1.Value(),It2.Value())/* ||
		SimilarInterference(It1.Value(),It2.Value())*/)) break;

	  T.InterferenceBoundaryGeometry(It2.Value(),TgtI,NormI,CurvI);
	  transTool.AddInterference(TolAng,
				    TgtI,NormI,CurvI,
				    It2.Value().Orientation(),
				    It2.Value().Transition(),
				    It2.Value().BoundaryTransition());
	  IL.Remove(It2);
	}
	// get the cumulated results
	It1.Value().Transition(transTool.Transition());
	It1.Value().BoundaryTransition(transTool.BoundaryTransition());
      }
    }
    It1.Next();
  }

/*  
  //Removing "coinciding" interference

  Standard_Real p1, p2;
  Standard_Real eps = 1.e-7;
  HLRAlgo_InterferenceList ILNew;
  HLRAlgo_Interference I1, I2;
  TopAbs_Orientation or1, or2;
  Standard_Integer l1, l2; //levels
  It1.Initialize(IL);

  if(It1.More()) {
    I1 = It1.Value();
    p1 = I1.Intersection().Parameter();
    l1 = I1.Intersection().Level();
    or1 = I1.Transition();

    ILNew.Append(I1);
    HLRAlgo_ListIteratorOfInterferenceList It2(ILNew);    

    It1.Next(); 
    
    while(It1.More()) {
      I2 = It1.Value();
      p2 = I2.Intersection().Parameter();
      l2 = I2.Intersection().Level();
      or2 = I2.Transition();
      
      if(p2 - p1 <= eps && or1 == or2) {
	ILNew.Remove(It2);
	if(l2 < l1) {
	  ILNew.Append(I2);
	}
	else {
	  ILNew.Append(I1);
	}
      }
      else {
	ILNew.Append(I2);
      }
      It1.Next();
      if(It2.More()) It2.Next();
      p1 = p2;
      l1 = l2;
      or1 = or2;
      I1 = I2;
    }

    IL = ILNew;
	    
  }
*/

}
