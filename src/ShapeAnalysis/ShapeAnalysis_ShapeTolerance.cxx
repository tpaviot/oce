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

//#76 rln 11.03.99 S4135: compute average without weights according to tolerances
//szv#4 S4163
#include <ShapeAnalysis_ShapeTolerance.ixx>

#include <BRep_Tool.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>

#include <TopExp_Explorer.hxx>

#include <TopTools_MapOfShape.hxx>


//=======================================================================
//function : ShapeAnalysis_ShapeTolerance
//purpose  : 
//=======================================================================

ShapeAnalysis_ShapeTolerance::ShapeAnalysis_ShapeTolerance() : myNbTol (0)
{
}

static  void  AddTol (const Standard_Real tol, Standard_Integer&   nbt,
	      Standard_Real&  cmin, Standard_Real& cmoy, Standard_Real& cmax)
{
  nbt ++;
  if      (nbt == 1)  cmin = cmoy = cmax = tol;
  else {
    if (cmin > tol) cmin = tol;
    if (cmax < tol) cmax = tol;
//    cmoy += tol;
//  Calcul en moyenne geometrique  entre 1 et 1e-7
    Standard_Integer mult = 1;
    //#76 rln 11.03.99 S4135: compute average without weights according to tolerances
/*    if      (tol < 1.e-07) mult = 10000;
    else if (tol < 1.e-06) mult =  3000;
    else if (tol < 1.e-05) mult =  1000;
    else if (tol < 1.e-04) mult =   300;
    else if (tol < 1.e-03) mult =   100;
    else if (tol < 1.e-02) mult =    30;
    else if (tol < 1.e-01) mult =    10;
    else if (tol < 1.    ) mult =     3;
*/
    nbt += (mult-1);
    cmoy += (tol * mult);
  }
}


//=======================================================================
//function : Tolerance
//purpose  : 
//=======================================================================

Standard_Real ShapeAnalysis_ShapeTolerance::Tolerance(const TopoDS_Shape& shape,const Standard_Integer mode,const TopAbs_ShapeEnum type) 
{
  InitTolerance();
  AddTolerance (shape, type);
  return GlobalTolerance (mode);
}

//=======================================================================
//function : OverTolerance
//purpose  : 
//=======================================================================

 Handle(TopTools_HSequenceOfShape) ShapeAnalysis_ShapeTolerance::OverTolerance(const TopoDS_Shape& shape,const Standard_Real value,const TopAbs_ShapeEnum type) const
{
  if (value >= 0) return InTolerance (shape,value,0.,type);
  else return InTolerance (shape,0.,value,type);
}

//=======================================================================
//function : InTolerance
//purpose  : 
//=======================================================================

 Handle(TopTools_HSequenceOfShape) ShapeAnalysis_ShapeTolerance::InTolerance(const TopoDS_Shape& shape,const Standard_Real valmin,const Standard_Real valmax,const TopAbs_ShapeEnum type) const
{
  Standard_Real tol;
  Standard_Boolean over = (valmax < valmin);  // pas de liminite max
  Handle(TopTools_HSequenceOfShape) sl = new TopTools_HSequenceOfShape ();

  TopExp_Explorer myExp;

  // Iteration sur les Faces

  if (type == TopAbs_FACE || type == TopAbs_SHAPE) {
    myExp.Init(shape, TopAbs_FACE);
    while(myExp.More()) {
      tol = BRep_Tool::Tolerance(TopoDS::Face(myExp.Current()));
      if (tol >= valmin && (over || (tol <= valmax)) ) sl->Append (myExp.Current());
      myExp.Next();
    }
  }

  // Iteration sur les Edges

  if (type == TopAbs_EDGE || type == TopAbs_SHAPE) {
    myExp.Init(shape, TopAbs_EDGE);
    while(myExp.More()) {
      tol = BRep_Tool::Tolerance(TopoDS::Edge(myExp.Current()));
      if (tol >= valmin && (over || (tol <= valmax)) ) sl->Append (myExp.Current());
      myExp.Next();
    }
  }

  // Iteration sur les Vertex

  if (type == TopAbs_VERTEX || type == TopAbs_SHAPE) {
    myExp.Init(shape, TopAbs_VERTEX);
    while(myExp.More()) {
      tol = BRep_Tool::Tolerance(TopoDS::Vertex(myExp.Current()));
      if (tol >= valmin && (over || (tol >= valmax)) ) sl->Append (myExp.Current());
      myExp.Next();
    }
  }

  // Iteration combinee (cumul) SHELL+FACE+EDGE+VERTEX, on retourne SHELL+FACE

  if (type == TopAbs_SHELL) {
    //  Exploration des shells
    TopTools_MapOfShape mapface;
    myExp.Init (shape, TopAbs_SHELL);
    while(myExp.More()) {
      Standard_Boolean iashell = Standard_False;
      TopoDS_Shape ash = myExp.Current();
      for (TopExp_Explorer face (ash,TopAbs_FACE); face.More(); face.Next()) {
	mapface.Add (face.Current());
	Handle(TopTools_HSequenceOfShape) fc =
	  InTolerance (face.Current(),valmin,valmax,type);
	if (fc->Length() > 0) {
	  sl->Append(fc);
	  iashell = Standard_True;
	}
      }
      if (iashell) sl->Append (ash);
      myExp.Next();
    }

    //  Les faces (libres ou sous shell)
    myExp.Init (shape, TopAbs_FACE);
    for (; myExp.More(); myExp.Next()) {
      Standard_Boolean iaface = Standard_False;
      if (mapface.Contains (myExp.Current()) ) continue;
      tol = BRep_Tool::Tolerance(TopoDS::Face(myExp.Current()));
      if (tol >= valmin && (over || (tol <= valmax)) ) iaface = Standard_True;
      else {
	// les edges contenues ?
	Handle(TopTools_HSequenceOfShape) fl =
	  InTolerance (myExp.Current(),valmin,valmax,TopAbs_EDGE);
	if (fl->Length() > 0) iaface = Standard_True;
	else {
	  fl = InTolerance (myExp.Current(),valmin,valmax,TopAbs_VERTEX);
	  if (fl->Length() > 0) iaface = Standard_True;
	}
      }
      if (iaface) sl->Append (myExp.Current());
    }

  }

  return sl;
}

