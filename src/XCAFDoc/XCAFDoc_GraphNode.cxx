// Created on: 2000-09-27
// Created by: Pavel TELKOV
// Copyright (c) 2000-2012 OPEN CASCADE SAS
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



#include <XCAFDoc_GraphNode.ixx>

//     class  methods working on the node:
//     ===================================

//=======================================================================
//function : Find
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_GraphNode::Find(const TDF_Label& L,
					 Handle(XCAFDoc_GraphNode)& G)
{
  return L.FindAttribute(XCAFDoc_GraphNode::GetDefaultGraphID(), G);
}

//=======================================================================
//GraphNode : GetDefaultGraphID
//purpose  : Static method to get the default ID of a GraphNode
//=======================================================================

const Standard_GUID&  XCAFDoc_GraphNode::GetDefaultGraphID() 
{
  static Standard_GUID XCAFDoc_GraphNodeID ("efd212f5-6dfd-11d4-b9c8-0060b0ee281b");
  return XCAFDoc_GraphNodeID; 
}

//=======================================================================
//GraphNode : Set
//purpose  : Finds or creates a GraphNode attribute with default ID
//=======================================================================

Handle(XCAFDoc_GraphNode) XCAFDoc_GraphNode::Set(const TDF_Label& L)
{
  Handle(XCAFDoc_GraphNode) GN;
  if (!L.FindAttribute(XCAFDoc_GraphNode::GetDefaultGraphID(), GN)) {
    GN = new XCAFDoc_GraphNode();
    GN->SetGraphID(XCAFDoc_GraphNode::GetDefaultGraphID());
    L.AddAttribute(GN);
  }
  return GN;
}

//=======================================================================
//function : Set
//purpose  : Finds or creates a GraphNode  attribute with explicit ID
//         : a driver for it
//=======================================================================

Handle(XCAFDoc_GraphNode) XCAFDoc_GraphNode::Set (const TDF_Label& L, 
						  const Standard_GUID& explicitID)
{
  Handle(XCAFDoc_GraphNode) GN;
  if (!L.FindAttribute(explicitID, GN)) {
    GN = new XCAFDoc_GraphNode ();    
    GN->SetGraphID( explicitID );
    L.AddAttribute( GN );
  }
  return GN;
}

//     Instance methods: 
//     ================ 

//=======================================================================
//function : XCAFDoc_GraphNode
//purpose  : 
//=======================================================================

XCAFDoc_GraphNode::XCAFDoc_GraphNode () 
{ 
}  


//=======================================================================
//function : SetGraphID
//purpose  : 
//=======================================================================

void XCAFDoc_GraphNode::SetGraphID (const Standard_GUID& explicitID)
{
  Backup();
  myGraphID = explicitID;
}



//=======================================================================
//function : SetFather
//purpose  : 
//=======================================================================

Standard_Integer XCAFDoc_GraphNode::SetFather(const Handle(XCAFDoc_GraphNode)& F) 
{
  Backup();
  Standard_Integer Findex = myFathers.Length();
  myFathers.Append(F);
  return ++Findex;
}

//=======================================================================
//function : SetChild
//purpose  : 
//=======================================================================

Standard_Integer XCAFDoc_GraphNode::SetChild(const Handle(XCAFDoc_GraphNode)& Ch) 
{
  Backup();
  Standard_Integer Chindex = myChildren.Length();
  myChildren.Append(Ch);
  return ++Chindex;
}

//=======================================================================
//function : UnSetFather
//purpose  : 
//=======================================================================

void XCAFDoc_GraphNode::UnSetFather(const Handle(XCAFDoc_GraphNode)& F) 
{
  Backup();
  Standard_Integer Findex = FatherIndex(F);
  if (Findex != 0)
  F->UnSetChildlink(this);
  UnSetFatherlink(F);
}


//=======================================================================
//function : UnSetFather
//purpose  : 
//=======================================================================

void XCAFDoc_GraphNode::UnSetFather(const Standard_Integer Findex) 
{
  if (Findex != 0)
  UnSetFather( GetFather(Findex) );
}


//=======================================================================
//function : UnSetFatherlink
//purpose  : Remove link finily
//=======================================================================

void XCAFDoc_GraphNode::UnSetFatherlink(const Handle(XCAFDoc_GraphNode)& F) 
{
  myFathers.Remove( FatherIndex(F) );
}

//=======================================================================
//function : UnSetChild
//purpose  : 
//=======================================================================

void XCAFDoc_GraphNode::UnSetChild(const Handle(XCAFDoc_GraphNode)& Ch) 
{
  Backup();
  Standard_Integer Chindex = ChildIndex(Ch);
  if (Chindex != 0) 
  Ch->UnSetFatherlink(this);
  UnSetChildlink(Ch);
}


//=======================================================================
//function : UnSetChild
//purpose  : 
//=======================================================================

 void XCAFDoc_GraphNode::UnSetChild(const Standard_Integer Chindex) 
{
  if (Chindex != 0 )
  UnSetChild( GetChild(Chindex) );
}


//=======================================================================
//function : UnSetChildlink
//purpose  : Remove link finily
//=======================================================================

void XCAFDoc_GraphNode::UnSetChildlink(const Handle(XCAFDoc_GraphNode)& Ch) 
{
  myChildren.Remove( ChildIndex(Ch) );
}

//=======================================================================
//function : GetFather
//purpose  : 
//=======================================================================

 Handle(XCAFDoc_GraphNode) XCAFDoc_GraphNode::GetFather(const Standard_Integer Findex) const
{
  Handle(XCAFDoc_GraphNode) F = myFathers.Value(Findex);
  return F;
}

