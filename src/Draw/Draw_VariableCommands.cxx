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



#include <Draw.ixx>
#ifdef HAVE_CONFIG_H
# include <oce-config.h>
#endif

#include <Standard_Stream.hxx>
#include <Standard_SStream.hxx>

#if defined(HAVE_IOS) || defined(WNT)
# include <ios>
#elif defined(HAVE_IOS_H)
# include <ios.h>
#endif

#include <Draw_Display.hxx>
#include <Draw_Appli.hxx>
#include <Draw_Number.hxx>
#include <Draw_Axis3D.hxx>
#include <Draw_Axis2D.hxx>
#include <Draw_Grid.hxx>
#include <Draw_Drawable3D.hxx>
#include <Draw_SequenceOfDrawable3D.hxx>
#include <Draw_VMap.hxx>
#include <Draw_ProgressIndicator.hxx>

#ifdef WNT
extern Draw_Viewer dout;
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#include <tcl.h>
#include <errno.h>

#include <OSD_Environment.hxx>

Standard_Boolean Draw_ParseFailed;

static Standard_Boolean autodisp = Standard_True;
static Standard_Boolean repaint2d,repaint3d;

extern Draw_Interpretor theCommands;

//===============================================
// dictionnary of variables
// Variables are stored in a map Integer, Transient
// The Integer Value is the content of the TCl variable 
//===============================================

static Draw_VMap theVariables;

//=======================================================================
//function : FindVariable
//purpose  : 
//=======================================================================

static Standard_Integer p_id;
static Standard_Integer p_X;
static Standard_Integer p_Y;
static Standard_Integer p_b;
static const char* p_Name = "";


static Draw_SaveAndRestore* Draw_First = NULL;

//=======================================================================
//function : Draw_SaveAndRestore
//purpose  : 
//=======================================================================

Draw_SaveAndRestore::Draw_SaveAndRestore
  (const char* name,
   Standard_Boolean (*test)(const Handle(Draw_Drawable3D)&),
  void (*save)(const Handle(Draw_Drawable3D)&, ostream&),
  Handle(Draw_Drawable3D) (*restore) (istream&),
  Standard_Boolean display) :
  myName(name),
  myTest(test),
  mySave(save), 
  myRestore(restore),
  myDisplay(display),
  myNext(Draw_First)
{
  Draw_First = this;
}

Standard_Boolean Draw_SaveAndRestore::Test(const Handle(Draw_Drawable3D)&d)
{return (*myTest) (d);}

void Draw_SaveAndRestore::Save(const Handle(Draw_Drawable3D)& d, 
			       ostream& os) const
{ (*mySave) (d,os);}

Handle(Draw_Drawable3D) Draw_SaveAndRestore::Restore(istream& is) const
{return (*myRestore) (is);}

//=======================================================================
// numeric save and restore
//=======================================================================

static Standard_Boolean numtest(const Handle(Draw_Drawable3D)& d) 
{
  return d->IsInstance(STANDARD_TYPE(Draw_Number));
}

static void numsave(const Handle(Draw_Drawable3D)&d, ostream& OS)
{
  Handle(Draw_Number) N = Handle(Draw_Number)::DownCast(d);
#if (defined(HAVE_IOS) && !defined(__sgi) && !defined(IRIX)) || ( defined(WNT) && !defined(USE_OLD_STREAMS))
  ios::fmtflags F = OS.flags();
  OS.setf(ios::scientific);
  OS.precision(15);
  OS.width(30);
#else
  long form = OS.setf(ios::scientific);
  int  prec = OS.precision(15);
  int w = OS.width(30);
#endif
  OS << N->Value()<<"\n";                                                                                 
  #if (defined(HAVE_IOS) && !defined(__sgi) && !defined(IRIX)) || (defined(WNT)&& !defined(USE_OLD_STREAMS))
  OS.setf(F);
#else
  OS.setf(form);
  OS.precision(prec);
  OS.width(w);
#endif
}

static Handle(Draw_Drawable3D) numrestore (istream& is)
{
  Standard_Real val;
  is >> val;
  Handle(Draw_Number) N = new Draw_Number(val);
  return N;
}


static Draw_SaveAndRestore numsr("Draw_Number",
				 numtest,numsave,numrestore,
				 Standard_False);

//=======================================================================
// save
//=======================================================================

