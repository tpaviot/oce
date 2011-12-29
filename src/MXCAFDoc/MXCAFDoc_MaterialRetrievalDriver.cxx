// File:      MXCAFDoc_MaterialRetrievalDriver.cxx
// Created:   10.12.08 09:46:46
// Author:    Pavel TELKOV
// Copyright: Open CASCADE 2008

#include <MXCAFDoc_MaterialRetrievalDriver.ixx>
#include <PXCAFDoc_Material.hxx>
#include <XCAFDoc_Material.hxx>

#include <TCollection_HAsciiString.hxx>
#include <PCollection_HAsciiString.hxx>


//=======================================================================
//function : MCAFDoc_MaterialRetrievalDriver
//purpose  : 
//=======================================================================

MXCAFDoc_MaterialRetrievalDriver::MXCAFDoc_MaterialRetrievalDriver
  (const Handle(CDM_MessageDriver)& theMsgDriver) : MDF_ARDriver (theMsgDriver)
{}

//=======================================================================
//function : VersionNumber
//purpose  : 
//=======================================================================

Standard_Integer MXCAFDoc_MaterialRetrievalDriver::VersionNumber() const
{ return 0; }

//=======================================================================
//function : SourceType
//purpose  : 
//=======================================================================

Handle(Standard_Type) MXCAFDoc_MaterialRetrievalDriver::SourceType() const
{
  static Handle(Standard_Type) sourceType = STANDARD_TYPE(PXCAFDoc_Material);
  return sourceType;
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) MXCAFDoc_MaterialRetrievalDriver::NewEmpty() const
{
  return new XCAFDoc_Material();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void MXCAFDoc_MaterialRetrievalDriver::Paste(const Handle(PDF_Attribute)& Source,
                                             const Handle(TDF_Attribute)& Target,
                                             const Handle(MDF_RRelocationTable)& RelocTable) const
{
  Handle(PXCAFDoc_Material) S = Handle(PXCAFDoc_Material)::DownCast (Source);
  Handle(XCAFDoc_Material) T = Handle(XCAFDoc_Material)::DownCast (Target);
  
  Handle(TCollection_HAsciiString) aName, aDescr, aDensName, aDensValType;
  if ( !S->GetName().IsNull() )
    aName = new TCollection_HAsciiString( (S->GetName())->Convert() );
  if ( !S->GetDescription().IsNull() )
    aDescr = new TCollection_HAsciiString( (S->GetDescription())->Convert() );
  if ( !S->GetDensName().IsNull() )
    aDensName = new TCollection_HAsciiString( (S->GetDensName())->Convert() );
  if ( !S->GetDensValType().IsNull() )
    aDensValType = new TCollection_HAsciiString( (S->GetDensValType())->Convert() );

  T->Set(aName, aDescr, S->GetDensity(), aDensName, aDensValType);
}
