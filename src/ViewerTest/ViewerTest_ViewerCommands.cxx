// Created on: 1998-09-01
// Created by: Robert COUBLANC
// Copyright (c) 1998-1999 Matra Datavision
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


// Robert Boehne 30 May 2000 : Dec Osf

#ifdef HAVE_CONFIG_H
# include <oce-config.h>
#endif

#ifdef WNT
#include <windows.h>
#endif

#include <Graphic3d_AspectMarker3d.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Graphic3d_ExportFormat.hxx>
#include <ViewerTest.hxx>
#include <ViewerTest_EventManager.hxx>
#include <Visual3d_View.hxx>
#include <Visual3d_ViewManager.hxx>
#include <V3d_LayerMgr.hxx>
#include <NIS_View.hxx>
#include <NIS_Triangulated.hxx>
#include <NIS_InteractiveContext.hxx>
#include <AIS_InteractiveContext.hxx>
#include <Draw_Interpretor.hxx>
#include <Draw.hxx>
#include <Draw_Appli.hxx>
#include <Aspect_PrintAlgo.hxx>
#include <Image_AlienPixMap.hxx>
#include <OSD_Timer.hxx>
#include <TColStd_SequenceOfInteger.hxx>
#include <Visual3d_LayerItem.hxx>
#include <V3d_LayerMgr.hxx>
#include <V3d_LayerMgrPointer.hxx>
#include <Aspect_TypeOfLine.hxx>
#include <Image_Diff.hxx>

#ifdef WNT
#undef DrawText
#endif

#include <Visual3d_Layer.hxx>
#include <cstdlib>

#ifndef WNT
#include <Graphic3d_GraphicDevice.hxx>
#include <Xw_GraphicDevice.hxx>
#include <Xw_WindowQuality.hxx>
#include <Xw_Window.hxx>
#include <X11/Xlib.h> /* contains some dangerous #defines such as Status, True etc. */
#include <X11/Xutil.h>
#include <tk.h>

#else

#include <Graphic3d_WNTGraphicDevice.hxx>
#include <WNT_WClass.hxx>
#include <WNT_Window.hxx>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_DEPRECATE
#endif

#endif

#ifndef max
# define max(a, b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
# define min(a, b)  (((a) < (b)) ? (a) : (b)) 
#endif

#define OCC120

//==============================================================================

//==============================================================================
//  VIEWER GLOBAL VARIABLES
//==============================================================================

Standard_IMPORT Standard_Boolean Draw_VirtualWindows;

Standard_EXPORT int ViewerMainLoop(Standard_Integer , const char** argv);
extern const Handle(NIS_InteractiveContext)& TheNISContext();

#ifdef WNT
static Handle(Graphic3d_WNTGraphicDevice)& GetG3dDevice(){
  static Handle(Graphic3d_WNTGraphicDevice) GD;
  return GD;
}

static Handle(WNT_Window)& VT_GetWindow() {
  static Handle(WNT_Window) WNTWin;
  return WNTWin;
}

#else
static Handle(Graphic3d_GraphicDevice)& GetG3dDevice(){
  static Handle(Graphic3d_GraphicDevice) GD;
  return GD;
}
static Handle(Xw_Window)& VT_GetWindow(){
  static Handle(Xw_Window) XWWin;
  return XWWin;
}
static Display *display;

static void VProcessEvents(ClientData,int);
#endif

#ifdef OCC120
static Standard_Boolean DegenerateMode = Standard_True;
#endif

#define ZCLIPWIDTH 1.

static void OSWindowSetup();

//==============================================================================
//  EVENT GLOBAL VARIABLES
//==============================================================================

static int Start_Rot = 0;
static int ZClipIsOn = 0;
static int X_Motion= 0,Y_Motion=0; // Current cursor position
static int X_ButtonPress = 0, Y_ButtonPress = 0; // Last ButtonPress position


//==============================================================================

#ifdef WNT
static LRESULT WINAPI ViewerWindowProc(
                                       HWND hwnd,
                                       UINT uMsg,
                                       WPARAM wParam,
                                       LPARAM lParam );
static LRESULT WINAPI AdvViewerWindowProc(
  HWND hwnd,
  UINT uMsg,
  WPARAM wParam,
  LPARAM lParam );
#endif


//==============================================================================
//function : WClass
//purpose  :
//==============================================================================

const Handle(MMgt_TShared)& ViewerTest::WClass()
{
  static Handle(MMgt_TShared) theWClass;
#ifdef WNT
  if (theWClass.IsNull()) {
    theWClass = new WNT_WClass ("GW3D_Class", AdvViewerWindowProc,
      CS_VREDRAW | CS_HREDRAW, 0, 0,
      ::LoadCursor (NULL, IDC_ARROW));
  }
#endif
  return theWClass;
}

//==============================================================================
//function : ViewerInit
//purpose  : Create the window viewer and initialize all the global variable
//==============================================================================

void ViewerTest::ViewerInit (const Standard_Integer thePxLeft,  const Standard_Integer thePxTop,
                             const Standard_Integer thePxWidth, const Standard_Integer thePxHeight)
{
  static Standard_Boolean isFirst = Standard_True;

  // Default position and dimension of the viewer window.
  // Note that left top corner is set to be sufficiently small to have 
  // window fit in the small screens (actual for remote desktops, see #23003).
  // The position corresponds to the window's client area, thus some 
  // gap is added for window frame to be visible.
  Standard_Integer aPxLeft   = 20;
  Standard_Integer aPxTop    = 40;
  Standard_Integer aPxWidth  = 409;
  Standard_Integer aPxHeight = 409;
  if (thePxWidth != 0 && thePxHeight != 0)
  {
    aPxLeft   = thePxLeft;
    aPxTop    = thePxTop;
    aPxWidth  = thePxWidth;
    aPxHeight = thePxHeight;
  }

  if (isFirst)
  {
    // Create the Graphic device
#ifdef WNT
    if (GetG3dDevice().IsNull()) GetG3dDevice() = new Graphic3d_WNTGraphicDevice();
    if (VT_GetWindow().IsNull())
    {
      // Create the Graphic device and the window
      Handle(WNT_GraphicDevice) g_Device = new WNT_GraphicDevice();

      VT_GetWindow() = new WNT_Window (g_Device, "Test3d",
                                       Handle(WNT_WClass)::DownCast (WClass()),
                                       WS_OVERLAPPEDWINDOW,
                                       aPxLeft, aPxTop,
                                       aPxWidth, aPxHeight,
                                       Quantity_NOC_BLACK);
      VT_GetWindow()->SetVirtual (Draw_VirtualWindows);
    }
#else
    if (GetG3dDevice().IsNull()) GetG3dDevice() =
      new Graphic3d_GraphicDevice (getenv ("DISPLAY"), Xw_TOM_READONLY);
    if (VT_GetWindow().IsNull())
    {
      VT_GetWindow() = new Xw_Window (GetG3dDevice(),
                                      "Test3d",
                                      aPxLeft, aPxTop,
                                      aPxWidth, aPxHeight,
                                      Xw_WQ_3DQUALITY,
                                      Quantity_NOC_BLACK);
      VT_GetWindow()->SetVirtual (Draw_VirtualWindows);
    }
#endif

    Handle(V3d_Viewer) a3DViewer, a3DCollector;
    // Viewer and View creation

    TCollection_ExtendedString NameOfWindow("Visu3D");

    a3DViewer = new V3d_Viewer(GetG3dDevice(), NameOfWindow.ToExtString());
    NameOfWindow = TCollection_ExtendedString("Collector");
    a3DCollector = new V3d_Viewer(GetG3dDevice(), NameOfWindow.ToExtString());
    a3DViewer->SetDefaultBackgroundColor(Quantity_NOC_BLACK);
    a3DCollector->SetDefaultBackgroundColor(Quantity_NOC_STEELBLUE);
    Handle(NIS_View) aView = Handle(NIS_View)::DownCast(ViewerTest::CurrentView());
    if (aView.IsNull())
    {
      //Handle(V3d_View) a3DViewCol = a3DViewer->CreateView();
      aView = new NIS_View (a3DViewer, VT_GetWindow());
      ViewerTest::CurrentView(aView);
      TheNISContext()->AttachView (aView);
    }

    // AIS setup
    if ( ViewerTest::GetAISContext().IsNull() ) {
      Handle(AIS_InteractiveContext) C =
        new AIS_InteractiveContext(a3DViewer,a3DCollector);
      ViewerTest::SetAISContext(C);
    }

    // Setup for X11 or NT
    OSWindowSetup();
    // Viewer and View creation

    a3DViewer->SetDefaultBackgroundColor(Quantity_NOC_BLACK);

    Handle (V3d_View) V = ViewerTest::CurrentView();

    V->SetDegenerateModeOn();
#ifdef OCC120
    DegenerateMode = V->DegenerateModeIsOn();
#endif
    //    V->SetWindow(VT_GetWindow(), NULL, MyViewProc, NULL);

    V->SetZClippingDepth(0.5);
    V->SetZClippingWidth(ZCLIPWIDTH/2.);
    a3DViewer->SetDefaultLights();
    a3DViewer->SetLightOn();

#ifndef WNT
#if TCL_MAJOR_VERSION  < 8
    Tk_CreateFileHandler((void*)ConnectionNumber(display),
      TK_READABLE, VProcessEvents, (ClientData) VT_GetWindow()->XWindow() );
#else
    Tk_CreateFileHandler(ConnectionNumber(display),
      TK_READABLE, VProcessEvents, (ClientData) VT_GetWindow()->XWindow() );
#endif
#endif

    isFirst = Standard_False;
  }
  VT_GetWindow()->Map();
}

//==============================================================================
//function : Vinit
//purpose  : Create the window viewer and initialize all the global variable
//    Use Tk_CreateFileHandler on UNIX to cath the X11 Viewer event
//==============================================================================

static int VInit (Draw_Interpretor& , Standard_Integer argc, const char** argv)
{
  Standard_Integer aPxLeft   = (argc > 1) ? atoi (argv[1]) : 0;
  Standard_Integer aPxTop    = (argc > 2) ? atoi (argv[2]) : 0;
  Standard_Integer aPxWidth  = (argc > 3) ? atoi (argv[3]) : 0;
  Standard_Integer aPxHeight = (argc > 4) ? atoi (argv[4]) : 0;
  ViewerTest::ViewerInit (aPxLeft, aPxTop, aPxWidth, aPxHeight);
  return 0;
}

//==============================================================================
//function : ProcessKeyPress
//purpose  : Handle KeyPress event from a CString
//==============================================================================

