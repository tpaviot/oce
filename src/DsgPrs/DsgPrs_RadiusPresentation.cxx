// Created on: 1995-03-01
// Created by: Arnaud BOUZY
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

//modified      20-feb-98 by <SZY>
//              Sergei Zaritchny

#include <DsgPrs_RadiusPresentation.ixx>
#include <gp_Lin.hxx>
#include <gp_Dir.hxx>
#include <gp_Circ.hxx>
#include <ElCLib.hxx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <Prs3d_Arrow.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_LengthAspect.hxx>
#include <Prs3d_Text.hxx>

#include <Graphic3d_Vertex.hxx>
#include <Graphic3d_AspectMarker3d.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Aspect_TypeOfLine.hxx>
#include <Aspect_TypeOfMarker.hxx>
#include <Aspect_AspectMarker.hxx>
#include <Quantity_Color.hxx>
#include <DsgPrs.hxx>
#include <Precision.hxx>
#include <gce_MakeLin.hxx>
#include <gce_MakeDir.hxx>


static Standard_Boolean DsgPrs_InDomain(const Standard_Real fpar,
                                        const Standard_Real lpar,
                                        const Standard_Real para)
{
  if (fpar >= 0.)
    return ((para >= fpar) && (para <= lpar));
  if (para >= (fpar+2.*M_PI)) return Standard_True;
  if (para <= lpar) return Standard_True;
  return Standard_False;
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void DsgPrs_RadiusPresentation::Add (const Handle(Prs3d_Presentation)& aPresentation,
				     const Handle(Prs3d_Drawer)& aDrawer,
				     const TCollection_ExtendedString& aText,
				     const gp_Pnt& AttachmentPoint,
				     const gp_Circ& aCircle,
				     const Standard_Real firstparam,
				     const Standard_Real lastparam,
				     const Standard_Boolean drawFromCenter,
				     const Standard_Boolean reverseArrow) 
{
  Standard_Real fpara = firstparam;
  Standard_Real lpara = lastparam;
  while (lpara > 2.*M_PI) {
    fpara -= 2.*M_PI;
    lpara -= 2.*M_PI;
  }
  Handle(Prs3d_LengthAspect) LA = aDrawer->LengthAspect();
  Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  Standard_Real parat = ElCLib::Parameter(aCircle,AttachmentPoint);
  gp_Pnt attpoint = AttachmentPoint;
  Standard_Boolean otherside = Standard_False;
  if ( !DsgPrs_InDomain(fpara,lpara,parat)) {
    Standard_Real otherpar = parat + M_PI;
    if (otherpar > 2.*M_PI) otherpar -= 2.*M_PI;
    if (DsgPrs_InDomain(fpara,lpara,otherpar)) {
      parat = otherpar;
      otherside = Standard_True;
    }
    else {
      const Standard_Real ecartpar = Min(Abs(fpara-parat),Abs(lpara-parat));
      const Standard_Real ecartoth = Min(Abs(fpara-otherpar),Abs(lpara-otherpar));
      if (ecartpar <= ecartoth) {
        parat = (parat < fpara)? fpara : lpara;
      }
      else {
        otherside = Standard_True;
        parat = (otherpar < fpara)? fpara : lpara;
      }
      gp_Pnt ptdir = ElCLib::Value(parat,aCircle);
      gp_Lin lsup(aCircle.Location(),gp_Dir(ptdir.XYZ()-aCircle.Location().XYZ()));
      const Standard_Real parpos = ElCLib::Parameter(lsup,AttachmentPoint);
      attpoint = ElCLib::Value(parpos,lsup);
    }
  }
  gp_Pnt ptoncirc = ElCLib::Value(parat,aCircle);
  gp_Lin L (aCircle.Location(),gp_Dir(attpoint.XYZ()-aCircle.Location().XYZ()));
  gp_Pnt firstpoint = attpoint;
  gp_Pnt drawtopoint = ptoncirc;
  if (drawFromCenter && !otherside) {
    const Standard_Real uatt = ElCLib::Parameter(L,attpoint);
    const Standard_Real uptc = ElCLib::Parameter(L,ptoncirc);
    if (Abs(uatt) > Abs(uptc))
      drawtopoint = aCircle.Location();
    else
      firstpoint = aCircle.Location();
  }

  Handle(Graphic3d_ArrayOfSegments) aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(firstpoint);
  aPrims->AddVertex(drawtopoint);
  Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

  gp_Dir arrdir = L.Direction();
  if (reverseArrow)
    arrdir.Reverse();

  // fleche
  Prs3d_Arrow::Draw(aPresentation,ptoncirc,arrdir,LA->Arrow1Aspect()->Angle(),LA->Arrow1Aspect()->Length());

  // texte
  Prs3d_Text::Draw(aPresentation,LA->TextAspect(),aText,attpoint);
}

//=======================================================================
//function : DsgPrs_RadiusPresentation::Add
//purpose  : SZY 20-february-98 
//         : adds radius representation according drawFromCenter value
//=======================================================================

void DsgPrs_RadiusPresentation::Add( const Handle(Prs3d_Presentation)& aPresentation,
				     const Handle(Prs3d_Drawer)& aDrawer,
				     const TCollection_ExtendedString& aText,
				     const gp_Pnt& AttachmentPoint,
				     const gp_Pnt& Center,
				     const gp_Pnt& EndOfArrow,
				     const DsgPrs_ArrowSide ArrowPrs,
				     const Standard_Boolean drawFromCenter,
				     const Standard_Boolean reverseArrow)
{
  Handle( Prs3d_LengthAspect ) LA = aDrawer->LengthAspect();
  Prs3d_Root::CurrentGroup( aPresentation )->SetPrimitivesAspect( LA->LineAspect()->Aspect() );

  gp_Pnt LineOrigin, LineEnd;
  DsgPrs::ComputeRadiusLine(Center, EndOfArrow, AttachmentPoint, drawFromCenter, LineOrigin, LineEnd);

  Handle(Graphic3d_ArrayOfSegments) aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(LineOrigin);
  aPrims->AddVertex(LineEnd);
  Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

  // text
  Prs3d_Text::Draw( aPresentation, LA->TextAspect(), aText, AttachmentPoint );

  gp_Dir ArrowDir = gce_MakeDir( LineOrigin , LineEnd );
  if (reverseArrow)
    ArrowDir.Reverse();
  DsgPrs::ComputeSymbol( aPresentation, LA, Center, EndOfArrow, ArrowDir.Reversed(), ArrowDir, ArrowPrs, drawFromCenter );
}
