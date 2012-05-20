// Created on: 1997-12-19
// Created by: Roman BORISOV /Philippe MANGIN
// Copyright (c) 1997-1999 Matra Datavision
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


#include <stdio.h>

#include <GeomFill_CorrectedFrenet.ixx>
#include <GeomAbs_CurveType.hxx>
#include <Adaptor3d_HCurve.hxx>
#include <gp_Trsf.hxx>
#include <Precision.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <Law_Interpolate.hxx>
#include <TColStd_SequenceOfReal.hxx>
#include <gp_Vec2d.hxx>
#include <BndLib_Add3dCurve.hxx>
#include <Bnd_Box.hxx>
#include <GeomLib.hxx>
#include <Law_Composite.hxx>
#include <Law_Constant.hxx>
#include <Law_BSpFunc.hxx>
#include <Law_BSpline.hxx>
#include <GeomFill_SnglrFunc.hxx>
//Patch
#include <Geom_Plane.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TColgp_HArray1OfPnt.hxx>

#ifdef DEB
static Standard_Boolean Affich=0;
#endif

#ifdef DRAW
static Standard_Integer CorrNumber = 0;
#include <Draw_Appli.hxx>
#include <DrawTrSurf.hxx>
#include <Draw_Segment2D.hxx>
//#include <Draw.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#endif

#ifdef DRAW 
static void draw(const Handle(Law_Function)& law)
{
  Standard_Real Step, u, v, tmin;
  Standard_Integer NbInt, i, j, jmax;
  NbInt = law->NbIntervals(GeomAbs_C3);
  TColStd_Array1OfReal Int(1, NbInt+1);
  law->Intervals(Int, GeomAbs_C3);
  gp_Pnt2d old;
  Handle(Draw_Segment2D) tg2d;  

  for(i = 1; i <= NbInt; i++){
    tmin = Int(i);
    Step = (Int(i+1)-Int(i))/4;
    if (i == NbInt) jmax = 4;
    else jmax = 3;
    for (j=1; j<=jmax; j++) { 
      u =  tmin + (j-1)*Step;
      v = law->Value(u);
      gp_Pnt2d point2d(u,v);
      if ((i>1)||(j>1)) {
	tg2d = new Draw_Segment2D(old, point2d,Draw_kaki);
	dout << tg2d;
      }
      old = point2d;
    }
  }
  dout.Flush();
}
#endif

//===============================================================
// Function : smoothlaw
// Purpose : to smooth a law : Reduce the number of knots
//===============================================================
static void smoothlaw(Handle(Law_BSpline)& Law,
		      const Handle(TColStd_HArray1OfReal)& Points,
		      const Handle(TColStd_HArray1OfReal)& Param,
		      const Standard_Real Tol) 
{
  Standard_Real tol, d;
  Standard_Integer ii, Nbk;
  Standard_Boolean B, Ok;
  Handle(Law_BSpline) BS = Law->Copy();

  Nbk = BS->NbKnots();
  tol = Tol/10;
  Ok = Standard_False;
  
  for (ii=Nbk-1; ii>1; ii--) { // Une premiere passe tolerance serres
    B = BS->RemoveKnot(ii, 0, tol);
    if (B) Ok = Standard_True;
  }

  if (Ok) { // controle
    tol = 0.;
    for (ii=1; ii<=Param->Length() && Ok; ii++) {
      d = Abs(BS->Value(Param->Value(ii))-Points->Value(ii));
      if (d > tol) tol = d;
      Ok = (tol <= Tol);
    }
    if (Ok) 
      tol = (Tol-tol)/2;
    else {
#if DEB
      cout << "smooth law echec" << endl;
#endif
      return; // Echec
    } 
  }
  else {
    tol = Tol/2;
  }

 
 if (Ok) Law = BS;

  Ok = Standard_False; // Une deuxieme passe tolerance desserre
  Nbk = BS->NbKnots();
  for (ii=Nbk-1; ii>1; ii--) { 
    B = BS->RemoveKnot(ii, 0, tol);
    if (B) Ok = Standard_True;
  }

  if (Ok) { // controle
    tol = 0.;
    for (ii=1; ii<=Param->Length() && Ok; ii++) {
      d = Abs(BS->Value(Param->Value(ii))-Points->Value(ii));
      if (d > tol) tol = d;
      Ok = (tol <= Tol);
    }
    if (!Ok) {
#if DEB
      cout << "smooth law echec" << endl;
#endif
    } 
  }
  if (Ok) Law = BS;

#if DEB
  if (Affich) {
    cout << "Knots Law : " << endl;
    for (ii=1; ii<=BS->NbKnots(); ii++) {
      cout << ii << " : " << BS->Knot(ii) << endl;
    }
  }
#endif
}

