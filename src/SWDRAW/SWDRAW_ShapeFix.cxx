// File:	SWDRAW_ShapeFix.cxx
// Created:	Tue Mar  9 15:49:13 1999
// Author:	data exchange team
//		<det@kinox.nnov.matra-dtv.fr>


#include <SWDRAW_ShapeFix.ixx>
#include <DBRep.hxx>
#include <SWDRAW.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt2d.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <BRepBuilderAPI.hxx>
#include <BRepTopAdaptor_FClass2d.hxx>

#include <ShapeBuild_ReShape.hxx>
#include <ShapeAnalysis_Edge.hxx>
#include <ShapeAnalysis_WireOrder.hxx>
#include <ShapeAnalysis_WireVertex.hxx>
#include <ShapeAnalysis_Wire.hxx>
#include <ShapeExtend_WireData.hxx>
#include <ShapeFix.hxx>
#include <ShapeFix_ShapeTolerance.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeFix_WireVertex.hxx>
#include <ShapeFix_Wireframe.hxx>
#include <ShapeFix_Face.hxx>
#include <ShapeFix_Shape.hxx>
#include <Precision.hxx>
#include <ShapeExtend_DataMapOfShapeListOfMsg.hxx>
#include <ShapeExtend_MsgRegistrator.hxx>
#include <ShapeExtend_DataMapIteratorOfDataMapOfShapeListOfMsg.hxx>
#include <Message_ListIteratorOfListOfMsg.hxx>
#include <Message_Msg.hxx>
#include <TCollection_AsciiString.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopTools_DataMapOfShapeListOfShape.hxx>
#include <TopAbs_State.hxx>

#ifdef AIX
#include <strings.h>
#endif
#include <stdio.h>
#include <ShapeExtend_WireData.hxx>

//=======================================================================
//function : edgesameparam
//purpose  : 
//=======================================================================

static Standard_Integer edgesameparam (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
//  const Standard_CString arg1 = argv[1];
  const Standard_CString arg2 (argc > 2 ? argv[2] : NULL);
//        ****    Edge:SameParameter         ****
  if (argc < 2) { di<<"shapename ,  option f to force, else only Edges not-SameParameter are computed"<<"\n"; return 1 /* Error */; }
  TopoDS_Shape Shape = DBRep::Get(argv[1]);

  if (!ShapeFix::SameParameter(Shape, (argc > 2 && arg2[0] == 'f') , BRepBuilderAPI::Precision()) )
    di<<"Some edges were not processed"<<"\n";
  di<<"\n";
  return 0; // Done
}

//=======================================================================
//function : settolerance
//purpose  : 
//=======================================================================

static Standard_Integer settolerance (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 3) {
    di<<    "myshape val   : forces tolerances at <val>"<<"\n"
      <<      "myshape < max : sets maximum tolerance to <max>"<<"\n"
	<<    "myshape > min : sets minimum tolerance to <min>"<<"\n"
	  <<  "myshape min max : bounds tolerances between <min> and <max>"<<"\n"
	    <<"myshape mode=v-e-f other args : idem but only on vertex-edge-face"<<"\n";
    return (argc < 2 ? 0 : 1 /* Error */);
  }
  Standard_CString arg1 = argv[1];
  Standard_CString arg2 = argv[2];
  TopoDS_Shape Shape = DBRep::Get(arg1);
  if (Shape.IsNull()) { di<<"Shape unknown : "<<arg1<<"\n"; return 1 /* Error */; }
  char mod2 = arg2[0];
  Standard_Integer premarg = 2;
  TopAbs_ShapeEnum styp = TopAbs_SHAPE;
  if (mod2 == 'v') { styp = TopAbs_VERTEX; premarg = 3; }
  if (mod2 == 'e') { styp = TopAbs_EDGE;   premarg = 3; }
  if (mod2 == 'w') { styp = TopAbs_WIRE;   premarg = 3; }
  if (mod2 == 'f') { styp = TopAbs_FACE;   premarg = 3; }
  if (mod2 == 'a') { styp = TopAbs_SHAPE;  premarg = 3; }

  Standard_Real tmin,tmax;
  mod2 = argv[premarg][0];
  if (mod2 == '=') tmin = tmax = atof (argv[argc-1]);
  else if (mod2 == '<') { tmin = 0; tmax = atof (argv[argc-1]); }
  else if (mod2 == '>') { tmin = atof (argv[argc-1]); tmax = 0; }
  else { tmin = atof (argv[premarg]);  tmax = atof (argv[argc-1]); }

  if (argc == premarg + 1 || tmin == tmax) di<<"Setting Tolerance to "<<tmin<<"\n";
  else if (tmax < tmin) di<<"Minimum Tolerance to "<<tmin<<"\n";
  else if (tmin <= 0)   di<<"Maximum Tolerance to "<<tmax<<"\n";
  else                  di<<"Tolerance Limited between "<<tmin<<" and "<<tmax<<"\n";
  ShapeFix_ShapeTolerance sat;
  sat.LimitTolerance (Shape,tmin,tmax,styp);
  return 0; // Done
}

