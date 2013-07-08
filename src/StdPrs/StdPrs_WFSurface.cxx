// Created on: 1995-08-04
// Created by: Modelistation
// Copyright (c) 1995-1999 Matra Datavision
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



#include <StdPrs_WFSurface.ixx>


#include <Graphic3d_Group.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>
#include <GeomAbs_IsoType.hxx>
#include <Prs3d_IsoAspect.hxx>
#include <Bnd_Box.hxx>
#include <Precision.hxx>
#include <BndLib_AddSurface.hxx>
#include <Adaptor3d_IsoCurve.hxx>
#include <StdPrs_Curve.hxx>
#include <TColgp_SequenceOfPnt.hxx>

#include <Prs3d_NListOfSequenceOfPnt.hxx>
#include <Prs3d_NListIteratorOfListOfSequenceOfPnt.hxx>


static void FindLimits(const Handle(Adaptor3d_HSurface)& surf ,
		       const Standard_Real             aLimit,
		       Standard_Real&                  UFirst,
		       Standard_Real&                  ULast,
		       Standard_Real&                  VFirst,
		       Standard_Real&                  VLast)
{
  UFirst = surf->FirstUParameter();
  ULast = surf->LastUParameter();
  VFirst = surf->FirstVParameter();
  VLast = surf->LastVParameter();
  
  Standard_Boolean UfirstInf = Precision::IsNegativeInfinite(UFirst);
  Standard_Boolean UlastInf  = Precision::IsPositiveInfinite(ULast);
  Standard_Boolean VfirstInf = Precision::IsNegativeInfinite(VFirst);
  Standard_Boolean VlastInf  = Precision::IsPositiveInfinite(VLast);
  
  if (UfirstInf || UlastInf) {
    gp_Pnt P1,P2;
    Standard_Real v;
    if (VfirstInf && VlastInf) 
      v = 0;
    else if (VfirstInf)
      v = VLast;
    else if (VlastInf)
      v = VFirst;
    else
      v = (VFirst + VLast) / 2;
    
    Standard_Real delta = aLimit * 2;

    if (UfirstInf && UlastInf) {
      do {
	delta /= 2;
	UFirst = - delta;
	ULast  =   delta;
	surf->D0(UFirst,v,P1);
	surf->D0(ULast,v,P2);
      } while (P1.Distance(P2) > aLimit);
    }
    else if (UfirstInf) {
      surf->D0(ULast,v,P2);
      do {
	delta /= 2;
	UFirst = ULast - delta;
	surf->D0(UFirst,v,P1);
      } while (P1.Distance(P2) > aLimit);
    }
    else if (UlastInf) {
      surf->D0(UFirst,v,P1);
      do {
	delta /= 2;
	ULast = UFirst + delta;
	surf->D0(ULast,v,P2);
      } while (P1.Distance(P2) > aLimit);
    }
  }

  if (VfirstInf || VlastInf) {
    gp_Pnt P1,P2;
    Standard_Real u = (UFirst + ULast) /2 ;

    Standard_Real delta = aLimit * 2;

    if (VfirstInf && VlastInf) {
      do {
	delta /= 2;
	VFirst = - delta;
	VLast  =   delta;
	surf->D0(u,VFirst,P1);
	surf->D0(u,VLast,P2);
      } while (P1.Distance(P2) > aLimit);
    }
    else if (VfirstInf) {
      surf->D0(u,VLast,P2);
      do {
	delta /= 2;
	VFirst = VLast - delta;
	surf->D0(u,VFirst,P1);
      } while (P1.Distance(P2) > aLimit);
    }
    else if (VlastInf) {
      surf->D0(u,VFirst,P1);
      do {
	delta /= 2;
	VLast = VFirst + delta;
	surf->D0(u,VLast,P2);
      } while (P1.Distance(P2) > aLimit);
    }
  }
}


