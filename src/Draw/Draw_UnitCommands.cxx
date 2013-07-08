// Created on: 1995-02-23
// Created by: Remi LEQUETTE
// Copyright (c) 1995-1999 Matra Datavision
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


#include <Draw.ixx>

#include <TCollection_AsciiString.hxx>
#include <Units_Token.hxx>
#include <Units_UnitSentence.hxx>
#include <Units_TokensSequence.hxx>
#include <UnitsAPI.hxx>
#include <Units.hxx>
#include <Units_UnitsDictionary.hxx>


//=======================================================================
//function : parsing
//purpose  : parsing of unit's expression
//=======================================================================
static Standard_Integer parsing
  (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 2) {
    di << "Usage : " << argv[0] << " string [nbiter]" << "\n";
    return 1;
  }

  TCollection_AsciiString aStrTok(argv[1]);
  Standard_Integer nbIter =1;
  if(argc >2)
    nbIter = Draw::Atoi(argv[2]);
  UnitsAPI::SetLocalSystem();
  Handle(Units_Token) atoken;
  Units_UnitSentence aUnitSent(aStrTok.ToCString());
  
  if(!aUnitSent.IsDone()) {
    di<<"can not create a sentence"<<"\n";
    return 1;
  }

  Standard_Integer i =1;
  for( ; i <= nbIter; i++) {
    aUnitSent.Analyse();
    //aUnitSent.Dump();
    Handle(Units_TokensSequence) aseq = aUnitSent.Sequence();
  }
  atoken = aUnitSent.Evaluate();
  di<<"Token word : "<<atoken->Word().ToCString()<<"\n";
  return 0;
}


//=======================================================================
//function : unitsdico
//purpose  : dump dictionary of units
//=======================================================================
static Standard_Integer unitsdico
  (Draw_Interpretor& /* di */, Standard_Integer /*argc*/, const char** /*argv*/)
{
  UnitsAPI::SetLocalSystem();
  Standard_Integer mode = 2;
  Units::DictionaryOfUnits(Standard_False)->Dump(mode);
  return 0;
}


//=======================================================================
//function : converttoSI
//purpose  : 
//=======================================================================
static Standard_Integer converttoSI
  (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 3) {
    di<<"Invalid number of parameter, use: unitconvtoSI real string"<<"\n";
    return 1;
  }

  Standard_Real aData = Draw::Atof(argv[1]);
  Standard_CString aUnit = argv[2];

  Standard_Real res = UnitsAPI::AnyToSI(aData,aUnit);
  di<<"result: "<<res<<"\n";

  return 0;
}


//=======================================================================
//function : converttoMDTV
//purpose  : 
//=======================================================================
static Standard_Integer converttoMDTV
  (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 3) {
    di<<"Invalid number of parameter, use: unitconvtoMDTV real string"<<"\n";
    return 1;
  }

  Standard_Real aData = Draw::Atof(argv[1]);
  Standard_CString aUnit = argv[2];

  UnitsAPI::SetLocalSystem(UnitsAPI_MDTV);
  Standard_Real res = UnitsAPI::AnyToLS(aData,aUnit);
  di<<"result: "<<res<<"\n";
  
  return 0;
}


//=======================================================================
//function : unit
//purpose  : 
//=======================================================================

static Standard_Integer unit(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  if(n == 4) {
    cout << Units::Convert(Draw::Atof(a[1]), a[2], a[3]) << endl;
    return 0;
  }
  else
    return 1;
}


//=======================================================================
//function : UnitCommands
//purpose  : 
//=======================================================================

void Draw::UnitCommands(Draw_Interpretor& theCommands)
{
  static Standard_Boolean Done = Standard_False;
  if (Done) return;
  Done = Standard_True;

  const char* g = "DRAW Unit Commands";
  
  theCommands.Add("unitparsing", "unitparsing string [nbiter]",
		  __FILE__,parsing,g);
  theCommands.Add("unitsdico","unitsdico",
                  __FILE__,unitsdico,g);
  theCommands.Add("unitconvtoSI","unitconvtoSI real string",
		  __FILE__,converttoSI,g);
  theCommands.Add("unitconvtoMDTV","unitconvtoMDTV real string",
		  __FILE__,converttoMDTV,g);
  theCommands.Add("unit","unit value unitfrom unitto",
		  __FILE__,unit,g);
}
