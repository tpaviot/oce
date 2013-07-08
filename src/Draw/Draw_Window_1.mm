// Copyright 2012 OPEN CASCADE SAS
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

#if defined(__APPLE__) && !defined(MACOSX_USE_GLX)

#import <Cocoa/Cocoa.h>

#include <Draw_Window.hxx>
#include <Cocoa_LocalPool.hxx>

@interface Draw_CocoaView : NSView
{
  NSImage* myImage;
}

- (void )setImage: (NSImage* )theImage;
- (void )redraw;
@end

@implementation Draw_CocoaView

- (void )setImage: (NSImage* )theImage
{
  [theImage retain];
  [myImage release];
  myImage = theImage;
}

- (BOOL )isFlipped
{
  return YES; // for drawing image from left-top corner
}

- (void )redraw
{
  [self setNeedsDisplay: YES];
}

- (void )drawRect: (NSRect )theRect
{

  NSRect aBounds = NSMakeRect (0.0, 0.0, myImage.size.width, myImage.size.height);

  [myImage drawInRect: aBounds
             fromRect: NSZeroRect
            operation: NSCompositeSourceOver
             fraction: 1
       respectFlipped: YES
                hints: nil];
}

- (void )dealloc
{
  [myImage release];
  [super dealloc];
}
@end

static Standard_Integer getScreenBottom()
{
  NSRect aRect = [[[NSScreen screens] objectAtIndex:0] frame];
  Standard_Integer aScreenBottom = Standard_Integer(aRect.size.height + aRect.origin.y);
  return aScreenBottom;
}

extern Standard_Boolean Draw_VirtualWindows;
static Standard_Boolean Draw_IsInZoomingMode = Standard_False;

Standard_Real Draw_RGBColorsArray[MAXCOLOR][3] = {{1.0,  1.0,  1.0},
                                                  {1.0,  0.0,  0.0},
                                                  {0.0,  1.0,  0.0},
                                                  {0.0,  0.0,  1.0},
                                                  {0.0,  1.0,  1.0},
                                                  {1.0,  0.84, 0.0},
                                                  {1.0,  0.0,  1.0},
                                                  {1.0,  0.2,  0.7},
                                                  {1.0,  0.65, 0.0},
                                                  {1.0,  0.89, 0.88},
                                                  {1.0,  0.63, 0.48},
                                                  {0.78, 0.08, 0.52},
                                                  {1.0,  1.0,  0.0},
                                                  {0.94, 0.9,  0.55},
                                                  {1.0,  0.5,  0.31}};

//=======================================================================
//function : Draw_Window
//purpose  :
//=======================================================================
Draw_Window::Draw_Window() :
  myWindow (NULL),
  myView (NULL),
  myImageBuffer (NULL),
  myUseBuffer (Standard_False),
  nextWindow (firstWindow),
  previousWindow (NULL)
{
  if (firstWindow != NULL) firstWindow->previousWindow = this;
  firstWindow = this;
}

//=======================================================================
//function : Draw_Window
//purpose  :
//=======================================================================
Draw_Window::Draw_Window (Standard_CString theTitle,
                          const Standard_Integer& theXLeft, const Standard_Integer& theYTop,
                          const Standard_Integer& theWidth, const Standard_Integer& theHeight):
  myWindow (NULL),
  myView (NULL),
  myImageBuffer (NULL),
  myUseBuffer (Standard_False),
  nextWindow (firstWindow),
  previousWindow (NULL)
{
  if (firstWindow != NULL) firstWindow->previousWindow = this;
  firstWindow = this;
  Init (theXLeft, theYTop, theWidth, theHeight);
  SetTitle (theTitle);
}

Draw_Window::Draw_Window (NSWindow*               theWindow, Standard_CString        theTitle,
                          const Standard_Integer& theXLeft,  const Standard_Integer& theYTop,
                          const Standard_Integer& theWidth,  const Standard_Integer& theHeight):
  myWindow (NULL),
  myView (NULL),
  myImageBuffer (NULL),
  myUseBuffer (Standard_False),
  nextWindow (firstWindow),
  previousWindow (NULL)
{
  myWindow = [theWindow retain];
  if (firstWindow != NULL) firstWindow->previousWindow = this;
  firstWindow = this;
  Init (theXLeft, theYTop, theWidth, theHeight);
  SetTitle (theTitle);
}

