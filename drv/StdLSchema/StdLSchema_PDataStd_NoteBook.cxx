#ifndef _StdLSchema_PDataStd_NoteBook_HeaderFile
#include <StdLSchema_PDataStd_NoteBook.hxx>
#endif
#ifndef _PDataStd_NoteBook_HeaderFile
#include <PDataStd_NoteBook.hxx>
#endif
#include <StdLSchema_PDataStd_NoteBook.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_NoteBook,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_NoteBook,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_NoteBook::New() const
{
  return new PDataStd_NoteBook(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_NoteBook::SAdd(const Handle(PDataStd_NoteBook)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_NoteBook")) {
      
    }
  }
}

void StdLSchema_PDataStd_NoteBook::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_NoteBook::SAdd((Handle(PDataStd_NoteBook)&)p,theSchema);
}

void StdLSchema_PDataStd_NoteBook::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_NoteBook::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_NoteBook::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_NoteBook::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
 
    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_NoteBook::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_NoteBook::SRead(p,f,theSchema);
}
