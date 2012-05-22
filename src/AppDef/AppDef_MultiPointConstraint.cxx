// Created on: 1991-03-16
// Created by: LPA
// Copyright (c) 1991-1999 Matra Datavision
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



#include <AppDef_MultiPointConstraint.ixx>

#include <Standard_OutOfRange.hxx>
#include <Standard_ConstructionError.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <TColgp_HArray1OfVec.hxx>
#include <TColgp_HArray1OfVec2d.hxx>


#define tabTang (*(Handle_TColgp_HArray1OfVec*)&ttabTang)
#define tabCurv (*(Handle_TColgp_HArray1OfVec*)&ttabCurv)
#define tabTang2d (*(Handle_TColgp_HArray1OfVec2d*)&ttabTang2d)
#define tabCurv2d (*(Handle_TColgp_HArray1OfVec2d*)&ttabCurv2d)




AppDef_MultiPointConstraint::AppDef_MultiPointConstraint() {}



AppDef_MultiPointConstraint::
       AppDef_MultiPointConstraint(const Standard_Integer NbPoles,
				   const Standard_Integer NbPoles2d):
                                   AppParCurves_MultiPoint(NbPoles, NbPoles2d)
{
}

AppDef_MultiPointConstraint::
       AppDef_MultiPointConstraint(const TColgp_Array1OfPnt& tabP):
                                  AppParCurves_MultiPoint(tabP)
{
}

AppDef_MultiPointConstraint::
       AppDef_MultiPointConstraint(const TColgp_Array1OfPnt2d& tabP2d):
                                  AppParCurves_MultiPoint(tabP2d)
{
}




AppDef_MultiPointConstraint::
       AppDef_MultiPointConstraint(const TColgp_Array1OfPnt& tabP,
				   const TColgp_Array1OfPnt2d& tabP2d):
                                   AppParCurves_MultiPoint(tabP, tabP2d)
{
}


AppDef_MultiPointConstraint::AppDef_MultiPointConstraint 
                             (const TColgp_Array1OfPnt& tabP, 
			      const TColgp_Array1OfPnt2d& tabP2d, 
			      const TColgp_Array1OfVec& tabVec, 
			      const TColgp_Array1OfVec2d& tabVec2d,
			      const TColgp_Array1OfVec& tabCur,
			      const TColgp_Array1OfVec2d& tabCur2d):
                              AppParCurves_MultiPoint(tabP, tabP2d) {

  if ((tabP.Length() != tabVec.Length()) ||
      (tabP2d.Length() != tabVec2d.Length()) ||
      (tabCur.Length() != tabP.Length()) ||
      (tabCur2d.Length() != tabP2d.Length())) {
    Standard_ConstructionError::Raise();
  }
  Handle(TColgp_HArray1OfVec) T3d = 
    new TColgp_HArray1OfVec(1, tabVec.Length());
  ttabTang = T3d;


  Handle(TColgp_HArray1OfVec2d) T2d = 
    new TColgp_HArray1OfVec2d(1, tabVec2d.Length());
  ttabTang2d = T2d;

  Standard_Integer i, Lower = tabVec.Lower();
  for (i = 1; i <= tabVec.Length(); i++) {
    tabTang->SetValue(i, tabVec.Value(Lower+i-1));
  }
  Lower = tabVec2d.Lower();
  for (i = 1; i <= tabVec2d.Length(); i++) {
    tabTang2d->SetValue(i, tabVec2d.Value(Lower+i-1));
  }

  Handle(TColgp_HArray1OfVec) C3d = 
    new TColgp_HArray1OfVec(1, tabCur.Length());
  ttabCurv = C3d;

  Handle(TColgp_HArray1OfVec2d) C2d = 
    new TColgp_HArray1OfVec2d(1, tabCur2d.Length());
  ttabCurv2d = C2d;

  Lower = tabCur.Lower();
  for (i = 1; i <= tabVec.Length(); i++) {
    tabCurv->SetValue(i, tabCur.Value(Lower+i-1));
  }
  Lower = tabCur2d.Lower();
  for (i = 1; i <= tabCur2d.Length(); i++) {
    tabCurv2d->SetValue(i, tabCur2d.Value(Lower+i-1));
  }

}


