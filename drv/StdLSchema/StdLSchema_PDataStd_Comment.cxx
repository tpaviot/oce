#ifndef _StdLSchema_PDataStd_Comment_HeaderFile
#include <StdLSchema_PDataStd_Comment.hxx>
#endif
#ifndef _PDataStd_Comment_HeaderFile
#include <PDataStd_Comment.hxx>
#endif
#include <StdLSchema_PDataStd_Comment.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_Comment,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_Comment,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_Comment::New() const
{
  return new PDataStd_Comment(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_Comment::SAdd(const Handle(PDataStd_Comment)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_Comment")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_CommentmyValue());

    }
  }
}

void StdLSchema_PDataStd_Comment::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_Comment::SAdd((Handle(PDataStd_Comment)&)p,theSchema);
}

void StdLSchema_PDataStd_Comment::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Comment) &pp = (Handle(PDataStd_Comment)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_CommentmyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_Comment::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_Comment::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_Comment::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Comment) &pp = (Handle(PDataStd_Comment)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HExtendedString) PDataStd_CommentmyValue;

    theSchema->ReadPersistentReference(PDataStd_CommentmyValue,f);
    pp->_CSFDB_SetPDataStd_CommentmyValue(PDataStd_CommentmyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_Comment::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_Comment::SRead(p,f,theSchema);
}
