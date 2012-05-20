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


#ifdef HAVE_CONFIG_H
# include <oce-config.h>
#endif

#ifndef WNT

#include <OSD_LoadMode.hxx>
#include <OSD_SharedLibrary.ixx>
#include <OSD_Function.hxx>

#include <stdio.h>

#ifdef HAVE_MALLOC_H
# include <malloc.h>
#endif

#ifdef __some_crappy_system__
/*
 * Values for 'mode' argument in dlopen().
 *
*/
#define RTLD_LAZY		1
#define RTLD_NOW	        2
/*
 * Interface to rld via unsupported __rld_libdl_interface() call.
 *
 */
#define _LIBDL_RLD_DLOPEN	1
#define _LIBDL_RLD_DLCLOSE	2
#define _LIBDL_RLD_DLSYM	3
#define _LIBDL_RLD_DLERROR	4
extern "C" {void	*dlopen(char *path, int mode);}
extern "C" {void*   dlsym   (       void*  handle,char* name);}
extern "C" {int     dlclose (       void  *handle  );}
extern "C" {void    *dlerror (void);}
#endif

#ifdef HAVE_DLFCN_H
# include <dlfcn.h>
#endif

#ifdef HAVE_DL_H
# include <dl.h>
#endif

extern "C" {size_t  strlen  (const  char*  s      );}


#define BAD(X)  ((X) == NULL)

// ----------------------------------------------------------------
//
// Create and initialize a shared library object to NULL
//
// ----------------------------------------------------------------
OSD_SharedLibrary::OSD_SharedLibrary():myHandle(NULL),myName(NULL){
}
// ----------------------------------------------------------------
//
// Create and initialize a shared library object to the
// name given as argument
//
// ----------------------------------------------------------------
OSD_SharedLibrary::OSD_SharedLibrary(const Standard_CString aName):myHandle(NULL) 
{
  if (aName != NULL) {
    myName = new char [(strlen (aName) + 1 )];
    strcpy (myName,aName);
  }
}
// ----------------------------------------------------------------
//
// Name: Returns the shared library name
//
// ----------------------------------------------------------------
Standard_CString  OSD_SharedLibrary::Name() const {
  return myName; 
}
// ----------------------------------------------------------------
//
// SetName: Sets a name to a shared library object
//
// ----------------------------------------------------------------
void  OSD_SharedLibrary::SetName(const Standard_CString aName)  {
  if (aName != NULL) {
    myName = new char [(strlen (aName) + 1 )];
    strcpy (myName,aName);
  }
}
// ----------------------------------------------------------------
//
// DlOpen:   The dlopen function provides an interface to the dynamic 
// library loader to allow shared libraries to be loaded and called at
// runtime.  
// The dlopen function attempts to load filename, in the address space 
// of the process, resolving symbols as appropriate.  Any libraries that      
// filename depends upon are also loaded.
//
// If mode is RTLD_LAZY, then the runtime loader does symbol resolution 
// only as needed.  Typically, this means that the first call	
// to a function in the newly loaded library will cause the resolution 
// of the address of that function to occur.  
//
// If mode is RTLD_NOW, then the runtime loader must do all
// symbol binding during the dlopen call.  
// The dlopen function returns a handle that is used by dlsym or 
// dlclose call.  If there is an error, a NULLpointer is returned.
//
// If a NULL filename is specified, dlopen returns a handle for the main      
// executable, which allows access to dynamic symbols in the running program.
//
// ----------------------------------------------------------------
Standard_Boolean  OSD_SharedLibrary::DlOpen(const OSD_LoadMode aMode ) {

#ifdef HAVE_DL_H
if (aMode == OSD_RTLD_LAZY){
//  myHandle = cxxshl_load(myName, BIND_FIRST | BIND_TOGETHER | BIND_DEFERRED | BIND_VERBOSE | DYNAMIC_PATH, 0L);
  myHandle = shl_load(myName, BIND_FIRST | BIND_TOGETHER | BIND_DEFERRED | BIND_VERBOSE | DYNAMIC_PATH, 0L);
}
else if (aMode == OSD_RTLD_NOW){
//  myHandle = cxxshl_load(myName, BIND_FIRST | BIND_TOGETHER | BIND_IMMEDIATE | BIND_VERBOSE | DYNAMIC_PATH, 0L);
  myHandle = shl_load(myName, BIND_FIRST | BIND_TOGETHER | BIND_IMMEDIATE | BIND_VERBOSE | DYNAMIC_PATH, 0L);

}
#else
if (aMode == OSD_RTLD_LAZY){
  myHandle = dlopen (myName,RTLD_LAZY);
}
else if (aMode == OSD_RTLD_NOW){
  myHandle = dlopen (myName,RTLD_NOW);
}
#endif

if (!BAD(myHandle)){
  return Standard_True;
 }
else {
  return Standard_False;
 }
}
// ----------------------------------------------------------------
//
// DlSymb: The dlsym function returns the address of the	
// symbol name found in the shared library corresponding to handle.  
// If the symbol is not	found, a NULL
// pointer is returned.
//
// ----------------------------------------------------------------
OSD_Function  OSD_SharedLibrary::DlSymb(const Standard_CString aName )const{

#ifndef HAVE_DL_H
void (*fp)();
fp =  (void (*)()) dlsym (myHandle,aName);
if (!BAD(fp)){
  return (OSD_Function)fp;
 }
else {
  return (OSD_Function)NULL;
 }
#else
  void *adr_get = NULL;
//  shl_t handlesym=0 ;

  errno = 0 ;
  //  if (  shl_findsym( &handlesym,aName,TYPE_PROCEDURE,&adr_get) == -1 ) {
  if ( shl_findsym((shl_t *)&myHandle,aName,TYPE_PROCEDURE,&adr_get) == -1 ) {
    if ( errno != 0 )
      perror("OSD_SharedLibrary : shl_findsym perror : ") ;
    return (OSD_Function)NULL;
  }
  else return (OSD_Function) adr_get;
#endif

}
// ----------------------------------------------------------------
//
//DlClose: The dlclose function deallocates the address space for the library
//corresponding	to handle.  If any user	function continues to call a symbol
//resolved in the address space	of a library that has been since been deallo-
//cated	by dlclose, the	results	are undefined.
//
// ----------------------------------------------------------------
void OSD_SharedLibrary::DlClose()const{

#ifndef HAVE_DL_H
 dlclose(myHandle);
#else
 shl_unload((shl_t)myHandle);
#endif

}
// ----------------------------------------------------------------
//
// DlError:  returns a string	describing the last error that
// occurred from a call to dlopen, dlclose or dlsym.
//
// ----------------------------------------------------------------
Standard_CString OSD_SharedLibrary::DlError()const{
#ifndef HAVE_DL_H
return (char*) dlerror();
#else
perror("shl_load, shl_findsym, or shl_unload : perror : ") ;
return (char*) errno;
#endif
}
// ----------------------------------------------------------------------------
// Destroy
// ----------------------------------------------------------------------------
void OSD_SharedLibrary::Destroy() {
  if (myName != NULL) {
     delete [] myName;
     myName = NULL;
     myHandle = NULL;
  }
}

