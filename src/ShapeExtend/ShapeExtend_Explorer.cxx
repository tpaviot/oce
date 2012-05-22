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

//szv#4 S4163
#include <ShapeExtend_Explorer.ixx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <BRep_Builder.hxx>

//=======================================================================
//function : ShapeExtend_Explorer
//purpose  : 
//=======================================================================

ShapeExtend_Explorer::ShapeExtend_Explorer()
{
}

//=======================================================================
//function : CompoundFromSeq
//purpose  : 
//=======================================================================

TopoDS_Shape ShapeExtend_Explorer::CompoundFromSeq
  (const Handle(TopTools_HSequenceOfShape)& seqval) const
{
  BRep_Builder B;
  TopoDS_Compound C;
  B.MakeCompound(C);
  Standard_Integer i,n = seqval->Length();
  for (i = 1; i <= n ; i ++)  B.Add(C,seqval->Value(i));
  return C;
}

//=======================================================================
//function : SeqFromCompound
//purpose  : 
//=======================================================================

static void FillList (const Handle(TopTools_HSequenceOfShape)& list,
		      const TopoDS_Shape& comp, const Standard_Boolean expcomp)
{
  for (TopoDS_Iterator it (comp); it.More(); it.Next()) {
    TopoDS_Shape sub = it.Value();
    if (sub.ShapeType() != TopAbs_COMPOUND) list->Append (sub);
    else if (!expcomp) list->Append (sub);
    else FillList (list,sub,expcomp);
  }
}

Handle(TopTools_HSequenceOfShape) ShapeExtend_Explorer::SeqFromCompound
       (const TopoDS_Shape& comp, const Standard_Boolean expcomp) const
{
  Handle(TopTools_HSequenceOfShape) list = new TopTools_HSequenceOfShape();
  if (comp.IsNull()) return list;
  if (comp.ShapeType() != TopAbs_COMPOUND) {
    list->Append (comp);
    return list;
  }
  FillList (list,comp,expcomp);
  return list;
}

//=======================================================================
//function : ListFromSeq
//purpose  : 
//=======================================================================

void ShapeExtend_Explorer::ListFromSeq (const Handle(TopTools_HSequenceOfShape)& seqval,
				       TopTools_ListOfShape& lisval,
				       const Standard_Boolean clear) const
{
  if (clear) lisval.Clear();
  if (seqval.IsNull()) return;
  Standard_Integer i, nb = seqval->Length();
  for (i = 1; i <= nb; i ++) lisval.Append (seqval->Value(i));
}

//=======================================================================
//function : SeqFromList
//purpose  : 
//=======================================================================

Handle(TopTools_HSequenceOfShape) ShapeExtend_Explorer::SeqFromList
       (const TopTools_ListOfShape& lisval) const
{
  Handle(TopTools_HSequenceOfShape) seqval = new TopTools_HSequenceOfShape();
  TopTools_ListIteratorOfListOfShape it;
  for (it.Initialize(lisval); it.More(); it.Next()) seqval->Append (it.Value());
  return seqval;
}

//=======================================================================
//function : ShapeType
//purpose  : 
//=======================================================================

TopAbs_ShapeEnum ShapeExtend_Explorer::ShapeType (const TopoDS_Shape& shape,
						 const Standard_Boolean compound) const
{
  if (shape.IsNull()) return TopAbs_SHAPE;
  TopAbs_ShapeEnum res = shape.ShapeType();
  if (!compound || res != TopAbs_COMPOUND) return res;
  res = TopAbs_SHAPE;
  for (TopoDS_Iterator iter(shape); iter.More(); iter.Next()) {
    TopoDS_Shape sh = iter.Value();
    if (sh.IsNull()) continue;
    TopAbs_ShapeEnum typ = sh.ShapeType();
    if (typ == TopAbs_COMPOUND) typ = ShapeType (sh,compound);
    if (res == TopAbs_SHAPE) res = typ;
    //   Egalite : OK;  Pseudo-Egalite : EDGE/WIRE ou FACE/SHELL
    else if (res == TopAbs_EDGE  && typ == TopAbs_WIRE)  res = typ;
    else if (res == TopAbs_WIRE  && typ == TopAbs_EDGE)  continue;
    else if (res == TopAbs_FACE  && typ == TopAbs_SHELL) res = typ;
    else if (res == TopAbs_SHELL && typ == TopAbs_FACE)  continue;
    else if (res != typ) return TopAbs_COMPOUND;
  }
  return res;
}

//=======================================================================
//function : SortedCompound
//purpose  : 
//=======================================================================

