// File:	IntTools_EdgeFace.cxx
// Created:	Mon Feb 26 10:23:38 2001
// Author:	Peter KURNEV
//		<pkv@irinox>
//

#include <IntTools_EdgeFace.ixx>



#include <IntTools_CArray1OfReal.hxx>
#include <IntTools.hxx>
#include <IntTools_CArray1OfInteger.hxx>
#include <IntTools_Range.hxx>
#include <IntTools_Tools.hxx>
#include <IntTools_Array1OfRange.hxx>
#include <IntTools_QuickSortRange.hxx>
#include <IntTools_CompareRange.hxx>
#include <IntTools_CommonPrt.hxx>
#include <IntTools_Root.hxx>
#include <IntTools_BeanFaceIntersector.hxx>
#include <IntTools_Context.hxx>

#include <BRep_Tool.hxx>

#include <GeomAdaptor_Surface.hxx>
#include <GeomAdaptor_Curve.hxx>

#include <Geom_Surface.hxx>
#include <Geom_Curve.hxx>

#include <GeomAPI_ProjectPointOnSurf.hxx>

#include <Precision.hxx>

#include <Bnd_Box.hxx>
#include <BndLib_AddSurface.hxx>

#include <gp_Cylinder.hxx>
#include <gp_Ax1.hxx>
#include <gp_Lin.hxx>
#include <gp_Cone.hxx>
#include <gp_Torus.hxx>
#include <gp_Circ.hxx>
#include <gp_Pln.hxx>


#include <Extrema_ExtCS.hxx>
#include <Extrema_POnCurv.hxx>
#include <Extrema_POnSurf.hxx>

// modified by NIZHNY-MKK  Thu Jul 21 11:35:59 2005
#include <IntCurveSurface_HInter.hxx>
#include <GeomAdaptor_HCurve.hxx>
#include <GeomAdaptor_HSurface.hxx>
#include <IntCurveSurface_IntersectionPoint.hxx>

#ifdef _MSC_VER
#pragma warning ( disable : 4101 )
#endif

static
  Standard_Boolean IsCoplanar (const BRepAdaptor_Curve&  ,
			       const BRepAdaptor_Surface& );
static
  Standard_Boolean IsRadius (const BRepAdaptor_Curve& aCurve ,
			     const BRepAdaptor_Surface& aSurface);
static
  Standard_Integer AdaptiveDiscret (const Standard_Integer iDiscret,
				    const BRepAdaptor_Curve& aCurve ,
				    const BRepAdaptor_Surface& aSurface);

//=======================================================================
//function : IntTools_EdgeFace::IntTools_EdgeFace
//purpose  : 
//=======================================================================
  IntTools_EdgeFace::IntTools_EdgeFace()
{
  myTolE=1.e-7;
  myTolF=1.e-7;
  myDiscret=30;
  myEpsT   =1e-12;
  myEpsNull=1e-12;
  myDeflection=0.01;
  myIsDone=Standard_False;
  myErrorStatus=1;
  myParallel=Standard_False;
  myPar1=0.;
  myContext = NULL;
}

//=======================================================================
//function : SetEdge
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetEdge(const TopoDS_Edge& anEdge)
{
  myEdge=anEdge;
}

//=======================================================================
//function : SetFace
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetFace(const TopoDS_Face& aFace)
{
  myFace=aFace;
}

//=======================================================================
//function : SetTolE
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetTolE(const Standard_Real aTol) 
{
  myTolE=aTol;
} 
//=======================================================================
//function : SetTolF
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetTolF(const Standard_Real aTol) 
{
  myTolF=aTol;
} 

//=======================================================================
//function : SetDiscretize
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetDiscretize(const Standard_Integer aDiscret)
{
  myDiscret=aDiscret;
}
//=======================================================================
//function : SetDeflection
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetDeflection(const Standard_Real aDefl) 
{
  myDeflection=aDefl;
} 
//=======================================================================
//function : SetEpsilonT
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetEpsilonT(const Standard_Real anEpsT) 
{
  myEpsT=anEpsT;
} 
//=======================================================================
//function : SetEpsilonNull
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetEpsilonNull(const Standard_Real anEpsNull) 
{
  myEpsNull=anEpsNull;
} 

//=======================================================================
//function : SetRange
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetRange(const Standard_Real aFirst,
				   const Standard_Real aLast) 
{
  myRange.SetFirst (aFirst);
  myRange.SetLast  (aLast);
} 

//=======================================================================
//function : SetRange
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetRange(const IntTools_Range& aRange) 
{
  myRange.SetFirst (aRange.First());
  myRange.SetLast  (aRange.Last());
} 
//=======================================================================
//function : IsDone
//purpose  : 
//=======================================================================
  Standard_Boolean IntTools_EdgeFace::IsDone()const 
{
  return myIsDone;
} 
//=======================================================================
//function : ErrorStatus
//purpose  : 
//=======================================================================
  Standard_Integer IntTools_EdgeFace::ErrorStatus()const 
{
  return myErrorStatus;
}
//=======================================================================
//function : CommonParts
//purpose  : 
//=======================================================================
  const IntTools_SequenceOfCommonPrts& IntTools_EdgeFace::CommonParts() const 
{
  return mySeqOfCommonPrts;
}
//=======================================================================
//function : Range
//purpose  : 
//=======================================================================
  const IntTools_Range&  IntTools_EdgeFace::Range() const
{
  return myRange;
} 

//=======================================================================
//function : CheckData
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::CheckData()
{
  if (BRep_Tool::Degenerated(myEdge)) {
    myErrorStatus=2;
  }
  if (!BRep_Tool::IsGeometric(myEdge)) { 
     myErrorStatus=3;
  }
}


