// Created on: 1997-01-06
// Created by: Yves FRICAUD
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


#include <TDF_LabelList.hxx>
#include <TNaming_Tool.ixx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_NewShapeIterator.hxx>
#include <TNaming_OldShapeIterator.hxx>
#include <TNaming_Iterator.hxx>
#include <TNaming_RefShape.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopTools_MapIteratorOfMapOfShape.hxx>

#include <Standard_NoSuchObject.hxx>

#define BUC60862

#ifdef BUC60862
#include <TNaming_Naming.hxx>
#include <TNaming_ListOfNamedShape.hxx>
#include <TDF_AttributeMap.hxx>
#include <TDF_Tool.hxx>
#include <TDF_MapIteratorOfAttributeMap.hxx>
#include <TopExp_Explorer.hxx>
#include <TNaming_ListIteratorOfListOfNamedShape.hxx>
#endif

//=======================================================================
//function : LastModif 
//purpose  : 
//=======================================================================

static void LastModif(      TNaming_NewShapeIterator& it,
		      const TopoDS_Shape&             S,
		            TopTools_MapOfShape&      MS,
		      const TDF_LabelMap&             Updated,
		            TDF_LabelList&            Deleted)
{ 
  Standard_Boolean YaModif = Standard_False;
  for (; it.More(); it.Next()) {
    const TDF_Label&    Lab = it.Label();
    if (!Updated.Contains(Lab)) continue;
    
    if (it.IsModification()) {
      YaModif = Standard_True;
      TNaming_NewShapeIterator it2(it);
      if (!it2.More()) {
	const TopoDS_Shape& S1   = it.Shape();
	if (S1.IsNull()) {
	  Deleted.Append(Lab);
	}
	else {
	  MS.Add (S1);  // Modified
	}
      }
      else
	LastModif(it2,it.Shape(),MS,Updated,Deleted);
    }
  }
  if (!YaModif) 
    MS.Add(S);  
}

//=======================================================================
//function : LastModif 
//purpose  : 
//=======================================================================

static void LastModif(TNaming_NewShapeIterator& it,
		      TopTools_MapOfShape&      MS,
		      const TopoDS_Shape&       S,
		      TDF_LabelList&            Deleted)
{
  Standard_Boolean YaModif = Standard_False;
  for (; it.More(); it.Next()) {
    const TDF_Label&    Lab = it.Label();
    if (it.IsModification()) {
      YaModif = Standard_True;
      TNaming_NewShapeIterator it2(it);
      if (!it2.More()) {
	const TopoDS_Shape& S1   = it.Shape();
	if (S1.IsNull()) {
	  Deleted.Append(Lab);
	}
	else {
	  MS.Add (S1);  // Modified
	}
      }
      else 
	LastModif(it2,MS,it.Shape(), Deleted);
    }
  }
  if (!YaModif) 
    MS.Add(S);
}

//=======================================================================
//function : MakeShape
//purpose  : 
//=======================================================================

static TopoDS_Shape MakeShape (const TopTools_MapOfShape& MS) 
{  
  if (!MS.IsEmpty ()) {
    TopTools_MapIteratorOfMapOfShape it(MS);
    if (MS.Extent() == 1) {
      return it.Key();
    }
    else {
      TopoDS_Compound C;
      BRep_Builder B;
      B.MakeCompound(C);
      for (; it.More(); it.Next()){ 
	B.Add(C,it.Key());
      }
      return C;
    }
  }
  return TopoDS_Shape();  
}

//=======================================================================
//function : GetShape
//purpose  : 
//=======================================================================

TopoDS_Shape TNaming_Tool::GetShape(const Handle(TNaming_NamedShape)& NS)
{  
  TNaming_Iterator itL (NS);
  TopTools_MapOfShape  MS;
  if(NS->Evolution() == TNaming_SELECTED) {
    for (; itL.More(); itL.Next()) {
      if(!itL.NewShape().IsNull()) {
	if(itL.NewShape().ShapeType() != TopAbs_VERTEX &&
	   !itL.OldShape().IsNull() && itL.OldShape().ShapeType() == TopAbs_VERTEX) {
	  const TopoDS_Shape& aS = itL.NewShape().Oriented(itL.OldShape().Orientation());
	  MS.Add(aS);
	} else
	  MS.Add(itL.NewShape());
      }
    }
  } else 
    for (; itL.More(); itL.Next()) {
      if (!itL.NewShape().IsNull()) MS.Add(itL.NewShape());      
    }
  return MakeShape(MS);
}

