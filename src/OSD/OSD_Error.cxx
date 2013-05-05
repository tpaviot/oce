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


#ifndef WNT

#include <OSD_Error.ixx>
#include <OSD_ErrorList.hxx>
#include <stdio.h>

/* Created by Stephan GARNAUD (ARM) 1992 for Matra Datavision */

OSD_Error::OSD_Error(){
 myErrno = 0;
}


void OSD_Error::Reset(){
 myErrno = 0;
}

Standard_Boolean OSD_Error::Failed()const{
 if (myErrno == 0) return (Standard_False);
              else return (Standard_True);
}



void OSD_Error::SetValue(const Standard_Integer errcode,
                         const Standard_Integer from,
                         const TCollection_AsciiString& message){
 myErrno = errcode;
 myCode  = (OSD_WhoAmI)from;
 myMessage = message;
}



Standard_Integer OSD_Error::Error()const{
 return(extCode);
}

 
void OSD_Error::Perror() {
 TCollection_AsciiString buffer;

 if (myErrno == 0) return;

 buffer += " :\n ";
 extCode = ERR_SURPRISE;

 switch (myErrno){
  case EBADF  :
   switch (myCode){
    case OSD_WFile:
      buffer += "Invalid file descriptor or bad mode";
      extCode = ERR_FBADF;
      break;
     case OSD_WMailBox:
      buffer += "Invalid mail box identification";
      extCode = ERR_MBADF;
      break;
    default:
      break;
    }
    break;


#ifdef SUN
  case EBADMSG:
   switch (myCode){
    case OSD_WFile:
     buffer += 
     "The message waiting to be read on stream is not a data message";
     extCode = ERR_FBADMSG;
     break;
    default:
      break;
   }
   break;
#endif

  case EINVAL: 
   switch (myCode){
    case OSD_WFileNode:
      buffer += "Can't unlink '.' or '..'";
      extCode = ERR_FNINVAL;
      break;
    case OSD_WFile:
      buffer += "Invalid file descriptor";
      extCode = ERR_FINVAL;
      break;
    case OSD_WMailBox :
      buffer += "Internal error : invalid arguments";
      extCode = ERR_MINVAL;
      break;
    default :
      buffer += "User error : Bad parameter";
      extCode = ERR_INVAL;
      break;
   }
   break;
#if !defined(sun) && !defined(SOLARIS)
  case EDQUOT :
   switch (myCode){
    case OSD_WDirectory:
    case OSD_WFileNode:
    case OSD_WFile :
     buffer += "Exceed quota of disk blocks";
     extCode = ERR_QUOT;
     break;
    default:
      break;
   }
   break;
#endif

#ifdef SUN
  case EDEADLK:
   switch (myCode){
    case OSD_WFile:
     buffer += "Lock is already blocked by another process";
     extCode = ERR_FDEADLK;
     break;
    default:
      break;
   }
   break;
#endif

  case ENOLCK:
   switch (myCode){
    case OSD_WFile:
     buffer += "No more file lock entries available";
     extCode = ERR_FNOLCK;
     break;
    default:
      break;
   }
   break;
  case EOPNOTSUPP:
   switch (myCode){
    case OSD_WFile:
     buffer += "File descriptor doesn't refer to a file";
     extCode = ERR_FWFD;
     break;
    default:
     break;
   }
   break;
  case EACCES: 
    buffer += "Permission denied";
    extCode = ERR_ACCESS;
    break;
  case EBUSY:
   switch (myCode){
    case OSD_WFileNode:
     buffer += "Still used by system or a process";
     extCode = ERR_FNBUSY;
     break;
    default:
      break;
   }
   break;
  case ERANGE:
   switch (myCode){
    case OSD_WFile:
     buffer += "Not enough or too many bytes written";
     extCode = ERR_FRANGE;
     break;
    case OSD_WSemaphore:
    case OSD_WSharedMemory:
     buffer += "system overflow value.\n";
     buffer += "Try to reconfigure Kernel with greater values";
     extCode = ERR_RANGE;
     break;
    default:
      break;
   }
   break;
  case EPERM: 
   switch (myCode){
    case OSD_WPackage:
     buffer += "Permission denied";
     extCode = ERR_PPERM;
     break;
    case OSD_WFileNode:
     buffer += "Permission denied or can't unlink directory";
     extCode = ERR_FPERM;
     break;
    case OSD_WMailBox :
     buffer += "User error : processes using mail boxes must ";
     buffer += "be\nused by the same user";
     extCode = ERR_MPERM;
     break;
    default : 
     buffer += "abnormal error : you modified OSD library";
     extCode = ERR_PERM;
     break;
    }
    break;
  case EROFS:
   switch (myCode){
    case OSD_WFileNode:
    case OSD_WFile:
     buffer += "Read only file system";
     extCode = ERR_ROFS;
     break;
    default:
     break;
   }
   break;
  case ENXIO:
  case EIO :
   switch (myCode){
    case OSD_WDirectory:
    case OSD_WFileNode:
     buffer += "I/O error";
     extCode = ERR_IO;
     break;
    case OSD_WFile :
     buffer += "I/O error or Hang up from terminal";
     extCode = ERR_FIO;
     break;
    default:
     break;
   }
   break;
  case EISDIR :
   switch (myCode){
    case OSD_WFileNode:
    case OSD_WFile :
     buffer += "The File is a Directory";
     extCode = ERR_ISDIR;
     break;
    default:
     break;
    }
    break;

#ifdef SUN
  case EWOULDBLOCK:
   switch (myCode){
    case OSD_WFile:
     buffer += "File is locked";
     extCode = ERR_FLOCKED;
     break;
    default:
     break;
   }
   break;
#endif

#ifdef IRIX4
  case EWOULDBLOCK:
   switch (myCode){
    case OSD_WFile:
     buffer += "File is locked";
     extCode = ERR_FLOCKED;
     break;
    default:
     break;
   }
   break;
#endif

  case EAGAIN:
   switch (myCode){
    case OSD_WFile:
     buffer += "No data ready to be read/written";
     extCode = ERR_FAGAIN;
     break;
    default:
     break;
   }
   break;
  case ENOTDIR:
   switch(myCode){
    case OSD_WDirectory:
    case OSD_WFileNode:
    case OSD_WFile:
     buffer += "A component of path is not a Directory";
     extCode = ERR_NOTDIR;
     break;
    default:
     break;
   }
   break;
  case EMLINK:
   switch (myCode){
    case OSD_WDirectory:
    buffer += "Too many links";
    extCode = ERR_DMLINK;
    break;
    default:
     break;
   }
   break;
  case ELOOP :
   switch (myCode){
    case OSD_WDirectory:
    case OSD_WFileNode:
    case OSD_WFile :
     buffer += "Too many symbolic links";
     break;
    default:
     break;
   }
   break;
  case EFAULT:
   buffer += "User error : arguments point to an illegal address";
   extCode = ERR_FAULT;
   break;
  case EFBIG:
   switch (myCode){
    case OSD_WFile:
     buffer += "Exceed process's file size limit or the maximum file size";
     extCode = ERR_FFBIG; 
     break;
    case OSD_WSemaphore:
     buffer += "Internal error : wrong number for this semaphore";
     extCode = ERR_SFBIG;
     break;
    default:
     break;
   }
   break;
  case EINTR:
   buffer += "operation breaked by a signal";
   extCode = ERR_INTR;
   break;
  case EIDRM: 
   buffer += "Semaphore externaly removed from system";
   extCode = ERR_SIDRM;
   break;
  case ENOMEM: 
   buffer += "Not enough memory";
   extCode = ERR_NOMEM;
   break;
  case EMFILE : 
   switch(myCode){   
    case OSD_WFile :
       buffer += "Too many file descriptors are currently in use by this process";
       extCode = ERR_FMFILE;
       break;
    case OSD_WMailBox :
       buffer += "Too many mail boxes opened";
       extCode = ERR_MMFILE;
       break;
    case OSD_WSharedMemory :
       buffer += "The number of shared memory segments attached to the calling process \nwould exceed the system imposed limit.\n";
       buffer += "Try to reconfigure Kernel with greater values";
       extCode = ERR_SMMFILE;
       break;
    default:
     break;
    }
    break;
  case ENAMETOOLONG :
   buffer += "File name too long";
   extCode = ERR_NAMETOOLONG;
   break;
  case ENFILE :
   switch (myCode){
    case OSD_WFile:
     buffer += "Too many files are currently open in the system";
     extCode = ERR_FNFILE;
     break;
    default:
     break;
   }
   break;
  case EXDEV:
   switch (myCode){
    case OSD_WFileNode:
     buffer += "The link named by path2 and the file named by path1 are\n";
     buffer += "on different logical devices (file systems)";
     extCode = ERR_FNXDEV;
     break;
    default:
     break;
   }
   break;
  case ENOENT:
   switch (myCode){
    case OSD_WFileNode:
    case OSD_WFile:
     if (myMessage != "Open") buffer += "File doesn't exist or";
      buffer += "Invalid path (empty string)";
     extCode = ERR_NOENT;
     break;
    case OSD_WDirectory:
     buffer += "A component of the path prefix of path does not exist";
     extCode = ERR_DNOENT;
     break;
    case OSD_WSemaphore:
    case OSD_WSharedMemory:
     buffer += "User error : Has not been created";
     extCode = ERR_SNOENT;
     break;
    default:
     break;
    }
    break;
  case ENOSPC: {
   switch (myCode){
    case OSD_WDirectory:
    case OSD_WFile:
     buffer += "No more free space on file system";
     extCode = ERR_FNOSPC;
     break;
    case OSD_WSharedMemory: {
     buffer += "You exceed number of shared memory allowed.\n";
     buffer += "Try to reconfigure Kernel with greater values";
     extCode = ERR_SMNOSPC;
     break;
   }
    default:
     break;
   }
   break;
 }

//
// AIX maps ENOTEMPTY to EEXIST.  Move this case block to
// the EEXIST case block.
//
#if (!defined(_AIX)) && (!defined(AIX))
  case ENOTEMPTY:
   switch (myCode){
    case OSD_WFileNode:
     buffer += "Directory not empty";
     extCode = ERR_FNNOTEMPTY;
     break;
    default:
     break;
   }
   break;
#endif

  case EEXIST: 
   switch(myCode){
    case OSD_WFileNode:
     buffer += "Directory not empty";
     extCode = ERR_FNNOTEMPTY;
     break;
    case OSD_WFile:
     buffer += "OSD_Create and OSD_Exclude are set and the named file exists";
     extCode = ERR_FEXIST;
     break;
    default:
     buffer += "Identifier already exists for this key";
     extCode = ERR_EXIST;
     break;
   }
   break;
  case E2BIG: 
   buffer += "Too many Semaphore/Shared memory for a process.";
   buffer += "Reconfigure Kernel with greater values";
   extCode = ERR_TOOBIG;
   break;
  case ESRCH  : 
   switch (myCode){
    case OSD_WMailBox :
     buffer += "Server process is dead.\n";
     buffer += "There is no more process to communicate with";
     extCode = ERR_MSRCH;
     break;
    default:
     break;
    }
    break;
   default: {
     Standard_Character buf[255];
     //
     sprintf(buf,"%sUnknowm error #%d",buffer.ToCString(),myErrno);
     TCollection_AsciiString interm(buf);
     buffer = interm;
     extCode = ERR_UNKNOWN;
   }
 }
 buffer += ".\n\n";
 OSD_OSDError::Raise (buffer.ToCString());
}