static void ProcessKeyPress( char *buf_ret )
{
  //cout << "KeyPress" << endl;
  const Handle(V3d_View) aView = ViewerTest::CurrentView();
  const Handle(NIS_View) aNisView = Handle(NIS_View)::DownCast (aView);
  // Letter in alphabetic order

  if ( !strcasecmp(buf_ret, "A") ) {
    // AXO
    aView->SetProj(V3d_XposYnegZpos);
  }
  else if ( !strcasecmp(buf_ret, "D") ) {
    // Reset
    aView->Reset();
  }
  else if ( !strcasecmp(buf_ret, "F") ) {
    // FitAll
    if (aNisView.IsNull())
      aView->FitAll();
    else
      aNisView->FitAll3d();
  }
  else if ( !strcasecmp(buf_ret, "H") ) {
    // HLR
    cout << "HLR" << endl;
#ifdef OCC120
    if (aView->DegenerateModeIsOn()) ViewerTest::CurrentView()->SetDegenerateModeOff();
    else aView->SetDegenerateModeOn();
    DegenerateMode = aView->DegenerateModeIsOn();
#else
    ViewerTest::CurrentView()->SetDegenerateModeOff();
#endif
  }
  else if ( !strcasecmp(buf_ret, "S") ) {
    // SHADING
    cout << "passage en mode 1 (shading pour les shapes)" << endl;
#ifndef OCC120
    ViewerTest::CurrentView()->SetDegenerateModeOn();
#endif
    Handle(AIS_InteractiveContext) Ctx = ViewerTest::GetAISContext();
    if(Ctx->NbCurrents()==0 ||
      Ctx->NbSelected()==0)
      Ctx->SetDisplayMode(AIS_Shaded);
    else{
      if(Ctx->HasOpenedContext()){
        for(Ctx->InitSelected();Ctx->MoreSelected();Ctx->NextSelected())
          Ctx->SetDisplayMode(Ctx->Interactive(),1,Standard_False);
      }
      else{
        for(Ctx->InitCurrent();Ctx->MoreCurrent();Ctx->NextCurrent())
          Ctx->SetDisplayMode(Ctx->Current(),1,Standard_False);
      }
      Ctx->UpdateCurrentViewer();
    }
  }
  else if ( !strcasecmp(buf_ret, "U") ) {
    // Unset display mode
    cout<<"passage au mode par defaut"<<endl;
#ifndef OCC120
    ViewerTest::CurrentView()->SetDegenerateModeOn();
#endif
    Handle(AIS_InteractiveContext) Ctx = ViewerTest::GetAISContext();
    if(Ctx->NbCurrents()==0 ||
      Ctx->NbSelected()==0)
      Ctx->SetDisplayMode(AIS_WireFrame);
    else{
      if(Ctx->HasOpenedContext()){
        for(Ctx->InitSelected();Ctx->MoreSelected();Ctx->NextSelected())
          Ctx->UnsetDisplayMode(Ctx->Interactive(),Standard_False);
      }
      else{
        for(Ctx->InitCurrent();Ctx->MoreCurrent();Ctx->NextCurrent())
          Ctx->UnsetDisplayMode(Ctx->Current(),Standard_False);
      }
      Ctx->UpdateCurrentViewer();
    }

  }
  else if ( !strcasecmp(buf_ret, "T") ) {
    // Top
    aView->SetProj(V3d_Zpos);
  }
  else if ( !strcasecmp(buf_ret, "B") ) {
    // Bottom
    aView->SetProj(V3d_Zneg);
  }
  else if ( !strcasecmp(buf_ret, "L") ) {
    // Left
    aView->SetProj(V3d_Xneg);
  }
  else if ( !strcasecmp(buf_ret, "R") ) {
    // Right
    aView->SetProj(V3d_Xpos);
  }

  else if ( !strcasecmp(buf_ret, "W") ) {
    // WIREFRAME
#ifndef OCC120
    ViewerTest::CurrentView()->SetDegenerateModeOn();
#endif
    cout << "passage en mode 0 (filaire pour les shapes)" << endl;
#ifndef OCC120
    ViewerTest::CurrentView()->SetDegenerateModeOn();
#endif
    Handle(AIS_InteractiveContext) Ctx = ViewerTest::GetAISContext();
    if(Ctx->NbCurrents()==0 ||
      Ctx->NbSelected()==0)
      Ctx->SetDisplayMode(AIS_WireFrame);
    else{
      if(Ctx->HasOpenedContext()){
        for(Ctx->InitSelected();Ctx->MoreSelected();Ctx->NextSelected())
          Ctx->SetDisplayMode(Ctx->Interactive(),0,Standard_False);
      }
      else{
        for(Ctx->InitCurrent();Ctx->MoreCurrent();Ctx->NextCurrent())
          Ctx->SetDisplayMode(Ctx->Current(),0,Standard_False);
      }
      Ctx->UpdateCurrentViewer();
    }
  }
  else if ( !strcasecmp(buf_ret, "Z") ) {
    // ZCLIP

    if ( ZClipIsOn ) {
      cout << "ZClipping OFF" << endl;
      ZClipIsOn = 0;

      aView->SetZClippingType(V3d_OFF);
      aView->Redraw();
    }
    else {
      cout << "ZClipping ON" << endl;
      ZClipIsOn = 1;

      aView->SetZClippingType(V3d_FRONT);
      aView->Redraw();
    }
  }
  else if ( !strcasecmp(buf_ret, ",") ) {
    ViewerTest::GetAISContext()->HilightNextDetected(ViewerTest::CurrentView());


  }
  else if ( !strcasecmp(buf_ret, ".") ) {
    ViewerTest::GetAISContext()->HilightPreviousDetected(ViewerTest::CurrentView());
  }
  // Number
  else{
    Standard_Integer Num = atoi(buf_ret);
    if(Num>=0 && Num<=7)
      ViewerTest::StandardModeActivation(Num);
  }
}

//==============================================================================
//function : ProcessExpose
//purpose  : Redraw the View on an Expose Event
//==============================================================================

static void ProcessExpose(  )
{ //cout << "Expose" << endl;
  ViewerTest::CurrentView()->Redraw();
}

//==============================================================================
//function : ProcessConfigure
//purpose  : Resize the View on an Configure Event
//==============================================================================

static void ProcessConfigure()
{
  Handle(V3d_View) V = ViewerTest::CurrentView();
  V->MustBeResized();
  V->Update();
  V->Redraw();
}

//==============================================================================
//function : ProcessButton1Press
//purpose  : Picking
//==============================================================================

static Standard_Boolean ProcessButton1Press(
  Standard_Integer ,
  const char** argv,
  Standard_Boolean pick,
  Standard_Boolean shift )
{
  Handle(ViewerTest_EventManager) EM = ViewerTest::CurrentEventManager();
  if ( pick ) {
    Standard_Real X, Y, Z;

    ViewerTest::CurrentView()->Convert(X_Motion, Y_Motion, X, Y, Z);

    Draw::Set(argv[1], X);
    Draw::Set(argv[2], Y);
    Draw::Set(argv[3], Z);}

  if(shift)
    EM->ShiftSelect();
  else
    EM->Select();

  pick = 0;
  return pick;
}

//==============================================================================
//function : ProcessButton3Press
//purpose  : Start Rotation
//==============================================================================

static void ProcessButton3Press()

{ // Start rotation
  Start_Rot = 1;
  ViewerTest::CurrentView()->SetDegenerateModeOn();
  ViewerTest::CurrentView()->StartRotation( X_ButtonPress, Y_ButtonPress );

}
//==============================================================================
//function : ProcessButtonRelease
//purpose  : Start Rotation
//==============================================================================

static void ProcessButtonRelease()

{ // End rotation
#ifdef OCC120
  if (Start_Rot) {
    Start_Rot = 0;
    if (!DegenerateMode) ViewerTest::CurrentView()->SetDegenerateModeOff();
  }
#else
  Start_Rot = 0;
  ViewerTest::CurrentView()->SetDegenerateModeOff();
#endif
}

//==============================================================================
//function : ProcessZClipMotion
//purpose  : Zoom
//==============================================================================

void ProcessZClipMotion()
{
  Handle(V3d_View)  a3DView = ViewerTest::CurrentView();
  if ( Abs(X_Motion - X_ButtonPress) > 2 ) {
    static Standard_Real CurZPos = 0.;

    //Quantity_Length VDX, VDY;
    //a3DView->Size(VDX,VDY);
    //Standard_Real VDZ = a3DView->ZSize();
    //printf("View size (%lf,%lf,%lf)\n", VDX, VDY, VDZ);

    Quantity_Length dx = a3DView->Convert(X_Motion - X_ButtonPress);

    // Front = Depth + width/2.
    Standard_Real D = 0.5;
    Standard_Real W = 0.1;

    CurZPos += (dx);

    D += CurZPos;

    //printf("dx %lf Depth %lf Width %lf\n", dx, D, W);

    a3DView->SetZClippingType(V3d_OFF);
    a3DView->SetZClippingDepth(D);
    a3DView->SetZClippingWidth(W);
    a3DView->SetZClippingType(V3d_FRONT);

    a3DView->Redraw();

    X_ButtonPress = X_Motion;
    Y_ButtonPress = Y_Motion;
  }
}

//==============================================================================
//function : ProcessControlButton1Motion
//purpose  : Zoom
//==============================================================================

static void ProcessControlButton1Motion()
{
  ViewerTest::CurrentView()->Zoom( X_ButtonPress, Y_ButtonPress, X_Motion, Y_Motion);

  X_ButtonPress = X_Motion;
  Y_ButtonPress = Y_Motion;
}

//==============================================================================
//function : ProcessControlButton2Motion
//purpose  : Pann
//==============================================================================

static void ProcessControlButton2Motion()
{
  Quantity_Length dx = ViewerTest::CurrentView()->Convert(X_Motion - X_ButtonPress);
  Quantity_Length dy = ViewerTest::CurrentView()->Convert(Y_Motion - Y_ButtonPress);

  dy = -dy; // Xwindow Y axis is from top to Bottom

  ViewerTest::CurrentView()->Panning( dx, dy );

  X_ButtonPress = X_Motion;
  Y_ButtonPress = Y_Motion;
}

//==============================================================================
//function : ProcessControlButton3Motion
//purpose  : Rotation
//==============================================================================

static void ProcessControlButton3Motion()
{
  if ( Start_Rot ) ViewerTest::CurrentView()->Rotation( X_Motion, Y_Motion);
}

//==============================================================================
//function : ProcessPointerMotion
//purpose  : Rotation
//==============================================================================

static void ProcessMotion()
{
  //pre-hilights detected objects at mouse position

  Handle(ViewerTest_EventManager) EM = ViewerTest::CurrentEventManager();
  EM->MoveTo(X_Motion, Y_Motion);
}


void ViewerTest::GetMousePosition(Standard_Integer& Xpix,Standard_Integer& Ypix)
{
  Xpix = X_Motion;Ypix=Y_Motion;
}

//==============================================================================
//function : ViewProject: implements VAxo, VTop, VLeft, ...
//purpose  : Switches to an axonometric, top, left and other views
//==============================================================================

static int ViewProject(Draw_Interpretor& di, const V3d_TypeOfOrientation ori)
{
  if ( ViewerTest::CurrentView().IsNull() ) 
  {
    di<<"Call vinit before this command, please"<<"\n";
    return 1;
  }

  ViewerTest::CurrentView()->SetProj(ori);
  return 0;
}

//==============================================================================
//function : VAxo
//purpose  : Switch to an Axonometric view
//Draw arg : No args
//==============================================================================

static int VAxo(Draw_Interpretor& di, Standard_Integer , const char** )
{
  return ViewProject(di, V3d_XposYnegZpos);
}

//==============================================================================
//function : VTop
//purpose  : Switch to a Top View
//Draw arg : No args
//==============================================================================

static int VTop(Draw_Interpretor& di, Standard_Integer , const char** )
{
  return ViewProject(di, V3d_Zpos);
}

//==============================================================================
//function : VBottom
//purpose  : Switch to a Bottom View
//Draw arg : No args
//==============================================================================

static int VBottom(Draw_Interpretor& di, Standard_Integer , const char** )
{
  return ViewProject(di, V3d_Zneg);
}

//==============================================================================
//function : VLeft
//purpose  : Switch to a Left View
//Draw arg : No args
//==============================================================================

static int VLeft(Draw_Interpretor& di, Standard_Integer , const char** )
{
  return ViewProject(di, V3d_Ypos);
}

//==============================================================================
//function : VRight
//purpose  : Switch to a Right View
//Draw arg : No args
//==============================================================================

static int VRight(Draw_Interpretor& di, Standard_Integer , const char** )
{
  return ViewProject(di, V3d_Yneg);
}

//==============================================================================
//function : VFront
//purpose  : Switch to a Front View
//Draw arg : No args
//==============================================================================

static int VFront(Draw_Interpretor& di, Standard_Integer , const char** )
{
  return ViewProject(di, V3d_Xpos);
}

//==============================================================================
//function : VBack
//purpose  : Switch to a Back View
//Draw arg : No args
//==============================================================================

static int VBack(Draw_Interpretor& di, Standard_Integer , const char** )
{
  return ViewProject(di, V3d_Xneg);
}

//==============================================================================
//function : VHelp
//purpose  : Dsiplay help on viewer Keyboead and mouse commands
//Draw arg : No args
//==============================================================================

static int VHelp(Draw_Interpretor& di, Standard_Integer , const char** )
{

  di << "Q : Quit the application" << "\n";

  di << "========================="<<"\n";
  di << "F : FitAll" << "\n";
  di << "T : TopView" << "\n";
  di << "B : BottomView" << "\n";
  di << "R : RightView" << "\n";
  di << "L : LeftView" << "\n";
  di << "A : AxonometricView" << "\n";
  di << "D : ResetView" << "\n";

  di << "========================="<<"\n";
  di << "S : Shading" << "\n";
  di << "W : Wireframe" << "\n";
  di << "H : HidelLineRemoval" << "\n";
  di << "U : Unset display mode" << "\n";

  di << "========================="<<"\n";
  di << "Selection mode "<<"\n";
  di << "0 : Shape" <<"\n";
  di << "1 : Vertex" <<"\n";
  di << "2 : Edge" <<"\n";
  di << "3 : Wire" <<"\n";
  di << "4 : Face" <<"\n";
  di << "5 : Shell" <<"\n";
  di << "6 : Solid" <<"\n";
  di << "7 : Compound" <<"\n";

  di << "========================="<<"\n";
  di << "Z : Switch Z clipping On/Off" << "\n";
  di << ", : Hilight next detected" << "\n";
  di << ". : Hilight previous detected" << "\n";

  return 0;
}

Standard_Boolean IsDragged = Standard_False;

Standard_Integer xx1, yy1, xx2, yy2;
//the first and last point in viewer co-ordinates

Standard_Boolean DragFirst;


#ifdef WNT

static Standard_Boolean Ppick = 0;
static Standard_Integer Pargc = 0;
static const char**           Pargv = NULL;


