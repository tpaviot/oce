#ifndef _ShapeSchema_PTopoDS_Shape1_HeaderFile
#include <ShapeSchema_PTopoDS_Shape1.hxx>
#endif
#ifndef _PTopoDS_Shape1_HeaderFile
#include <PTopoDS_Shape1.hxx>
#endif
#include <ShapeSchema_PTopoDS_Shape1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PTopoDS_Shape1::SAdd(const PTopoDS_Shape1& p, const Handle(Storage_Schema)& theSchema)
{
     theSchema->PersistentToAdd(p._CSFDB_GetPTopoDS_Shape1myTShape());
   ShapeSchema_PTopLoc_Location::SAdd(p._CSFDB_GetPTopoDS_Shape1myLocation(),theSchema);

}

void ShapeSchema_PTopoDS_Shape1::SWrite(const PTopoDS_Shape1& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginWriteObjectData();
    theSchema->WritePersistentReference(pp._CSFDB_GetPTopoDS_Shape1myTShape(),f);
    ShapeSchema_PTopLoc_Location::SWrite(pp._CSFDB_GetPTopoDS_Shape1myLocation(),f,theSchema);
  f.PutInteger(pp._CSFDB_GetPTopoDS_Shape1myOrient());

  f.EndWriteObjectData();
}

void ShapeSchema_PTopoDS_Shape1::SRead(PTopoDS_Shape1& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginReadObjectData();

    Handle(PTopoDS_TShape1) PTopoDS_Shape1myTShape;

    theSchema->ReadPersistentReference(PTopoDS_Shape1myTShape,f);
    pp._CSFDB_SetPTopoDS_Shape1myTShape(PTopoDS_Shape1myTShape);

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp._CSFDB_GetPTopoDS_Shape1myLocation(),f,theSchema);

    TopAbs_Orientation PTopoDS_Shape1myOrient;
    Standard_Integer i_CSFDB_PTopoDS_Shape1myOrient;
    f.GetInteger(i_CSFDB_PTopoDS_Shape1myOrient);
    PTopoDS_Shape1myOrient = (TopAbs_Orientation)i_CSFDB_PTopoDS_Shape1myOrient;
    pp._CSFDB_SetPTopoDS_Shape1myOrient(PTopoDS_Shape1myOrient);

  f.EndReadObjectData();
}
