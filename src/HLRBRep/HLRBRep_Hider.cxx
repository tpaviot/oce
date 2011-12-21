// File:	HLRBRep_Hider.cxx
// Created:	Thu Apr 17 19:33:55 1997
// Author:	Christophe MARION
//		<cma@partox.paris1.matra-dtv.fr>

#define No_Standard_OutOfRange

#include <HLRBRep_Hider.ixx>

#include <HLRAlgo_Coincidence.hxx>
#include <HLRAlgo_Interference.hxx>
#include <HLRAlgo_InterferenceList.hxx>
#include <HLRAlgo_ListIteratorOfInterferenceList.hxx>
#include <HLRAlgo_Intersection.hxx>
#include <HLRBRep_EdgeIList.hxx>
#include <HLRBRep_EdgeBuilder.hxx>
#include <HLRBRep_VertexList.hxx>
#include <HLRBRep_EdgeInterferenceTool.hxx>
#include <Standard_ErrorHandler.hxx>

//=======================================================================
//function : HLRBRep_Hider
//purpose  : 
//=======================================================================

HLRBRep_Hider::
HLRBRep_Hider (const Handle(HLRBRep_Data)& DS) :
  myDS(DS) 
{}

//=======================================================================
//function : OwnHiding
//purpose  : 
//=======================================================================

void HLRBRep_Hider::OwnHiding(const Standard_Integer)
{
}

//=======================================================================
//function : Hide
//purpose  : 
//=======================================================================

