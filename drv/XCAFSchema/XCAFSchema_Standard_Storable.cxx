#ifndef _XCAFSchema_Standard_Storable_HeaderFile
#include <XCAFSchema_Standard_Storable.hxx>
#endif
#ifndef _Standard_Storable_HeaderFile
#include <Standard_Storable.hxx>
#endif
#include <XCAFSchema_Standard_Storable.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void XCAFSchema_Standard_Storable::SWrite(const Standard_Storable& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginWriteObjectData();

  f.EndWriteObjectData();
}

void XCAFSchema_Standard_Storable::SRead(Standard_Storable& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginReadObjectData();

  f.EndReadObjectData();
}
