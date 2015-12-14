// Created on: 2012-04-09
// Created by: Sergey ANIKIN
// Copyright (c) 2012-2014 OPEN CASCADE SAS
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

#include <ViewerTest.hxx>

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <Draw.hxx>
#include <Draw_Interpretor.hxx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_ShaderObject.hxx>
#include <Graphic3d_ShaderProgram.hxx>
#include <OpenGl_AspectFace.hxx>
#include <OpenGl_AspectLine.hxx>
#include <OpenGl_AspectMarker.hxx>
#include <OpenGl_AspectText.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_Element.hxx>
#include <OpenGl_GlCore20.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <OpenGl_Workspace.hxx>
#include <OSD_Environment.hxx>
#include <OSD_File.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_Presentation.hxx>
#include <Prs3d_Root.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <Select3D_SensitiveCurve.hxx>
#include <SelectMgr_EntityOwner.hxx>
#include <SelectMgr_Selection.hxx>
#include <TCollection_AsciiString.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <Visual3d_View.hxx>
#include <ViewerTest_DoubleMapOfInteractiveAndName.hxx>
#include <ViewerTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName.hxx>

extern Standard_Boolean VDisplayAISObject (const TCollection_AsciiString& theName,
                                           const Handle(AIS_InteractiveObject)& theAISObj,
                                           Standard_Boolean theReplaceIfExists = Standard_True);
extern ViewerTest_DoubleMapOfInteractiveAndName& GetMapOfAIS();

//=======================================================================
//function : VUserDraw
//purpose  : Checks availability and operation of UserDraw feature
//=======================================================================
DEFINE_STANDARD_HANDLE(VUserDrawObj, AIS_InteractiveObject)

class VUserDrawObj : public AIS_InteractiveObject
{
public:
    // CASCADE RTTI
    DEFINE_STANDARD_RTTI(VUserDrawObj)

    VUserDrawObj()
    {
      myCoords[0] = -10.;
      myCoords[1] = -20.;
      myCoords[2] = -30.;
      myCoords[3] =  10.;
      myCoords[4] =  20.;
      myCoords[5] =  30.;
    }

public:
  class Element : public OpenGl_Element
  {
  private:
    Handle(VUserDrawObj) myIObj;

  public:
    Element (const Handle(VUserDrawObj)& theIObj,
             Graphic3d_BndBox4f* theBounds)
    : myIObj( theIObj )
    {
      if (!myIObj.IsNull())
        myIObj->GetBounds(theBounds);
    }

    virtual ~Element ()
    {
    }

    virtual void Render (const Handle(OpenGl_Workspace)& theWorkspace) const
    {
      if (!myIObj.IsNull())
        myIObj->Render(theWorkspace);
    }

    virtual void Release (OpenGl_Context*)
    {
      //
    }

  public:
    DEFINE_STANDARD_ALLOC
  };

private:
    // Virtual methods implementation
    void Compute (const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
                  const Handle(Prs3d_Presentation)& thePresentation,
                  const Standard_Integer theMode);

    void ComputeSelection (const Handle(SelectMgr_Selection)& theSelection,
                           const Standard_Integer theMode);

    // Called by VUserDrawElement
    void Render(const Handle(OpenGl_Workspace)& theWorkspace) const;
    void GetBounds(Graphic3d_BndBox4f* theBounds);

    GLfloat myCoords[6];

    friend class Element;
};
IMPLEMENT_STANDARD_HANDLE(VUserDrawObj, AIS_InteractiveObject)
IMPLEMENT_STANDARD_RTTIEXT(VUserDrawObj, AIS_InteractiveObject)

void VUserDrawObj::Compute(const Handle(PrsMgr_PresentationManager3d)& /*thePresentationManager*/,
                           const Handle(Prs3d_Presentation)& thePresentation,
                           const Standard_Integer /*theMode*/)
{
  thePresentation->Clear();

  Handle(Graphic3d_Group) aGrp = Prs3d_Root::CurrentGroup(thePresentation);
  aGrp->UserDraw(this, Standard_True, Standard_True);
}

