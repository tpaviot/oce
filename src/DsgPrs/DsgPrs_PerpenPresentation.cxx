// Created on: 1995-11-28
// Created by: Jean-Pierre COMBE
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



#include <DsgPrs_PerpenPresentation.ixx>

#include <gp_Lin.hxx>
#include <gp_Dir.hxx>
#include <ElCLib.hxx>
#include <gce_MakeLin.hxx>
#include <gce_MakeDir.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Graphic3d_Group.hxx>
#include <Prs3d_Arrow.hxx>
#include <Prs3d_Text.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_TextAspect.hxx>
#include <Prs3d_PointAspect.hxx>
#include <Prs3d_LengthAspect.hxx>
#include <TCollection_AsciiString.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>

#include <StdPrs_Point.hxx>

void DsgPrs_PerpenPresentation::Add (const Handle(Prs3d_Presentation)& aPresentation,
				     const Handle(Prs3d_Drawer)& aDrawer,
				     const gp_Pnt& pAx1,
				     const gp_Pnt& pAx2,
				     const gp_Pnt& pnt1,
				     const gp_Pnt& pnt2,
				     const gp_Pnt& OffsetPoint,
				     const Standard_Boolean intOut1,
				     const Standard_Boolean intOut2)
{
  Handle(Prs3d_LengthAspect) LA = aDrawer->LengthAspect();
  LA->LineAspect()->SetTypeOfLine(Aspect_TOL_SOLID); // ou DOT ou DOTDASH
  Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(LA->LineAspect()->Aspect());
  
  // segments
  Handle(Graphic3d_ArrayOfPrimitives) aPrims = new Graphic3d_ArrayOfPolylines(6,2);

  aPrims->AddBound(3);
  aPrims->AddVertex(OffsetPoint);
  aPrims->AddVertex(pAx1);
  aPrims->AddVertex(pAx2);

  // Symbol
  gp_Vec vec1(gce_MakeDir(OffsetPoint,pAx1));
  gp_Vec vec2(gce_MakeDir(OffsetPoint,pAx2));
  vec1 *= .2 * OffsetPoint.Distance(pAx1);
  vec2 *= .2 * OffsetPoint.Distance(pAx2);

  gp_Pnt pAx11 = OffsetPoint.Translated(vec1);
  gp_Pnt pAx22 = OffsetPoint.Translated(vec2);
  gp_Pnt p_symb = pAx22.Translated(vec1);

  aPrims->AddBound(3);
  aPrims->AddVertex(pAx11);
  aPrims->AddVertex(p_symb);
  aPrims->AddVertex(pAx22);

  Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

  // points attache
  if (intOut1 || intOut2)
  {
    LA->LineAspect()->SetTypeOfLine(Aspect_TOL_DOT); // ou DOT ou DOTDASH
    Prs3d_Root::NewGroup(aPresentation);
    Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    if (intOut1) {
      aPrims = new Graphic3d_ArrayOfSegments(2);
      aPrims->AddVertex(pAx1);
      aPrims->AddVertex(pnt1);
      Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);
    }
    if (intOut2) {
      aPrims = new Graphic3d_ArrayOfSegments(2);
      aPrims->AddVertex(pAx2);
      aPrims->AddVertex(pnt2);
      Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);
    }
  }
}
