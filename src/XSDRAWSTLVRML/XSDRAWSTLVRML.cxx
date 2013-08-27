// Created on: 2000-05-30
// Created by: Sergey MOZOKHIN
// Copyright (c) 2000-2012 OPEN CASCADE SAS
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



#include <XSDRAWSTLVRML.ixx>
#include <Draw_Interpretor.hxx>
#include <TopoDS_Shape.hxx>
#include <VrmlAPI.hxx>
#include <OSD_Path.hxx>
#include <StlAPI.hxx>
#include <XSDRAW.hxx>
#include <DBRep.hxx>
#include <VrmlAPI_Writer.hxx>
#include <Quantity_Color.hxx>
#include <Quantity_HArray1OfColor.hxx>
#include <StlAPI_Writer.hxx>
#include <Draw_PluginMacro.hxx>
#include <SWDRAW.hxx>
#include <XSDRAW.hxx>
#include <XSDRAWSTEP.hxx>
#include <XSDRAWIGES.hxx>
#include <AIS_InteractiveContext.hxx>
#include <ViewerTest.hxx>
#include <Draw.hxx>
#include <Draw_ProgressIndicator.hxx>
#include <RWStl.hxx>
#include <Quantity_Color.hxx>
#include <V3d_View.hxx>
#include <TCollection_AsciiString.hxx>

#include <SelectMgr_SelectionManager.hxx>
#include <StdSelect_ViewerSelector3d.hxx>

#include <Aspect_TypeOfMarker.hxx>
#include <Graphic3d_MaterialAspect.hxx>

#include <StlMesh_Mesh.hxx>
#include <StlMesh_SequenceOfMeshTriangle.hxx>

#include <MeshVS_Mesh.hxx>
#include <MeshVS_MeshPrsBuilder.hxx>
#include <MeshVS_TextPrsBuilder.hxx>
#include <MeshVS_Drawer.hxx>
#include <MeshVS_DrawerAttribute.hxx>
#include <MeshVS_MeshEntityOwner.hxx>
#include <MeshVS_DataMapOfIntegerAsciiString.hxx>

#include <XSDRAWSTLVRML_DataSource.hxx>
#include <XSDRAWSTLVRML_DrawableMesh.hxx>
#include <MeshVS_NodalColorPrsBuilder.hxx>
#include <MeshVS_ElementalColorPrsBuilder.hxx>
#include <Quantity_NameOfColor.hxx>
#include <TColgp_SequenceOfXYZ.hxx>
#include <TColStd_HPackedMapOfInteger.hxx>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hxx>
#include <Standard_ErrorHandler.hxx>
#include <VrmlData_Scene.hxx>
#include <VrmlData_ShapeConvert.hxx>
#include <VrmlData_DataMapOfShapeAppearance.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <Bnd_Box.hxx>

// avoid warnings on 'extern "C"' functions returning C++ classes
#ifdef _MSC_VER
#pragma warning(4:4190)
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

static Standard_Integer writestl
(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 3 || argc > 5) {
	di << "Use: " << argv[0] 
	<< " shape file [ascii/binary (0/1) : 1 by default] [InParallel (0/1) : 0 by default]" << "\n";
  } else {
    TopoDS_Shape aShape = DBRep::Get(argv[1]);
    Standard_Boolean isASCIIMode = Standard_False;
	Standard_Boolean isInParallel = Standard_False;
    if (argc > 3) {
      isASCIIMode = (Draw::Atoi(argv[3]) == 0);
      if (argc > 4) {
        isInParallel = (Draw::Atoi(argv[4]) == 1);
        Standard::SetReentrant(isInParallel);
      }
    }
    StlAPI_Writer aWriter;
    aWriter.ASCIIMode() = isASCIIMode;
    aWriter.Write (aShape, argv[2], isInParallel);
  }
  return 0;
}

static Standard_Integer readstl
(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc<3) di << "wrong number of parameters"    << "\n";
  else {
    TopoDS_Shape shape ;
    StlAPI::Read(shape,argv[2]);
    DBRep::Set(argv[1],shape);
  }
  return 0;
}

