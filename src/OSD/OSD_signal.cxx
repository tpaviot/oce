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


#include <OSD.ixx>

#ifndef WNT

//---------- All Systems except Windows NT : ----------------------------------

#ifdef HAVE_CONFIG_H
# include <oce-config.h>
#endif

# include <stdio.h>

#include <OSD_WhoAmI.hxx>
#include <OSD_SIGHUP.hxx>
#include <OSD_SIGINT.hxx>
#include <OSD_SIGQUIT.hxx>
#include <OSD_SIGILL.hxx>
#include <OSD_SIGKILL.hxx>
#include <OSD_SIGBUS.hxx>
#include <OSD_SIGSEGV.hxx>
#include <OSD_SIGSYS.hxx>
#include <Standard_NumericError.hxx>
#include <Standard_NullObject.hxx>
#include <Standard_DivideByZero.hxx>
#include <Standard_Overflow.hxx>

#include <Standard_ErrorHandler.hxx>

// POSIX threads
#ifdef HAVE_PTHREAD_H
 #include <pthread.h>
#endif

#ifdef HAVE_PTHREAD_H
static pthread_t getOCCThread () {
  static pthread_t TheOCCThread = 0;
  return TheOCCThread ;
}
#endif

#ifdef linux
#include <fenv.h>
#include <fpu_control.h>
static Standard_Boolean fFltExceptions = Standard_False;
#endif

//const OSD_WhoAmI Iam = OSD_WPackage;

typedef void (ACT_SIGIO_HANDLER)(void) ;
ACT_SIGIO_HANDLER *ADR_ACT_SIGIO_HANDLER = NULL ;

#if defined(HAVE_FLOATINGPOINT_H) && defined(HAVE_SYS_MACHSIG_H)
# include <floatingpoint.h>
# include <sys/machsig.h>
// JPT : Difference between SUN/SUNOS and SUN/SOLARIS 
# define FPE_FLTDIV_TRAP FPE_FLTDIV 
# define FPE_INTDIV_TRAP FPE_INTDIV 
# define FPE_FLTOVF_TRAP FPE_FLTOVF 
# define FPE_INTOVF_TRAP FPE_INTOVF
# define FPE_FLTUND_TRAP FPE_FLTUND 

#define	FPE_FLTRES_TRAP FPE_FLTRES	/* floating point inexact result */
#define	FPE_FLTINV_TRAP FPE_FLTINV	/* invalid floating point operation */
#define	FPE_FLTSUB_TRAP FPE_FLTSUB	/* subscript out of range */

extern "C" {int ieee_handler(char *,char *, sigfpe_handler_type&);}
# include <stdlib.h>
#endif

#ifdef DECOSF1
typedef void (* SIG_PFV) (int);
#endif

#if defined(HAVE_SIGFPE_H) && defined(HAVE_SYS_SIGINFO_H)
# include <sigfpe.h>
# include <sys/siginfo.h>
# define FPE_FLTDIV_TRAP FPE_FLTDIV 
# define FPE_INTDIV_TRAP FPE_INTDIV 
# define FPE_FLTOVF_TRAP FPE_FLTOVF 
# define FPE_INTOVF_TRAP FPE_INTOVF
# define FPE_FLTUND_TRAP FPE_FLTUND 
#endif 

#ifdef __GNUC__
# include <stdlib.h>
# include <stdio.h>
#else
#  ifdef SA_SIGINFO 
#    ifndef _AIX
#  include <sys/siginfo.h>
#     endif
#  endif
#endif
typedef void (* SIG_PFV) (int);

#ifdef HAVE_SIGNAL_H
# include <signal.h>
#endif

#ifdef HAVE_SYS_SIGNAL_H
# include <sys/signal.h>
#endif

#if defined(HAVE_PTHREAD_H) && defined(NO_CXX_EXCEPTION) 
//============================================================================
//====  GetOldSigAction
//====     get previous 
//============================================================================

static struct sigaction *GetOldSigAction() 
{
  static struct sigaction oldSignals[NSIG];
  return oldSignals;
}

