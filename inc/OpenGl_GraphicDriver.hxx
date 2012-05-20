// Created on: 2011-10-20
// Created by: Sergey ZERCHANINOV
// Copyright (c) 2011-2012 OPEN CASCADE SAS
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


#ifndef _OpenGl_GraphicDriver_HeaderFile
#define _OpenGl_GraphicDriver_HeaderFile

#include <Graphic3d_GraphicDriver.hxx>
#include <Handle_OpenGl_GraphicDriver.hxx>

#include <Standard_CString.hxx>

#include <Handle_TColStd_HArray1OfByte.hxx>
#include <Handle_TColStd_HArray1OfReal.hxx>
#include <Quantity_PlaneAngle.hxx>
#include <Quantity_NameOfColor.hxx>
#include <Handle_AlienImage_AlienImage.hxx>
#include <Image_CRawBufferData.hxx>

#include <Aspect_Display.hxx>
#include <Aspect_GradientFillMethod.hxx>
#include <Aspect_FillMethod.hxx>
#include <Aspect_CLayer2d.hxx>
#include <Aspect_TypeOfTriedronPosition.hxx>
#include <Aspect_TypeOfTriedronEcho.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_PrintAlgo.hxx>

#include <Graphic3d_CView.hxx>
#include <Graphic3d_CStructure.hxx>
#include <Graphic3d_CGroup.hxx>
#include <Graphic3d_TypeOfPrimitive.hxx>
#include <Graphic3d_CPick.hxx>
#include <Graphic3d_TypeOfPolygon.hxx>
#include <Graphic3d_TextPath.hxx>
#include <Graphic3d_HorizontalTextAlignment.hxx>
#include <Graphic3d_VerticalTextAlignment.hxx>
#include <Graphic3d_PrimitiveArray.hxx>
#include <Graphic3d_CUserDraw.hxx>
#include <Graphic3d_CGraduatedTrihedron.hxx>
#include <Graphic3d_TypeOfComposition.hxx>
#include <Graphic3d_TypeOfTexture.hxx>
#include <Graphic3d_CInitTexture.hxx>
#include <Graphic3d_ExportFormat.hxx>
#include <Graphic3d_SortType.hxx>
#include <Graphic3d_PtrFrameBuffer.hxx>
#include <Graphic3d_Array1OfVertex.hxx>
#include <Graphic3d_Array1OfVertexN.hxx>
#include <Graphic3d_Array1OfVertexNT.hxx>
#include <Graphic3d_Array1OfVertexC.hxx>
#include <Graphic3d_Array1OfVertexNC.hxx>
#include <Graphic3d_Array2OfVertex.hxx>
#include <Graphic3d_Array2OfVertexN.hxx>
#include <Graphic3d_Array2OfVertexNT.hxx>
#include <NCollection_DataMap.hxx>

class TColStd_Array1OfInteger;
class TColStd_Array1OfReal;
class TColStd_Array2OfReal;
class TColStd_HArray1OfByte;
class Graphic3d_VertexNC;
class Graphic3d_Vector;
class Quantity_Color;
class Graphic3d_Vertex;
class Aspect_Array1OfEdge;
class TCollection_ExtendedString;
class AlienImage_AlienImage;
class TColStd_HArray1OfReal;
class Handle(OpenGl_View);
class Handle(OpenGl_Workspace);
class OpenGl_Structure;

//! This class defines an OpenGl graphic driver <br>
class OpenGl_GraphicDriver : public Graphic3d_GraphicDriver
{
 public:

  //! Constructor
  Standard_EXPORT OpenGl_GraphicDriver (const Standard_CString theShrName);

