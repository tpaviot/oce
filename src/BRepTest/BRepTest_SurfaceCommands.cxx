// Created on: 1993-07-22
// Created by: Remi LEQUETTE
// Copyright (c) 1993-1999 Matra Datavision
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
#include <stdio.h>
#include <BRepTest.hxx>
#include <GeometryTest.hxx>

#include <DrawTrSurf.hxx>
#include <DBRep.hxx>
#include <Draw_Interpretor.hxx>
#include <Draw_Appli.hxx>

#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <BRepTools_Quilt.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepBuilderAPI.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepOffsetAPI_FindContigousEdges.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <Geom_Surface.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_SequenceOfShape.hxx>
#include <Precision.hxx>
#include <Draw_ProgressIndicator.hxx>

#ifdef WNT
//#define strcasecmp strcmp Already defined
#include <stdio.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

//-----------------------------------------------------------------------
// suppressarg : suppress a[d],modifie na--
//-----------------------------------------------------------------------
static void suppressarg(Standard_Integer& na,const char** a,const Standard_Integer d) 
{
  for(Standard_Integer i=d;i<na;i++) {
    a[i]=a[i+1];
    a[i+1]=NULL;
  }
  na--;
}


//=======================================================================
// mkface
//=======================================================================

static Standard_Integer mkface(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  if (n < 3) return 1;
  
  Handle(Geom_Surface) S = DrawTrSurf::GetSurface(a[2]);
  if (S.IsNull()) {
    cout << a[2] << " is not a surface" << endl;
    return 1;
  }
  
  Standard_Boolean mkface = a[0][2] == 'f';
  TopoDS_Shape res;

  Standard_Boolean Segment = Standard_False;
  if ( !mkface && (n == 4 || n == 8)) {
    Segment = !strcmp(a[n-1],"1");
    n--;
  }

  if (n == 3) {
    if (mkface)
      res = BRepBuilderAPI_MakeFace(S, Precision::Confusion());
    else
      res = BRepBuilderAPI_MakeShell(S,Segment);
  }
  else if (n <= 5) {
    if (!mkface) return 1;
    Standard_Boolean orient = (n  == 4);
    TopoDS_Shape W = DBRep::Get(a[3],TopAbs_WIRE);
    if (W.IsNull()) return 1;
    res = BRepBuilderAPI_MakeFace(S,TopoDS::Wire(W),orient);
  }
  else {
    if (mkface)
      res = BRepBuilderAPI_MakeFace(S,atof(a[3]),atof(a[4]),atof(a[5]),atof(a[6]),Precision::Confusion());
    else
      res = BRepBuilderAPI_MakeShell(S,atof(a[3]),atof(a[4]),atof(a[5]),atof(a[6]),
			      Segment);
  }
  
  DBRep::Set(a[1],res);
  return 0;
}

//=======================================================================
// quilt
//=======================================================================

static Standard_Integer quilt(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  if (n < 4) return 1;
  BRepTools_Quilt Q;

  Standard_Integer i = 2;
  while (i < n) {
    TopoDS_Shape S = DBRep::Get(a[i]);
    if (!S.IsNull()) {
      if (S.ShapeType() == TopAbs_EDGE) {
	if (i+1 < n) {
	  TopoDS_Shape E = DBRep::Get(a[i+1]);
	  if (!E.IsNull()) {
	    if (E.ShapeType() == TopAbs_EDGE) {
	      i++;
	      Q.Bind(TopoDS::Edge(S),TopoDS::Edge(E));
	    }
	  }
	}
      }
      if (S.ShapeType() == TopAbs_VERTEX) {
	if (i+1 < n) {
	  TopoDS_Shape E = DBRep::Get(a[i+1]);
	  if (!E.IsNull()) {
	    if (E.ShapeType() == TopAbs_VERTEX) {
	      i++;
	      Q.Bind(TopoDS::Vertex(S),TopoDS::Vertex(E));
	    }
	  }
	}
      }
      else {
	Q.Add(S);
      }
    }
    i++;
  }

  DBRep::Set(a[1],Q.Shells());
  return 0;
}


//=======================================================================
// mksurface
//=======================================================================

