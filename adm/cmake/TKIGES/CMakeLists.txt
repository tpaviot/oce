project(TKIGES)

if (WIN32)
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESData_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESFile_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESBasic_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESGraph_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESGeom_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESDimen_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESDraw_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESSolid_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESDefs_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESAppli_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESConvGeom_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESSelect_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESToBRep_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__GeomToIGES_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__Geom2dToIGES_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__BRepToIGES_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__BRepToIGESBRep_DLL" )
  list( APPEND TKIGES_PRECOMPILED_DEFS "-D__IGESControl_DLL" )
  string( REGEX REPLACE ";" " " TKIGES_PRECOMPILED_DEFS "${TKIGES_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKIGES_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESData" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESData" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESFile" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESFile" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESBasic" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESBasic" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESGraph" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESGraph" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESGeom" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESGeom" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESDimen" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESDimen" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESDraw" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESDraw" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESSolid" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESSolid" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESDefs" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESDefs" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESAppli" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESAppli" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESConvGeom" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESConvGeom" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESSelect" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESSelect" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESToBRep" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESToBRep" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/GeomToIGES" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/GeomToIGES" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/Geom2dToIGES" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/Geom2dToIGES" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/BRepToIGES" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/BRepToIGES" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/BRepToIGESBRep" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/BRepToIGESBRep" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../drv/IGESControl" )
  list( APPEND TKIGES_COMPILER_DIRECTORIES "../../../src/IGESControl" )

