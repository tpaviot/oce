// File:	BRepAlgo_Loop.cxx
// Created:	Fri Nov 10 16:25:22 1995
// Author:	Yves FRICAUD
//		<yfr@stylox>

#include <stdio.h>

#include <BRepAlgo_Loop.ixx>

#include <BRep_Builder.hxx>
#include <BRepAlgo_FaceRestrictor.hxx>
#include <BRep_Tool.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom_Surface.hxx>
#include <TopExp.hxx>
#include <TopTools_SequenceOfShape.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfShapeListOfShape.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <Precision.hxx>
#include <BRep_TVertex.hxx>
#include <BRep_TEdge.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfShapeShape.hxx>

#ifdef DRAW
#include <DBRep.hxx>
#endif
#ifdef DEB
Standard_Boolean AffichLoop  = Standard_False;
Standard_Integer NbLoops     = 0;
Standard_Integer NbWires     = 1;
static char* name = new char[100];
#endif

//=======================================================================
//function : BRepAlgo_Loop
//purpose  : 
//=======================================================================

BRepAlgo_Loop::BRepAlgo_Loop()
{
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void BRepAlgo_Loop::Init(const TopoDS_Face& F)
{
  myConstEdges.Clear(); 
  myVerOnEdges.Clear();
  myNewWires  .Clear();
  myNewFaces  .Clear();
  myNewEdges  .Clear();
  myFace = F;
}


//=======================================================================
//function : Bubble
//purpose  : Ordonne la sequence de vertex en parametre croissant. 
//=======================================================================

static void Bubble(const TopoDS_Edge&        E,
		   TopTools_SequenceOfShape& Seq) 
{
  Standard_Boolean Invert   = Standard_True;
  Standard_Integer NbPoints = Seq.Length();
  Standard_Real    U1,U2;
  TopoDS_Vertex    V1,V2;

  while (Invert) {
    Invert = Standard_False;
    for ( Standard_Integer i = 1; i < NbPoints; i++) {
      TopoDS_Shape aLocalV = Seq.Value(i)  .Oriented(TopAbs_INTERNAL);
      V1 = TopoDS::Vertex(aLocalV);
      aLocalV = Seq.Value(i+1).Oriented(TopAbs_INTERNAL);
      V2 = TopoDS::Vertex(aLocalV);
//      V1 = TopoDS::Vertex(Seq.Value(i)  .Oriented(TopAbs_INTERNAL));
//      V2 = TopoDS::Vertex(Seq.Value(i+1).Oriented(TopAbs_INTERNAL));

      U1 = BRep_Tool::Parameter(V1,E);
      U2 = BRep_Tool::Parameter(V2,E);
      if (U2 < U1) {
	Seq.Exchange(i,i+1);
	Invert = Standard_True;
      }
    }
  }
}



//=======================================================================
//function : AddEdges
//purpose  : 
//=======================================================================

void BRepAlgo_Loop::AddEdge (TopoDS_Edge&                E, 
			     const TopTools_ListOfShape& LV)
{
  myVerOnEdges.Bind(E,LV);
}


//=======================================================================
//function : AddConstEdges
//purpose  : 
//=======================================================================

void BRepAlgo_Loop::AddConstEdge (const TopoDS_Edge& E)
{
  myConstEdges.Append(E);
}

//=======================================================================
//function : AddConstEdges
//purpose  : 
//=======================================================================

void BRepAlgo_Loop::AddConstEdges(const TopTools_ListOfShape& LE)
{
  TopTools_ListIteratorOfListOfShape itl(LE);
  for (; itl.More(); itl.Next()) {
    myConstEdges.Append(itl.Value());
  }
}


//=======================================================================
//function : UpdateClosedEdge
//purpose  : Si le premier ou dernier vertex d intersection
//           coincide avec le vertex de fermeture il est supprime de SV.
//           il sera ajoute au debut et a la fin de SV par l appelant.
//=======================================================================

static TopoDS_Vertex  UpdateClosedEdge(const TopoDS_Edge&         E,
				       TopTools_SequenceOfShape&  SV)
{
  TopoDS_Vertex    VB [2], V1, V2, VRes;
  gp_Pnt           P,PC;
  Standard_Boolean OnStart = 0, OnEnd = 0;
  //// modified by jgv, 13.04.04 for OCC5634 ////
  TopExp::Vertices (E,V1,V2);
  //Standard_Real    Tol = Precision::Confusion();
  Standard_Real    Tol = BRep_Tool::Tolerance( V1 );
  ///////////////////////////////////////////////
  
  if (SV.IsEmpty()) return VRes;

  VB[0] = TopoDS::Vertex(SV.First());
  VB[1] = TopoDS::Vertex(SV.Last ());
  PC = BRep_Tool::Pnt(V1);

  for ( Standard_Integer i = 0 ; i < 2 ; i++) {
    P = BRep_Tool::Pnt(VB [i]);
    if (P.IsEqual(PC,Tol)) {
      VRes = VB [i];
      if (i == 0) OnStart = Standard_True;
      else        OnEnd   = Standard_True;
    }
  }
  if (OnStart && OnEnd) {
    if (!VB[0].IsSame(VB[1])) {
#ifdef DEB
      if (AffichLoop)
	cout <<" Deux vertex different sur vertex de fermeture"<<endl;
#endif
    }
    else {
      SV.Remove(1);
      if (!SV.IsEmpty()) SV.Remove(SV.Length());
    }
  }
  else if (OnStart) SV.Remove(1);
  else if (OnEnd  ) SV.Remove(SV.Length());

  return VRes;
}



//=======================================================================
//function : RemovePendingEdges
//purpose  : 
//=======================================================================

static void RemovePendingEdges(TopTools_DataMapOfShapeListOfShape& MVE)
{
  //--------------------------------
  // Suppression des edges pendants.
  //--------------------------------
  TopTools_DataMapIteratorOfDataMapOfShapeListOfShape Mapit;
  TopTools_ListOfShape                     ToRemove;
  TopTools_ListIteratorOfListOfShape       itl;
  Standard_Boolean                         YaSupress = Standard_True;
  TopoDS_Vertex                            V1,V2;
  
  while (YaSupress) {
    YaSupress = Standard_False;
    TopTools_ListOfShape VToRemove;
    TopTools_MapOfShape  EToRemove;

    for (Mapit.Initialize(MVE); Mapit.More(); Mapit.Next()) {

      if (Mapit.Value().IsEmpty()) {
	VToRemove.Append(Mapit.Key());
      }
      if (Mapit.Value().Extent() == 1) {
	const TopoDS_Edge& E = TopoDS::Edge(Mapit.Value().First());
	TopExp::Vertices(E,V1,V2) ;
	if (!V1.IsSame(V2)) {
	  VToRemove.Append(Mapit.Key());
	  EToRemove.Add(Mapit.Value().First());
	}
      }
    }
    
    if (!VToRemove.IsEmpty()) {
      YaSupress = Standard_True;
      for (itl.Initialize(VToRemove); itl.More(); itl.Next()) {
	MVE.UnBind(itl.Value());
      }
      if (!EToRemove.IsEmpty()) {
	for (Mapit.Initialize(MVE); Mapit.More(); Mapit.Next()) {
	  TopTools_ListOfShape& LE = MVE.ChangeFind(Mapit.Key());
	  itl.Initialize(LE);
	  while (itl.More()) {
	    if (EToRemove.Contains(itl.Value())) {
	      LE.Remove(itl);
	    }
	    else itl.Next();
	  }
	}
      }
    } 
  }
}
//=======================================================================
//function : SamePnt2d
//purpose  : 
//=======================================================================

static Standard_Boolean  SamePnt2d(TopoDS_Vertex  V,
				   TopoDS_Edge&   E1,
				   TopoDS_Edge&   E2,
				   TopoDS_Face&   F)
{
  Standard_Real   f1,f2,l1,l2;
  gp_Pnt2d        P1,P2;
  TopoDS_Shape aLocalF = F.Oriented(TopAbs_FORWARD);
  TopoDS_Face FF = TopoDS::Face(aLocalF);
//  TopoDS_Face FF = TopoDS::Face(F.Oriented(TopAbs_FORWARD));
  Handle(Geom2d_Curve) C1 = BRep_Tool::CurveOnSurface(E1,FF,f1,l1);  
  Handle(Geom2d_Curve) C2 = BRep_Tool::CurveOnSurface(E2,FF,f2,l2);  
  if (E1.Orientation () == TopAbs_FORWARD) P1 = C1->Value(f1);
  else                                     P1 = C1->Value(l1);
  
  if (E2.Orientation () == TopAbs_FORWARD) P2 = C2->Value(l2);
  else                                     P2 = C2->Value(f2);
  Standard_Real Tol  = 100*BRep_Tool::Tolerance(V);
  Standard_Real Dist = P1.Distance(P2);
  return Dist < Tol; 
}

//=======================================================================
//function : SelectEdge
//purpose  : Trouve l edge <NE> connexe a <CE> par le vertex <CV> dans
//           la liste <LE>. <NE> est supprime de la liste. Si <CE> est 
//           aussi dans la liste <LE> avec la meme orientation, il est
//           supprime de la liste.
//=======================================================================

static Standard_Boolean  SelectEdge(const TopoDS_Face&    F,
				    const TopoDS_Edge&    CE,
				    const TopoDS_Vertex&  CV,
				    TopoDS_Edge&          NE,
				    TopTools_ListOfShape& LE)
{
  TopTools_ListIteratorOfListOfShape itl;
  NE.Nullify();
#ifdef DEB  
  if (AffichLoop) {
    if ( LE.Extent() > 2) {
      cout <<"vertex sur plus de 2 edges dans une face."<<endl;
    }
  }
#endif
  for ( itl.Initialize(LE); itl.More(); itl.Next()) {
    if (itl.Value().IsEqual(CE)) {
      LE.Remove(itl);
      break;
    }
  }
  if (LE.Extent() > 1) {
    //--------------------------------------------------------------
    // Plusieurs edges possibles. 
    // - Test les edges differentes de CE , Selection de l edge
    // pour lequel CV a les U,V les plus proches dans la face
    // que ceux correspondant a CE.
    // - Si plusieurs edge donne des representation < la tolerance.
    // discrimination sur les tangentes.
    //--------------------------------------------------------------
    TopLoc_Location L;
    Standard_Real   f,l;
    TopoDS_Face FForward = F;
    FForward.Orientation(TopAbs_FORWARD);

    Handle(Geom2d_Curve) C = BRep_Tool::CurveOnSurface(CE,FForward,f,l);
    Standard_Integer k = 1, kmin = 0;
    Standard_Real    dist,distmin  = 100*BRep_Tool::Tolerance(CV);
    Standard_Real    u ;
    if (CE.Orientation () == TopAbs_FORWARD) u = l;
    else                                     u = f;

    gp_Pnt2d         P2,PV = C->Value(u); 
    
    for ( itl.Initialize(LE); itl.More(); itl.Next()) {
      const TopoDS_Edge& E = TopoDS::Edge(itl.Value());
      if (!E.IsSame(CE)) {
	C    = BRep_Tool::CurveOnSurface(E,FForward,f,l);
	if (E.Orientation () == TopAbs_FORWARD) u = f;
	else                                    u = l;
	P2   = C->Value(u); 
	dist = PV.Distance(P2);
	if ( dist <= distmin) {
	  kmin    = k;
	  distmin = dist;
	}
      }
      k++;
    }
    if (kmin == 0) return Standard_False;

    k = 1; itl.Initialize(LE);
    while (k < kmin) {k++; itl.Next();}
    NE = TopoDS::Edge(itl.Value());
    LE.Remove(itl);
  }
  else if (LE.Extent() == 1) {
    NE = TopoDS::Edge(LE.First());
    LE.RemoveFirst();
  }
  else {
    return Standard_False;
  }
#ifdef DRAW
  if (AffichLoop) {  
    DBRep::Set("Selected",NE);
  }

#endif
  return Standard_True;
}
//=======================================================================
//function : Store
//purpose  : 
//=======================================================================

static void  PurgeNewEdges(TopTools_DataMapOfShapeListOfShape& NewEdges,
			   const TopTools_MapOfShape&          UsedEdges)
{
  TopTools_DataMapIteratorOfDataMapOfShapeListOfShape it(NewEdges);
  for (; it.More(); it.Next()) {
    TopTools_ListOfShape& LNE = NewEdges.ChangeFind(it.Key());
    TopTools_ListIteratorOfListOfShape itL(LNE);
    while (itL.More()) {
      const TopoDS_Shape& NE = itL.Value();
      if (!UsedEdges.Contains(NE)) {
	LNE.Remove(itL);
      }
      else {
	itL.Next();
      }
    }
  }
  
}

//=======================================================================
//function : Store
//purpose  : 
//=======================================================================

static void StoreInMVE (const TopoDS_Face&                  F,
			TopoDS_Edge&                  E,
			TopTools_DataMapOfShapeListOfShape& MVE,
			Standard_Boolean&                   YaCouture,
			TopTools_DataMapOfShapeShape& VerticesForSubstitute )
{      
  TopoDS_Vertex V1, V2, V;
  TopTools_ListOfShape Empty;
  
  Standard_Real Tol = 0.001; //5.e-05; //5.e-07;
//  gp_Pnt P1, P2, P;
  gp_Pnt P1, P;
  TopTools_DataMapIteratorOfDataMapOfShapeListOfShape Mapit;
  BRep_Builder BB;
  for (Mapit.Initialize( MVE ); Mapit.More(); Mapit.Next())
    {
      V = TopoDS::Vertex( Mapit.Key() );
      P = BRep_Tool::Pnt( V );
      TopTools_ListOfShape VList;
      TopoDS_Iterator VerExp( E );
      for (; VerExp.More(); VerExp.Next())
	VList.Append( VerExp.Value() );
      TopTools_ListIteratorOfListOfShape itl( VList );
      for (; itl.More(); itl.Next())
	{
	  V1 = TopoDS::Vertex( itl.Value() );
	  P1 = BRep_Tool::Pnt( V1 );
	  if (P.IsEqual( P1, Tol ) && !V.IsSame(V1))
	    {
	      V.Orientation( V1.Orientation() );
	      if (VerticesForSubstitute.IsBound( V1 ))
		{
		  TopoDS_Shape OldNewV = VerticesForSubstitute( V1 );
		  if (! OldNewV.IsSame( V ))
		    {
		      VerticesForSubstitute.Bind( OldNewV, V );
		      VerticesForSubstitute( V1 ) = V;
		    }
		}
	      else
		{
		  if (VerticesForSubstitute.IsBound( V ))
		    {
		      TopoDS_Shape NewNewV = VerticesForSubstitute( V );
		      if (! NewNewV.IsSame( V1 ))
			VerticesForSubstitute.Bind( V1, NewNewV );
		    }
		  else
		    {
		      VerticesForSubstitute.Bind( V1, V );
		      TopTools_DataMapIteratorOfDataMapOfShapeShape mapit( VerticesForSubstitute );
		      for (; mapit.More(); mapit.Next())
			if (mapit.Value().IsSame( V1 ))
			  VerticesForSubstitute( mapit.Key() ) = V;
		    }
		}
	      E.Free( Standard_True );
	      BB.Remove( E, V1 );
	      BB.Add( E, V );
	    }
	}
    }

  TopExp::Vertices(E,V1,V2);
  if( V1.IsNull() && V2.IsNull() ){ YaCouture = Standard_False; return; }
  if (!MVE.IsBound(V1)) {
    MVE.Bind(V1,Empty);
  }
  MVE(V1).Append(E);
  if (!V1.IsSame(V2)) {
     if (!MVE.IsBound(V2)) {
      MVE.Bind(V2,Empty);
    }
    MVE(V2).Append(E);
  }
  TopLoc_Location L ;
  Handle(Geom_Surface) S = BRep_Tool::Surface(F,L);
  if (BRep_Tool::IsClosed(E,S,L)) {
    MVE(V2).Append(E.Reversed());
    if (!V1.IsSame(V2)) {
      MVE(V1).Append(E.Reversed());
    }
    YaCouture = Standard_True;
  }
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void BRepAlgo_Loop::Perform()
{
  TopTools_DataMapIteratorOfDataMapOfShapeListOfShape Mapit;  
  TopTools_ListIteratorOfListOfShape                  itl;
  TopoDS_Vertex                                       V1,V2;
  Standard_Boolean                                    YaCouture = Standard_False;

#ifdef DEB
  if (AffichLoop) {
    cout <<"NewLoop"<<endl;
    NbLoops++;
#ifdef DRAW
    Standard_Integer NbEdges = 1;
    sprintf(name,"FLoop_%d",NbLoops);
    DBRep::Set(name,myFace);
    for (Mapit.Initialize(myVerOnEdges); Mapit.More(); Mapit.Next()) { 
      const TopoDS_Edge& E = TopoDS::Edge(Mapit.Key());
      sprintf(name,"EEE_%d_%d",NbLoops,NbEdges++);
      DBRep::Set(name,E);
    }
    for (itl.Initialize(myConstEdges); itl.More(); itl.Next()) {
      const TopoDS_Edge& E = TopoDS::Edge(itl.Value());    
      sprintf(name,"EEE_%d_%d",NbLoops,NbEdges++);
      DBRep::Set(name,E);
    }
#endif
  }
#endif
  
  //------------------------------------------------
  // Decoupe des edges
  //------------------------------------------------
  for (Mapit.Initialize(myVerOnEdges); Mapit.More(); Mapit.Next()) {
    TopTools_ListOfShape LCE;

    CutEdge (TopoDS::Edge(Mapit.Key()),Mapit.Value(), LCE);

    myNewEdges.Bind(Mapit.Key(),LCE);
  }
  //-----------------------------------
  // Construction map vertex => edges
  //-----------------------------------
  TopTools_DataMapOfShapeListOfShape MVE;

  // ajout des edges decoupees.
  for (Mapit.Initialize(myNewEdges); Mapit.More(); Mapit.Next()) {
    for (itl.Initialize(myNewEdges(Mapit.Key())); itl.More(); itl.Next()) {
      TopoDS_Edge& E = TopoDS::Edge(itl.Value());
      StoreInMVE(myFace,E,MVE,YaCouture,myVerticesForSubstitute);
    }
  }
  
  // ajout des edges const
  // Les edges de couture peuvent etre doubles ou non dans myConstEdges
  // => appel une seule fois StoreInMVE qui se charge de les doubler
  TopTools_MapOfShape DejaVu;
  for (itl.Initialize(myConstEdges); itl.More(); itl.Next()) {
    TopoDS_Edge& E = TopoDS::Edge(itl.Value());
    if (DejaVu.Add(E))
      StoreInMVE(myFace,E,MVE,YaCouture,myVerticesForSubstitute);
  }

#ifdef DRAW
  if (AffichLoop) {
    cout <<"NewLoop"<<endl;
    Standard_Integer NbEdges = 1;
    TopTools_MapOfShape Done;
    for (Mapit.Initialize(MVE); Mapit.More();Mapit.Next()) {
      for (itl.Initialize(Mapit.Value()); itl.More(); itl.Next()) {
	TopoDS_Edge& E = TopoDS::Edge(itl.Value());
	if (Done.Add(E)) {
	  sprintf(name,"EEC_%d_%d",NbLoops,NbEdges++);
	  DBRep::Set(name,E);
	}
      }
    }
  }
#endif

  //-----------------------------------------------
  // Construction des wires et des nouvelles faces. 
  //----------------------------------------------
  TopoDS_Vertex    VF,VL,CV;
  TopoDS_Edge      CE,NE,EF;
  BRep_Builder     B;
  TopoDS_Wire      NW;
  Standard_Boolean End;

  TopTools_MapOfShape UsedEdges;

  while (!MVE.IsEmpty()) {
    B.MakeWire(NW);
    //--------------------------------
    // Suppression des edges pendants.
    //--------------------------------
    RemovePendingEdges(MVE);

    if (MVE.IsEmpty()) break; 
    //--------------------------------
    // Edge de depart.
    //--------------------------------
    Mapit.Initialize(MVE);
    EF = CE = TopoDS::Edge(Mapit.Value().First());
    TopExp::Vertices(CE,V1,V2);
    //--------------------------------
    // VF vertex debut du nouveau wire
    //--------------------------------
    if (CE.Orientation() == TopAbs_FORWARD) { CV = VF = V1;}
    else                                    { CV = VF = V2;}
    if (!MVE.IsBound(CV)) continue;
    for ( itl.Initialize(MVE(CV)); itl.More(); itl.Next()) {
      if (itl.Value().IsEqual(CE)) {
	MVE(CV).Remove(itl);
	break;
      }
    }
    End  = Standard_False;
    
    while (!End) {
      //-------------------------------
      // Construction d un wire.
      //-------------------------------
      TopExp::Vertices(CE,V1,V2);
      if (!CV.IsSame(V1)) CV = V1; else CV = V2;

      B.Add (NW,CE);
      UsedEdges.Add(CE);

      if (!MVE.IsBound(CV) || MVE(CV).IsEmpty()) {
	End = Standard_True;
      }
      else {
	End = !SelectEdge(myFace,CE,CV,NE,MVE(CV));
	if (!End) {
	  CE = NE;
	  if (MVE(CV).IsEmpty()) MVE.UnBind(CV);
	}	
      }
    }
    //--------------------------------------------------
    // Ajout du nouveau wire dans l ensemble des wires
    //------------------------------------------------
    Standard_Real Tol = 0.001; //5.e-05; //5.e-07;
    TopExp_Explorer explo( NW, TopAbs_VERTEX );
    for (; explo.More(); explo.Next())
      {
	const TopoDS_Vertex& aV = TopoDS::Vertex( explo.Current() );
	Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*) &(aV).TShape());
	TV->Tolerance( Tol );
	TV->Modified( Standard_True );
      }
    for (explo.Init( NW, TopAbs_EDGE ); explo.More(); explo.Next())
      {
	const TopoDS_Edge& aE = TopoDS::Edge( explo.Current() );
	Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &(aE).TShape());
	TE->Tolerance( Tol );
	TE->Modified( Standard_True );
      }

    if (VF.IsSame(CV) && SamePnt2d(VF,EF,CE,myFace))
      myNewWires.Append (NW);
    else {
#ifdef DEB
      cout <<"BRepAlgo_Loop: Open Wire"<<endl;
      if (AffichLoop)
	cout << "OpenWire is : NW_"<<NbLoops<<"_"<<NbWires<<endl;
#endif
    }
#ifdef DRAW
    if (AffichLoop) {
      sprintf(name,"NW_%d_%d",NbLoops,NbWires++);	
      DBRep::Set(name,NW);
    }
#endif
  }
  
  PurgeNewEdges(myNewEdges,UsedEdges);
}