#ifdef SOLARIS
static sigfpe_handler_type *GetOldFPE()
{
  static sigfpe_handler_type aIEEEHandler[5] = { NULL, NULL, NULL, NULL, NULL } ;
  return aIEEEHandler;
}
#endif
#endif


//============================================================================
//==== SetSignal 
//====     Set the differents signals:
//============================================================================

void OSD::SetSignal(const Standard_Boolean aFloatingSignal) 
{
  static int first_time = 3 ;
  struct sigaction act, oact;
  int              stat = 0;

  if( aFloatingSignal ) {
    //==== Enable the floating point exceptions ===============
#if defined (__sun) || defined (SOLARIS)
    sigfpe_handler_type PHandler = (sigfpe_handler_type) Handler ;
    stat = ieee_handler("set", "invalid",  PHandler);
    stat = ieee_handler("set", "division", PHandler) || stat;
    stat = ieee_handler("set", "overflow", PHandler) || stat;
    //stat = ieee_handler("set", "underflow", PHandler) || stat;
    //stat = ieee_handler("set", "inexact", PHandler) || stat;
    if (stat) {
      cerr << "ieee_handler does not work !!! KO " << endl;
    }
#elif defined (linux)
    feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
    //feenableexcept (FE_INVALID | FE_DIVBYZERO);
    fFltExceptions = Standard_True;
#endif
  }
  else if ( first_time & 1 ) {
//    cout << "SetSignal( Standard_False ) is not implemented..." << endl ;
    first_time = first_time & (~ 1) ;
  }

#if defined (sgi) || defined (IRIX )
 if ( first_time & 2 ) {
   char *TRAP_FPE = getenv("TRAP_FPE") ;
   if ( TRAP_FPE == NULL ) {
     cout << "On SGI you must set TRAP_FPE environment variable : " << endl ;
     cout << "set env(TRAP_FPE) \"UNDERFL=FLUSH_ZERO;OVERFL=DEFAULT;DIVZERO=DEFAULT;INT_OVERFL=DEFAULT\" or" << endl ;
     cout << "setenv TRAP_FPE \"UNDERFL=FLUSH_ZERO;OVERFL=DEFAULT;DIVZERO=DEFAULT;INT_OVERFL=DEFAULT\"" << endl ;
//     exit(1) ;
     first_time = first_time & (~ 2) ;
   }
 }
#endif

  //==== Save the old Signal Handler, and set the new one ===================

  sigemptyset(&act.sa_mask) ;

#ifdef SA_RESTART
  act.sa_flags   = SA_RESTART ;
#else
  act.sa_flags   = 0 ;
#endif
#ifdef SA_SIGINFO
  act.sa_flags = act.sa_flags | SA_SIGINFO ;
  act.sa_sigaction = (void(*)(int, siginfo_t *, void*)) &Handler ;
#else
  act.sa_handler =  (SIG_PFV) &Handler ;
#endif

  //==== Always detected the signal "SIGFPE" =================================
  stat = sigaction(SIGFPE,&act,&oact);   // ...... floating point exception 
  if (stat) {
     cerr << "sigaction does not work !!! KO " << endl;
     perror("sigaction ");
  }

  //==== Detected the only the "free" signals ================================
  sigaction(SIGHUP,&act,&oact);    // ...... hangup  

#ifdef OBJS
  if(oact.sa_handler) 
	sigaction(SIGHUP,&oact,&oact);
#endif

  sigaction(SIGINT,&act,&oact);   // ...... interrupt   

#ifdef OBJS
  if(oact.sa_handler) 
	sigaction(SIGINT,&oact,&oact);
#endif
            
  sigaction(SIGQUIT,&act,&oact);  // ...... quit

#ifdef OBJS
  if(oact.sa_handler) 
	sigaction(SIGQUIT,&oact,&oact);
#endif

  sigaction(SIGILL,&act,&oact);   // ...... illegal instruction 

#ifdef OBJS
  if(oact.sa_handler) 
	sigaction(SIGILL,&oact,&oact);
#endif

  sigaction(SIGBUS,&act,&oact);   // ...... bus error 

#ifdef OBJS
  if(oact.sa_handler) 
	sigaction(SIGBUS,&oact,&oact);
#endif

#if (!defined (linux)) && (!defined(LININTEL))
  sigaction(SIGSYS,&act,&oact);   // ...... bad argument to system call

# ifdef OBJS
  if(oact.sa_handler) 
	sigaction(SIGSYS,&oact,&oact);
# endif
#endif

#if defined (__sgi) || defined(IRIX)
  sigaction(SIGTRAP,&act,&oact);   // Integer Divide By Zero (IRIX)

# ifdef OBJS
  if(oact.sa_handler) 
	sigaction(SIGTRAP,&oact,&oact);
# endif
#endif

#ifdef SA_SIGINFO
	act.sa_sigaction = (void(*)(int, siginfo_t *, void*)) &SegvHandler ;
#else
	act.sa_handler = (SIG_PFV) &SegvHandler ; 
#endif

  if ( sigaction( SIGSEGV , &act , &oact ) )  // ...... segmentation violation
    perror("OSD::SetSignal sigaction( SIGSEGV , &act , &oact ) ") ;

#ifdef OBJS
  if(oact.sa_handler) 
	sigaction(SIGSEGV,&oact,&oact);
#endif
#if defined(__osf__) || defined(DECOSF1)
   struct sigaction action, prev_action;
   action.sa_handler = SIG_IGN;
   action.sa_mask = 0;
   action.sa_flags = 0;
   
   if (sigaction (SIGFPE, &action, &prev_action) == -1) {
     perror ("sigaction");
     exit (1);
   }
#endif

}
//============================================================================
//==== Handler 
//====     Catche the differents signals:
//====          1- The Fatal signals, which cause the end of process:
//====          2- The exceptions which are "signaled" by Raise.
//====     The Fatal Signals:
//====        SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGKILL, SIGBUS, SIGSYS
//====     The Exceptions:
//====        SIGFPE
//====         (SUN versions)
//====           FPE_INTOVF_TRAP    // ..... integer overflow
//====           FPE_INTDIV_TRAP    // ..... integer divide by zero
//====           FPE_FLTINEX_TRAP   // ..... [floating inexact result]
//====           FPE_FLTDIV_TRAP    // ..... [floating divide by zero]
//====           FPE_FLTUND_TRAP    // ..... [floating underflow]
//====           FPE_FLTOPER_TRAP   // ..... [floating inexact result]
//====           FPE_FLTOVF_TRAP    // ..... [floating overflow]
//==== SIGSEGV is handled by "SegvHandler()"
//============================================================================


