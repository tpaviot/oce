// File:        Draw_Window.cxx
// Created:     Wed Jul 27 17:52:01 1994
// Author:      Remi LEQUETTE
//              <rle@bravox>
//
// Updated by DPF Fri Mar 21 18:40:58 1997
//              Added casting in void to compile
//              on AO1 int 32 bits -> pointer 64 bits ????
//
// Robert Boehne 30 May 2000 : Dec Osf

// include windows.h first to have all definitions available
#ifdef WNT
#include <windows.h>
#endif

#include <Standard_ErrorHandler.hxx>

#include <tcl.h>
#include <Draw_Interpretor.hxx>
#include <Draw_Appli.hxx>
#include <TCollection_AsciiString.hxx>
#include <Image_PixMap.hxx>

extern Draw_Interpretor theCommands;
Standard_IMPORT Standard_Boolean Draw_VirtualWindows;
static Tcl_Interp *interp;        /* Interpreter for this application. */

/*
 *----------------------------------------------------------------------
 *
 * Prompt --
 *
 *        Issue a prompt on standard output, or invoke a script
 *        to issue the prompt.
 *
 * Results:
 *        None.
 *
 * Side effects:
 *        A prompt gets output, and a Tcl script may be evaluated
 *        in interp.
 *
 *----------------------------------------------------------------------
 */

static void Prompt(Tcl_Interp *Interp, int partial)
{

  // MKV 29.03.05
#if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4))) && !defined(USE_NON_CONST)
    const char *promptCmd;
#else
    char *promptCmd;
#endif
    int code;
    Tcl_Channel  outChannel, errChannel;
    outChannel = Tcl_GetStdChannel(TCL_STDOUT);
    promptCmd = Tcl_GetVar(Interp,(char*)
        (partial ? "tcl_prompt2" : "tcl_prompt1"), TCL_GLOBAL_ONLY);

    if (promptCmd == NULL) {
defaultPrompt:
      if (!partial && outChannel) {
        Tcl_Write(outChannel, "% ", 2);
      }
    } else {
      code = Tcl_Eval(Interp, promptCmd);
      outChannel = Tcl_GetStdChannel(TCL_STDOUT);
      errChannel = Tcl_GetStdChannel(TCL_STDERR);
      if (code != TCL_OK) {
        if (errChannel) {
          Tcl_Write(errChannel, Tcl_GetStringResult(Interp), -1);
          Tcl_Write(errChannel, "\n", 1);
        }
        Tcl_AddErrorInfo(Interp,
                         "\n    (script that generates prompt)");
        goto defaultPrompt;
      }
    }
    if (outChannel) {
      Tcl_Flush(outChannel);
    }
}

#ifndef WNT

#ifdef HAVE_CONFIG_H
# include <oce-config.h>
#endif

#include <OSD_Timer.hxx>

#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#else
#include <sys/ioctl.h>
#endif

#include <fcntl.h>

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#include <Draw_Window.hxx>

#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif


#include <Draw_WindowBase.hxx>
#include <X11/XWDFile.h>

#include <stdio.h>
#include <tk.h>

/*
 * Global variables used by the main program:
 */

static Tk_Window mainWindow;    /* The main window for the application.  If
                                 * NULL then the application no longer
                                 * exists. */
char *tcl_RcFileName = NULL;    /* Name of a user-specific startup script
                                 * to source if the application is being run
                                 * interactively (e.g. "~/.wishrc").  Set
                                 * by Tcl_AppInit.  NULL means don't source
                                 * anything ever. */

static Tcl_DString command;     /* Used to assemble lines of terminal input
                                 * into Tcl commands. */
static Tcl_DString line;        /* Used to read the next line from the
                                 * terminal input. */
//static char errorExitCmd[] = "exit 1";

/*
 * Forward declarations for procedures defined later in this file:
 */

static void StdinProc (ClientData clientData, int mask);

static void Prompt (Tcl_Interp *Interp, int partial);

static Standard_Boolean tty;        /* Non-zero means standard input is a
                                 * terminal-like device.  Zero means it's
                                 * a file. */

static unsigned long thePixels[MAXCOLOR];


Display*         Draw_WindowDisplay = NULL;
Standard_Integer Draw_WindowScreen = 0;
Colormap         Draw_WindowColorMap;
Standard_Boolean Draw_BlackBackGround = Standard_True;
Standard_Boolean Draw_LowWindows = Standard_False;


// Initialization of static variables of Draw_Window
//======================================================
Draw_Window* Draw_Window::firstWindow = NULL;


//=======================================================================
//function : Draw_Window
//purpose  :
//=======================================================================
Draw_Window::Draw_Window() :
       base(*new Base_Window()),
       win(0),
       myBuffer(0),
       next(firstWindow),
       previous(NULL),
       myUseBuffer(Standard_False),
       withWindowManager(Standard_True)
{
  myMother = RootWindow(Draw_WindowDisplay,
                        Draw_WindowScreen);

  if (firstWindow) firstWindow->previous = this;
  firstWindow = this;
}

//=======================================================================
//function : Draw_Window
//purpose  :
//=======================================================================
Draw_Window::Draw_Window(Window mother) :
       base(*new Base_Window()),
       win(0),
       myBuffer(0),
       next(firstWindow),
       previous(NULL),
       myUseBuffer(Standard_False),
       withWindowManager(Standard_True)
{
  myMother = mother;

  if (firstWindow) firstWindow->previous = this;
  firstWindow = this;
}

//=======================================================================
//function : Draw_Window
//purpose  :
//=======================================================================
Draw_Window::Draw_Window (const char* title,
                          Standard_Integer X, Standard_Integer Y,
                          Standard_Integer DX, Standard_Integer DY) :
       base(*new Base_Window()),
       win(0),
       myBuffer(0),
       next(firstWindow),
       previous(NULL),
       myUseBuffer(Standard_False),
       withWindowManager(Standard_True)
{
  myMother = RootWindow(Draw_WindowDisplay,
                        Draw_WindowScreen);

  if (firstWindow) firstWindow->previous = this;
  firstWindow = this;
  Init(X,Y,DX,DY);
  SetTitle(title);
}

//=======================================================================
//function : Draw_Window
//purpose  :
//=======================================================================
Draw_Window::Draw_Window (const char* window ) :
       base(*new Base_Window()),
       win(0),
       myBuffer(0),
       next(firstWindow),
       previous(NULL),
       myUseBuffer(Standard_False),
       withWindowManager(Standard_True)
{
  sscanf(window,"%lx",&win);
  Standard_Integer X,Y,DX,DY;

  if (firstWindow) firstWindow->previous = this;
  firstWindow = this;
  GetPosition(X,Y);
  DX=HeightWin();
  DY=WidthWin();

  Init(X,Y,DX,DY);
}

//=======================================================================
//function : Draw_Window
//purpose  :
//=======================================================================
Draw_Window::Draw_Window (Window mother,
                          char* title,
                          Standard_Integer X, Standard_Integer Y,
                          Standard_Integer DX, Standard_Integer DY) :
       base(*new Base_Window()),
       win(0),
       myBuffer(0),
       next(firstWindow),
       previous(NULL),
       myUseBuffer(Standard_False),
       withWindowManager(Standard_True)
{
  myMother = mother;

  if (firstWindow) firstWindow->previous = this;
  firstWindow = this;
  Init(X,Y,DX,DY);
  SetTitle(title);
}

//=======================================================================
//function : ~Draw_Window
//purpose  :
//=======================================================================
Draw_Window::~Draw_Window()
{
  if (previous)
    previous->next = next;
  else
    firstWindow = next;
  if (next)
    next->previous = previous;

  if (myBuffer != 0)
  {
    XFreePixmap(Draw_WindowDisplay, myBuffer);
    myBuffer = 0;
  }
  // Liberation pointer on Base_Window
  delete &base;
}

