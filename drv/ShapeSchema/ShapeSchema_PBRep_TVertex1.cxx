#ifndef _ShapeSchema_PBRep_TVertex1_HeaderFile
#include <ShapeSchema_PBRep_TVertex1.hxx>
#endif
#ifndef _PBRep_TVertex1_HeaderFile
#include <PBRep_TVertex1.hxx>
#endif
#include <ShapeSchema_PBRep_TVertex1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_TVertex1,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_TVertex1,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_TVertex1::New() const
{
  return new PBRep_TVertex1(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_TVertex1::SAdd(const Handle(PBRep_TVertex1)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_TVertex1")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShape1myShapes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_TVertex1myPoints());

    }
  }
}

void ShapeSchema_PBRep_TVertex1::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_TVertex1::SAdd((Handle(PBRep_TVertex1)&)p,theSchema);
}

void ShapeSchema_PBRep_TVertex1::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TVertex1) &pp = (Handle(PBRep_TVertex1)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShape1myShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShape1myFlags());
  f.PutReal(pp->_CSFDB_GetPBRep_TVertex1myTolerance());
    ShapeSchema_gp_Pnt::SWrite(pp->_CSFDB_GetPBRep_TVertex1myPnt(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_TVertex1myPoints(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_TVertex1::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_TVertex1::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_TVertex1::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TVertex1) &pp = (Handle(PBRep_TVertex1)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfShape1) PTopoDS_TShape1myShapes;

    theSchema->ReadPersistentReference(PTopoDS_TShape1myShapes,f);
    pp->_CSFDB_SetPTopoDS_TShape1myShapes(PTopoDS_TShape1myShapes);

    Standard_Integer PTopoDS_TShape1myFlags;
    f.GetInteger(PTopoDS_TShape1myFlags);
    pp->_CSFDB_SetPTopoDS_TShape1myFlags(PTopoDS_TShape1myFlags);

    Standard_Real PBRep_TVertex1myTolerance;
    f.GetReal(PBRep_TVertex1myTolerance);
    pp->_CSFDB_SetPBRep_TVertex1myTolerance(PBRep_TVertex1myTolerance);

    ShapeSchema_gp_Pnt::SRead((gp_Pnt&)pp->_CSFDB_GetPBRep_TVertex1myPnt(),f,theSchema);

    Handle(PBRep_PointRepresentation) PBRep_TVertex1myPoints;

    theSchema->ReadPersistentReference(PBRep_TVertex1myPoints,f);
    pp->_CSFDB_SetPBRep_TVertex1myPoints(PBRep_TVertex1myPoints);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_TVertex1::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_TVertex1::SRead(p,f,theSchema);
}
