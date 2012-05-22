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

#include <OSD_DirectoryIterator.ixx>
#include <OSD_WhoAmI.hxx>

#include <stdio.h>

#ifdef	HAVE_DIRENT_H
# include <dirent.h>
#endif

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif

//const OSD_WhoAmI Iam = OSD_WDirectoryIterator;

OSD_DirectoryIterator::OSD_DirectoryIterator() {

 myDescr = NULL ;
}

OSD_DirectoryIterator::OSD_DirectoryIterator(const OSD_Path& where,
                                             const TCollection_AsciiString& Mask){
 myDescr = NULL ;
 Initialize(where, Mask) ;
}

// For Windows NT compatibility -----------
void OSD_DirectoryIterator :: Destroy () {}
//-----------------------------------------

void OSD_DirectoryIterator::Initialize(const OSD_Path& where,
                                   const TCollection_AsciiString& Mask){

 myFlag = Standard_False;
 where.SystemName(myPlace);
 if (myPlace.Length()==0) myPlace = ".";
 myMask = Mask;
 if (myDescr) {
   closedir((DIR *)myDescr) ;
   myDescr = NULL ;
 }
 myInit = 1 ;
}

// Is there another directory entry ?

Standard_Boolean OSD_DirectoryIterator::More(){
 if (myInit) {
   myInit = 0 ;
   myDescr = (Standard_Address) opendir(myPlace.ToCString()); 
   if (myDescr) {            // LD : Si repertoire inaccessible retourner False
     myFlag = Standard_True;
     myInit = 0 ;
     Next();          // Now find first entry
   }
 }
 return (myFlag);
}

// Private :  See if directory name matches with a mask (like "*.c")
// LD : reecrit (original dans OSD_FileIterator.cxx)


static int strcmp_joker(const char *Mask,const char *Name)
{
  const char *p, *s ;

  for(p = Mask,s = Name ; *p && *p != '*' ; p++,s++)
    if (*p != *s) return 0 ;
  if (!*p) return !(*s) ;
  while (*p == '*') p++ ;
  if (!*p) return 1 ;
  for (;*s; s++)
    if (strcmp_joker(p,s)) return 1 ;
  return 0 ;
}

// Find next directory entry in current directory

void OSD_DirectoryIterator::Next(){
int again = 1;
struct stat stat_buf;
char full_name[255];

 myFlag = 0;   // Initialize to nothing found

 do{
    myEntry = readdir((DIR *)myDescr);
   
    if (!myEntry){   // No file found
     myEntry = NULL;              // Keep pointer clean
     myFlag = Standard_False;   // No more files/directory
     closedir((DIR *)myDescr) ;       // so close directory
     myDescr = NULL;
     again = 0;
    }
    else {
//     if (!strcmp(entry->d_name,".")) continue;     LD : on prend ces 
//     if (!strcmp(entry->d_name,"..")) continue;         2 directories.

     // Is it a directory ?

     sprintf(full_name,"%s/%s",myPlace.ToCString(),
	     ((struct dirent *)myEntry)->d_name);		 // LD debug
     stat(full_name, &stat_buf);
     if (S_ISDIR(stat_buf.st_mode))   // Ensure me it's not a file
      if (strcmp_joker(myMask.ToCString(), ((struct dirent *)myEntry)->d_name)){
							 // Does it follow mask ?
       myFlag = Standard_True;
       again = 0;
     }
    }

 } while (again);

}


// Get Name of selected directory

OSD_Directory OSD_DirectoryIterator::Values(){
OSD_Path thisvalue;
TCollection_AsciiString Name;
TCollection_AsciiString Ext;
Standard_Integer position;

 if (myEntry) Name = ((struct dirent *)myEntry)->d_name ;

 position = Name.Search(".");

 if (position != -1){
  Ext = Name.Split(position - 1) ;   // Debug LD
//  Ext.Remove(1,position);
//  Name.Remove( position,Ext.Length()+1);
 }

 thisvalue.SetValues("", "", "", "", "", Name,Ext);
 TheIterator.SetPath (thisvalue);

 return (TheIterator);
}


void OSD_DirectoryIterator::Reset(){
 myError.Reset();
}

