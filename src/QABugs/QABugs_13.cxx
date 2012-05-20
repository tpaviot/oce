// Created on: 2002-05-16
// Created by: QA Admin
// Copyright (c) 2002-2012 OPEN CASCADE SAS
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



#include <QABugs.hxx>

#include <Draw_Interpretor.hxx>
#include <DBRep.hxx>
#include <DrawTrSurf.hxx>
#include <AIS_InteractiveContext.hxx>
#include <ViewerTest.hxx>
#include <AIS_Shape.hxx>
#include <TopoDS_Shape.hxx>

#include <tcl.h>
#include <stdio.h>

#include <gp_Ax2.hxx>
#include <gp_Circ.hxx>
#include <gp_Pln.hxx>
#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepGProp.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Plane.hxx>
#include <Law_Linear.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopExp_Explorer.hxx>
#include <GProp_GProps.hxx>
#include <Standard_ErrorHandler.hxx>

//=======================================================================
//function :  OCC332
//purpose  : 
//=======================================================================
static Standard_Integer OCC332bug (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  // Used to Display Geometry or Topolgy
  char name[255];
  char *pname = name;
  Standard_Boolean check = Standard_True;

  // Set default arguments
  double wall_thickness = 10.0;
  double dia1 = 80.0;
  double dia2 = 100.0;
  double length = 400.0;
  double major_radius = 280.0;

  // Convert arguments
  if (argc>1) wall_thickness = atof(argv[1]);
  if (argc>2) dia1 = atof(argv[2]);
  if (argc>3) dia2 = atof(argv[3]);
  if (argc>4) major_radius = atof(argv[4]);
  if (argc>5) length = atof(argv[5]);
  double bend_angle = length/major_radius;

  //if ((bend_angle >= M_PI)) {
  if ((bend_angle >= M_PI)) {
    di << "The arguments are invalid." << "\n";
    return(TCL_ERROR);
  }
  di << "creating the shape for a bent tube" << "\n";

  double radius_l = dia1/2.0;
  double radius_r = dia2/2.0;

  // SUPPORT:
  // 1. There is no need to normalize the direction - it's done automatically
  //gp_Ax2 origin(gp_Pnt(5000.0,-300.0, 1000.0),
		//gp_Dir(0.0, -1.0/sqrt(2.0), -1.0/sqrt(2.0)));
  gp_Ax2 origin(gp_Pnt(5000.0,-300.0,1000.0),gp_Dir(0.0,-1.0,-1.0));

  TopoDS_Face myFace;
  TopoDS_Shape myShape, gasSolid;
  TopoDS_Solid wallSolid;

  // Construct a circle for the first face, on the xy-plane at the origin
  gp_Pln circ1Plane(origin.Location(), origin.Direction());
  gp_Circ faceCircle(origin, radius_l);
  gp_Circ outFaceCircle(origin, radius_l+wall_thickness);

  // Construct center for a circle to be the spine of
  // revolution, on the xz-plane at x=major_radius
  gp_Pnt circ_center = origin.Location().Translated(major_radius*origin.XDirection());

  // This point will be the center of the second face.
  // SUPPORT:
  // - There is no need in this point - we'll use angle instead.
  //gp_Pnt endPoint = origin.Location();
  //endPoint.Translate(major_radius*(1.0-cos(bend_angle))*origin.XDirection()) ;
  //endPoint.Translate((-major_radius*sin(bend_angle))*origin.Direction());

  // Construct the plane for the second face to sit on.
  // SUPPORT:
  // - It is better to use rotation instead of explicit calculations
  //gp_Pln circ2Plane = gce_MakePln(circ_center, endPoint,
  //				  endPoint.Translated(major_radius*origin.YDirection())
  //				  ).Value();
  gp_Ax1 circ_axis(circ_center,origin.YDirection());
  gp_Pln circ2Plane = circ1Plane.Rotated(circ_axis,bend_angle);

  // The circle used for the spine.
  // SUPPORT:
  // - Use direction (-X) instead of (X) to obtain correct right-handed system.
  //   It is very important to maintain correct orientation between spine
  //   and circles axes.
  //gp_Ax2 spineAxis(circ_center, origin.YDirection(), origin.XDirection());
  gp_Ax2 spineAxis(circ_center, origin.YDirection(), -origin.XDirection());
  gp_Circ circle(spineAxis, major_radius);

  // SUPPORT:
  // - There is no need to create 2nd circles - they will be created by MakePipeShell.
  //gp_Ax2 circ2axis(endPoint, circ2Plane.Axis().Direction(), origin.YDirection());
  //gp_Circ faceCircle2(circ2axis,radius_r);
  //gp_Circ outFaceCircle2(circ2axis,radius_r+wall_thickness);

  TopoDS_Edge E1 = BRepBuilderAPI_MakeEdge(faceCircle);
  TopoDS_Wire Wire1_ = BRepBuilderAPI_MakeWire(E1).Wire();
  
  // Create the face at the near end for the wall solid, an annular ring.
  TopoDS_Edge Eout1 = BRepBuilderAPI_MakeEdge(outFaceCircle);
  TopoDS_Wire outerWire1_ = BRepBuilderAPI_MakeWire(Eout1).Wire();

  // SUPPORT:
  // - There is no need to create 2nd circles -
  //   they will be created by MakePipeShell
  //TopoDS_Edge E2 = BRepBuilderAPI_MakeEdge(faceCircle2);
  //TopoDS_Wire Wire2_ = BRepBuilderAPI_MakeWire(E2).Wire();
  
  // Create the face at the far end for the wall solid, an annular ring.
  // SUPPORT:
  // - There is no need to create 2nd circles -
  //   they will be created by MakePipeShell
  //TopoDS_Edge Eout2 = BRepBuilderAPI_MakeEdge(outFaceCircle2);
  //TopoDS_Wire outerWire2_ = BRepBuilderAPI_MakeWire(Eout2).Wire();

  // SUPPORT:
  // - It is better to use bend angle calculated above
  //Handle(Geom_Curve) SpineCurve = GC_MakeArcOfCircle(circle,
  //						     endPoint,
  //						     origin.Location(),
  //						     Standard_True).Value();
  Handle(Geom_Curve) SpineCurve = GC_MakeArcOfCircle(circle,
                                                     0.0,
                                                     bend_angle,
						     Standard_True).Value();

  // SUPPORT:
  // - Use correct formula for scaling laws
  Handle(Law_Linear) myLaw1 = new Law_Linear();
  Handle(Law_Linear) myLaw2 = new Law_Linear();
  //if ((radius_r - radius_l) < Precision::Confusion())
  //{
    //myLaw1->Set(SpineCurve->FirstParameter(), 1.0,
		//SpineCurve->LastParameter(), 1.0);
    //myLaw2->Set(SpineCurve->FirstParameter(), 1.0,
		//SpineCurve->LastParameter(), 1.0);
  //}
  //else
  //{
    //myLaw1->Set(SpineCurve->FirstParameter(), radius_r/(radius_r-radius_l),
		//SpineCurve->LastParameter(), 1.0);
    //myLaw2->Set(SpineCurve->FirstParameter(), (radius_r+wall_thickness)/(radius_r-radius_l),
		//SpineCurve->LastParameter(), 1.0);
  //}
  myLaw1->Set(SpineCurve->FirstParameter(),1.0,
              SpineCurve->LastParameter(),radius_r/radius_l);
  myLaw2->Set(SpineCurve->FirstParameter(),1.0,
              SpineCurve->LastParameter(),(radius_r+wall_thickness)/(radius_l+wall_thickness));

  BRepBuilderAPI_MakeFace mkFace;

  BRepBuilderAPI_MakeEdge mkEdge;

  mkEdge.Init(SpineCurve);
  if (!mkEdge.IsDone()) return 0;
  TopoDS_Wire SpineWire = BRepBuilderAPI_MakeWire(mkEdge.Edge()).Wire();

  sprintf (name,"SpineWire");
  DBRep::Set(name,SpineWire);

  sprintf (name,"Wire1_");
  DBRep::Set(name,Wire1_);

  sprintf (name,"outerWire1_");
  DBRep::Set(name,outerWire1_);

  // SUPPORT:
  // - There is no need to create 2nd circles
  //sprintf (name,"Wire2_");
  //DBRep::Set(name,Wire2_);
  //sprintf (name,"outerWire2_");
  //DBRep::Set(name,outerWire2_);

  di.Eval("fit");

  // SUPPORT:
  // - There is no need in these vertices
  //TopoDS_Vertex Location1, Location2;
  //TopExp::Vertices(SpineWire, Location1, Location2);

  // Make inner pipe shell
  BRepOffsetAPI_MakePipeShell mkPipe1(SpineWire);
  mkPipe1.SetTolerance(1.0e-8,1.0e-8,1.0e-6);
  //mkPipe1.SetTransitionMode(BRepBuilderAPI_Transformed); // Default mode !!
  mkPipe1.SetLaw(Wire1_, myLaw1/*, Location2*/, Standard_False, Standard_False);
  mkPipe1.Build();
  if (!mkPipe1.IsDone()) return 0;

  // Make outer pipe shell
  BRepOffsetAPI_MakePipeShell mkPipe2(SpineWire);
  mkPipe2.SetTolerance(1.0e-8,1.0e-8,1.0e-6);
  //mkPipe2.SetTransitionMode(BRepBuilderAPI_Transformed); // Default mode !!
  mkPipe2.SetLaw(outerWire1_, myLaw2/*, Location2*/, Standard_False, Standard_False);
  mkPipe2.Build();
  if (!mkPipe2.IsDone()) return 0;

  // Make face for first opening
  Handle(Geom_Plane) Plane1 = new Geom_Plane(circ1Plane);
  mkFace.Init(Plane1,Standard_False,Precision::Confusion());
  // SUPPORT:
  // - Use wires created by MakePipeShell
  //mkFace.Add(TopoDS::Wire(outerWire1_));
  //mkFace.Add(TopoDS::Wire(Wire1_.Reversed()));
  mkFace.Add(TopoDS::Wire(mkPipe2.FirstShape()));
  mkFace.Add(TopoDS::Wire(mkPipe1.FirstShape().Reversed()));
  if (!mkFace.IsDone()) return 0;
  TopoDS_Face Face1 = mkFace.Face();

  // Make face for second opening
  Handle(Geom_Plane) Plane2 = new Geom_Plane(circ2Plane);
  mkFace.Init(Plane2,Standard_False,Precision::Confusion());
  // SUPPORT:
  // - Use wires created by MakePipeShell
  //mkFace.Add(TopoDS::Wire(outerWire2_));
  //mkFace.Add(TopoDS::Wire(Wire2_.Reversed()));
  mkFace.Add(TopoDS::Wire(mkPipe2.LastShape()));
  mkFace.Add(TopoDS::Wire(mkPipe1.LastShape().Reversed()));
  if (!mkFace.IsDone()) return 0;
  TopoDS_Face Face2 = mkFace.Face();

  // Make tube
  TopoDS_Shell TubeShell;
  BRep_Builder B;
  B.MakeShell(TubeShell);
  TopExp_Explorer getFaces;
  TopoDS_Face test_face;
  getFaces.Init(mkPipe1.Shape(), TopAbs_FACE);
  // SUPPORT:
  // - In our case there should be only 1 pipe face
  //while (getFaces.More())
  //  {
  //    test_face = TopoDS::Face(getFaces.Current());
  //    Handle(Geom_Surface) S = BRep_Tool::Surface(test_face); 
  //    GeomLib_IsPlanarSurface IsPl(S);
  //    if (!IsPl.IsPlanar()) {
  //	B.Add(TubeShell,getFaces.Current().Reversed());
  //    }
  //    getFaces.Next();
  //  }
  if (getFaces.More())
    B.Add(TubeShell,getFaces.Current().Reversed());

  // Grab the gas solid now that we've extracted the faces.
  mkPipe1.MakeSolid();
  gasSolid = mkPipe1.Shape();

  sprintf (name,"gasSolid_");
  DBRep::Set(name,gasSolid);

  //getFaces.Clear();
  getFaces.Init(mkPipe2.Shape(), TopAbs_FACE);
  // SUPPORT:
  // - In our case there should be only 1 pipe face
  //while (getFaces.More())
  //  {
  //    B.Add(TubeShell,getFaces.Current());
  //    getFaces.Next();
  //  }
  if (getFaces.More())
    B.Add(TubeShell,getFaces.Current());

  B.Add(TubeShell,Face1.Reversed());
  B.Add(TubeShell,Face2);

  B.MakeSolid(wallSolid);
  B.Add(wallSolid,TubeShell);

  sprintf (name,"wallSolid_");
  DBRep::Set(name,wallSolid);

  // Now calculated the volume of the outside tube.
  GProp_GProps gprops;
  BRepGProp::VolumeProperties(wallSolid, gprops);
  di << "The wallSolid's volume is: " << gprops.Mass() << "\n";

  if (check) {
    if (!(BRepCheck_Analyzer(wallSolid).IsValid()))
      di << "The TopoDS_Solid was checked, and it was invalid!" << "\n";
    else
      di << "The TopoDS_Solid was checked, and it was valid." << "\n";
    if (!wallSolid.Closed())
      di << "The TopoDS_Solid is not closed!" << "\n";
    else
      di << "The TopoDS_Solid is closed." << "\n";
    if (!wallSolid.Checked())
      di << "The TopoDS_Solid is not checked!" << "\n";
    else
      di << "The TopoDS_Solid has been checked." << "\n";
    if (wallSolid.Infinite())
      di << "The TopoDS_Solid is infinite!" << "\n";
    else
      di << "The TopoDS_Solid is finite." << "\n";
  }

  di << "The result is a ";
  // Check to see if we have a solid
  switch (wallSolid.ShapeType()) {
  case (TopAbs_COMPOUND):
    di << "TopAbs_COMPOUND" << "\n";
    break;
  case (TopAbs_COMPSOLID):
    di << "TopAbs_COMPSOLID" << "\n";
    break;
  case (TopAbs_SOLID):
    di << "TopAbs_SOLID" << "\n";
    break;
  case (TopAbs_SHELL):
    di << "TopAbs_SHELL" << "\n";
    break;
  case (TopAbs_FACE):
    di << "TopAbs_FACE" << "\n";
    break;
  case (TopAbs_WIRE):
    di << "TopAbs_WIRE" << "\n";
    break;
  case (TopAbs_EDGE):
    di << "TopAbs_EDGE" << "\n";
    break;
  case (TopAbs_VERTEX):
    di << "TopAbs_VERTEX" << "\n";
    break;
  case (TopAbs_SHAPE):
    di << "TopAbs_SHAPE" << "\n";
  }
  di << "Can we turn it into a solid? ";
  try {
    OCC_CATCH_SIGNALS
    di << " yes" << "\n";
  }
  catch (Standard_TypeMismatch) {
    di << " no" << "\n";
  }

  getFaces.Clear();
  getFaces.Init(wallSolid, TopAbs_FACE);
  int i =0;
  while (getFaces.More())
    {
      i++;
      sprintf(name,"Face%d",i);
      di << "Face named " << name << "\n";
      DBRep::Set(name,getFaces.Current());
      getFaces.Next();
    }

  return 0;
}

