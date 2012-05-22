// Created on: 1996-07-15
// Created by: Laurent BUCHARD
// Copyright (c) 1996-1999 Matra Datavision
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



//  Modified by skv - Thu Sep  4 11:22:05 2003 OCC578

#include <BRepClass3d_SClassifier.ixx>

#include <gp_Pnt.hxx>
#include <gp_Lin.hxx>
#include <gp_Vec.hxx>
#include <BRepClass3d_Intersector3d.hxx>
#include <TopoDS.hxx>

#include <IntCurvesFace_Intersector.hxx>
// modified by NIZHNY-MKK  Mon Jun 21 15:13:40 2004
#include <Precision.hxx>
#include <ElCLib.hxx>
#include <Geom_Surface.hxx>
#include <BRep_Tool.hxx>

static
  void FaceNormal (const TopoDS_Face& aF,
		   const Standard_Real U,
		   const Standard_Real V,
		   gp_Dir& aDN);

static 
  Standard_Real GetAddToParam(const gp_Lin& L,const Standard_Real P,const Bnd_Box& B);



//=======================================================================
//function : BRepClass3d_SClassifier
//purpose  : 
//=======================================================================
BRepClass3d_SClassifier::BRepClass3d_SClassifier() 
{ 
}


//=======================================================================
//function : BRepClass3d_SClassifier
//purpose  : 
//=======================================================================
BRepClass3d_SClassifier::BRepClass3d_SClassifier(BRepClass3d_SolidExplorer& S,
						 const gp_Pnt&  P,
						 const Standard_Real Tol) { 
  if(S.Reject(P)) { 
    myState=3; //-- in ds solid case without face 
  }
  else { 
    Perform(S,P,Tol);
  }
}