static Standard_Integer writevrml
(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc<3) di << "wrong number of parameters"    << "\n";
  else {
    TopoDS_Shape shape = DBRep::Get(argv[1]);
    //     VrmlAPI_Writer writer;
    //     writer.SetTransparencyToMaterial(writer.GetFrontMaterial(),0.0);
    //      Quantity_Color color;
    //      color.SetValues(Quantity_NOC_GOLD);
    //      Handle(Quantity_HArray1OfColor) Col = new Quantity_HArray1OfColor(1,1);
    //      Col->SetValue(1,color);
    //      writer.SetDiffuseColorToMaterial(writer.GetFrontMaterial(),Col);
    //      writer.SetRepresentation(VrmlAPI_ShadedRepresentation);
    //      writer.SetDeflection(0.01);
    //      writer.Write(shape, argv[2]);
    VrmlAPI::Write(shape, argv[2]);
  }
  return 0;
}

//=======================================================================
//function : loadvrml
//purpose  :
//=======================================================================

static Standard_Integer loadvrml
(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc<3) di << "wrong number of parameters"    << "\n";
  else {
    TopoDS_Shape shape ;
    VrmlData_DataMapOfShapeAppearance ShapeAppMap;

    //-----------------------------------------------------------
    filebuf fic;
    istream aStream (&fic);

    if (fic.open(argv[2], ios::in)) {

      VrmlData_Scene aScene;

      aScene.SetVrmlDir (".");
      aScene << aStream;
      const char * aStr = 0L;
      switch (aScene.Status()) {

      case VrmlData_StatusOK:
        {
          shape = aScene.GetShape(ShapeAppMap);
          break;
        }
      case VrmlData_EmptyData:          aStr = "EmptyData"; break;
      case VrmlData_UnrecoverableError: aStr = "UnrecoverableError"; break;
      case VrmlData_GeneralError:       aStr = "GeneralError"; break;
      case VrmlData_EndOfFile:          aStr = "EndOfFile"; break;
      case VrmlData_NotVrmlFile:        aStr = "NotVrmlFile"; break;
      case VrmlData_CannotOpenFile:     aStr = "CannotOpenFile"; break;
      case VrmlData_VrmlFormatError:    aStr = "VrmlFormatError"; break;
      case VrmlData_NumericInputError:  aStr = "NumericInputError"; break;
      case VrmlData_IrrelevantNumber:   aStr = "IrrelevantNumber"; break;
      case VrmlData_BooleanInputError:  aStr = "BooleanInputError"; break;
      case VrmlData_StringInputError:   aStr = "StringInputError"; break;
      case VrmlData_NodeNameUnknown:    aStr = "NodeNameUnknown"; break;
      case VrmlData_NonPositiveSize:    aStr = "NonPositiveSize"; break;
      case VrmlData_ReadUnknownNode:    aStr = "ReadUnknownNode"; break;
      case VrmlData_NonSupportedFeature:aStr = "NonSupportedFeature"; break;
      default: /* Do nothing */ break;
      }
      if (aStr) {
        di << " ++ VRML Error: " << aStr << " in line "
          << aScene.GetLineError() << "\n";
      }
      else {
        DBRep::Set(argv[1],shape);
      }
    }
    else {
      di << "cannot open file" << "\n";
    }


    //-----------------------------------------------------------
  }
  return 0;
}

//=======================================================================
//function : storevrml
//purpose  :
//=======================================================================

static Standard_Integer storevrml
(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 4) {
    di << "wrong number of parameters"    << "\n";
    di << "use: storevrml shape file defl type_of_conversion (0, 1, 2)"    << "\n";
  }
  else {
    TopoDS_Shape shape = DBRep::Get(argv[1]);
    Standard_Real defl = Draw::Atof(argv[3]);
    Standard_Integer type = 1;
    if(argc > 4) type = Draw::Atoi(argv[4]);
    type = Max(0, type);
    type = Min(2, type);

    Standard_Boolean ExtFace = Standard_False;
    if(type == 0 || type == 2) ExtFace = Standard_True;
    Standard_Boolean ExtEdge = Standard_False;
    if(type == 1 || type == 2) ExtEdge = Standard_True;

    VrmlData_Scene aScene;
    VrmlData_ShapeConvert Conv(aScene);
    Conv.AddShape(shape);
    Conv.Convert(ExtFace, ExtEdge, defl);

    filebuf foc;
    ostream outStream (&foc);
    if (foc.open (argv[2], ios::out))
      outStream << aScene;
  }
  return 0;
}


