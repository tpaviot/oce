// Created on: 1994-03-30
// Created by: Laurent BUCHARD
// Copyright (c) 1994-1999 Matra Datavision
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




#define MARCHEPASSIUNESEULEFACE 0


#ifdef DEB
#define LBRCOMPT 0
#else 
#define LBRCOMPT 0
#endif

#if LBRCOMPT
#include <stdio.h>

class StatistiquesBRepClass3d { 
public:
  long unsigned NbConstrVide;
  long unsigned NbLoad;
  long unsigned NbConstrShape;
  long unsigned NbConstrShapePnt;
  long unsigned NbPerform;
  long unsigned NbPerformRejection;
  long unsigned NbPerformInfinitePoint;
  long unsigned NbDestroy;
public:
  StatistiquesBRepClass3d() { 
    NbConstrVide=NbLoad=NbConstrShape=NbConstrShapePnt=NbPerform=NbPerformInfinitePoint=NbDestroy=0;
  }
  ~StatistiquesBRepClass3d() { 
    printf("\n--- Statistiques BRepClass3d:\n");

    printf("\nConstructeurVide    : %10lu",NbConstrVide);
    printf("\nConstructeur(Shape) : %10lu",NbConstrShape);
    printf("\nLoad(Shape)         : %10lu",NbLoad);
    printf("\nPerform(pnt3d)      : %10lu",NbPerform);
    printf("\nPerform(pnt3d) REJ  : %10lu",NbPerformRejection);
    printf("\nPerformInfinitePoint: %10lu",NbPerformInfinitePoint);
    printf("\nDestroy             : %10lu",NbDestroy             );
  }
};

static StatistiquesBRepClass3d STAT;
#endif



#include <BRepClass3d_SolidClassifier.ixx>

#include <TopoDS_Shape.hxx>

BRepClass3d_SolidClassifier::BRepClass3d_SolidClassifier()
{
  aSolidLoaded=isaholeinspace=Standard_False;
#if LBRCOMPT
  STAT.NbConstrVide++;
#endif
}


void BRepClass3d_SolidClassifier::Load(const TopoDS_Shape& S) {

#if LBRCOMPT
  STAT.NbLoad++;
#endif

  if(aSolidLoaded) { 
    explorer.Destroy();
  }
  explorer.InitShape(S);
  aSolidLoaded = Standard_True;


#if MARCHEPASSIUNESEULEFACE
  PerformInfinitePoint(1e-7);
  if(State()==TopAbs_OUT) { 
    isaholeinspace=Standard_False;
  }
  else { 
    isaholeinspace=Standard_True;
  }
#endif  
}

BRepClass3d_SolidClassifier::BRepClass3d_SolidClassifier(const TopoDS_Shape& S)
:  aSolidLoaded(Standard_True),explorer(S) 
{ 
#if LBRCOMPT
  STAT.NbConstrShape++;
#endif
#if MARCHEPASSIUNESEULEFACE
  PerformInfinitePoint(1e-7);
  if(State()==TopAbs_OUT) { 
    isaholeinspace=Standard_False;
  }
  else { 
    isaholeinspace=Standard_True;
  }
#endif  
}

BRepClass3d_SolidClassifier::BRepClass3d_SolidClassifier(const TopoDS_Shape& S,
							 const gp_Pnt&       P,
							 const Standard_Real Tol) 
: explorer(S) { 
#if LBRCOMPT
  STAT.NbConstrShapePnt++;
#endif
  aSolidLoaded = Standard_True;
#if MARCHEPASSIUNESEULEFACE  
  PerformInfinitePoint(1e-7);
  if(State()==TopAbs_OUT) { 
    isaholeinspace=Standard_False;
  }
  else { 
    isaholeinspace=Standard_True;
  }
  
  if(isaholeinspace==Standard_False) { 
    if(explorer.Box().IsOut(P)) { 
      ForceOut(); 
    }
    else {
      Perform(P,Tol); 
    }
  }
  else { 
    if(explorer.Box().IsOut(P)) { 
      ForceIn(); 
    }
    else {
      Perform(P,Tol); 
    }
  }
#else 
  Perform(P,Tol); 
#endif
}


void BRepClass3d_SolidClassifier::Perform(const gp_Pnt& P,const Standard_Real Tol) { 
#if LBRCOMPT
  STAT.NbPerform++;
#endif
#if MARCHEPASSIUNESEULEFACE 
  if(aSolidLoaded) { 
    if(isaholeinspace==Standard_False) { 
      if(explorer.Box().IsOut(P)) { 
	ForceOut(); 
#if LBRCOMPT
	STAT.NbPerformRejection++;
#endif
	
      }
      else {
	BRepClass3d_SClassifier::Perform(explorer,P,Tol);
      }
    }
    else { 
      if(explorer.Box().IsOut(P)) { 
	ForceIn(); 
#if LBRCOMPT
	STAT.NbPerformRejection++;
#endif
	
      }
      else {
	BRepClass3d_SClassifier::Perform(explorer,P,Tol);
      }
    }
  }
#else 
  BRepClass3d_SClassifier::Perform(explorer,P,Tol);
#endif
}

void BRepClass3d_SolidClassifier::PerformInfinitePoint(const Standard_Real Tol) { 
#if LBRCOMPT
  STAT.NbPerformInfinitePoint++;
#endif

  if(aSolidLoaded) { 
    BRepClass3d_SClassifier::PerformInfinitePoint(explorer,Tol);
    if(State()==TopAbs_OUT) 
      isaholeinspace=Standard_False;
    else 
      isaholeinspace=Standard_True;
  }
}



void BRepClass3d_SolidClassifier::Destroy() { 
#if LBRCOMPT
  STAT.NbDestroy++;
#endif

  if(aSolidLoaded) { 
    explorer.Destroy();
    aSolidLoaded = Standard_False;
  }
}