//=======================================================================
//function : InitialShape
//purpose  : 
//=======================================================================

TopoDS_Shape TNaming_Tool::OriginalShape (const Handle(TNaming_NamedShape)& NS)
{
  TNaming_Iterator itL (NS);
  TopTools_MapOfShape  MS;
  for (; itL.More(); itL.Next()) {
    MS.Add(itL.OldShape());
  }
  return MakeShape(MS);
}  

//=======================================================================
static void ApplyOrientation (TopTools_MapOfShape& MS, 
			      const TopAbs_Orientation OrientationToApply)
{
 if (!MS.IsEmpty ()) {
   TopTools_MapOfShape aMS;
   aMS.Assign(MS);
   TopTools_MapIteratorOfMapOfShape it(aMS);
   for (; it.More(); it.Next()) {
     if(it.Key().Orientation() != OrientationToApply) {
       TopoDS_Shape aS = it.Key();
       MS.Remove(aS);
       aS.Orientation(OrientationToApply);
       MS.Add(aS);
     }  
   }
 }
}

//=======================================================================
//function : CurrentShape
//purpose  : 
//=======================================================================

TopoDS_Shape TNaming_Tool::CurrentShape(const Handle(TNaming_NamedShape)& Att)
{ 
  TopTools_MapOfShape MS;
  TDF_LabelList Deleted;

  TNaming_Iterator itL (Att);
  for (; itL.More(); itL.Next()) {
    const TopoDS_Shape& S = itL.NewShape();
    if (S.IsNull()) continue;
    Standard_Boolean YaOrientationToApply(Standard_False);
    TopAbs_Orientation OrientationToApply(TopAbs_FORWARD);
    if(Att->Evolution() == TNaming_SELECTED) {
      if (itL.More() && itL.NewShape().ShapeType() != TopAbs_VERTEX &&
	  !itL.OldShape().IsNull() && itL.OldShape().ShapeType() == TopAbs_VERTEX) {
	YaOrientationToApply = Standard_True;
	OrientationToApply = itL.OldShape().Orientation();
      }
    }
    TNaming_NewShapeIterator it(itL);
    if (!it.More()) {
	MS.Add(S);
    }
    else {
//      LastModif(it, MS, S, Deleted);
      TopTools_MapOfShape MS2;  // to be optimized later
      LastModif(it, MS2, S, Deleted);
      if (YaOrientationToApply) ApplyOrientation (MS2, OrientationToApply);
      for (TopTools_MapIteratorOfMapOfShape itMS2(MS2); itMS2.More();itMS2.Next()) 
	MS.Add(itMS2.Key());
    }
  }
  return MakeShape (MS);
}

//=======================================================================
//function : CurrentShape
//purpose  : 
//=======================================================================
TopoDS_Shape TNaming_Tool::CurrentShape(const Handle(TNaming_NamedShape)& Att,
					const TDF_LabelMap&           Updated)
{  
  TDF_Label Lab = Att->Label();

  TopTools_MapOfShape MS;
  TDF_LabelList Deleted;
  
  if (!Updated.Contains(Lab)) {
    return TopoDS_Shape();
  }

  TNaming_Iterator itL (Att);
  for (; itL.More(); itL.Next()) {
    const TopoDS_Shape& S = itL.NewShape();
    if (S.IsNull()) continue;
    Standard_Boolean YaOrientationToApply(Standard_False);
    TopAbs_Orientation OrientationToApply(TopAbs_FORWARD);
    if(Att->Evolution() == TNaming_SELECTED) {
      if (itL.More() && itL.NewShape().ShapeType() != TopAbs_VERTEX &&
	  !itL.OldShape().IsNull() && itL.OldShape().ShapeType() == TopAbs_VERTEX) {
	YaOrientationToApply = Standard_True;
	OrientationToApply = itL.OldShape().Orientation();
      }
    }
    TNaming_NewShapeIterator it(itL);
    if (!it.More()) {
      MS.Add(S);
    }
    else {
//      LastModif(it, S, MS, Updated, Deleted);
      TopTools_MapOfShape MS2; // to be optimized later
      LastModif(it, S, MS2, Updated, Deleted);
      if (YaOrientationToApply) ApplyOrientation (MS2, OrientationToApply);
      for (TopTools_MapIteratorOfMapOfShape itMS2(MS2); itMS2.More();itMS2.Next()) 
	MS.Add(itMS2.Key());
    }
  }
  return MakeShape (MS);
}