static Standard_Integer mksurface(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  if (n < 3) return 1;

  TopoDS_Shape S = DBRep::Get(a[2],TopAbs_FACE);
  if (S.IsNull()) return 1;
  TopLoc_Location L;
  Handle(Geom_Surface) C = BRep_Tool::Surface(TopoDS::Face(S),L);


  DrawTrSurf::Set(a[1],C->Transformed(L.Transformation()));
  return 0;
}

//=======================================================================
// mkplane
//=======================================================================

static Standard_Integer mkplane(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  if (n < 3) return 1;

  TopoDS_Shape S = DBRep::Get(a[2],TopAbs_WIRE);
  if (S.IsNull()) return 1;

  Standard_Boolean OnlyPlane = Standard_False;
  if ( n == 4) {
    OnlyPlane =  !strcmp(a[3],"1");
  }

  TopoDS_Face F = (TopoDS_Face) BRepBuilderAPI_MakeFace(TopoDS::Wire(S), OnlyPlane);

  DBRep::Set(a[1],F);
  return 0;
}

//=======================================================================
// pcurve
//=======================================================================
Standard_IMPORT Draw_Color DrawTrSurf_CurveColor(const Draw_Color col);
Standard_IMPORT void DBRep_WriteColorOrientation ();
Standard_IMPORT Draw_Color DBRep_ColorOrientation (const TopAbs_Orientation Or);

static Standard_Integer pcurve(Draw_Interpretor& , Standard_Integer n, const char** a)
{
  Standard_Boolean mute = Standard_False;
  for(Standard_Integer ia=1;ia<n;ia++) {
    if (!strcasecmp(a[ia],"-mute")) {
      suppressarg(n,a,ia);
      mute = Standard_True;
    }
  }

  if (n == 2) {
    // pcurves of a face
    TopoDS_Shape S = DBRep::Get(a[1],TopAbs_FACE);
    if (S.IsNull()) return 1;

    if (!mute) DBRep_WriteColorOrientation();
    Draw_Color col, savecol = DrawTrSurf_CurveColor(Draw_rouge);

    char* name = new char[100];
    Standard_Real f,l;
    S.Orientation(TopAbs_FORWARD);
    TopExp_Explorer ex(S,TopAbs_EDGE);
    for (Standard_Integer i=1; ex.More(); ex.Next(), i++) {
      const Handle(Geom2d_Curve) c = BRep_Tool::CurveOnSurface
	(TopoDS::Edge(ex.Current()),TopoDS::Face(S),f,l);
      if ( c.IsNull() ) {
        cout << "Error: Edge " << i << " does not have pcurve" << endl;
        continue;
      }
      col = DBRep_ColorOrientation(ex.Current().Orientation());
      DrawTrSurf_CurveColor(col);

      sprintf(name,"%s_%d",a[1],i);
      DrawTrSurf::Set(name,new Geom2d_TrimmedCurve(c,f,l));
    }
    DrawTrSurf_CurveColor(savecol);

  }
  else if (n >= 4) {
    TopoDS_Shape SE = DBRep::Get(a[2],TopAbs_EDGE);
    if (SE.IsNull()) return 1;
    TopoDS_Shape SF = DBRep::Get(a[3],TopAbs_FACE);
    if (SF.IsNull()) return 1;

    Draw_Color col, savecol = DrawTrSurf_CurveColor(Draw_rouge);
    Standard_Real f,l;
    const Handle(Geom2d_Curve) c = BRep_Tool::CurveOnSurface
      (TopoDS::Edge(SE),TopoDS::Face(SF),f,l);

    col = DBRep_ColorOrientation(SE.Orientation());
    DrawTrSurf_CurveColor(col);
    DrawTrSurf::Set(a[1],new Geom2d_TrimmedCurve(c,f,l));
    DrawTrSurf_CurveColor(savecol);
  }
  else { 
    return 1;
  }
    
  return 0;
}

//=======================================================================
// sewing
//=======================================================================

