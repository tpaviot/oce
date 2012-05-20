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

#include <Interface_LineBuffer.ixx>
#include <Standard_OutOfRange.hxx>



//  LineBuffer, c est une String avec une Longueur reservee fixe au depart
//  et une longueur effective <thelen>. theline(thelen+1) vaut '\0'



Interface_LineBuffer::Interface_LineBuffer (const Standard_Integer size)
    : theline (size+1,' ')
{
  theline.SetValue(1,'\0');
  themax = size;  theinit = thelen = theget = thekeep = thefriz = 0;
}

    void  Interface_LineBuffer::SetMax (const Standard_Integer max)
{
  if (max > theline.Length()) Standard_OutOfRange::Raise
    ("Interface LineBuffer : SetMax");
  if (max <= 0) themax = theline.Length();
  else themax = max;
}


    void  Interface_LineBuffer::SetInitial (const Standard_Integer initial)
{
  if (thefriz > 0) return;
  if (initial >= themax) Standard_OutOfRange::Raise
    ("Interface LineBuffer : SetInitial");
  if (initial <= 0) theinit = 0;
  else theinit = initial;
}

    void  Interface_LineBuffer::SetKeep ()
      {  thekeep = -thelen;  }

    Standard_Boolean  Interface_LineBuffer::CanGet (const Standard_Integer more)
{
  theget = more;
  if ((thelen + theinit + more) <= themax) return Standard_True;
  if (thekeep < 0) thekeep = -thekeep;
  return Standard_False;
}

    Standard_CString  Interface_LineBuffer::Content () const 
      {  return theline.ToCString();  }

    Standard_Integer  Interface_LineBuffer::Length () const 
      {  return thelen + theinit;  }  // +theinit : longueur vraie avec blancs

    void  Interface_LineBuffer::FreezeInitial ()
      {  thefriz = theinit+1;  theinit = 0;  }

    void  Interface_LineBuffer::Clear ()
{
  theget = thekeep = thelen = thefriz = 0;
  theline.SetValue(1,'\0');
}

// ....                        RESULTATS                        ....

    void  Interface_LineBuffer::Prepare ()
{
//  ATTENTION aux blanx initiaux
  if (theinit > 0) {
    Standard_Integer i; // svv Jan11 2000 : porting on DEC
    // pdn Protection
    if( (thelen +theinit) > themax)
      return;
    
    for (i = thelen + 1; i > 0; i --) {
      theline.SetValue(i + theinit, theline.Value(i));
    }
    for (i = 1; i <= theinit; i ++)  theline.SetValue(i,' ');
  }
//  GERER KEEP : est-il jouable ? sinon, annuler. sioui, noter la jointure
  if (thekeep > 0) thekeep += (theinit+1);  // theinit, et +1 car Keep INCLUS
  if (thekeep > 0)
    {  if ((thelen + theget + theinit - thekeep) >= themax) thekeep = 0;  }
  if (thekeep > 0)
    { thekept = theline.Value(thekeep); theline.SetValue(thekeep,'\0');  }
}

    void  Interface_LineBuffer::Keep ()
{
//  Si Keep, sauver de thekeep + 1  a  thelen (+1 pour 0 final)
  if (thekeep > 0) {
    theline.SetValue(1,thekept);
    for (Standard_Integer i = thekeep+1; i <= thelen+theinit+1; i ++) {
      theline.SetValue(i-thekeep+1, theline.Value(i));
    }
    thelen = thelen+theinit-thekeep+1;
  }
  else Clear();
  theget = thekeep = 0;
  if (thefriz > 0) {  theinit = thefriz - 1;  thefriz = 0;  }
}


    void  Interface_LineBuffer::Move (TCollection_AsciiString& str)
{
  Prepare();
  str.AssignCat(theline.ToCString());
  Keep();
}

    void  Interface_LineBuffer::Move (const Handle(TCollection_HAsciiString)& str)
{
  Prepare();
  str->AssignCat(theline.ToCString());
  Keep();
}

    Handle(TCollection_HAsciiString)  Interface_LineBuffer::Moved ()
{
  Prepare();
  Handle(TCollection_HAsciiString) R =
    new TCollection_HAsciiString(theline.ToCString());
  Keep();
  return R;
}

// ....                        AJOUTS                        ....

    void  Interface_LineBuffer::Add (const Standard_CString text)
      {  Add (text,strlen(text));  }

    void  Interface_LineBuffer::Add
  (const Standard_CString text, const Standard_Integer lntext)
{
  Standard_Integer lnt =
    (lntext > (themax-thelen-theinit) ? (themax-thelen-theinit) : lntext);
  for (Standard_Integer i = 1; i <= lnt; i ++)
    theline.SetValue (thelen+i, text[i-1]);
  thelen += lnt;
  theline.SetValue (thelen+1, '\0');
}

    void  Interface_LineBuffer::Add (const TCollection_AsciiString& text)
      {  Add ( text.ToCString() , text.Length() );  }

    void  Interface_LineBuffer::Add (const Standard_Character text)
{
  theline.SetValue (thelen+1,text);
  thelen ++;
  theline.SetValue (thelen+1,'\0');
}