//===============================================================
// Function : FindPlane
// Purpose : 
//===============================================================
static Standard_Boolean FindPlane ( const Handle(Adaptor3d_HCurve)& c,
				    Handle( Geom_Plane )& P )
{
  Standard_Boolean found = Standard_True;
  Handle(TColgp_HArray1OfPnt) TabP;

  switch (c->GetType()) {
    
  case GeomAbs_Line:
    {
      found = Standard_False;
    }
    break;
    
  case GeomAbs_Circle:
    P = new Geom_Plane(gp_Ax3(c->Circle().Position()));
    break;
    
  case GeomAbs_Ellipse:
    P = new Geom_Plane(gp_Ax3(c->Ellipse().Position()));
    break;
    
  case GeomAbs_Hyperbola:
    P = new Geom_Plane(gp_Ax3(c->Hyperbola().Position()));
    break;
    
  case GeomAbs_Parabola:
    P = new Geom_Plane(gp_Ax3(c->Parabola().Position()));
    break;
    
  case GeomAbs_BezierCurve:
    {
      Handle(Geom_BezierCurve) GC = c->Bezier();
      Standard_Integer nbp = GC->NbPoles();
      if ( nbp < 2) 
	found = Standard_False;
      else if ( nbp == 2) {
	found = Standard_False;
      }
      else {
	TabP = new (TColgp_HArray1OfPnt) (1, nbp);
	GC->Poles(TabP->ChangeArray1());
      }
    }
    break;
    
  case GeomAbs_BSplineCurve:
    {
      Handle(Geom_BSplineCurve) GC = c->BSpline();
      Standard_Integer nbp = GC->NbPoles();
      if ( nbp < 2) 
	found = Standard_False;
      else if ( nbp == 2) {
	found = Standard_False;
      }
      else {
	TabP = new (TColgp_HArray1OfPnt) (1, nbp);
	GC->Poles(TabP->ChangeArray1());
      }
    }
    break;
    
  default:
    { // On utilise un echantillonage
      Standard_Integer nbp = 15 + c->NbIntervals(GeomAbs_C3);
      Standard_Real f, l, t, inv;
      Standard_Integer ii;
      f = c->FirstParameter();
      l = c->LastParameter();
      inv = 1./(nbp-1);
      for (ii=1; ii<=nbp; ii++) {
	t = ( f*(nbp-ii) + l*(ii-1));
	t *= inv;
	TabP->SetValue(ii, c->Value(t));
      }
    }
  }
  
  if (! TabP.IsNull()) { // Recherche d'un plan moyen et controle
    Standard_Boolean issingular;
    gp_Ax2 inertia;
    GeomLib::AxeOfInertia(TabP->Array1(), inertia, issingular);
    if (issingular) {
      found = Standard_False;
    }
    else {
      P = new Geom_Plane(inertia);
    }
    if (found)
      {
	//control = Controle(TabP->Array1(), P,  myTolerance);
//	Standard_Boolean isOnPlane;
	Standard_Real a,b,c,d, dist;
	Standard_Integer ii;
	P->Coefficients(a,b,c,d);
	for (ii=1; ii<=TabP->Length() && found; ii++) {
	  const gp_XYZ& xyz = TabP->Value(ii).XYZ();
	  dist = a*xyz.X() + b*xyz.Y() + c*xyz.Z() + d;
	  found = (Abs(dist) <= Precision::Confusion());
	}
	return found;
      }
  }

  return found;
}

//===============================================================
// Function : 
// Purpose :
//===============================================================
GeomFill_CorrectedFrenet::GeomFill_CorrectedFrenet() 
 : isFrenet(Standard_False)
{
  frenet = new GeomFill_Frenet();
}