#else

//------------------------------------------------------------------------
//-------------------  Windows NT sources for OSD_Error ------------------
//------------------------------------------------------------------------

#define STRICT
#include <OSD_Error.hxx>
#include <OSD_ErrorList.hxx>

#include <windows.h>

typedef struct _error_table {

                DWORD            wnt_error;
                Standard_Integer csf_error;

               } ERROR_TABLE;

static int      fPrefix     = 1;
static ostream* errorStream = &cerr;

static ERROR_TABLE commErrorTable [] = {

 { ERROR_INVALID_FUNCTION,      ERR_INVAL       },
 { ERROR_FILE_NOT_FOUND,        ERR_NOENT       },
 { ERROR_PATH_NOT_FOUND,        ERR_NOENT       },
 { ERROR_ACCESS_DENIED,         ERR_ACCESS      },
 { ERROR_ARENA_TRASHED,         ERR_NOMEM       },
 { ERROR_NOT_ENOUGH_MEMORY,     ERR_NOMEM       },
 { ERROR_INVALID_BLOCK,         ERR_NOMEM       },
 { ERROR_BAD_ENVIRONMENT,       ERR_TOOBIG      },
 { ERROR_INVALID_ACCESS,        ERR_INVAL       },
 { ERROR_INVALID_DATA,          ERR_INVAL       },
 { ERROR_INVALID_DRIVE,         ERR_NOENT       },
 { ERROR_CURRENT_DIRECTORY,     ERR_ACCESS      },
 { ERROR_NO_MORE_FILES,         ERR_NOENT       },
 { ERROR_LOCK_VIOLATION,        ERR_ACCESS      },
 { ERROR_SHARING_VIOLATION,     ERR_ACCESS      },
 { ERROR_BAD_NETPATH,           ERR_NOENT       },
 { ERROR_NETWORK_ACCESS_DENIED, ERR_ACCESS      },
 { ERROR_BAD_NET_NAME,          ERR_NOENT       },
 { ERROR_FILE_EXISTS,           ERR_EXIST       },
 { ERROR_CANNOT_MAKE,           ERR_ACCESS      },
 { ERROR_FAIL_I24,              ERR_ACCESS      },
 { ERROR_INVALID_PARAMETER,     ERR_INVAL       },
 { ERROR_DRIVE_LOCKED,          ERR_ACCESS      },
 { ERROR_INVALID_HANDLE,        ERR_INVAL       },
 { ERROR_NEGATIVE_SEEK,         ERR_INVAL       },
 { ERROR_SEEK_ON_DEVICE,        ERR_ACCESS      },
 { ERROR_NOT_LOCKED,            ERR_ACCESS      },
 { ERROR_BAD_PATHNAME,          ERR_NOENT       },
 { ERROR_LOCK_FAILED,           ERR_ACCESS      },
 { ERROR_ALREADY_EXISTS,        ERR_EXIST       },
 { ERROR_FILENAME_EXCED_RANGE,  ERR_NOENT       },
 { ERROR_NOT_ENOUGH_QUOTA,      ERR_QUOT        },
 { ERROR_IO_DEVICE,             ERR_IO          },
 { ERROR_INVALID_BLOCK,         ERR_FAULT       },
 { ERROR_BAD_THREADID_ADDR,     ERR_FAULT       },
 { ERROR_INVALID_ADDRESS,       ERR_FAULT       },
 { ERROR_MAPPED_ALIGNMENT,      ERR_FAULT       },
 { ERROR_BUFFER_OVERFLOW,       ERR_NAMETOOLONG }

};