  Standard_EXPORT Standard_Boolean Begin (const Standard_CString ADisplay);
  Standard_EXPORT Standard_Boolean Begin (const Aspect_Display ADisplay);
  Standard_EXPORT void End ();
  Standard_EXPORT Standard_Integer InquireLightLimit ();
  Standard_EXPORT void InquireMat (const Graphic3d_CView& ACView, TColStd_Array2OfReal& AMatO, TColStd_Array2OfReal& AMatM);
  Standard_EXPORT Standard_Integer InquireViewLimit ();
  Standard_EXPORT Standard_Boolean InquireTextureAvailable ();
  Standard_EXPORT void Blink (const Graphic3d_CStructure& ACStructure,const Standard_Boolean Create);
  Standard_EXPORT void BoundaryBox (const Graphic3d_CStructure& ACStructure, const Standard_Boolean Create);
  Standard_EXPORT void HighlightColor (const Graphic3d_CStructure& ACStructure, const Standard_ShortReal R, const Standard_ShortReal G, const Standard_ShortReal B, const Standard_Boolean Create);
  Standard_EXPORT void NameSetStructure (const Graphic3d_CStructure& ACStructure);

public: // Methods for graphical groups

  Standard_EXPORT void ClearGroup (const Graphic3d_CGroup& ACGroup);
  Standard_EXPORT void CloseGroup (const Graphic3d_CGroup& ACGroup);
  Standard_EXPORT void FaceContextGroup (const Graphic3d_CGroup& theCGroup,
                                         const Standard_Integer  theNoInsert);
  Standard_EXPORT void Group (Graphic3d_CGroup& theCGroup);
  Standard_EXPORT void LineContextGroup (const Graphic3d_CGroup& theCGroup,
                                         const Standard_Integer  theNoInsert);
  Standard_EXPORT void MarkerContextGroup (const Graphic3d_CGroup& theCGroup,
                                           const Standard_Integer  theNoInsert);
  Standard_EXPORT void MarkerContextGroup (const Graphic3d_CGroup& theCGroup,
                                           const Standard_Integer  theNoInsert,
                                           const Standard_Integer  theMarkWidth,
                                           const Standard_Integer  theMarkHeight,
                                           const Handle(TColStd_HArray1OfByte)& theTexture);
  Standard_EXPORT void OpenGroup (const Graphic3d_CGroup& theCGroup);
  Standard_EXPORT void RemoveGroup (const Graphic3d_CGroup& theCGroup);
  Standard_EXPORT void TextContextGroup (const Graphic3d_CGroup& theCGroup,
                                         const Standard_Integer  theNoInsert);

public: // Methods for graphical structures

  Standard_EXPORT void ClearStructure (const Graphic3d_CStructure& theCStructure);
  Standard_EXPORT void ContextStructure (const Graphic3d_CStructure& theCStructure);
  Standard_EXPORT void Connect (const Graphic3d_CStructure& theFather,
                                const Graphic3d_CStructure& theSon);
  Standard_EXPORT void Disconnect (const Graphic3d_CStructure& theFather,
                                   const Graphic3d_CStructure& theSon);
  Standard_EXPORT void DisplayStructure (const Graphic3d_CView&      theCView,
                                         const Graphic3d_CStructure& theCStructure,
                                         const Standard_Integer      thePriority);
  Standard_EXPORT void EraseStructure (const Graphic3d_CView&      theCView,
                                       const Graphic3d_CStructure& theCStructure);
  Standard_EXPORT void RemoveStructure (const Graphic3d_CStructure& theCStructure);
  Standard_EXPORT void Structure (Graphic3d_CStructure& theCStructure);

public:

