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

#include <OSD_Process.ixx>
#include <OSD_WhoAmI.hxx>
#include <OSD_Environment.hxx>

const OSD_WhoAmI Iam = OSD_WProcess;

#include <errno.h>

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#include <stdlib.h>

#ifdef HAVE_SYS_PARAM_H
# include <sys/param.h>
#endif

#if defined(HAVE_TIME_H)
# include <time.h>
#endif

#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif

#ifdef HAVE_PWD_H
# include <pwd.h>       // For command getpwuid
#endif

OSD_Process::OSD_Process(){
}


void OSD_Process::Spawn (const TCollection_AsciiString& cmd,
			 const Standard_Boolean /*ShowWindow*/)
{
 system(cmd.ToCString());
}


void OSD_Process::TerminalType(TCollection_AsciiString& Name){
TCollection_AsciiString which="TERM";
OSD_Environment term (which,"");

 term.Value();
 which = term.Value();
 Name = term.Name();
}


// Get date of system date

Quantity_Date  OSD_Process::SystemDate(){
Quantity_Date result;
Standard_Integer month=0,day=0,year=0,hh=0,mn=0,ss=0;
struct tm transfert;
time_t secs;
struct timeval tval;
int status;

 status = gettimeofday( &tval, NULL );
 if (status == -1) myError.SetValue (errno, Iam, "GetSystem");
 else {
  secs = tval.tv_sec;
#ifdef HAVE_LOCALTIME_R
  localtime_r(&secs, &transfert);
#else
  memcpy(&transfert, localtime(&secs), sizeof(struct tm));
#endif
  month = transfert.tm_mon + 1;  // Add to January (month #1)
  day   = transfert.tm_mday;
  year  = transfert.tm_year;
  hh    = transfert.tm_hour;
  mn    = transfert.tm_min ;
  ss    = transfert.tm_sec ;
}

 result.SetValues ( month, day, year+1900, hh, mn, ss);
 return (result);
}


Standard_Integer OSD_Process::ProcessId(){
 return (getpid());
}


Standard_Integer OSD_Process::UserId(){
 return (getuid());
}


TCollection_AsciiString OSD_Process::UserName(){
 struct passwd *infos;
 infos = getpwuid(getuid()); 
 TCollection_AsciiString result=infos->pw_name;

 return(result);
}

Standard_Boolean OSD_Process::IsSuperUser (){
  if (getuid()) {
    return Standard_False;
  }
  else {
    return Standard_True;
  }
}


OSD_Path OSD_Process::CurrentDirectory(){
OSD_Path result;
TCollection_AsciiString Name;
char *ret;
#if !defined(MAXPATHLEN) && defined(__GLIBC__)
 char *cwd = getcwd(NULL,0);
 ret = cwd;
#else
char cwd[MAXPATHLEN+1] ;
 ret = getcwd(cwd,MAXPATHLEN+1);
#endif

 if (!ret)
   myError.SetValue (errno, Iam, "Where");
 else {
   Name = cwd;

//   JPT : August,20 1993. This code has been replaced by #ifdef ... #endif
//   position = Name.SearchFromEnd(".");
//   if (position != -1){
//     Ext = Name;
//     Ext.Remove(1,position);
//     Name.Remove( position,Ext.Length()+1);
//   }
//   result.SetValues("","","","","",Name,Ext);
//   End

#if defined(vax) || defined(__vms)
   Standard_Integer iDisk = Name.Search(":");
   if (iDisk){
     TCollection_AsciiString Disk;
     TCollection_AsciiString Directory;
     Disk = Name.SubString(1,iDisk-1);
     Directory = Name.SubString(iDisk+1,Name.Length());
     result.SetValues("","","",Disk,Directory,"","");
   }
#else
   Name += TCollection_AsciiString("/");
   result = OSD_Path(Name);
   //      result.SetValues("","","","",Name,"","");
#endif

#if !defined(MAXPATHLEN) && defined(__GLIBC__)
   free(cwd);
#endif
 }
return (result);
}


