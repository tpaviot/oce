#include <IFSelect_ListEditor.ixx>

IFSelect_ListEditor::IFSelect_ListEditor  ()
: themax (0) , thetouc (0)  {  }

     IFSelect_ListEditor::IFSelect_ListEditor
  (const Handle(Interface_TypedValue)& def, const Standard_Integer max)
: themax (max) , thedef (def) , thetouc (0)    {  }


void  IFSelect_ListEditor::LoadModel (const Handle(Interface_InterfaceModel)& model)
{  themodl = model;  }

void  IFSelect_ListEditor::LoadValues (const Handle(TColStd_HSequenceOfHAsciiString)& vals)
{
  theorig = vals;
  ClearEdit();
}


void  IFSelect_ListEditor::SetTouched ()
{  thetouc = 1;  }

void  IFSelect_ListEditor::ClearEdit ()
{
  theedit = new TColStd_HSequenceOfHAsciiString();
  thestat = new TColStd_HSequenceOfInteger();
  if (theorig.IsNull()) return;
  Standard_Integer i,nb = theorig->Length();
  for (i = 1; i <= nb; i ++) {
    theedit->Append (theorig->Value(i));
    thestat->Append (0);
  }
  thetouc = 0;
}

//  ########    CHECK    ########

static Standard_Boolean  CheckValue
  (const Handle(TCollection_HAsciiString)& val,
   const Handle(Interface_InterfaceModel)& modl,
   const Handle(Interface_TypedValue)& thedef)
{
  if (val.IsNull() || modl.IsNull() || thedef.IsNull()) return Standard_True;

  Interface_ParamType pty = thedef->Type();
  if (!thedef->Satisfies(val)) return Standard_False;
  if (pty == Interface_ParamIdent && !val.IsNull()) {
    if (modl->NextNumberForLabel(val->ToCString(),0) <= 0)
      return Standard_False;
  }
  return Standard_True;
}

//  ########    EDITION    ########

Standard_Boolean  IFSelect_ListEditor::LoadEdited
  (const Handle(TColStd_HSequenceOfHAsciiString)& list)
{
  if (list.IsNull()) return Standard_False;
  Standard_Integer i, nb = list->Length();
  if (nb > themax) return Standard_False;

//   check values
  if (!thedef.IsNull()) {
    for (i = 1; i <= nb; i ++) {
      Handle(TCollection_HAsciiString) newval = list->Value(i);
      if (!CheckValue (newval,themodl,thedef)) return Standard_False;
    }
  }

//  OK
  theedit = list;
  thestat = new TColStd_HSequenceOfInteger();
  for (i = 1; i <= nb; i ++) thestat->Append (1);
  thetouc = 1;

  return Standard_True;
}


Standard_Boolean  IFSelect_ListEditor::SetValue
  (const Standard_Integer num, const Handle(TCollection_HAsciiString)& val)
{
  if (theedit.IsNull()) return Standard_False;
  if (num < 1 || num > theedit->Length()) return Standard_False;

//   check value
  if (!CheckValue(val,themodl,thedef)) return Standard_False;

// OK
  theedit->SetValue (num,val);
  thestat->SetValue (num,1);
  thetouc = 1;
  return Standard_True;
}


Standard_Boolean  IFSelect_ListEditor::AddValue
  (const Handle(TCollection_HAsciiString)& val, const Standard_Integer atnum)
{
  if (theedit.IsNull()) return Standard_False;
  if (themax > 0 && theedit->Length() >= themax) return Standard_False;
  if (!CheckValue (val,themodl,thedef)) return Standard_False;
  if (atnum > 0) {
    theedit->InsertBefore (atnum,val);
    thestat->InsertBefore (atnum,2);
  } else {
    theedit->Append (val);
    thestat->Append (2);
  }
  thetouc = 2;
  return Standard_True;
}


Standard_Boolean  IFSelect_ListEditor::Remove
  (const Standard_Integer num, const Standard_Integer howmany)
{
  if (theedit.IsNull()) return Standard_False;
  Standard_Integer nb = theedit->Length();
  if (num < 0) return Standard_False;
  if (num == 0) return Remove (nb-howmany,howmany);

  if ((num+howmany) > nb) return Standard_False;
  theedit->Remove(num,howmany);
  thestat->Remove(num,howmany);
  thetouc = 3;
  return Standard_True;
}


//  ########    QUERIES    ########

Handle(TColStd_HSequenceOfHAsciiString)  IFSelect_ListEditor::OriginalValues () const
{  return theorig;  }

Handle(TColStd_HSequenceOfHAsciiString)  IFSelect_ListEditor::EditedValues () const
{  return theedit;  }


Standard_Integer  IFSelect_ListEditor::NbValues (const Standard_Boolean edited) const
{
  if (edited) return (theedit.IsNull() ? 0 : theedit->Length());
  return (theorig.IsNull() ? 0 : theorig->Length());
}


Handle(TCollection_HAsciiString)  IFSelect_ListEditor::Value
  (const Standard_Integer num, const Standard_Boolean edited) const
{
  Handle(TCollection_HAsciiString) val;
  if (edited) {
    if (theedit.IsNull()) return val;
    if (num < 1 || num > theedit->Length()) return val;
    val = theedit->Value(num);
  } else {
    if (theorig.IsNull()) return val;
    if (num < 1 || num > theorig->Length()) return val;
    val = theorig->Value(num);
  }
  return val;
}

Standard_Boolean  IFSelect_ListEditor::IsChanged (const Standard_Integer num) const
{
  if (thestat.IsNull()) return Standard_False;
  if (num < 1 || num > thestat->Length()) return Standard_False;
  Standard_Integer stat = thestat->Value(num);
  return (stat != 0);
}

Standard_Boolean  IFSelect_ListEditor::IsModified (const Standard_Integer num) const
{
  if (thestat.IsNull()) return Standard_False;
  if (num < 1 || num > thestat->Length()) return Standard_False;
  Standard_Integer stat = thestat->Value(num);
  return (stat == 1);
}

Standard_Boolean  IFSelect_ListEditor::IsAdded (const Standard_Integer num) const
{
  if (thestat.IsNull()) return Standard_False;
  if (num < 1 || num > thestat->Length()) return Standard_False;
  Standard_Integer stat = thestat->Value(num);
  return (stat == 2);
}

Standard_Boolean  IFSelect_ListEditor::IsTouched () const
      {  return (thetouc != 0);  }
