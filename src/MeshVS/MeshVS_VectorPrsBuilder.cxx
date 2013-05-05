// Created on: 2003-09-19
// Created by: Alexander SOLOVYOV
// Copyright (c) 2003-2012 OPEN CASCADE SAS
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


#include <MeshVS_VectorPrsBuilder.ixx>

#include <MeshVS_DisplayModeFlags.hxx>

#include <Graphic3d_ArrayOfPolylines.hxx>
#include <Graphic3d_ArrayOfPolygons.hxx>
#include <Graphic3d_ArrayOfTriangleFans.hxx>
#include <Graphic3d_MaterialAspect.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_AspectFillArea3d.hxx>
#include <Graphic3d_Group.hxx>

#include <TColStd_MapIteratorOfPackedMapOfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_HPackedMapOfInteger.hxx>

#include <Precision.hxx>

#include <gp_Ax3.hxx>

#include <Prs3d_Root.hxx>

#include <Aspect_TypeOfLine.hxx>

#include <MeshVS_DataSource.hxx>
#include <MeshVS_Drawer.hxx>
#include <MeshVS_DrawerAttribute.hxx>
#include <MeshVS_Mesh.hxx>
#include <MeshVS_EntityType.hxx>
#include <MeshVS_DataMapIteratorOfDataMapOfIntegerVector.hxx>
#include <MeshVS_Buffer.hxx>

//================================================================
// Function : Constructor MeshVS_VectorPrsBuilder
// Purpose  :
//================================================================
MeshVS_VectorPrsBuilder::MeshVS_VectorPrsBuilder ( const Handle(MeshVS_Mesh)& Parent,
                                                   const Standard_Real MaxLength,
                                                   const Quantity_Color& VectorColor,
                                                   const MeshVS_DisplayModeFlags& Flags,
                                                   const Handle (MeshVS_DataSource)& DS,
                                                   const Standard_Integer Id,
                                                   const MeshVS_BuilderPriority& Priority,
                                                   const Standard_Boolean IsSimplePrs )
: MeshVS_PrsBuilder ( Parent, Flags, DS, Id, Priority ),
myIsSimplePrs( IsSimplePrs ),
mySimpleWidthPrm( 2.5 ),
mySimpleStartPrm( 0.85 ),
mySimpleEndPrm( 0.95 )
{
  Handle ( MeshVS_Drawer ) aDrawer = GetDrawer();
  if ( !aDrawer.IsNull() )
  {
    aDrawer->SetDouble ( MeshVS_DA_VectorMaxLength, MaxLength );
    aDrawer->SetColor  ( MeshVS_DA_VectorColor, VectorColor );
    aDrawer->SetDouble ( MeshVS_DA_VectorArrowPart, 0.1 );
  }
}

//================================================================
// Function : GetVectors
// Purpose  :
//================================================================
const MeshVS_DataMapOfIntegerVector& MeshVS_VectorPrsBuilder::GetVectors
  ( const Standard_Boolean IsElements ) const
{
  if ( IsElements )
    return myElemVectorMap;
  else
    return myNodeVectorMap;
}

//================================================================
// Function : SetVectors
// Purpose  :
//================================================================
void MeshVS_VectorPrsBuilder::SetVectors ( const Standard_Boolean IsElements,
                                           const MeshVS_DataMapOfIntegerVector& theMap )
{
  if ( IsElements )
    myElemVectorMap = theMap;
  else
    myNodeVectorMap = theMap;
}

//================================================================
// Function : HasVectors
// Purpose  :
//================================================================
Standard_Boolean MeshVS_VectorPrsBuilder::HasVectors ( const Standard_Boolean IsElement ) const
{
  Standard_Boolean aRes = (myNodeVectorMap.Extent()>0);
  if ( IsElement )
    aRes = (myElemVectorMap.Extent()>0);
  return aRes;

}

//================================================================
// Function : GetVector
// Purpose  :
//================================================================
Standard_Boolean MeshVS_VectorPrsBuilder::GetVector ( const Standard_Boolean IsElement,
                                                      const Standard_Integer ID,
                                                      gp_Vec& Vect ) const
{
  const MeshVS_DataMapOfIntegerVector* aMap = &myNodeVectorMap;
  if ( IsElement )
    aMap = &myElemVectorMap;

  Standard_Boolean aRes = aMap->IsBound ( ID );
  if ( aRes )
    Vect = aMap->Find ( ID );

  return aRes;
}

