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

//szv#9:PRO19565:04Oct99 loss of rotation matrix corrected
#include <IGESData_ToolLocation.ixx>
#include <Interface_EntityIterator.hxx>
#include <Interface_Macros.hxx>
#include <IGESData_TransfEntity.hxx>
#include <IGESData_SingleParentEntity.hxx>
#include <IGESData_GeneralModule.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax3.hxx>
#include <Standard_DomainError.hxx>

#define TYPEFORASSOC 402

IGESData_ToolLocation::IGESData_ToolLocation (const Handle(IGESData_IGESModel)& amodel,
						const Handle(IGESData_Protocol)& protocol)
: thelib (protocol),
  therefs (0,amodel->NbEntities()),
  theassocs (0,amodel->NbEntities())
{
  theprec  = 1.e-05;
  themodel = amodel;
  therefs.Init(0);  theassocs.Init(0);
  Load();
}

void  IGESData_ToolLocation::Load ()
{
  // Pour chaque Entite, sauf Transf et Assoc (sauf SingleParent), on considere
  // ses "OwnShared" comme etant dependents
  Standard_Integer nb = themodel->NbEntities();
  for (Standard_Integer i = 1; i <= nb; i ++) {
    Handle(IGESData_IGESEntity) ent = themodel->Entity(i);
    if (ent->IsKind(STANDARD_TYPE(IGESData_TransfEntity))) continue;
    // Cas de SingleParentEntity
    if (ent->IsKind(STANDARD_TYPE(IGESData_SingleParentEntity))) {
      DeclareAndCast(IGESData_SingleParentEntity,assoc,ent);
      Standard_Integer nbc = assoc->NbChildren();
      Handle(IGESData_IGESEntity) parent = assoc->SingleParent();
      for (Standard_Integer j = 1; j <= nbc; j ++)
	SetParentAssoc(parent,assoc->Child(j));
      continue;
    }
    if (ent->TypeNumber() == TYPEFORASSOC) continue; // Assoc sauf SingleParent
    // Cas courant
    SetOwnAsDependent (ent); // qui opere
  }
}

void IGESData_ToolLocation::SetPrecision (const Standard_Real prec)
{  theprec = prec;  }

void IGESData_ToolLocation::SetReference (const Handle(IGESData_IGESEntity)& parent,
					  const Handle(IGESData_IGESEntity)& child)
{
  Standard_Integer np = themodel->Number(parent);
  Standard_Integer nc = themodel->Number(child);
  if (np == 0 || nc == 0) return;
  if (therefs(nc) > 0) np = -1;    // note ambigu
  therefs.SetValue(nc,np);
}

void IGESData_ToolLocation::SetParentAssoc (const Handle(IGESData_IGESEntity)& parent,
					    const Handle(IGESData_IGESEntity)& child)
{
  Standard_Integer np = themodel->Number(parent);
  Standard_Integer nc = themodel->Number(child);
  if (np == 0 || nc == 0) return;
  if (theassocs(nc) > 0) np = -1;    // note ambigu
  theassocs.SetValue(nc,np);
}

void  IGESData_ToolLocation::ResetDependences (const Handle(IGESData_IGESEntity)& child)
{
  Standard_Integer nc = themodel->Number(child);
  if (nc == 0) return;
  therefs.SetValue(nc,0);
  theassocs.SetValue(nc,0);
}

void  IGESData_ToolLocation::SetOwnAsDependent (const Handle(IGESData_IGESEntity)& ent)
{
  Handle(IGESData_GeneralModule) module;
  Standard_Integer CN;
  if (!thelib.Select(ent,module,CN)) return;
  Interface_EntityIterator list;
  module->OwnSharedCase(CN,ent,list);
  // Remarque : en toute rigueur, il faudrait ignorer les entites referencees
  // dont le SubordinateStatus vaut 0 ou 2 ...
  // Question : ce Status est-il toujours bien comme il faut ?
  for (list.Start(); list.More(); list.Next())
    SetReference (ent, GetCasted(IGESData_IGESEntity,list.Value()) );
}

//  #########################################################################
//  ########                        RESULTATS                        ########

Standard_Boolean  IGESData_ToolLocation::IsTransf
  (const Handle(IGESData_IGESEntity)& ent) const
{  return ent->IsKind(STANDARD_TYPE(IGESData_TransfEntity));  }

Standard_Boolean  IGESData_ToolLocation::IsAssociativity
  (const Handle(IGESData_IGESEntity)& ent) const
{  return (ent->TypeNumber() == TYPEFORASSOC);  }

Standard_Boolean  IGESData_ToolLocation::HasTransf
  (const Handle(IGESData_IGESEntity)& ent) const
{  return ent->HasTransf();  }

gp_GTrsf  IGESData_ToolLocation::ExplicitLocation
  (const Handle(IGESData_IGESEntity)& ent) const
{  return ent->Location();  }


Standard_Boolean  IGESData_ToolLocation::IsAmbiguous
  (const Handle(IGESData_IGESEntity)& ent) const
{
  Standard_Integer num = themodel->Number(ent);
  if (num == 0) return Standard_False;
  if (therefs(num) <  0 || theassocs(num) <  0) return Standard_True;
  if (therefs(num) != 0 && theassocs(num) != 0) return Standard_True;
  return Standard_False;
}

