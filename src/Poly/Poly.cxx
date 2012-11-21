// Created on: 1995-03-06
// Created by: Laurent PAINNOT
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


#include <Standard_Stream.hxx>
#include <Poly.ixx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <Poly_Triangle.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <Poly_Array1OfTriangle.hxx>
#include <Poly_ListOfTriangulation.hxx>

#include <Poly_Polygon3D.hxx>
#include <Poly_Polygon2D.hxx>
#include <Precision.hxx>
#include <TShort_Array1OfShortReal.hxx>
#include <TShort_HArray1OfShortReal.hxx>

//=======================================================================
//function : Catenate
//purpose  : Join several triangulations to one new triangulation object
//=======================================================================

Handle(Poly_Triangulation) Poly::Catenate (const Poly_ListOfTriangulation& lstTri)
{
  Standard_Integer nNodes(0);
  Standard_Integer nTrian(0);

  // Sum up the total number of nodes.
  Poly_ListOfTriangulation::Iterator anIter(lstTri);
  for (; anIter.More(); anIter.Next()) {
    const Handle(Poly_Triangulation)& aTri = anIter.Value();
    if (aTri.IsNull() == Standard_False) {
      nNodes += aTri->NbNodes();
      nTrian += aTri->NbTriangles();
    }
  }

  Handle(Poly_Triangulation) aResult;
  if (nNodes > 0) {
    aResult = new Poly_Triangulation(nNodes, nTrian, Standard_False);
    Standard_Integer i, iNode[3];
    nNodes = 0;
    nTrian = 0;
    TColgp_Array1OfPnt&    arrNode  = aResult->ChangeNodes();
    Poly_Array1OfTriangle& arrTrian = aResult->ChangeTriangles();
    for (anIter.Init(lstTri); anIter.More(); anIter.Next()) {
      const Handle(Poly_Triangulation)& aTri = anIter.Value();
      if (aTri.IsNull() == Standard_False) {
        const TColgp_Array1OfPnt&    srcNode  = aTri->Nodes();
        const Poly_Array1OfTriangle& srcTrian = aTri->Triangles();
        const Standard_Integer nbNodes = aTri->NbNodes(); 
        const Standard_Integer nbTrian = aTri->NbTriangles(); 
        for (i = 1; i <= nbNodes; i++) {
          arrNode.SetValue(i + nNodes, srcNode(i));
        }
        for (i = 1; i <= nbTrian; i++) {
          srcTrian(i).Get(iNode[0], iNode[1], iNode[2]);
          arrTrian.SetValue(i + nTrian, Poly_Triangle(iNode[0] + nNodes,
                                                      iNode[1] + nNodes,
                                                      iNode[2] + nNodes));
        }
        nNodes += nbNodes;
        nTrian += nbTrian;
      }
    }
  }
  return aResult;
}

//=======================================================================
//function : Write
//purpose  :
//=======================================================================