static Standard_Integer save(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n <= 2) return 1;


  const char* name = a[2];
  filebuf fic;
  ostream os(&fic);
  os.precision(15);
  if (!fic.open(name,ios::out)) {
    di << "Cannot open file for writing "<<name;
    return 1;
  }

  Handle(Draw_Drawable3D) D = Draw::Get(a[1]);
  if (!D.IsNull()) {
    // find a tool
    Draw_SaveAndRestore* tool = Draw_First;
    Handle(Draw_ProgressIndicator) progress = new Draw_ProgressIndicator ( di, 1 );
    progress->SetScale ( 0, 100, 1 );
    progress->NewScope(100,"Writing");
    progress->Show();

    while (tool) {
      if (tool->Test(D)) break;
      tool = tool->Next();
    }
    if (tool) {
      os << tool->Name() << "\n";
      Draw::SetProgressBar(progress);
      tool->Save(D,os);
      os << "\n";
    }
    else {
      di << "No method for saving " << a[1];
      return 1;
    }
    Draw::SetProgressBar( 0 );
    progress->EndScope();
    progress->Show();
  }
  
  os << "0\n\n";

  Standard_Boolean res = Standard_False;

  errno = 0;
  fic.close();

  res = os.good() && !errno;
  if( !res )
  {
    di<<"File has not been written";
    return 1;
  }

  di << a[1];
  return 0;
}

//=======================================================================
// read
//=======================================================================

static Standard_Integer restore(Draw_Interpretor& di, Standard_Integer n, const char** a)
{

  if (n <= 2) return 1;

  const char* fname = a[1];
  const char* name  = a[2];
  
  filebuf fic;
  istream in(&fic);
  if (!fic.open(fname,ios::in)) {
    di << "Cannot open file for reading : "<<fname;
    return 1;
  }
  
  char typ[255];
  in >> typ;
  if (!in.fail()) {
    // search a tool
    Handle(Draw_ProgressIndicator) progress = new Draw_ProgressIndicator ( di, 1 );
    progress->NewScope(100,"Reading");
    progress->Show();

    Draw_SaveAndRestore* tool = Draw_First;
    while (tool) {
      if (!strcmp(typ,tool->Name())) break;
      Draw::SetProgressBar(progress);
      tool = tool->Next();
    }
    if (tool) {
      Handle(Draw_Drawable3D) D = tool->Restore(in);
      Draw::Set(name,D,tool->Disp() && autodisp);
    }
    else {
      di << "Cannot restore a  " << typ;
      return 1;
    }
    Draw::SetProgressBar( 0 );
    progress->EndScope();
    progress->Show();
  }
  
  di << name;
  return 0;
}

//=======================================================================
// display
//=======================================================================

static Standard_Integer display(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n <= 1) return 1;
  else {
    for (Standard_Integer i = 1; i < n; i++) {
      Handle(Draw_Drawable3D) D = Draw::Get(a[i]);
      if (!D.IsNull()) {
	if (!D->Visible()) {
	  dout << D;
	  di << a[i] << " ";
	}
      }
    }
  }
  return 0;
}

//=======================================================================
// erase, clear, donly
//=======================================================================

static Standard_Integer erase(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  static Standard_Boolean draw_erase_mute = Standard_False;
  if (n == 2) {
    if (!strcasecmp(a[1],"-mute")) {
      draw_erase_mute = Standard_True;
      return 0;
    }
  }

  Standard_Boolean donly = !strcasecmp(a[0],"donly");
  
  if (n <= 1 || donly) {
    // clear, 2dclear, donly, erase (without arguments)
    Standard_Integer i;
    
    // solve the names for "." before erasing
    if (donly) {
      for (i = 1; i < n; i++) {
	Handle(Draw_Drawable3D) D = Draw::Get(a[i]);
	if (D.IsNull()) {
	  if ((a[i][0] == '.') && (a[i][1] == '\0'))
	    cout << "Missed !!!" << endl;
	  return 0;
	}
      }
    }
    
    // sauvegarde des proteges visibles
    Draw_SequenceOfDrawable3D prot;
    for (i = 1; i <= theVariables.Extent(); i++) {
      const Handle(Draw_Drawable3D)& D = *((Handle(Draw_Drawable3D)*)&theVariables(i));
      if (!D.IsNull()) {
	if (D->Protected() && D->Visible())
	  prot.Append(D);
      }
    }
  
    // effacement de toutes les variables
    Standard_Integer erasemode = 1;
    if (a[0][0] == '2') erasemode = 2;
    if (a[0][0] == 'c') erasemode = 3;
    
    // effacement des graphiques non variables
    if (erasemode == 2) 
      dout.Clear2D();
    else if (erasemode == 3)
      dout.Clear3D();
    else
      dout.Clear();
    
    // affichage pour donly
    if (donly) {
      for (i = 1; i < n; i++) {
	Handle(Draw_Drawable3D) D = Draw::Get(a[i]);
	if (!D.IsNull()) {
	  if (!D->Visible()) {
	    dout << D;
	    if (!draw_erase_mute) di << a[i] << " ";
	  }
	}
      }
    }
    
  // afficahge des proteges
    for (i = 1; i <= prot.Length(); i++)
      dout << prot(i);
    
    
  }
  else {
    for (Standard_Integer i = 1; i < n; i++) {
      Handle(Draw_Drawable3D) D = Draw::Get(a[i]);
      if (!D.IsNull()) {
	if (D->Visible()) {
	    dout.RemoveDrawable(D);
	    if (!draw_erase_mute) di << D->Name() << " ";
	  }
      }
    }
    dout.Repaint2D();
    dout.Repaint3D();
  }
  draw_erase_mute = Standard_False;
  repaint2d = Standard_False;
  repaint3d = Standard_False;
  dout.Flush();
  return 0;
}



