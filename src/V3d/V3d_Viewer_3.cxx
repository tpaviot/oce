// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

/***********************************************************************
 
     FONCTION :
     ----------
        Classe V3d_Viewer_3.cxx :
 
     HISTORIQUE DES MODIFICATIONS   :
     --------------------------------
      00-09-92 : GG  ; Creation.
      27-12-98 : FMN ; PERF: OPTIMISATION LOADER (LOPTIM)

     REMARQUES :
     -----------
 
************************************************************************/

//			-> Remove the grid plane axis when it is requested.
//			-> Redraw the privilegied grid plane after any change

/*----------------------------------------------------------------------*/
/*
 * Includes
 */

#include <V3d_Viewer.jxx>

#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <Graphic3d_Structure.hxx>
#include <Graphic3d_Group.hxx>

#include <Graphic3d_ArrayOfSegments.hxx>

/*----------------------------------------------------------------------*/
/*
 * Static variable
 */

static TCollection_AsciiString _XLetter() {
    static TCollection_AsciiString XLetter("X");
return XLetter;
}
#define XLetter _XLetter()

static TCollection_AsciiString _YLetter() {
    static TCollection_AsciiString YLetter("Y");
return YLetter;
}
#define YLetter _YLetter()

static TCollection_AsciiString _ZLetter() {
    static TCollection_AsciiString ZLetter("Z");
return ZLetter;
}
#define ZLetter _ZLetter()

/*----------------------------------------------------------------------*/

void V3d_Viewer::SetPrivilegedPlane(const gp_Ax3& aPlane)
{
  myPrivilegedPlane = aPlane;
  Grid()->SetDrawMode(Grid()->DrawMode());
  for (InitActiveViews (); MoreActiveViews (); NextActiveViews ())
    ActiveView ()->SetGrid (myPrivilegedPlane, Grid ());
  if(myDisplayPlane)
    DisplayPrivilegedPlane(Standard_True,myDisplayPlaneLength);
  else
    Update();
}

/*----------------------------------------------------------------------*/

gp_Ax3 V3d_Viewer::PrivilegedPlane() const
{
  return myPrivilegedPlane;
}

/*----------------------------------------------------------------------*/
void V3d_Viewer::DisplayPrivilegedPlane(const Standard_Boolean OnOff, const Quantity_Length aSize)
{
  Standard_Boolean Change = (myDisplayPlane != OnOff);
  myDisplayPlane = OnOff;
  myDisplayPlaneLength = aSize;

  if(myDisplayPlane)
  {
    if(myPlaneStructure.IsNull()) {
      myPlaneStructure = new Graphic3d_Structure(MyViewer);
      myPlaneStructure->SetInfiniteState(Standard_True);
      myPlaneStructure->Display();
    }
    else
      myPlaneStructure->Clear();

    Handle(Graphic3d_Group) Group = myPlaneStructure->NewGroup();

    Handle(Graphic3d_AspectLine3d) LineAttrib = new Graphic3d_AspectLine3d() ;
    LineAttrib->SetColor(Quantity_Color(Quantity_NOC_GRAY60));
    Group->SetPrimitivesAspect(LineAttrib) ;

    Handle(Graphic3d_AspectText3d) TextAttrib = new Graphic3d_AspectText3d();
    TextAttrib->SetColor(Quantity_Color(Quantity_NOC_ROYALBLUE1));
    Group->SetPrimitivesAspect(TextAttrib);

    Handle(Graphic3d_ArrayOfSegments) aPrims = new Graphic3d_ArrayOfSegments(6);

    const gp_Pnt &p0 = myPrivilegedPlane.Location();

    const gp_Pnt pX(p0.XYZ() + myDisplayPlaneLength*myPrivilegedPlane.XDirection().XYZ());
    aPrims->AddVertex(p0);
    aPrims->AddVertex(pX);
    Group->Text(XLetter.ToCString(),Graphic3d_Vertex(pX.X(),pX.Y(),pX.Z()),1./81.);

    const gp_Pnt pY(p0.XYZ() + myDisplayPlaneLength*myPrivilegedPlane.YDirection().XYZ());
    aPrims->AddVertex(p0);
    aPrims->AddVertex(pY);
    Group->Text(YLetter.ToCString(),Graphic3d_Vertex(pY.X(),pY.Y(),pY.Z()),1./81.);
    
    const gp_Pnt pZ(p0.XYZ() + myDisplayPlaneLength*myPrivilegedPlane.Direction().XYZ());
    aPrims->AddVertex(p0);
    aPrims->AddVertex(pZ);
    Group->Text(ZLetter.ToCString(),Graphic3d_Vertex(pZ.X(),pZ.Y(),pZ.Z()),1./81.);

    Group->AddPrimitiveArray(aPrims);

	myPlaneStructure->Display();
  }
  else
  {
    if( !myPlaneStructure.IsNull() )  myPlaneStructure->Erase();
  }
  if(Change) Update();
}

/*----------------------------------------------------------------------*/