static LRESULT WINAPI AdvViewerWindowProc( HWND hwnd,
                                          UINT Msg,
                                          WPARAM wParam,
                                          LPARAM lParam )
{
  if ( !ViewerTest::CurrentView().IsNull() ) {

    WPARAM fwKeys = wParam;

    switch( Msg ) {

    case WM_LBUTTONUP:
      IsDragged = Standard_False;
      if( !DragFirst )
      {
        HDC hdc = GetDC( hwnd );
        SelectObject( hdc, GetStockObject( WHITE_PEN ) );
        SelectObject( hdc, GetStockObject( HOLLOW_BRUSH ) );
        SetROP2( hdc, R2_NOT );
        Rectangle( hdc, xx1, yy1, xx2, yy2 );
        ReleaseDC( hwnd, hdc );

        const Handle(ViewerTest_EventManager) EM =
          ViewerTest::CurrentEventManager();
        if ( fwKeys & MK_SHIFT )
          EM->ShiftSelect( min( xx1, xx2 ), max( yy1, yy2 ),
          max( xx1, xx2 ), min( yy1, yy2 ));
        else
          EM->Select( min( xx1, xx2 ), max( yy1, yy2 ),
          max( xx1, xx2 ), min( yy1, yy2 ));
      }
      return ViewerWindowProc( hwnd, Msg, wParam, lParam );

    case WM_LBUTTONDOWN:
      if( fwKeys == MK_LBUTTON || fwKeys == ( MK_LBUTTON | MK_SHIFT ) )
      {
        IsDragged = Standard_True;
        DragFirst = Standard_True;
        xx1 = LOWORD(lParam);
        yy1 = HIWORD(lParam);
      }
      return ViewerWindowProc( hwnd, Msg, wParam, lParam );

      break;

    case WM_MOUSEMOVE:
      if( IsDragged )
      {
        HDC hdc = GetDC( hwnd );

        HGDIOBJ anObj = SelectObject( hdc, GetStockObject( WHITE_PEN ) );
        SelectObject( hdc, GetStockObject( HOLLOW_BRUSH ) );
        SetROP2( hdc, R2_NOT );

        if( !DragFirst )
          Rectangle( hdc, xx1, yy1, xx2, yy2 );

        DragFirst = Standard_False;
        xx2 = LOWORD(lParam);
        yy2 = HIWORD(lParam);

        Rectangle( hdc, xx1, yy1, xx2, yy2 );

        SelectObject( hdc, anObj );

        ReleaseDC( hwnd, hdc );
      }
      else
        return ViewerWindowProc( hwnd, Msg, wParam, lParam );
      break;

    default:
      return ViewerWindowProc( hwnd, Msg, wParam, lParam );
    }
    return 0;
  }
  return ViewerWindowProc( hwnd, Msg, wParam, lParam );
}


static LRESULT WINAPI ViewerWindowProc( HWND hwnd,
                                       UINT Msg,
                                       WPARAM wParam,
                                       LPARAM lParam )
{
  /*static Standard_Boolean Ppick = 0;
  static Standard_Integer Pargc = 0;
  static char**           Pargv = NULL;*/

  static int Up = 1;

  if ( !ViewerTest::CurrentView().IsNull() ) {
    PAINTSTRUCT    ps;

    switch( Msg ) {
    case WM_CLOSE:
      // do not destroy the window - just hide it!
      VT_GetWindow()->Unmap();
      return 0;
    case WM_PAINT:
      //cout << "\t WM_PAINT" << endl;
      BeginPaint(hwnd, &ps);
      EndPaint(hwnd, &ps);
      ProcessExpose();
      break;

    case WM_SIZE:
      //cout << "\t WM_SIZE" << endl;
      ProcessConfigure();
      break;

    case WM_KEYDOWN:
      //cout << "\t WM_KEYDOWN " << (int) wParam << endl;

      if ( (wParam != VK_SHIFT) && (wParam != VK_CONTROL) ) {
        char c[2];
        c[0] = (char) wParam;
        c[1] = '\0';
        ProcessKeyPress( c);
      }
      break;

    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
      //cout << "\t WM_xBUTTONUP" << endl;
      Up = 1;
      ProcessButtonRelease();
      break;

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
      {
        //cout << "\t WM_xBUTTONDOWN" << endl;
        WPARAM fwKeys = wParam;

        Up = 0;

        X_ButtonPress = LOWORD(lParam);
        Y_ButtonPress = HIWORD(lParam);

        if ( Msg == WM_LBUTTONDOWN) {
          if(fwKeys & MK_CONTROL) {
            Ppick = ProcessButton1Press( Pargc, Pargv, Ppick,  (fwKeys & MK_SHIFT) );
          } else
            ProcessButton1Press( Pargc, Pargv, Ppick,  (fwKeys & MK_SHIFT) );
        }
        else if ( Msg == WM_RBUTTONDOWN ) {
          // Start rotation
          ProcessButton3Press( );
        }
      }
      break;

    case WM_MOUSEMOVE:
      {
        //cout << "\t WM_MOUSEMOVE" << endl;
        WPARAM fwKeys = wParam;
        X_Motion = LOWORD(lParam);
        Y_Motion = HIWORD(lParam);

        if ( Up &&
          fwKeys & ( MK_LBUTTON|MK_MBUTTON|MK_RBUTTON ) ) {
            Up = 0;
            X_ButtonPress = LOWORD(lParam);
            Y_ButtonPress = HIWORD(lParam);

            if ( fwKeys & MK_RBUTTON ) {
              // Start rotation
              ProcessButton3Press();
            }
          }

          if ( fwKeys & MK_CONTROL ) {
            if ( fwKeys & MK_LBUTTON ) {
              ProcessControlButton1Motion();
            }
            else if ( fwKeys & MK_MBUTTON ||
              ((fwKeys&MK_LBUTTON) &&
              (fwKeys&MK_RBUTTON) ) ){
                ProcessControlButton2Motion();
              }
            else if ( fwKeys & MK_RBUTTON ) {
              ProcessControlButton3Motion();
            }
          }
#ifdef BUG
          else if ( fwKeys & MK_SHIFT ) {
            if ( fwKeys & MK_MBUTTON ||
              ((fwKeys&MK_LBUTTON) &&
              (fwKeys&MK_RBUTTON) ) ) {
                cout << "ProcessZClipMotion()" << endl;
                ProcessZClipMotion();
              }
          }
#endif
          else
            if (( fwKeys & MK_MBUTTON || ((fwKeys&MK_LBUTTON) && (fwKeys&MK_RBUTTON) ) )){
              ProcessZClipMotion();
            }
            else {
              ProcessMotion();
            }
      }
      break;

    default:
      return( DefWindowProc( hwnd, Msg, wParam, lParam ));
    }
    return 0L;
  }

  return DefWindowProc( hwnd, Msg, wParam, lParam );
}