//=======================================================================
// draw
//=======================================================================

static Standard_Integer draw(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  if (n < 3) return 1;
  Standard_Integer id = atoi(a[1]);
  if (!dout.HasView(id)) {
    cout << "bad view number in draw"<<endl;
    return 1;
  }
  Standard_Integer mo = atoi(a[2]);
  Draw_Display d = dout.MakeDisplay(id);
  d.SetMode(mo);
  Standard_Integer i;
  for (i = 3; i < n; i++) {
    Handle(Draw_Drawable3D) D = Draw::Get(a[i]);
    if (!D.IsNull()) D->DrawOn(d);
  }
  d.Flush();
  return 0;
}

//=======================================================================
// protect, unprotect
//=======================================================================

static Standard_Integer protect(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n <= 1) return 1;
  Standard_Boolean prot = *a[0] != 'u';
  for (Standard_Integer i = 1; i < n; i++) {
    Handle(Draw_Drawable3D) D = Draw::Get(a[i]);
    if (!D.IsNull()) {
      D->Protected(prot);
      di << a[i] << " ";
    }
  }
  return 0;
}

//=======================================================================
// autodisplay
//=======================================================================

static Standard_Integer autodisplay(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n <= 1)
    autodisp = !autodisp;
  else 
    autodisp = !(!strcasecmp(a[1],"0"));

  if (autodisp)
    di << "1";
  else
    di << "0";

  return 0;
}


//=======================================================================
// whatis
//=======================================================================

static Standard_Integer whatis(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n <= 1) return 1;
  for (Standard_Integer i = 1; i < n; i++) {
    Handle(Draw_Drawable3D) D = Draw::Get(a[i]);
    if (!D.IsNull()) {
      D->Whatis(di);
    }
  }
  return 0;
}


//=======================================================================
// value
//=======================================================================

static Standard_Integer value(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n != 2) return 1;
  di << atof(a[1]);

  return 0;
}

//=======================================================================
//function : dname
//purpose  : 
//=======================================================================
static Standard_Integer dname(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n <= 1) {
    return 1;
  }
  //
  Standard_PCharacter pC;
  Standard_Integer i;
  Handle(Draw_Drawable3D) aD;
  //
  for (i = 1; i < n; ++i) {
    aD = Draw::Get(a[i]);
    if (!aD.IsNull()) {
      //modified by NIZNHY-PKV Tue Jun 10 10:18:13 2008f
      //di << a[i];
      pC=(Standard_PCharacter)aD->Name();
      di << pC;
      //modified by NIZNHY-PKV Tue Jun 10 10:18:18 2008t
    }
  }
  return 0;
}

//=======================================================================
// dump
//=======================================================================


static Standard_Integer dump(Draw_Interpretor& DI, Standard_Integer n, const char** a)
{
  if(n < 2) return 1;
  Standard_Integer i;
  for (i = 1; i < n; i++) {
    Handle(Draw_Drawable3D) D = Draw::Get(a[i]);
    if (!D.IsNull()) {
      Standard_SStream sss;
      sss.precision(15);
      sss << "\n\n*********** Dump of " << a[i] << " *************\n";
      D->Dump(sss);
      DI << sss;
    }
  }
  return 0;
}

//=======================================================================
// copy
//=======================================================================