Handle(GeomFill_TrihedronLaw) GeomFill_CorrectedFrenet::Copy() const
{
  Handle(GeomFill_CorrectedFrenet) copy = new (GeomFill_CorrectedFrenet)();
  if (!myCurve.IsNull()) copy->SetCurve(myCurve);
  return copy;
}

 void GeomFill_CorrectedFrenet::SetCurve(const Handle(Adaptor3d_HCurve)& C) 
{
 
  GeomFill_TrihedronLaw::SetCurve(C);
  if (! C.IsNull()) { 
    frenet->SetCurve(C);
 
    GeomAbs_CurveType type;
    type = C->GetType();
    switch  (type) {
    case GeomAbs_Circle:
    case GeomAbs_Ellipse:
    case GeomAbs_Hyperbola:
    case GeomAbs_Parabola:
    case GeomAbs_Line:
      {
	// No probleme isFrenet
	isFrenet = Standard_True;
      }
     default :
       { 
	 // We have to search singulaties
	 isFrenet = Standard_True;
	 Init(); 
       }
    }
  }
}


//===============================================================
// Function : Init
// Purpose : Compute angle's law
//===============================================================
 void GeomFill_CorrectedFrenet::Init()
{ 
  EvolAroundT = new Law_Composite();  
  Standard_Integer NbI = frenet->NbIntervals(GeomAbs_C0), i;
  TColStd_Array1OfReal T(1, NbI + 1);
  frenet->Intervals(T, GeomAbs_C0);
  Handle(Law_Function) Func;
  //OCC78
  TColStd_SequenceOfReal SeqPoles, SeqAngle; 
  TColgp_SequenceOfVec SeqTangent, SeqNormal; 
  
  gp_Vec Tangent, Normal, BN;
  frenet->D0(myTrimmed->FirstParameter(), Tangent, Normal, BN);
  Standard_Integer NbStep;
//  Standard_Real StartAng = 0, AvStep, Step, t;
  Standard_Real StartAng = 0, AvStep, Step;

#if DRAW
  Standard_Real t;

  if (Affich) { // Display the curve C'^C''(t)
    GeomFill_SnglrFunc CS(myCurve);
    NbStep = 99;
    AvStep = (myTrimmed->LastParameter() - 
	      myTrimmed->FirstParameter())/NbStep;
    TColgp_Array1OfPnt TabP(1, NbStep+1);
 
    TColStd_Array1OfReal TI(1, NbStep+1);
    TColStd_Array1OfInteger M(1,NbStep+1); 
    M.Init(1);
    M(1) = M(NbStep+1) = 2;
    for (i=1; i<=NbStep+1; i++) {
      t = (myTrimmed->FirstParameter()+ (i-1)*AvStep);
      CS.D0(t, TabP(i));
      TI(i) = t;
    }
    char tname[100];
    Standard_CString name = tname ;
    sprintf(name,"Binorm_%d", ++CorrNumber);
    Handle(Geom_BSplineCurve) BS = new 
      (Geom_BSplineCurve) (TabP, TI, M, 1);
//    DrawTrSurf::Set(&name[0], BS);
    DrawTrSurf::Set(name, BS);
  }
#endif
 

  NbStep = 10;
  AvStep = (myTrimmed->LastParameter() - myTrimmed->FirstParameter())/NbStep;  
  for(i = 1; i <= NbI; i++) {
    NbStep = Max(Standard_Integer((T(i+1) - T(i))/AvStep), 3);
    Step = (T(i+1) - T(i))/NbStep;
    if(!InitInterval(T(i), T(i+1), Step, StartAng, Tangent, Normal, AT, AN, Func, SeqPoles, SeqAngle, SeqTangent, SeqNormal))
      if(isFrenet) isFrenet = Standard_False;
    Handle(Law_Composite)::DownCast(EvolAroundT)->ChangeLaws().Append(Func);
  }
  if(myTrimmed->IsPeriodic()) 
    Handle(Law_Composite)::DownCast(EvolAroundT)->SetPeriodic();

  TLaw = EvolAroundT;
  //OCC78
  Standard_Integer iEnd = SeqPoles.Length();
  HArrPoles = new TColStd_HArray1OfReal(1, iEnd);
  HArrAngle = new TColStd_HArray1OfReal(1, iEnd);
  HArrTangent = new TColgp_HArray1OfVec(1, iEnd);
  HArrNormal = new TColgp_HArray1OfVec(1, iEnd);
  for(i = 1; i <= iEnd; i++){
    HArrPoles->ChangeValue(i) = SeqPoles(i); 
    HArrAngle->ChangeValue(i) = SeqAngle(i); 
    HArrTangent->ChangeValue(i) = SeqTangent(i); 
    HArrNormal->ChangeValue(i) = SeqNormal(i); 
  };

#if DRAW
  if (Affich) {
    draw(EvolAroundT);
  }
#endif
}

