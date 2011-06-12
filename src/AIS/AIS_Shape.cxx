// File:	AIS_Shape.cxx
// Created:	Fri Dec 20 17:18:37 1996
// Author:	Robert COUBLANC
//		<rob@robox.paris1.matra-dtv.fr>
// Modified:    Christiane ARMAND: 5/05/97: dans le compute on prend en 
//              compte le cas des objets infinis     
//              ROB : introduction des primitives connectees
//                    Pour le calcul des faces sensibles...
//   oct-03-97  ROB : en fonction du type de shapes, on change les coeffs de polygonisation...
//                    (correction du Pb des cercles pas assez discretises...)

#define BUC60577	//GG_191099 Draw correct bounding box and Menage ...

#define BUC60547        //GG_091299 Enable to show a Shape of type COMPOUND

#define GER61351	//GG_171199     Enable to set an object RGB color
//	  	instead a restricted object NameOfColor. 
//	    	Redefines the Color(),Material(),Transparency() methods .
//	     	enable to get separately the shape attributes.

#define IMP040200	//GG Enable to compute selection after transformation

#define BUC60918	//GG 31/05/01 To avoid transparency bug between 
//			transparent and non transparent objects, 
//			increase display priority for transparent objects

#include <AIS_Shape.ixx>


#include <Standard_ErrorHandler.hxx>
#include <OSD_Timer.hxx>
#include <TColStd_ListIteratorOfListOfInteger.hxx>

#include <Quantity_Color.hxx>

#include <gp_Pnt.hxx>
#include <Bnd_Box.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools_ShapeSet.hxx>
#include <BRepTools.hxx>
#include <BRepBndLib.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>

#include <Aspect_TypeOfLine.hxx>
#include <Graphic3d_Structure.hxx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <Graphic3d_AspectMarker3d.hxx>
#include <Graphic3d_AspectFillArea3d.hxx>
#include <Graphic3d_Array1OfVertex.hxx>
#include <Graphic3d_ArrayOfPrimitives.hxx>
#include <Graphic3d_MaterialAspect.hxx>

#include <Prs3d_Presentation.hxx>
#include <Prs3d_Root.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_IsoAspect.hxx>

//#include <StdPrs_WFSectionShape.hxx>
#include <StdPrs_WFShape.hxx>
#include <StdPrs_WFDeflectionShape.hxx>
#include <StdPrs_ShadedShape.hxx>
#include <StdPrs_HLRShape.hxx>
#include <StdPrs_HLRPolyShape.hxx>

#include <PrsMgr_ModedPresentation.hxx>

#include <Select3D_SensitiveEntity.hxx>
#include <StdSelect.hxx>
#include <StdSelect_BRepSelectionTool.hxx>
#include <StdSelect_BRepOwner.hxx>
#include <StdSelect_DisplayMode.hxx>

#include <AIS_GraphicTool.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Drawer.hxx>
#include <HLRBRep.hxx>
#include <Precision.hxx>

#include <Standard_Failure.hxx>
#include <Standard_ErrorHandler.hxx>
#include <Select3D_SensitiveBox.hxx>
#ifdef BUC60547
#include <TopoDS_Iterator.hxx>
#endif

static Standard_Boolean myFirstCompute;

Standard_Real AIS_Shape::GetDeflection(const TopoDS_Shape& aShape,
				   const Handle(Prs3d_Drawer)& aDrawer)
{
  // WARNING: this same piece of code appears several times in Prs3d classes
  Standard_Real aDeflection;
  if (aDrawer->TypeOfDeflection() == Aspect_TOD_RELATIVE) {
    Bnd_Box B;
    BRepBndLib::Add(aShape, B);
    if ( ! B.IsVoid() )
    {
      Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
      B.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
      aDeflection = Max( aXmax-aXmin, Max(aYmax-aYmin, aZmax-aZmin)) *
                    aDrawer->DeviationCoefficient() * 4;
    }
    else
      aDeflection = aDrawer->MaximalChordialDeviation();
  }
  else
    aDeflection = aDrawer->MaximalChordialDeviation();
  return aDeflection;
}

void AIS_Shape::DisplayBox(const Handle(Prs3d_Presentation)& aPrs,
		       const Bnd_Box& B,
		       const Handle(Prs3d_Drawer)& aDrawer)
{
  Standard_Real X[2],Y[2],Z[2];
  Standard_Integer Indx [16] ;
  if ( B.IsVoid() )
    return; // nothing to show

#ifdef BUC60577
  Indx [0]=1;Indx [1]=2;Indx [2]=4;Indx [3]=3;
  Indx [4]=5;Indx [5]=6;Indx [6]=8;Indx [7]=7;
  Indx [8]=1;Indx [9]=3;Indx [10]=7;Indx [11]=5;
  Indx [12]=2;Indx [13]=4;Indx [14]=8;Indx [15]=6;
  B.Get(X[0], Y[0], Z[0], X[1], Y[1], Z[1]);
#else
  Indx [0]=1;Indx [1]=2;Indx [2]=3;Indx [3]=4;Indx [4]=5;Indx [5]=6;Indx [6]=7;
  Indx [7]=8;Indx [8]=1;Indx [9]=2;Indx [10]=6;Indx [10]=5;Indx [10]=3;
  Indx [10]=4;Indx [10]=8;Indx [10]=7;
  B.Get(X[1], Y[1], Z[1], X[2], Y[2], Z[2]);
#endif

  Graphic3d_Array1OfVertex V(1,8);
  Standard_Integer Rank(0);
  for(Standard_Integer k=0;k<=1;k++)
    for(Standard_Integer j=0;j<=1;j++)
      for(Standard_Integer i=0;i<=1;i++)
	V(++Rank) = Graphic3d_Vertex(X[i],Y[j],Z[k]);
  
  
  Handle(Graphic3d_Group) G = Prs3d_Root::CurrentGroup(aPrs);
  Quantity_Color Q;
  Aspect_TypeOfLine A;
  Standard_Real W;
  aDrawer->LineAspect()->Aspect()->Values(Q,A,W);
  

  G->SetGroupPrimitivesAspect(new Graphic3d_AspectLine3d(Q,Aspect_TOL_DOTDASH,W));
  
  G->BeginPrimitives();Standard_Integer I,J;
  Graphic3d_Array1OfVertex VVV (1,5);
  for(I=1;I<=4;I++){
    for(J=1;J<=4;J++){
      VVV.SetValue(J,V(Indx[J+4*I-5]));
    }
    VVV.SetValue(5,VVV(1));
    G->Polyline(VVV);
  }
  G->EndPrimitives();
}
		     
