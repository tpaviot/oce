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

#include <IGESSelect_SelectPCurves.ixx>
#include <IGESData_IGESEntity.hxx>
#include <IGESGeom_CurveOnSurface.hxx>
#include <IGESGeom_TrimmedSurface.hxx>
#include <IGESGeom_BoundedSurface.hxx>
#include <IGESGeom_Boundary.hxx>
#include <IGESBasic_Group.hxx>
#include <IGESSolid_ManifoldSolid.hxx>
#include <IGESSolid_Shell.hxx>
#include <IGESSolid_Face.hxx>
#include <IGESSolid_Loop.hxx>
#include <IGESSelect_SelectBasicGeom.hxx>

#include <Interface_Macros.hxx>

IGESSelect_SelectPCurves::IGESSelect_SelectPCurves
  (const Standard_Boolean basic)
    : IFSelect_SelectExplore (-1) , thebasic (basic)    {  }


    Standard_Boolean  IGESSelect_SelectPCurves::Explore
  (const Standard_Integer level, const Handle(Standard_Transient)& ent,
   const Interface_Graph& G, Interface_EntityIterator& explored) const
{
  DeclareAndCast(IGESData_IGESEntity,igesent,ent);
  if (igesent.IsNull()) return Standard_False;
  Standard_Integer igt = igesent->TypeNumber();

//   TrimmedSurface 144
  if (igt == 144) {
    DeclareAndCast(IGESGeom_TrimmedSurface,trs,ent);
      explored.AddItem(trs->OuterContour());
      Standard_Integer i, nb = trs->NbInnerContours();
      for (i = 1; i <= nb; i ++) explored.AddItem (trs->InnerContour(i));
    return Standard_True;
  }

//   CurveOnSurface 142
  if (igt == 142) {
    DeclareAndCast(IGESGeom_CurveOnSurface,crf,ent);
    explored.AddItem(crf->CurveUV());
    if (thebasic) IGESSelect_SelectBasicGeom::SubCurves (crf->CurveUV(),explored);
    return Standard_True;
  }

//   Boundary 141
  if (igt == 141) {
    DeclareAndCast(IGESGeom_Boundary,bnd,ent);
    Standard_Integer i, nb = bnd->NbModelSpaceCurves();
    for (i = 1; i <= nb; i ++) {
      Standard_Integer j,np = bnd->NbParameterCurves(i);
      for (j = 1; j <= np; j ++) {
	explored.AddItem (bnd->ParameterCurve(i,j));
      }
    }
    return (nb > 0);
  }

//   BoundedSurface 143
  if (igt == 143) {
    DeclareAndCast(IGESGeom_BoundedSurface,bns,ent);
    Standard_Integer i, nb = bns->NbBoundaries(); //szv#4:S4163:12Mar99 optimized
      for (i = 1; i <= nb; i ++) explored.AddItem (bns->Boundary(i));
      return (nb != 0);
    //return Standard_True; //szv#4:S4163:12Mar99 unreached
  }


//  Groups ... en dernier de la serie 402
  if (igt == 402) {
    DeclareAndCast(IGESBasic_Group,gr,ent);
    if (gr.IsNull()) return Standard_False;
    Standard_Integer i, nb = gr->NbEntities();
    for (i = 1; i <= nb; i ++)  explored.AddItem (gr->Entity(i));
    return Standard_True;
  }


//  ManifoldSolid 186  -> Shells
  if (igt == 186) {
    DeclareAndCast(IGESSolid_ManifoldSolid,msb,ent);
    explored.AddItem (msb->Shell());
    Standard_Integer i, nb = msb->NbVoidShells();
    for (i = 1; i <= nb; i ++)  explored.AddItem (msb->VoidShell(i));
    return Standard_True;
  }

//  Shell 514 -> Faces
  if (igt == 514) {
    DeclareAndCast(IGESSolid_Shell,sh,ent);
    Standard_Integer i, nb = sh->NbFaces();
    for (i = 1; i <= nb; i ++)  explored.AddItem (sh->Face(i));
    return Standard_True;
  }

//  Face 510 -> Loops
  if (igt == 510) {
    DeclareAndCast(IGESSolid_Face,fc,ent);
      Standard_Integer i, nb = fc->NbLoops();
      for (i = 1; i <= nb; i ++)  explored.AddItem (fc->Loop(i));
    return Standard_True;
  }

//  Loop 508 -> PCurves (enfin !)
  if (igt == 508) {
    DeclareAndCast(IGESSolid_Loop,lp,ent);
    Standard_Integer i, nb = lp->NbEdges();
    for (i = 1; i <= nb; i ++)  {
      Standard_Integer j, np = lp->NbParameterCurves(i);
      for (j = 1; j <= np; j ++) //szv#4:S4163:12Mar99 was bug
	explored.AddItem(lp->ParametricCurve(i,j));
    }
    return Standard_True;
  }

//   LES LIGNES : seult si en tant que pcurve : donc level >= 3
//   Lignes en general. Attention CopiousData, aux variantes "habillage"
  if (level < 3) return Standard_False;

  if (igt == 106) return (igesent->FormNumber() < 20);
  if ( (igt >= 100 && igt <= 106) || igt == 110 || igt == 112 || igt == 116 ||
      igt == 126 || igt == 130) return Standard_True;

//  Pas trouve
  return Standard_False;
}


    TCollection_AsciiString IGESSelect_SelectPCurves::ExploreLabel () const
{
  if (thebasic) return TCollection_AsciiString ("Basic PCurves");
  else return TCollection_AsciiString ("Global PCurves");
}