TopoDS_Shape ShapeExtend_Explorer::SortedCompound (const TopoDS_Shape& shape,
						  const TopAbs_ShapeEnum type,
						  const Standard_Boolean explore,
						  const Standard_Boolean compound) const
{
  if (shape.IsNull()) return shape;
  TopAbs_ShapeEnum typ = shape.ShapeType();
  TopoDS_Shape sh, sh0;
  Standard_Integer nb = 0;

  //  Compound : on le prend, soit tel quel, soit son contenu
  if (typ == TopAbs_COMPOUND || typ == TopAbs_COMPSOLID) {
    TopoDS_Compound C;
    BRep_Builder B;
    B.MakeCompound (C);
    for (TopoDS_Iterator it(shape); it.More(); it.Next()) {
      sh0 = SortedCompound (it.Value(),type,explore,compound);
      if (sh0.IsNull()) continue;
      sh = sh0;
      typ = sh.ShapeType();
      if (typ == TopAbs_COMPOUND && !compound) {
	for (TopoDS_Iterator it2 (sh); it2.More(); it2.Next())
	  {  nb ++;  sh = it2.Value();  B.Add (C, sh);  }
      }
      else  {  nb ++;  B.Add (C,sh);  }
    }
    if (nb == 0) C.Nullify();
    else if (nb == 1) return sh;
    return C;
  }

  //   Egalite : OK;  Pseudo-Egalite : EDGE/WIRE ou FACE/SHELL
  if (typ == type) return shape;
  if (typ == TopAbs_EDGE && type == TopAbs_WIRE) {
    BRep_Builder B;
    TopoDS_Wire W;
    B.MakeWire (W);
    B.Add (W,shape);
    return W;
  }
  if (typ == TopAbs_FACE && type == TopAbs_SHELL) {
    BRep_Builder B;
    TopoDS_Shell S;
    B.MakeShell (S);
    B.Add (S,shape);
    return S;
  }

  //   Le reste : selon exploration
  if (!explore) {
    TopoDS_Shape nulsh;
    return nulsh;
  }

  //  Ici, on doit explorer
  //  SOLID + mode COMPOUND : reconduire les SHELLs
  if (typ == TopAbs_SOLID && compound) {
    TopoDS_Compound C;
    BRep_Builder B;
    B.MakeCompound (C);
    for (TopoDS_Iterator it(shape); it.More(); it.Next()) {
      sh0 = SortedCompound (it.Value(),type,explore,compound);
      if (sh0.IsNull()) continue;
      sh = sh0;
      nb ++;  B.Add (C,sh);
    }
    if (nb == 0) C.Nullify();
    else if (nb == 1) return sh;
    return C;
  }

  //  Exploration classique
  TopoDS_Compound CC;
  BRep_Builder BB;
  BB.MakeCompound(CC);
  //Standard_Integer iena = Standard_False; //szv#4:S4163:12Mar99 unused
  for (TopExp_Explorer expl (shape,type); expl.More(); expl.Next()) {
    nb ++;  sh = expl.Current();
    BB.Add (CC,sh);
  }
  if (nb == 0) CC.Nullify();
  else if (nb == 1) return sh;
  return CC;
}

//=======================================================================
//function : DispatchList
//purpose  : 
//=======================================================================

void ShapeExtend_Explorer::DispatchList (const Handle(TopTools_HSequenceOfShape)& list,
					 Handle(TopTools_HSequenceOfShape)& vertices,
					 Handle(TopTools_HSequenceOfShape)& edges,
					 Handle(TopTools_HSequenceOfShape)& wires,
					 Handle(TopTools_HSequenceOfShape)& faces,
					 Handle(TopTools_HSequenceOfShape)& shells,
					 Handle(TopTools_HSequenceOfShape)& solids,
					 Handle(TopTools_HSequenceOfShape)& compsols,
					 Handle(TopTools_HSequenceOfShape)& compounds) const
{
  if (list.IsNull()) return;
  if (vertices.IsNull())  vertices  = new TopTools_HSequenceOfShape();
  if (edges.IsNull())     edges     = new TopTools_HSequenceOfShape();
  if (wires.IsNull())     wires     = new TopTools_HSequenceOfShape();
  if (faces.IsNull())     faces     = new TopTools_HSequenceOfShape();
  if (shells.IsNull())    shells    = new TopTools_HSequenceOfShape();
  if (solids.IsNull())    solids    = new TopTools_HSequenceOfShape();
  if (compsols.IsNull())  compsols  = new TopTools_HSequenceOfShape();
  if (compounds.IsNull()) compounds = new TopTools_HSequenceOfShape();

  Standard_Integer i,nb = list->Length();
  for (i = 1; i <= nb; i ++) {
    TopoDS_Shape sh = list->Value(i);
    if (sh.IsNull()) continue;
    switch (sh.ShapeType()) {
      case TopAbs_VERTEX    : vertices->Append(sh); break;
      case TopAbs_EDGE      : edges->Append(sh); break;
      case TopAbs_WIRE      : wires->Append(sh); break;
      case TopAbs_FACE      : faces->Append(sh); break;
      case TopAbs_SHELL     : shells->Append(sh); break;
      case TopAbs_SOLID     : solids->Append(sh); break;
      case TopAbs_COMPSOLID : compsols->Append(sh); break;
      case TopAbs_COMPOUND  : compounds->Append(sh); break;
      default : break;
    }
  }
}