//=======================================================================
//function : CurrentNamedShape
//purpose  : 
//=======================================================================
Handle(TNaming_NamedShape) TNaming_Tool::CurrentNamedShape(const Handle(TNaming_NamedShape)& Att,
							   const TDF_LabelMap&           Updated)
{
  TopoDS_Shape CS = CurrentShape(Att,Updated);
  if (CS.IsNull()) {
    Handle(TNaming_NamedShape) NS;
    return NS;
  }
  return NamedShape(CS,Att->Label());
}

//=======================================================================
//function : CurrentNamedShape
//purpose  : 
//=======================================================================
Handle(TNaming_NamedShape) TNaming_Tool::CurrentNamedShape(const Handle(TNaming_NamedShape)& Att)

{
  TopoDS_Shape CS = CurrentShape(Att);
  if (CS.IsNull()) {
    Handle(TNaming_NamedShape) NS;
    return NS;
  }
  return NamedShape(CS,Att->Label());
}

//=======================================================================
//function : FindModifUntil
//purpose  : 
//=======================================================================

static void FindModifUntil (TNaming_NewShapeIterator&         it,
			    TopTools_MapOfShape&              MS,
			    const Handle(TNaming_NamedShape)& Context)
{ 
  for (; it.More(); it.Next()) {
    if (!it.Shape().IsNull()) {
      if (it.NamedShape() == Context) {
	MS.Add(it.Shape());
      }
      else {
	TNaming_NewShapeIterator it2(it);
	FindModifUntil (it2,MS,Context);
      }
    }
  }
}

//=======================================================================
//function : GeneratedShape
//purpose  : 
//=======================================================================
TopoDS_Shape TNaming_Tool::GeneratedShape(const TopoDS_Shape&               S,
					  const Handle(TNaming_NamedShape)& Generation)

{  
  TopTools_MapOfShape MS;
  Handle(TNaming_UsedShapes) US;
  Generation->Label().Root().FindAttribute(TNaming_UsedShapes::GetID(),US);
  
  for (TNaming_NewShapeIterator it(S,US);  it.More(); it.Next()) {
    if (!it.Shape().IsNull() && it.NamedShape() == Generation) {
      MS.Add(it.Shape());
    }
  }
  if (MS.IsEmpty()) {
    TNaming_NewShapeIterator it2(S,US);
    FindModifUntil (it2,MS,Generation);
  }
  return MakeShape (MS);
}

//=======================================================================
//function : FirstOlds
//purpose  : 
//=======================================================================
void TNaming_Tool::FirstOlds (const Handle(TNaming_UsedShapes)& US,
			      const TopoDS_Shape&         S,
			      TNaming_OldShapeIterator&  it,
			      TopTools_MapOfShape&       MS,
			      TDF_LabelList&          Labels) 
{  
  Standard_Integer TransDef;
  Standard_Boolean YaModif = 0;

  for (; it.More(); it.Next()) {
    if (it.IsModification()) {
      YaModif = 1;
      TNaming_OldShapeIterator it2(it);
      if (!it2.More()) { 
	Labels.Append(TNaming_Tool::Label(US,it.Shape(),TransDef));
	MS.Add (it.Shape()); 
      }
      else {
	FirstOlds(US,it.Shape(),it2,MS,Labels);
      }
    }
  }
  if (!YaModif) MS.Add(S);
}

//=======================================================================
//function : InitialShape
//purpose  : 
//=======================================================================