AppDef_MultiPointConstraint::AppDef_MultiPointConstraint
			     (const TColgp_Array1OfPnt& tabP, 
			      const TColgp_Array1OfPnt2d& tabP2d, 
			      const TColgp_Array1OfVec& tabVec, 
			      const TColgp_Array1OfVec2d& tabVec2d):
                              AppParCurves_MultiPoint(tabP, tabP2d) {

  if ((tabP.Length() != tabVec.Length()) ||
      (tabP2d.Length() != tabVec2d.Length())) {
    Standard_ConstructionError::Raise();
  }

  
  Handle(TColgp_HArray1OfVec) T3d = 
    new TColgp_HArray1OfVec(1, tabVec.Length());
  ttabTang = T3d;

  Handle(TColgp_HArray1OfVec2d) T2d = 
    new TColgp_HArray1OfVec2d(1, tabVec2d.Length());
  ttabTang2d = T2d;

  Standard_Integer i, Lower = tabVec.Lower();
  for (i = 1; i <= tabVec.Length(); i++) {
    tabTang->SetValue(i, tabVec.Value(Lower+i-1));
  }
  Lower = tabVec2d.Lower();
  for (i = 1; i <= tabVec2d.Length(); i++) {
    tabTang2d->SetValue(i, tabVec2d.Value(Lower+i-1));
  }
}



AppDef_MultiPointConstraint::AppDef_MultiPointConstraint (
                             const TColgp_Array1OfPnt& tabP, 
			     const TColgp_Array1OfVec& tabVec):
                                      AppParCurves_MultiPoint(tabP) {
  
  if (tabP.Length() != tabVec.Length()) {
    Standard_ConstructionError::Raise();
  }
  Handle(TColgp_HArray1OfVec) T3d = 
    new TColgp_HArray1OfVec(1, tabVec.Length());
  ttabTang = T3d;

  Standard_Integer i, Lower = tabVec.Lower();
  for (i = 1; i <= tabVec.Length(); i++) {
    tabTang->SetValue(i, tabVec.Value(Lower+i-1));
  }
}


AppDef_MultiPointConstraint::AppDef_MultiPointConstraint 
                             (const TColgp_Array1OfPnt& tabP, 
			      const TColgp_Array1OfVec& tabVec,
			      const TColgp_Array1OfVec& tabCur):
                                      AppParCurves_MultiPoint(tabP) {

  if ((tabP.Length() != tabVec.Length()) ||
      (tabP.Length() != tabCur.Length())) {
    Standard_ConstructionError::Raise();
  }
  Handle(TColgp_HArray1OfVec) T3d = 
    new TColgp_HArray1OfVec(1, tabVec.Length());
  ttabTang = T3d;

  Standard_Integer i, Lower = tabVec.Lower();
  for (i = 1; i <= tabVec.Length(); i++) {
    tabTang->SetValue(i, tabVec.Value(Lower+i-1));
  }

  Handle(TColgp_HArray1OfVec) C3d = 
    new TColgp_HArray1OfVec(1, tabCur.Length());
  ttabCurv = C3d;

  Lower = tabCur.Lower();
  for (i = 1; i <= tabCur.Length(); i++) {
    tabCurv->SetValue(i, tabCur.Value(Lower+i-1));
  }
}



AppDef_MultiPointConstraint::AppDef_MultiPointConstraint 
                             (const TColgp_Array1OfPnt2d& tabP2d, 
			      const TColgp_Array1OfVec2d& tabVec2d):

                                      AppParCurves_MultiPoint(tabP2d) {

  if (tabP2d.Length() != tabVec2d.Length()) {
    Standard_ConstructionError::Raise();
  }

  Handle(TColgp_HArray1OfVec2d) T2d = 
    new TColgp_HArray1OfVec2d(1, tabVec2d.Length());
  ttabTang2d = T2d;

  Standard_Integer i, Lower = tabVec2d.Lower();
  for (i = 1; i <= tabVec2d.Length(); i++) {
    tabTang2d->SetValue(i, tabVec2d.Value(Lower+i-1));
  }

}