#include <gce_MakePln.hxx>
#include <TopExp.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
///////#else
///////#include <BRepAlgo_Fuse.hxx>
///////#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgo_Fuse.hxx>

//=======================================================================
//function :  OCC544
//purpose  : 
//=======================================================================
static Standard_Integer OCC544 (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if(argc > 7) {
    di << "Usage : " << argv[0] << " [[[[[wT [[[[d1 [[[d2 [[R [length [BRepAlgoAPI/BRepAlgo = 1/0]]]]]]" << "\n";
    return 1;
  }
  Standard_Boolean IsBRepAlgoAPI = Standard_True;
  if (argc == 7) {
    Standard_Integer IsB = atoi(argv[6]);
    if (IsB != 1) {
      IsBRepAlgoAPI = Standard_False;
#if ! defined(BRepAlgo_def01)
//      di << "Error: There is not BRepAlgo_Fuse class" << "\n";
//      return 1;
#endif
    }
  }

  // Used to Display Geometry or Topolgy
  char name[255];
  char *pname = name;
  //bool check = true;
  Standard_Boolean check = Standard_True;

  // Set default arguments
  double radius_l = 20.0;
  double radius_r = 80.0;
  // mkv 15.07.03 double bend_angle = M_PI/2.0;
  double bend_angle = M_PI/2.0;

  double major_rad = 280.0;
  double wall_thickness = 10.0;
		    

  // Convert arguments
  if (argc>1) radius_l = atof(argv[1]);
  if (argc>2) radius_r = atof(argv[2]);
  if (argc>3) bend_angle = atof(argv[3]);
  if (argc>4) major_rad = atof(argv[4]);
  if (argc>5) wall_thickness = atof(argv[5]);

  // mkv 15.07.03 if ((bend_angle >= 2.0*M_PI)) {
  if ((bend_angle >= 2.0*M_PI)) {
    di << "The arguments are invalid." << "\n";
    return(TCL_ERROR);
  }
  di << "creating the shape for a bent tube" << "\n";
 
  gp_Ax2 origin(gp_Pnt(500.0,-300.0, 100.0),
		gp_Dir(0.0, -1.0/sqrt(2.0), -1.0/sqrt(2.0)));

  TopoDS_Face firstFace, lastFace;
  TopoDS_Solid wallSolid, myShape;
  // Construct a circle for the first face, on the xy-plane at the origin
  gp_Pln circ1Plane(origin.Location(), origin.Direction());
  gp_Circ faceCircle(origin, radius_l);
  gp_Circ outFaceCircle(origin, radius_l+wall_thickness);

  // Construct center for a circle to be the spine of
  // revolution, on the xz-plane at x=major_rad
  gp_Pnt circ_center = origin.Location().Translated(
						    major_rad*origin.XDirection()
						    );

  // This point will be the center of the second face.
  gp_Pnt endPoint = origin.Location();
  endPoint.Translate(major_rad*(1.0-cos(bend_angle))*origin.XDirection()) ;
  endPoint.Translate((-major_rad*sin(bend_angle))*origin.Direction());

  // Construct the plane for the second face to sit on.
  gp_Pln circ2Plane = gce_MakePln(circ_center, endPoint,
				  endPoint.Translated(major_rad*origin.YDirection())
				  ).Value();

  // The circle used for the spine.
  gp_Ax2 spineAxis(circ_center, origin.YDirection(), origin.XDirection());
  gp_Circ circle(spineAxis, major_rad);

  gp_Ax2 circ2axis(endPoint, circ2Plane.Axis().Direction(), origin.YDirection());
  gp_Circ faceCircle2(circ2axis,radius_r);
  gp_Circ outFaceCircle2(circ2axis,radius_r+wall_thickness);

  TopoDS_Edge E1_1 = BRepBuilderAPI_MakeEdge(faceCircle, 0, M_PI);
  TopoDS_Edge E1_2 = BRepBuilderAPI_MakeEdge(faceCircle, M_PI, 2.*M_PI);
  TopoDS_Wire Wire1_ = BRepBuilderAPI_MakeWire(E1_1, E1_2);
  
  // Create the face at the near end for the wall solid, an annular ring.
  TopoDS_Edge Eout1_1 = BRepBuilderAPI_MakeEdge(outFaceCircle, 0, M_PI);
  TopoDS_Edge Eout1_2 = BRepBuilderAPI_MakeEdge(outFaceCircle, M_PI, 2.*M_PI);
  TopoDS_Wire outerWire1_ = BRepBuilderAPI_MakeWire(Eout1_1, Eout1_2);
 
  TopoDS_Edge E2_1 = BRepBuilderAPI_MakeEdge(faceCircle2, 0, M_PI);
  TopoDS_Edge E2_2 = BRepBuilderAPI_MakeEdge(faceCircle2, M_PI, 2.*M_PI);
  TopoDS_Wire Wire2_ = BRepBuilderAPI_MakeWire(E2_1, E2_2);
  
  // Create the face at the far end for the wall solid, an annular ring.
  TopoDS_Edge Eout2_1 = BRepBuilderAPI_MakeEdge(outFaceCircle2, 0, M_PI);
  TopoDS_Edge Eout2_2 = BRepBuilderAPI_MakeEdge(outFaceCircle2, M_PI, 2.*M_PI);
  TopoDS_Wire outerWire2_ = BRepBuilderAPI_MakeWire(Eout2_1, Eout2_2);

  BRepBuilderAPI_MakeFace mkFace;

  Handle(Geom_Curve) SpineCurve = GC_MakeArcOfCircle(circle,
						     endPoint,
						     origin.Location(),
						     Standard_True).Value();
  Handle(Law_Linear) myLaw = new Law_Linear();
  Handle(Law_Linear) myLaw2 = new Law_Linear();

  myLaw->Set(SpineCurve->FirstParameter(),
	     radius_r/radius_l,
	     SpineCurve->LastParameter(),
	     1.0);

  myLaw2->Set(SpineCurve->FirstParameter(),
	      (radius_r+wall_thickness)/(radius_l+wall_thickness),
	      SpineCurve->LastParameter(),
	      1.0);

  di << "SpineCurve->FirstParameter() is " << SpineCurve->FirstParameter() << "\n";
  di << "SpineCurve->LastParameter() is " << SpineCurve->LastParameter() << "\n";
  di << "Law1 Value at FirstParameter() is " << myLaw->Value(SpineCurve->FirstParameter()) << "\n";
  di << "Law1 Value at LastParameter() is " << myLaw->Value(SpineCurve->LastParameter()) << "\n";
  di << "radius_r / radius_l is " << radius_r/radius_l << "\n";

  BRepBuilderAPI_MakeEdge mkEdge;

  mkEdge.Init(SpineCurve);
  if (!mkEdge.IsDone()) return TCL_ERROR;
  TopoDS_Wire SpineWire = BRepBuilderAPI_MakeWire(mkEdge.Edge()).Wire();

  sprintf (name,"SpineWire");
  DBRep::Set(name,SpineWire);

  sprintf (name,"Wire1_");
  DBRep::Set(name,Wire1_);

  sprintf (name,"outerWire1_");
  DBRep::Set(name,outerWire1_);

  sprintf (name,"Wire2_");
  DBRep::Set(name,Wire2_);

  sprintf (name,"outerWire2_");
  DBRep::Set(name,outerWire2_);

  di.Eval("fit");

  TopoDS_Vertex Location1, Location2;

  TopExp::Vertices(SpineWire, Location2, Location1);

  sprintf (name,"Location1");
  DBRep::Set(name,Location1);

  sprintf (name,"Location2");
  DBRep::Set(name,Location2);

  // Make inner pipe shell
  BRepOffsetAPI_MakePipeShell mkPipe1(SpineWire);
  mkPipe1.SetTolerance(1.0e-8,1.0e-8,1.0e-6);
  mkPipe1.SetTransitionMode(BRepBuilderAPI_Transformed);
  mkPipe1.SetMode(Standard_False);
  mkPipe1.SetLaw(Wire1_, myLaw, Location1, Standard_False, Standard_False);
  mkPipe1.Build();
  if (!mkPipe1.IsDone()) return TCL_ERROR;

  // Make outer pipe shell
  BRepOffsetAPI_MakePipeShell mkPipe2(SpineWire);
  mkPipe2.SetTolerance(1.0e-8,1.0e-8,1.0e-6);
  mkPipe2.SetTransitionMode(BRepBuilderAPI_Transformed);
  mkPipe2.SetMode(Standard_False);
  mkPipe2.SetLaw(outerWire1_, myLaw2, Location1, Standard_False, Standard_False);
 mkPipe2.Build();
  if (!mkPipe2.IsDone()) return TCL_ERROR;

//    sprintf(name,"w1-first");
//    DBRep::Set(name,mkPipe1.FirstShape());

//    sprintf(name,"w1-last");
//    DBRep::Set(name,mkPipe1.LastShape());

//    sprintf(name,"w2-first");
//    DBRep::Set(name,mkPipe2.FirstShape());

//    sprintf(name,"w2-last");
//    DBRep::Set(name,mkPipe2.LastShape());

  BRepOffsetAPI_Sewing SewIt(1.0e-4);

  // Make tube
  TopExp_Explorer getFaces;
  TopoDS_Face test_face;
  getFaces.Init(mkPipe1.Shape(), TopAbs_FACE);
  while (getFaces.More())
    {
      SewIt.Add(getFaces.Current().Reversed());
      getFaces.Next();
    }

  // Make face for first opening
  Handle(Geom_Plane) Plane1 = new Geom_Plane(circ1Plane);
  mkFace.Init(Plane1,Standard_False,Precision::Confusion());
  mkFace.Add(TopoDS::Wire(outerWire1_));
  mkFace.Add(TopoDS::Wire(Wire1_.Reversed()));
  if (!mkFace.IsDone()) return TCL_ERROR;
  TopoDS_Face Face1 = mkFace.Face();

  // Make face for second opening
  Handle(Geom_Plane) Plane2 = new Geom_Plane(circ2Plane);
  mkFace.Init(Plane2,Standard_False,Precision::Confusion());
  mkFace.Add(TopoDS::Wire(outerWire2_));
  mkFace.Add(TopoDS::Wire(Wire2_.Reversed()));
  if (!mkFace.IsDone()) return TCL_ERROR;
  TopoDS_Face Face2 = mkFace.Face();

  // Grab the gas solid now that we've extracted the faces.
  mkPipe1.MakeSolid();
  myShape = TopoDS::Solid(mkPipe1.Shape());

  getFaces.Clear();
  getFaces.Init(mkPipe2.Shape(), TopAbs_FACE);
  while (getFaces.More())
    {
      SewIt.Add(getFaces.Current());
      getFaces.Next();
    }

  SewIt.Add(Face1.Reversed());
  SewIt.Add(Face2);

  SewIt.Perform();

  di << "The result of the Sewing operation is a ";
  // Check to see if we have a solid
  switch (SewIt.SewedShape().ShapeType()) {
  case (TopAbs_COMPOUND):
    di << "TopAbs_COMPOUND" << "\n";
    break;
  case (TopAbs_COMPSOLID):
    di << "TopAbs_COMPSOLID" << "\n";
    break;
  case (TopAbs_SOLID):
    di << "TopAbs_SOLID" << "\n";
    break;
  case (TopAbs_SHELL):
    di << "TopAbs_SHELL" << "\n";
    break;
  case (TopAbs_FACE):
    di << "TopAbs_FACE" << "\n";
    break;
  case (TopAbs_WIRE):
    di << "TopAbs_WIRE" << "\n";
    break;
  case (TopAbs_EDGE):
    di << "TopAbs_EDGE" << "\n";
    break;
  case (TopAbs_VERTEX):
    di << "TopAbs_VERTEX" << "\n";
    break;
  case (TopAbs_SHAPE):
    di << "TopAbs_SHAPE" << "\n";
  }

  BRep_Builder B;

  TopoDS_Shell TubeShell;
  di << "Can we turn it into a shell? ";
  try {
    OCC_CATCH_SIGNALS
    TubeShell = TopoDS::Shell(SewIt.SewedShape());
    B.MakeSolid(wallSolid);
    B.Add(wallSolid,TubeShell);
    di << " yes" << "\n";
  }
  catch (Standard_TypeMismatch) {
    di << "Can't convert to shell..." << "\n";
    TopExp_Explorer getSol;
    getSol.Init(SewIt.SewedShape(), TopAbs_SOLID);
    if (getSol.More()) {
      di << "First solid found in compound" << "\n";
      wallSolid = TopoDS::Solid(getSol.Current());
      TopoDS_Solid test_solid;
      while (getSol.More())
	{
	  di << "Next solid found in compound" << "\n";
	  getSol.Next();
	  test_solid = TopoDS::Solid(getSol.Current());
//////#if ! defined(BRepAlgoAPI_def01)
//////	  BRepAlgoAPI_Fuse fuser(test_solid, wallSolid);
//////#else
//////	  BRepAlgo_Fuse fuser(test_solid, wallSolid);
//////#endif
//////	  fuser.Build();
	  if (IsBRepAlgoAPI) {
	    di << "BRepAlgoAPI_Fuse fuser(test_solid, wallSolid)" <<"\n";
	    BRepAlgoAPI_Fuse fuser(test_solid, wallSolid);
	    fuser.Build();
	    wallSolid = TopoDS::Solid(fuser.Shape());
	  } else {
	    di << "BRepAlgo_Fuse fuser(test_solid, wallSolid)" <<"\n";
	    BRepAlgo_Fuse fuser(test_solid, wallSolid);
	    fuser.Build();
	    wallSolid = TopoDS::Solid(fuser.Shape());
	  }
//////	  wallSolid = TopoDS::Solid(fuser.Shape());
	}
    } else {
      // Let's see if we can extract shells instead of solids.
      TopExp_Explorer getShel;
      getShel.Init(SewIt.SewedShape(), TopAbs_SHELL);
      if (getShel.More()) {
	di << "First shell found in compound" << "\n";
	B.MakeSolid(wallSolid);
	di << "B.Add(wallSolid,TopoDS::Shell(getShel.Current()));" << "\n";
	int i = 1;
	while (getShel.More())
	  {
	    di << "Next shell found in compound" << "\n";
	    di << "B.Add(wallSolid,TopoDS::Shell(getShel.Current()));" << "\n";
	    sprintf(name,"shell%d", i++);
	    DBRep::Set(name,getShel.Current());
	    B.Add(wallSolid,TopoDS::Shell(getShel.Current()));
	    getShel.Next();
	  }
      }
    }
  }

  sprintf(name,"result");
  DBRep::Set(name,wallSolid);

  // Now calculated the volume of the outside tube.
  GProp_GProps gprops;
  BRepGProp::VolumeProperties(wallSolid, gprops);
  di << "The wallSolid's volume is: " << gprops.Mass() << "\n";

  if (check) {
    if (!(BRepCheck_Analyzer(wallSolid).IsValid()))
      di << "The TopoDS_Solid was checked, and it was invalid!" << "\n";
    else
      di << "The TopoDS_Solid was checked, and it was valid." << "\n";
    if (!wallSolid.Closed())
      di << "The TopoDS_Solid is not closed!" << "\n";
    else
      di << "The TopoDS_Solid is closed." << "\n";
    if (!wallSolid.Checked())
      di << "The TopoDS_Solid is not checked!" << "\n";
    else
      di << "The TopoDS_Solid has been checked." << "\n";
    if (wallSolid.Infinite())
      di << "The TopoDS_Solid is infinite!" << "\n";
    else
      di << "The TopoDS_Solid is finite." << "\n";
  }

  di << "The result is a ";
  // Check to see if we have a solid
  switch (wallSolid.ShapeType()) {
  case (TopAbs_COMPOUND):
    di << "TopAbs_COMPOUND" << "\n";
    break;
  case (TopAbs_COMPSOLID):
    di << "TopAbs_COMPSOLID" << "\n";
    break;
  case (TopAbs_SOLID):
    di << "TopAbs_SOLID" << "\n";
    break;
  case (TopAbs_SHELL):
    di << "TopAbs_SHELL" << "\n";
    break;
  case (TopAbs_FACE):
    di << "TopAbs_FACE" << "\n";
    break;
  case (TopAbs_WIRE):
    di << "TopAbs_WIRE" << "\n";
    break;
  case (TopAbs_EDGE):
    di << "TopAbs_EDGE" << "\n";
    break;
  case (TopAbs_VERTEX):
    di << "TopAbs_VERTEX" << "\n";
    break;
  case (TopAbs_SHAPE):
    di << "TopAbs_SHAPE" << "\n";
  }

  return 0;
}

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepBndLib.hxx>
#include <TopTools_Array1OfShape.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Common.hxx>
//////////#else
//////////#include <BRepAlgo_Cut.hxx>
//////////#include <BRepAlgo_Common.hxx>
//////////#include <BRepAlgoAPI_Cut.hxx>
//////////#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgo_Cut.hxx>
#include <BRepAlgo_Common.hxx>
#include <Precision.hxx>

