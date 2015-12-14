// Copyright (c) 1998-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

//------------------------------------------------------------------------
//                    UNIX Part
//------------------------------------------------------------------------

#ifndef _WIN32

#include <Standard_ProgramError.hxx>
#include <OSD_OSDError.hxx>
#include <OSD_WhoAmI.hxx>
#include <OSD_FromWhere.hxx>
#include <OSD_File.ixx>

#include <Standard_PCharacter.hxx>

const OSD_WhoAmI Iam = OSD_WFile;

#if defined (sun) || defined(SOLARIS)
#define POSIX
#else             
#define SYSV
#endif

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define NEWLINE '\10';

// ---------------------------------------------------------------------
// Create an empty file object
// ---------------------------------------------------------------------

OSD_File::OSD_File():OSD_FileNode()
{
 ImperativeFlag = Standard_False;
 myLock         = OSD_NoLock;
 myIO           = 0;
 myMode         = OSD_ReadWrite;
 myFILE         = (Standard_Address) NULL;
 myFileChannel  = -1;
 myFileHandle   = 0;
}

// ---------------------------------------------------------------------
// Create and initialize a file object
// ---------------------------------------------------------------------

OSD_File::OSD_File(const OSD_Path& Name):OSD_FileNode(Name)
{
 ImperativeFlag = Standard_False;
 myLock         = OSD_NoLock;
 myIO           = 0;
 myMode         = OSD_ReadWrite;
 myFILE         = (Standard_Address) NULL;
 myFileChannel  = -1;
 myFileHandle   = 0;
}

// protect against occasional use of myFileHande in Linux code
#define myFileHandle myFileHandle_is_only_for_Windows

// ---------------------------------------------------------------------
// Build a file if it doesn't exist or create again if it already exists
// ---------------------------------------------------------------------

void OSD_File::Build(const OSD_OpenMode Mode,
                     const OSD_Protection& Protect){
 
 Standard_Integer internal_prot;
 Standard_Integer internal_mode = O_CREAT | O_TRUNC ;
 TCollection_AsciiString aBuffer;

 if (myPath.Name().Length()==0)
  Standard_ProgramError::Raise("OSD_File::Build : no name was given");

 if (myFileChannel != -1)
  Standard_ProgramError::Raise("OSD_File::Build : file is already open");


 myMode = Mode;

 internal_prot = Protect.Internal();

 const char* CMode = "r";

 switch (Mode){
  case OSD_ReadOnly:
   internal_mode |= O_RDONLY;
   CMode = "r";
   break;
  case OSD_WriteOnly:
   internal_mode |= O_WRONLY;
   CMode = "w";
   break;
  case OSD_ReadWrite:
   internal_mode |= O_RDWR;
   CMode = "w+";
   break;
 }

 myPath.SystemName( aBuffer ); 
 myFileChannel = open (aBuffer.ToCString(), internal_mode, internal_prot);
 if (myFileChannel >= 0) { 
   myFILE = fdopen (myFileChannel, CMode);
 }
 else
 /* Handle OPEN errors */

   myError.SetValue (errno, Iam, "Open");

}



// ---------------------------------------------------------------------
// Append to an existing file
// ---------------------------------------------------------------------

void  OSD_File::Append(const OSD_OpenMode Mode,
                       const OSD_Protection& Protect){

 Standard_Integer internal_prot;
 Standard_Integer internal_mode = O_APPEND;;
 TCollection_AsciiString aBuffer;

 if ( OSD_File::KindOfFile ( ) == OSD_DIRECTORY ) {
    Standard_ProgramError::Raise("OSD_File::Append : it is a directory");
 } 
 
 if (myPath.Name().Length()==0)
  Standard_ProgramError::Raise("OSD_File::Append : no name was given");

 if (myFileChannel != -1)
  Standard_ProgramError::Raise("OSD_File::Append : file is already open");

 internal_prot = Protect.Internal();
 myMode = Mode;
 const char* CMode = "r";

 switch (Mode){
  case OSD_ReadOnly:
   internal_mode |= O_RDONLY;
   CMode = "r";
   break;
  case OSD_WriteOnly:
   internal_mode |= O_WRONLY;
   CMode = "a";
   break;
  case OSD_ReadWrite:
   internal_mode |= O_RDWR;
   CMode = "a+";
   break;
 }

 // If file doesn't exist, creates it.

 if (!Exists()) internal_mode |= O_CREAT;

 myPath.SystemName ( aBuffer );
 myFileChannel = open (aBuffer.ToCString(), internal_mode, internal_prot);
 if (myFileChannel >= 0)
   myFILE = fdopen (myFileChannel, CMode);
 else
 /* Handle OPEN errors */

   myError.SetValue (errno, Iam, "Open");
}

// ---------------------------------------------------------------------
// Open a file
// ---------------------------------------------------------------------

void  OSD_File::Open(const OSD_OpenMode Mode,
                     const OSD_Protection& Protect){

 Standard_Integer internal_prot;
 Standard_Integer internal_mode = 0;
 TCollection_AsciiString aBuffer;

  if ( OSD_File::KindOfFile ( ) == OSD_DIRECTORY ) { 
    myError.SetValue (1, Iam, "Could not be open : it is a directory");
  }

 if (myPath.Name().Length()==0)
  Standard_ProgramError::Raise("OSD_File::Open : no name was given");

 if (myFileChannel != -1)
  Standard_ProgramError::Raise("OSD_File::Open : file is already open");

 internal_prot = Protect.Internal();
 myMode = Mode;
 const char* CMode = "r";

 switch (Mode){
  case OSD_ReadOnly:
   internal_mode |= O_RDONLY;
   CMode = "r";
   break;
  case OSD_WriteOnly:
   internal_mode |= O_WRONLY;
   CMode = "w";
   break;
  case OSD_ReadWrite:
   internal_mode |= O_RDWR;
   CMode = "w+";
   break;
 }

 myPath.SystemName ( aBuffer );
 myFileChannel = open (aBuffer.ToCString(), internal_mode, internal_prot);
 if (myFileChannel >= 0)
   myFILE = fdopen (myFileChannel, CMode);
 else
 /* Handle OPEN errors */

   myError.SetValue (errno, Iam, "Open");
}



// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
OSD_File OSD_File::BuildTemporary(){

#if defined(vax) || defined(__vms) || defined(VAXVMS)
 FILE *fic;
 OSD_File result;
 int dummy;

 fic = tmpfile();
 dummy = open("dummy", O_RDWR | O_CREAT);  // Open a dummy file
 result.myFileChannel = dummy - 1;         // This is file channel of "fic" +1
 close(dummy);                             // Close dummy file
 unlink("dummy");                          // Removes dummy file

#else 
 OSD_File result;
 char name[] = "/tmp/oce.XXXXXX";
 result.myFileChannel = mkstemp( name );

 TCollection_AsciiString aName ( name ) ;
 OSD_Path aPath( aName ) ;

 result.SetPath( aPath ) ;

 result.myFILE  = fdopen( result.myFileChannel, "w+" ) ;

#endif

 result.myMode = OSD_ReadWrite;

 return (result);
}
 


// ---------------------------------------------------------------------
// Read content of a file
// ---------------------------------------------------------------------
 
void  OSD_File::Read(TCollection_AsciiString& Buffer, 
                     const Standard_Integer Nbyte){
 Standard_PCharacter readbuf;
 int status;

  if ( OSD_File::KindOfFile ( ) == OSD_DIRECTORY ) { 
    Standard_ProgramError::Raise("OSD_File::Read : it is a directory");
  }

 if (myFileChannel == -1)
  Standard_ProgramError::Raise("OSD_File::Read : file is not open");

 if (Failed()) Perror();

 if (myMode == OSD_WriteOnly)
  Standard_ProgramError::Raise("OSD_File::Read : file is Write only");

 if (Nbyte <= 0)
  Standard_ProgramError::Raise("OSD_File::Read : Nbyte is null");

 TCollection_AsciiString transfert(Nbyte,' ');
 readbuf = (Standard_PCharacter)transfert.ToCString();  

 status = read (myFileChannel, readbuf, Nbyte);
 //
 Buffer = transfert;  // Copy transfert to Buffer

 if (status == -1) myError.SetValue (errno, Iam, "Read");
 else
 if ( status < Nbyte ) myIO = EOF;
}


// ---------------------------------------------------------------------
// Read a line from a file
// ---------------------------------------------------------------------

