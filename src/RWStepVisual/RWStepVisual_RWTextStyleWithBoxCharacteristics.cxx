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


#include <RWStepVisual_RWTextStyleWithBoxCharacteristics.ixx>
#include <Standard_Real.hxx>
#include <StepVisual_TextStyleForDefinedFont.hxx>

#include <StepVisual_HArray1OfBoxCharacteristicSelect.hxx>

#include <Interface_EntityIterator.hxx>


#include <StepVisual_TextStyleWithBoxCharacteristics.hxx>


RWStepVisual_RWTextStyleWithBoxCharacteristics::RWStepVisual_RWTextStyleWithBoxCharacteristics () {}

void RWStepVisual_RWTextStyleWithBoxCharacteristics::ReadStep
(const Handle(StepData_StepReaderData)& data,
 const Standard_Integer num,
 Handle(Interface_Check)& ach,
 const Handle(StepVisual_TextStyleWithBoxCharacteristics)& ent) const
{
  
  
  // --- Number of Parameter Control ---
  
  if (!data->CheckNbParams(num,3,ach,"text_style_with_box_characteristics has not 3 parameter(s)")) return;
  
  // --- inherited field : name ---
  
  Handle(TCollection_HAsciiString) aName;
  //szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
  data->ReadString (num,1,"name",ach,aName);
  
  // --- inherited field : characterAppearance ---
  
  Handle(StepVisual_TextStyleForDefinedFont) aCharacterAppearance;
  //szv#4:S4163:12Mar99 `Standard_Boolean stat2 =` not needed
  data->ReadEntity(num, 2,"character_appearance", ach, 
		   STANDARD_TYPE(StepVisual_TextStyleForDefinedFont), aCharacterAppearance);
  
  // --- own field : characteristics ---

  Standard_Integer numr, numpr;
  TCollection_AsciiString TypeHeigth("BOX_HEIGHT");
  TCollection_AsciiString TypeWidth("BOX_WIDTH");
  TCollection_AsciiString TypeSlant("BOX_SLANT_ANGLE");
  TCollection_AsciiString TypeRotate("BOX_ROTATE_ANGLE");
  TCollection_AsciiString TrueType;

  Handle(StepVisual_HArray1OfBoxCharacteristicSelect) aCharacteristics;
  Standard_Real aCharacteristicsItem;
  StepVisual_BoxCharacteristicSelect aBoxCharacteristicSelect;

  Standard_Integer nsub3;
  nsub3 = data->SubListNumber(num, 3, Standard_False);
  if (nsub3 !=0) {
    Standard_Integer nb3 = data->NbParams(nsub3);
    aCharacteristics = new StepVisual_HArray1OfBoxCharacteristicSelect(1, nb3);
    for (Standard_Integer i3 = 1; i3 <= nb3; i3 ++) {
      // Looks for true type :
      //szv#4:S4163:12Mar99 `Standard_Boolean statType =` not needed
      if (data->ReadTypedParam(nsub3,i3,Standard_True,"characteristics",ach,numr,numpr,TrueType)) {
	//szv#4:S4163:12Mar99 `Standard_Boolean stat3 =` not needed
	if (data->ReadReal (numr,numpr,"characteristics",ach,aCharacteristicsItem)) {
	  aBoxCharacteristicSelect.SetRealValue(aCharacteristicsItem);
	  if (TrueType == TypeHeigth)
	    aBoxCharacteristicSelect.SetTypeOfContent(1);
	  else if (TrueType == TypeWidth) 
	    aBoxCharacteristicSelect.SetTypeOfContent(2);
	  else if (TrueType == TypeSlant) 
	    aBoxCharacteristicSelect.SetTypeOfContent(3);
	  else if (TrueType == TypeRotate) 
	    aBoxCharacteristicSelect.SetTypeOfContent(4);
	  else {
	    ach->AddFail("Parameter #3 (characteristics) item has illegal TYPE");
	  }
	  aCharacteristics->SetValue(i3, aBoxCharacteristicSelect);
	}
	else {
	  ach->AddFail("Parameter #3 (characteristics) item is not a REAL");
	}
      }
      else {
	ach->AddFail("Parameter #3 (characteristics) item is not TYPED");
      }
    }
  }
  else {
    ach->AddFail("Parameter #3 (characteristics) is not a LIST");
  }
  
  //--- Initialisation of the read entity ---
  
  ent->Init(aName, aCharacterAppearance, aCharacteristics);
}


void RWStepVisual_RWTextStyleWithBoxCharacteristics::WriteStep
(StepData_StepWriter& SW,
 const Handle(StepVisual_TextStyleWithBoxCharacteristics)& ent) const
{
  
  // --- inherited field name ---
  
  SW.Send(ent->Name());
  
  // --- inherited field characterAppearance ---
  
  SW.Send(ent->CharacterAppearance());
  
  // --- own field : characteristics ---
  // Attention : a modifier avant utilisation

  SW.Send(ent->Characteristics());
}


void RWStepVisual_RWTextStyleWithBoxCharacteristics::Share(const Handle(StepVisual_TextStyleWithBoxCharacteristics)& ent, Interface_EntityIterator& iter) const
{
  
  iter.GetOneItem(ent->CharacterAppearance());
}