//=======================================================================
//function : Init
//purpose  :
//=======================================================================
void Draw_Window::Init(Standard_Integer X, Standard_Integer Y,
                       Standard_Integer DX, Standard_Integer DY)
{
  unsigned long setmask;

  if (Draw_BlackBackGround)
  {
    base.xswa.background_pixel = BlackPixel(Draw_WindowDisplay,Draw_WindowScreen);
    base.xswa.border_pixel     = WhitePixel(Draw_WindowDisplay,Draw_WindowScreen);
  }
  else
  {
    base.xswa.background_pixel = WhitePixel(Draw_WindowDisplay,Draw_WindowScreen);
    base.xswa.border_pixel     = BlackPixel(Draw_WindowDisplay,Draw_WindowScreen);
  }
  base.xswa.colormap         = Draw_WindowColorMap;
  setmask               = CWBackPixel | CWBorderPixel ;

  XSizeHints myHints;
  myHints.flags = USPosition;
  myHints.x = (int) X;
  myHints.y = (int) Y;

  if (win == 0)
  {
    win = XCreateWindow(Draw_WindowDisplay,
                        myMother,
                        (int) X,(int) Y,
                        (unsigned int) DX,(unsigned int) DY,
                        5,
                        DefaultDepth(Draw_WindowDisplay,Draw_WindowScreen),
                        InputOutput,
                        DefaultVisual(Draw_WindowDisplay,Draw_WindowScreen),
                        setmask,&base.xswa);
    XSelectInput(Draw_WindowDisplay, win, ButtonPressMask|ExposureMask|
                                          StructureNotifyMask);

    // advise to the window manager to place it where I need
    XSetWMNormalHints(Draw_WindowDisplay,win,&myHints);

    if (Draw_VirtualWindows)
    {
      myUseBuffer = Standard_True;
      InitBuffer();
    }
  }

  base.gc = XCreateGC(Draw_WindowDisplay, win, 0, NULL);

  XSetPlaneMask(Draw_WindowDisplay,base.gc,AllPlanes);
  XSetForeground(Draw_WindowDisplay,
                 base.gc, WhitePixel(Draw_WindowDisplay,Draw_WindowScreen));
  XSetBackground(Draw_WindowDisplay,
                 base.gc, BlackPixel(Draw_WindowDisplay,Draw_WindowScreen));
  // save in case of window recovery

  base.xswa.backing_store = Always;
  XChangeWindowAttributes(Draw_WindowDisplay, win,
                          CWBackingStore, &base.xswa);

  XSetLineAttributes (Draw_WindowDisplay, base.gc,
                      0, LineSolid, CapButt, JoinMiter);
}

//=======================================================================
//function : InitBuffer
//purpose  :
//=======================================================================
void Draw_Window::InitBuffer()
{
  if (myUseBuffer) {
    if (myBuffer != 0) {
      XFreePixmap (Draw_WindowDisplay, myBuffer);
    }
    XWindowAttributes winAttr;
    XGetWindowAttributes (Draw_WindowDisplay, win, &winAttr);
    myBuffer = XCreatePixmap (Draw_WindowDisplay, win, winAttr.width, winAttr.height, winAttr.depth);
  }
  else if (myBuffer != 0)
  {
    XFreePixmap (Draw_WindowDisplay, myBuffer);
    myBuffer = 0;
  }
}

//=======================================================================
//function : StopWinManager
//purpose  :
//=======================================================================
void Draw_Window::StopWinManager()
{
//  XGCValues winGc;
  XWindowAttributes winAttr;
  XGetWindowAttributes (Draw_WindowDisplay, win, &winAttr);
  Destroy();

  XSizeHints myHints;
  myHints.flags = USPosition;
  myHints.x = (int) 30;
  myHints.y = (int) 100;

  base.xswa.override_redirect = 1;
  base.xswa.border_pixel = BlackPixel(Draw_WindowDisplay,
                                 Draw_WindowScreen);
  base.xswa.background_pixel = WhitePixel(Draw_WindowDisplay,
                               Draw_WindowScreen);

  withWindowManager = Standard_False;

  win = XCreateWindow(Draw_WindowDisplay, myMother,
                      winAttr.x, winAttr.y,
                      winAttr.width, winAttr.height,
                      2,
                      CopyFromParent, InputOutput, CopyFromParent,
                      CWBorderPixel|CWOverrideRedirect|CWBackPixel, &base.xswa);


  // adwise to the window manager to place it where I wish
  XSetWMNormalHints(Draw_WindowDisplay,win,&myHints);

  // all masks of the old window are reassigned to the new one.
  XSelectInput(Draw_WindowDisplay,win,winAttr.your_event_mask);
}

//=======================================================================
//function : SetPosition
//purpose  :
//=======================================================================
void Draw_Window::SetPosition(Standard_Integer NewXpos,
                              Standard_Integer NewYpos)
{
  Standard_Integer x,y;
  GetPosition(x, y);

  if ( (x != NewXpos) || (y != NewYpos) )
    XMoveWindow(Draw_WindowDisplay, win, NewXpos, NewYpos);
}

//=======================================================================
//function : SetDimension
//purpose  :
//=======================================================================
void Draw_Window::SetDimension(Standard_Integer NewDx,
                               Standard_Integer NewDy)
{
  if ( (NewDx != WidthWin() ) || (NewDy != HeightWin() ) )
    XResizeWindow(Draw_WindowDisplay, win, NewDx, NewDy);
}

//=======================================================================
//function : GetPosition
//purpose  :
//=======================================================================
void Draw_Window::GetPosition(Standard_Integer &PosX,
                              Standard_Integer &PosY)
{
  XWindowAttributes winAttr;
  XGetWindowAttributes(Draw_WindowDisplay, win, &winAttr);

  PosX = winAttr.x;
  PosY = winAttr.y;
}

//=======================================================================
//function : HeightWin
//purpose  :
//=======================================================================
Standard_Integer Draw_Window::HeightWin() const
{
  Standard_Integer DY;
  XWindowAttributes winAttr;
  XGetWindowAttributes(Draw_WindowDisplay, win, &winAttr);

  DY = winAttr.height;
  return DY;
}

//=======================================================================
//function : WidthWin
//purpose  :
//=======================================================================
Standard_Integer Draw_Window::WidthWin() const
{
  Standard_Integer DX;
  XWindowAttributes winAttr;
  XGetWindowAttributes(Draw_WindowDisplay, win, &winAttr);

  DX = winAttr.width;
  return DX;
}

//=======================================================================
//function : SetTitle
//purpose  :
//=======================================================================
void Draw_Window::SetTitle(const char* title)
{
  XStoreName(Draw_WindowDisplay, win, title);
}

//=======================================================================
//function : GetTitle
//purpose  :
//=======================================================================
char* Draw_Window::GetTitle()
{
  char* title;
  XFetchName(Draw_WindowDisplay, win, &title);
  return title;
}

//=======================================================================
//function : GetDrawable
//purpose  :
//=======================================================================
Drawable Draw_Window::GetDrawable() const
{
  return myUseBuffer ? myBuffer : win;
}

//=======================================================================
//function :DefineColor
//purpose  :
//=======================================================================
Standard_Boolean Draw_Window::DefineColor(const Standard_Integer i, const char* colorName)
{
  XColor color;

  if (!XParseColor(Draw_WindowDisplay,Draw_WindowColorMap,colorName,&color))
    return Standard_False;
  if (!XAllocColor(Draw_WindowDisplay,Draw_WindowColorMap,&color))
    return Standard_False;
  thePixels[i % MAXCOLOR] = color.pixel;
  return Standard_True;
}

//=======================================================================
//function : DisplayWindow
//purpose  :
//=======================================================================
void Draw_Window::DisplayWindow()
{
  if (Draw_VirtualWindows)
  {
    return;
  }
  else if (Draw_LowWindows)
  {
    // the window <win> will be displayed so that not to be hidden
    // by any other window (on top)
    XMapWindow(Draw_WindowDisplay, win);
    XLowerWindow(Draw_WindowDisplay, win);
  }
  else
  {
    XMapRaised(Draw_WindowDisplay, win);
  }
  XFlush(Draw_WindowDisplay);
}

//=======================================================================
//function : Hide
//purpose  :
//=======================================================================
void Draw_Window::Hide()
{
   XUnmapWindow(Draw_WindowDisplay, win);
}

//=======================================================================
//function : Destroy
//purpose  :
//=======================================================================
void Draw_Window::Destroy()
{
  XDestroyWindow(Draw_WindowDisplay, win);
  win = 0;
  if (myBuffer != 0)
  {
    XFreePixmap(Draw_WindowDisplay, myBuffer);
    myBuffer = 0;
  }
}