//================================================================
// Function : SetVector
// Purpose  :
//================================================================
void MeshVS_VectorPrsBuilder::SetVector ( const Standard_Boolean IsElement,
                                          const Standard_Integer ID,
                                          const gp_Vec& Vect )
{
  MeshVS_DataMapOfIntegerVector* aMap = &myNodeVectorMap;
  if ( IsElement )
    aMap = &myElemVectorMap;

  Standard_Boolean aRes = aMap->IsBound ( ID );
  if ( aRes )
    aMap->ChangeFind ( ID ) = Vect;
  else
    aMap->Bind ( ID, Vect );
}

//================================================================
// Function : GetMaxVectorValue
// Purpose  :
//================================================================
void MeshVS_VectorPrsBuilder::GetMinMaxVectorValue ( const Standard_Boolean IsElement,
                                                     Standard_Real& MinValue,
                                                     Standard_Real& MaxValue ) const
{
  const MeshVS_DataMapOfIntegerVector* aMap = &myNodeVectorMap;
  if ( IsElement )
    aMap = &myElemVectorMap;

  MeshVS_DataMapIteratorOfDataMapOfIntegerVector anIt ( *aMap );
  if ( anIt.More() )
    MinValue = MaxValue = anIt.Value().Magnitude();

  Standard_Real aCurValue;

  for ( ; anIt.More(); anIt.Next() )
  {
    aCurValue = anIt.Value().Magnitude();
    if ( MinValue > aCurValue )
      MinValue = aCurValue;
    if ( MaxValue < aCurValue )
      MaxValue = aCurValue;
  }
}

//================================================================
// Function : Build
// Purpose  :
//================================================================

#define NB_VERTICES 2
#define NB_BOUNDS 1
#define NB_TRIANGLES 6
#define NB_FANS 1