//-----------------------------------------------------------------------------
static Standard_Integer createmesh
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{

  if (argc<3)
  {
    di << "Use: " << argv[0] << " <mesh name> <stl file>" << "\n";
    return 1;
  }

  // Progress indicator
  OSD_Path aFile( argv[2] );
  Handle(Draw_ProgressIndicator) aProgress = new Draw_ProgressIndicator (di, 1);
  Handle(StlMesh_Mesh) aSTLMesh = RWStl::ReadFile (aFile, aProgress);

  di << "Reading OK..." << "\n";
  Handle( XSDRAWSTLVRML_DataSource ) aDS = new XSDRAWSTLVRML_DataSource( aSTLMesh );
  di << "Data source is created successful" << "\n";
  Handle( MeshVS_Mesh ) aMesh = new MeshVS_Mesh();
  di << "MeshVS_Mesh is created successful" << "\n";

  aMesh->SetDataSource( aDS );
  aMesh->AddBuilder( new MeshVS_MeshPrsBuilder( aMesh.operator->() ), Standard_True );
  // Prepare triangle labels
  MeshVS_DataMapOfIntegerAsciiString aLabels;
  Standard_Integer anIndex = 1, aLen = aSTLMesh->Triangles().Length();
  for ( ; anIndex <= aLen; anIndex++ ){
    aLabels.Bind( anIndex, TCollection_AsciiString( anIndex ) );
  }

  Handle(MeshVS_TextPrsBuilder) aTextBuilder = new MeshVS_TextPrsBuilder( aMesh.operator->(), 20., Quantity_NOC_YELLOW );
  aTextBuilder->SetTexts( Standard_True, aLabels );
  aMesh->AddBuilder( aTextBuilder );

  // Hide all nodes by default
  Handle(TColStd_HPackedMapOfInteger) aNodes = new TColStd_HPackedMapOfInteger();
  aLen = aSTLMesh->Vertices().Length();
  for ( anIndex = 1; anIndex <= aLen; anIndex++ )
    aNodes->ChangeMap().Add( anIndex );
  aMesh->SetHiddenNodes( aNodes );

  Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();

  if ( aContext.IsNull() )
  {
    ViewerTest::ViewerInit();
    //To create a 3D view if it doesn't exist
    aContext = ViewerTest::GetAISContext();
    if( aContext.IsNull() )
    {
      di << "Cannot create 3D view" << "\n";
      return 0;
    }
  }

  aContext->Display( aMesh );
  aContext->Deactivate( aMesh );

  Draw::Set( argv[1], new XSDRAWSTLVRML_DrawableMesh( aMesh ) );
  Handle( V3d_View ) V = ViewerTest::CurrentView();
  if ( !V.IsNull() )
    V->FitAll();

  return 0;
}
//-----------------------------------------------------------------------------
Handle( MeshVS_Mesh ) getMesh( const char* name, Draw_Interpretor& di)
{
  Handle( XSDRAWSTLVRML_DrawableMesh ) aDrawMesh =
    Handle( XSDRAWSTLVRML_DrawableMesh )::DownCast( Draw::Get( name ) );

  if( aDrawMesh.IsNull() )
  {
    di << "There is no such object" << "\n";
    return NULL;
  }
  else
  {
    Handle( MeshVS_Mesh ) aMesh = aDrawMesh->GetMesh();
    if( aMesh.IsNull() )
    {
      di << "There is invalid mesh" << "\n";
      return NULL;
    }
    else
      return aMesh;
  }
}
//-----------------------------------------------------------------------------
static Standard_Integer meshdm
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<3)
    di << "wrong number of parameters" << "\n";
  else
  {
    Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
    if( !aMesh.IsNull() )
    {
      Standard_Integer DisplayMode = Draw::Atoi (argv[2]);

      Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();

      if( aContext.IsNull() )
        di << "The context is null" << "\n";
      else
      {
        Standard_Boolean HasLocal = aContext->HasOpenedContext();
        if( HasLocal )
          aContext->CloseLocalContext();

        aContext->SetDisplayMode( aMesh, DisplayMode );
        di << "Setting display mode: " << DisplayMode << "\n";

        if( HasLocal )
          aContext->OpenLocalContext();
      }
    }
  }
  return 0;
}
//-----------------------------------------------------------------------------
static Standard_Integer meshsm
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<3)
    di << "wrong number of parameters" << "\n";
  else
  {
    Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
    if( !aMesh.IsNull() )
    {
      Standard_Integer SelMode = Draw::Atoi (argv[2]);

      Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();

      if( aContext.IsNull() )
        di << "The context is null" << "\n";
      else
      {
        if( !aContext->HasOpenedContext() )
          aContext->OpenLocalContext();

        aContext->Load( aMesh, -1 );

        if( SelMode==-1 )
          aContext->CloseAllContexts();

        else if( SelMode==0 )
          aContext->Activate( aMesh, 0 );

        else if( SelMode>0 )
        {
          aContext->Deactivate( aMesh, 0 );

          if( SelMode & 1 )
            aContext->Activate( aMesh, 1 );
          else
            aContext->Deactivate( aMesh, 1 );

          if( SelMode & 4 )
            aContext->Activate( aMesh, 4 );
          else
            aContext->Deactivate( aMesh, 4 );

          if( SelMode & 8 )
            aContext->Activate( aMesh, 8 );
          else
            aContext->Deactivate( aMesh, 8 );
        }

        di << "Setting selection mode: " << SelMode << "\n";
      }
    }
  }
  return 0;
}
//-----------------------------------------------------------------------------
static Standard_Integer setcolor
(Draw_Interpretor& di, Standard_Integer argc, const char** argv, Standard_Integer Param )
{
  if (argc<5)
    di << "wrong number of parameters" << "\n";
  else
  {
    Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
    if( !aMesh.IsNull() )
    {
      Standard_Real r = Draw::Atof (argv[2]);
      Standard_Real g = Draw::Atof (argv[3]);
      Standard_Real b = Draw::Atof (argv[4]);
      aMesh->GetDrawer()->SetColor( (MeshVS_DrawerAttribute)Param, Quantity_Color( r, g, b, Quantity_TOC_RGB ) );

      Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();

      if( aContext.IsNull() )
        di << "The context is null" << "\n";
      else
        aContext->Redisplay( aMesh );
    }
  }
  return 0;
}
//-----------------------------------------------------------------------------
static Standard_Integer meshcolor
(Draw_Interpretor& interp, Standard_Integer argc, const char** argv )
{
  return setcolor( interp, argc, argv, MeshVS_DA_InteriorColor );
}
//-----------------------------------------------------------------------------
static Standard_Integer linecolor
(Draw_Interpretor& interp, Standard_Integer argc, const char** argv )
{
  return setcolor( interp, argc, argv, MeshVS_DA_EdgeColor );
}
//-----------------------------------------------------------------------------
static Standard_Integer meshmat
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<3)
    di << "wrong number of parameters" << "\n";
  else
  {
    Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
    if( !aMesh.IsNull() )
    {
      Standard_Integer mat = Draw::Atoi (argv[2]);

      Graphic3d_MaterialAspect aMatAsp =
        (Graphic3d_MaterialAspect)(Graphic3d_NameOfMaterial)mat;

      aMesh->GetDrawer()->SetMaterial( MeshVS_DA_FrontMaterial, aMatAsp );
      aMesh->GetDrawer()->SetMaterial( MeshVS_DA_BackMaterial, aMatAsp );

      Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();

      if( aContext.IsNull() )
        di << "The context is null" << "\n";
      else
        aContext->Redisplay( aMesh );
    }
  }
  return 0;
}
//-----------------------------------------------------------------------------
static Standard_Integer shrink
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<3)
    di << "wrong number of parameters" << "\n";
  else
  {
    Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
    if( !aMesh.IsNull() )
    {
      Standard_Real sh = Draw::Atof (argv[2]);
      aMesh->GetDrawer()->SetDouble( MeshVS_DA_ShrinkCoeff, sh );

      Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();

      if( aContext.IsNull() )
        di << "The context is null" << "\n";
      else
        aContext->Redisplay( aMesh );
    }
  }
  return 0;
}
//-----------------------------------------------------------------------------

