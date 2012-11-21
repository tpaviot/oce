// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Message_MsgFile_HeaderFile
#define _Message_MsgFile_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_CString_HeaderFile
#include <Standard_CString.hxx>
#endif
class TCollection_AsciiString;
class TCollection_ExtendedString;


//! A tool providing facility to load definitions of message strings from <br>
//!          resource file(s). <br>
//! <br>
//!          The message file is an ASCII file which defines a set of messages. <br>
//!          Each message is identified by its keyword (string). <br>
//! <br>
//!          All lines in the file starting with the exclamation sign <br>
//!          (perhaps preceeding by spaces and/or tabs) are ignored as comments. <br>
//! <br>
//!          Each line in the file starting with the dot character "." <br>
//!          (perhaps preceeding by spaces and/or tabs) defines the keyword. <br>
//!          The keyword is a string starting from the next symbol after dot <br>
//!          and ending at the symbol preceeding ending newline character "\n". <br>
//! <br>
//!          All the lines in the file after the keyword and before next <br>
//!          keyword (and which are not comments) define the message for that <br>
//!          keyword. If the message consists of several lines, the message <br>
//!          string will contain newline symbols "\n" between parts (but not <br>
//!          at the end). <br>
//! <br>
//!          The experimental support of Unicode message files is provided. <br>
//!          These are distinguished by two bytes FF.FE or FE.FF at the beginning. <br>
//! <br>
//!          The loaded messages are stored in static data map; all methods of that <br>
//!          class are also static. <br>
class Message_MsgFile  {
public:

  DEFINE_STANDARD_ALLOC

  //! Load message file <theFileName> from directory <theDirName> <br>
//!          or its sub-directory <br>
  Standard_EXPORT   static  Standard_Boolean Load(const Standard_CString theDirName,const Standard_CString theFileName) ;
  //! Load the messages from the given file, additive to any previously <br>
//!          loaded messages. Messages with same keywords, if already present, <br>
//!          are replaced with the new ones. <br>
  Standard_EXPORT   static  Standard_Boolean LoadFile(const Standard_CString theFName) ;
  //! Loads the messages from the file with name (without extension) <br>
//!          given by environment variable. <br>
//!          Extension of the file name is given separately. If its not <br>
//!          defined, it is taken: <br>
//!          - by default from environment CSF_LANGUAGE, <br>
//!          - if not defined either, as "us". <br>
  Standard_EXPORT   static  void LoadFromEnv(const Standard_CString envname,const Standard_CString filename,const Standard_CString ext = "") ;
  //! Adds new message to the map. Parameter <key> gives <br>
//!          the key of the message, <text> defines the message itself. <br>
//!          If there already was defined the message identified by the <br>
//!          same keyword, it is replaced with the new one. <br>
  Standard_EXPORT   static  Standard_Boolean AddMsg(const TCollection_AsciiString& key,const TCollection_ExtendedString& text) ;
  
  Standard_EXPORT   static const TCollection_ExtendedString& Msg(const Standard_CString key) ;
  //! Gives the text for the message identified by the keyword <key> <br>
//!          If there are no messages with such keyword defined, <br>
//!          the error message is returned. <br>
//!          In that case reference to static string is returned, it can <br>
//!          be chenged with next call(s) to Msg(). <br>
//!          Note: The error message is constructed like 'Unknown message: <key>', and can <br>
//!                itself be customized by defining message with key Message_Msg_BadKeyword. <br>
  Standard_EXPORT   static const TCollection_ExtendedString& Msg(const TCollection_AsciiString& key) ;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