//=======================================================================
//function : Prepare
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::Prepare() 
{
  Standard_Integer pri;
  IntTools_CArray1OfReal aPars;
 
  //
  // 1.Prepare Curve's data and Surface's data
  myC.Initialize(myEdge);
  GeomAbs_CurveType aCurveType;
  aCurveType=myC.GetType();
  //
  // 2.Prepare myCriteria
  if (aCurveType==GeomAbs_BSplineCurve||
	aCurveType==GeomAbs_BezierCurve) {
    myCriteria=1.5*myTolE+myTolF;
  }
  else {
    myCriteria=myTolE+myTolF;
  }
  // 2.a myTmin, myTmax
  myTmin=myRange.First();
  myTmax=myRange.Last();
  // 2.b myFClass2d
  myS.Initialize (myFace,Standard_True);
  myFClass2d.Init(myFace, 1.e-6);
  //
  // 2.c Prepare adaptive myDiscret
  myDiscret=AdaptiveDiscret(myDiscret, myC, myS);
  //
  //
  // 3.Prepare myPars 
  pri = IntTools::PrepareArgs(myC, myTmax, myTmin, myDiscret, myDeflection, aPars);
  if (pri) {
    myErrorStatus=6;
    return;
  }
  // 4.
  //ProjectableRanges
  Standard_Integer i, iProj, aNb, aNbProj, ind0, ind1;
  Standard_Real t0, t1, tRoot;
  
  //
  // Table of Projection's function values
  aNb=aPars.Length();
  IntTools_CArray1OfInteger anArrProjectability;
  anArrProjectability.Resize(aNb);
  
  for (iProj=0, i=0; i<aNb; i++) {
    t0=aPars(i);
    aNbProj=IsProjectable (t0); 
    
    anArrProjectability(i)=0;
    if (aNbProj) {
      anArrProjectability(i)=1;
      iProj++;
    }
  }
  //
  // Checking
  if (!iProj ) {
    myErrorStatus=7;
    return;
  }
  
  //
  // Projectable Ranges
  IntTools_Range aRange;
  
  ind0=anArrProjectability(0);
  if (ind0) {
    t0=aPars(0);
    aRange.SetFirst(t0);
  }
  
  for(i=1; i<aNb; i++) {
    ind1=anArrProjectability(i);
    t0=aPars(i-1);
    t1=aPars(i);

    if (i==(aNb-1)) {
      if (ind1 && ind0) {
	aRange.SetLast(t1);
	myProjectableRanges.Append(aRange);
      }
      if (ind1 && !ind0) {
	FindProjectableRoot(t0, t1, ind0, ind1, tRoot);
	aRange.SetFirst(tRoot);
	aRange.SetLast(t1);
	myProjectableRanges.Append(aRange);
      }
      //
      if (ind0 && !ind1) {
	FindProjectableRoot(t0, t1, ind0, ind1, tRoot);
	aRange.SetLast(tRoot);
	myProjectableRanges.Append(aRange);
      }
      //
      break;
    }
    
    if (ind0 != ind1) {
      FindProjectableRoot(t0, t1, ind0, ind1, tRoot);
      
      if (ind0 && !ind1) {
	aRange.SetLast(tRoot);
	myProjectableRanges.Append(aRange);
      }
      else {
	aRange.SetFirst(tRoot);
      }
    } // if (ind0 != ind1)
    ind0=ind1;
  } // for(i=1; i<aNb; i++) {
}

//=======================================================================
//function : FindProjectableRoot
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::FindProjectableRoot (const Standard_Real tt1,
					       const Standard_Real tt2,
					       const Standard_Integer ff1,
					       const Standard_Integer ff2,
					       Standard_Real& tRoot)
{
  Standard_Real tm, t1, t2, aEpsT;
  Standard_Integer anIsProj1, anIsProj2, anIsProjm;
  aEpsT=0.5*myEpsT;
  //
  // Root is inside [tt1, tt2]
  t1=tt1;  
  t2=tt2;
  anIsProj1=ff1;
  anIsProj2=ff2;
  
  while (1) {
    if (fabs(t1-t2) < aEpsT) {
      tRoot=(anIsProj1) ? t1 : t2;
      return;
    }
    tm=.5*(t1+t2);
    anIsProjm=IsProjectable(tm);
    
    if (anIsProjm != anIsProj1) {
      t2=tm;
      anIsProj2=anIsProjm;
    }
    else {
      t1=tm;
      anIsProj1=anIsProjm;
    }
  }
}
//=======================================================================
//function : IsProjectable
//purpose  : 
//=======================================================================
  Standard_Boolean IntTools_EdgeFace::IsProjectable(const Standard_Real t) const
{
  Standard_Boolean bFlag;
  Standard_Real Umin, Usup, Vmin, Vsup;

  const Handle(Geom_Surface)& GS=BRep_Tool::Surface(myFace);
  Umin=myS.FirstUParameter();
  Usup=myS.LastUParameter();
  Vmin=myS.FirstVParameter();
  Vsup=myS.LastVParameter ();
  
  gp_Pnt P;
  myC.D0(t, P);
  GeomAPI_ProjectPointOnSurf aProjector;
  //
  Standard_Real ULD = 0.0, VLD = 0.0;

  if(myContext == NULL) {
    aProjector.Init(P, GS, Umin, Usup, Vmin, Vsup, myEpsT);
    bFlag=aProjector.IsDone();
    
    if(bFlag) {
      aProjector.LowerDistanceParameters(ULD, VLD);
    }
  }
  else {
    GeomAPI_ProjectPointOnSurf& aLocProj = myContext->ProjPS(myFace);
    aLocProj.Perform(P);
    bFlag = aLocProj.IsDone();
    
    if(bFlag) {
      aLocProj.LowerDistanceParameters(ULD, VLD);
    }
  }
  //

  if (bFlag) {
    bFlag=Standard_False;

    // 
    TopAbs_State aState;
    gp_Pnt2d aP2d(ULD, VLD);

    if(myContext == NULL) {
      aState=myFClass2d.Perform(aP2d);
    }
    else {
      aState = myContext->FClass2d(myFace).Perform(aP2d);
    }
    //
    
    if (aState==TopAbs_IN || aState==TopAbs_ON) {
      bFlag=Standard_True;
    }
  }
  return bFlag;
}