static Standard_Boolean IsInList(const TColStd_ListOfInteger& LL, const Standard_Integer aMode)
{
  TColStd_ListIteratorOfListOfInteger It(LL);
  for(;It.More();It.Next()){
    if(It.Value()==aMode) 
      return Standard_True;}
  return Standard_False;
}

//==================================================
// Function: 
// Purpose :
//==================================================

AIS_Shape::
AIS_Shape(const TopoDS_Shape& shap):
AIS_InteractiveObject(PrsMgr_TOP_ProjectorDependant),
myshape(shap),
myCompBB(Standard_True),
myInitAng(0.)
{
  myFirstCompute = Standard_True;
  SetHilightMode(0);
  myDrawer->SetShadingAspectGlobal(Standard_False);
}

//=======================================================================
//function : Type
//purpose  : 
//=======================================================================
AIS_KindOfInteractive AIS_Shape::Type() const 
{return AIS_KOI_Shape;}


//=======================================================================
//function : Signature
//purpose  : 
//=======================================================================
Standard_Integer AIS_Shape::Signature() const 
{return 0;}

//=======================================================================
//function : AcceptShapeDecomposition
//purpose  : 
//=======================================================================
Standard_Boolean AIS_Shape::AcceptShapeDecomposition() const 
{return Standard_True;}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================
void AIS_Shape::Compute(const Handle(PrsMgr_PresentationManager3d)& /*aPresentationManager*/,
			const Handle(Prs3d_Presentation)& aPrs,
			const Standard_Integer aMode)
{  
  aPrs->Clear();
  if(myshape.IsNull()) return;

  // wire,edge,vertex -> pas de HLR + priorite display superieure
  Standard_Integer TheType = (Standard_Integer) myshape.ShapeType();
  if(TheType>4 && TheType<8) {
    aPrs->SetVisual(Graphic3d_TOS_ALL);
    aPrs->SetDisplayPriority(TheType+2);
  }
  // Shape vide -> Assemblage vide.
  if (myshape.ShapeType() == TopAbs_COMPOUND) {
#ifdef BUC60547
    TopoDS_Iterator anExplor (myshape);
#else
    TopExp_Explorer anExplor (myshape, TopAbs_VERTEX);
#endif
    if (!anExplor.More()) {
      return;
    }
  }
  
  
  if (IsInfinite()) aPrs->SetInfiniteState(Standard_True); //pas de prise en compte lors du FITALL
  switch (aMode) {
  case 0:{
    try { OCC_CATCH_SIGNALS  StdPrs_WFDeflectionShape::Add(aPrs,myshape,myDrawer); }
    catch (Standard_Failure) { 
#ifdef DEB
      cout << "AIS_Shape::Compute()  failed"<< endl;
#endif
      cout << "a Shape should be incorrect : No Compute can be maked on it  "<< endl;     
// on calcule une presentation de la boite englobante
//      Compute(aPresentationManager,aPrs,2);
    }
    break;
  }
  case 1:
    {
      Standard_Real prevangle ;
      Standard_Real newangle  ; 
      Standard_Real prevcoeff = 0;
      Standard_Real newcoeff = 0 ; 
      
      
      if (OwnDeviationAngle(newangle,prevangle) ||
	  OwnDeviationCoefficient(newcoeff,prevcoeff))
	if (Abs (newangle - prevangle) > Precision::Angular() ||
	    Abs (newcoeff - prevcoeff) > Precision::Confusion()  ) { 
#ifdef DEB
	  cout << "AIS_Shape : compute"<<endl;
	  cout << "newangl   : " << newangle << " # de " << "prevangl  : " << prevangle << " OU "<<endl;
	  cout << "newcoeff  : " << newcoeff << " # de " << "prevcoeff : " << prevcoeff << endl;
#endif
	  BRepTools::Clean(myshape);
	}
      
      //shading seulement a partir de face...
      if ((Standard_Integer) myshape.ShapeType()>4)
	StdPrs_WFDeflectionShape::Add(aPrs,myshape,myDrawer);
      else {
	myDrawer->SetShadingAspectGlobal(Standard_False);
	if (IsInfinite()) StdPrs_WFDeflectionShape::Add(aPrs,myshape,myDrawer);
	else 	{
	  {
	    try {
	      OCC_CATCH_SIGNALS
	      StdPrs_ShadedShape::Add(aPrs,myshape,myDrawer);
	    }
	    catch (Standard_Failure) {
#ifdef DEB
	      cout << "AIS_Shape::Compute() in ShadingMode failed"<< endl;
#endif
	      StdPrs_WFShape::Add(aPrs,myshape,myDrawer);
	    }
	  }
	}
      }
#ifdef BUC60918
      Standard_Real value = Transparency() ;
      if( value > 0. ) {
	SetTransparency( value );
      }
#endif
      break;
    }
  case 2:
    {
      // boite englobante
      if (IsInfinite()) StdPrs_WFDeflectionShape::Add(aPrs,myshape,myDrawer);
      else DisplayBox(aPrs,BoundingBox(),myDrawer);
    }


  } // end switch
  aPrs->ReCompute(); // for hidden line recomputation if necessary...
  
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void AIS_Shape::Compute(const Handle(PrsMgr_PresentationManager2d)& /*aPresentationManager*/,
			const Handle(Graphic2d_GraphicObject)& /*aGRO*/,
			const Standard_Integer /*aMode*/)
{
}

//=======================================================================
//function : Compute
//purpose  : Hidden Line Removal
//=======================================================================
void AIS_Shape::Compute(const Handle(Prs3d_Projector)& aProjector,
			const Handle(Prs3d_Presentation)& aPresentation)
{
  Compute(aProjector,aPresentation,myshape);
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void AIS_Shape::Compute(const Handle(Prs3d_Projector)&     aProjector,
			const Handle(Geom_Transformation)& TheTrsf,
			const Handle(Prs3d_Presentation)&  aPresentation)
{
  const TopLoc_Location& loc = myshape.Location();
  TopoDS_Shape shbis = myshape.Located(TopLoc_Location(TheTrsf->Trsf())*loc);
  Compute(aProjector,aPresentation,shbis);
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void AIS_Shape::Compute(const Handle(Prs3d_Projector)& aProjector,
			const Handle(Prs3d_Presentation)& aPresentation,
			const TopoDS_Shape& SH)
{
  if (SH.ShapeType() == TopAbs_COMPOUND) {
#ifdef BUC60547
    TopoDS_Iterator anExplor (SH);
#else
    TopExp_Explorer anExplor (SH, TopAbs_VERTEX);
#endif
    if (!anExplor.More()) // Shape vide -> Assemblage vide.
      return;
  }
  
  Handle (Prs3d_Drawer) defdrawer = GetContext()->DefaultDrawer();
  if (defdrawer->DrawHiddenLine()) 
    {myDrawer->EnableDrawHiddenLine();}
  else {myDrawer->DisableDrawHiddenLine();}
  
  Aspect_TypeOfDeflection prevdef = defdrawer->TypeOfDeflection();
  defdrawer->SetTypeOfDeflection(Aspect_TOD_RELATIVE);

// coefficients pour le calcul

  Standard_Real prevangle, newangle ,prevcoeff = 0,newcoeff = 0; 
  if (OwnHLRDeviationAngle(newangle,prevangle) || OwnHLRDeviationCoefficient(newcoeff, prevcoeff))
      
    if (Abs (newangle - prevangle) > Precision::Angular() ||
	Abs (newcoeff - prevcoeff) > Precision::Confusion()  ) { 
#ifdef DEB
      cout << "AIS_Shape : compute"<<endl;
      cout << "newangle  : " << newangle << " # de " << "prevangl  : " << prevangle << " OU "<<endl;
      cout << "newcoeff  : " << newcoeff << " # de " << "prevcoeff : " << prevcoeff << endl;
#endif
      BRepTools::Clean(SH);
    }
  
  {
    try {
      OCC_CATCH_SIGNALS
      StdPrs_HLRPolyShape::Add(aPresentation,SH,myDrawer,aProjector);
    }
    catch (Standard_Failure) {
#ifdef DEB
      cout <<"AIS_Shape::Compute(Proj) HLR Algorithm failed" << endl;
#endif
      StdPrs_WFShape::Add(aPresentation,SH,myDrawer);
    }
  }

  
  defdrawer->SetTypeOfDeflection (prevdef);
}

//=======================================================================
//function : SelectionType
//purpose  : gives the type according to the Index of Selection Mode
//=======================================================================

TopAbs_ShapeEnum AIS_Shape::SelectionType(const Standard_Integer aMode)
{
  switch(aMode){
  case 1:
    return TopAbs_VERTEX;
  case 2:
    return TopAbs_EDGE;
  case 3:
    return TopAbs_WIRE;
  case 4:
    return TopAbs_FACE;
  case 5:
    return TopAbs_SHELL;
  case 6:
    return TopAbs_SOLID;
  case 7:
    return TopAbs_COMPSOLID;
  case 8:
    return TopAbs_COMPOUND;
  case 0:
  default:
    return TopAbs_SHAPE;
  }
  
}
//=======================================================================
//function : SelectionType
//purpose  : gives the SelectionMode according to the Type od Decomposition...
//=======================================================================
Standard_Integer AIS_Shape::SelectionMode(const TopAbs_ShapeEnum aType)
{
  switch(aType){
  case TopAbs_VERTEX:
    return 1;
  case TopAbs_EDGE:
    return 2;
  case TopAbs_WIRE:
    return 3;
  case  TopAbs_FACE:
    return 4;
  case TopAbs_SHELL:
    return 5;
  case TopAbs_SOLID:
    return 6;
  case TopAbs_COMPSOLID:
    return 7;
  case TopAbs_COMPOUND:
    return 8;
  case TopAbs_SHAPE:
  default:
    return 0;
  }
}


//=======================================================================
//function : ComputeSelection
//purpose  : 
//=======================================================================

void AIS_Shape::ComputeSelection(const Handle(SelectMgr_Selection)& aSelection,
		 const Standard_Integer aMode)
{
  if(myshape.IsNull()) return;
  if (myshape.ShapeType() == TopAbs_COMPOUND) {
#ifdef BUC60547
    TopoDS_Iterator anExplor (myshape);
#else
    TopExp_Explorer anExplor (myshape, TopAbs_VERTEX);
#endif
    if (!anExplor.More()) // Shape vide -> Assemblage vide.
      return;
  }

  static TopAbs_ShapeEnum TypOfSel;
  TypOfSel = AIS_Shape::SelectionType(aMode);
  TopoDS_Shape shape = myshape;
#ifdef IMP040200
  if( HasTransformation() ) {
    Handle(Geom_Transformation) trsf = Transformation();
    shape = shape.Located(TopLoc_Location(trsf->Trsf())*shape.Location());
  }
#endif

// POP on protege contre un plantage dans les couches basses

  Standard_Real aDeflection = myDrawer->MaximalChordialDeviation();
  if (myDrawer->TypeOfDeflection() == Aspect_TOD_RELATIVE)
  {
    // On calcule la fleche en fonction des min max globaux de la piece:
    Bnd_Box aBndBox; //= BoundingBox(); ?
    BRepBndLib::Add (shape, aBndBox);
    if (!aBndBox.IsVoid())
    {
      Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
      aBndBox.Get (aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
      aDeflection = Max (aXmax - aXmin, Max (aYmax - aYmin, aZmax - aZmin)) * myDrawer->DeviationCoefficient();
    }
  }

  Standard_Boolean autoTriangulation = Standard_True;
  try {  
    OCC_CATCH_SIGNALS
    StdSelect_BRepSelectionTool::Load(aSelection,
                                      this,
                                      shape,
                                      TypOfSel,
                                      aDeflection,
                                      myDrawer->DeviationAngle(),
                                      autoTriangulation); 
  } catch ( Standard_Failure ) {
//    cout << "a Shape should be incorrect : A Selection on the Bnd  is activated   "<<endl;
    if ( aMode == 0 ) {
      Bnd_Box B = BoundingBox();
      Handle(StdSelect_BRepOwner) aOwner = new StdSelect_BRepOwner(shape,this);
      Handle(Select3D_SensitiveBox) aSensitiveBox = new Select3D_SensitiveBox(aOwner,B);
      aSelection->Add(aSensitiveBox);
    }
  }

  // insert the drawer in the BrepOwners for hilight...
  StdSelect::SetDrawerForBRepOwner(aSelection,myDrawer);
}

#ifdef GER61351
Quantity_NameOfColor AIS_Shape::Color() const {
Quantity_Color aColor;
  Color(aColor);
  return aColor.Name();
}

void AIS_Shape::Color( Quantity_Color& aColor ) const {
  aColor = myDrawer->ShadingAspect()->Color(myCurrentFacingModel);
}

Graphic3d_NameOfMaterial AIS_Shape::Material() const {
  return (myDrawer->ShadingAspect()->Material(myCurrentFacingModel)).Name();
}

Standard_Real AIS_Shape::Transparency() const {
  return myDrawer->ShadingAspect()->Transparency(myCurrentFacingModel);
}
#endif

//=======================================================================
//function : SetColor
//purpose  : 
//=======================================================================

void AIS_Shape::SetColor(const Quantity_NameOfColor aCol)
#ifdef GER61351
{
  SetColor(Quantity_Color(aCol));
}

void AIS_Shape::SetColor(const Quantity_Color &aCol)
#endif
{
  hasOwnColor = Standard_True;
#ifdef GER61351
  if( !HasColor() && !IsTransparent() && !HasMaterial() ) {
	myDrawer->SetShadingAspect(new Prs3d_ShadingAspect());
  }
#else
  myOwnColor  = aCol; 
  if(!myDrawer->HasShadingAspect()){
    Handle(Prs3d_ShadingAspect) asp = new Prs3d_ShadingAspect();
// recuperons le materiau reference...
    if(myDrawer->HasLink()){
      const Handle(Prs3d_Drawer)& refdr = myDrawer->Link();
      Graphic3d_MaterialAspect theRefMat = 
	refdr->ShadingAspect()->Aspect()->FrontMaterial();
      theRefMat.SetTransparency(myTransparency);
      asp->SetMaterial(theRefMat);
    }   
    
    myDrawer->SetShadingAspect(asp);
  } 
#endif

#ifdef GER61351
  myDrawer->ShadingAspect()->SetColor(aCol,myCurrentFacingModel);
#else
  myDrawer->ShadingAspect()->SetColor(aCol);
#endif
  myDrawer->SetShadingAspectGlobal(Standard_False);
    
  Standard_Real WW = HasWidth()? Width():AIS_GraphicTool::GetLineWidth(myDrawer->Link(),AIS_TOA_Line);

  myDrawer->SetLineAspect(new Prs3d_LineAspect(aCol,Aspect_TOL_SOLID,WW));
  myDrawer->SetWireAspect(new Prs3d_LineAspect(aCol,Aspect_TOL_SOLID,WW));
  myDrawer->SetFreeBoundaryAspect(new Prs3d_LineAspect(aCol,Aspect_TOL_SOLID,WW));
  myDrawer->SetUnFreeBoundaryAspect(new Prs3d_LineAspect(aCol,Aspect_TOL_SOLID,WW));
  myDrawer->SetSeenLineAspect(new Prs3d_LineAspect(aCol,Aspect_TOL_SOLID,WW));

  // modif du shading rapide...
  if(!GetContext().IsNull()){
    if( GetContext()->MainPrsMgr()->HasPresentation(this,1)){
      Handle(Prs3d_Presentation) P = GetContext()->MainPrsMgr()->CastPresentation(this,1)->Presentation();
      Handle(Graphic3d_Group) G = Prs3d_Root::CurrentGroup(P);
      Handle(Graphic3d_AspectFillArea3d) a4bis = myDrawer->ShadingAspect()->Aspect();
#ifdef BUC60577
      P->SetPrimitivesAspect(a4bis);
      G->SetGroupPrimitivesAspect(a4bis);
#else
      a4bis->SetInteriorColor(Quantity_Color(aCol)); // Already done above in SetColor(...)	

//***test rob : pour avoir la vraie couleur demandee en shading ***
// mais du coup, le shading est "plat" ...****
//      Graphic3d_MaterialAspect FMAT = a4bis->FrontMaterial();
//      FMAT.SetColor(Quantity_Color(aCol));
//      a4bis->SetFrontMaterial(FMAT);
//******

      P->SetPrimitivesAspect(myDrawer->ShadingAspect()->Aspect());
      G->SetGroupPrimitivesAspect(myDrawer->ShadingAspect()->Aspect());
#endif
    }  
  }

  LoadRecomputable(0);
  LoadRecomputable(2); 
}
//=======================================================================
//function : UnsetColor
//purpose  : 
//=======================================================================

void AIS_Shape::UnsetColor()
{
  // Evitons les stupidites...
  if(!HasColor() ){  myToRecomputeModes.Clear();
		     return;}
  
  hasOwnColor = Standard_False;

  Handle(Prs3d_LineAspect) NullAsp;
  Handle(Prs3d_ShadingAspect) NullShA;
  
  if(!HasWidth()){
    myDrawer->SetLineAspect(NullAsp);
    myDrawer->SetWireAspect(NullAsp);
    myDrawer->SetFreeBoundaryAspect(NullAsp);
    myDrawer->SetUnFreeBoundaryAspect(NullAsp);
    myDrawer->SetSeenLineAspect(NullAsp);
  }
  else{
#ifdef GER61351
    Quantity_Color CC;
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Line,CC);
    myDrawer->LineAspect()->SetColor(CC);
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Wire,CC);
    myDrawer->WireAspect()->SetColor(CC);
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Free,CC);
    myDrawer->FreeBoundaryAspect()->SetColor(CC);
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_UnFree,CC);
    myDrawer->UnFreeBoundaryAspect()->SetColor(CC);
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Seen,CC);
    myDrawer->SeenLineAspect()->SetColor(CC);
#else
    myDrawer->LineAspect()->SetColor(AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Line));
    myDrawer->WireAspect()->SetColor(AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Wire));
    myDrawer->FreeBoundaryAspect()->SetColor(AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Free));
    myDrawer->UnFreeBoundaryAspect()->SetColor(AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_UnFree));
    myDrawer->SeenLineAspect()->SetColor(AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Seen));
