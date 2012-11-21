// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XCAFDoc_ShapeTool_HeaderFile
#define _XCAFDoc_ShapeTool_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_XCAFDoc_ShapeTool_HeaderFile
#include <Handle_XCAFDoc_ShapeTool.hxx>
#endif

#ifndef _XCAFDoc_DataMapOfShapeLabel_HeaderFile
#include <XCAFDoc_DataMapOfShapeLabel.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _TDF_Attribute_HeaderFile
#include <TDF_Attribute.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_TDF_Attribute_HeaderFile
#include <Handle_TDF_Attribute.hxx>
#endif
#ifndef _Handle_TDF_RelocationTable_HeaderFile
#include <Handle_TDF_RelocationTable.hxx>
#endif
#ifndef _Handle_XCAFDoc_GraphNode_HeaderFile
#include <Handle_XCAFDoc_GraphNode.hxx>
#endif
class Standard_GUID;
class TDF_Label;
class TopoDS_Shape;
class TDF_LabelSequence;
class TopLoc_Location;
class TDF_Attribute;
class TDF_RelocationTable;
class TColStd_SequenceOfHAsciiString;
class XCAFDoc_GraphNode;
class TDF_AttributeSequence;
class TopTools_SequenceOfShape;


//!  A tool to store shapes in an XDE <br>
//! document in the form of assembly structure, and to maintain this structure. <br>
//! The API provided by this class allows to work with this <br>
//! structure regardless of its low-level implementation. <br>
//! All the shapes are stored on child labels of a main label which is <br>
//! XCAFDoc_DocumentTool::LabelShapes(). The label for assembly also has <br>
//! sub-labels, each of which represents the instance of <br>
//! another shape in that assembly (component). Such sub-label <br>
//! stores reference to the label of the original shape in the form <br>
//! of TDataStd_TreeNode with GUID XCAFDoc::ShapeRefGUID(), and its <br>
//! location encapsulated into the NamedShape. <br>
//! For correct work with an XDE document, it is necessary to use <br>
//! methods for analysis and methods for working with shapes. <br>
//! For example: <br>
//! if ( STool->IsAssembly(aLabel) ) <br>
//! { Standard_Boolean subchilds = Standard_False; (default) <br>
//! Standard_Integer nbc = STool->NbComponents <br>
//! (aLabel[,subchilds]); <br>
//! } <br>
//! If subchilds is True, commands also consider sub-levels. By <br>
//! default, only level one is checked. <br>
//! In this example, number of children from the first level of <br>
//! assembly will be returned. Methods for creation and initialization: <br>
//! Constructor: <br>
//! XCAFDoc_ShapeTool::XCAFDoc_ShapeTool() <br>
//! Getting a guid: <br>
//! Standard_GUID GetID (); <br>
//! Creation (if does not exist) of ShapeTool on label L: <br>
//! Handle(XCAFDoc_ShapeTool) XCAFDoc_ShapeTool::Set(const TDF_Label& L) <br>
//!   Analyze whether shape is a simple shape or an instance or a <br>
//! component of an assembly or it is an assembly ( methods of analysis). <br>
//! For example: <br>
//! STool->IsShape(aLabel) ; <br>
//! Analyze that the label represents a shape (simple <br>
//! shape, assembly or reference) or <br>
//! STool->IsTopLevel(aLabel); <br>
//! Analyze that the label is a label of a top-level shape. <br>
//!   Work with simple shapes, assemblies and instances ( <br>
//! methods for work with shapes). <br>
//! For example: <br>
//!   Add shape: <br>
//! Standard_Boolean makeAssembly; <br>
//! // True to interpret a Compound as an Assembly, False to take it <br>
//! as a whole <br>
//! aLabel = STool->AddShape(aShape, makeAssembly); <br>
//!        Get shape: <br>
//! TDF_Label aLabel... <br>
//! // A label must be present if <br>
//!  (aLabel.IsNull()) { ... no such label : abandon .. } <br>
//! TopoDS_Shape aShape; <br>
//! aShape = STool->GetShape(aLabel); <br>
//! if (aShape.IsNull()) <br>
//! { ... this label is not for a Shape ... } <br>
//!   To get a label from shape. <br>
//! Standard_Boolean findInstance = Standard_False; <br>
//! (this is default value) <br>
//! aLabel = STool->FindShape(aShape [,findInstance]); <br>
//! if (aLabel.IsNull()) <br>
//!  { ... no label found for this shape ... } <br>
class XCAFDoc_ShapeTool : public TDF_Attribute {

public:

  
  Standard_EXPORT   static const Standard_GUID& GetID() ;
  //! Create (if not exist) ShapeTool from XCAFDoc on <L>. <br>
  Standard_EXPORT   static  Handle_XCAFDoc_ShapeTool Set(const TDF_Label& L) ;
  //! Creates an empty tool <br>//! Creates a tool to work with a document <Doc> <br>
//!          Attaches to label XCAFDoc::LabelShapes() <br>
  Standard_EXPORT   XCAFDoc_ShapeTool();
  //! Returns True if the label is a label of top-level shape, <br>
//!          as opposed to component of assembly or subshape <br>
  Standard_EXPORT     Standard_Boolean IsTopLevel(const TDF_Label& L) const;
  //! Returns True if the label is not used by any assembly, i.e. <br>
//!          contains sublabels which are assembly components <br>
//!          This is relevant only if IsShape() is True <br>
//!    	    	    (There  is  no  Father TreeNode on  this  <L>) <br>
  Standard_EXPORT   static  Standard_Boolean IsFree(const TDF_Label& L) ;
  //! Returns True if the label represents a shape (simple shape, <br>
//!          assembly or reference) <br>
  Standard_EXPORT   static  Standard_Boolean IsShape(const TDF_Label& L) ;
  //! Returns True if the label is a label of simple shape <br>
  Standard_EXPORT   static  Standard_Boolean IsSimpleShape(const TDF_Label& L) ;
  //! Return true if <L> is a located instance of other shape <br>
//!          i.e. reference <br>
  Standard_EXPORT   static  Standard_Boolean IsReference(const TDF_Label& L) ;
  //! Returns True if the label is a label of assembly, i.e. <br>
//!          contains sublabels which are assembly components <br>
//!          This is relevant only if IsShape() is True <br>
  Standard_EXPORT   static  Standard_Boolean IsAssembly(const TDF_Label& L) ;
  //! Return true if <L> is reference serving as component <br>
//!          of assembly <br>
  Standard_EXPORT   static  Standard_Boolean IsComponent(const TDF_Label& L) ;
  //! Returns True if the label is a label of compound, i.e. <br>
//!          contains some sublabels <br>
//!          This is relevant only if IsShape() is True <br>
  Standard_EXPORT   static  Standard_Boolean IsCompound(const TDF_Label& L) ;
  //! Return true if <L> is subshape of the top-level shape <br>
  Standard_EXPORT   static  Standard_Boolean IsSubShape(const TDF_Label& L) ;
  //! Checks whether shape <sub> is subshape of shape stored on <br>
//!          label shapeL <br>
  Standard_EXPORT     Standard_Boolean IsSubShape(const TDF_Label& shapeL,const TopoDS_Shape& sub) const;
  