void OSD_Process::SetCurrentDirectory(const OSD_Path& where){
TCollection_AsciiString Name;
int status;

 where.SystemName(Name);

 status = chdir (Name.ToCString());
 if (status == -1) myError.SetValue(errno, Iam, "Move to directory");
}


void OSD_Process::Reset(){
 myError.Reset();
}

Standard_Boolean OSD_Process::Failed()const{
 return( myError.Failed());
}

void OSD_Process::Perror() {
 myError.Perror();
}


Standard_Integer OSD_Process::Error()const{
 return( myError.Error());
}

#else

//------------------------------------------------------------------------
//-------------------  WNT Sources of OSD_Path ---------------------------
//------------------------------------------------------------------------

//it is important to undefine NOUSER and enforce including <windows.h> before
//Standard_Macro.hxx defines it and includes <windows.h> causing compilation errors
#ifdef NOUSER
#undef NOUSER /* we need SW_HIDE from windows.h */
#endif
#include <windows.h>

#ifdef SetCurrentDirectory
# undef SetCurrentDirectory /* undefine SetCurrentDirectory from <winbase.h> to correctly include <OSD_Process.hxx> */
#endif
#include <OSD_Process.hxx>

#include <OSD_Path.hxx>
#include <Quantity_Date.hxx>

#include <OSD_WNT_1.hxx>
#include <lmcons.h> /// pour UNLEN  ( see MSDN about GetUserName() )
#if !defined (_MSC_VER) || (_MSC_VER >= 1600)
#include <stdint.h>
#endif

void _osd_wnt_set_error ( OSD_Error&, OSD_WhoAmI, ... );

OSD_Process :: OSD_Process () {

}  // end constructor

void OSD_Process :: Spawn ( const TCollection_AsciiString& cmd ,
			    const Standard_Boolean ShowWindow /* = Standard_True */) {

 STARTUPINFO         si;
 PROCESS_INFORMATION pi;

 ZeroMemory (  &si, sizeof ( STARTUPINFO )  );

 si.cb = sizeof ( STARTUPINFO );
 //============================================
 //---> Added by Stephane Routelous ( stephane.routelous@altavista.net )	[16.03.01]
 //---> Reason : to allow to hide the window
 if ( !ShowWindow )
 {
	 si.dwFlags		= STARTF_USESHOWWINDOW;
	 si.wShowWindow	= SW_HIDE;	
 }
 //<--- End Added by Stephane Routelous ( stephane.routelous@altavista.net )	[16.03.01]
 //============================================

 if (!CreateProcess (
      NULL, (char *)cmd.ToCString (), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi
                    )
 )

  _osd_wnt_set_error ( myError, OSD_WProcess );

 else {
 
  CloseHandle ( pi.hThread );

  WaitForSingleObject ( pi.hProcess, INFINITE );

  CloseHandle ( pi.hProcess );
 
 }  // end else

}  // end OSD_Process :: Spawn

void OSD_Process :: TerminalType ( TCollection_AsciiString& Name ) {

 Name = TEXT( "WIN32 console" );

}  // end OSD_Process :: TerminalType

Quantity_Date OSD_Process :: SystemDate () {

 Quantity_Date retVal;
 SYSTEMTIME    st;

 GetLocalTime ( &st );

 retVal.SetValues (
         st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds
        );

 return retVal;

}  // end OSD_Process :: SystemDate

Standard_Integer OSD_Process :: UserId () {

 PSID         retVal        = NULL;
 HANDLE       hProcessToken = INVALID_HANDLE_VALUE;
 PTOKEN_OWNER pTKowner      = NULL;

 if (  !OpenProcessToken (
         GetCurrentProcess (),
         TOKEN_QUERY, &hProcessToken
        ) ||
        (  pTKowner = ( PTOKEN_OWNER )GetTokenInformationEx (
                                       hProcessToken, TokenOwner
                                      )
        ) == NULL ||
        (  retVal   = CopySidEx ( pTKowner -> Owner )  ) == NULL
 )

  _osd_wnt_set_error ( myError, OSD_WProcess );

 if ( hProcessToken != INVALID_HANDLE_VALUE ) CloseHandle ( hProcessToken );
 if ( pTKowner      != NULL                 ) FreeTokenInformation ( pTKowner );

 return ( intptr_t )retVal;

}  // end OSD_Process :: UserId