#endif
  }
  
  if(myDrawer->HasShadingAspect()){
    myDrawer->SetShadingAspect(NullShA);
  }    
  
  if(!GetContext().IsNull()){
    if(GetContext()->MainPrsMgr()->HasPresentation(this,1)){
      Handle(Prs3d_Presentation) P = GetContext()->MainPrsMgr()->CastPresentation(this,1)->Presentation();
      Handle(Graphic3d_Group) G = Prs3d_Root::CurrentGroup(P);
      
      Handle(Graphic3d_AspectFillArea3d) a4bis = myDrawer->Link()->ShadingAspect()->Aspect();
#ifdef GER61351
      Quantity_Color CC;
      AIS_GraphicTool::GetInteriorColor(myDrawer->Link(),CC);
      a4bis->SetInteriorColor(CC);
#else
      Quantity_NameOfColor KOL = AIS_GraphicTool::GetInteriorColor(myDrawer->Link());
      a4bis->SetInteriorColor(Quantity_Color(KOL));
#endif
      P->SetPrimitivesAspect(a4bis);
      G->SetGroupPrimitivesAspect(a4bis);
    }
}
  LoadRecomputable(0);
  LoadRecomputable(2);
  
}


//=======================================================================
//function : SetWidth
//purpose  : 
//=======================================================================