void Poly::Write(const Handle(Poly_Triangulation)& T,
                 Standard_OStream& OS,
                 const Standard_Boolean Compact)
{
  OS << "Poly_Triangulation\n";
  if (Compact) {
    OS << T->NbNodes() << " " << T->NbTriangles() << " ";
    OS << ((T->HasUVNodes()) ? "1" : "0") << "\n";
  }
  else {
    OS << setw(8) << T->NbNodes() << " Nodes\n";
    OS << setw(8) << T->NbTriangles() << " Triangles\n";
    OS << ((T->HasUVNodes()) ? "with" : "without") << " UV nodes\n";
  }

  // write the deflection

  if (!Compact) OS << "Deflection : ";
  OS << T->Deflection() << "\n";

  // write the 3d nodes

  if (!Compact) OS << "\n3D Nodes :\n";

  Standard_Integer i, nbNodes = T->NbNodes();
  const TColgp_Array1OfPnt& Nodes = T->Nodes();
  for (i = 1; i <= nbNodes; i++) {
    if (!Compact) OS << setw(10) << i << " : ";
    if (!Compact) OS << setw(17);
    OS << Nodes(i).X() << " ";
    if (!Compact) OS << setw(17);
    OS << Nodes(i).Y() << " ";
    if (!Compact) OS << setw(17);
    OS << Nodes(i).Z() << "\n";
  }

  if (T->HasUVNodes()) {
    if (!Compact) OS << "\nUV Nodes :\n";
    const TColgp_Array1OfPnt2d& UVNodes = T->UVNodes();
    for (i = 1; i <= nbNodes; i++) {
      if (!Compact) OS << setw(10) << i << " : ";
    if (!Compact) OS << setw(17);
      OS << UVNodes(i).X() << " ";
    if (!Compact) OS << setw(17);
      OS << UVNodes(i).Y() << "\n";
    }
  }

  if (!Compact) OS << "\nTriangles :\n";
  Standard_Integer nbTriangles = T->NbTriangles();
  Standard_Integer n1, n2, n3;
  const Poly_Array1OfTriangle& Triangles = T->Triangles();
  for (i = 1; i <= nbTriangles; i++) {
    if (!Compact) OS << setw(10) << i << " : ";
    Triangles(i).Get(n1, n2, n3);
    if (!Compact) OS << setw(10);
    OS << n1 << " ";
    if (!Compact) OS << setw(10);
    OS << n2 << " ";
    if (!Compact) OS << setw(10);
    OS << n3 << "\n";
  }

}

//=======================================================================
//function : Write
//purpose  :
//=======================================================================

void Poly::Write(const Handle(Poly_Polygon3D)& P,
                 Standard_OStream&             OS,
                 const Standard_Boolean        Compact)
{
  OS << "Poly_Polygon3D\n";
  if (Compact) {
    OS << P->NbNodes() << " ";
    OS << ((P->HasParameters()) ? "1" : "0") << "\n";
  }
  else {
    OS << setw(8) << P->NbNodes() << " Nodes\n";
    OS << ((P->HasParameters()) ? "with" : "without") << " parameters\n";
  }

  // write the deflection

  if (!Compact) OS << "Deflection : ";
  OS << P->Deflection() << "\n";

  // write the nodes

  if (!Compact) OS << "\nNodes :\n";

  Standard_Integer i, nbNodes = P->NbNodes();
  const TColgp_Array1OfPnt& Nodes = P->Nodes();
  for (i = 1; i <= nbNodes; i++) {
    if (!Compact) OS << setw(10) << i << " : ";
    if (!Compact) OS << setw(17);
    OS << Nodes(i).X() << " ";
    if (!Compact) OS << setw(17);
    OS << Nodes(i).Y() << " ";
    if (!Compact) OS << setw(17);
    OS << Nodes(i).Z() << "\n";
  }

  if (P->HasParameters()) {
    if (!Compact) OS << "\nParameters :\n";
    const TColStd_Array1OfReal& Param = P->Parameters();
    for (i = 1; i <= nbNodes; i++) {
      OS << Param(i) << " ";
    }
    OS <<"\n";
  }


}


//=======================================================================
//function : Write
//purpose  :
//=======================================================================

void Poly::Write(const Handle(Poly_Polygon2D)& P,
                 Standard_OStream&             OS,
                 const Standard_Boolean        Compact)
{
  OS << "Poly_Polygon2D\n";
  if (Compact) {
    OS << P->NbNodes() << " ";
  }
  else {
    OS << setw(8) << P->NbNodes() << " Nodes\n";
  }

  // write the deflection

  if (!Compact) OS << "Deflection : ";
  OS << P->Deflection() << "\n";

  // write the nodes

  if (!Compact) OS << "\nNodes :\n";

  Standard_Integer i, nbNodes = P->NbNodes();
  const TColgp_Array1OfPnt2d& Nodes = P->Nodes();
  for (i = 1; i <= nbNodes; i++) {
    if (!Compact) OS << setw(10) << i << " : ";
    if (!Compact) OS << setw(17);
    OS << Nodes(i).X() << " ";
    if (!Compact) OS << setw(17);
    OS << Nodes(i).Y() << "\n";
  }
}



