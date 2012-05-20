// Created on: 1995-02-22
// Created by: Jacques GOUSSARD
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



#include <BRepOffsetAPI_DraftAngle.ixx>

#include <Draft_Modification.hxx>
#include <TopoDS.hxx>
#include <Geom_Surface.hxx>
#include <TopLoc_Location.hxx>

#include <TopTools_ListIteratorOfListOfShape.hxx>

#include <BRepLib.hxx>
#include <BRepFill_DataMapOfShapeSequenceOfReal.hxx>
#include <TopTools_DataMapOfShapeSequenceOfShape.hxx>
#include <TopTools_SequenceOfShape.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepTools.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <TColStd_SequenceOfReal.hxx>
#include <TopOpeBRep_EdgesIntersector.hxx>
#include <TopOpeBRep_Point2d.hxx>
#include <Precision.hxx>
#include <BRepFill_DataMapIteratorOfDataMapOfShapeSequenceOfReal.hxx>
#include <BRepOffsetAPI_SequenceOfSequenceOfReal.hxx>
#include <BRepOffsetAPI_SequenceOfSequenceOfShape.hxx>
#include <BRepTools_Substitution.hxx>
#include <BRep_Builder.hxx>
#include <TopExp.hxx>
#include <BRep_Tool.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepLib_MakeVertex.hxx>
#include <BRep_TEdge.hxx>
#include <BRep_ListIteratorOfListOfCurveRepresentation.hxx>
#include <BRep_GCurve.hxx>
#include <TopoDS_Wire.hxx>
#include <BRepAdaptor_Curve2d.hxx>

//=======================================================================
//function : BRepOffsetAPI_DraftAngle
//purpose  : 
//=======================================================================

BRepOffsetAPI_DraftAngle::BRepOffsetAPI_DraftAngle () {}


//=======================================================================
//function : BRepOffsetAPI_DraftAngle
//purpose  : 
//=======================================================================

BRepOffsetAPI_DraftAngle::BRepOffsetAPI_DraftAngle (const TopoDS_Shape& S)
{
  myInitialShape = S;
  myModification = new Draft_Modification(S);
}


//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================

void BRepOffsetAPI_DraftAngle::Clear ()
{
  if (!myModification.IsNull()) {
    (*((Handle(Draft_Modification)*)&myModification))->Clear();
  }
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void BRepOffsetAPI_DraftAngle::Init (const TopoDS_Shape& S)
{
  myInitialShape = S;
  NotDone();
  if (!myModification.IsNull()) {
    (*((Handle(Draft_Modification)*)&myModification))->Init(S);   
  }
  else {
    myModification = new Draft_Modification(S);
  }
}


//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void BRepOffsetAPI_DraftAngle::Add(const TopoDS_Face& F,
			     const gp_Dir& D,
			     const Standard_Real Angle,
			     const gp_Pln& Plane,
                             const Standard_Boolean Flag)
{
// POP-DPF : protection
  if ( Abs(Angle) <= 1.e-04 ) 
    return;
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),"");
  (*((Handle(Draft_Modification)*)&myModification))->Add(F,D,Angle,Plane, Flag);
}


//=======================================================================
//function : AddDone
//purpose  : 
//=======================================================================

Standard_Boolean BRepOffsetAPI_DraftAngle::AddDone () const
{
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),"");
  return (*((Handle(Draft_Modification)*)&myModification))
    ->ProblematicShape().IsNull();
}


//=======================================================================
//function : Remove
//purpose  : 
//=======================================================================

void BRepOffsetAPI_DraftAngle::Remove(const TopoDS_Face& F)
{
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),"");
  (*((Handle(Draft_Modification)*)&myModification))->Remove(F);
}


//=======================================================================
//function : ProblematicShape
//purpose  : 
//=======================================================================

const TopoDS_Shape& BRepOffsetAPI_DraftAngle::ProblematicShape () const
{
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),"");
  return (*((Handle(Draft_Modification)*)&myModification))->ProblematicShape();
}


//=======================================================================
//function : ErrorStatus
//purpose  : 
//=======================================================================

Draft_ErrorStatus BRepOffsetAPI_DraftAngle::Status () const
{
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),"");
  return (*((Handle(Draft_Modification)*)&myModification))->Error();
}