void AIS_Shape::SetWidth(const Standard_Real W)
{
  if(HasColor() || HasWidth()){ 
    myDrawer->LineAspect()->SetWidth(W);
    myDrawer->WireAspect()->SetWidth(W);
    myDrawer->FreeBoundaryAspect()->SetWidth(W);
    myDrawer->UnFreeBoundaryAspect()->SetWidth(W);
    myDrawer->SeenLineAspect()->SetWidth(W);
  }
  else{
#ifdef GER61351
    Quantity_Color CC;
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Line,CC);
    myDrawer->SetLineAspect(new Prs3d_LineAspect(CC,Aspect_TOL_SOLID,W));
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Wire,CC);
    myDrawer->SetWireAspect(new Prs3d_LineAspect(CC,Aspect_TOL_SOLID,W));
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Free,CC);
    myDrawer->SetFreeBoundaryAspect(new Prs3d_LineAspect(CC,Aspect_TOL_SOLID,W));
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_UnFree,CC);
    myDrawer->SetUnFreeBoundaryAspect(new Prs3d_LineAspect(CC,Aspect_TOL_SOLID,W));
    AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Seen,CC);
    myDrawer->SetSeenLineAspect(new Prs3d_LineAspect(CC,Aspect_TOL_SOLID,W));
#else
    Quantity_NameOfColor KOL = AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Line);
    myDrawer->SetLineAspect(new Prs3d_LineAspect(KOL,Aspect_TOL_SOLID,W));

    KOL = AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Wire);
    myDrawer->SetWireAspect(new Prs3d_LineAspect(KOL,Aspect_TOL_SOLID,W));

    KOL = AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Free);
    myDrawer->SetFreeBoundaryAspect(new Prs3d_LineAspect(KOL,Aspect_TOL_SOLID,W));

    KOL = AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_UnFree);
    myDrawer->SetUnFreeBoundaryAspect(new Prs3d_LineAspect(KOL,Aspect_TOL_SOLID,W));

    KOL = AIS_GraphicTool::GetLineColor(myDrawer->Link(),AIS_TOA_Seen);
    myDrawer->SetSeenLineAspect(new Prs3d_LineAspect(KOL,Aspect_TOL_SOLID,W));
