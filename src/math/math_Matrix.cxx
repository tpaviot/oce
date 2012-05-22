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

#include <math_Matrix.ixx>
#include <math_Vector.hxx>

#include <Standard_DimensionError.hxx>
#include <Standard_DivideByZero.hxx>
#include <Standard_RangeError.hxx>
#include <math_SingularMatrix.hxx> 
#include <math_NotSquare.hxx>
#include <math_Gauss.hxx>


void math_Matrix::SetLowerRow(const Standard_Integer LowerRow) {
  
  Array.SetLowerRow(LowerRow);
  Standard_Integer Rows = RowNumber();
  LowerRowIndex = LowerRow;
  UpperRowIndex = LowerRowIndex + Rows - 1;
}

void math_Matrix::SetLowerCol(const Standard_Integer LowerCol) {
  
  Array.SetLowerCol(LowerCol);
  Standard_Integer Cols = ColNumber();
  LowerColIndex = LowerCol;
  UpperColIndex = LowerColIndex + Cols - 1;
}

math_Matrix::math_Matrix (const Standard_Integer LowerRow,
			  const Standard_Integer UpperRow,
			  const Standard_Integer LowerCol,
			  const Standard_Integer UpperCol): 
			  
			  LowerRowIndex(LowerRow),
			  UpperRowIndex(UpperRow),
			  LowerColIndex(LowerCol),
			  UpperColIndex(UpperCol),
			  Array(LowerRow, UpperRow,
				LowerCol, UpperCol) 
{
  
  Standard_RangeError_Raise_if((LowerRow > UpperRow) ||
			       (LowerCol > UpperCol), "");
}

math_Matrix::math_Matrix (const Standard_Integer LowerRow,
			  const Standard_Integer UpperRow,
			  const Standard_Integer LowerCol,
			  const Standard_Integer UpperCol,
			  const Standard_Real InitialValue): 
			  
			  LowerRowIndex(LowerRow),
			  UpperRowIndex(UpperRow),
			  LowerColIndex(LowerCol),
			  UpperColIndex(UpperCol),
			  Array(LowerRow, UpperRow,
				LowerCol, UpperCol) 
{
  
  Standard_RangeError_Raise_if((LowerRow > UpperRow) ||
			       (LowerCol > UpperCol), "");
  Array.Init(InitialValue);
}

math_Matrix::math_Matrix (const Standard_Address Tab,
			  const Standard_Integer LowerRow,
			  const Standard_Integer UpperRow,
			  const Standard_Integer LowerCol,
			  const Standard_Integer UpperCol) :
			  
			  LowerRowIndex(LowerRow),
			  UpperRowIndex(UpperRow),
			  LowerColIndex(LowerCol),
			  UpperColIndex(UpperCol),
			  Array(*((const Standard_Real *)Tab), 
				LowerRow, UpperRow,
				LowerCol, UpperCol) 
{ 
  
  Standard_RangeError_Raise_if((LowerRow > UpperRow) ||
			       (LowerCol > UpperCol), "");
}

void math_Matrix::Init(const Standard_Real InitialValue) 
{
  Array.Init(InitialValue);
}

math_Matrix::math_Matrix (const math_Matrix& Other): 

LowerRowIndex(Other.LowerRow()),
UpperRowIndex(Other.UpperRow()),
LowerColIndex(Other.LowerCol()),
UpperColIndex(Other.UpperCol()),
Array(Other.Array) 
{
}



math_Matrix math_Matrix::Divided (const Standard_Real Right) const 
{
  Standard_DivideByZero_Raise_if(Abs(Right) <= RealEpsilon(), "");
  math_Matrix temp = Multiplied(1./Right);
  return temp;
}


Standard_Real math_Matrix::Determinant() const 
{ 
  math_Gauss Sol(*this);
  
  if(Sol.IsDone()) {
    return Sol.Determinant();
  }
  else {
    return 0.0;
  }
}

