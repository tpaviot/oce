// File:	Approx_SameParameter.cxx
// Created:	Tue Jun  6 09:51:17 1995
// Author:	Xavier BENVENISTE
//		<xab@nonox>

//  Modified by skv - Wed Jun  2 11:49:59 2004 OCC5898

#include <Approx_SameParameter.ixx>
#include <TColStd_Array1OfReal.hxx>
#include <BSplCLib.hxx>
#include <Adaptor3d_CurveOnSurface.hxx>
#include <Geom2dAdaptor_Curve.hxx>
#include <Geom2dAdaptor_HCurve.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomAdaptor_HCurve.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <GeomAdaptor_HSurface.hxx>
//#include <GCPnts_UniformDeflection.hxx>
#include <GCPnts_QuasiUniformDeflection.hxx>
#include <Extrema_LocateExtPC.hxx>
#include <AdvApprox_ApproxAFunction.hxx>
#include <GeomLib_MakeCurvefromApprox.hxx>
#include <Precision.hxx>

#define MAX_ARRAY_SIZE 1000 // IFV, Jan 2000

#ifdef DEB
#ifdef DRAW
#include <DrawTrSurf.hxx>
#endif
#include <Geom2d_BSplineCurve.hxx>
#include <stdio.h>
static Standard_Boolean Voir     = Standard_False;
static Standard_Boolean AffichFw = Standard_False;
static Standard_Integer NbCurve = 0;
#endif
//
//   sert a tester si Extrema raconte pas des betises
//


static void ProjectPointOnCurve(const Standard_Real      InitValue,
				const gp_Pnt             APoint,
				const Standard_Real      Tolerance,
				const Standard_Integer   NumIteration,
				const Adaptor3d_Curve&     Curve,
				Standard_Boolean&        Status,
				Standard_Real&           Result)
{
  Standard_Integer num_iter = 0,
  not_done = 1,
  ii ;
  
  gp_Pnt a_point ;
  gp_Vec   vector,
  d1,
  d2 ;
  Standard_Real func,
  func_derivative,
  param = InitValue ;
  Status = Standard_False ;
  Standard_Real Toler = 1.0e-12;
  do {
    num_iter += 1 ;
    Curve.D2(param,
	      a_point,
	     d1,
	     d2) ;
    for (ii = 1 ; ii <= 3 ; ii++) {
      vector.SetCoord(ii, APoint.Coord(ii) - a_point.Coord(ii)) ;
    }
    func = vector.Dot(d1) ;
    func_derivative = vector.Dot(d2) ;
    func_derivative -= d1.Dot(d1) ;
    if ( Abs(func) < Tolerance * d1.Magnitude()) {
      not_done = 0 ;
      Status = Standard_True ;
    }
    else
      { // fixing a bug PRO18577 : avoid divizion by zero
	if( Abs(func_derivative) > Toler )  {
	  param -= func / func_derivative ;
	}
	param = Max(param,Curve.FirstParameter()) ;
	param = Min(param,Curve.LastParameter())  ;
	Status = Standard_True ;
      }
  } 
  while (not_done && num_iter <= NumIteration) ;
  Result = param ;
}  
     


//=======================================================================
//class : Approx_SameParameter_Evaluator
//purpose  : 
//=======================================================================

class Approx_SameParameter_Evaluator : public AdvApprox_EvaluatorFunction
{
 public:
  Approx_SameParameter_Evaluator (const TColStd_Array1OfReal& theFlatKnots, 
                                  const TColStd_Array1OfReal& thePoles,
                                  const Handle(Adaptor2d_HCurve2d)& theHCurve2d) 
    : FlatKnots(theFlatKnots), Poles(thePoles), HCurve2d(theHCurve2d) {}

  virtual void Evaluate (Standard_Integer *Dimension,
		         Standard_Real     StartEnd[2],
                         Standard_Real    *Parameter,
                         Standard_Integer *DerivativeRequest,
                         Standard_Real    *Result, // [Dimension]
                         Standard_Integer *ErrorCode);
  