#endif    
  }
  myOwnWidth = W;
  LoadRecomputable(0); // signifier qu'il faut recalculer uniquement le wireframe....
  LoadRecomputable(2); // et la boite englobante...
  
}

//=======================================================================
//function : UnsetWidth
//purpose  : 
//=======================================================================

void AIS_Shape::UnsetWidth()
{
  if(myOwnWidth== 0.0){  myToRecomputeModes.Clear();
		      return;}
  myOwnWidth=0.0;
  Handle(Prs3d_LineAspect) NullAsp;
  
  if(!HasColor()){
    myDrawer->SetLineAspect(NullAsp);
    myDrawer->SetWireAspect(NullAsp);
    myDrawer->SetFreeBoundaryAspect(NullAsp);
    myDrawer->SetUnFreeBoundaryAspect(NullAsp);
    myDrawer->SetSeenLineAspect(NullAsp);
  }
  else{
    myDrawer->LineAspect()->SetWidth(AIS_GraphicTool::GetLineWidth(myDrawer->Link(),AIS_TOA_Line));
    myDrawer->WireAspect()->SetWidth(AIS_GraphicTool::GetLineWidth(myDrawer->Link(),AIS_TOA_Wire));
    myDrawer->FreeBoundaryAspect()->SetWidth(AIS_GraphicTool::GetLineWidth(myDrawer->Link(),AIS_TOA_Free));
    myDrawer->UnFreeBoundaryAspect()->SetWidth(AIS_GraphicTool::GetLineWidth(myDrawer->Link(),AIS_TOA_UnFree));
    myDrawer->SeenLineAspect()->SetWidth(AIS_GraphicTool::GetLineWidth(myDrawer->Link(),AIS_TOA_Seen));
  }
  LoadRecomputable(0);
}


