#ifndef _XCAFSchema_Quantity_Color_HeaderFile
#include <XCAFSchema_Quantity_Color.hxx>
#endif
#ifndef _Quantity_Color_HeaderFile
#include <Quantity_Color.hxx>
#endif
#include <XCAFSchema_Quantity_Color.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void XCAFSchema_Quantity_Color::SWrite(const Quantity_Color& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginWriteObjectData();
  f.PutShortReal(pp._CSFDB_GetQuantity_ColorMyRed());
  f.PutShortReal(pp._CSFDB_GetQuantity_ColorMyGreen());
  f.PutShortReal(pp._CSFDB_GetQuantity_ColorMyBlue());

  f.EndWriteObjectData();
}

void XCAFSchema_Quantity_Color::SRead(Quantity_Color& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginReadObjectData();

    Standard_ShortReal Quantity_ColorMyRed;
    f.GetShortReal(Quantity_ColorMyRed);
    pp._CSFDB_SetQuantity_ColorMyRed(Quantity_ColorMyRed);

    Standard_ShortReal Quantity_ColorMyGreen;
    f.GetShortReal(Quantity_ColorMyGreen);
    pp._CSFDB_SetQuantity_ColorMyGreen(Quantity_ColorMyGreen);

    Standard_ShortReal Quantity_ColorMyBlue;
    f.GetShortReal(Quantity_ColorMyBlue);
    pp._CSFDB_SetQuantity_ColorMyBlue(Quantity_ColorMyBlue);

  f.EndReadObjectData();
}