static Standard_Integer sewing (Draw_Interpretor& theDi, 
				Standard_Integer theArgc, const char** theArgv)
{
  BRepBuilderAPI_Sewing aSewing;
  Standard_Integer aPar = 1;
  TopTools_SequenceOfShape aSeq;

  Standard_Real aTol = 1.0e-06;
  Standard_Boolean aSewingMode = Standard_True;
  Standard_Boolean anAnalysisMode = Standard_True;
  Standard_Boolean aCuttingMode = Standard_True;
  Standard_Boolean aNonManifoldMode = Standard_False;
  Standard_Boolean aSameParameterMode = Standard_True;
  Standard_Boolean aFloatingEdgesMode = Standard_False;
  Standard_Boolean aFaceMode = Standard_True;
  Standard_Boolean aSetMinTol = Standard_False;
  Standard_Real aMinTol = 0.;
  Standard_Real aMaxTol = Precision::Infinite();

  for (Standard_Integer i = 2; i < theArgc; i++)
  {
    if (theArgv[i][0] == '-' || theArgv[i][0] == '+')
    {
      Standard_Boolean aVal = (theArgv[i][0] == '+' ? Standard_True : Standard_False);
      switch (tolower(theArgv[i][1]))
      {
      case 'm':
        {
          if (tolower(theArgv[i][2]) == 'i' && i+1 < theArgc)
          {
            if (atof (theArgv[i+1]))
            {
              aMinTol = atof (theArgv[++i]);
              aSetMinTol = Standard_True;
            }
            else
            {
              theDi << "Error! min tolerance can't possess the null value" << "\n";
              return (1);
            }
          }
          if (tolower(theArgv[i][2]) == 'a' && i+1 < theArgc)
          {
            if (atof (theArgv[i+1]))
              aMaxTol = atof (theArgv[++i]);
            else
            {
              theDi << "Error! max tolerance can't possess the null value" << "\n";
              return (1);
            }
          }
        }
        break;
      case 's': aSewingMode = aVal; break;
      case 'a': anAnalysisMode = aVal; break;
      case 'c': aCuttingMode = aVal; break;
      case 'n': aNonManifoldMode = aVal; break;
      case 'p': aSameParameterMode = aVal; break;
      case 'e': aFloatingEdgesMode = aVal; break;
      case 'f': aFaceMode = aVal; break;
      }
    }
    else
    {
      TopoDS_Shape aShape = DBRep::Get (theArgv[i]);
      if (!aShape.IsNull())
      {
        aSeq.Append (aShape);
        aPar++;
      }
      else
      {
        if (atof (theArgv[i]))
          aTol = atof (theArgv[i]);
      }
    }
  }
   
  if (aPar < 2)
  {
    theDi << "Use: " << theArgv[0] << " result [tolerance] shape1 shape2 ... [min tolerance] [max tolerance] [switches]" << "\n";
    theDi << "To set user's value of min/max tolerances the following syntax is used: +<parameter> <value>" << "\n";
    theDi << "- parameters are identified by letters:" << "\n";
    theDi << "  mint - min tolerance" << "\n";
    theDi << "  maxt - max tolerance" << "\n";
    theDi << "Switches allow to tune other parameters of Sewing" << "\n";
    theDi << "The following syntax is used: <symbol><parameter>" << "\n";
    theDi << "- symbol may be - to set parameter off, + to set on" << "\n";
    theDi << "- parameters are identified by letters:" << "\n";
    theDi << "  s - mode for creating sewed shape" << "\n";
    theDi << "  a - mode for analysis of input shapes" << "\n";
    theDi << "  c - mode for cutting of free edges" << "\n";
    theDi << "  n - mode for non manifold processing" << "\n";
    theDi << "  p - mode for same parameter processing for edges" << "\n";
    theDi << "  e - mode for sewing floating edges" << "\n";
    theDi << "  f - mode for sewing faces" << "\n";
    return (1);
  }
    
  if (!aSetMinTol)
    aMinTol = aTol*1e-4;
  if (aTol < Precision::Confusion())
    aTol = Precision::Confusion();
  if (aMinTol < Precision::Confusion())
    aMinTol = Precision::Confusion();
  if (aMinTol > aTol)
  {
    theDi << "Error! min tolerance can't exceed working tolerance" << "\n";
    return (1);
  }
  if (aMaxTol < aTol)
  {
    theDi << "Error! max tolerance can't be less than working tolerance" << "\n";
    return (1);
  }

  aSewing.Init (aTol, aSewingMode, anAnalysisMode, aCuttingMode, aNonManifoldMode);
  aSewing.SetSameParameterMode (aSameParameterMode);
  aSewing.SetFloatingEdgesMode (aFloatingEdgesMode);
  aSewing.SetFaceMode (aFaceMode);
  aSewing.SetMinTolerance (aMinTol);
  aSewing.SetMaxTolerance (aMaxTol);

  for (Standard_Integer i = 1; i <= aSeq.Length(); i++)
    aSewing.Add(aSeq.Value(i));
  
  Handle(Draw_ProgressIndicator) aProgress = new Draw_ProgressIndicator (theDi, 1);
  aSewing.Perform (aProgress);
  aSewing.Dump();

  const TopoDS_Shape& aRes = aSewing.SewedShape();
  if (!aRes.IsNull())
    DBRep::Set(theArgv[1], aRes);
  return 0;
}

