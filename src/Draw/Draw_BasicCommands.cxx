// Created on: 1995-02-23
// Created by: Remi LEQUETTE
// Copyright (c) 1995-1999 Matra Datavision
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


#include <Standard_Macro.hxx>
#include <Standard_Stream.hxx>
#include <Standard_SStream.hxx>

#include <Draw.ixx>
#include <Draw_Appli.hxx>
#include <Draw_Printer.hxx>

#include <Message.hxx>
#include <Message_Messenger.hxx>
#include <OSD_MemInfo.hxx>

#ifdef HAVE_CONFIG_H
# include <oce-config.h>
#endif

#if defined(HAVE_TIME_H) || defined(WNT)
# include <time.h>
#endif

#ifdef HAVE_SIGNAL_H
# include <signal.h>
#endif

#ifndef WNT
# include <sys/resource.h>
# ifdef HAVE_STRINGS_H
#  include <strings.h>
# endif
#else
//WNT
extern Standard_Boolean Draw_Batch;
#include <windows.h>
#include <winbase.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef OCE_HAVE_LIMITS
# include <limits>
#elif defined (OCE_HAVE_LIMITS_H)
# include <limits.h>
#endif

#ifdef WNT
# include <limits>
#endif

static clock_t MDTV_CPU_LIMIT;   // Cpu_limit in Sec.
static clock_t MDTV_CPU_CURRENT; // cpu time already used at last
                                 // cpulimit call. (sec.) 
//#define strcasecmp strcmp Already defined
#define RLIM_INFINITY   0x7fffffff
#endif

#include <Draw_Chronometer.hxx>
#include <OSD_MAllocHook.hxx>
#include <OSD_Chronometer.hxx>

#if defined (__hpux) || defined ( HPUX )
#define RLIM_INFINITY   0x7fffffff
#define	RLIMIT_CPU	0
#endif



//=======================================================================
// chronom
//=======================================================================

extern Standard_Boolean Draw_Chrono;

static Standard_Integer chronom(Draw_Interpretor& di,
				Standard_Integer n,const char** a)
{
  if ((n == 1) || (*a[1] == '0') || (*a[1] == '1')) {
    if (n == 1)
      Draw_Chrono = !Draw_Chrono;
    else
      Draw_Chrono = (*a[1] == '1');

    if (Draw_Chrono) di << "Chronometers activated."<<"\n";
    else di << "Chronometers desactivated."<<"\n";
  }
  else {
    Handle(Draw_Drawable3D) D = Draw::Get(a[1]);
    Handle(Draw_Chronometer) C;
    if (!D.IsNull()) {
      C = Handle(Draw_Chronometer)::DownCast(D);
    }
    if (C.IsNull()) {
      C = new Draw_Chronometer();
    Draw::Set(a[1],C,Standard_False);
    }
    if (n <= 2) {
      C->Timer().Reset();
    }
    else {
      if (!strcasecmp(a[2],"reset"))
	C->Timer().Reset();
      if (!strcasecmp(a[2],"start"))
	C->Timer().Start();
      if (!strcasecmp(a[2],"stop"))
	C->Timer().Stop();
      if (!strcasecmp(a[2],"show"))
	C->Timer().Show();
    }
  }
  return 0;
}

static Standard_Integer dchronom(Draw_Interpretor& I,
				 Standard_Integer n,const char** a)
{
  if ((n == 1) || (*a[1] == '0') || (*a[1] == '1')) {
    if (n == 1)
      Draw_Chrono = !Draw_Chrono;
    else
      Draw_Chrono = (*a[1] == '1');

    if (Draw_Chrono) I << "Chronometers activated."<<"\n";
    else I << "Chronometers desactivated."<<"\n";
  }
  else {
    Handle(Draw_Drawable3D) D = Draw::Get(a[1]);
    Handle(Draw_Chronometer) C;
    if (!D.IsNull()) {
      C = Handle(Draw_Chronometer)::DownCast(D);
    }
    if (C.IsNull()) {
      C = new Draw_Chronometer();
    Draw::Set(a[1],C,Standard_False);
    }
    if (n <= 2) {
      C->Timer().Reset();
    }
    else {
      if (!strcasecmp(a[2],"reset"))
	C->Timer().Reset();
      if (!strcasecmp(a[2],"start"))
	C->Timer().Start();
      if (!strcasecmp(a[2],"stop"))
	C->Timer().Stop();
      if (!strcasecmp(a[2],"show")) {
	Standard_SStream ss;
	C->Timer().Show(ss);
	I << ss;
      }
    }
  }
  return 0;
}



