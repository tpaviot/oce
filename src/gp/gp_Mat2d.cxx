// File gp_Mat2d.cxx, JCV 08/01/91
//  10/09/97 : PMN : Correction BUC40192 (pb avec les matrices negatives)

#ifndef DEB
#define No_Standard_OutOfRange
#define No_Standard_ConstructionError
#endif

#include <gp_Mat2d.ixx>
#include <Standard_ConstructionError.hxx>

gp_Mat2d::gp_Mat2d (const gp_XY& Col1, const gp_XY& Col2)
{
  Mat2d00 = Col1.X(); Mat2d10 = Col1.Y();
  Mat2d01 = Col2.X(); Mat2d11 = Col2.Y();
}

void gp_Mat2d::SetCol (const Standard_Integer Col,
		       const gp_XY& Value)
{
  Standard_OutOfRange_Raise_if (Col < 1 || Col > 2,"");
  if  (Col == 1) {
    Mat2d00 = Value.X();
    Mat2d10 = Value.Y();
  }
  else {
    Mat2d01 = Value.X();
    Mat2d11 = Value.Y();
  }
}

void gp_Mat2d::SetCols (const gp_XY& Col1,
			const gp_XY& Col2)
{
  Mat2d00 = Col1.X(); Mat2d10 = Col1.Y();
  Mat2d01 = Col2.X(); Mat2d11 = Col2.Y();
}

void gp_Mat2d::SetRow (const Standard_Integer Row, const gp_XY& Value)
{
  Standard_OutOfRange_Raise_if (Row < 1 || Row > 2,"");
  if (Row == 1) {
    Mat2d00 = Value.X();
    Mat2d01 = Value.Y();
  }
  else {
    Mat2d10 = Value.X();
    Mat2d11 = Value.Y();
  }
}

void gp_Mat2d::SetRows (const gp_XY& Row1, const gp_XY& Row2)
{
  Mat2d00 = Row1.X(); Mat2d01 = Row1.Y();
  Mat2d10 = Row2.X(); Mat2d11 = Row2.Y();
}

gp_XY gp_Mat2d::Column (const Standard_Integer Col) const
{
  Standard_OutOfRange_Raise_if (Col < 1 || Col > 2,"");
  if (Col == 1) return gp_XY (Mat2d00,Mat2d10);
  return gp_XY (Mat2d01,Mat2d11);
}

gp_XY gp_Mat2d::Diagonal () const
{ 
  return gp_XY (Mat2d00,Mat2d11);
}

gp_XY gp_Mat2d::Row (const Standard_Integer Row) const
{
  Standard_OutOfRange_Raise_if (Row < 1 || Row > 2,"");
  if (Row == 1) return gp_XY (Mat2d00,Mat2d01);
  return gp_XY (Mat2d10,Mat2d11);
}

void gp_Mat2d::Invert ()
{
  Standard_Real det ;
  gp_Mat2d NewMat;
  Nat00 = Mat2d11 ;
  Nat01 = -Mat2d01 ;
  Nat10 = -Mat2d10 ;
  Nat11 = Mat2d00  ;
  det = Nat00 * Nat11 - Nat01 * Nat10 ;
  Standard_Real val = det;
  if (val < 0) val = - val;
  Standard_ConstructionError_Raise_if (val <= gp::Resolution(),"");
  det = 1.0 / det ;
  Mat2d00 = Nat00 * det ;
  Mat2d10 = Nat10 * det ;
  Mat2d01 = Nat01 * det ;
  Mat2d11 = Nat11 * det ;
}

void gp_Mat2d::Power (const Standard_Integer N)
{
  if      (N ==  1) { }
  else if (N ==  0) { SetIdentity (); }
  else if (N == -1) { Invert(); }
  else {
    if (N < 0) Invert();
    Standard_Integer Npower = N;
    if (Npower < 0) Npower = - Npower;
    Npower--;
    gp_Mat2d Temp = *this;
    while (1) {
      if (IsOdd(Npower)) Multiply (Temp);
      if (Npower == 1)   break;
      Temp.Multiply (Temp);
      Npower = Npower/2;
    }
  }
}

