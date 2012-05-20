// Created by: DAUTRY Philippe
// Copyright (c) 1997-1999 Matra Datavision
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

//      	---------------------

// Version:	0.0
//Version	Date		Purpose
//		0.0	Mar 11 1997	Creation



#include <TDF_CopyTool.ixx>

#include <TDF_ClosureTool.hxx>
#include <TDF_Attribute.hxx>
#include <TDF_AttributeDataMap.hxx>
#include <TDF_AttributeIterator.hxx>
#include <TDF_AttributeMap.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_DataMapIteratorOfAttributeDataMap.hxx>
#include <TDF_DataMapIteratorOfLabelDataMap.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelDataMap.hxx>
#include <TDF_LabelMap.hxx>
#include <TDF_ListIteratorOfLabelList.hxx>
#include <TDF_MapIteratorOfAttributeMap.hxx>
#include <TDF_MapIteratorOfLabelMap.hxx>

#include <Standard_TypeMismatch.hxx>

#define DeclareAndSpeedCast(V,T,Vdown) Handle(T) Vdown = *((Handle(T)*)& V)
#define DeclareConstAndSpeedCast(V,T,Vdown) const Handle(T)& Vdown = (Handle(T)&) V
#define SpeedCast(V,T,Vdown) Vdown = *((Handle(T)*)& V)


//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

void TDF_CopyTool::Copy
(const Handle(TDF_DataSet)& aSourceDataSet,
 const Handle(TDF_RelocationTable)& aRelocationTable) 
{
  TDF_IDFilter privilegeFilter; // Ignore the target attribute's privilege!
  TDF_IDFilter refFilter; // Will not be used.
  TDF_CopyTool::Copy
    (aSourceDataSet, aRelocationTable, privilegeFilter,
     refFilter, Standard_False);
}


//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

void TDF_CopyTool::Copy
(const Handle(TDF_DataSet)& aSourceDataSet,
 const Handle(TDF_RelocationTable)& aRelocationTable,
 const TDF_IDFilter& aPrivilegeFilter) 
{
  TDF_IDFilter refFilter; // Will not be used.
  TDF_CopyTool::Copy
    (aSourceDataSet, aRelocationTable, aPrivilegeFilter,
     refFilter, Standard_False);

}

//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

void TDF_CopyTool::Copy
(const Handle(TDF_DataSet)&             aSourceDataSet,
 const Handle(TDF_RelocationTable)&     aRelocationTable,
 const TDF_IDFilter&                    aPrivilegeFilter,
 const TDF_IDFilter&                    /* aRefFilter */,
 const Standard_Boolean                 /* setSelfContained */) 
{
  if (aSourceDataSet->IsEmpty()) return;

  TDF_LabelMap&        srcLabs = aSourceDataSet->Labels();
  TDF_AttributeMap&    srcAtts = aSourceDataSet->Attributes();
  TDF_LabelList&       rootLst = aSourceDataSet->Roots();

  TDF_LabelDataMap&     theLabMap  = aRelocationTable->LabelTable();
  TDF_AttributeDataMap& theAttMap  = aRelocationTable->AttributeTable();

  // Parallel exploration of the root label structures:
  // * builds the target labels not found;
  // * binds the source attributes with the target ones;
  // * binds the source attributes with new target ones if there is none.

  // Label pre-binding is tested before paste.
  // For it is possible to copy the roots at another place with OTHER TAGS,
  // we first ask <theLabMap> if each source root label is already bound.

  for (TDF_ListIteratorOfLabelList labLItr(rootLst);
       labLItr.More(); labLItr.Next()) {
    const TDF_Label& sLab = labLItr.Value();
    if (theLabMap.IsBound(sLab)) {
      TDF_Label tIns(theLabMap.Find(sLab));
      TDF_CopyTool::CopyLabels(sLab,tIns,
			       theLabMap,theAttMap,srcLabs,srcAtts);
    }
    // if not bound : do nothing!
  }

  // The relocation attribute table is now ready,
  // except for the label unattached attributes,
  // but everybody can update the relocation table...

  // Now: the paste phasis!
  TDF_DataMapIteratorOfAttributeDataMap attItr2(theAttMap);
  for (;attItr2.More(); attItr2.Next()) {
    const Handle(TDF_Attribute)& sAtt = attItr2.Key();
    if (!sAtt.IsNull()) { // This condition looks superfluous; and below also.
      const Handle(TDF_Attribute)& tAtt = attItr2.Value();
      // 1 - No copy on itself.
      // 2 - The target attribute is present BUT its privilege over the
      // source one must be ignored. The source attribute can be copied.
      if ((sAtt != tAtt) && aPrivilegeFilter.IsIgnored(tAtt->ID()))
	sAtt->Paste(tAtt,aRelocationTable);
    }
  }
}



//=======================================================================
//function : CopyLabels
//purpose  : Internal root label copy recursive method.
//=======================================================================

void TDF_CopyTool::CopyLabels
(const TDF_Label& aSLabel,
 TDF_Label& aTargetLabel,
 TDF_LabelDataMap& aLabMap,
 TDF_AttributeDataMap& aAttMap,
 const TDF_LabelMap& aSrcLabelMap,
 const TDF_AttributeMap& aSrcAttributeMap)
{
  TDF_CopyTool::CopyAttributes(aSLabel,aTargetLabel,
			       aAttMap,aSrcAttributeMap);

  // Does the same for the children.
  for (TDF_ChildIterator childItr(aSLabel); childItr.More(); childItr.Next()){
    const TDF_Label& childSLab = childItr.Value();
    if (aSrcLabelMap.Contains(childSLab)) {
      TDF_Label childTIns = aTargetLabel.FindChild(childSLab.Tag());
      aLabMap.Bind(childSLab,childTIns);
      TDF_CopyTool::CopyLabels(childSLab,childTIns,
			       aLabMap,aAttMap,
			       aSrcLabelMap,aSrcAttributeMap);
    }
  }
}


//=======================================================================
//function : CopyAttributes
//purpose  : Internal attribute copy method.
//=======================================================================

void TDF_CopyTool::CopyAttributes
(const TDF_Label& aSLabel,
 TDF_Label& aTargetLabel,
 TDF_AttributeDataMap& aAttMap,
 const TDF_AttributeMap& aSrcAttributeMap)
{
  Handle(TDF_Attribute) tAtt;

  // Finds the target attributes or creates them empty.
  for (TDF_AttributeIterator attItr(aSLabel);
       attItr.More(); attItr.Next()) {
    const Handle(TDF_Attribute) sAtt = attItr.Value();
    if (aSrcAttributeMap.Contains(sAtt)) {
      const Standard_GUID& id = sAtt->ID();
      if (!aTargetLabel.FindAttribute(id,tAtt)) {
	tAtt = sAtt->NewEmpty();
	aTargetLabel.AddAttribute(tAtt);
	aAttMap.Bind(sAtt,tAtt);
      }
      else {
	// Some attributes have the same ID, but are different and
	// exclusive. This obliged to test the dynamic type identity.
	if (tAtt->IsInstance(sAtt->DynamicType()))
	  aAttMap.Bind(sAtt,tAtt);
	else
	  Standard_TypeMismatch::Raise
	    ("TDF_CopyTool: Cannot paste to a different type attribute.");
      }
    }
  }
}