static Standard_Integer mdisplay
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<2)
    di << "wrong number of parameters" << "\n";
  else
  {
    Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
    if( !aMesh.IsNull() )
    {
      Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();

      if( aContext.IsNull() )
        di << "The context is null" << "\n";
      else
      {
        if( aContext->HasOpenedContext() )
          aContext->CloseLocalContext();

        aContext->Display( aMesh );
      }
    }
  }
  return 0;
}
//-----------------------------------------------------------------------------
static Standard_Integer merase
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<2)
    di << "wrong number of parameters" << "\n";
  else
  {
    Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
    if( !aMesh.IsNull() )
    {
      Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();

      if( aContext.IsNull() )
        di << "The context is null" << "\n";
      else
      {
        if( aContext->HasOpenedContext() )
          aContext->CloseLocalContext();

        aContext->Erase( aMesh );
      }
    }
    else
      di << "Mesh is null" << "\n";
  }
  return 0;
}
//-----------------------------------------------------------------------------
static Standard_Integer hidesel
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<1)
  {
    di << "wrong number of parameters" << "\n";
    return 0;
  }


  Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();
  Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
  if( aMesh.IsNull() )
  {
    di << "The mesh is invalid" << "\n";
    return 0;
  }

  if( aContext.IsNull() )
    di << "The context is null" << "\n";
  else
  {
    Handle(TColStd_HPackedMapOfInteger) aHiddenNodes = aMesh->GetHiddenNodes();
    Handle(TColStd_HPackedMapOfInteger) aHiddenElements = aMesh->GetHiddenElems();
    for( aContext->InitSelected(); aContext->MoreSelected(); aContext->NextSelected() )
    {
      Handle( MeshVS_MeshEntityOwner ) anOwner =
        Handle( MeshVS_MeshEntityOwner )::DownCast( aContext->SelectedOwner() );
      if( !anOwner.IsNull() ) {
        if( anOwner->Type()==MeshVS_ET_Node )
          aHiddenNodes->ChangeMap().Add( anOwner->ID() );
        else
          aHiddenElements->ChangeMap().Add( anOwner->ID() );
      }
    }
    aContext->ClearSelected();
    aMesh->SetHiddenNodes( aHiddenNodes );
    aMesh->SetHiddenElems( aHiddenElements );
    aContext->Redisplay( aMesh );
  }

  return 0;
}
//-----------------------------------------------------------------------------
static Standard_Integer showonly
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<1)
  {
    di << "wrong number of parameters" << "\n";
    return 0;
  }


  Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();
  Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
  if( aMesh.IsNull() )
  {
    di << "The mesh is invalid" << "\n";
    return 0;
  }

  if( aContext.IsNull() )
    di << "The context is null" << "\n";
  else
  {
    Handle(TColStd_HPackedMapOfInteger) aHiddenNodes =
      new TColStd_HPackedMapOfInteger(aMesh->GetDataSource()->GetAllNodes());
    Handle(TColStd_HPackedMapOfInteger) aHiddenElements =
      new TColStd_HPackedMapOfInteger(aMesh->GetDataSource()->GetAllElements());
    for( aContext->InitSelected(); aContext->MoreSelected(); aContext->NextSelected() )
    {
      Handle( MeshVS_MeshEntityOwner ) anOwner =
        Handle( MeshVS_MeshEntityOwner )::DownCast( aContext->SelectedOwner() );
      if( !anOwner.IsNull() ) {
        if( anOwner->Type()==MeshVS_ET_Node )
          aHiddenNodes->ChangeMap().Remove( anOwner->ID() );
        else
          aHiddenElements->ChangeMap().Remove( anOwner->ID() );
      }
    }
    aMesh->SetHiddenNodes( aHiddenNodes );
    aMesh->SetHiddenElems( aHiddenElements );
    aContext->Redisplay( aMesh );
  }

  return 0;
}
//-----------------------------------------------------------------------------
static Standard_Integer showall
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<1)
  {
    di << "wrong number of parameters" << "\n";
    return 0;
  }

  Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();
  Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );
  if( aMesh.IsNull() )
  {
    di << "The mesh is invalid" << "\n";
    return 0;
  }

  if( aContext.IsNull() )
    di << "The context is null" << "\n";
  else
  {
    aMesh->SetHiddenNodes( 0 );
    aMesh->SetHiddenElems( 0 );
    aContext->Redisplay( aMesh );
  }

  return 0;
}
//-----------------------------------------------------------------------------
static Standard_Integer delmesh
(Draw_Interpretor& di, Standard_Integer argc, const char** argv )
{
  if (argc<2)
  {
    di << "wrong number of parameters" << "\n";
    return 0;
  }

  Handle( MeshVS_Mesh ) aMesh = getMesh( argv[1], di );

  if( aMesh.IsNull() )
  {
    di << "The mesh is invalid" << "\n";
    return 0;
  }
  else
  {
    Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();

    aContext->ClearSelected();

    if( aContext->HasOpenedContext() )
      aContext->CloseAllContexts();

    aContext->Remove( aMesh );
    aContext->SelectionManager()->Remove( aMesh );
    aMesh->ClearSelections();
    aContext->MainSelector()->Clear();

    Draw::Set( argv[1], Handle(XSDRAWSTLVRML_DrawableMesh)() );

    Standard::Purge();
  }
  return 0;
}
//-----------------------------------------------------------------------------

