// File:	TNaming_Name.cxx
// Created:	Fri Mar 21 15:07:41 1997
// Author:	Yves FRICAUD
//		<yfr@claquox.paris1.matra-dtv.fr>


#include <TNaming_Name.ixx>
#include <TNaming.hxx>
#include <TNaming_NamingTool.hxx>
#include <TNaming_Naming.hxx>
#include <TNaming_ShapesSet.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_Iterator.hxx>
#include <TNaming_NewShapeIterator.hxx>
#include <TNaming_ListOfNamedShape.hxx>
#include <TNaming_ListIteratorOfListOfNamedShape.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>

#include <TopTools_MapOfShape.hxx>
#include <TopTools_MapIteratorOfMapOfShape.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelList.hxx>
#include <TDF_LabelMap.hxx>
#include <TNaming_Tool.hxx>

#include <Standard_NotImplemented.hxx>
#include <Standard_ConstructionError.hxx>
#include <TopTools_Array1OfShape.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shell.hxx>

// mpv modifications 08.04.2002
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_CompSolid.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <TopTools_HArray2OfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_DataMapOfShapeListOfShape.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfShapeListOfShape.hxx>
// end of mpv modifications 08.04.2002

#include <TNaming_NCollections.hxx>

#define BUC60925
#define OCC352

//#define OCC355
//#define MDTV_DEB
//#define MDTV_DEB_OR
//#define MDTV_DEB_UNN
//#define  MDTV_DEB_INT
//#define MDTV_DEB_GEN
//#define  MDTV_DEB_MODUN
//#define MDTV_DEB_FNB
//#define  MDTV_DEB_WIN
#ifdef MDTV_DEB
#include <TCollection_AsciiString.hxx>
#include <TDF_Tool.hxx>
#include <BRepTools.hxx>
#include <DbgTools.hxx>
#endif
#ifdef DEB
#include <TCollection_AsciiString.hxx>
#include <TDF_Tool.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_MapIteratorOfLabelMap.hxx>
//=======================================================================
void PrintEntry(const TDF_Label&       label)
{
  TCollection_AsciiString entry;
  TDF_Tool::Entry(label, entry);
  cout << "LabelEntry = "<< entry << endl;
}
//=======================================================================
void PrintEntries(const TDF_LabelMap& map)
{
  cout << "=== Labels Map ===" <<endl;
  TCollection_AsciiString entry;
  TDF_MapIteratorOfLabelMap it(map);
  for(;it.More();it.Next()) {
    TDF_Tool::Entry(it.Key(), entry);
      cout << "LabelEntry = "<< entry << endl;
    }
}

#include <BRepTools.hxx>
//=======================================================================
static void DbgTools_Write(const TopoDS_Shape& shape,
		      const Standard_CString filename) 
{
  char buf[256];
  if(strlen(filename) > 256) return;
  strcpy (buf, filename);
  char* p = buf;
  while (*p) {
    if(*p == ':')
      *p = '-';
    p++;
  }
  ofstream save (buf);
  if(!save) 
    cout << "File " << buf << " was not created: rdstate = " << save.rdstate() << endl;
  save << "DBRep_DrawableShape" << endl << endl;
  if(!shape.IsNull()) BRepTools::Write(shape, save);
  save.close();
}
//=======================================================================
static void DbgTools_Write(const TopTools_MapOfShape& MS,  const Standard_CString filename) 
{
  if (!MS.IsEmpty ()) {
    TCollection_AsciiString aNam (filename);
    Standard_Integer i(0);
    TopTools_MapIteratorOfMapOfShape it(MS);
    for(;it.More();it.Next(),i++) {
      TCollection_AsciiString aName = aNam + "_" + i + ".brep";
      DbgTools_Write ( it.Key(), aName.ToCString());
    }
  }
}
//=======================================================================
static void DbgTools_WriteNSOnLabel (const Handle(TNaming_NamedShape)& NS,  
				     const Standard_CString filename) 
{
  if(!NS.IsNull() && !NS->IsEmpty() ) {
    TCollection_AsciiString aNam (filename);
    TCollection_AsciiString oldS ("_Old");
    TCollection_AsciiString newS ("_New_");
    Standard_Integer i(0);
    TNaming_Iterator it(NS);
    for(;it.More(); it.Next(),i++) {
      TCollection_AsciiString aName1 = aNam + oldS + i + ".brep";
      TCollection_AsciiString aName2 = aNam + newS + i + ".brep";
      const TopoDS_Shape& oldShape = it.OldShape();
      const TopoDS_Shape& newShape = it.NewShape();
      if(!oldShape.IsNull())
	DbgTools_Write ( oldShape, aName1.ToCString());
      if(!newShape.IsNull())
	DbgTools_Write ( newShape, aName2.ToCString());      
    }
  }
}
#endif

//=======================================================================
//
//====================================================================
static Standard_Boolean ValidArgs(const TNaming_ListOfNamedShape& Args)
{
  TNaming_ListIteratorOfListOfNamedShape it(Args);
  for (;it.More();it.Next()) {
    const Handle(TNaming_NamedShape)& aNS = it.Value();
    if(aNS.IsNull()) {
#ifdef MDTV_DEB 
      cout << "ValidArgs:: NS (Naming argument) is NULL" <<endl;
#endif	
      return Standard_False;
    }
    else 
      if(aNS->IsEmpty()) {
#ifdef MDTV_DEB 
	TCollection_AsciiString entry;
	TDF_Tool::Entry(aNS->Label(), entry);
	cout << "ValidArgs:: Empty NS, Label = " << entry <<endl;
#endif	
      return Standard_False;
    }
      else  
	if(!aNS->IsValid()) {
#ifdef MDTV_DEB 
	  TCollection_AsciiString entry;
	  TDF_Tool::Entry(aNS->Label(), entry);
	  cout << "ValidArgs::Not valid NS Label = " << entry <<endl;
#endif	
	  return Standard_False; 
	}
    }
  return Standard_True;
}

//=======================================================================
//function : TNaming_Name
//purpose  : 
//=======================================================================

TNaming_Name::TNaming_Name():myIndex(-1)
{
}


//=======================================================================
//function : Type
//purpose  : 
//=======================================================================

void TNaming_Name::Type(const TNaming_NameType aType) 
{
  myType = aType;
}

//=======================================================================
//function : Type
//purpose  : 
//=======================================================================

void TNaming_Name::ShapeType(const TopAbs_ShapeEnum T) 
{
  myShapeType = T;
}

//=======================================================================
//function : Shape
//purpose  : 
//=======================================================================

void TNaming_Name::Shape(const TopoDS_Shape& theShape) 
{
  myShape = theShape;
  
}

//=======================================================================
//function : Shape
//purpose  : 
//=======================================================================

TopoDS_Shape TNaming_Name::Shape() const
{
  return myShape;
}

//=======================================================================
//function : Append
//purpose  : 
//=======================================================================

void TNaming_Name::Append(const Handle(TNaming_NamedShape)& arg) 
{
  myArgs.Append (arg);
}

//=======================================================================
//function : StopNamedShape
//purpose  : 
//=======================================================================

void TNaming_Name::StopNamedShape (const Handle(TNaming_NamedShape)& arg) 
{
  myStop = arg;
}

//=======================================================================
//function : Index
//purpose  : 
//=======================================================================

void TNaming_Name::Index (const Standard_Integer I)
{
  myIndex = I;
}


//=======================================================================
//function : TNaming_NameType
//purpose  : 
//=======================================================================

TNaming_NameType TNaming_Name::Type() const 
{
  return myType;
}

//=======================================================================
//function : TNaming_NameType
//purpose  : 
//=======================================================================

TopAbs_ShapeEnum TNaming_Name::ShapeType() const 
{
  return myShapeType;
}

//=======================================================================
//function : Append
//purpose  : 
//=======================================================================

void TNaming_Name::Paste (TNaming_Name& into,
			  const Handle(TDF_RelocationTable)& RT) const
{
  into.myType      = myType;
  into.myShapeType = myShapeType;
  into.myShape     = myShape; 
  into.myArgs.Clear();
//  into.myOrientation = myOrientation;
  Handle(TNaming_NamedShape) NS;

  for (TNaming_ListIteratorOfListOfNamedShape it(myArgs); it.More(); it.Next()) {
    RT->HasRelocation(it.Value(),NS);
    into.myArgs.Append (NS);
  }
  if (!myStop.IsNull()) {
    RT->HasRelocation(myStop,NS);
    into.myStop = NS;
  }
  if (!myContextLabel.IsNull()) {
    RT->HasRelocation(myContextLabel,into.myContextLabel);
  }
}

//=======================================================================
//function : Arguments
//purpose  : 
//=======================================================================
      
const TNaming_ListOfNamedShape& TNaming_Name::Arguments() const
{
  return myArgs;
}

//=======================================================================
//function : Arguments
//purpose  : 
//=======================================================================
      
Handle(TNaming_NamedShape) TNaming_Name::StopNamedShape() const
{
  return myStop;
}

//=======================================================================
//function : Index
//purpose  : 
//=======================================================================
      
Standard_Integer TNaming_Name::Index() const
{
  return myIndex;
}