//=======================================================================
//function : SetMaterial
//purpose  : 
//=======================================================================
void AIS_Shape::SetMaterial(const Graphic3d_NameOfMaterial aMat)
{
#ifdef GER61351
  if( !HasColor() && !IsTransparent() && !HasMaterial() ) {
	myDrawer->SetShadingAspect(new Prs3d_ShadingAspect());
  }
  myDrawer->ShadingAspect()->SetMaterial(aMat,myCurrentFacingModel);
  hasOwnMaterial = Standard_True;
#else
  AIS_InteractiveObject::SetMaterial(aMat);
#endif
  if(!GetContext().IsNull()){
    if(GetContext()->MainPrsMgr()->HasPresentation(this,1)){
      Handle(Prs3d_Presentation) P = GetContext()->MainPrsMgr()->CastPresentation(this,1)->Presentation();
      Handle(Graphic3d_Group) G = Prs3d_Root::CurrentGroup(P);
      
      Handle(Graphic3d_AspectFillArea3d) a4bis = myDrawer->ShadingAspect()->Aspect();
      P->SetPrimitivesAspect(a4bis);
      G->SetGroupPrimitivesAspect(a4bis);
    }
  }
  myRecomputeEveryPrs =Standard_False; // aucun mode a recalculer :uniquement update viewer
  myToRecomputeModes.Clear();  
}
//=======================================================================
//function : SetMaterial
//purpose  : 
//=======================================================================
void AIS_Shape::SetMaterial(const Graphic3d_MaterialAspect& aMat)
{
#ifdef GER61351
  if( !HasColor() && !IsTransparent() && !HasMaterial() ) {
	myDrawer->SetShadingAspect(new Prs3d_ShadingAspect());
  }
  myDrawer->ShadingAspect()->SetMaterial(aMat,myCurrentFacingModel);
  hasOwnMaterial = Standard_True;
#else
  AIS_InteractiveObject::SetMaterial(aMat);
#endif  
  if(!GetContext().IsNull()){
  if(GetContext()->MainPrsMgr()->HasPresentation(this,1)){
    Handle(Prs3d_Presentation) P = GetContext()->MainPrsMgr()->CastPresentation(this,1)->Presentation();
    Handle(Graphic3d_Group) G = Prs3d_Root::CurrentGroup(P);
    
    Handle(Graphic3d_AspectFillArea3d) a4bis = myDrawer->ShadingAspect()->Aspect();
    P->SetPrimitivesAspect(a4bis);
    G->SetGroupPrimitivesAspect(a4bis);
  }
}
  myRecomputeEveryPrs =Standard_False; // aucun mode a recalculer :uniquement update viewer
  myToRecomputeModes.Clear();  
}

