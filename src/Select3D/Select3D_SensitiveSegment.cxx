// Created on: 1995-01-25
// Created by: Mister rmi
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



#include <Select3D_SensitiveSegment.ixx>
#include <SelectBasics_BasicTool.hxx>
#include <gp_Vec.hxx>
#include <gp_Vec2d.hxx>
#include <Bnd_Box2d.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Lin2d.hxx>
#include <ElCLib.hxx>
#include <Extrema_ExtElC.hxx>
#include <Extrema_POnCurv.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <Precision.hxx>
#include <SelectBasics_ListIteratorOfListOfBox2d.hxx>

#include <CSLib_Class2d.hxx>

//=====================================================
// Function : Create
// Purpose  :Constructor
//=====================================================

Select3D_SensitiveSegment::
Select3D_SensitiveSegment(const Handle(SelectBasics_EntityOwner)& OwnerId, 
                          const gp_Pnt& FirstP,
                          const gp_Pnt& LastP,
                          const Standard_Integer MaxRect):
Select3D_SensitiveEntity(OwnerId),
mymaxrect(MaxRect)
{
  mystart = FirstP;
  myend = LastP;
}

//=====================================================
// Function :
// Purpose  :
//=====================================================

void Select3D_SensitiveSegment
::Project(const Handle(Select3D_Projector)& aProj)
{
  Select3D_SensitiveEntity::Project(aProj); // to set the field last proj...
  gp_Pnt2d aPoint2dStart;
  gp_Pnt2d aPoint2dEnd;
  
  if(HasLocation()) 
  {
    gp_Pnt aStart(mystart.x, mystart.y, mystart.z);
    gp_Pnt aEnd(myend.x, myend.y, myend.z);
    aProj->Project(aStart.Transformed(Location().Transformation()),aPoint2dStart);
    aProj->Project(aEnd.Transformed(Location().Transformation()),aPoint2dEnd);
  }
  else 
  {
    aProj->Project(mystart,aPoint2dStart);
    aProj->Project(myend,aPoint2dEnd);
  }
  myprojstart = aPoint2dStart;
  myprojend = aPoint2dEnd;
}

//=====================================================
// Function : Areas 
// Purpose  :
//=====================================================

void Select3D_SensitiveSegment
::Areas(SelectBasics_ListOfBox2d& theareas)
{
//  gp_Dir2d dy (0.,1.);
  gp_Pnt2d aPStart(myprojstart.x,myprojstart.y);
  if(aPStart.Distance(myprojend)<=Precision::Confusion()) 
  {
      Bnd_Box2d curbox;
      curbox.Set(myprojstart);
      theareas.Append(curbox);
  }
  else 
  {
    gp_Vec2d MyVec(myprojstart,myprojend);//,VAxx(gp_Dir2d(0.,1.));
    Standard_Real theangle = Abs(gp_Dir2d(0.,1.).Angle(gp_Vec2d(myprojstart,myprojend)));
    if(theangle>=M_PI/2.) theangle-=M_PI/2;
    if(theangle>=M_PI/12. && theangle <=5*M_PI/12.)
      { 
        TColgp_Array1OfPnt2d BoxPoint (1,mymaxrect+1); 
        BoxPoint (1) = myprojstart;
        BoxPoint(mymaxrect+1)=myprojend; 
        gp_Vec2d Vtr = MyVec/mymaxrect;
        Standard_Integer i; 
        for ( i=2;i<=mymaxrect;i++) 
        { 
          BoxPoint (i) = BoxPoint (i-1).Translated(Vtr); 
        } 
        for (i=2;i<=mymaxrect+1;i++) 
        { 
          Bnd_Box2d curbox;
          curbox.Set(BoxPoint(i-1));
          curbox.Add(BoxPoint(i));
          theareas.Append(curbox);
        }
      }
    else
      { 
        Bnd_Box2d curbox; 
        curbox.Set(myprojstart); 
        curbox.Add(myprojend); 
        theareas.Append(curbox);
      }
  }
}

//=====================================================
// Function : Matches
// Purpose  :
//=====================================================

Standard_Boolean Select3D_SensitiveSegment
::Matches(const Standard_Real X,
          const Standard_Real Y,
          const Standard_Real aTol,
          Standard_Real&  DMin)
{
  gp_Pnt2d aPStart(myprojstart.x,myprojstart.y);
  gp_Pnt2d aPEnd(myprojend.x,myprojend.y);
  if ( ! SelectBasics_BasicTool::MatchSegment (aPStart, aPEnd, X, Y, aTol, DMin) )
    return Standard_False;
  return Select3D_SensitiveEntity::Matches (X, Y, aTol, DMin); // compute and validate depth
}

