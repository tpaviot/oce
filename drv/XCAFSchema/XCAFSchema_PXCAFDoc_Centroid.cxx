#ifndef _XCAFSchema_PXCAFDoc_Centroid_HeaderFile
#include <XCAFSchema_PXCAFDoc_Centroid.hxx>
#endif
#ifndef _PXCAFDoc_Centroid_HeaderFile
#include <PXCAFDoc_Centroid.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_Centroid.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_Centroid,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_Centroid,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_Centroid::New() const
{
  return new PXCAFDoc_Centroid(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_Centroid::SAdd(const Handle(PXCAFDoc_Centroid)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_Centroid")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_Centroid::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_Centroid::SAdd((Handle(PXCAFDoc_Centroid)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_Centroid::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Centroid) &pp = (Handle(PXCAFDoc_Centroid)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    XCAFSchema_gp_Pnt::SWrite(pp->_CSFDB_GetPXCAFDoc_CentroidmyPCentroid(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Centroid::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_Centroid::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_Centroid::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Centroid) &pp = (Handle(PXCAFDoc_Centroid)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    XCAFSchema_gp_Pnt::SRead((gp_Pnt&)pp->_CSFDB_GetPXCAFDoc_CentroidmyPCentroid(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Centroid::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_Centroid::SRead(p,f,theSchema);
}