if (WIN32)
else()
endif()

  list( APPEND TKIGES_USED_LIBS TKBRep )
  list( APPEND TKIGES_USED_LIBS TKernel )
  list( APPEND TKIGES_USED_LIBS TKMath )
  list( APPEND TKIGES_USED_LIBS TKTopAlgo )
  list( APPEND TKIGES_USED_LIBS TKShHealing )
  list( APPEND TKIGES_USED_LIBS TKG2d )
  list( APPEND TKIGES_USED_LIBS TKG3d )
  list( APPEND TKIGES_USED_LIBS TKGeomBase )
  list( APPEND TKIGES_USED_LIBS TKGeomAlgo )
  list( APPEND TKIGES_USED_LIBS TKPrim )
  list( APPEND TKIGES_USED_LIBS TKBool )
  list( APPEND TKIGES_USED_LIBS TKOffset )
  list( APPEND TKIGES_USED_LIBS TKXSBase )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_Array1OfDirPart_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_Array1OfDirPart_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_Array1OfIGESEntity_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_Array1OfIGESEntity_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_FileRecognizer_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_FileRecognizer_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_GlobalNodeOfSpecificLib_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_GlobalNodeOfSpecificLib_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_GlobalNodeOfWriterLib_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_GlobalNodeOfWriterLib_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_HArray1OfIGESEntity_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_HArray1OfIGESEntity_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_NodeOfSpecificLib_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_NodeOfSpecificLib_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_NodeOfWriterLib_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_NodeOfWriterLib_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_SpecificLib_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_SpecificLib_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESData/IGESData_WriterLib_0.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../drv/IGESData/IGESData_WriterLib_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_BasicEditor.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_BasicEditor.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_ColorEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_ColorEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_DefSwitch.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_DefSwitch.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_DefaultGeneral.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_DefaultGeneral.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_DefaultSpecific.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_DefaultSpecific.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_DirChecker.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_DirChecker.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_DirPart.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_DirPart.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_FileProtocol.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_FileProtocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_FreeFormatEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_FreeFormatEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_GeneralModule.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_GeneralModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_GlobalSection.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_GlobalSection.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_IGESDumper.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_IGESDumper.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_IGESEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_IGESEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_IGESModel.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_IGESModel.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_IGESReaderData.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_IGESReaderData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_IGESReaderTool.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_IGESReaderTool.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_IGESType.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_IGESType.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_IGESWriter.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_IGESWriter.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_LabelDisplayEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_LabelDisplayEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_LevelListEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_LevelListEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_LineFontEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_LineFontEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_NameEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_NameEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_ParamCursor.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_ParamCursor.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_ParamReader.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_ParamReader.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_Protocol.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_Protocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_ReadWriteModule.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_ReadWriteModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_SingleParentEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_SingleParentEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_SpecificModule.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_SpecificModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_ToolLocation.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_ToolLocation.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_TransfEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_TransfEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_UndefinedEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_UndefinedEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESData/IGESData_ViewKindEntity.cxx" )
  SOURCE_GROUP (IGESData FILES "../../../src/IGESData/IGESData_ViewKindEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESFile/IGESFile_Read.cxx" )
  SOURCE_GROUP (IGESFile FILES "../../../src/IGESFile/IGESFile_Read.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESFile/analiges.c" )
  SOURCE_GROUP (IGESFile FILES "../../../src/IGESFile/analiges.c")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESFile/igesread.c" )
  SOURCE_GROUP (IGESFile FILES "../../../src/IGESFile/igesread.c")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESFile/liriges.c" )
  SOURCE_GROUP (IGESFile FILES "../../../src/IGESFile/liriges.c")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESFile/structiges.c" )
  SOURCE_GROUP (IGESFile FILES "../../../src/IGESFile/structiges.c")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESBasic/IGESBasic_Array1OfLineFontEntity_0.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../drv/IGESBasic/IGESBasic_Array1OfLineFontEntity_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESBasic/IGESBasic_Array2OfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../drv/IGESBasic/IGESBasic_Array2OfHArray1OfReal_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfIGESEntity_0.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfIGESEntity_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfInteger_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfReal_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfXYZ_0.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfXYZ_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfXY_0.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../drv/IGESBasic/IGESBasic_HArray1OfHArray1OfXY_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESBasic/IGESBasic_HArray1OfLineFontEntity_0.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../drv/IGESBasic/IGESBasic_HArray1OfLineFontEntity_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESBasic/IGESBasic_HArray2OfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../drv/IGESBasic/IGESBasic_HArray2OfHArray1OfReal_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_AssocGroupType.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_AssocGroupType.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ExternalRefFile.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ExternalRefFile.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ExternalRefFileIndex.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ExternalRefFileIndex.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ExternalRefFileName.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ExternalRefFileName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ExternalRefLibName.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ExternalRefLibName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ExternalRefName.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ExternalRefName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ExternalReferenceFile.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ExternalReferenceFile.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_GeneralModule.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_GeneralModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_Group.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_Group.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_GroupWithoutBackP.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_GroupWithoutBackP.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_Hierarchy.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_Hierarchy.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_Name.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_Name.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_OrderedGroup.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_OrderedGroup.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_OrderedGroupWithoutBackP.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_OrderedGroupWithoutBackP.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_Protocol.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_Protocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ReadWriteModule.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ReadWriteModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_SingleParent.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_SingleParent.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_SingularSubfigure.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_SingularSubfigure.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_SpecificModule.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_SpecificModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_SubfigureDef.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_SubfigureDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolAssocGroupType.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolAssocGroupType.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefFile.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefFile.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefFileIndex.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefFileIndex.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefFileName.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefFileName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefLibName.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefLibName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefName.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolExternalRefName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolExternalReferenceFile.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolExternalReferenceFile.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolGroup.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolGroup.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolGroupWithoutBackP.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolGroupWithoutBackP.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolHierarchy.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolHierarchy.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolName.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolOrderedGroup.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolOrderedGroup.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolOrderedGroupWithoutBackP.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolOrderedGroupWithoutBackP.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolSingleParent.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolSingleParent.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolSingularSubfigure.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolSingularSubfigure.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESBasic/IGESBasic_ToolSubfigureDef.cxx" )
  SOURCE_GROUP (IGESBasic FILES "../../../src/IGESBasic/IGESBasic_ToolSubfigureDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGraph/IGESGraph_Array1OfColor_0.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../drv/IGESGraph/IGESGraph_Array1OfColor_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGraph/IGESGraph_Array1OfTextDisplayTemplate_0.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../drv/IGESGraph/IGESGraph_Array1OfTextDisplayTemplate_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGraph/IGESGraph_Array1OfTextFontDef_0.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../drv/IGESGraph/IGESGraph_Array1OfTextFontDef_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGraph/IGESGraph_HArray1OfColor_0.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../drv/IGESGraph/IGESGraph_HArray1OfColor_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGraph/IGESGraph_HArray1OfTextDisplayTemplate_0.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../drv/IGESGraph/IGESGraph_HArray1OfTextDisplayTemplate_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGraph/IGESGraph_HArray1OfTextFontDef_0.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../drv/IGESGraph/IGESGraph_HArray1OfTextFontDef_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_Color.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_Color.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_DefinitionLevel.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_DefinitionLevel.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_DrawingSize.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_DrawingSize.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_DrawingUnits.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_DrawingUnits.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_GeneralModule.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_GeneralModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_HighLight.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_HighLight.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_IntercharacterSpacing.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_IntercharacterSpacing.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_LineFontDefPattern.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_LineFontDefPattern.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_LineFontDefTemplate.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_LineFontDefTemplate.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_LineFontPredefined.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_LineFontPredefined.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_NominalSize.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_NominalSize.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_Pick.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_Pick.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_Protocol.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_Protocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ReadWriteModule.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ReadWriteModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_SpecificModule.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_SpecificModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_TextDisplayTemplate.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_TextDisplayTemplate.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_TextFontDef.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_TextFontDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolColor.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolColor.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolDefinitionLevel.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolDefinitionLevel.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolDrawingSize.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolDrawingSize.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolDrawingUnits.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolDrawingUnits.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolHighLight.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolHighLight.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolIntercharacterSpacing.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolIntercharacterSpacing.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolLineFontDefPattern.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolLineFontDefPattern.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolLineFontDefTemplate.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolLineFontDefTemplate.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolLineFontPredefined.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolLineFontPredefined.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolNominalSize.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolNominalSize.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolPick.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolPick.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolTextDisplayTemplate.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolTextDisplayTemplate.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolTextFontDef.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolTextFontDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_ToolUniformRectGrid.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_ToolUniformRectGrid.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGraph/IGESGraph_UniformRectGrid.cxx" )
  SOURCE_GROUP (IGESGraph FILES "../../../src/IGESGraph/IGESGraph_UniformRectGrid.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGeom/IGESGeom_Array1OfBoundary_0.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../drv/IGESGeom/IGESGeom_Array1OfBoundary_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGeom/IGESGeom_Array1OfCurveOnSurface_0.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../drv/IGESGeom/IGESGeom_Array1OfCurveOnSurface_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGeom/IGESGeom_Array1OfTransformationMatrix_0.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../drv/IGESGeom/IGESGeom_Array1OfTransformationMatrix_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGeom/IGESGeom_HArray1OfBoundary_0.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../drv/IGESGeom/IGESGeom_HArray1OfBoundary_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGeom/IGESGeom_HArray1OfCurveOnSurface_0.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../drv/IGESGeom/IGESGeom_HArray1OfCurveOnSurface_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESGeom/IGESGeom_HArray1OfTransformationMatrix_0.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../drv/IGESGeom/IGESGeom_HArray1OfTransformationMatrix_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_BSplineCurve.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_BSplineCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_BSplineSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_BSplineSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_Boundary.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_Boundary.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_BoundedSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_BoundedSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_CircularArc.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_CircularArc.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_CompositeCurve.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_CompositeCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ConicArc.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ConicArc.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_CopiousData.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_CopiousData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_CurveOnSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_CurveOnSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_Direction.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_Direction.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_Flash.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_Flash.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_GeneralModule.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_GeneralModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_Line.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_Line.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_OffsetCurve.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_OffsetCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_OffsetSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_OffsetSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_Plane.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_Plane.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_Point.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_Point.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_Protocol.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_Protocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ReadWriteModule.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ReadWriteModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_RuledSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_RuledSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_SpecificModule.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_SpecificModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_SplineCurve.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_SplineCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_SplineSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_SplineSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_SurfaceOfRevolution.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_SurfaceOfRevolution.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_TabulatedCylinder.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_TabulatedCylinder.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolBSplineCurve.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolBSplineCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolBSplineSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolBSplineSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolBoundary.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolBoundary.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolBoundedSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolBoundedSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolCircularArc.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolCircularArc.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolCompositeCurve.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolCompositeCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolConicArc.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolConicArc.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolCopiousData.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolCopiousData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolCurveOnSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolCurveOnSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolDirection.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolDirection.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolFlash.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolFlash.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolLine.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolLine.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolOffsetCurve.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolOffsetCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolOffsetSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolOffsetSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolPlane.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolPlane.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolPoint.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolPoint.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolRuledSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolRuledSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolSplineCurve.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolSplineCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolSplineSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolSplineSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolSurfaceOfRevolution.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolSurfaceOfRevolution.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolTabulatedCylinder.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolTabulatedCylinder.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolTransformationMatrix.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolTransformationMatrix.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_ToolTrimmedSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_ToolTrimmedSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_TransformationMatrix.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_TransformationMatrix.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESGeom/IGESGeom_TrimmedSurface.cxx" )
  SOURCE_GROUP (IGESGeom FILES "../../../src/IGESGeom/IGESGeom_TrimmedSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDimen/IGESDimen_Array1OfGeneralNote_0.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../drv/IGESDimen/IGESDimen_Array1OfGeneralNote_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDimen/IGESDimen_Array1OfLeaderArrow_0.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../drv/IGESDimen/IGESDimen_Array1OfLeaderArrow_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDimen/IGESDimen_HArray1OfGeneralNote_0.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../drv/IGESDimen/IGESDimen_HArray1OfGeneralNote_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDimen/IGESDimen_HArray1OfLeaderArrow_0.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../drv/IGESDimen/IGESDimen_HArray1OfLeaderArrow_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_AngularDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_AngularDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_BasicDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_BasicDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_CenterLine.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_CenterLine.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_CurveDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_CurveDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_DiameterDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_DiameterDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_DimensionDisplayData.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_DimensionDisplayData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_DimensionTolerance.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_DimensionTolerance.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_DimensionUnits.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_DimensionUnits.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_DimensionedGeometry.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_DimensionedGeometry.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_FlagNote.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_FlagNote.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_GeneralLabel.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_GeneralLabel.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_GeneralModule.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_GeneralModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_GeneralNote.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_GeneralNote.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_GeneralSymbol.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_GeneralSymbol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_LeaderArrow.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_LeaderArrow.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_LinearDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_LinearDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_NewDimensionedGeometry.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_NewDimensionedGeometry.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_NewGeneralNote.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_NewGeneralNote.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_OrdinateDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_OrdinateDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_PointDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_PointDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_Protocol.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_Protocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_RadiusDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_RadiusDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ReadWriteModule.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ReadWriteModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_Section.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_Section.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_SectionedArea.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_SectionedArea.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_SpecificModule.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_SpecificModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolAngularDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolAngularDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolBasicDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolBasicDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolCenterLine.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolCenterLine.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolCurveDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolCurveDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolDiameterDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolDiameterDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolDimensionDisplayData.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolDimensionDisplayData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolDimensionTolerance.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolDimensionTolerance.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolDimensionUnits.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolDimensionUnits.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolDimensionedGeometry.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolDimensionedGeometry.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolFlagNote.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolFlagNote.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolGeneralLabel.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolGeneralLabel.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolGeneralNote.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolGeneralNote.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolGeneralSymbol.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolGeneralSymbol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolLeaderArrow.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolLeaderArrow.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolLinearDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolLinearDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolNewDimensionedGeometry.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolNewDimensionedGeometry.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolNewGeneralNote.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolNewGeneralNote.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolOrdinateDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolOrdinateDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolPointDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolPointDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolRadiusDimension.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolRadiusDimension.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolSection.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolSection.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolSectionedArea.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolSectionedArea.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_ToolWitnessLine.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_ToolWitnessLine.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDimen/IGESDimen_WitnessLine.cxx" )
  SOURCE_GROUP (IGESDimen FILES "../../../src/IGESDimen/IGESDimen_WitnessLine.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDraw/IGESDraw_Array1OfConnectPoint_0.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../drv/IGESDraw/IGESDraw_Array1OfConnectPoint_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDraw/IGESDraw_Array1OfViewKindEntity_0.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../drv/IGESDraw/IGESDraw_Array1OfViewKindEntity_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDraw/IGESDraw_HArray1OfConnectPoint_0.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../drv/IGESDraw/IGESDraw_HArray1OfConnectPoint_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDraw/IGESDraw_HArray1OfViewKindEntity_0.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../drv/IGESDraw/IGESDraw_HArray1OfViewKindEntity_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_CircArraySubfigure.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_CircArraySubfigure.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ConnectPoint.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ConnectPoint.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_Drawing.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_Drawing.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_DrawingWithRotation.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_DrawingWithRotation.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_GeneralModule.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_GeneralModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_LabelDisplay.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_LabelDisplay.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_NetworkSubfigure.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_NetworkSubfigure.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_NetworkSubfigureDef.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_NetworkSubfigureDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_PerspectiveView.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_PerspectiveView.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_Planar.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_Planar.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_Protocol.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_Protocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ReadWriteModule.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ReadWriteModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_RectArraySubfigure.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_RectArraySubfigure.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_SegmentedViewsVisible.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_SegmentedViewsVisible.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_SpecificModule.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_SpecificModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolCircArraySubfigure.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolCircArraySubfigure.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolConnectPoint.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolConnectPoint.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolDrawing.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolDrawing.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolDrawingWithRotation.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolDrawingWithRotation.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolLabelDisplay.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolLabelDisplay.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolNetworkSubfigure.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolNetworkSubfigure.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolNetworkSubfigureDef.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolNetworkSubfigureDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolPerspectiveView.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolPerspectiveView.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolPlanar.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolPlanar.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolRectArraySubfigure.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolRectArraySubfigure.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolSegmentedViewsVisible.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolSegmentedViewsVisible.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolView.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolView.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolViewsVisible.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolViewsVisible.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ToolViewsVisibleWithAttr.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ToolViewsVisibleWithAttr.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_View.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_View.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ViewsVisible.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ViewsVisible.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDraw/IGESDraw_ViewsVisibleWithAttr.cxx" )
  SOURCE_GROUP (IGESDraw FILES "../../../src/IGESDraw/IGESDraw_ViewsVisibleWithAttr.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSolid/IGESSolid_Array1OfFace_0.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../drv/IGESSolid/IGESSolid_Array1OfFace_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSolid/IGESSolid_Array1OfLoop_0.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../drv/IGESSolid/IGESSolid_Array1OfLoop_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSolid/IGESSolid_Array1OfShell_0.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../drv/IGESSolid/IGESSolid_Array1OfShell_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSolid/IGESSolid_Array1OfVertexList_0.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../drv/IGESSolid/IGESSolid_Array1OfVertexList_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSolid/IGESSolid_HArray1OfFace_0.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../drv/IGESSolid/IGESSolid_HArray1OfFace_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSolid/IGESSolid_HArray1OfLoop_0.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../drv/IGESSolid/IGESSolid_HArray1OfLoop_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSolid/IGESSolid_HArray1OfShell_0.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../drv/IGESSolid/IGESSolid_HArray1OfShell_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSolid/IGESSolid_HArray1OfVertexList_0.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../drv/IGESSolid/IGESSolid_HArray1OfVertexList_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_Block.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_Block.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_BooleanTree.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_BooleanTree.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ConeFrustum.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ConeFrustum.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ConicalSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ConicalSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_Cylinder.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_Cylinder.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_CylindricalSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_CylindricalSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_EdgeList.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_EdgeList.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_Ellipsoid.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_Ellipsoid.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_Face.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_Face.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_GeneralModule.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_GeneralModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_Loop.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_Loop.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ManifoldSolid.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ManifoldSolid.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_PlaneSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_PlaneSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_Protocol.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_Protocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ReadWriteModule.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ReadWriteModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_RightAngularWedge.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_RightAngularWedge.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_SelectedComponent.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_SelectedComponent.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_Shell.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_Shell.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_SolidAssembly.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_SolidAssembly.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_SolidInstance.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_SolidInstance.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_SolidOfLinearExtrusion.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_SolidOfLinearExtrusion.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_SolidOfRevolution.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_SolidOfRevolution.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_SpecificModule.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_SpecificModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_Sphere.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_Sphere.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_SphericalSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_SphericalSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolBlock.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolBlock.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolBooleanTree.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolBooleanTree.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolConeFrustum.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolConeFrustum.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolConicalSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolConicalSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolCylinder.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolCylinder.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolCylindricalSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolCylindricalSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolEdgeList.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolEdgeList.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolEllipsoid.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolEllipsoid.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolFace.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolFace.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolLoop.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolLoop.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolManifoldSolid.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolManifoldSolid.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolPlaneSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolPlaneSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolRightAngularWedge.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolRightAngularWedge.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolSelectedComponent.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolSelectedComponent.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolShell.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolShell.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolSolidAssembly.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolSolidAssembly.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolSolidInstance.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolSolidInstance.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolSolidOfLinearExtrusion.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolSolidOfLinearExtrusion.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolSolidOfRevolution.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolSolidOfRevolution.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolSphere.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolSphere.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolSphericalSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolSphericalSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolToroidalSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolToroidalSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolTorus.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolTorus.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToolVertexList.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToolVertexList.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_TopoBuilder.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_TopoBuilder.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_ToroidalSurface.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_ToroidalSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_Torus.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_Torus.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSolid/IGESSolid_VertexList.cxx" )
  SOURCE_GROUP (IGESSolid FILES "../../../src/IGESSolid/IGESSolid_VertexList.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDefs/IGESDefs_Array1OfTabularData_0.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../drv/IGESDefs/IGESDefs_Array1OfTabularData_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDefs/IGESDefs_HArray1OfHArray1OfTextDisplayTemplate_0.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../drv/IGESDefs/IGESDefs_HArray1OfHArray1OfTextDisplayTemplate_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESDefs/IGESDefs_HArray1OfTabularData_0.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../drv/IGESDefs/IGESDefs_HArray1OfTabularData_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_AssociativityDef.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_AssociativityDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_AttributeDef.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_AttributeDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_AttributeTable.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_AttributeTable.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_GeneralModule.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_GeneralModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_GenericData.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_GenericData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_MacroDef.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_MacroDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_Protocol.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_Protocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_ReadWriteModule.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_ReadWriteModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_SpecificModule.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_SpecificModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_TabularData.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_TabularData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_ToolAssociativityDef.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_ToolAssociativityDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_ToolAttributeDef.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_ToolAttributeDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_ToolAttributeTable.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_ToolAttributeTable.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_ToolGenericData.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_ToolGenericData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_ToolMacroDef.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_ToolMacroDef.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_ToolTabularData.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_ToolTabularData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_ToolUnitsData.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_ToolUnitsData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESDefs/IGESDefs_UnitsData.cxx" )
  SOURCE_GROUP (IGESDefs FILES "../../../src/IGESDefs/IGESDefs_UnitsData.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESAppli/IGESAppli_Array1OfFiniteElement_0.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../drv/IGESAppli/IGESAppli_Array1OfFiniteElement_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESAppli/IGESAppli_Array1OfFlow_0.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../drv/IGESAppli/IGESAppli_Array1OfFlow_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESAppli/IGESAppli_Array1OfNode_0.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../drv/IGESAppli/IGESAppli_Array1OfNode_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESAppli/IGESAppli_HArray1OfFiniteElement_0.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../drv/IGESAppli/IGESAppli_HArray1OfFiniteElement_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESAppli/IGESAppli_HArray1OfFlow_0.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../drv/IGESAppli/IGESAppli_HArray1OfFlow_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESAppli/IGESAppli_HArray1OfNode_0.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../drv/IGESAppli/IGESAppli_HArray1OfNode_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_DrilledHole.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_DrilledHole.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ElementResults.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ElementResults.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_FiniteElement.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_FiniteElement.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_Flow.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_Flow.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_FlowLineSpec.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_FlowLineSpec.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_GeneralModule.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_GeneralModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_LevelFunction.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_LevelFunction.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_LevelToPWBLayerMap.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_LevelToPWBLayerMap.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_LineWidening.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_LineWidening.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_NodalConstraint.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_NodalConstraint.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_NodalDisplAndRot.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_NodalDisplAndRot.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_NodalResults.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_NodalResults.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_Node.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_Node.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_PWBArtworkStackup.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_PWBArtworkStackup.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_PWBDrilledHole.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_PWBDrilledHole.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_PartNumber.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_PartNumber.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_PinNumber.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_PinNumber.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_PipingFlow.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_PipingFlow.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_Protocol.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_Protocol.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ReadWriteModule.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ReadWriteModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ReferenceDesignator.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ReferenceDesignator.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_RegionRestriction.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_RegionRestriction.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_SpecificModule.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_SpecificModule.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolDrilledHole.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolDrilledHole.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolElementResults.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolElementResults.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolFiniteElement.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolFiniteElement.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolFlow.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolFlow.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolFlowLineSpec.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolFlowLineSpec.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolLevelFunction.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolLevelFunction.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolLevelToPWBLayerMap.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolLevelToPWBLayerMap.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolLineWidening.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolLineWidening.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolNodalConstraint.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolNodalConstraint.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolNodalDisplAndRot.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolNodalDisplAndRot.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolNodalResults.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolNodalResults.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolNode.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolNode.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolPWBArtworkStackup.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolPWBArtworkStackup.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolPWBDrilledHole.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolPWBDrilledHole.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolPartNumber.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolPartNumber.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolPinNumber.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolPinNumber.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolPipingFlow.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolPipingFlow.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolReferenceDesignator.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolReferenceDesignator.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESAppli/IGESAppli_ToolRegionRestriction.cxx" )
  SOURCE_GROUP (IGESAppli FILES "../../../src/IGESAppli/IGESAppli_ToolRegionRestriction.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESConvGeom/IGESConvGeom.cxx" )
  SOURCE_GROUP (IGESConvGeom FILES "../../../src/IGESConvGeom/IGESConvGeom.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESConvGeom/IGESConvGeom_GeomBuilder.cxx" )
  SOURCE_GROUP (IGESConvGeom FILES "../../../src/IGESConvGeom/IGESConvGeom_GeomBuilder.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSelect/IGESSelect_FileModifier_0.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../drv/IGESSelect/IGESSelect_FileModifier_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../drv/IGESSelect/IGESSelect_ModelModifier_0.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../drv/IGESSelect/IGESSelect_ModelModifier_0.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_Activator.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_Activator.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_AddFileComment.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_AddFileComment.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_AddGroup.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_AddGroup.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_AutoCorrect.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_AutoCorrect.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_ChangeLevelList.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_ChangeLevelList.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_ChangeLevelNumber.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_ChangeLevelNumber.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_ComputeStatus.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_ComputeStatus.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_CounterOfLevelNumber.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_CounterOfLevelNumber.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_DispPerDrawing.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_DispPerDrawing.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_DispPerSingleView.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_DispPerSingleView.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_Dumper.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_Dumper.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_EditDirPart.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_EditDirPart.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_EditHeader.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_EditHeader.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_FloatFormat.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_FloatFormat.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_IGESName.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_IGESName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_IGESTypeForm.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_IGESTypeForm.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_RebuildDrawings.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_RebuildDrawings.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_RebuildGroups.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_RebuildGroups.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_RemoveCurves.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_RemoveCurves.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectBasicGeom.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectBasicGeom.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectBypassGroup.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectBypassGroup.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectBypassSubfigure.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectBypassSubfigure.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectDrawingFrom.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectDrawingFrom.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectFaces.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectFaces.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectFromDrawing.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectFromDrawing.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectFromSingleView.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectFromSingleView.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectLevelNumber.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectLevelNumber.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectName.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectPCurves.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectPCurves.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectSingleViewFrom.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectSingleViewFrom.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectSubordinate.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectSubordinate.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SelectVisibleStatus.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SelectVisibleStatus.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SetGlobalParameter.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SetGlobalParameter.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SetLabel.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SetLabel.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SetVersion5.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SetVersion5.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SignColor.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SignColor.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SignLevelNumber.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SignLevelNumber.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SignStatus.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SignStatus.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_SplineToBSpline.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_SplineToBSpline.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_UpdateCreationDate.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_UpdateCreationDate.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_UpdateFileName.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_UpdateFileName.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_UpdateLastChange.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_UpdateLastChange.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_ViewSorter.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_ViewSorter.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESSelect/IGESSelect_WorkLibrary.cxx" )
  SOURCE_GROUP (IGESSelect FILES "../../../src/IGESSelect/IGESSelect_WorkLibrary.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_Actor.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_Actor.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_AlgoContainer.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_AlgoContainer.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_BRepEntity.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_BRepEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_BasicCurve.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_BasicCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_BasicSurface.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_BasicSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_CurveAndSurface.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_CurveAndSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_IGESBoundary.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_IGESBoundary.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_Reader.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_Reader.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_ToolContainer.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_ToolContainer.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_TopoCurve.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_TopoCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESToBRep/IGESToBRep_TopoSurface.cxx" )
  SOURCE_GROUP (IGESToBRep FILES "../../../src/IGESToBRep/IGESToBRep_TopoSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/GeomToIGES/GeomToIGES_GeomCurve.cxx" )
  SOURCE_GROUP (GeomToIGES FILES "../../../src/GeomToIGES/GeomToIGES_GeomCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/GeomToIGES/GeomToIGES_GeomEntity.cxx" )
  SOURCE_GROUP (GeomToIGES FILES "../../../src/GeomToIGES/GeomToIGES_GeomEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/GeomToIGES/GeomToIGES_GeomPoint.cxx" )
  SOURCE_GROUP (GeomToIGES FILES "../../../src/GeomToIGES/GeomToIGES_GeomPoint.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/GeomToIGES/GeomToIGES_GeomSurface.cxx" )
  SOURCE_GROUP (GeomToIGES FILES "../../../src/GeomToIGES/GeomToIGES_GeomSurface.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/GeomToIGES/GeomToIGES_GeomVector.cxx" )
  SOURCE_GROUP (GeomToIGES FILES "../../../src/GeomToIGES/GeomToIGES_GeomVector.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/Geom2dToIGES/Geom2dToIGES_Geom2dCurve.cxx" )
  SOURCE_GROUP (Geom2dToIGES FILES "../../../src/Geom2dToIGES/Geom2dToIGES_Geom2dCurve.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/Geom2dToIGES/Geom2dToIGES_Geom2dEntity.cxx" )
  SOURCE_GROUP (Geom2dToIGES FILES "../../../src/Geom2dToIGES/Geom2dToIGES_Geom2dEntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/Geom2dToIGES/Geom2dToIGES_Geom2dPoint.cxx" )
  SOURCE_GROUP (Geom2dToIGES FILES "../../../src/Geom2dToIGES/Geom2dToIGES_Geom2dPoint.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/Geom2dToIGES/Geom2dToIGES_Geom2dVector.cxx" )
  SOURCE_GROUP (Geom2dToIGES FILES "../../../src/Geom2dToIGES/Geom2dToIGES_Geom2dVector.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/BRepToIGES/BRepToIGES_BREntity.cxx" )
  SOURCE_GROUP (BRepToIGES FILES "../../../src/BRepToIGES/BRepToIGES_BREntity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/BRepToIGES/BRepToIGES_BRShell.cxx" )
  SOURCE_GROUP (BRepToIGES FILES "../../../src/BRepToIGES/BRepToIGES_BRShell.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/BRepToIGES/BRepToIGES_BRSolid.cxx" )
  SOURCE_GROUP (BRepToIGES FILES "../../../src/BRepToIGES/BRepToIGES_BRSolid.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/BRepToIGES/BRepToIGES_BRWire.cxx" )
  SOURCE_GROUP (BRepToIGES FILES "../../../src/BRepToIGES/BRepToIGES_BRWire.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/BRepToIGESBRep/BRepToIGESBRep_Entity.cxx" )
  SOURCE_GROUP (BRepToIGESBRep FILES "../../../src/BRepToIGESBRep/BRepToIGESBRep_Entity.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESControl/IGESControl_ActorWrite.cxx" )
  SOURCE_GROUP (IGESControl FILES "../../../src/IGESControl/IGESControl_ActorWrite.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESControl/IGESControl_AlgoContainer.cxx" )
  SOURCE_GROUP (IGESControl FILES "../../../src/IGESControl/IGESControl_AlgoContainer.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESControl/IGESControl_Controller.cxx" )
  SOURCE_GROUP (IGESControl FILES "../../../src/IGESControl/IGESControl_Controller.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESControl/IGESControl_IGESBoundary.cxx" )
  SOURCE_GROUP (IGESControl FILES "../../../src/IGESControl/IGESControl_IGESBoundary.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESControl/IGESControl_Reader.cxx" )
  SOURCE_GROUP (IGESControl FILES "../../../src/IGESControl/IGESControl_Reader.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESControl/IGESControl_ToolContainer.cxx" )
  SOURCE_GROUP (IGESControl FILES "../../../src/IGESControl/IGESControl_ToolContainer.cxx")

  list( APPEND TKIGES_USED_SRCFILES "../../../src/IGESControl/IGESControl_Writer.cxx" )
  SOURCE_GROUP (IGESControl FILES "../../../src/IGESControl/IGESControl_Writer.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKIGES)
 add_library( TKIGES SHARED ${TKIGES_USED_SRCFILES} )

 set_property(TARGET TKIGES PROPERTY FOLDER DataExchange)

 install( TARGETS TKIGES
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKIGES.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKIGES PROPERTIES COMPILE_FLAGS "${TKIGES_PRECOMPILED_DEFS}" )
 include_directories( ${TKIGES_COMPILER_DIRECTORIES} )
 target_link_libraries( TKIGES ${TKIGES_USED_LIBS} )
endif()