//=======================================================================
//function : ~Draw_Window
//purpose  :
//=======================================================================
Draw_Window::~Draw_Window()
{
  if (previousWindow != NULL)
  {
    previousWindow->nextWindow = nextWindow;
  }
  else
  {
    firstWindow = nextWindow;
  }

  if (nextWindow != NULL)
  {
    nextWindow->previousWindow = previousWindow;
  }

  if (myWindow != NULL)
  { 
    [myWindow release];
    myWindow = NULL;
  }

  if (myView != NULL)
  {
    [myView release];
    myView = NULL;
  }

  if (myImageBuffer != NULL)
  {
    [myImageBuffer release];
    myImageBuffer = NULL;
  }
}

//=======================================================================
//function : Init
//purpose  :
//=======================================================================
void Draw_Window::Init (const Standard_Integer& theXLeft, const Standard_Integer& theYTop,
                        const Standard_Integer& theWidth, const Standard_Integer& theHeight)
{
  Cocoa_LocalPool aLocalPool;

  // converting left-bottom coordinate to left-top coordinate
  Standard_Integer anYTop = getScreenBottom() - theYTop - theHeight;

  if (myWindow == NULL)
  {
    NSRect     aRectNs   = NSMakeRect (theXLeft, anYTop, theWidth, theHeight);
    NSUInteger aWinStyle = NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask;

    myWindow = [[NSWindow alloc] initWithContentRect: aRectNs
                                           styleMask: aWinStyle
                                             backing: NSBackingStoreBuffered
                                               defer: NO];
  }

  if (myView == NULL)
  {
    NSRect aBounds = [[myWindow contentView] bounds];
    
    myView = [[Draw_CocoaView alloc] initWithFrame: aBounds];
    [myWindow setContentView: myView];
  }

  if (myImageBuffer == NULL)
  {
    NSRect aRectNs = [myView bounds];
    myImageBuffer  = [[NSImage alloc] initWithSize: aRectNs.size];
  }

  [myView setImage: myImageBuffer];

  myUseBuffer = Draw_VirtualWindows;

  myCurrentColor = 3;

  [myWindow setBackgroundColor: NSColor.blackColor];
  [myWindow setReleasedWhenClosed: NO];
}

//=======================================================================
//function : InitBuffer
//purpose  :
//=======================================================================
void Draw_Window::InitBuffer()
{
  //
}

//=======================================================================
//function : SetPosition
//purpose  :
//=======================================================================
void Draw_Window::SetPosition (const Standard_Integer& theNewXpos,
                               const Standard_Integer& theNewYpos)
{
  NSPoint aNewPosition = NSMakePoint (theNewXpos, theNewYpos);
  [myWindow setFrameTopLeftPoint: aNewPosition];
}

//=======================================================================
//function : SetDimension
//purpose  :
//=======================================================================
void Draw_Window::SetDimension (const Standard_Integer& theNewWidth,
                                const Standard_Integer& theNewHeight)
{
  NSRect aWindowRect = [myWindow frame];
  Standard_Integer aNewY = aWindowRect.origin.y + aWindowRect.size.height - theNewHeight;
  NSRect aNewContentRect = NSMakeRect (aWindowRect.origin.x, aNewY,
                                       theNewWidth, theNewHeight);
  [myWindow setFrame: aNewContentRect display: YES];
}

//=======================================================================
//function : GetPosition
//purpose  :
//=======================================================================
void Draw_Window::GetPosition (Standard_Integer &thePosX,
                               Standard_Integer &thePosY)
{
  NSRect aWindowRect = [myWindow frame];
  thePosX = aWindowRect.origin.x;
  thePosY = getScreenBottom() - aWindowRect.origin.y - aWindowRect.size.height;
}

//=======================================================================
//function : HeightWin
//purpose  :
//=======================================================================
Standard_Integer Draw_Window::HeightWin() const
{
  NSRect aViewBounds = [myView bounds];
  return aViewBounds.size.height;
}

//=======================================================================
//function : WidthWin
//purpose  :
//=======================================================================
Standard_Integer Draw_Window::WidthWin() const
{
  NSRect aViewBounds = [myView bounds];
  return aViewBounds.size.width;
}

