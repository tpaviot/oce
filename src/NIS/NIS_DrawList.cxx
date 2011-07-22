// File:      NIS_DrawList.cxx
// Created:   09.07.07 21:46
// Author:    Alexander GRIGORIEV
// Copyright: Open Cascade 2007

#include <NIS_Drawer.hxx>
#include <NIS_View.hxx>

#ifdef WNT
#include <windows.h>
#endif
#include <GL/gl.h>

//=======================================================================
//function : NIS_DrawList()
//purpose  : Empty Constructor
//=======================================================================

NIS_DrawList::NIS_DrawList ()
{
#ifdef ARRAY_LISTS
  myListID = 0;
#else
  myListID[0] = 0;
  myListID[1] = 0;
  myListID[2] = 0;
  myListID[3] = 0;
  myListID[4] = 0;
#endif
  myIsUpdated[0] = Standard_True;
  myIsUpdated[1] = Standard_True;
  myIsUpdated[2] = Standard_True;
  myIsUpdated[3] = Standard_True;
  myIsUpdated[4] = Standard_True;
}

//=======================================================================
//function : NIS_DrawList()
//purpose  : Constructor
//=======================================================================

NIS_DrawList::NIS_DrawList (const Handle_NIS_View& theView)
  : myView      (theView)
{
#ifdef ARRAY_LISTS
  myListID = 0;
#else
  myListID[0] = 0;
  myListID[1] = 0;
  myListID[2] = 0;
  myListID[3] = 0;
  myListID[4] = 0;
#endif
  myIsUpdated[0] = Standard_True;
  myIsUpdated[1] = Standard_True;
  myIsUpdated[2] = Standard_True;
  myIsUpdated[3] = Standard_True;
  myIsUpdated[4] = Standard_True;
}

//=======================================================================
//function : ~NIS_DrawList
//purpose  : 
//=======================================================================

NIS_DrawList::~NIS_DrawList ()
{
  //if (myListID != 0)
    //glDeleteLists (myListID, 5);
}

//=======================================================================
//function : ClearListID
//purpose  : Set myListID to 0.
//=======================================================================

void NIS_DrawList::ClearListID (const Standard_Integer theType)
{
#ifndef ARRAY_LISTS
  if (theType >= 0) {
    // To be called only in Callback context (i.e. when GL context is active)
    if (myListID[theType] > 0) {
      glDeleteLists(myListID[theType], 1);
      myListID[theType] = 0;
    }
    myIsUpdated[theType] = Standard_False;
  }
#endif
}

//=======================================================================
//function : ClearListID
//purpose  : Set myListID to 0.
//=======================================================================

void NIS_DrawList::ClearListID (const Handle_NIS_View& theView)
{
#ifdef ARRAY_LISTS
  if (myListID > 0)
    myView->GetExListId().Add(myListID);
  myListID = 0;
#else
  NIS_View * pView = (myView.IsNull()) ?
    theView.operator->() : myView.operator->();
  if (pView) {
    if (myListID[0] > 0)
      pView->GetExListId().Add(myListID[0]);
    myListID[0] = 0;
    if (myListID[1] > 0)
      pView->GetExListId().Add(myListID[1]);
    myListID[1] = 0;
    if (myListID[2] > 0)
      pView->GetExListId().Add(myListID[2]);
    myListID[2] = 0;
    if (myListID[3] > 0)
      pView->GetExListId().Add(myListID[3]);
    myListID[3] = 0;
    if (myListID[4] > 0)
      pView->GetExListId().Add(myListID[4]);
    myListID[4] = 0;
  }

#endif
  myIsUpdated[0] = Standard_False;
  myIsUpdated[1] = Standard_False;
  myIsUpdated[2] = Standard_False;
  myIsUpdated[3] = Standard_False;
  myIsUpdated[4] = Standard_False;
}

//=======================================================================
//function : BeginPrepare
//purpose  : 
//=======================================================================

void NIS_DrawList::BeginPrepare (const Standard_Integer theType)
{
#ifdef ARRAY_LISTS
  if (myListID == 0)
    myListID = glGenLists(5);
#else
  if (GetListID(theType) == 0)
    myListID[theType] = glGenLists(1);
#endif
  glNewList (GetListID(theType), GL_COMPILE);
}

//=======================================================================
//function : EndPrepare
//purpose  : 
//=======================================================================

void NIS_DrawList::EndPrepare (const Standard_Integer theType)
{
  glEndList ();
  myIsUpdated[theType] = Standard_False;
}

//=======================================================================
//function : Call
//purpose  : 
//=======================================================================

void NIS_DrawList::Call (const Standard_Integer theType)
{
  glCallList (GetListID (theType));
}

//=======================================================================
//function : SetDynHilighted
//purpose  : 
//=======================================================================

Standard_Boolean NIS_DrawList::SetDynHilighted
                                (const Standard_Boolean              isHili,
                                 const Handle_NIS_InteractiveObject& theObj)
{
  Standard_Boolean aResult (Standard_False);
  NCollection_List<Handle_NIS_InteractiveObject>::Iterator anIt(myDynHilighted);
  for (; anIt.More(); anIt.Next())
    if (anIt.Value() == theObj)
      break;
  if (anIt.More()) {
    if (isHili == Standard_False) {
      myIsUpdated[NIS_Drawer::Draw_DynHilighted] = Standard_True;
      myDynHilighted.Remove (anIt);
      aResult = Standard_True;
    }
  } else
    if (isHili == Standard_True) {
      myIsUpdated[NIS_Drawer::Draw_DynHilighted] = Standard_True;
      myDynHilighted.Append (theObj);
      aResult = Standard_True;
    }
  return aResult;
}

//=======================================================================
//function : SetUpdated
//purpose  : 
//=======================================================================

void NIS_DrawList::SetUpdated (const Standard_Integer theType,
                               const Standard_Boolean theFlag)
{ 
  if (theFlag)
    SetUpdated(theType);
  else
    myIsUpdated [theType] = Standard_False;
}

//=======================================================================
//function : SetUpdated
//purpose  : 
//=======================================================================

void NIS_DrawList::SetUpdated (const Standard_Integer theType)
{
  myIsUpdated [theType] = Standard_True;
  if (theType == NIS_Drawer::Draw_Hilighted)
    myDynHilighted.Clear();
}
