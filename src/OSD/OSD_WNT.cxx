// Created by: PLOTNIKOV Eugeny
// Copyright (c) 1996-1999 Matra Datavision
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

#ifdef WNT

/******************************************************************************/
/* File:      OSD_WNT.cxx                                                     */
/* Purpose:   Security management routines ( more convinient than WIN32       */
/*            ones ) and other convinient functions.                          */
/******************************************************************************/
/***/
#include <OSD_WNT_1.hxx>

#include <tchar.h>
#include <stdlib.h>
/***/
static void Init ( void );
/***/
static DWORD dwLevel;
/***/
class Init_OSD_WNT {  // provides initialization

 public:

  Init_OSD_WNT () { Init (); dwLevel = TlsAlloc (); }

}; // end Init_OSD_WNT

static Init_OSD_WNT initOsdWnt;
/***/
static BOOL   fInit = FALSE;
static PSID*  predefinedSIDs;
static HANDLE hHeap;
/***/
static DELETE_DIR_PROC   _delete_dir_proc;
static MOVE_DIR_PROC     _move_dir_proc;
static COPY_DIR_PROC     _copy_dir_proc;
static RESPONSE_DIR_PROC _response_dir_proc;
/***/
#define PREDEFINED_SIDs_COUNT           9
#define UNIVERSAL_PREDEFINED_SIDs_COUNT 5
/***/
#define SID_INTERACTIVE   0
#define SID_NETWORK       1
#define SID_LOCAL         2
#define SID_DIALUP        3
#define SID_BATCH         4
#define SID_CREATOR_OWNER 5
#define SID_ADMIN         6
#define SID_WORLD         7
#define SID_NULL          8
/***/
/******************************************************************************/
/* Function : AllocSD                                                       */
/* Purpose  : Allocates and initializes security identifier                 */
/* Returns  : Pointer to allocated SID on success, NULL otherwise           */
/* Warning  : Allocated SID must be deallocated by 'FreeSD' function        */
/******************************************************************************/
/***/
PSECURITY_DESCRIPTOR AllocSD ( void ) {

 PSECURITY_DESCRIPTOR retVal =
  ( PSECURITY_DESCRIPTOR )HeapAlloc (
                           hHeap, 0, sizeof ( SECURITY_DESCRIPTOR )
                          );

 if ( retVal != NULL &&
      !InitializeSecurityDescriptor ( retVal, SECURITY_DESCRIPTOR_REVISION )
 ) {
 
  HeapFree (  hHeap, 0, ( PVOID )retVal  );
  retVal = NULL;
 
 }  /* end if */

 return retVal; 

}  /* end AllocSD */
/***/
/******************************************************************************/
/* Function : FreeSD                                                        */
/* Purpose  : Deallocates security identifier which was allocated by the    */
/*            'AllocSD' function                                            */
/******************************************************************************/
/***/
void FreeSD ( PSECURITY_DESCRIPTOR pSD ) {

 BOOL   fPresent;
 BOOL   fDaclDefaulted;
 PACL   pACL;
 
 if (  GetSecurityDescriptorDacl ( pSD, &fPresent, &pACL, &fDaclDefaulted ) &&
       fPresent
 )

  HeapFree (  hHeap, 0, ( PVOID )pACL  );

 HeapFree (  hHeap, 0, ( PVOID )pSD  );

}  /* end FreeSD */
/***/
/******************************************************************************/
/* Function : GetTokenInformationEx                                         */
/* Purpose  : Allocates and fills out access token                          */
/* Returns  : Pointer to the access token on success, NULL otherwise        */
/* Warning  : Allocated access token  must be deallocated by                */
/*            'FreeTokenInformation' function                               */
/******************************************************************************/
/***/

LPVOID GetTokenInformationEx ( HANDLE hToken, TOKEN_INFORMATION_CLASS tic ) {

 DWORD  errVal;
 DWORD  dwSize;
 DWORD  dwSizeNeeded = 0;
 LPVOID buffer       = NULL;
 BOOL   fOK          = FALSE;
 bool   Ret = true;

  do {

   dwSize = dwSizeNeeded;
   errVal = ERROR_SUCCESS;
 
   if (  !GetTokenInformation ( hToken, tic, buffer, dwSize, &dwSizeNeeded )  ) {

    if (   (  errVal = GetLastError ()  ) != ERROR_INSUFFICIENT_BUFFER   )
    {    
      Ret = false;
      break;
    }

    if (  ( buffer = HeapAlloc (  hHeap, 0, dwSizeNeeded  ) ) == NULL  )
    {    
      Ret = false;
      break;
    }

   }  /* end if */
 
  } while ( errVal != ERROR_SUCCESS );

  if (Ret)
  fOK = TRUE;

  if ( !fOK && buffer != NULL ) {
  
   HeapFree ( hHeap, 0, buffer );
   buffer = NULL;
  
  }  /* end if */

 return buffer;

}  /* end GetTokenInformationEx */