//===============================================================
// Function : InitInterval
// Purpose : Compute the angle law on a span
//===============================================================
 Standard_Boolean GeomFill_CorrectedFrenet::
 InitInterval(const Standard_Real First, const Standard_Real Last, 
	      const Standard_Real Step, 
	      Standard_Real& startAng, gp_Vec& prevTangent, 
	      gp_Vec& prevNormal, gp_Vec& aT, gp_Vec& aN, 
	      Handle(Law_Function)& FuncInt,
	      TColStd_SequenceOfReal& SeqPoles,
	      TColStd_SequenceOfReal& SeqAngle,
	      TColgp_SequenceOfVec& SeqTangent,
	      TColgp_SequenceOfVec& SeqNormal) const
{
  Bnd_Box Boite;
  gp_Vec Tangent, Normal, BN, cross;
  TColStd_SequenceOfReal parameters;
  TColStd_SequenceOfReal EvolAT;
  Standard_Real Param = First, LengthMin, L, norm;
  Standard_Boolean isZero = Standard_True, isConst = Standard_True;
  Standard_Integer i;
  gp_Pnt PonC;
  gp_Vec D1;

  frenet->SetInterval(First, Last); //To have the rigth evaluation at bounds
  GeomFill_SnglrFunc CS(myCurve);
  BndLib_Add3dCurve::Add(CS, First, Last, 1.e-2, Boite);
  LengthMin = Boite.GetGap()*1.e-4;
    
  aT = gp_Vec(0, 0, 0);
  aN = gp_Vec(0, 0, 0);   

  Standard_Real angleAT = 0.0 , currParam, currStep = Step;

  Handle( Geom_Plane ) aPlane;
  Standard_Boolean isPlanar = FindPlane( myCurve, aPlane );

  i = 1;
  currParam = Param;
  Standard_Real DLast = Last - Precision::PConfusion();

  while (Param < Last) {
    if (currParam > DLast) {
      currStep = DLast - Param;
      currParam = Last;
    }
    if (isPlanar)
      currParam = Last;

    frenet->D0(currParam, Tangent, Normal, BN);
    if (prevTangent.Angle(Tangent) < M_PI/3 || i == 1) {
      parameters.Append(currParam);
      //OCC78
      SeqPoles.Append(Param);      
      SeqAngle.Append(i > 1? EvolAT(i-1) : startAng);   
      SeqTangent.Append(prevTangent); 
      SeqNormal.Append(prevNormal);   
      angleAT = CalcAngleAT(Tangent,Normal,prevTangent,prevNormal);

      if(isConst && i > 1)
        if(Abs(angleAT) > Precision::PConfusion())
          isConst = Standard_False;

      angleAT += (i > 1) ? EvolAT(i-1) : startAng; 
      EvolAT.Append(angleAT);
      prevNormal = Normal;

      if(isZero)
        if(Abs(angleAT) > Precision::PConfusion())
          isZero = Standard_False;
      
      aT += Tangent;
      cross = Tangent.Crossed(Normal);
      aN.SetLinearForm(Sin(angleAT), cross,
		       1 - Cos(angleAT), Tangent.Crossed(cross),
		       Normal+aN);
      prevTangent = Tangent;
      Param = currParam;
      i++;

      //Evaluate the Next step
      CS.D1(Param, PonC, D1);
      L = Max(PonC.XYZ().Modulus()/2, LengthMin);
      norm = D1.Magnitude(); 
      if (norm < Precision::Confusion()) {
	norm = Precision::Confusion();
      }
      currStep = L / norm;
      if  (currStep > Step) currStep = Step;//default value
    }
    else 
      currStep /= 2; // Step too long !

    currParam = Param + currStep;    
  }

  if (! isPlanar)
    {
      aT /= parameters.Length() - 1;
      aN /= parameters.Length() - 1;
    }
  startAng = angleAT;

// Interpolation
  if (isConst || isPlanar) {
    FuncInt = new Law_Constant();
    Handle(Law_Constant)::DownCast(FuncInt)->Set( angleAT, First, Last );
  }

  else {
    Standard_Integer Length = parameters.Length();
    Handle(TColStd_HArray1OfReal) pararr = 
      new TColStd_HArray1OfReal(1, Length);
    Handle(TColStd_HArray1OfReal) angleATarr = 
      new TColStd_HArray1OfReal(1, Length);
    

    for (i = 1; i <= Length; i++) {
      pararr->ChangeValue(i) = parameters(i);
      angleATarr->ChangeValue(i) = EvolAT(i);
    }

#if DEB
    if (Affich) {
      cout<<"NormalEvolution"<<endl; 
      for (i = 1; i <= Length; i++) {
	cout<<"("<<pararr->Value(i)<<", "<<angleATarr->Value(i)<<")" << endl;
      }
      cout<<endl;
    } 
#endif

    Law_Interpolate lawAT(angleATarr, pararr, 
			  Standard_False, Precision::PConfusion());
    lawAT.Perform();
    Handle(Law_BSpline) BS = lawAT.Curve();
    smoothlaw(BS, angleATarr, pararr, 0.1);

    FuncInt = new Law_BSpFunc(BS, First, Last);
  }
  return isZero;
}
//===============================================================
// Function : CalcAngleAT (OCC78)
// Purpose : Calculate angle of rotation of trihedron normal and its derivatives relative 
//           at any position on his curve
//===============================================================
Standard_Real GeomFill_CorrectedFrenet::CalcAngleAT(const gp_Vec& Tangent, const gp_Vec& Normal,  
						    const gp_Vec& prevTangent, const gp_Vec& prevNormal) const
{
  Standard_Real angle;
  gp_Vec Normal_rot, cross;
  angle = Tangent.Angle(prevTangent);
  if (Abs(angle) > Precision::Angular()) {
    cross = Tangent.Crossed(prevTangent).Normalized();
    Normal_rot = Normal + sin(angle)*cross.Crossed(Normal) + 
      (1 - cos(angle))*cross.Crossed(cross.Crossed(Normal));
  }
  else
    Normal_rot = Normal;
  Standard_Real angleAT = Normal_rot.Angle(prevNormal);
  if(angleAT > Precision::Angular() && M_PI - angleAT > Precision::Angular())
    if (Normal_rot.Crossed(prevNormal).IsOpposite(prevTangent, Precision::Angular())) 
      angleAT = -angleAT;
  return angleAT;
};
//===============================================================
// Function : ... (OCC78)
// Purpose : This family of functions produce conversion of angle utility
//===============================================================
static Standard_Real corrPI_2PI(Standard_Real Ang){
  return Ang = (Ang >= 0.0? Ang: 2*M_PI+Ang);
};
static Standard_Real corr2PI_PI(Standard_Real Ang){
  return Ang = (Ang < M_PI? Ang: Ang-2*M_PI);
};
static Standard_Real diffAng(Standard_Real A, Standard_Real Ao){
  Standard_Real dA = (A-Ao) - Floor((A-Ao)/2.0/M_PI)*2.0*M_PI;
  return dA = dA >= 0? corr2PI_PI(dA): -corr2PI_PI(-dA);
};
//===============================================================
// Function : CalcAngleAT (OCC78)
// Purpose : Calculate angle of rotation of trihedron normal and its derivatives relative 
//           at any position on his curve
//===============================================================
Standard_Real GeomFill_CorrectedFrenet::GetAngleAT(const Standard_Real Param) const{
  // Search index of low margin from poles of TLaw by bisection method
  Standard_Integer iB = 1, iE = HArrPoles->Length(), iC = (iE+iB)/2;
  if(Param == HArrPoles->Value(iB)) return TLaw->Value(Param);
  if(Param > HArrPoles->Value(iE)) iC = iE; 
  if(iC < iE){
    while(!(HArrPoles->Value(iC) <= Param && Param <= HArrPoles->Value(iC+1))){
      if(HArrPoles->Value(iC) < Param) iB = iC; else iE = iC;
      iC = (iE+iB)/2;
    };
    if(HArrPoles->Value(iC) == Param || Param == HArrPoles->Value(iC+1)) return TLaw->Value(Param);
  };
  //  Calculate differenciation between apporoximated and local values of AngleAT
  Standard_Real AngP = TLaw->Value(Param), AngPo = HArrAngle->Value(iC), dAng = AngP - AngPo;
  gp_Vec Tangent, Normal, BN;
  frenet->D0(Param, Tangent, Normal, BN);
  Standard_Real DAng = CalcAngleAT(Tangent, Normal, HArrTangent->Value(iC), HArrNormal->Value(iC));
  Standard_Real DA = diffAng(DAng,dAng);
  // The correction (there is core of OCC78 bug)
  if(Abs(DA) > M_PI/2.0){
    AngP = AngPo + DAng;
  };
  return AngP;
};
//===============================================================
// Function : D0
// Purpose :
//===============================================================
 Standard_Boolean GeomFill_CorrectedFrenet::D0(const Standard_Real Param,
					       gp_Vec& Tangent,
					       gp_Vec& Normal,
					       gp_Vec& BiNormal)
{
  frenet->D0(Param, Tangent, Normal, BiNormal);
  if (isFrenet) return Standard_True;
 
  Standard_Real angleAT; 
  //angleAT = TLaw->Value(Param);
  angleAT = GetAngleAT(Param); //OCC78
  
// rotation around Tangent
  gp_Vec cross;
  cross =  Tangent.Crossed(Normal);
  Normal.SetLinearForm(Sin(angleAT), cross,
		       (1 - Cos(angleAT)), Tangent.Crossed(cross),
		       Normal);
  BiNormal = Tangent.Crossed(Normal);

  return Standard_True;
}

