#ifndef _StdSchema_PDF_Attribute_HeaderFile
#include <StdSchema_PDF_Attribute.hxx>
#endif
#ifndef _PDF_Attribute_HeaderFile
#include <PDF_Attribute.hxx>
#endif
#include <StdSchema_PDF_Attribute.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDF_Attribute,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDF_Attribute,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDF_Attribute::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void StdSchema_PDF_Attribute::SAdd(const Handle(PDF_Attribute)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDF_Attribute")) {
      
    }
  }
}

void StdSchema_PDF_Attribute::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDF_Attribute::SAdd((Handle(PDF_Attribute)&)p,theSchema);
}

void StdSchema_PDF_Attribute::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_Attribute) &pp = (Handle(PDF_Attribute)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDF_Attribute::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDF_Attribute::SWrite(p,f,theSchema);
}


void StdSchema_PDF_Attribute::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_Attribute) &pp = (Handle(PDF_Attribute)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDF_Attribute::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDF_Attribute::SRead(p,f,theSchema);
}