/***/
/******************************************************************************/
/* Function : FreeTokenInformation                                          */
/* Purpose  : Deallocates access token which was allocated by the           */
/*            'GetTokenInformationEx' function                              */
/******************************************************************************/
/***/
void FreeTokenInformation ( LPVOID lpvTkInfo ) {

 HeapFree (  hHeap, 0, lpvTkInfo  );

}  /* end FreeTokenInformation */
/***/
/******************************************************************************/
/* Function : Init                                                          */
/* Purpose  : Allocates and initializes predefined security identifiers     */
/* Warning  : Generates 'STATUS_NO_MEMORY' software exception if there are  */
/*            insufficient of memory. This exception can be caught by using */
/*            software exception handling ( SEH ) mechanism                 */
/*            ( __try / __except )                                          */
/******************************************************************************/
/***/
static void Init ( void ) {

 SID_IDENTIFIER_AUTHORITY sidIDAnull    = SECURITY_NULL_SID_AUTHORITY;
 SID_IDENTIFIER_AUTHORITY sidIDAworld   = SECURITY_WORLD_SID_AUTHORITY;
 SID_IDENTIFIER_AUTHORITY sidIDANT      = SECURITY_NT_AUTHORITY;
 SID_IDENTIFIER_AUTHORITY sidIDAlocal   = SECURITY_LOCAL_SID_AUTHORITY;
 SID_IDENTIFIER_AUTHORITY sidIDAcreator = SECURITY_CREATOR_SID_AUTHORITY;

 if ( !fInit ) {

  predefinedSIDs = ( PSID* )HeapAlloc (
                             hHeap = GetProcessHeap (),
                             HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY,
                             PREDEFINED_SIDs_COUNT * sizeof ( PSID* )
                            );

  AllocateAndInitializeSid (
   &sidIDANT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
   0, 0, 0, 0, 0, 0, &predefinedSIDs[ SID_ADMIN ]
  );

  AllocateAndInitializeSid (
   &sidIDAworld, 1, SECURITY_WORLD_RID,
   0, 0, 0, 0, 0, 0, 0, &predefinedSIDs[ SID_WORLD ]
  );

  AllocateAndInitializeSid (
   &sidIDANT, 1, SECURITY_INTERACTIVE_RID,
   0, 0, 0, 0, 0, 0, 0, &predefinedSIDs[ SID_INTERACTIVE ]
  );

  AllocateAndInitializeSid (
   &sidIDANT, 1, SECURITY_NETWORK_RID,
   0, 0, 0, 0, 0, 0, 0, &predefinedSIDs[ SID_NETWORK ]
  );

  AllocateAndInitializeSid (
   &sidIDAlocal, 1, SECURITY_LOCAL_RID,
   0, 0, 0, 0, 0, 0, 0, &predefinedSIDs[ SID_LOCAL ]
  );

  AllocateAndInitializeSid (
   &sidIDANT, 1, SECURITY_DIALUP_RID,
   0, 0, 0, 0, 0, 0, 0, &predefinedSIDs[ SID_DIALUP ]
  );

  AllocateAndInitializeSid (
   &sidIDANT, 1, SECURITY_BATCH_RID,
   0, 0, 0, 0, 0, 0, 0, &predefinedSIDs[ SID_BATCH ]
  );

  AllocateAndInitializeSid (
   &sidIDAcreator, 1, SECURITY_CREATOR_OWNER_RID,
   0, 0, 0, 0, 0, 0, 0, &predefinedSIDs[ SID_CREATOR_OWNER ]
  );

  AllocateAndInitializeSid (
   &sidIDAnull, 1, SECURITY_NULL_RID,
   0, 0, 0, 0, 0, 0, 0, &predefinedSIDs[ SID_NULL ]
  );

  fInit = TRUE;

 }  /* end if */

}  /* end init */
/***/
/******************************************************************************/
/* Function : PredefinedSid                                                 */
/* Purpose  : Checks whether specified SID predefined or not                */
/* Returns  : TRUE if specified SID is predefined, FALSE otherwise          */
/******************************************************************************/
/***/
BOOL PredefinedSid ( PSID pSID ) {

 int i;

 for ( i = 0; i < PREDEFINED_SIDs_COUNT; ++i )
 
  if (  EqualSid ( pSID, predefinedSIDs[ i ] )  )

   return TRUE;
 
 return FALSE;

}  /* end PredefinedSid */
/***/
/******************************************************************************/
/* Function : NtPredefinedSid                                               */
/* Purpose  : Checks whether specified SID universal or not                 */
/* Returns  : TRUE if specified SID is NOT universal, FALSE otherwise       */
/******************************************************************************/
/***/
BOOL NtPredefinedSid ( PSID pSID ) {

 int                       i;
 PSID_IDENTIFIER_AUTHORITY pTestIDA;
 SID_IDENTIFIER_AUTHORITY  ntIDA = SECURITY_NT_AUTHORITY;
 PDWORD                    pdwTestSA;

 for ( i = 0; i < UNIVERSAL_PREDEFINED_SIDs_COUNT; ++i )

  if (  EqualSid ( pSID, predefinedSIDs[ i ] )  )

   return TRUE;

 pTestIDA = GetSidIdentifierAuthority ( pSID );

 if (   memcmp (  pTestIDA, &ntIDA, sizeof ( SID_IDENTIFIER_AUTHORITY )  ) == 0   ) {
 
  pdwTestSA = GetSidSubAuthority ( pSID, 0 );

  if ( *pdwTestSA == SECURITY_LOGON_IDS_RID )

   return TRUE;
     
 }  /* end if */

 return FALSE;

}  /* end NtPredefinedSid */
/***/
/******************************************************************************/
/* Function : AdminSid                                                      */
/* Purpose  : Returns SID of the administrative user account                */
/******************************************************************************/
/***/
PSID AdminSid ( void ) {

 return predefinedSIDs[ SID_ADMIN ];

}  /* end AdminSid */
/***/
/******************************************************************************/
/* Function : WorldSid                                                      */
/* Purpose  : Returns SID of group that includes all users                  */
/******************************************************************************/
/***/
PSID WorldSid ( void ) {

 return predefinedSIDs[ SID_WORLD ];

}  /* end WorldSid */
/***/
/******************************************************************************/
/* Function : InteractiveSid                                                */
/* Purpose  : Returns SID of group that includes all users logged on for    */
/*            interactive operation                                         */
/******************************************************************************/
/***/
PSID InteractiveSid ( void ) {

 return predefinedSIDs[ SID_INTERACTIVE ];

}  /* end InteractiveSID */
/***/
/******************************************************************************/
/* Function : NetworkSid                                                    */
/* Purpose  : Returns SID of group that includes all users logged on across */
/*            a network                                                     */
/******************************************************************************/
/***/
PSID NetworkSid ( void ) {

 return predefinedSIDs[ SID_NETWORK ];

}  /* end NetworkSid */
/***/
/******************************************************************************/
/* Function : LocalSid                                                      */
/* Purpose  : Returns SID of group that includes all users logged on locally*/
/******************************************************************************/
/***/
PSID LocalSid ( void ) {

 return predefinedSIDs[ SID_LOCAL ];

}  /* end LocalSid */
/***/
/******************************************************************************/
/* Function : DialupSid                                                     */
/* Purpose  : Returns SID of group that includes all users logged on to     */
/*            terminals using a dialup modem                                */
/******************************************************************************/
/***/
PSID DialupSid ( void ) {

 return predefinedSIDs[ SID_DIALUP ];
          
}  /* end DialupSid */
/***/
/******************************************************************************/
/* Function : BatchSid                                                      */
/* Purpose  : Returns SID of group that includes all users logged on using  */
/*            a batch queue facility                                        */
/******************************************************************************/
/***/
PSID BatchSid ( void ) {

 return predefinedSIDs[ SID_BATCH ];

}  /* end BatchSid */
/***/
/******************************************************************************/
/* Function : CreatorOwnerSid                                               */
/* Purpose  : Returns SID of 'CREATOR OWNER' special group                  */
/******************************************************************************/
/***/
PSID CreatorOwnerSid ( void ) {

 return predefinedSIDs[ SID_CREATOR_OWNER ];

}  /* end CreatorOwnerSid */
/***/
/******************************************************************************/
/* Function : NullSid                                                       */
/* Purpose  : Returns null SID                                              */
/******************************************************************************/
/***/
PSID NullSid ( void ) {

 return predefinedSIDs[ SID_NULL ];

}  /* end NullSid */
/***/
/******************************************************************************/
/* Function : GetFileSecurityEx                                             */
/* Purpose  : Allocates a security descriptor and fills it out by security  */
/*            information which belongs to the specified file               */
/* Returns  : Pointer to the allocated security descriptor on success       */
/*            NULL otherwise                                                */
/* Warning  : Allocated security descriptor must be deallocated by          */
/*            'FreeFileSecurity' function                                   */
/******************************************************************************/
/***/