//=======================================================================
// continuity
//=======================================================================

static Standard_Integer continuity (Draw_Interpretor& , 
				    Standard_Integer n, const char** a)
{
  if (n < 2) return (1);

  BRepOffsetAPI_FindContigousEdges aFind;

  TopoDS_Shape sh = DBRep::Get(a[1]);
  Standard_Integer i=1;
  if (sh.IsNull()) {
    if (n < 3) return (1);
    Standard_Real tol = atof(a[1]);
    aFind.Init(tol, Standard_False);
    i = 2;
  }
  
  while (i < n) {
    sh = DBRep::Get(a[i]);
    aFind.Add(sh);
    i++;
  }

  aFind.Perform();
  aFind.Dump();

  for (i=1; i<=aFind.NbContigousEdges(); i++) {
    const TopTools_ListOfShape& list = aFind.ContigousEdgeCouple(i);
    const TopoDS_Edge& sec1 = TopoDS::Edge(list.First());
    const TopoDS_Edge& sec2 = TopoDS::Edge(list.Last());
    aFind.SectionToBoundary(sec1);
    aFind.SectionToBoundary(sec2);
  }

  return 0;
}

//=======================================================================
// encoderegularity
//=======================================================================
static Standard_Integer encoderegularity (Draw_Interpretor& , 
					  Standard_Integer n, const char** a)

{
  if (n < 2) return 1;
  TopoDS_Shape sh = DBRep::Get(a[1]);
  if (sh.IsNull()) return 1;
  if (n==2) 
    BRepLib::EncodeRegularity(sh);
  else {
    Standard_Real Tol = atof(a[2]);
    Tol *= M_PI/180.;
    BRepLib::EncodeRegularity(sh, Tol);
  }
  return 0;
}


//=======================================================================
//function : SurfaceCommands
//purpose  : 
//=======================================================================

void  BRepTest::SurfaceCommands(Draw_Interpretor& theCommands)
{
  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;

  DBRep::BasicCommands(theCommands);
  GeometryTest::SurfaceCommands(theCommands);

  const char* g = "Surface topology commands";

  theCommands.Add("mkface",
		  "mkface facename surfacename [ufirst ulast vfirst vlast] [wire [norient]]",
		  __FILE__,mkface,g);

  theCommands.Add("mkshell",
		  "mkshell shellname surfacename [ufirst ulast vfirst vlast] [segment 0/1]",
		  __FILE__,mkface,g);

  theCommands.Add("quilt",
		  "quilt compoundname shape1 edgeshape2  edgeshape1... shape2  edgeshape3 edgeshape1or2 ... shape3 ...",
		  __FILE__,quilt,g);
  
  theCommands.Add("mksurface",
		  "mksurface surfacename facename",
		  __FILE__,mksurface,g);

  theCommands.Add("mkplane",
		  "mkplane facename wirename [OnlyPlane 0/1]",
		  __FILE__,mkplane,g);

  theCommands.Add("pcurve",
		  "pcurve [name edgename] facename",
		  __FILE__,pcurve,g);

  theCommands.Add("sewing",
		  "sewing result [tolerance] shape1 shape2 ... [min tolerance] [max tolerance] [switches]",
		  __FILE__,sewing, g);

  theCommands.Add("continuity", 
		  "continuity [tolerance] shape1 shape2 ...",
		  __FILE__,continuity, g);

  theCommands.Add("encoderegularity", 
		  "encoderegularity shape [tolerance (in degree)]",
		  __FILE__,encoderegularity, g);
}

