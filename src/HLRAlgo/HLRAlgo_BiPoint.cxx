// Created on: 1995-06-22
// Created by: Christophe MARION
// Copyright (c) 1995-1999 Matra Datavision
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


#ifndef No_Exception
#define No_Exception
#endif
#include <HLRAlgo_BiPoint.ixx>

#define PntX1  myCoordinates[ 0]
#define PntY1  myCoordinates[ 1]
#define PntZ1  myCoordinates[ 2]
#define PntX2  myCoordinates[ 3]
#define PntY2  myCoordinates[ 4]
#define PntZ2  myCoordinates[ 5]
#define PntXP1 myCoordinates[ 6]
#define PntYP1 myCoordinates[ 7]
#define PntZP1 myCoordinates[ 8]
#define PntXP2 myCoordinates[ 9]
#define PntYP2 myCoordinates[10]
#define PntZP2 myCoordinates[11]

#define ShapeIndex  myIndices[0]
#define FaceConex1  myIndices[1]
#define Face1Pt1    myIndices[2]
#define Face1Pt2    myIndices[3]
#define FaceConex2  myIndices[4]
#define Face2Pt1    myIndices[5]
#define Face2Pt2    myIndices[6]
#define MinSeg      myIndices[7]
#define MaxSeg      myIndices[8]
#define SegFlags    myIndices[9]

//=======================================================================
//function : HLRAlgo_BiPoint
//purpose  : 
//=======================================================================

HLRAlgo_BiPoint::HLRAlgo_BiPoint (const Standard_Real X1,
				  const Standard_Real Y1,
				  const Standard_Real Z1,
				  const Standard_Real X2,
				  const Standard_Real Y2,
				  const Standard_Real Z2,
				  const Standard_Real XT1,
				  const Standard_Real YT1,
				  const Standard_Real ZT1,
				  const Standard_Real XT2,
				  const Standard_Real YT2,
				  const Standard_Real ZT2,
				  const Standard_Integer Index,
				  const Standard_Boolean reg1,
				  const Standard_Boolean regn,
				  const Standard_Boolean outl,
				  const Standard_Boolean intl)
{
  PntX1 = X1;
  PntY1 = Y1;
  PntZ1 = Z1;
  PntX2 = X2;
  PntY2 = Y2;
  PntZ2 = Z2;
  PntXP1 = XT1;
  PntYP1 = YT1;
  PntZP1 = ZT1;
  PntXP2 = XT2;
  PntYP2 = YT2;
  PntZP2 = ZT2;
  ShapeIndex = Index;
  FaceConex1 = Face1Pt1   = Face1Pt2   = 
    FaceConex2 = Face2Pt1   = Face2Pt2   = 0;
  SegFlags   = 0;
  Rg1Line(reg1);
  RgNLine(regn);
  OutLine(outl);
  IntLine(intl);
  Hidden(Standard_False);
}

//=======================================================================
//function : HLRAlgo_BiPoint
//purpose  : 
//=======================================================================

HLRAlgo_BiPoint::HLRAlgo_BiPoint (const Standard_Real X1,
				  const Standard_Real Y1,
				  const Standard_Real Z1,
				  const Standard_Real X2,
				  const Standard_Real Y2,
				  const Standard_Real Z2,
				  const Standard_Real XT1,
				  const Standard_Real YT1,
				  const Standard_Real ZT1,
				  const Standard_Real XT2,
				  const Standard_Real YT2,
				  const Standard_Real ZT2,
				  const Standard_Integer Index,
				  const Standard_Boolean flag)
{
  PntX1 = X1;
  PntY1 = Y1;
  PntZ1 = Z1;
  PntX2 = X2;
  PntY2 = Y2;
  PntZ2 = Z2;
  PntXP1 = XT1;
  PntYP1 = YT1;
  PntZP1 = ZT1;
  PntXP2 = XT2;
  PntYP2 = YT2;
  PntZP2 = ZT2;
  ShapeIndex = Index;
  FaceConex1 = Face1Pt1   = Face1Pt2   = 
    FaceConex2 = Face2Pt1   = Face2Pt2   = 0;
  SegFlags   = flag;
  Hidden(Standard_False);
}

//=======================================================================
//function : HLRAlgo_BiPoint
//purpose  : 
//=======================================================================

HLRAlgo_BiPoint::HLRAlgo_BiPoint (const Standard_Real X1,
				  const Standard_Real Y1,
				  const Standard_Real Z1,
				  const Standard_Real X2,
				  const Standard_Real Y2,
				  const Standard_Real Z2,
				  const Standard_Real XT1,
				  const Standard_Real YT1,
				  const Standard_Real ZT1,
				  const Standard_Real XT2,
				  const Standard_Real YT2,
				  const Standard_Real ZT2,
				  const Standard_Integer Index,
				  const Standard_Integer i1,
				  const Standard_Integer i1p1,
				  const Standard_Integer i1p2,
				  const Standard_Boolean reg1,
				  const Standard_Boolean regn,
				  const Standard_Boolean outl,
				  const Standard_Boolean intl)
{
  PntX1 = X1;
  PntY1 = Y1;
  PntZ1 = Z1;
  PntX2 = X2;
  PntY2 = Y2;
  PntZ2 = Z2;
  PntXP1 = XT1;
  PntYP1 = YT1;
  PntZP1 = ZT1;
  PntXP2 = XT2;
  PntYP2 = YT2;
  PntZP2 = ZT2;
  ShapeIndex = Index;
  FaceConex1 = i1;
  Face1Pt1   = i1p1;
  Face1Pt2   = i1p2;
  FaceConex2 = Face2Pt1   = Face2Pt2   = 0;
  SegFlags   = 0;
  Rg1Line(reg1);
  RgNLine(regn);
  OutLine(outl);
  IntLine(intl);
  Hidden(Standard_False);
}