static Standard_Integer copy(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  if (n < 3) return 1;
  Standard_Boolean cop = !strcasecmp(a[0],"copy");

  Handle(Draw_Drawable3D) D;
  for (Standard_Integer i = 1; i < n; i += 2) {
    if (i+1 >= n) return 0;
    D = Draw::Get(a[i]);
    if (!D.IsNull()) {
      if (cop) 
	D = D->Copy();
      else 
	// clear old name
	Draw::Set(a[i],Handle(Draw_Drawable3D()));

      Draw::Set(a[i+1],D);
    }
  }
  return 0;
}

//=======================================================================
//function : repaint
//purpose  : 
//=======================================================================

static Standard_Integer repaintall(Draw_Interpretor& , Standard_Integer , const char** )
{
  if (repaint2d) dout.Repaint2D();
  repaint2d = Standard_False;
  if (repaint3d) dout.Repaint3D();
  repaint3d = Standard_False;
  dout.Flush();
  return 0;
}

//=======================================================================
//function : set
//purpose  : 
//=======================================================================

static Standard_Integer set(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 2) return 1;
  Standard_Integer i = 1;
  Standard_Real val=0;
  for (i = 1; i < n; i += 2) {
    val = 0;
    if (i+1 < n) val = atof(a[i+1]);
    Draw::Set(a[i],val);
  }
  di << val;
  return 0;
}

//=======================================================================
//function : dsetenv
//purpose  : 
//=======================================================================

static Standard_Integer dsetenv(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 2) {
    cout << "Use: " << argv[0] << " {varname} [value]" << endl;
    return 1;
  }

  OSD_Environment env (argv[1]);
  if (argc > 2 && argv[2][0] != '\0')
  {
    env.SetValue (argv[2]);
    env.Build();
  }
  else
    env.Remove();
  return env.Failed();
}

//=======================================================================
//function : dgetenv
//purpose  : 
//=======================================================================

static Standard_Integer dgetenv(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc < 2) {
    cout << "Use: " << argv[0] << " {varname}" << endl;
    return 1;
  }

  const char* val = getenv (argv[1]);
  di << ( val ? val : "" );
  return 0;
}

//=======================================================================
//function : isdraw
//purpose  : 
//=======================================================================

static Standard_Integer isdraw(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n != 2) return 1;
  Handle(Draw_Drawable3D) D = Draw::Get(a[1],Standard_False);
  if (D.IsNull())
    di << "0";
  else
    di << "1";
  return 0;
}

//=======================================================================
//function : isprot
//purpose  : 
//=======================================================================

Standard_Integer isprot(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n != 2) return 1;
  Handle(Draw_Drawable3D) D = Draw::Get(a[1],Standard_False);
  if (D.IsNull())
    di << "0";
  else {
    if (D->Protected())
      di << "1";
    else
      di << "0";
  }
  return 0;
}


//=======================================================================
//function : pick
//purpose  : 
//=======================================================================

static Standard_Integer pick(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  if (n < 6) return 1;
  Standard_Integer id;
  Standard_Integer X,Y,b;
  Standard_Boolean wait = (n == 6);
  if (!wait) id = atoi(a[1]);
  dout.Select(id,X,Y,b,wait);
  Standard_Real z = dout.Zoom(id);
  gp_Pnt P((Standard_Real)X /z,(Standard_Real)Y /z,0);
  gp_Trsf T;
  dout.GetTrsf(id,T);
  T.Invert();
  P.Transform(T);
  Draw::Set(a[1],id);
  Draw::Set(a[2],P.X());
  Draw::Set(a[3],P.Y());
  Draw::Set(a[4],P.Z());
  Draw::Set(a[5],b);
  return 0;
}


//=======================================================================
//function : lastrep
//purpose  : 
//=======================================================================

static Standard_Integer lastrep(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 5) return 1;

  Draw::Set(a[1],p_id);
  if (n == 5) {
    Draw::Set(a[2],p_X);
    Draw::Set(a[3],p_Y);
  }
  else if (n == 6) {
    Standard_Real z = dout.Zoom(p_id);
    gp_Pnt P((Standard_Real)p_X /z,(Standard_Real)p_Y /z,0);
    gp_Trsf T;
    dout.GetTrsf(p_id,T);
    T.Invert();
    P.Transform(T);
    Draw::Set(a[2],P.X());
    Draw::Set(a[3],P.Y());
    Draw::Set(a[4],P.Z());
  }
  else {
    di << "Too many args";
    return 1;
  }
  Draw::Set(a[n-1],p_b);
  di << p_Name;
  return 0;
}


