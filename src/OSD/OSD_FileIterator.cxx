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

#include <OSD_FileIterator.ixx>
#include <OSD_WhoAmI.hxx>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef	HAVE_DIRENT_H
# include <dirent.h>
# define NAMLEN(dirent) strlen((dirent)->d_name)
# ifdef VMS
extern char *vmsify PARAMS ((char *name, int type));
# endif
#else
# define dirent direct
# define NAMLEN(dirent) (dirent)->d_namlen
# ifdef HAVE_SYS_NDIR_H
#  include <sys/ndir.h>
# endif
# ifdef HAVE_SYS_DIR_H
#  include <sys/dir.h>
# endif
# ifdef HAVE_NDIR_H
#  include <ndir.h>
# endif
# ifdef HAVE_VMSDIR_H
#  include "vmsdir.h"
# endif /* HAVE_VMSDIR_H */
#endif

/* In GNU systems, <dirent.h> defines this macro for us.  */
#ifdef _D_NAMLEN
# undef NAMLEN
# define NAMLEN(d) _D_NAMLEN(d)
#endif

#if (defined (POSIX) || defined (VMS) || defined (WINDOWS32)) && !defined (__GNU_LIBRARY__)
/* Posix does not require that the d_ino field be present, and some
   systems do not provide it. */
# define REAL_DIR_ENTRY(dp) 1
# define FAKE_DIR_ENTRY(dp)
#else
# define REAL_DIR_ENTRY(dp) (dp->d_ino != 0)
# define FAKE_DIR_ENTRY(dp) (dp->d_ino = 1)
#endif /* POSIX */

//const OSD_WhoAmI Iam = OSD_WFileIterator;


OSD_FileIterator::OSD_FileIterator() {
 myDescr = NULL ;
}

OSD_FileIterator::OSD_FileIterator(const OSD_Path& where,
                                   const TCollection_AsciiString& Mask){
 myDescr = NULL ;
 Initialize(where, Mask) ;
}

// For Windows NT compatibility
void OSD_FileIterator :: Destroy () {}

