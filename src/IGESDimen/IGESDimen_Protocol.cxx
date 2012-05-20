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

#include <IGESDimen_Protocol.ixx>

#include <IGESDimen_GeneralNote.hxx>
#include <IGESDimen_AngularDimension.hxx>
#include <IGESDimen_GeneralSymbol.hxx>
#include <IGESDimen_BasicDimension.hxx>
#include <IGESDimen_LeaderArrow.hxx>
#include <IGESDimen_CenterLine.hxx>
#include <IGESDimen_LinearDimension.hxx>
#include <IGESDimen_CurveDimension.hxx>
#include <IGESDimen_NewDimensionedGeometry.hxx>
#include <IGESDimen_DiameterDimension.hxx>
#include <IGESDimen_NewGeneralNote.hxx>
#include <IGESDimen_DimensionDisplayData.hxx>
#include <IGESDimen_OrdinateDimension.hxx>
#include <IGESDimen_DimensionTolerance.hxx>
#include <IGESDimen_PointDimension.hxx>
#include <IGESDimen_DimensionUnits.hxx>
#include <IGESDimen_RadiusDimension.hxx>
#include <IGESDimen_DimensionedGeometry.hxx>
#include <IGESDimen_Section.hxx>
#include <IGESDimen_SectionedArea.hxx>
#include <IGESDimen_FlagNote.hxx>
#include <IGESDimen_WitnessLine.hxx>
#include <IGESDimen_GeneralLabel.hxx>

#include <IGESGeom.hxx>
#include <IGESGraph.hxx>
#include <IGESGeom_Protocol.hxx>
#include <IGESGraph_Protocol.hxx>

static int deja = 0;
static Handle(Standard_Type) atype01,atype02,atype03,atype04,atype05,atype06,
  atype07,atype08,atype09,atype10,atype11,atype12,atype13,atype14,atype15,
  atype16,atype17,atype18,atype19,atype20,atype21,atype22,atype23;

    IGESDimen_Protocol::IGESDimen_Protocol ()
{
  if (deja) return;  deja = 1;
  atype01 = STANDARD_TYPE(IGESDimen_AngularDimension);
  atype02 = STANDARD_TYPE(IGESDimen_BasicDimension);
  atype03 = STANDARD_TYPE(IGESDimen_CenterLine);
  atype04 = STANDARD_TYPE(IGESDimen_CurveDimension);
  atype05 = STANDARD_TYPE(IGESDimen_DiameterDimension);
  atype06 = STANDARD_TYPE(IGESDimen_DimensionDisplayData);
  atype07 = STANDARD_TYPE(IGESDimen_DimensionTolerance);
  atype08 = STANDARD_TYPE(IGESDimen_DimensionUnits);
  atype09 = STANDARD_TYPE(IGESDimen_DimensionedGeometry);
  atype10 = STANDARD_TYPE(IGESDimen_FlagNote);
  atype11 = STANDARD_TYPE(IGESDimen_GeneralLabel);
  atype12 = STANDARD_TYPE(IGESDimen_GeneralNote);
  atype13 = STANDARD_TYPE(IGESDimen_GeneralSymbol);
  atype14 = STANDARD_TYPE(IGESDimen_LeaderArrow);
  atype15 = STANDARD_TYPE(IGESDimen_LinearDimension);
  atype16 = STANDARD_TYPE(IGESDimen_NewDimensionedGeometry);
  atype17 = STANDARD_TYPE(IGESDimen_NewGeneralNote);
  atype18 = STANDARD_TYPE(IGESDimen_OrdinateDimension);
  atype10 = STANDARD_TYPE(IGESDimen_PointDimension);
  atype20 = STANDARD_TYPE(IGESDimen_RadiusDimension);
  atype21 = STANDARD_TYPE(IGESDimen_Section);
  atype22 = STANDARD_TYPE(IGESDimen_SectionedArea);
  atype23 = STANDARD_TYPE(IGESDimen_WitnessLine);
}

    Standard_Integer IGESDimen_Protocol::NbResources () const
      {  return 2;  }

    Handle(Interface_Protocol) IGESDimen_Protocol::Resource
  (const Standard_Integer num) const
{
  Handle(Interface_Protocol) res;
  if (num == 1) res = IGESGraph::Protocol();
  if (num == 2) res = IGESGeom::Protocol();
  return res;
}

    Standard_Integer IGESDimen_Protocol::TypeNumber
  (const Handle(Standard_Type)& atype) const
{
  if      (atype == atype01) return  1;
  else if (atype == atype02) return  2;
  else if (atype == atype03) return  3;
  else if (atype == atype04) return  4;
  else if (atype == atype05) return  5;
  else if (atype == atype06) return  6;
  else if (atype == atype07) return  7;
  else if (atype == atype08) return  8;
  else if (atype == atype09) return  9;
  else if (atype == atype10) return 10;
  else if (atype == atype11) return 11;
  else if (atype == atype12) return 12;
  else if (atype == atype13) return 13;
  else if (atype == atype14) return 14;
  else if (atype == atype15) return 15;
  else if (atype == atype16) return 16;
  else if (atype == atype17) return 17;
  else if (atype == atype18) return 18;
  else if (atype == atype19) return 19;
  else if (atype == atype20) return 20;
  else if (atype == atype21) return 21;
  else if (atype == atype22) return 22;
  else if (atype == atype23) return 23;
  return 0;
}
