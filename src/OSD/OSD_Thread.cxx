// Created on: 2006-04-12
// Created by: Andrey BETENEV
// Copyright (c) 2006-2012 OPEN CASCADE SAS
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


#include <OSD_Thread.ixx>

//=============================================
// OSD_Thread::OSD_Thread
//=============================================

OSD_Thread::OSD_Thread ()
  : myFunc(0), myThread(0), myThreadId(0), myPriority(0)
{}

//=============================================
// OSD_Thread::OSD_Thread
//=============================================

OSD_Thread::OSD_Thread (const OSD_ThreadFunction &func)
  : myFunc(func), myThread(0), myThreadId(0), myPriority(0)
{}

//=============================================
// OSD_Thread::OSD_Thread
//=============================================

OSD_Thread::OSD_Thread (const OSD_Thread &other)
  : myFunc(other.myFunc), myThread(0), myThreadId(0)
{
  Assign ( other );
}

//=============================================
// OSD_Thread::Assign
//=============================================

void OSD_Thread::Assign (const OSD_Thread &other)
{
  // copy function pointer 
  myFunc = other.myFunc;
  myPriority = other.myPriority;

#ifdef WNT

  // On Windows, close current handle 
  if ( myThread ) 
    CloseHandle ( myThread );
  myThread = 0;

  // and replace it by duplicate of the source handle 
  if ( other.myThread ) {
    HANDLE hProc = GetCurrentProcess(); // we are always within the same process
    DuplicateHandle ( hProc, other.myThread, hProc, &myThread,
		      0, TRUE, DUPLICATE_SAME_ACCESS );
  }

#else

  // On Unix/Linux, just copy the thread id
  myThread = other.myThread;

#endif  

  myThreadId = other.myThreadId;
}

//=============================================
// OSD_Thread::Destroy
//=============================================

void OSD_Thread::Destroy ()
{
#ifdef WNT

  // On Windows, close current handle 
  if ( myThread ) 
    CloseHandle ( myThread );

#else

  // On Unix/Linux, do nothing

#endif  

  myThread = 0;
  myThreadId = 0;
}

//=============================================
//function : SetPriority
//purpose  : Set the thread priority relative to the caller's priority
//=============================================

void OSD_Thread::SetPriority (const Standard_Integer thePriority)
{
  myPriority = thePriority;
#ifdef WNT
  if (myThread)
    SetThreadPriority (myThread, thePriority);
#endif
}

//=============================================
// OSD_Thread::SetFunction
//=============================================

void OSD_Thread::SetFunction (const OSD_ThreadFunction &func)
{
  // close current handle if any
  Destroy();
  myFunc = func;
}

//=============================================
// OSD_Thread::Run
//=============================================

#ifdef WNT
#include <malloc.h>
// On Windows the signature of the thread function differs from that on UNIX/Linux.
// As we use the same definition of the thread function on all platforms (POSIX-like),
// we need to introduce appropriate wrapper function on Windows.
struct WNTthread_data { void *data; OSD_ThreadFunction func; };
static DWORD WINAPI WNTthread_func (LPVOID data)
{
  WNTthread_data *adata = (WNTthread_data*)data;
  void* ret = adata->func ( adata->data );
  free ( adata );
  return (DWORD)ret;
}
#endif

Standard_Boolean OSD_Thread::Run (const Standard_Address data, 
#ifdef WNT
                                  const Standard_Integer WNTStackSize
#else
                                  const Standard_Integer
#endif
				  )
{
  if ( ! myFunc ) return Standard_False;

  myThreadId = 0;

#ifdef WNT

  // On Windows, close current handle if open
  if ( myThread ) 
    CloseHandle ( myThread );
  myThread = 0;

  // allocate intermediate data structure to pass both data parameter and address
  // of the real thread function to Windows thread wrapper function
  WNTthread_data *adata = (WNTthread_data*)malloc ( sizeof(WNTthread_data) );
  if ( ! adata ) return Standard_False;
  adata->data = data;
  adata->func = myFunc;

  // then try to create a new thread 
  
  myThread = CreateThread ( NULL, WNTStackSize, WNTthread_func,
                            adata, 0, &myThreadId );
  if ( myThread )
    SetThreadPriority (myThread, myPriority);
  else {
    memset ( adata, 0, sizeof(WNTthread_data) );
    free ( adata );
  }

#else

  // On Unix/Linux, create a new thread
  if ( pthread_create ( &myThread, 0, myFunc, data ) )
    myThread = 0;
  else myThreadId = myThread;

#endif  
  return myThread != 0;
}

//=============================================
// OSD_Thread::Detach
//=============================================

void OSD_Thread::Detach ()
{
#ifdef WNT

  // On Windows, close current handle 
  if ( myThread ) 
    CloseHandle ( myThread );

#else

  // On Unix/Linux, detach a thread
  if ( myThread ) 
    pthread_detach ( myThread );

#endif  

  myThread = 0;
  myThreadId = 0;
}

//=============================================
// OSD_Thread::Wait
//=============================================

Standard_Boolean OSD_Thread::Wait () const
{
  Standard_Address aRes = 0;
  return Wait ( aRes );
}

//=============================================
// OSD_Thread::Wait
//=============================================

Standard_Boolean OSD_Thread::Wait (Standard_Address &result) const
{
  // check that thread handle is not null
  result = 0;
  if ( ! myThread ) 
    return Standard_False;

#ifdef WNT

  // On Windows, wait for the thread handle to be signaled
  if ( WaitForSingleObject ( myThread, INFINITE ) != WAIT_OBJECT_0 ) 
    return Standard_False;

  // and convert result of the thread execution to Standard_Address
  DWORD anExitCode;
  if ( GetExitCodeThread ( myThread, &anExitCode ) )
    result = (Standard_Address)anExitCode;
  return Standard_True;

#else

  // On Unix/Linux, join the thread
  return ! pthread_join ( myThread, &result );

#endif  
}

//=============================================
// OSD_Thread::Wait
//=============================================

Standard_Boolean OSD_Thread::Wait (const Standard_Integer time, Standard_Address &result) const
{
  // check that thread handle is not null
  result = 0;
  if ( ! myThread ) 
    return Standard_False;

#ifdef WNT

  // On Windows, wait for the thread handle to be signaled
  DWORD ret = WaitForSingleObject ( myThread, time );
  if (ret == WAIT_OBJECT_0)
  {
    DWORD anExitCode;
    if ( GetExitCodeThread ( myThread, &anExitCode ) )
      result = (Standard_Address)anExitCode;
    return Standard_True;
  }
  else if (ret == WAIT_TIMEOUT)
  {
    return Standard_False;
  }

  return Standard_False;

#else

  // On Unix/Linux, join the thread
  return ! pthread_join ( myThread, &result );

#endif  
}

//=============================================
// OSD_Thread::GetId
//=============================================

Standard_ThreadId OSD_Thread::GetId () const
{
  return myThreadId;
}

//=============================================
// OSD_Thread::Current
//=============================================

Standard_ThreadId OSD_Thread::Current () 
{
#ifdef WNT
  return GetCurrentThreadId();
#else
  return pthread_self();
#endif  
}