PSECURITY_DESCRIPTOR GetFileSecurityEx ( LPCTSTR fileName, SECURITY_INFORMATION si ) {

 DWORD                errVal;
 DWORD                dwSize;
 DWORD                dwSizeNeeded = 0;
 PSECURITY_DESCRIPTOR retVal = NULL;
 BOOL                 fOK    = FALSE;
 bool                 Ret = true;
 

  do {

   dwSize = dwSizeNeeded;
   errVal = ERROR_SUCCESS;

   if (  !GetFileSecurity (
           fileName, si,
           retVal, dwSize, &dwSizeNeeded
          )
   ) {
 
    if (   (  errVal = GetLastError ()  ) != ERROR_INSUFFICIENT_BUFFER   ) {    
      Ret = false;
      break;
    }

    if (   (  retVal = ( PSECURITY_DESCRIPTOR )HeapAlloc ( hHeap, 0, dwSizeNeeded )
           ) == NULL
    ) {    
      Ret = false;
      break;
    }

   }  /* end if */
 
  } while ( errVal != ERROR_SUCCESS );

  if (Ret)
  fOK = TRUE;
 
  if ( !fOK && retVal != NULL ) {
  
   HeapFree ( hHeap, 0, retVal );
   retVal = NULL;
  
  }  /* end if */
 
 return retVal;

}  /* end GetFileSecurityEx */

/***/
/******************************************************************************/
/* Function : FreeFileSecurity                                              */
/* Purpose  : Deallocates security descriptor which was allocated by the    */
/*            'GetFileSecurityEx' function                                  */
/******************************************************************************/
/***/
void FreeFileSecurity ( PSECURITY_DESCRIPTOR pSD ) {

 HeapFree (  hHeap, 0, ( LPVOID )pSD  );

}  /* end FreeFileSecurity */
/***/
/******************************************************************************/
/* Function : LookupAccountSidEx                                            */
/* Purpose  : Looking for account corresponding to the given SID and returns*/
/*            a name of that account on success                             */
/* Returns  : TRUE if account was found in the security database            */
/*            FALSE otherwise                                               */
/* Warning  : If account was found then this function allocates memory      */
/*            needed to hold the name of that account and the name of the   */
/*            domain to which this account belongs. To free that memoty     */
/*            use 'FreeAccountNames' function                               */
/******************************************************************************/
/***/

BOOL LookupAccountSidEx ( PSID pSID, LPTSTR* name, LPTSTR* domain ) {

 DWORD        errVal;
 DWORD        dwSizeName   = 0;
 DWORD        dwSizeDomain = 0;
 BOOL         retVal       = FALSE;
 SID_NAME_USE eUse;
 bool Ret = true;

  do {   

   errVal = ERROR_SUCCESS;

   if (  !LookupAccountSid (
           NULL, pSID, *name, &dwSizeName, *domain, &dwSizeDomain, &eUse
          )
   ) {
   
    if (   (  errVal = GetLastError ()  ) != ERROR_INSUFFICIENT_BUFFER   ) 
    {    
      Ret = false;
      break;
    }

    if (   (  *name   = ( LPTSTR )HeapAlloc ( hHeap, 0, dwSizeName   )  ) == NULL ||
           (  *domain = ( LPTSTR )HeapAlloc ( hHeap, 0, dwSizeDomain )  ) == NULL
    ) 
    {    
      Ret = false;
      break;
    }
   
   }  /* end if */

  } while ( errVal != ERROR_SUCCESS );

  if (Ret)
  retVal = TRUE;

  if ( !retVal ) {
  
   if ( *name   == NULL ) HeapFree ( hHeap, 0, *name   );
   if ( *domain == NULL ) HeapFree ( hHeap, 0, *domain );
  
  }  /* end if */
 
 return retVal;

}  /* end LookupAccountSidEx */