//===============================================================
// Function : D1
// Purpose :
//===============================================================

 Standard_Boolean GeomFill_CorrectedFrenet::D1(const Standard_Real Param,
					       gp_Vec& Tangent,
					       gp_Vec& DTangent,
					       gp_Vec& Normal,
					       gp_Vec& DNormal,
					       gp_Vec& BiNormal,
					       gp_Vec& DBiNormal) 
{  
  frenet->D1(Param, Tangent, DTangent, Normal, DNormal, BiNormal, DBiNormal);
  if (isFrenet) return Standard_True;

  Standard_Real angleAT, d_angleAT;
  Standard_Real sina, cosa; 

  TLaw->D1(Param, angleAT, d_angleAT);
  angleAT = GetAngleAT(Param); //OCC78

  gp_Vec cross, dcross, tcross, dtcross, aux;
  sina = Sin(angleAT);
  cosa = Cos(angleAT);

  cross =  Tangent.Crossed(Normal);
  dcross.SetLinearForm(1, DTangent.Crossed(Normal),
		       Tangent.Crossed(DNormal));

  tcross = Tangent.Crossed(cross);
  dtcross.SetLinearForm(1, DTangent.Crossed(cross),
			Tangent.Crossed(dcross));  
  
  aux.SetLinearForm(sina, dcross,  
		    cosa*d_angleAT, cross);
  aux.SetLinearForm(1 - cosa, dtcross,
		    sina*d_angleAT, tcross,
		    aux);
  DNormal+=aux;

  Normal.SetLinearForm( sina, cross,  
		       (1 - cosa), tcross,
		       Normal);

  BiNormal = Tangent.Crossed(Normal);

  DBiNormal.SetLinearForm(1, DTangent.Crossed(Normal),
			  Tangent.Crossed(DNormal));

// for test
/*  gp_Vec FDN, Tf, Nf, BNf;
  Standard_Real h;
  h = 1.0e-8;
  if (Param + h > myTrimmed->LastParameter()) h = -h;
  D0(Param + h, Tf, Nf, BNf);
  FDN = (Nf - Normal)/h;
  cout<<"Param = "<<Param<<endl;
  cout<<"DN = ("<<DNormal.X()<<", "<<DNormal.Y()<<", "<<DNormal.Z()<<")"<<endl;
  cout<<"FDN = ("<<FDN.X()<<", "<<FDN.Y()<<", "<<FDN.Z()<<")"<<endl;
*/

  return Standard_True;
}