void OSD_File::ReadLine(TCollection_AsciiString& Buffer, 
			const Standard_Integer Nbyte,
			Standard_Integer& NByteRead)
{
  Standard_PCharacter readbuf, abuffer;
  //
  if (OSD_File::KindOfFile() == OSD_DIRECTORY ) { 
    Standard_ProgramError::Raise("OSD_File::Read : it is a directory");
  }
  if (myFileChannel == -1){
    Standard_ProgramError::Raise("OSD_File::ReadLine : file is not open");
  }
  if (Failed()) {
    Perror();
  }
  if (myMode == OSD_WriteOnly) {
    Standard_ProgramError::Raise("OSD_File::ReadLine : file is Write only");
  }
  if (Nbyte <= 0){
    Standard_ProgramError::Raise("OSD_File::ReadLine : Nbyte is null");
  }
  //
  TCollection_AsciiString transfert(Nbyte,' ');
  readbuf = (Standard_PCharacter)transfert.ToCString();
  //
  abuffer = fgets(readbuf, Nbyte, (FILE *) myFILE);
  //
  if (abuffer == NULL) {
    if (!feof((FILE *) myFILE)) {
      myError.SetValue (errno, Iam, "ReadLine");
      return;
    }
    else {
      myIO = EOF;
      Buffer.Clear();
      NByteRead = 0 ;
    }
  }
  else   {
    NByteRead = (Standard_Integer)strlen(abuffer);
    Buffer.SetValue(1,abuffer);  // Copy transfert to Buffer
    Buffer.Trunc(NByteRead);
  }
}
// -------------------------------------------------------------------------- 
// OSD::KindOfFile Retourne le type de fichier.
// -------------------------------------------------------------------------- 
OSD_KindFile OSD_File::KindOfFile ( ) const{
int status;
struct stat buffer;
TCollection_AsciiString FullName;
OSD_Path aPath;

Path(aPath);
aPath.SystemName (FullName);
status = stat (FullName.ToCString()  , &buffer );
if ( status == 0) {
  if       (  S_ISDIR(buffer.st_mode)  )  { return OSD_DIRECTORY ; }
  else if  (  S_ISREG(buffer.st_mode)  )  { return OSD_FILE      ; }
  else if  (  S_ISLNK(buffer.st_mode)  )  { return OSD_LINK      ; }
  else if  (  S_ISSOCK(buffer.st_mode) )  { return OSD_SOCKET    ; }
  else                                    { return OSD_UNKNOWN   ; }
}
return OSD_UNKNOWN   ; 

}
// -------------------------------------------------------------------------- 
// Read content of a file
// -------------------------------------------------------------------------- 
void  OSD_File::Read(      Standard_Address&  Buffer, 
                     const Standard_Integer   Nbyte,
                           Standard_Integer&  Readbyte)
{
  int status;
  
  Readbyte = 0;
  if ( OSD_File::KindOfFile ( ) == OSD_DIRECTORY ) { 
    Standard_ProgramError::Raise("OSD_File::Read : it is a directory");
  }
 
  if (myFileChannel == -1)
    Standard_ProgramError::Raise("OSD_File::Read : file is not open");
  
  if (Failed()) Perror();
  
  if (myMode == OSD_WriteOnly)
    Standard_ProgramError::Raise("OSD_File::Read : file is Write only");
  
  if (Nbyte <= 0)
    Standard_ProgramError::Raise("OSD_File::Read : Nbyte is null");

  if (Buffer == NULL)
    Standard_ProgramError::Raise("OSD_File::Read : Buffer is null");
  
  status = read (myFileChannel, (char*) Buffer, Nbyte);
  
  if (status == -1) myError.SetValue (errno, Iam, "Read");
  else{
    if ( status < Nbyte ) myIO = EOF;
    Readbyte = status;
  }
}

// Write content of a file

void  OSD_File::Write(const TCollection_AsciiString &Buffer, 
                      const Standard_Integer Nbyte){

 Standard_CString writebuf;
 int status;

 if ( OSD_File::KindOfFile ( ) == OSD_DIRECTORY ) { 
   Standard_ProgramError::Raise("OSD_File::Write : it is a directory");
 }
 
 if (myFileChannel == -1)
  Standard_ProgramError::Raise("OSD_File::Write : file is not open");

 if (Failed()) Perror();

 if (myMode == OSD_ReadOnly)
  Standard_ProgramError::Raise("OSD_File::Write : file is Read only");

 if (Nbyte <= 0)
  Standard_ProgramError::Raise("OSD_File::Write : Nbyte is null");

 writebuf = Buffer.ToCString();

 status = write (myFileChannel, writebuf, Nbyte);

 if ( status == -1) myError.SetValue (errno, Iam, "Write");
 else
 if ( status < Nbyte ) myIO = EOF;
}


void  OSD_File::Write(const Standard_Address   Buffer, 
                      const Standard_Integer   Nbyte)
{

  int status;
  
  if (myFileChannel == -1)
    Standard_ProgramError::Raise("OSD_File::Write : file is not open");
  
  if (Failed()) Perror();
  
  if (myMode == OSD_ReadOnly)
    Standard_ProgramError::Raise("OSD_File::Write : file is Read only");
  
  if (Nbyte <= 0)
    Standard_ProgramError::Raise("OSD_File::Write : Nbyte is null");
  
  status = write (myFileChannel, (const char *)Buffer, Nbyte);
  
  if ( status == -1) myError.SetValue (errno, Iam, "Write");
  else
    if ( status < Nbyte ) myIO = EOF;
}





// Move file pointer to a specified position

void  OSD_File::Seek(const Standard_Integer Offset, 
                     const OSD_FromWhere Whence){
 int iwhere=0;

 if (myFileChannel == -1)
  Standard_ProgramError::Raise("OSD_File::Seek : file is not open");

 if (Failed()) Perror();

 switch (Whence){
  case OSD_FromBeginning :
    iwhere = SEEK_SET;
    break;
  case OSD_FromHere:
    iwhere = SEEK_CUR;
    break;
  case OSD_FromEnd:
    iwhere = SEEK_END;
    break;
  default :
   myError.SetValue (EINVAL, Iam, "Seek");
 }

 off_t status = lseek (myFileChannel, Offset, iwhere);
 if (status == -1) myError.SetValue (errno, Iam, "Seek");
}






// Close a file

void  OSD_File::Close(){
 int status;

 if (myFileChannel == -1)
  Standard_ProgramError::Raise("OSD_File::Close : file is not open");

 if (Failed()) Perror();

 // note: it probably should be single call to fclose()...
 status = close (myFileChannel);

 if (status == -1) myError.SetValue (errno, Iam, "Close");
 myFileChannel = -1;
 if ( myFILE != NULL ) {
   status = fclose ( (FILE*) myFILE );
   myFILE = NULL;
 }
 myIO = 0;
}




// -------------------------------------------------------------------------- 
// Test if at end of file
// -------------------------------------------------------------------------- 

Standard_Boolean OSD_File::IsAtEnd(){
 if (myFileChannel == -1)
  Standard_ProgramError::Raise("OSD_File::IsAtEnd : file is not open");

 if (myIO == EOF) return (Standard_True);
 return (Standard_False);
}



/*void  OSD_File::Link(const TCollection_AsciiString& ToFile){
 if (myFileChannel == -1)
  Standard_ProgramError::Raise("OSD_File::Link : file is not open");

 TCollection_AsciiString aBuffer;
 myPath.SystemName ( aBuffer );
 link ( aBuffer.ToCString(), ToFile.ToCString() );

}*/



void  OSD_File::SetLock(const OSD_LockType Lock){
int status;

 if (myFileChannel == -1)
  Standard_ProgramError::Raise("OSD_File::SetLock : file is not open");


#ifdef POSIX
 int lock;
 struct stat buf;

 switch (Lock){
  case OSD_ExclusiveLock :
  case OSD_WriteLock     : lock = F_LOCK;
                           break;
  case OSD_ReadLock      : return;
                           break;
  default : myError.SetValue (EINVAL, Iam, "SetLock");
            return;
 }

 if (fstat (myFileChannel, &buf) == -1) {
  myError.SetValue (errno, Iam, "SetLock");
  return;
 }

 status = lockf(myFileChannel, lock, buf.st_size);
 if (status == -1) myError.SetValue (errno, Iam, "SetLock");
 else myLock = Lock;

#else
#ifdef SYSV
 struct stat  buf;
 struct flock key;

 switch (Lock){
  case OSD_ExclusiveLock :
  case OSD_WriteLock     : key.l_type = F_WRLCK;
                           break;
  case OSD_ReadLock      : key.l_type = F_RDLCK;
                           break;
  case OSD_NoLock : return;
 // default : myError.SetValue (EINVAL, Iam, "SetLock");
 }

 key.l_whence = 0;
 key.l_start = 0;
 key.l_len = 0;

 status = fcntl (myFileChannel, F_SETLKW, &key);
 if (status == -1) myError.SetValue (errno, Iam, "SetLock");
 else myLock = Lock;

 if (Lock == OSD_ExclusiveLock){
  fstat (myFileChannel, &buf);
  TCollection_AsciiString aBuffer;
  myPath.SystemName ( aBuffer );
  chmod( aBuffer.ToCString() ,buf.st_mode | S_ISGID);
  ImperativeFlag = Standard_True;
 }

#else   /* BSD */
 int lock;

 switch (Lock){
  case OSD_ExclusiveLock :
  case OSD_WriteLock     : lock = F_WRLCK;
                           break;
  case OSD_ReadLock      : lock = F_RDLCK;
                           break;
  default : myError.SetValue (EINVAL, Iam, "SetLock");
 }

 status = flock (myFileChannel, lock);
 if (status == -1) myError.SetValue (errno, Iam, "SetLock");
 else myLock = Lock;
#endif // SysV
#endif // POSIX
}




// Remove a lock from a file

void  OSD_File::UnLock(){
int status;

 if (myFileChannel == -1)
  Standard_ProgramError::Raise("OSD_File::UnLock : file is not open");

#ifdef POSIX
 struct stat buf;

 if (fstat(myFileChannel, &buf) == -1) {
  myError.SetValue(errno, Iam, "UnsetLock");
  return;
 }
 
 status = lockf(myFileChannel,F_ULOCK, buf.st_size);
  if (status == -1) myError.SetValue (errno, Iam, "SetLock");

#else
#ifdef SYSV
 struct stat  buf;
 struct flock key;

 if (ImperativeFlag){
  fstat (myFileChannel, &buf);
  TCollection_AsciiString aBuffer;
  myPath.SystemName ( aBuffer );
  chmod(aBuffer.ToCString(),buf.st_mode & ~S_ISGID);
  ImperativeFlag = Standard_False;
 }
 key.l_type = F_UNLCK;
 status = fcntl (myFileChannel, F_SETLK, &key);
 if (status == -1) myError.SetValue (errno, Iam, "UnSetLock");
#else

 status = flock (myFileChannel, LOCK_UN);
 if (status == -1) myError.SetValue (errno, Iam, "UnSetLock");
#endif
#endif // POSIX
 else myLock = OSD_NoLock;
}





// Return lock of a file

OSD_LockType  OSD_File::GetLock(){
 if (myFileChannel == -1)
  Standard_ProgramError::Raise("OSD_File::GetLock : file is not open");

 return(myLock);
}




