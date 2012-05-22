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

//#ifndef DEB
#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError
//#endif

#include <math_BFGS.ixx>

#include <math_BracketMinimum.hxx>
#include <math_BrentMinimum.hxx>
#include <math_FunctionWithDerivative.hxx>
#include <math_MultipleVarFunctionWithGradient.hxx>
#include <math_Matrix.hxx>

#define R 0.61803399
#define C (1.0-R)
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);
#define SIGN(a, b) ((b) > 0.0 ? fabs(a) : -fabs(a))
#define MOV3(a,b,c, d, e, f) (a)=(d); (b)= (e); (c)=(f);


// l'utilisation de math_BrentMinumim pur trouver un minimum dans une direction
// donnee n'est pas du tout optimale. voir peut etre interpolation cubique
// classique et aussi essayer "recherche unidimensionnelle economique"
// PROGRAMMATION MATHEMATIQUE (theorie et algorithmes) tome1 page 82.

class DirFunction : public math_FunctionWithDerivative {

     math_Vector *P0;
     math_Vector *Dir;
     math_Vector *P;
     math_Vector *G;
     math_MultipleVarFunctionWithGradient *F;

public :

     DirFunction(math_Vector& V1, 
                 math_Vector& V2,
                 math_Vector& V3,
		 math_Vector& V4,
                 math_MultipleVarFunctionWithGradient& f) ;

     void Initialize(const math_Vector& p0, const math_Vector& dir) const;
     void TheGradient(math_Vector& Grad);
     virtual Standard_Boolean Value(const Standard_Real x, Standard_Real& fval) ;
     virtual Standard_Boolean Values(const Standard_Real x, Standard_Real& fval, Standard_Real& D) ;
     virtual Standard_Boolean Derivative(const Standard_Real x, Standard_Real& D) ;

     
};

     DirFunction::DirFunction(math_Vector& V1, 
                              math_Vector& V2,
                              math_Vector& V3,
			      math_Vector& V4,
                              math_MultipleVarFunctionWithGradient& f) {
        
        P0  = &V1;
        Dir = &V2;
        P   = &V3;
        F   = &f;
	G =   &V4;
     }

     void DirFunction::Initialize(const math_Vector& p0, 
                                  const math_Vector& dir)  const{

        *P0 = p0;
        *Dir = dir;
     }

     void DirFunction::TheGradient(math_Vector& Grad) {
       Grad = *G;
     }


     Standard_Boolean DirFunction::Value(const Standard_Real x, 
					 Standard_Real& fval) 
     {
        *P = *Dir;
        P->Multiply(x);
        P->Add(*P0);        
        F->Value(*P, fval);
        return Standard_True;
     }

     Standard_Boolean DirFunction::Values(const Standard_Real x, 
					  Standard_Real& fval, 
					  Standard_Real& D) 
     {
        *P = *Dir;
        P->Multiply(x);
        P->Add(*P0);  
        F->Values(*P, fval, *G);
	D = (*G).Multiplied(*Dir);
        return Standard_True;
     }
     Standard_Boolean DirFunction::Derivative(const Standard_Real x, 
					      Standard_Real& D) 
     {
        *P = *Dir;
        P->Multiply(x);
        P->Add(*P0);        
	Standard_Real fval;
        F->Values(*P, fval, *G);
	D = (*G).Multiplied(*Dir);
        return Standard_True;
     }


static Standard_Boolean MinimizeDirection(math_Vector&   P,
					  Standard_Real  F0,
					  math_Vector&   Gr,
					  math_Vector&   Dir,
					  Standard_Real& Result,
					  DirFunction&   F) {



     Standard_Real ax, xx, bx, Fax, Fxx, Fbx, F1;
     F.Initialize(P, Dir);

     Standard_Real dy1, Hnr1, lambda, alfa=0;
     dy1 = Gr*Dir;
     if (dy1 != 0) {
       Hnr1 = Dir.Norm2();
       alfa = 0.7*(-F0)/dy1;
       lambda = 0.015/Sqrt(Hnr1);
     }
     else lambda = 1.0;
     if (lambda > alfa) lambda = alfa;
     F.Value(lambda, F1);
     math_BracketMinimum Bracket(F, 0.0, lambda, F0, F1);
     if(Bracket.IsDone()) {
       Bracket.Values(ax, xx, bx);
       Bracket.FunctionValues(Fax, Fxx, Fbx);

       Standard_Integer niter = 100;
       Standard_Real tol = 1.e-03;
       math_BrentMinimum Sol(tol, Fxx, niter, 1.e-08);
       Sol.Perform(F, ax, xx, bx);
       if(Sol.IsDone()) {
	 Standard_Real Scale = Sol.Location();
	 Result = Sol.Minimum();
	 Dir.Multiply(Scale);
	 P.Add(Dir);
	 return Standard_True;
       }
     }
     return Standard_False;
   }