void VUserDrawObj::ComputeSelection (const Handle(SelectMgr_Selection)& theSelection,
                                     const Standard_Integer /*theMode*/)
{
  Handle(SelectMgr_EntityOwner) anEntityOwner = new SelectMgr_EntityOwner(this);
  Handle(TColgp_HArray1OfPnt) aPnts = new TColgp_HArray1OfPnt(1, 5);
  aPnts->SetValue(1, gp_Pnt(myCoords[0], myCoords[1], myCoords[2]));
  aPnts->SetValue(2, gp_Pnt(myCoords[3], myCoords[4], myCoords[2]));
  aPnts->SetValue(3, gp_Pnt(myCoords[3], myCoords[4], myCoords[5]));
  aPnts->SetValue(4, gp_Pnt(myCoords[0], myCoords[1], myCoords[5]));
  aPnts->SetValue(5, gp_Pnt(myCoords[0], myCoords[1], myCoords[2]));
  Handle(Select3D_SensitiveCurve) aSensitive = new Select3D_SensitiveCurve(anEntityOwner, aPnts);
  theSelection->Add(aSensitive);
}

void VUserDrawObj::GetBounds(Graphic3d_BndBox4f* theBounds)
{
  if (theBounds)
  {
    Graphic3d_Vec4 aMinPt (myCoords[0], myCoords[1], myCoords[2], 1.0f);
    Graphic3d_Vec4 aMaxPt (myCoords[3], myCoords[4], myCoords[5], 1.0f);
    if (!theBounds->IsValid())
    {
      theBounds->Combine (Graphic3d_BndBox4f (aMinPt, aMaxPt));
    }
    else
    {
      theBounds->CornerMin() = aMinPt;
      theBounds->CornerMax() = aMaxPt;
    }
  }
}

void VUserDrawObj::Render(const Handle(OpenGl_Workspace)& theWorkspace) const
{
  // To test linking against OpenGl_Workspace and all aspect classes
  const OpenGl_AspectLine* aLA = theWorkspace->AspectLine(0);
  const OpenGl_AspectMarker* aMA = theWorkspace->AspectMarker(0);
  aMA->Type();
  const OpenGl_AspectText* aTA = theWorkspace->AspectText(0);
  aTA->FontName();
  TEL_COLOUR aColor = theWorkspace->NamedStatus & OPENGL_NS_HIGHLIGHT ?
    *(theWorkspace->HighlightColor) : aLA->Color();

  // To test OpenGl_Window
  //Handle(OpenGl_Context) aCtx = theWorkspace->GetGlContext();

  // Finally draw something to make sure UserDraw really works
  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_LIGHTING);
  glColor4fv(aColor.rgb);
  glBegin(GL_LINE_LOOP);
  glVertex3f(myCoords[0], myCoords[1], myCoords[2]);
  glVertex3f(myCoords[3], myCoords[4], myCoords[2]);
  glVertex3f(myCoords[3], myCoords[4], myCoords[5]);
  glVertex3f(myCoords[0], myCoords[1], myCoords[5]);
  glEnd();
  glPopAttrib();
}

OpenGl_Element* VUserDrawCallback(const CALL_DEF_USERDRAW * theUserDraw)
{
  Handle(VUserDrawObj) anIObj = (VUserDrawObj*)theUserDraw->Data;
  if (anIObj.IsNull())
  {
    std::cout << "VUserDrawCallback error: null object passed, the custom scene element will not be rendered" << std::endl;
  }

  return new VUserDrawObj::Element(anIObj, theUserDraw->Bounds);
}