void math_Matrix::Transpose() 
{ 
  math_NotSquare_Raise_if(RowNumber() != ColNumber(), "");
  
  Standard_Integer Row = LowerRowIndex;
  Standard_Integer Col = LowerColIndex;
  SetLowerCol(LowerRowIndex);
  Standard_Real Temp;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J = I; J <= UpperColIndex; J++) {
      Temp = Array(I, J);
      Array(I, J) = Array(J, I);
      Array(J, I) = Temp;
    }
  }
  SetLowerRow(Col);
  SetLowerCol(Row);
}

math_Matrix math_Matrix::Transposed() const 
{ 
  math_Matrix Result(LowerColIndex, UpperColIndex,
		     LowerRowIndex, UpperRowIndex);
  
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Result.Array(J, I) = Array(I, J);
    }
  }
  return Result;
}

void math_Matrix::Invert() 
{ 
  math_NotSquare_Raise_if(RowNumber() != ColNumber(), "");
  
  math_Gauss Sol(*this);
  if(Sol.IsDone()) {
    Sol.Invert(*this);
  }
  else {
    math_SingularMatrix::Raise(); // SingularMatrix Exception;
  }
}

math_Matrix math_Matrix::Inverse() const 
{
  
  math_Matrix Result = *this;
  Result.Invert();
  return Result;
}

void math_Matrix::Multiply (const Standard_Real Right) 
{ 
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Array(I, J) = Array(I, J) * Right;
    }
  }
}

math_Matrix math_Matrix::Multiplied (const Standard_Real Right) const
{ 
  math_Matrix Result(LowerRowIndex, UpperRowIndex, 
		     LowerColIndex, UpperColIndex);
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Result.Array(I, J) = Array(I, J) * Right;
    }
  }
  return Result;
}

math_Matrix math_Matrix::TMultiplied (const Standard_Real Right) const
{ 
  math_Matrix Result(LowerRowIndex, UpperRowIndex, 
		     LowerColIndex, UpperColIndex);
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Result.Array(I, J) = Array(I, J) * Right;
    }
  }
  return Result;
}



void math_Matrix::Divide (const Standard_Real Right) 
{ 
  Standard_DivideByZero_Raise_if(Abs(Right) <= RealEpsilon(), "");
  
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Array(I, J) = Array(I, J) / Right;
    }
  }
}

void math_Matrix::Add (const math_Matrix& Right) 
{
  Standard_DimensionError_Raise_if((RowNumber() != Right.RowNumber()) ||
				   (ColNumber() != Right.ColNumber()),
				   "");
  
  Standard_Integer I2 = Right.LowerRowIndex;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Standard_Integer J2 = Right.LowerColIndex;
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Array(I, J) = Array(I, J) + Right.Array(I2, J2);
      J2++;
    }
    I2++;
  }
}

void math_Matrix::Subtract (const math_Matrix& Right) 
{ 
  Standard_DimensionError_Raise_if((RowNumber() != Right.RowNumber()) ||
				   (ColNumber() != Right.ColNumber()),
				   "");
  
  Standard_Integer I2 = Right.LowerRowIndex;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Standard_Integer J2 = Right.LowerColIndex;
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Array(I, J) = Array(I, J) - Right.Array(I2, J2);
      J2++;
    }
    I2++;
  }
}

void math_Matrix::Set(const Standard_Integer I1,const Standard_Integer I2,
		      const Standard_Integer J1,const Standard_Integer J2,
		      const math_Matrix& M) 
{
  
  Standard_DimensionError_Raise_if((I1 < LowerRowIndex)       || 
				   (I2 > UpperRowIndex)       ||
				   (J1 < LowerColIndex)       ||
				   (J2 > UpperColIndex)       ||
				   (I1 > I2) || (J1 > J2)     ||
				   (I2-I1+1 != M.RowNumber()) ||
				   (J2-J1+1 != M.ColNumber()), "");
  
  Standard_Integer II = M.LowerRow();
  for(Standard_Integer I = I1; I <= I2; I++) {
    Standard_Integer JJ = M.LowerCol();
    for(Standard_Integer J = J1; J <= J2; J++) {
      Array(I, J) = M.Array(II, JJ);
      JJ++;
    }
    II++;
  }
}         

