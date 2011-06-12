// File:	RWStepElement_RWCurve3dElementDescriptor.cxx
// Created:	Thu Dec 12 17:28:59 2002 
// Author:	data exchange team
// Generator:	ExpToCas (EXPRESS -> CASCADE/XSTEP Translator) V1.2
// Copyright:	Open CASCADE 2002

#include <RWStepElement_RWCurve3dElementDescriptor.ixx>
#include <StepElement_CurveElementPurposeMember.hxx>
#include <StepElement_HArray1OfHSequenceOfCurveElementPurposeMember.hxx>
#include <StepElement_HSequenceOfCurveElementPurposeMember.hxx>

//=======================================================================
//function : RWStepElement_RWCurve3dElementDescriptor
//purpose  : 
//=======================================================================

RWStepElement_RWCurve3dElementDescriptor::RWStepElement_RWCurve3dElementDescriptor ()
{
}

//=======================================================================
//function : ReadStep
//purpose  : 
//=======================================================================

void RWStepElement_RWCurve3dElementDescriptor::ReadStep (const Handle(StepData_StepReaderData)& data,
                                                         const Standard_Integer num,
                                                         Handle(Interface_Check)& ach,
                                                         const Handle(StepElement_Curve3dElementDescriptor) &ent) const
{
  // Check number of parameters
  if ( ! data->CheckNbParams(num,3,ach,"curve3d_element_descriptor") ) return;

  // Inherited fields of ElementDescriptor

  StepElement_ElementOrder aElementDescriptor_TopologyOrder = StepElement_Linear;
  if (data->ParamType (num, 1) == Interface_ParamEnum) {
    Standard_CString text = data->ParamCValue(num, 1);
    if      (strcmp(text, ".LINEAR.")==0) aElementDescriptor_TopologyOrder = StepElement_Linear;
    else if (strcmp(text, ".QUADRATIC.")==0) aElementDescriptor_TopologyOrder = StepElement_Quadratic;
    else if (strcmp(text, ".CUBIC.")==0) aElementDescriptor_TopologyOrder = StepElement_Cubic;
    else ach->AddFail("Parameter #1 (element_descriptor.topology_order) has not allowed value");
  }
  else ach->AddFail("Parameter #1 (element_descriptor.topology_order) is not enumeration");

  Handle(TCollection_HAsciiString) aElementDescriptor_Description;
  data->ReadString (num, 2, "element_descriptor.description", ach, aElementDescriptor_Description);

  // Own fields of Curve3dElementDescriptor

  Handle(StepElement_HArray1OfHSequenceOfCurveElementPurposeMember) aPurpose;
  Standard_Integer sub3 = 0;
  if ( data->ReadSubList (num, 3, "purpose", ach, sub3) ) {
    Standard_Integer nb0 = data->NbParams(sub3);
    //Standard_Integer nbj0 = data->NbParams(data->ParamNumber(sub3,1));
    aPurpose = new StepElement_HArray1OfHSequenceOfCurveElementPurposeMember (1, nb0);
    for ( Standard_Integer i0=1; i0 <= nb0; i0++ ) {
      Handle(StepElement_HSequenceOfCurveElementPurposeMember) HSCEPM =
        new StepElement_HSequenceOfCurveElementPurposeMember;
      Standard_Integer subj3 = 0;
      if ( data->ReadSubList (sub3, i0, "sub-part(purpose)", ach, subj3) ) {
        Standard_Integer num4 = subj3;
        Standard_Integer nbj0 = data->NbParams(data->ParamNumber(sub3,i0));
        for ( Standard_Integer j0=1; j0 <= nbj0; j0++ ) {
          Handle(StepElement_CurveElementPurposeMember) aMember = new StepElement_CurveElementPurposeMember;
          data->ReadMember(num4, j0, "curve_element_purpose", ach, aMember);
          //data->ReadEntity (num4, j0, "curve_element_purpose", ach, anIt0);
          HSCEPM->Append(aMember);
        }
      }
      aPurpose->SetValue(i0, HSCEPM);
    }
  }

  // Initialize entity
  ent->Init(aElementDescriptor_TopologyOrder,
            aElementDescriptor_Description,
            aPurpose);
}

//=======================================================================
//function : WriteStep
//purpose  : 
//=======================================================================

void RWStepElement_RWCurve3dElementDescriptor::WriteStep (StepData_StepWriter& SW,
                                                          const Handle(StepElement_Curve3dElementDescriptor) &ent) const
{

  // Inherited fields of ElementDescriptor

  switch (ent->StepElement_ElementDescriptor::TopologyOrder()) {
    case StepElement_Linear: SW.SendEnum (".LINEAR."); break;
    case StepElement_Quadratic: SW.SendEnum (".QUADRATIC."); break;
    case StepElement_Cubic: SW.SendEnum (".CUBIC."); break;
  }

  SW.Send (ent->StepElement_ElementDescriptor::Description());

  // Own fields of Curve3dElementDescriptor

  SW.OpenSub();
  for (Standard_Integer i2=1; i2 <= ent->Purpose()->Length(); i2++ ) {
    SW.NewLine(Standard_False);
    SW.OpenSub();
    Handle(StepElement_HSequenceOfCurveElementPurposeMember) HSCEPM = ent->Purpose()->Value(i2);
    for (Standard_Integer j2=1; j2 <= HSCEPM->Length(); j2++ ) {
      Handle(StepElement_CurveElementPurposeMember) Var0 = HSCEPM->Value(j2);
      SW.Send (Var0);
    }
    SW.CloseSub();
  }
  SW.CloseSub();
}

//=======================================================================
//function : Share
//purpose  : 
//=======================================================================

void RWStepElement_RWCurve3dElementDescriptor::Share (const Handle(StepElement_Curve3dElementDescriptor) &ent,
                                                      Interface_EntityIterator& iter) const
{

  // Inherited fields of ElementDescriptor

  // Own fields of Curve3dElementDescriptor
/* CKY  17JUN04. Content is made of strings and enums. No entity !
  for (Standard_Integer i1=1; i1 <= ent->Purpose()->Length(); i1++ ) {
    Handle(StepElement_HSequenceOfCurveElementPurposeMember) HSCEPM = ent->Purpose()->Value(i1);
    for (Standard_Integer i2=1; i2 <= HSCEPM->Length(); i2++ ) {
      Handle(StepElement_CurveElementPurposeMember) Var1 = HSCEPM->Value(i2);
      iter.AddItem (Var1);
    }
  }
*/
}