//=======================================================================
//function : ifbatch
//purpose  : 
//=======================================================================

static Standard_Integer ifbatch(Draw_Interpretor& DI, Standard_Integer , const char** )
{
  if (Draw_Batch)
    DI << "1";
  else
    DI << "0";
  
  return 0;
}

//=======================================================================
//function : spy
//purpose  : 
//=======================================================================

extern Standard_Boolean Draw_Spying;
extern filebuf Draw_Spyfile;

static Standard_Integer spy(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (Draw_Spying) 
    Draw_Spyfile.close();
  Draw_Spying = Standard_False;
  if (n > 1) {
    if (!Draw_Spyfile.open(a[1],ios::out)) {
      di << "Cannot open "<<a[1]<<" for writing"<<"\n";
      return 1;
    }
    Draw_Spying = Standard_True;
  }
  return 0;
}

static Standard_Integer dlog(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n != 2 && n != 3)
  {
    cout << "Enable or disable logging: " << a[0] << " {on|off}" << endl;
    cout << "Reset log: " << a[0] << " reset" << endl;
    cout << "Get log content: " << a[0] << " get" << endl;
    return 1;
  }

  if (! strcmp (a[1], "on") && n == 2)
  {
    di.SetDoLog (Standard_True);
//    di.Log() << "dlog on" << endl; // for symmetry
  }
  else if (! strcmp (a[1], "off") && n == 2)
  {
    di.SetDoLog (Standard_False);
  }
  else if (! strcmp (a[1], "reset") && n == 2)
  {
    di.Log().str("");
  }
  else if (! strcmp (a[1], "get") && n == 2)
  {
    di << di.Log().str().c_str();
  }
  else if (! strcmp (a[1], "add") && n == 3)
  {
    di.Log() << a[2] << "\n";
  }
  else {
    cout << "Unrecognized option(s): " << a[1] << endl;
    return 1;
  }
  return 0;
}

static Standard_Integer decho(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n != 2)
  {
    cout << "Enable or disable echoing: " << a[0] << " {on|off}" << endl;
    return 1;
  }

  if (! strcmp (a[1], "on"))
  {
    di.SetDoEcho (Standard_True);
  }
  else if (! strcmp (a[1], "off"))
  {
    di.SetDoEcho (Standard_False);
  }
  else {
    cout << "Unrecognized option: " << a[1] << endl;
    return 1;
  }
  return 0;
}

//=======================================================================
//function : wait
//purpose  : 
//=======================================================================

static Standard_Integer Draw_wait(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  Standard_Integer w = 10;
  if (n > 1)
    w = atoi(a[1]);
  time_t ct = time(NULL) + w;
  while (time(NULL) < ct) {};
  return 0;
}

//=======================================================================
//function : cpulimit
//purpose  : 
//=======================================================================
#ifdef WNT
static unsigned int __stdcall CpuFunc (void * param)
{
  clock_t aCurrent;
  while (1)
  {
    Sleep (5);
    Standard_Real anUserSeconds, aSystemSeconds;
    OSD_Chronometer::GetProcessCPU (anUserSeconds, aSystemSeconds);
    aCurrent = clock_t(anUserSeconds + aSystemSeconds);
    
    if ((aCurrent - MDTV_CPU_CURRENT) >= MDTV_CPU_LIMIT)
    {
      printf ("CpuFunc : Fin sur Cpu Limit \n");
      ExitProcess (2);
      return 0;
    }
  }
  return 0;
}
#endif