TopoDS_Shape TNaming_Tool::InitialShape(const TopoDS_Shape&  S,
					const TDF_Label&     Acces,
					TDF_LabelList&       Labels) 
{
  Handle(TNaming_UsedShapes) US;
  Acces.Root().FindAttribute(TNaming_UsedShapes::GetID(),US);
  TopoDS_Shape Res;

  if (!TNaming_Tool::HasLabel(US,S)) return Res;

  Standard_Integer Transdef;
  Label(US,S,Transdef); 
  TopTools_MapOfShape MS;
  TNaming_OldShapeIterator it(S,Transdef,US);
  if (!it.More()) {
    return S;
  }
  else {
    FirstOlds(US,S,it,MS,Labels);
  }
  return MakeShape(MS);
}



//=======================================================================
//function : Back
//purpose  : 
//=======================================================================

static void Back (const Handle(TNaming_NamedShape)& NS,
		        TNaming_MapOfNamedShape&    MNS)
{  
  for (TNaming_Iterator it(NS); it.More(); it.Next()) {
    if (it.NewShape().IsNull()) continue;
    for (TNaming_OldShapeIterator Oldit(it); Oldit.More(); Oldit.Next()) {
      const TopoDS_Shape& OS = Oldit.Shape();
      if (!OS.IsNull()) {
	Handle(TNaming_NamedShape) NOS = TNaming_Tool::NamedShape(OS,NS->Label());
	// Continue de remonter
	if (!NOS.IsNull()) { 
	  if (MNS.Add(NOS)) Back (NOS,MNS);
	}
      }
    }
  }
}

//=======================================================================
//function : Collect
//purpose  : 
//=======================================================================

void TNaming_Tool::Collect(const Handle(TNaming_NamedShape)& NS,
			         TNaming_MapOfNamedShape&    MNS,
			   const Standard_Boolean            OnlyModif)
{
  MNS.Add(NS);
  Back   (NS,MNS);

  for (TNaming_Iterator it(NS); it.More(); it.Next()) {
    if  (it.NewShape().IsNull()) continue;
    for (TNaming_NewShapeIterator NewIt(it); NewIt.More(); NewIt.Next()) {
      if (!OnlyModif || NewIt.IsModification()) {
	// Continue la descente
	Collect(NewIt.NamedShape(),MNS,OnlyModif);
      }
    }
  }
}


// Pour DEBUGGER 
#ifdef DEB

//=======================================================================
//function : TNamingTool_Label
//purpose  : 
//=======================================================================
void TNamingTool_DumpLabel (const TopoDS_Shape& S,
			    const TDF_Label&    Acces)
{
  Handle(TNaming_NamedShape) NS = TNaming_Tool::NamedShape(S,Acces);
  NS->Label().EntryDump(cout);
  cout<<endl;
}

#include <BRepTools.hxx>
//=======================================================================
//function : 
//purpose  : 
//=======================================================================
void TNamingTool_Write (const TopoDS_Shape& S,
			const Standard_CString File)
{
  BRepTools::Write (S,File);  
}

#endif


#ifdef BUC60862
//=======================================================================
//function : FindShape
//purpose  : ANaming
//=======================================================================