  Standard_EXPORT void ActivateView (const Graphic3d_CView& ACView);
  Standard_EXPORT void AntiAliasing (const Graphic3d_CView& ACView, const Standard_Boolean AFlag);
  Standard_EXPORT void Background (const Graphic3d_CView& ACView);
  Standard_EXPORT void GradientBackground (const Graphic3d_CView& ACView, const Quantity_Color& AColor1, const Quantity_Color& AColor2, const Aspect_GradientFillMethod FillStyle);
  Standard_EXPORT void BackgroundImage (const Standard_CString FileName, const Graphic3d_CView& ACView, const Aspect_FillMethod FillStyle);
  Standard_EXPORT void SetBgImageStyle (const Graphic3d_CView& ACView, const Aspect_FillMethod FillStyle);
  Standard_EXPORT void SetBgGradientStyle (const Graphic3d_CView& ACView, const Aspect_GradientFillMethod FillStyle);
  Standard_EXPORT void ClipLimit (const Graphic3d_CView& ACView, const Standard_Boolean AWait);
  Standard_EXPORT void DeactivateView (const Graphic3d_CView& ACView);
  Standard_EXPORT void DepthCueing (const Graphic3d_CView& ACView, const Standard_Boolean AFlag);
  Standard_EXPORT Standard_Boolean ProjectRaster (const Graphic3d_CView& ACView, const Standard_ShortReal AX, const Standard_ShortReal AY, const Standard_ShortReal AZ, Standard_Integer& AU, Standard_Integer& AV);
  Standard_EXPORT Standard_Boolean UnProjectRaster (const Graphic3d_CView& ACView, const Standard_Integer Axm, const Standard_Integer Aym, const Standard_Integer AXM, const Standard_Integer AYM, const Standard_Integer AU, const Standard_Integer AV, Standard_ShortReal& AX, Standard_ShortReal& AY, Standard_ShortReal& AZ);
  Standard_EXPORT Standard_Boolean UnProjectRasterWithRay (const Graphic3d_CView& ACView, const Standard_Integer Axm, const Standard_Integer Aym, const Standard_Integer AXM, const Standard_Integer AYM, const Standard_Integer AU, const Standard_Integer AV, Standard_ShortReal& AX, Standard_ShortReal& AY, Standard_ShortReal& AZ, Standard_ShortReal& DX, Standard_ShortReal& DY, Standard_ShortReal& DZ);
  Standard_EXPORT void RatioWindow (const Graphic3d_CView& ACView);
  Standard_EXPORT void Redraw (const Graphic3d_CView& ACView, const Aspect_CLayer2d& ACUnderLayer, const Aspect_CLayer2d& ACOverLayer, const Standard_Integer x = 0, const Standard_Integer y = 0, const Standard_Integer width = 0, const Standard_Integer height = 0);
  Standard_EXPORT void RemoveView (const Graphic3d_CView& ACView);
  Standard_EXPORT void SetLight (const Graphic3d_CView& ACView);
  Standard_EXPORT void SetPlane (const Graphic3d_CView& ACView);
  Standard_EXPORT void SetVisualisation (const Graphic3d_CView& ACView);
  Standard_EXPORT void TransformStructure (const Graphic3d_CStructure& ACStructure);
  Standard_EXPORT void DegenerateStructure (const Graphic3d_CStructure& ACStructure);
  Standard_EXPORT void Transparency (const Graphic3d_CView& ACView, const Standard_Boolean AFlag);
  Standard_EXPORT void Update (const Graphic3d_CView& ACView, const Aspect_CLayer2d& ACUnderLayer, const Aspect_CLayer2d& ACOverLayer);
  Standard_EXPORT Standard_Boolean View (Graphic3d_CView& ACView);
  Standard_EXPORT void ViewMapping (const Graphic3d_CView& ACView, const Standard_Boolean AWait);
  Standard_EXPORT void ViewOrientation (const Graphic3d_CView& ACView,const Standard_Boolean AWait);
  Standard_EXPORT void Environment (const Graphic3d_CView& ACView);
  Standard_EXPORT void Marker (const Graphic3d_CGroup& ACGroup, const Graphic3d_Vertex& APoint, const Standard_Boolean EvalMinMax = Standard_True);
  Standard_EXPORT void MarkerSet (const Graphic3d_CGroup& ACGroup, const Graphic3d_Array1OfVertex& ListVertex, const Standard_Boolean EvalMinMax = Standard_True);
  Standard_EXPORT void Polygon (const Graphic3d_CGroup& ACGroup, const Graphic3d_Array1OfVertex& ListVertex, const Graphic3d_TypeOfPolygon AType = Graphic3d_TOP_CONVEX, const Standard_Boolean EvalMinMax = Standard_True);
  Standard_EXPORT void Text (const Graphic3d_CGroup& ACGroup, const Standard_CString AText, const Graphic3d_Vertex& APoint, const Standard_Real AHeight, const Quantity_PlaneAngle AAngle, const Graphic3d_TextPath ATp, const Graphic3d_HorizontalTextAlignment AHta, const Graphic3d_VerticalTextAlignment AVta, const Standard_Boolean EvalMinMax = Standard_True);
  Standard_EXPORT void Text (const Graphic3d_CGroup& ACGroup, const Standard_CString AText, const Graphic3d_Vertex& APoint, const Standard_Real AHeight, const Standard_Boolean EvalMinMax = Standard_True);
  Standard_EXPORT void Text (const Graphic3d_CGroup& ACGroup, const TCollection_ExtendedString& AText, const Graphic3d_Vertex& APoint, const Standard_Real AHeight, const Quantity_PlaneAngle AAngle, const Graphic3d_TextPath ATp, const Graphic3d_HorizontalTextAlignment AHta, const Graphic3d_VerticalTextAlignment AVta, const Standard_Boolean EvalMinMax = Standard_True);
  Standard_EXPORT void Text (const Graphic3d_CGroup& ACGroup, const TCollection_ExtendedString& AText, const Graphic3d_Vertex& APoint, const Standard_Real AHeight, const Standard_Boolean EvalMinMax = Standard_True);
  Standard_EXPORT void PrimitiveArray (const Graphic3d_CGroup& ACGroup,const Graphic3d_PrimitiveArray& parray,const Standard_Boolean EvalMinMax = Standard_True);
  Standard_EXPORT void UserDraw (const Graphic3d_CGroup& ACGroup,const Graphic3d_CUserDraw& AUserDraw);
  Standard_EXPORT void ZBufferTriedronSetup (const Quantity_NameOfColor XColor = Quantity_NOC_RED, const Quantity_NameOfColor YColor = Quantity_NOC_GREEN, const Quantity_NameOfColor ZColor = Quantity_NOC_BLUE1, const Standard_Real SizeRatio = 0.8, const Standard_Real AxisDiametr = 0.05, const Standard_Integer NbFacettes = 12);
  Standard_EXPORT void TriedronDisplay (const Graphic3d_CView& ACView, const Aspect_TypeOfTriedronPosition APosition = Aspect_TOTP_CENTER, const Quantity_NameOfColor AColor = Quantity_NOC_WHITE, const Standard_Real AScale = 0.02, const Standard_Boolean AsWireframe = Standard_True);
  Standard_EXPORT void TriedronErase (const Graphic3d_CView& ACView);
  Standard_EXPORT void TriedronEcho (const Graphic3d_CView& ACView, const Aspect_TypeOfTriedronEcho AType = Aspect_TOTE_NONE);
  Standard_EXPORT void GraduatedTrihedronDisplay (const Graphic3d_CView& view, const Graphic3d_CGraduatedTrihedron& cubic);
  Standard_EXPORT void GraduatedTrihedronErase (const Graphic3d_CView& view);
  Standard_EXPORT void GraduatedTrihedronMinMaxValues (const Standard_ShortReal xmin, const Standard_ShortReal ymin, const Standard_ShortReal zmin, const Standard_ShortReal xmax, const Standard_ShortReal ymax, const Standard_ShortReal zmax);
  Standard_EXPORT void BeginAnimation (const Graphic3d_CView& ACView);
  Standard_EXPORT void EndAnimation (const Graphic3d_CView& ACView);
  Standard_EXPORT Standard_Boolean BeginAddMode (const Graphic3d_CView& ACView);
  Standard_EXPORT void EndAddMode ();
  Standard_EXPORT Standard_Boolean BeginImmediatMode(const Graphic3d_CView& ACView, const Aspect_CLayer2d& ACUnderLayer, const Aspect_CLayer2d& ACOverLayer, const Standard_Boolean DoubleBuffer, const Standard_Boolean RetainMode);
  Standard_EXPORT void BeginPolyline ();
  Standard_EXPORT void ClearImmediatMode (const Graphic3d_CView& ACView,const Standard_Boolean aFlush = Standard_True);
  Standard_EXPORT void Draw (const Standard_ShortReal X, const Standard_ShortReal Y, const Standard_ShortReal Z);
  Standard_EXPORT void DrawStructure (const Graphic3d_CStructure& ACStructure);
  Standard_EXPORT void EndImmediatMode (const Standard_Integer Synchronize);
  Standard_EXPORT void EndPolyline ();
  Standard_EXPORT void Move (const Standard_ShortReal X, const Standard_ShortReal Y, const Standard_ShortReal Z);
  Standard_EXPORT void SetLineColor (const Standard_ShortReal R, const Standard_ShortReal G, const Standard_ShortReal B);
  Standard_EXPORT void SetLineType (const Standard_Integer Type);
  Standard_EXPORT void SetLineWidth (const Standard_ShortReal Width);
  Standard_EXPORT void SetMinMax (const Standard_ShortReal X1, const Standard_ShortReal Y1, const Standard_ShortReal Z1, const Standard_ShortReal X2, const Standard_ShortReal Y2, const Standard_ShortReal Z2);
  Standard_EXPORT void Transform (const TColStd_Array2OfReal& AMatrix, const Graphic3d_TypeOfComposition AType);
  Standard_EXPORT void Layer (Aspect_CLayer2d& ACLayer);
  Standard_EXPORT void RemoveLayer (const Aspect_CLayer2d& ACLayer);
  Standard_EXPORT void BeginLayer (const Aspect_CLayer2d& ACLayer);
  Standard_EXPORT void BeginPolygon2d ();
  Standard_EXPORT void BeginPolyline2d ();
  Standard_EXPORT void ClearLayer (const Aspect_CLayer2d& ACLayer);
  Standard_EXPORT void Draw (const Standard_ShortReal X,const Standard_ShortReal Y);
  Standard_EXPORT void Edge (const Standard_ShortReal X,const Standard_ShortReal Y);
  Standard_EXPORT void EndLayer ();
  Standard_EXPORT void EndPolygon2d ();
  Standard_EXPORT void EndPolyline2d ();
  Standard_EXPORT void Move (const Standard_ShortReal X,const Standard_ShortReal Y);
  Standard_EXPORT void Rectangle (const Standard_ShortReal X,const Standard_ShortReal Y,const Standard_ShortReal Width,const Standard_ShortReal Height);
  Standard_EXPORT void SetColor (const Standard_ShortReal R,const Standard_ShortReal G,const Standard_ShortReal B);
  Standard_EXPORT void SetTransparency (const Standard_ShortReal ATransparency);
  Standard_EXPORT void UnsetTransparency ();
  Standard_EXPORT void SetLineAttributes (const Standard_Integer Type,const Standard_ShortReal Width);