#define COMM_ERR_TABLE_SIZE (  sizeof ( commErrorTable ) / sizeof ( commErrorTable[ 0 ] )  )

static ERROR_TABLE dirErrorTable[] = {

 { ERROR_FILE_NOT_FOUND,       ERR_NOENT },
 { ERROR_PATH_NOT_FOUND,       ERR_NOENT },
 { ERROR_INVALID_DRIVE,        ERR_NOENT },
 { ERROR_NO_MORE_FILES,        ERR_NOENT },
 { ERROR_BAD_NETPATH,          ERR_NOENT },
 { ERROR_BAD_NET_NAME,         ERR_NOENT },
 { ERROR_BAD_PATHNAME,         ERR_NOENT },
 { ERROR_FILENAME_EXCED_RANGE, ERR_NOENT }

};

#define DIR_ERR_TABLE_SIZE (  sizeof ( dirErrorTable ) / sizeof ( dirErrorTable[ 0 ] )  )

static ERROR_TABLE fileErrorTable[] = {

 { ERROR_INVALID_HANDLE,        ERR_FBADF   },
 { ERROR_INVALID_TARGET_HANDLE, ERR_FBADF   },
 { ERROR_DIRECT_ACCESS_HANDLE,  ERR_FBADF   },
 { ERROR_FILE_EXISTS,           ERR_EXIST   },
 { ERROR_ALREADY_EXISTS,        ERR_EXIST   },
 { ERROR_TOO_MANY_OPEN_FILES,   ERR_FMFILE  },
 { ERROR_INVALID_FUNCTION,      ERR_FINVAL  },
 { ERROR_INVALID_ACCESS,        ERR_FINVAL  },
 { ERROR_INVALID_DATA,          ERR_FINVAL  },
 { ERROR_INVALID_PARAMETER,     ERR_FINVAL  },
 { ERROR_INVALID_HANDLE,        ERR_FINVAL  },
 { ERROR_NEGATIVE_SEEK,         ERR_FINVAL  },
 { ERROR_IO_PENDING,            ERR_FAGAIN  },
 { ERROR_WRITE_FAULT,           ERR_FIO     },
 { ERROR_READ_FAULT,            ERR_FIO     },
 { ERROR_NET_WRITE_FAULT,       ERR_FIO     },
 { ERROR_IO_DEVICE,             ERR_FIO     },
 { ERROR_LOCK_VIOLATION,        ERR_FLOCKED },
 { ERROR_LOCK_FAILED,           ERR_FLOCKED }

};