void HLRBRep_Hider::Hide(const Standard_Integer FI,
			 BRepTopAdaptor_MapOfShapeTool& MST)
{
  // *****************************************************************
  //
  // This algorithm hides a set of edges stored in the data structure <myDS>
  // with the hiding face number FI in <myDS>.
  //
  // Outline of the algorithm
  //
  //   1. Loop on the Edges (not hidden and not rejected by the face minmax)
  //   
  //       The rejections depending of the face are 
  //          - Edge above the face
  //          - Edge belonging to the face
  //          - Edge rejected by a wire minmax
  //
  //       Compute interferences with the not rejected edges of the face.
  //           Store IN and ON interferences in two sorted lists
  //               ILHidden and ILOn
  //       If ILOn is not empty
  //           Resolve ComplexTransitions in ILOn
  //           Resolve ON Intersections in ILOn
  //             An On interference may become
  //               IN  : Move it from ILOn to ILHidden
  //               OUT : Remove it from ILOn
  //       If ILHidden and ILOn are empty
  //           intersect the edge with the face and classify the Edge.
  //               - if inside and under the face hide it.
  //       Else
  //         If ILHidden is not empty
  //           Resolve ComplexTransitions in ILHidden
  //           Build Hidden parts of the edge
  //               - Hide them
  //           Build visible parts of the edge
  //           Build Parts of the edge under the boundary of the face
  //               - Hide them as Boundary
  //         If ILOn is not empty
  //           Build ON parts of the edge
  //               - Hide them as ON parts
  //           Build Parts of the edge on the boundary of the face
  //               - Hide them as ON parts on Boundary
  // 
  //
  // *****************************************************************

  myDS->InitEdge(FI,MST);
  if (!myDS->MoreEdge())                        // there is nothing to do
     return;                                    // **********************
  HLRBRep_EdgeInterferenceTool EIT(myDS); // List of Intersections
  HLRBRep_Array1OfEData& myEData = myDS->EDataArray();

#ifdef DEB
  Standard_Integer EToBeChecked = -1;
#endif
  for (; myDS->MoreEdge(); myDS->NextEdge()) {       // loop on the Edges
    Standard_Integer E = myDS->Edge();               // *****************

#ifdef DEB
    if(E == EToBeChecked) {
      cout << E << endl;
    }
#endif

    try {
      OCC_CATCH_SIGNALS
      Standard_Boolean hasOut = Standard_False;
      HLRAlgo_InterferenceList ILHidden;
      HLRAlgo_InterferenceList ILOn;
      EIT.LoadEdge();
      
      for (myDS->InitInterference();     // intersections with face-edges
	   myDS->MoreInterference();     // *****************************
	   myDS->NextInterference()) {
	if (myDS->RejectedInterference()) {
	  if (myDS->AboveInterference() &&
	      myDS->SimpleHidingFace ()) { 
	    hasOut = Standard_True;
	  }
	}
	else {
	  HLRAlgo_Interference& Int = myDS->Interference();
	  switch (Int.Intersection().State()) {
	  case TopAbs_IN      :
	    HLRBRep_EdgeIList::AddInterference(ILHidden,Int,EIT); break;
	  case TopAbs_ON      :
	    HLRBRep_EdgeIList::AddInterference(ILOn    ,Int,EIT); break;
	  case TopAbs_OUT     : 
	  case TopAbs_UNKNOWN :                                   break;
	  }
	}
      }
      
      //-- ============================================================
      Standard_Boolean Modif;
      do { 
	Modif = Standard_False; 
	HLRAlgo_ListIteratorOfInterferenceList ItSegHidden1(ILHidden);
	while(ItSegHidden1.More() && Modif==Standard_False) { 
	  HLRAlgo_Interference& Int1 = ItSegHidden1.Value();
	  Standard_Integer numseg1=Int1.Intersection().SegIndex();
	  if(numseg1!=0) { 
	    HLRAlgo_ListIteratorOfInterferenceList ItSegHidden2(ILHidden);
	    while(ItSegHidden2.More()  && Modif==Standard_False) {
	      HLRAlgo_Interference& Int2 = ItSegHidden2.Value();
	      Standard_Integer numseg2=Int2.Intersection().SegIndex();
	      if(numseg1+numseg2 == 0) { 
		//--printf("\nHidden Traitement du segment %d  %d\n",numseg1,numseg2); fflush(stdout);
		TopAbs_State stbef1,staft1,stbef2,staft2;
		Int1.Boundary().State3D(stbef1,staft1);  
		Int2.Boundary().State3D(stbef2,staft2);
		if(Int1.Orientation() == Int2.Orientation()) {
		  if(Int1.Transition() == Int2.Transition()) {
		    if(stbef1==stbef2 && staft1==staft2 && stbef1!=TopAbs_ON && staft1!=TopAbs_ON ) { 
		      //-- printf("\n Index1 = %d  Index2 = %d\n",Int1.Intersection().Index(),Int2.Intersection().Index());
		      Standard_Integer nind=-1;
		      if(Int1.Intersection().Index()!=0) { 
			nind=Int1.Intersection().Index();
		      }
		      if(Int2.Intersection().Index()!=0) {
			if(nind!=-1) {
			  if(Int1.Intersection().Index() != Int2.Intersection().Index()) { 
			    nind=-1;
			  }
			}
			else { 
			  nind=Int2.Intersection().Index();
			}
		      }
		      if(Int1.Intersection().Index()==0 && Int2.Intersection().Index()==0) nind=0;
		     
		      if(nind!=-1) { 
			//-- printf("\n Segment Supprime\n"); fflush(stdout);
			HLRAlgo_Intersection& inter = Int1.ChangeIntersection();
			inter.SegIndex(nind);
			Standard_Real p1 = Int1.Intersection().Parameter();
			Standard_Real p2 = Int2.Intersection().Parameter();
			inter.Parameter((p1+p2)*0.5);
			Int1.BoundaryTransition(TopAbs_EXTERNAL);

			ILHidden.Remove(ItSegHidden2);
			Modif=Standard_True;
		      }
		    }
		  }
		}
	      }
	      if(Modif==Standard_False) { 
		ItSegHidden2.Next();
	      }
	    }
	  }
	  if(Modif==Standard_False) { 
	    ItSegHidden1.Next();
	  }
	}
      }
      while(Modif);
	

      //-- ============================================================


      if (!ILOn.IsEmpty()) {         // process the interferences on ILOn
	                             // *********************************
      
	HLRBRep_EdgeIList::ProcessComplex   // complex transition on ILOn
	  (ILOn,EIT);                       // **************************

	HLRAlgo_ListIteratorOfInterferenceList It(ILOn); 
	
	while(It.More()) {           // process Intersections on the Face
                                     // *********************************
	  
	  HLRAlgo_Interference& Int = It.Value();
	  TopAbs_State stbef, staft;                // read the 3d states
	  Int.Boundary().State3D(stbef,staft);      // ******************

	  switch (Int.Transition()) {
	  case TopAbs_FORWARD  :
	    switch (staft) {
	    case TopAbs_OUT     :
	      ILOn.Remove(It);                            break;
	    case TopAbs_IN      :
	      HLRBRep_EdgeIList::AddInterference(ILHidden,Int,EIT);
	      ILOn.Remove(It);                            break;
	    case TopAbs_UNKNOWN : cout << "UNKNOWN state staft" << endl;
	    case TopAbs_ON      :
	      It.Next();                                  break;
	    }                                             break;
	  case TopAbs_REVERSED :
	    switch (stbef) {
	    case TopAbs_OUT     :
	      ILOn.Remove(It);                            break;
	    case TopAbs_IN      :
	      HLRBRep_EdgeIList::AddInterference(ILHidden,Int,EIT);
	      ILOn.Remove(It);                            break;
	    case TopAbs_UNKNOWN : cout << "UNKNOWN state stbef" << endl;
	    case TopAbs_ON      :
	      It.Next();                                  break;
	    }                                             break;
	  case TopAbs_EXTERNAL :
	    ILOn.Remove(It);                              break;
	  case TopAbs_INTERNAL :
	    switch (stbef) {
	    case TopAbs_IN        :
	      switch (staft) {
	      case TopAbs_IN      :
		HLRBRep_EdgeIList::AddInterference(ILHidden,Int,EIT);
		ILOn.Remove(It);                          break;
	      case TopAbs_ON      :
		Int.Transition(TopAbs_FORWARD );      // FORWARD  in ILOn,
		HLRBRep_EdgeIList::AddInterference    // REVERSED in ILHidden
		  (ILHidden,HLRAlgo_Interference   
		   (Int.Intersection(),
		    Int.Boundary(),
		    Int.Orientation(),
		    TopAbs_REVERSED,
		    Int.BoundaryTransition()),EIT);
		It.Next();                                break;
	      case TopAbs_OUT     :
		Int.Transition(TopAbs_REVERSED);      // set REVERSED
		HLRBRep_EdgeIList::AddInterference(ILHidden,Int,EIT);
		ILOn.Remove(It);                          break;
	      case TopAbs_UNKNOWN :
		cout << "UNKNOWN state after" << endl;
		It.Next();                                break;
	      }                                           break;
	    case TopAbs_ON :
	      switch (staft) {
	      case TopAbs_IN      :
		Int.Transition(TopAbs_REVERSED);      // REVERSED in ILOn,
		HLRBRep_EdgeIList::AddInterference    // REVERSED in ILHidden
		  (ILHidden,HLRAlgo_Interference   
		   (Int.Intersection(),
		    Int.Boundary(),
		    Int.Orientation(),
		    TopAbs_FORWARD,
		    Int.BoundaryTransition()),EIT);       break;
	      case TopAbs_ON      :                       break;
	      case TopAbs_OUT     :
		Int.Transition(TopAbs_REVERSED);          break;
	      case TopAbs_UNKNOWN :
		cout << "UNKNOWN state after" << endl;    break;
	      }	    
	      It.Next();                                  break;
	    case TopAbs_OUT :
	      switch (staft) {
	      case TopAbs_IN      :
		Int.Transition(TopAbs_FORWARD);       // set FORWARD
		HLRBRep_EdgeIList::AddInterference(ILHidden,Int,EIT);
		ILOn.Remove(It);                          break;
	      case TopAbs_ON      :
		Int.Transition(TopAbs_FORWARD );      // FORWARD  in ILOn
		It.Next();                                break;
	      case TopAbs_OUT     :
		ILOn.Remove(It);                          break;
	      case TopAbs_UNKNOWN :
		cout << "UNKNOWN state after" << endl;
		It.Next();                                break;
	      }                                           break;
	    case TopAbs_UNKNOWN :
	      cout << "UNKNOWN state stbef" << endl;      break;
	    }
	  }
	}
      }
      
      if (ILHidden.IsEmpty() && ILOn.IsEmpty() && !hasOut) {
	HLRBRep_EdgeData& ed = myEData(E);
	TopAbs_State st = myDS->Compare(E,ed);              // Classification
	if (st == TopAbs_IN || st == TopAbs_ON)             // **************
	  ed.Status().HideAll();
      }
      else {
	Standard_Real p1 = 0.,p2 = 0.;
	Standard_ShortReal tol1 = 0., tol2 = 0.;

	HLRBRep_EdgeData& ed = myEData(E);
	HLRAlgo_EdgeStatus& ES = ed.Status();

	Standard_Boolean foundHidden = Standard_False;
	
	if (!ILHidden.IsEmpty()) {    

	  HLRBRep_EdgeIList::ProcessComplex // complex transition on ILHidden
	    (ILHidden,EIT);                 // ******************************
	  Standard_Integer level = 0;
	  if (!myDS->SimpleHidingFace())                    // Level at Start
	    level = myDS->HidingStartLevel(E,ed,ILHidden);  // **************
	  	  HLRAlgo_ListIteratorOfInterferenceList It(ILHidden); 
	  
	  while(It.More()) {           // suppress multi-inside Intersections
	                               // ***********************************
	  
	    HLRAlgo_Interference& Int = It.Value();
	    switch (Int.Transition()) {
	      
	    case TopAbs_FORWARD  :
	      {
		Standard_Integer decal = Int.Intersection().Level();
		if (level > 0) ILHidden.Remove(It);
		else           It.Next();
		level = level + decal;
	      }
	      break;
	    case TopAbs_REVERSED : 
	      { 
		level = level - Int.Intersection().Level();
		if (level > 0) ILHidden.Remove(It);
		else           It.Next();
	      }
	      break;
	    case TopAbs_EXTERNAL :
	      It.Next();
	      break;
	    case TopAbs_INTERNAL :
	      It.Next();
	      break;
	    default :
	      It.Next();
	      break;
	    }
	  }
	  if (ILHidden.IsEmpty())                             // Edge hidden
	    ES.HideAll();                                     // ***********
	  else
	    foundHidden = Standard_True;
	}


	if (!ILHidden.IsEmpty()) {
	  //IFV

	  TopAbs_State aBuildIN = TopAbs_IN;
	  Standard_Boolean IsSuspision = Standard_True;
	  
	  Standard_Real pmax, pmin;
	  Standard_Boolean allInt = Standard_False;
	  Standard_Boolean allFor = Standard_False;
	  Standard_Boolean allRev = Standard_False;
	  pmin = RealLast();
	  pmax = -pmin;

	  if(ILHidden.Extent() > 1 ) {
	    allInt = Standard_True;
	    allFor = Standard_True;
	    allRev = Standard_True;
	    HLRAlgo_ListIteratorOfInterferenceList It(ILHidden);
	    for(;It.More(); It.Next()) {
	      Standard_Real p = It.Value().Intersection().Parameter();
	      allFor = allFor && ( It.Value().Transition() == TopAbs_FORWARD);
	      allRev = allRev && ( It.Value().Transition() == TopAbs_REVERSED);
	      allInt = allInt && ( It.Value().Transition() == TopAbs_INTERNAL);
	      if(p < pmin) pmin = p;
	      if(p > pmax) pmax = p;
	    }

	  }
	  
	  HLRAlgo_ListIteratorOfInterferenceList Itl(ILHidden);
	  HLRBRep_VertexList IL(EIT,Itl);


	  HLRBRep_EdgeBuilder EB(IL);
	  
	  EB.Builds(aBuildIN);                         // build hidden parts
	                                               // ******************
	  while (EB.MoreEdges()) {
	    while (EB.MoreVertices()) {
	      switch (EB.Orientation()) {
	      case TopAbs_FORWARD  : 
		p1   =  EB.Current().Parameter(); 
		tol1 =  EB.Current().Tolerance();
		break;
	      case TopAbs_REVERSED :
		p2   =  EB.Current().Parameter(); 
		tol2 =  EB.Current().Tolerance();
		break;
	      case TopAbs_INTERNAL :
	      case TopAbs_EXTERNAL :
		break;
	      }
	      EB.NextVertex();
	    }

	    if(Abs(p1 - p2) <= 1.e-7) {
	      EB.NextEdge();
	      continue;
	    }

	    if(allInt) {
	      if(p1 < pmin) p1 = pmin;
	      if(p2 > pmax) p2 = pmax;
	      //HLRBRep_EdgeData& ed = myEData(E);
	      //TopAbs_State st = myDS->Compare(E,ed);              // Classification
	    }
	    
	    TopAbs_State aTestState = TopAbs_IN;
	    if(IsSuspision) {
	      Standard_Integer aNbp = 1;
	      aTestState = myDS->SimplClassify(E, ed, aNbp, p1, p2);
	    }

	    if(aTestState != TopAbs_OUT) {
	      ES.Hide(p1,tol1,p2,tol2,
		      Standard_False,   // under  the Face
		      Standard_False);  // inside the Face
	    }
	    
	    EB.NextEdge();
	  }
	  
	  EB.Builds(TopAbs_ON);             // build parts under the boundary
	                                    // ******************************
	  while (EB.MoreEdges()) {
	    while (EB.MoreVertices()) {
	      switch (EB.Orientation()) {
	      case TopAbs_FORWARD  :
		p1   = EB.Current().Parameter(); 
		tol1 = EB.Current().Tolerance();
		break;
	      case TopAbs_REVERSED :
		p2   = EB.Current().Parameter(); 
		tol2 = EB.Current().Tolerance();
		break;
	      case TopAbs_INTERNAL :
	      case TopAbs_EXTERNAL :
		break;
	      }
	      EB.NextVertex();
	    }
	    ES.Hide(p1,tol1,p2,tol2,
		    Standard_False,   // under the Face
		    Standard_True);   // on the boundary
	    EB.NextEdge();
	  }
	}      
	
	if (!ILOn.IsEmpty()) {
	  Standard_Integer level = 0;
	  if (!myDS->SimpleHidingFace())                    // Level at Start
	    level = myDS->HidingStartLevel(E,ed,ILOn);      // **************
	  if (level > 0) {
	    HLRAlgo_ListIteratorOfInterferenceList It(ILOn); 
	    
	    while(It.More()) {         // suppress multi-inside Intersections
	                               // ***********************************
	      
	      HLRAlgo_Interference& Int = It.Value();
	      switch (Int.Transition()) {
		
	      case TopAbs_FORWARD  :
		{
		  Standard_Integer decal = Int.Intersection().Level();
		  if (level > 0) ILOn.Remove(It);
		  else           It.Next();
		  level = level + decal;
		}
		break;
	      case TopAbs_REVERSED :
		level = level - Int.Intersection().Level();
		if (level > 0) ILOn.Remove(It);
		else           It.Next();
		break;
	      case TopAbs_EXTERNAL :
	      case TopAbs_INTERNAL :
		default :
		It.Next();
		break;
	      }
	    }
	    if (ILOn.IsEmpty() && !foundHidden)               // Edge hidden
	      ES.HideAll();                                   // ***********
	  }
	}
	
	if (!ILOn.IsEmpty()) {
	  HLRBRep_VertexList IL(EIT,ILOn);
	  HLRBRep_EdgeBuilder EB(IL);
	  
	  EB.Builds (TopAbs_IN);                   // build parts on the Face
                                                   // ***********************
	  while (EB.MoreEdges()) {
	    while (EB.MoreVertices()) {
	      switch (EB.Orientation()) {
	      case TopAbs_FORWARD  : 
		p1   = EB.Current().Parameter(); 
		tol1 = EB.Current().Tolerance();
		break;
	      case TopAbs_REVERSED :
		p2   = EB.Current().Parameter(); 
		tol2 = EB.Current().Tolerance();
		break;
	      case TopAbs_INTERNAL :
	      case TopAbs_EXTERNAL :   
		break;
	      }
	      EB.NextVertex();
	    }
	    ES.Hide(p1,tol1,p2,tol2,
		    Standard_True,    // on     the Face
		    Standard_False);  // inside the Face
	    EB.NextEdge();
	  }
	  
	  EB.Builds(TopAbs_ON);      // build hidden parts under the boundary
                                     // *************************************
	  while (EB.MoreEdges()) {
	    while (EB.MoreVertices()) {
	      switch (EB.Orientation()) {
	      case TopAbs_FORWARD  :
		p1   = EB.Current().Parameter(); 
		tol1 = EB.Current().Tolerance();
		break;
	      case TopAbs_REVERSED :
		p2   = EB.Current().Parameter(); 
		tol2 = EB.Current().Tolerance();
		break;
	      case TopAbs_INTERNAL :
	      case TopAbs_EXTERNAL :
		break;
	      }
	      EB.NextVertex();
	    }
	    ES.Hide(p1,tol1,p2,tol2,
		    Standard_True,    // on the Face
		    Standard_True);   // on the boundary
	    EB.NextEdge();
	  }
	}
      }

    }

    catch(Standard_Failure) {
#ifdef DEB
      cout << "An exception was catched when hiding edge " << E;
      cout << " by the face " << FI << endl;
      Handle(Standard_Failure) fail = Standard_Failure::Caught();
      cout << fail << endl;
#endif
    }
  }
}

