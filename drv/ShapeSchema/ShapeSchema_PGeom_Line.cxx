#ifndef _ShapeSchema_PGeom_Line_HeaderFile
#include <ShapeSchema_PGeom_Line.hxx>
#endif
#ifndef _PGeom_Line_HeaderFile
#include <PGeom_Line.hxx>
#endif
#include <ShapeSchema_PGeom_Line.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Line,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Line,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Line::New() const
{
  return new PGeom_Line(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Line::SAdd(const Handle(PGeom_Line)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Line")) {
      
    }
  }
}

void ShapeSchema_PGeom_Line::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Line::SAdd((Handle(PGeom_Line)&)p,theSchema);
}

void ShapeSchema_PGeom_Line::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Line) &pp = (Handle(PGeom_Line)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax1::SWrite(pp->_CSFDB_GetPGeom_Lineposition(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Line::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Line::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Line::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Line) &pp = (Handle(PGeom_Line)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax1::SRead((gp_Ax1&)pp->_CSFDB_GetPGeom_Lineposition(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Line::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Line::SRead(p,f,theSchema);
}
