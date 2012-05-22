// Created on: 2001-09-19
// Created by: Alexander GRIGORIEV
// Copyright (c) 2001-2012 OPEN CASCADE SAS
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


#include <XmlLDrivers_NamespaceDef.ixx>

//=======================================================================
//function : XmlLDrivers_NamespaceDef
//purpose  : Empty constructor
//=======================================================================

XmlLDrivers_NamespaceDef::XmlLDrivers_NamespaceDef ()
 {}

//=======================================================================
//function : XmlLDrivers_NamespaceDef
//purpose  : Constructor
//=======================================================================

XmlLDrivers_NamespaceDef::XmlLDrivers_NamespaceDef
                                (const TCollection_AsciiString& thePrefix,
                                 const TCollection_AsciiString& theURI)
        : myPrefix (thePrefix), myURI (theURI)
{}

//=======================================================================
//function : Prefix
//purpose  : Query
//=======================================================================

const TCollection_AsciiString& XmlLDrivers_NamespaceDef::Prefix () const
{
  return myPrefix;
}

//=======================================================================
//function : URI
//purpose  : Query
//=======================================================================

const TCollection_AsciiString& XmlLDrivers_NamespaceDef::URI () const
{
  return myURI;
}