//=======================================================================
//function : SetTitle
//purpose  :
//=======================================================================
void Draw_Window::SetTitle (Standard_CString theTitle)
{
  NSString* aTitleNs = [[NSString alloc] initWithUTF8String: theTitle];
  [myWindow setTitle: aTitleNs];
  [aTitleNs release];
}

//=======================================================================
//function : GetTitle
//purpose  :
//=======================================================================
Standard_CString Draw_Window::GetTitle()
{
  Standard_CString aTitle = [[myWindow title] UTF8String];
  return aTitle;
}

//=======================================================================
//function :DefineColor
//purpose  :
//=======================================================================
Standard_Boolean Draw_Window::DefineColor (const Standard_Integer&, Standard_CString)
{
  return Standard_True; // unused
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

  if (myWindow != NULL)
  {
    [myWindow orderFront: NULL];
  }
}

//=======================================================================
//function : Hide
//purpose  :
//=======================================================================
void Draw_Window::Hide()
{
  if (myWindow != NULL)
  {
    [myWindow orderOut: NULL];
  }
}

//=======================================================================
//function : Destroy
//purpose  :
//=======================================================================
void Draw_Window::Destroy()
{  
  if (myWindow != NULL)
  { 
    [myWindow release];
    myWindow = NULL;
  }

  if (myView != NULL)
  {
    [myView release];
    myView = NULL;
  }

  if (myImageBuffer != NULL)
  {
    [myImageBuffer release];
    myImageBuffer = NULL;
  }
}

//=======================================================================
//function : Clear
//purpose  :
//=======================================================================
void Draw_Window::Clear()
{
  [myImageBuffer lockFocus];
  [[NSColor blackColor] set];
  NSRect anImageBounds = NSMakeRect (0.0, 0.0, myImageBuffer.size.width, myImageBuffer.size.height);
  NSRectFill (anImageBounds);
  [myImageBuffer unlockFocus];

  if (!myUseBuffer)
  {
    [myView redraw];
  }
}

//=======================================================================
//function : Flush
//purpose  :
//=======================================================================
void Draw_Window::Flush()
{
  //
}

//=======================================================================
//function : DrawString
//purpose  :
//=======================================================================
void Draw_Window::DrawString (const Standard_Integer& theXLeft, const Standard_Integer& theYTop, char* theText)
{
  Cocoa_LocalPool aLocalPool;

  NSString* aTextNs = [[[NSString alloc] initWithUTF8String: theText] autorelease];
  NSColor*  aColor  = [NSColor colorWithDeviceRed: Draw_RGBColorsArray[myCurrentColor][0]
                                            green: Draw_RGBColorsArray[myCurrentColor][1]
                                             blue: Draw_RGBColorsArray[myCurrentColor][2]
                                            alpha: 1.0f];
  NSDictionary* anAttributes = [[[NSDictionary alloc] initWithObjectsAndKeys: aColor, NSForegroundColorAttributeName, nil] autorelease];

  [myImageBuffer lockFocus];
  [aTextNs drawAtPoint: NSMakePoint (theXLeft, myImageBuffer.size.height - theYTop) withAttributes: anAttributes];
  [myImageBuffer unlockFocus];

  if (!myUseBuffer)
  {
    [myView redraw];
  }
}

//=======================================================================
//function : DrawSegments
//purpose  :
//=======================================================================
void Draw_Window::DrawSegments (Segment *theSegment, const Standard_Integer& theNumberOfElements)
{
  Cocoa_LocalPool aLocalPool;

  NSBezierPath* aPath = [[[NSBezierPath alloc] init] autorelease];

  NSImage* anImage;
  Standard_Integer anIter = 0;
  
  if (Draw_IsInZoomingMode)
  {
    // workaround for rectangle drawing when zooming
    anImage = [[myImageBuffer copy] autorelease];
    anIter  = 4;
  }
  else
  {
    anImage = myImageBuffer;
  }


  for (; anIter < theNumberOfElements; anIter++)
  {
    NSPoint aPoint = NSMakePoint (theSegment[anIter].myXStart, myImageBuffer.size.height - theSegment[anIter].myYStart);
    [aPath moveToPoint: aPoint];
    aPoint = NSMakePoint (theSegment[anIter].myXEnd, myImageBuffer.size.height - theSegment[anIter].myYEnd);
    [aPath lineToPoint: aPoint];
  }

  [anImage lockFocus];
  NSColor* aColor = [NSColor colorWithDeviceRed: Draw_RGBColorsArray[myCurrentColor][0]
                                          green: Draw_RGBColorsArray[myCurrentColor][1]
                                           blue: Draw_RGBColorsArray[myCurrentColor][2]
                                          alpha: 1.0f];
  [aColor set];
  [aPath stroke];
  [anImage unlockFocus];

  if (!myUseBuffer)
  {
    [myView setImage: anImage];
    [myView redraw];
  }
  
  Draw_IsInZoomingMode = Standard_False;
}

