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

#include <Vrml_SpotLight.ixx>

Vrml_SpotLight::Vrml_SpotLight():
  myOnOff(Standard_True),
  myIntensity(1),
  myDropOffRate(0), 
  myCutOffAngle(0.785398) 
{
  gp_Vec tmpVec(0,0,1);
  myLocation = tmpVec;

  tmpVec.SetCoord(0,0,-1);
  myDirection = tmpVec;

  Quantity_Color tmpColor(1,1,1,Quantity_TOC_RGB);
  myColor = tmpColor;
}

 Vrml_SpotLight::Vrml_SpotLight( const Standard_Boolean aOnOff, 
				 const Standard_Real aIntensity, 
			         const Quantity_Color& aColor, 
			         const gp_Vec& aLocation,
			         const gp_Vec& aDirection,
				 const Standard_Real aDropOffRate, 
				 const Standard_Real aCutOffAngle) 
{
  myOnOff = aOnOff;
  if (aIntensity < 0. || aIntensity > 1.)
    {
      Standard_Failure::Raise("Error : Light intensity must be in the range 0.0 to 1.0, inclusive.");
    }
  myIntensity = aIntensity;
  myColor = aColor;
  myLocation = aLocation;
  myDirection = aDirection;
  myDropOffRate = aDropOffRate;
  myCutOffAngle = aCutOffAngle;
}

void Vrml_SpotLight::SetOnOff(const Standard_Boolean aOnOff)
{
  myOnOff = aOnOff;
}

Standard_Boolean Vrml_SpotLight::OnOff() const 
{
  return myOnOff;
}

void Vrml_SpotLight::SetIntensity(const Standard_Real aIntensity)
{
  if (aIntensity < 0. || aIntensity > 1.)
    {
      Standard_Failure::Raise("Error : Light intensity must be in the range 0.0 to 1.0, inclusive.");
    }
  myIntensity = aIntensity;
}

Standard_Real Vrml_SpotLight::Intensity() const 
{
  return myIntensity;
}

void Vrml_SpotLight::SetColor(const Quantity_Color& aColor)
{
  myColor = aColor;
}

Quantity_Color Vrml_SpotLight::Color() const 
{
  return  myColor;
}

void Vrml_SpotLight::SetLocation(const gp_Vec& aLocation)
{
  myLocation = aLocation;
}

gp_Vec Vrml_SpotLight::Location() const 
{
  return myLocation;
}

void Vrml_SpotLight::SetDirection(const gp_Vec& aDirection)
{
  myDirection = aDirection;
}

gp_Vec Vrml_SpotLight::Direction() const 
{
  return myDirection;
}

void Vrml_SpotLight::SetDropOffRate(const Standard_Real aDropOffRate)
{
  myDropOffRate = aDropOffRate;
}

Standard_Real Vrml_SpotLight::DropOffRate() const 
{
  return myDropOffRate;
}

void Vrml_SpotLight::SetCutOffAngle(const Standard_Real aCutOffAngle)
{
  myCutOffAngle = aCutOffAngle;
}

Standard_Real Vrml_SpotLight::CutOffAngle() const 
{
  return myCutOffAngle;
}

Standard_OStream& Vrml_SpotLight::Print(Standard_OStream& anOStream) const 
{
 anOStream  << "SpotLight {" << endl;

 if ( myOnOff != Standard_True )
   {
    anOStream  << "    on" << "\t\t" << "FALSE" << endl;
//    anOStream << myOnOff << endl;
   }

 if ( Abs(myIntensity - 1) > 0.0001 )
   {
    anOStream  << "    intensity" << '\t';
    anOStream << myIntensity << endl;
   }

 if ( Abs(myColor.Red() - 1) > 0.0001 || 
     Abs(myColor.Green() - 1) > 0.0001 || 
     Abs(myColor.Blue() - 1) > 0.0001 )
   {
    anOStream  << "    color" << '\t';
    anOStream << myColor.Red() << ' ' << myColor.Green() << ' ' << myColor.Blue() << endl;
   }

 if ( Abs(myLocation.X() - 0) > 0.0001 || 
     Abs(myLocation.Y() - 0) > 0.0001 || 
     Abs(myLocation.Z() - 1) > 0.0001 ) 
   {
    anOStream  << "    location" << '\t';
    anOStream << myLocation.X() << ' ' << myLocation.Y() << ' ' << myLocation.Z() << endl;
   }

 if ( Abs(myDirection.X() - 0) > 0.0001 || 
     Abs(myDirection.Y() - 0) > 0.0001 || 
     Abs(myDirection.Z() + 1) > 0.0001 ) 
   {
    anOStream  << "    direction" << '\t';
    anOStream << myDirection.X() << ' ' << myDirection.Y() << ' ' << myDirection.Z() << endl;
   }

 if ( Abs(myDropOffRate - 0) > 0.0001 )
   {
    anOStream  << "    dropOffRate" << '\t';
    anOStream << myDropOffRate << endl;
   }

 if ( Abs(myCutOffAngle - 0.785398) > 0.0000001 )
   {
    anOStream  << "    cutOffAngle" << '\t';
    anOStream << myCutOffAngle << endl;
   }

 anOStream  << '}' << endl;
 return anOStream;
}
