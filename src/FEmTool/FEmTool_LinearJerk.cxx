// Created on: 1998-11-06
// Created by: Igor FEOKTISTOV
// Copyright (c) 1998-1999 Matra Datavision
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



#include <FEmTool_LinearJerk.ixx>
#include <PLib.hxx>
#include <TColStd_HArray2OfInteger.hxx>
#include <TColStd_HArray2OfReal.hxx>
#include <PLib_JacobiPolynomial.hxx>
#include <PLib_HermitJacobi.hxx>
#include <FEmTool_ElementsOfRefMatrix.hxx>
#include <math_IntegerVector.hxx>
#include <math_Vector.hxx>
#include <math_GaussSetIntegration.hxx>
#include <math.hxx>
#include <Standard_ConstructionError.hxx>


FEmTool_LinearJerk::FEmTool_LinearJerk(const Standard_Integer WorkDegree,
				       const GeomAbs_Shape ConstraintOrder):
       RefMatrix(0,WorkDegree,0,WorkDegree)
{
  static Standard_Integer Order = -333, WDeg = 14;
  static math_Vector MatrixElemts(0, ((WDeg+2)*(WDeg+1))/2 -1 );  

  myOrder = PLib::NivConstr(ConstraintOrder);


  //Calculating RefMatrix
  if (myOrder != Order) {
    if (WorkDegree > WDeg) Standard_ConstructionError::Raise("Degree too high");
    Order = myOrder;
    Standard_Integer DerOrder = 3;

    Handle(PLib_HermitJacobi) theBase = new PLib_HermitJacobi(WDeg, ConstraintOrder);
    FEmTool_ElementsOfRefMatrix Elem = FEmTool_ElementsOfRefMatrix(theBase, DerOrder);
    
    Standard_Integer maxDegree = WDeg+1;
    
    math_IntegerVector Order(1,1,Min(4*(maxDegree/2+1),math::GaussPointsMax()));

    math_Vector Lower(1,1,-1.), Upper(1,1,1.); 
    
    math_GaussSetIntegration anInt(Elem, Lower, Upper, Order);
    
    MatrixElemts = anInt.Value();
  }

  Standard_Integer i, j, ii, jj;
  for(ii=i = 0; i <= WorkDegree; i++) {
    RefMatrix(i, i) =  MatrixElemts(ii);
    for(j = i+1, jj = ii+1; j <= WorkDegree; j++, jj++) {
      RefMatrix(j, i) = RefMatrix(i, j) =  MatrixElemts(jj);
    }
    ii += WDeg+1-i;
  }
}

Handle(TColStd_HArray2OfInteger) FEmTool_LinearJerk::DependenceTable() const
{
  if(myCoeff.IsNull()) Standard_DomainError::Raise("FEmTool_LinearJerk::DependenceTable");

  Handle(TColStd_HArray2OfInteger) DepTab = 
    new TColStd_HArray2OfInteger(myCoeff->LowerCol(), myCoeff->UpperCol(),
				 myCoeff->LowerCol(), myCoeff->UpperCol(),0);
  Standard_Integer i;
  for(i = myCoeff->LowerCol(); i <= myCoeff->UpperCol(); i++) DepTab->SetValue(i,i,1);
  
  return DepTab;
}

