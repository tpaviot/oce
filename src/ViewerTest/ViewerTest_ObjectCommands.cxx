// Created on: 1998-11-12
// Created by: Robert COUBLANC
// Copyright (c) 1998-1999 Matra Datavision
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



//===============================================
//    AIS Objects Creation : Datums (axis,trihedrons,lines,planes)
//===============================================

#ifdef HAVE_CONFIG_H
#include <oce-config.h>
#endif

#include <ViewerTest.hxx>

#include <string.h>

#include <Quantity_NameOfColor.hxx>
#include <Draw_Interpretor.hxx>
#include <Draw.hxx>
#include <Draw_Appli.hxx>
#include <DBRep.hxx>

#include <OSD_Chronometer.hxx>
#include <TCollection_AsciiString.hxx>
#include <Visual3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <V3d_Plane.hxx>
#include <V3d.hxx>

#include <AIS_Shape.hxx>
#include <AIS_DisplayMode.hxx>
#include <TColStd_MapOfInteger.hxx>
#include <AIS_MapOfInteractive.hxx>
#include <ViewerTest_DoubleMapOfInteractiveAndName.hxx>
#include <ViewerTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName.hxx>
#include <ViewerTest_EventManager.hxx>

#include <TopoDS_Solid.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <TopAbs_ShapeEnum.hxx>

#include <TopoDS.hxx>
#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>

#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>

#include <TopAbs.hxx>
#include <TopExp.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>

#include <Draw_Window.hxx>
#include <AIS_ListIteratorOfListOfInteractive.hxx>
#include <AIS_ListOfInteractive.hxx>
#include <AIS_DisplayMode.hxx>
#include <AIS_Shape.hxx>

#include <AIS_InteractiveContext.hxx>
#include <Geom_Plane.hxx>
#include <gp_Pln.hxx>
#include <AIS_AngleDimension.hxx>
#include <TCollection_ExtendedString.hxx>
#include <GC_MakePlane.hxx>
#include <gp_Circ.hxx>
#include <AIS_Axis.hxx>
#include <Geom_Axis2Placement.hxx>
#include <Geom_Axis1Placement.hxx>
#include <AIS_Trihedron.hxx>
#include <AIS_Axis.hxx>
#include <gp_Trsf.hxx>
#include <TopLoc_Location.hxx>

#include <HLRAlgo_Projector.hxx>
#include <HLRBRep_PolyAlgo.hxx>
#include <HLRBRep_PolyHLRToShape.hxx>
#include <Aspect_Window.hxx>

#include <Graphic3d_ArrayOfPoints.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>
#include <Graphic3d_ArrayOfTriangles.hxx>
#include <Graphic3d_ArrayOfTriangleFans.hxx>
#include <Graphic3d_ArrayOfTriangleStrips.hxx>
#include <Graphic3d_ArrayOfQuadrangles.hxx>
#include <Graphic3d_ArrayOfQuadrangleStrips.hxx>
#include <Graphic3d_ArrayOfPolygons.hxx>
#include <Graphic3d_Group.hxx>
#include <Standard_Real.hxx>

#include <AIS_Circle.hxx>
#include <AIS_Drawer.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <Geom_Circle.hxx>
#include <GC_MakeCircle.hxx>
#include <Prs3d_Presentation.hxx>
#include <Select3D_SensitiveCircle.hxx>
#include <SelectMgr_EntityOwner.hxx>
#include <SelectMgr_Selection.hxx>
#include <StdFail_NotDone.hxx>
#include <StdPrs_ShadedShape.hxx>
#include <TopoDS_Wire.hxx>

#include <AIS_ConnectedShape.hxx>
#include <TopLoc_Location.hxx>
#include <TColStd_ListOfInteger.hxx>
#include <TColStd_ListIteratorOfListOfInteger.hxx>

#include <Select3D_SensitiveTriangle.hxx>
#include <Select3D_SensitiveCurve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <StdPrs_Curve.hxx>

#include <BRepExtrema_ExtPC.hxx>
#include <BRepExtrema_ExtPF.hxx>

#include <Prs3d_LineAspect.hxx>

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_DEPRECATE
#endif

extern ViewerTest_DoubleMapOfInteractiveAndName& GetMapOfAIS();
extern Standard_Boolean VDisplayAISObject (const TCollection_AsciiString& theName,
                                           const Handle(AIS_InteractiveObject)& theAISObj,
                                           Standard_Boolean theReplaceIfExists = Standard_True);
extern int ViewerMainLoop(Standard_Integer argc, const char** argv);
extern Handle(AIS_InteractiveContext)& TheAISContext();


//==============================================================================
//function : Vtrihedron 2d
//purpose  : Create a plane with a 2D  trihedron from a faceselection
//Draw arg : vtri2d  name
//==============================================================================
#include <AIS_PlaneTrihedron.hxx>



static int VTrihedron2D (Draw_Interpretor& di, Standard_Integer argc, const char** argv)

{
  // Verification des arguments
  if ( argc!=2) {di<<argv[0]<<" error"<<"\n"; return 1;}

  // Declarations
  Standard_Integer myCurrentIndex;
  // Fermeture des contextes
  TheAISContext()->CloseAllContexts();
  // Ouverture d'un contexte local et recuperation de son index.
  TheAISContext()->OpenLocalContext();
  myCurrentIndex=TheAISContext()->IndexOfCurrentLocal();
  // On active les modes de selections faces.
  TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(4) );
  di<<" Select a face ."<<"\n";

  // Boucle d'attente waitpick.
  Standard_Integer argccc = 5;
  const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
  const char **argvvv = (const char **) bufff;
  while (ViewerMainLoop( argccc, argvvv) ) { }
  // fin de la boucle

  TopoDS_Shape ShapeB;
  for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
    ShapeB = TheAISContext()->SelectedShape();
  }

  TopoDS_Face  FaceB=TopoDS::Face(ShapeB);

  // Construction du Plane
  // recuperation des edges des faces.
  TopExp_Explorer FaceExpB(FaceB,TopAbs_EDGE);

  TopoDS_Edge EdgeB=TopoDS::Edge(FaceExpB.Current() );
  // declarations
  gp_Pnt A,B,C;

  // si il y a plusieurs edges
  if (FaceExpB.More() ) {
    FaceExpB.Next();
    TopoDS_Edge EdgeC=TopoDS::Edge(FaceExpB.Current() );
    BRepAdaptor_Curve theCurveB(EdgeB);
    BRepAdaptor_Curve theCurveC(EdgeC);
    A=theCurveC.Value(0.1);
    B=theCurveC.Value(0.9);
    C=theCurveB.Value(0.5);
  }
  else {
    // FaceB a 1 unique edge courbe
    BRepAdaptor_Curve theCurveB(EdgeB);
    A=theCurveB.Value(0.1);
    B=theCurveB.Value(0.9);
    C=theCurveB.Value(0.5);
  }
  // Construction du Geom_Plane
  GC_MakePlane MkPlane(A,B,C);
  Handle(Geom_Plane) theGeomPlane=MkPlane.Value();

  // Construction de l'AIS_PlaneTrihedron
  Handle(AIS_PlaneTrihedron) theAISPlaneTri= new AIS_PlaneTrihedron(theGeomPlane );

  // Fermeture du contexte local.
  TheAISContext()->CloseLocalContext(myCurrentIndex);

  // on le display & bind
  TheAISContext()->Display(theAISPlaneTri );
  GetMapOfAIS().Bind ( theAISPlaneTri ,argv[1]);

  return 0;
}



//==============================================================================
//function : VTriherdron
//author   : ege
//purpose  : Create a trihedron. If no arguments are set, the default
//           trihedron (Oxyz) is created.
//Draw arg : vtrihedron  name  [Xo] [Yo] [Zo] [Zu] [Zv] [Zw] [Xu] [Xv] [Xw]
//==============================================================================

static int VTrihedron (Draw_Interpretor& di, Standard_Integer argc, const char** argv)

{
  // Verification des arguments
  if ( argc<2 || argc>11) {di<<argv[0]<<" Syntaxe error"<<"\n"; return 1;}

  // Declarations et creation des objets par default
  TCollection_AsciiString     name=argv[1];

  if(argc > 5 && argc!=11)
  {di<<argv[0]<<" Syntaxe error"<<"\n"; return 1;}

  // Cas ou il y a des arguments
  Standard_Real coord[9]={0.,0.,0.,0.,0.,1.,1.,0.,0.};
  if (argc>2){
    Standard_Integer i ;
    for( i=0;i<=2;i++)
      coord[i]= atof(argv[2+i]);

    if(argc>5){
      for(i=0;i<=2;i++){
        coord[3+i] = atof(argv[6+i]);
        coord[6+i] = atof(argv[8+i]);
      }
    }
  }
  gp_Pnt ThePoint(coord[0],coord[1],coord[2]);
  gp_Dir TheZVector(coord[3],coord[4],coord[5]);
  gp_Dir TheXVector(coord[6],coord[7],coord[8]);

  if ( !TheZVector.IsNormal(TheXVector,M_PI/180)) {di<<argv[0]<<" VectorX is not normal to VectorZ"<<"\n"; return 1;}

  Handle(Geom_Axis2Placement) OrigineAndAxii=new Geom_Axis2Placement(ThePoint,TheZVector,TheXVector);

  // Creation du triedre
  Handle(AIS_Trihedron) aShape= new AIS_Trihedron(OrigineAndAxii);
  GetMapOfAIS().Bind(aShape,name);
  TheAISContext()->Display(aShape);

  return 0;
}




//==============================================================================
//function : VSize
//author   : ege
//purpose  : Change the size of a named or selected trihedron
//           if no name : it affects the trihedrons witch are selected otherwise nothing is donne
//           if no value, the value is set at 100 by default
//Draw arg : vsize [name] [size]
//==============================================================================

static int VSize (Draw_Interpretor& di, Standard_Integer argc, const char** argv)

{
  // Declaration de booleens
  Standard_Boolean             ThereIsName;
  Standard_Boolean             ThereIsCurrent;
  Standard_Real                value;
  Standard_Boolean             hascol;
#ifdef DEB
  Quantity_NameOfColor         col;
#else
  Quantity_NameOfColor         col = Quantity_NOC_BLACK ;
#endif

  // Verification des arguments
  if ( argc>3 ) {di<<argv[0]<<" Syntaxe error"<<"\n"; return 1;}

  // Verification du nombre d'arguments
  if (argc==1)      {ThereIsName=Standard_False;value=100;}
  else if (argc==2) {ThereIsName=Standard_False;value=atof(argv[1]);}
  else              {ThereIsName=Standard_True;value=atof(argv[2]);}

  // On ferme le contexte local pour travailler dans le contexte global
  if(TheAISContext()->HasOpenedContext())
    TheAISContext()->CloseLocalContext();

  // On set le booleen ThereIsCurrent
  if (TheAISContext() -> NbCurrents() > 0) {ThereIsCurrent=Standard_True;}
  else {ThereIsCurrent=Standard_False;}



  //===============================================================
  // Il n'y a pas de nom  mais des objets selectionnes
  //===============================================================
  if (!ThereIsName && ThereIsCurrent)
  {

    ViewerTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName
      it (GetMapOfAIS());

    while ( it.More() ) {

      Handle(AIS_InteractiveObject) aShape=
        Handle(AIS_InteractiveObject)::DownCast(it.Key1());

      if (!aShape.IsNull() &&  TheAISContext()->IsCurrent(aShape) )
      {

        // On verifie que l'AIS InteraciveObject selectionne est bien
        // un AIS_Trihedron
        if (aShape->Type()==AIS_KOI_Datum && aShape->Signature()==3) {

          if (aShape->HasColor()) {
            hascol=Standard_True;

            // On recupere la couleur de aShape
            col=aShape->Color();}

          else hascol=Standard_False;

          // On downcast aShape  de AIS_InteractiveObject a AIS_Trihedron
          // pour lui appliquer la methode SetSize()
          Handle(AIS_Trihedron) aTrihedron = *(Handle(AIS_Trihedron)*) &aShape;

          // C'est bien un triedre,on chage sa valeur!
          aTrihedron->SetSize(value);

          // On donne la couleur au Trihedron
          if(hascol)   aTrihedron->SetColor(col);
          else         aTrihedron->UnsetColor();


          // The trihedron hasn't be errased from the map
          // so you just have to redisplay it
          TheAISContext() ->Redisplay(aTrihedron,Standard_False);

        }

      }

      it.Next();
    }

    TheAISContext() ->UpdateCurrentViewer();
  }

  //===============================================================
  // Il n'y a pas d'arguments et aucuns objets selectionne Rien A Faire!
  //===============================================================



  //===============================================================
  // Il y a un nom de triedre passe en argument
  //===============================================================
  if (ThereIsName) {
    TCollection_AsciiString name=argv[1];

    // on verifie que ce nom correspond bien a une shape
    Standard_Boolean IsBound= GetMapOfAIS().IsBound2(name);

    if (IsBound) {

      // on recupere la shape dans la map des objets displayes
      Handle(AIS_InteractiveObject) aShape =
        Handle(AIS_InteractiveObject)::DownCast(GetMapOfAIS().Find2(name));

      // On verifie que l'AIS InteraciveObject est bien
      // un AIS_Trihedron
      if (!aShape.IsNull() &&
        aShape->Type()==AIS_KOI_Datum && aShape->Signature()==3)
      {

        if (aShape->HasColor()) {
          hascol=Standard_True;

          // On recupere la couleur de aShape
          col=aShape->Color();}

        else hascol=Standard_False;

        // On downcast aShape de AIS_InteractiveObject a AIS_Trihedron
        // pour lui appliquer la methode SetSize()
        Handle(AIS_Trihedron) aTrihedron = *(Handle(AIS_Trihedron)*) &aShape;

        // C'est bien un triedre,on chage sa valeur
        aTrihedron->SetSize(value);

        // On donne la couleur au Trihedron
        if(hascol)   aTrihedron->SetColor(col);
        else         aTrihedron->UnsetColor();

        // The trihedron hasn't be errased from the map
        // so you just have to redisplay it
        TheAISContext() ->Redisplay(aTrihedron,Standard_False);

        TheAISContext() ->UpdateCurrentViewer();
      }
    }
  }
  return 0;
}


//==============================================================================

//==============================================================================
//function : VPlaneTrihedron
//purpose  : Create a plane from a trihedron selection. If no arguments are set, the default
//Draw arg : vplanetri  name
//==============================================================================
#include <AIS_Plane.hxx>



static int VPlaneTrihedron (Draw_Interpretor& di, Standard_Integer argc, const char** argv)

{
  // Verification des arguments
  if ( argc!=2) {di<<argv[0]<<" error"<<"\n"; return 1;}

  // Declarations
  Standard_Integer myCurrentIndex;
  // Fermeture des contextes locaux
  TheAISContext()->CloseAllContexts();

  // On recupere tous les trihedrons de la GetMapOfAIS()
  // et on active le mode de selection par face.
  // =================================================

  // Ouverture d'un contexte local et recuperation de son index.
  TheAISContext()->OpenLocalContext(Standard_False);
  myCurrentIndex=TheAISContext()->IndexOfCurrentLocal();

  ViewerTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName
    it (GetMapOfAIS());
  while(it.More()){
    Handle(AIS_InteractiveObject) ShapeA =
      Handle(AIS_InteractiveObject)::DownCast(it.Key1());
    // On verifie que c'est bien un trihedron
    if (!ShapeA.IsNull() &&
      ShapeA->Type()==AIS_KOI_Datum  && ShapeA->Signature()==3  ) {
        // on le downcast
        Handle(AIS_Trihedron) TrihedronA =((*(Handle(AIS_Trihedron)*)&ShapeA));
        // on le charge dans le contexte et on active le mode Plane.
        TheAISContext()->Load(TrihedronA,0,Standard_False);
        TheAISContext()->Activate(TrihedronA,3);
      }
      it.Next();
  }

  di<<" Select a plane."<<"\n";
  // Boucle d'attente waitpick.
  Standard_Integer argccc = 5;
  const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
  const char **argvvv = (const char **) bufff;
  while (ViewerMainLoop( argccc, argvvv) ) { }
  // fin de la boucle

  Handle(AIS_InteractiveObject) theIOB;
  for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
    theIOB = TheAISContext()->Interactive();
  }
  // on le downcast
  Handle(AIS_Plane) PlaneB =((*(Handle(AIS_Plane)*)&theIOB));

  // Fermeture du contexte local.
  TheAISContext()->CloseLocalContext(myCurrentIndex);

  // on le display & bind
  TheAISContext()->Display(PlaneB );
  GetMapOfAIS().Bind ( PlaneB ,argv[1]);

  return 0;
}



//==============================================================================
// Fonction        First click      2de click
//
// vaxis           vertex           vertex
//                 edge             None
// vaxispara       edge             vertex
// vaxisortho      edge             Vertex
// vaxisinter      Face             Face
//==============================================================================

//==============================================================================
//function : VAxisBuilder
//purpose  :
//Draw arg : vaxis AxisName Xa Ya Za Xb Yb Zb
//==============================================================================
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp.hxx>
#include <Geom_Line.hxx>

