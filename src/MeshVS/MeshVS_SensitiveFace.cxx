// File:	MeshVS_SensitiveFace.cxx
// Created:	Mon Sep 29 2003
// Author:	Alexander SOLOVYOV and Sergey LITONIN
// Copyright:	 Open CASCADE 2003

#include <MeshVS_SensitiveFace.ixx>

#include <TColgp_Array1OfPnt.hxx>
#include <Select3D_Projector.hxx>
#include <CSLib_Class2d.hxx>
#include <TopLoc_Location.hxx>

//=======================================================================
// name    : MeshVS_SensitiveFace::MeshVS_SensitiveFace
// Purpose :
//=======================================================================
MeshVS_SensitiveFace::MeshVS_SensitiveFace (
                   const Handle(SelectBasics_EntityOwner)& theOwnerId,
                   const TColgp_Array1OfPnt&               thePnts,
                   const Select3D_TypeOfSensitivity        theSensitivity )
: Select3D_SensitiveFace( theOwnerId, thePnts, theSensitivity )
{
  gp_XYZ c( 0, 0, 0 );
  Standard_Integer nbPnts = thePnts.Upper() - thePnts.Lower() + 1;
  for ( Standard_Integer i = thePnts.Lower(); i <= thePnts.Upper(); i++ )
    c += thePnts( i ).XYZ();
  myCentre.SetXYZ( c / nbPnts );
}

//=======================================================================
// name    : MeshVS_SensitiveFace::Project
// Purpose :
//=======================================================================
void MeshVS_SensitiveFace::Project( const Handle(Select3D_Projector)& aProj )
{
  Select3D_SensitiveFace::Project( aProj );
  if ( HasLocation() )
    aProj->Project( myCentre.Transformed( Location().Transformation() ), myProjCentre );
  else
    aProj->Project( myCentre, myProjCentre );
}

//=======================================================================
// name    : MeshVS_SensitiveFace::Matches
// Purpose :
//=======================================================================
Standard_Boolean MeshVS_SensitiveFace::Matches( const Standard_Real XMin,
                                                const Standard_Real YMin,
                                                const Standard_Real XMax,
                                                const Standard_Real YMax,
                                                const Standard_Real aTol )
{
  Bnd_Box2d aBox;
  aBox.Update( XMin-aTol, YMin-aTol, XMax+aTol, YMax+aTol );
  return !aBox.IsOut( myProjCentre );
}

//=======================================================================
// name    : MeshVS_SensitiveFace::Matches
// Purpose :
//=======================================================================
Standard_Boolean MeshVS_SensitiveFace::Matches( const TColgp_Array1OfPnt2d& Polyline,
                                                const Bnd_Box2d&            aBox,
                                                const Standard_Real         aTol )
{
  Standard_Real Umin, Vmin, Umax, Vmax;
  aBox.Get ( Umin,Vmin,Umax,Vmax );
  CSLib_Class2d aClassifier2d( Polyline, aTol, aTol, Umin, Vmin, Umax, Vmax );
  Standard_Integer aRes = aClassifier2d.SiDans( myProjCentre );

  return ( aRes == 1) ;
}
