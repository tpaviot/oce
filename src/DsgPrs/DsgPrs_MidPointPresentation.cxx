// Created on: 2000-10-20
// Created by: Julia DOROVSKIKH
// Copyright (c) 2000-2012 OPEN CASCADE SAS
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

#include <DsgPrs_MidPointPresentation.ixx>

#include <Precision.hxx>

#include <TCollection_ExtendedString.hxx>

#include <gp_Lin.hxx>
#include <gp_Circ.hxx>
#include <gp_Vec.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Pnt.hxx>

#include <ElCLib.hxx>

#include <Graphic3d_Group.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>
#include <Graphic3d_AspectLine3d.hxx>

#include <Prs3d_Root.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_LengthAspect.hxx>
#include <Prs3d_Text.hxx>

//===================================================================
//Function:Add
//Purpose: draws the representation of a radial symmetry between two vertices.
//===================================================================
void DsgPrs_MidPointPresentation::Add (const Handle(Prs3d_Presentation)& aPresentation,
				       const Handle(Prs3d_Drawer)& aDrawer,	
				       const gp_Ax2&  theAxe,
				       const gp_Pnt&  MidPoint,
				       const gp_Pnt&  Position,
				       const gp_Pnt&  AttachPoint,
				       const Standard_Boolean first)
{ 
  Standard_Real rad = AttachPoint.Distance(MidPoint)/20.0;

  Handle(Prs3d_LengthAspect) LA = aDrawer->LengthAspect();

  gp_Ax2 ax = theAxe;
  ax.SetLocation(MidPoint);
  gp_Circ aCircleM (ax,rad);

  if ( first )
  {
    // center of the symmetry - circle around the MidPoint
    Prs3d_Root::NewGroup(aPresentation);
    Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    const Standard_Real alpha = 2. * M_PI;
    const Standard_Integer nbp = 100;
    const Standard_Real dteta = alpha/(nbp-1);

    Handle(Graphic3d_ArrayOfPolylines) aPrims = new Graphic3d_ArrayOfPolylines(nbp+2,2);
    aPrims->AddBound(nbp);
    for (Standard_Integer i = 1; i <= nbp; i++)
      aPrims->AddVertex(ElCLib::Value(dteta*(i-1),aCircleM));

    // segment from mid point to the text position
    aPrims->AddBound(2);
    aPrims->AddVertex(Position.IsEqual(MidPoint,rad)? MidPoint : ElCLib::Value(ElCLib::Parameter(aCircleM,Position),aCircleM)); // mid point
    aPrims->AddVertex(Position); // text position

	Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

    // texte 
    TCollection_ExtendedString aText(" (+)");
    Prs3d_Text::Draw(aPresentation,LA->TextAspect(),aText,Position);
  }

  if ( !AttachPoint.IsEqual(MidPoint, Precision::Confusion()) )
  {
    if ( !first )
    {
      Prs3d_Root::NewGroup(aPresentation);
      Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(LA->LineAspect()->Aspect());
    }

    // segment from mid point to the geometry
    Handle(Graphic3d_ArrayOfSegments) aPrims = new Graphic3d_ArrayOfSegments(2);
    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(aCircleM,AttachPoint),aCircleM)); // mid point
    aPrims->AddVertex(AttachPoint); // attach point to the geometry
    Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);
  }
}
  