//=======================================================================
//function : Set
//purpose  : 
//=======================================================================
void Draw::Set(const Standard_CString name, 
	       const Handle(Draw_Drawable3D)& D)
{
 Draw::Set(name,D,autodisp);
}

// MKV 29.03.05
#if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4))) && !defined(USE_NON_CONST)
static char* tracevar(ClientData CD, Tcl_Interp*,const char*,const char*, Standard_Integer)
#else
static char* tracevar(ClientData CD, Tcl_Interp*, char*, char*, Standard_Integer)
#endif
{
  // protect if the map was destroyed before the interpretor
  if (theVariables.IsEmpty()) return NULL;

  // MKV 29.03.05
#if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4))) && !defined(USE_NON_CONST)
  Handle(Draw_Drawable3D)& D = *((Handle(Draw_Drawable3D)*)&theVariables((long)CD));
#else
  Standard_Integer index = (Standard_Integer) CD;
  Handle(Draw_Drawable3D)& D = *((Handle(Draw_Drawable3D)*)&theVariables(index));
#endif
  if (D.IsNull())
    return NULL;
  if (D->Protected())
    return (char*) "variable is protected";
  else {
    if (D->Visible()) {
      dout.RemoveDrawable(D);
      if (D->Is3D()) 
	repaint3d = Standard_True;
      else
	repaint2d = Standard_True;
    }
    D.Nullify();
    return NULL;
  }
}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================
void Draw::Set(const Standard_CString name, 
	       const Handle(Draw_Drawable3D)& D,
	       const Standard_Boolean displ)
{
  Standard_PCharacter pName;
  //
  pName=(Standard_PCharacter)name;
  //
  if ((name[0] == '.') && (name[1] == '\0')) {
    if (!D.IsNull()) {
      dout.RemoveDrawable(D);
      if (displ) dout << D;
    }
  }
  else {
    
    Tcl_UnsetVar(theCommands.Interp(),pName,0);
    if (!D.IsNull()) {
      Standard_Integer ival = theVariables.Extent() + 1;
      theVariables.Bind(ival,D);
      // MKV 29.03.05
#if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4))) && !defined(USE_NON_CONST)
      D->Name((const Standard_CString)Tcl_SetVar(theCommands.Interp(),name,name,0));
#else
      D->Name(Tcl_SetVar(theCommands.Interp(),pName,pName,0));
#endif
    
      // set the trace function
      Tcl_TraceVar(theCommands.Interp(),pName,TCL_TRACE_UNSETS,
		   tracevar,(ClientData)ival);
      
      if (displ) {
	if (!D->Visible())
	  dout << D;
      }
      else if (D->Visible())
	dout.RemoveDrawable(D);
    }
  }
}
//=======================================================================
//function : Set
//purpose  : 
//=======================================================================
void Draw::Set(const Standard_CString Name, const Standard_Real val)
{
  if ((Name[0] == '.') && (Name[1] == '\0')) return;
  Standard_CString aName = Name;
  Handle(Draw_Drawable3D) D = Draw::Get(aName,Standard_False);
  Handle(Draw_Number) N;
  if (!D.IsNull()) {
    N = Handle(Draw_Number)::DownCast(D);
  }
  if (N.IsNull()) {
    N = new Draw_Number(val);
    Draw::Set(aName,N,Standard_False);
  }
  else
    N->Value(val);
}
//=======================================================================
//function : Get
//purpose  : 
//=======================================================================
Handle(Draw_Drawable3D) Draw::Get(Standard_CString& name, 
			          const Standard_Boolean )
{
#if !((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4))) || defined(USE_NON_CONST)
  Standard_PCharacter pName;
  pName=(Standard_PCharacter)name;
#endif
  //
  Standard_Boolean pick = ((name[0] == '.') && (name[1] == '\0'));
  Handle(Draw_Drawable3D) D;
  if (pick) {
    cout << "Pick an object" << endl;
    dout.Select(p_id,p_X,p_Y,p_b);
    dout.Pick(p_id,p_X,p_Y,5,D,0);
    if (!D.IsNull()) {
      if (D->Name()) {
	name = p_Name = D->Name();
	//p_Name = (char *)D->Name();
      }
    }
  }
  else {
    // MKV 29.03.05
#if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4))) && !defined(USE_NON_CONST)
    Standard_Address index =  
      Tcl_VarTraceInfo(theCommands.Interp(),name,TCL_TRACE_UNSETS,
		       tracevar, NULL);
    if (index != 0) 
      D = Handle(Draw_Drawable3D)::DownCast(theVariables((long)index));
#else
    Standard_Integer index = (Standard_Integer) 
      Tcl_VarTraceInfo(theCommands.Interp(),
		       pName,
		       TCL_TRACE_UNSETS,
		       tracevar, NULL);
    if (index != 0)
      D = Handle(Draw_Drawable3D)::DownCast(theVariables(index));
#endif
#if 0
    if (D.IsNull() && complain)
      cout <<name<<" does not exist"<<endl;
#endif
  }
  return D;
}