//===============================================================
// Function : D2
// Purpose :
//===============================================================
 Standard_Boolean GeomFill_CorrectedFrenet::D2(const Standard_Real Param,
					       gp_Vec& Tangent,
					       gp_Vec& DTangent,
					       gp_Vec& D2Tangent,
					       gp_Vec& Normal,
					       gp_Vec& DNormal,
					       gp_Vec& D2Normal,
					       gp_Vec& BiNormal,
					       gp_Vec& DBiNormal,
					       gp_Vec& D2BiNormal) 
{
  frenet->D2(Param, Tangent, DTangent, D2Tangent, 
	     Normal, DNormal, D2Normal, 
	     BiNormal, DBiNormal, D2BiNormal);
  if (isFrenet) return Standard_True;

  Standard_Real angleAT, d_angleAT, d2_angleAT;
  Standard_Real sina, cosa; 
  TLaw->D2(Param, angleAT, d_angleAT, d2_angleAT);
  angleAT = GetAngleAT(Param); //OCC78

  gp_Vec cross, dcross, d2cross, tcross, dtcross, d2tcross, aux;
  sina = Sin(angleAT);
  cosa = Cos(angleAT);
  cross =  Tangent.Crossed(Normal);
  dcross.SetLinearForm(1, DTangent.Crossed(Normal),
		       Tangent.Crossed(DNormal));
  d2cross.SetLinearForm(1, D2Tangent.Crossed(Normal),
		        2, DTangent.Crossed(DNormal),
			Tangent.Crossed(D2Normal));
 
  
  tcross = Tangent.Crossed(cross);
  dtcross.SetLinearForm(1, DTangent.Crossed(cross),
			Tangent.Crossed(dcross));
  d2tcross.SetLinearForm(1, D2Tangent.Crossed(cross),
			 2, DTangent.Crossed(dcross),
			Tangent.Crossed(d2cross));


  aux.SetLinearForm(sina, d2cross,
		    2*cosa*d_angleAT, dcross,
		    cosa*d2_angleAT - sina*d_angleAT*d_angleAT, cross);
  
  aux.SetLinearForm(1 - cosa, d2tcross,
		    2*sina*d_angleAT, dtcross,
		    cosa*d_angleAT*d_angleAT + sina*d2_angleAT, tcross,
		    aux);
  D2Normal += aux;

/*  D2Normal += sina*(D2Tangent.Crossed(Normal) + 2*DTangent.Crossed(DNormal) + Tangent.Crossed(D2Normal)) + 
		    2*cosa*d_angleAT*(DTangent.Crossed(Normal) + Tangent.Crossed(DNormal)) + 
		    (cosa*d2_angleAT - sina*d_angleAT*d_angleAT)*Tangent.Crossed(Normal) + 
2*sina*d_angleAT*(DTangent.Crossed(Tangent.Crossed(Normal)) + Tangent.Crossed(DTangent.Crossed(Normal)) + Tangent.Crossed(Tangent.Crossed(DNormal))) + 
(1 - cosa)*(D2Tangent.Crossed(Tangent.Crossed(Normal)) + Tangent.Crossed(D2Tangent.Crossed(Normal)) + Tangent.Crossed(Tangent.Crossed(D2Normal)) + 2*DTangent.Crossed(DTangent.Crossed(Normal)) + 2*DTangent.Crossed(Tangent.Crossed(DNormal)) + 2*Tangent.Crossed(DTangent.Crossed(DNormal))) 
+ 
(cosa*d_angleAT*d_angleAT + sina*d2_angleAT)*Tangent.Crossed(Tangent.Crossed(Normal));*/

  
  aux.SetLinearForm(sina, dcross,  
		    cosa*d_angleAT, cross);
  aux.SetLinearForm(1 - cosa, dtcross,
		    sina*d_angleAT, tcross,
		    aux);
  DNormal+=aux;


  Normal.SetLinearForm( sina, cross,  
		       (1 - cosa), tcross,
		       Normal);

  BiNormal = Tangent.Crossed(Normal);

  DBiNormal.SetLinearForm(1, DTangent.Crossed(Normal),
			  Tangent.Crossed(DNormal));

  D2BiNormal.SetLinearForm(1, D2Tangent.Crossed(Normal),
			   2, DTangent.Crossed(DNormal),
			   Tangent.Crossed(D2Normal));

// for test
/*  gp_Vec FD2N, FD2T, FD2BN, Tf, DTf, Nf, DNf, BNf, DBNf;
  Standard_Real h;
  h = 1.0e-8;
  if (Param + h > myTrimmed->LastParameter()) h = -h;
  D1(Param + h, Tf, DTf, Nf, DNf, BNf, DBNf);
  FD2N = (DNf - DNormal)/h;
  FD2T = (DTf - DTangent)/h;
  FD2BN = (DBNf - DBiNormal)/h;
  cout<<"Param = "<<Param<<endl;
  cout<<"D2N = ("<<D2Normal.X()<<", "<<D2Normal.Y()<<", "<<D2Normal.Z()<<")"<<endl;
  cout<<"FD2N = ("<<FD2N.X()<<", "<<FD2N.Y()<<", "<<FD2N.Z()<<")"<<endl<<endl;
  cout<<"D2T = ("<<D2Tangent.X()<<", "<<D2Tangent.Y()<<", "<<D2Tangent.Z()<<")"<<endl;
  cout<<"FD2T = ("<<FD2T.X()<<", "<<FD2T.Y()<<", "<<FD2T.Z()<<")"<<endl<<endl;
  cout<<"D2BN = ("<<D2BiNormal.X()<<", "<<D2BiNormal.Y()<<", "<<D2BiNormal.Z()<<")"<<endl;
  cout<<"FD2BN = ("<<FD2BN.X()<<", "<<FD2BN.Y()<<", "<<FD2BN.Z()<<")"<<endl<<endl;  
*/
//
  return Standard_True;
}