//=======================================================================
//function : DistanceFunction
//purpose  : 
//=======================================================================
  Standard_Real IntTools_EdgeFace::DistanceFunction(const Standard_Real t)
{
  Standard_Real Umin, Usup, Vmin, Vsup, aD;
  //
  gp_Pnt P;
  myC.D0(t, P);
  //
  Standard_Boolean bIsEqDistance;

  bIsEqDistance= IntTools_EdgeFace::IsEqDistance(P, myS, 1.e-7, aD); 
  if (bIsEqDistance) {
    aD=aD-myCriteria;
    return aD; 
  }
  //
  const Handle(Geom_Surface)& GS=BRep_Tool::Surface(myFace);
  
  Umin=myS.FirstUParameter();
  Usup=myS.LastUParameter();
  Vmin=myS.FirstVParameter();
  Vsup=myS.LastVParameter ();
  
  //
  Standard_Boolean bFlag = Standard_False;

  if(myContext == NULL) {
    GeomAPI_ProjectPointOnSurf aProjector;
    aProjector.Init(P, GS, Umin, Usup, Vmin, Vsup, myEpsT);
    bFlag=aProjector.IsDone();

    if(bFlag) {
      aD=aProjector.LowerDistance();
    }
  }
  else {
    GeomAPI_ProjectPointOnSurf& aLocProj = myContext->ProjPS(myFace);
    aLocProj.Perform(P);
    bFlag = aLocProj.IsDone();
    
    if(bFlag) {
      aD = aLocProj.LowerDistance();
    }
  }
  //
  
  if (!bFlag) {
    myErrorStatus=11;
    return 99.;
  }
  
  // 
  //   aD=aProjector.LowerDistance();
  // 
  aD=aD-myCriteria;
  return aD; 
}
//
//=======================================================================
//function : IsEqDistance
//purpose  : 
//=======================================================================
  Standard_Boolean IntTools_EdgeFace::IsEqDistance(const gp_Pnt& aP,
						   const BRepAdaptor_Surface& aBAS,
						   const Standard_Real aTol,
						   Standard_Real& aD)
{
  Standard_Boolean bRetFlag=Standard_True;

  GeomAbs_SurfaceType aSurfType=aBAS.GetType();

  if (aSurfType==GeomAbs_Cylinder) {
    gp_Cylinder aCyl=aBAS.Cylinder();
    const gp_Ax1& anAx1  =aCyl.Axis();
    gp_Lin aLinAxis(anAx1);
    Standard_Real aDC, aRadius=aCyl.Radius();
    aDC=aLinAxis.Distance(aP);
    if (aDC < aTol) {
      aD=aRadius;
      return bRetFlag; 
    }
  }

  if (aSurfType==GeomAbs_Cone) {
    gp_Cone aCone=aBAS.Cone();
    const gp_Ax1& anAx1  =aCone.Axis();
    gp_Lin aLinAxis(anAx1);
    Standard_Real aDC, aRadius, aDS, aSemiAngle;
    aDC=aLinAxis.Distance(aP);
    if (aDC < aTol) {
      gp_Pnt anApex=aCone.Apex();
      aSemiAngle=aCone.SemiAngle();
      aDS=aP.Distance(anApex);
      
      aRadius=aDS*tan(aSemiAngle);
      aD=aRadius;
      return bRetFlag; 
    }
  }

  if (aSurfType==GeomAbs_Torus) {
    Standard_Real aMajorRadius, aMinorRadius, aDC;

    gp_Torus aTorus=aBAS.Torus();
    gp_Pnt aPLoc=aTorus.Location();
    aMajorRadius=aTorus.MajorRadius();
    
    aDC=fabs(aPLoc.Distance(aP)-aMajorRadius);
    if (aDC < aTol) {
      aMinorRadius=aTorus.MinorRadius();
      aD=aMinorRadius;
      return bRetFlag; 
    }
  }
  return !bRetFlag; 
}
//
//=======================================================================
//function : PrepareArgsFuncArrays
//purpose  : Obtain 
//           myFuncArray and myArgsArray for the interval [ta, tb]
//=======================================================================		
  void IntTools_EdgeFace::PrepareArgsFuncArrays(const Standard_Real ta,
						const Standard_Real tb)
{
  IntTools_CArray1OfReal anArgs, aFunc;
  Standard_Integer i, aNb, pri;
  Standard_Real t, f, f1;
  //
  // Prepare values of arguments for the interval [ta, tb]
  pri=IntTools::PrepareArgs (myC, tb, ta, myDiscret, myDeflection, anArgs);
  
  if (pri) {
    myErrorStatus=8;
    return;
  }
  //...
  aNb=anArgs.Length();

  if (!aNb){
    myErrorStatus=9;
    return;
  }
  //
  // Prepare values of functions for the interval [ta, tb]
  aFunc.Resize(aNb);
  for (i=0; i<aNb; i++) {
    t=anArgs(i);
    f1=DistanceFunction(t);
    f=f1+myCriteria; 

    if (myErrorStatus==11)
      return;
    
    if (f1 < myEpsNull) { 
      f=0.;
    }
    aFunc(i)=f;
  }
  //
  // Add points where the derivative = 0  
  AddDerivativePoints(anArgs, aFunc);

}


