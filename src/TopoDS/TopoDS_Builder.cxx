// Created on: 1991-04-09
// Created by: Remi LEQUETTE
// Copyright (c) 1991-1999 Matra Datavision
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


#include <TopoDS_Builder.ixx>

#include <TopoDS_TShape.hxx>
#include <TopoDS_TWire.hxx>
#include <TopoDS_TCompound.hxx>
#include <TopoDS_ListIteratorOfListOfShape.hxx>

#include <TopoDS_FrozenShape.hxx>
#include <TopoDS_UnCompatibleShapes.hxx>


//=======================================================================
//function : MakeShape
//purpose  : Make a Shape from a TShape
//=======================================================================

void TopoDS_Builder::MakeShape (TopoDS_Shape& S, 
                                const Handle(TopoDS_TShape)& T) const
{
  S.TShape(T);
  S.Location(TopLoc_Location());
  S.Orientation(TopAbs_FORWARD);
}


//=======================================================================
//function : Add
//purpose  : insert aComponent in aShape
//=======================================================================

void TopoDS_Builder::Add (TopoDS_Shape& aShape, 
                          const TopoDS_Shape& aComponent) const
{
  // From now the Component cannot be edited
  aComponent.TShape()->Free(Standard_False);

  // Note that freezing aComponent before testing if aShape is free
  // prevents from self-insertion
  // but aShape will be frozen when the Exception is raised
  if (aShape.Free())
  {
    static const unsigned int aTb[9]=
    {
      //COMPOUND to:
      (1<<((unsigned int)TopAbs_COMPOUND)),
      //COMPSOLID to:
      (1<<((unsigned int)TopAbs_COMPOUND)),
      //SOLID to:
      (1<<((unsigned int)TopAbs_COMPOUND)) |
      (1<<((unsigned int)TopAbs_COMPSOLID)),
      //SHELL to:
      (1<<((unsigned int)TopAbs_COMPOUND)) |
      (1<<((unsigned int)TopAbs_SOLID)),
      //FACE to:
      (1<<((unsigned int)TopAbs_COMPOUND)) |
      (1<<((unsigned int)TopAbs_SHELL)),
      //WIRE to:
      (1<<((unsigned int)TopAbs_COMPOUND)) |
      (1<<((unsigned int)TopAbs_FACE)),
      //EDGE to:
      (1<<((unsigned int)TopAbs_COMPOUND)) |
      (1<<((unsigned int)TopAbs_SOLID)) |
      (1<<((unsigned int)TopAbs_WIRE)),
      //VERTEX to:
      (1<<((unsigned int)TopAbs_COMPOUND)) |
      (1<<((unsigned int)TopAbs_SOLID)) |
      (1<<((unsigned int)TopAbs_FACE)) |
      (1<<((unsigned int)TopAbs_EDGE)),
      //SHAPE to:
      0
    };
    //
    const unsigned int iC=(unsigned int)aComponent.ShapeType();
    const unsigned int iS=(unsigned int)aShape.ShapeType();
    //
    if ((aTb[iC] & (1<<iS)) != 0) {
      TopoDS_ListOfShape& L = aShape.TShape()->ChangeShapes();
      L.Append(aComponent);
      TopoDS_Shape& S = L.Last();
      //
      // compute the relative Orientation
      if (aShape.Orientation() == TopAbs_REVERSED)
        S.Reverse();
      //
      // and the Relative Location
      const TopLoc_Location& aLoc=aShape.Location();
      if (!aLoc.IsIdentity())
        S.Move(aLoc.Inverted());
      //
      // Set the TShape as modified.
      aShape.TShape()->Modified(Standard_True);
    }
    else {
      TopoDS_UnCompatibleShapes::Raise("TopoDS_Builder::Add");
    }
  }
  else {
    TopoDS_FrozenShape::Raise("TopoDS_Buider::Add");
  }
}


//=======================================================================
//function : Remove
//purpose  : Remove a Shape from an other one
//=======================================================================

void TopoDS_Builder::Remove (TopoDS_Shape& aShape, 
                             const TopoDS_Shape& aComponent) const
{
  // check  if aShape  is  not Frozen
  TopoDS_FrozenShape_Raise_if (!aShape.Free(),"TopoDS_Builder::Remove");
  
  // compute the relative Orientation and Location of aComponent
  TopoDS_Shape S = aComponent;
  if (aShape.Orientation() == TopAbs_REVERSED)
    S.Reverse();
  S.Location(S.Location().Predivided(aShape.Location()));

  TopoDS_ListOfShape& L = aShape.TShape()->ChangeShapes();
  TopoDS_ListIteratorOfListOfShape It(L);
  while (It.More()) {
    if (It.Value() == S) {
      L.Remove(It);
      aShape.TShape()->Modified(Standard_True);
      break;
    }
    It.Next();
  }
}
