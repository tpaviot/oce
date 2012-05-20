// Created on: 1993-10-29
// Created by: Jean Marc LACHAUME
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


#include <Standard_Stream.hxx>
#include <HatchGen_PointOnElement.ixx>

//=======================================================================
// Function : HatchGen_PointOnElement
// Purpose  : Constructor.
//=======================================================================

HatchGen_PointOnElement::HatchGen_PointOnElement () :
       HatchGen_IntersectionPoint () ,
       myType (HatchGen_UNDETERMINED)
{
}

//=======================================================================
// Function : HatchGen_PointOnElement
// Purpose  : Constructor.
//=======================================================================

HatchGen_PointOnElement::HatchGen_PointOnElement (const HatchGen_PointOnElement& Point)
{
  myIndex  = Point.myIndex ;
  myParam  = Point.myParam ;
  myPosit  = Point.myPosit ;
  myBefore = Point.myBefore ;
  myAfter  = Point.myAfter ;
  mySegBeg = Point.mySegBeg ;
  mySegEnd = Point.mySegEnd ;
  myType   = Point.myType ;
}

//=======================================================================
// Function : HatchGen_PointOnElement
// Purpose  : Constructor.
//=======================================================================

HatchGen_PointOnElement::HatchGen_PointOnElement (const IntRes2d_IntersectionPoint& Point)
{
  const IntRes2d_Transition& TrsH = Point.TransitionOfFirst() ;
  const IntRes2d_Transition& TrsE = Point.TransitionOfSecond() ;

  myIndex = 0 ;

  myParam = Point.ParamOnSecond() ;

  switch (TrsE.PositionOnCurve()) {
      case IntRes2d_Head   : myPosit = TopAbs_FORWARD  ; break ;
      case IntRes2d_Middle : myPosit = TopAbs_INTERNAL ; break ;
      case IntRes2d_End    : myPosit = TopAbs_REVERSED ; break ;
  }

  switch (TrsH.TransitionType()) {
      case IntRes2d_In : {
        myBefore = TopAbs_OUT ;
	myAfter  = TopAbs_IN  ;
	myType   = (myPosit == TopAbs_INTERNAL) ? HatchGen_TRUE : HatchGen_TOUCH ;
	break ;
      }
      case IntRes2d_Out : {
        myBefore = TopAbs_IN  ;
	myAfter  = TopAbs_OUT ;
	myType   = (myPosit == TopAbs_INTERNAL) ? HatchGen_TRUE : HatchGen_TOUCH ;
	break ;
      }
//  Modified by Sergey KHROMOV - Fri Jan  5 12:07:34 2001 Begin
      case IntRes2d_Touch : {
	switch (TrsH.Situation()) {
	    case IntRes2d_Inside : {
	      myType   = HatchGen_TANGENT ;
	      switch (myPosit) {
	        case TopAbs_FORWARD : {
		  if (TrsE.IsOpposite()) {
		    myBefore = TopAbs_IN;
		    myAfter  = TopAbs_OUT;
		  } else {
		    myBefore = TopAbs_OUT;
		    myAfter  = TopAbs_IN;
		  }
		  break ;
	        }
		case TopAbs_INTERNAL : {
		  myBefore = TopAbs_IN  ; 
		  myAfter  = TopAbs_IN  ;
		  break ;
	        }
		case TopAbs_REVERSED : {
		  if (TrsE.IsOpposite()) {
		    myBefore = TopAbs_OUT;
		    myAfter  = TopAbs_IN;
		  } else {
		    myBefore = TopAbs_IN;
		    myAfter  = TopAbs_OUT;
		  }
		  break ;
	        }
	        case TopAbs_EXTERNAL:
		  break ;
	      }
	      break ;
	    }
	    case IntRes2d_Outside : {
	      myType   = HatchGen_TANGENT ;
	      switch (myPosit) {
	        case TopAbs_FORWARD : {
		  if (TrsE.IsOpposite()) {
		    myBefore = TopAbs_OUT;
		    myAfter  = TopAbs_IN;
		  } else {
		    myBefore = TopAbs_IN;
		    myAfter  = TopAbs_OUT;
		  }
		  break ;
	        }
		case TopAbs_INTERNAL : {
		  myBefore = TopAbs_OUT ;
		  myAfter  = TopAbs_OUT ;
		  break ;
		}
		case TopAbs_REVERSED : {
		  if (TrsE.IsOpposite()) {
		    myBefore = TopAbs_IN;
		    myAfter  = TopAbs_OUT;
		  } else {
		    myBefore = TopAbs_OUT;
		    myAfter  = TopAbs_IN;
		  }
		  break ;
	        }
	        case TopAbs_EXTERNAL:
		  break ;
	      }
	      break ;
	    }
	    case IntRes2d_Unknown : {
	      myBefore = TopAbs_UNKNOWN ;
	      myAfter  = TopAbs_UNKNOWN ;
	      myType   = HatchGen_TANGENT ;
	      break ;
	    }
	}
	break ;
      }
//  Modified by Sergey KHROMOV - Fri Jan  5 12:07:46 2001 End
      case IntRes2d_Undecided : {
	myBefore = TopAbs_UNKNOWN ;
	myAfter  = TopAbs_UNKNOWN ;
	myType   = HatchGen_UNDETERMINED ;
	break ;
      }
  }

  mySegBeg = Standard_False ;
  mySegEnd = Standard_False ;
}


