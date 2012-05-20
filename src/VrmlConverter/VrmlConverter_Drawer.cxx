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

#include <VrmlConverter_Drawer.ixx>
#include <Vrml_Material.hxx>

VrmlConverter_Drawer::VrmlConverter_Drawer():
  myNbPoints(17),
  myIsoOnPlane(Standard_False),
  myFreeBoundaryDraw(Standard_True),
  myUnFreeBoundaryDraw(Standard_True),
  myWireDraw(Standard_True),
  myChordialDeviation(0.1),
  myTypeOfDeflection(Aspect_TOD_RELATIVE),
  myMaximalParameterValue(500.), 
  myDeviationCoefficient(0.001),
  myDrawHiddenLine(Standard_False)
{
}

void VrmlConverter_Drawer::SetTypeOfDeflection(const Aspect_TypeOfDeflection aTypeOfDeflection)
{
 myTypeOfDeflection = aTypeOfDeflection;
}

Aspect_TypeOfDeflection VrmlConverter_Drawer::TypeOfDeflection() const 
{
 return myTypeOfDeflection;
}

void VrmlConverter_Drawer::SetMaximalChordialDeviation(const Quantity_Length aChordialDeviation)
{
 myChordialDeviation = aChordialDeviation;
}

Quantity_Length VrmlConverter_Drawer::MaximalChordialDeviation() const 
{
 return myChordialDeviation;
}

void VrmlConverter_Drawer::SetDeviationCoefficient(const Standard_Real aCoefficient)
{
 myDeviationCoefficient = aCoefficient;
}

Standard_Real VrmlConverter_Drawer::DeviationCoefficient() const 
{
 return myDeviationCoefficient;
}

void VrmlConverter_Drawer::SetDiscretisation(const Standard_Integer d)
{
 myNbPoints = d;
}

Standard_Integer VrmlConverter_Drawer::Discretisation() const 
{
 return myNbPoints;
}

void VrmlConverter_Drawer::SetMaximalParameterValue(const Standard_Real Value)
{
 myMaximalParameterValue = Value;
}

Standard_Real VrmlConverter_Drawer::MaximalParameterValue() const 
{
 return myMaximalParameterValue;
}

void VrmlConverter_Drawer::SetIsoOnPlane(const Standard_Boolean OnOff)
{
 myIsoOnPlane = OnOff;
}

Standard_Boolean VrmlConverter_Drawer::IsoOnPlane()const
{
 return myIsoOnPlane;
}

Handle (VrmlConverter_IsoAspect) VrmlConverter_Drawer::UIsoAspect()
{
  if (myUIsoAspect.IsNull()) 
    {
      Handle(Vrml_Material) m = new Vrml_Material;
      myUIsoAspect = new VrmlConverter_IsoAspect (m, Standard_False, 1);
    }
  return myUIsoAspect;
}

void VrmlConverter_Drawer::SetUIsoAspect ( const Handle(VrmlConverter_IsoAspect)& anAspect) 
{
 myUIsoAspect = anAspect;
}

Handle (VrmlConverter_IsoAspect) VrmlConverter_Drawer::VIsoAspect ()
{
  if (myVIsoAspect.IsNull()) 
    {
      Handle(Vrml_Material) m = new Vrml_Material;
      myVIsoAspect = new VrmlConverter_IsoAspect (m, Standard_False, 1);
    }
 return myVIsoAspect;
}

void VrmlConverter_Drawer::SetVIsoAspect ( const Handle(VrmlConverter_IsoAspect)& anAspect) 
{
 myVIsoAspect = anAspect;
}

Handle(VrmlConverter_LineAspect) VrmlConverter_Drawer::FreeBoundaryAspect() 
{
  if (myFreeBoundaryAspect.IsNull())
    {
      Handle(Vrml_Material) m = new Vrml_Material;
      myFreeBoundaryAspect = new VrmlConverter_LineAspect(m, Standard_False);
    }
  return myFreeBoundaryAspect;
}

void VrmlConverter_Drawer::SetFreeBoundaryAspect(const Handle(VrmlConverter_LineAspect)& anAspect)
{
 myFreeBoundaryAspect = anAspect;
}

void VrmlConverter_Drawer::SetFreeBoundaryDraw(const Standard_Boolean OnOff)
{
 myFreeBoundaryDraw = OnOff;
}

Standard_Boolean VrmlConverter_Drawer::FreeBoundaryDraw() const 
{
 return myFreeBoundaryDraw;
}