//=======================================================================
//function : Clear
//purpose  :
//=======================================================================
void Draw_Window::Clear()
{
  if (myUseBuffer)
  {
    // XClearArea only applicable for windows
    XGCValues currValues;
    XGetGCValues(Draw_WindowDisplay, base.gc, GCBackground | GCForeground, &currValues);
    XSetForeground(Draw_WindowDisplay, base.gc, currValues.background);
    XFillRectangle(Draw_WindowDisplay, myBuffer, base.gc, 0, 0, WidthWin(), HeightWin());
    XSetForeground(Draw_WindowDisplay, base.gc, currValues.foreground);
  }
  else
  {
    XClearArea(Draw_WindowDisplay, win, 0, 0, 0, 0, False);
  }
}

//=======================================================================
//function : Flush
//purpose  :
//=======================================================================
void Draw_Window::Flush()
{
  XFlush(Draw_WindowDisplay);
}

//=======================================================================
//function : DrawString
//purpose  :
//=======================================================================
void Draw_Window::DrawString(int X, int Y, char *text)
{
  XDrawString(Draw_WindowDisplay, GetDrawable(), base.gc, X, Y, text, strlen(text));
}

//=======================================================================
//function : DrawSegments
//purpose  :
//=======================================================================
void Draw_Window::DrawSegments(Segment *tab, int nbElem)
{
  XDrawSegments(Draw_WindowDisplay, GetDrawable(), base.gc, (XSegment*) tab, nbElem);
}

//=======================================================================
//function : Redraw
//purpose  :
//=======================================================================
void Draw_Window::Redraw()
{
  if (myUseBuffer) {
    XCopyArea (Draw_WindowDisplay,
               myBuffer, win, // source, destination Drawables
               base.gc,
               0, 0,  // source x, y
               WidthWin(), HeightWin(),
               0, 0); // destination x, y
  }
}

//=======================================================================
//function : SetColor
//purpose  :
//=======================================================================
void Draw_Window::SetColor(Standard_Integer color)
{
  XSetForeground(Draw_WindowDisplay, base.gc, thePixels[color]);
}

//=======================================================================
//function : SetMode
//purpose  :
//=======================================================================
void Draw_Window::SetMode( int mode)
{
  XSetFunction(Draw_WindowDisplay, base.gc, mode);
}

//=======================================================================
//function : Save
//purpose  :
//=======================================================================
Standard_Boolean Draw_Window::Save (const char* theFileName) const
{
  // make sure all draw operations done
  XSync (Draw_WindowDisplay, True);

  // the attributes
  XWindowAttributes winAttr;
  XGetWindowAttributes (Draw_WindowDisplay, win, &winAttr);

  if (!myUseBuffer)
  {
    // make sure that the whole window fit on display to prevent BadMatch error
    XWindowAttributes winAttrRoot;
    XGetWindowAttributes (Draw_WindowDisplay, XRootWindowOfScreen (winAttr.screen), &winAttrRoot);

    Window winChildDummy;
    int winLeft = 0;
    int winTop = 0;
    XTranslateCoordinates (Draw_WindowDisplay, win, XRootWindowOfScreen (winAttr.screen),
                           0, 0, &winLeft, &winTop, &winChildDummy);

    if (((winLeft + winAttr.width) > winAttrRoot.width)  || winLeft < winAttrRoot.x ||
        ((winTop + winAttr.height) > winAttrRoot.height) || winTop  < winAttrRoot.y)
    {
      std::cerr << "The window not fully visible! Can't create the snapshot.\n";
      return Standard_False;
    }
  }

  // find the image
  XImage* pximage = XGetImage (Draw_WindowDisplay, GetDrawable(),
                               0, 0, winAttr.width, winAttr.height,
                               AllPlanes, ZPixmap);
  if (pximage == NULL)
  {
    return Standard_False;
  }

  if (winAttr.visual->c_class == TrueColor)
  {
    Standard_Byte* aDataPtr = (Standard_Byte* )pximage->data;
    Handle(Image_PixMap) anImagePixMap = new Image_PixMap (aDataPtr,
                                                           pximage->width, pximage->height,
                                                           pximage->bytes_per_line,
                                                           pximage->bits_per_pixel,
                                                           Standard_True);
    // destroy the image
    XDestroyImage (pximage);

    // save the image
    return anImagePixMap->Dump (theFileName);
  }
  else
  {
    std::cerr << "Visual Type not supported!";
    // destroy the image
    XDestroyImage (pximage);
    return Standard_False;
  }
}


//=======================================================================
//function : ProcessEvent
//purpose  :
//=======================================================================

void ProcessEvent(Draw_Window& win, XEvent& xev)
{
  Standard_Integer X,Y,button,lenk;
  char c;
  KeySym keysym;
  XComposeStatus stat;
  char chainekey[10];


  switch (xev.type) {

  case Expose :
    win.WExpose();
    break;

  case ButtonPress :
    X = xev.xbutton.x;
    Y = xev.xbutton.y;
    button = xev.xbutton.button;
    win.WButtonPress(X,Y,button);
    break;

  case ButtonRelease :
    X = xev.xbutton.x;
    Y = xev.xbutton.y;
    button = xev.xbutton.button;
    win.WButtonRelease(X,Y,button);
    break;

  case KeyPress :
    lenk = XLookupString(&(xev.xkey),
                         chainekey,
                         10,
                         &keysym,
                         &stat);
    if (lenk==1)
      c = chainekey[0];
    else
      c = '\0';

    //WKeyPress(c,keysym);
    break;

  case MotionNotify :
    X = xev.xmotion.x;
    Y = xev.xmotion.y;
    win.WMotionNotify(X,Y);
    break;

  case ConfigureNotify :
    if (win.withWindowManager)
      win.WConfigureNotify(xev.xconfigure.x, xev.xconfigure.y,
                           xev.xconfigure.width,
                           xev.xconfigure.height);
    break;

  case UnmapNotify :

    win.WUnmapNotify();
    break;
  }
}

//=======================================================================
//function : WExpose
//purpose  :
//=======================================================================
void Draw_Window::WExpose()
{
}

//=======================================================================
//function : WButtonPress
//purpose  :
//=======================================================================
void Draw_Window::WButtonPress(const Standard_Integer,
                               const Standard_Integer,
                               const Standard_Integer&)
{
}

//=======================================================================
//function : WButtonRelease
//purpose  :
//=======================================================================
void Draw_Window::WButtonRelease(const Standard_Integer,
                                 const Standard_Integer,
                                 const Standard_Integer&)
{
}

/**************************
//=======================================================================
//function : WKeyPress
//purpose  :
//=======================================================================

void Draw_Window::WKeyPress(char, KeySym&)
{
}
***************************/

//=======================================================================
//function : WMotionNotify
//purpose  :
//=======================================================================
void Draw_Window::WMotionNotify(const Standard_Integer ,
                                const Standard_Integer )
{
}

//=======================================================================
//function : WConfigureNotify
//purpose  :
//=======================================================================

void Draw_Window::WConfigureNotify(const Standard_Integer,
                                   const Standard_Integer,
                                   const Standard_Integer,
                                   const Standard_Integer)
{
}

//=======================================================================
//function : Wait
//purpose  :
//=======================================================================

void Draw_Window::Wait (Standard_Boolean wait)
{
  Flush();
  if (!wait) {
        XSelectInput(Draw_WindowDisplay,win,
                     ButtonPressMask|ExposureMask | StructureNotifyMask |
                     PointerMotionMask);
  }
  else {
        XSelectInput(Draw_WindowDisplay,win,
                     ButtonPressMask|ExposureMask | StructureNotifyMask);
  }
}

//=======================================================================
//function : WUnmapNotify
//purpose  :
//=======================================================================

void Draw_Window::WUnmapNotify()
{
}


//======================================================
// funtion : ProcessEvents
// purpose : process pending X events
//======================================================