//=======================================================================
//function : HLRAlgo_BiPoint
//purpose  : 
//=======================================================================

HLRAlgo_BiPoint::HLRAlgo_BiPoint (const Standard_Real X1,
				  const Standard_Real Y1,
				  const Standard_Real Z1,
				  const Standard_Real X2,
				  const Standard_Real Y2,
				  const Standard_Real Z2,
				  const Standard_Real XT1,
				  const Standard_Real YT1,
				  const Standard_Real ZT1,
				  const Standard_Real XT2,
				  const Standard_Real YT2,
				  const Standard_Real ZT2,
				  const Standard_Integer Index,
				  const Standard_Integer i1,
				  const Standard_Integer i1p1,
				  const Standard_Integer i1p2,
				  const Standard_Boolean flag)
{
  PntX1 = X1;
  PntY1 = Y1;
  PntZ1 = Z1;
  PntX2 = X2;
  PntY2 = Y2;
  PntZ2 = Z2;
  PntXP1 = XT1;
  PntYP1 = YT1;
  PntZP1 = ZT1;
  PntXP2 = XT2;
  PntYP2 = YT2;
  PntZP2 = ZT2;
  ShapeIndex = Index;
  FaceConex1 = i1;
  Face1Pt1   = i1p1;
  Face1Pt2   = i1p2;
  FaceConex2 = Face2Pt1   = Face2Pt2   = 0;
  SegFlags   = flag;
  Hidden(Standard_False);
}

//=======================================================================
//function : HLRAlgo_BiPoint
//purpose  : 
//=======================================================================

HLRAlgo_BiPoint::HLRAlgo_BiPoint (const Standard_Real X1,
				  const Standard_Real Y1,
				  const Standard_Real Z1,
				  const Standard_Real X2,
				  const Standard_Real Y2,
				  const Standard_Real Z2,
				  const Standard_Real XT1,
				  const Standard_Real YT1,
				  const Standard_Real ZT1,
				  const Standard_Real XT2,
				  const Standard_Real YT2,
				  const Standard_Real ZT2,
				  const Standard_Integer Index,
				  const Standard_Integer i1,
				  const Standard_Integer i1p1,
				  const Standard_Integer i1p2,
				  const Standard_Integer i2,
				  const Standard_Integer i2p1,
				  const Standard_Integer i2p2,
				  const Standard_Boolean reg1,
				  const Standard_Boolean regn,
				  const Standard_Boolean outl,
				  const Standard_Boolean intl)
{
  PntX1 = X1;
  PntY1 = Y1;
  PntZ1 = Z1;
  PntX2 = X2;
  PntY2 = Y2;
  PntZ2 = Z2;
  PntXP1 = XT1;
  PntYP1 = YT1;
  PntZP1 = ZT1;
  PntXP2 = XT2;
  PntYP2 = YT2;
  PntZP2 = ZT2;
  ShapeIndex = Index;
  FaceConex1 = i1;
  Face1Pt1   = i1p1;
  Face1Pt2   = i1p2;
  FaceConex2 = i2;
  Face2Pt1   = i2p1;
  Face2Pt2   = i2p2;
  SegFlags   = 0;
  Rg1Line(reg1);
  RgNLine(regn);
  OutLine(outl);
  IntLine(intl);
  Hidden(Standard_False);
}

//=======================================================================
//function : HLRAlgo_BiPoint
//purpose  : 
//=======================================================================

HLRAlgo_BiPoint::HLRAlgo_BiPoint (const Standard_Real X1,
				  const Standard_Real Y1,
				  const Standard_Real Z1,
				  const Standard_Real X2,
				  const Standard_Real Y2,
				  const Standard_Real Z2,
				  const Standard_Real XT1,
				  const Standard_Real YT1,
				  const Standard_Real ZT1,
				  const Standard_Real XT2,
				  const Standard_Real YT2,
				  const Standard_Real ZT2,
				  const Standard_Integer Index,
				  const Standard_Integer i1,
				  const Standard_Integer i1p1,
				  const Standard_Integer i1p2,
				  const Standard_Integer i2,
				  const Standard_Integer i2p1,
				  const Standard_Integer i2p2,
				  const Standard_Boolean flag)
{
  PntX1 = X1;
  PntY1 = Y1;
  PntZ1 = Z1;
  PntX2 = X2;
  PntY2 = Y2;
  PntZ2 = Z2;
  PntXP1 = XT1;
  PntYP1 = YT1;
  PntZP1 = ZT1;
  PntXP2 = XT2;
  PntYP2 = YT2;
  PntZP2 = ZT2;
  ShapeIndex = Index;
  FaceConex1 = i1;
  Face1Pt1   = i1p1;
  Face1Pt2   = i1p2;
  FaceConex2 = i2;
  Face2Pt1   = i2p1;
  Face2Pt2   = i2p2;
  SegFlags   = flag;
  Hidden(Standard_False);
}