static Standard_Integer meshcolors( Draw_Interpretor& di,
                                    Standard_Integer argc,
                                    const char** argv )
{
  try
  {
    OCC_CATCH_SIGNALS
      if ( argc < 2 )
      {
        di << "Use : meshcolors meshname mode isreflect" << "\n";
        di << "mode : {elem1|elem2|nodal|nodaltex|none}"<< "\n";
        di << "       elem1 - different color for each element" << "\n";
        di << "       elem2 - one color for one side"<<"\n";
        di << "       nodal - different color for each node"<< "\n";
        di << "       nodaltex - different color for each node with texture interpolation"<< "\n";
        di << "       none  - clear"<< "\n";
        di << "isreflect : {0|1} "<< "\n";

        return 0;
      }

      Handle( MeshVS_Mesh ) aMesh = getMesh( argv[ 1 ], di );

      if ( aMesh.IsNull() )
      {
        di << "Mesh not found" << "\n";
        return 0;
      }
      Handle(AIS_InteractiveContext) anIC = ViewerTest::GetAISContext();
      if ( anIC.IsNull() )
      {
        di << "The context is null" << "\n";
        return 0;
      }
      if( !aMesh.IsNull() )
      {
        TCollection_AsciiString aMode = TCollection_AsciiString (argv[2]);
        Quantity_Color aColor1( (Quantity_NameOfColor)( Quantity_NOC_BLUE1 ) );
        Quantity_Color aColor2( (Quantity_NameOfColor)( Quantity_NOC_RED1 ) );
        if( aMode.IsEqual("elem1") || aMode.IsEqual("elem2") || aMode.IsEqual("nodal") || aMode.IsEqual("nodaltex") || aMode.IsEqual("none") )
        {
          Handle(MeshVS_PrsBuilder) aTempBuilder;
          Standard_Integer reflection = Draw::Atoi(argv[3]);

          for (int count = 0 ; count < aMesh->GetBuildersCount(); count++ ){
            aTempBuilder = Handle(MeshVS_PrsBuilder)::DownCast(aMesh->FindBuilder("MeshVS_ElementalColorPrsBuilder"));
            if( !aTempBuilder.IsNull())
              aMesh->RemoveBuilderById(aTempBuilder->GetId());

            aTempBuilder = Handle(MeshVS_PrsBuilder)::DownCast(aMesh->FindBuilder("MeshVS_NodalColorPrsBuilder"));
            if( !aTempBuilder.IsNull())
              aMesh->RemoveBuilderById(aTempBuilder->GetId());
          }

          if( aMode.IsEqual("elem1") || aMode.IsEqual("elem2") )
          {
            Handle(MeshVS_ElementalColorPrsBuilder) aBuilder = new MeshVS_ElementalColorPrsBuilder(
                aMesh, MeshVS_DMF_ElementalColorDataPrs | MeshVS_DMF_OCCMask );
              // Color
            const TColStd_PackedMapOfInteger& anAllElements = aMesh->GetDataSource()->GetAllElements();
            TColStd_MapIteratorOfPackedMapOfInteger anIter( anAllElements );

            if( aMode.IsEqual("elem1") )
              for ( ; anIter.More(); anIter.Next() )
              {
                Quantity_Color aColor( (Quantity_NameOfColor)( anIter.Key() % Quantity_NOC_WHITE ) );
                aBuilder->SetColor1( anIter.Key(), aColor );
              }
            else
              for ( ; anIter.More(); anIter.Next() )
                aBuilder->SetColor2( anIter.Key(), aColor1, aColor2 );

            aMesh->AddBuilder( aBuilder, Standard_True );
          }


          if( aMode.IsEqual("nodal") )
          {
            Handle(MeshVS_NodalColorPrsBuilder) aBuilder = new MeshVS_NodalColorPrsBuilder(
                aMesh, MeshVS_DMF_NodalColorDataPrs | MeshVS_DMF_OCCMask );
            aMesh->AddBuilder( aBuilder, Standard_True );

            // Color
            const TColStd_PackedMapOfInteger& anAllNodes =
              aMesh->GetDataSource()->GetAllNodes();
            TColStd_MapIteratorOfPackedMapOfInteger anIter( anAllNodes );
            for ( ; anIter.More(); anIter.Next() )
            {
              Quantity_Color aColor( (Quantity_NameOfColor)(
                anIter.Key() % Quantity_NOC_WHITE ) );
              aBuilder->SetColor( anIter.Key(), aColor );
            }
            aMesh->AddBuilder( aBuilder, Standard_True );
          }

          if(aMode.IsEqual("nodaltex"))
          {
            // assign nodal builder to the mesh
            Handle(MeshVS_NodalColorPrsBuilder) aBuilder = new MeshVS_NodalColorPrsBuilder(
                   aMesh, MeshVS_DMF_NodalColorDataPrs | MeshVS_DMF_OCCMask);
            aMesh->AddBuilder(aBuilder, Standard_True);
            aBuilder->UseTexture(Standard_True);

            // prepare color map for texture
            Aspect_SequenceOfColor aColorMap;
            aColorMap.Append((Quantity_NameOfColor) Quantity_NOC_RED);
            aColorMap.Append((Quantity_NameOfColor) Quantity_NOC_YELLOW);
            aColorMap.Append((Quantity_NameOfColor) Quantity_NOC_BLUE1);

            // prepare scale map for mesh - it will be assigned to mesh as texture coordinates
            // make mesh color interpolated from minimum X coord to maximum X coord
            Handle(MeshVS_DataSource) aDataSource = aMesh->GetDataSource();
            Standard_Real aMinX, aMinY, aMinZ, aMaxX, aMaxY, aMaxZ;

            // get bounding box for calculations
            aDataSource->GetBoundingBox().Get(aMinX, aMinY, aMinZ, aMaxX, aMaxY, aMaxZ);
            Standard_Real aDelta = aMaxX - aMinX;

            // assign color scale map values (0..1) to nodes
            TColStd_DataMapOfIntegerReal aScaleMap;
            TColStd_Array1OfReal aCoords(1, 3);
            Standard_Integer     aNbNodes;
            MeshVS_EntityType    aType;

            // iterate nodes
            const TColStd_PackedMapOfInteger& anAllNodes =
                  aMesh->GetDataSource()->GetAllNodes();
            TColStd_MapIteratorOfPackedMapOfInteger anIter(anAllNodes);
            for (; anIter.More(); anIter.Next())
            {
              //get node coordinates to aCoord variable
              aDataSource->GetGeom(anIter.Key(), Standard_False, aCoords, aNbNodes, aType);

              Standard_Real aScaleValue;
              try {
                OCC_CATCH_SIGNALS
                aScaleValue = (aCoords.Value(1) - (Standard_Real) aMinX) / aDelta;
              } catch(Standard_Failure) {
                aScaleValue = 0;
              }

              aScaleMap.Bind(anIter.Key(), aScaleValue);
            }

            //set color map for builder and a color for invalid scale value
            aBuilder->SetColorMap(aColorMap);
            aBuilder->SetInvalidColor(Quantity_NOC_BLACK);
            aBuilder->SetTextureCoords(aScaleMap);
            aMesh->AddBuilder(aBuilder, Standard_True);

            //set viewer to display texures
            const Handle(V3d_Viewer)& aViewer = anIC->CurrentViewer();
            for (aViewer->InitActiveViews(); aViewer->MoreActiveViews(); aViewer->NextActiveViews())
                 aViewer->ActiveView()->SetSurfaceDetail(V3d_TEX_ALL);
          }

          aMesh->GetDrawer()->SetBoolean ( MeshVS_DA_ColorReflection, 0 != reflection );

          anIC->Redisplay( aMesh );
        }
        else
        {
          di << "Wrong mode name" << "\n";
          return 0;
        }
      }
  }
  catch ( Standard_Failure )
  {
    di << "Error" << "\n";
  }

  return 0;
}
//-----------------------------------------------------------------------------

