// Created on: 1994-02-18
// Created by: Remi LEQUETTE
// Copyright (c) 1994-1999 Matra Datavision
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


#include <Standard_Stream.hxx>
#include <BRepTest.hxx>
#include <Draw_Interpretor.hxx>
#include <Draw_Appli.hxx>
#include <DBRep.hxx>
#include <BRepGProp.hxx>
#include <TopoDS_Shape.hxx>
#include <GProp_PrincipalProps.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>

#include <Draw_Axis3D.hxx>
#include <Precision.hxx>
#include <OSD_Chronometer.hxx>
#include <Geom_Surface.hxx>
#include <DrawTrSurf.hxx>
#include <Geom_Plane.hxx>
#include <gp_Pln.hxx>

#ifdef WNT
Standard_IMPORT Draw_Viewer dout;
#endif


Standard_Integer props(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 2) {
    di << "Use: " << a[0] << " shape [epsilon] [c[losed]] [x y z]" << "\n";
    di << "Compute properties of the shape" << "\n";
    di << "The epsilon, if given, defines relative precision of computation" << "\n";
    di << "The \"closed\" flag, if present, do computation only closed shells of the shape" << "\n";
    di << "The centroid coordinates will be put to DRAW variables x y z (if given)\n" << "\n";
    return 1;
  }

  TopoDS_Shape S = DBRep::Get(a[1]);
  if (S.IsNull()) return 0;

  GProp_GProps G;

  Standard_Boolean onlyClosed = Standard_False;
  Standard_Real eps = 1.0;
  Standard_Boolean witheps = Standard_False;
  if((n > 2 && *a[2]=='c') || (n > 3 && *a[3]=='c')) onlyClosed = Standard_True;
  if(n > 2 && *a[2]!='c' && n != 5) {eps = Draw::Atof (a[2]); witheps = Standard_True;}

  if (witheps){
    if (Abs(eps) < Precision::Angular()) return 2;
    if (*a[0] == 'l')
      BRepGProp::LinearProperties(S,G);
    else if (*a[0] == 's')
      eps = BRepGProp::SurfaceProperties(S,G,eps);
    else 
      eps = BRepGProp::VolumeProperties(S,G,eps,onlyClosed);
  }
  else {
    if (*a[0] == 'l')
      BRepGProp::LinearProperties(S,G);
    else if (*a[0] == 's')
      BRepGProp::SurfaceProperties(S,G);
    else 
      BRepGProp::VolumeProperties(S,G,onlyClosed);
  }
  
  gp_Pnt P = G.CentreOfMass();
  gp_Mat I = G.MatrixOfInertia();

  if (n >= 5) {
    Standard_Integer shift =  n - 5;
    Draw::Set(a[shift+2],P.X());
    Draw::Set(a[shift+3],P.Y());
    Draw::Set(a[shift+4],P.Z());
  }
	    
  Standard_SStream aSStream1;
  aSStream1 << "\n\n";
  aSStream1 << "Mass : " << setw(15) << G.Mass() << "\n" << "\n";
  if(witheps && *a[0] != 'l') aSStream1 << "Relative error of mass computation : " <<  setw(15) << eps <<  "\n" << "\n";
  
  aSStream1 << "Center of gravity : \n";
  aSStream1 << "X = " << setw(15) << P.X() << "\n";
  aSStream1 << "Y = " << setw(15) << P.Y() << "\n";
  aSStream1 << "Z = " << setw(15) << P.Z() << "\n";
  aSStream1 << "\n";
  
  aSStream1 << "Matrix of Inertia : \n";
  aSStream1 << setw(15) << I(1,1);
  aSStream1 << " " << setw(15) << I(1,2);
  aSStream1 << " " << setw(15) << I(1,3) << "\n";
  aSStream1 << setw(15) << I(2,1);
  aSStream1 << " " << setw(15) << I(2,2);
  aSStream1 << " " << setw(15) << I(2,3) << "\n";
  aSStream1 << setw(15) << I(3,1);
  aSStream1 << " " << setw(15) << I(3,2);
  aSStream1 << " " << setw(15) << I(3,3) << "\n";
  aSStream1 << "\n";
  aSStream1 << ends;
  di << aSStream1;

  GProp_PrincipalProps Pr = G.PrincipalProperties();

  Standard_Real Ix,Iy,Iz;
  Pr.Moments(Ix,Iy,Iz);
  
  Standard_SStream aSStream2;
  aSStream2 << "Moments : \n";
  aSStream2 << "IX = " << setw(15) << Ix << "\n";
  aSStream2 << "IY = " << setw(15) << Iy << "\n";
  aSStream2 << "IZ = " << setw(15) << Iz << "\n";
  aSStream2 << "\n";
  aSStream2 << ends;
  di << aSStream2;

  //if (n == 2) {  
    gp_Ax2 axes(P,Pr.ThirdAxisOfInertia(),Pr.FirstAxisOfInertia());
    
    Handle(Draw_Axis3D) Dax = new Draw_Axis3D(axes,Draw_orange,30);
    dout << Dax;
  //}

  return 0;
}


