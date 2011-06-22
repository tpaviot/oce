// File:	HLRAlgo_PolyShellData.cxx
// Created:	Fri May  5 15:58:19 1995
// Author:	Christophe MARION
//		<cma@ecolox>
#ifndef No_Exception
//#define No_Exception
#endif
#include <HLRAlgo_PolyShellData.ixx>
#include <HLRAlgo_ListIteratorOfListOfBPoint.hxx>
#include <HLRAlgo_BiPoint.hxx>
#include <HLRAlgo_PolyData.hxx>

#define PntX1  ((Standard_Real*)Coordinates)[ 0]
#define PntY1  ((Standard_Real*)Coordinates)[ 1]
#define PntZ1  ((Standard_Real*)Coordinates)[ 2]
#define PntX2  ((Standard_Real*)Coordinates)[ 3]
#define PntY2  ((Standard_Real*)Coordinates)[ 4]
#define PntZ2  ((Standard_Real*)Coordinates)[ 5]
#define PntXP1 ((Standard_Real*)Coordinates)[ 6]
#define PntYP1 ((Standard_Real*)Coordinates)[ 7]
#define PntZP1 ((Standard_Real*)Coordinates)[ 8]
#define PntXP2 ((Standard_Real*)Coordinates)[ 9]
#define PntYP2 ((Standard_Real*)Coordinates)[10]
#define PntZP2 ((Standard_Real*)Coordinates)[11]

#define TotXMin ((Standard_Real*)TotMinMax)[0]
#define TotYMin ((Standard_Real*)TotMinMax)[1]
#define TotZMin ((Standard_Real*)TotMinMax)[2]
#define TotXMax ((Standard_Real*)TotMinMax)[3]
#define TotYMax ((Standard_Real*)TotMinMax)[4]
#define TotZMax ((Standard_Real*)TotMinMax)[5]

//=======================================================================
//function : HLRAlgo_PolyShellData
//purpose  : 
//=======================================================================

HLRAlgo_PolyShellData::
HLRAlgo_PolyShellData (const Standard_Integer nbFace)
:  myPolyg(0,nbFace)
{}

//=======================================================================
//function : UpdateGlobalMinMax
//purpose  : 
//=======================================================================

void 
HLRAlgo_PolyShellData::
UpdateGlobalMinMax(const Standard_Address TotMinMax)
{
  HLRAlgo_ListIteratorOfListOfBPoint it;
  
  for (it.Initialize(mySegList); it.More(); it.Next()) {      
    HLRAlgo_BiPoint& BP = it.Value();
    const Standard_Address Coordinates = BP.Coordinates();
    if (PntXP1 < PntXP2) {
      if      (TotXMin > PntXP1) TotXMin = PntXP1;
      else if (TotXMax < PntXP2) TotXMax = PntXP2;
    }
    else             {
      if      (TotXMin > PntXP2) TotXMin = PntXP2;
      else if (TotXMax < PntXP1) TotXMax = PntXP1;
    }
    if (PntYP1 < PntYP2) {
      if      (TotYMin > PntYP1) TotYMin = PntYP1;
      else if (TotYMax < PntYP2) TotYMax = PntYP2;
    }
    else             {
      if      (TotYMin > PntYP2) TotYMin = PntYP2;
      else if (TotYMax < PntYP1) TotYMax = PntYP1;
    }
    if (PntZP1 < PntZP2) {
      if      (TotZMin > PntZP1) TotZMin = PntZP1;
      else if (TotZMax < PntZP2) TotZMax = PntZP2;
    }
    else             {
      if      (TotZMin > PntZP2) TotZMin = PntZP2;
      else if (TotZMax < PntZP1) TotZMax = PntZP1;
    }
  }
  Standard_Integer nbFace      = myPolyg.Upper();
  Handle(HLRAlgo_PolyData)* pd = NULL;
  if(nbFace > 0) pd =  (Handle(HLRAlgo_PolyData)*)&(myPolyg.ChangeValue(1));
  
  for (Standard_Integer i = 1; i <= nbFace; i++) {
    (*pd)->UpdateGlobalMinMax(TotMinMax);
    pd++;
  }
}

//=======================================================================
//function : UpdateHiding
//purpose  : 
//=======================================================================

void HLRAlgo_PolyShellData::
UpdateHiding (const Standard_Integer nbHiding)
{
  if (nbHiding > 0)
    myHPolHi = new TColStd_HArray1OfTransient(1,nbHiding);
  else myHPolHi.Nullify();
}