  Standard_EXPORT     Standard_Boolean SearchUsingMap(const TopoDS_Shape& S,TDF_Label& L,const Standard_Boolean findWithoutLoc,const Standard_Boolean findSubshape) const;
  //! General tool to find a (sub) shape in the document <br>
//!        * If findInstance is True, and S has a non-null location, <br>
//!          first tries to find the shape among the top-level shapes <br>
//!          with this location <br>
//!        * If not found, and findComponent is True, tries to find the shape <br>
//!          among the components of assemblies <br>
//!        * If not found, tries to find the shape without location <br>
//!          among top-level shapes <br>
//!        * If not found and findSubshape is True, tries to find a <br>
//!          shape as a subshape of top-level simple shapes <br>
//!          Returns False if nothing is found <br>
  Standard_EXPORT     Standard_Boolean Search(const TopoDS_Shape& S,TDF_Label& L,const Standard_Boolean findInstance = Standard_True,const Standard_Boolean findComponent = Standard_True,const Standard_Boolean findSubshape = Standard_True) const;
  //! Returns the label corresponding to shape S <br>
//!          (searches among top-level shapes, not including subcomponents <br>
//!          of assemblies) <br>
//!          If findInstance is False (default), searches for the <br>
//!          non-located shape (i.e. among original shapes) <br>
//!          If findInstance is True, searches for the shape with the same <br>
//!          location, including shape instances <br>
//!          Return True if <S> is found. <br>
  Standard_EXPORT     Standard_Boolean FindShape(const TopoDS_Shape& S,TDF_Label& L,const Standard_Boolean findInstance = Standard_False) const;
  //! Does the same as previous method <br>
//!          Returns Null label if not found <br>
  Standard_EXPORT     TDF_Label FindShape(const TopoDS_Shape& S,const Standard_Boolean findInstance = Standard_False) const;
  //! To get TopoDS_Shape from shape's label <br>
//!          For component, returns new shape with correct location <br>
//!          Returns False if label does not contain shape <br>
  Standard_EXPORT   static  Standard_Boolean GetShape(const TDF_Label& L,TopoDS_Shape& S) ;
  //! To get TopoDS_Shape from shape's label <br>
//!          For component, returns new shape with correct location <br>
//!          Returns Null shape if label does not contain shape <br>
  Standard_EXPORT   static  TopoDS_Shape GetShape(const TDF_Label& L) ;
  //! Creates new (empty) top-level shape. <br>
//!          Initially it holds empty TopoDS_Compound <br>
  Standard_EXPORT     TDF_Label NewShape() const;
  //! Sets representation (TopoDS_Shape) for top-level shape <br>
  Standard_EXPORT     void SetShape(const TDF_Label& L,const TopoDS_Shape& S) ;
  //! Adds a new top-level (creates and returns a new label) <br>
//!          If makeAssembly is True, treats TopAbs_COMPOUND shapes <br>
//!          as assemblies (creates assembly structure). <br>
//!          NOTE: <makePrepare> replace components without location <br>
//!          in assmebly by located components to avoid some problems. <br>
  Standard_EXPORT     TDF_Label AddShape(const TopoDS_Shape& S,const Standard_Boolean makeAssembly = Standard_True,const Standard_Boolean makePrepare = Standard_True) ;
  //! Removes shape (whole label and all its sublabels) <br>
//!          If removeCompletely is true, removes complete shape <br>
//!          If removeCompletely is false, removes instance(location) only <br>
//!          Returns False (and does nothing) if shape is not free <br>
//!          or is not top-level shape <br>
  Standard_EXPORT     Standard_Boolean RemoveShape(const TDF_Label& L,const Standard_Boolean removeCompletely = Standard_True) const;
  //! set hasComponents into false <br>
  Standard_EXPORT     void Init() ;
  //! recursive <br>
  Standard_EXPORT     void ComputeShapes(const TDF_Label& L) ;
  //! Compute a sequence of simple shapes <br>
  Standard_EXPORT     void ComputeSimpleShapes() ;
  //! Returns a sequence of all top-level shapes <br>
  Standard_EXPORT     void GetShapes(TDF_LabelSequence& Labels) const;
  //! Returns a sequence of all top-level shapes <br>
//!          which are free (i.e. not referred by any other) <br>
  Standard_EXPORT     void GetFreeShapes(TDF_LabelSequence& FreeLabels) const;
  //! Returns list of labels which refer shape L as component <br>
//!          Returns number of users (0 if shape is free) <br>
  Standard_EXPORT   static  Standard_Integer GetUsers(const TDF_Label& L,TDF_LabelSequence& Labels,const Standard_Boolean getsubchilds = Standard_False) ;
  //! Returns location of instance <br>
  Standard_EXPORT   static  TopLoc_Location GetLocation(const TDF_Label& L) ;
  //! Returns label which corresponds to a shape referred by L <br>
//!          Returns False if label is not reference <br>
  Standard_EXPORT   static  Standard_Boolean GetReferredShape(const TDF_Label& L,TDF_Label& Label) ;
  //! Returns number of Assembles components <br>
  Standard_EXPORT   static  Standard_Integer NbComponents(const TDF_Label& L,const Standard_Boolean getsubchilds = Standard_False) ;
  //! Returns list of components of assembly <br>
//!          Returns False if label is not assembly <br>
  Standard_EXPORT   static  Standard_Boolean GetComponents(const TDF_Label& L,TDF_LabelSequence& Labels,const Standard_Boolean getsubchilds = Standard_False) ;
  //! Adds a component given by its label and location to the assembly <br>
//!          Note: assembly must be IsAssembly() or IsSimpleShape() <br>
  Standard_EXPORT     TDF_Label AddComponent(const TDF_Label& assembly,const TDF_Label& comp,const TopLoc_Location& Loc) const;
  //! Adds a shape (located) as a component to the assembly <br>
//!          If necessary, creates an additional top-level shape for <br>
//!          component and return the Label of component. <br>
//!          If expand is True and component is Compound, it will <br>
//!          be created as assembly also <br>
//!          Note: assembly must be IsAssembly() or IsSimpleShape() <br>
  Standard_EXPORT     TDF_Label AddComponent(const TDF_Label& assembly,const TopoDS_Shape& comp,const Standard_Boolean expand = Standard_False) ;
  //! Removes a component from its assembly <br>
  Standard_EXPORT     void RemoveComponent(const TDF_Label& comp) const;
  //! Update an assembly at label <L> <br>
  Standard_EXPORT     void UpdateAssembly(const TDF_Label& L) const;
  //! Finds a label for subshape <sub> of shape stored on <br>
//!          label shapeL <br>
//!          Returns Null label if it is not found <br>
  Standard_EXPORT     Standard_Boolean FindSubShape(const TDF_Label& shapeL,const TopoDS_Shape& sub,TDF_Label& L) const;
  //! Adds a label for subshape <sub> of shape stored on <br>
//!          label shapeL <br>
//!          Returns Null label if it is not subshape <br>
  Standard_EXPORT     TDF_Label AddSubShape(const TDF_Label& shapeL,const TopoDS_Shape& sub) const;
  