//=======================================================================
//function : stwire
//purpose  : 
//=======================================================================

static Standard_Integer stwire (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 2) { // help
    di<<"Donner nom shape depart + nom shape resultat + option"<<"\n";
    di<<"Options de chargement :  x add connected  (sinon add simple)\n"
      <<  "Options de traitement :  l fix little/BRepBuilderAPI\n"
      <<"Options de sortie : aucune make simple\n"
      <<"  m MakeAPI r avec reorder  v vertex\n"
      <<"Autres (se cumulent) :  q quid(stats)"<<"\n";
    return 0;
  }
  if (argc < 4) { di<<"stwire tout court pour help"<<"\n"; return 1 /* Error */; }
  Standard_CString arg1 = argv[1];
  Standard_CString arg2 = argv[2];

//  Options
  Standard_Integer i;  int ox,ol,om,orint,oq,ov;  ox=ol=om=orint=oq=ov=0;
  for (i = 3; i < argc; i ++) {
    int valopt = 1;
    char opt = argv[i][0];
    if (opt == '+')   opt = argv[i][1];
    if (opt == '-') { opt = argv[i][1]; valopt = 0; }
    switch (opt) {
    case 'l' : ol = valopt; break;
    case 'm' : om = valopt; break;
    case 'q' : oq = valopt; break;
    case 'r' : orint = valopt; break;
    case 'v' : ov = valopt; break;
    case 'x' : ox = valopt; break;
    default : break;
    }
  }
  TopoDS_Shape Shape = DBRep::Get(arg1);
  if (Shape.IsNull()) { di<<arg1<<" inconnu"<<"\n"; return 1 /* Error */; }

//  On y va
  Handle(ShapeExtend_WireData) sbwd = new ShapeExtend_WireData;
  Handle(ShapeAnalysis_Wire) saw = new ShapeAnalysis_Wire;
  saw->Load ( sbwd );
  
  TopoDS_Shape awire;  // en principe un Wire
  if (Shape.ShapeType() == TopAbs_WIRE) {
    awire = Shape;
  } else if (Shape.ShapeType() == TopAbs_FACE) {
    saw->SetFace (TopoDS::Face(Shape));
    TopExp_Explorer expw(Shape,TopAbs_WIRE);
    if (expw.More()) awire = expw.Current();
    saw->SetPrecision (BRepBuilderAPI::Precision());
  }
  if (awire.IsNull()) {
    di<<"Neither FACE nor WIRE : "<<arg1<<"\n";
    di<<"Considering as list of edges ..."<<"\n";
    awire = Shape;
//    return 1 /* Error */;
  }

// Chargement : normal ou par connected(oriented)
//  if (ox) {
    for (TopExp_Explorer exp(Shape,TopAbs_EDGE); exp.More(); exp.Next()) {
      TopoDS_Edge E = TopoDS::Edge (exp.Current());
      Standard_Integer orient = saw->CheckShapeConnect (E);
      di<<"Orientation : "<<orient<<" LowerDist : "<< saw->MinDistance3d() << "\n";
      if (ox) sbwd->AddOriented (E,orient);
      else sbwd->Add (E);
    }