//==============================================================================
//function : ViewerMainLoop
//purpose  : Get a Event on the view and dispatch it
//==============================================================================
int ViewerMainLoop(Standard_Integer argc, const char** argv)
{

  //cout << "No yet implemented on WNT" << endl;
  /*static Standard_Boolean Ppick = 0;
  static Standard_Integer Pargc = 0;
  static char**           Pargv = NULL;*/

  //Ppick = (argc > 0)? -1 : 0;
  Ppick = (argc > 0)? 1 : 0;
  Pargc = argc;
  Pargv = argv;

  if ( Ppick ) {
    MSG msg;
    msg.wParam = 1;

    cout << "Start picking" << endl;

    //while ( Ppick == -1 ) {
    while ( Ppick == 1 ) {
      // Wait for a ProcessButton1Press() to toggle pick to 1 or 0
      if (GetMessage(&msg, NULL, 0, 0) ) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

    cout << "Picking done" << endl;
  }

  return Ppick;
}


#else

int ViewerMainLoop(Standard_Integer argc, const char** argv)

{ Standard_Boolean pick = argc > 0;

// X11 Event loop

static XEvent report;

XNextEvent( display, &report );
//    cout << "rep type = " << report.type << endl;
//    cout << "rep button = " << report.xbutton.button << endl;

switch ( report.type ) {
      case Expose:
        {
          ProcessExpose();
        }
        break;
      case ConfigureNotify:
        {
          ProcessConfigure();
        }
        break;
      case KeyPress:
        {

          KeySym ks_ret ;
          char buf_ret[11] ;
          int ret_len ;
          XComposeStatus status_in_out;

          ret_len = XLookupString( ( XKeyEvent *)&report ,
            (char *) buf_ret , 10 ,
            &ks_ret , &status_in_out ) ;


          buf_ret[ret_len] = '\0' ;

          if ( ret_len ) {
            ProcessKeyPress( buf_ret);
          }
        }
        break;
      case ButtonPress:
        //  cout << "ButtonPress" << endl;
        {
          X_ButtonPress = report.xbutton.x;
          Y_ButtonPress = report.xbutton.y;

          if ( report.xbutton.button == Button1 )
            if(  report.xbutton.state & ControlMask )
              pick = ProcessButton1Press( argc, argv, pick,
              ( report.xbutton.state & ShiftMask) );
            else
            {
              IsDragged = Standard_True;
              xx1 = X_ButtonPress;
              yy1 = Y_ButtonPress;
              DragFirst = Standard_True;
            }
          else if ( report.xbutton.button == Button3 )
            // Start rotation
            ProcessButton3Press();
        }
        break;
      case ButtonRelease:
        {
          //    cout<<"relachement du bouton "<<(report.xbutton.button==3 ? "3": "on s'en fout") <<endl;
          //    cout << IsDragged << endl;
          //    cout << DragFirst << endl;

          if( IsDragged )
          {
            if( !DragFirst )
            {
              Aspect_Handle aWindow = VT_GetWindow()->XWindow();
              GC gc = XCreateGC( display, aWindow, 0, 0 );
              //  XSetFunction( display, gc, GXinvert );
              XDrawRectangle( display, aWindow, gc, min( xx1, xx2 ), min( yy1, yy2 ), abs( xx2-xx1 ), abs( yy2-yy1 ) );
            }

            Handle( AIS_InteractiveContext ) aContext = ViewerTest::GetAISContext();
            if( aContext.IsNull() )
            {
              cout << "The context is null. Please use vinit before createmesh" << endl;
              return 0;
            }

            Standard_Boolean ShiftPressed = ( report.xbutton.state & ShiftMask );
            if( report.xbutton.button==1 )
              if( DragFirst )
                if( ShiftPressed )
                {
                  aContext->ShiftSelect();
                  //                   cout << "shift select" << endl;
                }
                else
                {
                  aContext->Select();
                  //                   cout << "select" << endl;
                }
              else
                if( ShiftPressed )
                {
                  aContext->ShiftSelect( min( xx1, xx2 ), min( yy1, yy2 ),
                    max( xx1, xx2 ), max( yy1, yy2 ),
                    ViewerTest::CurrentView());
                  //                   cout << "shift select" << endl;
                }
                else
                {
                  aContext->Select( min( xx1, xx2 ), min( yy1, yy2 ),
                    max( xx1, xx2 ), max( yy1, yy2 ),
                    ViewerTest::CurrentView() );
                  //                   cout << "select" << endl;
                }
            else
              ProcessButtonRelease();

            IsDragged = Standard_False;
          }
          else
            ProcessButtonRelease();
        }
        break;
      case MotionNotify:
        {
          //    XEvent dummy;

          X_Motion = report.xmotion.x;
          Y_Motion = report.xmotion.y;

          if( IsDragged )
          {
            Aspect_Handle aWindow = VT_GetWindow()->XWindow();
            GC gc = XCreateGC( display, aWindow, 0, 0 );
            XSetFunction( display, gc, GXinvert );

            if( !DragFirst )
              XDrawRectangle( display, aWindow, gc, min( xx1, xx2 ), min( yy1, yy2 ), abs( xx2-xx1 ), abs( yy2-yy1 ) );

            xx2 = X_Motion;
            yy2 = Y_Motion;
            DragFirst = Standard_False;

            //cout << "draw rect : " << xx2 << ", " << yy2 << endl;
            XDrawRectangle( display, aWindow, gc, min( xx1, xx2 ), min( yy1, yy2 ), abs( xx2-xx1 ), abs( yy2-yy1 ) );
          }
          else
          {

            //cout << "MotionNotify " << X_Motion << "," << Y_Motion << endl;

            // remove all the ButtonMotionMask
            while( XCheckMaskEvent( display, ButtonMotionMask, &report) ) ;

            if ( ZClipIsOn && report.xmotion.state & ShiftMask ) {
              if ( Abs(X_Motion - X_ButtonPress) > 2 ) {

                Quantity_Length VDX, VDY;

                ViewerTest::CurrentView()->Size(VDX,VDY);
                Standard_Real VDZ =0 ;
                VDZ = ViewerTest::CurrentView()->ZSize();

                //          printf("%lf,%lf,%lf\n", VDX, VDY, VDZ);
                printf("%f,%f,%f\n", VDX, VDY, VDZ);

                Quantity_Length dx = 0 ;
                dx = ViewerTest::CurrentView()->Convert(X_Motion - X_ButtonPress);

                cout << dx << endl;

                dx = dx / VDX * VDZ;

                cout << dx << endl;

                // Front = Depth + width/2.
                //ViewerTest::CurrentView()->SetZClippingDepth(dx);
                //ViewerTest::CurrentView()->SetZClippingWidth(0.);

                ViewerTest::CurrentView()->Redraw();
              }
            }

            if ( report.xmotion.state & ControlMask ) {
              if ( report.xmotion.state & Button1Mask ) {
                ProcessControlButton1Motion();
              }
              else if ( report.xmotion.state & Button2Mask ) {
                ProcessControlButton2Motion();
              }
              else if ( report.xmotion.state & Button3Mask ) {
                ProcessControlButton3Motion();
              }
            }
            else {
              ProcessMotion();
            }
          }
        }
        break;
}


return pick;
}

//==============================================================================
//function : VProcessEvents
//purpose  : call by Tk_CreateFileHandler() to be able to manage the
//       event in the Viewer window
//==============================================================================

static void VProcessEvents(ClientData,int)
{
  //cout << "VProcessEvents" << endl;

  // test for X Event
  while (XPending(display)) {
    ViewerMainLoop( 0, NULL);
  }
}
#endif

//==============================================================================
//function : OSWindowSetup
//purpose  : Setup for the X11 window to be able to cath the event
//==============================================================================


static void OSWindowSetup()
{
#ifndef WNT
  // X11

  Window  window   = VT_GetWindow()->XWindow();

  Standard_Address theDisplay = GetG3dDevice()->XDisplay();
  display = (Display * ) theDisplay;
  //  display = (Display *)GetG3dDevice()->XDisplay();

  XSynchronize(display, 1);

  VT_GetWindow()->Map();

  // X11 : For keyboard on SUN
  XWMHints wmhints;
  wmhints.flags = InputHint;
  wmhints.input = 1;

  XSetWMHints( display, window, &wmhints);

  XSelectInput( display, window,  ExposureMask | KeyPressMask |
    ButtonPressMask | ButtonReleaseMask |
    StructureNotifyMask |
    PointerMotionMask |
    Button1MotionMask | Button2MotionMask |
    Button3MotionMask
    );

  XSynchronize(display, 0);

#else
  // WNT
#endif

}


//==============================================================================
//function : VFit

//purpose  : Fitall, no DRAW arguments
//Draw arg : No args
//==============================================================================

static int VFit(Draw_Interpretor& , Standard_Integer , const char** )
{
  const Handle(V3d_View) aView = ViewerTest::CurrentView();
  Handle(NIS_View) V = Handle(NIS_View)::DownCast(aView);
  if (V.IsNull() == Standard_False) {
    V->FitAll3d();
  } else if (aView.IsNull() == Standard_False) {
    aView->FitAll();
  }
  return 0;
}

//==============================================================================
//function : VZFit
//purpose  : ZFitall, no DRAW arguments
//Draw arg : No args
//==============================================================================

static int VZFit(Draw_Interpretor& , Standard_Integer , const char** )
{
  Handle(V3d_View) V = ViewerTest::CurrentView();
  if ( !V.IsNull() ) V->ZFitAll(); return 0; }


static int VRepaint(Draw_Interpretor& , Standard_Integer , const char** )
{
  Handle(V3d_View) V = ViewerTest::CurrentView();
  if ( !V.IsNull() ) V->Redraw(); return 0;
}


//==============================================================================
//function : VClear
//purpose  : Remove all the object from the viewer
//Draw arg : No args
//==============================================================================

static int VClear(Draw_Interpretor& , Standard_Integer , const char** )
{
  Handle(V3d_View) V = ViewerTest::CurrentView();
  if(!V.IsNull())
    ViewerTest::Clear();
  return 0;
}

//==============================================================================
//function : VPick
//purpose  :
//==============================================================================

static int VPick(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{ if (ViewerTest::CurrentView().IsNull() ) return 1;

if ( argc < 4 ) {
  di << argv[0] << "Invalid number of arguments" << "\n";
  return 1;
}

while (ViewerMainLoop( argc, argv)) {
}

return 0;
}



//==============================================================================
//function : InitViewerTest
//purpose  : initialisation de toutes les variables static de  ViewerTest (dp)
//==============================================================================

void ViewerTest_InitViewerTest (const Handle(AIS_InteractiveContext)& context)
{
  Handle(V3d_Viewer) viewer = context->CurrentViewer();
  ViewerTest::SetAISContext(context);
  viewer->InitActiveViews();
  Handle(V3d_View) view = viewer->ActiveView();
  if (viewer->MoreActiveViews()) ViewerTest::CurrentView(view);
  ViewerTest::ResetEventManager();
  Handle(Aspect_GraphicDevice) device = viewer->Device();
  Handle(Aspect_Window) window = view->Window();
#ifndef WNT
  // X11
  VT_GetWindow() = Handle(Xw_Window)::DownCast(window);
  GetG3dDevice() = Handle(Graphic3d_GraphicDevice)::DownCast(device);
  OSWindowSetup();
  static int first = 1;
  if ( first ) {
#if TCL_MAJOR_VERSION  < 8
    Tk_CreateFileHandler((void*)ConnectionNumber(display),
      TK_READABLE, VProcessEvents, (ClientData) 0);
#else
    Tk_CreateFileHandler(ConnectionNumber(display),
      TK_READABLE, VProcessEvents, (ClientData) 0);
#endif
    first = 0;
  }
#endif
}


//==============================================================================
//function : VSetBg
//purpose  : Load image as background
//==============================================================================

static int VSetBg(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 2 || argc > 3)
  {
    di << "Usage : " << argv[0] << " imagefile [filltype] : Load image as background" << "\n";
    di << "filltype can be one of CENTERED, TILED, STRETCH, NONE" << "\n";
    return 1;
  }

  Handle(AIS_InteractiveContext) AISContext = ViewerTest::GetAISContext();
  if(AISContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return 1;
  }

  Aspect_FillMethod aFillType = Aspect_FM_CENTERED;
  if (argc == 3)
  {
    const char* szType = argv[2];
    if      (strcmp(szType, "NONE"    ) == 0) aFillType = Aspect_FM_NONE;
    else if (strcmp(szType, "CENTERED") == 0) aFillType = Aspect_FM_CENTERED;
    else if (strcmp(szType, "TILED"   ) == 0) aFillType = Aspect_FM_TILED;
    else if (strcmp(szType, "STRETCH" ) == 0) aFillType = Aspect_FM_STRETCH;
    else
    {
      di << "Wrong fill type : " << szType << "\n";
      di << "Must be one of CENTERED, TILED, STRETCH, NONE" << "\n";
      return 1;
    }
  }

  Handle(V3d_View) V3dView = ViewerTest::CurrentView();
  V3dView->SetBackgroundImage(argv[1], aFillType, Standard_True);

  return 0;
}

//==============================================================================
//function : VSetBgMode
//purpose  : Change background image fill type
//==============================================================================

static int VSetBgMode(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc != 2)
  {
    di << "Usage : " << argv[0] << " filltype : Change background image mode" << "\n";
    di << "filltype must be one of CENTERED, TILED, STRETCH, NONE" << "\n";
    return 1;
  }

  Handle(AIS_InteractiveContext) AISContext = ViewerTest::GetAISContext();
  if(AISContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return 1;
  }

  Aspect_FillMethod aFillType = Aspect_FM_NONE;
  if (argc == 2)
  {
    const char* szType = argv[1];
    if      (strcmp(szType, "NONE"    ) == 0) aFillType = Aspect_FM_NONE;
    else if (strcmp(szType, "CENTERED") == 0) aFillType = Aspect_FM_CENTERED;
    else if (strcmp(szType, "TILED"   ) == 0) aFillType = Aspect_FM_TILED;
    else if (strcmp(szType, "STRETCH" ) == 0) aFillType = Aspect_FM_STRETCH;
    else
    {
      di << "Wrong fill type : " << szType << "\n";
      di << "Must be one of CENTERED, TILED, STRETCH, NONE" << "\n";
      return 1;
    }
  }

  Handle(V3d_View) V3dView = ViewerTest::CurrentView();
  V3dView->SetBgImageStyle(aFillType, Standard_True);

  return 0;
}

//==============================================================================
//function : VSetGradientBg
//purpose  : Mount gradient background
//==============================================================================
static int VSetGradientBg(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc != 8 )
  {
    di << "Usage : " << argv[0] << " R1 G1 B1 R2 G2 B2 Type : Mount gradient background" << "\n";
    di << "R1,G1,B1,R2,G2,B2 = [0..255]" << "\n";
    di << "Type must be one of 0 = NONE, 1 = HOR, 2 = VER, 3 = DIAG1, 4 = DIAG2" << "\n";
    di << "                    5 = CORNER1, 6 = CORNER2, 7 = CORNER3, 8 = CORNER4" << "\n";
    return 1;
  }

  Handle(AIS_InteractiveContext) AISContext = ViewerTest::GetAISContext();
  if(AISContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return 1;
  }
  if (argc == 8)
  {

    Standard_Real R1 = atof(argv[1])/255.;
    Standard_Real G1 = atof(argv[2])/255.;
    Standard_Real B1 = atof(argv[3])/255.;
    Quantity_Color aColor1(R1,G1,B1,Quantity_TOC_RGB);

    Standard_Real R2 = atof(argv[4])/255.;
    Standard_Real G2 = atof(argv[5])/255.;
    Standard_Real B2 = atof(argv[6])/255.;

    Quantity_Color aColor2(R2,G2,B2,Quantity_TOC_RGB);
    int aType = atoi(argv[7]);
    if( aType < 0 || aType > 8 )
    {
      di << "Wrong fill type " << "\n";
      di << "Must be one of 0 = NONE, 1 = HOR, 2 = VER, 3 = DIAG1, 4 = DIAG2" << "\n";
      di << "               5 = CORNER1, 6 = CORNER2, 7 = CORNER3, 8 = CORNER4" << "\n";
      return 1;
    }

    Aspect_GradientFillMethod aMethod = Aspect_GradientFillMethod(aType);

    Handle(V3d_View) V3dView = ViewerTest::CurrentView();
    V3dView->SetBgGradientColors( aColor1, aColor2, aMethod, 1);
  }

  return 0;
}

//==============================================================================
//function : VSetGradientBgMode
//purpose  : Change gradient background fill style
//==============================================================================
static int VSetGradientBgMode(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc != 2 )
  {
    di << "Usage : " << argv[0] << " Type : Change gradient background fill type" << "\n";
    di << "Type must be one of 0 = NONE, 1 = HOR, 2 = VER, 3 = DIAG1, 4 = DIAG2" << "\n";
    di << "                    5 = CORNER1, 6 = CORNER2, 7 = CORNER3, 8 = CORNER4" << "\n";
    return 1;
  }

  Handle(AIS_InteractiveContext) AISContext = ViewerTest::GetAISContext();
  if(AISContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return 1;
  }
  if (argc == 2)
  {
    int aType = atoi(argv[1]);
    if( aType < 0 || aType > 8 )
    {
      di << "Wrong fill type " << "\n";
      di << "Must be one of 0 = NONE, 1 = HOR, 2 = VER, 3 = DIAG1, 4 = DIAG2" << "\n";
      di << "               5 = CORNER1, 6 = CORNER2, 7 = CORNER3, 8 = CORNER4" << "\n";
      return 1;
    }

    Aspect_GradientFillMethod aMethod = Aspect_GradientFillMethod(aType);

    Handle(V3d_View) V3dView = ViewerTest::CurrentView();
    V3dView->SetBgGradientStyle( aMethod, 1 );
  }

  return 0;
}

//==============================================================================
//function : VSetColorBg
//purpose  : Set color background
//==============================================================================
static int VSetColorBg(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc != 4 )
  {
    di << "Usage : " << argv[0] << " R G B : Set color background" << "\n";
    di << "R,G,B = [0..255]" << "\n";
    return 1;
  }

  Handle(AIS_InteractiveContext) AISContext = ViewerTest::GetAISContext();
  if(AISContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return 1;
  }
  if (argc == 4)
  {

    Standard_Real R = atof(argv[1])/255.;
    Standard_Real G = atof(argv[2])/255.;
    Standard_Real B = atof(argv[3])/255.;
    Quantity_Color aColor(R,G,B,Quantity_TOC_RGB);

    Handle(V3d_View) V3dView = ViewerTest::CurrentView();
    V3dView->SetBackgroundColor( aColor );
    V3dView->Update();
  }

  return 0;
}

//==============================================================================
//function : VScale
//purpose  : View Scaling
//==============================================================================

static int VScale(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  Handle(V3d_View) V3dView = ViewerTest::CurrentView();
  if ( V3dView.IsNull() ) return 1;

  if ( argc != 4 ) {
    di << argv[0] << "Invalid number of arguments" << "\n";
    return 1;
  }
  V3dView->SetAxialScale( atof(argv[1]),  atof(argv[2]),  atof(argv[3]) );
  return 0;
}
//==============================================================================
//function : VTestZBuffTrihedron
//purpose  : Displays a V3d_ZBUFFER'ed or V3d_WIREFRAME'd trihedron
//==============================================================================

