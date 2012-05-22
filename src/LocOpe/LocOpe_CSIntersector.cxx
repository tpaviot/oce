// Created on: 1996-06-11
// Created by: Jacques GOUSSARD
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



#include <LocOpe_CSIntersector.ixx>

#include <LocOpe_PntFace.hxx>
#include <LocOpe_SequenceOfPntFace.hxx>
#include <TopExp_Explorer.hxx>

#include <IntCurvesFace_Intersector.hxx>
#include <GeomAdaptor_HCurve.hxx>
#include <Geom_Circle.hxx>


#include <Standard_ConstructionError.hxx>

#include <TopoDS.hxx>
#include <Precision.hxx>

static Standard_Boolean LocAfter (const LocOpe_SequenceOfPntFace&,
				  const Standard_Real,
				  const Standard_Real,
				  TopAbs_Orientation&,
				  Standard_Integer&,
				  Standard_Integer&);
				  
static Standard_Boolean LocBefore (const LocOpe_SequenceOfPntFace&,
				   const Standard_Real,
				   const Standard_Real,
				   TopAbs_Orientation&,
				   Standard_Integer&,
				   Standard_Integer&);
				   
static Standard_Boolean LocAfter (const LocOpe_SequenceOfPntFace&,
				  const Standard_Integer,
				  const Standard_Real,
				  TopAbs_Orientation&,
				  Standard_Integer&,
				  Standard_Integer&);

#ifdef DEB				  
static Standard_Boolean LocBefore (const LocOpe_SequenceOfPntFace&,
				   const Standard_Integer,
				   Standard_Integer&,
				   Standard_Integer&);
#endif


static void AddPoints(IntCurvesFace_Intersector&,
                      LocOpe_SequenceOfPntFace&,
		      const TopoDS_Face&);




