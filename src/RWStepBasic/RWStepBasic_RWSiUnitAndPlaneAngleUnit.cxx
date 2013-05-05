// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

#include <RWStepBasic_RWSiUnitAndPlaneAngleUnit.ixx>
#include <StepBasic_SiUnit.hxx>
#include <StepBasic_PlaneAngleUnit.hxx>
#include <StepBasic_DimensionalExponents.hxx>
#include <StepBasic_SiPrefix.hxx>
#include <StepBasic_SiUnitName.hxx>
#include <RWStepBasic_RWSiUnit.hxx>


RWStepBasic_RWSiUnitAndPlaneAngleUnit::RWStepBasic_RWSiUnitAndPlaneAngleUnit ()
{
}

void RWStepBasic_RWSiUnitAndPlaneAngleUnit::ReadStep(const Handle(StepData_StepReaderData)& data,
						     const Standard_Integer num0,
						     Handle(Interface_Check)& ach,
						     const Handle(StepBasic_SiUnitAndPlaneAngleUnit)& ent) const
{
  Standard_Integer num = num0;
  
  // --- Instance of common supertype NamedUnit ---
  if (!data->CheckNbParams(num,1,ach,"named_unit")) return;
	
  // --- field : dimensions ---
  // --- this field is redefined ---
  //szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
  data->CheckDerived(num,1,"dimensions",ach,Standard_False);
  num = data->NextForComplex(num);

  // --- Instance of plex componant PlaneAngleUnit ---
  if (!data->CheckNbParams(num,0,ach,"plane_angle_unit")) return;
  num = data->NextForComplex(num);

  // --- Instance of plex componant SiUnit ---
  if (!data->CheckNbParams(num,2,ach,"si_unit")) return;

  // --- field : prefix ---
  RWStepBasic_RWSiUnit reader;
  StepBasic_SiPrefix aPrefix = StepBasic_spExa; // (0)
  Standard_Boolean hasAprefix = Standard_False;
  if (data->IsParamDefined(num,1)) {
    if (data->ParamType(num,1) == Interface_ParamEnum) {
      Standard_CString text = data->ParamCValue(num,1);
      hasAprefix = reader.DecodePrefix(aPrefix,text);
      if(!hasAprefix){
	      ach->AddFail("Enumeration si_prefix has not an allowed value");
        return;
      }
    }
    else{
      ach->AddFail("Parameter #2 (prefix) is not an enumeration");
      return;
    }
  }
	
  // --- field : name ---
  StepBasic_SiUnitName aName = StepBasic_sunMetre; // 0
  if (data->ParamType(num,2) == Interface_ParamEnum) {
    Standard_CString text = data->ParamCValue(num,2);
    if(!reader.DecodeName(aName,text)){
      ach->AddFail("Enumeration si_unit_name has not an allowed value");
      return;
    }
  }
  else{
    ach->AddFail("Parameter #2 (name) is not an enumeration");
    return;
  }
  
 // @todo Apart the fail, nothing is done , and wrong enum values are used

  //--- Initialisation of the red entity ---
  ent->Init(hasAprefix,aPrefix,aName);
}


void RWStepBasic_RWSiUnitAndPlaneAngleUnit::WriteStep(StepData_StepWriter& SW,
						      const Handle(StepBasic_SiUnitAndPlaneAngleUnit)& ent) const
{
  // --- Instance of common supertype NamedUnit ---
  SW.StartEntity("NAMED_UNIT");
  
  // --- field : dimensions ---
  // --- redefined field ---
  SW.SendDerived();

  // --- Instance of plex componant PlaneAngleUnit ---
  SW.StartEntity("PLANE_ANGLE_UNIT");

  // --- Instance of plex componant SiUnit ---
  SW.StartEntity("SI_UNIT");
	
  // --- field : prefix ---
  RWStepBasic_RWSiUnit writer;
  Standard_Boolean hasAprefix = ent->HasPrefix();
  if (hasAprefix) 
    SW.SendEnum(writer.EncodePrefix(ent->Prefix()));
  else
    SW.SendUndef();
  
  // --- field : name ---
  SW.SendEnum(writer.EncodeName(ent->Name()));
}