 private:
  const TColStd_Array1OfReal& FlatKnots;
  const TColStd_Array1OfReal& Poles;
  Handle(Adaptor2d_HCurve2d) HCurve2d;
};

void Approx_SameParameter_Evaluator::Evaluate (Standard_Integer *,/*Dimension*/
                                               Standard_Real    /*StartEnd*/[2],
                                               Standard_Real    *Parameter,
                                               Standard_Integer *DerivativeRequest,
                                               Standard_Real    *Result,
                                               Standard_Integer *ReturnCode) 
{ 
  gp_Pnt2d Point ;
  gp_Vec2d Vector ;
  Standard_Integer extrap_mode[2] ;
  extrap_mode[0] = extrap_mode[1] = 3;
  Standard_Real eval_result[2] ;
  Standard_Real *PolesArray =
    (Standard_Real *) &Poles(Poles.Lower()) ;
  //
  // evaluate the 1D bspline that represents the change in parameterization
  //
  BSplCLib::Eval(*Parameter,
		 Standard_False,
		 *DerivativeRequest,
		 extrap_mode[0],
		 3,
		 FlatKnots,
		 1,
		 PolesArray[0],
                 eval_result[0]) ;
  
  
  if (*DerivativeRequest == 0){
    HCurve2d->D0(eval_result[0],Point);
    Point.Coord(Result[0],Result[1]);
  }
  else if (*DerivativeRequest == 1){
    HCurve2d->D1(eval_result[0], Point, Vector);
    Vector.Multiply(eval_result[1]);
    Vector.Coord(Result[0],Result[1]);
  }
  ReturnCode[0] = 0 ;
}

static Standard_Real ComputeTolReached(const Handle(Adaptor3d_HCurve)& c3d,
				       const Adaptor3d_CurveOnSurface& cons,
				       const Standard_Integer        nbp)
{
  Standard_Real d2 = 0.;
  Standard_Integer nn = nbp;
  Standard_Real unsurnn = 1./nn;
  Standard_Real first = c3d->FirstParameter();
  Standard_Real last  = c3d->LastParameter();
  for(Standard_Integer i = 0; i <= nn; i++){
    Standard_Real t = unsurnn*i;
    Standard_Real u = first*(1.-t) + last*t;
    gp_Pnt Pc3d = c3d->Value(u);
    gp_Pnt Pcons = cons.Value(u);
    if (Precision::IsInfinite(Pcons.X()) ||
	Precision::IsInfinite(Pcons.Y()) ||
	Precision::IsInfinite(Pcons.Z())) {
      d2=Precision::Infinite();
      break;
    }
    Standard_Real temp = Pc3d.SquareDistance(Pcons);
    if(temp > d2) d2 = temp;
  }
  d2 = 1.5*sqrt(d2);
  if(d2<1.e-7) d2 = 1.e-7;
  return d2;
}