//=======================================================================
//function : UnsetMaterial
//purpose  : 
//=======================================================================
void AIS_Shape::UnsetMaterial()
{
#ifdef GER61351
  if( !HasMaterial() ) return;
  if( HasColor() || IsTransparent()) {
    Graphic3d_MaterialAspect mat = AIS_GraphicTool::GetMaterial(myDrawer->Link()); 
    if( HasColor() ) {
	Quantity_Color color = myDrawer->ShadingAspect()->Color(myCurrentFacingModel);
      mat.SetColor(color);
    }
    if( IsTransparent() ) {
	Standard_Real trans = myDrawer->ShadingAspect()->Transparency(myCurrentFacingModel);
      mat.SetTransparency(trans);
    }
    myDrawer->ShadingAspect()->SetMaterial(mat,myCurrentFacingModel);
  } else {
    Handle(Prs3d_ShadingAspect) SA;
    myDrawer->SetShadingAspect(SA);
  }
  hasOwnMaterial = Standard_False;
#else
  AIS_InteractiveObject::UnsetMaterial();
#endif
  if(!GetContext().IsNull()){

    if(GetContext()->MainPrsMgr()->HasPresentation(this,1)){
      Handle(Prs3d_Presentation) P = GetContext()->MainPrsMgr()->CastPresentation(this,1)->Presentation();
      Handle(Graphic3d_Group) G = Prs3d_Root::CurrentGroup(P);
      
      Handle(Graphic3d_AspectFillArea3d) a4bis = myDrawer->ShadingAspect()->Aspect();
      P->SetPrimitivesAspect(a4bis);
      G->SetGroupPrimitivesAspect(a4bis);
    }
  }
  myRecomputeEveryPrs =Standard_False; // aucun mode a recalculer :uniquement update viewer
  myToRecomputeModes.Clear();  
  
}
//=======================================================================
//function : SetTransparency
//purpose  : 
//=======================================================================

void AIS_Shape::SetTransparency(const Standard_Real AValue)
{
#ifdef GER61351
  if(!HasColor() && !HasMaterial() ) {
        myDrawer->SetShadingAspect(new Prs3d_ShadingAspect());
  }
  myDrawer->ShadingAspect()->SetTransparency(AValue,myCurrentFacingModel);
  myTransparency = AValue;
#else
  AIS_InteractiveObject::SetTransparency(AValue);
#endif  
  if(!GetContext().IsNull()){
    if(GetContext()->MainPrsMgr()->HasPresentation(this,1)){
      Handle(Prs3d_Presentation) P = GetContext()->MainPrsMgr()->CastPresentation(this,1)->Presentation();
      Handle(Graphic3d_Group) G = Prs3d_Root::CurrentGroup(P);
      
      Handle(Graphic3d_AspectFillArea3d) a4bis = myDrawer->ShadingAspect()->Aspect();
      P->SetPrimitivesAspect(a4bis);
#ifdef BUC60918 	//force highest priority for transparent objects
      P->SetDisplayPriority(10);	
#endif
      G->SetGroupPrimitivesAspect(a4bis);
    }
  }
  myRecomputeEveryPrs =Standard_False; // aucun mode a recalculer :uniquement update viewer
  myToRecomputeModes.Clear();  
  
}

//=======================================================================
//function : UnsetTransparency
//purpose  : 
//=======================================================================
void AIS_Shape::UnsetTransparency()
{
#ifdef GER61351
  if(HasColor() || HasMaterial() ) {
    myDrawer->ShadingAspect()->SetTransparency(0.0,myCurrentFacingModel);
  } else {
    Handle(Prs3d_ShadingAspect) SA;
    myDrawer->SetShadingAspect(SA);
  }
  myTransparency = 0.0;
#else
  AIS_InteractiveObject::UnsetTransparency();
#endif
  if(!GetContext().IsNull()){
    
    if(GetContext()->MainPrsMgr()->HasPresentation(this,1)){
      Handle(Prs3d_Presentation) P = GetContext()->MainPrsMgr()->CastPresentation(this,1)->Presentation();
      Handle(Graphic3d_Group) G = Prs3d_Root::CurrentGroup(P);
      
      Handle(Graphic3d_AspectFillArea3d) a4bis = myDrawer->ShadingAspect()->Aspect();
      P->SetPrimitivesAspect(a4bis);
      G->SetGroupPrimitivesAspect(a4bis);
#ifdef BUC60918	
      P->ResetDisplayPriority();
#endif
    }
  }
  myRecomputeEveryPrs =Standard_False; // aucun mode a recalculer :uniquement update viewer
  myToRecomputeModes.Clear();  
}


void AIS_Shape::LoadRecomputable(const Standard_Integer TheMode)
{
  myRecomputeEveryPrs =Standard_False;
  if(!IsInList(myToRecomputeModes,TheMode))
    myToRecomputeModes.Append(TheMode);
}



//=======================================================================
//function : BoundingBox
//purpose  : 
//=======================================================================

const Bnd_Box& AIS_Shape::BoundingBox()  
{
  if (myshape.ShapeType() == TopAbs_COMPOUND) {
#ifdef BUC60547
    TopoDS_Iterator anExplor (myshape);
#else
    TopExp_Explorer anExplor (myshape, TopAbs_VERTEX);
#endif
    if (!anExplor.More()) { // Shape vide -> Assemblage vide.
      myBB.SetVoid();      
      return myBB;
    }
  }

  if(myCompBB) {
    BRepBndLib::AddClose(myshape, myBB);
    myCompBB = Standard_False;    
  }
  return myBB;
}

//*****
//***** Reset
//=======================================================================
//function : SetOwnDeviationCoefficient
//purpose  : resets myhasOwnDeviationCoefficient to Standard_False and
//           returns Standard_True if it change
//=======================================================================

Standard_Boolean AIS_Shape::SetOwnDeviationCoefficient ()
{
  Standard_Boolean itSet = myDrawer->IsOwnDeviationCoefficient();
  if(itSet)  myDrawer->SetDeviationCoefficient();
  return itSet;

}


//=======================================================================
//function : SetHLROwnDeviationCoefficient
//purpose  : resets myhasOwnHLRDeviationCoefficient to Standard_False and
//           returns Standard_True if it change
//=======================================================================

Standard_Boolean AIS_Shape::SetOwnHLRDeviationCoefficient ()
{
  Standard_Boolean itSet = myDrawer->IsOwnHLRDeviationCoefficient();
  if(itSet)  myDrawer->SetHLRDeviationCoefficient();
  return itSet;

}