Handle(VrmlConverter_LineAspect) VrmlConverter_Drawer::WireAspect() 
{
  if (myWireAspect.IsNull())
    {
      Handle(Vrml_Material) m = new Vrml_Material;
      myWireAspect = new VrmlConverter_LineAspect(m, Standard_False);
    }
  return myWireAspect;
}

void VrmlConverter_Drawer::SetWireAspect(const Handle(VrmlConverter_LineAspect)& anAspect)
{
 myWireAspect = anAspect;
}

void VrmlConverter_Drawer::SetWireDraw(const Standard_Boolean OnOff)
{
 myWireDraw = OnOff;
}

Standard_Boolean VrmlConverter_Drawer::WireDraw() const 
{
 return myWireDraw;
}

Handle(VrmlConverter_LineAspect) VrmlConverter_Drawer::UnFreeBoundaryAspect() 
{
  if (myUnFreeBoundaryAspect.IsNull())
    {
      Handle(Vrml_Material) m = new Vrml_Material;
      myUnFreeBoundaryAspect = new VrmlConverter_LineAspect(m, Standard_False);
    }
  return myUnFreeBoundaryAspect;
}

void VrmlConverter_Drawer::SetUnFreeBoundaryAspect(const Handle(VrmlConverter_LineAspect)& anAspect)
{
 myUnFreeBoundaryAspect = anAspect;
}

void VrmlConverter_Drawer::SetUnFreeBoundaryDraw(const Standard_Boolean OnOff)
{
 myUnFreeBoundaryDraw = OnOff;
}

Standard_Boolean VrmlConverter_Drawer::UnFreeBoundaryDraw() const 
{
 return myUnFreeBoundaryDraw;
}

Handle(VrmlConverter_LineAspect) VrmlConverter_Drawer::LineAspect() 
{
  if (myLineAspect.IsNull())
    {
      Handle(Vrml_Material) m = new Vrml_Material;
      myLineAspect = new VrmlConverter_LineAspect(m, Standard_False);
    }
  return myLineAspect;
}

void VrmlConverter_Drawer::SetLineAspect(const Handle(VrmlConverter_LineAspect)& anAspect)
{
 myLineAspect = anAspect;
}

Handle(VrmlConverter_PointAspect) VrmlConverter_Drawer::PointAspect() 
{
  if (myPointAspect.IsNull())
    {
      Handle(Vrml_Material) m = new Vrml_Material;
      myPointAspect = new VrmlConverter_PointAspect(m, Standard_False);
    }
 return myPointAspect;
}

void VrmlConverter_Drawer::SetPointAspect(const Handle(VrmlConverter_PointAspect)& anAspect)
{
 myPointAspect = anAspect;
}

Handle(VrmlConverter_ShadingAspect) VrmlConverter_Drawer::ShadingAspect() 
{
  if (myShadingAspect.IsNull())
    {
      myShadingAspect = new VrmlConverter_ShadingAspect;
    }
 return myShadingAspect;
}

void VrmlConverter_Drawer::SetShadingAspect(const Handle(VrmlConverter_ShadingAspect)& anAspect)
{
 myShadingAspect = anAspect;
}

Standard_Boolean VrmlConverter_Drawer::DrawHiddenLine () const {return myDrawHiddenLine;}

void VrmlConverter_Drawer::EnableDrawHiddenLine () {myDrawHiddenLine=Standard_True;}

void VrmlConverter_Drawer::DisableDrawHiddenLine () {myDrawHiddenLine=Standard_False;}

Handle (VrmlConverter_LineAspect) VrmlConverter_Drawer::HiddenLineAspect () 
{
  if (myHiddenLineAspect.IsNull())
    {
      Handle(Vrml_Material) m = new Vrml_Material;
      myHiddenLineAspect = new VrmlConverter_LineAspect(m, Standard_False);
    }
  return myHiddenLineAspect;
}

void VrmlConverter_Drawer::SetHiddenLineAspect ( const Handle(VrmlConverter_LineAspect)& anAspect) 
{
 myHiddenLineAspect = anAspect;
}

Handle (VrmlConverter_LineAspect) VrmlConverter_Drawer::SeenLineAspect ()  
{
  if (mySeenLineAspect.IsNull())
    {
      Handle(Vrml_Material) m = new Vrml_Material;
      mySeenLineAspect = new VrmlConverter_LineAspect(m, Standard_False);
    }
  return mySeenLineAspect;
}

void VrmlConverter_Drawer::SetSeenLineAspect ( const Handle(VrmlConverter_LineAspect)& anAspect) 
{
 mySeenLineAspect = anAspect;
}
