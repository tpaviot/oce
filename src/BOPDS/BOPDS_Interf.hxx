// Created by: Peter KURNEV
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


#ifndef BOPDS_Interf_HeaderFile
#define BOPDS_Interf_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif

#ifndef _IntTools_CommonPrt_HeaderFile
#include <IntTools_CommonPrt.hxx>
#endif

#include <NCollection_BaseAllocator.hxx>
#include <BOPDS_VectorOfCurve.hxx>
#include <BOPDS_VectorOfPoint.hxx>
/**
 * The class BOPDS_Interf is is to store the information about
 * the interference between two shapes. 
 * The class BOPDS_Interf is root class 
 *
*/
//=======================================================================
//function : BOPDS_Interf
//purpose  : 
//=======================================================================
class BOPDS_Interf  {
 public:
  //
  /**
   * Sets the indices of interferred shapes
   * @param theIndex1
   *   index of the first shape
   * @param theIndex2
   *   index of the second shape
   */
  void SetIndices(const Standard_Integer theIndex1,
		  const Standard_Integer theIndex2) {
    myIndex1=theIndex1; 
    myIndex2=theIndex2; 
  }; 
  //
  /**
   * Returns the indices of interferred shapes
   * @param theIndex1
   *   index of the first shape
   * @param theIndex2
   *   index of the second shape
   */
  void Indices(Standard_Integer& theIndex1,
	       Standard_Integer& theIndex2) const {
		 theIndex1=myIndex1; 
		 theIndex2=myIndex2; 
	       };
  //
  /**
   * Sets the index of the first interferred shape
   * @param theIndex
   *   index of the first shape 
   */
  void SetIndex1(const Standard_Integer theIndex) {
    myIndex1=theIndex; 
  };
  //
  /**
   * Sets the index of the second interferred shape
   * @param theIndex
   *   index of the second shape 
   */
  void SetIndex2(const Standard_Integer theIndex) {
    myIndex2=theIndex;
  };
  //
  /**
   * Returns the index of the first interferred shape
   * @return
   *   index of the first shape 
   */
  Standard_Integer Index1() const {
    return myIndex1; 
  };
  //
  /**
   * Returns the index of the second interferred shape
   * @return
   *   index of the second shape 
   */
  Standard_Integer Index2() const {
    return myIndex2; 
  };
  //
  /**
   * Returns the index of that are opposite to the given index
   * @param theI
   *   the index
   * @return
   *   index of opposite shape 
   */
  Standard_Integer OppositeIndex(const Standard_Integer theI) const {
    if (theI==myIndex1) {
      return myIndex2;
    }
    else if(theI==myIndex2) {
      return myIndex1;
    }
    else {
      return -1;
    }
  };
  //
  /**
   * Returns true if the interference contains given index
   * @param theIndex 
   *   the index
   * @return
   *   true if the interference contains given index
   */
  Standard_Boolean Contains(const Standard_Integer theIndex)const {
    return (myIndex1==theIndex || myIndex2==theIndex);
  }
  //
  /**
   * Sets the index of new shape 
   * @param theIndex 
   *   the index
   */
  void SetIndexNew(const Standard_Integer theIndex) {
    myIndexNew=theIndex;
  };
  //
  //
  /**
   * Returns the index of new shape 
   * @return theIndex 
   *   the index of new shape 
   */
  Standard_Integer IndexNew() const {
    return myIndexNew; 
  };
  //
  /**
   * Returns true if the interference has index of new shape
   * that is equal to the given index 
   * @param theIndex 
   *   the index
   * @return true if the interference has index of new shape
   * that is equal to the given index 
   */
  Standard_Boolean HasIndexNew(Standard_Integer& theIndex) const {
    theIndex=myIndexNew;
    return (myIndexNew>=0);
  };
  //
  /**
   * Returns true if the interference has index of new shape
   *   the index
   * @return true if the interference has index of new shape
   */
  Standard_Boolean HasIndexNew() const {
    return (myIndexNew>=0);
  };
  //
 protected:     
  BOPDS_Interf() :
    myIndex1(-1), 
    myIndex2(-1),
    myIndexNew(-1),
    myAllocator(NCollection_BaseAllocator::CommonBaseAllocator()) {
  };
  //
  BOPDS_Interf(const Handle(NCollection_BaseAllocator)& theAllocator) :
    myIndex1(-1), 
    myIndex2(-1),
    myIndexNew(-1),
    myAllocator(theAllocator) {
  };
  //
  virtual ~BOPDS_Interf() {
  };
  