//  }
//  else sbwd->Init (awire);
  
  Handle(ShapeFix_Wire) sfw = new ShapeFix_Wire;
  sfw->Init ( saw );

//   Traitement en cours
  if (ol) {
    Standard_Integer nb = sfw->NbEdges();
    for (i = 1; i <= nb; i ++) {
      Standard_Boolean stat = sfw->FixSmall (i, Standard_True, 0.0);
      //cout<<"FixSmall for"<<i<<(stat ? " done" : " not done"); //:sw <<" StatusFix="<<STW.StatusFix()<<"\n";
      di<<"FixSmall for"<<i;
      if (!stat) {
	di<<" not done";
      } else {
	di<<" done";
      }
      if ( sfw->LastFixStatus ( ShapeExtend_FAIL ) ) di << " (failed)";
      di << "\n";
    }
  }

//  Traitement
  if (orint) {  // reorder ?
    ShapeAnalysis_WireOrder WO ( (Shape.ShapeType() != TopAbs_FACE), BRepBuilderAPI::Precision());

    Standard_Integer stwo = saw->CheckOrder (WO);
    Standard_Integer nb = WO.NbEdges();
    di<<"Reorder status : "<<stwo<<"  NbEdges="<<nb<<"\n";
    for (i = 1; i <= nb; i ++) {
      Standard_Integer iord = WO.Ordered(i);
      di<<"Edge n0 "<<i;
      if ( sbwd->Edge(iord).Orientation() == TopAbs_REVERSED) di<<" REV";
      else di<<" FWD";
      di<<" ordered to "<<iord<<" Gap="<<WO.Gap(i)<<"\n";
    }
    di<<"Reorder not yet done"<<"\n";
    sfw->FixReorder (WO);
//   Mais on n execute pas
  }

//  Statistiques
  if (oq) {
    ShapeAnalysis_Edge sae;
    Standard_Integer nb = sbwd->NbEdges();
    di<<"NbEdges : "<<nb<<"\n";
    for (i = 1; i <= nb; i ++) {
      TopoDS_Edge E = sbwd->Edge(i);
      di<<"Edge "<<i;
      if (E.Orientation() == TopAbs_REVERSED) di<<" REV";
      else di<<" FWD";
      if (BRep_Tool::Degenerated(E)) di<<" DGNR";
      if (sbwd->IsSeam(i))        di<<" SEAM_WIRE";
      if (Shape.ShapeType() == TopAbs_FACE &&
	  sae.IsSeam(E,TopoDS::Face(Shape)))  di<<" SEAM_FACE";
      if (Shape.ShapeType() == TopAbs_FACE ) {
	if (sae.HasPCurve(E,TopoDS::Face(Shape)))     di<<" PCU";
	else di<<" NO_PCU";
      }
      if (sae.HasCurve3d(E))    di<<" C3D";
      else di<<" NO_C3D";
      if (sae.IsClosed3d(E))  di<<" CLOSED";
      di<<"\n";
    }
  }

