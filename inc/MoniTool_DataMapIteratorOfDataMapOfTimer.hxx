// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _MoniTool_DataMapIteratorOfDataMapOfTimer_HeaderFile
#define _MoniTool_DataMapIteratorOfDataMapOfTimer_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_BasicMapIterator_HeaderFile
#include <TCollection_BasicMapIterator.hxx>
#endif
#ifndef _Standard_CString_HeaderFile
#include <Standard_CString.hxx>
#endif
#ifndef _Handle_MoniTool_Timer_HeaderFile
#include <Handle_MoniTool_Timer.hxx>
#endif
#ifndef _Handle_MoniTool_DataMapNodeOfDataMapOfTimer_HeaderFile
#include <Handle_MoniTool_DataMapNodeOfDataMapOfTimer.hxx>
#endif
class Standard_NoSuchObject;
class MoniTool_Timer;
class MoniTool_MTHasher;
class MoniTool_DataMapOfTimer;
class MoniTool_DataMapNodeOfDataMapOfTimer;



class MoniTool_DataMapIteratorOfDataMapOfTimer  : public TCollection_BasicMapIterator {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   MoniTool_DataMapIteratorOfDataMapOfTimer();
  
  Standard_EXPORT   MoniTool_DataMapIteratorOfDataMapOfTimer(const MoniTool_DataMapOfTimer& aMap);
  
  Standard_EXPORT     void Initialize(const MoniTool_DataMapOfTimer& aMap) ;
  
  Standard_EXPORT    const Standard_CString& Key() const;
  
  Standard_EXPORT    const Handle_MoniTool_Timer& Value() const;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