//=======================================================================
//function : PerformInfinitePoint
//purpose  : 
//=======================================================================
void BRepClass3d_SClassifier::PerformInfinitePoint(BRepClass3d_SolidExplorer& aSE,
						   const Standard_Real /*Tol*/) {
  //-- Idea : Take point A in face1 and point B in face B 
  //-- (if there is only one face, take 2 points in the same face.)
  //-- 
  //-- Intersect straight line AB with the solid and produce transition of the 
  //-- first point. If the solid has only one face and the straight line AB does not cut it 
  //-- it is not possible to decide.

  if(aSE.Reject(gp_Pnt(0,0,0))) { 
    myState=3; //-- in ds solid case without face 
    return;
  }
  //
  //------------------------------------------------------------
  // 1
  Standard_Boolean bFound, bFlag;
  Standard_Integer nump;
  Standard_Real aParam, aU1, aV1, aU2, aV2;
  gp_Pnt A,B;
  gp_Dir aDN1, aDN2;
  TopoDS_Face aF1, aF2;
  //
  nump = 0;
  aParam = 0.5;
  myFace.Nullify();
  myState=2; 
  for(aSE.InitShell(); aSE.MoreShell() && nump<2;  aSE.NextShell()) { 
    for(aSE.InitFace();	aSE.MoreFace()  && nump<2; ) {
      TopoDS_Face aF = aSE.CurrentFace();
      aSE.NextFace();
      if(!nump) { 
	nump++;
	bFound=aSE.FindAPointInTheFace(aF, A, aU1, aV1, aParam);
	if (!bFound) {
	  return;
	}
	aF1=aF;
	if(!aSE.MoreFace()) { 
	  nump++;
	  bFound=aSE.FindAPointInTheFace(aF, B, aU2, aV2, aParam);
	  if (!bFound) {
	    return;
	  }
	  aF2=aF;
	}
      }// if(nump==0) {    
      else if(nump==1) { 
	bFound=aSE.FindAPointInTheFace(aF, B, aU2, aV2, aParam);
	if(!bFound) { 
	  return;
	} 
	aF2=aF;
	nump++;
      }
    }// for(aSE.InitFace();	aSE.MoreFace()  && nump<2; ) {
  }// for(aSE.InitShell(); aSE.MoreShell() && nump<2;  aSE.NextShell()) { 
  //
  //------------------------------------------------------------
  // 2
  Standard_Integer cpasbon;
  Standard_Real parmin, aD2, aSP;
  IntCurveSurface_TransitionOnCurve aTC;    
  TopAbs_State aState;
  //
  parmin = RealLast();
  //
  bFlag=Standard_False;
  if (aF1!=aF2) {
    FaceNormal(aF1, aU1, aV1, aDN1);
    FaceNormal(aF2, aU2, aV2, aDN2);
    aSP=1.-aDN1*aDN2;
    if (aSP < 1.e-5) {
      bFlag=!bFlag;
    }
  }
  //
  aD2=A.SquareDistance(B);
  if(aD2<0.000001 || bFlag) { 
    B.SetCoord(A.X()+1,A.Y()+1,A.Z()+1);
  }
  //
  cpasbon = 0;
  gp_Vec AB(A,B);
  //
  do { 
    switch (cpasbon) 
      {
      case 1 : AB.SetX(-AB.X());break;
      case 2 : AB.SetY(-AB.Y());break;
      case 3 : AB.SetZ(-AB.Z());break;
      case 4 : AB.SetY(-AB.Y());break;
      case 5 : AB.SetX(-AB.X());break;
      }
    gp_Lin L(A,gp_Dir(AB));    
    //-- cout<<"\npoint A "<<A.X()<<" "<<A.Y()<<" "<<A.Z()<<endl;
    //-- cout<<"\npoint B "<<B.X()<<" "<<B.Y()<<" "<<B.Z()<<endl;
    for(aSE.InitShell();aSE.MoreShell();aSE.NextShell()) { 
      if(aSE.RejectShell(L) == Standard_False) { 
	for(aSE.InitFace();aSE.MoreFace(); aSE.NextFace()) {
	  if(aSE.RejectFace(L) == Standard_False) { 
	    TopoDS_Shape aLocalShape = aSE.CurrentFace();
	    TopoDS_Face f = TopoDS::Face(aLocalShape);
	    IntCurvesFace_Intersector& Intersector3d = aSE.Intersector(f);
	    Intersector3d.Perform(L,-RealLast(),parmin); 

	    if(Intersector3d.IsDone()) { 
	      if(Intersector3d.NbPnt()) { 
		if(Intersector3d.WParameter(1) < parmin) {
		  aState=Intersector3d.State(1);
		  parmin = Intersector3d.WParameter(1);
		  if(aState==TopAbs_IN || aState==TopAbs_ON) { 
		    aTC=Intersector3d.Transition(1);
		    //-- The intersection point between the line and a face F 
		    // -- of the solid is in the face F 
		    if(aTC == IntCurveSurface_Out) { 
		      //-- The line is going from inside the solid to outside 
		      //-- the solid.
		      myState = 3; //-- IN --
		    }
		    else if(aTC == IntCurveSurface_In) { 
		      myState = 4; //-- OUT --
		    }
		    myFace  = f;
		  }
		  /*
		  else if(Intersector3d.State(1)==TopAbs_ON)  {
		    //-- The intersection point between the line and a face F 
		    //-- of the solid is in the face F 
		    if(Intersector3d.Transition(1) == IntCurveSurface_Out) { 
		      //-- The line is going from inside the solid to outside 
		      //-- the solid.
		      myState = 3; //-- IN --
		    }
		    else if(Intersector3d.Transition(1) == IntCurveSurface_In) { 
		      myState = 4; //-- OUT --
		    }
		    //-- myState = 2;
		    myFace  = f;
		  }
		  */
		}
		
		else { 
		  //-- No point has been found by the Intersector3d.
		  //-- Or a Point has been found with a greater parameter.
		}
	      }
	    }
	  }
	} //-- Exploration of the faces
      } //-- Shell has not been rejected
      else { 
	myState=1; 
      }
    } //-- Exploration of the shells
    cpasbon++;
  }
  while(cpasbon!=0 && cpasbon<5);
}
//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================
void BRepClass3d_SClassifier::Perform(BRepClass3d_SolidExplorer& SolidExplorer,
				      const gp_Pnt&  P,
				      const Standard_Real Tol) 
{ 


  if(SolidExplorer.Reject(P)) { 
    myState=3; //-- in ds solid case without face 
    return;
  }


  myFace.Nullify();
  myState = 0;
  if(SolidExplorer.Reject(P) == Standard_False) { 
    gp_Lin L;
    Standard_Real Par;
    //-- We compute the intersection betwwen the line builded in the Solid Explorer
    //-- and the shape.

    //-- --------------------------------------------------------------------------------
    //-- Calculate intersection with the face closest to the direction of bounding boxes 
    //-- by priority so that to have the smallest possible parmin. 
    //-- optimization to produce as much as possible rejections with other faces. 
    Standard_Integer iFlag;
    //

    //  Modified by skv - Thu Sep  4 11:22:05 2003 OCC578 Begin
    //  If found line passes through a bound of any face, it means that the line
    //  is not found properly and it is necessary to repeat whole procedure.
    //  That's why the main loop while is added.
    Standard_Boolean isFaultyLine = Standard_True;
    Standard_Integer anIndFace    = 0;
    Standard_Real    parmin;

    while (isFaultyLine) {
      if (anIndFace == 0) {
	iFlag = SolidExplorer.Segment(P,L,Par);
      } else {
	iFlag = SolidExplorer.OtherSegment(P,L,Par);
      }

      Standard_Integer aCurInd = SolidExplorer.GetFaceSegmentIndex();

      if (aCurInd > anIndFace) {
	anIndFace = aCurInd;
      } else {
	myState = 1;

	return;
      }
      //  Modified by skv - Thu Sep  4 11:22:10 2003 OCC578 End

      if (iFlag==1) {
	// IsOnFace
	// iFlag==1 i.e face is Infinite
	myState=2; 

	return;
      }
      //SolidExplorer.Segment(P,L,Par);
      //
      //process results from uncorrected shells
      //
      //if(Par > 1.e+100 && L.Direction().IsParallel(gp_Dir(0.,0.,1.),1.e-8)) {
      if (iFlag==2) {
	myState = 4;
	return;
      }
      //-- BRepClass3d_Intersector3d Intersector3d;
    
      //  Modified by skv - Thu Sep  4 13:48:27 2003 OCC578 Begin
      // Check if the point is ON surface but OUT of the face. 
      // Just skip this face because it is bad for classification.
      if (iFlag == 3)
	continue;

      isFaultyLine = Standard_False;
//       Standard_Real parmin = RealLast();

//       for(SolidExplorer.InitShell();
// 	  SolidExplorer.MoreShell();
// 	  SolidExplorer.NextShell()) { 
      parmin = RealLast();

      for(SolidExplorer.InitShell();
	  SolidExplorer.MoreShell() && !isFaultyLine;
	  SolidExplorer.NextShell()) { 
//  Modified by skv - Thu Sep  4 13:48:27 2003 OCC578 End

	if(SolidExplorer.RejectShell(L) == Standard_False) { 

//  Modified by skv - Thu Sep  4 13:48:27 2003 OCC578 Begin
// 	  for(SolidExplorer.InitFace(); 
// 	      SolidExplorer.MoreFace(); 
// 	      SolidExplorer.NextFace()) {
	  for(SolidExplorer.InitFace(); 
	      SolidExplorer.MoreFace() && !isFaultyLine; 
	      SolidExplorer.NextFace()) {
//  Modified by skv - Thu Sep  4 13:48:27 2003 OCC578 End
	  
	    if(SolidExplorer.RejectFace(L) == Standard_False) { 
	    
	      //-- Intersector3d.Perform(L,Par,Tol,SolidExplorer.CurrentFace());
	      TopoDS_Shape aLocalShape = SolidExplorer.CurrentFace();
	      TopoDS_Face f = TopoDS::Face(aLocalShape);
	      //	    TopoDS_Face f = TopoDS::Face(SolidExplorer.CurrentFace());
	      IntCurvesFace_Intersector& Intersector3d = SolidExplorer.Intersector(f);

	      // MSV Oct 25, 2001: prolong segment, since there are cases when
	      // the intersector does not find intersection points with the original
	      // segment due to rough triangulation of a parametrized surface
	      Standard_Real addW = Max(10*Tol, 0.01*Par);
              Standard_Real AddW = addW;

	      Bnd_Box aBoxF = Intersector3d.Bounding();

              // MSV 23.09.2004: the box must be finite in order to
              // correctly prolong the segment to its bounds
              if (!aBoxF.IsVoid() && !aBoxF.IsWhole()) {
                Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
                aBoxF.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

                Standard_Real boxaddW = GetAddToParam(L,Par,aBoxF);
                addW = Max(addW,boxaddW);
              }

	      Standard_Real minW = -AddW;//-addW;
	      Standard_Real maxW = Min(Par*10,Par+addW);//Par+addW;
              //cout << "range [" << minW << "," << maxW << "]" << endl << endl;
	      Intersector3d.Perform(L,minW,maxW);
	      //Intersector3d.Perform(L,-Tol,Par+10.0*Tol);
	      if(Intersector3d.IsDone()) { 
		Standard_Integer i;
		for (i=1; i <= Intersector3d.NbPnt(); i++) { 
		  if(Abs(Intersector3d.WParameter(i)) < Abs(parmin)) {
 
		    parmin = Intersector3d.WParameter(i);
		    //  Modified by skv - Thu Sep  4 12:46:32 2003 OCC578 Begin
		    TopAbs_State aState = Intersector3d.State(i);
		    //  Modified by skv - Thu Sep  4 12:46:33 2003 OCC578 End
		    if(Abs(parmin)<=Tol) { 
		      myState = 2;
		      myFace  = f;
		    }
		    //  Modified by skv - Thu Sep  4 12:46:32 2003 OCC578 Begin
		    //  Treatment of case TopAbs_ON separately.

		    else if(aState==TopAbs_IN) { 
		    //  Modified by skv - Thu Sep  4 12:46:32 2003 OCC578 End

		      //-- The intersection point between the line and a face F 
		      // -- of the solid is in the face F 

		      IntCurveSurface_TransitionOnCurve tran = Intersector3d.Transition(i);
		      if (tran == IntCurveSurface_Tangent) {
#ifdef DEB
			cout<<"*Problem ds BRepClass3d_SClassifier.cxx"<<endl;
#endif
			continue; // ignore this point
		      }
		      // if parmin is negative we should reverse transition
		      if (parmin < 0)
			tran = (tran == IntCurveSurface_Out 
				? IntCurveSurface_In : IntCurveSurface_Out);
		      if(tran == IntCurveSurface_Out) { 
			//-- The line is going from inside the solid to outside 
			//-- the solid.
			myState = 3; //-- IN --
		      }
		      else /* if(tran == IntCurveSurface_In) */ { 
			myState = 4; //-- OUT --
		      }
		      myFace  = f;
		    }
		    //  Modified by skv - Thu Sep  4 12:48:50 2003 OCC578 Begin
		    // If the state is TopAbs_ON, it is necessary to chose
		    // another line and to repeat the whole procedure.
		    else if(aState==TopAbs_ON) {
		      isFaultyLine = Standard_True;

		      break;
		    }
		    //  Modified by skv - Thu Sep  4 12:48:50 2003 OCC578 End
		  }
		  else { 
		    //-- No point has been found by the Intersector3d.
		    //-- Or a Point has been found with a greater parameter.
		  }
		} //-- loop by intersection points
	      } //-- Face has not been rejected
	      else { 
		myState = 1;
	      }
	    }
	  } //-- Exploration of the faces
	} //-- Shell has not been rejected
	else { 
	  myState=1; 
	}
      } //-- Exploration of the shells

      //  Modified by skv - Thu Sep  4 11:42:03 2003 OCC578 Begin
      // The end of main loop.
    }
    //  Modified by skv - Thu Sep  4 11:42:03 2003 OCC578 End

#ifdef DEB
    //#################################################
    SolidExplorer.DumpSegment(P,L,parmin,State());
    //#################################################
#endif

  } //-- Solid has not been rejected
  else { 
    myState = 1;
  }
}