  //! Set text attributes for under-/overlayer. <br>
  //! <Font> argument defines the name of the font to be used, <br>
  //! <Type> argument defines the display type of the text, <br>
  //! <R> <G> <B> values define the color of decal or subtitle background. <br>
  //! To set the color of the text you can use the SetColor method. <br>
  Standard_EXPORT void SetTextAttributes (const Standard_CString FontName,const Standard_Integer Type,const Standard_ShortReal R,const Standard_ShortReal G,const Standard_ShortReal B);
  Standard_EXPORT void Text (const Standard_CString AText,const Standard_ShortReal X,const Standard_ShortReal Y,const Standard_ShortReal AHeight);
  Standard_EXPORT void TextSize (const Standard_CString AText,const Standard_ShortReal AHeight,Standard_ShortReal& AWidth,Standard_ShortReal& AnAscent,Standard_ShortReal& ADescent) const;
  Standard_EXPORT void SetBackFacingModel (const Graphic3d_CView& aView);
  //! print the contents of all layers of the view to the printer. <br>
  //! <hPrnDC> : Pass the PrinterDeviceContext (HDC), <br>
  //! <showBackground> : When set to FALSE then print the view without background color <br>
  //! (background is white) <br>
  //! else set to TRUE for printing with current background color. <br>
  //! <filename>: If != NULL, then the view will be printed to a file. <br>
  //! <printAlgorithm>: Select print algorithm: stretch, tile. <br>
  //! <theScaleFactor>: Scaling coefficient, used internally to scale the <br>
  //! printings accordingly to the scale factor selected in the printer <br>
  //! properties dialog. <br>
  //! Returns Standard_True if the data is passed to the printer, otherwise <br>
  //! Standard_False if the print operation failed due to the printer errors, <br>
  //! or lack of system memory. This might be related to insufficient memory <br>
  //! or some internal errors. All this errors are indicated by the message <br>
  //! boxes (on level of OpenGl_GraphicDriver). <br>
  //! Warning: This function can reuse FBO assigned to the view <br>
  //! Please take it into account if you use it for your purposes; <br>
  Standard_EXPORT Standard_Boolean Print (const Graphic3d_CView& ACView, const Aspect_CLayer2d& ACUnderLayer, const Aspect_CLayer2d& ACOverLayer, const Aspect_Handle hPrnDC, const Standard_Boolean showBackground, const Standard_CString filename, const Aspect_PrintAlgo printAlgorithm = Aspect_PA_STRETCH, const Standard_Real theScaleFactor = 1.0) const;
  Standard_EXPORT void SetDepthTestEnabled (const Graphic3d_CView& view,const Standard_Boolean isEnabled) const;
  Standard_EXPORT Standard_Boolean IsDepthTestEnabled (const Graphic3d_CView& view) const;
  //! Reads depths of shown pixels of the given rectangle (glReadPixels with GL_DEPTH_COMPONENT) <br>
  Standard_EXPORT void ReadDepths (const Graphic3d_CView& view,const Standard_Integer x,const Standard_Integer y,const Standard_Integer width,const Standard_Integer height,const Standard_Address buffer) const;
  //! Generate offscreen FBO (needs OpenGL2+ hardware) <br>
  //! If not supported on hardware returns NULL. <br>
  Standard_EXPORT Graphic3d_PtrFrameBuffer FBOCreate (const Graphic3d_CView& view, const Standard_Integer width, const Standard_Integer height);
  //! Remove offscreen FBO <br>
  Standard_EXPORT void FBORelease (const Graphic3d_CView& view, Graphic3d_PtrFrameBuffer& fboPtr);
  //! Dump active rendering buffer into specified memory buffer. <br>
  Standard_EXPORT Standard_Boolean BufferDump (const Graphic3d_CView& view, Image_CRawBufferData& buffer);
  Standard_EXPORT void SetGLLightEnabled (const Graphic3d_CView& view,const Standard_Boolean isEnabled) const;
  Standard_EXPORT Standard_Boolean IsGLLightEnabled (const Graphic3d_CView& view) const;
  //! Clear visualization data in graphical driver and stop <br>
  //! displaying the primitives array of the graphical group <theCGroup>. <br>
  //! This method is internal and should be used by Graphic3d_Group only. <br>
  Standard_EXPORT void RemovePrimitiveArray(const Graphic3d_CGroup& theCGroup,const Graphic3d_PrimitiveArray& thePArray);
  Standard_EXPORT Standard_Integer InquirePlaneLimit();
  Standard_EXPORT Standard_Integer CreateTexture(const Graphic3d_TypeOfTexture Type,const Handle(AlienImage_AlienImage)& Image,const Standard_CString FileName,const Handle(TColStd_HArray1OfReal)& TexUpperBounds) const;
  Standard_EXPORT void DestroyTexture(const Standard_Integer TexId) const;
  Standard_EXPORT void ModifyTexture(const Standard_Integer TexId,const Graphic3d_CInitTexture& AValue) const;
  Standard_EXPORT Standard_ShortReal DefaultTextHeight() const;
  Standard_EXPORT void FBOGetDimensions(const Graphic3d_CView& view,const Graphic3d_PtrFrameBuffer fboPtr,Standard_Integer& width,Standard_Integer& height,Standard_Integer& widthMax,Standard_Integer& heightMax);
  Standard_EXPORT void FBOChangeViewport(const Graphic3d_CView& view,Graphic3d_PtrFrameBuffer& fboPtr,const Standard_Integer width,const Standard_Integer height);
  Standard_EXPORT Standard_Boolean Export(const Standard_CString theFileName,const Graphic3d_ExportFormat theFormat,const Graphic3d_SortType theSortType,const Standard_Integer theWidth,const Standard_Integer theHeight,const Graphic3d_CView& theView,const Aspect_CLayer2d& theLayerUnder,const Aspect_CLayer2d& theLayerOver,const Standard_Real thePrecision = 0.005,const Standard_Address theProgressBarFunc = NULL,const Standard_Address theProgressObject = NULL);
  