static int VTestZBuffTrihedron(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  Handle(V3d_View) V3dView = ViewerTest::CurrentView();
  if ( V3dView.IsNull() ) return 1;

  V3dView->ZBufferTriedronSetup();

  if ( argc == 1 ) {
    // Set up default trihedron parameters
    V3dView->TriedronDisplay( Aspect_TOTP_LEFT_LOWER, Quantity_NOC_WHITE, 0.1, V3d_ZBUFFER );
  } else
  if ( argc == 7 )
  {
    Aspect_TypeOfTriedronPosition aPosition = Aspect_TOTP_LEFT_LOWER;
    const char* aPosType = argv[1];

    if ( strcmp(aPosType, "center") == 0 )
    {
      aPosition = Aspect_TOTP_CENTER;
    } else
    if (strcmp(aPosType, "left_lower") == 0)
    {
      aPosition = Aspect_TOTP_LEFT_LOWER;
    } else
    if (strcmp(aPosType, "left_upper") == 0)
    {
      aPosition = Aspect_TOTP_LEFT_UPPER;
    } else
    if (strcmp(aPosType, "right_lower") == 0)
    {
      aPosition = Aspect_TOTP_RIGHT_LOWER;
    } else
    if (strcmp(aPosType, "right_upper") == 0)
    {
      aPosition = Aspect_TOTP_RIGHT_UPPER;
    } else
    {
      di << argv[1] << " Invalid type of alignment"  << "\n";
      di << "Must be one of [ center, left_lower,"   << "\n";
      di << "left_upper, right_lower, right_upper ]" << "\n";
      return 1;
    }

    Standard_Real R = atof(argv[2])/255.;
    Standard_Real G = atof(argv[3])/255.;
    Standard_Real B = atof(argv[4])/255.;
    Quantity_Color aColor(R, G, B, Quantity_TOC_RGB);

    Standard_Real aScale = atof(argv[5]);

    if( aScale <= 0.0 )
    {
      di << argv[5] << " Invalid value. Must be > 0" << "\n";
      return 1;
    }

    V3d_TypeOfVisualization aPresentation = V3d_ZBUFFER;
    const char* aPresType = argv[6];

    if ( strcmp(aPresType, "wireframe") == 0 )
    {
      aPresentation = V3d_WIREFRAME;
    } else
    if (strcmp(aPresType, "zbuffer") == 0)
    {
      aPresentation = V3d_ZBUFFER;
    } else
    {
      di << argv[6] << " Invalid type of visualization" << "\n";
      di << "Must be one of [ wireframe, zbuffer ]"     << "\n";
      return 1;
    }

    V3dView->TriedronDisplay( aPosition, aColor.Name(), aScale, aPresentation );

  } else
  {
    di << argv[0] << " Invalid number of arguments" << "\n";
    return 1;
  }

  V3dView->ZFitAll();

  return 0;
}

//==============================================================================
//function : VRotate
//purpose  : Camera Rotating
//==============================================================================

static int VRotate( Draw_Interpretor& di, Standard_Integer argc, const char** argv ) {
  Handle(V3d_View) V3dView = ViewerTest::CurrentView();
  if ( V3dView.IsNull() ) {
    return 1;
  }

  if ( argc == 4 ) {
    V3dView->Rotate( atof(argv[1]), atof(argv[2]), atof(argv[3]) );
    return 0;
  } else if ( argc == 7 ) {
    V3dView->Rotate( atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]) );
    return 0;
  } else {
    di << argv[0] << " Invalid number of arguments" << "\n";
    return 1;
  }
}

//==============================================================================
//function : VZoom
//purpose  : View zoom in / out (relative to current zoom)
//==============================================================================

static int VZoom( Draw_Interpretor& di, Standard_Integer argc, const char** argv ) {
  Handle(V3d_View) V3dView = ViewerTest::CurrentView();
  if ( V3dView.IsNull() ) {
    return 1;
  }

  if ( argc == 2 ) {
    Standard_Real coef = atof(argv[1]);
    if ( coef <= 0.0 ) {
      di << argv[1] << "Invalid value" << "\n";
      return 1;
    }
    V3dView->SetZoom( atof(argv[1]) );
    return 0;
  } else {
    di << argv[0] << " Invalid number of arguments" << "\n";
    return 1;
  }
}

//==============================================================================
//function : VPan
//purpose  : View panning (in pixels)
//==============================================================================

static int VPan( Draw_Interpretor& di, Standard_Integer argc, const char** argv ) {
  Handle(V3d_View) V3dView = ViewerTest::CurrentView();
  if ( V3dView.IsNull() ) return 1;

  if ( argc == 3 ) {
    V3dView->Pan( atoi(argv[1]), atoi(argv[2]) );
    return 0;
  } else {
    di << argv[0] << " Invalid number of arguments" << "\n";
    return 1;
  }
}


//==============================================================================
//function : VExport
//purpose  : Export the view to a vector graphic format (PS, EMF, PDF)
//==============================================================================

static int VExport(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  Handle(V3d_View) V3dView = ViewerTest::CurrentView();
  if (V3dView.IsNull())
    return 1;

  if (argc == 1)
  {
    std::cout << "Usage: " << argv[0] << " Filename [Format]\n";
    return 1;
  }

  Graphic3d_ExportFormat anExpFormat = Graphic3d_EF_PDF;
  TCollection_AsciiString aFormatStr;

  TCollection_AsciiString aFileName (argv[1]);
  Standard_Integer aLen = aFileName.Length();

  if (argc > 2)
  {
    aFormatStr = TCollection_AsciiString (argv[2]);
  }
  else if (aLen >= 4)
  {
    if (aFileName.Value (aLen - 2) == '.')
    {
      aFormatStr = aFileName.SubString (aLen - 1, aLen);
    }
    else if (aFileName.Value (aLen - 3) == '.')
    {
      aFormatStr = aFileName.SubString (aLen - 2, aLen);
    }
    else
    {
      std::cout << "Export format couln't be detected from filename '" << argv[1] << "'\n";
      return 1;
    }
  }
  else
  {
    std::cout << "Export format couln't be detected from filename '" << argv[1] << "'\n";
    return 1;
  }

  aFormatStr.UpperCase();
  if (aFormatStr == "PS")
    anExpFormat = Graphic3d_EF_PostScript;
  else if (aFormatStr == "EPS")
    anExpFormat = Graphic3d_EF_EnhPostScript;
  else if (aFormatStr == "TEX")
    anExpFormat = Graphic3d_EF_TEX;
  else if (aFormatStr == "PDF")
    anExpFormat = Graphic3d_EF_PDF;
  else if (aFormatStr == "SVG")
    anExpFormat = Graphic3d_EF_SVG;
  else if (aFormatStr == "PGF")
    anExpFormat = Graphic3d_EF_PGF;
  else if (aFormatStr == "EMF")
    anExpFormat = Graphic3d_EF_EMF;
  else
  {
    std::cout << "Invalid export format '" << aFormatStr << "'\n";
    return 1;
  }

  if (!V3dView->View()->Export (argv[1], anExpFormat))
  {
    std::cout << "Export failed!\n";
    return 1;
  }
  return 0;
}

//==============================================================================
//function : VColorScale
//purpose  : representation color scale
//==============================================================================
#include <V3d_ColorScale.hxx>

static int VColorScale (Draw_Interpretor& di, Standard_Integer argc, const char ** argv)
{
  if ( argc != 1 && argc != 4 && argc != 5 && argc != 6 && argc != 8 )
  {
    di << "Usage : " << argv[0] << " [RangeMin = 0 RangeMax = 100 Intervals = 10 HeightFont = 16 Position = Right X = 0 Y = 0]  " << "\n";
    return 1;
  }

  Handle(AIS_InteractiveContext) aContext = ViewerTest::GetAISContext();
  if(aContext.IsNull()) {
    di << argv[0] << " ERROR : use 'vinit' command before " << "\n";
    return -1;
  }

  Standard_Real minRange = 0. , maxRange = 100. ;

  Standard_Integer numIntervals = 10 ;
  Standard_Integer textHeight = 16;
  Aspect_TypeOfColorScalePosition position = Aspect_TOCSP_RIGHT;
  Standard_Real X = 0., Y = 0. ;

  if ( argc < 9 )
  {
     if( argc > 3 )
     {
       minRange = atof( argv[1] );
       maxRange = atof( argv[2] );
       numIntervals = atoi( argv[3] );
     }
     if ( argc > 4 )
       textHeight = atoi( argv[4] );
     if ( argc > 5 )
       position = (Aspect_TypeOfColorScalePosition)atoi( argv[5] );
     if ( argc > 7 )
     {
       X = atof( argv[6] );
       Y = atof( argv[7] );
     }
  }
  Handle(V3d_View) curView = ViewerTest::CurrentView( );
  if ( curView.IsNull( ) )
    return 1;
  Handle(Aspect_ColorScale) aCSV = curView->ColorScale( );
  Handle(V3d_ColorScale) aCS = ( Handle( V3d_ColorScale )::DownCast( aCSV ) );
  if( ! aCS.IsNull( ) )
  {
    aCS->SetPosition( X , Y );
    aCS->SetHeight( 0.95) ;
    aCS->SetTextHeight( (Standard_Integer) textHeight );
    aCS->SetRange( minRange , maxRange );
    aCS->SetNumberOfIntervals( numIntervals );
    aCS->SetLabelPosition( position );
    if( !curView->ColorScaleIsDisplayed() )
      curView->ColorScaleDisplay( );
  }
  return 0;
}

//==============================================================================
//function : VGraduatedTrihedron
//purpose  : Displays a graduated trihedron
//==============================================================================

static void AddMultibyteString (TCollection_ExtendedString &name, const char *arg)
{
  const char *str = arg;
  while (*str)
  {
    unsigned short c1 = *str++;
    unsigned short c2 = *str++;
    if (!c1 || !c2) break;
    name += (Standard_ExtCharacter)((c1 << 8) | c2);
  }
}

static int VGraduatedTrihedron(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  // Check arguments
  if (argc != 2 && argc < 5)
  {
    di<<"Error: "<<argv[0]<<" - invalid number of arguments\n";
    di<<"Usage: type help "<<argv[0]<<"\n";
    return 1; //TCL_ERROR
  }

  Handle(V3d_View) aV3dView = ViewerTest::CurrentView();

  // Create 3D view if it doesn't exist
  if ( aV3dView.IsNull() )
  {
    ViewerTest::ViewerInit(); 
    aV3dView = ViewerTest::CurrentView();
    if( aV3dView.IsNull() )
    {
      di << "Error: Cannot create a 3D view\n";
      return 1; //TCL_ERROR
    }
  }

  // Erase (==0) or display (!=0)
  const int display = atoi(argv[1]);

  if (display)
  {
    // Text font
    TCollection_AsciiString font;
    if (argc < 6)
      font.AssignCat("Courier");
    else
      font.AssignCat(argv[5]);

    // Text is multibyte
    const Standard_Boolean isMultibyte = (argc < 7)? Standard_False : (atoi(argv[6]) != 0);

    // Set axis names
    TCollection_ExtendedString xname, yname, zname;
    if (argc >= 5)
    {
      if (isMultibyte)
      {
        AddMultibyteString(xname, argv[2]);
        AddMultibyteString(yname, argv[3]);
        AddMultibyteString(zname, argv[4]);
      }
      else
      {
        xname += argv[2];
        yname += argv[3];
        zname += argv[4];
      }
    }
    else
    {
      xname += "X (mm)";
      yname += "Y (mm)";
      zname += "Z (mm)";
    }

    aV3dView->GraduatedTrihedronDisplay(xname, yname, zname,
                                        Standard_True/*xdrawname*/, Standard_True/*ydrawname*/, Standard_True/*zdrawname*/,
                                        Standard_True/*xdrawvalues*/, Standard_True/*ydrawvalues*/, Standard_True/*zdrawvalues*/,
                                        Standard_True/*drawgrid*/,
                                        Standard_True/*drawaxes*/,
                                        5/*nbx*/, 5/*nby*/, 5/*nbz*/,
                                        10/*xoffset*/, 10/*yoffset*/, 10/*zoffset*/,
                                        30/*xaxisoffset*/, 30/*yaxisoffset*/, 30/*zaxisoffset*/,
                                        Standard_True/*xdrawtickmarks*/, Standard_True/*ydrawtickmarks*/, Standard_True/*zdrawtickmarks*/,
                                        10/*xtickmarklength*/, 10/*ytickmarklength*/, 10/*ztickmarklength*/,
                                        Quantity_NOC_WHITE/*gridcolor*/,
                                        Quantity_NOC_RED/*xnamecolor*/,Quantity_NOC_GREEN/*ynamecolor*/,Quantity_NOC_BLUE1/*znamecolor*/,
                                        Quantity_NOC_RED/*xcolor*/,Quantity_NOC_GREEN/*ycolor*/,Quantity_NOC_BLUE1/*zcolor*/,font);
  }
  else
    aV3dView->GraduatedTrihedronErase();

  ViewerTest::GetAISContext()->UpdateCurrentViewer();
  aV3dView->Redraw();

  return 0;
}

