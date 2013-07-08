// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Interface_ShareFlags_HeaderFile
#define _Interface_ShareFlags_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_Interface_InterfaceModel_HeaderFile
#include <Handle_Interface_InterfaceModel.hxx>
#endif
#ifndef _Interface_BitMap_HeaderFile
#include <Interface_BitMap.hxx>
#endif
#ifndef _Handle_TColStd_HSequenceOfTransient_HeaderFile
#include <Handle_TColStd_HSequenceOfTransient.hxx>
#endif
#ifndef _Handle_Interface_GTool_HeaderFile
#include <Handle_Interface_GTool.hxx>
#endif
#ifndef _Handle_Interface_Protocol_HeaderFile
#include <Handle_Interface_Protocol.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_Standard_Transient_HeaderFile
#include <Handle_Standard_Transient.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Interface_InterfaceModel;
class TColStd_HSequenceOfTransient;
class Standard_DomainError;
class Standard_OutOfRange;
class Interface_GeneralLib;
class Interface_GTool;
class Interface_Protocol;
class Interface_Graph;
class Standard_Transient;
class Interface_EntityIterator;


//! This class only says for each Entity of a Model, if it is <br>
//!           Shared or not by one or more other(s) of this Model <br>
//!           It uses the General Service "Shared". <br>
class Interface_ShareFlags  {
public:

  DEFINE_STANDARD_ALLOC

  //! Creates a ShareFlags from a Model and builds required data <br>
//!           (flags) by calling the General Service Library given as <br>
//!           argument <lib> <br>
  Standard_EXPORT   Interface_ShareFlags(const Handle(Interface_InterfaceModel)& amodel,const Interface_GeneralLib& lib);
  //! Same as above, but GeneralLib is detained by a GTool <br>
  Standard_EXPORT   Interface_ShareFlags(const Handle(Interface_InterfaceModel)& amodel,const Handle(Interface_GTool)& gtool);
  //! Same as above, but GeneralLib is defined through a Protocol <br>
  Standard_EXPORT   Interface_ShareFlags(const Handle(Interface_InterfaceModel)& amodel,const Handle(Interface_Protocol)& protocol);
  //! Same as above, but works with the GTool of the Model <br>
  Standard_EXPORT   Interface_ShareFlags(const Handle(Interface_InterfaceModel)& amodel);
  //! Creates a ShareFlags by querying informations from a Graph <br>
//!           (remark that Graph also has a method IsShared) <br>
  Standard_EXPORT   Interface_ShareFlags(const Interface_Graph& agraph);
  //! Returns the Model used for the evaluation <br>
  Standard_EXPORT     Handle_Interface_InterfaceModel Model() const;
  //! Returns True if <ent> is Shared by one or more other <br>
//!           Entity(ies) of the Model <br>
  Standard_EXPORT     Standard_Boolean IsShared(const Handle(Standard_Transient)& ent) const;
  //! Returns the Entities which are not Shared (see their flags) <br>
  Standard_EXPORT     Interface_EntityIterator RootEntities() const;
  //! Returns the count of root entities <br>
  Standard_EXPORT     Standard_Integer NbRoots() const;
  //! Returns a root entity according its rank in the list of roots <br>
//!           By default, it returns the first one <br>
  Standard_EXPORT     Handle_Standard_Transient Root(const Standard_Integer num = 1) const;





protected:





private:

  //! Computes flags at Creation time <br>
//! <br>
//!           Normally, gtool suffices. But if a Graph is created from a <br>
//!           GeneralLib directly, it cannot be used <br>
//!           If <gtool> is defined, it has priority <br>
  Standard_EXPORT     void Evaluate(const Interface_GeneralLib& lib,const Handle(Interface_GTool)& gtool) ;


Handle_Interface_InterfaceModel themodel;
Interface_BitMap theflags;
Handle_TColStd_HSequenceOfTransient theroots;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