//=======================================================================
//function : AddDerivativePoints
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::AddDerivativePoints(const IntTools_CArray1OfReal& t,
					      const IntTools_CArray1OfReal& f)  
{
  Standard_Integer i, j, n, k, nn=100;
  Standard_Real fr, tr, tr1, dEpsNull=10.*myEpsNull;
  IntTools_CArray1OfReal fd;
  TColStd_SequenceOfReal aTSeq, aFSeq;  

  n=t.Length();
  fd.Resize(n+1);
  //
  // Table of derivatives
  Standard_Real dfx, tx, tx1, fx, fx1, dt=1.e-6;
  // Left limit
  tx=t(0);
  tx1=tx+dt;
  fx=f(0);
  fx1=DistanceFunction(tx1);
  fx1=fx1+myCriteria;
  if (fx1 < myEpsNull) { 
    fx1=0.;
  }
  dfx=(fx1-fx)/dt;
  fd(0)=dfx;
  
  if (fabs(fd(0)) < dEpsNull){
    fd(0)=0.;
  }
  

  k=n-1;
  for (i=1; i<k; i++) {
    Standard_Real ti, ti1;
    ti=t(i);
    ti1=t(i-1);
    fd(i)=.5*(f(i+1)-f(i-1))/(t(i)-t(i-1));
    if (fabs(fd(i)) < dEpsNull){
      fd(i)=0.;
    }
  }
  // Right limit
  tx=t(n-1);
  tx1=tx-dt;
  fx=f(n-1);
  fx1=DistanceFunction(tx1);
  fx1=fx1+myCriteria;
  if (fx1 < myEpsNull) { 
    fx1=0.;
  }
  dfx=(fx-fx1)/dt;
  fd(n-1)=dfx;
  
  if (fabs(fd(n-1)) < dEpsNull){
    fd(n-1)=0.;
  }
  //
  // Finding the range where the derivatives have different signs
  // for neighbouring points
  for (i=1; i<n; i++) {
    Standard_Real fd1, fd2, t1, t2;
    t1 =t(i-1);
    t2 =t(i);
    fd1=fd(i-1);
    fd2=fd(i);

    if (fd1*fd2 < 0.) {
      if (fabs(fd1) < myEpsNull) {
	tr=t1;
	fr=DistanceFunction(tr);//fd1;
      }
      else if (fabs(fd2) < myEpsNull) {
	tr=t2;
	fr=DistanceFunction(tr);
      }
      else {
	tr=FindSimpleRoot(2, t1, t2, fd1);
	fr=DistanceFunction(tr);
      }
      
      aTSeq.Append(tr);
      aFSeq.Append(fr);
    }
  } // end of for (i=1; i<n; i++)
  //
  // remove identical t, f
  nn=aTSeq.Length();
  if (nn) {
    for (i=1; i<=aTSeq.Length(); i++) {
      tr=aTSeq(i);
      for (j=0; j<n; j++) {
	tr1=t(j);
	if (fabs (tr1-tr) < myEpsT) {
	  aTSeq.Remove(i);
	  aFSeq.Remove(i);
	}
      }
    }
    nn=aTSeq.Length();
  }
  //
  // sorting args and funcs in increasing order
  if (nn) {
    k=nn+n;
    IntTools_Array1OfRange anArray1OfRange(1, k);
    for (i=1; i<=n; i++) {
      anArray1OfRange(i).SetFirst(t(i-1));
      anArray1OfRange(i).SetLast (f(i-1));
    }
    for (i=1; i<=nn; i++) {
      anArray1OfRange(n+i).SetFirst(aTSeq(i));
      anArray1OfRange(n+i).SetLast (aFSeq(i));
    }
    
    IntTools_QuickSortRange aQuickSortRange;
    IntTools_CompareRange aComparator;
    aQuickSortRange.Sort (anArray1OfRange, aComparator);
    
    // filling the  output arrays
    myArgsArray.Resize(k);
    myFuncArray.Resize(k);
    for (i=1; i<=k; i++) {
      myArgsArray(i-1)=anArray1OfRange(i).First();
      myFuncArray(i-1)=anArray1OfRange(i).Last ();
    }
  }
  
  else { // nn=0
    myArgsArray.Resize(n);
    myFuncArray.Resize(n);
    for (i=0; i<n; i++) {
      myArgsArray(i)=t(i); 
      myFuncArray(i)=f(i); 
    }
  }
}

//=======================================================================
//function : DerivativeFunction
//purpose  : 
//=======================================================================
  Standard_Real IntTools_EdgeFace::DerivativeFunction(const Standard_Real t2)
{
  Standard_Real t1, t3, aD1, aD2, aD3;
  Standard_Real dt=1.e-9;
  t1=t2-dt;
  aD1=DistanceFunction(t1);
  t3=t2+dt;
  aD3=DistanceFunction(t3);
  
  aD2=.5*(aD3-aD1)/dt;
  return aD2; 
}

//=======================================================================
//function : FindSimpleRoot
//purpose  : [private]
//=======================================================================
  Standard_Real IntTools_EdgeFace::FindSimpleRoot (const Standard_Integer IP,
						   const Standard_Real tA,
						   const Standard_Real tB,
						   const Standard_Real fA)
{
  Standard_Real r, a, b, y, x0, s;
  
  a=tA; b=tB; r=fA;
  
  while (1) {
    x0=.5*(a+b);

    if (IP==1)
      y=DistanceFunction(x0);
    else 
      y=DerivativeFunction(x0);
    
    if (fabs(b-a) < myEpsT || y==0.) {
      return x0;
    }
    
        
    s=y*r;

    if (s<0.) {
      b=x0;
      continue;
    }

    if (s>0.) {
      a=x0; r=y;
    }
  }
}
//=======================================================================
//function : FindGoldRoot
//purpose  : [private]
//=======================================================================
  Standard_Real IntTools_EdgeFace::FindGoldRoot (const Standard_Real tA,
						 const Standard_Real tB,
						 const Standard_Real coeff)
{
  Standard_Real gs=0.61803399;
  Standard_Real a, b, xp, xl, yp, yl;

  a=tA;  b=tB;
  
  xp=a+(b-a)*gs;
  xl=b-(b-a)*gs;
  yp=coeff*DistanceFunction(xp);
  yl=coeff*DistanceFunction(xl);
  
 
  while (1) {
    
    if (fabs(b-a) < myEpsT) {
      return .5*(b+a);
    }
    
    if (yp < yl) {
      a=xl;
      xl=xp;
      xp=a+(b-a)*gs;
      yp=coeff*DistanceFunction(xp);
    }
    
    else {
      b=xp;
      xp=xl;
      yp=yl;
      xl=b-(b-a)*gs;
      yl=coeff*DistanceFunction(xl);
    }
  }
}  