static Standard_Boolean Check(const TColStd_Array1OfReal& FlatKnots, 
                              const TColStd_Array1OfReal& Poles,
                              const Standard_Integer nbp,
			      const TColStd_Array1OfReal& pc3d,
//			      const TColStd_Array1OfReal& pcons,
			      const TColStd_Array1OfReal& ,
			      const Handle(Adaptor3d_HCurve)& c3d,
			      const Adaptor3d_CurveOnSurface& cons,
			      Standard_Real& tol,
			      const Standard_Real oldtol)
{
  Standard_Real d = tol;
  Standard_Integer extrap_mode[2] ;
  extrap_mode[0] = extrap_mode[1] = 3;
  Standard_Integer i;
#ifdef DEB
  if (Voir) {
    cout<<endl;
    cout<<"Controle du changement de variable : "<<endl;
    cout<<"baillement mesure par projection : "<<d<<endl;
    cout<<"Nombre de points : "<<nbp<<endl;
  }
#endif
#if 0
  Standard_Real glis = 0., dglis = 0.;
  for(i = 1; i <= nbp; i++){
    Standard_Real tc3d = pc3d(i);
    gp_Pnt Pc3d = c3d->Value(tc3d);
    Standard_Real tcons;
    BSplCLib::Eval(tc3d,Standard_False,0,extrap_mode[0],
		   3,FlatKnots,1, (Standard_Real&)Poles(1),tcons);
    gp_Pnt Pcons = cons.Value(tcons);
    Standard_Real temp = Pc3d.SquareDistance(Pcons);
    if(temp >= dglis) dglis = temp;
    temp = Abs(tcons-pcons(i));
    if(temp >= glis) glis = temp;
  }
  dglis = sqrt(dglis);
#ifdef DEB
  if ( Voir) {
    cout<<"glissement de parametre aux points imposes : "<<glis<<endl;
    cout<<"distance de glissement aux points imposes : "<<dglis<<endl;
  }
#endif
  dglis = 0.;
  for(i = 1; i < nbp; i++){
    Standard_Real tc3d = 0.5*(pc3d(i)+pc3d(i+1));
    gp_Pnt Pc3d = c3d->Value(tc3d);
    Standard_Real tcons;
    BSplCLib::Eval(tc3d,Standard_False,0,extrap_mode[0],
		   3,FlatKnots,1, (Standard_Real&)Poles(1),tcons);
    gp_Pnt Pcons = cons.Value(tcons);
    Standard_Real temp = Pc3d.SquareDistance(Pcons);
    if(temp >= dglis) dglis = temp;
  }
  dglis = sqrt(dglis);
#ifdef DEB
  if (Voir)
    cout<<"distance de glissement en milieu d intervals : "<<dglis<<endl;
#endif
#endif

  Standard_Real d2 = 0.;
  Standard_Integer nn = 2*nbp;
  Standard_Real unsurnn = 1./nn;
//  Modified by skv - Wed Jun  2 11:49:59 2004 OCC5898 Begin
// Correction of the interval of valid values. This condition has no sensible
// grounds. But it is better then the old one (which is commented out) because
// it fixes the bug OCC5898. To develop more or less sensible criterion it is
// necessary to deeply investigate this problem which is not possible in frames
// of debugging.

//   Standard_Real firstborne= 2*pc3d(1)-pc3d(nbp);
//   Standard_Real lastborne= 2*pc3d(nbp)-pc3d(1);
  Standard_Real firstborne= 3.*pc3d(1)   - 2.*pc3d(nbp);
  Standard_Real lastborne = 3.*pc3d(nbp) - 2.*pc3d(1);
//  Modified by skv - Wed Jun  2 11:50:03 2004 OCC5898 End
  for(i = 0; i <= nn; i++){
    Standard_Real t = unsurnn*i;
    Standard_Real tc3d = pc3d(1)*(1.-t) + pc3d(nbp)*t;
    gp_Pnt Pc3d = c3d->Value(tc3d);
    Standard_Real tcons;
    BSplCLib::Eval(tc3d,Standard_False,0,extrap_mode[0],
		   3,FlatKnots,1, (Standard_Real&)Poles(1),tcons);
    if (tcons < firstborne || tcons > lastborne) {
      tol=Precision::Infinite();
      return Standard_False;
    }
    gp_Pnt Pcons = cons.Value(tcons);
    Standard_Real temp = Pc3d.SquareDistance(Pcons);
    if(temp > d2) d2 = temp;
  }
  tol = sqrt(d2);
#ifdef DEB
  if (Voir)
    cout<<"distance max sur "<<nn<<" points : "<<tol<<endl<<endl;
#endif
  return ((tol <= d) || (tol > 0.8 * oldtol));
}


//=======================================================================
//function : Approx_SameParameter
//purpose  : 
//=======================================================================

Approx_SameParameter::Approx_SameParameter(const Handle(Geom_Curve)&   C3D,
					   const Handle(Geom2d_Curve)& C2D,
					   const Handle(Geom_Surface)& S,
					   const Standard_Real         Tol):
 mySameParameter(Standard_True), myDone(Standard_False)
{
  myHCurve2d = new Geom2dAdaptor_HCurve(C2D);
  myC3d      = new GeomAdaptor_HCurve(C3D);
  mySurf     = new GeomAdaptor_HSurface(S);
  Build(Tol);
}