 protected:  	
  Standard_Integer myIndex1;
  Standard_Integer myIndex2;
  Standard_Integer myIndexNew;
  Handle(NCollection_BaseAllocator) myAllocator;
};
/**
 * The class BOPDS_InterfVV is is to store the information about
 * the interference of the type vertex/vertex. 
*/
//=======================================================================
//function : BOPDS_InterfVV
//purpose  : 
//=======================================================================
class BOPDS_InterfVV  : public BOPDS_Interf {
 public:
  //
  /**
   *  Constructor
   */
  BOPDS_InterfVV() : BOPDS_Interf() {
  };
  //
  /**
   *  Constructor
   * @param theAllocator
   *   allocator to manage the memory
   */
  BOPDS_InterfVV(const Handle(NCollection_BaseAllocator)& theAllocator) 
    : BOPDS_Interf(theAllocator) {
  };
  //
  /**
   *  Destructor
   */
  virtual ~BOPDS_InterfVV() {
  };
  //
};
/**
 * The class BOPDS_InterfVE is is to store the information about
 * the interference of the type vertex/edge. 
*/
//=======================================================================
//function : BOPDS_InterfVE
//purpose  : 
//=======================================================================
class BOPDS_InterfVE  : public BOPDS_Interf {
 public:
  //
  /**
   *  Constructor
   */
  BOPDS_InterfVE() 
    :
      BOPDS_Interf(),
      myParameter(0.) {
  };
  //
  /**
   *  Constructor
   * @param theAllocator
   *   allocator to manage the memory
   */
  BOPDS_InterfVE(const Handle(NCollection_BaseAllocator)& theAllocator) 
    :
      BOPDS_Interf(theAllocator),
      myParameter(0.) {
  };
  //
  /**
   *  Destructor
   */
  virtual ~BOPDS_InterfVE() {
  };
  //
  /**
   *  Modifier
   * Sets the value of parameter 
   * of the point of the vertex 
   * on the curve of the edge
   * @param theT
   *   value of parameter 
   */
  void SetParameter(const Standard_Real theT) {
    myParameter=theT;
  };
  //
  /**
   *  Selector
   * Returrns the value of parameter 
   * of the point of the vertex 
   * on the curve of the edge
   * @return
   *   value of parameter 
   */
  Standard_Real Parameter() const {
    return myParameter;
  };
  
 protected:
  Standard_Real myParameter;
  
};
/**
 * The class BOPDS_InterfVF is is to store the information about
 * the interference of the type vertex/face 
*/
//=======================================================================
//function : BOPDS_InterfVF
//purpose  : 
//=======================================================================
class BOPDS_InterfVF  : public BOPDS_Interf {
 public:
  //
  /**
   *  Constructor
   */
  BOPDS_InterfVF()
    : BOPDS_Interf(),
      myU(0.),
      myV(0.) {
  };
  //
  /**
   *  Constructor
   * @param theAllocator
   *   allocator to manage the memory
   */
  BOPDS_InterfVF(const Handle(NCollection_BaseAllocator)& theAllocator)
    : BOPDS_Interf(theAllocator),
      myU(0.),
      myV(0.) {
  };
  //
  /**
   *  Destructor
   */  
  virtual ~BOPDS_InterfVF() {
  };
  //
  /**
   * Modifier
   * Sets the value of parameters 
   * of the point of the vertex 
   * on the surface of of the face
   * @param theU
   *   value of U parameter
   * @param theV 
   *   value of U parameter 
   */
  void SetUV(const Standard_Real theU,
	     const Standard_Real theV) {
    myU=theU;
    myV=theV;
  };
  //
  /**
   * Selector
   * Returns the value of parameters 
   * of the point of the vertex 
   * on the surface of of the face
   * @param theU
   *   value of U parameter
   * @param theV 
   *   value of U parameter 
   */
  void UV(Standard_Real& theU,Standard_Real& theV) const {
    theU=myU;
    theV=myV;
  };
  
 protected:
  Standard_Real myU;
  Standard_Real myV;
      
};
/**
 * The class BOPDS_InterfEE is is to store the information about
 * the interference of the type edge/edge. 
*/
//=======================================================================
//function : BOPDS_InterfEE
//purpose  : 
//=======================================================================
class BOPDS_InterfEE  : public BOPDS_Interf {
 public:
  //
  /**
   *  Constructor
   */
  BOPDS_InterfEE() : BOPDS_Interf() {
  };
  //
  /**
   *  Constructor
   * @param theAllocator
   *   allocator to manage the memory
   */
  BOPDS_InterfEE(const Handle(NCollection_BaseAllocator)& theAllocator)
    : BOPDS_Interf(theAllocator) {
  };
  //
  /**
   *  Destructor
   */
  virtual ~BOPDS_InterfEE() {
  };
  //
  /**
   *  Modifier
   * Sets the info of common part 
   * @param theCP
   *   common part
   */
  void SetCommonPart(const IntTools_CommonPrt& theCP) {
    myCommonPart=theCP;
  };
  //
  /**
   *  Selector
   * Returns the info of common part 
   * @return
   *   common part
   */
  const IntTools_CommonPrt& CommonPart() const {
    return myCommonPart;
  };
  