//==============================================================================
//function : VPrintView
//purpose  : Test printing algorithm, print the view to image file with given
//           width and height. Printing implemented only for WNT.
//==============================================================================
static int VPrintView (Draw_Interpretor& di, Standard_Integer argc, 
                       const char** argv)
{
#ifndef WNT
  di << "Printing implemented only for wnt!\n";
  return 1;
#else

  Handle(AIS_InteractiveContext) aContextAIS = NULL;
  Handle(V3d_View) aView = NULL;
  aContextAIS = ViewerTest::GetAISContext();
  if (!aContextAIS.IsNull())
  {
    const Handle(V3d_Viewer)& Vwr = aContextAIS->CurrentViewer();
    Vwr->InitActiveViews();
    if(Vwr->MoreActiveViews())
      aView = Vwr->ActiveView();
  }

  // check for errors
  if (aView.IsNull())
  {
    di << "Call vinit before!\n";
    return 1;
  }
  else if (argc < 4)
  {
    di << "Use: " << argv[0];
    di << " width height filename [print algo=0]\n";
    di << "width, height of the intermediate buffer for operation\n";
    di << "algo : {0|1}\n";
    di << "        0 - stretch algorithm\n";
    di << "        1 - tile algorithm\n";
    di << "test printing algorithms into an intermediate buffer\n";
    di << "with saving output to an image file\n";
    return 1;
  }

  // get the input params
  Standard_Integer aWidth  = atoi (argv[1]);
  Standard_Integer aHeight = atoi (argv[2]);
  Standard_Integer aMode   = 0;
  TCollection_AsciiString aFileName = TCollection_AsciiString (argv[3]);
  if (argc==5)
    aMode = atoi (argv[4]);

  // check the input parameters
  if (aWidth <= 0 || aHeight <= 0)
  {
    di << "Width and height must be positive values!\n";
    return 1;
  }
  if (aMode != 0 && aMode != 1)
    aMode = 0;

  // define compatible bitmap
  HDC anDC = CreateCompatibleDC(0);
  BITMAPINFO aBitmapData;
  memset (&aBitmapData, 0, sizeof (BITMAPINFOHEADER));
  aBitmapData.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
  aBitmapData.bmiHeader.biWidth         = aWidth ;
  aBitmapData.bmiHeader.biHeight        = aHeight;
  aBitmapData.bmiHeader.biPlanes        = 1;
  aBitmapData.bmiHeader.biBitCount      = 24;
  aBitmapData.bmiHeader.biXPelsPerMeter = 0;
  aBitmapData.bmiHeader.biYPelsPerMeter = 0;
  aBitmapData.bmiHeader.biClrUsed       = 0;
  aBitmapData.bmiHeader.biClrImportant  = 0;
  aBitmapData.bmiHeader.biCompression   = BI_RGB;
  aBitmapData.bmiHeader.biSizeImage     = 0;

  // Create Device Independent Bitmap
  void* aBitsOut = NULL;
  HBITMAP aMemoryBitmap = CreateDIBSection (anDC, &aBitmapData, DIB_RGB_COLORS,
                                            &aBitsOut, NULL, 0);
  HGDIOBJ anOldBitmap   = SelectObject(anDC, aMemoryBitmap);

  Standard_Boolean isSaved = Standard_False, isPrinted = Standard_False;
  if (aBitsOut != NULL)
  {    
    if (aMode == 0)
      isPrinted = aView->Print(anDC,1,1,0,Aspect_PA_STRETCH);
    else
      isPrinted = aView->Print(anDC,1,1,0,Aspect_PA_TILE);

    // succesfully printed into an intermediate buffer
    if (isPrinted)
    {
      Image_PixMap aWrapper;
      aWrapper.InitWrapper (Image_PixMap::ImgBGR, (Standard_Byte* )aBitsOut, aWidth, aHeight, aWidth * 3 + aWidth % 4);
      aWrapper.SetTopDown (false);

      Image_AlienPixMap anImageBitmap;
      anImageBitmap.InitCopy (aWrapper);
      isSaved = anImageBitmap.Save (aFileName);
    }
    else
    {
      di << "Print operation failed due to printing errors or\n";
      di << "insufficient memory available\n";
      di << "Please, try to use smaller dimensions for this test\n";
      di << "command, as it allocates intermediate buffer for storing\n";
      di << "the result\n";
    }
  }
  else
  {
    di << "Can't allocate memory for intermediate buffer\n";
    di << "Please use smaller dimensions\n";
  }

  if (aMemoryBitmap)
  {
    SelectObject (anDC, anOldBitmap);
    DeleteObject (aMemoryBitmap);
    DeleteDC(anDC);
  }

  if (!isSaved)
  {
    di << "Save to file operation failed. This operation may fail\n";
    di << "if you don't have enough available memory, then you can\n";
    di << "use smaller dimensions for the output file\n";
    return 1;
  }

  return 0;

#endif
}

//==============================================================================
//function : VZLayer
//purpose  : Test z layer operations for v3d viewer
//==============================================================================
static int VZLayer (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  Handle(AIS_InteractiveContext) aContextAIS = ViewerTest::GetAISContext ();
  if (aContextAIS.IsNull())
  {
    di << "Call vinit before!\n";
    return 1;
  }
  else if (argc < 2)
  {
    di << "Use: vzlayer " << argv[0];
    di << " add/del/get [id]\n";
    di << " add - add new z layer to viewer and print its id\n";
    di << " del - del z layer by its id\n";
    di << " get - print sequence of z layers in increasing order of their overlay level\n";
    di << "id - the layer identificator value defined when removing z layer\n";
    return 1;
  }

  const Handle(V3d_Viewer)& aViewer = aContextAIS->CurrentViewer();
  if (aViewer.IsNull())
  {
    di << "No active viewer!\n";
    return 1;
  }

  // perform operation
  TCollection_AsciiString anOp = TCollection_AsciiString (argv[1]);
  if (anOp == "add")
  {
    Standard_Integer aNewId;
    if (!aViewer->AddZLayer (aNewId))
    {
      di << "Impossible to add new z layer!\n";
      return 1;
    }

    di << "New z layer added with index: " << aNewId << "\n";
  }
  else if (anOp == "del")
  {
    if (argc < 3)
    {
      di << "Please also provide as argument id of z layer to remove\n";
      return 1;
    }

    Standard_Integer aDelId = atoi (argv[2]);
    if (!aViewer->RemoveZLayer (aDelId))
    {
      di << "Impossible to remove the z layer or invalid id!\n";
      return 1;
    }

    di << "Z layer " << aDelId << " has been removed\n";
  }
  else if (anOp == "get")
  {
    TColStd_SequenceOfInteger anIds;
    aViewer->GetAllZLayers (anIds);
    for (Standard_Integer aSeqIdx = 1; aSeqIdx <= anIds.Length(); aSeqIdx++)
    {
      di << anIds.Value (aSeqIdx) << " ";
    }

    di << "\n";
  }
  else
  {
    di << "Invalid operation, please use { add / del / get }\n";
    return 1;
  }

  return 0;
}

DEFINE_STANDARD_HANDLE(V3d_TextItem, Visual3d_LayerItem)

// this class provides a presentation of text item in v3d view under-/overlayer
class V3d_TextItem : public Visual3d_LayerItem
{
public:

  // CASCADE RTTI
  DEFINE_STANDARD_RTTI(V3d_TextItem)

  // constructor
  Standard_EXPORT V3d_TextItem(const TCollection_AsciiString& theText,
                               const Standard_Real theX1,
                               const Standard_Real theY1,
                               const Standard_Real theHeight,
                               const TCollection_AsciiString& theFontName,
                               const Quantity_Color& theColor,
                               const Quantity_Color& theSubtitleColor,
                               const Aspect_TypeOfDisplayText& theTypeOfDisplay,
                               const Handle(Visual3d_Layer)& theLayer);

  // redraw method
  Standard_EXPORT void RedrawLayerPrs();

private:

  Standard_Real            myX1;
  Standard_Real            myY1;
  Standard_Real            myHeight;
  TCollection_AsciiString  myText;
  TCollection_AsciiString  myFontName;
  Quantity_Color           myColor;
  Quantity_Color           mySubtitleColor;
  Aspect_TypeOfDisplayText myType;
  Handle(Visual3d_Layer)   myLayer;

};

IMPLEMENT_STANDARD_HANDLE(V3d_TextItem, Visual3d_LayerItem)
IMPLEMENT_STANDARD_RTTIEXT(V3d_TextItem, Visual3d_LayerItem)

// create and add to display the text item
V3d_TextItem::V3d_TextItem (const TCollection_AsciiString& theText,
                            const Standard_Real theX1,
                            const Standard_Real theY1,
                            const Standard_Real theHeight,
                            const TCollection_AsciiString& theFontName,
                            const Quantity_Color& theColor,
                            const Quantity_Color& theSubtitleColor,
                            const Aspect_TypeOfDisplayText& theTypeOfDisplay,
                            const Handle(Visual3d_Layer)& theLayer)
 : myX1 (theX1), myY1 (theY1),
   myHeight (theHeight),
   myText (theText),
   myFontName (theFontName),
   myColor (theColor),
   mySubtitleColor (theSubtitleColor),
   myType (theTypeOfDisplay),
   myLayer (theLayer)
{
  if (!myLayer.IsNull ())
    myLayer->AddLayerItem (this);
}

// render item
void V3d_TextItem::RedrawLayerPrs ()
{ 
  if (myLayer.IsNull ())
    return;

  myLayer->SetColor (myColor);
  myLayer->SetTextAttributes (myFontName.ToCString (), myType, mySubtitleColor);
  myLayer->DrawText (myText.ToCString (), myX1, myY1, myHeight);
}

DEFINE_STANDARD_HANDLE(V3d_LineItem, Visual3d_LayerItem)

// The Visual3d_LayerItem line item for "vlayerline" command
// it provides a presentation of line with user-defined 
// linewidth, linetype and transparency.
class V3d_LineItem : public Visual3d_LayerItem 
{
public:
  // CASCADE RTTI
  DEFINE_STANDARD_RTTI(V3d_LineItem) 
  
  // constructor
  Standard_EXPORT V3d_LineItem(Standard_Real X1, Standard_Real Y1,
                               Standard_Real X2, Standard_Real Y2,
                               V3d_LayerMgrPointer theLayerMgr,
                               Aspect_TypeOfLine theType = Aspect_TOL_SOLID,
                               Standard_Real theWidth    = 0.5,
                               Standard_Real theTransp   = 1.0);

  // redraw method
  Standard_EXPORT   void RedrawLayerPrs();

private:

  Standard_Real       myX1, myY1, myX2, myY2;
  Standard_Real       myWidth;
  Standard_Real       myTransparency;
  Aspect_TypeOfLine   myType;
  V3d_LayerMgrPointer myLayerMgr;
};

IMPLEMENT_STANDARD_HANDLE(V3d_LineItem, Visual3d_LayerItem)
IMPLEMENT_STANDARD_RTTIEXT(V3d_LineItem, Visual3d_LayerItem)

// default constructor for line item
V3d_LineItem::V3d_LineItem(Standard_Real X1, Standard_Real Y1, 
                           Standard_Real X2, Standard_Real Y2,
                           V3d_LayerMgrPointer theLayerMgr,
                           Aspect_TypeOfLine theType,
                           Standard_Real theWidth,
                           Standard_Real theTransp) :
  myX1(X1), myY1(Y1), myX2(X2), myY2(Y2),
  myWidth(theWidth), myTransparency(theTransp),
  myType(theType), myLayerMgr(theLayerMgr)
{
  if (myLayerMgr && !myLayerMgr->Overlay().IsNull())
    myLayerMgr->Overlay()->AddLayerItem (this);
}

// render line
void V3d_LineItem::RedrawLayerPrs ()
{
  Handle (Visual3d_Layer) aOverlay;
 
  if (myLayerMgr)
    aOverlay = myLayerMgr->Overlay();

  if (!aOverlay.IsNull())
  {
    Quantity_Color aColor(1.0, 0, 0, Quantity_TOC_RGB);
    aOverlay->SetColor(aColor);
    aOverlay->SetTransparency((Standard_ShortReal)myTransparency);
    aOverlay->SetLineAttributes((Aspect_TypeOfLine)myType, myWidth);
    aOverlay->BeginPolyline();
    aOverlay->AddVertex(myX1, myY1);
    aOverlay->AddVertex(myX2, myY2);
    aOverlay->ClosePrimitive();
  }
}