static int VAxisBuilder(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  // Declarations
  Standard_Boolean HasArg;
  TCollection_AsciiString name;
  Standard_Integer MyCurrentIndex;

  // Verification
  if (argc<2 || argc>8 ) {di<<" Syntaxe error"<<"\n";return 1;}
  if (argc==8) HasArg=Standard_True;
  else HasArg=Standard_False;

  name=argv[1];
  // Fermeture des contextes
  TheAISContext()->CloseAllContexts();

  // Cas ou il y a des arguments
  // Purpose: Teste le constructeur AIS_Axis::AIS_Axis(x: Line from Geom)
  if (HasArg) {
    Standard_Real coord[6];
    for(Standard_Integer i=0;i<=5;i++){
      coord[i]=atof(argv[2+i]);
    }
    gp_Pnt p1(coord[0],coord[1],coord[2]), p2(coord[3],coord[4],coord[5]) ;

    gp_Vec myVect (p1,p2);
    Handle(Geom_Line) myLine=new Geom_Line (p1 ,myVect );
    Handle(AIS_Axis) TheAxis=new AIS_Axis (myLine );
    GetMapOfAIS().Bind (TheAxis,name);
    TheAISContext()->Display(TheAxis);
  }

  // Pas d'arguments
  else {
    // fonction vaxis
    // Purpose: Teste le constructeur AIS_Axis::AIS_Axis (x:Axis1Placement from Geom)
    if ( !strcasecmp(argv[0], "vaxis")) {
      TheAISContext()->OpenLocalContext();
      MyCurrentIndex=TheAISContext()->IndexOfCurrentLocal();

      // Active le mode edge et le mode vertex
      TheAISContext()->ActivateStandardMode(AIS_Shape::SelectionType(1) );
      TheAISContext()->ActivateStandardMode(AIS_Shape::SelectionType(2) );
      di<<" Select an edge or a vertex."<<"\n";

      // Boucle d'attente waitpick.
      Standard_Integer argcc = 5;
      const char *buff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
      const char **argvv = (const char **) buff;
      while (ViewerMainLoop( argcc, argvv) ) { }
      // fin de la boucle

      // recuperation de la shape.
      TopoDS_Shape ShapeA;
      for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
        ShapeA = TheAISContext()->SelectedShape();
      }
      // recuperation de l'AIS_InteractiveObject
      //Handle(AIS_InteractiveObject) myAISio=TheAISContext()->Current();
      // down cast en AIS_Point si sig et type
      // AIS_Point -> Geom_Pnt ....

      if (ShapeA.ShapeType()==TopAbs_VERTEX) {
        // on desactive le mode edge
        TheAISContext()->DeactivateStandardMode(AIS_Shape::SelectionType(2) );
        di<<" Select a different vertex."<<"\n";

        TopoDS_Shape ShapeB;
        do {
          // Boucle d'attente waitpick.
          Standard_Integer argccc = 5;
          const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
          const char **argvvv = (const char **) bufff;
          while (ViewerMainLoop( argccc, argvvv) ) { }
          // fin de la boucle
          for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
            ShapeB = TheAISContext()->SelectedShape();
          }


        } while(ShapeB.IsSame(ShapeA) );

        // Fermeture du context local
        TheAISContext()->CloseLocalContext(MyCurrentIndex);

        // Construction de l'axe
        gp_Pnt   A=BRep_Tool::Pnt(TopoDS::Vertex(ShapeA)  );
        gp_Pnt   B=BRep_Tool::Pnt(TopoDS::Vertex(ShapeB)  );
        gp_Vec   V (A,B);
        gp_Dir   D (V);
        Handle(Geom_Axis1Placement) OrigineAndVect=new Geom_Axis1Placement (A,D);
        Handle(AIS_Axis) TheAxis=new AIS_Axis (OrigineAndVect);
        GetMapOfAIS().Bind (TheAxis,name);
        TheAISContext()->Display(TheAxis);
      }
      else {
        // Un unique edge (ShapeA) a ete picke
        // Fermeture du context local
        TheAISContext()->CloseLocalContext(MyCurrentIndex);
        // Constuction de l'axe
        TopoDS_Edge    ed =TopoDS::Edge(ShapeA);
        TopoDS_Vertex  Va,Vb;
        TopExp::Vertices(ed,Va,Vb );
        gp_Pnt A=BRep_Tool::Pnt(Va);
        gp_Pnt B=BRep_Tool::Pnt(Vb);
        gp_Vec  V (A,B);
        gp_Dir   D (V);
        Handle(Geom_Axis1Placement) OrigineAndVect=new Geom_Axis1Placement (A,D);
        Handle(AIS_Axis) TheAxis=new AIS_Axis (OrigineAndVect);
        GetMapOfAIS().Bind (TheAxis,name);
        TheAISContext()->Display(TheAxis);
      }

    }

    // Fonction axispara
    // Purpose: Teste le constructeur AIS_Axis::AIS_Axis(x: Axis2Placement from Geom, y: TypeOfAxis from AIS)
    else if ( !strcasecmp(argv[0], "vaxispara")) {

      TheAISContext()->OpenLocalContext();
      MyCurrentIndex=TheAISContext()->IndexOfCurrentLocal();

      // Active le mode edge
      TheAISContext()->ActivateStandardMode(AIS_Shape::SelectionType(2) );
      di<<" Select an edge."<<"\n";

      // Boucle d'attente waitpick.
      Standard_Integer argcc = 5;
      const char *buff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
      const char **argvv = (const char **) buff;
      while (ViewerMainLoop( argcc, argvv) ) { }
      // fin de la boucle

      TopoDS_Shape ShapeA;
      for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
        ShapeA = TheAISContext()->SelectedShape();
      }
      // Active le mode vertex et deactive edges
      TheAISContext()->DeactivateStandardMode(AIS_Shape::SelectionType(2) );
      TheAISContext()->ActivateStandardMode(AIS_Shape::SelectionType(1) );
      di<<" Select a vertex."<<"\n";

      // Boucle d'attente waitpick.
      Standard_Integer argccc = 5;
      const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
      const char **argvvv = (const char **) bufff;
      while (ViewerMainLoop( argccc, argvvv) ) { }
      // fin de la boucle

      // On peut choisir un pnt sur l'edge
      TopoDS_Shape ShapeB;
      for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
        ShapeB = TheAISContext()->SelectedShape();
      }
      // Fermeture du context local
      TheAISContext()->CloseLocalContext(MyCurrentIndex);

      // Construction de l'axe
      TopoDS_Edge    ed=TopoDS::Edge(ShapeA) ;
      gp_Pnt B=BRep_Tool::Pnt(TopoDS::Vertex(ShapeB) );
      TopoDS_Vertex  Va,Vc;
      TopExp::Vertices(ed,Va,Vc );
      gp_Pnt A=BRep_Tool::Pnt(Va);
      gp_Pnt C=BRep_Tool::Pnt(Vc);
      gp_Vec  V (A,C);
      gp_Dir   D (V);
      Handle(Geom_Axis1Placement) OrigineAndVect=new Geom_Axis1Placement (B,D);
      Handle(AIS_Axis) TheAxis=new AIS_Axis (OrigineAndVect);
      GetMapOfAIS().Bind (TheAxis,name);
      TheAISContext()->Display(TheAxis);

    }

    // Fonction axisortho
    else  {
      TheAISContext()->OpenLocalContext();
      MyCurrentIndex=TheAISContext()->IndexOfCurrentLocal();

      // Active le mode edge
      TheAISContext()->ActivateStandardMode(AIS_Shape::SelectionType(2) );
      di<<" Select an edge."<<"\n";

      // Boucle d'attente waitpick.
      Standard_Integer argcc = 5;
      const char *buff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
      const char **argvv = (const char **) buff;
      while (ViewerMainLoop( argcc, argvv) ) { }
      // fin de la boucle

      TopoDS_Shape ShapeA;
      for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
        ShapeA = TheAISContext()->SelectedShape();
      }
      // Active le mode vertex et deactive edges
      TheAISContext()->DeactivateStandardMode(AIS_Shape::SelectionType(2) );
      TheAISContext()->ActivateStandardMode(AIS_Shape::SelectionType(1) );
      di<<" Slect a vertex."<<"\n";

      // Boucle d'attente waitpick.
      Standard_Integer argccc = 5;
      const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
      const char **argvvv = (const char **) bufff;
      while (ViewerMainLoop( argccc, argvvv) ) { }
      // fin de la boucle

      // On peut choisir un pnt sur l'edge
      TopoDS_Shape ShapeB;
      for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
        ShapeB = TheAISContext()->SelectedShape();
      }
      // Fermeture du context local
      TheAISContext()->CloseLocalContext(MyCurrentIndex);

      // Construction de l'axe
      TopoDS_Edge    ed=TopoDS::Edge(ShapeA) ;
      gp_Pnt B=BRep_Tool::Pnt(TopoDS::Vertex(ShapeB) );
      TopoDS_Vertex  Va,Vc;
      TopExp::Vertices(ed,Va,Vc );
      gp_Pnt A=BRep_Tool::Pnt(Va);
      gp_Pnt C=BRep_Tool::Pnt(Vc);
      gp_Pnt E(A.Y()+A.Z()-C.Y()-C.Z()  ,C.X()-A.X() ,C.X()-A.X() );
      gp_Vec  V (A,E);
      gp_Dir   D (V);
      Handle(Geom_Axis1Placement) OrigineAndVect=new Geom_Axis1Placement (B,D);
      Handle(AIS_Axis) TheAxis=new AIS_Axis (OrigineAndVect);
      GetMapOfAIS().Bind (TheAxis,name);
      TheAISContext()->Display(TheAxis);

    }

  }
  return 0;
}


//==============================================================================
// Fonction        First click      Result
//
// vpoint          vertex           AIS_Point=Vertex
//                 edge             AIS_Point=Middle of the edge
//==============================================================================

//==============================================================================
//function : VPointBuilder
//purpose  : Build an AIS_Point from coordinates or with a selected vertex or edge
//Draw arg : vpoint PoinName [Xa] [Ya] [Za]
//==============================================================================
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp.hxx>
#include <AIS_Point.hxx>
#include <Geom_CartesianPoint.hxx>

static int VPointBuilder(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  // Declarations
  Standard_Boolean HasArg;
  TCollection_AsciiString name;
  Standard_Integer myCurrentIndex;

  // Verification
  if (argc<2 || argc>5 ) {di<<" Syntaxe error"<<"\n";return 1;}
  if (argc==5) HasArg=Standard_True;
  else HasArg=Standard_False;

  name=argv[1];
  // Fermeture des contextes
  TheAISContext()->CloseAllContexts();

  // Il y a des arguments: teste l'unique constructeur AIS_Pnt::AIS_Pnt(Point from Geom)
  if (HasArg) {
    Standard_Real thecoord[3];
    for(Standard_Integer i=0;i<=2;i++)
      thecoord[i]=atof(argv[2+i]);
    Handle(Geom_CartesianPoint )  myGeomPoint= new Geom_CartesianPoint (thecoord[0],thecoord[1],thecoord[2]);
    Handle(AIS_Point)  myAISPoint=new AIS_Point(myGeomPoint );
    GetMapOfAIS().Bind (myAISPoint,name);
    TheAISContext()->Display(myAISPoint);
  }

  // Il n'a pas d'arguments
  else {
    TheAISContext()->OpenLocalContext();
    myCurrentIndex=TheAISContext()->IndexOfCurrentLocal();

    // Active le mode Vertex et Edges
    TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(1) );
    TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(2) );
    di<<" Select a vertex or an edge(build the middle)"<<"\n";

    // Boucle d'attente waitpick.
    Standard_Integer argcc = 5;
    const char *buff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
    const char **argvv = (const char **) buff;
    while (ViewerMainLoop( argcc, argvv) ) { }
    // fin de la boucle

    TopoDS_Shape ShapeA;
    for (TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
      ShapeA= TheAISContext()->SelectedShape();
    }

    if (ShapeA.ShapeType()==TopAbs_VERTEX ) {
      // Un vertex a ete selectionne
      // Fermeture du context local
      TheAISContext()->CloseLocalContext(myCurrentIndex);

      // Construction du point
      gp_Pnt A=BRep_Tool::Pnt(TopoDS::Vertex(ShapeA ) );
      Handle(Geom_CartesianPoint) myGeomPoint= new Geom_CartesianPoint (A );
      Handle(AIS_Point)  myAISPoint = new AIS_Point  (myGeomPoint );
      GetMapOfAIS().Bind(myAISPoint,name);
      TheAISContext()->Display(myAISPoint);
    }
    else {
      // Un Edge a ete selectionne
      // Fermeture du context local
      TheAISContext()->CloseLocalContext(myCurrentIndex);

      // Construction du point milieu de l'edge
      TopoDS_Edge myEdge=TopoDS::Edge(ShapeA);
      TopoDS_Vertex myVertexA,myVertexB;
      TopExp::Vertices (myEdge ,myVertexA ,myVertexB );
      gp_Pnt A=BRep_Tool::Pnt(myVertexA );
      gp_Pnt B=BRep_Tool::Pnt(myVertexB );
      // M est le milieu de [AB]
      Handle(Geom_CartesianPoint) myGeomPointM= new Geom_CartesianPoint ( (A.X()+B.X())/2  , (A.Y()+B.Y())/2  , (A.Z()+B.Z())/2  );
      Handle(AIS_Point)  myAISPointM = new AIS_Point  (myGeomPointM );
      GetMapOfAIS().Bind(myAISPointM,name);
      TheAISContext()->Display(myAISPointM);
    }

  }
  return 0;

}

//==============================================================================
// Function        1st click   2de click  3de click
// vplane          Vertex      Vertex     Vertex
//                 Vertex      Edge
//                 Edge        Vertex
//                 Face
// vplanepara      Face        Vertex
//                 Vertex      Face
// vplaneortho     Face        Edge
//                 Edge        Face
//==============================================================================

//==============================================================================
//function : VPlaneBuilder
//purpose  : Build an AIS_Plane from selected entities or Named AIS components
//Draw arg : vplane PlaneName [AxisName]  [PointName]
//                            [PointName] [PointName] [PointName]
//                            [PlaneName] [PointName]
//==============================================================================