//=======================================================================
// Function : IsIdentical
// Purpose  : Tests if the point is identical to an other.
//=======================================================================

Standard_Boolean HatchGen_PointOnElement::IsIdentical (const HatchGen_PointOnElement& Point,
						       const Standard_Real Confusion) const
{
  Standard_Real Delta = Abs (myParam - Point.myParam) ;
  return (   (Delta    <= Confusion)
          && (myIndex  == Point.myIndex)
          && (myPosit  == Point.myPosit)
          && (myType   == Point.myType)
          && (myBefore == Point.myBefore)
          && (myAfter  == Point.myAfter)
          && (mySegBeg == Point.mySegBeg)
          && (mySegEnd == Point.mySegEnd)) ;
}

//=======================================================================
// Function : IsDifferent
// Purpose  : Tests if the point is different from an other.
//=======================================================================

Standard_Boolean HatchGen_PointOnElement::IsDifferent (const HatchGen_PointOnElement& Point,
						       const Standard_Real Confusion) const
{
  Standard_Real Delta = Abs (myParam - Point.myParam) ;
  return (   (Delta    >  Confusion)
          || (myIndex  != Point.myIndex)
          || (myPosit  != Point.myPosit)
          || (myType   != Point.myType)
          || (myBefore != Point.myBefore)
          || (myAfter  != Point.myAfter)
          || (mySegBeg != Point.mySegBeg)
          || (mySegEnd != Point.mySegEnd)) ;
}

//=======================================================================
// Function : Dump
// Purpose  : Dump of the point on element
//=======================================================================

void HatchGen_PointOnElement::Dump (const Standard_Integer Index) const
{
  cout << "    --- Point on element " ;
  if (Index > 0) {
    cout << "# " << setw(3) << Index << " " ;
  } else {
    cout << "------" ;
  }
  cout << "---------------" << endl ;

  cout << "        Index of the element = " << myIndex << endl ;
  cout << "        Parameter on element = " << myParam << endl ;
  cout << "        Position  on element = " ;
  switch (myPosit) {
      case TopAbs_FORWARD  : cout << "FORWARD  (i.e. BEGIN  )" ; break ;
      case TopAbs_INTERNAL : cout << "INTERNAL (i.e. MIDDLE )" ; break ;
      case TopAbs_REVERSED : cout << "REVERSED (i.e. END    )" ; break ;
      case TopAbs_EXTERNAL : cout << "EXTERNAL (i.e. UNKNOWN)" ; break ;
  }
  cout << endl ;
  cout << "        Intersection Type    = " ;
  switch (myType) {
      case HatchGen_TRUE         : cout << "TRUE"         ; break ;
      case HatchGen_TOUCH        : cout << "TOUCH"        ; break ;
      case HatchGen_TANGENT      : cout << "TANGENT"      ; break ;
      case HatchGen_UNDETERMINED : cout << "UNDETERMINED" ; break ;
  }
  cout << endl ;
  cout << "        State Before         = " ;
  switch (myBefore) {
      case TopAbs_IN      : cout << "IN"      ; break ;
      case TopAbs_OUT     : cout << "OUT"     ; break ;
      case TopAbs_ON      : cout << "ON"      ; break ;
      case TopAbs_UNKNOWN : cout << "UNKNOWN" ; break ;
  }
  cout << endl ;
  cout << "        State After          = " ;
  switch (myAfter) {
      case TopAbs_IN      : cout << "IN"      ; break ;
      case TopAbs_OUT     : cout << "OUT"     ; break ;
      case TopAbs_ON      : cout << "ON"      ; break ;
      case TopAbs_UNKNOWN : cout << "UNKNOWN" ; break ;
  }
  cout << endl ;
  cout << "        Beginning of segment = " << (mySegBeg ? "TRUE" : "FALSE") << endl ;
  cout << "        End       of segment = " << (mySegEnd ? "TRUE" : "FALSE") << endl ;

  cout << "    ------------------------------------------" << endl ;
}