// -------------------------------------------------------------------------- 
// Return size of a file
// -------------------------------------------------------------------------- 

Standard_Size  OSD_File::Size(){
 struct stat buffer;
 int status;

 if (myPath.Name().Length()==0)
  Standard_ProgramError::Raise("OSD_File::Size : empty file name");

 TCollection_AsciiString aBuffer;
 myPath.SystemName ( aBuffer );
 status = stat( aBuffer.ToCString() ,&buffer );
 if (status == -1) {
  myError.SetValue (errno, Iam, "Size");
  return 0;
 }

 return (Standard_Size)buffer.st_size;
}


// -------------------------------------------------------------------------- 
// Print contains of a file
// -------------------------------------------------------------------------- 

void OSD_File::Print (const OSD_Printer &WhichPrinter ){
char buffer[255];
TCollection_AsciiString PrinterName;

 if (myPath.Name().Length()==0)
   Standard_ProgramError::Raise("OSD_File::Print : empty file name");

 WhichPrinter.Name(PrinterName);

 TCollection_AsciiString aBuffer;
 myPath.SystemName ( aBuffer );

 if (PrinterName.Length()==0)
   sprintf(buffer,"lp %s",aBuffer.ToCString());
 else
   sprintf(buffer,"lpr -P%s %s",PrinterName.ToCString(),aBuffer.ToCString());

 if (0 != system(buffer))
   Standard_ProgramError::Raise("OSD_File::Print : lp/lpr failed");;
}


// -------------------------------------------------------------------------- 
// Test if a file is open
// -------------------------------------------------------------------------- 

Standard_Boolean OSD_File::IsOpen()const{

 if (myPath.Name().Length()==0)
   Standard_ProgramError::Raise("OSD_File::IsOpen : empty file name");

 return (myFileChannel != -1);
}


Standard_Boolean OSD_File::IsLocked(){

 if (myPath.Name().Length()==0)
   Standard_ProgramError::Raise("OSD_File::IsLocked : empty file name");

 return(myLock != OSD_NoLock); 
}

Standard_Boolean OSD_File::IsReadable()
{
  TCollection_AsciiString FileName ;

  myPath.SystemName(FileName) ;

  if (access(FileName.ToCString(),F_OK|R_OK))
    return Standard_False;
  else
    return Standard_True;
}

Standard_Boolean OSD_File::IsWriteable()
{
  TCollection_AsciiString FileName ;

  myPath.SystemName(FileName) ;

  if (access(FileName.ToCString(),F_OK|R_OK|W_OK))
    return Standard_False;
  else
    return Standard_True;
}

Standard_Boolean OSD_File::IsExecutable()
{
  TCollection_AsciiString FileName ;

  myPath.SystemName(FileName) ;

  if (access(FileName.ToCString(),F_OK|X_OK))
    return Standard_False;
  else
    return Standard_True;
}

#else /* _WIN32 */

//------------------------------------------------------------------------
//-------------------  Windows NT sources for OSD_File -------------------
//------------------------------------------------------------------------

#include <windows.h>

#include <OSD_File.hxx>
#include <OSD_Protection.hxx>
#include <OSD_Printer.hxx>
#include <Standard_ProgramError.hxx>

#include <OSD_WNT_1.hxx>

#include <stdio.h>
#include <io.h>
#if !defined (_MSC_VER) || (_MSC_VER >= 1600)
#include <stdint.h>
#endif
#include <Standard_PCharacter.hxx>
#include <TCollection_ExtendedString.hxx>

#ifndef _INC_TCHAR
# include <tchar.h>
#endif  // _INC_TCHAR

#if defined(__CYGWIN32__) || defined(__MINGW32__) || defined(__BORLANDC__)
#define VAC
#define _int64 int64_t
#endif

#if defined(_MSC_VER) || defined(__BORLANDC__)
#pragma comment( lib, "WSOCK32.LIB"  )
#pragma comment( lib, "WINSPOOL.LIB" )
#endif

#define ACE_HEADER_SIZE (  sizeof ( ACCESS_ALLOWED_ACE ) - sizeof ( DWORD )  )

#define RAISE( arg ) Standard_ProgramError :: Raise (  ( arg )  )
#define TEST_RAISE( arg ) _test_raise (  myFileHandle, ( arg )  )

#define OPEN_NEW    0
#define OPEN_OLD    1
#define OPEN_APPEND 2

void                            _osd_wnt_set_error        ( OSD_Error&, OSD_WhoAmI, ... );
PSECURITY_DESCRIPTOR __fastcall _osd_wnt_protection_to_sd ( const OSD_Protection&, BOOL, wchar_t* = NULL );
BOOL                 __fastcall _osd_wnt_sd_to_protection (
                                 PSECURITY_DESCRIPTOR, OSD_Protection&, BOOL
                                );
BOOL                 __fastcall _osd_print (const Standard_PCharacter, const wchar_t* );

static void      __fastcall _test_raise ( HANDLE, Standard_CString );
static DWORDLONG __fastcall _get_line   ( Standard_PCharacter&, DWORD );
static int       __fastcall _get_buffer ( HANDLE, Standard_PCharacter&, DWORD, BOOL, BOOL );
static DWORD     __fastcall _get_access_mask ( OSD_SingleProtection );
static DWORD     __fastcall _get_dir_access_mask ( OSD_SingleProtection prt );
static HANDLE    __fastcall _open_file  ( Standard_CString, OSD_OpenMode, DWORD, LPBOOL = NULL );

static OSD_SingleProtection __fastcall _get_protection     ( DWORD );
static OSD_SingleProtection __fastcall _get_protection_dir ( DWORD );

typedef OSD_SingleProtection ( __fastcall *GET_PROT_FUNC ) ( DWORD );

Standard_Integer __fastcall _get_file_type ( Standard_CString, HANDLE );

// ---------------------------------------------------------------------
// Create an empty file object
// ---------------------------------------------------------------------

OSD_File :: OSD_File ()
{
 ImperativeFlag = Standard_False;
 myLock         = OSD_NoLock;
 myIO           = 0;
 myFileChannel  = -1;
 myFileHandle   = INVALID_HANDLE_VALUE;
}  // end constructor ( 1 )

// ---------------------------------------------------------------------
// Create and initialize a file object
// ---------------------------------------------------------------------

OSD_File :: OSD_File ( const OSD_Path& Name ) : OSD_FileNode ( Name )
{
 ImperativeFlag = Standard_False;
 myLock         = OSD_NoLock;
 myIO           = 0;
 myPath         = Name;
 myFileChannel  = -1;
 myFileHandle   = INVALID_HANDLE_VALUE;
}  // end constructor ( 2 )

// protect against occasional use of myFileHande in Windows code
#define myFileChannel myFileChannel_is_only_for_Linux

// ---------------------------------------------------------------------
// Build a file if it doesn't exist or create again if it already exists
// ---------------------------------------------------------------------

void OSD_File :: Build (
                  const OSD_OpenMode Mode, const OSD_Protection& Protect
                 ) {

 TCollection_AsciiString fName;

 if ( OSD_File::KindOfFile ( ) == OSD_DIRECTORY ) { 
   Standard_ProgramError::Raise("OSD_File::Read : it is a directory");
 }
                                        
 if (myFileHandle != INVALID_HANDLE_VALUE)

  RAISE(  "OSD_File :: Build (): incorrect call - file already opened"  );

 myMode = Mode;
 myPath.SystemName ( fName );

 if (  fName.IsEmpty ()  )

  RAISE(  "OSD_File :: Build (): incorrent call - no filename given"  );

 myFileHandle = _open_file ( fName.ToCString (), Mode, OPEN_NEW );

 if (myFileHandle == INVALID_HANDLE_VALUE)

  _osd_wnt_set_error ( myError, OSD_WFile );

 else {

  SetProtection ( Protect );
  myIO |= FLAG_FILE;

 }  // end else

}  // end OSD_File :: Build



// ---------------------------------------------------------------------
// Open a file
// ---------------------------------------------------------------------

void OSD_File :: Open (const OSD_OpenMode Mode, const OSD_Protection& /*Protect*/)
{

 TCollection_AsciiString fName;


 if (myFileHandle != INVALID_HANDLE_VALUE)

  RAISE(  "OSD_File :: Open (): incorrect call - file already opened"  );

 myMode = Mode;
 myPath.SystemName ( fName );

 if (  fName.IsEmpty ()  )

  RAISE(  "OSD_File :: Open (): incorrent call - no filename given"  );

 myFileHandle = _open_file ( fName.ToCString (), Mode, OPEN_OLD );

 if (myFileHandle == INVALID_HANDLE_VALUE) {

   _osd_wnt_set_error ( myError, OSD_WFile );
 }
 else
   {
     myIO |= _get_file_type (  fName.ToCString (), myFileHandle  );
   }
}  // end OSD_File :: Open

// ---------------------------------------------------------------------
// Append to an existing file
// ---------------------------------------------------------------------

void OSD_File :: Append (
                  const OSD_OpenMode Mode, const OSD_Protection& Protect
                 ) {

 BOOL                    fNew = FALSE;
 TCollection_AsciiString fName;

 if (myFileHandle != INVALID_HANDLE_VALUE)

  RAISE(  "OSD_File :: Append (): incorrect call - file already opened"  );

 myMode = Mode;
 myPath.SystemName ( fName );

 if (  fName.IsEmpty ()  )

  RAISE(  "OSD_File :: Append (): incorrent call - no filename given"  );

 myFileHandle = _open_file ( fName.ToCString (), Mode, OPEN_APPEND, &fNew );

 if (myFileHandle == INVALID_HANDLE_VALUE)

  _osd_wnt_set_error ( myError, OSD_WFile );

 else {

  if ( !fNew ) {

   myIO |= _get_file_type (  fName.ToCString (), myFileHandle  );
   Seek ( 0, OSD_FromEnd );

  } else {
  
   SetProtection ( Protect );
   myIO |= FLAG_FILE;
  
  }  // end else

 }  // end else;

}  // end OSD_File :: Append