#define FILE_ERR_TABLE_SIZE (  sizeof ( fileErrorTable ) / sizeof ( fileErrorTable[ 0 ] )  )

static ERROR_TABLE fileNodeErrorTable[] = {

 { ERROR_INVALID_FUNCTION,      ERR_FNINVAL    },
 { ERROR_INVALID_ACCESS,        ERR_FNINVAL    },
 { ERROR_INVALID_DATA,          ERR_FNINVAL    },
 { ERROR_INVALID_PARAMETER,     ERR_FNINVAL    },
 { ERROR_INVALID_HANDLE,        ERR_FNINVAL    },
 { ERROR_NEGATIVE_SEEK,         ERR_FNINVAL    },
 { ERROR_DISK_FULL,             ERR_FNOSPC     },
 { ERROR_DIR_NOT_EMPTY,         ERR_FNNOTEMPTY },
 { ERROR_NOT_SAME_DEVICE,       ERR_FNXDEV     }

};

#define FILE_NODE_ERR_TABLE_SIZE (  sizeof ( fileNodeErrorTable ) /    \
                                    sizeof ( fileNodeErrorTable[ 0 ] ) \
                                 )

static Standard_Integer _get_comm_error ( DWORD );

OSD_Error :: OSD_Error () {

 Reset ();

}  // end constructor ( 1 )