//===============================================================
// Function : NbIntervals
// Purpose :
//===============================================================
 Standard_Integer GeomFill_CorrectedFrenet::NbIntervals(const GeomAbs_Shape S) const
{
  Standard_Integer NbFrenet, NbLaw;
  NbFrenet = frenet->NbIntervals(S);
  if (isFrenet) return NbFrenet;

  NbLaw = EvolAroundT->NbIntervals(S);
  if (NbFrenet == 1)
    return  NbLaw;

  TColStd_Array1OfReal FrenetInt(1, NbFrenet + 1);
  TColStd_Array1OfReal LawInt(1, NbLaw + 1);
  TColStd_SequenceOfReal Fusion;

  frenet->Intervals(FrenetInt, S);
  EvolAroundT->Intervals(LawInt, S);
  GeomLib::FuseIntervals(FrenetInt, LawInt, Fusion);

  return Fusion.Length()-1;
}

//===============================================================
// Function : Intervals
// Purpose :
//===============================================================
 void GeomFill_CorrectedFrenet::Intervals(TColStd_Array1OfReal& T,
					  const GeomAbs_Shape S) const
{
  Standard_Integer NbFrenet, NbLaw;
  if (isFrenet) {
    frenet->Intervals(T, S);
    return;
  }

  NbFrenet = frenet->NbIntervals(S);
  if(NbFrenet==1) {
    EvolAroundT->Intervals(T, S);
  }

  NbLaw = EvolAroundT->NbIntervals(S);
  
  TColStd_Array1OfReal FrenetInt(1, NbFrenet + 1);
  TColStd_Array1OfReal LawInt(1, NbLaw + 1);
  TColStd_SequenceOfReal Fusion;
  
  frenet->Intervals(FrenetInt, S);
  EvolAroundT->Intervals(LawInt, S);
  GeomLib::FuseIntervals(FrenetInt, LawInt, Fusion);

  for(Standard_Integer i = 1; i <= Fusion.Length(); i++)
    T.ChangeValue(i) = Fusion.Value(i);
}