//=======================================================================
//function : MakeShape
//purpose  : 
//=======================================================================

static TopoDS_Shape MakeShape (const TopTools_MapOfShape& MS) 
{  
  if (!MS.IsEmpty ()) {
    TopTools_MapIteratorOfMapOfShape it(MS);
    if (MS.Extent() == 1) {
      return it.Key();
    }
    else {
      TopoDS_Compound C;
      BRep_Builder B;
      B.MakeCompound(C);
      for (; it.More(); it.Next()){ 
	B.Add(C,it.Key());
      }
      return C;
    }
  }
  return TopoDS_Shape();  
}

#ifdef OCC352

//=======================================================================
//function : ShapeWithType
//purpose  : Tries to make shape with given type from the given shape
//=======================================================================

static TopoDS_Shape ShapeWithType(const TopoDS_Shape     theShape,
				  const TopAbs_ShapeEnum theType ) {
  if (theShape.IsNull() || theType == TopAbs_SHAPE) return theShape;
  Standard_Integer aType = theShape.ShapeType();
  if (aType == theType) return theShape;

  TopTools_ListOfShape aShapes;
  if (aType == TopAbs_COMPOUND) {
    TopoDS_Iterator anIter(theShape);
    if (anIter.More()) aType = anIter.Value().ShapeType();
    for(;anIter.More();anIter.Next()) aShapes.Append(anIter.Value());
    if (aType == theType) {
      if (aShapes.Extent() == 1) return aShapes.First();
      else return theShape;
    }
  } else aShapes.Append(theShape);

  TopoDS_Shape aResult;
  TopTools_ListIteratorOfListOfShape aListIter(aShapes);

  if (aType < theType) {
    Standard_Integer aCount;
    for(aCount=0;aListIter.More();aListIter.Next()) {
      TopExp_Explorer anExp(aListIter.Value(),theType);
      if (anExp.More()) {
	if (!anExp.Current().IsNull()) {
	  aResult = anExp.Current();
	  aCount++;
	  if (aCount > 1) return theShape;
	}
      }
    }
    if (aCount == 1) return aResult;
  } else { // if the shape type more complex than shapes from aShapes list, try make it
    switch (aType) {
    case TopAbs_VERTEX: // can't do something from vertex
      break;
    case TopAbs_EDGE: {// make wire from edges
      if (theType <= TopAbs_SOLID) break;
      BRepBuilderAPI_MakeWire aMakeWire;
      aMakeWire.Add(aShapes);
      if (!aMakeWire.IsDone()) return theShape;
      if (theType == TopAbs_WIRE) return aMakeWire.Wire();
      aShapes.Clear(); // don't break: we can do something more of it
      aShapes.Append(aMakeWire.Wire());
      aListIter.Initialize(aShapes);
    }
    case TopAbs_WIRE: {// make faceS from wires (one per one)
      if (theType < TopAbs_SOLID) break;
      TopTools_ListOfShape aFaces;
      for(;aListIter.More();aListIter.Next()) {
	BRepBuilderAPI_MakeFace aMakeFace(TopoDS::Wire(aListIter.Value()));
	if (!aMakeFace.IsDone()) aFaces.Append(aMakeFace.Face());
      }
      if (theType == TopAbs_FACE) {
	if (aFaces.Extent() == 1) return aFaces.First();
	return theShape;
      }
      aShapes.Assign(aFaces); // don't break: we can do something more of it
      aListIter.Initialize(aShapes);
    }
    case TopAbs_FACE: {// make shell from faces
      if (theType < TopAbs_SOLID) break;
      BRep_Builder aShellBuilder;
      TopoDS_Shell aShell;
      aShellBuilder.MakeShell(aShell);
      for(;aListIter.More();aListIter.Next()) aShellBuilder.Add(aShell,TopoDS::Face(aListIter.Value()));
      if (theType == TopAbs_SHELL) return aShell;
      aShapes.Clear(); // don't break: we can do something more of it
      aShapes.Append(aShell);
      aListIter.Initialize(aShapes);
    }
    case TopAbs_SHELL: {// make solids from shells (one per one)
      TopTools_ListOfShape aSolids;
      for(;aListIter.More();aListIter.Next()) {
	BRepBuilderAPI_MakeSolid aMakeSolid(TopoDS::Shell(aListIter.Value()));
	if (aMakeSolid.IsDone()) aSolids.Append(aMakeSolid.Solid());
      }
      if (theType == TopAbs_SOLID) {
	if (aSolids.Extent() == 1) return aSolids.First();
	return theShape;
      }
      aShapes.Assign(aSolids); // don't break: we can do something more of it
      aListIter.Initialize(aShapes);
    }
    case TopAbs_SOLID: {// make compsolid from solids
      BRep_Builder aCompBuilder;
      TopoDS_CompSolid aCompSolid;
      aCompBuilder.MakeCompSolid(aCompSolid);
      for(;aListIter.More();aListIter.Next()) aCompBuilder.Add(aCompSolid,TopoDS::Solid(aListIter.Value()));
      if (theType == TopAbs_COMPSOLID) return aCompSolid;
    }
    }
  }
  return theShape;
}

#endif

//=======================================================================
//function : FindModifUntil
//purpose  : 
//=======================================================================

static Standard_Boolean FindModifUntil (TNaming_NewShapeIterator&         it,
					TopTools_MapOfShape&              MS,
					const TopoDS_Shape&               S,
					const Handle(TNaming_NamedShape)& Context)
{ 
  Standard_Boolean found = Standard_False;
  for (; it.More(); it.Next()) {
    if (!it.Shape().IsNull()) {
      if (it.NamedShape() == Context) {
	MS.Add(S);
	found = Standard_True;
      }
      else { // New shape != Context
	TNaming_NewShapeIterator it2(it);
	found = FindModifUntil (it2,MS,it.Shape(),Context);
      }
    }
  }
  return found;
}

//=======================================================================
//function : ModifUntil
//purpose  : returns map <theMS> of generators of Target
//=======================================================================

static void SearchModifUntil (const TDF_LabelMap&               /*Valid*/,
			      const Handle(TNaming_NamedShape)& Target,
			      const TNaming_ListOfNamedShape& theListOfGenerators,
			      TopTools_MapOfShape&              theMS)
{

#ifdef MDTV_DEB_MODUN
   DbgTools_WriteNSOnLabel(Target, "SMUntil_"); // Target <== generated
  Standard_Integer i = 0;
  TCollection_AsciiString aGen1("Gens_New_"), aGen2("Gented_Old_"), Und("_");
#endif 
  // Test si S apparait comme oldshape dans Context. : Test if S appears as oldshape in Context.
  Standard_Boolean found = Standard_False;
  for (TNaming_ListIteratorOfListOfNamedShape it(theListOfGenerators); it.More(); it.Next()) {
    const Handle(TNaming_NamedShape)& aNS = it.Value();
#ifdef MDTV_DEB_MODUN  
    i++;
    Standard_Integer j = 0;
#endif
    for (TNaming_Iterator itL (aNS); itL.More(); itL.Next()) { // <- generators
      const TopoDS_Shape& S = itL.NewShape();
      found = Standard_False;
      
#ifdef MDTV_DEB_MODUN
      j++;
      Standard_Integer k = 0;
      TCollection_AsciiString aNam1 = aGen1 + i + Und + j + ".brep";
      DbgTools_Write(S, aNam1.ToCString());
#endif   
      for  (TNaming_Iterator itC (Target); itC.More(); itC.Next()) {  // <- generated
	const TopoDS_Shape& OS = itC.OldShape();
#ifdef MDTV_DEB_MODUN
	k++;
	TCollection_AsciiString aNam2 = aGen2 + i + Und + j + Und + k + ".brep";
	DbgTools_Write(OS, aNam2.ToCString());
#endif 
	if (OS.IsSame(S)) {
	  theMS.Add(S);
	  found = Standard_True;
#ifdef MDTV_DEB_MODUN
	  cout << aNam2 << " is Same with " << aNam1 <<endl;
#endif
	  break;
	}
      }
      if (!found) {
	TNaming_NewShapeIterator it1(itL);
	found = FindModifUntil (it1,theMS,S,Target);
      }
    }
  }
}