static Standard_Integer VUserDraw (Draw_Interpretor& di,
                                    Standard_Integer argc,
                                    const char ** argv)
{
  Handle(AIS_InteractiveContext) aContext = ViewerTest::GetAISContext();
  if (aContext.IsNull())
  {
    di << argv[0] << "Call 'vinit' before!\n";
    return 1;
  }

  Handle(OpenGl_GraphicDriver) aDriver = Handle(OpenGl_GraphicDriver)::DownCast (aContext->CurrentViewer()->Driver());
  if (aDriver.IsNull())
  {
    std::cerr << "Graphic driver not available.\n";
    return 1;
  }

  if (argc > 2)
  {
    di << argv[0] << "Wrong number of arguments, only the object name expected\n";
    return 1;
  }

  TCollection_AsciiString aName (argv[1]);
  VDisplayAISObject(aName, Handle(AIS_InteractiveObject)());

  // register the custom element factory function
  aDriver->UserDrawCallback() = VUserDrawCallback;

  Handle(VUserDrawObj) anIObj = new VUserDrawObj();
  VDisplayAISObject(aName, anIObj);

  return 0;
}

//==============================================================================
//function : VFeedback
//purpose  :
//==============================================================================

static int VFeedback (Draw_Interpretor& theDI,
                      Standard_Integer  /*theArgNb*/,
                      const char**      /*theArgVec*/)
{
  // get the active view
  Handle(V3d_View) aView = ViewerTest::CurrentView();
  if (aView.IsNull())
  {
    std::cerr << "No active view. Please call vinit.\n";
    return 1;
  }

  unsigned int aBufferSize = 1024 * 1024;
  for (;;)
  {
    size_t aBytes = (size_t )aBufferSize * sizeof(GLfloat);
    if (aBytes / sizeof(GLfloat) != (size_t )aBufferSize)
    {
      // finito la commedia
      std::cerr << "Can not allocate buffer - requested size ("
                << (double(aBufferSize / (1024 * 1024)) * double(sizeof(GLfloat)))
                << " MiB) is out of address space\n";
      return 1;
    }

    GLfloat* aBuffer = (GLfloat* )Standard::Allocate (aBytes);
    if (aBuffer == NULL)
    {
      // finito la commedia
      std::cerr << "Can not allocate buffer with size ("
                << (double(aBufferSize / (1024 * 1024)) * double(sizeof(GLfloat)))
                << " MiB)\n";
      return 1;
    }

    glFeedbackBuffer ((GLsizei )aBufferSize, GL_2D, aBuffer);
    glRenderMode (GL_FEEDBACK);

    aView->Redraw();

    GLint aResult = glRenderMode (GL_RENDER);
    if (aResult < 0)
    {
      aBufferSize *= 2;

      void* aPtr = aBuffer;
      Standard::Free (aPtr);
      aBuffer = NULL;
      continue;
    }

    std::cout << "FeedBack result= " << aResult << "\n";
    GLint aPntNb     = 0;
    GLint aTriNb     = 0;
    GLint aQuadsNb   = 0;
    GLint aPolyNb    = 0;
    GLint aNodesNb   = 0;
    GLint aLinesNb   = 0;
    GLint aBitmapsNb = 0;
    GLint aPassThrNb = 0;
    GLint aUnknownNb = 0;
    const GLint NODE_VALUES = 2; // GL_2D
    for (GLint anIter = 0; anIter < aResult;)
    {
        const GLfloat aPos = aBuffer[anIter];
        switch ((GLint )aPos)
        {
          case GL_POINT_TOKEN:
          {
            ++aPntNb;
            ++aNodesNb;
            anIter += 1 + NODE_VALUES;
            break;
          }
          case GL_LINE_RESET_TOKEN:
          case GL_LINE_TOKEN:
          {
            ++aLinesNb;
            aNodesNb += 2;
            anIter += 1 + 2 * NODE_VALUES;
            break;
          }
          case GL_POLYGON_TOKEN:
          {
            const GLint aCount = (GLint )aBuffer[++anIter];
            aNodesNb += aCount;
            anIter += aCount * NODE_VALUES + 1;
            if (aCount == 3)
            {
              ++aTriNb;
            }
            else if (aCount == 4)
            {
              ++aQuadsNb;
            }
            else
            {
              ++aPolyNb;
            }
            break;
          }
          case GL_BITMAP_TOKEN:
          case GL_DRAW_PIXEL_TOKEN:
          case GL_COPY_PIXEL_TOKEN:
          {
            ++aBitmapsNb;
            anIter += 1 + NODE_VALUES;
            break;
          }
          case GL_PASS_THROUGH_TOKEN:
          {
            ++aPassThrNb;
            anIter += 2; // header + value
            break;
          }
          default:
          {
            ++anIter;
            ++aUnknownNb;
            break;
          }
       }
    }
    void* aPtr = aBuffer;
    Standard::Free (aPtr);

    // return statistics
    theDI << "Total nodes:   " << aNodesNb   << "\n"
          << "Points:        " << aPntNb     << "\n"
          << "Line segments: " << aLinesNb   << "\n"
          << "Triangles:     " << aTriNb     << "\n"
          << "Quads:         " << aQuadsNb   << "\n"
          << "Polygons:      " << aPolyNb    << "\n"
          << "Bitmap tokens: " << aBitmapsNb << "\n"
          << "Pass through:  " << aPassThrNb << "\n"
          << "UNKNOWN:       " << aUnknownNb << "\n";

    double aLen2D      = double(aNodesNb * 2 + aPntNb + aLinesNb * 2 + (aTriNb + aQuadsNb + aPolyNb) * 2 + aBitmapsNb + aPassThrNb);
    double aLen3D      = double(aNodesNb * 3 + aPntNb + aLinesNb * 2 + (aTriNb + aQuadsNb + aPolyNb) * 2 + aBitmapsNb + aPassThrNb);
    double aLen3D_rgba = double(aNodesNb * 7 + aPntNb + aLinesNb * 2 + (aTriNb + aQuadsNb + aPolyNb) * 2 + aBitmapsNb + aPassThrNb);
    theDI << "Buffer size GL_2D:       " << aLen2D      * double(sizeof(GLfloat)) / double(1024 * 1024) << " MiB\n"
          << "Buffer size GL_3D:       " << aLen3D      * double(sizeof(GLfloat)) / double(1024 * 1024) << " MiB\n"
          << "Buffer size GL_3D_COLOR: " << aLen3D_rgba * double(sizeof(GLfloat)) / double(1024 * 1024) << " MiB\n";
    return 0;
  }
}

