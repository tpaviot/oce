#ifndef _ShapeSchema_PBRep_TFace1_HeaderFile
#include <ShapeSchema_PBRep_TFace1.hxx>
#endif
#ifndef _PBRep_TFace1_HeaderFile
#include <PBRep_TFace1.hxx>
#endif
#include <ShapeSchema_PBRep_TFace1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_TFace1,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_TFace1,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_TFace1::New() const
{
  return new PBRep_TFace1(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_TFace1::SAdd(const Handle(PBRep_TFace1)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_TFace1")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShape1myShapes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_TFace1mySurface());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_TFace1myTriangulation());
   ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_TFace1myLocation(),theSchema);

    }
  }
}

void ShapeSchema_PBRep_TFace1::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_TFace1::SAdd((Handle(PBRep_TFace1)&)p,theSchema);
}

void ShapeSchema_PBRep_TFace1::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TFace1) &pp = (Handle(PBRep_TFace1)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShape1myShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShape1myFlags());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_TFace1mySurface(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_TFace1myTriangulation(),f);
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_TFace1myLocation(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPBRep_TFace1myTolerance());
  f.PutBoolean(pp->_CSFDB_GetPBRep_TFace1myNaturalRestriction());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_TFace1::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_TFace1::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_TFace1::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TFace1) &pp = (Handle(PBRep_TFace1)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfShape1) PTopoDS_TShape1myShapes;

    theSchema->ReadPersistentReference(PTopoDS_TShape1myShapes,f);
    pp->_CSFDB_SetPTopoDS_TShape1myShapes(PTopoDS_TShape1myShapes);

    Standard_Integer PTopoDS_TShape1myFlags;
    f.GetInteger(PTopoDS_TShape1myFlags);
    pp->_CSFDB_SetPTopoDS_TShape1myFlags(PTopoDS_TShape1myFlags);

    Handle(PGeom_Surface) PBRep_TFace1mySurface;

    theSchema->ReadPersistentReference(PBRep_TFace1mySurface,f);
    pp->_CSFDB_SetPBRep_TFace1mySurface(PBRep_TFace1mySurface);

    Handle(PPoly_Triangulation) PBRep_TFace1myTriangulation;

    theSchema->ReadPersistentReference(PBRep_TFace1myTriangulation,f);
    pp->_CSFDB_SetPBRep_TFace1myTriangulation(PBRep_TFace1myTriangulation);

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_TFace1myLocation(),f,theSchema);

    Standard_Real PBRep_TFace1myTolerance;
    f.GetReal(PBRep_TFace1myTolerance);
    pp->_CSFDB_SetPBRep_TFace1myTolerance(PBRep_TFace1myTolerance);

    Standard_Boolean PBRep_TFace1myNaturalRestriction;
    f.GetBoolean(PBRep_TFace1myNaturalRestriction);
    pp->_CSFDB_SetPBRep_TFace1myNaturalRestriction(PBRep_TFace1myNaturalRestriction);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_TFace1::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_TFace1::SRead(p,f,theSchema);
}