//=======================================================================
//function : ModifUntil
//purpose  : 
//=======================================================================
// NamedShape for this type is assembled from all last modifications of the 
// last argument shapes (see method  TNaming_NamingTool::CurrentShape), 
// which are not descendants (see method TNaming_NamingTool::BuildDescendants) 
// of the stop shape. This type of naming is used for identification shapes, 
// which has only one parent with evolution PRIMITIVE (or itself), which 
// uniquely identifies it. In most cases stop shape is empty and this algorithm 
// is equal to the algorithm for IDENTITY. 
//=======================================================================
static Standard_Boolean ModifUntil (const TDF_Label&                  L,
				    const TDF_LabelMap&               Valid,
				    const TNaming_ListOfNamedShape&   Args,
				    const Handle(TNaming_NamedShape)& Stop)
{
  TopTools_MapOfShape MS; 
  TDF_LabelMap Forbiden;
#ifdef BUC60925
  if(!ValidArgs(Args)) return Standard_False;
#endif
  TNaming_NamingTool::BuildDescendants (Stop, Forbiden); // fills Forbidden from Stop

#ifdef MDTV_DEB_GEN  
  cout <<"Regenerating ModifUntil => ";
  PrintEntry(L);
  DbgTools_WriteNSOnLabel(Args.Last(), "ModifUntil-");
 
#endif
  // all last modifications of the last argument
  TNaming_NamingTool::CurrentShape  (Valid, Forbiden,Args.Last(),MS); 
#ifdef MDTV_DEB_GEN  
  Standard_Integer i(0);
  TopTools_MapIteratorOfMapOfShape it(MS);
  TCollection_AsciiString aNam("ModifUnti_MS_");
  TCollection_AsciiString ext(".brep"); 
#endif
  TNaming_Builder B(L);
  for (TopTools_MapIteratorOfMapOfShape itM(MS); itM.More(); itM.Next()) {
    const TopoDS_Shape& S = itM.Key();
    B.Select(S,S);
#ifdef MDTV_DEB_GEN  
    TCollection_AsciiString aName = aNam + ++i + ext;
    DbgTools_Write(S, aName.ToCString()) ;
    cout << aName.ToCString() << " TS = " << S.TShape()->This() <<endl;
#endif
  }
  return Standard_True;
}

//=======================================================================
//function : ContShape
//purpose  : 
//=======================================================================
// from the NS of the first argument TNaming_Iterator is started, shape "S" 
// is the NewShape from Iterator with index "myIndex" of the Name, this 
// shape and all last modifications (except NamedShapes - descendants of 
// the stop shape) are the parts of resulting NamedShape.
//=======================================================================
static Standard_Boolean ConstShape (const TDF_Label&                  L,
				    const TDF_LabelMap&               Valid,
				    const TNaming_ListOfNamedShape&   Args,
				    const Handle(TNaming_NamedShape)& Stop,
				    const Standard_Integer            Index)
{
  TopTools_MapOfShape MS; 
  TDF_LabelMap Forbiden;
#ifdef BUC60925
  if(!ValidArgs(Args)) return Standard_False;
#endif
  TNaming_NamingTool::BuildDescendants (Stop, Forbiden);

  TopoDS_Shape S;
  Standard_Integer i = 1;
  for (TNaming_Iterator it(Args.First()); it.More(); it.Next(), i++) {
    if (Index == i) {
      S = it.NewShape();
      break;
    }
  }
  if (S.IsNull()) return Standard_False;

  TNaming_NamingTool::CurrentShapeFromShape  (Valid,Forbiden,L,S,MS);

 
  TNaming_Builder B(L);
  for (TopTools_MapIteratorOfMapOfShape itM(MS); itM.More(); itM.Next()) {
    const TopoDS_Shape& SS = itM.Key();
    B.Select(SS,SS);
  }
  return Standard_True;
}