void OSD_Error :: Perror () {

  if (errorStream == NULL)
    return;

 Standard_Character buff[ 32 ];
 Standard_CString   ptr;

 if ( fPrefix ) {
 
  lstrcpy (  buff, TEXT( "Error ( " )  );

  switch ( myCode ) {
  
   case OSD_WDirectoryIterator:

    ptr = TEXT( "OSD_DirectoryIterator" );

   break;

   case OSD_WDirectory:

    ptr = TEXT( "OSD_Directory" );

   break;

   case OSD_WFileIterator:

    ptr = TEXT( "OSD_FileIterator" );

   break;

   case OSD_WFile:
  
    ptr = TEXT( "OSD_File" );

   break;

   case OSD_WFileNode:

    ptr = TEXT( "OSD_FileNode" );

   break;

   case OSD_WHost:

    ptr = TEXT( "OSD_Host" );

   break;

   case OSD_WProcess:

    ptr = TEXT( "OSD_Environment" );

   break;

   case OSD_WEnvironmentIterator:

    ptr = TEXT( "OSD_EnvironmentIterator" );

   break;

   case OSD_WEnvironment:

    ptr = TEXT( "OSD_Environment" );

   break;

   case OSD_WSharedMemory:

    ptr = TEXT( "OSD_SharedMemory" );

   break;

   case OSD_WDisk:

    ptr = TEXT( "OSD_Disk" );

   break;

   default:

    ptr = TEXT( "Unknown" );

  }  // end switch

  lstrcat ( buff, ptr );
  lstrcat (  buff, TEXT( " )" )  );
  ( *errorStream ) << buff;
 
 }  // end if ( fPrefix . . . )

 ( *errorStream ) << TEXT( ": " ) << myMessage.ToCString () << endl << flush;

}  // end OSD_Error :: Perror