  Standard_EXPORT     TDF_Label FindMainShapeUsingMap(const TopoDS_Shape& sub) const;
  //! Performs a search among top-level shapes to find <br>
//!          the shape containing <sub> as subshape <br>
//!          Checks only simple shapes, and returns the first found <br>
//!          label (which should be the only one for valid model) <br>
  Standard_EXPORT     TDF_Label FindMainShape(const TopoDS_Shape& sub) const;
  //! Returns list of labels identifying subshapes of the given shape <br>
//!          Returns False if no subshapes are placed on that label <br>
  Standard_EXPORT   static  Standard_Boolean GetSubShapes(const TDF_Label& L,TDF_LabelSequence& Labels) ;
  //! returns the label under which shapes are stored <br>
  Standard_EXPORT     TDF_Label BaseLabel() const;
  
  Standard_EXPORT     void Dump(const Standard_Boolean deep = Standard_False) const;
  //! Print in cout type of shape found on <L> label <br>
//!          and the entry of <L>, with <level> tabs before. <br>
//!          If <deep>, print also TShape and Location addresses <br>
  Standard_EXPORT   static  void DumpShape(const TDF_Label& L,const Standard_Integer level = 0,const Standard_Boolean deep = Standard_False) ;
  
  Standard_EXPORT    const Standard_GUID& ID() const;
  
