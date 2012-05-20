// Created on: 1999-02-11
// Created by: Pavel DURANDIN
// Copyright (c) 1999-1999 Matra Datavision
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



#include <Interface_Macros.hxx>
#include <STEPSelections_Counter.ixx>
#include <StepShape_ShapeDefinitionRepresentation.hxx>
#include <Interface_EntityIterator.hxx>
#include <Interface_Graph.hxx>
#include <StepShape_ContextDependentShapeRepresentation.hxx>
#include <StepShape_FacetedBrep.hxx>
#include <StepShape_BrepWithVoids.hxx>
#include <StepShape_ClosedShell.hxx>
#include <StepShape_OrientedClosedShell.hxx>
#include <StepShape_ShellBasedSurfaceModel.hxx>
#include <StepShape_Shell.hxx>
#include <StepShape_OpenShell.hxx>
#include <StepShape_FacetedBrepAndBrepWithVoids.hxx>
#include <StepRepr_MappedItem.hxx>
#include <StepShape_FaceSurface.hxx>
#include <StepRepr_RepresentationRelationship.hxx>
#include <StepRepr_ShapeRepresentationRelationship.hxx>
#include <STEPConstruct_Assembly.hxx>
#include <StepShape_ShapeRepresentation.hxx>
#include <StepShape_GeometricCurveSet.hxx>
#include <StepShape_GeometricSetSelect.hxx>
#include <StepBasic_ProductRelatedProductCategory.hxx>
#include <StepGeom_CompositeCurveSegment.hxx>
#include <StepRepr_RepresentationMap.hxx>

STEPSelections_Counter::STEPSelections_Counter()
{
  myNbFaces = 0;
  myNbShells = 0;
  myNbSolids = 0;
  myNbWires = 0;
  myNbEdges =0;
}