//=======================================================================
//function : Get
//purpose  : 
//=======================================================================
Standard_Boolean Draw::Get(const Standard_CString name, 
			   Standard_Real& val)
{
  if ((name[0] == '.') && (name[1] == '\0')) {
    return Standard_False;
  }
  Standard_CString aName = name;
  Handle(Draw_Drawable3D) D = Draw::Get(aName,Standard_False);
  if (!D.IsNull()) {
    Handle(Draw_Number) N = Handle(Draw_Number)::DownCast(D);
    if (!N.IsNull()) {
      val = N->Value();
      return Standard_True;
    }
  }
  return Standard_False;
}

//=======================================================================
//function : LastPick
//purpose  : 
//=======================================================================
void  Draw::LastPick(Standard_Integer& view, 
		     Standard_Integer& X, 
		     Standard_Integer& Y, 
		     Standard_Integer& button)
{
  view = p_id;
  X = p_X;
  Y = p_Y;
  button = p_b;
}
//=======================================================================
//function : Repaint
//purpose  : 
//=======================================================================
void  Draw::Repaint()
{
  repaint2d = Standard_True;
  repaint3d = Standard_True;
}

//=======================================================================
//function : trigonometric functions
//purpose  : 
//=======================================================================

//static Standard_Integer trigo (Draw_Interpretor& di, Standard_Integer n, const char** a)
static Standard_Integer trigo (Draw_Interpretor& di, Standard_Integer , const char** a)
{

  Standard_Real x = atof(a[1]);

  if (!strcasecmp(a[0],"cos"))
    di << Cos(x);
  else if (!strcasecmp(a[0],"sin"))
    di << Sin(x);
  else if (!strcasecmp(a[0],"tan"))
    di << Tan(x);
  else if (!strcasecmp(a[0],"sqrt"))
    di << Sqrt(x);
  else if (!strcasecmp(a[0],"acos"))
    di << ACos(x);
  else if (!strcasecmp(a[0],"asin"))
    di << ASin(x);
  else if (!strcasecmp(a[0],"atan2"))
    di << ATan2(x,atof(a[2]));

  return 0;
}


//=======================================================================
// Atof and Atoi
//=======================================================================

#undef atof
#undef atoi

static Standard_Boolean Numeric(char c)
{
  return (c == '.' || (c >= '0' && c <= '9'));
}

static Standard_Boolean Alphabetic(char c)
{
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'));
}

static Standard_Real Parse(char*&);