  Standard_EXPORT     void Restore(const Handle(TDF_Attribute)& with) ;
  
  Standard_EXPORT     Handle_TDF_Attribute NewEmpty() const;
  
  Standard_EXPORT     void Paste(const Handle(TDF_Attribute)& into,const Handle(TDF_RelocationTable)& RT) const;
  //! Returns True if the label is a label of external references, i.e. <br>
//!          there are some reference on the no-step files, which are <br>
//!          described in document only their names <br>
  Standard_EXPORT   static  Standard_Boolean IsExternRef(const TDF_Label& L) ;
  //! Sets the names of references on the no-step files <br>
  Standard_EXPORT     TDF_Label SetExternRefs(const TColStd_SequenceOfHAsciiString& SHAS) const;
  //! Sets the names of references on the no-step files <br>
  Standard_EXPORT     void SetExternRefs(const TDF_Label& L,const TColStd_SequenceOfHAsciiString& SHAS) const;
  //! Gets the names of references on the no-step files <br>
  Standard_EXPORT   static  void GetExternRefs(const TDF_Label& L,TColStd_SequenceOfHAsciiString& SHAS) ;
  //! Sets the SHUO structure between upper_usage and next_usage <br>
//!          create multy-level (if number of labels > 2) SHUO from first to last <br>
//!          Initialise out <MainSHUOAttr> by main upper_usage SHUO attribute. <br>
//!          Returns FALSE if some of labels in not component label <br>
  Standard_EXPORT     Standard_Boolean SetSHUO(const TDF_LabelSequence& Labels,Handle(XCAFDoc_GraphNode)& MainSHUOAttr) const;
  //! Returns founded SHUO GraphNode attribute <aSHUOAttr> <br>
//!          Returns false in other case <br>
  Standard_EXPORT   static  Standard_Boolean GetSHUO(const TDF_Label& SHUOLabel,Handle(XCAFDoc_GraphNode)& aSHUOAttr) ;
  //! Returns founded SHUO GraphNodes of indicated component <br>
//!          Returns false in other case <br>
  Standard_EXPORT   static  Standard_Boolean GetAllComponentSHUO(const TDF_Label& CompLabel,TDF_AttributeSequence& SHUOAttrs) ;
  //! Returns the sequence of labels of SHUO attributes, <br>
//!          which is upper_usage for this next_usage SHUO attribute <br>
//!                                          (that indicated by label) <br>
//!          NOTE: returns upper_usages only on one level (not recurse) <br>
//!          NOTE: do not clear the sequence before filling <br>
  Standard_EXPORT   static  Standard_Boolean GetSHUOUpperUsage(const TDF_Label& NextUsageL,TDF_LabelSequence& Labels) ;
  //! Returns the sequence of labels of SHUO attributes, <br>
//!          which is next_usage for this upper_usage SHUO attribute <br>
//!                                          (that indicated by label) <br>
//!          NOTE: returns next_usages only on one level (not recurse) <br>
//!          NOTE: do not clear the sequence before filling <br>
  Standard_EXPORT   static  Standard_Boolean GetSHUONextUsage(const TDF_Label& UpperUsageL,TDF_LabelSequence& Labels) ;
  //! Remove SHUO from component sublabel, <br>
//!                                remove all dependencies on other SHUO. <br>
//!          Returns FALSE if cannot remove SHUO dependencies. <br>
//!          NOTE: remove any styles that associated with this SHUO. <br>
  Standard_EXPORT     Standard_Boolean RemoveSHUO(const TDF_Label& SHUOLabel) const;
  //! Serach the path of labels in the document, <br>
//!          that corresponds the component from any assembly <br>
//!          Try to search the sequence of labels with location that <br>
//!          produce this shape as component of any assembly <br>
//!          NOTE: Clear sequence of labels before filling <br>
  Standard_EXPORT     Standard_Boolean FindComponent(const TopoDS_Shape& theShape,TDF_LabelSequence& Labels) const;
  //! Search for the component shape that styled by shuo <br>
//!          Returns null shape if no any shape is found. <br>
  Standard_EXPORT     TopoDS_Shape GetSHUOInstance(const Handle(XCAFDoc_GraphNode)& theSHUO) const;
  //! Search for the component shape by labelks path <br>
//!          and set SHUO structure for founded label structure <br>
//!          Returns null attribute if no component in any assembly found. <br>
  Standard_EXPORT     Handle_XCAFDoc_GraphNode SetInstanceSHUO(const TopoDS_Shape& theShape) const;
  //! Seaching for component shapes that styled by shuo <br>
//!          Returns empty sequence of shape if no any shape is found. <br>
  Standard_EXPORT     Standard_Boolean GetAllSHUOInstances(const Handle(XCAFDoc_GraphNode)& theSHUO,TopTools_SequenceOfShape& theSHUOShapeSeq) const;
  //! Searchs the SHUO by labels of components <br>
//!          from upper_usage componet to next_usage <br>
//!          Returns null attribute if no SHUO found <br>
  Standard_EXPORT   static  Standard_Boolean FindSHUO(const TDF_LabelSequence& Labels,Handle(XCAFDoc_GraphNode)& theSHUOAttr) ;




  DEFINE_STANDARD_RTTI(XCAFDoc_ShapeTool)

protected:




private: 

  //! Adds a new top-level (creates and returns a new label) <br>
//!          For internal use. Used by public method AddShape. <br>
  Standard_EXPORT     TDF_Label addShape(const TopoDS_Shape& S,const Standard_Boolean makeAssembly = Standard_True) ;
  //! Makes a shape on label L to be a reference to shape refL <br>
//!          with location loc <br>
  Standard_EXPORT   static  void MakeReference(const TDF_Label& L,const TDF_Label& refL,const TopLoc_Location& loc) ;

XCAFDoc_DataMapOfShapeLabel myShapeLabels;
XCAFDoc_DataMapOfShapeLabel mySubShapes;
XCAFDoc_DataMapOfShapeLabel mySimpleShapes;
Standard_Boolean hasSimpleShapes;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