//=======================================================================
//function : ConnectedFaces
//purpose  : 
//=======================================================================

const TopTools_ListOfShape& BRepOffsetAPI_DraftAngle::ConnectedFaces
   (const TopoDS_Face& F) const
{
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),"");
  return (*((Handle(Draft_Modification)*)&myModification))->ConnectedFaces(F);
}


//=======================================================================
//function : ModifiedFaces
//purpose  : 
//=======================================================================

const TopTools_ListOfShape& BRepOffsetAPI_DraftAngle::ModifiedFaces() const
{
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),"");
  return (*((Handle(Draft_Modification)*)&myModification))->ModifiedFaces();
}

//=======================================================================
//function : ModifiedFaces
//purpose  : 
//=======================================================================

const TopTools_ListOfShape& BRepOffsetAPI_DraftAngle::Generated(const TopoDS_Shape& S) 
{
  myGenerated.Clear();
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),"");
  Handle(Draft_Modification) DMod = (*((Handle(Draft_Modification)*)&myModification));

  if (S.ShapeType() == TopAbs_FACE) {
    Handle(Geom_Surface) Surf;
    TopLoc_Location      L;
    Standard_Real        Tol;
    Standard_Boolean     RW,RF;
    if (DMod->NewSurface(TopoDS::Face(S), Surf, L, Tol, RW, RF)) {
      myGenerated.Append(ModifiedShape (S));
 
    }
  }
  return myGenerated;
}

//=======================================================================
//function : ModifiedFaces
//purpose  : 
//=======================================================================

const TopTools_ListOfShape& BRepOffsetAPI_DraftAngle::Modified(const TopoDS_Shape& S) 
{
  myGenerated.Clear();
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),"");
  Handle(Draft_Modification) DMod = (*((Handle(Draft_Modification)*)&myModification));

  if (S.ShapeType() == TopAbs_FACE) {
    Handle(Geom_Surface) Surf;
    TopLoc_Location      L;
    Standard_Real        Tol;
    Standard_Boolean     RW,RF;
    
    if (!DMod->NewSurface(TopoDS::Face(S), Surf, L, Tol, RW, RF)) {
      // Ce n est pas une generation => peut etre une  modif
      myGenerated.Append(ModifiedShape (S));
      if (myGenerated.Extent() == 1 && myGenerated.First().IsSame(S)) {
	myGenerated.Clear();
      }
    }
  }
  return myGenerated;
}


//=======================================================================
//function : Build
//purpose  : 
//=======================================================================

void BRepOffsetAPI_DraftAngle::Build()
{
  (*((Handle(Draft_Modification)*)&myModification))->Perform();
  if (!(*((Handle(Draft_Modification)*)&myModification))->IsDone()) {
    NotDone();
  }
  else {
    DoModif(myInitialShape);
    //BRepLib::SameParameter( myShape, 1.0e-7, Standard_True ); //patch
    CorrectWires();
    BRepLib::SameParameter( myShape, 1.0e-7, Standard_True ); //patch
  }
}

//=======================================================================
//function : CorrectWires
//purpose  : 
//=======================================================================