//  Resultat
  TopoDS_Wire result;
  if (ov) {
    ShapeAnalysis_WireVertex sawv;
    sawv.Init ( sbwd, saw->Precision() );
    sawv.Analyze();
    Standard_Integer nb = sbwd->NbEdges();
    di<<"Nb(End)Vertex : "<<nb<<"\n";
    for (i = 1; i <= nb; i ++) {
      gp_XYZ pos; Standard_Real upre,ufol;
      Standard_Integer stat = sawv.Data (i,pos,upre,ufol);
      di<<i<<" : ";
      switch (stat) {
      case 0 : di<<"Same Vertex"<<"\n"; break;
      case 1 : di<<"Same Coords with recorded precisions (but not Same Vertex)"<<"\n"; break;
      case 2 : di<<"Close (with preci="<< saw->Precision()<<")"<<"\n"; break;
      case 3 : di<<"End of "<<i<<" OK, Start of "<<(i == nb ? 1 : i+1)<<" at U="<<ufol; break;
      case 4 : di<<"End of "<<i<<" at U="<<upre<<", Start of "<<(i == nb ? 1 : i+1)<<" OK"; break;
      case 5 : di<<"Intersection, End of "<<i<<" at U="<<upre<<", Start of "<<(i == nb ? 1 : i+1)<<" at U="<<ufol; break;
	default : di<<"Disjoined"<<"\n";
      }
      if (stat >= 3 && stat <= 5) di<<"\n   - Position : "<<pos.X()<<"  "<<pos.Y()<<"  "<<pos.Z()<<"\n";
    }
    ShapeFix_WireVertex sfwv;
    sfwv.Init ( sawv );
    di<<"Nb Fixed Vertex : "<< sfwv.Fix() <<"\n";
  }
  /*
  if (oc) {
    if ( Shape.ShapeType() == TopAbs_FACE ) {
      Correct_Wire CW ( TopoDS::Face(Shape) );
      Standard_Integer i, nb = sbwd->NbEdges();
      Standard_Integer num = 1;
      for (i = 1; i <= nb; i ++)  CW.Add (sbwd->Edge(i));
      CW.Perform ( saw->Precision() );
      nb = CW.NbWires();
      if (nb != 1) {
	//  On prend celui qui a le plus d edges
	Standard_Integer nbe, maxe = 0;
	for (i = 1; i <= nb; i ++) {
	  TopoDS_Wire wir = CW.Wire(i);
	  nbe = 0;
	  for (TopoDS_Iterator ite(wir); ite.More(); ite.Next()) nbe ++;
	  if (nbe > maxe) { num = i; maxe = nbe; }
	}
	di<<"Correct_Wire produced "<<nb<<" Wires, taken n0 "<<num<<"\n";
      }
      result = CW.Wire (num);
    }
    else di << "Cannot apply Correct_Wire: face not defined" << "\n";
  }
  */
  else if (om) result = sbwd->WireAPIMake();
  else         result = sbwd->Wire();
  if (result.IsNull()) {
    di<<"Pas de resultat, desole"<<"\n";
    return 1;  // Fail
  }
  DBRep::Set (arg2,result);
  return 0; // Done
}

//=======================================================================
//function : reface
//purpose  : 
//=======================================================================

static Standard_Integer reface (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 3) { di<<"Donner un nom de SHAPE (SHELL ou FACE) + un nom de RESULTAT"<<"\n"; return 1 /* Error */; }
  Standard_CString arg1 = argv[1];
  Standard_CString arg2 = argv[2];
  TopoDS_Shape Shape = DBRep::Get(arg1);
  if (Shape.IsNull()) { di<<"Shape unknown : "<<arg1<<"\n"; return 1 /* Error */; }

  Standard_Boolean rebuild = Standard_False;

  Handle(ShapeFix_Face) STF = new ShapeFix_Face;
//  Options ?
  Standard_Integer i; // svv Jan11 2000 : porting on DEC
  for (i = 3; i < argc; i ++) {
    Standard_Boolean valopt = Standard_True;
    char opt = argv[i][0];
    if (opt == '+')   opt = argv[i][1];
    if (opt == '-') { opt = argv[i][1]; valopt = Standard_False; }
    //cout<<(valopt ? ".." : ".. NO");
    if (!valopt) {
      di<<".. NO";
    } else {
      di<<"..";
    }

    if (opt == 'R') { di<<" REBUILD-ANYWAY .."; rebuild = valopt; }
    if (opt == 'd') { di<<" fix-dgnr .."; STF->FixWireTool()->FixDegeneratedMode() = valopt; }
    if (opt == 'r') { di<<" fix-reorder-wire .."; STF->FixWireTool()->FixReorderMode()    = valopt; }
    if (opt == 'k') {
    }
  }

  TopoDS_Face  face;
  ShapeBuild_ReShape resh;

  Standard_Integer nbf = 0, nbfc = 0;
  for (TopExp_Explorer EF (Shape,TopAbs_FACE); EF.More(); EF.Next()) {
    TopoDS_Face F = TopoDS::Face (EF.Current());    face = F;
    nbf ++;
    Standard_Boolean newface = Standard_False;
//    on va voir si ShapeTool_Face trouve qqchose a redire
//:sw    ShapeTool_Wire STW;
//:sw    STW.SetFace (F);

    STF->Init (F);  // qui fait tout
    STF->Perform();
    face = STF->Face();
    newface = STF->Status(ShapeExtend_DONE) || rebuild;
    if (newface) { nbfc ++; resh.Replace (F,face); }
  }
  if (nbfc > 0) {
    di<<"Faces reprises par ShapeFix_Face : "<<nbfc<<"\n";
    DBRep::Set (arg2,resh.Apply (Shape,TopAbs_FACE,2));
    return 0; // Done
  }
  else di<<"ShapeFix_Face n a rien trouve a redire"<<"\n";
  return 0;
}


