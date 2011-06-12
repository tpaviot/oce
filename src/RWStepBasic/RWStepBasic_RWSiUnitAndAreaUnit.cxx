// File:	RWStepBasic_RWSiUnitAndAreaUnit.cxx
// Created:	Mon Oct 11 15:37:59 1999
// Author:	data exchange team
//		<det@friendox>


#include <RWStepBasic_RWSiUnitAndAreaUnit.ixx>
#include <StepBasic_SiUnit.hxx>
#include <RWStepBasic_RWSiUnit.hxx>
#include <StepBasic_DimensionalExponents.hxx>


RWStepBasic_RWSiUnitAndAreaUnit::RWStepBasic_RWSiUnitAndAreaUnit ()
{
}

void RWStepBasic_RWSiUnitAndAreaUnit::ReadStep(const Handle(StepData_StepReaderData)& data,
					       const Standard_Integer num0,
					       Handle(Interface_Check)& ach,
					       const Handle(StepBasic_SiUnitAndAreaUnit)& ent) const
{
  Standard_Integer num = 0;
  data->NamedForComplex("AREA_UNIT",num0,num,ach);
  if (!data->CheckNbParams(num,0,ach,"area_unit")) return;

  data->NamedForComplex("NAMED_UNIT NMDUNT",num0,num,ach);
  if (!data->CheckNbParams(num,1,ach,"named_unit")) return;
  Handle(StepBasic_DimensionalExponents) aDimensions;
  data->ReadEntity(num, 1,"dimensions", ach, STANDARD_TYPE(StepBasic_DimensionalExponents), aDimensions);
  
  data->NamedForComplex("SI_UNIT SUNT",num0,num,ach);
  if (!data->CheckNbParams(num,2,ach,"si_unit")) return;
  
  RWStepBasic_RWSiUnit reader;
  StepBasic_SiPrefix aPrefix = StepBasic_spExa; // (0)
  Standard_Boolean hasAprefix = Standard_False;
  if (data->IsParamDefined(num,1)) {
    if (data->ParamType(num,1) == Interface_ParamEnum) {
      Standard_CString text = data->ParamCValue(num,1);
      hasAprefix = reader.DecodePrefix(aPrefix,text);
      if(!hasAprefix)
	ach->AddFail("Enumeration si_prefix has not an allowed value");
    }
    else ach->AddFail("Parameter #2 (prefix) is not an enumeration");
  }
     
  StepBasic_SiUnitName aName = StepBasic_sunMetre; // 0
  if (data->ParamType(num,2) == Interface_ParamEnum) {
    Standard_CString text = data->ParamCValue(num,2);
    if(!reader.DecodeName(aName,text))
      ach->AddFail("Enumeration si_unit_name has not an allowed value");
  }
  else ach->AddFail("Parameter #3 (name) is not an enumeration");
  
  // @todo Apart the fail, nothing is done , and wrong enum values are used
 
  ent->Init(hasAprefix,aPrefix,aName);
  ent->SetDimensions(aDimensions);
}

void RWStepBasic_RWSiUnitAndAreaUnit::WriteStep(StepData_StepWriter& SW,
						const Handle(StepBasic_SiUnitAndAreaUnit)& ent) const
{
  SW.StartEntity("AREA_UNIT");
  SW.StartEntity("NAMED_UNIT");
  SW.Send(ent->Dimensions());
  SW.StartEntity("SI_UNIT");
  
  RWStepBasic_RWSiUnit writer;
  Standard_Boolean hasAprefix = ent->HasPrefix();
  if (hasAprefix) 
    SW.SendEnum(writer.EncodePrefix(ent->Prefix()));
  else
    SW.SendUndef();
  
  SW.SendEnum(writer.EncodeName(ent->Name()));   
}
  
