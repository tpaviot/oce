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

#ifndef __OSD_WNT_H
# define __OSD_WNT_H

# ifndef STRICT
#  define STRICT
# endif  /* STRICT */

# ifndef _INC_WINDOWS
#  include <windows.h>
# endif  /* _INC_WINDOWS */

# ifndef OSDAPI
#  if !defined(HAVE_NO_DLL)
#   ifdef __OSD_DLL
#    define OSDAPI __declspec( dllexport )
#   else
#    define OSDAPI __declspec( dllimport )
#   endif  /* OSD_DLL */
#  else
#   define OSDAPI
#  endif
# endif  /* OSDAPI */

#if defined(__CYGWIN32__)
#define _TINT int
#endif

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

enum DIR_RESPONSE { DIR_ABORT, DIR_RETRY, DIR_IGNORE };

enum MB_ITEMTYPE { MBT_BUTTON, MBT_ICON };

#define FLAG_READ_PIPE  0x00000001
#define FLAG_EOF        0x00000002
#define FLAG_FILE       0x00000004
#define FLAG_DIRECTORY  0x00000008
#define FLAG_PIPE       0x00000010
#define FLAG_SOCKET     0x00000020
#define FLAG_NAMED_PIPE 0x00000040
#define FLAG_DEVICE     0x00000080
#define FLAG_TYPE       0x0000007C

// 2 macros modified for VisualAge
//#define LODWORD( a ) ( DWORD )(   ( ( DWORDLONG )( a ) ) & 0x00000000FFFFFFFF   )
//#define HIDWORD( a ) ( DWORD )(   ( ( DWORDLONG )( a ) ) >> 32                  )

#ifdef __BORLANDC__
# define LODWORD( a ) ( DWORD )(   ( ( DWORDLONG )( a ) ) & 0x00000000FFFFFFFF   )
# define HIDWORD( a ) ( DWORD )(   ( ( DWORDLONG )( a ) ) >> 32                  )
#else
# define LODWORD( a ) ( DWORD )(   ( ( _int64 )( a ) ) & 0x00000000FFFFFFFF   )
# define HIDWORD( a ) ( DWORD )(   ( ( _int64 )( a ) ) >> 32                  )
#endif

typedef struct _group_sid {

                DWORD  nCount;
                PSID*  pSID;

               } GROUP_SID, *PGROUP_SID;

typedef struct _MB_DESC {

                MB_ITEMTYPE   itemType;
                int           itemId;
                const char*   buttonLabel;

               } MB_DESC, *LPMB_DESC;


typedef struct _file_ace {

                ACE_HEADER header;
                DWORD      dwMask;
                PSID       pSID;

               } FILE_ACE, *PFILE_ACE;

typedef void ( *MOVE_DIR_PROC   ) ( LPCWSTR, LPCWSTR );
typedef void ( *COPY_DIR_PROC   ) ( LPCWSTR, LPCWSTR );
typedef void ( *DELETE_DIR_PROC ) ( LPCWSTR          );

typedef DIR_RESPONSE ( *RESPONSE_DIR_PROC ) ( LPCWSTR );

#define GET_SID( pACE ) (  ( PSID )(   (  ( PBYTE )pACE    ) + \
                                       sizeof ( ACE_HEADER ) + \
                                       sizeof ( DWORD      )   \
                                   )                           \
                        )

#define GET_MSK( pACE ) (  ( PDWORD )(   (  ( PBYTE )pACE    ) + \
                                         sizeof ( ACE_HEADER )   \
                                     )                           \
                        )

PSECURITY_DESCRIPTOR OSDAPI AllocSD ( void                 );
void                 OSDAPI FreeSD  ( PSECURITY_DESCRIPTOR );

LPVOID OSDAPI GetTokenInformationEx ( HANDLE, TOKEN_INFORMATION_CLASS );
void   OSDAPI FreeTokenInformation  ( LPVOID                          );

PSECURITY_DESCRIPTOR OSDAPI GetFileSecurityEx ( LPCWSTR, SECURITY_INFORMATION );
void                 OSDAPI FreeFileSecurity  ( PSECURITY_DESCRIPTOR          );

BOOL OSDAPI LookupAccountSidEx ( PSID, LPWSTR*, LPWSTR* );
void OSDAPI FreeAccountNames   ( LPWSTR, LPWSTR         );

PSID OSDAPI GetSecurityDescriptorOwnerEx ( PSECURITY_DESCRIPTOR );
PSID OSDAPI GetSecurityDescriptorGroupEx ( PSECURITY_DESCRIPTOR );
PACL OSDAPI GetSecurityDescriptorDaclEx  ( PSECURITY_DESCRIPTOR );

PACL OSDAPI CreateAcl ( DWORD );
void OSDAPI FreeAcl   ( PACL  );

BOOL OSDAPI PredefinedSid   ( PSID );
BOOL OSDAPI NtPredefinedSid ( PSID );
PSID OSDAPI AdminSid        ( void );
PSID OSDAPI WorldSid        ( void );
PSID OSDAPI InteractiveSid  ( void );
PSID OSDAPI NetworkSid      ( void );
PSID OSDAPI LocalSid        ( void );
PSID OSDAPI DialupSid       ( void );
PSID OSDAPI BatchSid        ( void );
PSID OSDAPI CreatorOwnerSid ( void );
PSID OSDAPI NullSid         ( void );
PSID OSDAPI NtSid           ( void );

PSID OSDAPI CopySidEx ( PSID );
void OSDAPI FreeSidEx ( PSID );

PGROUP_SID OSDAPI AllocGroupSid ( PSECURITY_DESCRIPTOR );
void       OSDAPI FreeGroupSid  ( PGROUP_SID           );

PVOID OSDAPI AllocAccessAllowedAce ( DWORD, BYTE, PSID );
void  OSDAPI FreeAce ( PVOID );

BOOL OSDAPI MoveDirectory   ( LPCWSTR, LPCWSTR );
BOOL OSDAPI CopyDirectory   ( LPCWSTR, LPCWSTR );

void OSDAPI SetMoveDirectoryProc     ( MOVE_DIR_PROC     );
void OSDAPI SetCopyDirectoryProc     ( COPY_DIR_PROC     );
void OSDAPI SetResponseDirectoryProc ( RESPONSE_DIR_PROC );

# ifdef __cplusplus
}
# endif  /* __cplusplus */

#endif  /* __OSD_WNT_H */