static Standard_Integer OCC817 (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  //////////if(argc != 3) {
  //////////  cout << "Usage : " << argv[0] << " result mesh_delta" << endl;
  //////////  return 1;	
  //////////}
  if(argc < 3 || argc > 4) {
    di << "Usage : " << argv[0] << " result mesh_delta [BRepAlgoAPI/BRepAlgo = 1/0]" << "\n";
    return 1;
  }
  Standard_Boolean IsBRepAlgoAPI = Standard_True;
  if (argc == 4) {
    Standard_Integer IsB = atoi(argv[3]);
    if (IsB != 1) {
      IsBRepAlgoAPI = Standard_False;
#if ! defined(BRepAlgo_def02)
//      di << "Error: There is not BRepAlgo_Cut class" << "\n";
//      return 1;
#endif
#if ! defined(BRepAlgo_def03)
//      di << "Error: There is not BRepAlgo_Common class" << "\n";
//      return 1;
#endif
    }
  }
  
  Standard_Real delt = 5.0*Precision::Confusion();
  Standard_Real mesh_delt = atof(argv[2]);
  if (mesh_delt <= 0.0)
  {
    di<<"Error: mesh_delta must be positive value"<<"\n";
    return -1;
  }

  // Create outer box solid
  gp_Pnt P(0,0,0);
  TopoDS_Solid fullSolid = BRepPrimAPI_MakeBox(P, 30.0, 30.0, 30.0).Solid();

  // Create inner box solid
  P.SetX(10); P.SetY(10); P.SetZ(10);
  TopoDS_Solid internalSolid = BRepPrimAPI_MakeBox(P, 10.0, 10.0, 10.0).Solid();

  // Cut inner from outer
//////////#if ! defined(BRepAlgoAPI_def01)
//////////  BRepAlgoAPI_Cut cut( fullSolid, internalSolid );
//////////#else
//////////  BRepAlgo_Cut cut( fullSolid, internalSolid );
//////////#endif
//////////  TopoDS_Shape cut_shape = cut.Shape();
//////////  if ( !cut.IsDone() )
//////////  {
//////////    cout << "Error: Could not cut volumes" << endl;
//////////    return -1;
//////////  }

  TopoDS_Shape cut_shape;
  if (IsBRepAlgoAPI) {
    di << "BRepAlgoAPI_Cut cut( fullSolid, internalSolid )" <<"\n";
    BRepAlgoAPI_Cut cut( fullSolid, internalSolid );
    cut_shape = cut.Shape();
    if ( !cut.IsDone() )
      {
	di << "Error: Could not cut volumes" << "\n";
	return -1;
      }
  } else {
    di << "BRepAlgo_Cut cut( fullSolid, internalSolid )" <<"\n";
    BRepAlgo_Cut cut( fullSolid, internalSolid );
    cut_shape = cut.Shape();
    if ( !cut.IsDone() )
      {
	di << "Error: Could not cut volumes" << "\n";
	return -1;
      }
  }

  // see if we have a solid
  Standard_Integer found_solid = 0;
  TopoDS_Solid cutSolid;
  TopExp_Explorer Ex;
  for (Ex.Init(cut_shape, TopAbs_SOLID); Ex.More(); Ex.Next())
  {
    TopoDS_Solid sol = TopoDS::Solid(Ex.Current());
    if (!sol.IsNull()) { cutSolid = sol; found_solid++; }
  }
  if ( found_solid != 1 )
  {
    di << "Error: Cut operation produced " << found_solid << " solids" << "\n";
    return -1;
  }
  DBRep::Set(argv[1],cutSolid);

  // Calculate initial volume
  GProp_GProps volumeVProps;
  BRepGProp::VolumeProperties (cutSolid, volumeVProps);
  di << "Info: Original volume  = " << volumeVProps.Mass() << "\n";

  //
  // build bounding box and calculate bounds for initial mesh
  //
  Bnd_Box bndBox;
  BRepBndLib::Add( cutSolid, bndBox );
  Standard_Real Xmin, Ymin, Zmin, Xmax, Ymax, Zmax;
  bndBox.Get( Xmin, Ymin, Zmin, Xmax, Ymax, Zmax );
  Xmin -= delt;
  Ymin -= delt;
  Zmin -= delt;
  Xmax += delt;
  Ymax += delt;
  Zmax += delt;
  di<<"Info: Bounds\n  ("<<Xmin<<","<<Ymin<<","<<Zmin<<")\n  ("<<Xmax<<","<<Ymax<<","<<Zmax<<")"<<"\n";

  // grid the bounding box
  Standard_Integer NumXsubvolumes = (Xmax - Xmin) / mesh_delt; if (NumXsubvolumes <= 0) NumXsubvolumes = 1;
  Standard_Integer NumYsubvolumes = (Ymax - Ymin) / mesh_delt; if (NumYsubvolumes <= 0) NumYsubvolumes = 1;
  Standard_Integer NumZsubvolumes = (Zmax - Zmin) / mesh_delt; if (NumZsubvolumes <= 0) NumZsubvolumes = 1;
  const Standard_Real StepX = (Xmax - Xmin) / NumXsubvolumes;
  const Standard_Real StepY = (Ymax - Ymin) / NumYsubvolumes;
  const Standard_Real StepZ = (Zmax - Zmin) / NumZsubvolumes;
  const Standard_Integer NumSubvolumes = NumXsubvolumes * NumYsubvolumes * NumZsubvolumes;
  di << "Info: NumSubvolumesX = " << NumXsubvolumes << "\n";
  di << "Info: NumSubvolumesY = " << NumYsubvolumes << "\n";
  di << "Info: NumSubvolumesZ = " << NumZsubvolumes << "\n";
  di << "Info: NumSubvolumes = " << NumSubvolumes << "\n";

  //
  // construct initial mesh of cutSolid
  //
  TopTools_Array1OfShape SubvolumeSolid(0,NumSubvolumes-1);
  TColStd_Array1OfReal SubvolumeVol(0,NumSubvolumes-1);
  Standard_Real accumulatedVolume = 0.0;
  Standard_Integer i, j, k, l = 0;
  Standard_Real x = Xmin;
  for ( i = 0; i < NumXsubvolumes; i++ )
  {
    Standard_Real y = Ymin;
    for ( j = 0; j < NumYsubvolumes; j++ )
    {
      Standard_Real z = Zmin;
      for ( k = 0; k < NumZsubvolumes; k++ )
      {
	P.SetX(x);
	P.SetY(y);
	P.SetZ(z);
	TopoDS_Shape aSubvolume = BRepPrimAPI_MakeBox(P, StepX, StepY, StepZ).Solid();
        di<<"Info: box b_"<<l<<" "<<P.X()<<" "<<P.Y()<<" "<<P.Z()<<" "<<StepX<<" "<<StepY<<" "<<StepZ<<"\n";
	if ( aSubvolume.IsNull())
        {
	  di << "Error: could not construct subvolume " << l << "\n";
	  return 1;
	}
	SubvolumeSolid.SetValue(l,aSubvolume);
	GProp_GProps subvolumeVProps;
	BRepGProp::VolumeProperties (SubvolumeSolid(l), subvolumeVProps);
        const Standard_Real vol = subvolumeVProps.Mass();
	di << "Info: original subvolume " << l << " volume = " << vol << "\n";
        SubvolumeVol.SetValue(l,vol);
        accumulatedVolume += vol;
	l++;
	z += StepZ;
      }
      y += StepY;
    }
    x += StepX;
  }
  di << "Info: Accumulated mesh volume = " << accumulatedVolume << "\n";

  //  
  // trim mesh to cutSolid
  //
  accumulatedVolume = 0.0;
  for ( l = 0; l < NumSubvolumes; l++ )
  {
    TopoDS_Shape copySolid = BRepBuilderAPI_Copy(cutSolid).Shape();

    // perform common
//////////#if ! defined(BRepAlgoAPI_def01)
//////////    BRepAlgoAPI_Common common(copySolid/*cutSolid*/, SubvolumeSolid(l));
//////////#else
//////////    BRepAlgo_Common common(copySolid/*cutSolid*/, SubvolumeSolid(l));
//////////#endif
//////////    if (!common.IsDone())
//////////    {
//////////      cout << "Error: could not construct a common solid " << l << endl;
//////////      return 1;
//////////    }

    TopoDS_Shape aCommonShape;
    if (IsBRepAlgoAPI) {
      di << "BRepAlgoAPI_Common common(copySolid/*cutSolid*/, SubvolumeSolid(l))" <<"\n";
      BRepAlgoAPI_Common common(copySolid/*cutSolid*/, SubvolumeSolid(l));
      if (!common.IsDone())
	{
	  di << "Error: could not construct a common solid " << l << "\n";
	  return 1;
	}
      aCommonShape = common.Shape();
    } else {
      di << "BRepAlgo_Common common(copySolid/*cutSolid*/, SubvolumeSolid(l))" <<"\n";
      BRepAlgo_Common common(copySolid/*cutSolid*/, SubvolumeSolid(l));
      if (!common.IsDone())
	{
	  di << "Error: could not construct a common solid " << l << "\n";
	  return 1;
	}
      aCommonShape = common.Shape();
    }

    // see if we have a solid
    found_solid = 0;
    TopoDS_Shape commonShape;
    //////////for (Ex.Init(common.Shape(), TopAbs_SOLID); Ex.More(); Ex.Next())
    for (Ex.Init(aCommonShape, TopAbs_SOLID); Ex.More(); Ex.Next())
    {
      TopoDS_Solid sol = TopoDS::Solid(Ex.Current());
      if (!sol.IsNull()) { commonShape = sol; found_solid++; }
    }
    if ( found_solid != 1 )
    {
      di << "Info: Common operation " << l << " produced " << found_solid << " solids" << "\n";
    }
    else
    {
      SubvolumeSolid.SetValue(l,commonShape);
      GProp_GProps subvolumeVProps;
      BRepGProp::VolumeProperties (SubvolumeSolid(l), subvolumeVProps);
      const Standard_Real vol = subvolumeVProps.Mass();
      const Standard_Boolean err = (vol > SubvolumeVol(l)) || (vol <= 0.0);
      //cout << (err? "ERROR" : "Info") << ": final subvolume " << l << " volume = " << vol << endl;
      if (err)
	di << "ERROR" << ": final subvolume " << l << " volume = " << vol << "\n";
      else
	di << "Info" << ": final subvolume " << l << " volume = " << vol << "\n";
      accumulatedVolume += vol;
      if (err)
      {
        char astr[80];
        sprintf(astr,"e_%d",l);
        DBRep::Set(astr,commonShape);
      }
    }
  }
  di << "Info: Accumulated meshed volume = " << accumulatedVolume << "\n";

  return 0;	
}

void QABugs::Commands_13(Draw_Interpretor& theCommands) {
  char *group = "QABugs";

  theCommands.Add ("OCC332", "OCC332 [wall_thickness [dia1 [dia2 [length [major_radius]]]]]", __FILE__, OCC332bug, group);
  //////theCommands.Add("OCC544", "OCC544 [[[[[wT [[[[d1 [[[d2 [[R [length]]]]]", __FILE__, OCC544, group);
  theCommands.Add("OCC544", "OCC544 [[[[[wT [[[[d1 [[[d2 [[R [length [BRepAlgoAPI/BRepAlgo = 1/0]]]]]]", __FILE__, OCC544, group);
  //////theCommands.Add("OCC817", "OCC817 result mesh_delta", __FILE__, OCC817, group);
  theCommands.Add("OCC817", "OCC817 result mesh_delta [BRepAlgoAPI/BRepAlgo = 1/0]", __FILE__, OCC817, group);

  return;
}