//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void LocOpe_CSIntersector::Init(const TopoDS_Shape& S)
{
  myDone = Standard_False;
  myShape = S;
  if (myPoints != NULL) {
    delete [] (LocOpe_SequenceOfPntFace *)myPoints;
    myPoints = NULL;
  }
  myNbelem = 0;
}


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void LocOpe_CSIntersector::Perform(const LocOpe_SequenceOfLin& Slin)
{
  if (myShape.IsNull() || Slin.Length() <= 0) {
    Standard_ConstructionError::Raise();
  }
  myDone = Standard_False;

  myNbelem = Slin.Length();
  if (myPoints != NULL) {
    delete [] (LocOpe_SequenceOfPntFace *)myPoints;
  }
  myPoints = 
    (LocOpe_SequenceOfPntFace *) new LocOpe_SequenceOfPntFace[myNbelem];

  Standard_Real binf = RealFirst();
  Standard_Real bsup = RealLast();
  TopExp_Explorer exp(myShape,TopAbs_FACE);
  for (; exp.More(); exp.Next()) {
    const TopoDS_Face& theface = TopoDS::Face(exp.Current());
    IntCurvesFace_Intersector theInt(theface,Precision::PConfusion());
    for (Standard_Integer i = 1; i<=myNbelem; i++) {
      theInt.Perform(Slin(i),binf,bsup);
      if (theInt.IsDone()) {
	AddPoints(theInt,(((LocOpe_SequenceOfPntFace*)myPoints)[i-1]),theface);
      }
    }
  }
  myDone = Standard_True;
}


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void LocOpe_CSIntersector::Perform(const LocOpe_SequenceOfCirc& Scir)
{
  if (myShape.IsNull() || Scir.Length() <= 0) {
    Standard_ConstructionError::Raise();
  }
  myDone = Standard_False;

  myNbelem = Scir.Length();
  if (myPoints != NULL) {
    delete [] (LocOpe_SequenceOfPntFace *)myPoints;
  }
  myPoints = 
    (LocOpe_SequenceOfPntFace *) new LocOpe_SequenceOfPntFace[myNbelem];

  TopExp_Explorer exp(myShape,TopAbs_FACE);
  Handle(GeomAdaptor_HCurve) HC = new GeomAdaptor_HCurve ();
  Standard_Real binf = 0.;
  Standard_Real bsup = 2.*M_PI;


  for (; exp.More(); exp.Next()) {
    const TopoDS_Face& theface = TopoDS::Face(exp.Current());
    IntCurvesFace_Intersector theInt(theface,0.);
    for (Standard_Integer i = 1; i<=myNbelem; i++) {

      HC->ChangeCurve().Load(new Geom_Circle(Scir(i)));
      theInt.Perform(HC,binf,bsup);
      if (theInt.IsDone()) {
	AddPoints(theInt,(((LocOpe_SequenceOfPntFace*)myPoints)[i-1]),theface);
      }
    }
  }
  myDone = Standard_True;
}

    

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void LocOpe_CSIntersector::Perform(const TColGeom_SequenceOfCurve& Scur)
{
  if (myShape.IsNull() || Scur.Length() <= 0) {
    Standard_ConstructionError::Raise();
  }
  myDone = Standard_False;

  myNbelem = Scur.Length();
  if (myPoints != NULL) {
    delete [] (LocOpe_SequenceOfPntFace *)myPoints;
  }
  myPoints = 
    (LocOpe_SequenceOfPntFace *) new LocOpe_SequenceOfPntFace[myNbelem];

  TopExp_Explorer exp(myShape,TopAbs_FACE);
  Handle(GeomAdaptor_HCurve) HC = new GeomAdaptor_HCurve ();
  for (; exp.More(); exp.Next()) {
    const TopoDS_Face& theface = TopoDS::Face(exp.Current());
    IntCurvesFace_Intersector theInt(theface,0.);
    for (Standard_Integer i = 1; i<=myNbelem; i++) {
      if (Scur(i).IsNull()) {
	continue;
      }
      HC->ChangeCurve().Load(Scur(i));
      Standard_Real binf = HC->FirstParameter();
      Standard_Real bsup = HC->LastParameter();
      theInt.Perform(HC,binf,bsup);
      if (theInt.IsDone()) {
	AddPoints(theInt,(((LocOpe_SequenceOfPntFace*)myPoints)[i-1]),theface);
      }
    }
  }
  myDone = Standard_True;
}

    

//=======================================================================
//function : NbPoints
//purpose  : 
//=======================================================================

Standard_Integer LocOpe_CSIntersector::NbPoints
   (const Standard_Integer I) const
{
  if (!myDone) {StdFail_NotDone::Raise();}
  if (I <= 0 || I > myNbelem) {
    Standard_OutOfRange::Raise();
  }
  return ((LocOpe_SequenceOfPntFace *)myPoints)[I-1].Length();
}

//=======================================================================
//function : Point
//purpose  : 
//=======================================================================

const LocOpe_PntFace& LocOpe_CSIntersector::
   Point(const Standard_Integer I,
	 const Standard_Integer Index) const
{
  if (!myDone) {StdFail_NotDone::Raise();}
  if (I <= 0 || I > myNbelem) {
    Standard_OutOfRange::Raise();
  }
  return ((LocOpe_SequenceOfPntFace *)myPoints)[I-1](Index);
}
    
//=======================================================================
//function : Destroy
//purpose  : 
//=======================================================================

void LocOpe_CSIntersector::Destroy()
{
  if (myPoints != NULL) {
    delete [] (LocOpe_SequenceOfPntFace *)myPoints;
    myPoints = NULL;
  }
}


//=======================================================================
//function : LocalizeAfter
//purpose  : 
//=======================================================================