 protected:
  IntTools_CommonPrt myCommonPart;
};
/**
 * The class BOPDS_InterfEF is is to store the information about
 * the interference of the type edge/face. 
*/
//=======================================================================
//function : BOPDS_InterfEF
//purpose  : 
//=======================================================================
class BOPDS_InterfEF  : public BOPDS_Interf {
 public:
  //
  /**
   *  Constructor
   */
  BOPDS_InterfEF(): BOPDS_Interf() {
  };
  //
  /**
   *  Constructor
   * @param theAllocator
   *   allocator to manage the memory
   */
  /**
   *  Constructor
   * @param theAllocator
   *   allocator to manage the memory
   */
  BOPDS_InterfEF(const Handle(NCollection_BaseAllocator)& theAllocator)
    : BOPDS_Interf(theAllocator) {
  };
  //
  /**
   *  Destructor
   */
  virtual ~BOPDS_InterfEF() {
  };
  //
  /**
   * Modifier
   * Sets the info of common part 
   * @param theCP
   *   common part
   */
  void SetCommonPart(const IntTools_CommonPrt& theCP){
    myCommonPart=theCP;
  };
  //
  /**
   *  Selector
   * Returns the info of common part 
   * @return
   *   common part
   */
  const IntTools_CommonPrt& CommonPart() const {
    return myCommonPart;
  };
  //
 protected:
  IntTools_CommonPrt myCommonPart;
}
/**
 * The class BOPDS_InterfFF is is to store the information about
 * the interference of the type face/face. 
*/;
//=======================================================================
//function : BOPDS_InterfFF
//purpose  : 
//=======================================================================
class BOPDS_InterfFF  : public BOPDS_Interf {
 public:
  //
  /**
   *  Constructor
   */
  BOPDS_InterfFF()
    : 
      BOPDS_Interf(),
      myTolR3D(1.e-7),
      myTolR2D(1.e-7),
      myCurves(myAllocator),
      myPoints(myAllocator) {
  };
  //
  /**
   *  Constructor
   * @param theAllocator
   *   allocator to manage the memory
   */
  /**
  BOPDS_InterfFF(const Handle(NCollection_BaseAllocator)& theAllocator)
    : 
      BOPDS_Interf(theAllocator),
      myTolR3D(1.e-7),
      myTolR2D(1.e-7),
      myCurves(myAllocator),
      myPoints(myAllocator) {
  };
  */
  //
  /**
   *  Destructor
   */
  virtual ~BOPDS_InterfFF() {
  };
  //
  /**
   * Initializer
   * @param theNbCurves
   *   number of intersection curves
   * @param theNbPoints
   *   number of intersection points
   */
  void Init(const Standard_Integer theNbCurves,
            const Standard_Integer theNbPoints) {
    if (theNbCurves>0) {
      myCurves.SetStartSize(theNbCurves);
      myCurves.SetIncrement(theNbCurves);
      myCurves.Init();
    }
    if (theNbPoints>0) {
      myPoints.SetStartSize(theNbPoints);
      myPoints.SetIncrement(theNbPoints);
      myPoints.Init();
    }
  }
  //
  /**
   * Modifier
   * Sets the value of 3D tolerance  
   * @param theTol
   *   3D tolerance
   */
  void SetTolR3D(const Standard_Real theTol) {
     myTolR3D=theTol;
  }
  //
  /**
   * Selector
   * Returns the value of 3D tolerance  
   * @return
   *   3D tolerance
   */
  Standard_Real TolR3D()const {
    return myTolR3D;
  }
  //
  /**
   * Modifier
   * Sets the value of 2D tolerance  
   * @param theTol
   *   2D tolerance
   */
  void SetTolR2D(const Standard_Real theTol) {
     myTolR2D=theTol;;
  }
  //
  /**
   * Selector 
   * Returns the value of 2D tolerance  
   * @return
   *   2D tolerance
   */
  Standard_Real TolR2D()const {
    return myTolR2D;
  }
  //
  /**
   * Selector
   * Returns the intersection curves  
   * @return
   *   intersection curves 
   */
  const BOPDS_VectorOfCurve& Curves()const{
    return myCurves;
  };
  //
  /**
   * Selector/Modifier
   * Returns the intersection curves  
   * @return
   *   intersection curves 
   */
  BOPDS_VectorOfCurve& ChangeCurves(){
    return myCurves;
  };
  //
  /**
   * Selector
   * Returns the intersection points  
   * @return
   *   intersection points
   */
  const BOPDS_VectorOfPoint& Points()const{
    return myPoints;
  };
  //
  /**
   * Selector/Modifier
   * Returns the intersection points  
   * @return
   *   intersection points
   */
  BOPDS_VectorOfPoint& ChangePoints(){
    return myPoints;
  };
  //
 protected:
  Standard_Real myTolR3D;
  Standard_Real myTolR2D;
  BOPDS_VectorOfCurve myCurves;
  BOPDS_VectorOfPoint myPoints;
};

#endif