void OSD::Handler(const OSD_Signals theSignal,
		  const Standard_Address
#ifdef SA_SIGINFO
		                         theSigInfo
#endif
		  ,const Standard_Address
#if defined(HAVE_PTHREAD_H) && defined(NO_CXX_EXCEPTION) 
                                         theContext
#endif
		  )
{
  struct sigaction oldact, act;

  // re-install the signal

  if ( ! sigaction (theSignal, NULL, &oldact) ) {
      // cout << " signal is " << theSignal << " handler is " <<  oldact.sa_handler << endl;
      if (sigaction (theSignal, &oldact, &act)) perror ("sigaction");
  }
  else 
      perror ("sigaction");

  siginfo_t * aSigInfo = NULL;
#ifdef SA_SIGINFO
  aSigInfo = (siginfo_t *) theSigInfo;
#endif

#if defined(HAVE_PTHREAD_H) && defined(NO_CXX_EXCEPTION) 

//#ifdef DEB
//  cout << " current thread " << pthread_self() << endl;
//#endif


  if (pthread_self() != getOCCThread()  || !Standard_ErrorHandler::IsInTryBlock()) {
    // use the previous signal handler
      // cout << "OSD::Handler: signal " << (int) theSignal << " occured outside a try block " <<  endl ;
    
    struct sigaction *oldSignals = GetOldSigAction();
    struct sigaction  asigacthandler =  oldSignals[(int) theSignal];
  
    if (asigacthandler.sa_flags & SA_SIGINFO) {
      void (*aCurInfoHandle)(int, siginfo_t *, void *) = asigacthandler.sa_sigaction;
      if (aSigInfo) {
	switch (aSigInfo->si_signo) {
	case SIGFPE:
	  {
#ifdef SOLARIS
	    sigfpe_handler_type *aIEEEHandlerTab = GetOldFPE();
	    sigfpe_handler_type  aIEEEHandler = NULL;

	    switch (aSigInfo->si_code) {
	    case FPE_INTDIV_TRAP :
	    case FPE_FLTDIV_TRAP :
	      aIEEEHandler = aIEEEHandlerTab[1];
	      break;
	    case FPE_INTOVF_TRAP :
	    case FPE_FLTOVF_TRAP :
	      aIEEEHandler = aIEEEHandlerTab[2];
	      break;
	    case FPE_FLTUND_TRAP :
	      aIEEEHandler = aIEEEHandlerTab[4];
	      break;
	    case FPE_FLTRES_TRAP:
	      aIEEEHandler = aIEEEHandlerTab[3];
	      break;
	    case FPE_FLTINV_TRAP :
	      aIEEEHandler = aIEEEHandlerTab[0];
	      break;
	    case FPE_FLTSUB_TRAP :
	    default:
	      break;
	    }
	    if (aIEEEHandler) {
	      // cout << "OSD::Handler: calling previous IEEE signal handler with info" <<  endl ;
	      void (*aFPEHandler)(int, siginfo_t *, void *) = (void(*)(int, siginfo*, void*)) aIEEEHandler;
	      (*aFPEHandler) (theSignal, aSigInfo, theContext);
	      return;
	    }
#endif
	  }
	  break;
	case SIGSEGV:
	  switch (aSigInfo->si_code) {
	  case SEGV_MAPERR:   
	    // cout << "OSD::Handler: SIGSEGV signal : address not mapped to object"; 
	    break;
	  case SEGV_ACCERR:
	    // cout << "OSD::Handler: SIGSEGV signal : invalid permissions for mapped object"; 
	    break;
	  default:
	    // cout << "OSD::Handler: SIGSEGV signal : unknown segv"; 
	    break;
	  }
	  // cout << " at address " << (void *) aSigInfo->si_addr << endl; 
	  break;
	case SIGBUS:
	  switch (aSigInfo->si_code) {
	  case BUS_ADRALN:
	    // cout << "OSD::Handler: SIGBUS signal : invalid address alignment";
	    break;
	  case BUS_ADRERR:
	    // cout << "OSD::Handler: SIGBUS signal : non-existent physical address"; 
	    break;
	  case BUS_OBJERR:
	    // cout << "OSD::Handler: SIGBUS signal :  object specific hardware error"; 
	    break;
	  default:
	    // cout << "OSD::Handler: SIGBUS signal : unknown sig bus";
	    break;
	  }
	  // cout << " at " << (void *) aSigInfo->si_addr << endl; 
	  break;
	case SIGILL:
	    // cout << "OSD::Handler: illegal instruction signal " << endl; 
	    break;
#ifdef SIGSYS
	case SIGSYS:
	    // cout << "OSD::Handler: bad argument to system call signal"<< endl ;
	    break;
#endif
	case SIGINT:
	    // cout << "OSD::Handler:  interrupt signal" << endl;
	    break;
	default:
	  break;
	}
      }
      if (aCurInfoHandle) {
	  // cout << "OSD::Handler: calling previous signal handler with info " << aCurInfoHandle <<  endl ;
	(*aCurInfoHandle) (theSignal, aSigInfo, theContext);
	cerr << " previous signal handler return" <<  endl ;
	return;
      }
      else {
	// cout << "OSD::Handler: no handler with info for the signal" << endl;
      }
    } else {
	// no siginfi needed for the signal
      void (*aCurHandler) (int) = asigacthandler.sa_handler;
      if(aCurHandler) {
	// cout << "OSD::Handler: calling previous signal handler" <<  endl ;
	(*aCurHandler) (theSignal);
	cerr << " previous signal handler return" <<  endl ;
	return;
      } 
    }
    // cout << " Signal occured outside a try block, but no handler for it" <<endl;
    return;
  }
#endif


  // cout << "OSD::Handler: signal " << (int) theSignal << " occured inside a try block " <<  endl ;

  if ( ADR_ACT_SIGIO_HANDLER != NULL ) (*ADR_ACT_SIGIO_HANDLER)() ;
    
#ifdef linux
  if (fFltExceptions)
    feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
    //feenableexcept (FE_INVALID | FE_DIVBYZERO);
#endif

  sigset_t set;
  sigemptyset(&set);

  switch(theSignal) {

  case SIGHUP:
    OSD_SIGHUP::NewInstance("SIGHUP 'hangup' detected.")->Jump();
    exit(SIGHUP);
    break;

  case SIGINT:
    OSD_SIGINT::NewInstance("SIGINT 'interrupt' detected.")->Jump();
    exit(SIGINT);
    break;

  case SIGQUIT:
    OSD_SIGQUIT::NewInstance("SIGQUIT 'quit' detected.")->Jump();
    exit(SIGQUIT);
    break;

  case SIGILL:
    OSD_SIGILL::NewInstance("SIGILL 'illegal instruction' detected.")->Jump();
    exit(SIGILL);
    break;

  case SIGKILL:
    OSD_SIGKILL::NewInstance("SIGKILL 'kill' detected.")->Jump();
    exit(SIGKILL);
    break;

  case SIGBUS:
    sigaddset(&set, SIGBUS);
    sigprocmask(SIG_UNBLOCK, &set, NULL) ;
    OSD_SIGBUS::NewInstance("SIGBUS 'bus error' detected.")->Jump();
    exit(SIGBUS);
    break;

  case SIGSEGV:
    OSD_SIGSEGV::NewInstance("SIGSEGV 'segmentation violation' detected.")->Jump();
    exit(SIGSEGV);
    break;

#ifdef SIGSYS
  case SIGSYS:
    OSD_SIGSYS::NewInstance("SIGSYS 'bad argument to system call' detected.")->Jump();
    exit(SIGSYS);
    break;
#endif

  case SIGFPE: 
    {
    sigaddset(&set, SIGFPE);
    sigprocmask(SIG_UNBLOCK, &set, NULL) ;
#ifdef DECOSF1
// Pour DEC/OSF1 SIGFPE = Division par zero.
// should be clarified why in debug mode only?
#ifdef DEBUG
    Standard_DivideByZero::NewInstance('')->Jump;
#endif
    break;
#endif	
#if (!defined (__sun)) && (!defined(SOLARIS))
    Standard_NumericError::NewInstance("SIGFPE Arithmetic exception detected")->Jump();
    break;
#else
    // Reste SOLARIS
    if (aSigInfo ) {
      switch(aSigInfo->si_code) {
      case FPE_FLTDIV_TRAP :
	Standard_DivideByZero::NewInstance("Floating Divide By Zero")->Jump(); break;
      case FPE_INTDIV_TRAP :
	Standard_DivideByZero::NewInstance("Integer Divide By Zero")->Jump(); break;
      case FPE_FLTOVF_TRAP :
	Standard_Overflow::NewInstance("Floating Overflow")->Jump(); break;
      case FPE_INTOVF_TRAP :
	Standard_Overflow::NewInstance("Integer Overflow")->Jump(); break;
      case FPE_FLTUND_TRAP :
	Standard_NumericError::NewInstance("Floating Underflow")->Jump(); break;
      case FPE_FLTRES_TRAP:
	Standard_NumericError::NewInstance("Floating Point Inexact Result")->Jump(); break;
      case FPE_FLTINV_TRAP :
	Standard_NumericError::NewInstance("Invalid Floating Point Operation")->Jump(); break;
      default:
	Standard_NumericError::NewInstance("Numeric Error")->Jump(); break;
      }
    }
    else {
      Standard_NumericError::NewInstance("SIGFPE Arithmetic exception detected")->Jump();
    }
#endif
    break;
  }
#if defined (__sgi) || defined(IRIX)
  case SIGTRAP: 
    sigaddset(&set, SIGTRAP);
    sigprocmask(SIG_UNBLOCK, &set, NULL) ;
    Standard_DivideByZero::NewInstance("SIGTRAP IntegerDivideByZero")->Jump(); break;
#endif
  default:
    cout << "Unexpected signal " << (Standard_Integer ) theSignal << endl ;
  }
}