static Standard_Real ParseValue(char*& name)
{
  while (*name == ' ' || *name == '\t') name++;
  Standard_Real x = 0;
  switch (*name) {

  case '\0' :
    break;

  case '(' :
    name++;
    x = Parse(name);
    if (*name != ')') 
      cout << "Mismatched parenthesis" << endl;
    name++;
    break;

  case '+' :
    name++;
    x = ParseValue(name);
    break;

  case '-' :
    name++;
    x = - ParseValue(name);
    break;

    default :
      {
	// process a string
	
	char* p = name;
	while (Numeric(*p)) p++;
	// process scientific notation
	if ((*p == 'e') || (*p == 'E')) {
	  if (Numeric(*(p+1)) || *(p+1) == '+' || *(p+1) == '-')
	    p+= 2;
	}
	while (Numeric(*p) || Alphabetic(*p)) p++;
	char c = *p;
	*p = '\0';
	
	if (Numeric(*name))   // numeric litteral
	  x = atof(name);
	else if (!Draw::Get((Standard_CString) name,x)) {  // variable
	  
	  // search for a function ...
	  *p = c;
	  // count arguments
	  Standard_Integer argc = 1;
	  char* q = p;
	  while ((*q == ' ') || (*q == '\t')) q++;
	  if (*q == '(') {
	    Standard_Integer pc = 1;
	    argc = 2;
	    q++;
	    while ((pc > 0) && *q) {
	      if (*q == '(') pc++;
	      if (*q == ')') pc--;
	      if ((pc == 1) && (*q == ',')) argc++;
	      q++;
	    }
	    if (pc > 0) {
	      cout << "Unclosed parenthesis"<< endl;
	      x = 0;
	    }
	    else {
	      // build function call 
	      // replace , and first and last () by space
	      if (argc > 1) {
		Standard_Integer i = 2;
		while (*p != '(') p++;
		*p = ' ';
		p++;
		pc = 1;
		while (pc > 0) {
		  if (*p == '(') pc++;
		  if (*p == ')') pc--;
		  if ((pc == 1) && (*p == ',')) {
		    *p = ' ';
		    p++;
		    i++;
		  }
		  else
		    p++;
		}
		*(p-1) = '\0';
		c = *p;

		// call the function, save the current result
		char* sv = 0;
		if (*theCommands.Result()) {
		  sv = new char [strlen(theCommands.Result())];
		  strcpy(sv,theCommands.Result());
		  theCommands.Reset();
		}
		if (theCommands.Eval(name) != 0) {
		  cout << "Call of function " << name << " failed" << endl;
		  x = 0;
		}
		else
		  x = atof(theCommands.Result());
		theCommands.Reset();
		if (sv) {
		  theCommands << sv;
		  delete [] sv;
		}
	      }
	    }
	  }
	  else
	    Draw_ParseFailed = Standard_True;
	}
	*p = c;
	name = p;
      }
    break;
    
  }
  while (*name == ' ' || *name == '\t') name++;
  return x;
}


static Standard_Real ParseFactor(char*& name)
{
  Standard_Real x = ParseValue(name);

  while (1) {
    char c = *name;
    if (c == '\0') return x;
    name++;
    switch (c) {

    case '*' :
      x *= ParseValue(name);
      break;

    case '/' :
      x /= ParseValue(name);
      break;

      default :
	name--;
	return x;
      
    }
  }
}

static Standard_Real Parse(char*& name)
{
  Standard_Real x = ParseFactor(name);

  while (1) {
    char c = *name;
    if (c == '\0') return x;
    name++;
    switch (c) {

    case '+' :
      x += ParseFactor(name);
      break;

    case '-' :
      x -= ParseFactor(name);
      break;

      default :
	name--;
	return x;
      
    }
  }
}
//=======================================================================
//function : Atof
//purpose  : 
//=======================================================================
Standard_Real Draw::Atof(const Standard_CString name)
{
  // copy the string
  char* n = new char[1+strlen(name)];
  char* b = n;
  strcpy(n,name);
  Standard_Real x = Parse(n);
  while ((*n == ' ') || (*n == '\t')) n++;
  if (*n) Draw_ParseFailed = Standard_True;
  delete [] b;
  return x;
}

Standard_Integer Draw::Atoi(const Standard_CString name)
{
  return (Standard_Integer ) Draw::Atof(name);
}
//=======================================================================
//function : Set
//purpose  : set a TCL var
//=======================================================================
void Draw::Set(const Standard_CString Name, const Standard_CString val)
{
  Standard_PCharacter pName, pVal;
  //
  pName=(Standard_PCharacter)Name;
  pVal=(Standard_PCharacter)val;
  //
  Tcl_SetVar(theCommands.Interp(), pName, pVal, 0);
}
//=======================================================================
// Command management
// refresh the screen
//=======================================================================

static void before()
{
  repaint2d = Standard_False;
  repaint3d = Standard_False;
}

void Draw_RepaintNowIfNecessary()
{
  if (repaint2d) dout.Repaint2D();
  if (repaint3d) dout.Repaint3D();
  repaint2d = Standard_False;
  repaint3d = Standard_False;
}

static void  after(Standard_Integer)
{
  Draw_RepaintNowIfNecessary();
}

extern void (*Draw_BeforeCommand)();
extern void (*Draw_AfterCommand)(Standard_Integer);