//===============================================================
// Function : SetInterval
// Purpose :
//===============================================================
 void GeomFill_CorrectedFrenet::SetInterval(const Standard_Real First, 
					    const Standard_Real Last) 
{
 GeomFill_TrihedronLaw::SetInterval(First, Last);
 frenet->SetInterval(First, Last);
 if (!isFrenet) TLaw =  EvolAroundT->Trim(First, Last,
					  Precision::PConfusion()/2);
}

//===============================================================
// Function : GetAverageLaw
// Purpose :
//===============================================================
 void GeomFill_CorrectedFrenet::GetAverageLaw(gp_Vec& ATangent,
					      gp_Vec& ANormal,
					      gp_Vec& ABiNormal) 
{
  if (isFrenet) frenet->GetAverageLaw(ATangent, ANormal, ABiNormal);
  else {
    ATangent = AT;
    ANormal = AN;
    ABiNormal = ATangent;
    ABiNormal.Cross(ANormal);
  }
}

//===============================================================
// Function : IsConstant
// Purpose :
//===============================================================
 Standard_Boolean GeomFill_CorrectedFrenet::IsConstant() const
{
 return (myCurve->GetType() == GeomAbs_Line);
}

//===============================================================
// Function : IsOnlyBy3dCurve
// Purpose :
//===============================================================
 Standard_Boolean GeomFill_CorrectedFrenet::IsOnlyBy3dCurve() const
{
 return Standard_True;
}