void BRepOffsetAPI_DraftAngle::CorrectWires()
{
  Standard_Real TolInter = 1.e-7;
  Standard_Integer i, j, k;

  TopTools_SequenceOfShape Eseq;
  TopTools_SequenceOfShape Wseq;
  TopTools_SequenceOfShape Fseq;
  TopoDS_Shape CurEdge, CurWire, CurFace;
  TopoDS_Iterator wit, eit;

  TopExp_Explorer fexp( myShape, TopAbs_FACE );
  for (; fexp.More(); fexp.Next())
    {
      CurFace = fexp.Current();
      wit.Initialize( CurFace );
      for (; wit.More(); wit.Next())
	{
	  CurWire = wit.Value();
	  TopTools_MapOfShape emap;
	  eit.Initialize( CurWire );
	  for (; eit.More(); eit.Next())
	    emap.Add( eit.Value() );
	  TopTools_MapIteratorOfMapOfShape mapit( emap );
	  for (; mapit.More(); mapit.Next())
	    {
	      CurEdge = mapit.Key();
	      if (BRepTools::IsReallyClosed( TopoDS::Edge(CurEdge), TopoDS::Face(CurFace) ))
		{
		  Eseq.Append( CurEdge );
		  Wseq.Append( CurWire );
		  Fseq.Append( CurFace );
		}
	    }
	}
    }

  BRepFill_DataMapOfShapeSequenceOfReal Emap;

  TopTools_SequenceOfShape NonSeam;
  TopTools_SequenceOfShape NonSeamWires;
  BRepOffsetAPI_SequenceOfSequenceOfReal ParsNonSeam;
  BRepOffsetAPI_SequenceOfSequenceOfShape Seam;
  BRepOffsetAPI_SequenceOfSequenceOfReal ParsSeam;

  TopTools_DataMapOfShapeShape WFmap;
  TopTools_DataMapOfShapeListOfShape WWmap;
  for (i = 1; i <= Eseq.Length(); i++)
    {
      CurEdge = Eseq(i);
      CurWire = Wseq(i);
      CurFace = Fseq(i);
      wit.Initialize( CurFace );
      for (; wit.More(); wit.Next())
	{
	  TopoDS_Shape aWire = wit.Value();
	  if (! aWire.IsSame( CurWire ))
	    {
	      TColgp_SequenceOfPnt pts;
	      TopTools_SequenceOfShape edges;
	      TColStd_SequenceOfReal pars;
	      Standard_Boolean Wadd = Standard_False;
	      eit.Initialize( aWire );
	      for (; eit.More(); eit.Next())
		{
		  TopoDS_Shape anEdge = eit.Value();
		  TopOpeBRep_EdgesIntersector EInter;
		  EInter.SetFaces( CurFace, CurFace );
		  EInter.ForceTolerances( TolInter, TolInter );
		  EInter.Perform( CurEdge, anEdge );
		  if (EInter.IsEmpty())
		    {
		      EInter.Perform( CurEdge.Reversed(), anEdge );
		      if (EInter.IsEmpty())
			continue;
		    }
		  Wadd = Standard_True;
		  if (! WFmap.IsBound( aWire ))
		    WFmap.Bind( aWire, CurFace );
		  Standard_Integer ind = 0;
		  for (j = 1; j <= NonSeam.Length(); j++)
		    if (anEdge.IsSame( NonSeam(j) ))
		      {
			ind = j;
			break;
		      }
		  if (ind == 0)
		    {
		      NonSeam.Append( anEdge );
		      NonSeamWires.Append( aWire );
		      ind = NonSeam.Length();
		      TColStd_SequenceOfReal emptyseq1, emptyseq2;
		      TopTools_SequenceOfShape emptyedgeseq;
		      ParsNonSeam.Append( emptyseq1 );
		      Seam.Append( emptyedgeseq );
		      ParsSeam.Append( emptyseq2 );
		    }
		  if (! Emap.IsBound( CurEdge ))
		    {
		      TColStd_SequenceOfReal emptyseq;
		      Emap.Bind( CurEdge, emptyseq );
		    }
		  EInter.InitPoint();
		  for (; EInter.MorePoint(); EInter.NextPoint())
		    {
		      const TopOpeBRep_Point2d& bp = EInter.Point();
		      if (bp.IsVertex(2))
			{
			  gp_Pnt Pnt = bp.Value();
			  Standard_Integer ied = 0;
			  for (j = 1; j <= pts.Length(); j++)
			    if (Pnt.IsEqual( pts(j), Precision::Confusion() ))
			      {
				ied = j;
				break;
			      }
			  if (ied == 0)
			    {
			      pts.Append( Pnt );
			      edges.Append( anEdge );
			      pars.Append( bp.Parameter(2) );
			      Emap(CurEdge).Append( bp.Parameter(1) );
			      ParsNonSeam(ind).Append( bp.Parameter(2) );
			      Seam(ind).Append( CurEdge );
			      ParsSeam(ind).Append( bp.Parameter(1) );
			    }
			  /*
			  else
			    {
			      Standard_Real ParOnSeam = bp.Parameter(1);
			      Standard_Real Par1 = pars(ied);
			      Standard_Real Par2 = bp.Parameter(2);
			      BRepAdaptor_Curve2d SeamCurve( CurEdge, CurFace );
			      BRepAdaptor_Curve2d Curve1( edges(ied), CurFace );
			      BRepAdaptor_Curve2d Curve2( anEdge. CurFace );
			      gp_Pnt2d P2d;
			      gp_Vec2d SeamDer, Der1, Der2;
			      //SeamCurve->D1( ParOnSeam, P2d, SeamDer );
			      //Curve1->D1( Par1, P2d, Der1 );
			      //Curve2->D1( Par2, P2d, Der2 );
			      Standard_Real Crossed1 = SeamDer ^ Der1;
			      Standard_Real Crossed2 = SeamDer ^ Der2;
			      //if (Crossed1 > 0
			    }
			  */
			}
		      else // ! bp.IsVertex(2)
			{
			  //Temporary the case of tangency is not implemented
			  Emap(CurEdge).Append( bp.Parameter(1) );
			  ParsNonSeam(ind).Append( bp.Parameter(2) );
			  Seam(ind).Append( CurEdge );
			  ParsSeam(ind).Append( bp.Parameter(1) );
			}
		    } //for (; EInter.MorePoint(); EInter.NextPoint())
		} //for (; eit.More(); eit.Next())
	      if (Wadd)
		{
		  if (! WWmap.IsBound( CurWire ))
		    {
		      TopTools_ListOfShape emptylist;
		      WWmap.Bind( CurWire, emptylist );
		    }
		  WWmap(CurWire).Append( aWire );
		}
	    } //if (! aWire.IsSame( CurWire ))
	} //for (; wit.More(); wit.Next())
    } //for (i = 1; i <= Eseq.Length(); i++)

  //Sorting
  for (i = 1; i <= NonSeam.Length(); i++)
    for (j = 1; j < ParsNonSeam(i).Length(); j++)
      for (k = j+1; k <= ParsNonSeam(i).Length(); k++)
	if (ParsNonSeam(i)(k) < ParsNonSeam(i)(j))
	  {
	    Standard_Real temp = ParsNonSeam(i)(j);
	    ParsNonSeam(i)(j) = ParsNonSeam(i)(k);
	    ParsNonSeam(i)(k) = temp;
	    TopoDS_Shape tmp = Seam(i)(j);
	    Seam(i)(j) = Seam(i)(k);
	    Seam(i)(k) = tmp;
	    temp = ParsSeam(i)(j);
	    ParsSeam(i)(j) = ParsSeam(i)(k);
	    ParsSeam(i)(k) = temp;
	  }
  BRepFill_DataMapIteratorOfDataMapOfShapeSequenceOfReal iter( Emap );
  for (; iter.More(); iter.Next())
    {
      TColStd_SequenceOfReal Seq;
      Seq = iter.Value();
      for (i = 1; i < Seq.Length(); i++)
      for (j = i+1; j <= Seq.Length(); j++)
	if (Seq(j) < Seq(i))
	  {
	    Standard_Real temp = Seq(i);
	    Seq(i) = Seq(j);
	    Seq(j) = temp;
	  }
      Emap( iter.Key() ) = Seq;
    }
  BRepFill_DataMapOfShapeSequenceOfReal EPmap;
  TopTools_DataMapOfShapeSequenceOfShape EVmap; //Seam
  TopTools_DataMapOfShapeSequenceOfShape EWmap; //Seam and wires intersecting it
  iter.Initialize( Emap );
  for (; iter.More(); iter.Next())
    {
      TColStd_SequenceOfReal parseq;
      EPmap.Bind( iter.Key(), parseq );
      TopTools_SequenceOfShape shapeseq;
      EVmap.Bind( iter.Key(), shapeseq );
      TopTools_SequenceOfShape shapeseq2;
      EWmap.Bind( iter.Key(), shapeseq2 );
    }

  //Reconstruction of non-seam edges
  BRepTools_Substitution aSub;
  BRep_Builder BB;
  for (i = 1; i <= NonSeam.Length(); i++)
    {
      TopoDS_Edge anEdge = TopoDS::Edge( NonSeam(i) );
      TopTools_ListOfShape NewEdges;
      TopoDS_Edge NewE;
      TopoDS_Vertex Vfirst, Vlast;
      TopExp::Vertices( anEdge, Vfirst, Vlast );
      Standard_Real par, FirstPar, LastPar;
      BRep_Tool::Range( anEdge, FirstPar, LastPar );
      Standard_Integer firstind = 1;
      par = ParsNonSeam(i)(1);
      TopoDS_Edge SeamEdge = TopoDS::Edge( Seam(i)(1) );
      //Find the face
      for (j = 1; j <= Eseq.Length(); j++)
	if (SeamEdge.IsSame( Eseq(j) ))
	  break;
      TopoDS_Face theFace = TopoDS::Face( Fseq(j) );
      TopLoc_Location L;
      Handle( Geom_Surface ) theSurf = BRep_Tool::Surface( theFace, L );
      if (Abs(par-FirstPar) <= Precision::Confusion())
	{
	  BB.UpdateVertex( Vfirst, ParsSeam(i)(1), SeamEdge, BRep_Tool::Tolerance(Vfirst) );
	  EPmap( SeamEdge ).Append( ParsSeam(i)(1) );
	  EVmap( SeamEdge ).Append( Vfirst );
	  EWmap( SeamEdge ).Append( NonSeamWires(i) );
	  firstind = 2;
	}
      Standard_Real prevpar = FirstPar;
      TopoDS_Vertex PrevV = Vfirst;
      for (j = firstind; j <= ParsNonSeam(i).Length(); j++)
	{
	  TopoDS_Shape aLocalShape = anEdge.EmptyCopied();
	  NewE = TopoDS::Edge( aLocalShape );
	  //NewE = TopoDS::Edge( anEdge.EmptyCopied() );
	  TopoDS_Vertex NewV;
	  par = ParsNonSeam(i)(j);
	  BB.Range( NewE, prevpar, par );
	  SeamEdge = TopoDS::Edge( Seam(i)(j) );
	  if (j == ParsNonSeam(i).Length() && Abs(par-LastPar) <= Precision::Confusion())
	    {
	      NewV = Vlast;
	      if (firstind == 2 && j == 2)
		{
		  BB.UpdateVertex( Vlast, ParsSeam(i)(j), SeamEdge, BRep_Tool::Tolerance(Vlast) );
		  EPmap( SeamEdge ).Append( ParsSeam(i)(j) );
		  EVmap( SeamEdge ).Append( Vlast );
		  EWmap( SeamEdge ).Append( NonSeamWires(i) );
		  break;
		}
	    }
	  else
	    {
	      BRepAdaptor_Curve bcur( NewE );
	      gp_Pnt Point = bcur.Value( par );
	      NewV = BRepLib_MakeVertex( Point );
	      BB.UpdateVertex( NewV, par, NewE, 10.*Precision::Confusion() );
	    }
	  BB.UpdateVertex( NewV, ParsSeam(i)(j), SeamEdge, 10.*Precision::Confusion() );
	  NewE.Orientation( TopAbs_FORWARD );
	  BB.Add( NewE, PrevV.Oriented(TopAbs_FORWARD) );
	  BB.Add( NewE, NewV.Oriented(TopAbs_REVERSED) );

	  NewEdges.Append( NewE );
	  EPmap( SeamEdge ).Append( ParsSeam(i)(j) );
	  EVmap( SeamEdge ).Append( NewV );
	  EWmap( SeamEdge ).Append( NonSeamWires(i) );

	  prevpar = par;
	  PrevV = NewV;
	}
      //The last edge
      TopoDS_Shape aLocalShape = anEdge.EmptyCopied();
      NewE = TopoDS::Edge( aLocalShape );
      //NewE = TopoDS::Edge( anEdge.EmptyCopied() );
      par = LastPar;
      if (Abs(prevpar-par) > Precision::Confusion())
	{
	  BB.Range( NewE, prevpar, par );
	  NewE.Orientation( TopAbs_FORWARD );
	  BB.Add( NewE, PrevV.Oriented(TopAbs_FORWARD) );
	  BB.Add( NewE, Vlast.Oriented(TopAbs_REVERSED) );
	  NewEdges.Append( NewE );
	}

      //Substitute anEdge by NewEdges
      aSub.Substitute( anEdge, NewEdges );
    }
  
  //Sorting of EPmap and EVmap and removing repeating points from them
  iter.Initialize( EPmap );
  for (; iter.More(); iter.Next())
    {
      TColStd_SequenceOfReal Seq;
      Seq = iter.Value();
      TopTools_SequenceOfShape SeqShape;
      SeqShape = EVmap( iter.Key() );
      TopTools_SequenceOfShape SeqShape2;
      SeqShape2 = EWmap( iter.Key() );
      for (i = 1; i < Seq.Length(); i++)
      for (j = i+1; j <= Seq.Length(); j++)
	if (Seq(j) < Seq(i))
	  {
	    Standard_Real temp = Seq(i);
	    Seq(i) = Seq(j);
	    Seq(j) = temp;
	    TopoDS_Shape tmp = SeqShape(i);
	    SeqShape(i) = SeqShape(j);
	    SeqShape(j) = tmp;
	    tmp = SeqShape2(i);
	    SeqShape2(i) = SeqShape2(j);
	    SeqShape2(j) = tmp;
	  }
      EPmap( iter.Key() ) = Seq;
      EVmap( iter.Key() ) = SeqShape;
      EWmap( iter.Key() ) = SeqShape2;
    }
  iter.Initialize( EPmap );
  for (; iter.More(); iter.Next())
    {
      TColStd_SequenceOfReal Seq;
      Seq = iter.Value();
      TopTools_SequenceOfShape SeqShape;
      SeqShape = EVmap( iter.Key() );
      TopTools_SequenceOfShape SeqShape2;
      SeqShape2 = EWmap( iter.Key() );
      Standard_Boolean remove = Standard_True;
      while (remove)
	{
	  remove = Standard_False;
	  for (i = 1; i < Seq.Length(); i++)
	    if (Abs(Seq(i)-Seq(i+1)) <= Precision::Confusion())
	      {
		Seq.Remove(i+1);
		SeqShape.Remove(i+1);
		SeqShape2.Remove(i+1);
		remove = Standard_True;
	      }
	}
      EPmap( iter.Key() ) = Seq;
      EVmap( iter.Key() ) = SeqShape;
      EWmap( iter.Key() ) = SeqShape2;
    }

  //Reconstruction of seam edges
  TopTools_DataMapOfShapeShape VEmap;
  iter.Initialize( Emap );
  for (; iter.More(); iter.Next())
    {
      TopoDS_Edge anEdge = TopoDS::Edge( iter.Key() );
      Standard_Boolean onepoint = Standard_False;
      TopTools_ListOfShape NewEdges;
      TColStd_SequenceOfReal Seq;
      Seq = iter.Value();
      TColStd_SequenceOfReal Seq2;
      Seq2 = EPmap( anEdge );
      TopTools_SequenceOfShape SeqVer;
      SeqVer = EVmap( anEdge );
      TopTools_SequenceOfShape SeqWire;
      SeqWire = EWmap( anEdge );
      TopoDS_Vertex Vfirst, Vlast;
      TopExp::Vertices( anEdge, Vfirst, Vlast );
      Standard_Real fpar, lpar, FirstPar, LastPar;
      BRep_Tool::Range( anEdge, FirstPar, LastPar );
      fpar = FirstPar;
      lpar = Seq(1);
      TopoDS_Edge NewE;
      Standard_Integer firstind = 1;
      if (Abs(fpar-lpar) <= Precision::Confusion())
	{
	  firstind = 2;
	  fpar = Seq(1);
	  lpar = Seq(2);
	}
      else
	{
	  if (Seq.Length()%2 != 0)
	    {
	      VEmap.Bind( Vfirst, anEdge );
	      firstind = 2;
	      fpar = Seq(1);
	      if (Seq.Length() > 2)
		lpar = Seq(2);
	      else
		onepoint = Standard_True;
	    }
	}
      if (!onepoint)
	{
	  TopoDS_Shape aLocalShape = anEdge.EmptyCopied();
	  NewE = TopoDS::Edge( aLocalShape );
	  //NewE = TopoDS::Edge( anEdge.EmptyCopied() );
	  BB.Range( NewE, fpar, lpar );
	  NewE.Orientation( TopAbs_FORWARD );
	  if (firstind == 1)
	    {
	      BB.Add( NewE, Vfirst.Oriented(TopAbs_FORWARD) );
	      aLocalShape = SeqVer(1).Oriented(TopAbs_REVERSED);
	      BB.Add( NewE, TopoDS::Vertex( aLocalShape ) );
	      //BB.Add( NewE, TopoDS::Vertex( SeqVer(1).Oriented(TopAbs_REVERSED) ) );
	    }
	  else
	    {
	      aLocalShape = SeqVer(1).Oriented(TopAbs_FORWARD);
	      BB.Add( NewE, TopoDS::Vertex( aLocalShape ) );
	      aLocalShape = SeqVer(2).Oriented(TopAbs_REVERSED);
	      BB.Add( NewE, TopoDS::Vertex( aLocalShape ) );
	      //BB.Add( NewE, TopoDS::Vertex( SeqVer(1).Oriented(TopAbs_FORWARD) ) );
	      //BB.Add( NewE, TopoDS::Vertex( SeqVer(2).Oriented(TopAbs_REVERSED) ) );
	    }
	  NewEdges.Append( NewE );
	  
	  firstind++;
	  for (i = firstind; i < Seq.Length(); i += 2)
	    {
	      aLocalShape = anEdge.EmptyCopied();
	      NewE = TopoDS::Edge( aLocalShape );
	      //NewE = TopoDS::Edge( anEdge.EmptyCopied() );
	      fpar = Seq(i);
	      lpar = Seq(i+1);
	      BB.Range( NewE, fpar, lpar );
	      //Find vertices
	      for (j = 1; j <= Seq2.Length(); j++)
		if (Abs(fpar-Seq2(j)) <= Precision::Confusion())
		  break;
	      NewE.Orientation( TopAbs_FORWARD );
	      TopoDS_Shape aLocalShape = SeqVer(j).Oriented(TopAbs_FORWARD);
	      BB.Add( NewE, TopoDS::Vertex( aLocalShape ) );
	      aLocalShape = SeqVer(j+1).Oriented(TopAbs_REVERSED);
	      BB.Add( NewE, TopoDS::Vertex( aLocalShape ) );
	      //BB.Add( NewE, TopoDS::Vertex( SeqVer(j).Oriented(TopAbs_FORWARD) ) );
	      //BB.Add( NewE, TopoDS::Vertex( SeqVer(j+1).Oriented(TopAbs_REVERSED) ) );
	      NewEdges.Append( NewE );
	    }
	}

      i = Seq.Length();
      fpar = Seq(i);
      lpar = LastPar;
      if (Abs(fpar-lpar) <= Precision::Confusion())
	continue;
      TopoDS_Shape aLocalShape = anEdge.EmptyCopied();
      NewE = TopoDS::Edge( aLocalShape );
      //NewE = TopoDS::Edge( anEdge.EmptyCopied() );
      BB.Range( NewE, fpar, lpar );
      NewE.Orientation( TopAbs_FORWARD );
      aLocalShape = SeqVer(SeqVer.Length()).Oriented(TopAbs_FORWARD);
      BB.Add( NewE, TopoDS::Vertex( aLocalShape ) );
      //BB.Add( NewE, TopoDS::Vertex( SeqVer(SeqVer.Length()).Oriented(TopAbs_FORWARD) ) );
      BB.Add( NewE, Vlast.Oriented(TopAbs_REVERSED) );
      NewEdges.Append( NewE );

      //Substitute anEdge by NewEdges
      aSub.Substitute( anEdge, NewEdges );
    }

  //Removing edges connected with missing extremities of seam edges
  TopTools_DataMapIteratorOfDataMapOfShapeShape itve( VEmap );
  for (; itve.More(); itve.Next())
    {
      TopoDS_Shape V = itve.Key();
      TopoDS_Shape E = itve.Value();
      TopoDS_Shape W;
      for (i = 1; i <= Eseq.Length(); i++)
	if (E.IsSame( Eseq(i) ))
	  {
	    W = Wseq(i);
	    break;
	  }
      TopoDS_Shape Etoremove;
      eit.Initialize( W );
      for (; eit.More(); eit.Next())
	{
	  TopoDS_Edge CurE = TopoDS::Edge( eit.Value() );
	  if (CurE.IsSame( E ))
	    continue;
	  TopoDS_Vertex Vfirst, Vlast;
	  TopExp::Vertices( CurE, Vfirst, Vlast );
	  if (Vfirst.IsSame( V ) || Vlast.IsSame( V ))
	    {
	      Etoremove = CurE;
	      break;
	    }
	}
      if (! Etoremove.IsNull())
	{
	  W.Free( Standard_True );
	  BB.Remove( W, Etoremove );
	}
    }

  aSub.Build( myShape );
  if (aSub.IsCopied( myShape ))
    {
      const TopTools_ListOfShape& listSh = aSub.Copy( myShape );
      if (! listSh.IsEmpty())
	myShape = listSh.First();
    }

  //Reconstruction of wires
  TopTools_ListOfShape theCopy;
  TopTools_DataMapIteratorOfDataMapOfShapeListOfShape itww( WWmap );
  for (; itww.More(); itww.Next())
    {
      CurWire = itww.Key();
      theCopy = aSub.Copy( CurWire );
      CurWire = theCopy.First();
      CurWire.Free( Standard_True );
      TopTools_ListIteratorOfListOfShape itl( itww.Value() );
      for (; itl.More(); itl.Next())
	{
	  TopoDS_Shape aWire = itl.Value();
	  CurFace = WFmap( aWire );
	  theCopy = aSub.Copy( aWire );
	  aWire = theCopy.First();
	  //Adjusting period
	  TopLoc_Location L;
	  Handle( Geom_Surface ) theSurf = BRep_Tool::Surface( TopoDS::Face(CurFace), L );
	  eit.Initialize( aWire );
	  for (; eit.More(); eit.Next())
	    {
	      TopoDS_Edge anEdge = TopoDS::Edge( eit.Value() );
	      gp_Pnt2d Pfirst, Plast, Pmid;
	      BRep_Tool::UVPoints( anEdge, TopoDS::Face(CurFace), Pfirst, Plast );
	      BRepAdaptor_Curve2d bc2d( anEdge, TopoDS::Face(CurFace) );
	      Pmid = bc2d.Value( (bc2d.FirstParameter()+bc2d.LastParameter())/2. );
	      gp_Vec2d offset;
	      Standard_Boolean translate = Standard_False;
	      if (Pfirst.X()-2.*M_PI > Precision::Confusion() ||
		  Plast.X()-2.*M_PI > Precision::Confusion()  ||
		  Pmid.X()-2.*M_PI > Precision::Confusion())
		{
		  offset.SetCoord( -2.*M_PI, 0 );
		  translate = Standard_True;
		}
	      if (Pfirst.X() < -Precision::Confusion() ||
		  Plast.X() < -Precision::Confusion()  ||
		  Pmid.X() < -Precision::Confusion())
		{
		  offset.SetCoord( 2.*M_PI, 0 );
		  translate = Standard_True;
		}
	      if (translate)
		{
		  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &anEdge.TShape());
		  BRep_ListIteratorOfListOfCurveRepresentation itcr( TE->ChangeCurves() );
		  Handle(BRep_GCurve) GC;
		  
		  for (; itcr.More(); itcr.Next())
		    {
		      GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
		      if (!GC.IsNull() && GC->IsCurveOnSurface( theSurf, L ))
			{
			  Handle(Geom2d_Curve) PC = GC->PCurve();
			  PC = Handle(Geom2d_Curve)::DownCast( PC->Translated( offset ) );
			  GC->PCurve( PC );
			  TE->ChangeCurves().Remove( itcr );
			  TE->ChangeCurves().Append( GC );
			  break;
			}
		    }
		}
	    }
	  ///////////////////
	  eit.Initialize( aWire, Standard_False );
	  for (; eit.More(); eit.Next())
	    {
	      TopoDS_Shape anEdge = eit.Value();
	      BB.Add( CurWire, anEdge );
	    }
	  if (aSub.IsCopied( CurFace ))
	    {
	      theCopy = aSub.Copy( CurFace );
	      CurFace = theCopy.First();
	    }
	  CurFace.Free( Standard_True );
	  BB.Remove( CurFace, aWire );
	}
    }
}