// ---------------------------------------------------------------------
// Read content of a file
// ---------------------------------------------------------------------
 
void OSD_File :: Read (
                  TCollection_AsciiString& Buffer, const Standard_Integer Nbyte
                 ) {

 if ( OSD_File::KindOfFile ( ) == OSD_DIRECTORY ) { 
#ifdef OCCT_DEBUG
   cout << " OSD_File::Read : it is a directory " << endl;
#endif
   return ;
//   Standard_ProgramError::Raise("OSD_File::Read : it is a directory");
 }
                                        
 Standard_Integer NbyteRead;
 Standard_Character* buff;

 TEST_RAISE(  "Read"  );
     
 buff = new Standard_Character[ Nbyte + 1 ];

 Read ( ( Standard_Address& )buff, Nbyte, NbyteRead );

 (  ( Standard_PCharacter )buff  )[ NbyteRead ] = 0;

 if ( NbyteRead != 0 )

  Buffer = ( Standard_PCharacter )buff;

 else

  Buffer.Clear ();

 delete [] buff;

}  // end OSD_File :: Read

// ---------------------------------------------------------------------
// Read a line from a file
// ---------------------------------------------------------------------

// Modified so that we have <nl> at end of line if we have read <nl> or <cr>
// in the file.
// by LD 17 dec 98 for B4.4

