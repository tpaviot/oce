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

#include <IntCurve_IConicTool.ixx>
#include <ElCLib.hxx>
#include <gp.hxx>


#define Object_To_Abs  Abs_To_Object.Inverted()
//======================================================================
#define Elips_a prm1
#define Elips_b prm2
#define Elips_c prm3

#define Elips_aa (Elips_a*Elips_a)
#define Elips_bb (Elips_b*Elips_b)
#define Elips_x0 (Axis.Location().X())
#define Elips_y0 (Axis.Location().Y())
//======================================================================
#define Hypr_a prm1
#define Hypr_b prm2
#define Hypr_aa (Hypr_a * Hypr_a)
#define Hypr_bb (Hypr_b * Hypr_b)
//======================================================================
#define Line_a prm1
#define Line_b prm2
#define Line_c prm3
//======================================================================
#define Circle_r  prm1
#define Circle_x0 prm2
#define Circle_y0 prm3
//======================================================================
#define Parab_f   prm1
#define Parab_2p  prm2

//======================================================================
IntCurve_IConicTool::IntCurve_IConicTool(void) {
//###### PLACER LE TYPE NON DEFINI ######
}


IntCurve_IConicTool::IntCurve_IConicTool(const IntCurve_IConicTool& ITool) {
  prm1=ITool.prm1;
  prm2=ITool.prm2;
  prm3=ITool.prm3;
  Axis=ITool.Axis;
  Abs_To_Object=ITool.Abs_To_Object;
  type=ITool.type;
}
//======================================================================
//======================================================================
IntCurve_IConicTool::IntCurve_IConicTool(const gp_Lin2d& Line) {
  Line.Coefficients(Line_a,Line_b,Line_c);
  Axis = gp_Ax22d(Line.Position(),Standard_True);
  type = GeomAbs_Line;
}
//======================================================================
IntCurve_IConicTool::IntCurve_IConicTool(const gp_Elips2d& Elips) {
  Elips_a = Elips.MajorRadius();
  Elips_b = Elips.MinorRadius();
  Elips_c = sqrt(Elips_a*Elips_a-Elips_b*Elips_b);
  Axis = Elips.Axis();
  Abs_To_Object.SetTransformation(gp::OX2d(),Axis.XAxis());
  type = GeomAbs_Ellipse;
}
//======================================================================
IntCurve_IConicTool::IntCurve_IConicTool(const gp_Circ2d& C) {
  Circle_r=C.Radius();
  Axis=C.Axis();
  Circle_x0=Axis.Location().X();
  Circle_y0=Axis.Location().Y();
  Abs_To_Object.SetTransformation(gp::OX2d(),Axis.XAxis());
  type = GeomAbs_Circle;
}
//======================================================================
IntCurve_IConicTool::IntCurve_IConicTool(const gp_Parab2d& P) {
  Parab_f=P.Focal();
  Parab_2p=4.0*Parab_f;
  Axis=P.Axis();
  Abs_To_Object.SetTransformation(gp::OX2d(),Axis.XAxis());
  type = GeomAbs_Parabola;
}
//======================================================================
IntCurve_IConicTool::IntCurve_IConicTool(const gp_Hypr2d& H) {
  Hypr_a = H.MajorRadius();
  Hypr_b = H.MinorRadius();
  Axis = H.Axis();
  Abs_To_Object.SetTransformation(gp::OX2d(),Axis.XAxis());
  type = GeomAbs_Hyperbola;
}
//----------------------------------------------------------------------
gp_Pnt2d IntCurve_IConicTool::Value(const Standard_Real X) const {
  switch(type) {
  case GeomAbs_Line:      return(ElCLib::LineValue(X,Axis.XAxis()));
  case GeomAbs_Ellipse:   return(ElCLib::EllipseValue(X,Axis,Elips_a,Elips_b));
  case GeomAbs_Circle:    return(ElCLib::CircleValue(X,Axis,Circle_r));
  case GeomAbs_Parabola:  return(ElCLib::ParabolaValue(X,Axis,Parab_f));
  case GeomAbs_Hyperbola: return(ElCLib::HyperbolaValue(X,Axis,Hypr_a,Hypr_b));
  default: { cout<<"### Erreur sur le  type de la courbe ###";
	    return(gp_Pnt2d(0.0,0.0)); }
  }
}