Standard_Boolean LocOpe_CSIntersector::LocalizeAfter
   (const Standard_Integer I,
    const Standard_Real From,
    const Standard_Real Tol,
    TopAbs_Orientation& Or,
    Standard_Integer& IndFrom,
    Standard_Integer& IndTo) const
{
  if (!myDone) {
    StdFail_NotDone::Raise();
  }
  if (I <= 0 || I > myNbelem) {
    Standard_OutOfRange::Raise();
  }
  return LocAfter((((LocOpe_SequenceOfPntFace*)myPoints)[I-1]),
		  From,Tol,Or,IndFrom,IndTo);
}


//=======================================================================
//function : LocalizeBefore
//purpose  : 
//=======================================================================

Standard_Boolean LocOpe_CSIntersector::LocalizeBefore 
   (const Standard_Integer I,
    const Standard_Real From,
    const Standard_Real Tol,
    TopAbs_Orientation& Or,
    Standard_Integer& IndFrom,
    Standard_Integer& IndTo) const
{
  if (!myDone) {
    StdFail_NotDone::Raise();
  }
  if (I <= 0 || I > myNbelem) {
    Standard_OutOfRange::Raise();
  }
  return LocBefore(((LocOpe_SequenceOfPntFace*)myPoints)[I-1],
		   From,Tol,Or,IndFrom,IndTo);
}

//=======================================================================
//function : LocalizeAfter
//purpose  : 
//=======================================================================

Standard_Boolean LocOpe_CSIntersector::LocalizeAfter 
   (const Standard_Integer I,
    const Standard_Integer FromInd,
    const Standard_Real Tol,
    TopAbs_Orientation& Or,
    Standard_Integer& IndFrom,
    Standard_Integer& IndTo) const
{
  if (!myDone) {
    StdFail_NotDone::Raise();
  }
  if (I <= 0 || I > myNbelem) {
    Standard_OutOfRange::Raise();
  }
  return LocAfter(((LocOpe_SequenceOfPntFace*)myPoints)[I-1],
		  FromInd,Tol,Or,IndFrom,IndTo);

}

//=======================================================================
//function : LocalizeBefore
//purpose  : 
//=======================================================================

Standard_Boolean LocOpe_CSIntersector::LocalizeBefore 
   (const Standard_Integer I,
    const Standard_Integer FromInd,
    const Standard_Real Tol,
    TopAbs_Orientation& Or,
    Standard_Integer& IndFrom,
    Standard_Integer& IndTo) const
{
  if (!myDone) {
    StdFail_NotDone::Raise();
  }
  if (I <= 0 || I > myNbelem) {
    Standard_OutOfRange::Raise();
  }
  return LocBefore(((LocOpe_SequenceOfPntFace*)myPoints)[I-1],
		   FromInd,Tol,Or,IndFrom,IndTo);
  
}




//=======================================================================
//function : LocAfter
//purpose  : 
//=======================================================================

static Standard_Boolean LocAfter (const LocOpe_SequenceOfPntFace& Spt,
				  const Standard_Real From,
				  const Standard_Real Tol,
				  TopAbs_Orientation& Or,
				  Standard_Integer& IndFrom,
				  Standard_Integer& IndTo)
{

  Standard_Real param,FMEPS = From - Tol;
  Standard_Integer i,ifirst,nbpoints = Spt.Length();
  for (ifirst=1; ifirst<=nbpoints; ifirst++) {
    if (Spt(ifirst).Parameter() >= FMEPS) {
      break;
    }
  }
  Standard_Boolean RetVal = Standard_False;
  if (ifirst <= nbpoints) {
    i = ifirst;
    IndFrom = ifirst;
    Standard_Boolean found = Standard_False;
    while (!found) {
      Or = Spt(i).Orientation();
      param = Spt(i).Parameter();
      i = i+1;
      while (i<=nbpoints) {
	if (Spt(i).Parameter()-param <= Tol) {
	  if (Or != TopAbs_EXTERNAL && Or != Spt(i).Orientation()) {
	    Or = TopAbs_EXTERNAL;
	  }
	  i++;
	}
	else {
	  break;
	}
      }
      if (Or == TopAbs_EXTERNAL) {
	found = (i > nbpoints);
	IndFrom = i;
      }
      else { // on a une intersection franche
	IndTo = i-1;
	found = Standard_True;
	RetVal = Standard_True;
      }
    }
  }

  return RetVal;
}