static Standard_Integer VPlaneBuilder (Draw_Interpretor& di,
                                       Standard_Integer argc,
                                       const char** argv)
{
  // Declarations
  Standard_Boolean hasArg;
  TCollection_AsciiString aName;
  Standard_Integer aCurrentIndex;

  // Verification
  if (argc<2 || argc>5 )
  {
    std::cout<<" Syntax error\n";
    return 1;
  }
  if (argc==5 || argc==4)
    hasArg=Standard_True;
  else 
    hasArg=Standard_False;

  aName=argv[1];
  // Close all contexts
  TheAISContext()->CloseAllContexts();

  // There are some arguments
  if (hasArg)
  {
    if (!GetMapOfAIS().IsBound2(argv[2] ))
    {
      std::cout<<"vplane: error 1st name doesn't exist in the GetMapOfAIS()\n";
      return 1;
    }
    // Get shape from map
    Handle(AIS_InteractiveObject) aShapeA =
      Handle(AIS_InteractiveObject)::DownCast (GetMapOfAIS().Find2(argv[2] ));

    // The first argument is an AIS_Point
    if (!aShapeA.IsNull() &&
        aShapeA->Type()==AIS_KOI_Datum &&
        aShapeA->Signature()==1)
    {
        // The second argument must also be an AIS_Point
        if (argc<5 || !GetMapOfAIS().IsBound2(argv[3]))
        {
          std::cout<<"vplane: error 2nd name doesn't exist in the GetMapOfAIS()\n";
          return 1;
        }
        // Get shape from map
        Handle(AIS_InteractiveObject) aShapeB =
          Handle(AIS_InteractiveObject)::DownCast (GetMapOfAIS().Find2(argv[3]));
        // If B is not an AIS_Point
        if (aShapeB.IsNull() ||
          (!(aShapeB->Type()==AIS_KOI_Datum && aShapeB->Signature()==1)))
        {
          std::cout<<"vplane: error 2nd object is expected to be an AIS_Point.\n";
          return 1;
        }
        // The third object is an AIS_Point
        if (!GetMapOfAIS().IsBound2(argv[4]) ) 
        {
          std::cout<<"vplane: error 3d name doesn't exist in the GetMapOfAIS().\n";
          return 1; 
        }
        // Get shape from map
        Handle(AIS_InteractiveObject) aShapeC =
          Handle(AIS_InteractiveObject)::DownCast (GetMapOfAIS().Find2(argv[4]));
        // If C is not an AIS_Point
        if (aShapeC.IsNull() ||
          (!(aShapeC->Type()==AIS_KOI_Datum && aShapeC->Signature()==1)))
        {
          std::cout<<"vplane: error 3d object is expected to be an AIS_Point.\n";
          return 1;
        }

        // Treatment of objects A, B, C
        // Downcast an AIS_IO to AIS_Point
        Handle(AIS_Point) anAISPointA = Handle(AIS_Point)::DownCast( aShapeA);
        Handle(AIS_Point) anAISPointB = Handle(AIS_Point)::DownCast( aShapeB);
        Handle(AIS_Point) anAISPointC = Handle(AIS_Point)::DownCast( aShapeC);

        Handle(Geom_CartesianPoint ) aCartPointA = 
          Handle(Geom_CartesianPoint)::DownCast( anAISPointA->Component());

        Handle(Geom_CartesianPoint ) aCartPointB = 
          Handle(Geom_CartesianPoint)::DownCast( anAISPointB->Component());

        Handle(Geom_CartesianPoint ) aCartPointC = 
          Handle(Geom_CartesianPoint)::DownCast( anAISPointC->Component());

        // Verification that the three points are different
        if(abs(aCartPointB->X()-aCartPointA->X())<=Precision::Confusion() &&
           abs(aCartPointB->Y()-aCartPointA->Y())<=Precision::Confusion() &&
           abs(aCartPointB->Z()-aCartPointA->Z())<=Precision::Confusion())
        {
          // B=A
          std::cout<<"vplane error: same points"<<"\n";return 1;
        }
        if(abs(aCartPointC->X()-aCartPointA->X())<=Precision::Confusion() &&
           abs(aCartPointC->Y()-aCartPointA->Y())<=Precision::Confusion() &&
           abs(aCartPointC->Z()-aCartPointA->Z())<=Precision::Confusion())
        {
          // C=A
          std::cout<<"vplane error: same points"<<"\n";return 1;
        }
        if(abs(aCartPointC->X()-aCartPointB->X())<=Precision::Confusion() &&
           abs(aCartPointC->Y()-aCartPointB->Y())<=Precision::Confusion() &&
           abs(aCartPointC->Z()-aCartPointB->Z())<=Precision::Confusion())
        {
          // C=B
          std::cout<<"vplane error: same points"<<"\n";return 1;
        }

        gp_Pnt A = aCartPointA->Pnt();
        gp_Pnt B = aCartPointB->Pnt();
        gp_Pnt C = aCartPointC->Pnt();

        // Construction of AIS_Plane
        GC_MakePlane MkPlane (A,B,C);
        Handle(Geom_Plane) aGeomPlane = MkPlane.Value();
        Handle(AIS_Plane)  anAISPlane = new AIS_Plane(aGeomPlane );
        GetMapOfAIS().Bind (anAISPlane,aName );
        TheAISContext()->Display(anAISPlane);
      }

      // The first argument is an AIS_Axis
      // Creation of a plane orthogonal to the axis through a point
    else if (aShapeA->Type()==AIS_KOI_Datum && aShapeA->Signature()==2 ) {
      // The second argument should be an AIS_Point
      if (argc!=4 || !GetMapOfAIS().IsBound2(argv[3] ) )
      {
        std::cout<<"vplane: error 2d name doesn't exist in the GetMapOfAIS()\n";
        return 1;
      }
      // Get shape from map
      Handle(AIS_InteractiveObject) aShapeB =
        Handle(AIS_InteractiveObject)::DownCast (GetMapOfAIS().Find2(argv[3]));
      // If B is not an AIS_Point
      if (aShapeB.IsNull() ||
        (!(aShapeB->Type()==AIS_KOI_Datum && aShapeB->Signature()==1)))
      {
        std::cout<<"vplane: error 2d object is expected to be an AIS_Point\n";
        return 1;
      }

      // Treatment of objects A and B
      Handle(AIS_Axis) anAISAxisA = Handle(AIS_Axis)::DownCast(aShapeA);
      Handle(AIS_Point) anAISPointB = Handle(AIS_Point)::DownCast(aShapeB);

      Handle(Geom_Line ) aGeomLineA = anAISAxisA ->Component();
      Handle(Geom_Point) aGeomPointB = anAISPointB->Component()  ;

      gp_Ax1 anAxis = aGeomLineA->Position();
      Handle(Geom_CartesianPoint) aCartPointB = 
        Handle(Geom_CartesianPoint)::DownCast(aGeomPointB);

      gp_Dir D =anAxis.Direction();
      gp_Pnt B = aCartPointB->Pnt();

      // Construction of AIS_Plane
      Handle(Geom_Plane) aGeomPlane = new Geom_Plane(B,D);
      Handle(AIS_Plane) anAISPlane = new AIS_Plane(aGeomPlane,B );
      GetMapOfAIS().Bind (anAISPlane,aName );
      TheAISContext()->Display(anAISPlane);

    }
    // The first argumnet is an AIS_Plane
    // Creation of a plane parallel to the plane passing through the point
    else if (aShapeA->Type()==AIS_KOI_Datum && aShapeA->Signature()==7)
    {
      // The second argument should be an AIS_Point
      if (argc!=4 || !GetMapOfAIS().IsBound2(argv[3]))
      {
        std::cout<<"vplane: error 2d name doesn't exist in the GetMapOfAIS()\n";
        return 1;
      }
      // Get shape from map
      Handle(AIS_InteractiveObject) aShapeB =
        Handle(AIS_InteractiveObject)::DownCast (GetMapOfAIS().Find2(argv[3]));
      // B should be an AIS_Point
      if (aShapeB.IsNull() ||
         (!(aShapeB->Type()==AIS_KOI_Datum && aShapeB->Signature()==1)))
      {
        std::cout<<"vplane: error 2d object is expected to be an AIS_Point\n";
        return 1;
      }

      // Treatment of objects A and B
      Handle(AIS_Plane) anAISPlaneA = Handle(AIS_Plane)::DownCast(aShapeA);
      Handle(AIS_Point) anAISPointB = Handle(AIS_Point)::DownCast(aShapeB);

      Handle(Geom_Plane) aNewGeomPlane= anAISPlaneA->Component();
      Handle(Geom_Point) aGeomPointB = anAISPointB->Component();

      Handle(Geom_CartesianPoint) aCartPointB = 
        Handle(Geom_CartesianPoint)::DownCast(aGeomPointB);
      gp_Pnt B= aCartPointB->Pnt();

      // Construction of an AIS_Plane
      Handle(AIS_Plane) anAISPlane = new AIS_Plane(aNewGeomPlane, B);
      GetMapOfAIS().Bind (anAISPlane, aName);
      TheAISContext()->Display(anAISPlane);
    }
    // Error
    else
    {
      std::cout<<"vplane: error 1st object is not an AIS\n";
      return 1;
    }
  }
  // There are no arguments
  else 
  {
    // Function vplane
    // Test the constructor AIS_Plane::AIS_Plane(Geom_Plane, Standard_Boolean )
    if (!strcasecmp(argv[0], "vplane"))
    {
      TheAISContext()->OpenLocalContext();
      aCurrentIndex=TheAISContext()->IndexOfCurrentLocal();

      // Active modes Vertex, Edge and Face
      TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(1));
      TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(2));
      TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(4));
      std::cout<<"Select a vertex, a face or an edge\n";

      // Wait for picking
      Standard_Integer argcc = 5;
      const char *buff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
      const char **argvv = (const char **) buff;
      while (ViewerMainLoop( argcc, argvv) ) { }
      // end of the loop

      TopoDS_Shape aShapeA;
      for (TheAISContext()->InitSelected();
           TheAISContext()->MoreSelected();
           TheAISContext()->NextSelected())
      {
        aShapeA = TheAISContext()->SelectedShape();
      }

      // aShapeA is a Vertex
      if (aShapeA.ShapeType()==TopAbs_VERTEX )
      {
        TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(4));
        std::cout<<" Select an edge or a different vertex\n";

        // Wait for picking
        Standard_Integer argccc = 5;
        const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
        const char **argvvv = (const char **) bufff;
        while (ViewerMainLoop( argccc, argvvv) ) { }
        // end of the loop

        TopoDS_Shape aShapeB;
        for (TheAISContext()->InitSelected();
          TheAISContext()->MoreSelected();
          TheAISContext()->NextSelected())
        {
          aShapeB = TheAISContext()->SelectedShape();
        }
        // aShapeB is a Vertex
        if (aShapeB.ShapeType()==TopAbs_VERTEX)
        {
          // A and B are the same
          if (aShapeB.IsSame(aShapeA))
          {
            std::cout<<" vplane: error, same points selected\n";
            return 1;
          }
          TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(2));
          std::cout<<" Select a different vertex\n";

          // Wait for picking
          Standard_Integer argcccc = 5;
          const char *buffff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
          const char **argvvvv = (const char **) buffff;
          while (ViewerMainLoop( argcccc, argvvvv) ) { }
          // end of the loop

          TopoDS_Shape aShapeC;
          for (TheAISContext()->InitSelected();
               TheAISContext()->MoreSelected();
               TheAISContext()->NextSelected())
          {
            aShapeC = TheAISContext()->SelectedShape();
          }
          // aShapeC is the same as A or B
          if (aShapeC.IsSame(aShapeA)||aShapeC.IsSame(aShapeB))
          {
            std::cout<<" vplane: error, same points selected\n";
            return 1;
          }

          // Close the local context
          TheAISContext()->CloseLocalContext(aCurrentIndex);

          // Construction of plane
          gp_Pnt A = BRep_Tool::Pnt(TopoDS::Vertex(aShapeA));
          gp_Pnt B = BRep_Tool::Pnt(TopoDS::Vertex(aShapeB));
          gp_Pnt C = BRep_Tool::Pnt(TopoDS::Vertex(aShapeC));
          GC_MakePlane MkPlane(A, B, C);
          Handle(Geom_Plane) aGeomPlane = MkPlane.Value();
          Handle(AIS_Plane) anAISPlane = new AIS_Plane (aGeomPlane);
          GetMapOfAIS().Bind (anAISPlane, aName);
          TheAISContext()->Display(anAISPlane);
        }
        // ShapeB is an edge
        else
        {
          // Verify that the vertex is not on the edge ShapeB
          TopoDS_Edge anEdgeB = TopoDS::Edge(aShapeB);
          TopoDS_Vertex aVertA = TopoDS::Vertex(aShapeA);

          BRepExtrema_ExtPC OrthoProj(aVertA, anEdgeB);
          if (OrthoProj.SquareDistance(1)<Precision::Approximation())
          {
            // The vertex is on the edge
            std::cout<<" vplane: error point is on the edge\n";
            return 1;
          }
          else
          {
            // Close the local context
            TheAISContext()->CloseLocalContext(aCurrentIndex);
            // Construction of plane
            gp_Pnt A = BRep_Tool::Pnt(aVertA);
            TopoDS_Vertex aVBa, aVBb;
            TopExp::Vertices(anEdgeB ,aVBa ,aVBb);
            gp_Pnt aBa = BRep_Tool::Pnt(aVBa);
            gp_Pnt aBb = BRep_Tool::Pnt(aVBb);
            GC_MakePlane MkPlane (A, aBa, aBb);
            Handle(Geom_Plane) aGeomPlane = MkPlane.Value();
            Handle(AIS_Plane) anAISPlane = new AIS_Plane (aGeomPlane);
            GetMapOfAIS().Bind (anAISPlane, aName);
            TheAISContext()->Display(anAISPlane);
          }
        }
      }
      // aShapeA is an edge
      else if (aShapeA.ShapeType()==TopAbs_EDGE)
      {
        TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(4));
        TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(2));
        std::cout<<" Select a vertex that don't belong to the edge\n";

        // Wait for picking
        Standard_Integer argccc = 5;
        const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
        const char **argvvv = (const char **) bufff;
        while (ViewerMainLoop( argccc, argvvv) ) { }
        // end of the loop

        TopoDS_Shape aShapeB;
        for (TheAISContext()->InitSelected();
             TheAISContext()->MoreSelected();
             TheAISContext()->NextSelected())
        {
          aShapeB = TheAISContext()->SelectedShape();
        }
        // aShapeB should be a Vertex
        // Check that the vertex aShapeB is not on the edge
        TopoDS_Edge anEdgeA = TopoDS::Edge(aShapeA);
        TopoDS_Vertex aVertB = TopoDS::Vertex(aShapeB);

        BRepExtrema_ExtPC OrthoProj (aVertB, anEdgeA);
        if (OrthoProj.SquareDistance(1)<Precision::Approximation())
        {
          // The vertex is on the edge
          std::cout<<" vplane: error point is on the edge\n";
          return 1;
        }
        else
        {
          // Close the local context
          TheAISContext()->CloseLocalContext(aCurrentIndex);
          // Construction of plane
          gp_Pnt B = BRep_Tool::Pnt(aVertB);
          TopoDS_Vertex aVAa, aVAb;
          TopExp::Vertices(anEdgeA, aVAa, aVAb);
          gp_Pnt Aa = BRep_Tool::Pnt(aVAa);
          gp_Pnt Ab = BRep_Tool::Pnt(aVAb);
          GC_MakePlane MkPlane (B,Aa,Ab);
          Handle(Geom_Plane) aGeomPlane = MkPlane.Value();
          Handle(AIS_Plane) anAISPlane = new AIS_Plane (aGeomPlane);
          GetMapOfAIS().Bind (anAISPlane ,aName);
          TheAISContext()->Display(anAISPlane);
        }
      }
      // aShapeA is a Face
      else
      {
        // Close the local context: nothing to select
        TheAISContext()->CloseLocalContext(aCurrentIndex);
        // Construction of plane
        TopoDS_Face aFace = TopoDS::Face(aShapeA);
        BRepAdaptor_Surface aSurface (aFace, Standard_False);
        if (aSurface.GetType()==GeomAbs_Plane)
        {
          gp_Pln aPlane = aSurface.Plane();
          Handle(Geom_Plane) aGeomPlane = new Geom_Plane(aPlane);
          Handle(AIS_Plane) anAISPlane = new AIS_Plane(aGeomPlane);
          GetMapOfAIS().Bind (anAISPlane, aName);
          TheAISContext()->Display(anAISPlane);
        }
        else
        {
          std::cout<<" vplane: error\n";
          return 1;
        }
      }
    }

    // Function vPlanePara
    // ===================
    // test the constructor AIS_Plane::AIS_Plane(Geom_Plane,gp_Pnt)
    else if (!strcasecmp(argv[0], "vplanepara"))
    {
      TheAISContext()->OpenLocalContext();
      aCurrentIndex = TheAISContext()->IndexOfCurrentLocal();

      // Activate modes Vertex and Face
      TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(1));
      TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(4));
      std::cout<<" Select a vertex or a face\n";

      // Wait for picking
      Standard_Integer argcc = 5;
      const char *buff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
      const char **argvv = (const char **) buff;
      while (ViewerMainLoop( argcc, argvv) ) { }
      // end of the loop

      TopoDS_Shape aShapeA;
      for (TheAISContext()->InitSelected();
           TheAISContext()->MoreSelected();
           TheAISContext()->NextSelected())
      {
        aShapeA = TheAISContext()->SelectedShape();
      }

      if (aShapeA.ShapeType()==TopAbs_VERTEX )
      {
        // aShapeA is a vertex
        // Deactivate the mode Vertex
        TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(1));
        std::cout<<" Select a face\n";

        // Wait for picking
        Standard_Integer argccc = 5;
        const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
        const char **argvvv = (const char **) bufff;
        while (ViewerMainLoop( argccc, argvvv) ) { }
        // end of the loop

        TopoDS_Shape aShapeB;
        for (TheAISContext()->InitSelected();
             TheAISContext()->MoreSelected();
             TheAISContext()->NextSelected())
        {
          // A vertex ShapeA can be on Face ShapeB
          aShapeB = TheAISContext()->SelectedShape();
        }

        // Close the local context
        TheAISContext()->CloseLocalContext(aCurrentIndex);

        // Construction of plane
        gp_Pnt A = BRep_Tool::Pnt(TopoDS::Vertex(aShapeA));

        TopoDS_Face aFace = TopoDS::Face(aShapeB);
        BRepAdaptor_Surface aSurface (aFace, Standard_False);
        if (aSurface.GetType()==GeomAbs_Plane )
        {
          gp_Pln aPlane = aSurface.Plane();
          // Construct a plane parallel to aGeomPlane through A
          aPlane.SetLocation(A);
          Handle(Geom_Plane) aGeomPlane = new Geom_Plane (aPlane);
          Handle(AIS_Plane) aAISPlane = new AIS_Plane (aGeomPlane, A);
          GetMapOfAIS().Bind (aAISPlane ,aName);
          TheAISContext()->Display(aAISPlane);
        }
        else
        {
          std::cout<<" vplanepara: error\n";
          return 1;
        }
      }
      else
      {
        // ShapeA is a Face
        // Deactive the mode Face
        TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(4));
        std::cout<<" Select a vertex\n";

        // Wait for picking
        Standard_Integer argccc = 5;
        const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
        const char **argvvv = (const char **) bufff;
        while (ViewerMainLoop( argccc, argvvv) ) { }
        // end of the loop

        TopoDS_Shape aShapeB;
        for (TheAISContext()->InitSelected();
             TheAISContext()->MoreSelected();
             TheAISContext()->NextSelected())
        {
          // A vertex ShapeB can be on Face ShapeA
          aShapeB = TheAISContext()->SelectedShape();
        }
        // Close the local context
        TheAISContext()->CloseLocalContext(aCurrentIndex);

        // Construction of plane
        gp_Pnt B = BRep_Tool::Pnt(TopoDS::Vertex(aShapeB));

        TopoDS_Face aFace=TopoDS::Face(aShapeA);
        BRepAdaptor_Surface aSurface (aFace, Standard_False);
        if (aSurface.GetType()==GeomAbs_Plane )
        {
          gp_Pln aPlane = aSurface.Plane();
          aPlane.SetLocation(B);
          Handle(Geom_Plane) aGeomPlane = new Geom_Plane (aPlane);
          // Construct a plane parallel to aGeomPlane through B
          Handle(AIS_Plane) anAISPlane = new AIS_Plane (aGeomPlane, B);
          GetMapOfAIS().Bind (anAISPlane, aName);
          TheAISContext()->Display(anAISPlane);
        }
        else
        {
          std::cout<<" vplanepara: error"<<"\n";return 1;
        }
      }
    }

    // Function vplaneortho
    // ====================
    // test the constructor AIS_Plane::AIS_Plane(Geom_Plane,gp_Pnt,gp_Pnt,gp_Pnt)
    else
    {
      TheAISContext()->OpenLocalContext();
      aCurrentIndex = TheAISContext()->IndexOfCurrentLocal();

      // Activate the modes Edge and Face
      TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(2));
      TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(4));
      std::cout<<" Select a face and an edge coplanar\n";

      // Wait for picking
      Standard_Integer argcc = 5;
      const char *buff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
      const char **argvv = (const char **) buff;
      while (ViewerMainLoop( argcc, argvv) ) { }
      // end of the loop

      TopoDS_Shape aShapeA;
      for (TheAISContext()->InitSelected();
           TheAISContext()->MoreSelected();
           TheAISContext()->NextSelected())
      {
        aShapeA = TheAISContext()->SelectedShape();
      }

      if (aShapeA.ShapeType()==TopAbs_EDGE )
      {
        // ShapeA is an edge, deactivate the mode Edge...
        TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(2));
        std::cout<<" Select a face\n";

        // Wait for picking
        Standard_Integer argccc = 5;
        const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
        const char **argvvv = (const char **) bufff;
        while (ViewerMainLoop( argccc, argvvv) ) { }
        // end of the loop

        TopoDS_Shape aShapeB;
        for (TheAISContext()->InitSelected();
             TheAISContext()->MoreSelected();
             TheAISContext()->NextSelected())
        {
          // Edge ShapeA can be on Face ShapeB
          aShapeB = TheAISContext()->SelectedShape();
        }

        // Close the local context
        TheAISContext()->CloseLocalContext(aCurrentIndex);

        // Construction of plane
        TopoDS_Edge anEdgeA = TopoDS::Edge(aShapeA);
        TopoDS_Vertex aVAa, aVAb;
        TopExp::Vertices(anEdgeA, aVAa, aVAb);
        gp_Pnt Aa = BRep_Tool::Pnt(aVAa);
        gp_Pnt Ab = BRep_Tool::Pnt(aVAb);
        gp_Vec ab (Aa,Ab);

        gp_Dir Dab (ab);
        // Creation of rotation axis
        gp_Ax1 aRotAxis (Aa,Dab);

        TopoDS_Face aFace = TopoDS::Face(aShapeB);
        // The edge must be parallel to the face
        BRepExtrema_ExtPF aHeightA (aVAa, aFace);
        BRepExtrema_ExtPF aHeightB (aVAb, aFace);
        // Compare to heights
        if (fabs(sqrt(aHeightA.SquareDistance(1)) - sqrt(aHeightB.SquareDistance(1)))
            >Precision::Confusion())
        {
          // the edge is not parallel to the face
          std::cout<<" vplaneortho error: the edge is not parallel to the face\n";
          return 1;
        }
        // the edge is OK
        BRepAdaptor_Surface aSurface (aFace, Standard_False);
        if (aSurface.GetType()==GeomAbs_Plane)
        {
          gp_Pln aPlane = aSurface.Plane();
          // It rotates a half turn round the axis of rotation
          aPlane.Rotate(aRotAxis , M_PI/2);

          Handle(Geom_Plane) aGeomPlane = new Geom_Plane (aPlane);
          // constructed aGeomPlane parallel to a plane containing the edge (center mid-edge)
          gp_Pnt aMiddle ((Aa.X()+Ab.X() )/2 ,(Aa.Y()+Ab.Y() )/2 ,(Aa.Z()+Ab.Z() )/2 );
          Handle(AIS_Plane) anAISPlane = new AIS_Plane (aGeomPlane, aMiddle);
          GetMapOfAIS().Bind (anAISPlane, aName);
          TheAISContext()->Display(anAISPlane);
        }
        else
        {
          std::cout<<" vplaneortho: error\n";
          return 1;
        }
      }
      else
      {
        // ShapeA is a Face, deactive the mode Face.
        TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(4));
        std::cout<<" Select an edge\n";

        // Wait for picking
        Standard_Integer argccc = 5;
        const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
        const char **argvvv = (const char **) bufff;
        while (ViewerMainLoop( argccc, argvvv) ) { }
        // end of the loop

        TopoDS_Shape aShapeB;
        for (TheAISContext()->InitSelected();
             TheAISContext()->MoreSelected();
             TheAISContext()->NextSelected())
        {
          // Edge ShapeB can be on Face ShapeA
          aShapeB = TheAISContext()->SelectedShape();
        }
        // Close the local context
        TheAISContext()->CloseLocalContext(aCurrentIndex);

        // Construction of plane
        TopoDS_Edge anEdgeB = TopoDS::Edge(aShapeB);
        TopoDS_Vertex aVBa, aVBb;
        TopExp::Vertices(anEdgeB, aVBa, aVBb);
        gp_Pnt aBa = BRep_Tool::Pnt(aVBa);
        gp_Pnt aBb = BRep_Tool::Pnt(aVBb);
        gp_Vec ab (aBa,aBb);
        gp_Dir Dab (ab);
        // Creation of rotation axe
        gp_Ax1 aRotAxis (aBa,Dab);

        TopoDS_Face aFace = TopoDS::Face(aShapeA);
        // The edge must be parallel to the face
        BRepExtrema_ExtPF aHeightA (aVBa, aFace);
        BRepExtrema_ExtPF aHeightB (aVBb, aFace);
        // Comparing the two heights
        if (fabs(sqrt(aHeightA.SquareDistance(1)) - sqrt(aHeightB.SquareDistance(1)))
            >Precision::Confusion())
        {
          // the edge is not parallel to the face
          std::cout<<" vplaneortho error: the edge is not parallel to the face\n";
          return 1;
        }
        // The edge is OK
        BRepAdaptor_Surface aSurface (aFace, Standard_False);
        if (aSurface.GetType()==GeomAbs_Plane)
        {
          gp_Pln aPlane = aSurface.Plane();
          // It rotates a half turn round the axis of rotation
          aPlane.Rotate(aRotAxis , M_PI/2);
          Handle(Geom_Plane) aGeomPlane = new Geom_Plane (aPlane);
          // constructed aGeomPlane parallel to a plane containing the edge theGeomPlane (center mid-edge)
          gp_Pnt aMiddle ((aBa.X()+aBb.X() )/2 , (aBa.Y()+aBb.Y() )/2 , (aBa.Z()+aBb.Z() )/2 );
          Handle(AIS_Plane) anAISPlane = new AIS_Plane (aGeomPlane, aMiddle);
          GetMapOfAIS().Bind (anAISPlane ,aName);
          TheAISContext()->Display(anAISPlane);
        }
        else
        {
          std::cout<<" vplaneortho: error\n";
          return 1;
        }
      }
    }
  }
  return 0;
}


//==============================================================================
// Fonction  vline
// ---------------  Uniquement par parametre. Pas de selection dans le viewer.
//==============================================================================

//==============================================================================
//function : VLineBuilder
//purpose  : Build an AIS_Line
//Draw arg : vline LineName  [AIS_PointName] [AIS_PointName]
//                           [Xa] [Ya] [Za]   [Xb] [Yb] [Zb]
//==============================================================================
#include <Geom_CartesianPoint.hxx>
#include <AIS_Line.hxx>


static int VLineBuilder(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  Standard_Integer myCurrentIndex;
  // Verifications
  if (argc!=4 && argc!=8 && argc!=2 )  {di<<"vline error: number of arguments not correct "<<"\n";return 1; }
  // Fermeture des contextes
  TheAISContext()->CloseAllContexts();

  // On recupere les parametres
  Handle(AIS_InteractiveObject) theShapeA;
  Handle(AIS_InteractiveObject) theShapeB;

  // Parametres: AIS_Point AIS_Point
  // ===============================
  if (argc==4) {
    theShapeA=
      Handle(AIS_InteractiveObject)::DownCast (GetMapOfAIS().Find2(argv[2]));
    // On verifie que c'est bien une AIS_Point
    if (!theShapeA.IsNull() &&
      theShapeA->Type()==AIS_KOI_Datum && theShapeA->Signature()==1) {
        // on recupere le deuxieme AIS_Point
        theShapeB=
          Handle(AIS_InteractiveObject)::DownCast (GetMapOfAIS().Find2(argv[3]));
        if (theShapeA.IsNull() ||
          (!(theShapeB->Type()==AIS_KOI_Datum && theShapeB->Signature()==1)))
        {
          di <<"vline error: wrong type of 2de argument."<<"\n";
          return 1;
        }
      }
    else {di <<"vline error: wrong type of 1st argument."<<"\n";return 1; }
    // Les deux parametres sont du bon type. On verifie que les points ne sont pas confondus
    Handle(AIS_Point) theAISPointA= *(Handle(AIS_Point)*)& theShapeA;
    Handle(AIS_Point) theAISPointB= *(Handle(AIS_Point)*)& theShapeB;

    Handle(Geom_Point ) myGeomPointBA=  theAISPointA->Component();
    Handle(Geom_CartesianPoint ) myCartPointA= *((Handle(Geom_CartesianPoint)*)&  myGeomPointBA);
    //    Handle(Geom_CartesianPoint ) myCartPointA= *(Handle(Geom_CartesianPoint)*)& (theAISPointA->Component() ) ;

    Handle(Geom_Point ) myGeomPointB=  theAISPointB->Component();
    Handle(Geom_CartesianPoint ) myCartPointB= *((Handle(Geom_CartesianPoint)*)&  myGeomPointB);
    //    Handle(Geom_CartesianPoint ) myCartPointB= *(Handle(Geom_CartesianPoint)*)& (theAISPointB->Component() ) ;

    if (myCartPointB->X()==myCartPointA->X() && myCartPointB->Y()==myCartPointA->Y() && myCartPointB->Z()==myCartPointA->Z() ) {
      // B=A
      di<<"vline error: same points"<<"\n";return 1;
    }
    // Les deux points sont OK...Construction de l'AIS_Line (en faite, le segment AB)
    Handle(AIS_Line) theAISLine= new AIS_Line(myCartPointA,myCartPointB );
    GetMapOfAIS().Bind(theAISLine,argv[1] );
    TheAISContext()->Display(theAISLine );

  }

  // Parametres 6 Reals
  // ==================

  else if (argc==8) {
    // On verifie que les deux points ne sont pas confondus

    Standard_Real coord[6];
    for(Standard_Integer i=0;i<=2;i++){
      coord[i]=atof(argv[2+i]);
      coord[i+3]=atof(argv[5+i]);
    }

    Handle(Geom_CartesianPoint ) myCartPointA=new Geom_CartesianPoint (coord[0],coord[1],coord[2] );
    Handle(Geom_CartesianPoint ) myCartPointB=new Geom_CartesianPoint (coord[3],coord[4],coord[5] );

    Handle(AIS_Line) theAISLine= new AIS_Line(myCartPointA,myCartPointB );
    GetMapOfAIS().Bind(theAISLine,argv[1] );
    TheAISContext()->Display(theAISLine );

  }

  // Pas de parametres: Selection dans le viewer.
  // ============================================

  else {
    TheAISContext()->OpenLocalContext();
    myCurrentIndex=TheAISContext()->IndexOfCurrentLocal();

    // Active le mode Vertex.
    TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(1) );
    di<<" Select a vertex "<<"\n";

    // Boucle d'attente waitpick.
    Standard_Integer argcc = 5;
    const char *buff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
    const char **argvv = (const char **) buff;
    while (ViewerMainLoop( argcc, argvv) ) { }
    // fin de la boucle

    TopoDS_Shape ShapeA;
    for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
      ShapeA = TheAISContext()->SelectedShape();
    }

    // ShapeA est un Vertex
    if (ShapeA.ShapeType()==TopAbs_VERTEX ) {

      di<<" Select a different vertex."<<"\n";

      TopoDS_Shape ShapeB;
      do {

        // Boucle d'attente waitpick.
        Standard_Integer argccc = 5;
        const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
        const char **argvvv = (const char **) bufff;
        while (ViewerMainLoop( argccc, argvvv) ) { }
        // fin de la boucle

        for(TheAISContext()->InitSelected() ;TheAISContext()->MoreSelected() ;TheAISContext()->NextSelected() ) {
          ShapeB = TheAISContext()->SelectedShape();
        }


      } while(ShapeB.IsSame(ShapeA) );

      // Fermeture du context local
      TheAISContext()->CloseLocalContext(myCurrentIndex);

      // Construction de la line
      gp_Pnt   A=BRep_Tool::Pnt(TopoDS::Vertex(ShapeA)  );
      gp_Pnt   B=BRep_Tool::Pnt(TopoDS::Vertex(ShapeB)  );

      Handle(Geom_CartesianPoint ) myCartPointA=new Geom_CartesianPoint(A);
      Handle(Geom_CartesianPoint ) myCartPointB=new Geom_CartesianPoint(B);

      Handle(AIS_Line) theAISLine= new AIS_Line(myCartPointA,myCartPointB );
      GetMapOfAIS().Bind(theAISLine,argv[1] );
      TheAISContext()->Display(theAISLine );

    }
    else  {
      di<<"vline error."<<"\n";
    }

  }

  return 0;
}

