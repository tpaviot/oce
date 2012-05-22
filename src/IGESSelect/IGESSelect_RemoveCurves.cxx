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

#include <IGESSelect_RemoveCurves.ixx>
#include <Interface_Macros.hxx>
#include <IGESGeom_TrimmedSurface.hxx>
#include <IGESGeom_BoundedSurface.hxx>
#include <IGESGeom_CurveOnSurface.hxx>
#include <IGESGeom_Boundary.hxx>
#include <IGESData_IGESEntity.hxx>
#include <IGESData_HArray1OfIGESEntity.hxx>
#include <IGESBasic_HArray1OfHArray1OfIGESEntity.hxx>
#include <TColStd_HArray1OfInteger.hxx>



IGESSelect_RemoveCurves::IGESSelect_RemoveCurves (const Standard_Boolean UV)
    : IGESSelect_ModelModifier (Standard_True)  ,  theUV (UV)    {  }

static Standard_Boolean  Edit
  (const Handle(Standard_Transient)& ent, const Standard_Boolean UV)
{
  Standard_Boolean res = Standard_False;
  DeclareAndCast(IGESGeom_TrimmedSurface,trsu,ent);
  if (!trsu.IsNull()) {
    res = Edit (trsu->OuterContour(),UV);
    Standard_Integer i,nb = trsu->NbInnerContours();
    for (i = 1; i <= nb; i ++) {
      res = res | Edit (trsu->InnerContour(i),UV);
    }
    return res;
  }

  DeclareAndCast(IGESGeom_BoundedSurface,bnsu,ent);
  if (!bnsu.IsNull()) {
    Standard_Integer i,nb = bnsu->NbBoundaries();
    for (i = 1; i <= nb; i ++) {
      res = res | Edit (bnsu->Boundary(i),UV);
    }
    return res;
  }

  DeclareAndCast(IGESGeom_CurveOnSurface,cons,ent);
  if (!cons.IsNull()) {
    Handle(IGESData_IGESEntity) cuv,c3d;
    cuv  = cons->CurveUV();
    c3d  = cons->Curve3D();
    Standard_Integer pref = cons->PreferenceMode();
    if (UV && !c3d.IsNull()) {
      if (cuv.IsNull() || c3d.IsNull()) return Standard_False;  // rien a faire
      cuv.Nullify();
      if (pref == 1) pref = 0;
      if (pref == 3) pref = 2;
    } else if (!cuv.IsNull()) {
      if (cuv.IsNull() || c3d.IsNull()) return Standard_False;  // rien a faire
      c3d.Nullify();
      if (pref == 2) pref = 0;
      if (pref == 3) pref = 1;
    }
    cons->Init ( cons->CreationMode(), cons->Surface(), cuv, c3d, pref );
    return Standard_True;
  }

  DeclareAndCast(IGESGeom_Boundary,bndy,ent);
  if (!bndy.IsNull()) {
    Standard_Integer i, nb = bndy->NbModelSpaceCurves();
    if (nb == 0) return Standard_False;
    Handle(IGESData_HArray1OfIGESEntity) arc3d = new IGESData_HArray1OfIGESEntity(1,nb);
    Handle(IGESBasic_HArray1OfHArray1OfIGESEntity) arcuv = new IGESBasic_HArray1OfHArray1OfIGESEntity (1,nb);
    Handle(TColStd_HArray1OfInteger) sens = new TColStd_HArray1OfInteger(1,nb);
    for (i = 1; i <= nb; i ++) {
      sens->SetValue (i,bndy->Sense(i));
      Handle(IGESData_HArray1OfIGESEntity) cuv = bndy->ParameterCurves(i);
      Handle(IGESData_IGESEntity) c3d = bndy->ModelSpaceCurve (i);
      if (UV) {
	if (cuv.IsNull() || c3d.IsNull()) continue;  // rien a faire
	cuv.Nullify();
	arcuv->SetValue (i,cuv);
      } else {
	if (cuv.IsNull() || c3d.IsNull()) continue;  // rien a faire
	c3d.Nullify();
	arc3d->SetValue (i,c3d);
	res = Standard_True;
      }
    }
//    Y a-t-il eu de la retouche ?
    Standard_Integer pref = bndy->PreferenceType();
    if (UV) {
      if (pref == 2) pref = 0;
      if (pref == 3) pref = 1;
    } else {
      if (pref == 1) pref = 0;
      if (pref == 3) pref = 2;
    }
    if (res) bndy->Init (bndy->BoundaryType(),pref,bndy->Surface(),arc3d,sens,arcuv);
    return res;
  }

  return Standard_False;
}


    void  IGESSelect_RemoveCurves::Performing
  (IFSelect_ContextModif& ctx,
   const Handle(IGESData_IGESModel)& target,
   Interface_CopyTool& TC) const
{
  for (ctx.Start(); ctx.More(); ctx.Next()) {
    if (Edit (ctx.ValueResult(),theUV) ) ctx.Trace ();
  }
}

    TCollection_AsciiString  IGESSelect_RemoveCurves::Label () const
{
  if (theUV) return TCollection_AsciiString ("Remove Curves UV on Face");
  else       return TCollection_AsciiString ("Remove Curves 3D on Face");
}