//=======================================================================
//function : GetChild
//purpose  : 
//=======================================================================

 Handle(XCAFDoc_GraphNode) XCAFDoc_GraphNode::GetChild(const Standard_Integer Chindex) const
{
  Handle(XCAFDoc_GraphNode) Ch = myChildren.Value(Chindex);
  return Ch;
}

//=======================================================================
//function : FatherIndex
//purpose  : 
//=======================================================================

Standard_Integer XCAFDoc_GraphNode::FatherIndex(const Handle(XCAFDoc_GraphNode)& F) const
{
  Standard_Integer Findex = 0;
  if (NbFathers()!=0) {
    for (Findex = 1 ; Findex <= NbFathers(); Findex++) {
      if ( F == myFathers.Value(Findex)) return Findex;
    }
  }
  return 0;
}

//=======================================================================
//function : ChildIndex
//purpose  : 
//=======================================================================

 Standard_Integer XCAFDoc_GraphNode::ChildIndex(const Handle(XCAFDoc_GraphNode)& Ch) const
{
  Standard_Integer Chindex;
  if (NbChildren()!=0) {
    for (Chindex = 1; Chindex <= NbChildren(); Chindex++) {
      if ( Ch == myChildren.Value(Chindex)) return Chindex;
    }
  }
  return 0;
}

//=======================================================================
//function : IsFather
//purpose  : 
//=======================================================================

 Standard_Boolean XCAFDoc_GraphNode::IsFather(const Handle(XCAFDoc_GraphNode)& Ch) const
{
  if ( ChildIndex(Ch) ) return Standard_True;
  return Standard_False;
}

//=======================================================================
//function : IsChild
//purpose  : 
//=======================================================================

 Standard_Boolean XCAFDoc_GraphNode::IsChild(const Handle(XCAFDoc_GraphNode)& F) const
{
  if ( FatherIndex(F) ) return Standard_True;
  return Standard_False;
}

//=======================================================================
//function : NbFathers
//purpose  : 
//=======================================================================

 Standard_Integer XCAFDoc_GraphNode::NbFathers() const
{
  return myFathers.Length();
}

//=======================================================================
//function : NbChildren
//purpose  : 
//=======================================================================

 Standard_Integer XCAFDoc_GraphNode::NbChildren() const
{
  return myChildren.Length();
}



//     Implementation of Attribute methods:  
//     ===================================  

//=======================================================================
//function : ID
//purpose  : 
//=======================================================================

const Standard_GUID& XCAFDoc_GraphNode::ID() const
{
  return myGraphID;
}


//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================

void XCAFDoc_GraphNode::Restore(const Handle(TDF_Attribute)& other) 
{
  Handle(XCAFDoc_GraphNode) F =  Handle(XCAFDoc_GraphNode)::DownCast(other);
  myFathers     = F->myFathers;
  myChildren    = F->myChildren;
  myGraphID     = F->myGraphID;
}


//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void XCAFDoc_GraphNode::Paste(const Handle(TDF_Attribute)& into,
			      const Handle(TDF_RelocationTable)& RT) const
{
  Handle(XCAFDoc_GraphNode) intof = Handle(XCAFDoc_GraphNode)::DownCast(into);
  Handle(XCAFDoc_GraphNode) func;
  Standard_Integer i = 1;
  for (; i <= NbFathers(); i++) {
    if (!RT->HasRelocation(myFathers(i), func) && RT->AfterRelocate()) {
      func.Nullify();
    }
    intof->SetFather(func);
  }

  i = 1;
  for (; i <= NbChildren(); i++) {
    if (!RT->HasRelocation(myChildren(i), func) && RT->AfterRelocate()) {
      func.Nullify();
    }
    intof->SetFather(func);
  }
  intof->SetGraphID(myGraphID);
}


//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) XCAFDoc_GraphNode::NewEmpty() const
{
  Handle(XCAFDoc_GraphNode) G = new XCAFDoc_GraphNode();
  G->SetGraphID(myGraphID);
  return G;
}


//=======================================================================
//function : References
//purpose  : 
//=======================================================================

void XCAFDoc_GraphNode::References(const Handle(TDF_DataSet)& aDataSet) const
{
  Standard_Integer i;
  Handle(XCAFDoc_GraphNode) fct;
  for ( i = 1; i <= NbChildren(); i++ ) {
    fct = myChildren(i);
    if (!fct.IsNull()) {
      aDataSet->AddAttribute(fct);
    }
  }
  for ( i = 1; i <= NbFathers(); i++ ) {
    fct = myFathers(i);
    if ( !fct.IsNull()) {
      aDataSet->AddAttribute(fct);
    }
  }
 
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

Standard_OStream& XCAFDoc_GraphNode::Dump (Standard_OStream& anOS) const
{
  TDF_Attribute::Dump (anOS);
  Standard_Integer i = 1;
  if ( myFathers.Length()!= 0 ) {
    anOS<<"  Fathers=";
    for (; i <= NbFathers(); i++) {
      if ( !myFathers(i)->Label().IsNull() ) 
	myFathers(i)->Label().EntryDump(anOS);
      anOS<<endl;
    }
  }
  i = 1;
  if ( myChildren.Length()!= 0 ) {
    anOS<<"  Children=";
    for (; i <= NbChildren(); i++) {
      if ( !myChildren(i)->Label().IsNull() )
	myChildren(i)->Label().EntryDump(anOS);
      anOS<<endl;
    }
  }
//  anOS<<endl;
  return anOS;
}

//=======================================================================
//function : BeforeForget
//purpose  : 
//=======================================================================

void XCAFDoc_GraphNode::BeforeForget()
{
  while ( myFathers.Length() > 0 ) 
    UnSetFather(1);
  while ( myChildren.Length() > 0 )
    UnSetChild(1);
}