//----------------------------------------------------------------------
void IntCurve_IConicTool::D1(const Standard_Real X,
			   gp_Pnt2d& Pt,
			   gp_Vec2d& Tan) const { 
    		 
  switch(type) {
  case GeomAbs_Line:     ElCLib::LineD1(X,Axis.XAxis(),Pt,Tan); break;
  case GeomAbs_Ellipse:     ElCLib::EllipseD1(X,Axis,Elips_a,Elips_b,Pt,Tan); break;
  case GeomAbs_Circle:     ElCLib::CircleD1(X,Axis,Circle_r,Pt,Tan); break;
  case GeomAbs_Parabola:     ElCLib::ParabolaD1(X,Axis,Parab_f,Pt,Tan); break;
  case GeomAbs_Hyperbola:     ElCLib::HyperbolaD1(X,Axis,Hypr_a,Hypr_b,Pt,Tan); break;
  default: { cout<<"### Erreur sur le  type de la courbe ###"; }
  }
}

//----------------------------------------------------------------------
void IntCurve_IConicTool::D2(const Standard_Real X,
			   gp_Pnt2d& Pt,
			   gp_Vec2d& Tan,
			   gp_Vec2d& Norm) const { 
    		 
  switch(type) {
  case GeomAbs_Line:     ElCLib::LineD1(X,Axis.XAxis(),Pt,Tan); Norm.SetCoord(0.0,0.0); break;
  case GeomAbs_Ellipse:     ElCLib::EllipseD2(X,Axis,Elips_a,Elips_b,Pt,Tan,Norm); break;
  case GeomAbs_Circle:     ElCLib::CircleD2(X,Axis,Circle_r,Pt,Tan,Norm); break;
  case GeomAbs_Parabola:     ElCLib::ParabolaD2(X,Axis,Parab_f,Pt,Tan,Norm); break;
  case GeomAbs_Hyperbola:     ElCLib::HyperbolaD2(X,Axis,Hypr_a,Hypr_b,Pt,Tan,Norm); break;
  default: { cout<<"### Erreur sur le  type de la courbe ###"; }
  }			     
}
//----------------------------------------------------------------------
#define AN_ELIPS 0 
//----------------------------------------------------------------------
Standard_Real IntCurve_IConicTool::Distance(const gp_Pnt2d& ThePoint) const {

  switch(type) {
  case GeomAbs_Line:
    {
      return(Line_a*ThePoint.X()+Line_b*ThePoint.Y()+Line_c);
    }

  case GeomAbs_Ellipse:
    {
#if AN_ELIPS
      gp_Pnt2d P=ThePoint;
      P.Transform(Abs_To_Object);
      Standard_Real x=P.X();
      Standard_Real y2=P.Y() * P.Y();
      return(sqrt(y2+(x+Elips_c)*(x+Elips_c))
	     +sqrt(y2+(x-Elips_c)*(x-Elips_c))-Elips_a-Elips_a);
#else
      gp_Pnt2d P=ThePoint;
      P.Transform(Abs_To_Object);
      Standard_Real x=P.X();
      Standard_Real y=P.Y()*(Elips_a/Elips_b);
      Standard_Real d=sqrt(x*x+y*y)-Elips_a;
      return(d);
#endif
    }

  case GeomAbs_Circle:
    {
      Standard_Real Dx=Circle_x0-ThePoint.X();
      Standard_Real Dy=Circle_y0-ThePoint.Y();
      return(sqrt(Dx*Dx+Dy*Dy)-Circle_r);
    }

  case GeomAbs_Parabola:
    {    //-- Distance(X,Y) = Y**2 - 2 P X 
      gp_Pnt2d P=ThePoint;
      P.Transform(Abs_To_Object);
      return(P.Y()*P.Y()-Parab_2p*P.X());
    }
    
  case GeomAbs_Hyperbola:
    { //-- Distance(X,Y) = (X/a)**2 - (Y/b)**2 -1
      //--                 pour x>0
      //--     -(Y/b)**2 - 1  sinon ?? 
      //--     avec un gradient avec x -> Abs(x)
      gp_Pnt2d P=ThePoint;
      P.Transform(Abs_To_Object);
      if(P.X()>0.0) 
	return((P.X()*P.X())/Hypr_aa 
	       -(P.Y()*P.Y())/Hypr_bb -1.0);
      else
	return((-P.X()*P.X())/Hypr_aa 
	       -(P.Y()*P.Y())/Hypr_bb -1.0);
    }			     
  default: { cout<<"### Erreur sur le  type de la courbe ###";
	    return(0.0); }
  }
}


