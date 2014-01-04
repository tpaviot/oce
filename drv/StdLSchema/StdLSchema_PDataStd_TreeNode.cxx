#ifndef _StdLSchema_PDataStd_TreeNode_HeaderFile
#include <StdLSchema_PDataStd_TreeNode.hxx>
#endif
#ifndef _PDataStd_TreeNode_HeaderFile
#include <PDataStd_TreeNode.hxx>
#endif
#include <StdLSchema_PDataStd_TreeNode.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_TreeNode,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_TreeNode,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_TreeNode::New() const
{
  return new PDataStd_TreeNode(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_TreeNode::SAdd(const Handle(PDataStd_TreeNode)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_TreeNode")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_TreeNodemyFirst());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_TreeNodemyNext());

    }
  }
}

void StdLSchema_PDataStd_TreeNode::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_TreeNode::SAdd((Handle(PDataStd_TreeNode)&)p,theSchema);
}

void StdLSchema_PDataStd_TreeNode::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_TreeNode) &pp = (Handle(PDataStd_TreeNode)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_TreeNodemyFirst(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_TreeNodemyNext(),f);
    StdLSchema_Standard_GUID::SWrite(pp->_CSFDB_GetPDataStd_TreeNodemyTreeID(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_TreeNode::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_TreeNode::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_TreeNode::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_TreeNode) &pp = (Handle(PDataStd_TreeNode)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PDataStd_TreeNode) PDataStd_TreeNodemyFirst;

    theSchema->ReadPersistentReference(PDataStd_TreeNodemyFirst,f);
    pp->_CSFDB_SetPDataStd_TreeNodemyFirst(PDataStd_TreeNodemyFirst);

    Handle(PDataStd_TreeNode) PDataStd_TreeNodemyNext;

    theSchema->ReadPersistentReference(PDataStd_TreeNodemyNext,f);
    pp->_CSFDB_SetPDataStd_TreeNodemyNext(PDataStd_TreeNodemyNext);

    StdLSchema_Standard_GUID::SRead((Standard_GUID&)pp->_CSFDB_GetPDataStd_TreeNodemyTreeID(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_TreeNode::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_TreeNode::SRead(p,f,theSchema);
}