//=======================================================================
//function : Intersection
//purpose  : 
//=======================================================================
//algorithm does next steps:
// 1. Sets to the "Forbiden" map  all shapes, which are descendants of stop 
//    shape. Named shapes at these labels can't be used.
// 2. Takes first argument (with method CurrentShape) and sets map "S" of 
//    ancestors (shapes, which belong to this one) of its shape with type 
//    "ShapeType" of Name.
// 3. Takes next argument of Name (with method CurrentShape) and removes 
//    from the map "S" all ancestors, which not belongs to the shape of 
//    this argument. This step is repeated for all arguments of this Name.
// 4. Adds to the result NamedShape all rest of shapes from the map "S".
//=======================================================================
static Standard_Boolean Intersection (const TDF_Label&                  L,
				      const TDF_LabelMap&               Valid,
				      const TNaming_ListOfNamedShape&   Args,
				      const Handle(TNaming_NamedShape)& Stop,
				      const TopAbs_ShapeEnum            ShapeType,
				      const Standard_Integer            Index)
{
  if (Args.IsEmpty()) return Standard_False;
#ifdef BUC60925
  if(!ValidArgs(Args)) return Standard_False;
#endif
  TNaming_ListIteratorOfListOfNamedShape it(Args); 
  TopTools_MapOfShape MS; 
  TDF_LabelMap        Forbiden;

#ifdef MDTV_DEB_INT
  if(!Stop.IsNull() && !Stop->Get().IsNull()) {
    DbgTools_Write(Stop->Get(), "Ints_Stop.brep");
    PrintEntry(Stop->Label());
  }
  cout <<"Ints: ShapeType = " << ShapeType << endl;
  cout <<"Argument 1 at ";
  PrintEntry(it.Value()->Label());
#endif 

  TNaming_NamingTool::BuildDescendants (Stop, Forbiden); // <==<1>

#ifdef MDTV_DEB_INT
  cout << "Intersection:: Valid Map: "<<endl;
  PrintEntries(Valid);
  cout << "Intersection:: Forbidden Map: "<<endl;
  PrintEntries(Forbiden);
#endif
  TopTools_ListOfShape aListOfAnc;
  TNaming_NamingTool::CurrentShape  (Valid, Forbiden,it.Value(),MS); // first argument
  TopoDS_Shape  CS = MakeShape(MS);
  TNaming_ShapesSet S(CS,ShapeType); // <==<2>
  aListOfAnc.Append(CS);
#ifdef MDTV_DEB_INT
  if(!CS.IsNull())
    DbgTools_Write(CS, "Int_CS_1.brep");
  Standard_Integer i=2;
  TCollection_AsciiString aNam("Int_CS_");
  TCollection_AsciiString ext(".brep");
 
#endif 
  it.Next();  // <<===<3.1>
  for (; it.More(); it.Next()) {
    MS.Clear();
    TNaming_NamingTool::CurrentShape (Valid,Forbiden,it.Value(),MS);
    CS = MakeShape(MS);
    aListOfAnc.Append(CS);
#ifdef MDTV_DEB_INT
    TCollection_AsciiString aName = aNam + i++ + ext;      
    DbgTools_Write(CS, aName.ToCString()) ;
    cout <<"Argument " << i << " at ";
    PrintEntry(it.Value()->Label());
#endif  

    TNaming_ShapesSet OS(CS,ShapeType);
    S.Filter(OS); //<<===<3.2>
#ifdef MDTV_DEB_INT
    Standard_Integer j = 1;
    TCollection_AsciiString aNam2("SSMap_"), aName3;
    TopTools_MapIteratorOfMapOfShape itm(S.Map());
    for(;itm.More();itm.Next(), j++) {
      aName3 = aNam2 + i + "_" + j + ".brep";
      DbgTools_Write(itm.Key(), aName3.ToCString());
    }
#endif 
  }

#ifdef MDTV_DEB_INT
  aNam = "Int_S_";
  i =1;
#endif

  TNaming_Builder B(L); //<<===<4>
  Standard_Boolean isOK(Standard_False);
  if(S.Map().Extent() > 1 && Index > 0 && ShapeType == TopAbs_EDGE) {
    Standard_Integer indxE(0), nbE(0), indxW(0),nbW(0), indxF(0);
    indxE =  Index & 0x000000FF;
    nbE   = (Index & 0x0000FF00) >> 8;
    indxW = (Index & 0x000F0000) >> 16;
    nbW   = (Index & 0x00F00000) >> 20;
    indxF = (Index & 0x0F000000) >> 24;
    Standard_Integer i(1);
    TopoDS_Shape aS;
    TopTools_ListIteratorOfListOfShape itl(aListOfAnc);
    for(;itl.More();itl.Next(),i++) {
      if(indxF == i) {
	aS = itl.Value();
	break;
      }      
    }
#ifdef MDTV_DEB_INT
    cout <<"Kept: indxE = " << indxE  <<" maxENum = " << nbE << " indxW = " <<indxW << " nbW = " <<nbW<<endl;
#endif      
    Standard_Integer aNbW(0), aCaseW(0);
    TopoDS_Iterator it2(aS);
    for (;it2.More();it2.Next()) aNbW++;  
    if(aNbW == nbW) aCaseW = 1;//exact solution for wire (nb of wires is kept)
    else aCaseW = 2; // indefinite description ==> compound which can include expected wire    
    if(aCaseW == 1) {      
      TopoDS_Shape aWire;
      Standard_Integer i(1);
      it2.Initialize(aS);
      for (;it2.More();it2.Next(),i++) {
	if(indxW == i) {
	  aWire = it2.Value();
	  break;
	}
      }
      Standard_Integer aNbE(0), aCaseE(0);
      it2.Initialize(aWire);
      for (;it2.More();it2.Next()) aNbE++;
      if(aNbE == nbE) aCaseE = 1;//exact solution for edge
      else aCaseE = 2;
      if(aCaseE == 1) {
	i=1;
	TopoDS_Shape anEdge;
	it2.Initialize(aWire);
	for (;it2.More();it2.Next(),i++) {
	  if(indxE == i) {
	    anEdge = it2.Value();
	    break;
	  }
	}
	if(!anEdge.IsNull()) {
	  B.Select(anEdge, anEdge);
	  isOK = Standard_True;
	}
      }
    }   
  } 
  if(!isOK)
#ifdef MDTV_DEB_INT
    for (TopTools_MapIteratorOfMapOfShape itM(S.Map()); itM.More(); itM.Next(),i++) {
#else
      
    for (TopTools_MapIteratorOfMapOfShape itM(S.Map()); itM.More(); itM.Next()) {
#endif
      const TopoDS_Shape& S1 = itM.Key();
#ifdef MDTV_DEB_INT
      TCollection_AsciiString aName = aNam + i + ext;      
      DbgTools_Write(S1, aName.ToCString()) ;
#endif  

      B.Select(S1,S1);
      isOK = Standard_True;
    }
  return isOK;
}
//=======================================================================
static void KeepInList(const TopoDS_Shape& CS, const TopAbs_ShapeEnum Type, TopTools_ListOfShape& aList)   
{
  if (CS.IsNull()) return;

  if (Type == TopAbs_SHAPE) { 
    if (CS.ShapeType() == TopAbs_SOLID ||
	CS.ShapeType() == TopAbs_FACE  ||
	CS.ShapeType() == TopAbs_EDGE  ||
	CS.ShapeType() == TopAbs_VERTEX ) {
      aList.Append(CS);
    }
    else {
      for (TopoDS_Iterator it(CS) ; it.More(); it.Next()) {
	aList.Append(it.Value());
      }
    }
  }
  else {
    if (Type > CS.ShapeType()) {
      for (TopExp_Explorer exp(CS,Type) ; exp.More(); exp.Next()) {
	aList.Append(exp.Current());
      }
    } else {
     aList.Append(CS);
    }
  }
}

//=======================================================================
//function : Union
//purpose  : 
//=======================================================================
// Resulting NamedShape contains compound of next shapes: 
// compound of last modifications of each argument (see CurrentShape method) 
// without descendants of the stop shape.
//=======================================================================
static Standard_Boolean Union (const TDF_Label&                  L,
			       const TDF_LabelMap&               Valid,
			       const TNaming_ListOfNamedShape&   Args,
			       const Handle(TNaming_NamedShape)& Stop,
			       const TopAbs_ShapeEnum            ShapeType,
			       const TDF_Label&                  ContextLabel)
{  
  if (Args.IsEmpty()) return Standard_False;
#ifdef BUC60925
  if(!ValidArgs(Args)) return Standard_False;
#endif
  // temporary solution for Orientation name
  Standard_Boolean isOr(Standard_True);
/* not completed
  const TDF_Label& aLabel = L.Father();
  if(!aLabel.IsNull()) {
  PrintEntry(L);
  PrintEntry(aLabel);
    Handle (TNaming_Naming)  Naming;
    if(aLabel.FindAttribute(TNaming_Naming::GetID(), Naming)) {
      const TNaming_Name& aName = Naming->GetName();
      if(aName.Type() == TNaming_ORIENTATION) {
	const TNaming_ListOfNamedShape&   Args = aName.Arguments();
	if(Args.Extent() > 2) {
	  const Handle(TNaming_NamedShape)& A = Args.First();
	  if(!A.IsNull()) {
	    PrintEntry(A->Label());
	    if (A->Label() == L) 
	      isOr = Standard_True;	    
	  }
	} else 
	  if(!Args.Extent())
	    isOr = Standard_True;
      }
    }
  }
*/
  // end of temp. sol.

  TNaming_ListIteratorOfListOfNamedShape it(Args);
  TopTools_MapOfShape MS; 
  TDF_LabelMap        Forbiden;
  
  TNaming_NamingTool::BuildDescendants (Stop, Forbiden);//fill Forbidden
  TNaming_NamingTool::CurrentShape  (Valid, Forbiden,it.Value(),MS); // fill MS with last modifications of the first argument
  TopoDS_Shape  CS = MakeShape(MS);

  TopTools_ListOfShape aListS;
  if(isOr)
    KeepInList(CS,ShapeType,aListS);
  TNaming_ShapesSet S(CS,ShapeType);//fill internal map of shapeset by shapes of the specified type
#ifdef MDTV_DEB_UNN
  TCollection_AsciiString entry; 
  TDF_Tool::Entry(it.Value()->Label(), entry);
  TCollection_AsciiString Nam("Arg_");
  TCollection_AsciiString aNam = Nam + entry + "_" + "1.brep";
  DbgTools_Write(CS, aNam.ToCString());
  Standard_Integer ii = 1;
#endif
  it.Next();
  for (; it.More(); it.Next()) {
#ifdef MDTV_DEB_UNN  
    TDF_Tool::Entry(it.Value()->Label(), entry);
#endif
      MS.Clear();
      TNaming_NamingTool::CurrentShape (Valid, Forbiden,it.Value(),MS);// fill MS with last modifications of the it.Value()
      CS = MakeShape(MS);
      if(isOr)
	KeepInList(CS,ShapeType,aListS); 
      TNaming_ShapesSet OS(CS,ShapeType);
      S.Add(OS); //concatenate both shapesets
 
#ifdef MDTV_DEB_UNN 
    ii++;
    TCollection_AsciiString aNm = Nam + entry + "_" + ii + ".brep";
    DbgTools_Write(CS, aNm.ToCString());
    cout <<"Arg: Entry = " <<entry <<"  TShape = " << CS.TShape() <<endl;
#endif
  }

// start szy 27.05.08
  TopoDS_Shape aCand;
  Standard_Boolean found = Standard_False;
  if(!ContextLabel.IsNull()) {
    Handle(TNaming_NamedShape) CNS;
    ContextLabel.FindAttribute(TNaming_NamedShape::GetID(),CNS);
    TopoDS_Shape aContext;
    if(!CNS.IsNull()) {
      MS.Clear();
      TNaming_NamingTool::CurrentShape (Valid, Forbiden, CNS, MS);
      aContext = MakeShape(MS);
#ifdef MDTV_DEB_UNN 
      TCollection_AsciiString anEntry;
      TDF_Tool::Entry(ContextLabel, anEntry);
      cout << "UNION: Context Label = " <<  anEntry << endl;
      DbgTools_Write(aContext, "Union_Context.brep");
      TCollection_AsciiString aN ("aMap_");
      TopTools_MapIteratorOfMapOfShape it(S.Map());
      for(Standard_Integer i=1; it.More();it.Next(), i++) {
	TCollection_AsciiString aName = aN + i + ".brep";
	DbgTools_Write(it.Key(), aName.ToCString());
      }
#endif
    }
    TopTools_ListOfShape aList;
    TopExp_Explorer anExpl(aContext, ShapeType);
    for(;anExpl.More(); anExpl.Next()) 
      aList.Append(anExpl.Current());
#ifdef MDTV_DEB_UNN
    cout <<"UNION: ShapeType = " << ShapeType << " List ext = " << aList.Extent()<<endl;
    TopAbs_ShapeEnum aTyp = TopAbs_SHAPE;
    TopTools_MapIteratorOfMapOfShape it1 (S.Map());
    for (int i=1;it1.More();it1.Next(),i++) {
      cout << "Map("<<i<<"): TShape = " << it1.Key().TShape() << " Orient = " << it1.Key().Orientation() <<endl;
      aTyp = it1.Key().ShapeType();
    }
    
    TopExp_Explorer exp(aContext, aTyp);
    for(int i =1;exp.More();exp.Next(), i++) {
     cout << "Context("<<i<<"): TShape = " << exp.Current().TShape() << " Orient = " << exp.Current().Orientation() <<endl;
    }
	    
#endif
    TopTools_ListIteratorOfListOfShape itl(aList);
    for(;itl.More();itl.Next()) {
      aCand = itl.Value(); 
#ifdef MDTV_DEB_UNN 
      DbgTools_Write(aCand, "Cand.brep");
#endif
      Standard_Integer num = S.Map().Extent();
      anExpl.Init(aCand, (ShapeType == TopAbs_WIRE) ? TopAbs_EDGE : TopAbs_FACE); 
      for(;anExpl.More();anExpl.Next()) {
	if(S.Map().Contains(anExpl.Current()))
	  num--;
      } 
      if(num == 0) {
	found = Standard_True; 
	break;
      }
    }
// end szy 27.05.08
  }

  TNaming_Builder B(L);
#ifdef MDTV_DEB_UNN
  if(!ContextLabel.IsNull()) {
    if(found) cout << "UNION: Shape is found in Context" <<endl;
    else cout << "UNION: Shape is NOT found in Context" <<endl;
  }
#endif
#ifdef OCC352
  if(found) 
    B.Select(aCand, aCand);
  else {
    BRep_Builder aCompoundBuilder;
    TopoDS_Compound aCompound;
    aCompoundBuilder.MakeCompound(aCompound);
    if(!isOr)
      for (TopTools_MapIteratorOfMapOfShape itM(S.Map()); itM.More(); itM.Next()) {
	aCompoundBuilder.Add(aCompound,itM.Key());
      }
    else
      for (TopTools_ListIteratorOfListOfShape itL(aListS); itL.More(); itL.Next()) {
	aCompoundBuilder.Add(aCompound,itL.Value());
      }
    TopoDS_Shape aShape = ShapeWithType(aCompound,ShapeType);
#ifdef MDTV_DEB_UNN 
    DbgTools_Write(aShape, "Union_Selected.brep");
    DbgTools_Write(aCompound, "Union_Compound.brep");
#endif
    B.Select(aShape,aShape);
  }
#else

  for (TopTools_MapIteratorOfMapOfShape itM(S.Map()); itM.More(); itM.Next()) {
    const TopoDS_Shape& S = itM.Key();
    B.Select(S,S);
  }

#endif

  return Standard_True;
}

//=======================================================================
// function: FindShape
//
//=======================================================================
static TopoDS_Shape FindShape(const TNaming_DataMapOfShapeMapOfShape& DM) 
{
  TopoDS_Shape aResult;
  Standard_Integer aNum = DM.Extent();
  if(aNum < 1) return aResult;  
  TopTools_ListOfShape List;
  TNaming_DataMapIteratorOfDataMapOfShapeMapOfShape it(DM);
  if(it.More()) {
    const TopoDS_Shape& aKey1 = it.Key();
    const TNaming_MapOfShape& aMap = it.Value();

    TNaming_MapIteratorOfMapOfShape itm(aMap); // iterate first map
    for (;itm.More();itm.Next()) {
      const TopoDS_Shape& aS = itm.Key(); // element of the first map
      Standard_Boolean isCand(Standard_True); // aS is a Candidate
      TNaming_DataMapIteratorOfDataMapOfShapeMapOfShape it2(DM);
      for (;it2.More();it2.Next()) {
	const TopoDS_Shape& aKey2 = it2.Key();
	if(aKey2 == aKey1) continue;
	const TNaming_MapOfShape& aMap2 = it2.Value();
	if(!aMap2.Contains(aS)) isCand = Standard_False;
      } 
      if(isCand)
	List.Append(aS);
    }
  }
  if(List.IsEmpty()) return aResult;
  if(List.Extent() == 1) return List.First();
  TopTools_ListIteratorOfListOfShape itl (List);
  TopoDS_Compound Compound;
  BRep_Builder B;
  B.MakeCompound(Compound);
  for (; itl.More(); itl.Next()){ 
    B.Add(Compound,itl.Value());
  }
  return Compound; 
}

//=======================================================================
//function : Generation
//purpose  : Resolves Name from arguments: arg1 - generated (target shape)
//         : arg2 - the generator: the oldest ancestor (usually NS with 
//         : PRIMITIVE evolution. (See TNaming_Localizer::FindGenerator).
//         : Resulting NamedShape contains shape, which is in the first 
//         : argument NamedShape and is modification of the last argument NS.
//=======================================================================

static Standard_Boolean  Generated (const TDF_Label&                L,
				    const TDF_LabelMap&             Valid,
				    const TNaming_ListOfNamedShape& Args)
{
  if (Args.Extent() < 2) {
    Standard_ConstructionError::Raise("TNaming_Name::Solve: => Generated");
  }
  // First argument : label of generation
  // Next arguments : generators.

#ifdef BUC60925
  if(!ValidArgs(Args)) return Standard_False;
#endif

  TDF_Label   LabelOfGeneration = Args.First()->Label();
#ifdef MDTV_DEB_GEN
      DbgTools_Write(Args.First()->Get(),  "Generated.brep") ;
#endif
  // Nouvell valeurs des generateurs dans l attribut de generation
  TopTools_MapOfShape aMS;
  TNaming_ListOfNamedShape aGenerators; 
  aGenerators.Assign(Args); 
  aGenerators.RemoveFirst(); 
#ifdef MDTV_DEB_GEN
      DbgTools_Write(aGenerators.First()->Get(),  "Generators.brep") ;
#endif
  SearchModifUntil (Valid, Args.First(), aGenerators, aMS);
  Handle(TNaming_Naming) aNaming;
  TopoDS_Shape aSelection;
  L.FindAttribute(TNaming_Naming::GetID(),aNaming);
  if(!aNaming.IsNull()) 
    aSelection = aNaming->GetName().Shape();
#ifdef MDTV_DEB_GEN
  DbgTools_Write(aSelection,  "G_Selection.brep") ;
  cout << "Generated::SearchModifUntil aMS.Extent() = " << aMS.Extent() <<endl;
  DbgTools_Write(aMS, "SearchModifUntil_Result");
#endif
   Handle(TNaming_NamedShape) anOldNS;
   Standard_Integer aVer = -1;// Initial build of name
   L.FindAttribute(TNaming_NamedShape::GetID(),anOldNS);
   if(!anOldNS.IsNull()) 
     aVer = anOldNS->Version();

#ifdef MDTV_DEB_GEN
  Standard_Integer i = 0, j=1;
  TCollection_AsciiString aNam2("Gen_New_");
  TCollection_AsciiString aNam1("Gen_Old_");
  TCollection_AsciiString ext(".brep");
#endif
  TNaming_Builder B(L); // NS
  TopTools_ListOfShape aList;
  TNaming_DataMapOfShapeMapOfShape aDM; 
  for (TopTools_MapIteratorOfMapOfShape itMS(aMS); itMS.More(); itMS.Next()) {
    const TopoDS_Shape& OS = itMS.Key();
#ifdef MDTV_DEB_GEN
    TCollection_AsciiString aName = aNam1 + ++i + ext;      
    DbgTools_Write(OS, aName.ToCString()) ;
    Standard_Integer j=0;
#endif
    TNaming_MapOfShape aMapDM; 
    for (TNaming_NewShapeIterator itNew(OS,L); itNew.More(); itNew.Next()) 
      if (itNew.Label() == LabelOfGeneration) {
	aMapDM.Add(itNew.Shape());
	aList.Append(itNew.Shape());//szy 21.10.03
#ifdef MDTV_DEB_GEN
	TCollection_AsciiString aName = aNam2 + i +  "_" + ++j + ext;      
	DbgTools_Write(itNew.Shape(), aName.ToCString()) ;
#endif
      }
    if(aMapDM.Extent())
      aDM.Bind(OS, aMapDM);
  }

  if(aVer == -1) { //initial 
    Standard_Integer i = 1;
    TNaming_Name& aName =  aNaming->ChangeName();
    TopTools_ListIteratorOfListOfShape it(aList);
    if(!aSelection.IsNull()) {
      for(;it.More();it.Next(),i++) {
	if(it.Value().IsSame(aSelection)) {
	  B.Select(it.Value(), it.Value());
	  aName.Index(i); // for debug - index of selection in the list
	  break;
	}
      }
    } else {// Selection == Null
      for(;it.More();it.Next())
	B.Select(it.Value(), it.Value()); 
    }
  }
  else { 
    // *** Regeneration *** //
    if(aList.Extent() == 1) { // trivial case
      B.Select(aList.Last(), aList.Last()); 
    } 
    else {
      TNaming_Name& aName =  aNaming->ChangeName();
      const TopAbs_ShapeEnum aType = aName.ShapeType();
      TopTools_ListOfShape aList2; 
      TopTools_ListIteratorOfListOfShape it(aList);
      for(;it.More();it.Next()) {
	if(it.Value().ShapeType() == aType) //collect only the same type
	  aList2.Append(it.Value());
      }
      if(!aList2.Extent()) return Standard_False; // Empty

      Standard_Boolean found = Standard_False;
      //TopoDS_Shape aShape = FindShape(aList2);
      TopoDS_Shape aShape = FindShape(aDM);
#ifdef MDTV_DEB_GEN
      if(!aShape.IsNull())
	DbgTools_Write(aShape,  "G_FindShape.brep") ;
#endif
      if(!aShape.IsNull()) found = Standard_True;
#ifdef MDTV_DEB_GEN
      cout << "Generated ==>aGenerators.Extent() = " <<aGenerators.Extent() <<" aMS.Extent()= " <<aMS.Extent()<<endl;
#endif
      if(found) {
#ifdef MDTV_DEB_GEN
      cout << "Generated ==> Shape is found!" <<endl;
#endif
	TopTools_ListOfShape aLM;
	Standard_Boolean aHas = Standard_False;
	Standard_Boolean a1NB = Standard_False;
	if(aGenerators.Extent() != aMS.Extent()) { //missed generators
	  aHas = Standard_True;//has lost generatos
#ifdef MDTV_DEB_GEN
      cout << "Generated ==> has lost generatos!" <<endl;
#endif
	  for (TNaming_ListIteratorOfListOfNamedShape itg(aGenerators); itg.More(); itg.Next()) {
	    if(!aMS.Contains(itg.Value()->Get())) 
	      aLM.Append(itg.Value()->Get());
	  }
	  if(aLM.Extent() == 1) {//lost 1
	    TopTools_ListIteratorOfListOfShape itm(aLM);
	    TopoDS_Shape aSM = itm.Value(); // Missed
	    for (TopTools_MapIteratorOfMapOfShape itMS1(aMS); itMS1.More(); itMS1.Next()) {
	      const TopoDS_Shape& aS = itMS1.Key();
	      if(aSM.ShapeType() == aS.ShapeType()) {
		if(aS.ShapeType() == TopAbs_EDGE) {
		  TopoDS_Vertex aVCom;
		  if(TopExp::CommonVertex(TopoDS::Edge(aS), TopoDS::Edge(aSM), aVCom))
		    {a1NB = Standard_True; 
		     break;} //lost only 1 neigbour
		} else if(aS.ShapeType() == TopAbs_FACE) {
		  TopExp_Explorer expl1(aS, TopAbs_EDGE);
		  for(;expl1.More();expl1.Next()) {
		    TopExp_Explorer expl2(aSM, TopAbs_EDGE);
		    for(;expl2.More();expl2.Next()) {
		      if(expl1.Current().IsSame(expl2.Current()))
			{a1NB = Standard_True;
			 break;} //lost only 1 neigbour
		    }
		  }
		}
	      }
	    }
// 	    if(aShape.ShapeType() == TopAbs_VERTEX && a1NBE) {
// 	//if atleast 1 Gen was missed and the Gen is Edge
// 	      TopTools_ListIteratorOfListOfShape it(aList);
// 	      for(;it.More();it.Next()) {
// 		if(it.Value().ShapeType() == TopAbs_EDGE) {
// 		  const TopoDS_Shape& aV1 = TopExp::FirstVertex(TopoDS::Edge(it.Value()));
// 		  const TopoDS_Shape& aV2 = TopExp::LastVertex(TopoDS::Edge(it.Value()));
// 		  if(aShape.IsSame(aV1)) {aShape2 =  aV2; 	cout << "##### => V2 " <<endl;break;}
// 		  else 
// 		    if(aShape.IsSame(aV2)) {aShape2 =  aV1;	cout << "##### => V1 " <<endl;break;}
// 		}	  
// 	      }
// 	    }
	  }
	}
	if(!aHas) // all arguments were kept
	  B.Select(aShape, aShape); //only this case is correct on 100%
	else {
	  if (a1NB) //Has, but may be ...
	    B.Select(aShape, aShape); 	
	  else { 
	    // put Compound, may be if possible processed later in Sel. Driver
	    TopTools_ListIteratorOfListOfShape it1(aList2);
	    for(;it1.More();it1.Next())
	      B.Select(it1.Value(), it1.Value()); 
	  }
	}
    } else 
      {	//not found
#ifdef MDTV_DEB_GEN
	cout << "Generated ==> Shape is NOT found! Probably Compound will be built" <<endl;
#endif

	TopTools_ListIteratorOfListOfShape it2(aList2);
	for(;it2.More();it2.Next())
	  B.Select(it2.Value(), it2.Value()); 
      }
    }
  }    
  return Standard_True;
}

//=======================================================================
//function : Identity
//purpose  : Regenerates Naming attribute with Name = IDENTITY
//=======================================================================
// Name with this type must contain only one NamedShape attribute as argument. 
// Algorithm takes all last modifications of NamedShape of this argument  
// starting with this one ( see method TNaming_NamingTool::CurrentShape ). 
// Algorithm takes only NamedShapes belonging to the labels from the Valid 
// labels map (if it's not empty) and put to the resulting NamedShape as compound. 
//=======================================================================
static Standard_Boolean Identity (const TDF_Label&                L,
                                  const TDF_LabelMap&             Valid,
                                  const TNaming_ListOfNamedShape& Args,
                                  const TopAbs_ShapeEnum          ShapeType)
{
  if (Args.Extent() > 2) {
    Standard_ConstructionError::Raise("TNaming_Name::Solve");
    }
#ifdef BUC60925
  if(!ValidArgs(Args)) return Standard_False;
#endif
  const Handle(TNaming_NamedShape)& A = Args.First();
  TopTools_MapOfShape MS;
  TDF_LabelMap        Forbiden;
  TNaming_NamingTool::CurrentShape (Valid,Forbiden,A,MS);
#ifdef MDTV_DEB_SOL2
  //TCollection_AsciiString entry;
  //TDF_Tool::Entry(L, entry);
  //TDF_Tool::Entry(A->Label(), entry);
#endif  
  TNaming_Builder B(L);
  for (TopTools_MapIteratorOfMapOfShape itM(MS); itM.More(); itM.Next()) {
#ifdef OCC352
    const TopoDS_Shape& S = ShapeWithType(itM.Key(),ShapeType);
#else
    const TopoDS_Shape& S = itM.Key();
#endif
#ifdef MDTV_DEB_SOL2
    //TopAbs_Orientation Or = S.Orientation();
#endif
    B.Select(S,S);
  }
  return Standard_True;
}

//=======================================================================
//function : FilterByNeighbourgs
//purpose  : regenerated the specified shape with help of its neighbours
//=======================================================================
// result -  is a subshape of the first argument of the Name with type = 
// ShapeType of this Name, which has a common subshapes (boundaries) with 
// each neighbour - shapes from the other arguments of the Name.
//=======================================================================
static Standard_Boolean  FilterByNeighbourgs (const TDF_Label&                L,
					      const TDF_LabelMap&             Valid,
					      const TNaming_ListOfNamedShape& Args,
					      const Handle(TNaming_NamedShape)& Stop,
					      const TopAbs_ShapeEnum          ShapeType)
{  

  TNaming_Builder B(L); 

  TDF_LabelMap        Forbiden;
#ifdef BUC60925
  if(!ValidArgs(Args)) return Standard_False;
#endif
  TNaming_NamingTool::BuildDescendants (Stop, Forbiden); //all descendants of Stop (New shapes) are forbidden
  if (!Stop.IsNull())    Forbiden.Remove(Stop->Label());
  //----------------------------------------
  // First argument: collection has to be filtered.
  //----------------------------------------
  Handle(TNaming_NamedShape) Cand  = Args.First(); //collection of candidates
   
#ifdef MDTV_DEB_FNB
  Standard_Integer i = 1;
  TCollection_AsciiString aNam("Cand_");
  TCollection_AsciiString ext(".brep");
  DbgTools_WriteNSOnLabel(Cand, aNam.ToCString());  
  cout << "Cand (Args.First()) Label = ";
  PrintEntry(Cand->Label());  
  cout << "Valid Label map:" <<endl;
  PrintEntries(Valid);
#endif

  TopTools_MapOfShape    SCand;
  TNaming_NamingTool::CurrentShape  (Valid, Forbiden,Cand,SCand);//fills SCand with last modifications of Cand. CandNS should be at the same level (before) as NS of FilterByNBS

#ifdef MDTV_DEB_FNB
  TCollection_AsciiString aNam2("SCand");
  DbgTools_Write(SCand, aNam2.ToCString());  
  cout <<"SCand Extent = " << SCand.Extent() << " Expected ShapeType = " << ShapeType << endl;
#endif 

  //------------------------------------------------------------
  // Autres arguments : contiennent les voisins du bon candidat.
  // Other arguments  : contains the neighbors of the good candidate.
  //------------------------------------------------------------
  TopAbs_ShapeEnum              TC = TopAbs_EDGE;
  if (ShapeType == TopAbs_EDGE) TC = TopAbs_VERTEX;
  if (ShapeType == TopAbs_VERTEX) TC = TopAbs_VERTEX; // szy 31.03.10 - to process case when Candidate is of type Vertex
 
#ifdef MDTV_DEB_FNB
  i=1;
  aNam = "Boundaries";
#endif
  if(SCand.Extent() == 1) { // check if a collection is inside
    TopTools_MapIteratorOfMapOfShape it(SCand);
    const TopoDS_Shape& aS = it.Key();
    if(!aS.IsNull()) 
      if(aS.ShapeType() == TopAbs_COMPOUND && aS.ShapeType() != ShapeType) {
	TopoDS_Iterator itt(aS);
	for(;itt.More();itt.Next()) 
	  SCand.Add(itt.Value());      
	SCand.Remove(aS);
      }
  }
  for (TopTools_MapIteratorOfMapOfShape itCand(SCand); itCand.More(); itCand.Next()) { //1
    const TopoDS_Shape& S    = itCand.Key();
    TopTools_MapOfShape Boundaries;
    if(S.ShapeType() == TopAbs_VERTEX) //# szy 31.03.10
      Boundaries.Add (S); //#
    else  //#
      for (TopExp_Explorer exp(S,TC); exp.More(); exp.Next()) { //put boundaries of each candidate (from SCand) to the Boundaries map
	Boundaries.Add (exp.Current());
#ifdef MDTV_DEB_FNB
	TCollection_AsciiString aName = aNam + i++ + ext;      
	DbgTools_Write(exp.Current(),  aName.ToCString()) ;
#endif
      }
    
    TNaming_ListIteratorOfListOfNamedShape it(Args); 
    it.Next(); 
    Standard_Boolean Keep = 1;
#ifdef MDTV_DEB_FNB
    cout <<"Args number = " << Args.Extent() <<endl;
    i=1;
    aNam = "Boundaries";
#endif
    for ( ; it.More(); it.Next()) { //2 ==> for each Arg
      Standard_Boolean Connected = Standard_False;
      // Le candidat doit etre  connexe a au moins un shape de
      // chaque NamedShape des voisins.
      // The candidate should be connectedand and have at least one shape of NamedShape
      // of each neighbor.
      const Handle(TNaming_NamedShape)& NSVois = it.Value();  //neighbor 

#ifdef MDTV_DEB_FNB
      DbgTools_WriteNSOnLabel(NSVois, "Next_Neighbor_") ;
#endif
      
      TopTools_MapOfShape    SVois;
      TNaming_NamingTool::CurrentShape  (Valid, Forbiden,NSVois,SVois); // fills SVois with last modifications of NSVois

#ifdef MDTV_DEB_FNB
      TCollection_AsciiString aNam2("SVois");
      DbgTools_Write(SVois, aNam2.ToCString());
#endif 

      for (TopTools_MapIteratorOfMapOfShape itVois(SVois); itVois.More(); itVois.Next()) { //6
	const TopoDS_Shape& Vois = itVois.Key();
	for (TopExp_Explorer exp1(Vois,TC); exp1.More(); exp1.Next()) { //7
	  if (Boundaries.Contains(exp1.Current())) {
	    Connected = Standard_True; // has common boundaries with candidate shape
#ifdef MDTV_DEB_FNB
	    DbgTools_Write(Vois, "Neighbor_Connected.brep");
#endif
	    break;
	  }
	} //7
	if (Connected) break;
      } //6
      if (!Connected) {
	Keep = 0;
	break;
      }
    } //2
    if (Keep) {
      B.Select (S,S);
#ifdef MDTV_DEB_FNB
      DbgTools_Write(S,  "FilterByNbs_Sel.brep") ;
#endif
    }
  } //1
  return Standard_True;
}

//=======================================================================
static const TopoDS_Shape FindSubShapeInAncestor(const TopoDS_Shape& Selection, const TopoDS_Shape& Context )
{
#ifdef MDTV_DEB_OR_AG
  DbgTools_Write(Selection, "Orientation_Selection.brep");
  DbgTools_Write(Context, "Orientation_Context.brep");
  TopExp_Explorer expl1(Context, Selection.ShapeType());
  int i = 0;
  TCollection_AsciiString SS( "Orientation_Current_");
  for(;expl1.More(); expl1.Next()) {      
    if(expl1.Current().IsSame(Selection)) {
      i++;
      cout <<"FindSubShape:  = " <<expl1.Current().ShapeType() << " TS = " <<expl1.Current().TShape() << endl;
      TCollection_AsciiString nam = SS + i + ".brep";
      DbgTools_Write(expl1.Current(), nam.ToCString());	
    }
  }
#endif 
  if(Selection.ShapeType() != TopAbs_COMPOUND) {
    TopExp_Explorer anExpl(Context, Selection.ShapeType());
    for(;anExpl.More(); anExpl.Next()) {
#ifdef MDTV_DEB_OR_AG
      cout <<"FindSubShape:  = " <<anExpl.Current().ShapeType() << " TS = " <<anExpl.Current().TShape()->This() << endl;
      DbgTools_Write(anExpl.Current(), "Orientation_Current.brep");
#endif    
      if(anExpl.Current().IsSame(Selection)) 
	return anExpl.Current();
    }
  }

  return TopoDS_Shape();
}

//=======================================================================
//static Standard_Integer Count(const TopoDS_Shape& S)
//{
//  Standard_Integer N(0);
//  TopoDS_Iterator it(S);
//  for(;it.More();it.Next()) {
//    if(it.Value().ShapeType() != TopAbs_COMPOUND && it.Value().ShapeType() != TopAbs_COMPSOLID)
//      N++;
//    else {
//      N += Count(it.Value());
//    }
//  }
//  return N;
//}
//=======================================================================
static Standard_Integer Aggregation (const TopoDS_Shape& S, const TopoDS_Shape& AS, TNaming_Builder& B)
{
  Standard_Integer N(0);
  TopoDS_Iterator it(S);
  for(;it.More();it.Next()) {
    const TopoDS_Shape& sel = it.Value();
    if(sel.ShapeType() > TopAbs_COMPSOLID) {
      const TopoDS_Shape& CS = FindSubShapeInAncestor(sel, AS);
      if(!CS.IsNull()) {
	B.Select(CS, CS);
	N++;
      }
    } else 
      N += Aggregation(sel, AS, B);    
  }
  return N;
}

//==========================================================================
//function : Orientation
//purpose  : to solve  ORIENTATION name
// this function explores the second argument | arguments (Context) and 
// keeps at the label (L) the first argument (S) with the orientation it  
// has in the context. Index is used only for Seam edge recomputing 
//==========================================================================
static Standard_Boolean ORientation (const TDF_Label&                L,
				     const TDF_LabelMap&             Valid,
				     const TNaming_ListOfNamedShape& Args,
				     const Handle(TNaming_NamedShape)& Stop,
				     const Standard_Integer          Index)
{

  if(!ValidArgs(Args)) return Standard_False;

  const Handle(TNaming_NamedShape)& A = Args.First();
  TopTools_MapOfShape MS; 
  TDF_LabelMap        Forbiden;
  TNaming_NamingTool::BuildDescendants (Stop, Forbiden);
  TNaming_NamingTool::CurrentShape (Valid,Forbiden,A,MS);

  TopoDS_Shape S; 
  Standard_Boolean isSplit(Standard_False);
  if (!MS.IsEmpty ()) {
    TopTools_MapIteratorOfMapOfShape it(MS);
    if (MS.Extent() == 1) {
      S = it.Key(); 
    } 
    else {
      isSplit = Standard_True;
      S = MakeShape(MS);
#ifdef MDTV_DEB_OR
      for(Standard_Integer i=1;it.More();it.Next(), i++) {
	TCollection_AsciiString aNam("OR_Selection_");
	TCollection_AsciiString aName = aNam + i + ".brep";
	DbgTools_Write(it.Key(), aName.ToCString());
      }
#endif
    }
  }

  TNaming_Builder B(L);
  if(S.IsNull()) 
    return Standard_False;
#ifdef MDTV_DEB_OR
  DbgTools_Write(S, "Orientation_S.brep");
#endif

  TopTools_ListOfShape aSList;
  // tmp. solution
  if(S.ShapeType() == TopAbs_COMPOUND && !isSplit) {
    TopoDS_Iterator it(S);
    for(;it.More();it.Next())
      aSList.Append(it.Value());
  } //
 
  TopTools_MapOfShape MSC; 
  if(aSList.Extent() == 0) {
    const Handle(TNaming_NamedShape)& Anc = Args.Last();
#ifdef MDTV_DEB_OR
    cout << "### ORIENTATION: Ancestor ";
    PrintEntry(Anc->Label());
#endif
    MSC.Clear();
    TNaming_NamingTool::CurrentShape (Valid,Forbiden,Anc,MSC);
    if(MSC.Extent() == 1) {
      for (TopTools_MapIteratorOfMapOfShape itM(MSC); itM.More(); itM.Next()) {
	const TopoDS_Shape& AS = itM.Key(); 
// <=== start 21.10.2009
	TopoDS_Shape CS;
	if(Index > 0) { //only for seam edge
	  TopoDS_Iterator itw(AS);
	  for(;itw.More();itw.Next()) {
	    Standard_Boolean found(Standard_False);
	    TopoDS_Iterator it(itw.Value());
	    for(int i=1;it.More();it.Next(),i++) {
	      if(i == Index && it.Value().IsSame(S)) {
		CS = it.Value();
		found = Standard_True;
#ifdef MDTV_DEB_OR
		cout << "ORIENTATION => ORDER = " << i <<endl;
#endif
		break;
	      }
	    }
	    if(found) break;
	  }
	} else
	  CS =  FindSubShapeInAncestor(S, AS);
// <=== end 21.10.2009
#ifdef MDTV_DEB_OR
	cout << "ORIENTATION: Selection" <<" TShape = " <<CS.TShape() <<" Orientation = " << CS.Orientation() <<endl;
	cout << "ORIENTATION: Context " << "ShapeType = "<<AS.ShapeType() << " TShape = " <<AS.TShape() <<endl;
	DbgTools_Write(AS, "Orientation_Cnt.brep");
#endif
	if(!CS.IsNull()) {
	  B.Select(CS, CS);
	} else {
	  if(!Aggregation(S, AS, B)) 
	    return Standard_False;        
	}
      }  
    } else {
      const TopoDS_Shape  AS = MakeShape(MSC);
      const TopoDS_Shape& CS =  FindSubShapeInAncestor(S, AS);
      if(!CS.IsNull()) {
	B.Select(CS, CS);
      }  else {
	if(!Aggregation(S, AS, B)) 
	  return Standard_False;        
      }
    }
  } else {
    TNaming_ListIteratorOfListOfNamedShape it(Args); 
    it.Next(); //skip first

    // temporary solution. To be optimized (+ has connection with Union name)
    Handle(TopTools_HArray2OfShape) Arr; // Arr(1,1) - selection; Arr(1,2) - Context shape
    Arr = new TopTools_HArray2OfShape (1, aSList.Extent(), 1, 2);
    TopTools_ListIteratorOfListOfShape it1(aSList);
    Standard_Integer i = 1;
    for(; it1.More(); it1.Next(), it.Next(), i++) {
      Arr->SetValue(i, 1, it1.Value());
      MSC.Clear();
      TNaming_NamingTool::CurrentShape (Valid,Forbiden,it.Value(),MSC);
      if(MSC.Extent() == 1) {
	for (TopTools_MapIteratorOfMapOfShape itM(MSC); itM.More(); itM.Next()) {
	  const TopoDS_Shape& AS = itM.Key(); 
	  Arr->SetValue(i, 2, AS);
	}
      } else {
	const TopoDS_Shape  AS = MakeShape(MSC);
	Arr->SetValue(i, 2, AS);
      }
    } 
    
    if(aSList.Extent() == 1) {
      const TopoDS_Shape& S = Arr->Value(1,1);
      if(S.ShapeType() != TopAbs_COMPOUND) {	    
	const TopoDS_Shape& CS =  FindSubShapeInAncestor(S, Arr->Value(1,2));
	if(!CS.IsNull()) {
	  B.Select(CS, CS);
	} else 
	  return Standard_False;
      } 
      else {
#ifdef MDTV_DEB_OR
	DbgTools_Write(Arr->Value(1,2), "Ancestor.brep");
#endif
	if(!Aggregation(S, Arr->Value(1,2), B)) { 
	  return Standard_False;
	}
      }
    }
    else { // > 1   
      for(Standard_Integer i = Arr->LowerRow();i <= Arr->UpperRow();i++) {
	const TopoDS_Shape& S = Arr->Value(i,1);
	const TopoDS_Shape& AC = Arr->Value(i,2);
	if(S.ShapeType() != TopAbs_COMPOUND) {	    
	  const TopoDS_Shape& CS =  FindSubShapeInAncestor(S, AC);
	  if(!CS.IsNull()) {
	    B.Select(CS, CS);
	  } else 
	    return Standard_False;
	}
	else {
#ifdef MDTV_DEB_OR
	  DbgTools_Write(AC, "Aggregation.brep");
#endif
	  if(!Aggregation(S, AC, B)) { 
	    return Standard_False;
	  }
	}
      }
    }
  } // end of tmp. solution 

  return Standard_True;
}

//===========================================================================
//function : WireIN
//purpose  : to solve  WIREIN name; Index for case if the Face has several wires
//=======================================================================
static Standard_Boolean WireIN(const TDF_Label&                L,
			       const TDF_LabelMap&             Valid,
			       const TNaming_ListOfNamedShape& Args,
			       const Standard_Integer          Index)
{
  Standard_Boolean aResult(Standard_False);
  if(!ValidArgs(Args)) return aResult;
  TopTools_MapOfShape MS; 
  TDF_LabelMap        Forbiden;
  if (Args.Extent() != 1 ) 
    Standard_ConstructionError::Raise("TNaming_Name::Solve"); 
  const Handle(TNaming_NamedShape)& A = Args.Last(); 
  TNaming_NamingTool::CurrentShape (Valid,Forbiden,A,MS);
#ifdef MDTV_DEB_WIN
  cout <<"MS Extent = " <<MS.Extent() <<endl;
#endif
  Standard_Integer indx(0), num(0);
  if(Index > 0) {
    indx = Index & 0x000000FF;
    num  = (Index & 0x0000FF00) >> 8;
#ifdef MDTV_DEB_WIN
    cout <<"Kept indx = " << indx  <<" maxNum" << num << endl;
#endif      
  }
  TNaming_Builder B(L);
  for (TopTools_MapIteratorOfMapOfShape itM(MS); itM.More(); itM.Next()) {
    const TopoDS_Shape& S = itM.Key()	;
#ifdef MDTV_DEB_WIN
    if(!S.IsNull()) {
      DbgTools_Write(S, "WireIN_S.brep");
      cout <<"WIREIN: ShapeType = " << S.ShapeType() << " TS = " << S.TShape()->This() <<endl;
    }
#endif
    Standard_Integer aNum(0), aCase(0);
    TopoDS_Iterator it2(S);
    for (;it2.More();it2.Next()) aNum++;      
    if(Index > 0) {
      if(num == aNum) aCase = 1;//exact solution
      else if(aNum == 1)   aCase = 2;// possible merge of initial wires
      else aCase = 3; // indefinite description ==> compound which can include expected wire
    }
    
    Standard_Integer i(0);
    for (it2.Initialize(S);it2.More();it2.Next()) {
#ifdef MDTV_DEB_WIN
      if(!it2.Value().IsNull()) {
	DbgTools_Write(it2.Value(), "WireIN_it2Value.brep");
	cout <<"WIREIN: ShapeType = " << it2.Value().ShapeType() << " TS = " << it2.Value().TShape()->This() <<endl;
      }
#endif
      i++;
      if(it2.Value().ShapeType() == TopAbs_WIRE) {
	if(Index > 0 ) { //szy 26/03/10
	  if(aCase == 1) {
	    if(i == indx) {
	      aResult  = Standard_True;
	      B.Select(it2.Value(),it2.Value());
	      break;
	    }
	  } else {
	    B.Select(it2.Value(),it2.Value());
	    aResult = Standard_True;
	  }
	}
	else {
	  B.Select(it2.Value(),it2.Value());
	  aResult = Standard_True;
	}
      }
    }
  }
  return aResult;
}
#ifdef DEB
//=======================================================================
static  Standard_CString NameTypeToString (const TNaming_NameType Type)
{
  switch(Type)
    {
    case  TNaming_UNKNOWN             : return "UNKNOWN";
    case  TNaming_IDENTITY            : return "IDENTITY";
    case  TNaming_MODIFUNTIL          : return "MODIFUNTIL";
    case  TNaming_GENERATION          : return "GENERATION";
    case  TNaming_INTERSECTION        : return "INTERSECTION";
    case  TNaming_UNION               : return "UNION";
    case  TNaming_SUBSTRACTION        : return "SUBSTRACTION";
    case  TNaming_CONSTSHAPE          : return "CONSTSHAPE";
    case  TNaming_FILTERBYNEIGHBOURGS : return "FILTERBYNEIGHBOURGS";
    case  TNaming_ORIENTATION         : return "ORIENTATION";
    case  TNaming_WIREIN              : return "WIREIN";
      default :
        Standard_DomainError::Raise("TNaming_NameType; enum term unknown ");
    }
  return "";
}
#endif
//=======================================================================
//function : Solve
//purpose  : 
//=======================================================================

Standard_Boolean TNaming_Name::Solve(const TDF_Label&    aLab,
				     const TDF_LabelMap& Valid) const
{
  Standard_Boolean Done = 0;
  try {
  switch (myType) {
  case TNaming_UNKNOWN :
    {
      break;
    }  
  case TNaming_IDENTITY :
    {  
      Done = Identity(aLab,Valid,myArgs,myShapeType); 
      break;
    }
  case TNaming_MODIFUNTIL:
    {
      Done = ModifUntil (aLab,Valid,myArgs,myStop);
      break;
    }
  case TNaming_GENERATION:
    {
      Done = Generated (aLab,Valid,myArgs);
      break;
    }
  case TNaming_INTERSECTION:
    {
      Done = Intersection (aLab,Valid,myArgs,myStop,myShapeType,myIndex); 
      break;
    }
  case TNaming_UNION:
    {
      Done = Union (aLab,Valid,myArgs,myStop,myShapeType, myContextLabel);
      break;
    }
  case TNaming_SUBSTRACTION: 
    {
      Standard_NotImplemented::Raise();
//      Done = Substraction (aLab,Valid,myArgs);
      break;
    }
  case TNaming_CONSTSHAPE:
    {
      Done = ConstShape (aLab,Valid,myArgs,myStop,myIndex);
      break;
    }
  case TNaming_FILTERBYNEIGHBOURGS:
    {
      Done = FilterByNeighbourgs (aLab,Valid,myArgs,myStop,myShapeType);
      break;
    }
  case TNaming_ORIENTATION: 
    {
      Done = ORientation (aLab,Valid,myArgs,myStop,myIndex);
      break;
    }
  case TNaming_WIREIN: 
    {
      Done = WireIN (aLab,Valid,myArgs,myIndex);
      break;
    }
  }
} catch (...) {
#ifdef DEB  
  cout << "Name::Solve: EXCEPTION==> NameType = " << NameTypeToString(myType) << "  ";
  PrintEntry(aLab);
#endif
}
  return Done;
}

//=======================================================================
//function : ContextLabel
//purpose  : Set
//=======================================================================

void TNaming_Name::ContextLabel(const TDF_Label& theLabel)
{
  myContextLabel = theLabel;
}

//=======================================================================
//function : ContextLabel
//purpose  : Get
//=======================================================================

const TDF_Label&  TNaming_Name::ContextLabel() const
{ 
  return myContextLabel;
}
/*
//=======================================================================
//function : Orientation
//purpose  : Set
//=======================================================================

void TNaming_Name::Orientation(const Standard_Boolean theOrientation)
{
  myOrientation = theOrientation;
}

//=======================================================================
//function : ContextLabel
//purpose  : Get
//=======================================================================

const Standard_Boolean TNaming_Name::Orientation() const
{ 
  return myOrientation;
}
*/