//=======================================================================
//function : CutEdges
//purpose  : 
//=======================================================================

void BRepAlgo_Loop::CutEdge (const TopoDS_Edge&          E,
			     const TopTools_ListOfShape& VOnE,
			             TopTools_ListOfShape& NE   ) const 
{
  TopoDS_Shape aLocalE  = E.Oriented(TopAbs_FORWARD);
  TopoDS_Edge WE = TopoDS::Edge(aLocalE);
//  TopoDS_Edge WE = TopoDS::Edge(E.Oriented(TopAbs_FORWARD));

  Standard_Real                      U1,U2;
  TopoDS_Vertex                      V1,V2;
  TopTools_SequenceOfShape           SV;
  TopTools_ListIteratorOfListOfShape it(VOnE);
  BRep_Builder                       B;

  for ( ; it.More(); it.Next()) {
    SV.Append(it.Value());
  }
  //--------------------------------
  // Tri des vertex sur l edge.
  //--------------------------------
  Bubble (WE,SV);

  Standard_Integer NbVer = SV.Length();
  //----------------------------------------------------------------
  // Construction des nouvelles edges.
  // Remarque : les vertex extremites de l edges ne sont pas 
  //            forcement dans la liste des vertex
  //----------------------------------------------------------------
  if (SV.IsEmpty()) {
    NE.Append(E);
    return;
  }
  TopoDS_Vertex    VF,VL;
  Standard_Real    f,l;
  BRep_Tool::Range(WE,f,l);
  TopExp::Vertices(WE,VF,VL);

  if (NbVer == 2) {
    if (SV(1).IsEqual(VF) && SV(2).IsEqual(VL)) {
      NE.Append(E);
#ifdef DRAW
      if (AffichLoop) {  
      DBRep::Set("ECOpied",E);
    }      
#endif
      return;
    }
  }
  //----------------------------------------------------
  // Traitement des edges fermes
  // Si un vertex d intersection est sur le vertex
  // commun il doit apparaitre eb debut et en fin de SV.
  //----------------------------------------------------
  TopoDS_Vertex VCEI;
  if (!VF.IsNull() && VF.IsSame(VL)) {
    VCEI = UpdateClosedEdge(WE,SV);    
    if (!VCEI.IsNull()) {
      TopoDS_Shape aLocalV = VCEI.Oriented(TopAbs_FORWARD);
      VF = TopoDS::Vertex(aLocalV);
      aLocalV = VCEI.Oriented(TopAbs_REVERSED); 
      VL = TopoDS::Vertex(aLocalV);
//      VF = TopoDS::Vertex(VCEI.Oriented(TopAbs_FORWARD));
//      VL = TopoDS::Vertex(VCEI.Oriented(TopAbs_REVERSED)); 
    }
    SV.Prepend(VF);
    SV.Append(VL);
  }
  else {
    //-----------------------------------------
    // Ajout eventuel des extremites de l edge.
    //-----------------------------------------
    if (!VF.IsNull() && !VF.IsSame(SV.First())) SV.Prepend(VF);
    if (!VL.IsNull() && !VL.IsSame(SV.Last ())) SV.Append (VL);
  }

  while (!SV.IsEmpty()) {
    while (!SV.IsEmpty() && 
	   SV.First().Orientation() != TopAbs_FORWARD) {
      SV.Remove(1);
    }
    if (SV.IsEmpty())
      break;
    V1  = TopoDS::Vertex(SV.First());
    SV.Remove(1);
    if (SV.IsEmpty())
      break;
    if (SV.First().Orientation() == TopAbs_REVERSED) {
      V2  = TopoDS::Vertex(SV.First());
      SV.Remove(1);
      //-------------------------------------------
      // Copie de l edge et restriction par V1 V2.
      //-------------------------------------------
      TopoDS_Shape NewEdge = WE.EmptyCopied();
      TopoDS_Shape aLocalEdge = V1.Oriented(TopAbs_FORWARD);
      B.Add  (NewEdge,aLocalEdge);
      aLocalEdge = V2.Oriented(TopAbs_REVERSED);
      B.Add  (TopoDS::Edge(NewEdge),aLocalEdge);
//      B.Add  (NewEdge,V1.Oriented(TopAbs_FORWARD));
//      B.Add  (NewEdge,V2.Oriented(TopAbs_REVERSED));
      if (V1.IsSame(VF)) 
	U1 = f;
      else 
//	U1=BRep_Tool::Parameter
//	  (TopoDS::Vertex(V1.Oriented(TopAbs_INTERNAL)),WE);
	{
	  TopoDS_Shape aLocalV = V1.Oriented(TopAbs_INTERNAL);
	  U1=BRep_Tool::Parameter(TopoDS::Vertex(aLocalV),WE);
	}
      if (V2.IsSame(VL))
	U2 = l;
      else
	{
	  TopoDS_Shape aLocalV = V2.Oriented(TopAbs_INTERNAL);
	  U2=BRep_Tool::Parameter(TopoDS::Vertex(aLocalV),WE);
//	U2=BRep_Tool::Parameter
//	  (TopoDS::Vertex(V2.Oriented(TopAbs_INTERNAL)),WE);
	}
      B.Range (TopoDS::Edge(NewEdge),U1,U2);
#ifdef DRAW
    if (AffichLoop) {  
      DBRep::Set("Cut",NewEdge);
    }
#endif
      NE.Append(NewEdge.Oriented(E.Orientation()));
    }
  }

  //Remove edges with size <= tolerance
  Standard_Real Tol = 0.001; //5.e-05; //5.e-07;
  it.Initialize(NE);
  while (it.More())
    {
      // skl : I change "E" to "EE"
      TopoDS_Edge EE = TopoDS::Edge( it.Value() );
      Standard_Real fpar, lpar;
      BRep_Tool::Range( EE, fpar, lpar );
      if (lpar - fpar <= Precision::Confusion())
	NE.Remove(it);
      else
	{
	  gp_Pnt2d pf, pl;
	  BRep_Tool::UVPoints( EE, myFace, pf, pl );
	  if (pf.Distance(pl) <= Tol && !EE.Closed())
	    NE.Remove(it);
	  else
	    it.Next();
	}
    }
}