//=======================================================================
//function : MakeType
//purpose  : 
//=======================================================================
  Standard_Integer IntTools_EdgeFace::MakeType(IntTools_CommonPrt&  aCommonPrt)
{
  Standard_Real  af1, al1;
  Standard_Real df1, tm;
  Standard_Boolean bAllNullFlag;
  //
  bAllNullFlag=aCommonPrt.AllNullFlag();
  if (bAllNullFlag) {
    aCommonPrt.SetType(TopAbs_EDGE);
    return 0;
  }
  //
  aCommonPrt.Range1(af1, al1);

  {
    gp_Pnt aPF, aPL;
    myC.D0(af1, aPF);
    myC.D0(al1, aPL);
    df1=aPF.Distance(aPL);
    Standard_Boolean isWholeRange = Standard_False;
    
    if((Abs(af1 - myRange.First()) < myC.Resolution(myCriteria)) &&
       (Abs(al1 - myRange.Last()) < myC.Resolution(myCriteria)))
      isWholeRange = Standard_True;

    
    if ((df1 > myCriteria * 2.) && isWholeRange) {
      aCommonPrt.SetType(TopAbs_EDGE);
    }
    else {
      if(isWholeRange) {
	tm = (af1 + al1) * 0.5;

	if(aPF.Distance(myC.Value(tm)) > myCriteria * 2.) {
	  aCommonPrt.SetType(TopAbs_EDGE);
	  return 0;
	}
      }

      if(!CheckTouch(aCommonPrt, tm)) {
	tm = (af1 + al1) * 0.5;
      }
      aCommonPrt.SetType(TopAbs_VERTEX);
      aCommonPrt.SetVertexParameter1(tm);
      aCommonPrt.SetRange1 (af1, al1);
    }
    return 0;
  }

#if 0 // @todo Should this code really be removed? (a test will be appropriate)
  //
  dt=al1-af1;
  if (dt<1.e-5) {
    gp_Pnt aPF, aPL;
    myC.D0(af1, aPF);
    myC.D0(al1, aPL);
    df1=aPF.Distance(aPL);
    if (df1<myCriteria) {
      //
      tm=.5*(af1+al1);
      aCommonPrt.SetType(TopAbs_VERTEX);
      aCommonPrt.SetVertexParameter1(tm);
      aCommonPrt.SetRange1 (af1, al1);
      return 0;
    }
  }
  //
  IsIntersection (af1, al1);
  //
  if (!myParallel) {
    aCommonPrt.SetType(TopAbs_VERTEX);
    aCommonPrt.SetVertexParameter1(myPar1);
    aCommonPrt.SetRange1 (af1, al1);
  }
  else {
    dt=al1-af1;
    if (dt<1.e-5) {
      df1=DistanceFunction(af1);
      df2=DistanceFunction(al1);
      tm=(df1 < df2) ? af1 : al1;
      aCommonPrt.SetType(TopAbs_VERTEX);
      aCommonPrt.SetVertexParameter1(tm);
      aCommonPrt.SetRange1 (af1, al1);
    }

    else {
      aCommonPrt.SetType(TopAbs_EDGE);
    }
  }
  return 0;
#endif
}


//=======================================================================
//function : IsIntersection
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::IsIntersection (const Standard_Real ta, 
					  const Standard_Real tb) 
{
  IntTools_CArray1OfReal anArgs, aFunc;
  Standard_Integer i, aNb, pri, aCnt=0;
  //
  Standard_Integer aCntIncreasing=1, aCntDecreasing=1;
  Standard_Real t, f, f1;
  //
  // Prepare values of arguments for the interval [ta, tb]
  pri=IntTools::PrepareArgs (myC, tb, ta, myDiscret, myDeflection, anArgs);
  aNb=anArgs.Length();
  
  aFunc.Resize(aNb);
  for (i=0; i<aNb; i++) {
    t=anArgs(i);
    
    f1=DistanceFunction(t);
    f=f1+myCriteria; 

    if (fabs(f1) < myEpsNull) { 
      aCnt++;
      f=0.;
    }
    aFunc(i)=f;
    //
    if (i) {
      if (aFunc(i)>aFunc(i-1)) {
	aCntIncreasing++;
      }
      if (aFunc(i)<aFunc(i-1)) {
	aCntDecreasing++;
      }
    }
    //
  }

  if (aCnt==aNb) {
    myParallel=Standard_True;
    return;
  }
  
  FindDerivativeRoot(anArgs, aFunc);

  //
  if (myParallel) {
    if (!(myC.GetType()==GeomAbs_Line 
	  && 
	  myS.GetType()==GeomAbs_Cylinder)) {
      if (aCntDecreasing==aNb) {
	myPar1=anArgs(aNb-1);
	myParallel=Standard_False;
      }
      if (aCntIncreasing==aNb) {
	myPar1=anArgs(0);
	myParallel=Standard_False;
      }
    }
  }
  //
  return ;
}