TopAbs_State BRepClass3d_SClassifier::State() const { 
  if(myState==2)  return(TopAbs_ON);
  if(myState==4)        return(TopAbs_OUT);          //--
  else if(myState==3)   return(TopAbs_IN);           //-- 
  return(TopAbs_OUT);             
}

TopoDS_Face BRepClass3d_SClassifier::Face() const {  
  return(myFace);
}

Standard_Boolean BRepClass3d_SClassifier::Rejected() const { 
  return(myState==1); 
}

  
Standard_Boolean BRepClass3d_SClassifier::IsOnAFace() const { 
  return(myState==2);
}


void BRepClass3d_SClassifier::ForceIn() {
  myState=3;
}

void BRepClass3d_SClassifier::ForceOut() { 
  myState=4;
}

Standard_Real GetAddToParam(const gp_Lin&       L,
                            const Standard_Real P,
                            const Bnd_Box&      B)
{
  Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  B.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
  Standard_Real x[2] = {aXmin,aXmax}, y[2] = {aYmin,aYmax}, z[2] = {aZmin,aZmax};
  Standard_Integer i = 0, j = 0, k = 0;
  Standard_Real Par = P;
  for(i = 0 ; i < 2; i++) {
    for(j = 0; j < 2; j++) {
      for(k = 0; k < 2; k++) {
        Standard_Real X = fabs(x[i]-L.Location().X());
        Standard_Real Y = fabs(y[j]-L.Location().Y());
        Standard_Real Z = fabs(z[k]-L.Location().Z());
        if(X < 1.e+20 && Y < 1.e+20 && Z < 1.e+20) {
          gp_Pnt aP(x[i],y[j],z[k]);
          Standard_Real par = ElCLib::Parameter(L,aP);
          if(par > Par)
            Par = par;
        }
        else
          return 1.e+20;
      }
    }
  }
  return Par - P;
}
//=======================================================================
//function : FaceNormal
//purpose  : 
//=======================================================================
void FaceNormal (const TopoDS_Face& aF,
		 const Standard_Real U,
		 const Standard_Real V,
		 gp_Dir& aDN)
{
  gp_Pnt aPnt ;
  gp_Vec aD1U, aD1V, aN;
  Handle(Geom_Surface) aS;

  aS=BRep_Tool::Surface(aF);
  aS->D1 (U, V, aPnt, aD1U, aD1V);
  aN=aD1U.Crossed(aD1V);
  aN.Normalize();  
  aDN.SetXYZ(aN.XYZ());
  if (aF.Orientation() == TopAbs_REVERSED){
    aDN.Reverse();
  }
  return;
}