Standard_Real FEmTool_LinearJerk::Value() 
{
  Standard_Integer deg = Min(myCoeff->ColLength() - 1, RefMatrix.UpperRow()), 
                   i, j, j0 = myCoeff->LowerRow(), degH = Min(2*myOrder+1, deg),
                   NbDim = myCoeff->RowLength(), dim;

  TColStd_Array2OfReal NewCoeff( 1, NbDim, 0, deg);

  Standard_Real coeff = (myLast - myFirst)/2., cteh3 = 2./Pow(coeff,5), 
                mfact, Jline;

  Standard_Integer k1;

  Standard_Real J = 0.;

  for(i = 0; i <= degH; i++) {
    k1 = (i <= myOrder)? i : i - myOrder - 1;
    mfact = Pow(coeff,k1);
    for(dim = 1; dim <= NbDim; dim++) 
      NewCoeff(dim, i) = myCoeff->Value(j0 + i, dim) * mfact;
  }

  for(i = degH + 1; i <= deg; i++) {
    for(dim = 1; dim <= NbDim; dim++) 
      NewCoeff(dim, i) = myCoeff->Value(j0 + i, dim);
  }

  for(dim = 1; dim <= NbDim; dim++) {
  
    for(i = 0; i <= deg; i++) {

      Jline = 0.5 * RefMatrix(i, i) * NewCoeff(dim, i);

      for(j = 0; j < i; j++) 
	Jline += RefMatrix(i, j) * NewCoeff(dim, j);
      
      J += Jline * NewCoeff(dim, i);
      if(J < 0.) J = 0.;
    }    

  }

  return cteh3*J;

}

void FEmTool_LinearJerk::Hessian(const Standard_Integer Dimension1,
				 const Standard_Integer Dimension2, math_Matrix& H) 
{
 
  Handle(TColStd_HArray2OfInteger) DepTab = DependenceTable();

  if(Dimension1 < DepTab->LowerRow() || Dimension1 > DepTab->UpperRow() || 
     Dimension2 < DepTab->LowerCol() || Dimension2 > DepTab->UpperCol()) 
    Standard_OutOfRange::Raise("FEmTool_LinearJerk::Hessian");

  if(DepTab->Value(Dimension1,Dimension2) == 0) 
    Standard_DomainError::Raise("FEmTool_LinearJerk::Hessian");

  Standard_Integer deg = Min(RefMatrix.UpperRow(), H.RowNumber() - 1), degH = Min(2*myOrder+1, deg);

  Standard_Real coeff = (myLast - myFirst)/2., cteh3 = 2./Pow(coeff,5), mfact;
  Standard_Integer k1, k2, i, j, i0 = H.LowerRow(), j0 = H.LowerCol(), i1, j1;

  H.Init(0.);

  i1 = i0;
  for(i = 0; i <= degH; i++) {
    k1 = (i <= myOrder)? i : i - myOrder - 1;
    mfact = Pow(coeff,k1)*cteh3;
    // Hermite*Hermite part of matrix
    j1 = j0 + i;
    for(j = i; j <= degH; j++) {
      k2 = (j <= myOrder)? j : j - myOrder - 1;
      H(i1, j1) = mfact*Pow(coeff, k2)*RefMatrix(i, j);
      if (i != j) H(j1, i1) = H(i1, j1);
      j1++;
    }
    // Hermite*Jacobi part of matrix
    j1 = j0 + degH + 1;
    for(j = degH + 1; j <= deg; j++) {
      H(i1, j1) = mfact*RefMatrix(i, j);
      H(j1, i1) = H(i1, j1);
      j1++;
    }
    i1++;
  }


  // Jacoby*Jacobi part of matrix
  i1 = i0 + degH + 1;
  for(i = degH+1; i <= deg; i++) {
    j1 = j0 + i;
    for(j = i; j <= deg; j++) {
      H(i1, j1) = cteh3*RefMatrix(i, j);
      if (i != j) H(j1, i1) = H(i1, j1);
      j1++;
    }
    i1++;
  }

}

void FEmTool_LinearJerk::Gradient(const Standard_Integer Dimension,math_Vector& G) 
{
  if(Dimension < myCoeff->LowerCol() || Dimension > myCoeff->UpperCol()) 
    Standard_OutOfRange::Raise("FEmTool_LinearJerk::Gradient");

  Standard_Integer deg = Min(G.Length() - 1, myCoeff->ColLength() - 1);

  math_Vector X(0,deg);
  Standard_Integer i, i1 = myCoeff->LowerRow();
  for(i = 0; i <= deg; i++) X(i) = myCoeff->Value(i1+i, Dimension);

  math_Matrix H(0,deg,0,deg);
  Hessian(Dimension, Dimension, H);
  
  G.Multiply(H, X);

}