//=======================================================================
//function : NewWires
//purpose  : 
//=======================================================================

const TopTools_ListOfShape&  BRepAlgo_Loop::NewWires() const 
{  
  return myNewWires;
}

//=======================================================================
//function : NewFaces
//purpose  : 
//=======================================================================

const TopTools_ListOfShape&  BRepAlgo_Loop::NewFaces() const 
{  
  return myNewFaces;
}
 
//=======================================================================
//function : WiresToFaces
//purpose  : 
//=======================================================================

void  BRepAlgo_Loop::WiresToFaces() 
{  
  if (!myNewWires.IsEmpty()) {
    BRepAlgo_FaceRestrictor FR;
    TopoDS_Shape aLocalS = myFace.Oriented(TopAbs_FORWARD);
    FR.Init (TopoDS::Face(aLocalS),Standard_False);
//    FR.Init (TopoDS::Face(myFace.Oriented(TopAbs_FORWARD)),
//	     Standard_False);
    TopTools_ListIteratorOfListOfShape it(myNewWires);
    for (; it.More(); it.Next()) {
      FR.Add(TopoDS::Wire(it.Value()));
    }

    FR.Perform();
    
    if (FR.IsDone()) {
      TopAbs_Orientation OriF = myFace.Orientation();
      for (; FR.More(); FR.Next()) {
	myNewFaces.Append(FR.Current().Oriented(OriF));
      }
    }
  }
}


//=======================================================================
//function : NewEdges
//purpose  : 
//=======================================================================

const TopTools_ListOfShape&  BRepAlgo_Loop::NewEdges(const TopoDS_Edge& E) const 
{
  return myNewEdges(E);
}

//=======================================================================
//function : GetVerticesForSubstitute
//purpose  : 
//=======================================================================

void  BRepAlgo_Loop::GetVerticesForSubstitute( TopTools_DataMapOfShapeShape& VerVerMap ) const
{
  VerVerMap = myVerticesForSubstitute;
}
//=======================================================================
//function : VerticesForSubstitute
//purpose  : 
//=======================================================================

void  BRepAlgo_Loop::VerticesForSubstitute( TopTools_DataMapOfShapeShape& VerVerMap )
{
  myVerticesForSubstitute = VerVerMap;
}