void  math_BFGS::Perform(math_MultipleVarFunctionWithGradient& F,
                         const math_Vector& StartingPoint) {
  
       Standard_Boolean Good;
       Standard_Integer n = TheLocation.Length();
       Standard_Integer j, i;
       Standard_Real fae, fad, fac;

       math_Vector xi(1, n), dg(1, n), hdg(1, n);
       math_Matrix hessin(1, n, 1, n);
       hessin.Init(0.0);

       math_Vector Temp1(1, n);
       math_Vector Temp2(1, n);
       math_Vector Temp3(1, n);
       math_Vector Temp4(1, n);
       DirFunction F_Dir(Temp1, Temp2, Temp3, Temp4, F);

       TheLocation = StartingPoint;
       Good = F.Values(TheLocation, PreviousMinimum, TheGradient);
       if(!Good) { 
         Done = Standard_False;
         TheStatus = math_FunctionError;
         return;
       }
       for(i = 1; i <= n; i++) {
         hessin(i, i) = 1.0;
	 xi(i) = -TheGradient(i);
       }


       for(nbiter = 1; nbiter <= Itermax; nbiter++) {
	 TheMinimum = PreviousMinimum;
         Standard_Boolean IsGood = MinimizeDirection(TheLocation, TheMinimum,
						     TheGradient,
                                                     xi, TheMinimum, F_Dir);
         if(!IsGood) {
           Done = Standard_False;
           TheStatus = math_DirectionSearchError;
           return;
         }
         if(IsSolutionReached(F)) {
           Done = Standard_True;
           TheStatus = math_OK;
           return;
         }
	 if (nbiter == Itermax) {
	   Done = Standard_False;
	   TheStatus = math_TooManyIterations;
	   return;
	 }
         PreviousMinimum = TheMinimum;

	 dg = TheGradient;

         Good = F.Values(TheLocation, TheMinimum, TheGradient);
         if(!Good) { 
           Done = Standard_False;
           TheStatus = math_FunctionError;
           return;
         }

         for(i = 1; i <= n; i++) {
	   dg(i) = TheGradient(i) - dg(i);
	 }
	 for(i = 1; i <= n; i++) {
	   hdg(i) = 0.0;
	   for (j = 1; j <= n; j++) 
	     hdg(i) += hessin(i, j) * dg(j);
	 }
	 fac = fae = 0.0;
	 for(i = 1; i <= n; i++) {
	   fac += dg(i) * xi(i);
	   fae += dg(i) * hdg(i);
	 }
         fac = 1.0 / fac;
         fad = 1.0 / fae;

	 for(i = 1; i <= n; i++) 
	   dg(i) = fac * xi(i) - fad * hdg(i);
	 
         for(i = 1; i <= n; i++) 
           for(j = 1; j <= n; j++)
             hessin(i, j) += fac * xi(i) * xi(j)
               - fad * hdg(i) * hdg(j) + fae * dg(i) * dg(j);

	 for(i = 1; i <= n; i++) {
	   xi(i) = 0.0;
	   for (j = 1; j <= n; j++) xi(i) -= hessin(i, j) * TheGradient(j);
	 }  
       }
       Done = Standard_False;
       TheStatus = math_TooManyIterations;
       return;
   }

    Standard_Boolean math_BFGS::IsSolutionReached(
                           math_MultipleVarFunctionWithGradient&) const {

       return 2.0 * fabs(TheMinimum - PreviousMinimum) <= 
              XTol * (fabs(TheMinimum) + fabs(PreviousMinimum) + EPSZ);
    }

    math_BFGS::math_BFGS(math_MultipleVarFunctionWithGradient& F,
                         const math_Vector& StartingPoint, 
                         const Standard_Real        Tolerance,
                         const Standard_Integer     NbIterations,
                         const Standard_Real        ZEPS) 
                         : TheLocation(1, StartingPoint.Length()),
                           TheGradient(1, StartingPoint.Length()) {

       XTol = Tolerance;
       EPSZ = ZEPS;
       Itermax = NbIterations;
       Perform(F, StartingPoint);
    }
                             
    math_BFGS::math_BFGS(math_MultipleVarFunctionWithGradient& F,
                         const Standard_Real        Tolerance,
                         const Standard_Integer     NbIterations,
                         const Standard_Real        ZEPS) 
                         : TheLocation(1, F.NbVariables()),
                           TheGradient(1, F.NbVariables()) {

       XTol = Tolerance;
       EPSZ = ZEPS;
       Itermax = NbIterations;
    }


    void math_BFGS::Delete()
    {}

    void math_BFGS::Dump(Standard_OStream& o) const {

       o<< "math_BFGS resolution: ";
       if(Done) {
         o << " Status = Done \n";
	 o <<" Location Vector = " << Location() << "\n";
	 o <<" Minimum value = "<< Minimum()<<"\n";
	 o <<" Number of iterations = "<<NbIterations() <<"\n";;
       }
       else {
         o<< " Status = not Done because " << (Standard_Integer)TheStatus << "\n";
       }
    }