static Standard_Integer mesh_edge_width( Draw_Interpretor& di,
                                        Standard_Integer argc,
                                        const char** argv )
{
  try
  {
    OCC_CATCH_SIGNALS
      if ( argc < 3 )
      {
        di << "Wrong number of parameters. Use : mesh_edge_width mesh width" << "\n";
        return 0;
      }

      Handle(MeshVS_Mesh) aMesh = getMesh( argv[ 1 ], di );
      if ( aMesh.IsNull() )
      {
        di << "Mesh not found" << "\n";
        return 0;
      }

      const char* aWidthStr = argv[ 2 ];
      if ( aWidthStr == 0 || Draw::Atof( aWidthStr ) <= 0 )
      {
        di << "Width must be real value more than zero" << "\n";
        return 0;
      }

      double aWidth = Draw::Atof( aWidthStr );

      Handle(AIS_InteractiveContext) anIC = ViewerTest::GetAISContext();
      if ( anIC.IsNull() )
      {
        di << "The context is null" << "\n";
        return 0;
      }

      Handle(MeshVS_Drawer) aDrawer = aMesh->GetDrawer();
      if ( aDrawer.IsNull() )
      {
        di << "The drawer is null" << "\n";
        return 0;
      }

      aDrawer->SetDouble( MeshVS_DA_EdgeWidth, aWidth );
      anIC->Redisplay( aMesh );
  }
  catch ( Standard_Failure )
  {
    di << "Error" << "\n";
  }

  return 0;
}