  //! Add a new top-level z layer with ID <theLayerId> for <br>
  //! the view. Z layers allow drawing structures in higher layers <br>
  //! in foreground of structures in lower layers. To add a structure <br>
  //! to desired layer on display it is necessary to set the layer <br>
  //! index for the structure. <br>
  Standard_EXPORT void AddZLayer(const Graphic3d_CView& theCView,
                                 const Standard_Integer theLayerId);

  //! Remove Z layer from the specified view. All structures <br>
  //! displayed at the moment in layer will be displayed in default layer <br>
  //! ( the bottom-level z layer ). To unset layer index from associated <br>
  //! structures use method UnsetZLayer (...). <br>
  Standard_EXPORT void RemoveZLayer(const Graphic3d_CView& theCView,
                                    const Standard_Integer theLayerId);

  //! Unset Z layer ID for all structures. The structure <br>
  //! indexes will be set to default layer ( the bottom-level z layer with <br>
  //! ID = 0 ). <br>
  Standard_EXPORT void UnsetZLayer(const Standard_Integer theLayerId);

  //! Change Z layer of a structure. The new z layer ID will <br>
  //! be used to define the associated layer for structure on display. <br>
  //! It is recommended to take care of redisplaying the structures already <br>
  //! presented in view with previously set layer index. This is usually <br>
  //! done by viewer manager. Z layers allow drawing structures in <br>
  //! higher layers in foreground of structures in lower layers. <br>
  Standard_EXPORT void ChangeZLayer(const Graphic3d_CStructure& theCStructure,
                                    const Standard_Integer theLayerId);

