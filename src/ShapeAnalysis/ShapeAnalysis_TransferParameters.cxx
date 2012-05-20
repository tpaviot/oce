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

#include <ShapeAnalysis_TransferParameters.ixx>
#include <Geom_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <ShapeAnalysis_Edge.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <BRep_Tool.hxx>
#include <gp.hxx>
#include <ShapeBuild_Edge.hxx>


//=======================================================================
//function : ShapeAnalysis_TransferParameters
//purpose  : 
//=======================================================================

ShapeAnalysis_TransferParameters::ShapeAnalysis_TransferParameters()
{
  myScale = 1.;
  myShift = 0.;
}


//=======================================================================
//function : ShapeAnalysis_TransferParameters
//purpose  : 
//=======================================================================

ShapeAnalysis_TransferParameters::ShapeAnalysis_TransferParameters(const TopoDS_Edge& E,
                                                                   const TopoDS_Face& F)
{
  Init(E,F);
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void ShapeAnalysis_TransferParameters::Init(const TopoDS_Edge& E, const TopoDS_Face& F) 
{
  myScale = 1.;
  myShift = 0.;
  Standard_Real l,f,l2d = 0.0,f2d = 0.0;
  TopLoc_Location L;
  myEdge = E;
  ShapeAnalysis_Edge sae;
  Handle(Geom_Curve) curve3d;// = BRep_Tool::Curve (E,f,l);
  sae.Curve3d ( E, curve3d, f, l ,Standard_False);
  myFirst = f;
  myLast = l;
  Handle(Geom2d_Curve) curve2d;// = BRep_Tool::CurveOnSurface (E, F, f2d,l2d);
  // ShapeAnalysis_Edge sae;
  if (! F.IsNull() ) { // process free edges
    sae.PCurve ( E, F, curve2d, f2d, l2d,Standard_False );
  }
  myFirst2d = f2d;
  myLast2d = l2d;
  myFace = F;
  if ( curve3d.IsNull() || curve2d.IsNull() ) return;

  Standard_Real ln2d  = l2d - f2d;
  Standard_Real ln3d  = l - f;
  myScale = ( ln3d <= gp::Resolution() ? 1. : ln2d / ln3d );
  myShift =  f2d - f * myScale;
}

//=======================================================================
//function : SetMaxTolerance
//purpose  : 
//=======================================================================

void ShapeAnalysis_TransferParameters::SetMaxTolerance( const Standard_Real maxtol )
{
  myMaxTolerance = maxtol;
}


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================


Handle(TColStd_HSequenceOfReal) ShapeAnalysis_TransferParameters::Perform
        (const Handle(TColStd_HSequenceOfReal)& Params,
         const Standard_Boolean To2d)
{
  Handle(TColStd_HSequenceOfReal) res = new TColStd_HSequenceOfReal;
  for (Standard_Integer i = 1 ; i <= Params->Length(); i++) 
    res->Append(Perform(Params->Value(i),To2d));
 return res; 
  
}


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

Standard_Real ShapeAnalysis_TransferParameters::Perform(const Standard_Real Param,
                                                        const Standard_Boolean To2d) 
{
  Standard_Real NewParam;
  if(To2d) 
    NewParam = myShift + Param*myScale;
  else
    NewParam =  -myShift/myScale + Param*1./myScale;
  return NewParam;
}


//=======================================================================
//function : TransferRange
//purpose  : 
//=======================================================================

void ShapeAnalysis_TransferParameters::TransferRange(TopoDS_Edge& newEdge,
                                                     const Standard_Real prevPar,
                                                     const Standard_Real currPar,
                                                     const Standard_Boolean Is2d) 
{
  ShapeBuild_Edge sbe;
  if(Is2d) {
    Standard_Real span2d = myLast2d - myFirst2d;  
    Standard_Real tmp1,tmp2;
    if(prevPar > currPar) {
      tmp1 = currPar;
      tmp2 = prevPar;
    }
    else {
      tmp1 = prevPar;
      tmp2 = currPar;
    }
    Standard_Real alpha = (tmp1-myFirst2d) / span2d;
    Standard_Real beta  = (tmp2 - myFirst2d) / span2d;
      sbe.CopyRanges(newEdge,myEdge, alpha, beta);
  }
  else {
    Standard_Real alpha = (prevPar-myFirst)/(myLast - myFirst);
    Standard_Real beta  = (currPar - myFirst)/(myLast - myFirst);
    sbe.CopyRanges(newEdge,myEdge, alpha, beta);
 }
}


//=======================================================================
//function : IsSameRange
//purpose  : 
//=======================================================================

Standard_Boolean ShapeAnalysis_TransferParameters::IsSameRange() const
{
  return myShift == 0. && myScale == 1.;
}