void STEPSelections_Counter::Count(const Interface_Graph& graph,
				   const Handle(Standard_Transient)& start)
{
  if(start.IsNull()) return;
  
  if (start->IsKind(STANDARD_TYPE(StepBasic_ProductRelatedProductCategory))) return;
  
  if (start->IsKind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation))) {
    DeclareAndCast(StepShape_ShapeDefinitionRepresentation,sdr,start);
    Count(graph,sdr->UsedRepresentation());
    Interface_EntityIterator subs = graph.Shareds(start);
    for (subs.Start(); subs.More(); subs.Next()) {
      DeclareAndCast(StepShape_ContextDependentShapeRepresentation,anitem,subs.Value());
      if (anitem.IsNull()) continue;
      Count(graph,anitem);
    }
    return;
  }
  
  if (start->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation))) {
    DeclareAndCast(StepShape_ShapeRepresentation,sr,start);
    Standard_Integer nb = sr->NbItems();
    for (Standard_Integer i = 1; i <= nb; i++) {
      Handle(StepRepr_RepresentationItem) anitem = sr->ItemsValue(i);
      Count(graph,anitem);
    }
    return;
  }
    
  if (start->IsKind(STANDARD_TYPE(StepShape_FacetedBrep))) {
    DeclareAndCast(StepShape_FacetedBrep,fbr,start);
    myMapOfSolids.Add(start);
    myNbSolids++;
    AddShell(fbr->Outer());
    return;
  }
  
  if (start->IsKind(STANDARD_TYPE(StepShape_BrepWithVoids))) {
    DeclareAndCast(StepShape_BrepWithVoids,brwv,start);
    myMapOfSolids.Add(start);
    myNbSolids++;
    AddShell(brwv->Outer());
    Standard_Integer nbvoids = brwv->NbVoids();
    for(Standard_Integer i = 1; i <= nbvoids; i++)
      AddShell(brwv->VoidsValue(i));
    return;
  }
  
  if (start->IsKind(STANDARD_TYPE(StepShape_ManifoldSolidBrep))) {
    DeclareAndCast(StepShape_ManifoldSolidBrep,msbr,start);
    myMapOfSolids.Add(start);
    myNbSolids++;
    AddShell(msbr->Outer());
    return;
  }
  
  if (start->IsKind(STANDARD_TYPE(StepShape_ShellBasedSurfaceModel))) {
    DeclareAndCast(StepShape_ShellBasedSurfaceModel,sbsm,start);
    Standard_Integer nbItems = sbsm->NbSbsmBoundary();
    for(Standard_Integer i = 1; i <= nbItems; i++) {
      Handle(StepShape_OpenShell) osh = sbsm->SbsmBoundaryValue(i).OpenShell();
      if(!osh.IsNull()) AddShell(osh);
      Handle(StepShape_ClosedShell) csh = sbsm->SbsmBoundaryValue(i).ClosedShell();
      if(!csh.IsNull()) AddShell(csh);
    }
    return;  
  }
  
  if (start->IsKind(STANDARD_TYPE(StepShape_FacetedBrepAndBrepWithVoids))) {
    DeclareAndCast(StepShape_FacetedBrepAndBrepWithVoids,fbwv,start);
    myMapOfSolids.Add(start);
    myNbSolids++;
    AddShell(fbwv->Outer());
    Standard_Integer nbvoids = fbwv->NbVoids();
    for(Standard_Integer i = 1; i <= nbvoids; i++)
      AddShell(fbwv->VoidsValue(i));
    return;
  }
  
  if (start->IsKind(STANDARD_TYPE(StepShape_GeometricSet))) {
    DeclareAndCast(StepShape_GeometricSet,gs,start);
    Standard_Integer nbElem = gs->NbElements();
    for (Standard_Integer i = 1; i <= nbElem ; i++) {
      StepShape_GeometricSetSelect aGSS = gs->ElementsValue(i);
      Handle(Standard_Transient) ent = aGSS.Value();
      Handle(StepGeom_CompositeCurve) ccurve = Handle(StepGeom_CompositeCurve)::DownCast(ent);
      if(!ccurve.IsNull()) {
	myNbWires++;
	myMapOfWires.Add(ccurve);
	AddCompositeCurve(ccurve);
      } else 
	if(ent->IsKind(STANDARD_TYPE(StepGeom_Curve))) {
	  myNbEdges++;
	  myMapOfEdges.Add(ent);
	} else
	  if(ent->IsKind(STANDARD_TYPE(StepGeom_Surface))) {
	    myNbFaces++;
	    myMapOfFaces.Add(ent);
	  }
    } 
  }

  
  if (start->IsKind(STANDARD_TYPE(StepRepr_MappedItem))) {
    DeclareAndCast(StepRepr_MappedItem,mi,start);
    Count(graph,mi->MappingTarget());
    Handle(StepRepr_RepresentationMap) map =  mi->MappingSource();
    if(map.IsNull()) return;
    Count(graph,map->MappedRepresentation());
    return;
  }
  
  if (start->IsKind(STANDARD_TYPE(StepShape_FaceSurface))) {
    myNbFaces++;
    myMapOfFaces.Add(start);
    return;
  }
  
  if (start->IsKind(STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation))) {
    DeclareAndCast(StepShape_ContextDependentShapeRepresentation,CDSR,start);
    DeclareAndCast(StepRepr_RepresentationRelationship,SRR,CDSR->RepresentationRelation());
    if ( SRR.IsNull() ) return ;
    
    Handle(StepRepr_Representation) rep;
    Standard_Boolean SRRReversed = STEPConstruct_Assembly::CheckSRRReversesNAUO ( graph.Model(), CDSR );
    if(SRRReversed)
      rep = SRR->Rep2();
    else
      rep = SRR->Rep1();
    
    Interface_EntityIterator subs = graph.Sharings(rep);
    for (subs.Start(); subs.More(); subs.Next()) 
      if ( subs.Value()->IsKind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation))) {
	DeclareAndCast(StepShape_ShapeDefinitionRepresentation,SDR,subs.Value());
	Count(graph,SDR);
      }
    //???
    return;
  }
  
  if (start->IsKind (STANDARD_TYPE(StepRepr_ShapeRepresentationRelationship)) ) {
    DeclareAndCast(StepRepr_ShapeRepresentationRelationship,und,start);
    for (Standard_Integer i = 1; i <= 2; i ++) {
      Handle(Standard_Transient) anitem;
      if (i == 1) anitem = und->Rep1();
      if (i == 2) anitem = und->Rep2();
      Count(graph,anitem);
    } 
    return;
  } 
}

void STEPSelections_Counter::Clear()
{
  myMapOfFaces.Clear();
  myMapOfShells.Clear();
  myMapOfSolids.Clear();
  myMapOfWires.Clear();
  myMapOfEdges.Clear();
  myNbFaces = 0;
  myNbShells = 0;
  myNbSolids = 0;
  myNbWires = 0;
  myNbEdges =0;
}

void STEPSelections_Counter::AddShell(const Handle(StepShape_ConnectedFaceSet)& cfs)
{
  myMapOfShells.Add(cfs);
  myNbShells++;
  Standard_Integer nbf = cfs->NbCfsFaces();
  for(Standard_Integer i =1; i <= nbf; i++)
    myMapOfFaces.Add(cfs->CfsFacesValue(i));
  myNbFaces+=nbf;
  return;
}

void STEPSelections_Counter::AddCompositeCurve(const Handle(StepGeom_CompositeCurve)& ccurve)
{
  Standard_Integer nbs = ccurve->NbSegments();
  for ( Standard_Integer i=1; i <= nbs; i++ ) {
//  #ifdef AIX   CKY : common code for all platforms: Handle() not Handle()&
    Handle(StepGeom_CompositeCurveSegment) ccs = ccurve->SegmentsValue ( i );
    Handle(StepGeom_Curve) crv = ccs->ParentCurve();

    if(crv->IsKind(STANDARD_TYPE(StepGeom_CompositeCurve)))
      AddCompositeCurve(Handle(StepGeom_CompositeCurve)::DownCast(crv));
    else {
      myNbEdges++;
      myMapOfEdges.Add(crv);
    }
  }
}