void OSD_File :: ReadLine (
                  TCollection_AsciiString& Buffer,
                  const Standard_Integer NByte, Standard_Integer& NbyteRead
                 ) {

 DWORDLONG          status;
 DWORD              dwBytesRead;
 DWORD              dwDummy;
 Standard_Character peekChar;
 Standard_PCharacter ppeekChar;
 Standard_PCharacter cBuffer;
 Standard_CString   eos;
 DWORD              dwSeekPos;

 if ( OSD_File::KindOfFile ( ) == OSD_DIRECTORY ) { 
   Standard_ProgramError::Raise("OSD_File::Read : it is a directory");
 }
                                        
 TEST_RAISE(  "ReadLine"  );              

 if (  myIO & FLAG_PIPE && !( myIO & FLAG_READ_PIPE )  )

  RAISE(  "OSD_File :: ReadLine (): attempt to read from write only pipe"  );

                                        // +----> leave space for end-of-string
                                        // |       plus <CR><LF> sequence      
                                        // |

 ppeekChar=&peekChar;
 cBuffer = new Standard_Character[ NByte + 3 ];

 if ( myIO & FLAG_FILE ) {
 
  if (!ReadFile (myFileHandle, cBuffer, (DWORD)NByte, &dwBytesRead, NULL)) {  // an error occured

   _osd_wnt_set_error ( myError, OSD_WFile );   
   Buffer.Clear ();
   NbyteRead = 0;
   
  } else if ( dwBytesRead == 0 ) {  // end-of-file reached
   
   Buffer.Clear ();
   NbyteRead = 0;
   myIO |= FLAG_EOF;
   
  } else {
   myIO &= ~FLAG_EOF ;  // if the file increased since last read (LD)
   status = _get_line ( cBuffer, dwBytesRead );

   dwSeekPos = LODWORD( status );
   eos       = ( Standard_CString )HIDWORD( status );
#ifdef VAC
   if ( (__int64) status == (__int64) -1 ) {  // last character in the buffer is <CR> -
#else
   if ( status == 0xFFFFFFFFFFFFFFFF ) {  // last character in the buffer is <CR> -
                                          // peek next character to see if it is a <LF>
#endif
    if (!ReadFile (myFileHandle, ppeekChar, 1, &dwDummy, NULL)) {
    
     _osd_wnt_set_error ( myError, OSD_WFile );

    } else if ( dwDummy != 0 ) {  // end-of-file reached ?

     if ( peekChar != '\n' )  // if we did not get a <CR><LF> sequence
    
     // adjust file position

      SetFilePointer (myFileHandle, -1, NULL, FILE_CURRENT);

    } else
     myIO |= FLAG_EOF;

    NbyteRead = dwBytesRead;

   } else {

    if ( dwSeekPos != 0 )
     SetFilePointer (myFileHandle, (LONG)dwSeekPos, NULL, FILE_CURRENT);

    NbyteRead = ( Standard_Integer )( eos - cBuffer );

   }

  }  // end else
   
 } else if ( myIO & FLAG_SOCKET || myIO & FLAG_PIPE || myIO & FLAG_NAMED_PIPE ) {

  dwBytesRead = (DWORD)_get_buffer (myFileHandle, cBuffer, 
                                    (DWORD)NByte, TRUE, myIO & FLAG_SOCKET);

  if (  ( int )dwBytesRead == -1  ) { // an error occured

   _osd_wnt_set_error ( myError, OSD_WFile );
   Buffer.Clear ();
   NbyteRead = 0;

  } else if ( dwBytesRead == 0 )  { // connection closed - set end-of-file flag

   Buffer.Clear ();
   NbyteRead = 0;
   myIO |= FLAG_EOF;

  } else {

   status = _get_line ( cBuffer, dwBytesRead );

   dwSeekPos = LODWORD( status );
   eos       = ( Standard_CString )HIDWORD( status );

#ifdef VAC
   if ( (__int64) status == (__int64) -1 ) {  // last character in the buffer is <CR> -
#else  
   if ( status == 0xFFFFFFFFFFFFFFFF ) {  // last character in the buffer is <CR> -    
                                          // peek next character to see if it is a <LF>
#endif

    NbyteRead = dwBytesRead; // (LD) always fits this case.

    dwDummy = _get_buffer (myFileHandle, ppeekChar, 1, TRUE, myIO & FLAG_SOCKET);
    if (  ( int )dwDummy == -1  ) {  // an error occured
   
     _osd_wnt_set_error ( myError, OSD_WFile );

    } else if ( dwDummy != 0 ) {  // connection closed ?

     if ( peekChar == '\n' )  // we got a <CR><LF> sequence

       dwBytesRead++ ;  // (LD) we have to jump <LF>
    } else

     myIO |= FLAG_EOF;

   } else {

    if ( dwSeekPos != 0 )
     dwBytesRead = dwBytesRead + dwSeekPos;

    NbyteRead  = ( Standard_Integer )( eos - cBuffer );

   }

   // Don't rewrite datas in cBuffer.

   Standard_PCharacter cDummyBuffer = new Standard_Character[ NByte + 3 ];

   // remove pending input
   _get_buffer (myFileHandle, cDummyBuffer, dwBytesRead, FALSE, myIO & FLAG_SOCKET);
   delete [] cDummyBuffer ;

  }  // end else
   
 } else

  RAISE(  "OSD_File :: ReadLine (): incorrect call - file is a directory"  );

 if (  !Failed () && !IsAtEnd ()  )

  Buffer = cBuffer;

 delete [] (Standard_PCharacter)cBuffer;

}  // end OSD_File :: ReadLine

// -------------------------------------------------------------------------- 
// Read content of a file
// -------------------------------------------------------------------------- 

void OSD_File :: Read (
                  Standard_Address& Buffer,
                  const Standard_Integer Nbyte, Standard_Integer& Readbyte
                 ) {

 DWORD dwBytesRead;

 if ( OSD_File::KindOfFile ( ) == OSD_DIRECTORY ) { 
   Standard_ProgramError::Raise("OSD_File::Read : it is a directory");
 }
                                        
 TEST_RAISE(  "Read"  );

 if (  myIO & FLAG_PIPE && !( myIO & FLAG_READ_PIPE )  )

  RAISE(  "OSD_File :: Read (): attempt to read from write only pipe"  );

 if (!ReadFile (myFileHandle, Buffer, (DWORD)Nbyte, &dwBytesRead, NULL)) {
 
  _osd_wnt_set_error ( myError, OSD_WFile );
  dwBytesRead = 0;
 
 } else if ( dwBytesRead == 0 )

  myIO |= FLAG_EOF;

 else

  myIO &= ~FLAG_EOF;

 Readbyte = ( Standard_Integer )dwBytesRead;

}  // end OSD_File :: Read

void OSD_File :: Write (
                  const TCollection_AsciiString& Buffer,
                  const Standard_Integer Nbyte
                 ) {

 Write (  ( Standard_Address )Buffer.ToCString (), Nbyte  );

}  // end OSD_File :: Write

// -------------------------------------------------------------------------- 
// Write content of a file
// -------------------------------------------------------------------------- 

void OSD_File :: Write (
                  const Standard_Address Buffer,
                  const Standard_Integer Nbyte
                 ) {

 DWORD dwBytesWritten;

 TEST_RAISE(  "Write"  );

 if ( myIO & FLAG_PIPE && myIO & FLAG_READ_PIPE )

  RAISE(  "OSD_File :: Write (): attempt to write to read only pipe"  );

 if (!WriteFile (myFileHandle, Buffer, (DWORD)Nbyte, &dwBytesWritten, NULL) || 
     dwBytesWritten != (DWORD)Nbyte)

  _osd_wnt_set_error ( myError, OSD_WFile );

}  // end OSD_File :: Write

void OSD_File :: Seek (
                  const Standard_Integer Offset, const OSD_FromWhere Whence
                 ) {

 DWORD dwMoveMethod = 0;

 TEST_RAISE(  "Seek"  );

 if ( myIO & FLAG_FILE || myIO & FLAG_DIRECTORY ) {

  switch ( Whence ) {
  
   case OSD_FromBeginning:

    dwMoveMethod = FILE_BEGIN;

   break;

   case OSD_FromHere:

    dwMoveMethod = FILE_CURRENT;

   break;

   case OSD_FromEnd:

    dwMoveMethod = FILE_END;

   break;

   default:

    RAISE(  "OSD_File :: Seek (): invalid parameter"  );
  
  }  // end switch

  if (SetFilePointer (myFileHandle, (LONG)Offset, NULL, dwMoveMethod) == 0xFFFFFFFF)

   _osd_wnt_set_error ( myError, OSD_WFile );
  
 }  // end if

 myIO &= ~FLAG_EOF;

}  // end OSD_File :: Seek

// -------------------------------------------------------------------------- 
// Close a file
// -------------------------------------------------------------------------- 

void OSD_File :: Close () {

 TEST_RAISE(  "Close"  );

 CloseHandle (myFileHandle);

 myFileHandle = INVALID_HANDLE_VALUE;
 myIO          = 0;

}  // end OSD_File :: Close

// -------------------------------------------------------------------------- 
// Test if at end of file
// -------------------------------------------------------------------------- 

Standard_Boolean OSD_File :: IsAtEnd () {

 TEST_RAISE(  "IsAtEnd"  );

 if (myIO & FLAG_EOF)
   return Standard_True ;
 return Standard_False ;

}  // end OSD_File :: IsAtEnd

OSD_KindFile OSD_File :: KindOfFile () const {

 OSD_KindFile     retVal;
 Standard_Integer flags;

 if (myFileHandle == INVALID_HANDLE_VALUE) {

  TCollection_AsciiString fName;

  myPath.SystemName ( fName );

  if (  fName.IsEmpty ()  )

   RAISE(  "OSD_File :: KindOfFile (): incorrent call - no filename given"  );

  flags = _get_file_type (fName.ToCString(), INVALID_HANDLE_VALUE);

 } else

  flags = myIO;

 switch ( flags & FLAG_TYPE ) {
 
  case FLAG_FILE:

   retVal = OSD_FILE;

  break;

  case FLAG_DIRECTORY:

   retVal = OSD_DIRECTORY;

  break;

  case FLAG_SOCKET:

   retVal = OSD_SOCKET;

  break;

  default:

   retVal = OSD_UNKNOWN;
 
 }  // end switch

 return retVal;

}  // end OSD_File :: KindOfFile

#ifdef VAC
 char tmpbuf [MAX_PATH];
 if (GetTempPath (MAX_PATH, tmpbuf) == 0)
 {
    perror ("ERROR in GetTempPath");
    exit (10);
 }
 char tmpbuf2 [MAX_PATH];
 if (GetTempFileName (tmpbuf, NULL, 0, tmpbuf2) == 0)
 {
    perror ("ERROR in GetTempFileName");
    exit (10);
 }
 TCollection_AsciiString fileName (  tmpbuf2  );
#else
 TCollection_AsciiString fileName (  _ttmpnam ( NULL )  );
#endif


//-------------------------------------------------debutpri???980424

typedef struct _osd_wnt_key {

                HKEY   hKey;
                LPCTSTR keyPath;

               } OSD_WNT_KEY;


OSD_File OSD_File :: BuildTemporary () {

 OSD_Protection prt;
 OSD_File       retVal;
 HKEY           hKey;
 TCHAR          tmpPath[ MAX_PATH ];
 BOOL           fOK = FALSE;
 OSD_WNT_KEY    regKey[ 2 ] = {
 
                 { HKEY_LOCAL_MACHINE,
                   "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"
                 },
                 { HKEY_USERS,
                   ".DEFAULT\\Environment"
                 }
 
                };
 
 for ( int i = 0; i < 2; ++i ) {

  if (  RegOpenKeyEx (
         regKey[ i ].hKey, regKey[ i ].keyPath, 0, KEY_QUERY_VALUE, &hKey
       ) == ERROR_SUCCESS
  ) {
  
   DWORD dwType;
   DWORD dwSize = 0;

   if (  RegQueryValueEx (
          hKey, "TEMP", NULL, &dwType, NULL, &dwSize
         ) == ERROR_SUCCESS
   ) {
  
    LPTSTR kVal = ( LPTSTR )HeapAlloc (
                             GetProcessHeap (), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS,
                             dwSize + sizeof ( TCHAR )
                            );

     RegQueryValueEx (  hKey, "TEMP", NULL, &dwType, ( LPBYTE )kVal, &dwSize  );

     if ( dwType == REG_EXPAND_SZ )
    
      ExpandEnvironmentStrings ( kVal, tmpPath, MAX_PATH );

     else

      lstrcpy ( tmpPath, kVal );

    HeapFree (  GetProcessHeap (), 0, ( LPVOID )kVal  );
    fOK = TRUE;

   }  // end if

   RegCloseKey ( hKey );

  }  // end if

  if ( fOK ) break;

 }  // end for

 if ( !fOK ) lstrcpy (  tmpPath, "./"  );
 
 GetTempFileName ( tmpPath, "CSF", 0, tmpPath );

 retVal.SetPath (  OSD_Path ( tmpPath )  );
 retVal.Build   (  OSD_ReadWrite, prt    );

 return retVal;

}  // end OSD_File :: BuildTemporary

//-------------------------------------------------finpri???980424


void OSD_File :: SetLock ( const OSD_LockType Lock ) {

 DWORD      dwFlags;
 OVERLAPPED ovlp;

 TEST_RAISE(  "SetLock"  );
 
 ZeroMemory (  &ovlp, sizeof ( OVERLAPPED )  );

 bool Ret = true;
 if (Ret){

  if (  ( myLock = Lock ) == OSD_NoLock  ) {

   UnLock ();
   Ret = false;

  } else if ( myLock == OSD_ReadLock || myLock == OSD_ExclusiveLock ) {

   dwFlags = LOCKFILE_EXCLUSIVE_LOCK;

  } else

   dwFlags = 0;
 }

 if (Ret)
 {
  LARGE_INTEGER aSize;
  aSize.QuadPart = Size();
  if (!LockFileEx (myFileHandle, dwFlags, 0, aSize.LowPart, aSize.HighPart, &ovlp)) {

   _osd_wnt_set_error ( myError, OSD_WFile );
   Ret = false;

  }  // end if
 }
 if (Ret)
 {
  ImperativeFlag = Standard_True;
 }

}  // end OSD_File :: SetLock


void OSD_File :: UnLock () {

 TEST_RAISE(  "Unlock"  );

 if ( ImperativeFlag ) {
 
  LARGE_INTEGER aSize;
  aSize.QuadPart = Size();
  if (!UnlockFile (myFileHandle, 0, 0, aSize.LowPart, aSize.HighPart))
   
   _osd_wnt_set_error ( myError, OSD_WFile );

  ImperativeFlag = Standard_False;
 
 }  // end if

}  // end OSD_File :: UnLock

OSD_LockType OSD_File :: GetLock () {

 return myLock;

}  // end OSD_File :: GetLock

Standard_Boolean OSD_File :: IsLocked () {

 TEST_RAISE(  "IsLocked"  );

 return ImperativeFlag;

}  // end OSD_File :: IsLocked


// -------------------------------------------------------------------------- 
// Return size of a file
// -------------------------------------------------------------------------- 

Standard_Size OSD_File :: Size () {

 Standard_Integer retVal;

 TEST_RAISE(  "Size"  );

 LARGE_INTEGER aSize;
 aSize.QuadPart = 0;
 retVal = GetFileSizeEx (myFileHandle, &aSize);

 if (  retVal == 0  )

  _osd_wnt_set_error ( myError, OSD_WFile );

 return (Standard_Size)aSize.QuadPart;

}  // end OSD_File :: Size

// -------------------------------------------------------------------------- 
// Print contains of a file
// -------------------------------------------------------------------------- 

void OSD_File :: Print ( const OSD_Printer& WhichPrinter ) {

 if (myFileHandle != INVALID_HANDLE_VALUE)

  RAISE(  "OSD_File :: Print (): incorrect call - file opened"  );

 TCollection_AsciiString pName, fName;

 WhichPrinter.Name ( pName );
 myPath.SystemName ( fName );
 TCollection_ExtendedString fNameW(fName);

 if (   !_osd_print ( (Standard_PCharacter)pName.ToCString (),
                      (const wchar_t*)fNameW.ToExtString ()  )   )

  _osd_wnt_set_error ( myError, OSD_WFile );

}  // end OSD_File :: Print

// -------------------------------------------------------------------------- 
// Test if a file is open
// -------------------------------------------------------------------------- 

Standard_Boolean OSD_File :: IsOpen () const {

 return myFileHandle != INVALID_HANDLE_VALUE;

}  // end OSD_File :: IsOpen


PSECURITY_DESCRIPTOR __fastcall _osd_wnt_protection_to_sd (
                                 const OSD_Protection& prot, BOOL fDir, wchar_t* fName
                                ) {

 int                  i, j;
 BOOL                 fOK      = FALSE;
 PACL                 pACL     = NULL;
 HANDLE               hProcess = NULL;
 PSID                 pSIDowner;
 PSID                 pSIDadmin;
 PSID                 pSIDworld;
 PSID                 pSIDtemp;
 DWORD                dwAccessAdmin;
 DWORD                dwAccessGroup;
 DWORD                dwAccessOwner;
 DWORD                dwAccessWorld;
 DWORD                dwAccessAdminDir;
 DWORD                dwAccessGroupDir;
 DWORD                dwAccessOwnerDir;
 DWORD                dwAccessWorldDir;
 DWORD                dwACLsize       = sizeof ( ACL );
 DWORD                dwIndex         = 0;
 PTOKEN_OWNER         pTkOwner        = NULL;
 PTOKEN_GROUPS        pTkGroups       = NULL;
 PTOKEN_PRIMARY_GROUP pTkPrimaryGroup = NULL;
 PSECURITY_DESCRIPTOR retVal = NULL;
 PSECURITY_DESCRIPTOR pfSD = NULL;
 BOOL                 fDummy;
 PFILE_ACE            pFileACE;
 bool                 Ret = true;

 if (Ret) {

  j = fDir ? 1 : 0;

  if (  !OpenProcessToken (
          GetCurrentProcess (), TOKEN_QUERY, &hProcess
         )
  ) Ret = false;
 }

  if (Ret) {
  if (   (  pTkGroups = ( PTOKEN_GROUPS )GetTokenInformationEx (
                                          hProcess, TokenGroups
                                         )
         ) == NULL
  ) Ret = false;
  }
  
  if (Ret)
  {
  if (   (  pTkOwner = ( PTOKEN_OWNER )GetTokenInformationEx (
                                        hProcess, TokenOwner
                                       )
         ) == NULL
  ) Ret = false;
  }

  if (Ret)
  {
  if (   (  pTkPrimaryGroup = ( PTOKEN_PRIMARY_GROUP )GetTokenInformationEx (
                                                       hProcess, TokenPrimaryGroup
                                                      )
         ) == NULL
  ) Ret = false;
  }

  if (Ret)
  {

retry:
  if ( fName == NULL )

   pSIDowner = pTkOwner -> Owner;

  else {

   pfSD = GetFileSecurityEx ( fName, OWNER_SECURITY_INFORMATION );

   if (  pfSD == NULL || !GetSecurityDescriptorOwner ( pfSD, &pSIDowner, &fDummy )  ) {

    fName = NULL;
    goto retry;

   }  // end if

  }  // end else

  pSIDadmin = AdminSid ();
  pSIDworld = WorldSid ();

  dwAccessAdmin = _get_access_mask (  prot.System ()  );
  dwAccessGroup = _get_access_mask (  prot.Group  ()  );
  dwAccessOwner = _get_access_mask (  prot.User   ()  );
  dwAccessWorld = _get_access_mask (  prot.World  ()  );

  dwAccessAdminDir = _get_dir_access_mask (  prot.System ()  );
  dwAccessGroupDir = _get_dir_access_mask (  prot.Group  ()  );
  dwAccessOwnerDir = _get_dir_access_mask (  prot.User   ()  );
  dwAccessWorldDir = _get_dir_access_mask (  prot.World  ()  );

  if (  dwAccessGroup != 0  ) {
                                             
   for ( i = 0; i < ( int )pTkGroups -> GroupCount; ++i ) {

    pSIDtemp = pTkGroups -> Groups[ i ].Sid;

    if (  !NtPredefinedSid ( pSIDtemp                                  ) &&
          !EqualSid        ( pSIDtemp, pSIDworld                       ) &&
          !EqualSid        ( pSIDtemp, pTkPrimaryGroup -> PrimaryGroup ) &&
           IsValidSid      ( pSIDtemp                                  )
    )

     dwACLsize += ( (  GetLengthSid ( pSIDtemp ) + ACE_HEADER_SIZE  ) << j );

   }  // end for
  
  }  // end if

  dwACLsize += (  ( ( GetLengthSid ( pSIDowner ) + ACE_HEADER_SIZE ) << j ) +
                  ( ( GetLengthSid ( pSIDadmin ) + ACE_HEADER_SIZE ) << j ) +
                  ( ( GetLengthSid ( pSIDworld ) + ACE_HEADER_SIZE ) << j )
               );

  if (   (  pACL = CreateAcl ( dwACLsize )  ) == NULL   ) Ret = false;
  }

  if (Ret)
  {

  if ( dwAccessAdmin != 0 )

   if (   (  pFileACE = ( PFILE_ACE )AllocAccessAllowedAce (
                                      dwAccessAdmin, 0,
                                      pSIDadmin
                                     )
           ) != NULL
   ) {

    AddAce ( pACL, ACL_REVISION, dwIndex++, pFileACE, pFileACE -> header.AceSize );

    if ( fDir ) {

     pFileACE -> dwMask = dwAccessAdminDir;
     pFileACE -> header.AceFlags = OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE;
     AddAce ( pACL, ACL_REVISION, dwIndex++, pFileACE, pFileACE -> header.AceSize );

    }  // end if

    FreeAce ( pFileACE );

   }  // end if

  if ( dwAccessOwner != 0 )

   if (   (  pFileACE = ( PFILE_ACE )AllocAccessAllowedAce (
                                      dwAccessOwner, 0, pSIDowner
                                     )
          ) != NULL
   ) {

    AddAce ( pACL, ACL_REVISION, dwIndex++, pFileACE, pFileACE -> header.AceSize );

    if ( fDir ) {

     pFileACE -> dwMask = dwAccessOwnerDir;
     pFileACE -> header.AceFlags = OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE;
     AddAce ( pACL, ACL_REVISION, dwIndex++, pFileACE, pFileACE -> header.AceSize );
   
    }  // end if

    FreeAce ( pFileACE );

   }  // end if

  if ( dwAccessWorld != 0 )

   if (   (  pFileACE = ( PFILE_ACE )AllocAccessAllowedAce (
                                      dwAccessWorld, 0, pSIDworld
                                     )
          ) != NULL
   ) {

    AddAce ( pACL, ACL_REVISION, dwIndex++, pFileACE, pFileACE -> header.AceSize );

    if ( fDir ) {

     pFileACE -> header.AceFlags = OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE;
     AddAce ( pACL, ACL_REVISION, dwIndex++, pFileACE, pFileACE -> header.AceSize );
   
    }  // end if

    FreeAce ( pFileACE );

   }  // end if

  if ( dwAccessGroup != 0 ) {

   for ( i = 0; i < ( int )pTkGroups -> GroupCount; ++i ) {

    pSIDtemp = pTkGroups -> Groups[ i ].Sid;

    if (  !NtPredefinedSid ( pSIDtemp                                  ) &&
          !EqualSid        ( pSIDtemp, pSIDworld                       ) &&
          !EqualSid        ( pSIDtemp, pTkPrimaryGroup -> PrimaryGroup ) &&
           IsValidSid      ( pSIDtemp                                  )
    ) {

     if ( dwAccessGroup != 0 )

      if (   (  pFileACE = ( PFILE_ACE )AllocAccessAllowedAce (
                                         dwAccessGroup, 0, pSIDtemp
                                        )
             ) != NULL
      ) {

       AddAce ( pACL, ACL_REVISION, dwIndex++, pFileACE, pFileACE -> header.AceSize );

      if ( fDir ) {

       pFileACE -> header.AceFlags = OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE;
       AddAce ( pACL, ACL_REVISION, dwIndex++, pFileACE, pFileACE -> header.AceSize );
   
      }  // end if

      FreeAce ( pFileACE );

     }  // end if

    }  // end if

   }  // end for

  }  // end if
  } // if (Ret)

  if (Ret)
  if (   (  retVal = AllocSD ()  ) == NULL   ) Ret = false;

  if (Ret)
  if (  !SetSecurityDescriptorDacl ( retVal, TRUE, pACL, TRUE )  ) Ret = false;

  if (Ret)
  fOK = TRUE;

  if ( !fOK ) {

   if ( retVal != NULL )
       
    FreeSD ( retVal );

   else if ( pACL != NULL )

    FreeAcl ( pACL );

   retVal = NULL;
  
  }  // end if

  if ( hProcess        != NULL ) CloseHandle          ( hProcess        );
  if ( pTkOwner        != NULL ) FreeTokenInformation ( pTkOwner        );
  if ( pTkGroups       != NULL ) FreeTokenInformation ( pTkGroups       );
  if ( pTkPrimaryGroup != NULL ) FreeTokenInformation ( pTkPrimaryGroup );
  if ( pfSD            != NULL ) FreeFileSecurity     ( pfSD            );
 
 return retVal;
 
}  // end _osd_wnt_protection_to_sd */


static void __fastcall _test_raise ( HANDLE hFile, Standard_CString str ) {

 Standard_Character buff[ 64 ];

 if (hFile == INVALID_HANDLE_VALUE) {
 
  strcpy (  buff, "OSD_File :: "  );
  strcat (  buff, str );
  strcat (  buff, " (): wrong access"  );

  Standard_ProgramError :: Raise ( buff );
 
 }  // end if

}  // end _test_raise

// Modified so that we have <nl> at end of line if we have read <nl> or <cr>
// by LD 17 dec 98 for B4.4

static DWORDLONG __fastcall _get_line ( Standard_PCharacter& buffer, DWORD dwBuffSize ) {

 DWORDLONG        retVal;
 Standard_PCharacter ptr;

 buffer[ dwBuffSize ] = 0;
 ptr                  = buffer;

 while ( *ptr != 0 ) {
 
  if (  *ptr == '\n'  ) {
  
   ptr++ ;   // jump newline char.
   *ptr = 0 ;
   retVal = ptr - buffer - dwBuffSize;
   retVal &= 0x0000000FFFFFFFF;// import 32-bit to 64-bit
#ifdef VAC
   retVal = (DWORDLONG) ( (unsigned __int64) retVal | (((unsigned __int64) ptr) << 32) );
#else
   retVal |= (   (  ( DWORDLONG )( DWORD )ptr  ) << 32   );
#endif   
   return retVal;
  
  } else if (  *ptr == '\r' && ptr[ 1 ] == '\n'  ) {
  
   *(ptr++) = '\n' ; // Substitue carriage return by newline.
   *ptr = 0 ;
   retVal = ptr + 1 - buffer - dwBuffSize;
   retVal &= 0x0000000FFFFFFFF;// import 32-bit to 64-bit
#ifdef VAC
   retVal = (DWORDLONG) ( (unsigned __int64) retVal | (((unsigned __int64) ptr) << 32) );
#else
   retVal |= (   (  ( DWORDLONG )( DWORD )ptr  ) << 32   );
#endif
   return retVal;
  
  } else if (  *ptr == '\r' && ptr[ 1 ] == 0  ) {
    *ptr = '\n' ; // Substitue carriage return by newline

#ifdef VAC  
    return (DWORDLONG) (__int64) (-1);
#else
    return 0xFFFFFFFFFFFFFFFF;
#endif
  }
  ++ptr;
  
 }  // end while

#ifdef VAC
 retVal  = (DWORDLONG) ( ( (unsigned __int64) ((DWORD) buffer + dwBuffSize) ) << 32 );
 retVal = (DWORDLONG) ( (unsigned __int64) retVal & (((unsigned __int64) 0xFFFFFFFF) << 32) );
#else
 retVal  = (   (  ( DWORDLONG )( ( DWORD )buffer + dwBuffSize )  ) << 32   );
 retVal &= 0xFFFFFFFF00000000;
#endif

 return retVal;

}  // end _get_line

static int __fastcall _get_buffer (
                        HANDLE hChannel,
                        Standard_PCharacter& buffer, 
				   DWORD dwSize,
                        BOOL fPeek, BOOL fSocket
                       ) {

 int   retVal = -1;
 int   flags;
 DWORD dwDummy;
 DWORD dwBytesRead;

 if ( fSocket ) {
 
  flags = fPeek ? MSG_PEEK : 0;

  retVal = recv (  ( SOCKET )hChannel, buffer, ( int )dwSize, flags  );

  if ( retVal == SOCKET_ERROR ) retVal = -1;

 } else {
 
  if ( fPeek ) {
   
   if (  !PeekNamedPipe (
           hChannel, buffer, dwSize, &dwBytesRead, &dwDummy, &dwDummy
          ) && GetLastError () != ERROR_BROKEN_PIPE
   )

    retVal = -1;

   else

    retVal = ( int )dwBytesRead;
   
  } else {

   if (  !ReadFile ( hChannel, buffer, dwSize, &dwBytesRead, NULL )  )
       
    retVal = -1;

   else

    retVal = ( int )dwBytesRead;
   
  }  // end else
 
 }  // end else

 return retVal;

}  // end _get_buffer


static DWORD __fastcall _get_access_mask ( OSD_SingleProtection prt ) {

 DWORD retVal = 0;

 switch ( prt ) {
 
  case OSD_None:

   retVal = 0;

  break;

  case OSD_R:

   retVal = FILE_GENERIC_READ;

  break;

  case OSD_W:

   retVal = FILE_GENERIC_WRITE;

  break;

  case OSD_RW:

   retVal = FILE_GENERIC_READ | FILE_GENERIC_WRITE;

  break;

  case OSD_X:

   retVal = FILE_GENERIC_EXECUTE;

  break;

  case OSD_RX:

   retVal = FILE_GENERIC_READ | FILE_GENERIC_EXECUTE;

  break;

  case OSD_WX:

   retVal = FILE_GENERIC_WRITE | FILE_GENERIC_EXECUTE;

  break;

  case OSD_RWX:

   retVal = FILE_GENERIC_READ | FILE_GENERIC_WRITE | FILE_GENERIC_EXECUTE;

  break;

  case OSD_D:

   retVal = DELETE;

  break;

  case OSD_RD:

   retVal = FILE_GENERIC_READ | DELETE;

  break;

  case OSD_WD:

   retVal = FILE_GENERIC_WRITE | DELETE;

  break;

  case OSD_RWD:

   retVal = FILE_GENERIC_READ | FILE_GENERIC_WRITE | DELETE;

  break;

  case OSD_XD:

   retVal = FILE_GENERIC_EXECUTE | DELETE;

  break;

  case OSD_RXD:

   retVal = FILE_GENERIC_READ | FILE_GENERIC_EXECUTE | DELETE;

  break;

  case OSD_WXD:

   retVal = FILE_GENERIC_WRITE | FILE_GENERIC_EXECUTE | DELETE;

  break;

  case OSD_RWXD:

   retVal = FILE_GENERIC_READ | FILE_GENERIC_WRITE | FILE_GENERIC_EXECUTE | DELETE;

  break;

  default:

   RAISE(  "_get_access_mask (): incorrect parameter"  );
 
 }  // end switch

 return retVal;

}  // end _get_access_mask

static DWORD __fastcall _get_dir_access_mask ( OSD_SingleProtection prt ) {

 DWORD retVal = 0;

 switch ( prt ) {
 
  case OSD_None:

   retVal = 0;

  break;

  case OSD_R:

   retVal = GENERIC_READ;

  break;

  case OSD_W:

   retVal = GENERIC_WRITE;

  break;

  case OSD_RW:

   retVal = GENERIC_READ | GENERIC_WRITE;

  break;

  case OSD_X:

   retVal = GENERIC_EXECUTE;

  break;

  case OSD_RX:

   retVal = GENERIC_READ | GENERIC_EXECUTE;

  break;

  case OSD_WX:

   retVal = GENERIC_WRITE | GENERIC_EXECUTE;

  break;

  case OSD_RWX:

   retVal = GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;

  break;

  case OSD_D:

   retVal = DELETE;

  break;

  case OSD_RD:

   retVal = GENERIC_READ | DELETE;

  break;

  case OSD_WD:

   retVal = GENERIC_WRITE | DELETE;

  break;

  case OSD_RWD:

   retVal = GENERIC_READ | GENERIC_WRITE | DELETE;

  break;

  case OSD_XD:

   retVal = GENERIC_EXECUTE | DELETE;

  break;

  case OSD_RXD:

   retVal = GENERIC_READ | GENERIC_EXECUTE | DELETE;

  break;

  case OSD_WXD:

   retVal = GENERIC_WRITE | GENERIC_EXECUTE | DELETE;

  break;

  case OSD_RWXD:

   retVal = GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE | DELETE;

  break;

  default:

   RAISE(  "_get_dir_access_mask (): incorrect parameter"  );
 
 }  // end switch

 return retVal;

}  // end _get_dir_access_mask

static HANDLE __fastcall _open_file (
                          Standard_CString fName,
                          OSD_OpenMode oMode,
                          DWORD dwOptions, LPBOOL fNew
                         ) {

 HANDLE retVal = INVALID_HANDLE_VALUE;
 DWORD  dwDesiredAccess = 0;
 DWORD  dwCreationDistribution;

 switch ( oMode ) {
  
  case OSD_ReadOnly:

   dwDesiredAccess = GENERIC_READ;

  break;

  case OSD_WriteOnly:

   dwDesiredAccess = GENERIC_WRITE;

  break;

  case OSD_ReadWrite:

   dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;

  break;

  default:

   RAISE(  "_open_file (): incorrect parameter"  );
  
 }  // end switch

 dwCreationDistribution = ( dwOptions != OPEN_NEW ) ? OPEN_EXISTING : CREATE_ALWAYS;

 // make wide character string from UTF-8
 TCollection_ExtendedString fNameW(fName, Standard_True);
 retVal = CreateFileW (
           (const wchar_t*) fNameW.ToExtString(), dwDesiredAccess,
           FILE_SHARE_READ | FILE_SHARE_WRITE,
           NULL, dwCreationDistribution, FILE_ATTRIBUTE_NORMAL, NULL
          );

 if ( retVal          == INVALID_HANDLE_VALUE &&
      dwOptions       == OPEN_APPEND          &&
      GetLastError () == ERROR_FILE_NOT_FOUND
 ) {

 
  dwCreationDistribution = CREATE_ALWAYS;
  
  retVal = CreateFileW (
            (const wchar_t*) fNameW.ToExtString(), dwDesiredAccess,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, dwCreationDistribution, FILE_ATTRIBUTE_NORMAL, NULL
           );

  *fNew = TRUE;

 }  // end if

 return retVal;

}  // end _open_file

Standard_Integer __fastcall _get_file_type (
                             Standard_CString fName, HANDLE fileHandle
                            ) {

 Standard_Integer retVal = 0;
 DWORD            dwType;
 int              fileType;

 fileType = (fileHandle == INVALID_HANDLE_VALUE ? 
             FILE_TYPE_DISK : GetFileType (fileHandle));

 switch ( fileType ) {
 
  case FILE_TYPE_UNKNOWN:

   retVal = FLAG_SOCKET;

  break;

  case FILE_TYPE_DISK:
  {
   // make wide character string from UTF-8
   TCollection_ExtendedString fNameW(fName, Standard_True);
   dwType = GetFileAttributesW ( (const wchar_t*) fNameW.ToExtString() );
   if (  dwType  != 0xFFFFFFFF  )

    retVal =  dwType & FILE_ATTRIBUTE_DIRECTORY ? FLAG_DIRECTORY : FLAG_FILE;

   else

    retVal = 0x80000000;
  }
  break;

  case FILE_TYPE_CHAR:

   retVal = FLAG_DEVICE;

  break;

  case FILE_TYPE_PIPE:

   retVal = FLAG_PIPE;

  break;
 
 }  // end switch

 return retVal;

}  // end _get_file_type


BOOL __fastcall _osd_wnt_sd_to_protection (
                 PSECURITY_DESCRIPTOR pSD, OSD_Protection& prot, BOOL fDir
                ) {

 int           i;
 BOOL          fPresent;
 BOOL          fDefaulted;
 PACL          pACL;
 PSID          pSIDowner;
 PSID          pSIDadmin;
 PSID          pSIDworld;
 LPVOID        pACE;
 DWORD         dwAccessOwner = 0;
 DWORD         dwAccessGroup = 0;
 DWORD         dwAccessAdmin = 0;
 DWORD         dwAccessWorld = 0;
 BOOL          retVal = FALSE;
 GET_PROT_FUNC _get_prot_func = fDir ? &_get_protection_dir : &_get_protection;

 BOOL          Ret = true;
 if (Ret) {

  if (  !GetSecurityDescriptorOwner ( pSD, &pSIDowner, &fDefaulted )  ) Ret = false;
 }

 if (Ret)
 {
  if (  !GetSecurityDescriptorDacl ( pSD, &fPresent, &pACL, &fDefaulted ) ||
        !fPresent
  ) Ret = false;
 }

 if (Ret)
 {
  if ( pSIDowner == NULL || pACL == NULL ) {
  
   SetLastError ( ERROR_NO_SECURITY_ON_OBJECT );
   Ret = false;
  }  // end if
 }
 if (Ret)
 {
  pSIDadmin = AdminSid ();
  pSIDworld = WorldSid ();

  for ( i = 0; i < ( int )pACL -> AceCount; ++i ) {
  
   if (  GetAce ( pACL, i, &pACE )  ) {
   
    if (   EqualSid (  pSIDowner, GET_SID( pACE )  )   )

     dwAccessOwner = (  ( PACE_HEADER )pACE  ) -> AceType == ACCESS_DENIED_ACE_TYPE ?
                     0 : *GET_MSK( pACE );

    else if (   EqualSid (  pSIDadmin, GET_SID( pACE )  )   )

     dwAccessAdmin = (  ( PACE_HEADER )pACE  ) -> AceType == ACCESS_DENIED_ACE_TYPE ?
                     0 : *GET_MSK( pACE );

    else if (   EqualSid (  pSIDworld, GET_SID( pACE )  )   )

     dwAccessWorld = (  ( PACE_HEADER )pACE  ) -> AceType == ACCESS_DENIED_ACE_TYPE ?
                     0 : *GET_MSK( pACE );

    else

     dwAccessGroup = (  ( PACE_HEADER )pACE  ) -> AceType == ACCESS_DENIED_ACE_TYPE ?
                     0 : *GET_MSK( pACE );
   
   }  // end if
  
  }  // end for

  prot.SetValues (
        ( *_get_prot_func ) ( dwAccessAdmin ),
        ( *_get_prot_func ) ( dwAccessOwner ),
        ( *_get_prot_func ) ( dwAccessGroup ),
        ( *_get_prot_func ) ( dwAccessWorld )
       );

  retVal = TRUE;
  
 }   
       
 return retVal;

}  // end _osd_wnt_sd_to_protection


static OSD_SingleProtection __fastcall _get_protection ( DWORD mask ) {

 OSD_SingleProtection retVal;

 switch ( mask ) {
 
  case FILE_GENERIC_READ:

   retVal = OSD_R;

  break;

  case FILE_GENERIC_WRITE:

   retVal = OSD_W;

  break;

  case FILE_GENERIC_READ | FILE_GENERIC_WRITE:

   retVal = OSD_RW;

  break;

  case FILE_GENERIC_EXECUTE:

   retVal = OSD_X;

  break;

  case FILE_GENERIC_READ | FILE_GENERIC_EXECUTE:

   retVal = OSD_RX;

  break;

  case FILE_GENERIC_WRITE | FILE_GENERIC_EXECUTE:

   retVal = OSD_WX;

  break;

  case FILE_GENERIC_READ | FILE_GENERIC_WRITE | FILE_GENERIC_EXECUTE:

   retVal = OSD_RWX;

  break;

  case DELETE:

   retVal = OSD_D;

  break;

  case FILE_GENERIC_READ | DELETE:

   retVal = OSD_RD;

  break;

  case FILE_GENERIC_WRITE | DELETE:

   retVal = OSD_WD;

  break;

  case FILE_GENERIC_READ | FILE_GENERIC_WRITE | DELETE:

   retVal = OSD_RWD;

  break;

  case FILE_GENERIC_EXECUTE | DELETE:

   retVal = OSD_XD;

  break;

  case FILE_GENERIC_READ | FILE_GENERIC_EXECUTE | DELETE:

   retVal = OSD_RXD;

  break;

  case FILE_GENERIC_WRITE | FILE_GENERIC_EXECUTE | DELETE:

   retVal = OSD_WXD;

  break;

  case FILE_ALL_ACCESS:
  case FILE_GENERIC_READ | FILE_GENERIC_WRITE | FILE_GENERIC_EXECUTE | DELETE:

   retVal = OSD_RWXD;

  break;

  case 0:
  default:

   retVal = OSD_None;
 
 }  // end switch

 return retVal;

}  // end _get_protection

static OSD_SingleProtection __fastcall _get_protection_dir ( DWORD mask ) {

 OSD_SingleProtection retVal;

 switch ( mask ) {
 
  case GENERIC_READ:

   retVal = OSD_R;

  break;

  case GENERIC_WRITE:

   retVal = OSD_W;

  break;

  case GENERIC_READ | GENERIC_WRITE:

   retVal = OSD_RW;

  break;

  case GENERIC_EXECUTE:

   retVal = OSD_X;

  break;

  case GENERIC_READ | GENERIC_EXECUTE:

   retVal = OSD_RX;

  break;

  case GENERIC_WRITE | GENERIC_EXECUTE:

   retVal = OSD_WX;

  break;

  case GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE:

   retVal = OSD_RWX;

  break;

  case DELETE:

   retVal = OSD_D;

  break;

  case GENERIC_READ | DELETE:

   retVal = OSD_RD;

  break;

  case GENERIC_WRITE | DELETE:

   retVal = OSD_WD;

  break;

  case GENERIC_READ | GENERIC_WRITE | DELETE:

   retVal = OSD_RWD;

  break;

  case GENERIC_EXECUTE | DELETE:

   retVal = OSD_XD;

  break;

  case GENERIC_READ | GENERIC_EXECUTE | DELETE:

   retVal = OSD_RXD;

  break;

  case GENERIC_WRITE | GENERIC_EXECUTE | DELETE:

   retVal = OSD_WXD;

  break;

  case FILE_ALL_ACCESS:
  case GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE | DELETE:

   retVal = OSD_RWXD;

  break;

  case 0:
  default:

   retVal = OSD_None;
 
 }  // end switch

 return retVal;

}  // end _get_protection_dir


BOOL __fastcall _osd_print (const Standard_PCharacter pName, const wchar_t* fName ) {

 BOOL   fOK, fJob;                
 HANDLE hPrinter = NULL;
 BYTE   jobInfo[ MAX_PATH + sizeof ( DWORD ) ];
 DWORD  dwNeeded, dwCode = 0;
 bool Ret = true;

 fOK = fJob = FALSE;

 if (Ret) {
 
  if (  !OpenPrinter ( Standard_PCharacter(pName), &hPrinter, NULL )  ) {
  
   hPrinter = NULL;
   Ret = false;
  
  }  // end if
 }

 if (Ret)
 {
  if (   !AddJobW (
           hPrinter, 1, jobInfo, MAX_PATH + sizeof ( DWORD ), &dwNeeded
          )
  ) Ret = false;
 }

 if (Ret)
 { 
  fJob = TRUE;

  if (  !CopyFileW (
          fName, (LPWSTR) (  ( ADDJOB_INFO_1* )jobInfo  ) -> Path, FALSE
         )
  )  Ret = false;
 }

 if (Ret)
 {
  if (  !ScheduleJob (
          hPrinter, (  ( ADDJOB_INFO_1* )jobInfo  ) -> JobId
         )
  ) Ret = false;
 }
  
 if (Ret)
  fOK = TRUE;

  if ( !fOK ) {
  
   BYTE  info[ 1024 ];
   DWORD dwBytesNeeded;

   dwCode = GetLastError ();

   if ( fJob && hPrinter != NULL ) {

    GetJob (
     hPrinter, (  ( ADDJOB_INFO_1* )jobInfo  ) -> JobId, 1, 
     info, 1024, &dwBytesNeeded
    );

    if ( fJob ) SetJob (
                 hPrinter,
                 (  ( ADDJOB_INFO_1* )jobInfo  ) -> JobId,
                 1, info, JOB_CONTROL_CANCEL
                );

   }  // end if

  }  // end if

  if ( hPrinter != NULL ) ClosePrinter ( hPrinter );

 if ( !fOK ) SetLastError ( dwCode );

 return fOK;
                
}  // end _osd_print


Standard_Boolean OSD_File::IsReadable()
{
  TCollection_AsciiString FileName ;
  HANDLE Channel ;

  myPath.SystemName(FileName) ;
  Channel = _open_file(FileName.ToCString(), OSD_ReadOnly, OPEN_OLD) ;
  if (Channel == INVALID_HANDLE_VALUE)
    return Standard_False ;
  else {
    CloseHandle (Channel) ;
    return Standard_True ;
  }
}


Standard_Boolean OSD_File::IsWriteable()
{
  TCollection_AsciiString FileName ;
  HANDLE Channel ;

  myPath.SystemName(FileName) ;
  Channel = _open_file(FileName.ToCString(), OSD_ReadWrite, OPEN_OLD) ;
  if (Channel == INVALID_HANDLE_VALUE)
    return Standard_False ;
  else {
    CloseHandle (Channel) ;
    return Standard_True ;
  }
}

Standard_Boolean OSD_File::IsExecutable()
{
  return IsReadable() ;

//  if (_access(FileName.ToCString(),0))
}

#endif /* _WIN32 */


// ---------------------------------------------------------------------
// Read lines in a file while it is increasing.
// Each line is terminated with a <nl>.
// ---------------------------------------------------------------------

#include <OSD.hxx>

Standard_Boolean OSD_File::ReadLastLine(TCollection_AsciiString& aLine,const Standard_Integer aDelay,const Standard_Integer aNbTries)
{
  static Standard_Integer MaxLength = 1000 ;
  Standard_Integer Len ;
  Standard_Integer Count = aNbTries ;

  if (Count <= 0)
      return Standard_False ;
  for(;;) {
    ReadLine(aLine, MaxLength, Len) ;
    if (!aLine.IsEmpty()) 
      return Standard_True ;
    if (!--Count)
      return Standard_False ;
    OSD::SecSleep(aDelay) ;
  }
}


Standard_Boolean OSD_File::Edit()
{
  cout << "Function OSD_File::Edit() not yet implemented." << endl;
  return Standard_False ;
}




