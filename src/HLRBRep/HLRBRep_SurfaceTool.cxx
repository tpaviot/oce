// Created by: Laurent BUCHARD
// Copyright (c) 1993-1999 Matra Datavision
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


#include <HLRBRep_SurfaceTool.ixx>
#include <BRepAdaptor_Surface.hxx>

Standard_Integer  HLRBRep_SurfaceTool::NbSamplesU(const Standard_Address S) { 
  Standard_Integer nbs;
  GeomAbs_SurfaceType typS = ((BRepAdaptor_Surface *)S)->GetType();
  switch(typS) { 
  case GeomAbs_Plane:
    {
      nbs = 2;
    }
    break;
  case GeomAbs_BezierSurface: 
    {
      nbs =  3 + ((BRepAdaptor_Surface *)S)->NbUPoles();
    }
    break;
  case GeomAbs_BSplineSurface: 
    {
      nbs = ((BRepAdaptor_Surface *)S)->NbUKnots();
      nbs*= ((BRepAdaptor_Surface *)S)->UDegree();
      if(nbs < 2) nbs=2;
      
    }
    break;
  case GeomAbs_Torus: 
    {
      nbs = 20;
    }
    break;
  case GeomAbs_Cylinder:
  case GeomAbs_Cone:
  case GeomAbs_Sphere:
  case GeomAbs_SurfaceOfRevolution:
  case GeomAbs_SurfaceOfExtrusion:
    {
      nbs = 10;
    }
    break;
    
  default: 
    {
      nbs = 10;
    }
    break;
  }
  return(nbs);
}

Standard_Integer  HLRBRep_SurfaceTool::NbSamplesV(const Standard_Address S) { 
  Standard_Integer nbs;
  GeomAbs_SurfaceType typS = ((BRepAdaptor_Surface *)S)->GetType();
  switch(typS) { 
  case GeomAbs_Plane:
    {
      nbs = 2;
    }
    break;
  case GeomAbs_BezierSurface: 
    {
      nbs =  3 + ((BRepAdaptor_Surface *)S)->NbVPoles();
    }
    break;
  case GeomAbs_BSplineSurface: 
    {
      nbs = ((BRepAdaptor_Surface *)S)->NbVKnots();
      nbs*= ((BRepAdaptor_Surface *)S)->VDegree();
      if(nbs < 2) nbs=2;
      
    }
    break;
  case GeomAbs_Cylinder:
  case GeomAbs_Cone:
  case GeomAbs_Sphere:
  case GeomAbs_Torus:
  case GeomAbs_SurfaceOfRevolution:
  case GeomAbs_SurfaceOfExtrusion:
    {
      nbs = 15;
    }
    break;
    
  default: 
    {
      nbs = 10;
    }
    break;
  }
  return(nbs);
}

Standard_Integer  HLRBRep_SurfaceTool::NbSamplesU(const Standard_Address S,
						      const Standard_Real u1,
						      const Standard_Real u2) { 
  Standard_Integer nbs = NbSamplesU(S);
  Standard_Integer n = nbs;
  if(nbs>10) { 
    Standard_Real uf = FirstUParameter(S);
    Standard_Real ul = LastUParameter(S);
    n*= (Standard_Integer)((u2-u1)/(uf-ul));
    if(n>nbs) n = nbs;
    if(n<5)   n = 5;
  }
  return(n);
}

Standard_Integer  HLRBRep_SurfaceTool::NbSamplesV(const Standard_Address S,
						      const Standard_Real v1,
						      const Standard_Real v2) { 
  Standard_Integer nbs = NbSamplesV(S);
  Standard_Integer n = nbs;
  if(nbs>10) { 
    Standard_Real vf = FirstVParameter(S);
    Standard_Real vl = LastVParameter(S);
    n*= (Standard_Integer)((v2-v1)/(vf-vl));
    if(n>nbs) n = nbs;
    if(n<5)   n = 5;
  }
  return(n);
}