//==============================================================================
// class   : FilledCircle
// purpose : creates filled circle based on AIS_InteractiveObject 
//           and Geom_Circle.
//           This class is used to check method Matches() of class 
//           Select3D_SensitiveCircle with member myFillStatus = Standard_True, 
//           because none of AIS classes provides creation of 
//           Select3D_SensitiveCircle with member myFillStatus = Standard_True 
//           (look method ComputeSelection() )
//============================================================================== 

Handle(Geom_Circle) CreateCircle(gp_Pnt theCenter, Standard_Real theRadius) 
{
  gp_Ax2 anAxes(theCenter, gp_Dir(gp_Vec(0., 0., 1.))); 
  gp_Circ aCirc(anAxes, theRadius);
  Handle(Geom_Circle) aCircle = new Geom_Circle(aCirc);
  return aCircle;
}

DEFINE_STANDARD_HANDLE(FilledCircle, AIS_InteractiveObject)

class FilledCircle : public AIS_InteractiveObject 
{
public:
    // CASCADE RTTI
    DEFINE_STANDARD_RTTI(FilledCircle)

    FilledCircle(gp_Pnt theCenter, Standard_Real theRadius);
    FilledCircle(Handle(Geom_Circle) theCircle);

private:
    TopoDS_Face ComputeFace();

    // Virtual methods implementation
    void Compute (  const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
                  const Handle(Prs3d_Presentation)& thePresentation,
                  const Standard_Integer theMode);

    void ComputeSelection (  const Handle(SelectMgr_Selection)& theSelection, 
                           const Standard_Integer theMode);

protected:
    Handle(Geom_Circle) myCircle;
    Standard_Boolean myFilledStatus;

}; 

IMPLEMENT_STANDARD_HANDLE(FilledCircle, AIS_InteractiveObject)
IMPLEMENT_STANDARD_RTTIEXT(FilledCircle, AIS_InteractiveObject)

FilledCircle::FilledCircle(gp_Pnt theCenter, Standard_Real theRadius) 
{
  myCircle = CreateCircle(theCenter, theRadius);
  myFilledStatus = Standard_True;
}

FilledCircle::FilledCircle(Handle(Geom_Circle) theCircle) 
{
  myCircle = theCircle;
  myFilledStatus = Standard_True;
}

TopoDS_Face FilledCircle::ComputeFace() 
{
  // Create edge from myCircle 
  BRepBuilderAPI_MakeEdge anEdgeMaker(myCircle->Circ());
  TopoDS_Edge anEdge = anEdgeMaker.Edge(); 

  // Create wire from anEdge 
  BRepBuilderAPI_MakeWire aWireMaker(anEdge);
  TopoDS_Wire aWire = aWireMaker.Wire();

  // Create face from aWire
  BRepBuilderAPI_MakeFace aFaceMaker(aWire);
  TopoDS_Face aFace = aFaceMaker.Face();

  return aFace;
}

void FilledCircle::Compute(const Handle_PrsMgr_PresentationManager3d &thePresentationManager, 
                           const Handle_Prs3d_Presentation &thePresentation, 
                           const Standard_Integer theMode) 
{
  thePresentation->Clear();

  TopoDS_Face aFace = ComputeFace();

  if (aFace.IsNull()) return;
  if (theMode != 0) return;

  StdPrs_ShadedShape::Add(thePresentation, aFace, myDrawer);
}

void FilledCircle::ComputeSelection(const Handle_SelectMgr_Selection &theSelection, 
                                    const Standard_Integer theMode)
{
  Handle(SelectMgr_EntityOwner) anEntityOwner = new SelectMgr_EntityOwner(this);
  Handle(Select3D_SensitiveCircle) aSensitiveCircle = new Select3D_SensitiveCircle(anEntityOwner, 
      myCircle, myFilledStatus);
  theSelection->Add(aSensitiveCircle);
}

//==============================================================================
// Fonction  vcircle
// -----------------  Uniquement par parametre. Pas de selection dans le viewer.
//==============================================================================

//==============================================================================
//function : VCircleBuilder
//purpose  : Build an AIS_Circle
//Draw arg : vcircle CircleName PlaneName PointName Radius IsFilled
//                              PointName PointName PointName IsFilled
//==============================================================================

void DisplayCircle (Handle (Geom_Circle) theGeomCircle,
                    TCollection_AsciiString theName, 
                    Standard_Boolean isFilled) 
{
  Handle(AIS_InteractiveObject) aCircle;
  if (isFilled) 
  {
    aCircle = new FilledCircle(theGeomCircle);
  }
  else
  {
    aCircle = new AIS_Circle(theGeomCircle);
  }

  // Check if there is an object with given name
  // and remove it from context
  if (GetMapOfAIS().IsBound2(theName)) 
  {
    Handle(Standard_Transient) anObj = GetMapOfAIS().Find2(theName);
    Handle(AIS_InteractiveObject) anInterObj = 
         Handle(AIS_InteractiveObject)::DownCast(anObj);
    TheAISContext()->Remove(anInterObj, Standard_False);
    GetMapOfAIS().UnBind2(theName);
   }

   // Bind the circle to its name
   GetMapOfAIS().Bind(aCircle, theName);

   // Display the circle
   TheAISContext()->Display(aCircle);
  
}

static int VCircleBuilder(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  Standard_Integer myCurrentIndex;
  // Verification of the arguments
  if (argc>6 || argc<2) 
  { 
    std::cout << "vcircle error: expect 4 arguments.\n"; 
    return 1; // TCL_ERROR 
  }
  TheAISContext()->CloseAllContexts();

  // There are all arguments
  if (argc == 6) 
  {
    // Get arguments
    TCollection_AsciiString aName(argv[1]);
    Standard_Boolean isFilled = (Standard_Boolean)atoi(argv[5]);

    Handle(AIS_InteractiveObject) theShapeA;
    Handle(AIS_InteractiveObject) theShapeB;

    theShapeA =
      Handle(AIS_InteractiveObject)::DownCast(GetMapOfAIS().Find2(argv[2]));
    theShapeB =
      Handle(AIS_InteractiveObject)::DownCast(GetMapOfAIS().Find2(argv[3]));


    // Arguments: AIS_Point AIS_Point AIS_Point
    // ========================================
    if (!theShapeA.IsNull() && !theShapeB.IsNull() &&
      theShapeA->Type()==AIS_KOI_Datum && theShapeA->Signature()==1)
    {
      if (theShapeB->Type()!=AIS_KOI_Datum || theShapeB->Signature()!=1 ) 
      {
        std::cout << "vcircle error: 2d argument is unexpected to be a point.\n";
        return 1; // TCL_ERROR 
      }
      // The third object must be a point
      Handle(AIS_InteractiveObject) theShapeC =
        Handle(AIS_InteractiveObject)::DownCast(GetMapOfAIS().Find2(argv[4]));
      if (theShapeC.IsNull() ||
        theShapeC->Type()!=AIS_KOI_Datum || theShapeC->Signature()!=1 ) 
      {
        std::cout << "vcircle error: 3d argument is unexpected to be a point.\n";
        return 1; // TCL_ERROR 
      }
        // tag
        // Verify that the three points are different
        Handle(AIS_Point) theAISPointA = Handle(AIS_Point)::DownCast(theShapeA);
        Handle(AIS_Point) theAISPointB = Handle(AIS_Point)::DownCast(theShapeB);
        Handle(AIS_Point) theAISPointC = Handle(AIS_Point)::DownCast(theShapeC);
        
        Handle(Geom_Point) myGeomPointA = theAISPointA->Component();
        Handle(Geom_CartesianPoint) myCartPointA = 
          Handle(Geom_CartesianPoint)::DownCast(myGeomPointA);

        Handle(Geom_Point) myGeomPointB = theAISPointB->Component();
        Handle(Geom_CartesianPoint) myCartPointB =
          Handle(Geom_CartesianPoint)::DownCast(myGeomPointB);

        Handle(Geom_Point) myGeomPointC = theAISPointC->Component();
        Handle(Geom_CartesianPoint) myCartPointC =
          Handle(Geom_CartesianPoint)::DownCast(myGeomPointC);

        // Test A=B
        if (abs(myCartPointA->X()-myCartPointB->X()) <= Precision::Confusion() && 
          abs(myCartPointA->Y()-myCartPointB->Y()) <= Precision::Confusion() && 
          abs(myCartPointA->Z()-myCartPointB->Z()) <= Precision::Confusion() ) 
        {
          std::cout << "vcircle error: Same points.\n"; 
          return 1; // TCL_ERROR 
        }
        // Test A=C
        if (abs(myCartPointA->X()-myCartPointC->X()) <= Precision::Confusion() &&
          abs(myCartPointA->Y()-myCartPointC->Y()) <= Precision::Confusion() && 
          abs(myCartPointA->Z()-myCartPointC->Z()) <= Precision::Confusion() ) 
        {
          std::cout << "vcircle error: Same points.\n"; 
          return 1; // TCL_ERROR 
        }
        // Test B=C
        if (abs(myCartPointB->X()-myCartPointC->X()) <= Precision::Confusion() && 
          abs(myCartPointB->Y()-myCartPointC->Y()) <= Precision::Confusion() && 
          abs(myCartPointB->Z()-myCartPointC->Z()) <= Precision::Confusion() ) 
        {
          std::cout << "vcircle error: Same points.\n"; 
          return 1;// TCL_ERROR 
        }
        // Construction of the circle
        GC_MakeCircle Cir = GC_MakeCircle (myCartPointA->Pnt(), 
          myCartPointB->Pnt(), myCartPointC->Pnt() );
        Handle (Geom_Circle) theGeomCircle;
        try 
        {
          theGeomCircle = Cir.Value();
        }
        catch (StdFail_NotDone)
        {
          std::cout << "vcircle error: can't create circle\n";
          return -1; // TCL_ERROR
        }
        
        DisplayCircle(theGeomCircle, aName, isFilled);
    }

    // Arguments: AIS_Plane AIS_Point Real
    // ===================================
    else if (theShapeA->Type() == AIS_KOI_Datum && 
      theShapeA->Signature() == 7 ) 
    {
      if (theShapeB->Type() != AIS_KOI_Datum || 
        theShapeB->Signature() != 1 ) 
      {
        std::cout << "vcircle error: 2d element is a unexpected to be a point.\n"; 
        return 1; // TCL_ERROR 
      }
      // �heck that the radius is >= 0
      if (atof(argv[4]) <= 0 ) 
      {
        std::cout << "vcircle error: the radius must be >=0.\n"; 
        return 1; // TCL_ERROR 
      }

      // Recover the normal to the plane
      Handle(AIS_Plane) theAISPlane = Handle(AIS_Plane)::DownCast(theShapeA);
      Handle(AIS_Point) theAISPointB = Handle(AIS_Point)::DownCast(theShapeB); 

      Handle(Geom_Plane) myGeomPlane = theAISPlane->Component();
      Handle(Geom_Point) myGeomPointB = theAISPointB->Component();
      Handle(Geom_CartesianPoint) myCartPointB = 
        Handle(Geom_CartesianPoint)::DownCast(myGeomPointB);

      gp_Pln mygpPlane = myGeomPlane->Pln();
      gp_Ax1 thegpAxe = mygpPlane.Axis();
      gp_Dir theDir = thegpAxe.Direction();
      gp_Pnt theCenter = myCartPointB->Pnt();
      Standard_Real TheR = atof(argv[4]);
      GC_MakeCircle Cir = GC_MakeCircle (theCenter, theDir ,TheR);
      Handle (Geom_Circle) theGeomCircle;
      try 
      {
        theGeomCircle = Cir.Value();
      }
      catch (StdFail_NotDone)
      {
        std::cout << "vcircle error: can't create circle\n";
        return -1; // TCL_ERROR
      }

      DisplayCircle(theGeomCircle, aName, isFilled);

    }

    // Error
    else
    {
      std::cout << "vcircle error: 1st argument is a unexpected type.\n"; 
      return 1; // TCL_ERROR 
    }

  }
  // No arguments: selection in the viewer
  // =========================================
  else 
  {
    // Get the name of the circle 
    TCollection_AsciiString aName(argv[1]);

    TheAISContext()->OpenLocalContext();
    myCurrentIndex = TheAISContext()->IndexOfCurrentLocal();

    // Activate selection mode for vertices and faces
    TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(1) );
    TheAISContext()->ActivateStandardMode (AIS_Shape::SelectionType(4) );
    std::cout << " Select a vertex or a face\n";

    // Wait for picking
    Standard_Integer argcc = 5;
    const char *buff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
    const char **argvv = (const char **) buff;
    while (ViewerMainLoop( argcc, argvv) ) { }
    // end of the loop

    TopoDS_Shape ShapeA;
    for(TheAISContext()->InitSelected(); 
      TheAISContext()->MoreSelected(); 
      TheAISContext()->NextSelected() ) 
    {
      ShapeA = TheAISContext()->SelectedShape();
    }

    // ShapeA is a Vertex
    if (ShapeA.ShapeType() == TopAbs_VERTEX ) 
    {
      TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(4) );
      std::cout << " Select a different vertex\n";

      TopoDS_Shape ShapeB;
      do 
      {
        // Wait for picking
        Standard_Integer argccc = 5;
        const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
        const char **argvvv = (const char **) bufff;
        while (ViewerMainLoop( argccc, argvvv) ) { }
        // end of the loop

        for(TheAISContext()->InitSelected(); 
          TheAISContext()->MoreSelected(); 
          TheAISContext()->NextSelected() ) 
        {
          ShapeB = TheAISContext()->SelectedShape();
        }
      } while(ShapeB.IsSame(ShapeA) );

      // Selection of ShapeC
      std::cout << " Select the last vertex\n";
      TopoDS_Shape ShapeC;
      do 
      {
        // Wait for picking
        Standard_Integer argcccc = 5;
        const char *buffff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
        const char **argvvvv = (const char **) buffff;
        while (ViewerMainLoop( argcccc, argvvvv) ) { }
        // end of the loop

        for(TheAISContext()->InitSelected(); 
          TheAISContext()->MoreSelected(); 
          TheAISContext()->NextSelected() ) 
        {
          ShapeC = TheAISContext()->SelectedShape();
        }
      } while(ShapeC.IsSame(ShapeA) || ShapeC.IsSame(ShapeB) );
      
      // Get isFilled
      Standard_Boolean isFilled;
      std::cout << "Enter filled status (0 or 1)\n";
      cin >> isFilled;

      // Close the local context
      TheAISContext()->CloseLocalContext(myCurrentIndex);

      // Construction of the circle
      gp_Pnt A = BRep_Tool::Pnt(TopoDS::Vertex(ShapeA));
      gp_Pnt B = BRep_Tool::Pnt(TopoDS::Vertex(ShapeB));
      gp_Pnt C = BRep_Tool::Pnt(TopoDS::Vertex(ShapeC));

      GC_MakeCircle Cir = GC_MakeCircle (A, B, C);
      Handle (Geom_Circle) theGeomCircle;
      try 
      {
        theGeomCircle = Cir.Value();
      }
      catch (StdFail_NotDone)
      {
        std::cout << "vcircle error: can't create circle\n";
        return -1; // TCL_ERROR
      }

      DisplayCircle(theGeomCircle, aName, isFilled);

    }
    // Shape is a face
    else
    {
      std::cout << " Select a vertex (in your face)\n";
      TheAISContext()->DeactivateStandardMode (AIS_Shape::SelectionType(4) );

      TopoDS_Shape ShapeB;
      // Wait for picking
      Standard_Integer argccc = 5;
      const char *bufff[] = { "VPick", "X", "VPickY","VPickZ", "VPickShape" };
      const char **argvvv = (const char **) bufff;
      while (ViewerMainLoop( argccc, argvvv) ) { }
      // end of the loop

      for(TheAISContext()->InitSelected(); 
        TheAISContext()->MoreSelected(); 
        TheAISContext()->NextSelected() ) 
      {
        ShapeB = TheAISContext()->SelectedShape();
      }

      // Recover the radius 
      Standard_Real theRad;
      do 
      {
        std::cout << " Enter the value of the radius:\n";
        cin >> theRad;
      } while (theRad <= 0);
      
      // Get filled status
      Standard_Boolean isFilled;
      std::cout << "Enter filled status (0 or 1)\n";
      cin >> isFilled;

      // Close the local context
      TheAISContext()->CloseLocalContext(myCurrentIndex);
      // Construction of the circle

      // Recover the normal to the plane. tag
      TopoDS_Face myFace = TopoDS::Face(ShapeA);
      BRepAdaptor_Surface mySurface (myFace, Standard_False);
      gp_Pln myPlane = mySurface.Plane();
      Handle(Geom_Plane) theGeomPlane = new Geom_Plane (myPlane);
      gp_Pln mygpPlane = theGeomPlane->Pln();
      gp_Ax1 thegpAxe = mygpPlane.Axis();
      gp_Dir theDir = thegpAxe.Direction();

      // Recover the center
      gp_Pnt theCenter = BRep_Tool::Pnt(TopoDS::Vertex(ShapeB));

      // �onstruct the circle
      GC_MakeCircle Cir = GC_MakeCircle (theCenter, theDir ,theRad);
      Handle (Geom_Circle) theGeomCircle;
      try 
      {
        theGeomCircle = Cir.Value();
      }
      catch (StdFail_NotDone)
      {
        std::cout << "vcircle error: can't create circle\n";
        return -1; // TCL_ERROR
      }

      DisplayCircle(theGeomCircle, aName, isFilled);
      
    }

  }

  return 0;
}


//===============================================================================================
//function : VDrawText
//author   : psn
//purpose  : Create a text.
//Draw arg : vdrawtext  name  [X] [Y] [Z] [R] [G] [B] [hor_align] [ver_align] [angle] [zoomable]
//===============================================================================================
#include <Graphic3d_Group.hxx>
#include <Graphic3d_Structure.hxx>
#include <Graphic3d_NameOfFont.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <Graphic2d_GraphicObject.hxx>
#include <Graphic3d_Array1OfVertex.hxx>
#include <Graphic3d_AspectFillArea3d.hxx>
#include <Graphic3d_StructureManager.hxx>
#include <Graphic3d_VerticalTextAlignment.hxx>
#include <Graphic3d_HorizontalTextAlignment.hxx>

#include <Visual3d_ViewManager.hxx>
#include <ViewerTest_Tool.ixx>

#include <Standard_DefineHandle.hxx>

#include <Prs3d_Root.hxx>
#include <Prs3d_Text.hxx>
#include <Prs3d_TextAspect.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <PrsMgr_PresentationManager3d.hxx>

#include <TCollection_ExtendedString.hxx>
#include <TCollection_AsciiString.hxx>