Standard_Integer vpropsgk(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 2) {
    di << "Use: " << a[0] << " shape epsilon closed span mode [x y z]" << "\n";
    di << "Compute properties of the shape" << "\n";
    di << "The epsilon defines relative precision of computation" << "\n";
    di << "The \"closed\" flag, if equal 1, causes computation only closed shells of the shape" << "\n";
    di << "The \"span\" flag, if equal 1, says that computation is performed on spans" << "\n";
    di << "      This option makes effect only for BSpline surfaces." << "\n";
    di << "mode can be 0 - only volume calculations" << "\n";
    di << "            1 - volume and gravity center" << "\n";
    di << "            2 - volume, gravity center and matrix of inertia" << "\n";
    di << "The centroid coordinates will be put to DRAW variables x y z (if given)\n" << "\n";
    return 1;
  }

  if ( n > 2 && n < 6) {
    di << "Wrong arguments" << "\n";
    return 1;
  }

  TopoDS_Shape S = DBRep::Get(a[1]);
  if (S.IsNull()) return 0;

  GProp_GProps G;

  Standard_Boolean onlyClosed  = Standard_False;
  Standard_Boolean isUseSpan   = Standard_False;
  Standard_Boolean CGFlag = Standard_False;
  Standard_Boolean IFlag = Standard_False;
  Standard_Real    eps         = 1.e-3;
//Standard_Real    aDefaultTol = 1.e-3;
  Standard_Integer mode = 0;

  eps = Draw::Atof(a[2]);
  mode = Draw::Atoi(a[3]);
  if(mode > 0) onlyClosed = Standard_True;
  mode = Draw::Atoi(a[4]);
  if(mode > 0) isUseSpan = Standard_True;

  mode = Draw::Atoi(a[5]);
  if(mode == 1 || mode == 3) CGFlag = Standard_True;
  if(mode == 2 || mode == 3) IFlag = Standard_True;

  //OSD_Chronometer aChrono;

  //aChrono.Reset();
  //aChrono.Start();
  eps = BRepGProp::VolumePropertiesGK(S, G, eps, onlyClosed, isUseSpan, CGFlag, IFlag);
  //aChrono.Stop();

  Standard_SStream aSStream0;
  Standard_Integer anOutWidth = 24;

  aSStream0.precision(15);
  aSStream0 << "\n\n";
  aSStream0 << "Mass : " << setw(anOutWidth) << G.Mass() << "\n" << "\n";
  aSStream0 << "Relative error of mass computation : " <<  setw(anOutWidth) << eps <<  "\n" << "\n";
  aSStream0 << ends;
  di << aSStream0;

  if(CGFlag || IFlag) {
    Standard_SStream aSStream1;
    gp_Pnt P = G.CentreOfMass();
    if (n > 6) {
      Draw::Set(a[6],P.X());
    }
    if (n > 7) {
      Draw::Set(a[7],P.Y());
    }
    if (n > 8) {
      Draw::Set(a[8],P.Z());
    }
  
    aSStream1.precision(15);
    aSStream1 << "Center of gravity : \n";
    aSStream1 << "X = " << setw(anOutWidth) << P.X() << "\n";
    aSStream1 << "Y = " << setw(anOutWidth) << P.Y() << "\n";
    aSStream1 << "Z = " << setw(anOutWidth) << P.Z() << "\n";
    aSStream1 << "\n";
 
    if(IFlag) {
      gp_Mat I = G.MatrixOfInertia();

      aSStream1 << "Matrix of Inertia : \n";
      aSStream1 << setw(anOutWidth) << I(1,1);
      aSStream1 << " " << setw(anOutWidth) << I(1,2);
      aSStream1 << " " << setw(anOutWidth) << I(1,3) << "\n";
      aSStream1 << setw(anOutWidth) << I(2,1);
      aSStream1 << " " << setw(anOutWidth) << I(2,2);
      aSStream1 << " " << setw(anOutWidth) << I(2,3) << "\n";
      aSStream1 << setw(anOutWidth) << I(3,1);
      aSStream1 << " " << setw(anOutWidth) << I(3,2);
      aSStream1 << " " << setw(anOutWidth) << I(3,3) << "\n";
      aSStream1 << "\n";
    }
    aSStream1 << ends;
    di << aSStream1;
  }

  if(IFlag) {

    GProp_PrincipalProps Pr = G.PrincipalProperties();

    Standard_Real Ix,Iy,Iz;
    Pr.Moments(Ix,Iy,Iz);
    gp_Pnt P = G.CentreOfMass();
  
    Standard_SStream aSStream2;

    aSStream2.precision(15);
    aSStream2 << "Moments : \n";
    aSStream2 << "IX = " << setw(anOutWidth) << Ix << "\n";
    aSStream2 << "IY = " << setw(anOutWidth) << Iy << "\n";
    aSStream2 << "IZ = " << setw(anOutWidth) << Iz << "\n";
    aSStream2 << "\n";
    aSStream2 << "\n";
    aSStream2 << ends;
    di << aSStream2;

    gp_Ax2 axes(P,Pr.ThirdAxisOfInertia(),Pr.FirstAxisOfInertia());
    
    Handle(Draw_Axis3D) Dax = new Draw_Axis3D(axes,Draw_orange,30);
    dout << Dax;
  }
  return 0;
}


//=======================================================================
//function : GPropCommands
//purpose  : 
//=======================================================================

void  BRepTest::GPropCommands(Draw_Interpretor& theCommands)
{
  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;

  DBRep::BasicCommands(theCommands);

  const char* g = "Global properties";
  theCommands.Add("lprops",
		  "lprops name [epsilon] [x y z] : compute linear properties",
		  __FILE__,
		  props,
		  g);
  theCommands.Add("sprops",
		  "sprops name [epsilon] [x y z] : compute surfacic properties",
		  __FILE__,
		  props,
		  g);
  theCommands.Add("vprops",
		  "vprops name [epsilon] [c[losed]] [x y z] : compute volumic properties",
		  __FILE__,
		  props,
		  g);

  theCommands.Add("vpropsgk",
		  "vpropsgk name epsilon closed span mode [x y z] : compute volumic properties",
		  __FILE__,
		  vpropsgk,
		  g);
}