static void ProcessEvents(ClientData,int)
{
  // test for X Event

  while (XPending(Draw_WindowDisplay)) {

    XEvent xev;
    xev.type = 0;

    XNextEvent(Draw_WindowDisplay,&xev);

    /* search the window in the window list */
    Draw_Window* w = Draw_Window::firstWindow;
    Standard_Integer found=0;
    while (w) {
      if (xev.xany.window == w->win) {
        ProcessEvent(*w, xev);
        found=1;
        break;
      }
      w = w->next;
    }
    if (found==0) {
      Tk_HandleEvent(&xev);
    }
  }
}

//======================================================
// funtion :Run_Appli
// purpose :
//======================================================


static Standard_Boolean(*Interprete) (char*);

void Run_Appli(Standard_Boolean (*interprete) (char*))
{
  Tcl_Channel outChannel, inChannel ;
  Interprete = interprete;

#ifdef _TK

    /*
     * Commands will come from standard input, so set up an event
     * handler for standard input.  If the input device is aEvaluate the
     * .rc file, if one has been specified, set up an event handler
     * for standard input, and print a prompt if the input
     * device is a terminal.
     */
  inChannel = Tcl_GetStdChannel(TCL_STDIN);
  if (inChannel) {
            Tcl_CreateChannelHandler(inChannel, TCL_READABLE, StdinProc,
                    (ClientData) inChannel);
        }

  // Create a handler for the draw display

  // Adding of the casting into void* to be able to compile on AO1
  // ConnectionNumber(Draw_WindowDisplay) is an int 32 bits
  //                    (void*) is a pointer      64 bits ???????

#if TCL_MAJOR_VERSION  < 8
    Tk_CreateFileHandler((void*) ConnectionNumber(Draw_WindowDisplay),
                         TK_READABLE, ProcessEvents,(ClientData) 0 );
#else
    Tk_CreateFileHandler(ConnectionNumber(Draw_WindowDisplay),
                         TK_READABLE, ProcessEvents,(ClientData) 0 );
#endif

#endif

  if (tty) Prompt(theCommands.Interp(), 0);
  Prompt(theCommands.Interp(), 0);

  outChannel = Tcl_GetStdChannel(TCL_STDOUT);
  if (outChannel) {
        Tcl_Flush(outChannel);
    }
  Tcl_DStringInit(&command);

  /*
   * Loop infinitely, waiting for commands to execute.  When there
   * are no windows left, Tk_MainLoop returns and we exit.
   */

#ifdef _TK

  if (Draw_VirtualWindows) {
    // main window will never shown
    // but main loop will parse all Xlib messages
    Tcl_Eval(theCommands.Interp(), "wm withdraw .");
  }
  Tk_MainLoop();

#else

  fd_set readset;
  Standard_Integer count = ConnectionNumber(Draw_WindowDisplay);
  Standard_Integer numfd;
  while (1) {
      FD_ZERO(&readset);
      FD_SET(0,&readset);
      FD_SET(count,&readset);
#ifdef HPUX
      numfd = select(count+1,(Integer*)&readset,NULL,NULL,NULL);
#else
      numfd = select(count+1,&readset,NULL,NULL,NULL);
#endif
      if (FD_ISSET(0,&readset))     StdinProc((ClientData)0,0);
      if (FD_ISSET(count,&readset)) ProcessEvents((ClientData)0,0);
    }

#endif
}

//======================================================
// funtion : Init_Appli()
// purpose :
//======================================================
Standard_Boolean Init_Appli()
{
  theCommands.Init();
  interp = theCommands.Interp();

  Tcl_Init(interp) ;
  try {
    OCC_CATCH_SIGNALS
    Tk_Init(interp) ;
  } catch  (Standard_Failure) {
    cout <<" Pb au lancement de TK_Init "<<endl;
  }

  Tcl_StaticPackage(interp, "Tk", Tk_Init, (Tcl_PackageInitProc *) NULL);

  mainWindow =
  Tk_MainWindow(interp) ;
  if (mainWindow == NULL) {
    fprintf(stderr, "%s\n", Tcl_GetStringResult(interp));
    exit(1);
  }
  Tk_Name(mainWindow) =
  Tk_GetUid(Tk_SetAppName(mainWindow,
                          "Draw")) ;

  Tk_GeometryRequest(mainWindow, 200, 200);

  if (Draw_WindowDisplay == NULL) {
    Draw_WindowDisplay = Tk_Display(mainWindow);
  }
  if (Draw_WindowDisplay == NULL) {
    cout << "Cannot open display : "<<XDisplayName(NULL)<<endl;
    cout << "Interpret commands in batch mode."<<endl;
    return Standard_False;
  }
  //
  // synchronize the display server : could be done within Tk_Init
  //
  XSynchronize(Draw_WindowDisplay, True);
  XSetInputFocus(Draw_WindowDisplay,
                 PointerRoot,
                 RevertToPointerRoot,
                 CurrentTime);

  Draw_WindowScreen   = DefaultScreen(Draw_WindowDisplay);
  Draw_WindowColorMap = DefaultColormap(Draw_WindowDisplay,
                                        Draw_WindowScreen);
  tty = isatty(0);
  Tcl_SetVar(interp,"tcl_interactive",(char*)(tty ? "1" : "0"), TCL_GLOBAL_ONLY);
//  Tcl_SetVar(interp,"tcl_interactive",tty ? "1" : "0", TCL_GLOBAL_ONLY);
  return Standard_True;
}

//======================================================
// funtion : Destroy_Appli()
// purpose :
//======================================================
void Destroy_Appli()
{
  //XCloseDisplay(Draw_WindowDisplay);
}

//======================================================
// funtion : GetNextEvent()
// purpose :
//======================================================
void GetNextEvent(Event& ev)
{
  XEvent xev;
  XNextEvent(Draw_WindowDisplay, &xev);
  switch(xev.type)
  {
      case ButtonPress :
           ev.type = 4;
           ev.window = xev.xbutton.window;
           ev.button = xev.xbutton.button;
           ev.x = xev.xbutton.x;
           ev.y = xev.xbutton.y;
           break;

      case MotionNotify :
           ev.type = 6;
           ev.window = xev.xmotion.window;
           ev.button = 0;
           ev.x = xev.xmotion.x;
           ev.y = xev.xmotion.y;
           break;
   }
}

/*
 *----------------------------------------------------------------------
 *
 * StdinProc --
 *
 *        This procedure is invoked by the event dispatcher whenever
 *        standard input becomes readable.  It grabs the next line of
 *        input characters, adds them to a command being assembled, and
 *        executes the command if it's complete.
 *
 * Results:
 *        None.
 *
 * Side effects:
 *        Could be almost arbitrary, depending on the command that's
 *        typed.
 *
 *----------------------------------------------------------------------
 */

    /* ARGSUSED */
//static void StdinProc(ClientData clientData, int mask)
static void StdinProc(ClientData clientData, int )
{
  static int gotPartial = 0;
  char *cmd;
//  int code, count;
  int count;
  Tcl_Channel chan = (Tcl_Channel) clientData;

  // MSV Nov 2, 2001: patch for TCL 8.3: initialize line to avoid exception
  //                  when first user input is an empty string
  Tcl_DStringFree(&line);
  count = Tcl_Gets(chan, &line);

  // MKV 26.05.05
#if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4)))
  Tcl_DString linetmp;
  Tcl_DStringInit(&linetmp);
  Tcl_UniChar * UniCharString;
  UniCharString = Tcl_UtfToUniCharDString(Tcl_DStringValue(&line),-1,&linetmp);
  Standard_Integer l = Tcl_UniCharLen(UniCharString);
  TCollection_AsciiString AsciiString("");
  Standard_Character Character;
  Standard_Integer i;
  for (i=0; i<l; i++) {
    Character = UniCharString[i];
    AsciiString.AssignCat(Character);
  }
  Tcl_DStringInit(&line);
  Tcl_DStringAppend(&line, AsciiString.ToCString(), -1);
#endif
  if (count < 0) {
    if (!gotPartial) {
      if (tty) {
        Tcl_Exit(0);
      } else {
        Tcl_DeleteChannelHandler(chan, StdinProc, (ClientData) chan);
      }
      return;
    } else {
      count = 0;
    }
  }

  (void) Tcl_DStringAppend(&command, Tcl_DStringValue(&line), -1);
  cmd = Tcl_DStringAppend(&command, "\n", -1);
  Tcl_DStringFree(&line);
  try {
    OCC_CATCH_SIGNALS
  if (!Tcl_CommandComplete(cmd)) {
    gotPartial = 1;
    goto prompt;
  }
  gotPartial = 0;

  /*
   * Disable the stdin channel handler while evaluating the command;
   * otherwise if the command re-enters the event loop we might
   * process commands from stdin before the current command is
   * finished.  Among other things, this will trash the text of the
   * command being evaluated.
   */

  Tcl_CreateChannelHandler(chan, 0, StdinProc, (ClientData) chan);


  /*
   * Disable the stdin file handler while evaluating the command;
   * otherwise if the command re-enters the event loop we might
   * process commands from stdin before the current command is
   * finished.  Among other things, this will trash the text of the
   * command being evaluated.
   */

#ifdef _TK
   //  Tk_CreateFileHandler(0, 0, StdinProc, (ClientData) 0);
#endif
    //
    // xab average to avoid an output SIGBUS of DRAW
    // to ultimately prescise or remove once
    // the problem of free on the global variable at the average
    //
    //

  Interprete(cmd);


  Tcl_CreateChannelHandler(chan, TCL_READABLE, StdinProc,
                           (ClientData) chan);
  Tcl_DStringFree(&command);

  /*
   * Output a prompt.
   */

prompt:
  if (tty) Prompt(interp, gotPartial);

 } catch (Standard_Failure) {}

}