//=======================================================================
//function : Commands
//purpose  : 
//=======================================================================
void  Draw::VariableCommands(Draw_Interpretor& theCommands)
{
  static Standard_Boolean Done = Standard_False;
  if (Done) return;
  Done = Standard_True;

  // set up start and stop command
  Draw_BeforeCommand = &before;
  Draw_AfterCommand  = &after;

  //  set up some variables

  const char* n;
  Handle(Draw_Axis3D) theAxes3d = new Draw_Axis3D(gp_Pnt(0,0,0),Draw_bleu,20);
  n = "axes";
  Draw::Set(n,theAxes3d);
  theAxes3d->Protected(Standard_True);

  Handle(Draw_Axis2D) theAxes2d = new Draw_Axis2D(gp_Pnt2d(0,0),Draw_bleu,20);
  n = "axes2d";
  Draw::Set(n,theAxes2d);
  theAxes2d->Protected(Standard_True);

  n = "pi";
  Draw::Set(n,M_PI);
  Draw::Get(n)->Protected(Standard_True);

  n = "pinf";
  Draw::Set(n,RealLast());
  Draw::Get(n)->Protected(Standard_True);

  n = "minf";
  Draw::Set(n,RealFirst());
  Draw::Get(n)->Protected(Standard_True);

  n = "grid";
  Handle(Draw_Grid) theGrid = new Draw_Grid();
  Draw::Set(n, theGrid);
  theGrid->Protected(Standard_True);
  

  const char* g;

  g = "DRAW Numeric functions";

  theCommands.Add("cos" ,"cos(x)" ,__FILE__,trigo,g);
  theCommands.Add("sin" ,"sin(x)" ,__FILE__,trigo,g);
  theCommands.Add("tan" ,"tan(x)" ,__FILE__,trigo,g);
  theCommands.Add("acos" ,"acos(x)" ,__FILE__,trigo,g);
  theCommands.Add("asin" ,"asin(x)" ,__FILE__,trigo,g);
  theCommands.Add("atan2" ,"atan2(x,y)" ,__FILE__,trigo,g);
  theCommands.Add("sqrt","sqrt(x)",__FILE__,trigo,g);

  g = "DRAW Variables management";

  theCommands.Add("protect","protect name ...",__FILE__,protect,g);
  theCommands.Add("unprotect","unprotect name ...",__FILE__,protect,g);

  theCommands.Add("bsave","bsave name filename",__FILE__,save,g);
  theCommands.Add("brestore","brestore filename name",__FILE__,restore,g);

  theCommands.Add("isdraw","isdraw var, return 1 if Draw value",__FILE__,isdraw,g);
  theCommands.Add("isprot","isprot var, return 1 if Draw var is protected",__FILE__,isprot,g);
  
  theCommands.Add("autodisplay","toggle autodisplay [0/1]",__FILE__,autodisplay,g);
  theCommands.Add("display","display [name1 name2 ...], no names display all",__FILE__,display,g);
  theCommands.Add("donly","donly [name1 name2 ...], erase and display",__FILE__,erase,g);
  theCommands.Add("erase","erase [name1 name2 ...], no names erase all",__FILE__,erase,g);
  theCommands.Add("draw","draw view mode [name1 name2 ...], draw on view with mode",__FILE__,draw,g);
  theCommands.Add("clear","clear display",__FILE__,erase,g);
  theCommands.Add("2dclear","clear display (2d objects)",__FILE__,erase,g);
  theCommands.Add("repaint","repaint, force redraw",__FILE__,repaintall,g);

  theCommands.Add("dtyp", "dtyp name1 name2",__FILE__,whatis,g);
  theCommands.Add("dval", "dval name, return value",__FILE__,value,g);
  theCommands.Add("dname", "dname name, print name",__FILE__,dname,g);
  theCommands.Add("dump", "dump name1 name2 ...",__FILE__,dump,g);
  theCommands.Add("copy",  "copy name1 toname1 name2 toname2 ...",__FILE__,copy,g);
  // san - 02/08/2002 - `rename` command changed to `renamevar` since it conflicts with 
  // the built-in Tcl command `rename`
  //theCommands.Add("rename","rename name1 toname1 name2 toname2 ...",__FILE__,copy,g);
  theCommands.Add("renamevar","renamevar name1 toname1 name2 toname2 ...",__FILE__,copy,g);
  theCommands.Add("dset","var1 value1 vr2 value2 ...",__FILE__,set,g);

  // commands to access C environment variables; see Mantis issue #23197
  theCommands.Add("dgetenv","var : get value of environment variable in C subsystem",__FILE__,dgetenv,g);
  theCommands.Add("dsetenv","var [value] : set (unset if value is empty) environment variable in C subsystem",__FILE__,dsetenv,g);

  theCommands.Add("pick","pick id X Y Z b [nowait]",__FILE__,pick,g);
  theCommands.Add("lastrep","lastrep id X Y [Z] b, return name",__FILE__,lastrep,g);

}
