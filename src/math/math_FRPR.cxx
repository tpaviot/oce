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

#include <math_FRPR.ixx>

#include <math_BracketMinimum.hxx>
#include <math_BrentMinimum.hxx>
#include <math_Function.hxx>
#include <math_MultipleVarFunction.hxx>
#include <math_MultipleVarFunctionWithGradient.hxx>

// l'utilisation de math_BrentMinumim pur trouver un minimum dans une direction
// donnee n'est pas du tout optimale. voir peut etre interpolation cubique
// classique et aussi essayer "recherche unidimensionnelle economique"
// PROGRAMMATION MATHEMATIQUE (theorie et algorithmes) tome1 page 82.

class DirFunctionTer : public math_Function {

     math_Vector *P0;
     math_Vector *Dir;
     math_Vector *P;
     math_MultipleVarFunction *F;

public :

     DirFunctionTer(math_Vector& V1, 
                 math_Vector& V2,
                 math_Vector& V3,
                 math_MultipleVarFunction& f);

     void Initialize(const math_Vector& p0, const math_Vector& dir);

     virtual Standard_Boolean Value(const Standard_Real x, Standard_Real& fval);
};

     DirFunctionTer::DirFunctionTer(math_Vector& V1, 
                              math_Vector& V2,
                              math_Vector& V3,
                              math_MultipleVarFunction& f) {
        
        P0  = &V1;
        Dir = &V2;
        P   = &V3;
        F   = &f;
     }

     void DirFunctionTer::Initialize(const math_Vector& p0, 
                                  const math_Vector& dir) {

        *P0 = p0;
        *Dir = dir;
     }

     Standard_Boolean DirFunctionTer::Value(const Standard_Real x, Standard_Real& fval) {

        *P = *Dir;
        P->Multiply(x);
        P->Add(*P0);        
        F->Value(*P, fval);
        return Standard_True;
     }

static Standard_Boolean MinimizeDirection(math_Vector& P,
                                 math_Vector& Dir,
                                 Standard_Real& Result,
                                 DirFunctionTer& F) {

     Standard_Real ax, xx, bx;

     F.Initialize(P, Dir);
     math_BracketMinimum Bracket(F, 0.0, 1.0);
     if(Bracket.IsDone()) {
       Bracket.Values(ax, xx, bx);
       math_BrentMinimum Sol(F, ax, xx, bx, 1.0e-10, 100);
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


void  math_FRPR::Perform(math_MultipleVarFunctionWithGradient& F,
                         const math_Vector& StartingPoint) {
  
       Standard_Boolean Good;
       Standard_Integer n = TheLocation.Length();
       Standard_Integer j, its;
       Standard_Real gg, gam, dgg;

       math_Vector g(1, n), h(1, n);
 
       math_Vector Temp1(1, n);
       math_Vector Temp2(1, n);
       math_Vector Temp3(1, n);
       DirFunctionTer F_Dir(Temp1, Temp2, Temp3, F);

       TheLocation = StartingPoint;
       Good = F.Values(TheLocation, PreviousMinimum, TheGradient);
       if(!Good) { 
         Done = Standard_False;
         TheStatus = math_FunctionError;
         return;
       }

       g = -TheGradient;
       h = g;
       TheGradient = g;

       for(its = 1; its <= Itermax; its++) {
	 Iter = its;
	 
         Standard_Boolean IsGood = MinimizeDirection(TheLocation,
                                            TheGradient, TheMinimum, F_Dir);
         if(!IsGood) {
           Done = Standard_False;
           TheStatus = math_DirectionSearchError;
           return;
         }
         if(IsSolutionReached(F)) {
           Done = Standard_True;
	   State = F.GetStateNumber();
           TheStatus = math_OK;
           return;
         }
         Good = F.Values(TheLocation, PreviousMinimum, TheGradient);
         if(!Good) { 
           Done = Standard_False;
           TheStatus = math_FunctionError;
           return;
         }

	 dgg =0.0;
	 gg = 0.0;
	 
	 for(j = 1; j<= n; j++) {
	   gg += g(j)*g(j);
//	   dgg += TheGradient(j)*TheGradient(j);  //for Fletcher-Reeves
	   dgg += (TheGradient(j)+g(j)) * TheGradient(j);  //for Polak-Ribiere
	 }

	 if (gg == 0.0) {
	   //Unlikely. If gradient is exactly 0 then we are already done.
	   Done = Standard_False;
	   TheStatus = math_FunctionError;
	   return;
	 }
	 
	 gam = dgg/gg;
	 g = -TheGradient;
	 TheGradient = g + gam*h;
	 h = TheGradient;
       }
       Done = Standard_False;
       TheStatus = math_TooManyIterations;
       return;

     }



    Standard_Boolean math_FRPR::IsSolutionReached(
//                           math_MultipleVarFunctionWithGradient& F) {
                           math_MultipleVarFunctionWithGradient& ) {

       return (2.0 * fabs(TheMinimum - PreviousMinimum)) <= 
              XTol * (fabs(TheMinimum) + fabs(PreviousMinimum) + EPSZ);
    }

    math_FRPR::math_FRPR(math_MultipleVarFunctionWithGradient& F,
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
                             

    math_FRPR::math_FRPR(math_MultipleVarFunctionWithGradient& F,
                         const Standard_Real        Tolerance,
                         const Standard_Integer     NbIterations,
                         const Standard_Real        ZEPS) 
                         : TheLocation(1, F.NbVariables()),
                           TheGradient(1, F.NbVariables()) {

       XTol = Tolerance;
       EPSZ = ZEPS;
       Itermax = NbIterations;
    }


    void math_FRPR::Delete()
    {}

    void math_FRPR::Dump(Standard_OStream& o) const {

       o << "math_FRPR ";
       if(Done) {
         o << " Status = Done \n";
	 o << " Location Vector = "<< TheLocation << "\n";
         o << " Minimum value = " << TheMinimum <<"\n";
         o << " Number of iterations = " << Iter <<"\n";
       }
       else {
         o << " Status = not Done because " << (Standard_Integer)TheStatus << "\n";
       }
    }