//===================================================================
//Function:Add
//Purpose: draws the representation of a radial symmetry between two linear segments.
//===================================================================
void DsgPrs_MidPointPresentation::Add (const Handle(Prs3d_Presentation)& aPresentation,
				       const Handle(Prs3d_Drawer)& aDrawer,	
				       const gp_Ax2&  theAxe,
				       const gp_Pnt&  MidPoint,
				       const gp_Pnt&  Position,
				       const gp_Pnt&  AttachPoint,
				       const gp_Pnt&  Point1,
				       const gp_Pnt&  Point2,
				       const Standard_Boolean first)
{
  Standard_Real rad = AttachPoint.Distance(MidPoint)/20.0;
  if ( rad <= Precision::Confusion() ) rad = Point1.Distance(Point2)/20.0;

  Handle(Prs3d_LengthAspect) LA = aDrawer->LengthAspect();

  gp_Ax2 ax = theAxe;
  ax.SetLocation(MidPoint);
  gp_Circ aCircleM (ax,rad);

  // segment on line
  Prs3d_Root::NewGroup(aPresentation);
  Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  Handle(Graphic3d_ArrayOfPrimitives) aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(Point1);
  aPrims->AddVertex(Point2);
  Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

  if ( first )
  {
    // center of the symmetry - circle around the MidPoint
    const Standard_Real alpha = 2. * M_PI;
    const Standard_Integer nbp = 100;
    const Standard_Real dteta = alpha/(nbp-1);

    aPrims = new Graphic3d_ArrayOfPolylines(nbp+2,2);
    aPrims->AddBound(nbp);
    for (Standard_Integer i = 1; i <= nbp; i++)
      aPrims->AddVertex(ElCLib::Value(dteta*(i-1),aCircleM));

    // segment from mid point to the text position
    aPrims->AddBound(2);
    aPrims->AddVertex(Position.IsEqual(MidPoint,rad)? MidPoint : ElCLib::Value(ElCLib::Parameter(aCircleM,Position),aCircleM)); // mid point
    aPrims->AddVertex(Position); // text position

	Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

    // texte
    TCollection_ExtendedString aText (" (+)");
    Prs3d_Text::Draw(aPresentation,LA->TextAspect(),aText,Position);
  }

  if ( !AttachPoint.IsEqual(MidPoint, Precision::Confusion()) )
  {
    // mid point
    aPrims = new Graphic3d_ArrayOfSegments(2);
    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(aCircleM,AttachPoint),aCircleM));
    aPrims->AddVertex(AttachPoint); // attach point to the geometry
    Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);
  }
}
  
//===================================================================
//Function:Add
//Purpose: draws the representation of a radial symmetry between two circular arcs.
//===================================================================
void DsgPrs_MidPointPresentation::Add (const Handle(Prs3d_Presentation)& aPresentation,
				       const Handle(Prs3d_Drawer)& aDrawer,	
				       const gp_Circ& aCircle,
				       const gp_Pnt&  MidPoint,
				       const gp_Pnt&  Position,
				       const gp_Pnt&  AttachPoint,
				       const gp_Pnt&  Point1,
				       const gp_Pnt&  Point2,
				       const Standard_Boolean first)
{
  Standard_Real rad = AttachPoint.Distance(MidPoint)/20.0;
  if ( rad <= Precision::Confusion() ) rad = Point1.Distance(Point2)/20.0;

  Handle(Prs3d_LengthAspect) LA = aDrawer->LengthAspect();

  gp_Ax2 ax = aCircle.Position();
  ax.SetLocation(MidPoint);
  gp_Circ aCircleM (ax,rad);

  // segment on circle
  Prs3d_Root::NewGroup(aPresentation);
  Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  const Standard_Real pf = ElCLib::Parameter(aCircle,Point1);
  const Standard_Real pl = ElCLib::Parameter(aCircle,Point2);
  Standard_Real alpha = pl - pf;
  if ( alpha < 0 ) alpha += 2. * M_PI;
  const Standard_Integer nb = (Standard_Integer)(50.0*alpha/M_PI);
  Standard_Integer nbp = Max(4,nb);
  Standard_Real dteta = alpha/(nbp-1);

  Handle(Graphic3d_ArrayOfPrimitives) aPrims = new Graphic3d_ArrayOfPolylines(nbp);
  for (Standard_Integer i = 1; i <= nbp; i++)
    aPrims->AddVertex(ElCLib::Value(pf + dteta*(i-1),aCircle));
  Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

  if ( first )
  {
    // center of the symmetry - circle around the MidPoint
    alpha = 2. * M_PI;
    nbp = 100;
    dteta = alpha/(nbp-1);

    aPrims = new Graphic3d_ArrayOfPolylines(nbp+2,2);
    aPrims->AddBound(nbp);
    for (Standard_Integer i = 1; i <= nbp; i++)
      aPrims->AddVertex(ElCLib::Value(dteta*(i-1),aCircleM));

    // segment from mid point to the text position
    aPrims->AddBound(2);
    aPrims->AddVertex(Position.IsEqual(MidPoint,rad)? MidPoint : ElCLib::Value(ElCLib::Parameter(aCircleM,Position),aCircleM)); // mid point
    aPrims->AddVertex(Position); // text position

	Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

    // texte 
    TCollection_ExtendedString aText (" (+)");
    Prs3d_Text::Draw(aPresentation,LA->TextAspect(),aText,Position);
  }

  if ( !AttachPoint.IsEqual(MidPoint, Precision::Confusion()) )
  {
    // segment from mid point to the geometry
    aPrims = new Graphic3d_ArrayOfSegments(2);
    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(aCircleM,AttachPoint),aCircleM)); // mid point
    aPrims->AddVertex(AttachPoint); // attach point to the geometry
    Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);
  }
}
  