void OSD_Error :: SetValue (
                   const Standard_Integer Errcode,
                   const Standard_Integer From,
                   const TCollection_AsciiString& Message
                  ) {

 int i;

 myErrno   = Errcode;
 myCode    = ( OSD_WhoAmI )From;
 myMessage = Message;

 switch ( From ) {
 
  case OSD_WDirectory:

   for ( i = 0; i < DIR_ERR_TABLE_SIZE; ++i )

    if ( dirErrorTable[ i ].wnt_error == ( DWORD )Errcode ) {

     extCode = dirErrorTable[ i ].csf_error;
     break;

   }  // end if

  if ( i == DIR_ERR_TABLE_SIZE ) extCode = _get_comm_error ( Errcode );

  break;

  case OSD_WFile:

   for ( i = 0; i < FILE_ERR_TABLE_SIZE; ++i )

    if ( fileErrorTable[ i ].wnt_error == ( DWORD )Errcode ) {

     extCode = fileErrorTable[ i ].csf_error;
     break;

   }  // end if

  if ( i == FILE_ERR_TABLE_SIZE ) extCode = _get_comm_error ( Errcode );

  break;
 
  case OSD_WFileNode:

   for ( i = 0; i < FILE_NODE_ERR_TABLE_SIZE; ++i )

    if ( fileNodeErrorTable[ i ].wnt_error == ( DWORD )Errcode ) {

     extCode = fileNodeErrorTable[ i ].csf_error;
     break;

   }  // end if

  if ( i == FILE_NODE_ERR_TABLE_SIZE ) extCode = _get_comm_error ( Errcode );

  break;

  default:

   extCode = _get_comm_error ( Errcode );

 }  // end switch

}  // end OSD_Error :: SetValue

Standard_Integer OSD_Error :: Error () const {

 return extCode;

}  // end OSD_Error :: Error

Standard_Boolean OSD_Error :: Failed () const {

 return myErrno == ERROR_SUCCESS ? Standard_False : Standard_True;

}  // end OSD_Error :: Failed

void OSD_Error :: Reset () {

 myErrno = ERROR_SUCCESS; 
 if (errorStream != NULL)
 {
   ( *errorStream ).clear ();
   ( *errorStream ).seekp ( 0 );
   ( *errorStream ).clear ();
 }

}  // end OSD_Error :: Reset

void SetErrorStream ( ostream* errStream ) {

 errorStream = errStream;

}  // end SetErrorStream

void EnablePrefix ( int fEnable ) {

 fPrefix = fEnable;

}  // end EnablePrefix

int ErrorPrefix ( void ) {

 return fPrefix;

}  // end ErrorPrefix

ostream* ErrorStream ( void ) {

 return errorStream;

}  // end ErrorStream

static Standard_Integer _get_comm_error ( DWORD dwCode ) {

 int              i;
 Standard_Integer retVal = ERR_SURPRISE;

 for ( i = 0; i < COMM_ERR_TABLE_SIZE; ++i )

  if ( commErrorTable[ i ].wnt_error == ( DWORD )dwCode ) {

   retVal = commErrorTable[ i ].csf_error;
   break;

  }  // end if

 return retVal;

}  // end _get_comm_error

#endif
