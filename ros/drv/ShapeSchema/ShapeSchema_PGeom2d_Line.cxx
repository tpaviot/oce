#ifndef _ShapeSchema_PGeom2d_Line_HeaderFile
#include <ShapeSchema_PGeom2d_Line.hxx>
#endif
#ifndef _PGeom2d_Line_HeaderFile
#include <PGeom2d_Line.hxx>
#endif
#include <ShapeSchema_PGeom2d_Line.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Line,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Line,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Line::New() const
{
  return new PGeom2d_Line(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_Line::SAdd(const Handle(PGeom2d_Line)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Line")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Line::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Line::SAdd((Handle(PGeom2d_Line)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Line::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Line) &pp = (Handle(PGeom2d_Line)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax2d::SWrite(pp->_CSFDB_GetPGeom2d_Lineposition(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Line::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Line::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Line::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Line) &pp = (Handle(PGeom2d_Line)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax2d::SRead((gp_Ax2d&)pp->_CSFDB_GetPGeom2d_Lineposition(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Line::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Line::SRead(p,f,theSchema);
}
