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

#include <MoniTool_Stat.ixx>
#include <TCollection_AsciiString.hxx>

//static MoniTool_Stat Statvoid("");
//static MoniTool_Stat Statact ("");

//not Used
//static Standard_CString voidname = "";


MoniTool_Stat::MoniTool_Stat (const Standard_CString title)
{
  thetit  = new TCollection_HAsciiString(title);
  thelev  = 0;
  thetot  = new TColStd_HArray1OfInteger (1,20);  thetot->Init(0);
  thedone = new TColStd_HArray1OfInteger (1,20);  thetot->Init(0);
  thecurr = new TColStd_HArray1OfInteger (1,20);  thetot->Init(0);
}

    MoniTool_Stat::MoniTool_Stat (const MoniTool_Stat& )
{  }

    MoniTool_Stat&  MoniTool_Stat::Current ()
{
  static MoniTool_Stat thecur;
  return thecur;
}

    Standard_Integer  MoniTool_Stat::Open (const Standard_Integer nb)
{
  thelev ++;
  thetot->SetValue(thelev,nb);
  thedone->SetValue(thelev,0);
  thecurr->SetValue(thelev,0);
  return thelev;
}

void  MoniTool_Stat::OpenMore (const Standard_Integer id, const Standard_Integer nb)
{
  if (id <= 0 || id > thelev) return;
  thetot->SetValue (id, thetot->Value(id)+nb);
}

void  MoniTool_Stat::Add (const Standard_Integer nb)
{
  thedone->SetValue (thelev, thedone->Value(thelev) + nb);
  thecurr->SetValue (thelev, 0);
}

void  MoniTool_Stat::AddSub (const Standard_Integer nb)
{
  thecurr->SetValue (thelev, nb);
}

void  MoniTool_Stat::AddEnd ()
{
  thedone->SetValue (thelev, thedone->Value(thelev) + thecurr->Value(thelev));
  thecurr->SetValue (thelev, 0);
}

void MoniTool_Stat::Close (const Standard_Integer id)
{
  if (id < thelev) Close (id+1);
  AddEnd();
  thelev --;
}

Standard_Integer  MoniTool_Stat::Level () const
{  return thelev;  }

Standard_Real  MoniTool_Stat::Percent (const Standard_Integer fromlev) const
{
  if (fromlev > thelev) return 0;
  Standard_Real r1,r2,r3;
  Standard_Integer tot  = thetot->Value(fromlev);
  Standard_Integer done = thedone->Value(fromlev);
  if (done >= tot) return 100.;
  if (fromlev == thelev) {
    r1 = tot;  r2 = done;
    return (r2*100)/r1;
  }
  Standard_Integer cur = thecurr->Value(fromlev);
  r1 = tot;  r2 = done;
  r3 = 0;
  if (cur > 0) { r3 = cur; r3 = cur/tot; r3 = r3*Percent (fromlev+1); }
  if (r1 == 0) return 1;
  return (r2*100)/r1 + r3;
}