//============================================================================
//==== SegvHandler 
//============================================================================

#ifdef SA_SIGINFO

#ifdef NO_CXX_EXCEPTION
void OSD::SegvHandler(const OSD_Signals theSig,
                      const Standard_Address ip,
		      const Standard_Address theContext)
{
  if (!Standard_ErrorHandler::IsInTryBlock()) {
    Handler(theSig, ip, theContext);
    return;
  }
#else
void OSD::SegvHandler(const OSD_Signals,
                      const Standard_Address ip,
		      const Standard_Address)
{
#endif

#ifdef linux
  if (fFltExceptions)
    feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
    //feenableexcept (FE_INVALID | FE_DIVBYZERO);
#endif

//  cout << "OSD::SegvHandler activated(SA_SIGINFO)" << endl ;
  if ( ip != NULL ) {
     sigset_t set;
     sigemptyset(&set);
     sigaddset(&set, SIGSEGV);
     sigprocmask (SIG_UNBLOCK, &set, NULL) ;
     void *address = ((siginfo_t *)ip)->si_addr ;
     if ( (((long) address )& ~0xffff) == (long) UndefinedHandleAddress ) {
	Standard_NullObject::NewInstance("Attempt to access to null object")->Jump();
      }
     else {
       char Msg[100];
       sprintf(Msg,"SIGSEGV 'segmentation violation' detected. Address %lx",
	       (long ) address ) ;
       OSD_SIGSEGV::NewInstance(Msg)->Jump();
     }
   }
  else
    cout << "Wrong undefined address." << endl ;
  exit(SIGSEGV);
}

#if defined (_hpux) || defined(HPUX)
//============================================================================
//==== SegvHandler 
//============================================================================

// Not ACTIVE ? SA_SIGINFO is defined on SUN, OSF, SGI and HP (and Linux) !
// pour version 09.07
void OSD::SegvHandler(const OSD_Signals aSig, const Standard_Address code,
                      const Standard_Address scp)
//void OSD::SegvHandler(const OSD_Signals aSig, int code, const Standard_Address scp)
{
  unsigned long Space  ;
  unsigned long Offset ;
  char Msg[100] ;

  if ( scp != NULL ) {
    Space = ((struct sigcontext *)scp)->sc_sl.sl_ss.ss_cr20 ;
    Offset = ((struct sigcontext *)scp)->sc_sl.sl_ss.ss_cr21 ;
//    cout << "Wrong address = " << hex(Offset) << endl ;
    if ((Offset & ~0xffff) == (long)UndefinedHandleAddress)
	Standard_NullObject::Jump("Attempt to access to null object") ;
    else {
       sprintf(Msg,"SIGSEGV 'segmentation violation' detected. Address %lx",Offset) ;
       OSD_SIGSEGV::Jump(Msg);
//    scp->sc_pcoq_head = scp->sc_pcoq_tail ;       Permettrait de continuer a
//    scp->sc_pcoq_tail = scp->sc_pcoq_tail + 0x4 ; l'intruction suivant le segv.
    }
  }
  else
    cout << "Wrong undefined address." << endl ;
  exit(SIGSEGV);
} 

#endif
#else
// Must be there for compatibility with Windows NT system ---------------

Standard_Integer OSD :: WntHandler ( const Standard_Address )
  {return 0 ;}

#endif
#endif
