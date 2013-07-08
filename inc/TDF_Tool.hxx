// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TDF_Tool_HeaderFile
#define _TDF_Tool_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_TDF_Data_HeaderFile
#include <Handle_TDF_Data.hxx>
#endif
#ifndef _Standard_CString_HeaderFile
#include <Standard_CString.hxx>
#endif
#ifndef _Standard_OStream_HeaderFile
#include <Standard_OStream.hxx>
#endif
class TDF_Label;
class TDF_IDFilter;
class TDF_AttributeMap;
class TCollection_AsciiString;
class TColStd_ListOfInteger;
class TDF_Data;
class TDF_LabelList;
class TDF_LabelIntegerMap;


//! This class provides general services for a data framework. <br>
class TDF_Tool  {
public:

  DEFINE_STANDARD_ALLOC

  //! Returns the number of labels of the tree, <br>
//! including <aLabel>. aLabel is also included in this figure. <br>
//! This information is useful in setting the size of an array. <br>
  Standard_EXPORT   static  Standard_Integer NbLabels(const TDF_Label& aLabel) ;
  //! Returns the total number of attributes attached <br>
//! to the labels dependent on the label aLabel. <br>
//! The attributes of aLabel are also included in this figure. <br>
//! This information is useful in setting the size of an array. <br>
  Standard_EXPORT   static  Standard_Integer NbAttributes(const TDF_Label& aLabel) ;
  //! Returns the number of attributes of the tree, <br>
//!          selected by a<Filter>, including those of <br>
//!          <aLabel>. <br>
  Standard_EXPORT   static  Standard_Integer NbAttributes(const TDF_Label& aLabel,const TDF_IDFilter& aFilter) ;
  //! Returns true if <aLabel> and its descendants <br>
//!          reference only attributes or labels attached to <br>
//!          themselves. <br>
  Standard_EXPORT   static  Standard_Boolean IsSelfContained(const TDF_Label& aLabel) ;
  //! Returns true if <aLabel> and its descendants <br>
//!          reference only attributes or labels attached to <br>
//!          themselves and kept by <aFilter>. <br>
  Standard_EXPORT   static  Standard_Boolean IsSelfContained(const TDF_Label& aLabel,const TDF_IDFilter& aFilter) ;
  //! Returns in <theAtts> the attributes having out <br>
//!          references. <br>
//! <br>
//!          Caution: <theAtts> is not cleared before use! <br>
  Standard_EXPORT   static  void OutReferers(const TDF_Label& theLabel,TDF_AttributeMap& theAtts) ;
  //! Returns in <atts> the attributes having out <br>
//!          references and kept by <aFilterForReferers>. <br>
//!          It considers only the references kept by <aFilterForReferences>. <br>
//!          Caution: <atts> is not cleared before use! <br>
  Standard_EXPORT   static  void OutReferers(const TDF_Label& aLabel,const TDF_IDFilter& aFilterForReferers,const TDF_IDFilter& aFilterForReferences,TDF_AttributeMap& atts) ;
  //! Returns in <atts> the referenced attributes. <br>
//!          Caution: <atts> is not cleared before use! <br>
  Standard_EXPORT   static  void OutReferences(const TDF_Label& aLabel,TDF_AttributeMap& atts) ;
  //! Returns in <atts> the referenced attributes and kept by <aFilterForReferences>. <br>
//!          It considers only the referers kept by <aFilterForReferers>. <br>
//!          Caution: <atts> is not cleared before use! <br>
  Standard_EXPORT   static  void OutReferences(const TDF_Label& aLabel,const TDF_IDFilter& aFilterForReferers,const TDF_IDFilter& aFilterForReferences,TDF_AttributeMap& atts) ;
  //! Returns the label having the same sub-entry as <br>
//!          <aLabel> but located as descendant as <toRoot> <br>
//!          instead of <fromRoot>. <br>
//! <br>
//!          Exemple : <br>
//! <br>
//!          aLabel = 0:3:24:7:2:7 <br>
//!          fromRoot = 0:3:24 <br>
//!          toRoot = 0:5 <br>
//!          returned label = 0:5:7:2:7 <br>
  Standard_EXPORT   static  void RelocateLabel(const TDF_Label& aSourceLabel,const TDF_Label& fromRoot,const TDF_Label& toRoot,TDF_Label& aTargetLabel,const Standard_Boolean create = Standard_False) ;
  //! Returns the entry for the label aLabel in the form <br>
//! of the ASCII character string anEntry containing <br>
//! the tag list for aLabel. <br>
  Standard_EXPORT   static  void Entry(const TDF_Label& aLabel,TCollection_AsciiString& anEntry) ;
  //! Returns the entry of <aLabel> as list of integers <br>
//!          in <aTagList>. <br>
  Standard_EXPORT   static  void TagList(const TDF_Label& aLabel,TColStd_ListOfInteger& aTagList) ;
  //! Returns the entry expressed by <anEntry> as list <br>
//!          of integers in <aTagList>. <br>
  Standard_EXPORT   static  void TagList(const TCollection_AsciiString& anEntry,TColStd_ListOfInteger& aTagList) ;
  //! Returns the label expressed by <anEntry>; creates <br>
//!          the label if it does not exist and if <create> is <br>
//!          true. <br>
  Standard_EXPORT   static  void Label(const Handle(TDF_Data)& aDF,const TCollection_AsciiString& anEntry,TDF_Label& aLabel,const Standard_Boolean create = Standard_False) ;
  //! Returns the label expressed by <anEntry>; creates <br>
//!          the label if it does not exist and if <create> is <br>
//!          true. <br>
  Standard_EXPORT   static  void Label(const Handle(TDF_Data)& aDF,const Standard_CString anEntry,TDF_Label& aLabel,const Standard_Boolean create = Standard_False) ;
  //! Returns the label expressed by <anEntry>; creates <br>
//!          the label if it does not exist and if <create> is <br>
//!          true. <br>
  Standard_EXPORT   static  void Label(const Handle(TDF_Data)& aDF,const TColStd_ListOfInteger& aTagList,TDF_Label& aLabel,const Standard_Boolean create = Standard_False) ;
  //! Adds the labels of <aLabelList> to <aLabelMap> if <br>
//!          they are unbound, or increases their reference <br>
//!          counters. At the end of the process, <aLabelList> <br>
//!          contains only the ADDED labels. <br>
  Standard_EXPORT   static  void CountLabels(TDF_LabelList& aLabelList,TDF_LabelIntegerMap& aLabelMap) ;
  //! Decreases the reference counters of the labels of <br>
//!          <aLabelList> to <aLabelMap>, and removes labels <br>
//!          with null counter. At the end of the process, <br>
//!          <aLabelList> contains only the SUPPRESSED labels. <br>
  Standard_EXPORT   static  void DeductLabels(TDF_LabelList& aLabelList,TDF_LabelIntegerMap& aLabelMap) ;
  //! Dumps <aDF> and its labels and their attributes. <br>
  Standard_EXPORT   static  void DeepDump(Standard_OStream& anOS,const Handle(TDF_Data)& aDF) ;
  //! Dumps <aDF> and its labels and their attributes, <br>
//!          if their IDs are kept by <aFilter>. Dumps also the <br>
//!          attributes content. <br>
  Standard_EXPORT   static  void ExtendedDeepDump(Standard_OStream& anOS,const Handle(TDF_Data)& aDF,const TDF_IDFilter& aFilter) ;
  //! Dumps <aLabel>, its chilren and their attributes. <br>
  Standard_EXPORT   static  void DeepDump(Standard_OStream& anOS,const TDF_Label& aLabel) ;
  //! Dumps <aLabel>, its chilren and their attributes, <br>
//!          if their IDs are kept by <aFilter>. Dumps also the <br>
//!          attributes content. <br>
  Standard_EXPORT   static  void ExtendedDeepDump(Standard_OStream& anOS,const TDF_Label& aLabel,const TDF_IDFilter& aFilter) ;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