//==============================================================================
//function : VImmediateFront
//purpose  :
//==============================================================================

static int VImmediateFront (Draw_Interpretor& /*theDI*/,
                            Standard_Integer  theArgNb,
                            const char**      theArgVec)
{
  // get the context
  Handle(AIS_InteractiveContext) aContextAIS = ViewerTest::GetAISContext();
  if (aContextAIS.IsNull())
  {
    std::cerr << "No active view. Please call vinit.\n";
    return 1;
  }

  Handle(Graphic3d_GraphicDriver) aDriver = aContextAIS->CurrentViewer()->Driver();

  if (aDriver.IsNull())
  {
    std::cerr << "Graphic driver not available.\n";
    return 1;
  }

  if (theArgNb < 2)
  {
    std::cerr << "Wrong number of arguments.\n";
    return 1;
  }

  Graphic3d_CView* aCView = (Graphic3d_CView* )(ViewerTest::CurrentView()->View()->CView());
  aDriver->SetImmediateModeDrawToFront (*aCView, atoi(theArgVec[1]) != 0);
  return 0;
}

//==============================================================================
//function : VGlInfo
//purpose  :
//==============================================================================

static int VGlInfo (Draw_Interpretor& theDI,
                    Standard_Integer  theArgNb,
                    const char**      theArgVec)
{
  // get the active view
  Handle(V3d_View) aView = ViewerTest::CurrentView();
  if (aView.IsNull())
  {
    std::cerr << "No active view. Please call vinit.\n";
    return 1;
  }

  if (theArgNb <= 1)
  {
    Handle(OpenGl_GraphicDriver) aDriver = Handle(OpenGl_GraphicDriver)::DownCast (aView->View()->GraphicDriver());
    if (aDriver.IsNull())
    {
      std::cerr << "Error: view does not use OpenGL.\n";
      return 1;
    }
    Handle(OpenGl_Context) aCtx = aDriver->GetSharedContext();
    Standard_CString aDebugInfo = !aCtx.IsNull() && aCtx->IsDebugContext()
                                ? "  GLdebug     =  ON\n"
                                : "";
    theDI << "OpenGL info:\n"
          << "  GLvendor    = '" << (const char* )glGetString(GL_VENDOR)   << "'\n"
          << "  GLdevice    = '" << (const char* )glGetString(GL_RENDERER) << "'\n"
          << "  GLversion   = '" << (const char* )glGetString(GL_VERSION)  << "'\n"
          << "  GLSLversion = '" << (const char* )glGetString(GL_SHADING_LANGUAGE_VERSION) << "'\n"
          << aDebugInfo;
    return 0;
  }

  const Standard_Boolean isList = theArgNb >= 3;
  for (Standard_Integer anIter = 1; anIter < theArgNb; ++anIter)
  {
    TCollection_AsciiString aName (theArgVec[anIter]);
    aName.UpperCase();
    const char* aValue = NULL;
    if (aName.Search ("VENDOR") != -1)
    {
      aValue = (const char* )glGetString (GL_VENDOR);
    }
    else if (aName.Search ("RENDERER") != -1)
    {
      aValue = (const char* )glGetString (GL_RENDERER);
    }
    else if (aName.Search ("SHADING_LANGUAGE_VERSION") != -1
          || aName.Search ("GLSL") != -1)
    {
      aValue = (const char* )glGetString (GL_SHADING_LANGUAGE_VERSION);
    }
    else if (aName.Search ("VERSION") != -1)
    {
      aValue = (const char* )glGetString (GL_VERSION);
    }
    else if (aName.Search ("EXTENSIONS") != -1)
    {
      aValue = (const char* )glGetString (GL_EXTENSIONS);
    }
    else
    {
      std::cerr << "Unknown key '" << aName.ToCString() << "'\n";
      return 1;
    }

    if (isList)
    {
      theDI << "{" << aValue << "} ";
    }
    else
    {
      theDI << aValue;
    }
  }

  return 0;
}


