#ifndef _XCAFSchema_PXCAFDoc_GraphNode_HeaderFile
#include <XCAFSchema_PXCAFDoc_GraphNode.hxx>
#endif
#ifndef _PXCAFDoc_GraphNode_HeaderFile
#include <PXCAFDoc_GraphNode.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_GraphNode.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_GraphNode,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_GraphNode,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_GraphNode::New() const
{
  return new PXCAFDoc_GraphNode(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_GraphNode::SAdd(const Handle(PXCAFDoc_GraphNode)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_GraphNode")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_GraphNodemyFathers());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_GraphNodemyChildren());

    }
  }
}

void XCAFSchema_PXCAFDoc_GraphNode::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_GraphNode::SAdd((Handle(PXCAFDoc_GraphNode)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_GraphNode::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_GraphNode) &pp = (Handle(PXCAFDoc_GraphNode)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_GraphNodemyFathers(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_GraphNodemyChildren(),f);
    XCAFSchema_Standard_GUID::SWrite(pp->_CSFDB_GetPXCAFDoc_GraphNodemyGraphID(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_GraphNode::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_GraphNode::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_GraphNode::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_GraphNode) &pp = (Handle(PXCAFDoc_GraphNode)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PXCAFDoc_GraphNodeSequence) PXCAFDoc_GraphNodemyFathers;

    theSchema->ReadPersistentReference(PXCAFDoc_GraphNodemyFathers,f);
    pp->_CSFDB_SetPXCAFDoc_GraphNodemyFathers(PXCAFDoc_GraphNodemyFathers);

    Handle(PXCAFDoc_GraphNodeSequence) PXCAFDoc_GraphNodemyChildren;

    theSchema->ReadPersistentReference(PXCAFDoc_GraphNodemyChildren,f);
    pp->_CSFDB_SetPXCAFDoc_GraphNodemyChildren(PXCAFDoc_GraphNodemyChildren);

    XCAFSchema_Standard_GUID::SRead((Standard_GUID&)pp->_CSFDB_GetPXCAFDoc_GraphNodemyGraphID(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_GraphNode::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_GraphNode::SRead(p,f,theSchema);
}
