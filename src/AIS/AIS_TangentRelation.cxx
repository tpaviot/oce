// Created on: 1996-12-05
// Created by: Jean-Pierre COMBE/Odile Olivier
// Copyright (c) 1996-1999 Matra Datavision
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


#include <Standard_NotImplemented.hxx>

#include <AIS_TangentRelation.ixx>
#include <DsgPrs_TangentPresentation.hxx>

#include <Select3D_SensitiveSegment.hxx>
#include <SelectMgr_EntityOwner.hxx>

#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopAbs_ShapeEnum.hxx>


#include <Geom_Plane.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>

#include <ElCLib.hxx>
#include <gp_Pln.hxx>
#include <gp_Lin.hxx>
#include <gp_Circ.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>

#include <AIS.hxx>
#include <TColStd_ListIteratorOfListOfTransient.hxx>
#include <AIS_Shape.hxx>
#include <Bnd_Box.hxx>
#include <Precision.hxx>
#include <Geom_Ellipse.hxx>
#include <GeomAPI_ExtremaCurveCurve.hxx>

//=======================================================================
//function : Constructor
//purpose  : 
//=======================================================================
AIS_TangentRelation::AIS_TangentRelation(const TopoDS_Shape& aFShape, 
					 const TopoDS_Shape& aSShape, 
					 const Handle(Geom_Plane)& aPlane, 
					 const Standard_Integer anExternRef)
  :myExternRef(anExternRef)
{
  myFShape = aFShape;
  mySShape = aSShape;
  myPlane = aPlane;
  myAutomaticPosition = Standard_False;
}

//=======================================================================
//function : ExternRef
//purpose  : 
//=======================================================================
Standard_Integer AIS_TangentRelation::ExternRef()
{
  return myExternRef;
}