//==============================================================================
//function : VShaderProg
//purpose  : Sets the pair of vertex and fragment shaders for the object
//==============================================================================
static Standard_Integer VShaderProg (Draw_Interpretor& /*theDI*/,
                                     Standard_Integer  theArgNb,
                                     const char**      theArgVec)
{
  Handle(AIS_InteractiveContext) aCtx = ViewerTest::GetAISContext();
  if (aCtx.IsNull())
  {
    std::cerr << "Use 'vinit' command before " << theArgVec[0] << "\n";
    return 1;
  }
  else if (theArgNb < 2)
  {
    std::cerr << theArgVec[0] << " syntax error: lack of arguments\n";
    return 1;
  }

  TCollection_AsciiString aLastArg (theArgVec[theArgNb - 1]);
  aLastArg.UpperCase();
  const Standard_Boolean toTurnOff = aLastArg == "OFF";
  Standard_Integer       anArgsNb  = theArgNb - 1;
  Handle(Graphic3d_ShaderProgram) aProgram;
  if (!toTurnOff
   && aLastArg == "PHONG")
  {
    aProgram = new Graphic3d_ShaderProgram (Graphic3d_ShaderProgram::ShaderName_Phong);
  }
  if (!toTurnOff
   && aProgram.IsNull())
  {
    if (theArgNb < 3)
    {
      std::cerr << theArgVec[0] << " syntax error: lack of arguments\n";
      return 1;
    }

    const TCollection_AsciiString aSrcVert = theArgVec[theArgNb - 2];
    const TCollection_AsciiString aSrcFrag = theArgVec[theArgNb - 1];
    if (!aSrcVert.IsEmpty()
     && !OSD_File (aSrcVert).Exists())
    {
      std::cerr << "Non-existing vertex shader source\n";
      return 1;
    }
    if (!aSrcFrag.IsEmpty()
     && !OSD_File (aSrcFrag).Exists())
    {
      std::cerr << "Non-existing fragment shader source\n";
      return 1;
    }

    aProgram = new Graphic3d_ShaderProgram();
    aProgram->AttachShader (Graphic3d_ShaderObject::CreateFromFile (Graphic3d_TOS_VERTEX,   aSrcVert));
    aProgram->AttachShader (Graphic3d_ShaderObject::CreateFromFile (Graphic3d_TOS_FRAGMENT, aSrcFrag));
    anArgsNb = theArgNb - 2;
  }

  Handle(AIS_InteractiveObject) anIO;
  if (anArgsNb <= 1
   || *theArgVec[1] == '*')
  {
    for (ViewerTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName anIter (GetMapOfAIS());
          anIter.More(); anIter.Next())
    {
      anIO = Handle(AIS_InteractiveObject)::DownCast (anIter.Key1());
      if (!anIO.IsNull())
      {
        anIO->Attributes()->ShadingAspect()->Aspect()->SetShaderProgram (aProgram);
        aCtx->Redisplay (anIO, Standard_False);
      }
    }
    aCtx->UpdateCurrentViewer();
    return 0;
  }

  for (Standard_Integer anArgIter = 1; anArgIter < anArgsNb; ++anArgIter)
  {
    const TCollection_AsciiString aName (theArgVec[anArgIter]);
    if (!GetMapOfAIS().IsBound2 (aName))
    {
      std::cerr << "Warning: " << aName.ToCString() << " is not displayed\n";
      continue;
    }
    anIO = Handle(AIS_InteractiveObject)::DownCast (GetMapOfAIS().Find2 (aName));
    if (anIO.IsNull())
    {
      std::cerr << "Warning: " << aName.ToCString() << " is not an AIS object\n";
      continue;
    }
    anIO->Attributes()->ShadingAspect()->Aspect()->SetShaderProgram (aProgram);
    aCtx->Redisplay (anIO, Standard_False);
  }

  aCtx->UpdateCurrentViewer();
  return 0;
}