static Standard_Integer cpulimit(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
#ifndef WNT
  rlimit rlp;
  rlp.rlim_max = RLIM_INFINITY;
  if (n <= 1)
    rlp.rlim_cur = RLIM_INFINITY;
  else
    rlp.rlim_cur = atoi(a[1]);

  int status;
  status=setrlimit(RLIMIT_CPU,&rlp);
  if (status !=0)
    di << "status cpulimit setrlimit : " << status << "\n";

#else
//WNT
  static int aFirst = 1;

  unsigned int __stdcall CpuFunc (void *);
  unsigned aThreadID;

  if (n <= 1)
    MDTV_CPU_LIMIT = RLIM_INFINITY;
  else
  {
    MDTV_CPU_LIMIT = atoi (a[1]);
    Standard_Real anUserSeconds, aSystemSeconds;
    OSD_Chronometer::GetProcessCPU (anUserSeconds, aSystemSeconds);
    MDTV_CPU_CURRENT = clock_t(anUserSeconds + aSystemSeconds);

    if (aFirst) // Launch the thread only at the 1st call.
    {
      aFirst = 0;
      _beginthreadex (NULL, 0, CpuFunc, NULL, 0, &aThreadID);
    }
  }

#endif

  return 0;
}

//=======================================================================
//function : mallochook
//purpose  : 
//=======================================================================

static Standard_Integer mallochook(Draw_Interpretor& di, Standard_Integer n,
                                   const char** a)
{
  if (n < 2)
  {
    di << "\
usage: mallochook cmd\n\
where cmd is one of:\n\
  set [<op>]      - set callback to malloc/free; op is one of the following:\n\
                    0 - set callback to NULL,\n\
                    1 - set callback OSD_MAllocHook::CollectBySize (default)\n\
                    2 - set callback OSD_MAllocHook::LogFileHandler\n\
  reset           - reset the CollectBySize handler\n\
  report1 [<outfile>]\n\
                  - write report from CollectBySize handler in <outfile>\n\
  open [<logfile>]\n\
                  - open file for writing the log with LogFileHandler\n\
  close           - close the log file with LogFileHandler\n\
  report2 [<flag>] [<logfile>] [<outfile>]\n\
                  - scan <logfile> written with LogFileHandler\n\
                    and make synthesized report in <outfile>; <flag> can be:\n\
                    0 - simple stats by sizes (default),\n\
                    1 - with alive allocation numbers\n\
By default <logfile> is \"mem-log.txt\", <outfile> is \"mem-stat.txt\""
      << "\n";
    return 0;
  }
  if (strcmp(a[1], "set") == 0)
  {
    int aType = (n > 2 ? atoi(a[2]) : 1);
    if (aType < 0 || aType > 2)
    {
      di << "unknown op of the command set" << "\n";
      return 1;
    }
    else if (aType == 0)
    {
      OSD_MAllocHook::SetCallback(NULL);
      di << "callback is unset" << "\n";
    }
    else if (aType == 1)
    {
      OSD_MAllocHook::SetCallback(OSD_MAllocHook::GetCollectBySize());
      di << "callback is set to CollectBySize" << "\n";
    }
    else //if (aType == 2)
    {
      OSD_MAllocHook::SetCallback(OSD_MAllocHook::GetLogFileHandler());
      di << "callback is set to LogFileHandler" << "\n";
    }
  }
  else if (strcmp(a[1], "reset") == 0)
  {
    OSD_MAllocHook::GetCollectBySize()->Reset();
    di << "CollectBySize handler is reset" << "\n";
  }
  else if (strcmp(a[1], "open") == 0)
  {
    const char* aFileName = (n > 2 ? a[2] : "mem-log.txt");
    if (!OSD_MAllocHook::GetLogFileHandler()->Open(aFileName))
    {
      di << "cannot create file " << aFileName << " for writing" << "\n";
      return 1;
    }
    di << "log file " << aFileName << " is opened for writing" << "\n";
  }
  else if (strcmp(a[1], "close") == 0)
  {
    OSD_MAllocHook::GetLogFileHandler()->Close();
    di << "log file is closed" << "\n";
  }
  else if (strcmp(a[1], "report1") == 0)
  {
    const char* aOutFile = "mem-stat.txt";
    if (n > 2)
      aOutFile = a[2];
    if (OSD_MAllocHook::GetCollectBySize()->MakeReport(aOutFile))
    {
      di << "report " << aOutFile << " has been created" << "\n";
    }
    else
    {
      di << "cannot create report " << aOutFile << "\n";
      return 1;
    }
  }
  else if (strcmp(a[1], "report2") == 0)
  {
    Standard_Boolean includeAlive = Standard_False;
    const char* aLogFile = "mem-log.txt";
    const char* aOutFile = "mem-stat.txt";
    if (n > 2)
    {
      includeAlive = (atoi(a[2]) != 0);
      if (n > 3)
      {
        aLogFile = a[3];
        if (n > 4)
          aOutFile = a[4];
      }
    }
    if (OSD_MAllocHook::LogFileHandler::MakeReport(aLogFile, aOutFile, includeAlive))
    {
      di << "report " << aOutFile << " has been created" << "\n";
    }
    else
    {
      di << "cannot create report " << aOutFile << " from the log file "
        << aLogFile << "\n";
      return 1;
    }
  }
  else
  {
    di << "unrecognized command " << a[1] << "\n";
    return 1;
  }
  return 0;
}