//=======================================================================
//function : LocBefore
//purpose  : 
//=======================================================================

static Standard_Boolean LocBefore (const LocOpe_SequenceOfPntFace& Spt,
				   const Standard_Real From,
				   const Standard_Real Tol,
				   TopAbs_Orientation& Or,
				   Standard_Integer& IndFrom,
				   Standard_Integer& IndTo)
{
  Standard_Real param,FPEPS = From + Tol;
  Standard_Integer i,ifirst,nbpoints = Spt.Length();
  for (ifirst=nbpoints; ifirst>=1; ifirst--) {
    if (Spt(ifirst).Parameter() <= FPEPS) {
      break;
    }
  }
  Standard_Boolean RetVal = Standard_False;
  if (ifirst >= 1) {
    i = ifirst;
    IndTo = ifirst;
    Standard_Boolean found = Standard_False;
    while (!found) {
      Or = Spt(i).Orientation();
      param = Spt(i).Parameter();
      i = i-1;
      while (i>=1) {
	if (param - Spt(i).Parameter() <= Tol) {
	  if (Or != TopAbs_EXTERNAL && Or != Spt(i).Orientation()) {
	    Or = TopAbs_EXTERNAL;
	  }
	  i--;
	}
	else {
	  break;
	}
      }
      if (Or == TopAbs_EXTERNAL) {
	found = (i < 1);
	IndTo = i;
      }
      else { // on a une intersection franche
	IndFrom = i+1;
	found = Standard_True;
	RetVal = Standard_True;
      }
    }
  }

  return RetVal;
}

//=======================================================================
//function : LocAfter
//purpose  : 
//=======================================================================

static Standard_Boolean LocAfter (const LocOpe_SequenceOfPntFace& Spt,
				  const Standard_Integer FromInd,
				  const Standard_Real Tol,
				  TopAbs_Orientation& Or,
				  Standard_Integer& IndFrom,
				  Standard_Integer& IndTo)
{
  Standard_Integer nbpoints = Spt.Length();
  if (FromInd >= nbpoints) {
    return Standard_False;
  }
 
  Standard_Real param,FMEPS;
  Standard_Integer i,ifirst;
  if (FromInd >= 1) {
    FMEPS = Spt(FromInd).Parameter() - Tol;
    for (ifirst=FromInd+1; ifirst<=nbpoints; ifirst++) {
      if (Spt(ifirst).Parameter() >= FMEPS) {
	break;
      }
    }
  }
  else {
    ifirst = 1;
  }

  Standard_Boolean RetVal = Standard_False;
  if (ifirst <= nbpoints) {
    i = ifirst;
    IndFrom = ifirst;
    Standard_Boolean found = Standard_False;
    while (!found) {
      Or = Spt(i).Orientation();
      param = Spt(i).Parameter();
      i = i+1;
      while (i<=nbpoints) {
	if (Spt(i).Parameter()-param <= Tol) {
	  if (Or != TopAbs_EXTERNAL && Or != Spt(i).Orientation()) {
	    Or = TopAbs_EXTERNAL;
	  }
	  i++;
	}
	else {
	  break;
	}
      }
      if (Or == TopAbs_EXTERNAL) {
	found = (i > nbpoints);
	IndFrom = i;
      }
      else { // on a une intersection franche
	IndTo = i-1;
	found = Standard_True;
	RetVal = Standard_True;
      }
    }
  }
  return RetVal;
}


//=======================================================================
//function : LocBefore
//purpose  : 
//=======================================================================

