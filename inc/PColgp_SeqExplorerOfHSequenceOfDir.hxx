// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _PColgp_SeqExplorerOfHSequenceOfDir_HeaderFile
#define _PColgp_SeqExplorerOfHSequenceOfDir_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_PColgp_SeqNodeOfHSequenceOfDir_HeaderFile
#include <Handle_PColgp_SeqNodeOfHSequenceOfDir.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_PColgp_HSequenceOfDir_HeaderFile
#include <Handle_PColgp_HSequenceOfDir.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class PColgp_SeqNodeOfHSequenceOfDir;
class PColgp_HSequenceOfDir;
class Standard_NoSuchObject;
class Standard_OutOfRange;
class gp_Dir;



class PColgp_SeqExplorerOfHSequenceOfDir  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   PColgp_SeqExplorerOfHSequenceOfDir(const Handle(PColgp_HSequenceOfDir)& S);
  
  Standard_EXPORT     gp_Dir Value(const Standard_Integer Index) ;
  
  Standard_EXPORT     Standard_Boolean Contains(const gp_Dir& T) ;
  
  Standard_EXPORT     Standard_Integer Location(const Standard_Integer N,const gp_Dir& T,const Standard_Integer FromIndex,const Standard_Integer ToIndex) ;
  
  Standard_EXPORT     Standard_Integer Location(const Standard_Integer N,const gp_Dir& T) ;





protected:





private:



Handle_PColgp_SeqNodeOfHSequenceOfDir CurrentItem;
Standard_Integer CurrentIndex;
Handle_PColgp_HSequenceOfDir TheSequence;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
