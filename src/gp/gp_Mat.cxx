// File gp_Mat.cxx, JCV 05/12/90
//  10/09/97 : PMN : Correction BUC40192 (pb avec les matrices negatives)

#ifndef DEB
#define No_Standard_OutOfRange
#define No_Standard_ConstructionError
#endif

#include <gp_Mat.ixx>

gp_Mat::gp_Mat (const gp_XYZ& Col1,
		const gp_XYZ& Col2,
		const gp_XYZ& Col3)
{
  Mat00 = Col1.X(); Mat10 = Col1.Y(); Mat20 = Col1.Z();
  Mat01 = Col2.X(); Mat11 = Col2.Y(); Mat21 = Col2.Z();
  Mat02 = Col3.X(); Mat12 = Col3.Y(); Mat22 = Col3.Z();
}

void gp_Mat::SetCol (const Standard_Integer Col,
		     const gp_XYZ& Value) {

  Standard_OutOfRange_Raise_if (Col < 1 || Col > 3, " ");
  if      (Col == 1) {
    Mat00 = Value.X(); Mat10 = Value.Y(); Mat20 = Value.Z();
  }
  else if (Col == 2) {
    Mat01 = Value.X(); Mat11 = Value.Y(); Mat21 = Value.Z();
  }
  else {
    Mat02 = Value.X(); Mat12 = Value.Y(); Mat22 = Value.Z();
  }
}

void gp_Mat::SetCols (const gp_XYZ& Col1,
		      const gp_XYZ& Col2,
		      const gp_XYZ& Col3)
{
  Mat00 = Col1.X(); Mat10 = Col1.Y(); Mat20 = Col1.Z();
  Mat01 = Col2.X(); Mat11 = Col2.Y(); Mat21 = Col2.Z();
  Mat02 = Col3.X(); Mat12 = Col3.Y(); Mat22 = Col3.Z();
}

void gp_Mat::SetCross (const gp_XYZ& Ref)
{
  Standard_Real X = Ref.X();
  Standard_Real Y = Ref.Y();
  Standard_Real Z = Ref.Z();
  Mat00 = Mat11 = Mat22 = 0.0;
  Mat01 = - Z;  
  Mat02 = Y;
  Mat12 = - X;
  Mat10 = Z;
  Mat20 = - Y;
  Mat21 = X;
}

void gp_Mat::SetDot (const gp_XYZ& Ref)
{
  Standard_Real X = Ref.X();
  Standard_Real Y = Ref.Y();
  Standard_Real Z = Ref.Z();
  Mat00 = X * X;
  Mat11 = Y * Y;
  Mat22 = Z * Z;
  Mat01 = X * Y;
  Mat02 = X * Z;
  Mat12 = Y * Z;
  Mat10 = Mat01;
  Mat20 = Mat02;
  Mat21 = Mat12;
}

void gp_Mat::SetRotation (const gp_XYZ& Axis,
			  const Standard_Real Ang)
{
  //    Rot = I + sin(Ang) * M + (1. - cos(Ang)) * M*M
  //    avec  M . XYZ = Axis ^ XYZ

//  const Standard_Address M = (Standard_Address)&(matrix[0][0]);
  gp_XYZ V = Axis.Normalized();
  SetCross (V);
  Multiply (sin(Ang));
  gp_Mat Temp;
  Temp.SetScale (1.0);
  Add (Temp);
  Standard_Real A = V.X();
  Standard_Real B = V.Y();
  Standard_Real C = V.Z();
  Temp.SetRow (1, gp_XYZ(- C*C - B*B,      A*B,           A*C     ));
  Temp.SetRow (2, gp_XYZ(     A*B,      -A*A - C*C,        B*C    ));
  Temp.SetRow (3, gp_XYZ(     A*C,          B*C,       - A*A - B*B));
  Temp.Multiply (1.0 - cos(Ang));
  Add (Temp);
}

void gp_Mat::SetRow (const Standard_Integer Row,
		     const gp_XYZ& Value)
{
  Standard_OutOfRange_Raise_if (Row < 1 || Row > 3, " ");
  if      (Row == 1) {
    Mat00 = Value.X(); Mat01 = Value.Y(); Mat02 = Value.Z();
  }
  else if (Row == 2) {
    Mat10 = Value.X(); Mat11 = Value.Y(); Mat12 = Value.Z();
  }
  else {
    Mat20 = Value.X(); Mat21 = Value.Y(); Mat22 = Value.Z();
  }
}

