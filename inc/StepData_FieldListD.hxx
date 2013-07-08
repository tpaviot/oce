// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StepData_FieldListD_HeaderFile
#define _StepData_FieldListD_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_StepData_HArray1OfField_HeaderFile
#include <Handle_StepData_HArray1OfField.hxx>
#endif
#ifndef _StepData_FieldList_HeaderFile
#include <StepData_FieldList.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class StepData_HArray1OfField;
class Standard_OutOfRange;
class StepData_Field;


//! Describes a list of fields, in a general way <br>
//!           This basic class is for a null size list <br>
//!           Subclasses are for 1, N (fixed) or Dynamic sizes <br>
class StepData_FieldListD  : public StepData_FieldList {
public:

  DEFINE_STANDARD_ALLOC

  //! Creates a FieldListD of <nb> Fields <br>
  Standard_EXPORT   StepData_FieldListD(const Standard_Integer nb);
  //! Sets a new count of Fields. Former contents are lost <br>
  Standard_EXPORT     void SetNb(const Standard_Integer nb) ;
  //! Returns the count of fields. Here, returns starting <nb> <br>
  Standard_EXPORT   virtual  Standard_Integer NbFields() const;
  //! Returns the field n0 <num> between 1 and NbFields (read only) <br>
  Standard_EXPORT   virtual const StepData_Field& Field(const Standard_Integer num) const;
  //! Returns the field n0 <num> between 1 and NbFields, in order to <br>
//!           modify its content <br>
  Standard_EXPORT   virtual  StepData_Field& CField(const Standard_Integer num) ;
  
  Standard_EXPORT   virtual  void Destroy() ;
Standard_EXPORT virtual ~StepData_FieldListD() { Destroy(); }





protected:





private:



Handle_StepData_HArray1OfField thefields;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