#else

//------------------------------------------------------------------------
//-------------------  Windows NT sources for OSD_SharedLibrary ----------
//------------------------------------------------------------------------

//it is important to define STRICT and enforce including <windows.h> before
//Standard_Macro.hxx undefines it and includes <windows.h> causing compilation errors
#ifndef STRICT
#define STRICT
#endif
#include <windows.h>

#include <OSD_SharedLibrary.ixx>

#include <OSD_Path.hxx>

#include <TCollection_AsciiString.hxx>


static DWORD              lastDLLError;
static Standard_Character errMsg[ 1024 ];

OSD_SharedLibrary :: OSD_SharedLibrary () {

 myHandle = NULL;
 myName   = NULL;

}  // end constructor ( 1 )

OSD_SharedLibrary :: OSD_SharedLibrary ( const Standard_CString aFilename ) {

 myHandle = NULL;
 myName   = NULL;

 SetName ( aFilename );

}  // end constructro ( 2 )

void OSD_SharedLibrary :: SetName ( const Standard_CString aName ) {

 OSD_Path                path ( aName );
 TCollection_AsciiString name ( aName );

 if ( myName != NULL )

  delete [] myName;

 myName = new Standard_Character[ strlen ( aName ) + 1 ];

 strcpy ( myName, aName );

 name = path.Name ();
 name.AssignCat (  path.Extension ()  );

 myHandle = GetModuleHandle (  name.ToCString ()  );

}  // end OSD_SharedLibrary :: SetName

Standard_CString OSD_SharedLibrary :: Name () const {

 return myName;

}  // end OSD_SharedLibrary :: Name

Standard_Boolean OSD_SharedLibrary :: DlOpen ( const OSD_LoadMode Mode ) {

 Standard_Boolean retVal = Standard_True;

 if (  (  myHandle ) == NULL &&
       (  myHandle = ( HINSTANCE )LoadLibraryEx (
                                   myName, NULL, LOAD_WITH_ALTERED_SEARCH_PATH
                                  )  ) == NULL
 ) {
 
  lastDLLError = GetLastError ();
  retVal       = Standard_False;
 
 }  // end if

 return retVal;

}  // end OSD_SharedLibrary :: DlOpen

OSD_Function OSD_SharedLibrary :: DlSymb ( const Standard_CString Name ) const {

 OSD_Function func = ( OSD_Function )GetProcAddress (  ( HMODULE )myHandle, Name  );

 if ( func == NULL ) {
#ifdef __BORLANDC__ //borland decorates exported C style routines with '_'
  Standard_Character* myAlternativeName = new Standard_Character[ strlen ( Name ) + 1 + 1 ];
  static Standard_Character* myAddition = "_";
  strcpy(myAlternativeName, myAddition);
  strcat(myAlternativeName, Name);
  func = ( OSD_Function )GetProcAddress (  ( HMODULE )myHandle, myAlternativeName  );
  delete [] myAlternativeName;
 if ( func == NULL )
#endif
  lastDLLError = GetLastError ();
 }

 return func;

}  // end OSD_SharedLibrary :: DlSymb

void OSD_SharedLibrary :: DlClose () const {

 FreeLibrary (  ( HMODULE )myHandle  );

}  // end OSD_SharedLibrary :: DlClose

Standard_CString OSD_SharedLibrary :: DlError () const {

 FormatMessage (
  FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
  0, lastDLLError, MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL ), errMsg, 1024, ( va_list* )&myName
 );

 return errMsg;

}  // end OSD_SharedLibrary :: DlError

void OSD_SharedLibrary :: Destroy () {

 if ( myName != NULL ) delete [] myName;

}  // end OSD_SharedLibrary :: Destroy

#endif