#ifdef DEB
static Standard_Boolean LocBefore (const LocOpe_SequenceOfPntFace& Spt,
				   const Standard_Integer FromInd,
				   const Standard_Real Tol,
				   TopAbs_Orientation& Or,
				   Standard_Integer& IndFrom,
				   Standard_Integer& IndTo)
{
  Standard_Integer nbpoints = Spt.Length();
  if (FromInd <= 1) {
    return Standard_False;
  }
 
  Standard_Real param,FPEPS;
  Standard_Integer i,ifirst;
  if (FromInd <= nbpoints) {
    FPEPS = Spt(FromInd).Parameter() + Tol;
    for (ifirst=FromInd-1; ifirst>=1; ifirst--) {
      if (Spt(ifirst).Parameter() <= FPEPS) {
	break;
      }
    }
  }
  else {
    ifirst = nbpoints;
  }

  Standard_Boolean RetVal = Standard_False;
  if (ifirst >= 1) {
    i = ifirst;
    IndTo = ifirst;
    Standard_Boolean found = Standard_False;
    while (!found) {
      Or = Spt(i).Orientation();
      param = Spt(i).Parameter();
      i = i-1;
      while (i>=1) {
	if (param - Spt(i).Parameter() <= Tol) {
	  if (Or != TopAbs_EXTERNAL && Or != Spt(i).Orientation()) {
	    Or = TopAbs_EXTERNAL;
	  }
	  i--;
	}
	else {
	  break;
	}
      }
      if (Or == TopAbs_EXTERNAL) {
	found = (i < 1);
	IndTo = i;
      }
      else { // on a une intersection franche
	IndFrom = i+1;
	found = Standard_True;
	RetVal = Standard_True;
      }
    }
  }
  return RetVal;
}
#endif


//=======================================================================
//function : AddPoints
//purpose  : 
//=======================================================================

static void AddPoints(IntCurvesFace_Intersector& theInt,
                      LocOpe_SequenceOfPntFace& theSeq,
		      const TopoDS_Face& theface)
{
  Standard_Integer nbpoints = theSeq.Length();
  Standard_Integer newpnt = theInt.NbPnt();
  Standard_Real param,paramu,paramv;
  for (Standard_Integer j = 1; j<=newpnt; j++) {
    const gp_Pnt& thept = theInt.Pnt(j);
    param = theInt.WParameter(j);
    paramu = theInt.UParameter(j);
    paramv = theInt.VParameter(j);
#ifdef DEB
    TopAbs_Orientation theor;
#else
    TopAbs_Orientation theor=TopAbs_FORWARD;
#endif
    switch (theInt.Transition(j)) {
    case IntCurveSurface_In:
/* JAG 13.09.96
      if ( orface == TopAbs_FORWARD) {
	theor = TopAbs_FORWARD;
      }
      else if (orface == TopAbs_REVERSED) {
	theor = TopAbs_REVERSED;
      }
      else {
	theor = TopAbs_EXTERNAL;
      }
*/
      theor = TopAbs_FORWARD;

      break;
    case IntCurveSurface_Out:
/* JAG 13.09.96
      if ( orface == TopAbs_FORWARD) {
	theor = TopAbs_REVERSED;
      }
      else if (orface == TopAbs_REVERSED) {
	theor = TopAbs_FORWARD;
      }
      else {
	theor = TopAbs_EXTERNAL;
      }
*/
      theor = TopAbs_REVERSED;
      break;
    case IntCurveSurface_Tangent:
      theor = TopAbs_EXTERNAL;
      break;
      
    }
    LocOpe_PntFace newpt(thept,theface,theor,param,paramu,paramv);
//    for (Standard_Integer k=1; k <= nbpoints; k++) {
    Standard_Integer k;
    for ( k=1; k <= nbpoints; k++) {
      if (theSeq(k).Parameter() - param > 0.) {
	break;
      }
    }
    if (k <= nbpoints) {
      theSeq.InsertBefore(k,newpt);
    }
    else {
      theSeq.Append(newpt);
    }
    nbpoints++;
  }
}