//=======================================================================
//function : fixshape
//purpose  : 
//=======================================================================

static Standard_Integer fixshape (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  Handle(ShapeExtend_MsgRegistrator) msg = new ShapeExtend_MsgRegistrator;
  Handle(ShapeFix_Shape) sfs = new ShapeFix_Shape;
  sfs->SetMsgRegistrator ( msg );
  
  Standard_CString res = 0;
  Standard_Integer par = 0, mess=0;
  for ( Standard_Integer i=1; i < argc; i++ ) {
    if ( argv[i][0] == '-' || argv[i][0] == '+' || argv[i][0] == '*' ) {
      Standard_Integer val = ( argv[i][0] == '-' ? 0 : argv[i][0] == '+' ? 1 : -1 );
      switch ( argv[i][1] ) {
      case 'l': sfs->FixWireTool()->FixLackingMode()          = val;
      case 'o': sfs->FixFaceTool()->FixOrientationMode()      = val;
      case 'h': sfs->FixWireTool()->FixShiftedMode()          = val;
      case 'm': sfs->FixFaceTool()->FixMissingSeamMode()      = val;
      case 'd': sfs->FixWireTool()->FixDegeneratedMode()      = val;
      case 's': sfs->FixWireTool()->FixSmallMode()            = val;
      case 'i': sfs->FixWireTool()->FixSelfIntersectionMode() = val;
      case 'n': sfs->FixWireTool()->FixNotchedEdgesMode()     = val;
      case '?': mess                                          = val;
      }
      continue;
    }
    else {
      switch ( par ) {
      case 0: res = argv[i];                       break;
      case 1: {
        TopoDS_Shape initShape =  DBRep::Get(argv[i]);
        if(initShape.IsNull()) continue;
        sfs->Init ( initShape );
      } break;
      case 2: sfs->SetPrecision   (atof(argv[i])); break;
      case 3: sfs->SetMaxTolerance(atof(argv[i])); break;
      }
    }
    par++;
  }

  if ( par <2 ) {
    di << "Use: " << argv[0] << " result shape [tolerance [max_tolerance]] [switches]" << "\n"; 
    di << "Switches allow to tune parameters of ShapeFix" << "\n"; 
    di << "The following syntax is used: <symbol><parameter>" << "\n"; 
    di << "- symbol may be - to set parameter off, + to set on or * to set default" << "\n"; 
    di << "- parameters are identified by letters:" << "\n"; 
    di << "  l - FixLackingMode" << "\n"; 
    di << "  o - FixOrientationMode" << "\n"; 
    di << "  h - FixShiftedMode" << "\n"; 
    di << "  m - FixMissingSeamMode" << "\n"; 
    di << "  d - FixDegeneratedMode" << "\n"; 
    di << "  s - FixSmallMode" << "\n"; 
    di << "  i - FixSelfIntersectionMode" << "\n"; 
    di << "  n - FixNotchedEdgesMode" << "\n"; 
    di << "For enhanced message output, use switch '+?'" << "\n"; 
    return 1;
  }
  
  sfs->Perform();
  DBRep::Set (res,sfs->Shape());
  
  if ( mess ) {
    Standard_Integer num = 0;
    const ShapeExtend_DataMapOfShapeListOfMsg &map = msg->MapShape();
    for ( ShapeExtend_DataMapIteratorOfDataMapOfShapeListOfMsg it(map); it.More(); it.Next() ) {
      //cout << it.Key().TShape()->DynamicType()->Name() << " " << *(void**)&it.Key().TShape();
      Standard_SStream aSStream;
      aSStream << it.Key().TShape()->DynamicType()->Name() << " " << *(void**)&it.Key().TShape();
      di << aSStream;

      if ( mess <0 ) {
        char buff[256];
        sprintf ( buff, "%s_%d", res, ++num );
        di << " (saved in DRAW shape " << buff << ")";
        DBRep::Set (buff,it.Key());
      }
      di << ":" << "\n";
      for (Message_ListIteratorOfListOfMsg iter (it.Value()); iter.More(); iter.Next())
        di << "  " << TCollection_AsciiString(iter.Value().Value()).ToCString() << "\n";
    }
  }
  
  return 0; // Done
}