TCollection_AsciiString OSD_Process :: UserName () 
{
	Standard_PCharacter pBuff = new char[UNLEN + 1];
	DWORD                   dwSize = UNLEN + 1;
	TCollection_AsciiString retVal;
	if (  !GetUserName ( pBuff, &dwSize )  )
	{
		_osd_wnt_set_error ( myError, OSD_WProcess );
	}
	else
	{
		TCollection_AsciiString theTmpUserName(pBuff,(int)dwSize -1 );
		retVal = theTmpUserName;
	}
	delete [] pBuff;
	return retVal;
}  // end OSD_Process :: UserName

Standard_Boolean OSD_Process :: IsSuperUser () {

 Standard_Boolean retVal = FALSE;
 PSID             pSIDadmin;
 HANDLE           hProcessToken = INVALID_HANDLE_VALUE;
 PTOKEN_GROUPS    pTKgroups = NULL;

 if (  !OpenProcessToken (
         GetCurrentProcess (),
         TOKEN_QUERY, &hProcessToken
        ) ||
        (  pTKgroups = ( PTOKEN_GROUPS )GetTokenInformationEx (
                                         hProcessToken, TokenGroups
                                        )
        ) == NULL
 )

  _osd_wnt_set_error ( myError, OSD_WProcess );

 else {
 
  pSIDadmin = AdminSid ();

  for ( int i = 0; i < ( int )pTKgroups -> GroupCount; ++i )

   if (  EqualSid ( pTKgroups -> Groups[ i ].Sid, pSIDadmin )  ) {
   
    retVal = TRUE;
    break;
   
   }  // end if
 
 }  // end else

 if ( hProcessToken != INVALID_HANDLE_VALUE ) CloseHandle ( hProcessToken );
 if ( pTKgroups     != NULL                 ) FreeTokenInformation ( pTKgroups );

 return retVal;

}  // end OSD_Process :: IsSuperUser

Standard_Integer OSD_Process :: ProcessId () {

 return ( Standard_Integer )GetCurrentProcessId ();

}  // end OSD_Process :: ProcessId

OSD_Path OSD_Process :: CurrentDirectory () {

 Standard_PCharacter pBuff = NULL;
 DWORD            dwSize = 0;
 OSD_Path         retVal;

 dwSize = GetCurrentDirectory ( dwSize, pBuff );
 pBuff  = new Standard_Character[ dwSize ];

 if (   (  dwSize = GetCurrentDirectory ( dwSize, pBuff )  ) == 0   )

  _osd_wnt_set_error ( myError, OSD_WProcess );

 else
 
  retVal = OSD_Path ( pBuff );
 
 delete[] pBuff;

 return retVal;
 
}  // end OSD_Process :: CurrentDirectory

void OSD_Process :: SetCurrentDirectory ( const OSD_Path& where ) {

#ifdef UNICODE
# define SetCurrentDirectory  SetCurrentDirectoryW
#else
# define SetCurrentDirectory  SetCurrentDirectoryA
#endif  // UNICODE

 TCollection_AsciiString path;

 where.SystemName ( path );

 if (   !::SetCurrentDirectory (  path.ToCString ()  )   )

  _osd_wnt_set_error ( myError, OSD_WProcess );

}  // end OSD_Process :: SetCurrentDirectory

Standard_Boolean OSD_Process :: Failed () const {

 return myError.Failed ();

}  // end OSD_Process :: Failed

void OSD_Process :: Reset () {

 myError.Reset ();

}  // end OSD_Process :: Reset

void OSD_Process :: Perror () {

 myError.Perror ();

}  // end OSD_Process :: Perror

Standard_Integer OSD_Process :: Error () const {

 return myError.Error ();

}  // end OSD_Process :: Error

#endif