//=======================================================================
//function : InitTolerance
//purpose  : 
//=======================================================================

 void ShapeAnalysis_ShapeTolerance::InitTolerance() 
{
  myNbTol = 0;
  myTols[1] = 0;
}

//=======================================================================
//function : AddTolerance
//purpose  : 
//=======================================================================

 void ShapeAnalysis_ShapeTolerance::AddTolerance(const TopoDS_Shape& shape,const TopAbs_ShapeEnum type) 
{
  Standard_Integer nbt   = 0;
  Standard_Real tol, cmin = 0,cmoy = 0,cmax = 0;

  TopExp_Explorer myExp;

  // Iteration sur les Faces

  if (type == TopAbs_FACE || type == TopAbs_SHAPE) {
    myExp.Init(shape, TopAbs_FACE);
    while(myExp.More()) {
      tol = BRep_Tool::Tolerance(TopoDS::Face(myExp.Current()));
      AddTol (tol,nbt,cmin,cmoy,cmax);
      myExp.Next();
    }
  }

  // Iteration sur les Edges

  if (type == TopAbs_EDGE || type == TopAbs_SHAPE) {
    myExp.Init(shape, TopAbs_EDGE);
    while(myExp.More()) {
      tol = BRep_Tool::Tolerance(TopoDS::Edge(myExp.Current()));
      AddTol (tol,nbt,cmin,cmoy,cmax);
      myExp.Next();
    }
  }

  // Iteration sur les Vertices

  if (type == TopAbs_VERTEX || type == TopAbs_SHAPE) {
    myExp.Init(shape, TopAbs_VERTEX);
    while(myExp.More()) {
      tol = BRep_Tool::Tolerance(TopoDS::Vertex(myExp.Current()));
      AddTol (tol,nbt,cmin,cmoy,cmax);
      myExp.Next();
    }
  }

//  Resultat : attention en mode cumul
  if (nbt == 0) return;
  if (myNbTol == 0 || myTols[0] >  cmin) myTols[0] = cmin;
  if (myNbTol == 0 || myTols[2] <  cmax) myTols[2] = cmax;
  myTols[1] += cmoy;
  myNbTol   += nbt;
}

//=======================================================================
//function : GlobalTolerance
//purpose  : 
//=======================================================================

 Standard_Real ShapeAnalysis_ShapeTolerance::GlobalTolerance(const Standard_Integer mode) const
{
  //szv#4:S4163:12Mar99 optimized
  Standard_Real result = 0.;
  if (myNbTol != 0.) {
    if (mode < 0) result = myTols[0];
    else if (mode == 0) {
      if (myTols[0] == myTols[2]) result = myTols[0];
      else result =  myTols[1] / myNbTol;
    }
    else result = myTols[2];
  }

  return result;
}
