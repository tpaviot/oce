// Created on: 1996-08-27
// Created by: Jean Yves LEBEY
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


#include <TopOpeBRepTool_SolidClassifier.ixx>
#include <BRepClass3d_SolidClassifier.hxx>

//=======================================================================
//function : TopOpeBRepTool_SolidClassifier
//purpose  : 
//=======================================================================
TopOpeBRepTool_SolidClassifier::TopOpeBRepTool_SolidClassifier()
{
  Clear();
}

//modified by NIZNHY-PKV Mon Dec 16 10:39:00 2002 f
//=======================================================================
//function : Destroy
//purpose  : alias ~TopOpeBRepTool_SolidClassifier
//=======================================================================
void TopOpeBRepTool_SolidClassifier::Destroy() 
{
  Standard_Integer i, aNb;
  
  aNb=myShapeClassifierMap.Extent();
  for (i=1; i<=aNb; ++i) {
    Standard_Address anAddr=myShapeClassifierMap(i);
    BRepClass3d_SolidClassifier* pClsf=
      (BRepClass3d_SolidClassifier*) anAddr;
    delete pClsf;
  }
  myShapeClassifierMap.Clear();
}

//=======================================================================
//function : LoadSolid
//purpose  : 
//=======================================================================
void TopOpeBRepTool_SolidClassifier::LoadSolid(const TopoDS_Solid& SOL) 
{
  Standard_Boolean found = myShapeClassifierMap.Contains(SOL);

  if ( !found ) {
    myPClassifier = new BRepClass3d_SolidClassifier(SOL);
    myShapeClassifierMap.Add(SOL, (Standard_Address)myPClassifier);
  }
  else {
    myPClassifier = 
      (BRepClass3d_SolidClassifier*)myShapeClassifierMap.ChangeFromKey(SOL);
  }
}

//=======================================================================
//function : LoadShell
//purpose  : 
//=======================================================================
void TopOpeBRepTool_SolidClassifier::LoadShell(const TopoDS_Shell& SHE) 
{
  Standard_Boolean found = myShapeClassifierMap.Contains(SHE);
  if ( !found ) {
    myBuilder.MakeSolid(mySolid);
    myBuilder.Add(mySolid, SHE);
     
    myPClassifier = new BRepClass3d_SolidClassifier(mySolid);
    myShapeClassifierMap.Add(SHE, (Standard_Address)myPClassifier);
  }
  else {
    myPClassifier = 
      (BRepClass3d_SolidClassifier*)myShapeClassifierMap.ChangeFromKey(SHE);
  }
}
//modified by NIZNHY-PKV Mon Dec 16 10:53:41 2002 t

//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================
void TopOpeBRepTool_SolidClassifier::Clear() 
{
  myPClassifier = NULL;
  //modified by NIZNHY-PKV Mon Dec 16 10:46:04 2002 f
  //myClassifierMap.Clear();
  myShapeClassifierMap.Clear();
  //modified by NIZNHY-PKV Mon Dec 16 10:46:06 2002 t
  myState = TopAbs_UNKNOWN;
  myShell.Nullify();
  mySolid.Nullify();
}

//=======================================================================
//function : Classify
//purpose  : 
//=======================================================================
TopAbs_State TopOpeBRepTool_SolidClassifier::Classify (const TopoDS_Solid& SOL,
						       const gp_Pnt& P, 
						       const Standard_Real Tol)
{
  myPClassifier = NULL;
  myState = TopAbs_UNKNOWN;
  LoadSolid(SOL);
  if (myPClassifier == NULL) return myState;
  myPClassifier->Perform(P,Tol);
  myState = myPClassifier->State();
  const TopoDS_Shape& fres = myPClassifier->Face();
  if (fres.IsNull()) {
    // NYI : en cas d'elimination des faces EXTERNAL et INTERNAL par le
    // classifier BRepClass3d_SolidClassifier, traiter quand meme ces faces
    // pour generer l'etat ON/Solid quand le point est IN/face INTERNAL ou EXTERNAL 
    return myState;
  }
  TopAbs_Orientation ofres = fres.Orientation();
  if      ( ofres == TopAbs_EXTERNAL ) {
    if      ( myState == TopAbs_IN ) myState = TopAbs_OUT;
    else if ( myState == TopAbs_OUT ) myState = TopAbs_OUT;
    else if ( myState == TopAbs_ON ) myState = TopAbs_ON;
    else if ( myState == TopAbs_UNKNOWN ) myState = TopAbs_OUT;
  }
  else if ( ofres == TopAbs_INTERNAL ) {
    if      ( myState == TopAbs_IN ) myState = TopAbs_IN;
    else if ( myState == TopAbs_OUT) myState = TopAbs_IN;
    else if ( myState == TopAbs_ON ) myState = TopAbs_ON;
    else if ( myState == TopAbs_UNKNOWN ) myState = TopAbs_IN;
  }
  return myState;
}

//=======================================================================
//function : Classify
//purpose  : 
//=======================================================================
TopAbs_State TopOpeBRepTool_SolidClassifier::Classify(const TopoDS_Shell& SHE, 
						      const gp_Pnt& P, 
						      const Standard_Real Tol)
{
  myPClassifier = NULL;
  myState = TopAbs_UNKNOWN;
  LoadShell(SHE);
  if (myPClassifier == NULL) return myState;
  myPClassifier->Perform(P,Tol);
  myState = myPClassifier->State();
  return myState;
}

//=======================================================================
//function : State
//purpose  : 
//=======================================================================
TopAbs_State TopOpeBRepTool_SolidClassifier::State() const
{
  return myState;
}
//modified by NIZNHY-PKV Mon Dec 16 10:55:47 2002 f
/*
//=======================================================================
//function : LoadSolid
//purpose  : 
//=======================================================================

void TopOpeBRepTool_SolidClassifier::LoadSolid(const TopoDS_Solid& SOL) 
{
  Standard_Boolean found = myClassifierMap.Contains(SOL);
  if ( !found ) {
    myPClassifier = new BRepClass3d_SolidClassifier(SOL);
    myClassifierMap.Add(SOL,*myPClassifier);
  }
  else {
    myPClassifier = &myClassifierMap.ChangeFromKey(SOL);
  }
#ifdef DEB
  Standard_Integer i =
#endif
                       myClassifierMap.FindIndex(SOL); // DEB
}

//=======================================================================
//function : LoadShell
//purpose  : 
//=======================================================================
void TopOpeBRepTool_SolidClassifier::LoadShell(const TopoDS_Shell& SHE) 
{
  Standard_Boolean found = myClassifierMap.Contains(SHE);
  if ( !found ) {
    myBuilder.MakeSolid(mySolid);
    myBuilder.Add(mySolid,SHE);
    TopoDS_Shell* pshe = (TopoDS_Shell*)&SHE; (*pshe).Free(Standard_True);  
    myPClassifier = new BRepClass3d_SolidClassifier(mySolid);
    myClassifierMap.Add(SHE,*myPClassifier);
  }
  else {
    myPClassifier = &myClassifierMap.ChangeFromKey(SHE);
  }
#ifdef DEB
  Standard_Integer i =
#endif
                       myClassifierMap.FindIndex(SHE); // DEB
}
*/
//modified by NIZNHY-PKV Mon Dec 16 10:55:56 2002 t