//===================================================================
//Function:Add
//Purpose: draws the representation of a radial symmetry between two elliptic arcs.
//===================================================================
void DsgPrs_MidPointPresentation::Add (const Handle(Prs3d_Presentation)& aPresentation,
				       const Handle(Prs3d_Drawer)& aDrawer,	
				       const gp_Elips& aCircle,
				       const gp_Pnt&   MidPoint,
				       const gp_Pnt&   Position,
				       const gp_Pnt&   AttachPoint,
				       const gp_Pnt&   Point1,
				       const gp_Pnt&   Point2,
				       const Standard_Boolean first)
{
  Standard_Real rad = AttachPoint.Distance(MidPoint)/20.0;
  if ( rad <= Precision::Confusion() ) rad = Point1.Distance(Point2)/20.0;

  Handle(Prs3d_LengthAspect) LA = aDrawer->LengthAspect();

  gp_Pnt Ptmp,ptcur;

  gp_Ax2 ax = aCircle.Position();
  ax.SetLocation(MidPoint);
  gp_Circ aCircleM (ax,rad);

  // segment on ellipse
  Prs3d_Root::NewGroup(aPresentation);
  Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  const Standard_Real pf = ElCLib::Parameter(aCircle,Point1);
  const Standard_Real pl = ElCLib::Parameter(aCircle,Point2);
  Standard_Real alpha = pl - pf;
  if ( alpha < 0 ) alpha += 2 * M_PI;
  const Standard_Integer nb = (Standard_Integer)(50.0*alpha/M_PI);
  Standard_Integer nbp = Max(4,nb);
  Standard_Real dteta = alpha/(nbp-1);

  Handle(Graphic3d_ArrayOfPrimitives) aPrims = new Graphic3d_ArrayOfPolylines(nbp);
  for (Standard_Integer i = 1; i <= nbp; i++)
    aPrims->AddVertex(ElCLib::Value(pf + dteta*(i-1),aCircle));
  Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

  if ( first )
  {
    // center of the symmetry - circle around the MidPoint
    alpha = 2. * M_PI;
    nbp = 100;
    dteta = alpha/(nbp-1);

    aPrims = new Graphic3d_ArrayOfPolylines(nbp+2,2);
    aPrims->AddBound(nbp);
    for (Standard_Integer i = 1; i <= nbp; i++)
      aPrims->AddVertex(ElCLib::Value(dteta*(i-1),aCircleM));

    // segment from mid point to the text position
    aPrims->AddBound(2);
	aPrims->AddVertex(Position.IsEqual(MidPoint,rad)? MidPoint : ElCLib::Value(ElCLib::Parameter(aCircleM,Position),aCircleM)); // mid point
    aPrims->AddVertex(Position); // text position

	Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);

    // texte 
    TCollection_ExtendedString aText (" (+)");
    Prs3d_Text::Draw(aPresentation,LA->TextAspect(),aText,Position);
  }

  if ( !AttachPoint.IsEqual(MidPoint, Precision::Confusion()) )
  {
    // segment from mid point to the geometry
    aPrims = new Graphic3d_ArrayOfSegments(2);
    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(aCircleM,AttachPoint),aCircleM)); // mid point
    aPrims->AddVertex(AttachPoint); // attach point to the geometry
    Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims);
  }
}