//=======================================================================
//function : Redraw
//purpose  :
//=======================================================================
void Draw_Window::Redraw()
{
  if (myUseBuffer)
  {
    [myView redraw];
  }
}

//=======================================================================
//function : SetColor
//purpose  :
//=======================================================================
void Draw_Window::SetColor (const Standard_Integer& theColor)
{
  myCurrentColor = theColor;
}

//=======================================================================
//function : SetMode
//purpose  :
//=======================================================================
void Draw_Window::SetMode (const Standard_Integer& theMode)
{
  //
}

//=======================================================================
//function : Save
//purpose  :
//=======================================================================
Standard_Boolean Draw_Window::Save (Standard_CString theFileName) const
{
  Cocoa_LocalPool aLocalPool;

  NSString* aFileName = [[[NSString alloc] initWithUTF8String: theFileName] autorelease];
  NSString* aFileExtension = [[aFileName pathExtension] lowercaseString];

  NSDictionary* aFileTypeDict = [NSDictionary dictionaryWithObjectsAndKeys:
                                  [NSNumber numberWithInt: NSPNGFileType],  @"png",
                                  [NSNumber numberWithInt: NSBMPFileType],  @"bmp",
                                  [NSNumber numberWithInt: NSJPEGFileType], @"jpg",
                                  [NSNumber numberWithInt: NSGIFFileType],  @"gif",
                                  nil];

  NSBitmapImageFileType aFileType;

  if ([aFileTypeDict valueForKey: aFileExtension] != nil)
  {
    aFileType = [[aFileTypeDict valueForKey: aFileExtension] intValue];
  }
  else
  {
    return Standard_False; // unsupported image extension
  }

  NSBitmapImageRep* anImageRep = [NSBitmapImageRep imageRepWithData: [myImageBuffer TIFFRepresentation]];

  NSData* aData = [anImageRep representationUsingType: aFileType 
                                           properties: nil];

  Standard_Boolean isSuccess = [aData writeToFile: aFileName
                                       atomically: NO];

  return isSuccess;
}

Standard_Boolean Draw_Window::IsEqualWindows (const Standard_Integer& theWindowNumber)
{
  return ([myWindow windowNumber] == theWindowNumber);
}

void GetNextEvent (Standard_Boolean  theWait,
                   Standard_Integer& theWindowNumber,
                   Standard_Integer& theX,
                   Standard_Integer& theY,
                   Standard_Integer& theButton)
{
  Cocoa_LocalPool aLocalPool;

  unsigned int anEventMatchMask = NSLeftMouseDownMask | NSRightMouseDownMask;

  if (!theWait)
  {
    anEventMatchMask = anEventMatchMask | NSMouseMovedMask | NSLeftMouseDraggedMask;
    Draw_IsInZoomingMode = Standard_True;
  }

  NSEvent* anEvent = [NSApp nextEventMatchingMask: anEventMatchMask
                                        untilDate: [NSDate distantFuture]
                                           inMode: NSEventTrackingRunLoopMode
                                          dequeue: YES];

  NSWindow* aWindow = [anEvent window];
  NSView*   aView   = [aWindow contentView];
  theWindowNumber   = [aWindow windowNumber];

  NSPoint aMouseLoc = [aView convertPoint: [anEvent locationInWindow] fromView: nil];
  NSRect  aBounds   = [aView bounds];

  theX = Standard_Integer (aMouseLoc.x);
  theY = Standard_Integer (aMouseLoc.y);

  NSEventType anEventType = [anEvent type];

  if (anEventType == NSLeftMouseDown)
  {
    theButton = 1;
  }
  else if (anEventType == NSRightMouseDown)
  {
    theButton = 3;
  }
  else if ((anEventType == NSMouseMoved || anEventType == NSLeftMouseDragged) && !theWait)
  {
    theButton = 0;
  }
}
#endif // __APPLE__