void MeshVS_VectorPrsBuilder::Build ( const Handle(Prs3d_Presentation)& Prs,
                                      const TColStd_PackedMapOfInteger& IDs,
                                      TColStd_PackedMapOfInteger& IDsToExclude,
                                      const Standard_Boolean IsElement,
                                      const Standard_Integer theDisplayMode ) const
{
  Handle ( MeshVS_Drawer ) aDrawer = GetDrawer();
  Handle (MeshVS_DataSource) aSource = GetDataSource();
  if ( aSource.IsNull() || aDrawer.IsNull() || !HasVectors( IsElement ) ||
       ( theDisplayMode & GetFlags() )==0 )
    return;

  Standard_Integer aMaxFaceNodes;
  Standard_Real aMaxLen, anArrowPart = 0.1;

  if ( !aDrawer->GetInteger ( MeshVS_DA_MaxFaceNodes, aMaxFaceNodes ) ||
       aMaxFaceNodes <= 0 ||
       !aDrawer->GetDouble  ( MeshVS_DA_VectorMaxLength, aMaxLen )    ||
       aMaxLen <= 0       ||
       !aDrawer->GetDouble ( MeshVS_DA_VectorArrowPart, anArrowPart ) ||
       anArrowPart <= 0
     )
    return;

  MeshVS_Buffer aCoordsBuf (3*aMaxFaceNodes*sizeof(Standard_Real));
  TColStd_Array1OfReal aCoords (aCoordsBuf, 1, 3*aMaxFaceNodes);
  Standard_Integer NbNodes;
  MeshVS_EntityType aType;

  // DECLARE ARRAYS OF PRIMITIVES
  const MeshVS_DataMapOfIntegerVector& aMap = GetVectors ( IsElement );
  Standard_Integer aNbVectors = aMap.Extent();

  if ( aNbVectors <= 0 )
    return;

  // polylines
  Standard_Integer aNbVertices         = aNbVectors  * NB_VERTICES;
  Standard_Integer aNbBounds           = aNbVectors  * NB_BOUNDS;

  // fans
  Standard_Integer aNbTriangleVertices = aNbVectors  * (NB_TRIANGLES + 2);
  Standard_Integer aNbFans             = aNbVectors  * NB_TRIANGLES;

  Handle(Graphic3d_ArrayOfPrimitives) aLineArray =
    new Graphic3d_ArrayOfPolylines(aNbVertices, aNbBounds);
  Handle(Graphic3d_ArrayOfPrimitives) aArrowLineArray =
    new Graphic3d_ArrayOfPolylines(aNbVertices, aNbBounds);

  Handle(Graphic3d_ArrayOfTriangleFans) aTriangleArray =
    new Graphic3d_ArrayOfTriangleFans(aNbTriangleVertices, aNbFans);

  TColgp_Array1OfPnt anArrowPnt(1,8);
  Standard_Real k, b, aMaxValue, aMinValue, aValue, X, Y, Z;
  
  Standard_Real aMinLength = calculateArrow( anArrowPnt, aMaxLen, anArrowPart );
  gp_Vec aVec; gp_Trsf aTrsf;

  GetMinMaxVectorValue ( IsElement, aMinValue, aMaxValue );

  if ( aMaxValue - aMinValue > Precision::Confusion() )
  {
    k = 0.8 * aMaxLen / ( aMaxValue - aMinValue );
    b = aMaxLen - k * aMaxValue;
  }
  else
  {
    k = 0;
    b = aMaxLen;
  }

  TColStd_PackedMapOfInteger aCustomElements;

  // subtract the hidden elements and ids to exclude (to minimise allocated memory)
  TColStd_PackedMapOfInteger anIDs;
  anIDs.Assign( IDs );
  if ( IsElement )
  {
    Handle(TColStd_HPackedMapOfInteger) aHiddenElems = myParentMesh->GetHiddenElems();
    if ( !aHiddenElems.IsNull() )
      anIDs.Subtract( aHiddenElems->Map() );
  }
  anIDs.Subtract( IDsToExclude );

  TColStd_MapIteratorOfPackedMapOfInteger it (anIDs);
  for( ; it.More(); it.Next() )
  {
    Standard_Integer aKey = it.Key();
      if( GetVector ( IsElement, aKey, aVec ) )
      {
        aValue = aVec.Magnitude();

        if ( Abs( aValue ) < Precision::Confusion() )
          continue;

        if( aSource->GetGeom ( aKey, IsElement, aCoords, NbNodes, aType ) )
        {
          if( aType == MeshVS_ET_Node )
          {
            X = aCoords(1);
            Y = aCoords(2);
            Z = aCoords(3);
          }
          else if( aType == MeshVS_ET_Link || 
                   aType == MeshVS_ET_Face || 
                   aType == MeshVS_ET_Volume )
          {
            if( IsElement && IsExcludingOn() )
              IDsToExclude.Add( aKey );
            X = Y = Z = 0;
            for ( Standard_Integer i=1; i<=NbNodes; i++ )
            {
              X += aCoords (3*i-2);
              Y += aCoords (3*i-1);
              Z += aCoords (3*i);
            }
            X /= Standard_Real ( NbNodes );
            Y /= Standard_Real ( NbNodes );
            Z /= Standard_Real ( NbNodes );
          }
          else
          {
            aCustomElements.Add( aKey );
            continue;
          }

          aTrsf.SetDisplacement ( gp_Ax3 ( gp_Pnt ( 0, 0, 0 ), gp_Dir(0, 0, 1)),
                                  gp_Ax3 ( gp_Pnt ( X, Y, Z ), aVec ) );

          DrawVector ( aTrsf, Max( k * fabs( aValue ) + b, aMinLength), aMaxLen,
                       anArrowPnt, aLineArray, aArrowLineArray, aTriangleArray );
        }
      }
  }

  Prs3d_Root::NewGroup ( Prs );
  Handle (Graphic3d_Group) aVGroup = Prs3d_Root::CurrentGroup ( Prs );

  Quantity_Color aColor;
  aDrawer->GetColor ( MeshVS_DA_VectorColor, aColor );

  // Add primitive arrays to group
  Handle(Graphic3d_AspectLine3d) aLinAspect =
    new Graphic3d_AspectLine3d ( aColor, Aspect_TOL_SOLID, 1.5 );

  aVGroup->SetPrimitivesAspect( aLinAspect );
  aVGroup->AddPrimitiveArray( aLineArray );

  if ( !myIsSimplePrs )
  {
    Graphic3d_MaterialAspect aMatAspect;
    aMatAspect.SetAmbient( 1 );
    aMatAspect.SetDiffuse( 0 );
    aMatAspect.SetEmissive( 0 );
    aMatAspect.SetShininess( 1 );
    aMatAspect.SetSpecular( 0 );
    Handle(Graphic3d_AspectFillArea3d) aFillAspect =
      new Graphic3d_AspectFillArea3d (Aspect_IS_HOLLOW, aColor, aColor, Aspect_TOL_SOLID,
                                      1., aMatAspect, aMatAspect );

    aVGroup->SetPrimitivesAspect( aFillAspect );
    aVGroup->AddPrimitiveArray( aTriangleArray );
  }
  else
  {
    Handle(Graphic3d_AspectLine3d) anArrowLinAspect =
      new Graphic3d_AspectLine3d ( aColor, Aspect_TOL_SOLID, mySimpleWidthPrm * 1.5 );

    aVGroup->SetPrimitivesAspect( anArrowLinAspect );
    aVGroup->AddPrimitiveArray( aArrowLineArray );
  }

  if( !aCustomElements.IsEmpty() )
    CustomBuild( Prs, aCustomElements, IDsToExclude, theDisplayMode );
}