Standard_Boolean  IGESData_ToolLocation::HasParent
  (const Handle(IGESData_IGESEntity)& ent) const
{
  Standard_Integer num = themodel->Number(ent);
  if (num == 0) return Standard_False;
  if (therefs(num) <  0 || theassocs(num) <  0) Standard_DomainError::Raise
    ("IGESData_ToolLocation : HasParent");
  if (therefs(num) != 0 && theassocs(num) != 0) Standard_DomainError::Raise
    ("IGESData_ToolLocation : HasParent");
  if (therefs(num) != 0 || theassocs(num) != 0) return Standard_True;
  return Standard_False;
}

Handle(IGESData_IGESEntity)  IGESData_ToolLocation::Parent
  (const Handle(IGESData_IGESEntity)& ent) const
{
  Handle(IGESData_IGESEntity) parent;
  Standard_Integer num = themodel->Number(ent);
  if (num == 0) return parent;
  if (therefs(num) <  0 || theassocs(num) <  0) Standard_DomainError::Raise
    ("IGESData_ToolLocation : Parent");
  if (therefs(num) != 0 && theassocs(num) != 0) Standard_DomainError::Raise
    ("IGESData_ToolLocation : Parent");
  if (therefs(num)   != 0) parent = themodel->Entity (therefs   (num));
  if (theassocs(num) != 0) parent = themodel->Entity (theassocs (num));
  return parent;
}

Standard_Boolean  IGESData_ToolLocation::HasParentByAssociativity
  (const Handle(IGESData_IGESEntity)& ent) const
{
  Standard_Integer num = themodel->Number(ent);
  if (num == 0) return Standard_False;
  if (therefs(num) <  0 || theassocs(num) <  0) Standard_DomainError::Raise
    ("IGESData_ToolLocation : HasParentByAssociativity");
  if (therefs(num) != 0 && theassocs(num) != 0) Standard_DomainError::Raise
    ("IGESData_ToolLocation : HasParentByAssociativity");
  if (theassocs(num) != 0) return Standard_True;
  return Standard_False;
}

gp_GTrsf  IGESData_ToolLocation::ParentLocation
  (const Handle(IGESData_IGESEntity)& ent) const
{
  gp_GTrsf locat;    // par defaut, identite
  Handle(IGESData_IGESEntity) parent = Parent(ent);
  // Definition recursive
  if (!parent.IsNull()) locat = EffectiveLocation(parent);
  return locat;
}

gp_GTrsf  IGESData_ToolLocation::EffectiveLocation
  (const Handle(IGESData_IGESEntity)& ent) const
{
  gp_GTrsf locat  = ent->Location();
  // Combiner Transf et ParentLocation
  locat.PreMultiply (ParentLocation(ent));    // ne pas se tromper de sens !
  return locat;
}

Standard_Boolean  IGESData_ToolLocation::AnalyseLocation (const gp_GTrsf& loc,
							  gp_Trsf& result) const
{  return ConvertLocation (theprec,loc,result);  }

Standard_Boolean  IGESData_ToolLocation::ConvertLocation (const Standard_Real prec,
							  const gp_GTrsf& loc,
							  gp_Trsf& result,
							  const Standard_Real unit)
{
  if (result.Form() != gp_Identity) result = gp_Trsf();  // Identite forcee au depart
  // On prend le contenu de <loc>. Attention a l adressage
  gp_XYZ v1 ( loc.Value(1,1), loc.Value(1,2), loc.Value(1,3) );
  gp_XYZ v2 ( loc.Value(2,1), loc.Value(2,2), loc.Value(2,3) );
  gp_XYZ v3 ( loc.Value(3,1), loc.Value(3,2), loc.Value(3,3) );
  // A-t-on affaire a une similitude ?
  Standard_Real m1 = v1.Modulus();
  Standard_Real m2 = v2.Modulus();
  Standard_Real m3 = v3.Modulus();
  // D abord est-elle singuliere cette matrice ?
  if (m1 < prec || m2 < prec || m3 < prec) return Standard_False;
  Standard_Real mm = (m1+m2+m3)/3.; // voici la Norme moyenne, cf Scale
  if ( Abs(m1 - mm) > prec*mm ||
       Abs(m2 - mm) > prec*mm ||
       Abs(m3 - mm) > prec*mm ) return Standard_False;
  v1.Divide(m1);
  v2.Divide(m2);
  v3.Divide(m3);
  if ( Abs(v1.Dot(v2)) > prec ||
       Abs(v2.Dot(v3)) > prec ||
       Abs(v3.Dot(v1)) > prec ) return Standard_False;
  // Ici, Orthogonale et memes normes. En plus on l a Normee
  // Restent les autres caracteristiques :
  if (Abs(mm - 1.) > prec) result.SetScale(gp_Pnt(0,0,0),mm);
  gp_XYZ tp = loc.TranslationPart();
  if (unit != 1.) tp.Multiply(unit);
  if (tp.X() != 0. || tp.Y() != 0. || tp.Z() != 0.) result.SetTranslationPart(tp);
  // On isole le cas de l Identite (tellement facile et avantageux)
  if (v1.X() != 1. || v1.Y() != 0. || v1.Z() != 0. ||
      v2.X() != 0. || v2.Y() != 1. || v2.Z() != 0. ||
      v3.X() != 0. || v3.Y() != 0. || v3.Z() != 1. ) {
    // Pas Identite : vraie construction depuis un Ax3
    gp_Dir d1(v1);
    gp_Dir d2(v2);
    gp_Dir d3(v3);
    gp_Ax3 axes (gp_Pnt(0,0,0),d3,d1);
    d3.Cross(d1);
    if (d3.Dot(d2) < 0) axes.YReverse();
    gp_Trsf transf;
    transf.SetTransformation(axes);
    result *= transf; //szv#9:PRO19565:04Oct99
  }
  return Standard_True;
}