AppDef_MultiPointConstraint::AppDef_MultiPointConstraint 
                             (const TColgp_Array1OfPnt2d& tabP2d, 
			      const TColgp_Array1OfVec2d& tabVec2d,
			      const TColgp_Array1OfVec2d& tabCur2d):
                                      AppParCurves_MultiPoint(tabP2d) {

  if ((tabP2d.Length() != tabVec2d.Length()) ||
      (tabCur2d.Length() != tabP2d.Length()))  {
    Standard_ConstructionError::Raise();
  }
  Handle(TColgp_HArray1OfVec2d) T2d = 
    new TColgp_HArray1OfVec2d(1, tabVec2d.Length());
  ttabTang2d = T2d;

  Standard_Integer i, Lower = tabVec2d.Lower();
  for (i = 1; i <= tabVec2d.Length(); i++) {
    tabTang2d->SetValue(i, tabVec2d.Value(Lower+i-1));
  }

  Handle(TColgp_HArray1OfVec2d) C2d = 
    new TColgp_HArray1OfVec2d(1, tabCur2d.Length());
  ttabCurv2d = C2d;

  Lower = tabCur2d.Lower();
  for (i = 1; i <= tabCur2d.Length(); i++) {
    tabCurv2d->SetValue(i, tabCur2d.Value(Lower+i-1));
  }
}


  
void AppDef_MultiPointConstraint::SetTang (const Standard_Integer Index, 
					   const gp_Vec& Tang) {
  if (tabTang.IsNull())
    tabTang = new TColgp_HArray1OfVec (1, nbP);
  if ((Index <= 0) || (Index > nbP)) {
    Standard_OutOfRange::Raise();
  }
  tabTang->SetValue(Index, Tang);
}
  

gp_Vec AppDef_MultiPointConstraint::Tang (const Standard_Integer Index) const {
  if ((Index <= 0) || (Index > nbP)) {
    Standard_OutOfRange::Raise();
  }
  return tabTang->Value(Index);
}
  


void AppDef_MultiPointConstraint::SetTang2d (const Standard_Integer Index, 
				   const gp_Vec2d& Tang2d){
  if (tabTang2d.IsNull()) 
    tabTang2d = new TColgp_HArray1OfVec2d (1, nbP2d);
    
  if ((Index <= nbP) || 
      (Index > nbP+nbP2d)) {
    Standard_OutOfRange::Raise();
  }
  tabTang2d->SetValue(Index-nbP, Tang2d);
}


gp_Vec2d AppDef_MultiPointConstraint::Tang2d (const Standard_Integer Index) const {
  if ((Index <= nbP) || 
      (Index > nbP+nbP2d)) {
    Standard_OutOfRange::Raise();
  }
  return tabTang2d->Value(Index-nbP);
}


void AppDef_MultiPointConstraint::SetCurv (const Standard_Integer Index, const gp_Vec& Curv) {
  if (tabCurv.IsNull())
    tabCurv = new TColgp_HArray1OfVec (1, nbP);
  if ((Index <= 0) || (Index > nbP)) {
    Standard_OutOfRange::Raise();
  }
  tabCurv->SetValue(Index, Curv);
}
  

gp_Vec AppDef_MultiPointConstraint::Curv (const Standard_Integer Index) const {
  if ((Index <= 0) || (Index > nbP)) {
    Standard_OutOfRange::Raise();
  }
  return tabCurv->Value(Index);
}
  


void AppDef_MultiPointConstraint::SetCurv2d (const Standard_Integer Index, 
					     const gp_Vec2d& Curv2d){
  if (tabCurv2d.IsNull()) 
    tabCurv2d = new TColgp_HArray1OfVec2d (1, nbP2d);
  if ((Index <= nbP) || 
      (Index > nbP+nbP2d)) {
    Standard_OutOfRange::Raise();
  }
  tabCurv2d->SetValue(Index- nbP, Curv2d);
}



gp_Vec2d AppDef_MultiPointConstraint::Curv2d (const Standard_Integer Index) const {
  if ((Index <= nbP) ||
      (Index > nbP+nbP2d)) {
    Standard_OutOfRange::Raise();
  }
  return tabCurv2d->Value(Index - nbP);
}


Standard_Boolean AppDef_MultiPointConstraint::IsTangencyPoint() const
{
  return !(tabTang.IsNull() && tabTang2d.IsNull());
}

Standard_Boolean AppDef_MultiPointConstraint::IsCurvaturePoint() const
{
  return !(tabCurv.IsNull() && tabCurv2d.IsNull());
}




void AppDef_MultiPointConstraint::Dump(Standard_OStream& o) const
{
  o << "AppDef_MultiPointConstraint dump:" << endl;
}
