//static const char* sccsid = "@(#)math_Powell.cxx	3.2 95/01/10"; // Do not delete this line. Used by sccs.

//#ifndef DEB
#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError
//#endif

#include <math_Powell.ixx>
#include <math_BracketMinimum.hxx>
#include <math_BrentMinimum.hxx>
#include <math_Function.hxx>
#include <math_MultipleVarFunction.hxx>


static Standard_Real sqrarg;
#define SQR(a) (sqrarg=(a), sqrarg*sqrarg)

class DirFunctionBis : public math_Function {

  math_Vector *P0;
  math_Vector *Dir;
  math_Vector *P;
  math_MultipleVarFunction *F;

  public :
    DirFunctionBis(math_Vector& V1,
		math_Vector& V2,
		math_Vector& V3,
		math_MultipleVarFunction& f);

    void Initialize(const math_Vector& p0, const math_Vector& dir);

    virtual Standard_Boolean Value(const Standard_Real x, Standard_Real& fval);
};

 DirFunctionBis::DirFunctionBis(math_Vector& V1,
			  math_Vector& V2,
			  math_Vector& V3,
			  math_MultipleVarFunction& f) {
   P0 = &V1;
   Dir = &V2;
   P = &V3;
   F = &f;
 }


void DirFunctionBis::Initialize(const math_Vector& p0,
			     const math_Vector& dir) {

  *P0 = p0;
  *Dir = dir;
}

Standard_Boolean DirFunctionBis::Value(const Standard_Real x, Standard_Real& fval) {
  *P = *Dir;
  P->Multiply(x);
  P->Add(*P0);
  F->Value(*P, fval);
  return Standard_True;
}


static Standard_Boolean MinimizeDirection(math_Vector& P,
				 math_Vector& Dir,
				 Standard_Real& Result,
				 DirFunctionBis& F) {

  Standard_Real ax;
  Standard_Real xx;
  Standard_Real bx;


  F.Initialize(P, Dir);

  math_BracketMinimum Bracket(F, 0.0, 1.0);
  if (Bracket.IsDone()) {
    Bracket.Values(ax, xx, bx);
    math_BrentMinimum Sol(F, ax, xx, bx, 1.0e-10, 100);
    if (Sol.IsDone()) {
      Standard_Real Scale = Sol.Location();
      Result = Sol.Minimum();
      Dir.Multiply(Scale);
      P.Add(Dir);
      return Standard_True;
    }
  }
  return Standard_False;
}



void math_Powell::Perform(math_MultipleVarFunction& F,
			  const math_Vector& StartingPoint,
			  const math_Matrix& StartingDirections) {


  Done = Standard_False;
  Standard_Integer i, ibig, j;
  Standard_Real t, fptt, del;
  Standard_Integer n = TheLocation.Length();
  math_Vector pt(1,n);
  math_Vector ptt(1,n);
  math_Vector xit(1,n);
  math_Vector Temp1(1, n);
  math_Vector Temp2(1, n);
  math_Vector Temp3(1, n);
  DirFunctionBis F_Dir(Temp1, Temp2, Temp3, F);

  TheLocation = StartingPoint;
  TheDirections = StartingDirections;
  pt = TheLocation;  //sauvegarde du point initial


  for(Iter = 1; Iter<= Itermax; Iter++) {
    F.Value(TheLocation, PreviousMinimum);
    ibig = 0;
    del = 0.0;
    for (i = 1; i <= n; i++){
      for(j =1; j<= n; j++) xit(j) = TheDirections(j,i);
      F.Value(TheLocation, fptt); 
      Standard_Boolean IsGood = MinimizeDirection(TheLocation, xit, 
					 TheMinimum, F_Dir);

      if (!IsGood) {
	Done = Standard_False;
	TheStatus = math_DirectionSearchError;
	return;
      }

      if (fabs(fptt - TheMinimum)> del) {
	del = fabs(fptt- TheMinimum);
	ibig = i;
      }
    }

    if (IsSolutionReached(F)) {
      //Termination criterion
      State = F.GetStateNumber();
      Done = Standard_True;
      TheStatus = math_OK;
      return;
    }

    if (Iter == Itermax) {
      Done = Standard_False;
      TheStatus = math_TooManyIterations;
      return;
    }

      ptt = 2.0 * TheLocation - pt;
      xit = TheLocation - pt;
      pt = TheLocation;
    
    // Valeur de la fonction au point extrapole:

    F.Value(ptt, fptt);

    if (fptt < PreviousMinimum) {
      t = 2.0 *(PreviousMinimum -2.0*TheMinimum +fptt)*
	SQR(PreviousMinimum-TheMinimum -del)-del*
	  SQR(PreviousMinimum-fptt);
      if (t <0.0) {
	//Minimisation along the direction
	Standard_Boolean IsGood = MinimizeDirection(TheLocation, xit,
					   TheMinimum, F_Dir);
	if(!IsGood) {
	  Done = Standard_False;
	  TheStatus = math_FunctionError;
	  return;
	}
	
        for(j =1; j <= n; j++) {
	  TheDirections(j, ibig)=xit(j);
        }
      }
    }
  }
}
					   
Standard_Boolean math_Powell::IsSolutionReached(
//			 math_MultipleVarFunction& F) {
			 math_MultipleVarFunction& ) {
  
  return 2.0*fabs(PreviousMinimum - TheMinimum) <= 
    XTol*(fabs(PreviousMinimum)+fabs(TheMinimum) + EPSZ);
}



math_Powell::math_Powell(math_MultipleVarFunction& F,
			 const math_Vector& StartingPoint,
			 const math_Matrix& StartingDirections,
			 const Standard_Real Tolerance,
			 const Standard_Integer NbIterations,
			 const Standard_Real ZEPS) :
			   TheLocation(1, F.NbVariables()),
			   TheDirections(1, F.NbVariables(),
					 1, F.NbVariables()) {

    XTol = Tolerance;
    EPSZ = ZEPS;
    Itermax = NbIterations;
    Perform(F, StartingPoint, StartingDirections);
  }

math_Powell::math_Powell(math_MultipleVarFunction& F,
			 const Standard_Real Tolerance,
			 const Standard_Integer NbIterations,
			 const Standard_Real ZEPS) :
			   TheLocation(1, F.NbVariables()),
			   TheDirections(1, F.NbVariables(),
					 1, F.NbVariables()) {

    XTol = Tolerance;
    EPSZ = ZEPS;
    Itermax = NbIterations;
  }

void math_Powell::Delete()
{}

void math_Powell::Dump(Standard_OStream& o) const {

  o << "math_Powell resolution:";
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