void OSD_FileIterator::Initialize(const OSD_Path& where,
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

// Is there another file entry ?

Standard_Boolean OSD_FileIterator::More(){
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

// Private :  See if file name matches with a mask (like "*.c")

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

#if 0
    // LD : ancienne version.

#define TRUE  1
#define FALSE 0
#define NO_MASK '*'

static int strcmp_joker(char *fileMask,char *fileName)
{
    char *sauve_fileMask,*sauve_fileName;
    int compare_result;
    int beginning = 1;   // 0 if first character is a joker, otherwise 1

    while (*fileName) {        // Test end of AsciiString

     if (*fileMask == NO_MASK) {
      beginning = 0;

      while(*fileMask == NO_MASK) fileMask++;

      if (*fileMask) {
       while(*fileName && 
             *fileName != *fileMask) 
        fileName++;

       sauve_fileMask = fileMask;  // Save strings
       sauve_fileName = fileName;
      }
      else return(0);   // fileMask ends with a joker

     }
     else { // Compare two characters
      compare_result = *fileMask++ - *fileName++;

      if (compare_result != 0) 
       if (beginning) 
        return (compare_result); /* 1ere chaine pas de joker au debut */
       else {  // Look ahead for same string
        fileMask = sauve_fileMask;
        fileName = ++sauve_fileName;
        while(*fileName && 
              *fileName != *fileMask)
         fileName++;
        sauve_fileName = fileName;
       }

    }    

   }    

   while(*fileMask == NO_MASK) fileMask++;
   return(*fileMask - *fileName);
}
#endif

// Find next file entry in current directory

void OSD_FileIterator::Next(){
int again = 1;
struct stat stat_buf;
char full_name[255];

 myFlag = 0;   // Initialize to nothing found

 do {
    myEntry = readdir((DIR *)myDescr);
   
    if (!myEntry){   // No file found
     myEntry = NULL;              // Keep pointer clean
     myFlag = Standard_False;   // No more files/directory
     closedir((DIR *)myDescr) ;       // so close directory
     myDescr = NULL;
     again = 0;
    }
    else {
     if (!strcmp(((struct dirent *)myEntry)->d_name,".")) continue;
     if (!strcmp(((struct dirent *)myEntry)->d_name,"..")) continue;

     // Is it a file ?

     sprintf(full_name,"%s/%s",myPlace.ToCString(),
	     ((struct dirent *)myEntry)->d_name);		 // LD debug
#ifdef DEBUG
     cout << "Place : " << myPlace << endl;
     cout << "FName : " << full_name << endl;
#endif
     stat(full_name, &stat_buf);
     if (S_ISREG(stat_buf.st_mode))   // LD : Ensure me it's a regular file
      if (strcmp_joker(myMask.ToCString(), ((struct dirent *)myEntry)->d_name)){
							 // Does it follow mask ?
       myFlag = Standard_True;
       again = 0;
      }
    }

 } while (again);

}

// Get Name of selected file

OSD_File OSD_FileIterator::Values(){
OSD_Path thisvalue;
TCollection_AsciiString Name;
TCollection_AsciiString Ext;
Standard_Integer position;

 if (myEntry) Name = ((struct dirent *)myEntry)->d_name ;

 position = Name.Search(".");

 if (position != -1){
  Ext = Name;
  Ext.Remove(1,position-1);
  Name.Remove( position,Ext.Length());
 }

 thisvalue.SetValues("", "", "", "", "", Name,Ext); 
 TheIterator.SetPath (thisvalue);

 return (TheIterator);
}


void OSD_FileIterator::Reset(){
 myError.Reset();
}

Standard_Boolean OSD_FileIterator::Failed()const{
 return( myError.Failed());
}

void OSD_FileIterator::Perror() {
 myError.Perror();
}


Standard_Integer OSD_FileIterator::Error()const{
 return( myError.Error());
}

#else

//------------------------------------------------------------------------
//-------------------  Windows NT sources for OSD_FileIterator -----------
//------------------------------------------------------------------------

#define STRICT
#include <windows.h>

#include <OSD_FileIterator.ixx>

#define _FD (  ( PWIN32_FIND_DATA )myData  )

void _osd_wnt_set_error ( OSD_Error&, OSD_WhoAmI, ... );

OSD_FileIterator :: OSD_FileIterator (
                     const OSD_Path&                where,
                     const TCollection_AsciiString& Mask
                    ) {

 myFlag   = Standard_False;
 myHandle = ( intptr_t )INVALID_HANDLE_VALUE;

 where.SystemName ( myPlace );

 if (  myPlace.Length () == 0  ) myPlace = TEXT( "." );

 myMask = Mask;
 myData = NULL;

}  // end constructor

void OSD_FileIterator :: Destroy () {

 if ( myData != NULL ) HeapFree (  GetProcessHeap (), 0, myData  );

 if (  myHandle != ( intptr_t )INVALID_HANDLE_VALUE  )

  FindClose (  ( HANDLE )myHandle  );

}  // end  OSD_DirectoryIterator :: Destroy

Standard_Boolean OSD_FileIterator :: More () {

 if (  myHandle == ( intptr_t )INVALID_HANDLE_VALUE  ) {
 
  TCollection_AsciiString wc = myPlace + TEXT( "/" ) + myMask;

  myData = HeapAlloc (
            GetProcessHeap (), HEAP_GENERATE_EXCEPTIONS, sizeof ( WIN32_FIND_DATA )
           );

  myHandle = ( intptr_t )FindFirstFile (
                                  wc.ToCString (), ( PWIN32_FIND_DATA )myData
                                 );

  if (  myHandle == ( intptr_t )INVALID_HANDLE_VALUE  )
  
   _osd_wnt_set_error ( myError, OSD_WDirectoryIterator );
  
  else {
  
   myFlag      = Standard_True;
   myFirstCall = Standard_True;

   Next ();

  }  // end else
  
 } else if ( !myFlag ) {
 
  FindClose (  ( HANDLE )myHandle  );
  myHandle = ( intptr_t )INVALID_HANDLE_VALUE;
 
 }  // end if

 return myFlag;

}  // end OSD_FileIterator :: More

void OSD_FileIterator :: Next () {

 if (  myFirstCall && ( _FD -> dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )  ||
       !myFirstCall
 ) {
 
  do {
  
   if (   !FindNextFile (  ( HANDLE )myHandle, _FD  )   ) {
   
    myFlag = Standard_False;

    break;
   
   }  // end if
  
  } while (  ( _FD -> dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )  );
 
 }  // end if
 
 myFirstCall = Standard_False;

}  // end OSD_FileIterator :: Next

OSD_File OSD_FileIterator :: Values () {

 TheIterator.SetPath (   OSD_Path ( _FD -> cFileName  )   );

 return TheIterator;

}  // end OSD_FileIterator :: Values

Standard_Boolean OSD_FileIterator :: Failed () const {

 return myError.Failed ();

}  // end OSD_FileIterator :: Failed

void OSD_FileIterator :: Reset () {

 myError.Reset ();

}  // end OSD_FileIterator :: Reset

void OSD_FileIterator :: Perror () {

 myError.Perror ();

}  // end OSD_FileIterator :: Perror

Standard_Integer OSD_FileIterator :: Error () const {

 return myError.Error ();

}  // end  OSD_FileIterator :: Error

// For compatibility with UNIX version
OSD_FileIterator::OSD_FileIterator() {}

void OSD_FileIterator::Initialize(
                       const OSD_Path& where,
                       const TCollection_AsciiString& Mask){}
 
#endif