//=============================================================================
//function : VLayerLine
//purpose  : Draws line in the v3d view layer with given attributes: linetype,
//         : linewidth, transparency coefficient
//============================================================================
static int VLayerLine(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  // get the active view
  Handle(V3d_View) aView = ViewerTest::CurrentView();
  if (aView.IsNull())
  {
    di << "Call vinit before!\n";
    return 1;
  }
  else if (argc < 5)
  {
    di << "Use: " << argv[0];
    di << " x1 y1 x2 y2 [linewidth = 0.5] [linetype = 0] [transparency = 1]\n";
    di << " linetype : { 0 | 1 | 2 | 3 } \n";
    di << "              0 - solid  \n";
    di << "              1 - dashed \n";
    di << "              2 - dot    \n";
    di << "              3 - dashdot\n";
    di << " transparency : { 0.0 - 1.0 } \n";
    di << "                  0.0 - transparent\n";
    di << "                  1.0 - visible    \n";
    return 1;
  }

  // get the input params
  Standard_Real X1 = atof(argv[1]);
  Standard_Real Y1 = atof(argv[2]);
  Standard_Real X2 = atof(argv[3]);
  Standard_Real Y2 = atof(argv[4]);

  Standard_Real    aWidth = 0.5;
  Standard_Integer aType  = 0;
  Standard_Real    aTransparency = 1.0;

  // has width
  if (argc > 5)
    aWidth = atof(argv[5]);

  // has type
  if (argc > 6)
     aType = (Standard_Integer) atoi(argv[6]);

  // has transparency
  if (argc > 7)
  {
    aTransparency = atof(argv[7]);
    if (aTransparency < 0 || aTransparency > 1.0) 
      aTransparency = 1.0;
  }

  // select appropriate line type
  Aspect_TypeOfLine aLineType;
  switch (aType)
  {
    case 1:
      aLineType = Aspect_TOL_DASH;
    break;

    case 2:
      aLineType = Aspect_TOL_DOT;
    break;

    case 3:
      aLineType = Aspect_TOL_DOTDASH;
    break;

    default:
      aLineType = Aspect_TOL_SOLID;
  }

  // replace layer manager
  Handle(V3d_LayerMgr) aMgr = new V3d_LayerMgr(aView);
  aView->SetLayerMgr(aMgr);

  // add line item
  Handle (V3d_LineItem) anItem = new V3d_LineItem(X1, Y1, X2, Y2, 
                                                  aMgr.operator->(),
                                                  aLineType, aWidth, 
                                                  aTransparency);

  // update view
  aView->MustBeResized();
  aView->Redraw();

  return 0;
}

//=======================================================================
//function : VOverlayText
//purpose  : Test text displaying in view overlay
//=======================================================================
static int VOverlayText (Draw_Interpretor& di, Standard_Integer argc, const char**argv)
{
  // get the active view
  Handle(V3d_View) aView = ViewerTest::CurrentView();
  if (aView.IsNull())
  {
    di << "No active view. Please call vinit.\n";
    return 1;
  }
  else if (argc < 4 || argc > 13)
  {
    di << "Use: " << argv[0];
    di << " text x y [height] [font_name] [text_color: R G B] [displayType]\n";
    di << "[background_color: R G B]\n";
    di << "  height - pixel height of the text (default=10.0)\n";
    di << "  font_name - name of font (default=courier)\n";
    di << "  text_color - R G B values of text color (default=255.0 255.0 255.0)\n";
    di << "  display_type = {normal/subtitle/decal/blend}, (default=normal)\n";
    di << "  background_color- R G B values used for subtitle and decal text\n";
    di << "(default=255.0 255.0 255.0)\n";
    return 1;
  }
  
  TCollection_AsciiString aText (argv[1]);
  Standard_Real aPosX = atof(argv[2]);
  Standard_Real aPosY = atof(argv[3]);
  Standard_Real aHeight = (argc >= 5) ? atof (argv[4]) : 10.0;

  // font name
  TCollection_AsciiString aFontName = "Courier";
  if (argc >= 6)
    aFontName = TCollection_AsciiString (argv[5]);

  // text colors
  Quantity_Parameter aColorRed   = 1.0;
  Quantity_Parameter aColorGreen = 1.0;
  Quantity_Parameter aColorBlue  = 1.0;
  if (argc >= 9)
  {
    aColorRed   = atof (argv[6])/255.;
    aColorGreen = atof (argv[7])/255.;
    aColorBlue  = atof (argv[8])/255.;
  }

  // display type
  TCollection_AsciiString aDispStr;
  if (argc >= 10)
    aDispStr = TCollection_AsciiString (argv[9]);

  Aspect_TypeOfDisplayText aTextType = Aspect_TODT_NORMAL;
  if (aDispStr.IsEqual ("subtitle"))
    aTextType = Aspect_TODT_SUBTITLE;
  else if (aDispStr.IsEqual ("decal"))
    aTextType = Aspect_TODT_DEKALE;
  else if (aDispStr.IsEqual ("blend"))
    aTextType = Aspect_TODT_BLEND;

  // subtitle color
  Quantity_Parameter aSubRed   = 1.0;
  Quantity_Parameter aSubGreen = 1.0;
  Quantity_Parameter aSubBlue  = 1.0;
  if (argc == 13)
  {
    aSubRed   = atof (argv[10])/255.;
    aSubGreen = atof (argv[11])/255.;
    aSubBlue  = atof (argv[12])/255.;
  }

  // check fo current overlay
  Handle(Visual3d_Layer) anOverlay = aView->Viewer()->Viewer()->OverLayer ();
  if (anOverlay.IsNull ())
  {
    Handle(V3d_LayerMgr) aMgr = new V3d_LayerMgr (aView);
    anOverlay = aMgr->Overlay ();
    aView->SetLayerMgr (aMgr);
  }

  Quantity_Color aTextColor (aColorRed, aColorGreen, 
    aColorBlue, Quantity_TOC_RGB);
  Quantity_Color aSubtColor (aSubRed, aSubGreen, 
    aSubBlue, Quantity_TOC_RGB);

  // add text item
  Handle(V3d_TextItem) anItem = new V3d_TextItem (aText, aPosX, aPosY,
    aHeight, aFontName, aTextColor, aSubtColor, aTextType, anOverlay);

  // update view
  aView->MustBeResized();
  aView->Redraw();

  return 0;
}

//==============================================================================
//function : VGrid
//purpose  :
//==============================================================================

static int VGrid (Draw_Interpretor& theDI,
                  Standard_Integer  theArgNb,
                  const char**      theArgVec)
{
  // get the active view
  Handle(V3d_View)   aView   = ViewerTest::CurrentView();
  Handle(V3d_Viewer) aViewer = ViewerTest::GetViewerFromContext();
  if (aView.IsNull() || aViewer.IsNull())
  {
    std::cerr << "No active view. Please call vinit.\n";
    return 1;
  }

  Aspect_GridType     aType = aViewer->GridType();
  Aspect_GridDrawMode aMode = aViewer->GridDrawMode();

  Standard_Integer anIter = 1;
  for (; anIter < theArgNb; ++anIter)
  {
    const char* aValue = theArgVec[anIter];
    if (*aValue == 'r')
    {
      aType = Aspect_GT_Rectangular;
    }
    else if (*aValue == 'c')
    {
      aType = Aspect_GT_Circular;
    }
    else if (*aValue == 'l')
    {
      aMode = Aspect_GDM_Lines;
    }
    else if (*aValue == 'p')
    {
      aMode = Aspect_GDM_Points;
    }
    else if (strcmp (aValue, "off" ) == 0)
    {
      aViewer->DeactivateGrid();
      return 0;
    }
    else
    {
      break;
    }
  }

  Standard_Integer aTail = (theArgNb - anIter);
  if (aTail == 0)
  {
    aViewer->ActivateGrid (aType, aMode);
    return 0;
  }
  else if (aTail != 2 && aTail != 5)
  {
    std::cerr << "Incorrect arguments number! Usage:\n"
              << "vgrid [off] [Mode={r|c}] [Type={l|p}] [OriginX OriginY [StepX/StepRadius StepY/DivNb RotAngle]]\n";
    return 1;
  }

  Quantity_Length anOriginX, anOriginY;
  Quantity_PlaneAngle aRotAngle;
  if (aType == Aspect_GT_Rectangular)
  {
    Quantity_Length aRStepX, aRStepY;
    aViewer->RectangularGridValues (anOriginX, anOriginY, aRStepX, aRStepY, aRotAngle);

    anOriginX = atof (theArgVec[anIter++]);
    anOriginY = atof (theArgVec[anIter++]);
    if (aTail == 5)
    {
      aRStepX   = atof (theArgVec[anIter++]);
      aRStepY   = atof (theArgVec[anIter++]);
      aRotAngle = atof (theArgVec[anIter++]);
    }
    aViewer->SetRectangularGridValues (anOriginX, anOriginY, aRStepX, aRStepY, aRotAngle);
    aViewer->ActivateGrid (aType, aMode);
  }
  else if (aType == Aspect_GT_Circular)
  {
    Quantity_Length aRadiusStep;
    Standard_Integer aDivisionNumber;
    aViewer->CircularGridValues (anOriginX, anOriginY, aRadiusStep, aDivisionNumber, aRotAngle);

    anOriginX = atof (theArgVec[anIter++]);
    anOriginY = atof (theArgVec[anIter++]);
    if (aTail == 5)
    {
      aRadiusStep     = atof (theArgVec[anIter++]);
      aDivisionNumber = atoi (theArgVec[anIter++]);
      aRotAngle       = atof (theArgVec[anIter++]);
    }

    aViewer->SetCircularGridValues (anOriginX, anOriginY, aRadiusStep, aDivisionNumber, aRotAngle);
    aViewer->ActivateGrid (aType, aMode);
  }

  return 0;
}

//==============================================================================
//function : VFps
//purpose  :
//==============================================================================

static int VFps (Draw_Interpretor& theDI,
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

  Standard_Integer aFramesNb = (theArgNb > 1) ? atoi(theArgVec[1]) : 100;
  if (aFramesNb <= 0)
  {
    std::cerr << "Incorrect arguments!\n";
    return 1;
  }

  // the time is meaningless for first call
  // due to async OpenGl rendering
  aView->Redraw();

  // redraw view in loop to estimate average values
  OSD_Timer aTimer;
  aTimer.Start();
  for (Standard_Integer anInter = 0; anInter < aFramesNb; ++anInter)
  {
    aView->Redraw();
  }
  aTimer.Stop();
  Standard_Real aCpu;
  const Standard_Real aTime = aTimer.ElapsedTime();
  aTimer.OSD_Chronometer::Show (aCpu);

  const Standard_Real aFpsAver = Standard_Real(aFramesNb) / aTime;
  const Standard_Real aCpuAver = aCpu / Standard_Real(aFramesNb);

  // return statistics
  theDI << "FPS: " << aFpsAver << "\n"
        << "CPU: " << (1000.0 * aCpuAver) << " msec\n";

  return 0;
}


//==============================================================================
//function : VVbo
//purpose  :
//==============================================================================

static int VVbo (Draw_Interpretor& theDI,
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

  Handle(Graphic3d_GraphicDriver) aDriver =
         Handle(Graphic3d_GraphicDriver)::DownCast (aContextAIS->CurrentViewer()->Device()->GraphicDriver());
  if (aDriver.IsNull())
  {
    std::cerr << "Graphic driver not available.\n";
    return 1;
  }

  if (theArgNb < 2)
  {
    //theDI << "VBO: " << aDriver->ToUseVBO() << "\n";
    //return 0;
    std::cerr << "Wrong number of arguments.\n";
    return 1;
  }

  aDriver->EnableVBO (atoi(theArgVec[1]) != 0);
  return 0;
}

//==============================================================================
//function : VMemGpu
//purpose  :
//==============================================================================

static int VMemGpu (Draw_Interpretor& theDI,
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

  Handle(Graphic3d_GraphicDriver) aDriver =
         Handle(Graphic3d_GraphicDriver)::DownCast (aContextAIS->CurrentViewer()->Device()->GraphicDriver());
  if (aDriver.IsNull())
  {
    std::cerr << "Graphic driver not available.\n";
    return 1;
  }

  Standard_Size aFreeBytes = 0;
  TCollection_AsciiString anInfo;
  if (!aDriver->MemoryInfo (aFreeBytes, anInfo))
  {
    std::cerr << "Information not available.\n";
    return 1;
  }

  if (theArgNb > 1 && *theArgVec[1] == 'f')
  {
    theDI << Standard_Real (aFreeBytes);
  }
  else
  {
    theDI << anInfo;
  }

  return 0;
}