void TNaming_Tool::FindShape(const TDF_LabelMap&               Valid,
			     const TDF_LabelMap&               /*Forbiden*/,
			     const Handle(TNaming_NamedShape)& Arg,
			     TopoDS_Shape&                     S)
{
  if (!Valid.IsEmpty() && !Valid.Contains(Arg->Label())) return;
  if (Arg.IsNull() || Arg->IsEmpty()) return;
  
  // Which type of shape is being expected?
  Handle(TNaming_Naming) aNaming;
  if (!Arg->FindAttribute(TNaming_Naming::GetID(), aNaming)) {
#ifdef DEB
//    cout<<"TNaming_Tool::FindShape(): Naming attribute hasn't been found attached at the Argument label"<<endl;
#endif
    return;
  }

  // Looking for sub shapes of the result shape
  TopTools_MapOfShape subShapes;
  TopExp_Explorer anExpl(Arg->Get(), (TopAbs_ShapeEnum)((int)(aNaming->GetName().ShapeType()) + 1));
  for (; anExpl.More(); anExpl.Next()) subShapes.Add(anExpl.Current());
#ifdef DEB
//  cout<<"TNaming_Tool::FindShape(): Nb of sub shapes = "<<subShapes.Extent()<<endl;
#endif

  // Looking for external arguments:
  TNaming_ListOfNamedShape extArgs;
  TDF_AttributeMap outRefs;
  TDF_Tool::OutReferences(Arg->Label(), outRefs);
  if (outRefs.IsEmpty()) {
#ifdef DEB
//    cout<<"TNaming_Tool::FindShape(): No out references have been found"<<endl;
#endif
    return;
  }
  for (TDF_MapIteratorOfAttributeMap itr(outRefs); itr.More(); itr.Next()) {
    if (itr.Key()->DynamicType() == STANDARD_TYPE(TNaming_NamedShape)) {
#ifdef DEB
//      Standard_Integer nbExtArgs = extArgs.Extent();
#endif
      const Handle(TNaming_NamedShape)& anExtArg = Handle(TNaming_NamedShape)::DownCast(itr.Key());
      const Handle(TNaming_NamedShape)& aCurrentExtArg = TNaming_Tool::CurrentNamedShape(anExtArg);
      if (!aCurrentExtArg.IsNull() && !aCurrentExtArg->IsEmpty())
	extArgs.Append(aCurrentExtArg);
#ifdef DEB
//      if (extArgs.Extent() - 1 == nbExtArgs) {
//	cout<<"TNaming_Tool::FindShape(): An external reference has been found at ";
//	itr.Key()->Label().EntryDump(cout); cout<<endl;
//      }
#endif
    }
  }

  // The iterator on external arguments:
  TNaming_ListIteratorOfListOfNamedShape extArgsIterator (extArgs);
  for(; extArgsIterator.More(); extArgsIterator.Next()) {
    Handle(TNaming_NamedShape) anExtArg = extArgsIterator.Value();

    // Looking for context:
    Handle(TNaming_NamedShape) aContextNS;
    if (anExtArg->Label().Father().IsNull() ||
	!anExtArg->Label().Father().FindAttribute(TNaming_NamedShape::GetID(), aContextNS)) {
      aContextNS = anExtArg;
// #ifdef DEB
//       cout<<"TNaming_Tool::FindShape(): A context shape hasn't been found at the father label of the external argument"<<endl;
// #endif
//       continue;
    }

#ifdef DEB
//    cout<<"TNaming_Tool::FindShape(): Searching in the external reference ";
//    aContextNS->Label().EntryDump(cout); cout<<"  ";
#endif
    
    // Lets find the sub shape of the context which coincides with our sub shapes (subShapes map):
    TopExp_Explorer explC(aContextNS->Get(), aNaming->GetName().ShapeType()), explSubC;
    for (; explC.More(); explC.Next()) {
      Standard_Integer  DoesCoincide = 0;
      const TopoDS_Shape& possibleResult = explC.Current();
      TopTools_MapOfShape subShapesOfResult;
      for (explSubC.Init(possibleResult, (TopAbs_ShapeEnum)((int)(aNaming->GetName().ShapeType()) + 1)); 
	   explSubC.More(); explSubC.Next()) {
	subShapesOfResult.Add(explSubC.Current());
      }
      if (subShapesOfResult.Extent() != subShapes.Extent()) continue;
      for (TopTools_MapIteratorOfMapOfShape itrR(subShapesOfResult); itrR.More(); itrR.Next()) {
	for (TopTools_MapIteratorOfMapOfShape itr1(subShapes); itr1.More(); itr1.Next()) {
	  if (itrR.Key().IsSame(itr1.Key())) {
	    DoesCoincide++; //cout<<".";
	    break;
	  }
	}
      }
      if (DoesCoincide == subShapes.Extent()) {
#ifdef DEB
//	cout<<"TNaming_Tool::FindShape(): Found! ";
#endif
	S = possibleResult;
	break;
      }
    }

    if (!S.IsNull()) break;
#ifdef DEB
//    cout<<endl;
#endif

  }

#ifdef DEB
  if (S.IsNull()) {
    cout<<"TNaming_Tool::FindShape(): There hasn't been found a sub shape of the context shape coinciding with the sub shapes of naming"<<endl;
  }
#endif
      
}
#endif