//=======================================================================
//function : fixgaps
//purpose  : 
//=======================================================================

Standard_Integer fixgaps(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 3) return 1;
  
  TopoDS_Shape S = DBRep::Get(a[2]);
  if (S.IsNull()) {
    di << " Shape is null" << "\n";
    return 1;
  }

  Handle(ShapeFix_Wireframe) SFWF = new ShapeFix_Wireframe(S);
  Standard_Real prec = ( n >3 ? atof(a[3]) : 0. );
  SFWF->SetPrecision(prec);
  if ( SFWF->FixWireGaps() ) {
    DBRep::Set(a[1],SFWF->Shape());
    di<<" Wireframe gaps fixed on shape"<<"\n";
  }

  return 0;
}

//=======================================================================
//function : fixsmall
//purpose  : 
//=======================================================================

Standard_Integer fixsmall(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 3) return 1;
  
  TopoDS_Shape S = DBRep::Get(a[2]);
  if (S.IsNull()) {
    di << " Shape is null" << "\n";
    return 1;
  }

  Standard_Real prec = (n == 4)? atof(a[3]) : 1.;
  ShapeFix_Wireframe SFWF(S);
  SFWF.SetPrecision(prec);
  
  if (SFWF.FixSmallEdges()) {
    DBRep::Set(a[1],SFWF.Shape());
    di<<" Small edges fixed on shape"<<"\n";
  }

  return 0;
}

//=======================================================================
//function : fixsmalledges
//purpose  : 
//=======================================================================

static Standard_Integer fixsmalledges(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if( n < 3) {
    di<<"Invalid number of arguments"<<"\n";
    return 1;
  }
  TopoDS_Shape Sh = DBRep::Get(a[2]);
 
  Standard_Integer k = 3;
  Standard_Real tol = 100000;
  Standard_Integer mode = 2;
  Standard_Real tolang = PI/2;
  if(n > k) 
    tol = atof(a[k++]);
  
  if(n > k) 
    mode=  atoi(a[k++]);
   
  if(n > k) 
    tolang = atof(a[k++]);
     
  Handle(ShapeFix_Wireframe) aSfwr = new ShapeFix_Wireframe();
  Handle(ShapeBuild_ReShape) aReShape = new ShapeBuild_ReShape;
  aSfwr->SetContext(aReShape);
  aSfwr->Load(Sh);
  aSfwr->SetPrecision(tol);
  Standard_Boolean aModeDrop = Standard_True;
  if(mode == 2) 
    aModeDrop = Standard_False;
   
  TopTools_MapOfShape theSmallEdges, theMultyEdges;
  TopTools_DataMapOfShapeListOfShape theEdgeToFaces,theFaceWithSmall;
  aSfwr->CheckSmallEdges(theSmallEdges,theEdgeToFaces,theFaceWithSmall, theMultyEdges);
  aSfwr->MergeSmallEdges (theSmallEdges,theEdgeToFaces,theFaceWithSmall, theMultyEdges, aModeDrop,tolang);
   //aSfwr->FixSmallEdges(); 
  TopoDS_Shape resShape =  aSfwr->Shape();;
  DBRep::Set ( a[1], resShape );
  return 0;
}

//=======================================================================
//function : checkoverlapedges
//purpose  : 
//=======================================================================