/***/
/******************************************************************************/
/* Function : FreeAccountNames                                              */
/* Purpose  : Deallocates memory which was allocated by the                 */
/*            'LookupAccountSidEx' function                                 */
/******************************************************************************/
/***/
void FreeAccountNames ( LPTSTR lpszName, LPTSTR lpszDomain ) {

 HeapFree (  hHeap, 0, ( PVOID )lpszDomain  );
 HeapFree (  hHeap, 0, ( PVOID )lpszName    );

}  /* end FreeAccountNames */
/***/
/******************************************************************************/
/* Function : GetSecurityDescriptorOwnerEx                                  */
/* Purpose  : Returns owner SID in the specified security descriptor.       */
/*            If specified security descriptor does not have an owner field */
/*            then returns NULL                                             */
/******************************************************************************/
/***/
PSID GetSecurityDescriptorOwnerEx ( PSECURITY_DESCRIPTOR pSD ) {

 BOOL bDummy;
 PSID retVal;

 if (  !GetSecurityDescriptorOwner ( pSD, &retVal, &bDummy )  )
  
  retVal = NULL;

 return retVal;

}  /* end GetSecurityDescriptorOwnerEx */
/***/
/******************************************************************************/
/* Function : GetSecurityDescriptorGroupEx                                  */
/* Purpose  : Returns primary group SID in the specified security           */
/*            descriptor. If specified security descriptor does not have a  */
/*            primary group field then returns NULL                         */
/******************************************************************************/
/***/
PSID GetSecurityDescriptorGroupEx ( PSECURITY_DESCRIPTOR pSD ) {

 BOOL bDummy;
 PSID retVal;

 if (  !GetSecurityDescriptorGroup ( pSD, &retVal, &bDummy )  )
  
  retVal = NULL;

 return retVal;

}  /* end GetSecurityDescriptorGroupEx */
/***/
/******************************************************************************/
/* Function : GetSecurityDescriptorDaclEx                                   */
/* Purpose  : Returns a pointer to the discretionary access-control list in */
/*            the specified security descriptor. If specified security      */
/*            descriptor does not have a discretionary access-control list  */
/*            then returns NULL                                             */
/******************************************************************************/
/***/
PACL GetSecurityDescriptorDaclEx ( PSECURITY_DESCRIPTOR pSD ) {

 PACL retVal;
 BOOL bDummy;
 BOOL fPresent;

 if (  !GetSecurityDescriptorDacl ( pSD, &fPresent, &retVal, &bDummy ) ||
       !fPresent
 )

  retVal = NULL;

 return retVal;
 
}  /* end GetSecurityDescriptorDaclEx */
/***/
/******************************************************************************/
/* Function : CreateAcl                                                     */
/* Purpose  : Allocates and initializes access-control list                 */
/* Returns  : Pointer to the allocated and initialized ACL on success,      */
/*            NULL otherwise                                                */
/* Warning  : Allocated ACL must be deallocated by 'FreeAcl' function       */
/******************************************************************************/
/***/
PACL CreateAcl ( DWORD dwAclSize ) {

 PACL retVal;

 retVal = ( PACL )HeapAlloc ( hHeap, 0, dwAclSize );

 if ( retVal != NULL )

  InitializeAcl ( retVal, dwAclSize, ACL_REVISION );

 return retVal;

}  /* end CreateAcl */
/***/
/******************************************************************************/
/* Function : FreeAcl                                                       */
/* Purpose  : Deallocates access-control list which was allocated by the    */
/*            'CreateAcl' function                                          */
/******************************************************************************/
/***/
void FreeAcl ( PACL pACL ) {

 HeapFree (  hHeap, 0, ( PVOID )pACL  );

}  /* end FreeAcl */
/***/
/******************************************************************************/
/* Function : CopySidEx                                                     */
/* Purpose  : Makes a copy of the SID                                       */
/* Returns  : Pointer to the copy of the specified SID on success,          */
/*            NULL otherwise                                                */
/* Warning  : Allocated SID must be deallocated by 'FreeSidEx' function     */
/******************************************************************************/
/***/
PSID CopySidEx ( PSID pSIDsrc ) {

 DWORD dwLen;
 PSID  retVal;

 dwLen  = GetLengthSid ( pSIDsrc );
 retVal = ( PSID )HeapAlloc ( hHeap, 0, dwLen );

 if ( retVal != NULL )

  CopySid ( dwLen, retVal, pSIDsrc );

 return retVal;

}  /* end CopySidEx */
/***/
/******************************************************************************/
/* Function : FreeSidEx                                                     */
/* Purpose  : Deallocates SID which was allocated by the 'CopySidEx'        */
/*            function                                                      */
/******************************************************************************/
/***/
void FreeSidEx ( PSID pSID ) {

 HeapFree ( hHeap, 0, pSID );

}  /* end FreeSidEx */
/***/
/******************************************************************************/
/* Function : AllocGroupSid                                                 */
/* Purpose  : Allocates a structure which holds SIDs of groups which are    */
/*            not predefined. These SIDs is taking from the DACL of the     */
/*            specified security descriptor                                 */
/* Returns  : Pointer the allocated structure on success,                   */
/*            NULL otherwise                                                */
/* Warning  : Allocated structure must be deallocated by 'FreeGroupSid'     */
/*            function                                                      */
/******************************************************************************/
/***/
PGROUP_SID AllocGroupSid ( PSECURITY_DESCRIPTOR pSD ) {

 int        i;
 PGROUP_SID retVal  = NULL;
 PSID*      pSID    = NULL;
 DWORD      dwLen;
 DWORD      dwCount = 0;
 LPVOID     pACE;
 PACL       pACL;
 PSID       pSIDowner;
 PSID       pSIDadmin;
 PSID       pSIDworld;
 BOOL       fPresent;
 BOOL       fDefaulted;

 if (  GetSecurityDescriptorDacl ( pSD, &fPresent, &pACL, &fDefaulted ) &&
       fPresent                                                         &&
       GetSecurityDescriptorOwner ( pSD, &pSIDowner, &fDefaulted )      &&
       pSIDowner != NULL                                                &&
       (   retVal = ( PGROUP_SID )HeapAlloc (  hHeap, 0, sizeof ( GROUP_SID )  )   ) !=
        NULL
 ) {

  pSIDadmin = AdminSid ();
  pSIDworld = WorldSid ();
 
  for ( i = 0; i < ( int )pACL -> AceCount; ++i )
    if ( GetAce ( pACL, i, &pACE )                  &&
         !EqualSid (  pSIDadmin, GET_SID( pACE )  ) &&
         !EqualSid (  pSIDworld, GET_SID( pACE )  ) &&
         !EqualSid (  pSIDowner, GET_SID( pACE )  ) )
      ++dwCount;

  pSID    = ( PSID* )HeapAlloc (  hHeap, 0, dwCount * sizeof ( PSID )  );
  dwCount = 0;

  if ( pSID != NULL ) {
  
   for ( i = 0; i < ( int )pACL -> AceCount; ++i )
  
    if (  GetAce ( pACL, i, &pACE )                  &&
          !EqualSid (  pSIDadmin, GET_SID( pACE )  ) &&
          !EqualSid (  pSIDworld, GET_SID( pACE )  ) &&
          !EqualSid (  pSIDowner, GET_SID( pACE )  )
    ) {
   
     pSID[ dwCount ] = ( PSID )HeapAlloc (
                                hHeap, 0, dwLen = GetLengthSid (  GET_SID( pACE )  )
                               );

     if ( pSID[ dwCount ] != NULL )

      CopySid (  dwLen, pSID[ dwCount++ ], GET_SID( pACE )  );
   
    }  /* end if */

  }  /* end if */
    
  retVal -> nCount = dwCount;
  retVal -> pSID   = pSID;

 }  /* end if */

 return retVal;

}  /* end AllocGroupSid */
/***/
/******************************************************************************/
/* Function : FreeGroupSid                                                  */
/* Purpose  : Deallocates a structure which was allocated by the            */
/*            'AllocGroupSid' function                                      */
/******************************************************************************/
/***/
void FreeGroupSid ( PGROUP_SID pGSID ) {

 int i;

 for ( i = 0; i < ( int )pGSID -> nCount; ++i )

  HeapFree ( hHeap, 0, pGSID -> pSID[ i ] );

 HeapFree ( hHeap, 0, pGSID -> pSID );
 HeapFree ( hHeap, 0, pGSID         );

}  /* end FreeGroupSid */
/***/
/******************************************************************************/
/* Function : AllocAccessAllowedAce                                         */
/* Purpose  : Allocates and initializes access-control entry                */
/* Returns  : Pointer to the ACE on success, NULL othrwise                  */
/* Warning  : Allocated ACE must be deallocated by the 'FreeAce' function   */
/******************************************************************************/
/***/
PVOID AllocAccessAllowedAce ( DWORD dwMask, BYTE flags, PSID pSID ) {

 PFILE_ACE retVal;
 WORD      wSize;

 wSize = (WORD)( sizeof ( ACE_HEADER ) + sizeof ( DWORD ) + GetLengthSid ( pSID ) );

 retVal = ( PFILE_ACE )HeapAlloc ( hHeap, 0, wSize );

 if ( retVal != NULL ) {
 
  retVal -> header.AceType  = ACCESS_ALLOWED_ACE_TYPE;
  retVal -> header.AceFlags = flags;
  retVal -> header.AceSize  = wSize;

  retVal -> dwMask = dwMask;

  CopySid (  GetLengthSid ( pSID ), &retVal -> pSID, pSID  );
 
 }  /* end if */

 return retVal;

}  /* end AllocAccessAllowedAce */
/***/
/******************************************************************************/
/* Function : FreeAce                                                       */
/* Purpose  : Deallocates an ACE which was allocated by the                 */
/*            'AllocAccessAllowedAce ' function                             */
/******************************************************************************/
/***/
void FreeAce ( PVOID pACE ) {

 HeapFree ( hHeap, 0, pACE );

}  /* end FreeAce */

