// File GccAna_Circ2d3Tan.cxx_6, REG 08/07/91

#include <GccAna_Circ2d3Tan.jxx>

#include <ElCLib.hxx>
#include <IntAna2d_AnaIntersection.hxx>
#include <IntAna2d_IntPoint.hxx>
#include <gp_Lin2d.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Dir2d.hxx>
#include <GccAna_LinPnt2dBisec.hxx>
#include <GccAna_Lin2dBisec.hxx>
#include <GccInt_IType.hxx>
#include <GccInt_BLine.hxx>
#include <GccInt_BParab.hxx>
#include <IntAna2d_Conic.hxx>
#include <GccEnt_BadQualifier.hxx>

//=========================================================================
//   Creation d un cercle tangent a deux droites et a un point.           +
//=========================================================================

GccAna_Circ2d3Tan::
   GccAna_Circ2d3Tan (const GccEnt_QualifiedLin&  Qualified1 ,
                      const GccEnt_QualifiedLin&  Qualified2 ,
                      const gp_Pnt2d&             Point3     ,
		      const Standard_Real         Tolerance  ):

   cirsol(1,2)     ,
   qualifier1(1,2) ,
   qualifier2(1,2) ,
   qualifier3(1,2) ,
   TheSame1(1,2)   ,
   TheSame2(1,2)   ,
   TheSame3(1,2)   ,
   pnttg1sol(1,2)  ,
   pnttg2sol(1,2)  ,
   pnttg3sol(1,2)  ,
   par1sol(1,2)    ,  
   par2sol(1,2)    ,
   par3sol(1,2)    ,
   pararg1(1,2)    ,
   pararg2(1,2)    ,
   pararg3(1,2)    
{

   gp_Dir2d dirx(1.0,0.0);
   WellDone = Standard_False;
   Standard_Real Tol = Abs(Tolerance);
   NbrSol = 0;
   if (!(Qualified1.IsEnclosed() ||
	 Qualified1.IsOutside() || Qualified1.IsUnqualified()) ||
       !(Qualified2.IsEnclosed() ||
	 Qualified2.IsOutside() || Qualified2.IsUnqualified())) {
     GccEnt_BadQualifier::Raise();
     return;
   }

   pnttg3sol.Init(Point3);

//=========================================================================
//   Traitement.                                                          +
//=========================================================================

   gp_Lin2d L1  = Qualified1.Qualified();
   gp_Lin2d L2  = Qualified2.Qualified();
   gp_Pnt2d origin1(L1.Location());
   gp_Dir2d dir1(L1.Direction());
   gp_Dir2d normL1(-dir1.Y(),dir1.X());
   gp_Pnt2d origin2(L2.Location());
   gp_Dir2d dir2(L2.Direction());
   gp_Dir2d normL2(-dir2.Y(),dir2.X());

   GccAna_Lin2dBisec Bis1(L1,L2);
   GccAna_LinPnt2dBisec Bis2(L1,Point3);
   if (Bis1.IsDone() && Bis2.IsDone()) {
     Standard_Integer nbsolution1 = Bis1.NbSolutions();
     Handle(GccInt_Bisec) Sol2 = Bis2.ThisSolution();
     for (Standard_Integer i = 1 ; i <=  nbsolution1; i++) {
#ifdef DEB
       gp_Lin2d Sol1(Bis1.ThisSolution(i));
#else
       Bis1.ThisSolution(i) ;
#endif
       GccInt_IType typ2 = Sol2->ArcType();
       IntAna2d_AnaIntersection Intp;
       if (typ2 == GccInt_Lin) {
	 Intp.Perform(Bis1.ThisSolution(i),Sol2->Line());
       }
       else if (typ2 == GccInt_Par) {
	 Intp.Perform(Bis1.ThisSolution(i),IntAna2d_Conic(Sol2->Parabola()));
       }
       if (Intp.IsDone()) {
	 if (!Intp.IsEmpty()) {
	   for (Standard_Integer j = 1 ; j <= Intp.NbPoints() ; j++) {
	     gp_Pnt2d Center(Intp.Point(j).Value());
	     Standard_Real dist1 = L1.Distance(Center);
	     Standard_Real dist2 = L2.Distance(Center);
	     Standard_Real dist3 = Center.Distance(Point3);
	     Standard_Real Radius=0;
	     Standard_Integer nbsol2 = 0;
	     Standard_Integer nbsol3 = 0;
	     Standard_Boolean ok = Standard_False;
	     if (Qualified1.IsEnclosed()) {
	       if ((((origin1.X()-Center.X())*(-dir1.Y()))+
		    ((origin1.Y()-Center.Y())*(dir1.X())))<=0){
		 ok = Standard_True;
		 Radius = dist1;
	       }
	     }
	     else if (Qualified1.IsOutside()) {
	       if ((((origin1.X()-Center.X())*(-dir1.Y()))+
		    ((origin1.Y()-Center.Y())*(dir1.X())))>=0){
		 ok = Standard_True;
		 Radius = dist1;
	       }
	     }
	     else if (Qualified1.IsUnqualified()) {
	       ok = Standard_True;
	       Radius = dist1;
	     }
	     if (Qualified2.IsEnclosed()) {
	       if ((((origin2.X()-Center.X())*(-dir2.Y()))+
		    ((origin2.Y()-Center.Y())*(dir2.X())))<=0){
		 if (Abs(dist2-Radius) < Tol) { nbsol2 = 1; }
		 else { ok = Standard_False; }
	       }
	     }
	     else if (Qualified2.IsOutside() && ok) {
	       if ((((origin2.X()-Center.X())*(-dir2.Y()))+
		    ((origin2.Y()-Center.Y())*(dir2.X())))>=0){
		 if (Abs(dist2-Radius) < Tol) { nbsol2 = 1; }
		 else { ok = Standard_False; }
	       }
	     }
	     else if (Qualified2.IsUnqualified() && ok) {
	       if (Abs(dist2-Radius) < Tol) { nbsol2 = 1; }
	       else { ok = Standard_False; }
	     }
	     if (ok) {
	       if (Abs(dist3-Radius) < Tol) { nbsol3 = 1; }
	       else { ok = Standard_False; }
	     }
	     if (ok) {
	       for (Standard_Integer k = 1 ; k <= nbsol3 ; k++) {
		 NbrSol++;
		 cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center,dirx),Radius);
//               =======================================================
		 gp_Dir2d dc1(origin1.XY()-Center.XY());
		 if (!Qualified1.IsUnqualified()) { 
		   qualifier1(NbrSol) = Qualified1.Qualifier();
		 }
		 else if (dc1.Dot(normL1) > 0.0) {
		   qualifier1(NbrSol) = GccEnt_outside;
		 }
		 else { qualifier1(NbrSol) = GccEnt_enclosed; }
		 gp_Dir2d dc2(origin2.XY()-Center.XY());
		 if (!Qualified2.IsUnqualified()) { 
		   qualifier2(NbrSol) = Qualified2.Qualifier();
		 }
		 else if (dc2.Dot(normL2) > 0.0) {
		   qualifier2(NbrSol) = GccEnt_outside;
		 }
		 else { qualifier2(NbrSol) = GccEnt_enclosed; }
		 qualifier3(NbrSol) = GccEnt_noqualifier;
		 TheSame1(NbrSol) = 0;
		 gp_Dir2d dc(origin1.XY()-Center.XY());
		 Standard_Real sign = dc.Dot(gp_Dir2d(-dir1.Y(),dir1.X()));
		 dc = gp_Dir2d(sign*gp_XY(-dir1.Y(),dir1.X()));
		 pnttg1sol(NbrSol) = gp_Pnt2d(Center.XY()+Radius*dc.XY());
		 par1sol(NbrSol)=ElCLib::Parameter(cirsol(NbrSol),
						  pnttg1sol(NbrSol));
		 pararg1(NbrSol)=ElCLib::Parameter(L1,pnttg1sol(NbrSol));
		 TheSame2(NbrSol) = 0;
		 dc = gp_Dir2d(origin2.XY()-Center.XY());
		 sign = dc.Dot(gp_Dir2d(-dir2.Y(),dir2.X()));
		 dc = gp_Dir2d(sign*gp_XY(-dir2.Y(),dir2.X()));
		 pnttg2sol(NbrSol) = gp_Pnt2d(Center.XY()+Radius*dc.XY());
		 par2sol(NbrSol)=ElCLib::Parameter(cirsol(NbrSol),
						  pnttg2sol(NbrSol));
		 pararg2(NbrSol)=ElCLib::Parameter(L2,pnttg2sol(NbrSol));
		 TheSame3(NbrSol) = 0;
		 par3sol(NbrSol)=ElCLib::Parameter(cirsol(NbrSol),
						  pnttg3sol(NbrSol));
		 pararg3(NbrSol) = 0.;
	       }
	     }
	   }
	 }
	 WellDone = Standard_True;
       }
     }
   }
 }