#include <gp_Pnt.hxx>
#include <Quantity_NameOfColor.hxx>
#include <Quantity_Color.hxx>


DEFINE_STANDARD_HANDLE(MyTextClass, AIS_InteractiveObject)

class MyTextClass:public AIS_InteractiveObject
{
public:
  // CASCADE RTTI
  DEFINE_STANDARD_RTTI(MyTextClass )

  MyTextClass(){};

  MyTextClass
    (
      const TCollection_ExtendedString& , const gp_Pnt& ,
      Quantity_Color color,
      Standard_Integer aHJust,
      Standard_Integer aVJust ,
      Standard_Real Angle ,
      Standard_Boolean Zoom ,
      Standard_Real  Height,
      Font_FontAspect FontAspect,
      Standard_CString Font
    );

private:

  void Compute (  const Handle(PrsMgr_PresentationManager3d)& aPresentationManager,
                  const Handle(Prs3d_Presentation)& aPresentation,
                  const Standard_Integer aMode);

  void ComputeSelection (  const Handle(SelectMgr_Selection)& aSelection,
                           const Standard_Integer aMode){} ;

protected:
  TCollection_ExtendedString          aText;
  gp_Pnt                              aPosition;
  Standard_Real                       Red;
  Standard_Real                       Green;
  Standard_Real                       Blue;
  Standard_Real                       aAngle;
  Standard_Real                       aHeight;
  Standard_Boolean                    aZoomable;
  Quantity_Color                      aColor;
  Standard_CString                    aFont;
  Font_FontAspect                     aFontAspect;
  Graphic3d_HorizontalTextAlignment   aHJustification;
  Graphic3d_VerticalTextAlignment     aVJustification;
};



IMPLEMENT_STANDARD_HANDLE(MyTextClass, AIS_InteractiveObject)
IMPLEMENT_STANDARD_RTTIEXT(MyTextClass, AIS_InteractiveObject)


MyTextClass::MyTextClass( const TCollection_ExtendedString& text, const gp_Pnt& position,
                          Quantity_Color    color       = Quantity_NOC_YELLOW,
                          Standard_Integer  aHJust      = Graphic3d_HTA_LEFT,
                          Standard_Integer  aVJust      = Graphic3d_VTA_BOTTOM,
                          Standard_Real     angle       = 0.0 ,
                          Standard_Boolean  zoomable    = Standard_True,
                          Standard_Real     height      = 12.,
                          Font_FontAspect   fontAspect  = Font_FA_Regular,
                          Standard_CString  font        = "Courier")
{
  aText           = text;
  aPosition       = position;
  aHJustification = Graphic3d_HorizontalTextAlignment(aHJust);
  aVJustification = Graphic3d_VerticalTextAlignment(aVJust);
  aAngle          = angle;
  aZoomable       = zoomable;
  aHeight         = height;
  aColor          = color;
  aFontAspect     = fontAspect;
  aFont           = font;
};



//////////////////////////////////////////////////////////////////////////////
void MyTextClass::Compute(const Handle(PrsMgr_PresentationManager3d)& aPresentationManager,
                          const Handle(Prs3d_Presentation)& aPresentation,
                          const Standard_Integer aMode)
{

  aPresentation->Clear();

  Handle_Prs3d_TextAspect asp = myDrawer->TextAspect();

  asp->SetFont(aFont);
  asp->SetColor(aColor);
  asp->SetHeight(aHeight); // I am changing the myHeight value

  asp->SetHorizontalJustification(aHJustification);
  asp->SetVerticalJustification(aVJustification);
  asp->Aspect()->SetTextZoomable(aZoomable);
  asp->Aspect()->SetTextAngle(aAngle);
  asp->Aspect()->SetTextFontAspect(aFontAspect);
  Prs3d_Text::Draw(aPresentation, asp, aText, aPosition);

  /* This comment code is worked
  Handle(Graphic3d_Group) TheGroup = Prs3d_Root::CurrentGroup(aPresentation);
  Handle(Graphic3d_AspectFillArea3d) aspect = myDrawer->ShadingAspect()->Aspect();
  Graphic3d_Vertex vertices_text;
  vertices_text.SetCoord(aPosition.X(),aPosition.Y(),aPosition.Y());
  TheGroup->SetPrimitivesAspect(aspect);
  TheGroup->BeginPrimitives();
  TheGroup->Text(aText,vertices_text,aHeight,Standard_True);
  TheGroup->EndPrimitives();
  */
};

static int VDrawText (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  // Check arguments
  if (argc < 14)
  {
    di<<"Error: "<<argv[0]<<" - invalid number of arguments\n";
    di<<"Usage: type help "<<argv[0]<<"\n";
    return 1; //TCL_ERROR
  }

  Handle(AIS_InteractiveContext) aContext = ViewerTest::GetAISContext();

  // Create 3D view if it doesn't exist
  if ( aContext.IsNull() )
  {
    ViewerTest::ViewerInit();
    aContext = ViewerTest::GetAISContext();
    if( aContext.IsNull() )
    {
      di << "Error: Cannot create a 3D view\n";
      return 1; //TCL_ERROR
    }
  }

  // Text position
  const Standard_Real X = atof(argv[2]);
  const Standard_Real Y = atof(argv[3]);
  const Standard_Real Z = atof(argv[4]);
  const gp_Pnt pnt(X,Y,Z);

  // Text color
  const Quantity_Parameter R = atof(argv[5])/255.;
  const Quantity_Parameter G = atof(argv[6])/255.;
  const Quantity_Parameter B = atof(argv[7])/255.;
  const Quantity_Color aColor( R, G, B, Quantity_TOC_RGB );

  // Text alignment
  const int hor_align = atoi(argv[8]);
  const int ver_align = atoi(argv[9]);

  // Text angle
  const Standard_Real angle = atof(argv[10]);

  // Text zooming
  const Standard_Boolean zoom = atoi(argv[11]);

  // Text height
  const Standard_Real height = atof(argv[12]);

  // Text aspect
  const Font_FontAspect aspect = Font_FontAspect(atoi(argv[13]));

  // Text font
  TCollection_AsciiString font;
  if(argc < 15)
    font.AssignCat("Courier");
  else
    font.AssignCat(argv[14]);

  // Text is multibyte
  const Standard_Boolean isMultibyte = (argc < 16)? Standard_False : (atoi(argv[15]) != 0);

  // Read text string
  TCollection_ExtendedString name;
  if (isMultibyte)
  {
    const char *str = argv[1];
    while ( *str || *(str+1)=='\x0A' || *(str+1)=='\x0B' || *(str+1)=='\x0C' || *(str+1)=='\x0D'
                 || *(str+1)=='\x07' || *(str+1)=='\x08' || *(str+1)=='\x09' )
    {
      unsigned short c1 = *str++;
      unsigned short c2 = *str++;
      if (!c2) break;
      name += (Standard_ExtCharacter)((c1 << 8) | c2);
    }
  }
  else
  {
    name += argv[1];
  }

  if (name.Length())
  {
    Handle(MyTextClass) myT = new MyTextClass(name,pnt,aColor,hor_align,ver_align,angle,zoom,height,aspect,font.ToCString());
    aContext->Display(myT,Standard_True);
  }

  return 0;
}

#include <math.h>
#include <gp_Pnt.hxx>
#include <Graphic3d_ArrayOfPoints.hxx>
#include <Graphic3d_ArrayOfPrimitives.hxx>
#include <Graphic3d_Array1OfVertex.hxx>
#include <Graphic3d_ArrayOfTriangles.hxx>
#include <Poly_Array1OfTriangle.hxx>
#include <Poly_Triangle.hxx>
#include <Poly_Triangulation.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TShort_Array1OfShortReal.hxx>
#include <TShort_HArray1OfShortReal.hxx>

#include <AIS_Triangulation.hxx>
#include <Aspect_GraphicDevice.hxx>
#include <StdPrs_ToolShadedShape.hxx>
#include <Poly_Connect.hxx>
#include <TColgp_Array1OfDir.hxx>
#include <Graphic3d_GraphicDriver.hxx>

#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <Graphic3d_MaterialAspect.hxx>
#include <Graphic3d_AspectFillArea3d.hxx>

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <TopoDS_Shape.hxx>
#include <TopExp_Explorer.hxx>
#include <TopAbs.hxx>
#include <StdSelect_ShapeTypeFilter.hxx>


//===============================================================================================
//function : CalculationOfSphere
//author   : psn
//purpose  : Create a Sphere
//===============================================================================================

Handle( Poly_Triangulation ) CalculationOfSphere( double X , double Y , double Z ,
                                                  int res ,
                                                  double Radius ){
  double mRadius = Radius;
  double mCenter[3] = {X,Y,Z};
  int mThetaResolution;
  int mPhiResolution;
  double mStartTheta = 0;//StartTheta;
  double mEndTheta = 360;//EndTheta;
  double mStartPhi = 0;//StartPhi;
  double mEndPhi = 180;//EndPhi;
  res = res < 4 ? 4 : res;

  mThetaResolution = res;
  mPhiResolution = res;

  int i, j;
  int jStart, jEnd, numOffset;
  double x[3], n[3], deltaPhi, deltaTheta, phi, theta, radius;
  double startTheta, endTheta, startPhi, endPhi;
  int base, numPoles=0, thetaResolution, phiResolution;

  int pts[3];
  int piece = -1;
  int numPieces = 1;
  if ( numPieces > mThetaResolution ) {
    numPieces = mThetaResolution;
  }

  int localThetaResolution =  mThetaResolution;
  double localStartTheta =  mStartTheta;
  double localEndTheta =  mEndTheta;

  while ( localEndTheta < localStartTheta ) {
    localEndTheta += 360.0;
  }

  deltaTheta = (localEndTheta - localStartTheta) / localThetaResolution;

  // Change the ivars based on pieces.
  int start, end;
  start = piece * localThetaResolution / numPieces;
  end = (piece+1) * localThetaResolution / numPieces;
  localEndTheta = localStartTheta + (double)(end) * deltaTheta;
  localStartTheta = localStartTheta + (double)(start) * deltaTheta;
  localThetaResolution = end - start;

  // Create north pole if needed
  int number_point = 0;
  int number_pointArray = 0;

  if ( mStartPhi <= 0.0 ) {
    number_pointArray++;
    numPoles++;
  }
  if ( mEndPhi >= 180.0 ) {
    number_pointArray++;
    numPoles++;
  }

  // Check data, determine increments, and convert to radians
  startTheta = (localStartTheta < localEndTheta ? localStartTheta : localEndTheta);
  startTheta *= M_PI  / 180.0;
  endTheta = (localEndTheta > localStartTheta ? localEndTheta : localStartTheta);
  endTheta *= M_PI  / 180.0;


  startPhi = ( mStartPhi <  mEndPhi ?  mStartPhi :  mEndPhi);
  startPhi *= M_PI  / 180.0;
  endPhi = ( mEndPhi >  mStartPhi ?  mEndPhi :  mStartPhi);
  endPhi *= M_PI  / 180.0;

  phiResolution =  mPhiResolution - numPoles;
  deltaPhi = (endPhi - startPhi) / ( mPhiResolution - 1);
  thetaResolution = localThetaResolution;
  if ( fabs(localStartTheta - localEndTheta) < 360.0 ) {
    ++localThetaResolution;
  }
  deltaTheta = (endTheta - startTheta) / thetaResolution;

  jStart = ( mStartPhi <= 0.0 ? 1 : 0);
  jEnd = ( mEndPhi >= 180.0 ?  mPhiResolution - 1 :  mPhiResolution);

  // Create intermediate points
  for ( i = 0; i < localThetaResolution; i++ ) {
    for ( j = jStart; j < jEnd; j++ ) {
        number_pointArray++;
    }
  }

  //Generate mesh connectivity
  base = phiResolution * localThetaResolution;

  int number_triangle = 0 ;
  if ( mStartPhi <= 0.0 ) { // around north pole
    number_triangle += localThetaResolution;
  }

  if ( mEndPhi >= 180.0 ) { // around south pole
    number_triangle += localThetaResolution;
  }

  // bands in-between poles
  for ( i=0; i < localThetaResolution; i++){
    for ( j=0; j < (phiResolution-1); j++){
       number_triangle +=2;
    }
  }

  Handle( Poly_Triangulation ) polyTriangulation = new Poly_Triangulation(number_pointArray, number_triangle, false);
  TColgp_Array1OfPnt& PointsOfArray = polyTriangulation->ChangeNodes();
  Poly_Array1OfTriangle& pArrayTriangle = polyTriangulation->ChangeTriangles();

  if (  mStartPhi <= 0.0 ){
      x[0] =  mCenter[0];
      x[1] =  mCenter[1];
      x[2] =  mCenter[2] +  mRadius;
      PointsOfArray.SetValue(1,gp_Pnt(x[0],x[1],x[2]));
  }

  // Create south pole if needed
  if (  mEndPhi >= 180.0 ){
      x[0] =  mCenter[0];
      x[1] =  mCenter[1];
      x[2] =  mCenter[2] -  mRadius;
      PointsOfArray.SetValue(2,gp_Pnt(x[0],x[1],x[2]));
  }

  number_point = 3;
  for ( i=0; i < localThetaResolution; i++){
    theta = localStartTheta * M_PI / 180.0 + i*deltaTheta;
    for ( j = jStart; j < jEnd; j++){
        phi = startPhi + j*deltaPhi;
        radius =  mRadius * sin((double)phi);
        n[0] = radius * cos((double)theta);
        n[1] = radius * sin((double)theta);
        n[2] =  mRadius * cos((double)phi);
        x[0] = n[0] +  mCenter[0];
        x[1] = n[1] +  mCenter[1];
        x[2] = n[2] +  mCenter[2];
        PointsOfArray.SetValue(number_point,gp_Pnt(x[0],x[1],x[2]));
        number_point++;
      }
    }

  numPoles = 3;
  number_triangle = 1;
  if ( mStartPhi <= 0.0 ){// around north pole
    for (i=0; i < localThetaResolution; i++){
        pts[0] = phiResolution*i + numPoles;
        pts[1] = (phiResolution*(i+1) % base) + numPoles;
        pts[2] = 1;
        pArrayTriangle.SetValue(number_triangle,Poly_Triangle(pts[0],pts[1],pts[2]));
        number_triangle++;
      }
    }

  if (  mEndPhi >= 180.0 ){ // around south pole
    numOffset = phiResolution - 1 + numPoles;
    for (i=0; i < localThetaResolution; i++){
        pts[0] = phiResolution*i + numOffset;
        pts[2] = ((phiResolution*(i+1)) % base) + numOffset;
        pts[1] = numPoles - 1;
        pArrayTriangle.SetValue(number_triangle,Poly_Triangle(pts[0],pts[1],pts[2]));
        number_triangle++;
      }
    }

  // bands in-between poles

  for (i=0; i < localThetaResolution; i++){
    for (j=0; j < (phiResolution-1); j++){
        pts[0] = phiResolution*i + j + numPoles;
        pts[1] = pts[0] + 1;
        pts[2] = ((phiResolution*(i+1)+j) % base) + numPoles + 1;
        pArrayTriangle.SetValue(number_triangle,Poly_Triangle(pts[0],pts[1],pts[2]));
        number_triangle++;
        pts[1] = pts[2];
        pts[2] = pts[1] - 1;
        pArrayTriangle.SetValue(number_triangle,Poly_Triangle(pts[0],pts[1],pts[2]));
        number_triangle++;
      }
    }

  Poly_Connect* pc = new Poly_Connect(polyTriangulation);

  Handle(TShort_HArray1OfShortReal) Normals = new TShort_HArray1OfShortReal(1, polyTriangulation->NbNodes() * 3);

  Standard_Integer index[3];
  Standard_Real Tol = Precision::Confusion();

  gp_Dir Nor;
  for (i = PointsOfArray.Lower(); i <= PointsOfArray.Upper(); i++) {
      gp_XYZ eqPlan(0, 0, 0);
      for ( pc->Initialize(i); pc->More(); pc->Next()) {
        pArrayTriangle(pc->Value()).Get(index[0], index[1], index[2]);
        gp_XYZ v1(PointsOfArray(index[1]).Coord()-PointsOfArray(index[0]).Coord());
        gp_XYZ v2(PointsOfArray(index[2]).Coord()-PointsOfArray(index[1]).Coord());
        gp_XYZ vv = v1^v2;
        Standard_Real mod = vv.Modulus();
        if(mod < Tol) continue;
        eqPlan += vv/mod;
      }

      Standard_Real modmax = eqPlan.Modulus();

      if(modmax > Tol)
        Nor = gp_Dir(eqPlan);
      else
        Nor = gp_Dir(0., 0., 1.);

      Standard_Integer j = (i - PointsOfArray.Lower()) * 3;
      Normals->SetValue(j + 1, (Standard_ShortReal)Nor.X());
      Normals->SetValue(j + 2, (Standard_ShortReal)Nor.Y());
      Normals->SetValue(j + 3, (Standard_ShortReal)Nor.Z());
  }

  delete pc;
  polyTriangulation->SetNormals(Normals);

  return polyTriangulation;
}

//===============================================================================================
//function : VDrawSphere
//author   : psn
//purpose  : Create an AIS shape.
//===============================================================================================
static int VDrawSphere (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  // check for errors
  Handle(AIS_InteractiveContext) aContextAIS = ViewerTest::GetAISContext();
  if (aContextAIS.IsNull())
  {
    std::cout << "Call vinit before!\n";
    return 1;
  }
  else if (argc < 3)
  {
    std::cout << "Use: " << argv[0]
              << " shapeName Fineness [X=0.0 Y=0.0 Z=0.0] [Radius=100.0] [ToEnableVBO=1] [NumberOfViewerUpdate=1] [ToShowEdges=0]\n";
    return 1;
  }

  // read the arguments
  TCollection_AsciiString aShapeName (argv[1]);
  Standard_Integer aResolution = atoi (argv[2]);
  Standard_Real aCenterX = (argc > 5) ? atof (argv[3]) : 0.0;
  Standard_Real aCenterY = (argc > 5) ? atof (argv[4]) : 0.0;
  Standard_Real aCenterZ = (argc > 5) ? atof (argv[5]) : 0.0;
  Standard_Real aRadius =  (argc > 6) ? atof (argv[6]) : 100.0;
  Standard_Boolean toShowEdges =  (argc > 7) ? atoi (argv[7]) : Standard_False;

  // remove AIS object with given name from map
  VDisplayAISObject (aShapeName, Handle(AIS_InteractiveObject)());

  std::cout << "Compute Triangulation...\n";
  Handle(AIS_Triangulation) aShape
    = new AIS_Triangulation (CalculationOfSphere (aCenterX, aCenterY, aCenterZ,
                                                  aResolution,
                                                  aRadius));
  Standard_Integer aNumberPoints    = aShape->GetTriangulation()->Nodes().Length();
  Standard_Integer aNumberTriangles = aShape->GetTriangulation()->Triangles().Length();

  // stupid initialization of Green color in RGBA space as integer
  // probably wrong for big-endian CPUs
  Standard_Integer aRed    = 0;
  Standard_Integer aGreen  = 255;
  Standard_Integer aBlue   = 0;
  Standard_Integer anAlpha = 0; // not used
  Standard_Integer aColorInt = aRed;
  aColorInt += aGreen  << 8;
  aColorInt += aBlue   << 16;
  aColorInt += anAlpha << 24;

  // setup colors array per vertex
  Handle(TColStd_HArray1OfInteger) aColorArray = new TColStd_HArray1OfInteger (1, aNumberPoints);
  for (Standard_Integer aNodeId = 1; aNodeId <= aNumberPoints; ++aNodeId)
  {
    aColorArray->SetValue (aNodeId, aColorInt);
  }
  aShape->SetColors (aColorArray);

  // show statistics
  Standard_Integer aPointsSize      = aNumberPoints * 3 * sizeof(float);  // 3x GLfloat
  Standard_Integer aNormalsSize     = aNumberPoints * 3 * sizeof(float);  // 3x GLfloat
  Standard_Integer aColorsSize      = aNumberPoints * 3 * sizeof(float);  // 3x GLfloat without alpha
  Standard_Integer aTrianglesSize   = aNumberTriangles * 3 * sizeof(int); // 3x GLint
  Standard_Integer aPolyConnectSize = aNumberPoints * 4 + aNumberTriangles * 6 * 4;
  Standard_Integer aTotalSize       = aPointsSize + aNormalsSize + aColorsSize + aTrianglesSize;
  aTotalSize >>= 20; //MB
  aNormalsSize >>= 20;
  aColorsSize >>= 20;
  aTrianglesSize >>= 20;
  aPolyConnectSize >>= 20;
  std::cout << "NumberOfPoints:    " << aNumberPoints << "\n"
            << "NumberOfTriangles: " << aNumberTriangles << "\n"
            << "Amount of memory required for PolyTriangulation without Normals: " << (aTotalSize - aNormalsSize) << " Mb\n"
            << "Amount of memory for colors: " << aColorsSize << " Mb\n"
            << "Amount of memory for PolyConnect: " << aPolyConnectSize << " Mb\n"
            << "Amount of graphic card memory required: " << aTotalSize << " Mb\n";

  // Setting material properties, very important for desirable visual result!
  Graphic3d_MaterialAspect aMat (Graphic3d_NOM_PLASTIC);
  aMat.SetAmbient (0.2);
  aMat.SetSpecular (0.5);
  Handle(Graphic3d_AspectFillArea3d) anAspect
    = new Graphic3d_AspectFillArea3d (Aspect_IS_SOLID,
                                      Quantity_NOC_RED,
                                      Quantity_NOC_YELLOW,
                                      Aspect_TOL_SOLID,
                                      1.0,
                                      aMat,
                                      aMat);
  Handle(Prs3d_ShadingAspect) aShAsp = new Prs3d_ShadingAspect();
  if (toShowEdges)
  {
    anAspect->SetEdgeOn();
  }
  else
  {
    anAspect->SetEdgeOff();
  }
  aShAsp->SetAspect (anAspect);
  aShape->Attributes()->SetShadingAspect (aShAsp);

  VDisplayAISObject (aShapeName, aShape);
  return 0;
}