void math_Matrix::SetRow (const Standard_Integer Row,
			  const math_Vector& V) 
{ 
  
  Standard_RangeError_Raise_if((Row < LowerRowIndex) ||
			       (Row > UpperRowIndex) , "");
  
  Standard_DimensionError_Raise_if(ColNumber() != V.Length(), "");
  
  Standard_Integer I = V.LowerIndex;
  for(Standard_Integer Index = LowerColIndex; Index <= UpperColIndex; Index++) {
    Array(Row, Index) = V.Array(I);
    I++;
  }
}

void math_Matrix::SetCol (const Standard_Integer Col,
			  const math_Vector& V) 
{ 
  
  Standard_RangeError_Raise_if((Col < LowerColIndex) ||
			       (Col > UpperColIndex) , "");
  
  Standard_DimensionError_Raise_if(RowNumber() != V.Length(), "");
  
  Standard_Integer I = V.LowerIndex;
  for(Standard_Integer Index = LowerRowIndex; Index <= UpperRowIndex; Index++) {
    Array(Index, Col) = V.Array(I);
    I++;
  }
}

void math_Matrix::SetDiag(const Standard_Real Value)
{ 
  
  math_NotSquare_Raise_if(RowNumber() != ColNumber(), "");
  
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Array(I, I) = Value;
  }
}
math_Vector math_Matrix::Row (const Standard_Integer Row)  const 
{ 
  
  math_Vector Result(LowerColIndex, UpperColIndex);
  
  for(Standard_Integer Index = LowerColIndex; Index <= UpperColIndex; Index++) {
    Result.Array(Index) = Array(Row, Index);
  }
  return Result;
}

math_Vector math_Matrix::Col (const Standard_Integer Col) const 
{ 
  
  math_Vector Result(LowerRowIndex, UpperRowIndex);
  
  for(Standard_Integer Index = LowerRowIndex; Index <= UpperRowIndex; Index++) {
    Result.Array(Index) = Array(Index, Col);
  }
  return Result;
}

void math_Matrix::SwapRow(const Standard_Integer Row1,
			  const Standard_Integer Row2) 
{
  
  Standard_RangeError_Raise_if((Row1 < LowerRowIndex) ||
			       (Row1 > UpperRowIndex) ||
			       (Row2 < LowerRowIndex) ||
			       (Row2 > UpperRowIndex), "");
  
  math_Vector V1 = Row(Row1);
  math_Vector V2 = Row(Row2);
  SetRow(Row1,V2);
  SetRow(Row2,V1);
}

void math_Matrix::SwapCol(const Standard_Integer Col1,
			  const Standard_Integer Col2) 
{
  
  Standard_RangeError_Raise_if((Col1 < LowerColIndex) ||
			       (Col1 > UpperColIndex) ||
			       (Col2 < LowerColIndex) ||
			       (Col2 > UpperColIndex), "");
  
  math_Vector V1 = Col(Col1);
  math_Vector V2 = Col(Col2);
  SetCol(Col1,V2);
  SetCol(Col2,V1);
}



math_Matrix  math_Matrix::Multiplied (const math_Matrix& Right) const 
{ 
  
  Standard_DimensionError_Raise_if(ColNumber() != Right.RowNumber(), "");
  
  math_Matrix Result(LowerRowIndex,       UpperRowIndex,
		     Right.LowerColIndex, Right.UpperColIndex);
  
  Standard_Real Som;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J2 = Right.LowerColIndex; J2 <= Right.UpperColIndex; J2++) {
      Som = 0.0;
      Standard_Integer I2 = Right.LowerRowIndex;
      for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
	Som = Som + Array(I, J) * Right.Array(I2, J2);
	I2++;
      }
      Result.Array(I, J2) = Som;
    }
  }
  return Result;
}

