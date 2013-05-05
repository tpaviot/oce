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


#include <AIS_MidPointRelation.ixx>

#include <Standard_NotImplemented.hxx>

#include <Precision.hxx>

#include <AIS.hxx>
#include <AIS_Drawer.hxx>

#include <gce_MakeLin.hxx>
#include <ElCLib.hxx>
#include <gp_Lin.hxx>
#include <gp_Circ.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pln.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>

#include <Geom_Plane.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_TrimmedCurve.hxx>

#include <SelectMgr_EntityOwner.hxx>
#include <Select3D_SensitiveSegment.hxx>
#include <Select3D_SensitiveCurve.hxx>

#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAdaptor_Curve.hxx>

#include <Prs3d_Drawer.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_LengthAspect.hxx>

#include <DsgPrs_MidPointPresentation.hxx>
#include <TopoDS_Vertex.hxx>

//=======================================================================
//function : AIS_MidPointRelation
//purpose  : 
//=======================================================================
AIS_MidPointRelation::AIS_MidPointRelation(const TopoDS_Shape& aMidPointTool, 
					   const TopoDS_Shape& FirstShape, 
					   const TopoDS_Shape& SecondShape, 
					   const Handle(Geom_Plane)& aPlane)
:AIS_Relation(),
 myTool(aMidPointTool)
{
 SetFirstShape(FirstShape);
 SetSecondShape(SecondShape);
 SetPlane(aPlane);
 myPosition = aPlane->Pln().Location();
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================
void AIS_MidPointRelation::Compute(const Handle(PrsMgr_PresentationManager3d)&, 
				   const Handle(Prs3d_Presentation)& aprs, 
				   const Standard_Integer)
{
  aprs->Clear();
  
  if (myTool.ShapeType() == TopAbs_VERTEX)
    {
      gp_Pnt pp;
      Standard_Boolean isonplane;
      if ( AIS::ComputeGeometry(TopoDS::Vertex(myTool),pp,myPlane,isonplane) )
	{
	  if ( !isonplane ) ComputeProjVertexPresentation(aprs,TopoDS::Vertex(myTool),pp);
	}
      myMidPoint = pp;
    }
  else return;

  if ( myAutomaticPosition ) myPosition = myMidPoint;  

  switch (myFShape.ShapeType())
    {
    case TopAbs_FACE :
      {
	ComputeFaceFromPnt(aprs, Standard_True);
      }
      break;
    case TopAbs_EDGE :
      {
	ComputeEdgeFromPnt(aprs, Standard_True);
      }
      break;
    case TopAbs_VERTEX :
      {
	ComputeVertexFromPnt(aprs, Standard_True);
      }
      break;
    default:
      break;
    }

  switch (mySShape.ShapeType())
    {
    case TopAbs_FACE :
      {
	ComputeFaceFromPnt(aprs, Standard_False);
      }
      break;
    case TopAbs_EDGE :
      {
	ComputeEdgeFromPnt(aprs, Standard_False);
      }
      break;
    case TopAbs_VERTEX :
      {
	ComputeVertexFromPnt(aprs, Standard_False);
      }
      break;
    default:
      break;
    }
}

//=======================================================================
//function : Compute
//purpose  : to avoid warning at compilation (SUN)
//=======================================================================
void AIS_MidPointRelation::Compute(const Handle(Prs3d_Projector)& /*aProjector*/,
				   const Handle(Prs3d_Presentation)& /*aPresentation*/)
{
// Standard_NotImplemented::Raise("AIS_MidPointRelation::Compute(const Handle(Prs3d_Projector)&,const Handle(Prs3d_Presentation)&)");
// PrsMgr_PresentableObject::Compute( aProjector , aPresentation ) ;
}

void AIS_MidPointRelation::Compute(const Handle_Prs3d_Projector& aProjector,
				   const Handle_Geom_Transformation& aTransformation,
				   const Handle_Prs3d_Presentation& aPresentation)
{
 Standard_NotImplemented::Raise("AIS_MidPointRelation::Compute(const Handle_Prs3d_Projector&, const Handle_Geom_Transformation&, const Handle_Prs3d_Presentation&)");
 PrsMgr_PresentableObject::Compute( aProjector , aTransformation , aPresentation ) ;
}

//=======================================================================
//function : ComputeSelection
//purpose  : 
//=======================================================================
void AIS_MidPointRelation::ComputeSelection(const Handle(SelectMgr_Selection)& aSel, 
					    const Standard_Integer)
{
  Handle(Select3D_SensitiveSegment) seg;
  Handle(SelectMgr_EntityOwner) own = new SelectMgr_EntityOwner(this,7);

  if ( !myMidPoint.IsEqual(myFAttach,Precision::Confusion()) )
    {
      // segment from mid point to the first geometry
      seg = new Select3D_SensitiveSegment(own,myFAttach,myMidPoint);
      aSel->Add(seg);
      // segment from mid point to the second geometry
      seg = new Select3D_SensitiveSegment(own,mySAttach,myMidPoint);
      aSel->Add(seg);
    }
  if ( !myMidPoint.IsEqual(myPosition,Precision::Confusion()) )
    {
      // segment from mid point to the text position
      seg = new Select3D_SensitiveSegment(own,myMidPoint,myPosition);
      aSel->Add(seg);
    }

  // center of the symmetry - circle around the MidPoint
  gp_Ax2 ax = myPlane->Pln().Position().Ax2();
  ax.SetLocation(myMidPoint);
  Standard_Real rad = myFAttach.Distance(myMidPoint)/20.0;
  gp_Circ aCircleM (ax,rad);
  Handle(Geom_Circle) thecir = new Geom_Circle(aCircleM);
  Handle(Select3D_SensitiveCurve) scurv = new Select3D_SensitiveCurve(own, thecir);
  aSel->Add(scurv);

  Handle(Geom_Curve) curv;
  gp_Pnt firstp,lastp;
  Standard_Boolean isInfinite,isOnPlane;
  Handle(Geom_Curve) extCurv;

  // segment on first curve
  if ( myFShape.ShapeType() == TopAbs_EDGE )
    {
      TopoDS_Edge E = TopoDS::Edge(myFShape);
      if ( !AIS::ComputeGeometry(E,curv,firstp,lastp,extCurv,isInfinite,isOnPlane,myPlane) ) return;
      if ( curv->IsInstance(STANDARD_TYPE(Geom_Line)) ) // case of line
	{
	  // segment on line
	  seg = new Select3D_SensitiveSegment(own,myFirstPnt1,myFirstPnt2);
	  aSel->Add(seg);
	}
      else if ( curv->IsInstance(STANDARD_TYPE(Geom_Circle)) ) // case of circle
	{
	  // segment on circle
	  Handle(Geom_Circle) thecirc = (Handle(Geom_Circle)&) curv;
	  Standard_Real udeb = ElCLib::Parameter(thecirc->Circ(),myFirstPnt1);
	  Standard_Real ufin = ElCLib::Parameter(thecirc->Circ(),myFirstPnt2);
	  Handle(Geom_TrimmedCurve) thecu = new Geom_TrimmedCurve(thecirc,udeb,ufin);
	  
	  scurv = new Select3D_SensitiveCurve(own, thecu);
	  aSel->Add(scurv);
	}
      else if ( curv->IsInstance(STANDARD_TYPE(Geom_Ellipse)) ) // case of ellipse
	{
	  // segment on ellipse
	  Handle(Geom_Ellipse) theEll = (Handle(Geom_Ellipse)&) curv;
	  Standard_Real udeb = ElCLib::Parameter(theEll->Elips(),myFirstPnt1);
	  Standard_Real ufin = ElCLib::Parameter(theEll->Elips(),myFirstPnt2);
	  Handle(Geom_TrimmedCurve) thecu = new Geom_TrimmedCurve(theEll,udeb,ufin);
	  
	  scurv = new Select3D_SensitiveCurve(own, thecu);
	  aSel->Add(scurv);
	}
    }

  // segment on second curve
  if ( mySShape.ShapeType() == TopAbs_EDGE )
    {
      TopoDS_Edge E = TopoDS::Edge(mySShape);
      if ( !AIS::ComputeGeometry(E,curv,firstp,lastp,extCurv,isInfinite,isOnPlane,myPlane) ) return;
      if ( curv->IsInstance(STANDARD_TYPE(Geom_Line)) ) // case of line
	{
	  // segment on line
	  seg = new Select3D_SensitiveSegment(own,mySecondPnt1,mySecondPnt2);
	  aSel->Add(seg);
	}
      else if ( curv->IsInstance(STANDARD_TYPE(Geom_Circle)) ) // case of circle
	{
	  // segment on circle
	  Handle(Geom_Circle) thecirc = (Handle(Geom_Circle)&) curv;
	  Standard_Real udeb = ElCLib::Parameter(thecirc->Circ(),mySecondPnt1);
	  Standard_Real ufin = ElCLib::Parameter(thecirc->Circ(),mySecondPnt2);
	  Handle(Geom_TrimmedCurve) thecu = new Geom_TrimmedCurve(thecirc,udeb,ufin);
	  
	  scurv = new Select3D_SensitiveCurve(own, thecu);
	  aSel->Add(scurv);
	}
      else if ( curv->IsInstance(STANDARD_TYPE(Geom_Ellipse)) ) // case of ellipse
	{
	  // segment on ellipse
	  Handle(Geom_Ellipse) theEll = (Handle(Geom_Ellipse)&) curv;
	  Standard_Real udeb = ElCLib::Parameter(theEll->Elips(),mySecondPnt1);
	  Standard_Real ufin = ElCLib::Parameter(theEll->Elips(),mySecondPnt2);
	  Handle(Geom_TrimmedCurve) thecu = new Geom_TrimmedCurve(theEll,udeb,ufin);
	  
	  scurv = new Select3D_SensitiveCurve(own, thecu);
	  aSel->Add(scurv);
	}
    }
}

//=======================================================================
//function : ComputeFaceFromPnt
//purpose  : 
//=======================================================================
void AIS_MidPointRelation::ComputeFaceFromPnt(const Handle(Prs3d_Presentation)&,
					      const Standard_Boolean /*first*/)
{
}

//=======================================================================
//function : ComputeEdgeFromPnt
//purpose  : 
//=======================================================================
void AIS_MidPointRelation::ComputeEdgeFromPnt(const Handle(Prs3d_Presentation)& aprs,
					      const Standard_Boolean first)
{
  TopoDS_Edge E;
  if ( first ) E = TopoDS::Edge(myFShape);
  else         E = TopoDS::Edge(mySShape);

  Handle(Geom_Curve) geom;
  gp_Pnt ptat1,ptat2;
  Handle(Geom_Curve) extCurv;
  Standard_Boolean isInfinite,isOnPlane;
  if ( !AIS::ComputeGeometry(E, geom, ptat1, ptat2, extCurv, isInfinite, isOnPlane, myPlane) ) return;

  gp_Ax2 ax = myPlane->Pln().Position().Ax2();

  if ( geom->IsInstance(STANDARD_TYPE(Geom_Line)) )
    {
      if ( !isInfinite ) ComputePointsOnLine(ptat1,ptat2,first);
      else
	{
	  const gp_Lin& line = ((Handle(Geom_Line)&) geom)->Lin();
	  ComputePointsOnLine(line,first);
	}
      if ( first ) DsgPrs_MidPointPresentation::Add(aprs,myDrawer,ax,myMidPoint,myPosition,
						    myFAttach,myFirstPnt1,myFirstPnt2,first);
      else         DsgPrs_MidPointPresentation::Add(aprs,myDrawer,ax,myMidPoint,myPosition,
						    mySAttach,mySecondPnt1,mySecondPnt2,first);
    }
  else if ( geom->IsInstance(STANDARD_TYPE(Geom_Circle)) )
    {
      const Handle(Geom_Circle)& geom_cir = (Handle(Geom_Circle)&) geom;
      gp_Circ circ (geom_cir->Circ());
      ComputePointsOnCirc(circ,ptat1,ptat2,first);
      if ( first ) DsgPrs_MidPointPresentation::Add(aprs,myDrawer,circ,myMidPoint,myPosition,
						    myFAttach,myFirstPnt1,myFirstPnt2,first);
      else         DsgPrs_MidPointPresentation::Add(aprs,myDrawer,circ,myMidPoint,myPosition,
						    mySAttach,mySecondPnt1,mySecondPnt2,first);
    }
  else if ( geom->IsInstance(STANDARD_TYPE(Geom_Ellipse)) )
    {
      const Handle(Geom_Ellipse)& geom_ell = (Handle(Geom_Ellipse)&) geom;
      gp_Elips elips (geom_ell->Elips());
      ComputePointsOnElips(elips,ptat1,ptat2,first);
      if ( first ) DsgPrs_MidPointPresentation::Add(aprs,myDrawer,elips,myMidPoint,myPosition,
						    myFAttach,myFirstPnt1,myFirstPnt2,first);
      else         DsgPrs_MidPointPresentation::Add(aprs,myDrawer,elips,myMidPoint,myPosition,
						    mySAttach,mySecondPnt1,mySecondPnt2,first);
    }
  else return;

  // projection on myPlane
  if ( !isOnPlane ) ComputeProjEdgePresentation(aprs,E,geom,ptat1,ptat2);
}

//=======================================================================
//function : ComputeVertexFromPnt
//purpose  : 
//=======================================================================
void AIS_MidPointRelation::ComputeVertexFromPnt(const Handle(Prs3d_Presentation)& aprs,
						const Standard_Boolean first)
{
  gp_Ax2 ax = myPlane->Pln().Position().Ax2();
  if ( first )
    {
      Standard_Boolean isOnPlane;
      TopoDS_Vertex V = TopoDS::Vertex(myFShape);
      AIS::ComputeGeometry(V, myFAttach, myPlane, isOnPlane);
      DsgPrs_MidPointPresentation::Add(aprs,myDrawer,ax,myMidPoint,myPosition,myFAttach,first);
      if ( !isOnPlane ) ComputeProjVertexPresentation(aprs,V,myFAttach);
    }
  else
    {
      Standard_Boolean isOnPlane;
      TopoDS_Vertex V = TopoDS::Vertex(mySShape);
      AIS::ComputeGeometry(V, mySAttach, myPlane, isOnPlane);
      DsgPrs_MidPointPresentation::Add(aprs,myDrawer,ax,myMidPoint,myPosition,mySAttach,first);
      if ( !isOnPlane ) ComputeProjVertexPresentation(aprs,V,mySAttach);
    }
}

//=======================================================================
//function : ComputePointsOnLine
//purpose  : 
//=======================================================================
void AIS_MidPointRelation::ComputePointsOnLine(const gp_Lin& aLin,
					       const Standard_Boolean first)
{
  Standard_Real ppar = ElCLib::Parameter(aLin,myMidPoint);
  gp_Pnt anAttach = ElCLib::Value(ppar,aLin);

  Standard_Real dist = anAttach.Distance(myMidPoint)/10.0;
  if ( dist < Precision::Confusion() ) dist = 10.0;

  Standard_Real fpar = ppar + dist;
  Standard_Real spar = ppar - dist;

  gp_Pnt aPnt1 = ElCLib::Value(fpar,aLin);
  gp_Pnt aPnt2 = ElCLib::Value(spar,aLin);

  if ( first )
    {
      myFAttach = anAttach;
      myFirstPnt1 = aPnt1;
      myFirstPnt2 = aPnt2;
    }
  else
    {
      mySAttach = anAttach;
      mySecondPnt1 = aPnt1;
      mySecondPnt2 = aPnt2;
    }
}

//=======================================================================
//function : ComputePointsOnLine
//purpose  : 
//=======================================================================
void AIS_MidPointRelation::ComputePointsOnLine(const gp_Pnt& pnt1, const gp_Pnt& pnt2,
					       const Standard_Boolean first)
{
  gp_Vec aVec (pnt1,pnt2);
  gp_Lin aLin (pnt1,gp_Dir(aVec));

  Standard_Real fpar = ElCLib::Parameter(aLin,pnt1);
  Standard_Real spar = ElCLib::Parameter(aLin,pnt2);
  Standard_Real ppar = ElCLib::Parameter(aLin,myMidPoint);

  gp_Pnt aProjPnt = ElCLib::Value(ppar,aLin);
  Standard_Real dist = myMidPoint.Distance(aProjPnt);
  Standard_Real ll = pnt1.Distance(pnt2);
  Standard_Real segm = Min(dist,ll)*0.75;
  if ( dist < Precision::Confusion() ) segm = ll*0.75;

  gp_Pnt anAttach,aPnt1,aPnt2;
  anAttach = aProjPnt;
  gp_Vec aVecTr;
  if ( ppar <= fpar )
    {
      aPnt2 = pnt1;
      aVecTr = gp_Vec(pnt2,pnt1);
      aVecTr.Normalize();
      aPnt1 = aProjPnt.Translated(aVecTr*segm);
    }
  else if ( ppar >= spar )
    {
      aPnt1 = pnt2;
      aVecTr = gp_Vec(pnt1,pnt2);
      aVecTr.Normalize();
      aPnt2 = aProjPnt.Translated(aVecTr*segm);
    }
  else
    {
      Standard_Real dp1 = aProjPnt.Distance(pnt1);
      Standard_Real dp2 = aProjPnt.Distance(pnt2);

      segm = Min(dist,dp1)*0.75;
      aVecTr = gp_Vec(aProjPnt,pnt1);
      aVecTr.Normalize();
      aPnt1 = aProjPnt.Translated(aVecTr*segm);

      segm = Min(dist,dp2)*0.75;
      aVecTr = gp_Vec(aProjPnt,pnt2);
      aVecTr.Normalize();
      aPnt2 = aProjPnt.Translated(aVecTr*segm);
    }

  if ( first )
    {
      myFAttach = anAttach;
      myFirstPnt1 = aPnt1;
      myFirstPnt2 = aPnt2;
    }
  else
    {
      mySAttach = anAttach;
      mySecondPnt1 = aPnt1;
      mySecondPnt2 = aPnt2;
    }
}

//=======================================================================
//function : ComputePointsOnCirc
//purpose  : 
//=======================================================================
void AIS_MidPointRelation::ComputePointsOnCirc(const gp_Circ& aCirc,
					       const gp_Pnt& pnt1, const gp_Pnt& pnt2,
					       const Standard_Boolean first)
{
  gp_Pnt curpos = myMidPoint;

  // Case of confusion between the current position and the center 
  // of the circle -> we move the current position
  Standard_Real confusion (Precision::Confusion());
  gp_Pnt aCenter = aCirc.Location();
  if ( aCenter.Distance(curpos) <= confusion )
    {
      gp_Vec vprec(aCenter, pnt1);
      vprec.Normalize();
      curpos.Translate(vprec*1e-5);
    }
  
  Standard_Real pcurpos = ElCLib::Parameter(aCirc,curpos);

  Standard_Real rad = M_PI / 5.0;
  Standard_Real segm;

  Standard_Real pFPnt;
  Standard_Real pSPnt;

  if ( pnt1.IsEqual(pnt2,confusion) ) // full circle
    {
      pFPnt = pcurpos - rad;
      pSPnt = pcurpos + rad;
    }
  else
    {
      Standard_Real pFAttach = ElCLib::Parameter(aCirc,pnt1);
      Standard_Real pSAttach = ElCLib::Parameter(aCirc,pnt2);

      Standard_Real pSAttachM = pSAttach;
      Standard_Real deltap = pSAttachM - pFAttach;
      if ( deltap < 0 )
	{
	  deltap += 2 * M_PI;
	  pSAttachM += 2 * M_PI;
	}
      pSAttachM -= pFAttach;

      Standard_Real pmiddleout = pSAttachM/2.0 + M_PI;

      Standard_Real pcurpos1 = pcurpos;
      // define where curpos lays
      if ( pcurpos1 < pFAttach )
	{
	  pcurpos1 = pcurpos1 + 2 * M_PI - pFAttach;
	  if ( pcurpos1 > pSAttachM ) // out
	    {
	      segm = Min(rad,deltap*0.75);
	      if ( pcurpos1 > pmiddleout )
		{
		  pcurpos = pFAttach;
		  pFPnt = pFAttach;
		  pSPnt = pFAttach + segm;
		}
	      else
		{
		  pcurpos = pSAttach;
		  pFPnt = pSAttach - segm;
		  pSPnt = pSAttach;
		}
	    }
	  else // on arc
	    {
	      Standard_Real dp1 = pcurpos1 - pFAttach;
	      Standard_Real dp2 = pSAttachM - pcurpos1;

	      segm = Min(rad,dp1*0.75);
	      pFPnt = pcurpos - segm;
	      
	      segm = Min(rad,dp2*0.75);
	      pSPnt = pcurpos + segm;
	    }
	}
      else if ( pcurpos1 > (pFAttach + deltap) ) // out
	{
	  pcurpos1 -= pFAttach;
	  segm = Min(rad,deltap*0.75);
	  if ( pcurpos1 > pmiddleout )
	    {
	      pcurpos = pFAttach;
	      pFPnt = pFAttach;
	      pSPnt = pFAttach + segm;
	    }
	  else
	    {
	      pcurpos = pSAttach;
	      pFPnt = pSAttach - segm;
	      pSPnt = pSAttach;
	    }
	}
      else // on arc
	{
	  Standard_Real dp1 = pcurpos1 - pFAttach;
	  Standard_Real dp2 = pSAttach - pcurpos1;

	  segm = Min(rad,dp1*0.75);
	  pFPnt = pcurpos - segm;
	  
	  segm = Min(rad,dp2*0.75);
	  pSPnt = pcurpos + segm;
	}
    }

  if ( first )
    {
      myFAttach   = ElCLib::Value(pcurpos,aCirc);
      myFirstPnt1 = ElCLib::Value(pFPnt,aCirc);
      myFirstPnt2 = ElCLib::Value(pSPnt,aCirc);
    }
  else
    {
      mySAttach    = ElCLib::Value(pcurpos,aCirc);
      mySecondPnt1 = ElCLib::Value(pFPnt,aCirc);
      mySecondPnt2 = ElCLib::Value(pSPnt,aCirc);
    }
}

//=======================================================================
//function : ComputePointsOnElips
//purpose  : 
//=======================================================================
void AIS_MidPointRelation::ComputePointsOnElips(const gp_Elips& anEll,
						const gp_Pnt& pnt1, const gp_Pnt& pnt2,
					        const Standard_Boolean first)
{
  gp_Pnt curpos = myMidPoint;

  // Case of confusion between the current position and the center 
  // of the circle -> we move the current position
  Standard_Real confusion (Precision::Confusion());
  gp_Pnt aCenter = anEll.Location();
  if ( aCenter.Distance(curpos) <= confusion )
    {
      gp_Vec vprec(aCenter, pnt1);
      vprec.Normalize();
      curpos.Translate(vprec*1e-5);
    }
  
  Standard_Real pcurpos = ElCLib::Parameter(anEll,curpos);

  Standard_Real rad = M_PI / 5.0;
  Standard_Real segm;

  Standard_Real pFPnt;
  Standard_Real pSPnt;

  if ( pnt1.IsEqual(pnt2,confusion) ) // full circle
    {
      pFPnt = pcurpos - rad;
      pSPnt = pcurpos + rad;
    }
  else
    {
      Standard_Real pFAttach = ElCLib::Parameter(anEll,pnt1);
      Standard_Real pSAttach = ElCLib::Parameter(anEll,pnt2);

      Standard_Real pSAttachM = pSAttach;
      Standard_Real deltap = pSAttachM - pFAttach;
      if ( deltap < 0 )
	{
	  deltap += 2 * M_PI;
	  pSAttachM += 2 * M_PI;
	}
      pSAttachM -= pFAttach;

      Standard_Real pmiddleout = pSAttachM / 2.0 + M_PI;

      Standard_Real pcurpos1 = pcurpos;
      // define where curpos lays
      if ( pcurpos1 < pFAttach )
	{
	  pcurpos1 = pcurpos1 + 2 * M_PI - pFAttach;
	  if ( pcurpos1 > pSAttachM ) // out
	    {
	      segm = Min(rad,deltap*0.75);
	      if ( pcurpos1 > pmiddleout )
		{
		  pcurpos = pFAttach;
		  pFPnt = pFAttach;
		  pSPnt = pFAttach + segm;
		}
	      else
		{
		  pcurpos = pSAttach;
		  pFPnt = pSAttach - segm;
		  pSPnt = pSAttach;
		}
	    }
	  else // on arc
	    {
	      Standard_Real dp1 = pcurpos1 - pFAttach;
	      Standard_Real dp2 = pSAttachM - pcurpos1;

	      segm = Min(rad,dp1*0.75);
	      pFPnt = pcurpos - segm;
	      
	      segm = Min(rad,dp2*0.75);
	      pSPnt = pcurpos + segm;
	    }
	}
      else if ( pcurpos1 > (pFAttach + deltap) ) // out
	{
	  pcurpos1 -= pFAttach;
	  segm = Min(rad,deltap*0.75);
	  if ( pcurpos1 > pmiddleout )
	    {
	      pcurpos = pFAttach;
	      pFPnt = pFAttach;
	      pSPnt = pFAttach + segm;
	    }
	  else
	    {
	      pcurpos = pSAttach;
	      pFPnt = pSAttach - segm;
	      pSPnt = pSAttach;
	    }
	}
      else // on arc
	{
	  Standard_Real dp1 = pcurpos1 - pFAttach;
	  Standard_Real dp2 = pSAttach - pcurpos1;

	  segm = Min(rad,dp1*0.75);
	  pFPnt = pcurpos - segm;
	  
	  segm = Min(rad,dp2*0.75);
	  pSPnt = pcurpos + segm;
	}
    }

  if ( first )
    {
      myFAttach   = ElCLib::Value(pcurpos,anEll);
      myFirstPnt1 = ElCLib::Value(pFPnt,anEll);
      myFirstPnt2 = ElCLib::Value(pSPnt,anEll);
    }
  else
    {
      mySAttach    = ElCLib::Value(pcurpos,anEll);
      mySecondPnt1 = ElCLib::Value(pFPnt,anEll);
      mySecondPnt2 = ElCLib::Value(pSPnt,anEll);
    }
}