//=======================================================================
//function : SetExternRef
//purpose  : 
//=======================================================================
void AIS_TangentRelation::SetExternRef(const Standard_Integer aRef)
{
  myExternRef = aRef;
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================
void AIS_TangentRelation::Compute(const Handle(PrsMgr_PresentationManager3d)&, 
				  const Handle(Prs3d_Presentation)& aPresentation, 
				  const Standard_Integer)
{
  aPresentation->Clear();
 
  switch (myFShape.ShapeType())
    {
    case TopAbs_FACE :
      {
	ComputeTwoFacesTangent(aPresentation);
      }
      break;
    case TopAbs_EDGE :
      {
	ComputeTwoEdgesTangent(aPresentation);
      }
      break;
    default:
      break;
    }
}

//=======================================================================
//function : Compute
//purpose  : to avoid warning
//=======================================================================
void AIS_TangentRelation::Compute(const Handle(Prs3d_Projector)& aProjector,
				  const Handle(Prs3d_Presentation)& aPresentation)
{
// Standard_NotImplemented::Raise("AIS_TangentRelation::Compute(const Handle(Prs3d_Projector)&,const Handle(Prs3d_Presentation)&)");
  PrsMgr_PresentableObject::Compute( aProjector , aPresentation ) ;
}

void AIS_TangentRelation::Compute(const Handle_Prs3d_Projector& aProjector,
				  const Handle_Geom_Transformation& aTransformation,
				  const Handle_Prs3d_Presentation& aPresentation)
{
// Standard_NotImplemented::Raise("AIS_TangentRelation::Compute(const Handle_Prs3d_Projector&, const Handle_Geom_Transformation&, const Handle_Prs3d_Presentation&)");
  PrsMgr_PresentableObject::Compute( aProjector , aTransformation , aPresentation ) ;
}

//=======================================================================
//function : ComputeSelection
//purpose  : 
//=======================================================================
void AIS_TangentRelation::ComputeSelection(const Handle(SelectMgr_Selection)& aSelection, 
					   const Standard_Integer)
{
  gp_Vec vec(myDir);
  gp_Vec vec1 = vec.Multiplied(myLength);
  gp_Vec vec2 = vec.Multiplied(-myLength);
  gp_Pnt p1 = myPosition.Translated(vec1);
  gp_Pnt p2 = myPosition.Translated(vec2);

  Handle(SelectMgr_EntityOwner) own = new SelectMgr_EntityOwner(this,7);
  Handle(Select3D_SensitiveSegment) seg = new Select3D_SensitiveSegment(own,p1,p2);
  aSelection->Add(seg);
}

//=======================================================================
//function : ComputeTwoFacesTangent
//purpose  : 
//=======================================================================
void AIS_TangentRelation::ComputeTwoFacesTangent
  (const Handle(Prs3d_Presentation)& /*aPresentation*/)
{
}

// jfa 19/10/2000 begin
//=======================================================================
//function : ComputeTangencyPoint
//purpose  : 
//=======================================================================
static Standard_Boolean ComputeTangencyPoint(const Handle(Geom_Curve)& GC1,
					     const Handle(Geom_Curve)& GC2,
					     gp_Pnt& aPoint)
{
  Standard_Real U1f = GC1->FirstParameter();
  Standard_Real U1l = GC1->LastParameter();
  Standard_Real U2f = GC2->FirstParameter();
  Standard_Real U2l = GC2->LastParameter();

  gp_Pnt PC1;
  Standard_Real mindist=0;
  GeomAPI_ExtremaCurveCurve Ex(GC1,GC2,U1f,U1l,U2f,U2l);
  for ( Standard_Integer i = 1; i <= Ex.NbExtrema(); i++)
    {
      gp_Pnt P1,P2;
      Ex.Points(i,P1,P2);
      Standard_Real dist = P1.Distance(P2);
      if ( i == 1 )
	{
	  mindist = dist;
	  PC1 = P1;
	}
      else
	{
	  if ( (dist < mindist) || (dist < Precision::Confusion()) )
	    {
	      mindist = dist;
	      PC1 = P1;
	    }
	}
      if ( dist < Precision::Confusion() )
	{
	  if (GC1->IsInstance(STANDARD_TYPE(Geom_Line)))
	    {
	      continue; // tangent line and conic can have only one point with zero distance
	    }
	  gp_Vec aVector1,aVector2;
	  if (GC1->IsInstance(STANDARD_TYPE(Geom_Circle)))
	    {
	      const Handle(Geom_Circle)& circle = (Handle(Geom_Circle)&) GC1;
	      Standard_Real par_inter = ElCLib::Parameter(circle->Circ(), P1);
	      ElCLib::D1(par_inter,circle->Circ(),P1,aVector1);
	    }
	  else if (GC1->IsInstance(STANDARD_TYPE(Geom_Ellipse)))
	    {
	      const Handle(Geom_Ellipse)& ellipse = (Handle(Geom_Ellipse)&) GC1;
	      Standard_Real par_inter = ElCLib::Parameter(ellipse->Elips(), P1);
	      ElCLib::D1(par_inter,ellipse->Elips(),P1,aVector1);
	    }
	  if (GC2->IsInstance(STANDARD_TYPE(Geom_Circle)))
	    {
	      const Handle(Geom_Circle)& circle = (Handle(Geom_Circle)&) GC2;
	      Standard_Real par_inter = ElCLib::Parameter(circle->Circ(), P2);
	      ElCLib::D1(par_inter,circle->Circ(),P2,aVector2);
	    }
	  else if (GC2->IsInstance(STANDARD_TYPE(Geom_Ellipse)))
	    {
	      const Handle(Geom_Ellipse)& ellipse = (Handle(Geom_Ellipse)&) GC2;
	      Standard_Real par_inter = ElCLib::Parameter(ellipse->Elips(), P2);
	      ElCLib::D1(par_inter,ellipse->Elips(),P2,aVector2);
	    }
//	  if ( aVector1.IsParallel(aVector2, 100*Precision::Angular()) ) break;
	  if ( aVector1.IsParallel(aVector2, M_PI / 360.0) ) break; // 0.5 graduce
	}
    }
  aPoint = PC1;
  return Standard_True;
}
// jfa 19/10/2000 end

//=======================================================================
//function : ComputeTwoEdgesTangent
//purpose  : 
//=======================================================================
void AIS_TangentRelation::ComputeTwoEdgesTangent(const Handle(Prs3d_Presentation)& aPresentation)
{
  Handle(Geom_Curve) copy1,copy2;
  gp_Pnt ptat11,ptat12,ptat21,ptat22;
  Standard_Boolean isInfinite1,isInfinite2;
  Handle(Geom_Curve) extCurv;
  if (!AIS::ComputeGeometry(TopoDS::Edge(myFShape),
			    TopoDS::Edge(mySShape),
			    myExtShape,
			    copy1,
			    copy2,
			    ptat11,
			    ptat12,
			    ptat21,
			    ptat22,
			    extCurv,
			    isInfinite1,isInfinite2,
			    myPlane))
    {
      return;
    }

  aPresentation->SetInfiniteState(isInfinite1 || isInfinite2);
  // current face  
  BRepBuilderAPI_MakeFace makeface(myPlane->Pln());
  TopoDS_Face face(makeface.Face());  
  BRepAdaptor_Surface adp(makeface.Face());
    
  Standard_Integer typArg(0);
  
  if (copy1->IsInstance(STANDARD_TYPE(Geom_Line)))
    {
      typArg = 10;
    }
  else if (copy1->IsInstance(STANDARD_TYPE(Geom_Circle)))
    {
      typArg = 20;
    }
  else if (copy1->IsInstance(STANDARD_TYPE(Geom_Ellipse)))
    {
      typArg = 30;
    }
  else return;

  if (copy2->IsInstance(STANDARD_TYPE(Geom_Line)))
    {
      typArg += 1;
    }
  else if (copy2->IsInstance(STANDARD_TYPE(Geom_Circle)))
    {
      typArg += 2;
    }
  else if (copy2->IsInstance(STANDARD_TYPE(Geom_Ellipse)))
    {
      typArg += 3;
    }
  else return;

  //First find the tangengy vector if exists
  TopoDS_Vertex VCom;
  TopExp_Explorer expF(TopoDS::Edge(myFShape),TopAbs_VERTEX);
  TopExp_Explorer expS(TopoDS::Edge(mySShape),TopAbs_VERTEX);
  TopoDS_Shape tab[2];
  Standard_Integer p ;
  for (p = 0; expF.More(); expF.Next(),p++)
    {
      tab[p] = TopoDS::Vertex(expF.Current());
    }
  Standard_Boolean found(Standard_False);
  for ( ; expS.More() && !found; expS.Next())
    {
      for ( Standard_Integer l = 0; l<=p && !found; l++)
	{
	  found = ( expS.Current().IsSame(tab[l]));
	  if (found) VCom = TopoDS::Vertex(expS.Current());
	}
    }

  gp_Vec theVector;
  gp_Pnt pint3d; // tangency point
  gp_Dir theDir; // tangency direction
  Standard_Real par_inter = 0.0; // parameter of tangency point

  if (found)
    {
      pint3d = BRep_Tool::Pnt(VCom);
    }

  // Otherwise it is found as if it was known that 2 curves
  // are tangents (which must be the cases)
  switch (typArg)
    {
    case 12: // circle line      
       {
	const Handle(Geom_Line)& line = (Handle(Geom_Line)&) copy1;
	const Handle(Geom_Circle)& circle = (Handle(Geom_Circle)&) copy2;

	if ( !found )
	  {
	    // it is enough to project the circus  center on the straight line 
	    par_inter = ElCLib::Parameter(line->Lin(), circle->Location());
	    pint3d = ElCLib::Value(par_inter, line->Lin());
	  }
      
	theDir = line->Lin().Direction();
	myLength = circle->Radius()/5.;
	if ( !isInfinite1 )
	  {
	    Standard_Real copy1Length = ptat12.Distance(ptat11);
	    if ( copy1Length < myLength )
	      myLength = copy1Length/3.;
	  }
      }
      break;
    case 21: // circle line
      {
	const Handle(Geom_Circle)& circle = (Handle(Geom_Circle)&) copy1;
	const Handle(Geom_Line)& line = (Handle(Geom_Line)&) copy2;
      
	if (!found)
	  {
	    // it is enough to project the circus  center on the straight line 
	    par_inter = ElCLib::Parameter(line->Lin(), circle->Location());
	    pint3d = ElCLib::Value(par_inter, line->Lin());
	  }
      
	theDir = line->Lin().Direction();
	myLength = circle->Radius()/5.;
	if (!isInfinite2)
	  {
	    Standard_Real copy2Length = ptat21.Distance(ptat22);
	    if ( copy2Length < myLength )
	      myLength = copy2Length/3.;
	  }
      }
      break;
    // jfa 19/10/2000 begin
    case 13: // line ellipse
      {
	const Handle(Geom_Line)& line = (Handle(Geom_Line)&) copy1;
	const Handle(Geom_Ellipse)& ellipse = (Handle(Geom_Ellipse)&) copy2;

	if (!found)
	  {
	    ComputeTangencyPoint(line,ellipse,pint3d);
	  }
      
	theDir = line->Lin().Direction();
	myLength = ellipse->MajorRadius()/5.;

	if (!isInfinite1)
	  {
	    Standard_Real copy1Length = ptat12.Distance(ptat11);
	    if ( copy1Length < myLength )
	      myLength = copy1Length/3.;
	  }
      }
      break;
    case 31: // ellipse line
      {
	const Handle(Geom_Ellipse)& ellipse = (Handle(Geom_Ellipse)&) copy1;
	const Handle(Geom_Line)& line = (Handle(Geom_Line)&) copy2;
      
	if (!found)
	  {
	    ComputeTangencyPoint(line,ellipse,pint3d);
	  }
      
	theDir = line->Lin().Direction();
	myLength = ellipse->MajorRadius()/5.;

	if (!isInfinite2)
	  {
	    Standard_Real copy2Length = ptat21.Distance(ptat22);
	    if ( copy2Length < myLength )
	      myLength = copy2Length/3.;
	  }
      }
      break;
    case 22: // circle circle
      {
	const Handle(Geom_Circle)& circle1 = (Handle(Geom_Circle)&) copy1;
	const Handle(Geom_Circle)& circle2 = (Handle(Geom_Circle)&) copy2;
	Standard_Real R1 = circle1->Radius();
	Standard_Real R2 = circle2->Radius();
	myLength = Max(R1,R2)/5.0;
	if ( !found )
	  {
	    if ( (circle1->Location()).IsEqual(circle2->Location(),Precision::Confusion()) )
	      {
		if ( R1 >= R2 )
		  {
		    ElCLib::D1(par_inter,circle1->Circ(),pint3d,theVector);
		  }
		else
		  {
		    ElCLib::D1(par_inter,circle2->Circ(),pint3d,theVector);
		  }
	      }
	    else
	      {
		if ( R1 >= R2 )
		  {
		    par_inter = ElCLib::Parameter(circle1->Circ(), circle2->Location());
		    ElCLib::D1(par_inter,circle1->Circ(),pint3d,theVector);
		  }
		else
		  {
		    par_inter = ElCLib::Parameter(circle2->Circ(), circle1->Location());
		    ElCLib::D1(par_inter,circle2->Circ(),pint3d,theVector);
		  }
	      }
	  }
	else
	  {
	    par_inter = ElCLib::Parameter(circle1->Circ(), pint3d);
	    ElCLib::D1(par_inter,circle1->Circ(),pint3d,theVector);
	  }
	theDir = gp_Dir(theVector);    
      }
      break;
    case 23: // circle ellipse
      {
	const Handle(Geom_Circle)&  circle  = (Handle(Geom_Circle)&)  copy1;
	const Handle(Geom_Ellipse)& ellipse = (Handle(Geom_Ellipse)&) copy2;
	Standard_Real R1 = circle->Radius();
	Standard_Real R2 = ellipse->MajorRadius();
	myLength = Max(R1,R2)/5.0;
	if (!found)
	  {
	    if ( R1 >= R2 )
	      {
		ComputeTangencyPoint(circle,ellipse,pint3d);
		par_inter = ElCLib::Parameter(circle->Circ(), pint3d);
		ElCLib::D1(par_inter,circle->Circ(),pint3d,theVector);
	      }
	    else
	      {
		ComputeTangencyPoint(ellipse,circle,pint3d);
		par_inter = ElCLib::Parameter(ellipse->Elips(), pint3d);
		ElCLib::D1(par_inter,ellipse->Elips(),pint3d,theVector);
	      }
	  }
	else
	  {
	    par_inter = ElCLib::Parameter(circle->Circ(), pint3d);
	    ElCLib::D1(par_inter,circle->Circ(),pint3d,theVector);
	  }
	theDir = gp_Dir(theVector);    
      }
      break;
    case 32: // ellipse circle
      {
	const Handle(Geom_Ellipse)& ellipse = (Handle(Geom_Ellipse)&) copy1;
	const Handle(Geom_Circle)&  circle  = (Handle(Geom_Circle)&) copy2;
	Standard_Real R1 = ellipse->MajorRadius();
	Standard_Real R2 = circle->Radius();
	myLength = Max(R1,R2)/5.0;
	if (!found)
	  {
	    if ( R1 >= R2 )
	      {
		ComputeTangencyPoint(ellipse,circle,pint3d);
		par_inter = ElCLib::Parameter( ellipse->Elips(), pint3d);
		ElCLib::D1(par_inter,ellipse->Elips(),pint3d,theVector);
	      }
	    else
	      {
		ComputeTangencyPoint(circle,ellipse,pint3d);
		par_inter = ElCLib::Parameter( circle->Circ(), pint3d);
		ElCLib::D1(par_inter,circle->Circ(),pint3d,theVector);
	      }
	  }
	else
	  {
	    par_inter = ElCLib::Parameter(circle->Circ(), pint3d);
	    ElCLib::D1(par_inter,circle->Circ(),pint3d,theVector);
	  }
	theDir = gp_Dir(theVector);    
      }
      break;
    case 33: // ellipse ellipse
      {
	const Handle(Geom_Ellipse)& ellipse1 = (Handle(Geom_Ellipse)&) copy1;
	const Handle(Geom_Ellipse)& ellipse2 = (Handle(Geom_Ellipse)&) copy2;
	Standard_Real R1 = ellipse1->MajorRadius();
	Standard_Real R2 = ellipse2->MajorRadius();
	myLength = Max(R1,R2)/5.0;
	if (!found)
	  {
	    if ( R1 > R2 )
	      {
		ComputeTangencyPoint(ellipse1,ellipse2,pint3d);
		par_inter = ElCLib::Parameter( ellipse1->Elips(), pint3d);
		ElCLib::D1(par_inter,ellipse1->Elips(),pint3d,theVector);
	      }
	    else
	      {
		ComputeTangencyPoint(ellipse2,ellipse1,pint3d);
		par_inter = ElCLib::Parameter( ellipse2->Elips(), pint3d);
		ElCLib::D1(par_inter,ellipse2->Elips(),pint3d,theVector);
	      }
	  }
	else
	  {
	    par_inter = ElCLib::Parameter(ellipse1->Elips(), pint3d);
	    ElCLib::D1(par_inter,ellipse1->Elips(),pint3d,theVector);
	  }
	theDir = gp_Dir(theVector);    
      }
      break;
    // jfa 19/10/2000 end
    default:
      return;
    }

  myAttach = pint3d;
  myDir = theDir;
  myPosition = pint3d;
  myLength = Min(myLength,myArrowSize);

  DsgPrs_TangentPresentation::Add(aPresentation,myDrawer,myAttach,myDir,myLength);
  if ( (myExtShape != 0) &&  !extCurv.IsNull())
    {
      gp_Pnt pf, pl;
      if ( myExtShape == 1 )
	{
	  if (!isInfinite1)
	    {
	      pf = ptat11; 
	      pl = ptat12;
	    }
	  ComputeProjEdgePresentation(aPresentation,TopoDS::Edge(myFShape),copy1,pf,pl);
	}
      else
	{
	  if (!isInfinite2)
	    {
	      pf = ptat21; 
	      pl = ptat22;
	    }
	  ComputeProjEdgePresentation(aPresentation,TopoDS::Edge(mySShape),copy2,pf,pl);
	}
    }
}