//=======================================================================
//function : SetOwnDeviationAngle
//purpose  : resets myhasOwnDeviationAngle to Standard_False and
//           returns Standard_True if it change
//=======================================================================

Standard_Boolean AIS_Shape::SetOwnDeviationAngle ()
{
  Standard_Boolean itSet = myDrawer->IsOwnDeviationAngle();
  if(itSet)  myDrawer->SetDeviationAngle();
  return itSet;

}

//=======================================================================
//function : SetOwnHLRDeviationAngle
//purpose  : resets myhasOwnHLRDeviationAngle to Standard_False and
//           returns Standard_True if it change
//=======================================================================

Standard_Boolean AIS_Shape::SetOwnHLRDeviationAngle ()
{
  Standard_Boolean itSet = myDrawer->IsOwnHLRDeviationAngle();
  if(itSet)  myDrawer->SetHLRAngle();
  return itSet;

}
//***** SetOwn
//=======================================================================
//function : SetOwnDeviationCoefficient
//purpose  : 
//=======================================================================

void AIS_Shape::SetOwnDeviationCoefficient ( const Standard_Real  aCoefficient )
{
  myDrawer->SetDeviationCoefficient( aCoefficient );
  SetToUpdate(0) ; // WireFrame
  SetToUpdate(1) ; // Shadding
}

//=======================================================================
//function : SetOwnHLRDeviationCoefficient
//purpose  : 
//=======================================================================

void AIS_Shape::SetOwnHLRDeviationCoefficient ( const Standard_Real  aCoefficient )
{
  myDrawer->SetHLRDeviationCoefficient( aCoefficient );
  
}

//=======================================================================
//function : SetOwnDeviationAngle
//purpose  : 
//=======================================================================

void AIS_Shape::SetOwnDeviationAngle ( const Standard_Real  anAngle )
{

  myDrawer->SetDeviationAngle(anAngle );
  SetToUpdate(0) ;   // WireFrame
}
//=======================================================================
//function : SetOwnDeviationAngle
//purpose  : 
//=======================================================================

void AIS_Shape::SetAngleAndDeviation ( const Standard_Real  anAngle )
{
  Standard_Real OutAngl,OutDefl;
  HLRBRep::PolyHLRAngleAndDeflection(anAngle,OutAngl,OutDefl);
  SetOwnDeviationAngle(anAngle) ;
//  SetOwnDeviationAngle(OutAngl) ;
  SetOwnDeviationCoefficient(OutDefl) ;
  myInitAng = anAngle;
  SetToUpdate(0);
  SetToUpdate(1);
}

//=======================================================================
//function : UserAngle
//purpose  : 
//=======================================================================

Standard_Real AIS_Shape::UserAngle() const
{
  return myInitAng ==0. ? GetContext()->DeviationAngle(): myInitAng;
}


//=======================================================================
//function : SetHLRAngleAndDeviation
//purpose  : 
//=======================================================================

void AIS_Shape::SetHLRAngleAndDeviation ( const Standard_Real  anAngle )
{
  Standard_Real OutAngl,OutDefl;
  HLRBRep::PolyHLRAngleAndDeflection(anAngle,OutAngl,OutDefl);
  SetOwnHLRDeviationAngle( OutAngl );
  SetOwnHLRDeviationCoefficient(OutDefl);

}
//=======================================================================
//function : SetOwnHLRDeviationAngle
//purpose  : 
//=======================================================================

void AIS_Shape::SetOwnHLRDeviationAngle ( const Standard_Real  anAngle )
{
  myDrawer->SetHLRAngle( anAngle );
}

//***** GetOwn
//=======================================================================
//function : OwnDeviationCoefficient
//purpose  : 
//=======================================================================

Standard_Boolean AIS_Shape::OwnDeviationCoefficient ( Standard_Real &  aCoefficient,
						      Standard_Real & aPreviousCoefficient ) const
{
  aCoefficient = myDrawer->DeviationCoefficient();
  aPreviousCoefficient = myDrawer->PreviousDeviationCoefficient ();
  return myDrawer->IsOwnDeviationCoefficient() ;
}

//=======================================================================
//function : OwnHLRDeviationCoefficient
//purpose  : 
//=======================================================================

Standard_Boolean AIS_Shape::OwnHLRDeviationCoefficient ( Standard_Real & aCoefficient,
							 Standard_Real & aPreviousCoefficient ) const
{
  aCoefficient = myDrawer->HLRDeviationCoefficient();
  aPreviousCoefficient = myDrawer->PreviousHLRDeviationCoefficient ();
  return myDrawer->IsOwnHLRDeviationCoefficient();

}

//=======================================================================
//function : OwnDeviationAngle
//purpose  : 
//=======================================================================

Standard_Boolean AIS_Shape::OwnDeviationAngle ( Standard_Real &  anAngle,
						Standard_Real & aPreviousAngle ) const
{
  anAngle = myDrawer->DeviationAngle();
  aPreviousAngle = myDrawer->PreviousDeviationAngle (); 
  return myDrawer->IsOwnDeviationAngle();
}

//=======================================================================
//function : OwnHLRDeviationAngle
//purpose  : 
//=======================================================================

Standard_Boolean AIS_Shape::OwnHLRDeviationAngle ( Standard_Real &  anAngle,
						   Standard_Real & aPreviousAngle ) const
{
  anAngle = myDrawer->HLRAngle();
  aPreviousAngle = myDrawer->PreviousHLRDeviationAngle (); 
  return myDrawer->IsOwnHLRDeviationAngle();

}
