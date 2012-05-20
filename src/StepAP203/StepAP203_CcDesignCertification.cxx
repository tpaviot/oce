// Created on: 1999-11-26
// Created by: Andrey BETENEV
// Copyright (c) 1999 Matra Datavision
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

// Generator:	ExpToCas (EXPRESS -> CASCADE/XSTEP Translator) V1.0

#include <StepAP203_CcDesignCertification.ixx>

//=======================================================================
//function : StepAP203_CcDesignCertification
//purpose  : 
//=======================================================================

StepAP203_CcDesignCertification::StepAP203_CcDesignCertification ()
{
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void StepAP203_CcDesignCertification::Init (const Handle(StepBasic_Certification) &aCertificationAssignment_AssignedCertification,
                                            const Handle(StepAP203_HArray1OfCertifiedItem) &aItems)
{
  StepBasic_CertificationAssignment::Init(aCertificationAssignment_AssignedCertification);

  theItems = aItems;
}

//=======================================================================
//function : Items
//purpose  : 
//=======================================================================

Handle(StepAP203_HArray1OfCertifiedItem) StepAP203_CcDesignCertification::Items () const
{
  return theItems;
}

//=======================================================================
//function : SetItems
//purpose  : 
//=======================================================================

void StepAP203_CcDesignCertification::SetItems (const Handle(StepAP203_HArray1OfCertifiedItem) &aItems)
{
  theItems = aItems;
}