//=======================================================================
//function : OpenGlCommands
//purpose  :
//=======================================================================

void ViewerTest::OpenGlCommands(Draw_Interpretor& theCommands)
{
  const char* aGroup ="Commands for low-level TKOpenGl features";

  theCommands.Add("vuserdraw",
    "vuserdraw : name - simulates drawing with help of UserDraw",
    __FILE__, VUserDraw, aGroup);
  theCommands.Add("vfeedback",
    "vfeedback       : perform test GL feedback rendering",
    __FILE__, VFeedback, aGroup);
  theCommands.Add("vimmediatefront",
    "vimmediatefront : render immediate mode to front buffer or to back buffer",
    __FILE__, VImmediateFront, aGroup);
  theCommands.Add("vglinfo",
    "vglinfo [GL_VENDOR] [GL_RENDERER] [GL_VERSION] [GL_SHADING_LANGUAGE_VERSION] [GL_EXTENSIONS]"
    " : prints GL info",
    __FILE__, VGlInfo, aGroup);
  theCommands.Add("vshaderprog",
            "   'vshaderprog [name] pathToVertexShader pathToFragmentShader'"
    "\n\t\t: or 'vshaderprog [name] off'   to disable GLSL program"
    "\n\t\t: or 'vshaderprog [name] phong' to enable per-pixel lighting calculations"
    "\n\t\t: * might be used to specify all displayed objects",
    __FILE__, VShaderProg, aGroup);
}