//-----------------------------------------------------------------------------

void  XSDRAWSTLVRML::InitCommands (Draw_Interpretor& theCommands)
{
  const char* g = "XSTEP-STL/VRML";  // Step transfer file commands
  //XSDRAW::LoadDraw(theCommands);

  theCommands.Add ("writevrml", "shape file",__FILE__,writevrml,g);
  theCommands.Add ("writestl",  "shape file [ascii/binary (0/1) : 1 by default] [InParallel (0/1) : 0 by default]",__FILE__,writestl,g);
  theCommands.Add ("readstl",   "shape file",__FILE__,readstl,g);
  theCommands.Add ("loadvrml" , "shape file",__FILE__,loadvrml,g);
  theCommands.Add ("storevrml" , "shape file defl [type]",__FILE__,storevrml,g);

  theCommands.Add ("meshfromstl",   "creates MeshVS_Mesh from STL file",  __FILE__, createmesh, g );
  theCommands.Add ("meshdispmode",  "changes MeshVS_Mesh display mode",   __FILE__, meshdm,     g );
  theCommands.Add ("meshselmode",   "changes MeshVS_Mesh selection mode", __FILE__, meshsm,     g );
  theCommands.Add ("meshshadcolor", "change MeshVS_Mesh shading color",   __FILE__, meshcolor,  g );
  theCommands.Add ("meshlinkcolor", "change MeshVS_Mesh line color",      __FILE__, linecolor,  g );
  theCommands.Add ("meshmat",       "change MeshVS_Mesh material",        __FILE__, meshmat,    g );
  theCommands.Add ("meshshrcoef",   "change MeshVS_Mesh shrink coeff",    __FILE__, shrink,     g );
  theCommands.Add ("meshshow",      "display MeshVS_Mesh object",         __FILE__, mdisplay,   g );
  theCommands.Add ("meshhide",      "erase MeshVS_Mesh object",           __FILE__, merase,     g );
  theCommands.Add ("meshhidesel",   "hide selected entities",             __FILE__, hidesel,    g );
  theCommands.Add ("meshshowsel",   "show only selected entities",        __FILE__, showonly,   g );
  theCommands.Add ("meshshowall",   "show all entities",                  __FILE__, showall,    g );
  theCommands.Add ("meshdelete",    "delete MeshVS_Mesh object",          __FILE__, delmesh,    g );
  theCommands.Add ("meshcolors",    "display color presentation",         __FILE__, meshcolors, g );
  theCommands.Add ("mesh_edge_width", "set width of edges",               __FILE__, mesh_edge_width, g );
}

//==============================================================================
// XSDRAWSTLVRML::Factory
//==============================================================================
void XSDRAWSTLVRML::Factory(Draw_Interpretor& theDI)
{
  XSDRAWIGES::InitSelect();
  XSDRAWIGES::InitToBRep(theDI);
  XSDRAWIGES::InitFromBRep(theDI);
  XSDRAWSTEP::InitCommands(theDI);
  XSDRAWSTLVRML::InitCommands(theDI);
  SWDRAW::Init(theDI);
  XSDRAW::LoadDraw(theDI);
#ifdef DEB
  theDI << "Draw Plugin : All TKXSDRAW commands are loaded" << "\n";
#endif
}

// Declare entry point PLUGINFACTORY
DPLUGIN(XSDRAWSTLVRML)