  //! Change Z layer of a structure already presented in view. <br>
  //! It is recommended to update z layer of already <br>
  //! displayed structures with this method before setting new z layer <br>
  //! index to the structure. This is usually done by viewer manager. <br>
  Standard_EXPORT void ChangeZLayer(const Graphic3d_CStructure& theCStructure,
                                    const Graphic3d_CView& theCView,
                                    const Standard_Integer theNewLayerId);

  //! Get Z layer ID of the structure. If the structure doesn't exists in <br>
  //! graphic driver, the method returns -1. <br>
  Standard_EXPORT Standard_Integer GetZLayer(const Graphic3d_CStructure& theCStructure) const;

public:

  //! Returns true if VBO usage does not forbidden.
  Standard_EXPORT static Standard_Boolean ToUseVBO();

  //! VBO usage can be forbidden by this method even if it is supported by GL driver.
  //! Notice that disabling of VBO will cause rendering performance degradation.
  //! Warning! This method should be called only before any primitives are displayed in GL scene!
  Standard_EXPORT void EnableVBO (const Standard_Boolean theToTurnOn);

  //! Returns information about GPU memory usage.
  //! Please read OpenGl_Context::MemoryInfo() for more description.
  Standard_EXPORT Standard_Boolean MemoryInfo (Standard_Size&           theFreeBytes,
                                               TCollection_AsciiString& theInfo) const;

private:

  //! Access the global map of views.
  static NCollection_DataMap<Standard_Integer, Handle(OpenGl_View)>& GetMapOfViews();

  //! Access the global map of workspaces.
  static NCollection_DataMap<Standard_Integer, Handle(OpenGl_Workspace)>& GetMapOfWorkspaces();

  //! Access the global map of structures.
  static NCollection_DataMap<Standard_Integer, OpenGl_Structure*>& GetMapOfStructures();

  //! Deprecated.
  static void InvalidateAllWorkspaces();

public:

  DEFINE_STANDARD_RTTI(OpenGl_GraphicDriver)
};

#endif //_OpenGl_GraphicDriver_HeaderFile
