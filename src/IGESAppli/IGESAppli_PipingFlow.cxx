// Created by: CKY / Contract Toubro-Larsen
// Copyright (c) 1993-1999 Matra Datavision
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

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <IGESAppli_PipingFlow.ixx>
#include <Standard_DimensionMismatch.hxx>


IGESAppli_PipingFlow::IGESAppli_PipingFlow ()    {  }


    void  IGESAppli_PipingFlow::Init
  (const Standard_Integer nbContextFlags,
   const Standard_Integer aFlowType,
   const Handle(IGESData_HArray1OfIGESEntity)& allFlowAssocs,
   const Handle(IGESDraw_HArray1OfConnectPoint)& allConnectPoints,
   const Handle(IGESData_HArray1OfIGESEntity)& allJoins,
   const Handle(Interface_HArray1OfHAsciiString)& allFlowNames,
   const Handle(IGESGraph_HArray1OfTextDisplayTemplate)& allTextDisps,
   const Handle(IGESData_HArray1OfIGESEntity)& allContFlowAssocs)
{
  Standard_Integer num = allFlowAssocs->Length();
  if (allFlowAssocs->Lower()     != 1 ||
      allConnectPoints->Lower()  != 1 || allConnectPoints->Length()  != num ||
      allJoins->Lower()          != 1 || allJoins->Length()          != num ||
      allFlowNames->Lower()      != 1 || allFlowNames->Length()      != num ||
      allContFlowAssocs->Lower() != 1 || allContFlowAssocs->Length() != num )
    Standard_DimensionMismatch::Raise("IGESAppli_PipingFlow : Init");
  theNbContextFlags          = nbContextFlags;
  theTypeOfFlow              = aFlowType;
  theFlowAssociativities     = allFlowAssocs;
  theConnectPoints           = allConnectPoints;
  theJoins                   = allJoins;
  theFlowNames               = allFlowNames;
  theTextDisplayTemplates    = allTextDisps;
  theContFlowAssociativities = allContFlowAssocs;
  InitTypeAndForm(402,20);
}

    Standard_Boolean  IGESAppli_PipingFlow::OwnCorrect ()
{
  if (theNbContextFlags == 1) return Standard_False;
  theNbContextFlags = 1;
  return Standard_True;
}


    Standard_Integer  IGESAppli_PipingFlow::NbContextFlags () const
{
  return theNbContextFlags;
}

    Standard_Integer  IGESAppli_PipingFlow::NbFlowAssociativities () const
{
  return theFlowAssociativities->Length();
}

    Standard_Integer  IGESAppli_PipingFlow::NbConnectPoints () const
{
  return theConnectPoints->Length();
}

    Standard_Integer  IGESAppli_PipingFlow::NbJoins () const
{
  return theJoins->Length();
}

    Standard_Integer  IGESAppli_PipingFlow::NbFlowNames () const
{
  return theFlowNames->Length();
}

    Standard_Integer  IGESAppli_PipingFlow::NbTextDisplayTemplates () const
{
  return theTextDisplayTemplates->Length();
}

    Standard_Integer  IGESAppli_PipingFlow::NbContFlowAssociativities () const
{
  return theContFlowAssociativities->Length();
}

    Standard_Integer  IGESAppli_PipingFlow::TypeOfFlow () const
{
  return theTypeOfFlow;
}

    Handle(IGESData_IGESEntity)  IGESAppli_PipingFlow::FlowAssociativity
  (const Standard_Integer Index) const
{
  return theFlowAssociativities->Value(Index);
}

    Handle(IGESDraw_ConnectPoint)  IGESAppli_PipingFlow::ConnectPoint
  (const Standard_Integer Index) const
{
  return theConnectPoints->Value(Index);
}

    Handle(IGESData_IGESEntity)  IGESAppli_PipingFlow::Join
  (const Standard_Integer Index) const
{
  return theJoins->Value(Index);
}

    Handle(TCollection_HAsciiString)  IGESAppli_PipingFlow::FlowName
  (const Standard_Integer Index) const
{
  return theFlowNames->Value(Index);
}

    Handle(IGESGraph_TextDisplayTemplate)  IGESAppli_PipingFlow::TextDisplayTemplate
  (const Standard_Integer Index) const
{
  return theTextDisplayTemplates->Value(Index);
}

    Handle(IGESData_IGESEntity)  IGESAppli_PipingFlow::ContFlowAssociativity
  (const Standard_Integer Index) const
{
  return theContFlowAssociativities->Value(Index);
}