//==============================================================================
//function : dmeminfo
//purpose  :
//==============================================================================

static int dmeminfo (Draw_Interpretor& theDI,
                     Standard_Integer  theArgNb,
                     const char**      theArgVec)
{
  OSD_MemInfo aMemInfo;
  if (theArgNb <= 1)
  {
    theDI << aMemInfo.ToString();
    return 0;
  }

  for (Standard_Integer anIter = 1; anIter < theArgNb; ++anIter)
  {
    TCollection_AsciiString anArg (theArgVec[anIter]);
    anArg.LowerCase();
    if (anArg == "virt" || anArg == "v")
    {
      theDI << Standard_Real (aMemInfo.Value (OSD_MemInfo::MemVirtual)) << " ";
    }
    else if (anArg == "wset" || anArg == "w")
    {
      theDI << Standard_Real (aMemInfo.Value (OSD_MemInfo::MemWorkingSet)) << " ";
    }
    else if (anArg == "wsetpeak")
    {
      theDI << Standard_Real (aMemInfo.Value (OSD_MemInfo::MemWorkingSetPeak)) << " ";
    }
    else if (anArg == "swap")
    {
      theDI << Standard_Real (aMemInfo.Value (OSD_MemInfo::MemSwapUsage)) << " ";
    }
    else if (anArg == "swappeak")
    {
      theDI << Standard_Real (aMemInfo.Value (OSD_MemInfo::MemSwapUsagePeak)) << " ";
    }
    else if (anArg == "private")
    {
      theDI << Standard_Real (aMemInfo.Value (OSD_MemInfo::MemPrivate)) << " ";
    }
    else
    {
      std::cerr << "Unknown argument '" << theArgVec[anIter] << "'!\n";
    }
  }
  theDI << "\n";
  return 0;
}

void Draw::BasicCommands(Draw_Interpretor& theCommands)
{
  static Standard_Boolean Done = Standard_False;
  if (Done) return;
  Done = Standard_True;

  ios::sync_with_stdio();

  const char* g = "DRAW General Commands";
  
  theCommands.Add("batch", "returns 1 in batch mode",
		  __FILE__,ifbatch,g);
  theCommands.Add("spy","spy [file], Save commands in file. no file close",
		  __FILE__,spy,g);
  theCommands.Add("wait","wait [time(10)], wait time seconds",
		  __FILE__,Draw_wait,g);
  theCommands.Add("cpulimit","cpulimit [nbseconds], no args remove limits",
		  __FILE__,cpulimit,g);
  theCommands.Add("chrono","chrono [ name start/stop/reset/show]",
		  __FILE__,chronom,g);
  theCommands.Add("dchrono","dchrono [ name start/stop/reset/show]",
		  __FILE__,dchronom,g);
  theCommands.Add("mallochook",
                  "debug memory allocation/deallocation, w/o args for help",
                  __FILE__, mallochook, g);
  theCommands.Add ("meminfo",
    "meminfo [virt|v] [wset|w] [wsetpeak] [swap] [swappeak] [private]"
    " : memory counters for this process",
	  __FILE__, dmeminfo, g);

  // Logging commands; note that their names are hard-coded in the code 
  // of Draw_Interpretor, thus should not be changed without update of that code!
  theCommands.Add("dlog", "manage logging of commands and output; run without args to get help",
		  __FILE__,dlog,g);
  theCommands.Add("decho", "switch on / off echo of commands to cout; run without args to get help",
		  __FILE__,decho,g);
}