void gp_Mat::SetRows (const gp_XYZ& Row1,
		      const gp_XYZ& Row2,
		      const gp_XYZ& Row3)
{
  Mat00 = Row1.X(); Mat01 = Row1.Y(); Mat02 = Row1.Z();
  Mat10 = Row2.X(); Mat11 = Row2.Y(); Mat12 = Row2.Z();
  Mat20 = Row3.X(); Mat21 = Row3.Y(); Mat22 = Row3.Z();
}

gp_XYZ gp_Mat::Column (const Standard_Integer Col) const
{
  Standard_OutOfRange_Raise_if (Col < 1 || Col > 3, "");
  if (Col == 1) return gp_XYZ (Mat00,Mat10,Mat20);
  if (Col == 2) return gp_XYZ (Mat01,Mat11,Mat21);
  return gp_XYZ (Mat02,Mat12,Mat22);
}

gp_XYZ gp_Mat::Diagonal () const
{
  return gp_XYZ (Mat00, Mat11, Mat22);
}

gp_XYZ gp_Mat::Row (const Standard_Integer Row) const
{
  Standard_OutOfRange_Raise_if (Row < 1 || Row > 3, "");
  if (Row == 1) return gp_XYZ (Mat00,Mat01,Mat02);
  if (Row == 2) return gp_XYZ (Mat10,Mat11,Mat12);
  return gp_XYZ (Mat20,Mat21,Mat22);
}

void gp_Mat::Invert ()
{ 
  gp_Mat NewMat;    
  //
  // calcul de  la transposee de la commatrice
  //
  Nat00 = Mat11 * Mat22 - Mat12 * Mat21 ;
  Nat10 = -(Mat10 * Mat22 - Mat20 * Mat12) ;
  Nat20 = Mat10 * Mat21 - Mat20 * Mat11 ;
  Nat01 = - (Mat01 * Mat22 - Mat21 * Mat02) ;
  Nat11 = Mat00 * Mat22 - Mat20 * Mat02 ;
  Nat21 = -(Mat00 * Mat21 - Mat20 * Mat01) ;
  Nat02 = Mat01 * Mat12 - Mat11 * Mat02 ;
  Nat12 = -(Mat00 * Mat12 - Mat10 * Mat02) ;
  Nat22 = Mat00 * Mat11 - Mat01 * Mat10 ;
  Standard_Real det =  Mat00 * Nat00 + Mat01* Nat10 + Mat02 * Nat20 ;
  Standard_Real val = det;
  if (val < 0) val = - val;
  Standard_ConstructionError_Raise_if
    (val <= gp::Resolution(),"");
  det = 1.0e0 / det ;
  Mat00 = Nat00;
  Mat10 = Nat10;
  Mat20 = Nat20;
  Mat01 = Nat01;
  Mat11 = Nat11;
  Mat21 = Nat21;
  Mat02 = Nat02;
  Mat12 = Nat12;
  Mat22 = Nat22;
  Multiply(det) ;
}

gp_Mat gp_Mat::Inverted () const
{ 
  gp_Mat NewMat;
  //
  // calcul de  la transposee de la commatrice
  //
  Nat00 = Mat11 * Mat22 - Mat12 * Mat21 ;
  Nat10 = -(Mat10 * Mat22 - Mat20 * Mat12) ;
  Nat20 = Mat10 * Mat21 - Mat20 * Mat11 ;
  Nat01 = - (Mat01 * Mat22 - Mat21 * Mat02) ;
  Nat11 = Mat00 * Mat22 - Mat20 * Mat02 ;
  Nat21 = -(Mat00 * Mat21 - Mat20 * Mat01) ;
  Nat02 = Mat01 * Mat12 - Mat11 * Mat02 ;
  Nat12 = -(Mat00 * Mat12 - Mat10 * Mat02) ;
  Nat22 = Mat00 * Mat11 - Mat01 * Mat10 ;
  Standard_Real det =  Mat00 * Nat00 + Mat01* Nat10 + Mat02 * Nat20 ;
  Standard_Real val = det;
  if (val < 0) val = - val;
  Standard_ConstructionError_Raise_if
    (val <= gp::Resolution(),"");
  det = 1.0e0 / det ;
  NewMat.Multiply(det) ;
  return NewMat;
}

void gp_Mat::Power (const Standard_Integer N)
{
  if (N == 1) { }
  else if (N == 0)  { SetIdentity() ; }
  else if (N == -1) { Invert(); }
  else {
    if (N < 0) { Invert(); }
    Standard_Integer Npower = N;
    if (Npower < 0) Npower = - Npower;
    Npower--;
    gp_Mat Temp = *this;
    while (1) {
      if (IsOdd(Npower)) Multiply (Temp);
      if (Npower == 1)   break; 
      Temp.Multiply (Temp);
      Npower>>=1;
    }
  }
}