gp_Vec2d IntCurve_IConicTool::GradDistance(const gp_Pnt2d& ThePoint) const {

  switch(type) {
  case GeomAbs_Line: return(gp_Vec2d(Line_a,Line_b));

  case GeomAbs_Circle: {
    gp_Pnt2d P=ThePoint;
    P.Transform(Abs_To_Object);
    Standard_Real Gradx=0.0;
    Standard_Real Grady=0.0;
    Standard_Real x=P.X();
    Standard_Real y=P.Y();
    Standard_Real temp1=sqrt(y*y+x*x);
    if(temp1) {
      Gradx=x/temp1;
      Grady=y/temp1;
    }
    gp_Vec2d Gradient(Gradx,Grady);
    Gradient.Transform(Object_To_Abs);
    return(Gradient);
  }
  case GeomAbs_Ellipse: {
#if AN_ELIPS
    gp_Pnt2d P=ThePoint;
    P.Transform(Abs_To_Object);
    Standard_Real Gradx=0.0;
    Standard_Real Grady=0.0;
    Standard_Real x=P.X();
    Standard_Real y=P.Y();
    Standard_Real xmc=x-Elips_c;
    Standard_Real xpc=x+Elips_c;
    Standard_Real temp1=sqrt(y*y+xmc*xmc);
    Standard_Real temp2=sqrt(y*y+xpc*xpc);
    if(temp2) {
      Gradx=xpc/temp2;
      Grady=y/temp2;
    }
    if(temp1) {
      Gradx+=xmc/temp1;
      Grady+=y/temp1;
    }
    gp_Vec2d Gradient(Gradx,Grady);
    Gradient.Transform(Object_To_Abs);
    return(Gradient);
#else
    gp_Pnt2d P=ThePoint;
    P.Transform(Abs_To_Object);
    Standard_Real Gradx=0.0;
    Standard_Real Grady=0.0;
    Standard_Real x=P.X();
    Standard_Real y=P.Y()*(Elips_a/Elips_b);
    Standard_Real temp1=sqrt(y*y+x*x);
    if(temp1) {
      Gradx=x/temp1;
      Grady=(y*(Elips_a/Elips_b))/temp1;
    }
    gp_Vec2d Gradient(Gradx,Grady);
    Gradient.Transform(Object_To_Abs);
    return(Gradient);
#endif
  }
    
  case GeomAbs_Parabola: {    //-- Distance(X,Y) = Y**2 - 2 P X 
    gp_Pnt2d P=ThePoint;
    P.Transform(Abs_To_Object);
    gp_Vec2d Gradient(-Parab_2p,P.Y()+P.Y());
    Gradient.Transform(Object_To_Abs);
    return(Gradient);
  }
  case GeomAbs_Hyperbola: { //-- Distance(X,Y) = (X/a)**2 - (Y/b)**2 -1
    gp_Pnt2d P=ThePoint;
    P.Transform(Abs_To_Object);
    //--### la Branche a X negatif doit ramener vers les X positifs
    gp_Vec2d Gradient(2.0*Abs(P.X())/Hypr_aa,-2.0*P.Y()/Hypr_bb);
    Gradient.Transform(Object_To_Abs);
    return(Gradient);
  }
  default: { cout<<"### Erreur sur le  type de la courbe ###";
	    return(gp_Vec2d(0.0,0.0)); }
  }
}


Standard_Real IntCurve_IConicTool::FindParameter(const gp_Pnt2d& P) const {

  Standard_Real Param=0;
  
  switch(type) {
    
  case GeomAbs_Line: 
    Param=ElCLib::LineParameter(Axis.XAxis(),P);
    break;
    
  case GeomAbs_Circle:
    Param=ElCLib::CircleParameter(Axis,P);
    if(Param<0.0) { Param+=M_PI+M_PI; }
    break;
    
  case GeomAbs_Ellipse: {
    Param=ElCLib::EllipseParameter(Axis
				   ,Elips_a
				   ,Elips_b
				   ,P);
    if (Param < 0.0) { Param+=M_PI+M_PI; }
    break;
  }
    
  case GeomAbs_Parabola: {
    Param=ElCLib::ParabolaParameter(Axis,P);
    break;
  }
  case GeomAbs_Hyperbola: { 
    Param=ElCLib::HyperbolaParameter(Axis
				     ,Hypr_a
				     ,Hypr_b
				     ,P);
    break;
  }
  default:
    break;
  }
  
  return(Param);
}