//=====================================================
// Function : Matches
// Purpose  :
//=====================================================

Standard_Boolean Select3D_SensitiveSegment::
Matches (const Standard_Real XMin,
         const Standard_Real YMin,
         const Standard_Real XMax,
         const Standard_Real YMax,
         const Standard_Real aTol)
{
  Bnd_Box2d BoundBox;
  BoundBox.Update(XMin-aTol,YMin-aTol,XMax+aTol,YMax+aTol);
  if(BoundBox.IsOut(myprojstart)) return Standard_False;
  if( BoundBox.IsOut(myprojend)) return Standard_False;
  return Standard_True;
}

//=======================================================================
//function : Matches
//purpose  : 
//=======================================================================

Standard_Boolean Select3D_SensitiveSegment::
Matches (const TColgp_Array1OfPnt2d& aPoly,
         const Bnd_Box2d& aBox,
         const Standard_Real aTol)
{ 
  Standard_Real Umin,Vmin,Umax,Vmax;
  aBox.Get(Umin,Vmin,Umax,Vmax);
  CSLib_Class2d aClassifier2d(aPoly,aTol,aTol,Umin,Vmin,Umax,Vmax);

  Standard_Integer RES = aClassifier2d.SiDans(myprojstart);
  if (RES!=1) return Standard_False;

  RES = aClassifier2d.SiDans(myprojend);
  if (RES!=1) return Standard_False;

  return Standard_True;
}


//=======================================================================
//function : GetConnected
//purpose  : 
//=======================================================================

Handle(Select3D_SensitiveEntity) Select3D_SensitiveSegment::
GetConnected(const TopLoc_Location& aLoc)  
{
  Handle(Select3D_SensitiveSegment) NiouEnt = 
    new Select3D_SensitiveSegment(myOwnerId,mystart,myend,mymaxrect);

  if(HasLocation()) NiouEnt->SetLocation(Location());
  NiouEnt->UpdateLocation(aLoc);
  return NiouEnt;
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

void Select3D_SensitiveSegment::Dump(Standard_OStream& S,const Standard_Boolean FullDump) const
{
  S<<"\tSensitivePoint 3D :"<<endl;
  if(HasLocation())
    S<<"\t\tExisting Location"<<endl;
  S<<"\t\t P1 [ "<<mystart.x<<" , "<<mystart.y <<" , "<<mystart.z <<" ]"<<endl;
  S<<"\t\t P2 [ "<<myend.x<<" , "<<myend.y <<" , "<<myend.z <<" ]"<<endl;
  S<<"\t\t maxrect ="<<mymaxrect<<endl;
  
}
//=======================================================================
//function : ComputeDepth
//purpose  : 
//=======================================================================

Standard_Real Select3D_SensitiveSegment::ComputeDepth(const gp_Lin& EyeLine) const
{
#ifdef __BORLANDC__
  gp_Pnt aP0 = mystart.operator gp_Pnt();
  gp_Pnt aP1 = myend.operator gp_Pnt();
#else
  gp_Pnt aP0 = mystart;
  gp_Pnt aP1 = myend;
#endif

  // if segment is degenerated (zero length), just use depth of the end
  gp_XYZ aV = aP1.XYZ() - aP0.XYZ();
  Standard_Real aNorm = aV.Modulus();
  if ( aNorm <= gp::Resolution() )
    return ElCLib::Parameter (EyeLine, aP0);

  // else compute point on segment closest to the line
  gp_Lin aLine (aP0, aV);
  Extrema_ExtElC aTool (aLine, EyeLine, Precision::Angular());
  if ( aTool.IsDone() && ! aTool.IsParallel() )
  {
    for (Standard_Integer i=1; i <= aTool.NbExt(); i++)
    {
      Extrema_POnCurv POL1, POL2;
      aTool.Points (i, POL1, POL2);
      // use point found by extrema only if it is inside segment
      if ( POL1.Parameter() > 0. && POL1.Parameter() < aNorm )
        return ElCLib::Parameter (EyeLine, POL1.Value());
    }
  }

  // if extrema failed or lines are parallel, return closest of the segment ends
  return Min (ElCLib::Parameter (EyeLine, aP0),
              ElCLib::Parameter (EyeLine, aP1));
}