// ==============================================================================
// function : VReadPixel
// purpose  :
// ==============================================================================
static int VReadPixel (Draw_Interpretor& theDI,
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
  else if (theArgNb < 3)
  {
    std::cerr << "Usage : " << theArgVec[0] << " xPixel yPixel [{rgb|rgba|depth|hls|rgbf|rgbaf}=rgba] [name]\n";
    return 1;
  }

  Image_PixMap::ImgFormat aFormat     = Image_PixMap::IsBigEndianHost() ? Image_PixMap::ImgRGBA : Image_PixMap::ImgBGRA;
  Graphic3d_BufferType    aBufferType = Graphic3d_BT_RGBA;

  Standard_Integer aWidth, aHeight;
  aView->Window()->Size (aWidth, aHeight);
  const Standard_Integer anX = atoi (theArgVec[1]);
  const Standard_Integer anY = atoi (theArgVec[2]);
  if (anX < 0 || anX >= aWidth || anY < 0 || anY > aHeight)
  {
    std::cerr << "Pixel coordinates (" << anX << "; " << anY << ") are out of view (" << aWidth << " x " << aHeight << ")\n";
    return 1;
  }

  Standard_Boolean toShowName = Standard_False;
  Standard_Boolean toShowHls  = Standard_False;
  for (Standard_Integer anIter = 3; anIter < theArgNb; ++anIter)
  {
    TCollection_AsciiString aParam (theArgVec[anIter]);
    if (TCollection_AsciiString::ISSIMILAR      (aParam, TCollection_AsciiString ("rgb")))
    {
      aFormat     = Image_PixMap::IsBigEndianHost() ? Image_PixMap::ImgRGB : Image_PixMap::ImgBGR;
      aBufferType = Graphic3d_BT_RGB;
    }
    else if (TCollection_AsciiString::ISSIMILAR (aParam, TCollection_AsciiString ("hls")))
    {
      aFormat     = Image_PixMap::IsBigEndianHost() ? Image_PixMap::ImgRGB : Image_PixMap::ImgBGR;
      aBufferType = Graphic3d_BT_RGB;
      toShowHls   = Standard_True;
    }
    else if (TCollection_AsciiString::ISSIMILAR (aParam, TCollection_AsciiString ("rgbf")))
    {
      aFormat     = Image_PixMap::ImgRGBF;
      aBufferType = Graphic3d_BT_RGB;
    }
    else if (TCollection_AsciiString::ISSIMILAR (aParam, TCollection_AsciiString ("rgba")))
    {
      aFormat     = Image_PixMap::IsBigEndianHost() ? Image_PixMap::ImgRGBA : Image_PixMap::ImgBGRA;
      aBufferType = Graphic3d_BT_RGBA;
    }
    else if (TCollection_AsciiString::ISSIMILAR (aParam, TCollection_AsciiString ("rgbaf")))
    {
      aFormat     = Image_PixMap::ImgRGBAF;
      aBufferType = Graphic3d_BT_RGBA;
    }
    else if (TCollection_AsciiString::ISSIMILAR (aParam, TCollection_AsciiString ("depth")))
    {
      aFormat     = Image_PixMap::ImgGrayF;
      aBufferType = Graphic3d_BT_Depth;
    }
    else if (TCollection_AsciiString::ISSIMILAR (aParam, TCollection_AsciiString ("name")))
    {
      toShowName = Standard_True;
    }
  }

  Image_PixMap anImage;
  if (!anImage.InitTrash (aFormat, aWidth, aHeight))
  {
    std::cerr << "Image allocation failed\n";
    return 1;
  }
  else if (!aView->ToPixMap (anImage, aWidth, aHeight, aBufferType))
  {
    std::cerr << "Image dump failed\n";
    return 1;
  }

  Quantity_Parameter anAlpha;
  Quantity_Color aColor = anImage.PixelColor (anX, anY, anAlpha);
  if (toShowName)
  {
    if (aBufferType == Graphic3d_BT_RGBA)
    {
      theDI << Quantity_Color::StringName (aColor.Name()) << " " << anAlpha << "\n";
    }
    else
    {
      theDI << Quantity_Color::StringName (aColor.Name()) << "\n";
    }
  }
  else
  {
    switch (aBufferType)
    {
      default:
      case Graphic3d_BT_RGB:
      {
        if (toShowHls)
        {
          theDI << aColor.Hue() << " " << aColor.Light() << " " << aColor.Saturation() << "\n";
        }
        else
        {
          theDI << aColor.Red() << " " << aColor.Green() << " " << aColor.Blue() << "\n";
        }
        break;
      }
      case Graphic3d_BT_RGBA:
      {
        theDI << aColor.Red() << " " << aColor.Green() << " " << aColor.Blue() << " " << anAlpha << "\n";
        break;
      }
      case Graphic3d_BT_Depth:
      {
        theDI << aColor.Red() << "\n";
        break;
      }
    }
  }

  return 0;
}

//==============================================================================
//function : VDiffImage
//purpose  : The draw-command compares two images.
//==============================================================================

static int VDiffImage (Draw_Interpretor& theDI, Standard_Integer theArgNb, const char** theArgVec)
{
  if (theArgNb < 6)
  {
    theDI << "Not enough arguments.\n";
    return 1;
  }

  // image file names
  const char* anImgPathRef = theArgVec[1];
  const char* anImgPathNew = theArgVec[2];

  // get string tolerance and check its validity
  Standard_Real aTolColor = atof (theArgVec[3]);
  if (aTolColor < 0.0)
    aTolColor = 0.0;
  if (aTolColor > 1.0)
    aTolColor = 1.0;

  Standard_Boolean toBlackWhite     = (atoi (theArgVec[4]) == 1);
  Standard_Boolean isBorderFilterOn = (atoi (theArgVec[5]) == 1);

  // image file of difference
  const char* aDiffImagePath = (theArgNb >= 7) ? theArgVec[6] : NULL;

  // compare the images
  Image_Diff aComparer;
  if (!aComparer.Init (anImgPathRef, anImgPathNew, toBlackWhite))
  {
    return 1;
  }

  aComparer.SetColorTolerance (aTolColor);
  aComparer.SetBorderFilterOn (isBorderFilterOn);
  Standard_Integer aDiffColorsNb = aComparer.Compare();
  theDI << aDiffColorsNb << "\n";

  // save image of difference
  if (aDiffImagePath != NULL)
  {
    aComparer.SaveDiffImage (aDiffImagePath);
  }

  return 0;
}

//=======================================================================
//function : ViewerCommands
//purpose  :
//=======================================================================

void ViewerTest::ViewerCommands(Draw_Interpretor& theCommands)
{

  const char *group = "ZeViewer";
  theCommands.Add("vinit" ,
    "vinit            : vinit [leftPx topPx widthPx heightPx] : Create the Viewer window",
    __FILE__,VInit,group);
  theCommands.Add("vhelp" ,
    "vhelp            : display help on the viewer commands",
    __FILE__,VHelp,group);
  theCommands.Add("vtop" ,
    "vtop or <T>      : Top view" ,
    __FILE__,VTop,group);
  theCommands.Add("vbottom" ,
    "vbottom          : Bottom view" ,
    __FILE__,VBottom,group);
  theCommands.Add("vleft" ,
    "vleft            : Left view" ,
    __FILE__,VLeft,group);
  theCommands.Add("vright" ,
    "vright           : Right view" ,
    __FILE__,VRight,group);
  theCommands.Add("vaxo" ,
    " vaxo or <A>     : Axonometric view ",
    __FILE__,VAxo,group);
  theCommands.Add("vfront" ,
    "vfront           : Front view" ,
    __FILE__,VFront,group);
  theCommands.Add("vback" ,
    "vback            : Back view" ,
    __FILE__,VBack,group);
  theCommands.Add("vpick" ,
    "vpick           : vpick X Y Z [shape subshape] ( all variables as string )",
    VPick,group);
  theCommands.Add("vfit"    ,
    "vfit or <F>         : vfit",
    __FILE__,VFit,group);
  theCommands.Add("vzfit"    ,
    "vzfit",
    __FILE__,VZFit,group);
  theCommands.Add("vrepaint",
    "vrepaint        : vrepaint, force redraw",
    __FILE__,VRepaint,group);
  theCommands.Add("vclear",
    "vclear          : vclear",
    __FILE__,VClear,group);
  theCommands.Add("vsetbg",
    "vsetbg          : vsetbg imagefile [filltype] : Load image as background",
    __FILE__,VSetBg,group);
  theCommands.Add("vsetbgmode",
    "vsetbgmode      : vsetbgmode filltype : Change background image fill type",
    __FILE__,VSetBgMode,group);
  theCommands.Add("vsetgradientbg",
    "vsetgradientbg  : vsetgradientbg r1 g1 b1 r2 g2 b2 filltype : Mount gradient background",
    __FILE__,VSetGradientBg,group);
  theCommands.Add("vsetgrbgmode",
    "vsetgrbgmode    : vsetgrbgmode filltype : Change gradient background fill type",
    __FILE__,VSetGradientBgMode,group);
  theCommands.Add("vsetcolorbg",
    "vsetcolorbg     : vsetcolorbg r g b : Set background color",
    __FILE__,VSetColorBg,group);
  theCommands.Add("vscale",
    "vscale          : vscale X Y Z",
    __FILE__,VScale,group);
  theCommands.Add("vzbufftrihedron",
    "vzbufftrihedron [center|left_lower|left_upper|right_lower|right_upper"
    " textR=255 textG=255 textB=255 scale=0.1 wireframe|zbuffer]"
    " : Displays a V3d_ZBUFFER'ed or V3d_WIREFRAME'd trihedron",
    __FILE__,VTestZBuffTrihedron,group);
  theCommands.Add("vrotate",
    "vrotate         : vrotate AX AY AZ [X Y Z]",
    __FILE__,VRotate,group);
  theCommands.Add("vzoom",
    "vzoom           : vzoom coef",
    __FILE__,VZoom,group);
  theCommands.Add("vpan",
    "vpan            : vpan dx dy",
    __FILE__,VPan,group);
  theCommands.Add("vexport",
    "vexport         : vexport full_file_path {PS | EPS | TEX | PDF | SVG | PGF | EMF }"
    " : exports the view to a vector file of a given format"
    " : notice that EMF format requires patched gl2ps",
    __FILE__,VExport,group);
  theCommands.Add("vcolorscale",
    "vcolorscale     : vcolorscale [RangeMin = 0 RangeMax = 100 Intervals = 10 HeightFont = 16 Position = 2 X = 0 Y = 0]: draw color scale",
    __FILE__,VColorScale,group);
  theCommands.Add("vgraduatedtrihedron",
    "vgraduatedtrihedron : 1/0 (display/erase) [Xname Yname Zname [Font [isMultibyte]]]",
    __FILE__,VGraduatedTrihedron,group);
  theCommands.Add("vprintview" ,
    "vprintview : width height filename [algo=0] : Test print algorithm: algo = 0 - stretch, algo = 1 - tile",
    __FILE__,VPrintView,group);
  theCommands.Add("vzlayer",
    "vzlayer : add/del/get [id] : Z layer operations in v3d viewer: add new z layer, delete z layer, get z layer ids",
    __FILE__,VZLayer,group);
  theCommands.Add("voverlaytext",
    "voverlaytext : text x y [height] [font_name] [text_color: R G B] [display_type] [background_color: R G B]"
    " : height - pixel height of the text (default=10.0)"
    " : font_name - name of font (default=courier)"
    " : text_color - three values: RedColor GreenColor BlueColor (default = 255.0 255.0 255.0) "
    " : display_type = {normal/subtitle/decal/blend}, (default=normal) "
    " : background_color - three values: RedColor GreenColor BlueColor (default = 255.0 255.0 255.0), the parameter is defined for subtitle and decal display types ",
    __FILE__,VOverlayText,group);
  theCommands.Add("vlayerline",
    "vlayerline : vlayerline x1 y1 x2 y2 [linewidth=0.5] [linetype=0] [transparency=1.0]",
    __FILE__,VLayerLine,group);
  theCommands.Add ("vgrid",
    "vgrid [off] [Mode={r|c}] [Type={l|p}] [OriginX OriginY [StepX/StepRadius StepY/DivNb RotAngle]]"
    " : Mode - rectangular or circular"
    " : Type - lines or points",
    __FILE__, VGrid, group);
  theCommands.Add ("vfps",
    "vfps [framesNb=100] : estimate average frame rate for active view",
    __FILE__, VFps, group);
  theCommands.Add ("vvbo",
    "vvbo {0|1} : turn VBO usage On/Off; affects only newly displayed objects",
    __FILE__, VVbo, group);
  theCommands.Add ("vmemgpu",
    "vmemgpu [f]: print system-dependent GPU memory information if available;"
    " with f option returns free memory in bytes",
    __FILE__, VMemGpu, group);
  theCommands.Add ("vreadpixel",
    "vreadpixel xPixel yPixel [{rgb|rgba|depth|hls|rgbf|rgbaf}=rgba] [name]"
    " : Read pixel value for active view",
    __FILE__, VReadPixel, group);
  theCommands.Add("diffimage",
    "diffimage     : diffimage imageFile1 imageFile2 toleranceOfColor(0..1) blackWhite(1|0) borderFilter(1|0) [diffImageFile]",
    __FILE__, VDiffImage, group);
}
