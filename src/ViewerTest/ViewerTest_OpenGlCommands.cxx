// Created on: 2012-04-09
// Created by: Sergey ANIKIN
// Copyright (c) 2012 OPEN CASCADE SAS
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

#ifdef HAVE_CONFIG_H
# include <oce-config.h>
#endif

#include <ViewerTest.hxx>

#include <Aspect_GraphicDevice.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <Draw.hxx>
#include <Draw_Interpretor.hxx>
#include <Graphic3d_Group.hxx>
#include <OpenGl_ArbVBO.hxx>
#include <OpenGl_AspectFace.hxx>
#include <OpenGl_AspectLine.hxx>
#include <OpenGl_AspectMarker.hxx>
#include <OpenGl_AspectText.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_Element.hxx>
#include <OpenGl_ExtFBO.hxx>
#include <OpenGl_GlCore20.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <OpenGl_Workspace.hxx>
#include <Prs3d_Presentation.hxx>
#include <Prs3d_Root.hxx>
#include <Select3D_SensitiveCurve.hxx>
#include <SelectMgr_EntityOwner.hxx>
#include <SelectMgr_Selection.hxx>
#include <V3d_Viewer.hxx>
#include <TCollection_AsciiString.hxx>
#include <V3d_View.hxx>

extern Standard_Boolean VDisplayAISObject (const TCollection_AsciiString& theName,
                                           const Handle(AIS_InteractiveObject)& theAISObj,
                                           Standard_Boolean theReplaceIfExists = Standard_True);

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
             CALL_DEF_BOUNDS* theBounds)
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

    virtual void Release (const Handle(OpenGl_Context)& theGlCtx)
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
    void GetBounds(CALL_DEF_BOUNDS* theBounds);

    GLfloat myCoords[6];

    friend class Element;
};
IMPLEMENT_STANDARD_HANDLE(VUserDrawObj, AIS_InteractiveObject)
IMPLEMENT_STANDARD_RTTIEXT(VUserDrawObj, AIS_InteractiveObject)

void VUserDrawObj::Compute(const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
                           const Handle(Prs3d_Presentation)& thePresentation,
                           const Standard_Integer theMode)
{
  thePresentation->Clear();

  Handle(Graphic3d_Group) aGrp = Prs3d_Root::CurrentGroup(thePresentation);
  aGrp->UserDraw(this, Standard_True, Standard_True);
}

void VUserDrawObj::ComputeSelection (const Handle(SelectMgr_Selection)& theSelection,
                                     const Standard_Integer theMode)
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

void VUserDrawObj::GetBounds(CALL_DEF_BOUNDS* theBounds)
{
  if (theBounds)
  {
    theBounds->XMin = myCoords[0];
    theBounds->YMin = myCoords[1];
    theBounds->ZMin = myCoords[2];
    theBounds->XMax = myCoords[3];
    theBounds->YMax = myCoords[4];
    theBounds->ZMax = myCoords[5];
  }
}

void VUserDrawObj::Render(const Handle(OpenGl_Workspace)& theWorkspace) const
{
  // To test linking against OpenGl_Workspace and all aspect classes
  const OpenGl_AspectLine* aLA = theWorkspace->AspectLine(0);
  const OpenGl_AspectFace* aFA = theWorkspace->AspectFace(0);
  aFA->Context();
  const OpenGl_AspectMarker* aMA = theWorkspace->AspectMarker(0);
  aMA->Type();
  const OpenGl_AspectText* aTA = theWorkspace->AspectText(0);
  aTA->Font();
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

  Handle(OpenGl_GraphicDriver) aDriver = Handle(OpenGl_GraphicDriver)::DownCast (aContext->CurrentViewer()->Device()->GraphicDriver());
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
}