#define WILD_CARD     TEXT( "/*.*" )
#define WILD_CARD_LEN (  sizeof ( WILD_CARD )  )

/* LD : We do not need this routine any longer : */
/* Dont remove a no empty directory              */


#if 0

/***/
/******************************************************************************/
/* Function : DeleteDirectory                                               */
/* Purpose  : Deletes specified directory tree                              */
/* Returns  : TRUE on success, FALSE otherwise                              */
/******************************************************************************/
/***/
BOOL DeleteDirectory ( LPCTSTR dirName ) {

 PWIN32_FIND_DATA pFD;
 LPTSTR           pName = NULL;
 LPTSTR           pFullName = NULL;
 HANDLE           hFindFile = INVALID_HANDLE_VALUE;
 BOOL             fFind;
 BOOL             retVal = FALSE;
 DIR_RESPONSE     response;

 if (   (  pFD = ( PWIN32_FIND_DATA )HeapAlloc (
                                      hHeap, 0, sizeof ( WIN32_FIND_DATA )
                                     )
        ) != NULL &&
        (  pName = ( LPTSTR )HeapAlloc (
                              hHeap, 0, lstrlen ( dirName ) + WILD_CARD_LEN +
                              sizeof (  TEXT( '\x00' )  )
                             )
        ) != NULL
 ) {

  lstrcpy ( pName, dirName   );
  lstrcat ( pName, WILD_CARD );

  retVal = TRUE;
  fFind  = (  hFindFile = FindFirstFile ( pName, pFD )  ) != INVALID_HANDLE_VALUE;

  while ( fFind ) {

   if (  pFD -> cFileName[ 0 ] != TEXT( '.' ) ||
         pFD -> cFileName[ 0 ] != TEXT( '.' ) &&
         pFD -> cFileName[ 1 ] != TEXT( '.' )
   ) {

    if (   ( pFullName = ( LPTSTR )HeapAlloc (
                                    hHeap, 0,
                                    lstrlen ( dirName ) + lstrlen ( pFD -> cFileName ) +
                                    sizeof (  TEXT( '/' )  ) + sizeof (  TEXT( '\x00' )  )
                                   )
           ) == NULL
    ) break;

    lstrcpy ( pFullName, dirName );
    lstrcat (  pFullName, TEXT( "/" )  );
    lstrcat ( pFullName, pFD -> cFileName );
   
    if ( pFD -> dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {

     if (   !(  retVal = DeleteDirectory ( pFullName )  )   )

      break;
   
    } else {
retry:   
     if (   !(  retVal = DeleteFile ( pFullName )  )   ) {

      if ( _response_dir_proc != NULL ) {
      
       response = ( *_response_dir_proc ) ( pFullName );

       if ( response == DIR_ABORT )

        break;

       else if ( response == DIR_RETRY )

        goto retry;

       else if ( response == DIR_IGNORE )

        retVal = TRUE;

       else

        break;
      
      }  /* end if */

     } else if ( _delete_dir_proc != NULL )

      ( *_delete_dir_proc ) ( pFullName );

    }  /* end else */

    HeapFree ( hHeap, 0, pFullName );
    pFullName = NULL;

   }  /* end if */

   fFind = FindNextFile ( hFindFile, pFD );
  
  }  /* end while */

 }  /* end if */

 if ( hFindFile != INVALID_HANDLE_VALUE ) FindClose ( hFindFile );

 if ( pFullName != NULL ) HeapFree ( hHeap, 0, pFullName );
 if ( pName     != NULL ) HeapFree ( hHeap, 0, pName     );
 if ( pFD       != NULL ) HeapFree ( hHeap, 0, pFD       );

 if ( retVal ) {
retry_1:  
  retVal = RemoveDirectory ( dirName );

  if ( !retVal ) {
  
   if ( _response_dir_proc != NULL ) {
      
    response = ( *_response_dir_proc ) ( pFullName );

    if ( response == DIR_RETRY )

     goto retry_1;

    else if ( response == DIR_IGNORE )

     retVal = TRUE;

   }  /* end if */
  
  } else if ( _delete_dir_proc != NULL )

   ( *_delete_dir_proc ) ( dirName );

 }  /* end if */

 return retVal;

}  /* end DeleteDirectory */

#endif

/***/
/******************************************************************************/
/* Function : MoveDirectory                                                 */
/* Purpose  : Moves specified directory tree to the new location            */
/* Returns  : TRUE on success, FALSE otherwise                              */
/******************************************************************************/
/***/
BOOL MoveDirectory ( LPCTSTR oldDir, LPCTSTR newDir ) {

 PWIN32_FIND_DATA    pFD;
 LPTSTR              pName;
 LPTSTR              pFullNameSrc;
 LPTSTR              pFullNameDst;
 LPTSTR              driveSrc, driveDst;
 LPTSTR              pathSrc,  pathDst;
 HANDLE              hFindFile;
 BOOL                fFind;
 BOOL                retVal = FALSE;
 DIR_RESPONSE        response;
 DWORD               level;

 if (   (  level = ( DWORD )TlsGetValue ( dwLevel )  ) == NULL   ) {

  ++level;
  TlsSetValue (  dwLevel, ( LPVOID )level  );

  fFind = FALSE;
  driveSrc = driveDst = pathSrc = pathDst = NULL;
 
  if (   (  driveSrc = ( LPTSTR )HeapAlloc ( hHeap, 0, _MAX_DRIVE )  ) != NULL &&
         (  driveDst = ( LPTSTR )HeapAlloc ( hHeap, 0, _MAX_DRIVE )  ) != NULL &&
         (  pathSrc  = ( LPTSTR )HeapAlloc ( hHeap, 0, _MAX_DIR   )  ) != NULL &&
         (  pathDst  = ( LPTSTR )HeapAlloc ( hHeap, 0, _MAX_DIR   )  ) != NULL
  ) {
  
   _tsplitpath ( oldDir, driveSrc, pathSrc, NULL, NULL );
   _tsplitpath ( newDir, driveDst, pathDst, NULL, NULL );

   if (  _tcscmp ( driveSrc, driveDst ) == 0 &&
         _tcscmp ( pathSrc,  pathDst  ) == 0
   ) {
retry:   
    retVal = MoveFileEx (
              oldDir, newDir, MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED
             );
    fFind  = TRUE;

    if ( !retVal ) {
    
     if ( _response_dir_proc != NULL ) {
     
      response = ( *_response_dir_proc ) ( oldDir );

      if ( response == DIR_RETRY )

       goto retry;

      else if ( response == DIR_IGNORE )

       retVal = TRUE;

     }  /* end if */
    
    } else if ( _move_dir_proc != NULL )

     ( *_move_dir_proc ) ( oldDir, newDir );
    
   }  /* end if */
  
  }  /* end if */

  if ( pathDst  != NULL ) HeapFree ( hHeap, 0, pathDst  );
  if ( pathSrc  != NULL ) HeapFree ( hHeap, 0, pathSrc  );
  if ( driveDst != NULL ) HeapFree ( hHeap, 0, driveDst );
  if ( driveSrc != NULL ) HeapFree ( hHeap, 0, driveSrc );

  if ( fFind ) {
    
   --level;
   TlsSetValue (  dwLevel, ( LPVOID )level  );
   return retVal;

  }  // end if
 
 } else {
 
  ++level;
  TlsSetValue (  dwLevel, ( LPVOID )level  );
 
 }  // end else

 pFD          = NULL;
 pName        = NULL;
 pFullNameSrc = pFullNameDst = NULL;
 hFindFile    = INVALID_HANDLE_VALUE;
 retVal       = FALSE;

 retVal = CreateDirectory ( newDir, NULL );

 if (   retVal || (  !retVal && GetLastError () == ERROR_ALREADY_EXISTS  )   ) {

  if (   (  pFD = ( PWIN32_FIND_DATA )HeapAlloc (
                                       hHeap, 0, sizeof ( WIN32_FIND_DATA )
                                      )
         ) != NULL &&
         (  pName = ( LPTSTR )HeapAlloc (
                               hHeap, 0, lstrlen ( oldDir ) + WILD_CARD_LEN +
                               sizeof (  TEXT( '\x00' )  )
                              )
         ) != NULL
  ) {

   lstrcpy ( pName, oldDir    );
   lstrcat ( pName, WILD_CARD );

   retVal = TRUE;
   fFind  = (  hFindFile = FindFirstFile ( pName, pFD )  ) != INVALID_HANDLE_VALUE;

   while ( fFind ) {
  
    if (  pFD -> cFileName[ 0 ] != TEXT( '.' ) ||
          pFD -> cFileName[ 0 ] != TEXT( '.' ) &&
          pFD -> cFileName[ 1 ] != TEXT( '.' )
    ) {
  
     if (   ( pFullNameSrc = ( LPTSTR )HeapAlloc (
                                        hHeap, 0,
                                        lstrlen ( oldDir ) + lstrlen ( pFD -> cFileName ) +
                                        sizeof (  TEXT( '/' )  ) + sizeof (  TEXT( '\x00' )  )
                                       )
            ) == NULL ||
            ( pFullNameDst = ( LPTSTR )HeapAlloc (
                                        hHeap, 0,
                                        lstrlen ( newDir ) + lstrlen ( pFD -> cFileName ) +
                                        sizeof (  TEXT( '/' )  ) + sizeof (  TEXT( '\x00' )  )
                                       )
            ) == NULL
     ) break;
  
     lstrcpy ( pFullNameSrc, oldDir );
     lstrcat (  pFullNameSrc, TEXT( "/" )  );
     lstrcat ( pFullNameSrc, pFD -> cFileName );

     lstrcpy ( pFullNameDst, newDir );
     lstrcat (  pFullNameDst, TEXT( "/" )  );
     lstrcat ( pFullNameDst, pFD -> cFileName );

     if ( pFD -> dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {

      if (   FALSE == (  retVal = MoveDirectory ( pFullNameSrc, pFullNameDst )  )   ) break;
   
     } else {
retry_1:   
      if (   FALSE == (  retVal = MoveFileEx (
                           pFullNameSrc, pFullNameDst,
                           MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED
                          )
              )
      ) {
      
       if ( _response_dir_proc != NULL ) {
      
        response = ( *_response_dir_proc ) ( pFullNameSrc );

        if ( response == DIR_ABORT )

         break;

        else if ( response == DIR_RETRY )

         goto retry_1;

        else if ( response == DIR_IGNORE )

         retVal = TRUE;

        else

         break;

       }  /* end if */
      
      } else if ( _move_dir_proc != NULL )

       ( *_move_dir_proc ) ( pFullNameSrc, pFullNameDst );

     }  /* end else */

     HeapFree ( hHeap, 0, pFullNameDst );
     HeapFree ( hHeap, 0, pFullNameSrc );
     pFullNameSrc = pFullNameDst = NULL;

    }  /* end if */

    fFind = FindNextFile ( hFindFile, pFD );

   }  /* end while */

  }  /* end if */

 }  /* end if ( error creating directory ) */

 if ( hFindFile != INVALID_HANDLE_VALUE ) FindClose ( hFindFile );

 if ( pFullNameSrc != NULL ) HeapFree ( hHeap, 0, pFullNameSrc );
 if ( pFullNameDst != NULL ) HeapFree ( hHeap, 0, pFullNameDst );
 if ( pName        != NULL ) HeapFree ( hHeap, 0, pName        );
 if ( pFD          != NULL ) HeapFree ( hHeap, 0, pFD          );

 if ( retVal ) {
retry_2:  
  retVal = RemoveDirectory ( oldDir );

  if ( !retVal ) {
  
   if ( _response_dir_proc != NULL ) {
      
    response = ( *_response_dir_proc ) ( oldDir );

    if ( response == DIR_RETRY )

     goto retry_2;

    else if ( response == DIR_IGNORE )

     retVal = TRUE;

   }  /* end if */

  }  /* end if */
  
 }  /* end if */

 --level;
 TlsSetValue (  dwLevel, ( LPVOID )level  );

 return retVal;

}  /* end MoveDirectory */
/***/
/******************************************************************************/
/* Function : CopyDirectory                                                 */
/* Purpose  : Copies specified directory tree to the new location           */
/* Returns  : TRUE on success, FALSE otherwise                              */
/******************************************************************************/
/***/
BOOL CopyDirectory ( LPCTSTR dirSrc, LPCTSTR dirDst ) {

 PWIN32_FIND_DATA    pFD = NULL;
 LPTSTR              pName = NULL;
 LPTSTR              pFullNameSrc = NULL;
 LPTSTR              pFullNameDst = NULL;
 HANDLE              hFindFile = INVALID_HANDLE_VALUE;
 BOOL                fFind;
 BOOL                retVal = FALSE;
 DIR_RESPONSE        response;

 retVal = CreateDirectory ( dirDst, NULL );

 if (   retVal || (  !retVal && GetLastError () == ERROR_ALREADY_EXISTS  )   ) {

  if (   (  pFD = ( PWIN32_FIND_DATA )HeapAlloc (
                                       hHeap, 0, sizeof ( WIN32_FIND_DATA )
                                      )
         ) != NULL &&
         (  pName = ( LPTSTR )HeapAlloc (
                               hHeap, 0, lstrlen ( dirSrc ) + WILD_CARD_LEN +
                               sizeof (  TEXT( '\x00' )  )
                              )
         ) != NULL
  ) {

   lstrcpy ( pName, dirSrc    );
   lstrcat ( pName, WILD_CARD );

   retVal = TRUE;
   fFind  = (  hFindFile = FindFirstFile ( pName, pFD )  ) != INVALID_HANDLE_VALUE;

   while ( fFind ) {
  
    if (  pFD -> cFileName[ 0 ] != TEXT( '.' ) ||
          pFD -> cFileName[ 0 ] != TEXT( '.' ) &&
          pFD -> cFileName[ 1 ] != TEXT( '.' )
    ) {
  
     if (   ( pFullNameSrc = ( LPTSTR )HeapAlloc (
                                        hHeap, 0,
                                        lstrlen ( dirSrc ) + lstrlen ( pFD -> cFileName ) +
                                        sizeof (  TEXT( '/' )  ) + sizeof (  TEXT( '\x00' )  )
                                       )
            ) == NULL ||
            ( pFullNameDst = ( LPTSTR )HeapAlloc (
                                        hHeap, 0,
                                        lstrlen ( dirDst ) + lstrlen ( pFD -> cFileName ) +
                                        sizeof (  TEXT( '/' )  ) + sizeof (  TEXT( '\x00' )  )
                                       )
            ) == NULL
     ) break;
  
     lstrcpy ( pFullNameSrc, dirSrc );
     lstrcat (  pFullNameSrc, TEXT( "/" )  );
     lstrcat ( pFullNameSrc, pFD -> cFileName );

     lstrcpy ( pFullNameDst, dirDst );
     lstrcat (  pFullNameDst, TEXT( "/" )  );
     lstrcat ( pFullNameDst, pFD -> cFileName );

     if ( pFD -> dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {

      if (   FALSE == (  retVal = CopyDirectory ( pFullNameSrc, pFullNameDst )  )   ) break;
   
     } else {
retry:   
      if (   FALSE == (  retVal = CopyFile ( pFullNameSrc, pFullNameDst, FALSE )  )   ) {
      
       if ( _response_dir_proc != NULL ) {
      
        response = ( *_response_dir_proc ) ( pFullNameSrc );

        if ( response == DIR_ABORT )

         break;

        else if ( response == DIR_RETRY )

         goto retry;

        else if ( response == DIR_IGNORE )

         retVal = TRUE;

        else

         break;

       }  /* end if */
      
      } else if ( _copy_dir_proc != NULL )

       ( *_copy_dir_proc ) ( pFullNameSrc, pFullNameDst );

     }  /* end else */

     HeapFree ( hHeap, 0, pFullNameDst );
     HeapFree ( hHeap, 0, pFullNameSrc );
     pFullNameSrc = pFullNameDst = NULL;

    }  /* end if */

    fFind = FindNextFile ( hFindFile, pFD );

   }  /* end while */

  }  /* end if */

 }  /* end if ( error creating directory ) */

 if ( hFindFile != INVALID_HANDLE_VALUE ) FindClose ( hFindFile );

 if ( pFullNameSrc != NULL ) HeapFree ( hHeap, 0, pFullNameSrc );
 if ( pFullNameDst != NULL ) HeapFree ( hHeap, 0, pFullNameDst );
 if ( pName        != NULL ) HeapFree ( hHeap, 0, pName        );
 if ( pFD          != NULL ) HeapFree ( hHeap, 0, pFD          );

 return retVal;

}  /* end CopyDirectory */
/***/
/******************************************************************************/
/* Function : SetDeleteDirectoryProc                                        */
/* Purpose  : Sets callback procedure which is calling by the               */ 
/*            'DeleteDirectory' after deleteion of each item in the         */
/*            directory. To unregister this callback function supply NULL   */
/*            pointer                                                       */
/******************************************************************************/
/***/
void SetDeleteDirectoryProc ( DELETE_DIR_PROC proc ) {

 _delete_dir_proc = proc;

}  /* end SetDeleteDirectoryProc */
/***/
/******************************************************************************/
/* Function : SetMoveDirectoryProc                                          */
/* Purpose  : Sets callback procedure which is calling by the               */ 
/*            'MoveDirectory' after moving of each item in the              */
/*            directory. To unregister this callback function supply NULL   */
/*            pointer                                                       */
/******************************************************************************/
/***/
void SetMoveDirectoryProc ( MOVE_DIR_PROC proc ) {

 _move_dir_proc = proc;

}  /* end SetMoveDirectoryProc */
/***/
/******************************************************************************/
/* Function : SetCopyDirectoryProc                                          */
/* Purpose  : Sets callback procedure which is calling by the               */ 
/*            'CopyDirectory' after copying of each item in the             */
/*            directory. To unregister this callback function supply NULL   */
/*            pointer                                                       */
/******************************************************************************/
/***/
void SetCopyDirectoryProc ( COPY_DIR_PROC proc ) {

 _copy_dir_proc = proc;

}  /* end SetCopyDirectoryProc */
/***/
/******************************************************************************/
/* Function : SetResponseDirectoryProc                                      */
/* Purpose  : Sets callback procedure which is calling by the               */ 
/*            directoy processing function if an error was occur.           */
/*            The return value of that callback procedure determines        */
/*            behaviour of directoy processing functions in case of error.  */
/*            To unregister this callback function supply NULL pointer      */
/******************************************************************************/
/***/
void SetResponseDirectoryProc ( RESPONSE_DIR_PROC proc ) {

 _response_dir_proc = proc;

}  /* end SetResponseDirectoryProc */
/***/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
#endif