//=======================================================================
//function : Approx_SameParameter
//purpose  : 
//=======================================================================

Approx_SameParameter::Approx_SameParameter(const Handle(Adaptor3d_HCurve)&   C3D,
					   const Handle(Geom2d_Curve)&     C2D,
					   const Handle(Adaptor3d_HSurface)& S,
					   const Standard_Real            Tol):
 mySameParameter(Standard_True), myDone(Standard_False)
{
  myC3d = C3D;
  mySurf = S;
  myHCurve2d = new Geom2dAdaptor_HCurve(C2D);
  Build(Tol);
}


//=======================================================================
//function : Approx_SameParameter
//purpose  : 
//=======================================================================

Approx_SameParameter::Approx_SameParameter(const Handle(Adaptor3d_HCurve)&   C3D,
					   const Handle(Adaptor2d_HCurve2d)& C2D,
					   const Handle(Adaptor3d_HSurface)& S,
					   const Standard_Real            Tol):
 mySameParameter(Standard_True), myDone(Standard_False)
{
  myC3d = C3D;
  mySurf = S;
  myHCurve2d = C2D;
  Build(Tol);
}


//=======================================================================
//function : Build
//purpose  : 
//=======================================================================

void Approx_SameParameter::Build(const Standard_Real Tolerance)
{
  Standard_Integer ii ;
  Adaptor3d_CurveOnSurface CurveOnSurface(myHCurve2d,mySurf);
  Standard_Real fcons = CurveOnSurface.FirstParameter();
  Standard_Real lcons = CurveOnSurface.LastParameter();
  Standard_Real fc3d = myC3d->FirstParameter();
  Standard_Real lc3d = myC3d->LastParameter();

  GeomAbs_Shape Continuity = myHCurve2d->Continuity();

  if(Continuity > GeomAbs_C1) Continuity = GeomAbs_C1;

  //On controle les tangentes aux extremites pour savoir si le
  //reparametrage est possible et on calcule les tangentes aux
  //extremites de la fonction de changement de variable.
  Standard_Real tangent[2];
  tangent[0]=tangent[1]=0;
  gp_Pnt Pcons,Pc3d;
  gp_Vec Vcons,Vc3d;

  Standard_Real Tol = Tolerance;
  Standard_Real Tol2 = Tol * Tol;
  Standard_Real Tolp = myC3d->Resolution(Tol), deltamin = 50*Tolp;

  Standard_Real besttol2 = Tol2;
  Standard_Boolean extrok = 0;

  extrok = 1;
  CurveOnSurface.D1(fcons,Pcons,Vcons);
  myC3d->D1(fc3d,Pc3d,Vc3d);
  Standard_Real dist2 = Pcons.SquareDistance(Pc3d);
  Standard_Real dmax2 = dist2;

  Standard_Real magVcons = Vcons.Magnitude();
  if (magVcons > 1.e-12){
    tangent[0] = Vc3d.Magnitude() / magVcons;
  }
  else extrok = 0;

  CurveOnSurface.D1(lcons,Pcons,Vcons);
  myC3d->D1(lc3d,Pc3d,Vc3d);
  dist2 = Pcons.SquareDistance(Pc3d);

  if(dist2 > dmax2) dmax2 = dist2;
  magVcons = Vcons.Magnitude();
  if (magVcons > 1.e-12){
    tangent[1] = Vc3d.Magnitude() / magVcons;
  }
  else extrok = 0;


  if(dmax2 > besttol2) besttol2 = dmax2;

  //On prend un multiple de l echantillon du CheckShape,
  //au moins les points de controle seront bons. No comment!!!

  Standard_Integer NCONTROL = 22;
#ifdef DEB
  Standard_Integer nbcoups = 0;
#endif
  
  Standard_Boolean interpolok = 0;
  Standard_Real tolsov = 1.e200;
  //On prend des parametres a pas constant sur la curve on surface
  //et sur la courbe 3d.
  Standard_Real deltacons = lcons - fcons;
  deltacons /= (NCONTROL);
  Standard_Real deltac3d = lc3d - fc3d;
  deltac3d /= (NCONTROL);

  Standard_Real wcons = fcons;
  Standard_Real wc3d  = fc3d;
  
  Standard_Real qpcons[MAX_ARRAY_SIZE], qnewpcons[MAX_ARRAY_SIZE], 
                qpc3d[MAX_ARRAY_SIZE], qnewpc3d[MAX_ARRAY_SIZE];
  Standard_Real * pcons = qpcons; Standard_Real * newpcons = qnewpcons;
  Standard_Real * pc3d = qpc3d; Standard_Real * newpc3d = qnewpc3d;

  for ( ii = 0 ; ii < NCONTROL; ii++) {
    pcons[ii] = wcons;
    pc3d[ii]  = wc3d;
    wcons += deltacons;
    wc3d  += deltac3d;
  }
  pcons[NCONTROL] = lcons;
  pc3d[NCONTROL]  = lc3d;

  Standard_Integer New_NCONTROL = NCONTROL;
  if(Continuity < GeomAbs_C1) {
     Standard_Integer NbInt = myHCurve2d->NbIntervals(GeomAbs_C1) + 1;
     TColStd_Array1OfReal Param_de_decoupeC1 (1, NbInt);
     myHCurve2d->Intervals(Param_de_decoupeC1, GeomAbs_C1);
     TColStd_SequenceOfReal new_par;
     Standard_Integer inter = 1;
     ii =1;
     new_par.Append(fcons);

     while(Param_de_decoupeC1(inter) <= fcons + deltamin) inter++;
     while(Param_de_decoupeC1(NbInt) >= lcons - deltamin) NbInt--;

     while(inter <= NbInt || ii < NCONTROL) {
       if(Param_de_decoupeC1(inter) < pcons[ii]) {
	 new_par.Append(Param_de_decoupeC1(inter));
	 if((pcons[ii] - Param_de_decoupeC1(inter)) <= deltamin) {
	   ii++;
	   if(ii > NCONTROL) {ii = NCONTROL;}
	 }
	 inter++;
       }
       else {
	 if((Param_de_decoupeC1(inter) - pcons[ii]) > deltamin) {
	   new_par.Append(pcons[ii]);
	 }
	 ii++;
       }
     }
     
     new_par.Append(lcons);
     New_NCONTROL = new_par.Length() - 1;
     //simple protection if New_NCONTROL > allocated elements in array
     if (New_NCONTROL > MAX_ARRAY_SIZE) {
       mySameParameter = Standard_False;
       return;
     }
     for(ii = 1; ii <= New_NCONTROL; ii++){
       pcons[ii] = pc3d[ii] = new_par.Value(ii + 1);
     }
     pc3d[New_NCONTROL]  = lc3d;
   }

  
  Extrema_LocateExtPC Projector;
  Projector.Initialize(myC3d->Curve(),fc3d,lc3d,Tol);
  
  Standard_Integer count = 1;
  Standard_Real previousp = fc3d, initp=0, curp;//, deltamin = 50*Tolp;
  Standard_Real bornesup = lc3d - deltamin;
  Standard_Boolean projok = 0, 
    use_parameter ;
  for (ii = 1; ii < New_NCONTROL; ii++){    
    CurveOnSurface.D0(pcons[ii],Pcons);
    myC3d->D0(pc3d[ii],Pc3d);
    dist2 = Pcons.SquareDistance(Pc3d);
    use_parameter = (dist2 <= Tol2  && (pc3d[ii] > pc3d[count-1] + deltamin)) ;
    if(use_parameter) {
      
      if(dist2 > dmax2) dmax2 = dist2;
      initp = previousp = pc3d[count] = pc3d[ii];
      pcons[count] = pcons[ii];
      count++;
    }
    else {
      if(!projok) initp = pc3d[ii];
      projok = mySameParameter = Standard_False;
      Projector.Perform(Pcons, initp);
      if (Projector.IsDone()) {
	curp = Projector.Point().Parameter();
	Standard_Real dist_2 = Projector.SquareDistance();
	if(dist_2 > besttol2) besttol2 = dist_2;
	projok = 1;
      }
      else {
	ProjectPointOnCurve(initp,Pcons,Tol,30,myC3d->Curve(),projok,curp);
      }
      if(projok){
	if(curp > previousp + deltamin && curp < bornesup){
	  initp = previousp = pc3d[count] = curp;
	  pcons[count] = pcons[ii];
	  count++;
	}
      }
      else {
#ifdef DEB 
	// JAG
	cout << "Projection not done" << endl;
#endif
      }
    }
  }
  if(mySameParameter){
    myTolReached = 1.5*sqrt(dmax2);
    return;
  }
 
  if(!extrok) { // Si pas deja SameP et tgte aux fraise, on abandonne.
    mySameParameter = Standard_False;
#ifdef DEB
    cout<<"SameParameter probleme  : tangente nulle aux extremites"<<endl;
#endif
    return;
  }

  pcons[count] = lcons;
  pc3d[count]  = lc3d;

#ifdef DEB
  if (AffichFw) {
    char Name[17];
    Name[0]='\0';
    TColgp_Array1OfPnt2d    DEBP2d  (0,count);
    TColStd_Array1OfInteger DEBMults(0,count); 
    DEBMults.Init(1); DEBMults(0) = 2; DEBMults(count) = 2;
    TColStd_Array1OfReal    DEBKnots(0,count);
    for (Standard_Integer DEBi = 0; DEBi <= count; DEBi++) {
      DEBKnots(DEBi) = DEBi;
      DEBP2d  (DEBi) = gp_Pnt2d(pc3d[DEBi],pcons[DEBi]);
    }
    Handle(Geom2d_BSplineCurve) DEBBS = 
      new Geom2d_BSplineCurve(DEBP2d,DEBKnots,DEBMults,1);
    sprintf(Name,"DEBC2d_%d",++NbCurve);
#ifdef DRAW
    DrawTrSurf::Set(Name,DEBBS);
#endif
  }
#endif
    
  while(!interpolok){
    // Les tableaux et leurs bornes pour l interpolation.
    Standard_Integer num_knots = count + 7;
    Standard_Integer num_poles = count + 3;
    TColStd_Array1OfReal    Paramc3d(*pc3d,1,count+1);
    TColStd_Array1OfReal    Paramcons(*pcons,1,count+1);
    TColStd_Array1OfInteger ContactOrder(1,num_poles) ;
    TColStd_Array1OfReal    Poles(1,num_poles) ;
    TColStd_Array1OfReal    InterpolationParameters(1,num_poles) ;
    TColStd_Array1OfReal    FlatKnots(1,num_knots) ; 
    
    // On remplit les tableaux en faisant attention aux valeurs des bouts.
    ContactOrder.Init(0);
    ContactOrder(2) = ContactOrder(num_poles - 1) = 1;
    
    FlatKnots(1) = FlatKnots(2) = FlatKnots(3) = FlatKnots(4) = fc3d;
    FlatKnots(num_poles + 1) = FlatKnots(num_poles + 2) = 
      FlatKnots(num_poles + 3) = FlatKnots(num_poles + 4) = lc3d;
    
    Poles(1) = fcons; Poles(num_poles) = lcons;
    Poles(2) = tangent[0]; Poles(num_poles - 1) = tangent[1];
    
    InterpolationParameters(1) = InterpolationParameters(2) = fc3d;
    InterpolationParameters(num_poles - 1) = InterpolationParameters(num_poles) = lc3d;
    
    for (ii = 3; ii <= num_poles - 2; ii++) {
      Poles(ii) = Paramcons(ii - 1);
      InterpolationParameters(ii) = FlatKnots(ii+2) = Paramc3d(ii - 1);
    }
    Standard_Integer inversion_problem;
    BSplCLib::Interpolate(3,FlatKnots,InterpolationParameters,ContactOrder,
			  1,Poles(1),inversion_problem);
    if(inversion_problem) {
      Standard_ConstructionError::Raise();
    }

    //-------------------------------------------
#ifdef DEB
  if (AffichFw) {
    nbcoups ++;
    char Name[17];
    Name[0] = '\0';
    Standard_Integer nnn = 100;
    TColgp_Array1OfPnt2d    DEBP2d  (0,nnn);
    TColStd_Array1OfInteger DEBMults(0,nnn); 
    DEBMults.Init(1); DEBMults(0) = 2; DEBMults(nnn) = 2;
    TColStd_Array1OfReal    DEBKnots(0,nnn);
    Standard_Real du = (lc3d - fc3d) / nnn;
    Standard_Real u3d = fc3d;
    Standard_Integer extrap_mode[2] ;
    extrap_mode[0] = extrap_mode[1] = 3;
    Standard_Real eval_result[2] ;
    Standard_Integer DerivativeRequest = 0;
    Standard_Real *PolesArray =
      (Standard_Real *) &Poles(Poles.Lower()) ;

    for (Standard_Integer DEBi = 0; DEBi <= nnn; DEBi++) {
      DEBKnots(DEBi) = DEBi;
      BSplCLib::Eval(u3d,
		     Standard_False,
		     DerivativeRequest,
		     extrap_mode[0],
		     3,
		     FlatKnots,
		     1,
		     PolesArray[0],
		     eval_result[0]) ;

      DEBP2d  (DEBi) = gp_Pnt2d(u3d,eval_result[0]);
      u3d += du;
    }

    Handle(Geom2d_BSplineCurve) DEBBS = 
      new Geom2d_BSplineCurve(DEBP2d,DEBKnots,DEBMults,1);
    sprintf(Name,"DEBC2d_%d_%d",NbCurve,nbcoups );
#ifdef DRAW
    DrawTrSurf::Set(Name,DEBBS);
#endif
  }
#endif
//-------------------------------------------    

//-------------------------------------------
    // Test if par2d(par3d) is monotonous function or not           ----- IFV, Jan 2000
    // and try to insert new point to improve BSpline interpolation

    Standard_Integer extrap_mode[2] ;
    extrap_mode[0] = extrap_mode[1] = 3;
    Standard_Real eval_result[2] ;
    Standard_Integer DerivativeRequest = 0;
    Standard_Real *PolesArray =
      (Standard_Real *) &Poles(Poles.Lower()) ;

    Standard_Integer newcount = 0;
    for (ii = 0; ii < count; ii++) {
      
      newpcons[newcount] = pcons[ii];
      newpc3d[newcount] = pc3d[ii];
      newcount++;

      if(count - ii + newcount == MAX_ARRAY_SIZE) continue;

      BSplCLib::Eval(.5*(pc3d[ii]+pc3d[ii+1]), Standard_False, DerivativeRequest,
		     extrap_mode[0], 3, FlatKnots, 1, PolesArray[0], eval_result[0]);
		     
      if(eval_result[0] < pcons[ii] || eval_result[0] > pcons[ii+1]) {
	Standard_Real ucons = 0.5*(pcons[ii]+pcons[ii+1]);
	Standard_Real uc3d  = 0.5*(pc3d[ii]+pc3d[ii+1]);
	
	CurveOnSurface.D0(ucons,Pcons);
	Projector.Perform(Pcons, uc3d);
	if (Projector.IsDone()) {
	  curp = Projector.Point().Parameter();
	  Standard_Real dist_2 = Projector.SquareDistance();
	  if(dist_2 > besttol2) besttol2 = dist_2;
	  projok = 1;
	}
	else {
	  ProjectPointOnCurve(uc3d,Pcons,Tol,30,myC3d->Curve(),projok,curp);
	}
	if(projok){
	  if(curp > pc3d[ii] + deltamin && curp < pc3d[ii+1] - deltamin){
	    newpc3d[newcount] = curp;
	    newpcons[newcount] = ucons;
	    newcount ++;
	  }
	}
	else {
#ifdef DEB 
	  // JAG
	  cout << "Projection not done" << endl;
#endif
	}
      }
     
    }

    newpc3d[newcount] = pc3d[count];
    newpcons[newcount] = pcons[count];
    Standard_Real * temp;
    temp = pc3d;
    pc3d = newpc3d;
    newpc3d = temp;
    temp = pcons;
    pcons = newpcons;
    newpcons = temp;

    if((count != newcount) && newcount < MAX_ARRAY_SIZE) { count = newcount; continue;}

    count = newcount;

    Standard_Real algtol = sqrt(besttol2);

    interpolok = Check (FlatKnots, Poles, count+1, Paramc3d, Paramcons, 
                        myC3d, CurveOnSurface, algtol, tolsov);

    if (Precision::IsInfinite(algtol)) {
      mySameParameter = Standard_False;
#ifdef DEB
      cout<<"SameParameter probleme  : fonction d'interpolation du parametrage aux fraises !!"<<endl;
#endif
      return;
    }

    tolsov = algtol;

    interpolok = (interpolok || count >= MAX_ARRAY_SIZE);

    if(interpolok) {
        Standard_Real besttol = sqrt(besttol2);
#ifdef DEB
      if (Voir) {
	if(algtol > besttol){
	  cout<<"SameParameter : Tol non atteinte avant approx"<<endl;
	}
      }
#endif
      Handle(TColStd_HArray1OfReal) tol1d,tol2d,tol3d;
      tol1d = new TColStd_HArray1OfReal(1,2) ;
      tol1d->SetValue(1, mySurf->UResolution(besttol));
      tol1d->SetValue(2, mySurf->VResolution(besttol));

      Approx_SameParameter_Evaluator ev (FlatKnots, Poles, myHCurve2d); 
      AdvApprox_ApproxAFunction  anApproximator(2,0,0,tol1d,tol2d,tol3d,fc3d,lc3d,
						Continuity,11,40,ev);

      if (anApproximator.IsDone() || anApproximator.HasResult()) {
	GeomLib_MakeCurvefromApprox  aCurveBuilder(anApproximator) ;
	myCurve2d = aCurveBuilder.Curve2dFromTwo1d(1,2) ;
	myHCurve2d = new Geom2dAdaptor_HCurve(myCurve2d);
	CurveOnSurface.Load(myHCurve2d);
	myTolReached = ComputeTolReached(myC3d,CurveOnSurface,NCONTROL);
	myDone = Standard_True;
      } 
    }
    else {
#ifdef DEB
      if (Voir)
	cout<<"SameParameter : Pas assez de points, on enrichit"<<endl;
#endif

      Standard_Integer newcount = 0;
      for(Standard_Integer n = 0; n < count; n++){
	newpc3d[newcount] = pc3d[n];
	newpcons[newcount] = pcons[n];
	newcount ++;

	if(count - n + newcount == MAX_ARRAY_SIZE) continue;

	Standard_Real ucons = 0.5*(pcons[n]+pcons[n+1]);
	Standard_Real uc3d  = 0.5*(pc3d[n]+pc3d[n+1]);
	
	CurveOnSurface.D0(ucons,Pcons);
	Projector.Perform(Pcons, uc3d);
	if (Projector.IsDone()) {
	  curp = Projector.Point().Parameter();
	  Standard_Real dist_2 = Projector.SquareDistance();
	  if(dist_2 > besttol2) besttol2 = dist_2;
	  projok = 1;
	}
	else {
	  ProjectPointOnCurve(uc3d,Pcons,Tol,30,myC3d->Curve(),projok,curp);
	}
	if(projok){
	  if(curp > pc3d[n] + deltamin && curp < pc3d[n+1] - deltamin){
	    newpc3d[newcount] = curp;
	    newpcons[newcount] = ucons;
	    newcount ++;
	  }
	}
	else {
#ifdef DEB 
	  // JAG
	  cout << "Projection not done" << endl;
#endif
	}
      }
      newpc3d[newcount] = pc3d[count];
      newpcons[newcount] = pcons[count];
      Standard_Real * tempx;
      tempx = pc3d;
      pc3d = newpc3d;
      newpc3d = tempx;
      tempx = pcons;
      pcons = newpcons;
      newpcons = tempx;
      count = newcount;
    }
  }
}
