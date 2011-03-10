#ifndef _ShapeSchema_PBRep_TFace_HeaderFile
#include <ShapeSchema_PBRep_TFace.hxx>
#endif
#ifndef _PBRep_TFace_HeaderFile
#include <PBRep_TFace.hxx>
#endif
#include <ShapeSchema_PBRep_TFace.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_TFace,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_TFace,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_TFace::New() const
{
  return new PBRep_TFace(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_TFace::SAdd(const Handle(PBRep_TFace)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_TFace")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShapemyShapes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_TFacemySurface());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_TFacemyTriangulation());
   ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_TFacemyLocation(),theSchema);

    }
  }
}

void ShapeSchema_PBRep_TFace::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_TFace::SAdd((Handle(PBRep_TFace)&)p,theSchema);
}

void ShapeSchema_PBRep_TFace::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TFace) &pp = (Handle(PBRep_TFace)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShapemyShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShapemyFlags());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_TFacemySurface(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_TFacemyTriangulation(),f);
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_TFacemyLocation(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPBRep_TFacemyTolerance());
  f.PutBoolean(pp->_CSFDB_GetPBRep_TFacemyNaturalRestriction());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_TFace::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_TFace::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_TFace::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TFace) &pp = (Handle(PBRep_TFace)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfHShape) PTopoDS_TShapemyShapes;

    theSchema->ReadPersistentReference(PTopoDS_TShapemyShapes,f);
    pp->_CSFDB_SetPTopoDS_TShapemyShapes(PTopoDS_TShapemyShapes);

    Standard_Integer PTopoDS_TShapemyFlags;
    f.GetInteger(PTopoDS_TShapemyFlags);
    pp->_CSFDB_SetPTopoDS_TShapemyFlags(PTopoDS_TShapemyFlags);

    Handle(PGeom_Surface) PBRep_TFacemySurface;

    theSchema->ReadPersistentReference(PBRep_TFacemySurface,f);
    pp->_CSFDB_SetPBRep_TFacemySurface(PBRep_TFacemySurface);

    Handle(PPoly_Triangulation) PBRep_TFacemyTriangulation;

    theSchema->ReadPersistentReference(PBRep_TFacemyTriangulation,f);
    pp->_CSFDB_SetPBRep_TFacemyTriangulation(PBRep_TFacemyTriangulation);

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_TFacemyLocation(),f,theSchema);

    Standard_Real PBRep_TFacemyTolerance;
    f.GetReal(PBRep_TFacemyTolerance);
    pp->_CSFDB_SetPBRep_TFacemyTolerance(PBRep_TFacemyTolerance);

    Standard_Boolean PBRep_TFacemyNaturalRestriction;
    f.GetBoolean(PBRep_TFacemyNaturalRestriction);
    pp->_CSFDB_SetPBRep_TFacemyNaturalRestriction(PBRep_TFacemyNaturalRestriction);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_TFace::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_TFace::SRead(p,f,theSchema);
}