#else

// Source Specifique WNT

/****************************************************\
*  Draw_Window.cxx :
*
\****************************************************/

#include "Draw_Window.hxx"
#include "DrawRessource.h"
#include "init.h"

#include <Draw_Appli.hxx>
#include <OSD.hxx>

#ifdef _TK
# include <tk.h>
#endif

#define PENWIDTH 1
#define CLIENTWND 0
// Position of information in the extra memory

// indicates SUBSYSTEM:CONSOLE linker option, to be set to True in main()
Standard_EXPORT
Standard_Boolean Draw_IsConsoleSubsystem = Standard_False;


Standard_Boolean Draw_BlackBackGround = Standard_True;

// Creation of color stylos
HPEN colorPenTab[MAXCOLOR] = {CreatePen(PS_SOLID, PENWIDTH, RGB(255,255,255)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(255,0,0)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(0,255,0)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(0,0,255)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(0,255,255)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(255,215,0)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(255,0,255)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(255,52,179)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(255,165,0)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(255,228,225)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(255,160,122)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(199,21,133)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(255,255,0)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(240,230,140)),
                              CreatePen(PS_SOLID, PENWIDTH, RGB(255,127,80))};

// Correspondance mode X11 and WINDOWS NT
int modeTab[16] = {R2_BLACK, R2_MASKPEN, R2_MASKPENNOT, R2_COPYPEN,
                   R2_MASKNOTPEN, R2_NOP, R2_XORPEN, R2_MERGEPEN,
                   R2_NOTMASKPEN, R2_NOTXORPEN, R2_NOT, R2_MERGEPENNOT,
                   R2_NOTCOPYPEN, R2_MERGENOTPEN, R2_NOTMERGEPEN, R2_WHITE};

/*--------------------------------------------------------*\
|  CREATE DRAW WINDOW PROCEDURE
\*--------------------------------------------------------*/
HWND DrawWindow::CreateDrawWindow(HWND hWndClient, int nitem)
{
  if (Draw_IsConsoleSubsystem) {
    HWND aWin = CreateWindow (DRAWCLASS, DRAWTITLE,
                              WS_OVERLAPPEDWINDOW,
                              1,1,1,1,
                              NULL, NULL,::GetModuleHandle(NULL), NULL);
    SetWindowPos(aWin, HWND_TOPMOST, 1,1,1,1, SWP_NOMOVE);
    SetWindowPos(aWin, HWND_NOTOPMOST, 1,1,1,1, SWP_NOMOVE);
    return aWin;
  }
  else {
    HANDLE hInstance;
#ifndef _WIN64
    hInstance = (HANDLE)GetWindowLong(hWndClient,GWL_HINSTANCE);
#else
    hInstance = (HANDLE)GetWindowLong(hWndClient,GWLP_HINSTANCE);
#endif

    return CreateMDIWindow(DRAWCLASS, DRAWTITLE,
                           WS_CAPTION | WS_CHILD | WS_THICKFRAME,
                           1,1,0,0,
                           hWndClient, (HINSTANCE)hInstance, nitem);
  }
}


/*--------------------------------------------------------*\
|  DRAW WINDOW PROCEDURE
\*--------------------------------------------------------*/
LONG APIENTRY DrawWindow::DrawProc(HWND hWnd, UINT wMsg, WPARAM wParam, LONG lParam )
{
  DrawWindow* localObjet = (DrawWindow*)GetWindowLong(hWnd, CLIENTWND);
  if (!localObjet)
    {
      if (Draw_IsConsoleSubsystem)
        return LONG(DefWindowProc(hWnd, wMsg, wParam, lParam));
      else
        return LONG(DefMDIChildProc(hWnd, wMsg, wParam, lParam));
    }

  PAINTSTRUCT ps;

  switch(wMsg)
  {
  case WM_PAINT :
    BeginPaint(hWnd, &ps);
    if (localObjet->GetUseBuffer())
      localObjet->Redraw();
    else
      localObjet->WExpose();
    EndPaint(hWnd, &ps);
    return 0l;
    break;

  case WM_SIZE:
    if (localObjet->GetUseBuffer()) {
      localObjet->InitBuffer();
      localObjet->WExpose();
      localObjet->Redraw();
      return 0l;
      break;
    }

  default:
    if (Draw_IsConsoleSubsystem)
      return LONG(DefWindowProc(hWnd, wMsg, wParam, lParam));
    else
      return LONG(DefMDIChildProc(hWnd, wMsg, wParam, lParam));
  }
  return (0l);
}



/*
**  IMPLEMENTATION of the CLASS DRAWWINDOW
 */

/*--------------------------------------------------------*\
| Initialization of static variables of DrawWindow
\*--------------------------------------------------------*/

DrawWindow* DrawWindow::firstWindow = NULL;
HWND DrawWindow::hWndClientMDI = 0;

/*--------------------------------------------------------*\
| Constructors of Draw_Window
\*--------------------------------------------------------*/

// Default Constructor
//________________________
DrawWindow::DrawWindow() :
        win(0),
        next(firstWindow),
        previous(NULL),
        myMemHbm(NULL),
        myUseBuffer(Standard_False)
{
  if (firstWindow) firstWindow->previous = this;
  firstWindow = this;
}

//________________________
DrawWindow::DrawWindow(char* title,
                       Standard_Integer X, Standard_Integer Y,
                       Standard_Integer dX,Standard_Integer dY) :
       win(0),        next(firstWindow), previous(NULL), myMemHbm(NULL), myUseBuffer(Standard_False)
{
  if (firstWindow) firstWindow->previous = this;
  firstWindow = this;
  Init(X, Y, dX, dY);
  SetTitle(title);
}
DrawWindow::DrawWindow(char* title,
                       Standard_Integer X, Standard_Integer Y,
                       Standard_Integer dX,Standard_Integer dY,
                       HWND theWin) :
       win(theWin),next(firstWindow), previous(NULL), myMemHbm(NULL), myUseBuffer(Standard_False)
{
  if (firstWindow) firstWindow->previous = this;
  firstWindow = this;
  Init(X, Y, dX, dY);
  SetTitle(title);
}



/*--------------------------------------------------------*\
| Destructor of DrawWindow
\*--------------------------------------------------------*/
DrawWindow::~DrawWindow()
{
  if (previous)
    previous->next = next;
  else
    firstWindow = next;
  if (next)
    next->previous = previous;

  // Delete 'off-screen drawing'-related objects
  if (myMemHbm) {
    DeleteObject(myMemHbm);
    myMemHbm = NULL;
  }
}