//=======================================================================
//function : Dump
//purpose  :
//=======================================================================

void Poly::Dump(const Handle(Poly_Triangulation)& T, Standard_OStream& OS)
{
  Poly::Write(T,OS,Standard_False);
}


//=======================================================================
//function : Dump
//purpose  :
//=======================================================================

void Poly::Dump(const Handle(Poly_Polygon3D)& P, Standard_OStream& OS)
{
  Poly::Write(P,OS,Standard_False);
}


//=======================================================================
//function : Dump
//purpose  :
//=======================================================================

void Poly::Dump(const Handle(Poly_Polygon2D)& P, Standard_OStream& OS)
{
  Poly::Write(P,OS,Standard_False);
}


//=======================================================================
//function : ReadTriangulation
//purpose  :
//=======================================================================

Handle(Poly_Triangulation) Poly::ReadTriangulation(Standard_IStream& IS)
{
  // Read a triangulation

  char line[100];
  IS >> line;
  if (strcmp(line,"Poly_Triangulation")) {
    cout << "Not a Triangulation in the file" << endl;
    return Handle(Poly_Triangulation)();
  }

  Standard_Integer nbNodes, nbTriangles;
  Standard_Boolean hasUV;
  IS >> nbNodes >> nbTriangles >> hasUV;

  Standard_Real d;
  IS >> d;

  // read the 3d nodes
  Standard_Real x,y,z;
  Standard_Integer i;
  TColgp_Array1OfPnt Nodes(1, nbNodes);
  TColgp_Array1OfPnt2d UVNodes(1, nbNodes);

  for (i = 1; i <= nbNodes; i++) {
    IS >> x >> y >> z;
    Nodes(i).SetCoord(x,y,z);
  }

  // read the UV points if necessary

  if (hasUV) {
    for (i = 1; i <= nbNodes; i++) {
      IS >> x >> y;
      UVNodes(i).SetCoord(x,y);
    }
  }


  // read the triangles
  Standard_Integer n1,n2,n3;
  Poly_Array1OfTriangle Triangles(1, nbTriangles);
  for (i = 1; i <= nbTriangles; i++) {
    IS >> n1 >> n2 >> n3;
    Triangles(i).Set(n1,n2,n3);
  }


  Handle(Poly_Triangulation) T;

  if (hasUV) T =  new Poly_Triangulation(Nodes,UVNodes,Triangles);
  else T = new Poly_Triangulation(Nodes,Triangles);

  T->Deflection(d);

  return T;
}


//=======================================================================
//function : ReadPolygon3D
//purpose  :
//=======================================================================

Handle(Poly_Polygon3D) Poly::ReadPolygon3D(Standard_IStream& IS)
{
  // Read a 3d polygon

  char line[100];
  IS >> line;
  if (strcmp(line,"Poly_Polygon3D")) {
    cout << "Not a Polygon3D in the file" << endl;
    return Handle(Poly_Polygon3D)();
  }

  Standard_Integer nbNodes;
  IS >> nbNodes;

  Standard_Boolean hasparameters;
  IS >> hasparameters;

  Standard_Real d;
  IS >> d;

  // read the nodes
  Standard_Real x,y,z;
  Standard_Integer i;
  TColgp_Array1OfPnt Nodes(1, nbNodes);

  for (i = 1; i <= nbNodes; i++) {
    IS >> x >> y >> z;
    Nodes(i).SetCoord(x,y,z);
  }

  TColStd_Array1OfReal Param(1,nbNodes);
  if (hasparameters) {
    for (i = 1; i <= nbNodes; i++) {
      IS >> Param(i);
    }
  }

  Handle(Poly_Polygon3D) P;
  if (!hasparameters)
    P = new Poly_Polygon3D(Nodes);
  else
    P = new Poly_Polygon3D(Nodes, Param);

  P->Deflection(d);

  return P;
}

//=======================================================================
//function : ReadPolygon3D
//purpose  :
//=======================================================================