static Standard_Integer checkoverlapedges(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
   if( n < 3) {
     di<<"Invalid number of arguments"<<"\n";
     return 1;
   }
   TopoDS_Shape Sh1 = DBRep::Get(a[1]);
   TopoDS_Shape Sh2 = DBRep::Get(a[2]);
   if(Sh1.IsNull() || Sh2.IsNull()) {
     di<<"Invalid arguments"<<"\n";
     return 1;
   }
   TopoDS_Edge e1 = TopoDS::Edge(Sh1);
   TopoDS_Edge e2 = TopoDS::Edge(Sh2);
   if(e1.IsNull() || e2.IsNull()) {
     di<<"Invalid type of arguments"<<"\n";
     return 1;
   }
   Standard_Real aTol = Precision::Confusion();
   Standard_Real aDistDomain = 0.0;
   Standard_Integer k = 3;
   if(k < n)
     aTol = atof(a[k++]);
   if(k < n)
     aDistDomain = atof(a[k++]);
   
   ShapeAnalysis_Edge sae;
   if(sae.CheckOverlapping(e1,e2,aTol,aDistDomain)) {
     if(aDistDomain ==0.0)
       di<<"Edges is overlaping comletly"<<"\n";
     else {
        di<<"Edges is overlaped"<<"\n";
        di<<"with tolerance = "<<aTol<<"\n";
        di<<"on segment length = "<<aDistDomain<<"\n";
     }
   }
   else di<<"Edges is not overlaped"<<"\n";
   return 0;
}

//=======================================================================
//function : checkfclass2d
//purpose  : 
//=======================================================================

static Standard_Integer checkfclass2d(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if( n < 4) {
    di<<"Invalid number of arguments"<<"\n";
    return 1;
  }
  TopoDS_Shape Sh1 = DBRep::Get(a[1]);
  Standard_Real ucoord = atof(a[2]);
  Standard_Real vcoord = atof(a[3]);
  if(Sh1.IsNull() || Sh1.ShapeType()!= TopAbs_FACE) {
    di<<"Invalid arguments"<<"\n";
    return 1;
  }
  TopoDS_Face aFace = TopoDS::Face(Sh1);
  gp_Pnt2d p2d(ucoord,vcoord);
  BRepTopAdaptor_FClass2d f2d(aFace,Precision::Confusion());
  TopAbs_State stat = f2d.Perform(p2d);
  if(stat == TopAbs_OUT)
    di<<"Point is OUT"<<"\n";
  else if(stat == TopAbs_IN)
    di<<"Point is IN"<<"\n";
  else if(stat == TopAbs_ON)
    di<<"Point is ON"<<"\n";
  else
    di<<"Point is UNKNOWN"<<"\n";
  return 0;
}

//=======================================================================
//function : InitCommands
//purpose  : 
//=======================================================================

 void SWDRAW_ShapeFix::InitCommands(Draw_Interpretor& theCommands) 
{
  static Standard_Integer initactor = 0;
  if (initactor) return;  initactor = 1;
  
  Standard_CString g = SWDRAW::GroupName();
  
  theCommands.Add ("edgesameparam","nom shape draw ou * [+ option force]",
		   __FILE__,edgesameparam,g);
  theCommands.Add ("settolerance","shape [mode=v-e-f-a] val(fix value) or tolmin tolmax",
		   __FILE__,settolerance,g);
  theCommands.Add ("stwire","stwire tout court pour help complet",
		   __FILE__,stwire,g);
  theCommands.Add ("reface","shape result : controle sens wire",
		   __FILE__,reface,g);
  theCommands.Add ("fixshape","res shape [preci [maxpreci]] [{switches}]",
		   __FILE__,fixshape,g);
//  theCommands.Add ("testfill","result edge1 edge2",
//		   __FILE__,XSHAPE_testfill,g);
  theCommands.Add ("fixwgaps","result shape [toler=0]",
		   __FILE__,fixgaps,g);
  theCommands.Add ("fixsmall","result shape [toler=1.]",
		   __FILE__,fixsmall,g);
  theCommands.Add ("fixsmalledges","result shape [toler mode amxangle]",
		   __FILE__,fixsmalledges,g);
  theCommands.Add ("checkoverlapedges","edge1 edge2 [toler domaindist]",
		   __FILE__,checkoverlapedges,g);
  theCommands.Add ("checkfclass2d","face ucoord vcoord",
		   __FILE__,checkfclass2d,g);
}