//===============================================================================================
//function : VClipPlane
//purpose  :
//===============================================================================================
static int VClipPlane (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  Handle(V3d_Viewer) aViewer = ViewerTest::GetViewerFromContext();
  Handle(V3d_View) aView = ViewerTest::CurrentView();
  Standard_Real coeffA, coeffB, coeffC, coeffD;
  if (aViewer.IsNull() || aView.IsNull())
  {
    std::cout << "Viewer not initialized!\n";
    return 1;
  }

  // count an active planes count
  Standard_Integer aNewPlaneId = 1;
  Standard_Integer anActivePlanes = 0;
  for (aViewer->InitDefinedPlanes(); aViewer->MoreDefinedPlanes(); aViewer->NextDefinedPlanes(), ++aNewPlaneId)
  {
    Handle(V3d_Plane) aPlaneV3d = aViewer->DefinedPlane();
    if (aView->IsActivePlane (aPlaneV3d))
    {
      ++anActivePlanes;
    }
  }

  if (argc == 1)
  {
    // just show info about existing planes
    Standard_Integer aPlaneId = 1;
    std::cout << "Active planes: " << anActivePlanes << " from maximal " << aView->View()->PlaneLimit() << "\n";
    for (aViewer->InitDefinedPlanes(); aViewer->MoreDefinedPlanes(); aViewer->NextDefinedPlanes(), ++aPlaneId)
    {
      Handle(V3d_Plane) aPlaneV3d = aViewer->DefinedPlane();
      aPlaneV3d->Plane (coeffA, coeffB, coeffC, coeffD);
      gp_Pln aPlane (coeffA, coeffB, coeffC, coeffD);
      const gp_Pnt& aLoc = aPlane.Location();
      const gp_Dir& aNor = aPlane.Axis().Direction();
      Standard_Boolean isActive = aView->IsActivePlane (aPlaneV3d);
      std::cout << "Plane #" << aPlaneId
        << " " << aLoc.X() << " " << aLoc.Y() << " " << aLoc.Z()
        << " " << aNor.X() << " " << aNor.Y() << " " << aNor.Z()
        << (isActive ? " on" : " off")
        << (aPlaneV3d->IsDisplayed() ? ", displayed" : ", hidden")
        << "\n";
    }
    if (aPlaneId == 1)
    {
      std::cout << "No defined clipping planes\n";
    }
    return 0;
  }
  else if (argc == 2 || argc == 3)
  {
    Standard_Integer aPlaneIdToOff = (argc == 3) ? atoi (argv[1]) : 1;
    Standard_Boolean toIterateAll = (argc == 2);
    TCollection_AsciiString isOnOffStr ((argc == 3) ? argv[2] : argv[1]);
    isOnOffStr.LowerCase();
    Standard_Integer aPlaneId = 1;
    for (aViewer->InitDefinedPlanes(); aViewer->MoreDefinedPlanes(); aViewer->NextDefinedPlanes(), ++aPlaneId)
    {
      if (aPlaneIdToOff == aPlaneId || toIterateAll)
      {
        Handle(V3d_Plane) aPlaneV3d = aViewer->DefinedPlane();
        if (isOnOffStr.Search ("off") >= 0)
        {
          aView->SetPlaneOff (aPlaneV3d);
          std::cout << "Clipping plane #" << aPlaneId << " was disabled\n";
        }
        else if (isOnOffStr.Search ("on") >= 0)
        {
          // avoid z-fighting glitches
          aPlaneV3d->Erase();
          if (!aView->IsActivePlane (aPlaneV3d))
          {
            if (anActivePlanes < aView->View()->PlaneLimit())
            {
              aView->SetPlaneOn (aPlaneV3d);
              std::cout << "Clipping plane #" << aPlaneId << " was enabled\n";
            }
            else
            {
              std::cout << "Maximal active planes limit exceeded (" << anActivePlanes << ")\n"
                        << "You should disable or remove some existing plane to activate this one\n";
            }
          }
          else
          {
            std::cout << "Clipping plane #" << aPlaneId << " was already enabled\n";
          }
        }
        else if (isOnOffStr.Search ("del") >= 0 || isOnOffStr.Search ("rem") >= 0)
        {
          aPlaneV3d->Erase(); // not performed on destructor!!!
          aView->SetPlaneOff (aPlaneV3d);
          aViewer->DelPlane (aPlaneV3d);
          std::cout << "Clipping plane #" << aPlaneId << " was removed\n";
          if (toIterateAll)
          {
            for (aViewer->InitDefinedPlanes(); aViewer->MoreDefinedPlanes(); aViewer->InitDefinedPlanes(), ++aPlaneId)
            {
              aPlaneV3d = aViewer->DefinedPlane();
              aPlaneV3d->Erase(); // not performed on destructor!!!
              aView->SetPlaneOff (aPlaneV3d);
              aViewer->DelPlane (aPlaneV3d);
              std::cout << "Clipping plane #" << aPlaneId << " was removed\n";
            }
            break;
          }
          else
          {
            break;
          }
        }
        else if (isOnOffStr.Search ("disp") >= 0 || isOnOffStr.Search ("show") >= 0)
        {
          // avoid z-fighting glitches
          aView->SetPlaneOff (aPlaneV3d);
          aPlaneV3d->Display (aView);
          std::cout << "Clipping plane #" << aPlaneId << " was shown and disabled\n";
        }
        else if (isOnOffStr.Search ("hide") >= 0)
        {
          aPlaneV3d->Erase();
          std::cout << "Clipping plane #" << aPlaneId << " was hidden\n";
        }
        else
        {
          std::cout << "Usage: " << argv[0] << " [x y z dx dy dz] [planeId {on/off/del/display/hide}]\n";
          return 1;
        }
      }
    }
    if (aPlaneIdToOff >= aPlaneId && !toIterateAll)
    {
      std::cout << "Clipping plane with id " << aPlaneIdToOff << " not found!\n";
      return 1;
    }
    aView->Update();
    return 0;
  }
  else if (argc != 7)
  {
    std::cout << "Usage: " << argv[0] << " [x y z dx dy dz] [planeId {on/off/del/display/hide}]\n";
    return 1;
  }

  Standard_Real aLocX = atof (argv[1]);
  Standard_Real aLocY = atof (argv[2]);
  Standard_Real aLocZ = atof (argv[3]);
  Standard_Real aNormDX = atof (argv[4]);
  Standard_Real aNormDY = atof (argv[5]);
  Standard_Real aNormDZ = atof (argv[6]);

  Handle(V3d_Plane) aPlaneV3d = new V3d_Plane();
  gp_Pln aPlane (gp_Pnt (aLocX, aLocY, aLocZ), gp_Dir (aNormDX, aNormDY, aNormDZ));
  aPlane.Coefficients (coeffA, coeffB, coeffC, coeffD);
  aPlaneV3d->SetPlane(coeffA, coeffB, coeffC, coeffD);

  aViewer->AddPlane (aPlaneV3d); // add to defined planes list
  std::cout << "Added clipping plane #" << aNewPlaneId << "\n";
  if (anActivePlanes < aView->View()->PlaneLimit())
  {
    aView->SetPlaneOn (aPlaneV3d); // add to enabled planes list
    aView->Update();
  }
  else
  {
    std::cout << "Maximal active planes limit exceeded (" << anActivePlanes << ")\n"
              << "You should disable or remove some existing plane to activate the new one\n";
  }
  return 0;
}

//=============================================================================
//function : VComputeHLR
//purpose  :
//=============================================================================

static int VComputeHLR (Draw_Interpretor& di,
                        Standard_Integer argc,
                        const char** argv)
{
  Handle(AIS_InteractiveContext) aContextAIS = ViewerTest::GetAISContext ();

  if (aContextAIS.IsNull ())
  {
    di << "Please call vinit before\n";
    return 1;
  }

  if ( argc != 3 &&  argc != 12 )
  {
    di << "Usage: " << argv[0] << " ShapeName HlrName "
       << "[ eye_x eye_y eye_z dir_x dir_y dir_z upx upy upz ]" << "\n"
       << "                    ShapeName - name of the initial shape\n"
       << "                    HlrName - result hlr object from initial shape\n"
       << "                    eye, dir are eye position and look direction\n"
       << "                    up is the look up direction vector\n"
       << "                    Use vtop to see projected hlr shape\n";
    return 1;
  }

  // shape and new object name
  TCollection_AsciiString aShapeName (argv[1]);
  TCollection_AsciiString aHlrName (argv[2]);

  TopoDS_Shape aSh = DBRep::Get (argv[1]);
  if (aSh.IsNull()) 
  {
    BRep_Builder aBrepBuilder;
    BRepTools::Read (aSh, argv[1], aBrepBuilder);
    if (aSh.IsNull ())
    {
      di << "No shape with name " << argv[1] << " found\n";
      return 1;
    }
  }

  if (GetMapOfAIS ().IsBound2 (aHlrName))
  {
    di << "Presentable object with name " << argv[2] << " already exists\n";
    return 1;
  }

  // close local context
  if (aContextAIS->HasOpenedContext ())
    aContextAIS->CloseLocalContext ();

  Handle(HLRBRep_PolyAlgo) aPolyAlgo = new HLRBRep_PolyAlgo();
  HLRBRep_PolyHLRToShape aHLRToShape;

  gp_Pnt anEye;
  gp_Dir aDir;
  gp_Ax2 aProjAx;
  if (argc == 9)
  {
    gp_Dir anUp;

    anEye.SetCoord (atof (argv[3]), atof (argv[4]), atof (argv[5]));
    aDir.SetCoord (atof (argv[6]), atof (argv[7]), atof (argv[8]));
    anUp.SetCoord (atof (argv[9]), atof (argv[10]), atof (argv[11]));
    aProjAx.SetLocation (anEye);
    aProjAx.SetDirection (aDir);
    aProjAx.SetYDirection (anUp);
  }
  else
  {
    gp_Dir aRight;

    Handle(V3d_Viewer) aViewer = ViewerTest::GetViewerFromContext();
    Handle(V3d_View)   aView   = ViewerTest::CurrentView();
    Standard_Integer aWidth, aHeight;
    Standard_Real aCentX, aCentY, aCentZ, aDirX, aDirY, aDirZ;
    Standard_Real aRightX, aRightY, aRightZ;
    aView->Window()->Size (aWidth, aHeight);

    aView->ConvertWithProj (aWidth, aHeight/2, 
                            aRightX, aRightY, aRightZ,
                            aDirX, aDirY, aDirZ);

    aView->ConvertWithProj (aWidth/2, aHeight/2, 
                            aCentX, aCentY, aCentZ,
                            aDirX, aDirY, aDirZ);

    anEye.SetCoord (-aCentX, -aCentY, -aCentZ);
    aDir.SetCoord (-aDirX, -aDirY, -aDirZ);
    aRight.SetCoord (aRightX - aCentX, aRightY - aCentY, aRightZ - aCentZ);
    aProjAx.SetLocation (anEye);
    aProjAx.SetDirection (aDir);
    aProjAx.SetXDirection (aRight);
  }

  HLRAlgo_Projector aProjector (aProjAx);
  aPolyAlgo->Projector (aProjector);
  aPolyAlgo->Load (aSh);
  aPolyAlgo->Update ();

  aHLRToShape.Update (aPolyAlgo);

  // make hlr shape from input shape
  TopoDS_Compound aHlrShape;
  BRep_Builder aBuilder;
  aBuilder.MakeCompound (aHlrShape);

  TopoDS_Shape aCompound = aHLRToShape.VCompound();
  if (!aCompound.IsNull ())
  {
    aBuilder.Add (aHlrShape, aCompound);
  }
  
  // extract visible outlines
  aCompound = aHLRToShape.OutLineVCompound();
  if (!aCompound.IsNull ())
  {
    aBuilder.Add (aHlrShape, aCompound);
  }

  // create an AIS shape and display it
  Handle(AIS_Shape) anObject = new AIS_Shape (aHlrShape);
  GetMapOfAIS().Bind (anObject, aHlrName);
  aContextAIS->Display (anObject);

  aContextAIS->UpdateCurrentViewer ();

  return 0;
}

// This class is a wrap for Graphic3d_ArrayOfPrimitives; it is used for
// manipulating and displaying such an array with AIS context
DEFINE_STANDARD_HANDLE(MyPArrayObject, AIS_InteractiveObject)
class MyPArrayObject : public AIS_InteractiveObject
{

public:

  MyPArrayObject (const Handle(Graphic3d_ArrayOfPrimitives) theArray)
  {
    myArray = theArray;
  }

  DEFINE_STANDARD_RTTI(MyPArrayObject)

private:

  void Compute (const Handle(PrsMgr_PresentationManager3d)& aPresentationManager,
                const Handle(Prs3d_Presentation)& aPresentation,
                const Standard_Integer aMode);

  void ComputeSelection (const Handle(SelectMgr_Selection)& aSelection,
                         const Standard_Integer aMode) {};

protected:

  Handle(Graphic3d_ArrayOfPrimitives) myArray;

};

IMPLEMENT_STANDARD_HANDLE(MyPArrayObject, AIS_InteractiveObject)
IMPLEMENT_STANDARD_RTTIEXT(MyPArrayObject, AIS_InteractiveObject)

void MyPArrayObject::Compute (const Handle(PrsMgr_PresentationManager3d)& aPresentationManager,
                              const Handle(Prs3d_Presentation)& aPresentation,
                              const Standard_Integer aMode)
{
  aPresentation->Clear();

  Handle (Graphic3d_Group) aGroup = Prs3d_Root::CurrentGroup (aPresentation);
  aGroup->BeginPrimitives ();
  aGroup->AddPrimitiveArray (myArray);
  aGroup->EndPrimitives ();
}

static bool CheckInputCommand (const TCollection_AsciiString theCommand,
                               const char **theArgStr, int &theArgIndex,
                               int theArgCount, int theMaxArgs)
{
  // check if there is more elements than expected
  if (theArgIndex >= theMaxArgs)
    return false;

  TCollection_AsciiString aStrCommand(theArgStr[theArgIndex]);
  aStrCommand.LowerCase();
  if (aStrCommand.Search(theCommand) != 1 ||
      theArgIndex + (theArgCount - 1) >= theMaxArgs)
    return false;

  // go to the first data element
  theArgIndex++;

  // check data if it can be converted to numeric
  for (int aElement = 0; aElement < theArgCount; aElement++, theArgIndex++)
  {
    aStrCommand = theArgStr[theArgIndex];
    if (!aStrCommand.IsRealValue())
      return false;
  }

  return true;
}

//=============================================================================
//function : VDrawPArray
//purpose  : Draws primitives array from list of vertexes, bounds, edges
//=============================================================================

static int VDrawPArray (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  Handle(AIS_InteractiveContext) aContextAIS = ViewerTest::GetAISContext();
  if (aContextAIS.IsNull())
  {
    di << "Call vinit before!\n";
    return 1;
  }
  else if (argc < 3)
  {
    di << "Use: " << argv[0] << " Name TypeOfArray"
       << " [vertex] ... [bounds] ... [edges]\n"
       << "  TypeOfArray={ points | segments | polylines | triangles |\n"
       << "                trianglefans | trianglestrips | quads |\n"
       << "                quadstrips | polygons }\n"
       << "  vertex={ 'v' x y z [normal={ 'n' nx ny nz }] [color={ 'c' r g b }]"
       << " [texel={ 't' tx ty }] } \n"
       << "  bounds={ 'b' verticies_count [color={ 'c' r g b }] }\n"
       << "  edges={ 'e' vertex_id [hidden_edge={'h'}] }\n";
    return 1;
  }

  // read the arguments
  Standard_Integer aArgIndex = 1;
  TCollection_AsciiString aName (argv[aArgIndex++]);
  TCollection_AsciiString anArrayType (argv[aArgIndex++]);
  const Standard_Integer anArgsFrom = aArgIndex;

  // parse number of verticies, bounds, edges
  Standard_Integer aVertexNum = 0, aBoundNum = 0, aEdgeNum = 0;
  Standard_Boolean hasVColors, hasBColors, hasNormals, hasInfos, hasTexels;
  hasVColors = hasNormals = hasBColors = hasInfos = hasTexels = Standard_False;

  TCollection_AsciiString aCommand;
  while (aArgIndex < argc)
  {
    aCommand = argv[aArgIndex];
    aCommand.LowerCase();
    if (!aCommand.IsAscii())
    {
      di << "Unexpected argument: #" << aArgIndex - 1 << " , "
         << "should be an array element: 'v', 'b', 'e' \n";
      break;
    }

    // vertex command
    if (CheckInputCommand ("v", argv, aArgIndex, 3, argc))
    {
      // vertex has a normal or normal with color or texel
      if (CheckInputCommand ("n", argv, aArgIndex, 3, argc))
        hasNormals = Standard_True;

      // vertex has a color
      if (CheckInputCommand ("c", argv, aArgIndex, 3, argc))
        hasVColors = Standard_True;

      // vertex has a texel
      if (CheckInputCommand ("t", argv, aArgIndex, 2, argc))
        hasTexels = Standard_True;

      aVertexNum++;
    }
    // bound command
    else if (CheckInputCommand ("b", argv, aArgIndex, 1, argc))
    {
      // bound has color
      if (CheckInputCommand ("c", argv, aArgIndex, 3, argc))
        hasBColors = Standard_True;

      aBoundNum++;
    }
    // edge command
    else if (CheckInputCommand ("e", argv, aArgIndex, 1, argc))
    {
      // edge has a hide flag
      if (CheckInputCommand ("h", argv, aArgIndex, 0, argc))
        hasInfos = Standard_True;

      aEdgeNum++;
    }
    // unknown command
    else
      aArgIndex++;
  }

  if (aVertexNum == 0)
  {
    di << "You should pass any verticies in the list of array elements\n";
    return 1;
  }

  // create an array of primitives by types
  Handle(Graphic3d_ArrayOfPrimitives) anArray;
  if (anArrayType == "points")
    anArray = new Graphic3d_ArrayOfPoints (aVertexNum);
  else if (anArrayType == "segments")
    anArray = new Graphic3d_ArrayOfSegments (aVertexNum, aEdgeNum, hasVColors);
  else if (anArrayType == "polylines")
    anArray = new Graphic3d_ArrayOfPolylines (aVertexNum, aBoundNum, aEdgeNum,
                                              hasVColors, hasBColors, hasInfos);
  else if (anArrayType == "triangles")
    anArray = new Graphic3d_ArrayOfTriangles (aVertexNum, aEdgeNum, hasNormals,
                                              hasVColors, hasTexels, hasInfos);
  else if (anArrayType == "trianglefans")
    anArray = new Graphic3d_ArrayOfTriangleFans (aVertexNum, aBoundNum,
                                                 hasNormals, hasVColors,
                                                 hasBColors, hasTexels);
  else if (anArrayType == "trianglestrips")
    anArray = new Graphic3d_ArrayOfTriangleStrips (aVertexNum, aBoundNum,
                                                   hasNormals, hasVColors,
                                                   hasBColors, hasTexels);
  else if (anArrayType == "quads")
    anArray = new Graphic3d_ArrayOfQuadrangles (aVertexNum, aEdgeNum,
                                                hasNormals, hasVColors,
                                                hasTexels, hasInfos);
  else if (anArrayType == "quadstrips")
    anArray = new Graphic3d_ArrayOfQuadrangleStrips (aVertexNum, aBoundNum,
                                                     hasNormals, hasVColors,
                                                     hasBColors, hasTexels);
  else if (anArrayType == "polygons")
    anArray = new Graphic3d_ArrayOfPolygons (aVertexNum, aBoundNum, aEdgeNum,
                                             hasNormals, hasVColors, hasBColors,
                                             hasTexels, hasInfos);
  else
  {
    di << "Unexpected type of primitiives array\n";
    return 1;
  }

  // parse an array of primitives
  aArgIndex = anArgsFrom;
  while (aArgIndex < argc)
  {
    aCommand = argv[aArgIndex];
    aCommand.LowerCase();
    if (!aCommand.IsAscii())
      break;

    // vertex command
    if (CheckInputCommand ("v", argv, aArgIndex, 3, argc))
    {
      anArray->AddVertex (atof (argv[aArgIndex - 3]),
                          atof (argv[aArgIndex - 2]),
                          atof (argv[aArgIndex - 1]));

      // vertex has a normal or normal with color or texel
      if (CheckInputCommand ("n", argv, aArgIndex, 3, argc))
        anArray->SetVertexNormal (anArray->VertexNumber (),
                                  atof (argv[aArgIndex - 3]),
                                  atof (argv[aArgIndex - 2]),
                                  atof (argv[aArgIndex - 1]));
      
      if (CheckInputCommand ("c", argv, aArgIndex, 3, argc))
        anArray->SetVertexColor (anArray->VertexNumber (),
                                 atof (argv[aArgIndex - 3]),
                                 atof (argv[aArgIndex - 2]),
                                 atof (argv[aArgIndex - 1]));
      
      if (CheckInputCommand ("t", argv, aArgIndex, 2, argc))
        anArray->SetVertexTexel (anArray->VertexNumber (),
                                 atof (argv[aArgIndex - 2]),
                                 atof (argv[aArgIndex - 1]));
    }
    // bounds command
    else if (CheckInputCommand ("b", argv, aArgIndex, 1, argc))
    {
      Standard_Integer aVertCount = atoi (argv[aArgIndex - 1]);

      if (CheckInputCommand ("c", argv, aArgIndex, 3, argc))
        anArray->AddBound (aVertCount,
                           atof (argv[aArgIndex - 3]),
                           atof (argv[aArgIndex - 2]),
                           atof (argv[aArgIndex - 1]));

      else
        anArray->AddBound (aVertCount);
    }
    // edge command
    else if (CheckInputCommand ("e", argv, aArgIndex, 1, argc))
    {
      Standard_Integer aVertIndex = atoi (argv[aArgIndex - 1]);

      // edge has/hasn't hide flag
      if (CheckInputCommand ("h", argv, aArgIndex, 0, argc))
        anArray->AddEdge (aVertIndex, Standard_False);
      else
        anArray->AddEdge (aVertIndex, Standard_True);
    }
    // unknown command
    else
      aArgIndex++;
  }

  // create primitives array object
  Handle (MyPArrayObject) aPObject = new MyPArrayObject (anArray);

  // register the object in map
  VDisplayAISObject (aName, aPObject);

  return 0;
}