Handle(Poly_Polygon2D) Poly::ReadPolygon2D(Standard_IStream& IS)
{
  // Read a 2d polygon

  char line[100];
  IS >> line;
  if (strcmp(line,"Poly_Polygon2D")) {
    cout << "Not a Polygon2D in the file" << endl;
    return Handle(Poly_Polygon2D)();
  }

  Standard_Integer nbNodes;
  IS >> nbNodes;

  Standard_Real d;
  IS >> d;

  // read the nodes
  Standard_Real x,y;
  Standard_Integer i;
  TColgp_Array1OfPnt2d Nodes(1, nbNodes);

  for (i = 1; i <= nbNodes; i++) {
    IS >> x >> y;
    Nodes(i).SetCoord(x,y);
  }

  Handle(Poly_Polygon2D) P =
    new Poly_Polygon2D(Nodes);

  P->Deflection(d);

  return P;
}

//=======================================================================
//function : ComputeNormals
//purpose  :
//=======================================================================

void  Poly::ComputeNormals(const Handle(Poly_Triangulation)& Tri)
{
  const TColgp_Array1OfPnt&     arrNodes = Tri->Nodes();
  const Poly_Array1OfTriangle & arrTri   = Tri->Triangles();
  Standard_Integer              nbNormVal  = Tri->NbNodes() * 3;
  const Handle(TShort_HArray1OfShortReal) Normals =
    new TShort_HArray1OfShortReal(1, nbNormVal);
  Normals->Init(0.F);

  Standard_ShortReal            * arrNormal = &(Normals->ChangeValue(1));

  Standard_Real                 aCoord[3];
  Standard_Integer              iNode[3] = {0, 0, 0};
  Standard_Integer              iN, iTri;
  const Standard_Real eps2 = Precision::SquareConfusion();

  for (iTri = 1; iTri <= arrTri.Length(); iTri++) {
    // Get the nodes of the current triangle
    arrTri(iTri).Get (iNode[0], iNode[1], iNode[2]);
      const gp_XYZ aVec[2] = {
        arrNodes(iNode[1]).XYZ() - arrNodes(iNode[0]).XYZ(),
        arrNodes(iNode[2]).XYZ() - arrNodes(iNode[0]).XYZ()
      };

    // Find the normal vector of the current triangle
    gp_XYZ aNorm = aVec[0] ^ aVec[1];
    const Standard_Real aMod = aNorm.SquareModulus();
    if (aMod > eps2) {
      aNorm /= sqrt(aMod);
      aNorm.Coord (aCoord[0], aCoord[1], aCoord[2]);
      iNode[0] = (iNode[0]-1)*3;
      iNode[1] = (iNode[1]-1)*3;
      iNode[2] = (iNode[2]-1)*3;
      arrNormal[iNode[0]+0] += (Standard_ShortReal)aCoord[0];
      arrNormal[iNode[0]+1] += (Standard_ShortReal)aCoord[1];
      arrNormal[iNode[0]+2] += (Standard_ShortReal)aCoord[2];
      arrNormal[iNode[1]+0] += (Standard_ShortReal)aCoord[0];
      arrNormal[iNode[1]+1] += (Standard_ShortReal)aCoord[1];
      arrNormal[iNode[1]+2] += (Standard_ShortReal)aCoord[2];
      arrNormal[iNode[2]+0] += (Standard_ShortReal)aCoord[0];
      arrNormal[iNode[2]+1] += (Standard_ShortReal)aCoord[1];
      arrNormal[iNode[2]+2] += (Standard_ShortReal)aCoord[2];
    }
  }
  // Normalize all vectors
  for (iN = 0; iN < nbNormVal; iN+=3) {
    Standard_Real aMod (arrNormal[iN+0]*arrNormal[iN+0] +
                        arrNormal[iN+1]*arrNormal[iN+1] +
                        arrNormal[iN+2]*arrNormal[iN+2]);
    if (aMod < eps2) {
      arrNormal[iN+0] = 0.f;
      arrNormal[iN+1] = 0.f;
      arrNormal[iN+2] = 1.f;
    } else {
      aMod = sqrt(aMod);
      arrNormal[iN+0] = Standard_ShortReal(arrNormal[iN+0]/aMod);
      arrNormal[iN+1] = Standard_ShortReal(arrNormal[iN+1]/aMod);
      arrNormal[iN+2] = Standard_ShortReal(arrNormal[iN+2]/aMod);
    }
  }

  Tri->SetNormals(Normals);
}