//=======================================================================
//function : FindDerivativeRoot
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::FindDerivativeRoot(const IntTools_CArray1OfReal& t,
					     const IntTools_CArray1OfReal& f)  
{
  Standard_Integer i, n, k;
  Standard_Real fr, tr;
  IntTools_CArray1OfReal fd;
  TColStd_SequenceOfReal aTSeq, aFSeq;  
  
  myPar1=0.;
  myParallel=Standard_True;
  
  n=t.Length();
  fd.Resize(n+1);
  //
  // Table of derivatives
  fd(0)=(f(1)-f(0))/(t(1)-t(0));
  if (fabs(fd(0)) < myEpsNull) {
    fd(0)=0.;
  }

  k=n-1;
  for (i=1; i<k; i++) {
    fd(i)=.5*(f(i+1)-f(i-1))/(t(i)-t(i-1));
    if (fabs(fd(i)) < myEpsNull) {
      fd(i)=0.;
    }
  }

  fd(n-1)=(f(n-1)-f(n-2))/(t(n-1)-t(n-2));
  if (fabs(fd(n-1)) < myEpsNull) {
    fd(n-1)=0.;
  }
  //
  // Finding the range where the derivatives have different signs
  // for neighbouring points
  for (i=1; i<n; i++) {
    Standard_Real fd1, fd2, t1, t2, fabsfd1, fabsfd2;
    Standard_Boolean bF1, bF2;
    t1 =t(i-1);
    t2 =t(i);
    fd1=fd(i-1);
    fd2=fd(i);

    fabsfd1=fabs(fd1);
    bF1=fabsfd1 < myEpsNull;
    
    fabsfd2=fabs(fd2);
    bF2=fabsfd2 < myEpsNull;
    //
    if (fd1*fd2 < 0.) {
      tr=FindSimpleRoot(2, t1, t2, fd1);
      fr=DistanceFunction(tr);
      myPar1=tr;
      myParallel=Standard_False;
      break;
    }
    
    if (!bF1 && bF2) {
      tr=t2;
      fr=fd2;
      myPar1=tr;
      myParallel=Standard_False;
      break;
    }
    
    if (bF1 && !bF2) {
      tr=t1;
      fr=fd1;
      myPar1=tr;
      myParallel=Standard_False;
      break;
    }

  }
}
//=======================================================================
//function : RemoveIdenticalRoots 
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::RemoveIdenticalRoots()
{
  Standard_Integer aNbRoots, j, k;

  aNbRoots=mySequenceOfRoots.Length();
  for (j=1; j<=aNbRoots; j++) { 
    const IntTools_Root& aRj=mySequenceOfRoots(j);
    for (k=j+1; k<=aNbRoots; k++) {
      const IntTools_Root& aRk=mySequenceOfRoots(k);
      
      Standard_Real aTj, aTk, aDistance;
      gp_Pnt aPj, aPk;

      aTj=aRj.Root();
      aTk=aRk.Root();

      myC.D0(aTj, aPj);
      myC.D0(aTk, aPk);

      aDistance=aPj.Distance(aPk);
      if (aDistance < myCriteria) {
	mySequenceOfRoots.Remove(k);
	aNbRoots=mySequenceOfRoots.Length();
      }
    }
  }
}

//=======================================================================
//function : CheckTouch 
//purpose  : 
//=======================================================================
  Standard_Boolean IntTools_EdgeFace::CheckTouch(const IntTools_CommonPrt& aCP,
						 Standard_Real&            aTx) 
{
  Standard_Real aTF, aTL, Tol, U1f, U1l, V1f, V1l, af, al,aDist2, aMinDist2;
  Standard_Boolean theflag=Standard_False;
  Standard_Integer aNbExt, i, iLower ;

  aCP.Range1(aTF, aTL);

  //
  Standard_Real aCR;
  aCR=myC.Resolution(myCriteria);
  if((Abs(aTF - myRange.First()) < aCR) &&
     (Abs(aTL - myRange.Last())  < aCR)) {
    return theflag; // EDGE 
  }
  //

  Tol = Precision::PConfusion();

  const Handle(Geom_Curve)&  Curve   =BRep_Tool::Curve  (myC.Edge(), af, al);
  const Handle(Geom_Surface)& Surface=BRep_Tool::Surface(myS.Face());
  //   Surface->Bounds(U1f,U1l,V1f,V1l);
  U1f = myS.FirstUParameter();
  U1l = myS.LastUParameter();
  V1f = myS.FirstVParameter();
  V1l = myS.LastVParameter();
  
  GeomAdaptor_Curve   TheCurve   (Curve,aTF, aTL);
  GeomAdaptor_Surface TheSurface (Surface, U1f, U1l, V1f, V1l); 
				 
  Extrema_ExtCS anExtrema (TheCurve, TheSurface, Tol, Tol);

  aDist2 = 1.e100;

  if(anExtrema.IsDone()) {
    aMinDist2 = aDist2;

    if(!anExtrema.IsParallel()) {
      aNbExt=anExtrema.NbExt();
      
      if(aNbExt > 0) {
	iLower=1;
	for (i=1; i<=aNbExt; i++) {
	  aDist2=anExtrema.SquareDistance(i);
	  if (aDist2 < aMinDist2) {
	    aMinDist2=aDist2;
	    iLower=i;
	  }
	}
	aDist2=anExtrema.SquareDistance(iLower);
	Extrema_POnCurv aPOnC;
	Extrema_POnSurf aPOnS;
	anExtrema.Points(iLower, aPOnC, aPOnS);
	aTx=aPOnC.Parameter();
      }
      else {
	// modified by NIZHNY-MKK  Thu Jul 21 11:35:32 2005.BEGIN
	IntCurveSurface_HInter anExactIntersector;
  
	Handle(GeomAdaptor_HCurve) aCurve     = new GeomAdaptor_HCurve(TheCurve);
	Handle(GeomAdaptor_HSurface) aSurface = new GeomAdaptor_HSurface(TheSurface);
	
	anExactIntersector.Perform(aCurve, aSurface);

	if(anExactIntersector.IsDone()) {
	  Standard_Integer i = 0;

	  for(i = 1; i <= anExactIntersector.NbPoints(); i++) {
	    const IntCurveSurface_IntersectionPoint& aPoint = anExactIntersector.Point(i);
      
	    if((aPoint.W() >= aTF) && (aPoint.W() <= aTL)) {
	      aDist2=0.;
	      aTx = aPoint.W();
	    }
	  }
	}
	// modified by NIZHNY-MKK  Thu Jul 21 11:35:40 2005.END
      }
    }
    else {
      return theflag;
    }
  }

  Standard_Real aBoundaryDist;

  aBoundaryDist = DistanceFunction(aTF) + myCriteria;
  if(aBoundaryDist * aBoundaryDist < aDist2) {
    aDist2 = aBoundaryDist * aBoundaryDist;
    aTx = aTF;
  }
  
  aBoundaryDist = DistanceFunction(aTL) + myCriteria;
  if(aBoundaryDist * aBoundaryDist < aDist2) {
    aDist2 = aBoundaryDist * aBoundaryDist;
    aTx = aTL;
  }

  Standard_Real aParameter = (aTF + aTL) * 0.5;
  aBoundaryDist = DistanceFunction(aParameter) + myCriteria;
  if(aBoundaryDist * aBoundaryDist < aDist2) {
    aDist2 = aBoundaryDist * aBoundaryDist;
    aTx = aParameter;
  }

  if(aDist2 > myCriteria * myCriteria) {
    return theflag;
  }
  
  if (fabs (aTx-aTF) < myEpsT) {
    return !theflag;
  }

  if (fabs (aTx-aTL) < myEpsT) {
    return !theflag;
  }

  if (aTx>aTF && aTx<aTL) {
    return !theflag;
  }

  return theflag;
}