//=======================================================================
//function : VSetLocation
//purpose  : Change location of AIS interactive object
//=======================================================================

static Standard_Integer VSetLocation (Draw_Interpretor& di,
                                      Standard_Integer argc,
                                      const char ** argv)
{
  Handle(AIS_InteractiveContext) aContext = ViewerTest::GetAISContext();
  if (aContext.IsNull())
  {
    di << argv[0] << "ERROR : use 'vinit' command before " << "\n";
    return 1;
  }

  if (argc != 5)
  {
    di << "ERROR : Usage : " << argv[0] << " name x y z; new location" << "\n";
    return 1;
  }

  TCollection_AsciiString aName (argv[1]);
  Standard_Real aX = atof (argv[2]);
  Standard_Real aY = atof (argv[3]);
  Standard_Real aZ = atof (argv[4]);

  // find object
  ViewerTest_DoubleMapOfInteractiveAndName& aMap = GetMapOfAIS();
  Handle(AIS_InteractiveObject) anIObj;
  if (!aMap.IsBound2 (aName))
  {
    di << "Use 'vdisplay' before" << "\n";
    return 1;
  }
  else
  {
    anIObj = Handle(AIS_InteractiveObject)::DownCast (aMap.Find2 (aName));

    // not an AIS_InteractiveObject
    if (anIObj.IsNull())
    {
      di << argv[1] << " : Not an AIS interactive object" << "\n";
      return 1;
    }

    gp_Trsf aTrsf;
    aTrsf.SetTranslation (gp_Vec (aX, aY, aZ));
    TopLoc_Location aLocation (aTrsf);
    aContext->SetLocation (anIObj, aLocation);
    aContext->UpdateCurrentViewer();
  }

  return 0;
}

//===============================================================================================
//function : VConnect
//purpose  : Creates and displays AIS_ConnectedInteractive object from input object and location 
//Draw arg : vconnect name object Xo Yo Zo Xu Xv Xw Zu Zv Zw
//===============================================================================================

static Standard_Integer VConnect(Draw_Interpretor& di, 
                                 Standard_Integer argc, 
                                 const char ** argv) 
{
  // Check argumnets 
  if(argc != 12)
  {
    std::cout << "vconnect error: expect 11 argumnets\n"; 
    return 1; // TCL_ERROR
  }
  // Get values 
  TCollection_AsciiString aName(argv[1]); 
  TCollection_AsciiString anOriginObjectName(argv[2]); 
  if(aName.IsEqual(anOriginObjectName))
  {
    std::cout << "vconnect error: equal names for connected objects\n"; 
    return 1; // TCL_ERROR
  }
  // Check if the origin shape is not null
  Handle(AIS_InteractiveObject) anOriginObject;
  if(GetMapOfAIS().IsBound2(anOriginObjectName))
  {
    Handle(Standard_Transient) anObj = GetMapOfAIS().Find2(anOriginObjectName);
    anOriginObject = Handle(AIS_InteractiveObject)::DownCast(anObj);
    if(anOriginObject.IsNull())
    {
      std::cout << "Object " << anOriginObjectName << " is used for non AIS viewer\n!";
      return 1; // TCL_ERROR
    }
  }
  
  // Get location data
  Standard_Real aXo = atof(argv[3]);
  Standard_Real aYo = atof(argv[4]);
  Standard_Real aZo = atof(argv[5]);
  Standard_Real aXu = atof(argv[6]);
  Standard_Real aXv = atof(argv[7]);
  Standard_Real aXw = atof(argv[8]);
  Standard_Real aZu = atof(argv[9]);
  Standard_Real aZv = atof(argv[10]);
  Standard_Real aZw = atof(argv[11]);

  // Create transformation
  gp_Pnt aPoint(aXo, aYo, aZo);
  gp_Dir anXDir(aXu, aXv, aXw), aZDir(aZu, aZv, aZw);
  if(!anXDir.IsNormal(aZDir, Precision::Angular()))
  {
    std::cout << "vconnect error : XDir expects to be normal to ZDir\n"; 
    return 1; // TCL_ERROR
  } 
  gp_Ax3 anAx3(aPoint, aZDir, anXDir); 
  gp_Trsf aTrsf; 
  aTrsf.SetTransformation(anAx3); 
  TopLoc_Location aLocation(aTrsf);

  // Create connected object
  Handle(AIS_ConnectedInteractive) aConnectedObject = new AIS_ConnectedInteractive();
  aConnectedObject->Connect(anOriginObject, aLocation);

  // Check if there is another object with given name
  // and remove it from context
  if(GetMapOfAIS().IsBound2(aName))
  {
    Handle(AIS_InteractiveObject) anObj = 
      Handle(AIS_InteractiveObject)::DownCast(GetMapOfAIS().Find2(aName));
    TheAISContext()->Remove(anObj, Standard_False);
    GetMapOfAIS().UnBind2(aName);
  }

  // Bind connected object to its name 
  GetMapOfAIS().Bind(aConnectedObject, aName); 

  // Display connected object
  TheAISContext()->Display(aConnectedObject);

  return 0;
}

//===============================================================================================
//function : VConnectShape
//purpose  : Creates and displays AIS_ConnectedShape from input shape and location 
//Draw arg : vconnectsh name shape Xo Yo Zo Xu Xv Xw Zu Zv Zw
//===============================================================================================

static Standard_Integer VConnectShape(Draw_Interpretor& di, 
                                      Standard_Integer argc, 
                                      const char ** argv) 
{
  // Check argumnets 
  if(argc != 12)
  {
    std::cout << "vconnectsh error: expect 11 argumnets\n"; 
    return 1; // TCL_ERROR
  }
  // Get values 
  TCollection_AsciiString aName(argv[1]); 
  TCollection_AsciiString anOriginShapeName(argv[2]); 
  if(aName.IsEqual(anOriginShapeName))
  {
    std::cout << "vconnectsh error: equal names for connected shapes\n"; 
    return 1; // TCL_ERROR
  }
  // Check if the origin shape is not null
  Handle(AIS_InteractiveObject) anOriginShape;
  if(GetMapOfAIS().IsBound2(anOriginShapeName))
  {
    Handle(Standard_Transient) anObj = GetMapOfAIS().Find2(anOriginShapeName);
    anOriginShape = Handle(AIS_InteractiveObject)::DownCast(anObj);
    if(anOriginShape.IsNull())
    {
      std::cout << "Shape " << anOriginShapeName << " is used for non AIS viewer\n!";
      return 1; // TCL_ERROR
    }
  }

  // Get location data  
  Standard_Real aXo = atof(argv[3]);
  Standard_Real aYo = atof(argv[4]);
  Standard_Real aZo = atof(argv[5]);
  Standard_Real aXu = atof(argv[6]);
  Standard_Real aXv = atof(argv[7]);
  Standard_Real aXw = atof(argv[8]);
  Standard_Real aZu = atof(argv[9]);
  Standard_Real aZv = atof(argv[10]);
  Standard_Real aZw = atof(argv[11]);

  // Create transformation
  gp_Pnt aPoint(aXo, aYo, aZo);
  gp_Dir anXDir(aXu, aXv, aXw), aZDir(aZu, aZv, aZw);
  if(!anXDir.IsNormal(aZDir, Precision::Angular()))
  {
    std::cout << "vconnectsh error : XDir expects to be normal to ZDir\n"; 
    return 1; // TCL_ERROR
  } 
  gp_Ax3 anAx3(aPoint, aZDir, anXDir); 
  gp_Trsf aTrsf; 
  aTrsf.SetTransformation(anAx3); 
  TopLoc_Location aLocation(aTrsf);

  // Create connected shape
  Handle(AIS_Shape) aShape = Handle(AIS_Shape)::DownCast(anOriginShape);
  Handle(AIS_ConnectedShape) aConnectedShape = new AIS_ConnectedShape(aShape);
  aConnectedShape->Connect(anOriginShape, aLocation);

  // Check if there is another object with given name
  // and remove it from context
  if(GetMapOfAIS().IsBound2(aName))
  {
    Handle(AIS_InteractiveObject) anObj = 
      Handle(AIS_InteractiveObject)::DownCast(GetMapOfAIS().Find2(aName));
    TheAISContext()->Remove(anObj, Standard_False);
    GetMapOfAIS().UnBind2(aName);
  }

  // Bind connected shape to its name 
  GetMapOfAIS().Bind(aConnectedShape, aName); 

  // Display connected shape
  TheAISContext()->Display(aConnectedShape);

  return 0;
}

//===============================================================================================
//function : VSetSelectionMode
//purpose  : Sets input selection mode for input object or for all displayed objects 
//Draw arg : vselmode [object] mode On/Off (1/0)
//===============================================================================================

// function : InList 
// purpose  : checks if theMode is already turned on for theObj
Standard_Boolean InList(Handle(AIS_InteractiveContext) theAISContext, 
                          Handle(AIS_InteractiveObject) theObj, 
                          Standard_Integer theMode)
{
  TColStd_ListOfInteger anArray; 
  theAISContext->ActivatedModes(theObj, anArray);
  TColStd_ListIteratorOfListOfInteger anIt(anArray);
  for(; anIt.More(); anIt.Next())
  {
    if(anIt.Value() == theMode) 
      return Standard_True;
  }
  return Standard_False;
}

static Standard_Integer VSetSelectionMode(Draw_Interpretor& di, 
                                          Standard_Integer argc, 
                                          const char ** argv)
{
  // Check errors
  Handle(AIS_InteractiveContext) anAISContext = ViewerTest::GetAISContext();
  if(anAISContext.IsNull())
  {
    std::cout << "Call vinit before!\n";
    return 1; // TCL_ERROR
  }

  // Check the arguments 
  if(argc != 3 && argc != 4)
  {
    std::cout << "vselmode error : expects at least 2 arguments\n"; 
    return 1; // TCL_ERROR
  }

  Handle(AIS_InteractiveObject) anObj;

  // Set new selection mode for all objects in context
  if(argc == 3)
  {
    // Get arguments 
    Standard_Integer aMode = atoi(argv[1]);
    Standard_Boolean isTurnOn = atoi(argv[2]); 

    // Get all displayed objects
    AIS_ListOfInteractive anObjList;
    anAISContext->DisplayedObjects(anObjList);
    AIS_ListIteratorOfListOfInteractive anObjIter;

    if(aMode == 0)
    {
      if(anAISContext->HasOpenedContext())
        anAISContext->CloseLocalContext();
    }

    // Turn on aMode
    if(aMode != 0 && isTurnOn)
    {
      if(!anAISContext->HasOpenedContext())
      {
        anAISContext->OpenLocalContext(); 
        for(anObjIter.Initialize(anObjList); anObjIter.More(); anObjIter.Next())
        {
          anAISContext->Activate(anObjIter.Value(), aMode); 
        }
      }
      else
      {
        for(anObjIter.Initialize(anObjList); anObjIter.More(); anObjIter.Next())
        {
          anObj = anObjIter.Value();
          if(!InList(anAISContext, anObj, aMode))
            anAISContext->Activate(anObj, aMode);
        }
      }
    }

    // Turn off aMode
    if(aMode != 0 && !isTurnOn)
    {
      if(anAISContext->HasOpenedContext())
      {
        for(anObjIter.Initialize(anObjList); anObjIter.More(); anObjIter.Next())
        {
          anObj = anObjIter.Value();
          if(InList(anAISContext, anObj, aMode))
            anAISContext->Deactivate(anObj, aMode);
        }
      }
    }
  }

  // Set new selection mode for named object 
  else
  {
    // Get argumnets 
    Standard_Integer aMode = atoi(argv[2]);
    Standard_Boolean isTurnOn = atoi(argv[3]);
    TCollection_AsciiString aName(argv[1]); 

    // Check if there is an object with given name in context
    if(GetMapOfAIS().IsBound2(aName))
    {
      anObj = Handle(AIS_InteractiveObject)::
        DownCast(GetMapOfAIS().Find2(aName));
      if(anObj.IsNull())
      {
        std::cout << "vselmode error : object name is used for non AIS viewer\n"; 
        return 1; // TCL_ERROR
      }
    }

    if(aMode == 0)
    {
      if(anAISContext->HasOpenedContext())
        anAISContext->CloseLocalContext();
    }
    // Turn on aMode
    if(aMode != 0 && isTurnOn) 
    {
      if(!anAISContext->HasOpenedContext())
      {
        anAISContext->OpenLocalContext(); 
        anAISContext->Activate(anObj, aMode);
      }
      else
      {
        if(!InList(anAISContext, anObj, aMode))
          anAISContext->Activate(anObj, aMode);
      }
    }

    // Turn off aMode
    if(aMode != 0 && !isTurnOn)
    {
      if(anAISContext->HasOpenedContext())
      {
        if(InList(anAISContext, anObj, aMode))
          anAISContext->Deactivate(anObj, aMode);
      }
    }
  }
  return 0;
}

//==========================================================================
//class   : Triangle 
//purpose : creates Triangle based on AIS_InteractiveObject. 
//          This class was implemented for testing Select3D_SensitiveTriangle
//===========================================================================
DEFINE_STANDARD_HANDLE(Triangle, AIS_InteractiveObject)
class Triangle: public AIS_InteractiveObject 
{
public: 
  // CASCADE RTTI
  DEFINE_STANDARD_RTTI(FilledCircle) 
  Triangle (const gp_Pnt& theP1, 
            const gp_Pnt& theP2, 
            const gp_Pnt& theP3);
protected:
  void Compute (  const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
                  const Handle(Prs3d_Presentation)& thePresentation,
                  const Standard_Integer theMode);

  void ComputeSelection (  const Handle(SelectMgr_Selection)& theSelection, 
                           const Standard_Integer theMode);
private: 
  gp_Pnt myPoint1;
  gp_Pnt myPoint2;
  gp_Pnt myPoint3;
};
IMPLEMENT_STANDARD_HANDLE(Triangle, AIS_InteractiveObject)
IMPLEMENT_STANDARD_RTTIEXT(Triangle, AIS_InteractiveObject)

Triangle::Triangle (const gp_Pnt& theP1,
                    const gp_Pnt& theP2,
                    const gp_Pnt& theP3)
{
  myPoint1 = theP1;
  myPoint2 = theP2;
  myPoint3 = theP3;
}

void Triangle::Compute(const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
                       const Handle(Prs3d_Presentation)& thePresentation,
                       const Standard_Integer theMode)
{
  thePresentation->Clear();

  BRepBuilderAPI_MakeEdge anEdgeMaker1(myPoint1, myPoint2),
                          anEdgeMaker2(myPoint2, myPoint3),
                          anEdgeMaker3(myPoint3, myPoint1);

  TopoDS_Edge anEdge1 = anEdgeMaker1.Edge(),
              anEdge2 = anEdgeMaker2.Edge(),
              anEdge3 = anEdgeMaker3.Edge();
  if(anEdge1.IsNull() || anEdge2.IsNull() || anEdge3.IsNull())
    return;

  BRepBuilderAPI_MakeWire aWireMaker(anEdge1, anEdge2, anEdge3);
  TopoDS_Wire aWire = aWireMaker.Wire();
  if(aWire.IsNull()) return;

  BRepBuilderAPI_MakeFace aFaceMaker(aWire);
  TopoDS_Face aFace = aFaceMaker.Face();
  if(aFace.IsNull()) return;

  StdPrs_ShadedShape::Add(thePresentation, aFace, myDrawer);
}

void Triangle::ComputeSelection(const Handle(SelectMgr_Selection)& theSelection, 
                                const Standard_Integer theMode)
{
  Handle(SelectMgr_EntityOwner) anEntityOwner = new SelectMgr_EntityOwner(this);
  Handle(Select3D_SensitiveTriangle) aSensTriangle = 
    new Select3D_SensitiveTriangle(anEntityOwner, myPoint1, myPoint2, myPoint3);
  theSelection->Add(aSensTriangle);
}

//===========================================================================
//function : VTriangle 
//Draw arg : vtriangle Name PointName PointName PointName
//purpose  : creates and displays Triangle
//===========================================================================

//function: IsPoint
//purpose : checks if the object with theName is AIS_Point, 
//          if yes initialize thePoint from MapOfAIS
Standard_Boolean IsPoint (const TCollection_AsciiString& theName,
                          Handle(AIS_Point)& thePoint)
{
  Handle(AIS_InteractiveObject) anObject = 
    Handle(AIS_InteractiveObject)::DownCast(GetMapOfAIS().Find2(theName));
  if(anObject.IsNull() || 
     anObject->Type() != AIS_KOI_Datum || 
     anObject->Signature() != 1)
  {
    return Standard_False;
  }
  thePoint = Handle(AIS_Point)::DownCast(anObject);
  if(thePoint.IsNull())
    return Standard_False;
  return Standard_True;
}

//function: IsMatch
//purpose: checks if thePoint1 is equal to thePoint2
Standard_Boolean IsMatch (const Handle(Geom_CartesianPoint)& thePoint1,
                          const Handle(Geom_CartesianPoint)& thePoint2)
{
  if(abs(thePoint1->X()-thePoint2->X()) <= Precision::Confusion() &&
     abs(thePoint1->Y()-thePoint2->Y()) <= Precision::Confusion() &&
     abs(thePoint1->Z()-thePoint2->Z()) <= Precision::Confusion())
  {
    return Standard_True;
  }
  return Standard_False;
}