/*--------------------------------------------------------*\
|  Init
\*--------------------------------------------------------*/
void DrawWindow::Init(Standard_Integer theXLeft, Standard_Integer theYTop,
                      Standard_Integer theWidth, Standard_Integer theHeight)
{
  if (win == 0)
  {
    win = CreateDrawWindow(hWndClientMDI, 0);
  }

  // include decorations in the window dimensions
  // to reproduce same behaviour of Xlib window.
  theXLeft   -= GetSystemMetrics(SM_CXSIZEFRAME);
  theYTop    -= GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYCAPTION);
  theWidth   += 2 * GetSystemMetrics(SM_CXSIZEFRAME);
  theHeight  += 2 * GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYCAPTION);

  SetPosition (theXLeft, theYTop);
  SetDimension (theWidth, theHeight);
  // Save the pointer at the instance associated to the window
  SetWindowLong(win, CLIENTWND, (LONG)this);
  HDC hDC = GetDC(win);
  SetBkColor(hDC, RGB(0, 0, 0));
  myCurrPen  = 3;
  myCurrMode = 3;
  SelectObject(hDC, colorPenTab[myCurrPen]); // Default pencil
  SelectObject(hDC, GetStockObject(BLACK_BRUSH));
  SetTextColor(hDC, RGB(0,0,255));
  ReleaseDC(win, hDC);

  if (Draw_VirtualWindows)
  {
    // create a virtual window
    SetUseBuffer (Standard_True);
  }
}

/*--------------------------------------------------------*\
|  SetUseBuffer
\*--------------------------------------------------------*/
void DrawWindow::SetUseBuffer(Standard_Boolean use)
{
  myUseBuffer = use;
  InitBuffer();
}