//=======================================================================
// name    : DrawVector
// Purpose : Fill arrays of primitives for drawing force
//=======================================================================
void MeshVS_VectorPrsBuilder::DrawVector ( const gp_Trsf& theTrsf,
                                           const Standard_Real Length,
                                           const Standard_Real MaxLength,
                                           const TColgp_Array1OfPnt& ArrowPoints,
                                           const Handle(Graphic3d_ArrayOfPrimitives)& Lines,
                                           const Handle(Graphic3d_ArrayOfPrimitives)& ArrowLines,
                                           const Handle(Graphic3d_ArrayOfPrimitives)& Triangles) const
{
  const int PntNum = 8;

  const Standard_Real aMinLength = MaxLength * ( 1 - mySimpleStartPrm );
  const Standard_Real aLocalLength = ( !myIsSimplePrs || Length > aMinLength ? Length : aMinLength );
  // draw line
  gp_Pnt aLinePnt[ 2 ] = { gp_Pnt( 0, 0, 0 ) , gp_Pnt( 0, 0, aLocalLength ) };
  theTrsf.Transforms( aLinePnt[ 0 ].ChangeCoord() );
  theTrsf.Transforms( aLinePnt[ 1 ].ChangeCoord() );

  Lines->AddBound( 2 );
  Lines->AddVertex( aLinePnt[ 0 ] );
  Lines->AddVertex( aLinePnt[ 1 ] );

  // draw arrow
  if ( !myIsSimplePrs )
  {
    Standard_Integer l = ArrowPoints.Lower(),
                     u = ArrowPoints.Upper(),
                     i;
    if ( u-l < PntNum-1 )
      return;

    TColgp_Array1OfPnt anArrowPnt( l, u );
    for ( i = l; i < l+PntNum; i++ )
    {
      anArrowPnt( i ).ChangeCoord() = ArrowPoints ( i ).Coord() + gp_XYZ( 0, 0, aLocalLength );
      theTrsf.Transforms( anArrowPnt( i ).ChangeCoord() );
    }

    Triangles->AddBound(8);
    for ( i = 0; i < PntNum; i++ )
      Triangles->AddVertex( anArrowPnt( l+i ) );
  }
  else
  {
    const Standard_Real aEndPos = aLocalLength - MaxLength * ( 1 - mySimpleEndPrm );
    const Standard_Real aArrowLength = MaxLength * ( mySimpleEndPrm - mySimpleStartPrm );
    gp_Pnt aArrowPnt[ 2 ] = { gp_Pnt( 0, 0, aEndPos - aArrowLength ),
                              gp_Pnt( 0, 0, aEndPos ) };
    theTrsf.Transforms( aArrowPnt[ 0 ].ChangeCoord() );
    theTrsf.Transforms( aArrowPnt[ 1 ].ChangeCoord() );

    ArrowLines->AddBound( 2 );
    ArrowLines->AddVertex( aArrowPnt[ 0 ] );
    ArrowLines->AddVertex( aArrowPnt[ 1 ] );
  }
}

//=======================================================================
// name    : calculateArrow
// Purpose : Calculate points of arrow ( 8 pnts )
//=======================================================================
Standard_Real MeshVS_VectorPrsBuilder::calculateArrow ( TColgp_Array1OfPnt& Points,
                                                        const Standard_Real Length,
                                                        const Standard_Real ArrowPart )
{
  Standard_Real h = Length * ArrowPart;
  Standard_Real w = h / 5.;

  Standard_Integer f = Points.Lower();
  Points( f   ) = gp_Pnt( 0,  0, 0 );
  Points( f+1 ) = gp_Pnt( 0, -w, -h );
  Points( f+2 ) = gp_Pnt( w * 0.866, -w * 0.5, -h );
  Points( f+3 ) = gp_Pnt( w * 0.866,  w * 0.5, -h );
  Points( f+4 ) = gp_Pnt( 0 , w, -h );
  Points( f+5 ) = gp_Pnt( -w * 0.866,  w * 0.5, -h );
  Points( f+6 ) = gp_Pnt( -w * 0.866, -w * 0.5, -h );
  Points( f+7 ) = gp_Pnt( 0, -w, -h );

  return h;
}

//=======================================================================
// name    : SetSimplePrsMode
// Purpose : 
//=======================================================================
void MeshVS_VectorPrsBuilder::SetSimplePrsMode( const Standard_Boolean IsSimpleArrow )
{
  myIsSimplePrs = IsSimpleArrow;
}

//=======================================================================
// name    : SetSimplePrsParams
// Purpose : 
//=======================================================================
void MeshVS_VectorPrsBuilder::SetSimplePrsParams( const Standard_Real theLineWidthParam,
                                                  const Standard_Real theStartParam,
                                                  const Standard_Real theEndParam )
{
  mySimpleWidthPrm = theLineWidthParam;
  mySimpleStartPrm = theStartParam;
  mySimpleEndPrm   = theEndParam;
}