math_Matrix  math_Matrix::TMultiply (const math_Matrix& Right) const 
{ 
  
  Standard_DimensionError_Raise_if(RowNumber() != Right.RowNumber(), "");
  
  math_Matrix Result(LowerColIndex,       UpperColIndex,
		     Right.LowerColIndex, Right.UpperColIndex);
  
  Standard_Real Som;
  for(Standard_Integer I = LowerColIndex; I <= UpperColIndex; I++) {
    for(Standard_Integer J2 = Right.LowerColIndex; J2 <= Right.UpperColIndex; J2++) {
      Som = 0.0;
      Standard_Integer I2 = Right.LowerRowIndex;
      for(Standard_Integer J = LowerRowIndex; J <= UpperRowIndex; J++) {
	Som = Som + Array(J, I) * Right.Array(I2, J2);
	I2++;
      }
      Result.Array(I, J2) = Som;
    }
  }
  return Result;
}

math_Matrix  math_Matrix::Added (const math_Matrix& Right) const 
{ 
  
  Standard_DimensionError_Raise_if((RowNumber() != Right.RowNumber()) ||
				   (ColNumber() != Right.ColNumber()),
				   "");
  
  math_Matrix Result(LowerRowIndex, UpperRowIndex, 
		     LowerColIndex, UpperColIndex);
  
  Standard_Integer I2 = Right.LowerRowIndex;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Standard_Integer J2 = Right.LowerColIndex;
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Result.Array(I, J) = Array(I, J) + Right.Array(I2, J2);
      J2++;
    }
    I2++;
  }
  return Result;
}

math_Matrix  math_Matrix::Opposite () 
{ 
  
  math_Matrix Result(LowerRowIndex, UpperRowIndex, 
		     LowerColIndex, UpperColIndex);
  
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Result.Array(I, J) = - Array(I, J);
    }
  }
  return Result;
}

math_Matrix  math_Matrix::Subtracted (const math_Matrix& Right) const 
{ 
  
  Standard_DimensionError_Raise_if((RowNumber() != Right.RowNumber()) ||
				   (ColNumber() != Right.ColNumber()),
				   "");
  
  math_Matrix Result(LowerRowIndex, UpperRowIndex, 
		     LowerColIndex, UpperColIndex);
  
  Standard_Integer I2 = Right.LowerRowIndex;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Standard_Integer J2 = Right.LowerColIndex;
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Result.Array(I, J) = Array(I, J) - Right.Array(I2, J2);
      J2++;
    }
    I2++;
  }
  return Result;
}

void  math_Matrix::Multiply(const math_Vector&  Left, 
			    const math_Vector&  Right) 
{
  
  Standard_DimensionError_Raise_if((RowNumber() != Left.Length()) ||
				   (ColNumber() != Right.Length()),
				   "");
  
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Array(I, J) = Left.Array(I) * Right.Array(J);
    }
  }
}

void  math_Matrix::Multiply(const math_Matrix&  Left, 
			    const math_Matrix&  Right) 
{
  
  Standard_DimensionError_Raise_if((Left.ColNumber() != Right.RowNumber()) ||
				   (RowNumber() != Left.RowNumber()) ||
				   (ColNumber() != Right.ColNumber()),
				   "");
  
  Standard_Real Som;
  Standard_Integer I1 = Left.LowerRowIndex;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Standard_Integer J2 = Right.LowerColIndex;  
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Som = 0.0;
      Standard_Integer J1 = Left.LowerColIndex;
      Standard_Integer I2 = Right.LowerRowIndex;
      for(Standard_Integer K = Left.LowerColIndex; K <= Left.UpperColIndex; K++) {
	Som = Som + Left.Array(I1, J1) * Right.Array(I2, J2);
	J1++;
	I2++;
      }
      Array(I, J) = Som;
      J2++;
    }
    I1++;
  }
}