/*--------------------------------------------------------*\
|  InitBuffer
\*--------------------------------------------------------*/
void DrawWindow::InitBuffer()
{
  if (myUseBuffer) {
    RECT rc;
    HDC hDC = GetDC(win);
    GetClientRect(win, &rc);
    if (myMemHbm) {
      BITMAP aBmp;
      GetObject(myMemHbm, sizeof(BITMAP), &aBmp);
      if (rc.right-rc.left == aBmp.bmWidth && rc.bottom-rc.top == aBmp.bmHeight) return;
      DeleteObject(myMemHbm);
    }
    myMemHbm = (HBITMAP)CreateCompatibleBitmap(hDC,
                                      rc.right-rc.left,
                                      rc.bottom-rc.top);
    HDC aMemDC      = GetMemDC(hDC);
    FillRect(aMemDC, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
    ReleaseMemDC(aMemDC);
    ReleaseDC(win, hDC);
  }
  else {
    if (myMemHbm) {
      DeleteObject(myMemHbm);
      myMemHbm = NULL;
    }
  }
}

/*--------------------------------------------------------*\
|  GetMemDC
\*--------------------------------------------------------*/
HDC DrawWindow::GetMemDC(HDC theWinDC)
{
  if (!myUseBuffer) return NULL;

  HDC aWorkDC = CreateCompatibleDC(theWinDC);
  myOldHbm = (HBITMAP)SelectObject(aWorkDC, myMemHbm);
  SetROP2(aWorkDC, modeTab[myCurrMode]);
  SelectObject(aWorkDC, colorPenTab[myCurrPen]);
  SetBkColor(aWorkDC, RGB(0, 0, 0));
  SelectObject(aWorkDC, GetStockObject(BLACK_BRUSH));
  SetTextColor(aWorkDC, RGB(0,0,255));
  return aWorkDC;
}


/*--------------------------------------------------------*\
|  ReleaseMemDC
\*--------------------------------------------------------*/
void DrawWindow::ReleaseMemDC(HDC theMemDC)
{
  if (!myUseBuffer || !theMemDC) return;

  if (myOldHbm) SelectObject(theMemDC, myOldHbm);
  DeleteDC(theMemDC);
}


/*--------------------------------------------------------*\
|  SetPosition
\*--------------------------------------------------------*/
void DrawWindow::SetPosition(Standard_Integer posX, Standard_Integer posY)
{
  SetWindowPos(win, 0,
               posX, posY,
               0, 0,
               SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
}


/*--------------------------------------------------------*\
|  SetDimension
\*--------------------------------------------------------*/
void DrawWindow::SetDimension(Standard_Integer dimX, Standard_Integer dimY)
{
  SetWindowPos(win, 0,
               0, 0,
               dimX, dimY,
               SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
}


/*--------------------------------------------------------*\
|  GetPosition
\*--------------------------------------------------------*/
void DrawWindow::GetPosition(Standard_Integer &dimX,
                             Standard_Integer &dimY)
{
  RECT rect;
  GetWindowRect(win, &rect);

  POINT point;
  point.x = rect.left;
  point.y = rect.top;

  ScreenToClient(hWndClientMDI, &point);
  dimX = point.x;
  dimY = point.y;
}


/*--------------------------------------------------------*\
|  HeightWin
\*--------------------------------------------------------*/
Standard_Integer DrawWindow::HeightWin() const
{
  RECT rect;
  GetClientRect(win, &rect);
  return(rect.bottom-rect.top);
}


/*--------------------------------------------------------*\
|  WidthWin
\*--------------------------------------------------------*/
Standard_Integer DrawWindow::WidthWin() const
{
  RECT rect;
  GetClientRect(win, &rect);
  return(rect.right-rect.left);
}


/*--------------------------------------------------------*\
|  SetTitle
\*--------------------------------------------------------*/
void DrawWindow::SetTitle(char* title)
{
  SetWindowText(win, title);
}


/*--------------------------------------------------------*\
|  GetTitle
|    Attention do not forget to unallocate the memory
\*--------------------------------------------------------*/
char* DrawWindow::GetTitle()
{
  char* title=new char[31];
  GetWindowText(win, title, 30);
  return title;
}


/*--------------------------------------------------------*\
|  DisplayWindow
\*--------------------------------------------------------*/
void DrawWindow::DisplayWindow()
{
  if (Draw_VirtualWindows)
  {
    return;
  }
  ShowWindow (win, SW_SHOW);
  UpdateWindow (win);
}


/*--------------------------------------------------------*\
|  Hide
\*--------------------------------------------------------*/
void DrawWindow::Hide()
{
  ShowWindow(win, SW_HIDE);
}


/*--------------------------------------------------------*\
|  Destroy
\*--------------------------------------------------------*/
void DrawWindow::Destroy()
{
  DestroyWindow(win);
}



/*--------------------------------------------------------*\
|  Clear
\*--------------------------------------------------------*/
void DrawWindow::Clear()
{
  HDC hDC = GetDC(win);
  HDC aWorkDC = myUseBuffer ? GetMemDC(hDC) : hDC;

  int debug = GetROP2(aWorkDC);
  SaveDC(aWorkDC);
  SelectObject(aWorkDC,GetStockObject(BLACK_PEN));
  Rectangle(aWorkDC, 0, 0, WidthWin(), HeightWin());
  RestoreDC(aWorkDC,-1);

  if (myUseBuffer) ReleaseMemDC(aWorkDC);
  ReleaseDC(win,hDC);
}

/*--------------------------------------------------------*\
|  SaveBitmap
\*--------------------------------------------------------*/
static Standard_Boolean SaveBitmap (HBITMAP theHBitmap,
                                    const char* theFileName)
{
  // Copy data from HBITMAP
  BITMAP aBitmap;

  // Get informations about the bitmap
  GetObject (theHBitmap, sizeof(BITMAP), (LPSTR )&aBitmap);
  Standard_Integer aWidth  = aBitmap.bmWidth;
  Standard_Integer aHeight = aBitmap.bmHeight;

  // Setup image data
  BITMAPINFOHEADER aBitmapInfo;
  memset (&aBitmapInfo, 0, sizeof(BITMAPINFOHEADER));
  aBitmapInfo.biSize = sizeof(BITMAPINFOHEADER);
  aBitmapInfo.biWidth = aWidth;
  aBitmapInfo.biHeight = aHeight; // positive means bottom-up!
  aBitmapInfo.biPlanes = 1;
  aBitmapInfo.biBitCount = 32;
  aBitmapInfo.biCompression = BI_RGB;

  Standard_Integer aBytesPerLine = aWidth * 4;
  Standard_Byte* aDataPtr = new Standard_Byte[aBytesPerLine * aHeight];

  // Copy the pixels
  HDC aDC = GetDC (NULL);
  Standard_Boolean isSuccess
    = GetDIBits (aDC,             // handle to DC
                 theHBitmap,      // handle to bitmap
                 0,               // first scan line to set
                 aHeight,         // number of scan lines to copy
                 aDataPtr,        // array for bitmap bits
                 (LPBITMAPINFO )&aBitmapInfo, // bitmap data info
                 DIB_RGB_COLORS   // RGB
                 ) != 0;

  if (isSuccess)
  {
    Handle(Image_PixMap) anImagePixMap = new Image_PixMap (aDataPtr,
                                                           aWidth, aHeight,
                                                           aBytesPerLine,
                                                           aBitmapInfo.biBitCount,
                                                           Standard_False); // bottom-up!

    // Release dump memory here
    delete[] aDataPtr;

    // save the image
    anImagePixMap->Dump (theFileName);
  }
  else
  {
    // Release dump memory
    delete[] aDataPtr;
  }
  ReleaseDC (NULL, aDC);
  return isSuccess;
}

/*--------------------------------------------------------*\
|  Save
\*--------------------------------------------------------*/
Standard_Boolean DrawWindow::Save (const char* theFileName) const
{
  if (myUseBuffer)
  {
    return SaveBitmap (myMemHbm, theFileName);
  }

  RECT aRect;
  GetClientRect (win, &aRect);
  int aWidth  = aRect.right  - aRect.left;
  int aHeight = aRect.bottom - aRect.top;

  // Prepare the DCs
  HDC aDstDC = GetDC (NULL);
  HDC aSrcDC = GetDC (win); // we copy only client area
  HDC aMemDC = CreateCompatibleDC (aDstDC);

  // Copy the screen to the bitmap
  HBITMAP anHBitmapDump = CreateCompatibleBitmap (aDstDC, aWidth, aHeight);
  HBITMAP anHBitmapOld = (HBITMAP )SelectObject (aMemDC, anHBitmapDump);
  BitBlt (aMemDC, 0, 0, aWidth, aHeight, aSrcDC, 0, 0, SRCCOPY);

  Standard_Boolean isSuccess = SaveBitmap (anHBitmapDump, theFileName);

  // Free objects
  DeleteObject (SelectObject (aMemDC, anHBitmapOld));
  DeleteDC (aMemDC);

  return isSuccess;
}

/*--------------------------------------------------------*\
|  DrawString
\*--------------------------------------------------------*/
void DrawWindow::DrawString(int x,int y, char* text)
{
  HDC hDC = GetDC(win);
  HDC aWorkDC = myUseBuffer ? GetMemDC(hDC) : hDC;

  TextOut(aWorkDC, x, y, text, strlen(text));

  if (myUseBuffer) ReleaseMemDC(aWorkDC);
  ReleaseDC(win,hDC);
}

/*--------------------------------------------------------*\
|  DrawSegments
\*--------------------------------------------------------*/
void DrawWindow::DrawSegments(Segment *tab, int nbElem)
{
  HDC hDC = GetDC(win);
  HDC aWorkDC = myUseBuffer ? GetMemDC(hDC) : hDC;

  for(int i = 0 ; i < nbElem ; i++)
  {
    MoveToEx(aWorkDC, tab[i].x1, tab[i].y1, NULL);
    LineTo(aWorkDC, tab[i].x2, tab[i].y2);
  }

  if (myUseBuffer) ReleaseMemDC(aWorkDC);
  ReleaseDC(win,hDC);
}

/*--------------------------------------------------------*\
|  Redraw
\*--------------------------------------------------------*/
void DrawWindow::Redraw()
{
  if (myUseBuffer) {
    HDC hDC = GetDC(win);
    RECT rc;
    GetClientRect(win, &rc);
    HDC aMemDC = GetMemDC(hDC);
    BitBlt(hDC,
           rc.left, rc.top,
           rc.right-rc.left, rc.bottom-rc.top,
           aMemDC,
           0, 0, SRCCOPY);
    ReleaseMemDC(aMemDC);
    ReleaseDC(win,hDC);
  }
}

/*--------------------------------------------------------*\
|  SetMode
\*--------------------------------------------------------*/
void DrawWindow::SetMode(int mode)
{
  HDC hDC = GetDC(win);
  myCurrMode = mode;
  SetROP2(hDC, modeTab[mode]);
  ReleaseDC(win,hDC);
}


/*--------------------------------------------------------*\
|  SetColor
\*--------------------------------------------------------*/
void DrawWindow::SetColor(Standard_Integer color)
{
  HDC hDC = GetDC(win);
  myCurrPen = color;
  SelectObject(hDC,colorPenTab[color]);
  ReleaseDC(win,hDC);
}


/*--------------------------------------------------------*\
|  WExpose
\*--------------------------------------------------------*/
void DrawWindow::WExpose()
{
}


/*--------------------------------------------------------*\
|  WButtonPress
\*--------------------------------------------------------*/
void DrawWindow::WButtonPress(const Standard_Integer,
                               const Standard_Integer,
                               const Standard_Integer&)
{
}


/*--------------------------------------------------------*\
|  WButtonRelease
\*--------------------------------------------------------*/
void DrawWindow::WButtonRelease(const Standard_Integer,
                                 const Standard_Integer,
                                 const Standard_Integer&)
{
}


/*--------------------------------------------------------*\
|  WMotionNotify
\*--------------------------------------------------------*/
void Draw_Window::WMotionNotify(const Standard_Integer ,
                                const Standard_Integer )
{
}


/*--------------------------------------------------------*\
|  WConfigureNotify
\*--------------------------------------------------------*/
void DrawWindow::WConfigureNotify(const Standard_Integer,
                                   const Standard_Integer,
                                   const Standard_Integer,
                                   const Standard_Integer)
{
}


/*--------------------------------------------------------*\
|  WUnmapNotify
\*--------------------------------------------------------*/
void DrawWindow::WUnmapNotify()
{
}



/*
**  IMPLEMENTATION of the CLASS SEGMENT
 */

/*--------------------------------------------------------*\
|  Init
\*--------------------------------------------------------*/

void Segment::Init(Standard_Integer a1, Standard_Integer a2,
                   Standard_Integer a3, Standard_Integer a4)
{
  x1=a1;
  y1=a2;
  x2=a3;
  y2=a4;
}

static DWORD WINAPI tkLoop(VOID);
#ifdef _TK
static Tk_Window mainWindow;
#endif

//* threads sinchronization *//
DWORD  dwMainThreadId;
console_semaphore_value volatile console_semaphore = WAIT_CONSOLE_COMMAND;
char console_command[1000];

bool volatile isTkLoopStarted = false;

/*--------------------------------------------------------*\
|  Init_Appli
\*--------------------------------------------------------*/
Standard_Boolean Init_Appli(HINSTANCE hInst,
                            HINSTANCE hPrevInst, int nShow, HWND& hWndFrame )
{
  DWORD IDThread;
  HANDLE hThread;
  console_semaphore = STOP_CONSOLE;

  theCommands.Init();
  interp = theCommands.Interp();
  Tcl_Init(interp) ;

  dwMainThreadId = GetCurrentThreadId();

  //necessary for normal Tk operation
  hThread = CreateThread(NULL, // no security attributes
                           0,                           // use default stack size
                           (LPTHREAD_START_ROUTINE) tkLoop, // thread function
                           NULL,                    // no thread function argument
                           0,                       // use default creation flags
                           &IDThread);
  if (!hThread) {
    cout << "Tcl/Tk main loop thread not created. Switching to batch mode..." << endl;
#ifdef _TK
    try {
      OCC_CATCH_SIGNALS
      Tk_Init(interp) ;
    } catch  (Standard_Failure) {
      cout <<" Pb au lancement de TK_Init "<<endl;
    }

    Tcl_StaticPackage(interp, "Tk", Tk_Init, (Tcl_PackageInitProc *) NULL);
#endif
    //since the main Tcl/Tk loop wasn't created --> switch to batch mode
    return Standard_False;
  }

  // san - 06/08/2002 - Time for tkLoop to start; Tk fails to initialize otherwise
  while (!isTkLoopStarted)
    Sleep(10);

  // Saving of window classes
  if(!hPrevInst)
    if(!RegisterAppClass(hInst))
      return(Standard_False);

  if (Draw_VirtualWindows) {
    // main window will never shown
    Tcl_Eval(theCommands.Interp(), "wm withdraw .");
  }

  /*
   ** Enter the application message-polling loop.  This is the anchor for
   ** the application.
  */
  if(Draw_IsConsoleSubsystem)

    hWndFrame = NULL;

  else if (hWndFrame = CreateAppWindow(hInst))
  {
    ShowWindow(hWndFrame,nShow);
    UpdateWindow(hWndFrame);
  }

  return Standard_True;
}

Standard_Boolean Draw_Interprete (char*);

/*--------------------------------------------------------*\
|  readStdinThreadFunc
\*--------------------------------------------------------*/
static DWORD WINAPI readStdinThreadFunc(VOID)
{
  if (!Draw_IsConsoleSubsystem) return 1;

  while (1) {
    while (console_semaphore != WAIT_CONSOLE_COMMAND)
      Sleep(100);
    if (gets(console_command))
      {
        console_semaphore = HAS_CONSOLE_COMMAND;
      }

  }
  return 0;
}

/*--------------------------------------------------------*\
|  exitProc: finalization handler for Tcl/Tk thread. Forces parent process to die
\*--------------------------------------------------------*/
void exitProc(ClientData /*dc*/)
{
  HANDLE proc = GetCurrentProcess();
  TerminateProcess(proc, 0);
}

/*--------------------------------------------------------*\
|  tkLoop: implements Tk_Main()-like behaviour in a separate thread
\*--------------------------------------------------------*/
static DWORD WINAPI tkLoop(VOID)
{
  Tcl_CreateExitHandler(exitProc, 0);

#if (TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 5))
  Tcl_RegisterChannel(theCommands.Interp(),  Tcl_GetStdChannel(TCL_STDIN));
  Tcl_RegisterChannel(theCommands.Interp(),  Tcl_GetStdChannel(TCL_STDOUT));
  Tcl_RegisterChannel(theCommands.Interp(),  Tcl_GetStdChannel(TCL_STDERR));
#endif

#ifdef _TK
  try {
    OCC_CATCH_SIGNALS
    Standard_Integer res = Tk_Init(interp) ;
    if (res != TCL_OK)
      cout << "tkLoop: error in Tk initialization. Tcl reported: " << Tcl_GetStringResult(interp) << endl;

  } catch  (Standard_Failure) {
    cout <<"tkLoop: exception in TK_Init "<<endl;
  }
  Tcl_StaticPackage(interp, "Tk", Tk_Init, (Tcl_PackageInitProc *) NULL);

  mainWindow =
    Tk_MainWindow(interp) ;
  if (mainWindow == NULL) {
        fprintf(stderr, "%s\n", Tcl_GetStringResult(interp));
        cout << "tkLoop: Tk_MainWindow() returned NULL. Exiting..." << endl;
        Tcl_Exit(0);
   }
  Tk_Name(mainWindow) =
    Tk_GetUid(Tk_SetAppName(mainWindow,
                          "Draw")) ;

  if (Draw_VirtualWindows) {
    // main window will never shown
    Tcl_Eval(theCommands.Interp(), "wm withdraw .");
  }
#endif  //#ifdef _TK

  // msv - 16/09/2004 - set signal handler in the new thread
  OSD::SetSignal();

  // san - 06/08/2002 - inform the others that we have started
  isTkLoopStarted = true;

  while (console_semaphore == STOP_CONSOLE)
    Tcl_DoOneEvent(TCL_ALL_EVENTS | TCL_DONT_WAIT);

  if (Draw_IsConsoleSubsystem && console_semaphore == WAIT_CONSOLE_COMMAND)
    Prompt(interp, 0);

  //process a command
#ifdef _TK
  // san - 10/07/02 -- We should not exit until the Main Tk window is closed
  while (Tk_GetNumMainWindows() > 0) {
#else
  while (1) {
#endif
    while(Tcl_DoOneEvent(TCL_ALL_EVENTS | TCL_DONT_WAIT));
    if (console_semaphore == HAS_CONSOLE_COMMAND) {
      if (Draw_Interprete(console_command))
        if (Draw_IsConsoleSubsystem) Prompt(interp, 0);
      else
        if (Draw_IsConsoleSubsystem) Prompt(interp, 1);
      console_semaphore = WAIT_CONSOLE_COMMAND;
    }
    else
      Sleep(100);

  }

  Tcl_Exit(0);

  return 0;
}


/*--------------------------------------------------------*\
|  Run_Appli
\*--------------------------------------------------------*/
void Run_Appli(HWND hWnd)
{
  MSG msg;
  HACCEL hAccel = NULL;

  msg.wParam = 1;

//  if (!(hAccel = LoadAccelerators (hInstance, MAKEINTRESOURCE(ACCEL_ID))))
//        MessageBox(hWnd, "MDI: Load Accel failure!", "Error", MB_OK);
  DWORD IDThread;
  HANDLE hThread;
  if (Draw_IsConsoleSubsystem) {
    hThread = CreateThread(NULL, // no security attributes
                           0,                           // use default stack size
                           (LPTHREAD_START_ROUTINE) readStdinThreadFunc, // thread function
                           NULL,                    // no thread function argument
                           0,                       // use default creation flags
                           &IDThread);              // returns thread identifier
    if (!hThread) {
      cout << "pb in creation of the thread reading stdin" << endl;
      Draw_IsConsoleSubsystem = Standard_False;
      Init_Appli(GetModuleHandle(NULL),
                 GetModuleHandle(NULL),
                 1, hWnd); // reinit => create MDI client wnd
    }
  }

  //turn on the command interpretation mechanism (regardless of the mode)
  if (console_semaphore == STOP_CONSOLE)
    console_semaphore = WAIT_CONSOLE_COMMAND;

  //simple Win32 message loop
  while (GetMessage(&msg, NULL, 0, 0) > 0)
  {
    if (!TranslateAccelerator(hWnd, hAccel, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  ExitProcess(0);
}


/*--------------------------------------------------------*\
|  Destroy_Appli
\*--------------------------------------------------------*/
void Destroy_Appli(HINSTANCE hInst)
{
  UnregisterAppClass(hInst);
  for (int i = 0 ; i < MAXCOLOR ; i++)
    DeleteObject(colorPenTab[i]);
}

/*--------------------------------------------------------*\
|  SelectWait
\*--------------------------------------------------------*/
void DrawWindow::SelectWait(HANDLE& hWnd, int& x, int& y, int& button)
{
  MSG msg;

  msg.wParam = 1;

  GetMessage(&msg,NULL,0,0);
  while((msg.message != WM_RBUTTONDOWN && msg.message != WM_LBUTTONDOWN) ||
        ! ( Draw_IsConsoleSubsystem || IsChild(DrawWindow::hWndClientMDI,msg.hwnd)) )
    GetMessage(&msg,NULL,0,0);

  hWnd = msg.hwnd;
  x = LOWORD(msg.lParam);
  y = HIWORD(msg.lParam);
  if (msg.message == WM_LBUTTONDOWN)
    button = 1;
  else
    button = 3;
}

/*--------------------------------------------------------*\
|  SelectNoWait
\*--------------------------------------------------------*/
void DrawWindow::SelectNoWait(HANDLE& hWnd, int& x, int& y, int& button)
{
  MSG msg;

  msg.wParam = 1;

  GetMessage(&msg,NULL,0,0);
  while((msg.message != WM_RBUTTONDOWN && msg.message != WM_LBUTTONDOWN &&
        msg.message != WM_MOUSEMOVE) ||
        ! ( Draw_IsConsoleSubsystem || IsChild(DrawWindow::hWndClientMDI,msg.hwnd) ) )
    GetMessage(&msg,NULL,0,0);
  hWnd = msg.hwnd;
  x = LOWORD(msg.lParam);
  y = HIWORD(msg.lParam);
  switch (msg.message)
  {
    case WM_LBUTTONDOWN :
                    button = 1;
                    break;

    case WM_RBUTTONDOWN :
                    button = 3;
                    break;

    case WM_MOUSEMOVE :
                    button = 0;
                    break;
  }
}

Standard_Boolean DrawWindow::DefineColor (const Standard_Integer, const char*)
{
  return Standard_True;
};

#endif
