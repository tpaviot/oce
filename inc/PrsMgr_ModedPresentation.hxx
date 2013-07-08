// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _PrsMgr_ModedPresentation_HeaderFile
#define _PrsMgr_ModedPresentation_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_PrsMgr_Presentation_HeaderFile
#include <Handle_PrsMgr_Presentation.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class PrsMgr_Presentation;



class PrsMgr_ModedPresentation  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   PrsMgr_ModedPresentation();
  
  Standard_EXPORT   PrsMgr_ModedPresentation(const Handle(PrsMgr_Presentation)& aPresentation,const Standard_Integer aMode);
  
  Standard_EXPORT     Handle_PrsMgr_Presentation Presentation() const;
  
  Standard_EXPORT     Standard_Integer Mode() const;





protected:





private:



Handle_PrsMgr_Presentation myPresentation;
Standard_Integer myMode;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