Standard_Boolean OSD_DirectoryIterator::Failed()const{
 return( myError.Failed());
}

void OSD_DirectoryIterator::Perror() {
 myError.Perror();
}


Standard_Integer OSD_DirectoryIterator::Error()const{
 return( myError.Error());
}

#else

//------------------------------------------------------------------------
//-------------------  Windows NT sources for OSD_DirectoryIterator ------
//------------------------------------------------------------------------


#define STRICT
#include <windows.h>

#include <OSD_DirectoryIterator.ixx>

#define _FD (  ( PWIN32_FIND_DATA )myData  )

void _osd_wnt_set_error ( OSD_Error&, OSD_WhoAmI, ... );

OSD_DirectoryIterator :: OSD_DirectoryIterator (
                          const OSD_Path&                where,
                          const TCollection_AsciiString& Mask
                         ) {

 myFlag   = Standard_False;
 myHandle = ( Standard_Integer )INVALID_HANDLE_VALUE;

 where.SystemName ( myPlace );

 if (  myPlace.Length () == 0  ) myPlace = TEXT( "." );

 myMask = Mask;
 myData = NULL;

}  // end constructor

void OSD_DirectoryIterator :: Destroy () {

 if ( myData != NULL ) HeapFree (  GetProcessHeap (), 0, myData  );

 if (  myHandle != ( Standard_Integer )INVALID_HANDLE_VALUE  )

  FindClose (  ( HANDLE )myHandle  );

}  // end  OSD_DirectoryIterator :: Destroy

Standard_Boolean OSD_DirectoryIterator :: More () {

 if (  myHandle == ( Standard_Integer )INVALID_HANDLE_VALUE  ) {
 
  TCollection_AsciiString wc = myPlace + TEXT( "/" ) + myMask;

  myData = HeapAlloc (
            GetProcessHeap (), HEAP_GENERATE_EXCEPTIONS, sizeof ( WIN32_FIND_DATA )
           );

  myHandle = ( Standard_Integer )FindFirstFile (
                                  wc.ToCString (), ( PWIN32_FIND_DATA )myData
                                 );

  if (  myHandle == ( Standard_Integer )INVALID_HANDLE_VALUE  )
  
   _osd_wnt_set_error ( myError, OSD_WDirectoryIterator );
  
  else {
  
   myFlag      = Standard_True;
   myFirstCall = Standard_True;

   Next ();

  }  // end else
  
 } else if ( !myFlag ) {
 
  FindClose (  ( HANDLE )myHandle  );
  myHandle = ( Standard_Integer )INVALID_HANDLE_VALUE;
 
 }  // end if

 return myFlag;

}  // end OSD_DirectoryIterator :: More

void OSD_DirectoryIterator :: Next () {

 if (  myFirstCall && !( _FD -> dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )  ||
       !myFirstCall
 ) {
 
  do {
  
   if (   !FindNextFile (  ( HANDLE )myHandle, _FD  )   ) {
   
    myFlag = Standard_False;

    break;
   
   }  // end if
  
  } while (  !( _FD -> dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )  );
 
 }  // end if
 
 myFirstCall = Standard_False;

}  // end  OSD_DirectoryIterator :: Next

OSD_Directory OSD_DirectoryIterator :: Values () {

 TheIterator.SetPath (   OSD_Path ( _FD -> cFileName  )   );

 return TheIterator;

}  // end  OSD_DirectoryIterator :: Values

Standard_Boolean OSD_DirectoryIterator :: Failed () const {

 return myError.Failed ();

}  // end OSD_DirectoryIterator :: Failed

void OSD_DirectoryIterator :: Reset () {

 myError.Reset ();

}  // end OSD_DirectoryIterator :: Reset

void OSD_DirectoryIterator :: Perror () {

 myError.Perror ();

}  // end OSD_DirectoryIterator :: Perror

Standard_Integer OSD_DirectoryIterator :: Error () const {

 return myError.Error ();

}  // end OSD_DirectoryIterator :: Error

// For compatibility with UNIX version
OSD_DirectoryIterator::OSD_DirectoryIterator() {}

void OSD_DirectoryIterator::Initialize(
                             const OSD_Path& where,
                             const TCollection_AsciiString& Mask){}

#endif
