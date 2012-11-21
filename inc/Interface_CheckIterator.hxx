// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Interface_CheckIterator_HeaderFile
#define _Interface_CheckIterator_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_Interface_HSequenceOfCheck_HeaderFile
#include <Handle_Interface_HSequenceOfCheck.hxx>
#endif
#ifndef _Handle_TColStd_HSequenceOfInteger_HeaderFile
#include <Handle_TColStd_HSequenceOfInteger.hxx>
#endif
#ifndef _Handle_Interface_InterfaceModel_HeaderFile
#include <Handle_Interface_InterfaceModel.hxx>
#endif
#ifndef _TCollection_AsciiString_HeaderFile
#include <TCollection_AsciiString.hxx>
#endif
#ifndef _Handle_Interface_IntVal_HeaderFile
#include <Handle_Interface_IntVal.hxx>
#endif
#ifndef _Standard_CString_HeaderFile
#include <Standard_CString.hxx>
#endif
#ifndef _Handle_Interface_Check_HeaderFile
#include <Handle_Interface_Check.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_Standard_Transient_HeaderFile
#include <Handle_Standard_Transient.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Interface_CheckStatus_HeaderFile
#include <Interface_CheckStatus.hxx>
#endif
#ifndef _Handle_TColStd_HSequenceOfTransient_HeaderFile
#include <Handle_TColStd_HSequenceOfTransient.hxx>
#endif
#ifndef _Handle_Message_Messenger_HeaderFile
#include <Handle_Message_Messenger.hxx>
#endif
class Interface_HSequenceOfCheck;
class TColStd_HSequenceOfInteger;
class Interface_InterfaceModel;
class Interface_IntVal;
class Standard_NoSuchObject;
class Interface_Check;
class Standard_Transient;
class TColStd_HSequenceOfTransient;
class Message_Messenger;


//! Result of a Check operation (especially from InterfaceModel) <br>
class Interface_CheckIterator  {
public:

  DEFINE_STANDARD_ALLOC