static Standard_Integer VTriangle (Draw_Interpretor& di,
                                   Standard_Integer argc,
                                   const char ** argv)
{
  // Check arguments
  if (argc != 5)
  {
    std::cout<<"vtriangle error: expects 4 argumnets\n";
    return 1; // TCL_ERROR
  }

  TheAISContext()->CloseAllContexts();

  // Get and check values
  TCollection_AsciiString aName(argv[1]);

  Handle(AIS_Point) aPoint1, aPoint2, aPoint3;
  if (!IsPoint(argv[2], aPoint1))
  {
    std::cout<<"vtriangle error: the 2nd argument must be a point\n";
    return 1; // TCL_ERROR
  }
  if (!IsPoint(argv[3], aPoint2))
  {
    std::cout<<"vtriangle error: the 3d argument must be a point\n";
    return 1; // TCL_ERROR
  }
  if (!IsPoint(argv[4], aPoint3))
  {
    std::cout<<"vtriangle error: the 4th argument must be a point\n";
    return 1; // TCL_ERROR
  }

  // Check that points are different
  Handle(Geom_CartesianPoint) aCartPoint1 = 
    Handle(Geom_CartesianPoint)::DownCast(aPoint1->Component());
  Handle(Geom_CartesianPoint) aCartPoint2 = 
    Handle(Geom_CartesianPoint)::DownCast(aPoint2->Component());
  // Test aPoint1 = aPoint2
  if (IsMatch(aCartPoint1, aCartPoint2))
  {
    std::cout<<"vtriangle error: the 1st and the 2nd points are equal\n";
    return 1; // TCL_ERROR
  }
  // Test aPoint2 = aPoint3
  Handle(Geom_CartesianPoint) aCartPoint3 = 
    Handle(Geom_CartesianPoint)::DownCast(aPoint3->Component());
  if (IsMatch(aCartPoint2, aCartPoint3))
  {
    std::cout<<"vtriangle error: the 2nd and the 3d points are equal\n";
    return 1; // TCL_ERROR
  }
  // Test aPoint3 = aPoint1
  if (IsMatch(aCartPoint1, aCartPoint3))
  {
    std::cout<<"vtriangle error: the 1st and the 3d points are equal\n";
    return 1; // TCL_ERROR
  }

  // Create triangle
  Handle(Triangle) aTriangle = new Triangle(aCartPoint1->Pnt(),
                                            aCartPoint2->Pnt(),
                                            aCartPoint3->Pnt());

  // Check if there is an object with given name
  // and remove it from context
  if (GetMapOfAIS().IsBound2(aName))
  {
    Handle(Standard_Transient) anObj = GetMapOfAIS().Find2(aName);
    Handle(AIS_InteractiveObject) anInterObj = 
         Handle(AIS_InteractiveObject)::DownCast(anObj);
    TheAISContext()->Remove(anInterObj, Standard_False);
    GetMapOfAIS().UnBind2(aName);
  }

  // Bind triangle to its name
  GetMapOfAIS().Bind(aTriangle, aName);

  // Display triangle
  TheAISContext()->Display(aTriangle);
  return 0;
}

//class  : SegmentObject
//purpose: creates segment based on AIS_InteractiveObject.
//         This class was implemented for testing Select3D_SensitiveCurve
DEFINE_STANDARD_HANDLE(SegmentObject, AIS_InteractiveObject)
class SegmentObject: public AIS_InteractiveObject
{
public:
  // CASCADE RTTI
  DEFINE_STANDARD_RTTI(SegmentObject) 
  SegmentObject (const gp_Pnt& thePnt1, const gp_Pnt& thePnt2);
protected:
  void Compute (const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
                const Handle(Prs3d_Presentation)& thePresentation,
                const Standard_Integer theMode);

  void ComputeSelection (const Handle(SelectMgr_Selection)& theSelection, 
                         const Standard_Integer theMode);
private:
  gp_Pnt myPoint1;
  gp_Pnt myPoint2;
};
IMPLEMENT_STANDARD_HANDLE(SegmentObject, AIS_InteractiveObject)
IMPLEMENT_STANDARD_RTTIEXT(SegmentObject, AIS_InteractiveObject)

SegmentObject::SegmentObject (const gp_Pnt& thePnt1, const gp_Pnt& thePnt2)
{
  myPoint1 = thePnt1;
  myPoint2 = thePnt2;
}

void SegmentObject::Compute (const Handle_PrsMgr_PresentationManager3d &thePresentationManager,
                             const Handle_Prs3d_Presentation &thePresentation,
                             const Standard_Integer theMode)
{
  thePresentation->Clear();
  BRepBuilderAPI_MakeEdge anEdgeMaker(myPoint1, myPoint2);
  TopoDS_Edge anEdge = anEdgeMaker.Edge();
  if (anEdge.IsNull())
    return;
  BRepAdaptor_Curve aCurveAdaptor(anEdge);
  StdPrs_Curve::Add(thePresentation, aCurveAdaptor, myDrawer);
}

void SegmentObject::ComputeSelection (const Handle_SelectMgr_Selection &theSelection,
                                      const Standard_Integer theMode)
{
  Handle(SelectMgr_EntityOwner) anOwner = new SelectMgr_EntityOwner(this);
  Handle(TColgp_HArray1OfPnt) anArray = new TColgp_HArray1OfPnt(1, 2);
  anArray->SetValue(1, myPoint1);
  anArray->SetValue(2, myPoint2);
  Handle(Select3D_SensitiveCurve) aSensCurve = 
    new Select3D_SensitiveCurve(anOwner, anArray);
  theSelection->Add(aSensCurve);
}

//=======================================================================
//function  : VSegment
//Draw args : vsegment Name PointName PointName
//purpose   : creates and displays Segment
//=======================================================================
static Standard_Integer VSegment (Draw_Interpretor& di,
                                  Standard_Integer argc,
                                  const char ** argv)
{
  // Check arguments
  if(argc!=4)
  {
    std::cout<<"vsegment error: expects 3 arguments\n";
    return 1; // TCL_ERROR
  }

  TheAISContext()->CloseAllContexts();

  // Get and check arguments
  TCollection_AsciiString aName(argv[1]);
  Handle(AIS_Point) aPoint1, aPoint2;
  if (!IsPoint(argv[2], aPoint1))
  {
    std::cout<<"vsegment error: the 2nd argument should be a point\n";
    return 1; // TCL_ERROR
  }
  if (!IsPoint(argv[3], aPoint2))
  {
    std::cout<<"vsegment error: the 3d argument should be a point\n";
    return 1; // TCL_ERROR
  }
  //Check that points are different
  Handle(Geom_CartesianPoint) aCartPoint1 = 
    Handle(Geom_CartesianPoint)::DownCast(aPoint1->Component());
  Handle(Geom_CartesianPoint) aCartPoint2 = 
    Handle(Geom_CartesianPoint)::DownCast(aPoint2->Component());
  if(IsMatch(aCartPoint1, aCartPoint2))
  {
    std::cout<<"vsegment error: equal points\n";
    return 1; // TCL_ERROR
  }
  
  // Create segment
  Handle(SegmentObject) aSegment = new SegmentObject(aCartPoint1->Pnt(), aCartPoint2->Pnt());
  // Check if there is an object with given name
  // and remove it from context
  if (GetMapOfAIS().IsBound2(aName))
  {
    Handle(Standard_Transient) anObj = GetMapOfAIS().Find2(aName);
    Handle(AIS_InteractiveObject) anInterObj = 
         Handle(AIS_InteractiveObject)::DownCast(anObj);
    TheAISContext()->Remove(anInterObj, Standard_False);
    GetMapOfAIS().UnBind2(aName);
  }

  // Bind segment to its name
  GetMapOfAIS().Bind(aSegment, aName);

  // Display segment
  TheAISContext()->Display(aSegment);
  return 0;
}

//=======================================================================
//function : VObjZLayer
//purpose  : Set or get z layer id for presentable object
//=======================================================================

static Standard_Integer VObjZLayer (Draw_Interpretor& di,
                                    Standard_Integer argc,
                                    const char ** argv)
{
  Handle(AIS_InteractiveContext) aContext = ViewerTest::GetAISContext();
  if (aContext.IsNull())
  {
    di << argv[0] << "Call 'vinit' before!\n";
    return 1;
  }

  // get operation
  TCollection_AsciiString aOperation;
  if (argc >= 2)
    aOperation = TCollection_AsciiString (argv [1]);

  // check for correct arguments
  if (!(argc == 4 && aOperation.IsEqual ("set")) &&
      !(argc == 3 && aOperation.IsEqual ("get")))
  {
    di << "Usage : " << argv[0] << " set/get object [layerid]\n";
    di << " set - set layer id for interactive object, layerid - z layer id\n";
    di << " get - get layer id of interactive object\n";
    di << " argument layerid should be passed for set operation only\n";
    return 1;
  }

  // find object
  TCollection_AsciiString aName (argv[2]);
  ViewerTest_DoubleMapOfInteractiveAndName& aMap = GetMapOfAIS();
  if (!aMap.IsBound2 (aName))
  {
    di << "Use 'vdisplay' before" << "\n";
    return 1;
  }

  // find interactive object
  Handle(Standard_Transient) anObj = GetMapOfAIS().Find2 (aName);
  Handle(AIS_InteractiveObject) anInterObj =
    Handle(AIS_InteractiveObject)::DownCast (anObj);
  if (anInterObj.IsNull())
  {
    di << "Not an AIS interactive object!\n";
    return 1;
  }

  // process operation
  if (aOperation.IsEqual ("set"))
  {
    Standard_Integer aLayerId = atoi (argv [3]);
    aContext->SetZLayer (anInterObj, aLayerId);
  }
  else if (aOperation.IsEqual ("get"))
  {
    di << "Z layer id: " << aContext->GetZLayer (anInterObj);
  }
  
  return 0;
}

//=======================================================================
//function : VPolygonOffset
//purpose  : Set or get polygon offset parameters
//=======================================================================
static Standard_Integer VPolygonOffset(Draw_Interpretor& di,
                                       Standard_Integer argc,
                                       const char ** argv)
{
  Handle(AIS_InteractiveContext) aContext = ViewerTest::GetAISContext();
  if (aContext.IsNull())
  {
    std::cout << argv[0] << " Call 'vinit' before!\n";
    return 1;
  }

  if (argc > 2 && argc != 5)
  {
    std::cout << "Usage : " << argv[0] << " [object [mode factor units]] - sets/gets polygon offset parameters for an object,"
      "without arguments prints the default values" << std::endl;
    return 1;
  }

  // find object
  Handle(AIS_InteractiveObject) anInterObj;
  if (argc >= 2)
  {
    TCollection_AsciiString aName (argv[1]);
    ViewerTest_DoubleMapOfInteractiveAndName& aMap = GetMapOfAIS();
    if (!aMap.IsBound2 (aName))
    {
      std::cout << "Use 'vdisplay' before" << std::endl;
      return 1;
    }

    // find interactive object
    Handle(Standard_Transient) anObj = GetMapOfAIS().Find2 (aName);
    anInterObj = Handle(AIS_InteractiveObject)::DownCast (anObj);
    if (anInterObj.IsNull())
    {
      std::cout << "Not an AIS interactive object!" << std::endl;
      return 1;
    }
  }

  Standard_Integer aMode;
  Standard_ShortReal    aFactor, aUnits;
  if (argc == 5)
  {
    aMode   = atoi(argv[2]);
    aFactor = (Standard_ShortReal) atof(argv[3]);
    aUnits  = (Standard_ShortReal) atof(argv[4]);

    anInterObj->SetPolygonOffsets(aMode, aFactor, aUnits);
    aContext->UpdateCurrentViewer();
    return 0;
  }
  else if (argc == 2)
  {
    if (anInterObj->HasPolygonOffsets())
    {
      anInterObj->PolygonOffsets(aMode, aFactor, aUnits);
      std::cout << "Current polygon offset parameters for " << argv[1] << ":" << std::endl;
      std::cout << "\tMode: "   << aMode   << std::endl;
      std::cout << "\tFactor: " << aFactor << std::endl;
      std::cout << "\tUnits: "  << aUnits  << std::endl;
      return 0;
    }
    else
    {
      std::cout << "Specific polygon offset parameters are not set for " << argv[1] << std::endl;
    }
  }

  std::cout << "Default polygon offset parameters:" << std::endl;
  aContext->DefaultDrawer()->ShadingAspect()->Aspect()->PolygonOffsets(aMode, aFactor, aUnits);
  std::cout << "\tMode: "   << aMode   << std::endl;
  std::cout << "\tFactor: " << aFactor << std::endl;
  std::cout << "\tUnits: "  << aUnits  << std::endl;

  return 0;
}

//=======================================================================
//function : VShowFaceBoundaries
//purpose  : Set face boundaries drawing on/off for ais object
//=======================================================================
static Standard_Integer VShowFaceBoundary (Draw_Interpretor& di,
                                           Standard_Integer argc,
                                           const char ** argv)
{
  Handle(AIS_InteractiveContext) aContext = ViewerTest::GetAISContext ();
  if (aContext.IsNull ())
  {
    std::cout << argv[0] << " Call 'vinit' before!\n";
    return 1;
  }

  if ((argc != 3 && argc < 6) || argc > 8)
  {
    std::cout << "Usage :\n " << argv[0]
              << " ObjectName isOn [R G B [LineWidth [LineStyle]]]\n"
              << "   ObjectName - name of AIS interactive object. \n"
              << "                if ObjectName = \"\", then set as default\n"
              << "                settings for all newly displayed objects\n"
              << "   isOn       - flag indicating whether the boundaries\n"
              << "                should be turned on or off (can be set\n"
              << "                to 0 (off) or 1 (on)).\n"
              << "   R, G, B    - red, green and blue components of boundary\n"
              << "                color in range (0 - 255).\n"
              << "                (default is (0, 0, 0)\n"
              << "   LineWidth  - line width\n"
              << "                (default is 1)\n"
              << "   LineStyle  - line fill style :\n"
              << "                 0 - solid  \n"
              << "                 1 - dashed \n"
              << "                 2 - dot    \n"
              << "                 3 - dashdot\n"
              << "                 (default is solid)";
    return 1;
  }

  TCollection_AsciiString aName (argv[1]);

  Quantity_Parameter aRed      = 0.0;
  Quantity_Parameter aGreen    = 0.0;
  Quantity_Parameter aBlue     = 0.0;
  Standard_Real      aWidth    = 1.0;
  Aspect_TypeOfLine  aLineType = Aspect_TOL_SOLID;
  
  // find object
  Handle(AIS_InteractiveObject) anInterObj;

  // if name is empty - apply attributes for default aspect
  if (!aName.IsEmpty ())
  {
    ViewerTest_DoubleMapOfInteractiveAndName& aMap = GetMapOfAIS ();
    if (!aMap.IsBound2 (aName))
    {
      std::cout << "Use 'vdisplay' on " << aName << " before" << std::endl;
      return 1;
    }

    // find interactive object
    Handle(Standard_Transient) anObj = GetMapOfAIS ().Find2 (aName);
    anInterObj = Handle(AIS_InteractiveObject)::DownCast (anObj);
    if (anInterObj.IsNull ())
    {
      std::cout << "Not an AIS interactive object!" << std::endl;
      return 1;
    }
  }
  
  const Handle(Prs3d_Drawer)& aDrawer = (aName.IsEmpty ()) ?
    TheAISContext ()->DefaultDrawer () : anInterObj->Attributes ();

  // turn boundaries on/off
  Standard_Boolean isBoundaryDraw = (atoi (argv[2]) == 1);
  aDrawer->SetFaceBoundaryDraw (isBoundaryDraw);
  
  // set boundary line color
  if (argc >= 6)
  {
    // Text color
    aRed   = atof (argv[3])/255.;
    aGreen = atof (argv[4])/255.;
    aBlue  = atof (argv[5])/255.;
  }

  // set line width
  if (argc >= 7)
  {
    aWidth = (Standard_Real)atof (argv[6]);
  }

  // select appropriate line type
  if (argc == 8)
  {
    switch (atoi (argv[7]))
    {
      case 1: aLineType = Aspect_TOL_DASH;    break;
      case 2: aLineType = Aspect_TOL_DOT;     break;
      case 3: aLineType = Aspect_TOL_DOTDASH; break;
      default:
        aLineType = Aspect_TOL_SOLID;
    }
  }

  Quantity_Color aColor (aRed, aGreen, aBlue, Quantity_TOC_RGB);

  Handle(Prs3d_LineAspect) aBoundaryAspect = 
    new Prs3d_LineAspect (aColor, aLineType, aWidth);

  aDrawer->SetFaceBoundaryAspect (aBoundaryAspect);

  TheAISContext()->Redisplay (anInterObj);
  
  return 0;
}

//=======================================================================
//function : ObjectsCommands
//purpose  :
//=======================================================================

void ViewerTest::ObjectCommands(Draw_Interpretor& theCommands)
{
  const char *group ="AISObjects";
  theCommands.Add("vtrihedron",
    "vtrihedron         : vtrihedron name [Xo] [Yo] [Zo] [Zu] [Zv] [Zw] [Xu] [Xv] [Xw] ",
    __FILE__,VTrihedron,group);

  theCommands.Add("vtri2d",
    "vtri2d Name Selection in the viewer only ",
    __FILE__,VTrihedron2D ,group);

  theCommands.Add("vplanetri",
    "vplanetri Name Selection in the viewer only ",
    __FILE__,VPlaneTrihedron ,group);

  theCommands.Add("vsize",
    "vsize       : vsize [name(Default=Current)] [size(Default=100)] ",
    __FILE__,VSize,group);

  theCommands.Add("vaxis",
    "vaxis nom [Xa] [Ya] [Za] [Xb] [Yb] [Zb]",
    __FILE__,VAxisBuilder,group);

  theCommands.Add("vaxispara",
    "vaxispara  nom ",
    __FILE__,VAxisBuilder,group);

  theCommands.Add("vaxisortho",
    "vaxisotho  nom ",
    __FILE__,VAxisBuilder,group);

  theCommands.Add("vpoint",
    "vpoint  PointName [Xa] [Ya] [Za] ",
    __FILE__,VPointBuilder,group);

  theCommands.Add("vplane",
    "vplane  PlaneName [AxisName/PlaneName/PointName] [PointName/PointName/PointName] [Nothing/Nothing/PointName] ",
    __FILE__,VPlaneBuilder,group);

  theCommands.Add("vplanepara",
    "vplanepara  PlaneName  ",
    __FILE__,VPlaneBuilder,group);

  theCommands.Add("vplaneortho",
    "vplaneortho  PlaneName  ",
    __FILE__,VPlaneBuilder,group);

  theCommands.Add("vline",
    "vline: vline LineName [Xa/PointName] [Ya/PointName] [Za] [Xb] [Yb] [Zb]  ",
    __FILE__,VLineBuilder,group);

  theCommands.Add("vcircle",
    "vcircle CircleName [PointName PointName PointName IsFilled]\n\t\t\t\t\t[PlaneName PointName Radius IsFilled]",
    __FILE__,VCircleBuilder,group);

  theCommands.Add("vdrawtext",
    "vdrawtext  : vdrawtext name X Y Z R G B hor_align ver_align angle zoomable height Aspect [Font [isMultiByte]]",
    __FILE__,VDrawText,group);

  theCommands.Add("vdrawsphere",
    "vdrawsphere: vdrawsphere shapeName Fineness [X=0.0 Y=0.0 Z=0.0] [Radius=100.0] [ToShowEdges=0]\n",
    __FILE__,VDrawSphere,group);

  theCommands.Add("vclipplane",
    "vclipplane : vclipplane [x y z dx dy dz] [planeId {on/off/del/display/hide}]",
    __FILE__,VClipPlane,group);

  theCommands.Add ("vsetlocation",
        "vsetlocation : name x y z; set new location for an interactive object",
        __FILE__, VSetLocation, group);

  theCommands.Add (
    "vcomputehlr",
    "vcomputehlr: shape hlrname [ eyex eyey eyez lookx looky lookz ]",
    __FILE__, VComputeHLR, group);

  theCommands.Add("vdrawparray",
    "vdrawparray : vdrawparray Name TypeOfArray [vertex = { 'v' x y z [vertex_normal = { 'n' x y z }] [vertex_color = { 'c' r g b }] ] ... [bound = { 'b' vertex_count [bound_color = { 'c' r g b }] ] ... [edge = { 'e' vertex_id [edge_hidden = { 'h' }] ]",
    __FILE__,VDrawPArray,group);

  theCommands.Add("vconnect", 
    "vconnect : name object Xo Yo Zo Xu Xv Xw Zu Zv Zw", 
    __FILE__, VConnect, group);

  theCommands.Add("vconnectsh", 
    "vconnectsh : name shape Xo Yo Zo Xu Xv Xw Zu Zv Zw", 
    __FILE__, VConnectShape, group);

  theCommands.Add("vselmode", 
    "vselmode : [object] mode On/Off (1/0)", 
    __FILE__, VSetSelectionMode, group);

  theCommands.Add("vtriangle",
    "vtriangle Name PointName PointName PointName", 
    __FILE__, VTriangle,group);

  theCommands.Add("vsegment",
    "vsegment Name PointName PointName", 
    __FILE__, VSegment,group);

  theCommands.Add("vobjzlayer",
    "vobjzlayer : set/get object [layerid] - set or get z layer id for the interactive object",
    __FILE__, VObjZLayer, group);
  
  theCommands.Add("vpolygonoffset",
    "vpolygonoffset : [object [mode factor units]] - sets/gets polygon offset parameters for an object, without arguments prints the default values",
    __FILE__, VPolygonOffset, group);

  theCommands.Add ("vshowfaceboundary",
    "vshowfaceboundary : ObjectName isOn (1/0) [R G B [LineWidth [LineStyle]]]"
    "- turns on/off drawing of face boundaries for ais object "
    "and defines boundary line style.",
    __FILE__, VShowFaceBoundary, group);
}