//=======================================================================
//function : PointOnTriangle
//purpose  : 
//=======================================================================

Standard_Real Poly::PointOnTriangle (const gp_XY& theP1, const gp_XY& theP2, const gp_XY& theP3, 
			             const gp_XY& theP, gp_XY& theUV)
{
  gp_XY aDP = theP  - theP1;
  gp_XY aDU = theP2 - theP1;
  gp_XY aDV = theP3 - theP1;
  Standard_Real aDet = aDU ^ aDV;

  // case of non-degenerated triangle
  if ( Abs (aDet) > gp::Resolution() )
  {
    Standard_Real aU =  (aDP ^ aDV) / aDet;
    Standard_Real aV = -(aDP ^ aDU) / aDet;

    // if point is inside triangle, just return parameters
    if ( aU > -gp::Resolution() &&
         aV > -gp::Resolution() &&
         1. - aU - aV > -gp::Resolution() ) 
    {
      theUV.SetCoord (aU, aV);
      return 0.;
    }

    // else find closest point on triangle sides; note that in general case  
    // triangle can be very distorted and it is necessary to check 
    // projection on all sides regardless of values of computed parameters

    // project on side U=0
    aU = 0.;
    aV = Min (1., Max (0., (aDP * aDV) / aDV.SquareModulus()));
    Standard_Real aD = (aV * aDV - aDP).SquareModulus();

    // project on side V=0
    Standard_Real u = Min (1., Max (0., (aDP * aDU) / aDU.SquareModulus()));
    Standard_Real d = (u * aDU - aDP).SquareModulus();
    if ( d < aD )
    {
      aU = u;
      aV = 0.;
      aD = d;
    }

    // project on side U+V=1
    gp_XY aDUV = aDV - aDU;
    Standard_Real v = Min (1., Max (0., ((aDP - aDU) * aDUV) / aDUV.SquareModulus()));
    d = (theP2 + v * aDUV - theP).SquareModulus();
    if ( d < aD )
    {
      aU = 1. - v;
      aV = v;
      aD = d;
    }

    theUV.SetCoord (aU, aV);
    return aD;
  }

  // degenerated triangle
  Standard_Real aL2U = aDU.SquareModulus();
  Standard_Real aL2V = aDV.SquareModulus();
  if ( aL2U < gp::Resolution() ) // side 1-2 is degenerated
  {
    if ( aL2V < gp::Resolution() ) // whole triangle is degenerated to point
    {
      theUV.SetCoord (0., 0.);
      return (theP - theP1).SquareModulus();
    }
    else
    {
      theUV.SetCoord (0., (aDP * aDV) / aL2V);
      return (theP - (theP1 + theUV.Y() * aDV)).SquareModulus();
    }
  }
  else if ( aL2V < gp::Resolution() ) // side 1-3 is degenerated
  {
    theUV.SetCoord ((aDP * aDU) / aL2U, 0.);
    return (theP - (theP1 + theUV.X() * aDU)).SquareModulus();
  }
  else // sides 1-2 and 1-3 are collinear
  {
    // select parameter on one of sides so as to have points closer to picked
    Standard_Real aU = Min (1., Max (0., (aDP * aDU) / aL2U));
    Standard_Real aV = Min (1., Max (0., (aDP * aDV) / aL2V));
    Standard_Real aD1 = (aDP - aU * aDU).SquareModulus();
    Standard_Real aD2 = (aDP - aV * aDV).SquareModulus();
    if ( aD1 < aD2 )
    {
      theUV.SetCoord ((aDP * aDU) / aL2U, 0.);
      return aD1;
    }
    else
    {
      theUV.SetCoord (0., (aDP * aDV) / aL2V);
      return aD2;
    }
  }
}

