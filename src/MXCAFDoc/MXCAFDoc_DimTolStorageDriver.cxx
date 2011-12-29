// File:      MXCAFDoc_DimTolStorageDriver.cxx
// Created:   10.12.08 09:06:26
// Author:    Pavel TELKOV
// Copyright: Open CASCADE 2008

#include <MXCAFDoc_DimTolStorageDriver.ixx>
#include <XCAFDoc_DimTol.hxx>
#include <PXCAFDoc_DimTol.hxx>

#include <TCollection_HAsciiString.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <PCollection_HAsciiString.hxx>
#include <PColStd_HArray1OfReal.hxx>

//=======================================================================
//function : MXCAFDoc_DimTolStorageDriver
//purpose  : 
//=======================================================================

MXCAFDoc_DimTolStorageDriver::MXCAFDoc_DimTolStorageDriver
  (const Handle(CDM_MessageDriver)& theMsgDriver) : MDF_ASDriver (theMsgDriver)
{}

//=======================================================================
//function : VersionNumber
//purpose  : 
//=======================================================================

Standard_Integer MXCAFDoc_DimTolStorageDriver::VersionNumber() const
{ return 0; }

//=======================================================================
//function : SourceType
//purpose  : 
//=======================================================================

Handle(Standard_Type) MXCAFDoc_DimTolStorageDriver::SourceType() const
{
  static Handle(Standard_Type) sourceType = STANDARD_TYPE(XCAFDoc_DimTol);
  return sourceType;
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(PDF_Attribute) MXCAFDoc_DimTolStorageDriver::NewEmpty() const
{
  return new PXCAFDoc_DimTol();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void MXCAFDoc_DimTolStorageDriver::Paste(const Handle(TDF_Attribute)& Source,
                                         const Handle(PDF_Attribute)& Target,
                                         const Handle(MDF_SRelocationTable)& RelocTable) const
{
  Handle(XCAFDoc_DimTol) S = Handle(XCAFDoc_DimTol)::DownCast (Source);
  Handle(PXCAFDoc_DimTol) T = Handle(PXCAFDoc_DimTol)::DownCast (Target);
  Handle(TColStd_HArray1OfReal) aHArr = S->GetVal();
  Handle(PColStd_HArray1OfReal) aVals;
  if ( !aHArr.IsNull() )
  {
    Standard_Integer i = aHArr->Lower(), n = aHArr->Upper();
    aVals = new PColStd_HArray1OfReal( i, n );
     for( ; i <= n; i++ )
       aVals->SetValue( i, aHArr->Value( i ) );
  }
  Handle(TCollection_HAsciiString) aNameStr = S->GetName();
  Handle(TCollection_HAsciiString) aDescrStr = S->GetDescription();
  
  Handle(PCollection_HAsciiString) aName, aDescr;
  if ( !aNameStr.IsNull() )
    aName = new PCollection_HAsciiString (aNameStr->String());
  if ( !aDescrStr.IsNull() )
    aDescr = new PCollection_HAsciiString (aDescrStr->String());

  T->Set(S->GetKind(), aVals, aName, aDescr);
}