//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void StdPrs_WFSurface::Add (const Handle(Prs3d_Presentation)& aPresentation,
			    const Handle(Adaptor3d_HSurface)&   aSurface,
			    const Handle(Prs3d_Drawer)&       aDrawer)
{
  
    Standard_Real  U1, U2, V1, V2;
    Standard_Real MaxP = aDrawer->MaximalParameterValue();

    FindLimits(aSurface, MaxP, U1, U2, V1, V2);

    Prs3d_NListOfSequenceOfPnt freeCurves; 
    Prs3d_NListOfSequenceOfPnt UIsoCurves; 
    Prs3d_NListOfSequenceOfPnt VIsoCurves; 
    TColgp_SequenceOfPnt Pnts;
    
    Standard_Boolean UClosed = aSurface->IsUClosed();
    Standard_Boolean VClosed = aSurface->IsVClosed();
      
    Standard_Real TheDeflection;
    Aspect_TypeOfDeflection TOD = aDrawer->TypeOfDeflection();    
    if (TOD == Aspect_TOD_RELATIVE) {
// On calcule la fleche en fonction des min max globaux de la piece:
       Bnd_Box Total;
       BndLib_AddSurface::Add(aSurface->Surface(),U1, U2, V1, V2, 0.,Total);
       Standard_Real m = aDrawer->MaximalChordialDeviation()/
	 aDrawer->DeviationCoefficient();
       Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
       Total.Get( aXmin, aYmin, aZmin, aXmax, aYmax, aZmax );
       if ( ! (Total.IsOpenXmin() || Total.IsOpenXmax() ))
	  m = Min ( m , Abs (aXmax-aXmin));
       if ( ! (Total.IsOpenYmin() || Total.IsOpenYmax() ))
	  m = Min ( m , Abs (aYmax-aYmin));
       if ( ! (Total.IsOpenZmin() || Total.IsOpenZmax() ))
	  m = Min ( m , Abs (aZmax-aZmin));

       TheDeflection = m * aDrawer->DeviationCoefficient();
    }
    else
      TheDeflection = aDrawer->MaximalChordialDeviation();  

    Adaptor3d_IsoCurve anIso;
    anIso.Load(aSurface);

    // Trace des frontieres.
    // *********************
    //
    if ( !(UClosed && VClosed) ) {
	
      (Prs3d_Root::CurrentGroup(aPresentation))->SetPrimitivesAspect
	(aDrawer->FreeBoundaryAspect()->Aspect());
      if ( !UClosed ) 
	{ 
	  anIso.Load(GeomAbs_IsoU,U1,V1,V2);
	  StdPrs_Curve::Add(aPresentation,anIso,TheDeflection, aDrawer, Pnts, Standard_False);
	  freeCurves.Append(Pnts);
	  Pnts.Clear();
	  anIso.Load(GeomAbs_IsoU,U2,V1,V2);
	  StdPrs_Curve::Add(aPresentation,anIso,TheDeflection, aDrawer, Pnts, Standard_False);
	  freeCurves.Append(Pnts);
	  Pnts.Clear();
	}
      if ( !VClosed )
	{
	  anIso.Load(GeomAbs_IsoV,V1,U1,U2);
	  StdPrs_Curve::Add(aPresentation,anIso,TheDeflection, aDrawer, Pnts, Standard_False);
	  freeCurves.Append(Pnts);
	  Pnts.Clear();
	  anIso.Load(GeomAbs_IsoV,V2,U1,U2);
	  StdPrs_Curve::Add(aPresentation,anIso,TheDeflection, aDrawer, Pnts, Standard_False);
	  freeCurves.Append(Pnts);
	  Pnts.Clear();
	}
    }
    //
    // Trace des isoparametriques.
    // ***************************
    //
    Standard_Integer fin = aDrawer->UIsoAspect()->Number();
    if ( fin != 0) {
      
      (Prs3d_Root::CurrentGroup(aPresentation))->SetPrimitivesAspect
	(aDrawer->UIsoAspect()->Aspect());
      
      Standard_Real du= UClosed ? (U2-U1)/fin : (U2-U1)/(1+fin);
      for (Standard_Integer i=1; i<=fin;i++){
	anIso.Load(GeomAbs_IsoU,U1+du*i,V1,V2);
	StdPrs_Curve::Add(aPresentation,anIso,TheDeflection, aDrawer, Pnts, Standard_False);
	UIsoCurves.Append(Pnts);
	Pnts.Clear();
      }
    }
    fin = aDrawer->VIsoAspect()->Number();
    if ( fin != 0) {
      
      (Prs3d_Root::CurrentGroup(aPresentation))->SetPrimitivesAspect
	(aDrawer->VIsoAspect()->Aspect());
      
      Standard_Real dv= VClosed ?(V2-V1)/fin : (V2-V1)/(1+fin);
      for (Standard_Integer i=1; i<=fin;i++){
	anIso.Load(GeomAbs_IsoV,V1+dv*i,U1,U2);
	StdPrs_Curve::Add(aPresentation,anIso,TheDeflection, aDrawer, Pnts, Standard_False);
	VIsoCurves.Append(Pnts);
	Pnts.Clear();
      }
    }
    
    Standard_Integer nbVertices = 0, nbBounds = 0; 
    //Draw surface via primitive array
    if(UIsoCurves.Size() > 0) {
      nbBounds = UIsoCurves.Size();
      Prs3d_NListIteratorOfListOfSequenceOfPnt It;
      for( It.Init(UIsoCurves); It.More(); It.Next())
	nbVertices += It.Value().Length();
      Handle(Graphic3d_ArrayOfPolylines) UIsoArray =
	new Graphic3d_ArrayOfPolylines(nbVertices,nbBounds);
      for( It.Init(UIsoCurves); It.More(); It.Next()) {
	TColgp_SequenceOfPnt Pnts;
	Pnts.Assign(It.Value());
	UIsoArray->AddBound(Pnts.Length());
	for(int i=1; i<=Pnts.Length(); i++)
	  UIsoArray->AddVertex(Pnts.Value(i));
      }      
      Handle(Graphic3d_Group) TheGroup = Prs3d_Root::NewGroup(aPresentation);
      TheGroup->SetPrimitivesAspect(aDrawer->UIsoAspect()->Aspect());
      TheGroup->AddPrimitiveArray(UIsoArray);
    }
    
    if(VIsoCurves.Size() > 0) {
      nbBounds = VIsoCurves.Size();
      Prs3d_NListIteratorOfListOfSequenceOfPnt It;
      for( It.Init(VIsoCurves); It.More(); It.Next())
	nbVertices += It.Value().Length();
      Handle(Graphic3d_ArrayOfPolylines) VIsoArray =
	new Graphic3d_ArrayOfPolylines(nbVertices,nbBounds);
      for( It.Init(VIsoCurves); It.More(); It.Next()) {
	TColgp_SequenceOfPnt Pnts;
	Pnts.Assign(It.Value());
	VIsoArray->AddBound(Pnts.Length());
	for(int i=1; i<=Pnts.Length(); i++)
	  VIsoArray->AddVertex(Pnts.Value(i));
      }
      Handle(Graphic3d_Group) TheGroup = Prs3d_Root::NewGroup(aPresentation);
      TheGroup->SetPrimitivesAspect(aDrawer->VIsoAspect()->Aspect());
      TheGroup->AddPrimitiveArray(VIsoArray);
    } 
    if(freeCurves.Size() > 0) {
      nbBounds = freeCurves.Size();
      Prs3d_NListIteratorOfListOfSequenceOfPnt It;
      for( It.Init(freeCurves); It.More(); It.Next())
	nbVertices += It.Value().Length();
      Handle(Graphic3d_ArrayOfPolylines) freeArray =
	new Graphic3d_ArrayOfPolylines(nbVertices,nbBounds);
      for( It.Init(freeCurves); It.More(); It.Next()) {
	TColgp_SequenceOfPnt Pnts;
	Pnts.Assign(It.Value());
	freeArray->AddBound(Pnts.Length());
	for(int i=1; i<=Pnts.Length(); i++)
	  freeArray->AddVertex(Pnts.Value(i));
      }
      Handle(Graphic3d_Group) TheGroup = Prs3d_Root::NewGroup(aPresentation);
      TheGroup->SetPrimitivesAspect(aDrawer->FreeBoundaryAspect()->Aspect());
      TheGroup->AddPrimitiveArray(freeArray);
    }
  }