//=======================================================================
//function : SetContext
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::SetContext(const IntTools_PContext& theContext) 
{
  myContext = theContext;
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================
  void IntTools_EdgeFace::Perform() 
{
  Standard_Integer i, aNb;
  IntTools_CommonPrt aCommonPrt;
  //IntTools_Root aRoot; // Wng in Gcc 3.0
  //...

  aCommonPrt.SetEdge1(myEdge);
  //
  //
  myErrorStatus=0;
  CheckData();
  if (myErrorStatus)
    return;

  myIsDone = Standard_False;
  myC.Initialize(myEdge);
  GeomAbs_CurveType aCurveType;
  aCurveType=myC.GetType();
  //
  // Prepare myCriteria
  if (aCurveType==GeomAbs_BSplineCurve||
	aCurveType==GeomAbs_BezierCurve) {
    //--- 5112
    Standard_Real diff1 = (myTolE/myTolF);
    Standard_Real diff2 = (myTolF/myTolE);
    if( diff1 > 100 || diff2 > 100 ) {
      myCriteria = Max(myTolE,myTolF);
    }
    else //--- 5112
      myCriteria=1.5*myTolE+myTolF;
  }
  else {
    myCriteria=myTolE+myTolF;
  }

  myTmin=myRange.First();
  myTmax=myRange.Last();

  myS.Initialize (myFace,Standard_True);

  if(myContext == NULL) {
    myFClass2d.Init(myFace, 1.e-6);
  }

  IntTools_BeanFaceIntersector anIntersector(myC, myS, myTolE, myTolF);
  anIntersector.SetBeanParameters(myRange.First(), myRange.Last());
  //
  anIntersector.SetContext(myContext);
  //
  anIntersector.Perform();

  if(!anIntersector.IsDone()) {
    return;
  }

  for(Standard_Integer r = 1; r <= anIntersector.Result().Length(); r++) {
    const IntTools_Range& aRange = anIntersector.Result().Value(r);
    
    if(IsProjectable(IntTools_Tools::IntermediatePoint(aRange.First(), aRange.Last()))) {
      aCommonPrt.SetRange1(aRange.First(), aRange.Last());
      mySeqOfCommonPrts.Append(aCommonPrt);
    }
  }

  aNb = mySeqOfCommonPrts.Length();

  for (i=1; i<=aNb; i++) {
    IntTools_CommonPrt& aCP=mySeqOfCommonPrts.ChangeValue(i);
    //
    Standard_Real aTx1, aTx2;
    gp_Pnt aPx1, aPx2;
    //
    aCP.Range1(aTx1, aTx2);
    myC.D0(aTx1, aPx1);
    myC.D0(aTx2, aPx2);
    aCP.SetBoundingPoints(aPx1, aPx2);
    //
    MakeType (aCP); 
  }
  {
    // Line\Cylinder's Common Parts treatement
    GeomAbs_CurveType   aCType;
    GeomAbs_SurfaceType aSType;
    TopAbs_ShapeEnum aType;
    Standard_Boolean bIsTouch;
    Standard_Real aTx;

    aCType=myC.GetType();
    aSType=myS.GetType();
    
    if (aCType==GeomAbs_Line && aSType==GeomAbs_Cylinder) {
      for (i=1; i<=aNb; i++) {
	IntTools_CommonPrt& aCP=mySeqOfCommonPrts(i);
	aType=aCP.Type();
	if (aType==TopAbs_EDGE) {
	  bIsTouch=CheckTouch (aCP, aTx);
	  if (bIsTouch) {
	    aCP.SetType(TopAbs_VERTEX);
	    aCP.SetVertexParameter1(aTx);
	    aCP.SetRange1 (aTx, aTx);
	  }
	}
	if (aType==TopAbs_VERTEX) {
	  bIsTouch=CheckTouchVertex (aCP, aTx);
	  if (bIsTouch) {
	    aCP.SetVertexParameter1(aTx);
	    aCP.SetRange1 (aTx, aTx);
	  }
	}
      }
    }

    // Circle\Plane's Common Parts treatement
    
    if (aCType==GeomAbs_Circle && aSType==GeomAbs_Plane) {
      Standard_Boolean bIsCoplanar, bIsRadius;
      bIsCoplanar=IsCoplanar(myC, myS);
      bIsRadius=IsRadius(myC, myS);
      if (!bIsCoplanar && !bIsRadius) {
	for (i=1; i<=aNb; i++) {
	  IntTools_CommonPrt& aCP=mySeqOfCommonPrts(i);
	  aType=aCP.Type();
	  if (aType==TopAbs_EDGE) {
	    bIsTouch=CheckTouch (aCP, aTx);
	    if (bIsTouch) {
	      aCP.SetType(TopAbs_VERTEX);
	      aCP.SetVertexParameter1(aTx);
	      aCP.SetRange1 (aTx, aTx);
	    }
	  }
	}
      }
    }
  }
  myIsDone=Standard_True;
}

//
// myErrorStatus
// 1 - the method Perform() is not invoked  
// 2,3,4,5 -the method CheckData() fails
// 6 - PrepareArgs() problems
// 7 - No Projectable ranges
// 8,9 - PrepareArgs() problems occured inside  projectable Ranges
// 11 - can't fill array  aFunc(i) in PrepareArgsFuncArrays 


//=======================================================================
//function : CheckTouch 
//purpose  : 
//=======================================================================
  Standard_Boolean IntTools_EdgeFace::CheckTouchVertex (const IntTools_CommonPrt& aCP,
							Standard_Real& aTx) 
{
  Standard_Real aTF, aTL, Tol, U1f,U1l,V1f,V1l, af, al,aDist2, aMinDist2, aTm, aDist2New;
  Standard_Boolean theflag=Standard_False;
  Standard_Integer aNbExt, i, iLower ;

  aCP.Range1(aTF, aTL);

  aTm=0.5*(aTF+aTL);
  aDist2=DistanceFunction(aTm);
  aDist2 *= aDist2;

  Tol = Precision::PConfusion();

  const Handle(Geom_Curve)&  Curve   =BRep_Tool::Curve  (myC.Edge(), af, al);
  const Handle(Geom_Surface)& Surface=BRep_Tool::Surface(myS.Face());

  Surface->Bounds(U1f,U1l,V1f,V1l);
  
  GeomAdaptor_Curve   TheCurve   (Curve,aTF, aTL);
  GeomAdaptor_Surface TheSurface (Surface, U1f, U1l, V1f, V1l); 
				 
  Extrema_ExtCS anExtrema (TheCurve, TheSurface, Tol, Tol);
   
  if(!anExtrema.IsDone()) {
    return theflag;
  }
  if (anExtrema.IsParallel()) {
    return theflag;
  }
  
  aNbExt=anExtrema.NbExt() ;
  if (!aNbExt) {
     return theflag;
  }

  iLower=1;
  aMinDist2=1.e100;
  for (i=1; i<=aNbExt; ++i) {
    aDist2=anExtrema.SquareDistance(i);
    if (aDist2 < aMinDist2) {
      aMinDist2=aDist2;
      iLower=i;
    }
  }

  aDist2New=anExtrema.SquareDistance(iLower);
  
  if (aDist2New > aDist2) {
    aTx=aTm;
    return !theflag;
  }
  
  if (aDist2New > myCriteria * myCriteria) {
    return theflag;
  }

  Extrema_POnCurv aPOnC;
  Extrema_POnSurf aPOnS;
  anExtrema.Points(iLower, aPOnC, aPOnS);

  
  aTx=aPOnC.Parameter();
  
  if (fabs (aTx-aTF) < myEpsT) {
    return !theflag;
  }

  if (fabs (aTx-aTL) < myEpsT) {
    return !theflag;
  }

  if (aTx>aTF && aTx<aTL) {
    return !theflag;
  }

  return theflag;
}


//=======================================================================
//function :  IsCoplanar
//purpose  : 
//=======================================================================
Standard_Boolean IsCoplanar (const BRepAdaptor_Curve& aCurve ,
			       const BRepAdaptor_Surface& aSurface)
{
  Standard_Boolean bFlag=Standard_False;

  GeomAbs_CurveType   aCType;
  GeomAbs_SurfaceType aSType;

  aCType=aCurve.GetType();
  aSType=aSurface.GetType();
    
  if (aCType==GeomAbs_Circle && aSType==GeomAbs_Plane) {
    gp_Circ aCirc=aCurve.Circle();
    const gp_Ax1& anAx1=aCirc.Axis();
    const gp_Dir& aDirAx1=anAx1.Direction();
    
    gp_Pln aPln=aSurface.Plane();
    const gp_Ax1& anAx=aPln.Axis();
    const gp_Dir& aDirPln=anAx.Direction();

    bFlag=IntTools_Tools::IsDirsCoinside(aDirAx1, aDirPln);
  }
  return bFlag;
}
//=======================================================================
//function :  IsRadius
//purpose  : 
//=======================================================================
Standard_Boolean IsRadius (const BRepAdaptor_Curve& aCurve ,
			   const BRepAdaptor_Surface& aSurface)
{
  Standard_Boolean bFlag=Standard_False;

  GeomAbs_CurveType   aCType;
  GeomAbs_SurfaceType aSType;

  aCType=aCurve.GetType();
  aSType=aSurface.GetType();
    
  if (aCType==GeomAbs_Circle && aSType==GeomAbs_Plane) {
    gp_Circ aCirc=aCurve.Circle();
    const gp_Pnt aCenter=aCirc.Location();
    Standard_Real aR=aCirc.Radius();
    gp_Pln aPln=aSurface.Plane();
    Standard_Real aD=aPln.Distance(aCenter);
    if (fabs (aD-aR) < 1.e-7) {
      return !bFlag;
    }
  }
  return bFlag;
}
//
//=======================================================================
//function :  AdaptiveDiscret
//purpose  : 
//=======================================================================
Standard_Integer AdaptiveDiscret (const Standard_Integer iDiscret,
				  const BRepAdaptor_Curve& aCurve ,
				  const BRepAdaptor_Surface& aSurface)
{
  Standard_Integer iDiscretNew;

  iDiscretNew=iDiscret;

  GeomAbs_CurveType   aCType;
  GeomAbs_SurfaceType aSType;

  aCType=aCurve.GetType();
  aSType=aSurface.GetType();
    
  if (aSType==GeomAbs_Cylinder) {
   Standard_Real aELength, aRadius, dL, dLR;

   aELength=IntTools::Length(aCurve.Edge());
   dL=aELength/iDiscret;
   
   gp_Cylinder aCylinder=aSurface.Cylinder();
   aRadius=aCylinder.Radius();
   dLR=2*aRadius;

   iDiscretNew=(Standard_Integer)(aELength/dLR);
   
   if (iDiscretNew<iDiscret) {
     iDiscretNew=iDiscret;
   }
     
  }
  return iDiscretNew;
}


#ifdef _MSC_VER
#pragma warning ( default : 4101 )
#endif