void math_Matrix::TMultiply(const math_Matrix& TLeft, 
			    const math_Matrix&  Right) 
{
  
  Standard_DimensionError_Raise_if((TLeft.RowNumber() != Right.RowNumber()) ||
				   (RowNumber() != TLeft.ColNumber()) ||
				   (ColNumber() != Right.ColNumber()),
				   "");
  
  Standard_Real Som;
  Standard_Integer I1 = TLeft.LowerColIndex;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Standard_Integer J2 = Right.LowerColIndex;  
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Som = 0.0;
      Standard_Integer J1 = TLeft.LowerRowIndex;
      Standard_Integer I2 = Right.LowerRowIndex;
      for(Standard_Integer K = TLeft.LowerRowIndex; K <= TLeft.UpperRowIndex; K++) {
	Som = Som + TLeft.Array(J1, I1) * Right.Array(I2, J2);
	J1++;
	I2++;
      }
      Array(I, J) = Som;
      J2++;
    }
    I1++;
  }
}

void  math_Matrix::Add (const math_Matrix&  Left, 
			const math_Matrix&  Right) 
{
  
  Standard_DimensionError_Raise_if((RowNumber() != Right.RowNumber()) ||
				   (ColNumber() != Right.ColNumber()) ||
				   (Right.RowNumber() != Left.RowNumber()) ||
				   (Right.ColNumber() != Left.ColNumber()),
				   "");
  
  Standard_Integer I1 = Left.LowerRowIndex;
  Standard_Integer I2 = Right.LowerRowIndex;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Standard_Integer J1 = Left.LowerColIndex;
    Standard_Integer J2 = Right.LowerColIndex;
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Array(I, J) = Left.Array(I1, J1) + Right.Array(I2, J2);
      J1++;
      J2++;
    }
    I1++;
    I2++;
  }
}

void  math_Matrix::Subtract(const math_Matrix&  Left,
			    const math_Matrix&  Right) 
{
  
  Standard_DimensionError_Raise_if((RowNumber() != Right.RowNumber()) ||
				   (ColNumber() != Right.ColNumber()) ||
				   (Right.RowNumber() != Left.RowNumber()) ||
				   (Right.ColNumber() != Left.ColNumber()),
				   "");
  
  Standard_Integer I1 = Left.LowerRowIndex;
  Standard_Integer I2 = Right.LowerRowIndex;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Standard_Integer J1 = Left.LowerColIndex;
    Standard_Integer J2 = Right.LowerColIndex;
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Array(I, J) = Left.Array(I1, J1) - Right.Array(I2, J2);
      J1++;
      J2++;
    }
    I1++;
    I2++;
  }
}


void math_Matrix::Multiply(const math_Matrix& Right) 
{
  
  Standard_DimensionError_Raise_if(ColNumber() != Right.RowNumber(), "");
  
  Standard_Real Som;
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J2 = Right.LowerColIndex; J2 <= Right.UpperColIndex; J2++) {
      Som = 0.0;
      Standard_Integer I2 = Right.LowerRowIndex;
      for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
	Som = Som + Array(I, J) * Right.Array(I2, J2);
	I2++;
      }
      Array(I, J2) = Som;
    }
  }
}



math_Vector math_Matrix::Multiplied(const math_Vector& Right)const
{
  
  Standard_DimensionError_Raise_if(ColNumber() != Right.Length(), "");
  
  math_Vector Result(LowerRowIndex, UpperRowIndex);
  
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    Result.Array(I) = 0.0;
    Standard_Integer II = Right.LowerIndex;
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      Result.Array(I) = Result.Array(I) + Array(I, J) * Right.Array(II);
      II++;
    }
  }
  return Result;
}

math_Matrix& math_Matrix::Initialized(const math_Matrix& Other) 
{
  
  Standard_DimensionError_Raise_if((RowNumber() != Other.RowNumber()) ||
				   (ColNumber() != Other.ColNumber()), "");
  
  (Other.Array).Copy(Array);
  return *this;
}




void math_Matrix::Dump(Standard_OStream& o)const

{
  o << "math_Matrix of RowNumber = " << RowNumber();
  o << " and ColNumber = " << ColNumber() << "\n";
  
  for(Standard_Integer I = LowerRowIndex; I <= UpperRowIndex; I++) {
    for(Standard_Integer J = LowerColIndex; J <= UpperColIndex; J++) {
      o << "math_Matrix ( " << I << ", " << J << " ) = ";
      o << Array(I, J) << "\n";
    }
  }
}