  //! Creates an empty CheckIterator <br>
  Standard_EXPORT   Interface_CheckIterator();
  //! Creates a CheckIterator with a name (displayed by Print as a <br>
//!           title) <br>
  Standard_EXPORT   Interface_CheckIterator(const Standard_CString name);
  //! Sets / Changes the name <br>
  Standard_EXPORT     void SetName(const Standard_CString name) ;
  //! Returns the recorded name (can be empty) <br>
  Standard_EXPORT     Standard_CString Name() const;
  //! Defines a Model, used to locate entities (not required, if it <br>
//!           is absent, entities are simply less documented) <br>
  Standard_EXPORT     void SetModel(const Handle(Interface_InterfaceModel)& model) ;
  //! Returns the stored model (can be a null handle) <br>
  Standard_EXPORT     Handle_Interface_InterfaceModel Model() const;
  //! Clears the list of checks <br>
  Standard_EXPORT     void Clear() ;
  //! Merges another CheckIterator into <me>, i.e. adds each of its <br>
//!           Checks. Content of <other> remains unchanged. <br>
//!           Takes also the Model but not the Name <br>
  Standard_EXPORT     void Merge(Interface_CheckIterator& other) ;
  //! Adds a Check to the list to be iterated <br>
//!           This Check is Accompanied by Entity Number in the Model <br>
//!           (0 for Global Check or Entity unknown in the Model), if 0 and <br>
//!           Model is recorded in <me>, it is computed <br>
  Standard_EXPORT     void Add(const Handle(Interface_Check)& ach,const Standard_Integer num = 0) ;
  //! Returns the Check which was attached to an Entity given its <br>
//!           Number in the Model. <num>=0 is for the Global Check. <br>
//!           If no Check was recorded for this Number, returns an empty <br>
//!           Check. <br>
//!  Remark : Works apart from the iteration methods (no interference) <br>
  Standard_EXPORT    const Handle_Interface_Check& Check(const Standard_Integer num) const;
  //! Returns the Check attached to an Entity <br>
//!           If no Check was recorded for this Entity, returns an empty <br>
//!           Check. <br>
//!  Remark : Works apart from the iteration methods (no interference) <br>
  Standard_EXPORT    const Handle_Interface_Check& Check(const Handle(Standard_Transient)& ent) const;
  //! Returns the Check bound to an Entity Number (0 : Global) <br>
//!           in order to be consulted or completed on the spot <br>
//!           I.e. returns the Check if is already exists, or adds it then <br>
//!           returns the new empty Check <br>
  Standard_EXPORT     Handle_Interface_Check& CCheck(const Standard_Integer num) ;
  //! Returns the Check bound to an Entity, in order to be consulted <br>
//!           or completed on the spot <br>
//!           I.e. returns the Check if is already exists, or adds it then <br>
//!           returns the new empty Check <br>
  Standard_EXPORT     Handle_Interface_Check& CCheck(const Handle(Standard_Transient)& ent) ;
  //! Returns True if : no Fail has been recorded if <failsonly> is <br>
//!           True, no Check at all if <failsonly> is False <br>
  Standard_EXPORT     Standard_Boolean IsEmpty(const Standard_Boolean failsonly) const;
  //! Returns worst status among : OK, Warning, Fail <br>
  Standard_EXPORT     Interface_CheckStatus Status() const;
  //! Tells if this check list complies with a given status : <br>
//!           OK (i.e. empty),  Warning (at least one Warning, but no Fail), <br>
//!           Fail (at least one), Message (not OK), NoFail, Any <br>
  Standard_EXPORT     Standard_Boolean Complies(const Interface_CheckStatus status) const;
  //! Returns a CheckIterator which contains the checks which comply <br>
//!           with a given status <br>
//!           Each check is added completely (no split Warning/Fail) <br>
  Standard_EXPORT     Interface_CheckIterator Extract(const Interface_CheckStatus status) const;
  //! Returns a CheckIterator which contains the check which comply <br>
//!           with a message, plus some conditions as follows : <br>
//!           <incl> = 0 : <mess> exactly matches one of the messages <br>
//!           <incl> < 0 : <mess> is contained by one of the messages <br>
//!           <incl> > 0 : <mess> contains one of the messages <br>
//!           For <status> : for CheckWarning and CheckFail, considers only <br>
//!             resp. Warning or Check messages. for CheckAny, considers all <br>
//!             other values are ignored (answer will be false) <br>
//!           Each Check which complies is entirely taken <br>
  Standard_EXPORT     Interface_CheckIterator Extract(const Standard_CString mess,const Standard_Integer incl,const Interface_CheckStatus status) const;
  //! Removes the messages of all Checks, under these conditions : <br>
//!           <incl> = 0 : <mess> exactly matches one of the messages <br>
//!           <incl> < 0 : <mess> is contained by one of the messages <br>
//!           <incl> > 0 : <mess> contains one of the messages <br>
//!           For <status> : for CheckWarning and CheckFail, considers only <br>
//!             resp. Warning or Check messages. for CheckAny, considers all <br>
//!             other values are ignored (nothing is done) <br>
//!           Returns True if at least one message has been removed, False else <br>
  Standard_EXPORT     Standard_Boolean Remove(const Standard_CString mess,const Standard_Integer incl,const Interface_CheckStatus status) ;
  //! Returns the list of entities concerned by a Check <br>
//!           Only fails if <failsonly> is True, else all non-empty checks <br>
//!           If <global> is true, adds the model for a global check <br>
//!           Else, global check is ignored <br>
  Standard_EXPORT     Handle_TColStd_HSequenceOfTransient Checkeds(const Standard_Boolean failsonly,const Standard_Boolean global) const;
  //! Starts Iteration. Thus, it is possible to restart it <br>
//!           Remark : an iteration may be done with a const Iterator <br>
//!           While its content is modified (through a pointer), this allows <br>
//!           to give it as a const argument to a function <br>
  Standard_EXPORT     void Start() const;
  //! Returns True if there are more Checks to get <br>
  Standard_EXPORT     Standard_Boolean More() const;
  //! Sets Iteration to next Item <br>
  Standard_EXPORT     void Next() const;
  //! Returns Check currently Iterated <br>
//!           It brings all other informations (status, messages, ...) <br>
//!           The Number of the Entity in the Model is given by Number below <br>
  Standard_EXPORT    const Handle_Interface_Check& Value() const;
  //! Returns Number of Entity for the Check currently iterated <br>
//!           or 0 for GlobalCheck <br>
  Standard_EXPORT     Standard_Integer Number() const;
  //! Prints the list of Checks with their attached Numbers <br>
//!           If <failsonly> is True, prints only Fail messages <br>
//!           If <failsonly> is False, prints all messages <br>
//!           If <final> = 0 (D), prints also original messages if different <br>
//!           If <final> < 0, prints only original messages <br>
//!           If <final> > 0, prints only final messages <br>
//!           It uses the recorded Model if it is defined <br>
//!  Remark : Works apart from the iteration methods (no interference) <br>
  Standard_EXPORT     void Print(const Handle(Message_Messenger)& S,const Standard_Boolean failsonly,const Standard_Integer final = 0) const;
  //! Works as Print without a model, but for entities which have <br>
//!           no attached number (Number not positive), tries to compute <br>
//!           this Number from <model> and displays "original" or "computed" <br>
  Standard_EXPORT     void Print(const Handle(Message_Messenger)& S,const Handle(Interface_InterfaceModel)& model,const Standard_Boolean failsonly,const Standard_Integer final = 0) const;
  //! Clears data of iteration <br>
  Standard_EXPORT     void Destroy() ;
~Interface_CheckIterator()
{
  Destroy();
}





protected:





private:



Handle_Interface_HSequenceOfCheck thelist;
Handle_TColStd_HSequenceOfInteger thenums;
Handle_Interface_InterfaceModel themod;
TCollection_AsciiString thename;
Handle_Interface_IntVal thecurr;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
