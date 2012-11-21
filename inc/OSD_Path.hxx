// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _OSD_Path_HeaderFile
#define _OSD_Path_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_AsciiString_HeaderFile
#include <TCollection_AsciiString.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _OSD_SysType_HeaderFile
#include <OSD_SysType.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Standard_ConstructionError;
class Standard_NullObject;
class OSD_OSDError;
class Standard_NumericError;
class Standard_ProgramError;
class TCollection_AsciiString;



class OSD_Path  {
public:

  DEFINE_STANDARD_ALLOC

  //! Creates a Path object initialized to an empty string. <br>
//!          i.e. current directory. <br>
  Standard_EXPORT   OSD_Path();
  //! Creates a Path object initialized by dependant path. <br>
//!          ex: OSD_Path me ("/usr/bin/myprog.sh",OSD_UnixBSD); <br>
//! <br>
//!              OSD_Path me ("sys$common:[syslib]cc.exe",OSD_OSF) will <br>
//!              raise a ProgramError due to invalid name for this <br>
//!              type of system. <br>
//!              In order to avoid a 'ProgramError' , use IsValid(...) <br>
//!              to ensure you the validity of <aDependentName>. <br>
//!              Raises ConstructionError when the path is either null <br>
//!              or contains characters not in range of ' '...'~'. <br>
  Standard_EXPORT   OSD_Path(const TCollection_AsciiString& aDependentName,const OSD_SysType aSysType = OSD_Default);
  //! Initializes a system independent path. <br>
//!          By default , the Path conversion will be assumed using <br>
//!          currently used system. <br>
//!          A special syntax is used to specify a "aTrek" in an <br>
//!          independent manner : <br>
//!          a "|" represents directory separator <br>
//!          a "^" means directory above (father) <br>
//!          examples: <br>
//!          "|usr|bin" - On UNIX -> "/usr/bin" <br>
//!                     - On VMS  -> "[usr.bin]" <br>
//!                     - On MSDOS-> "\usr\bin" <br>
//!                     - On MacOs-> ": usr : bin" <br>
  Standard_EXPORT   OSD_Path(const TCollection_AsciiString& aNode,const TCollection_AsciiString& aUsername,const TCollection_AsciiString& aPassword,const TCollection_AsciiString& aDisk,const TCollection_AsciiString& aTrek,const TCollection_AsciiString& aName,const TCollection_AsciiString& anExtension);
  //! Gets each component of a path. <br>
  Standard_EXPORT     void Values(TCollection_AsciiString& aNode,TCollection_AsciiString& aUsername,TCollection_AsciiString& aPassword,TCollection_AsciiString& aDisk,TCollection_AsciiString& aTrek,TCollection_AsciiString& aName,TCollection_AsciiString& anExtension) const;
  //! Sets each component of a path. <br>
  Standard_EXPORT     void SetValues(const TCollection_AsciiString& aNode,const TCollection_AsciiString& aUsername,const TCollection_AsciiString& aPassword,const TCollection_AsciiString& aDisk,const TCollection_AsciiString& aTrek,const TCollection_AsciiString& aName,const TCollection_AsciiString& anExtension) ;
  //! Returns system dependent path <br>
//!          <aType> is one among Unix,VMS ... <br>
//!          This function is not private because you may need to <br>
//!          display system dependent path on a front-end. <br>
//!          It can be useful when communicating with another system. <br>
//!          For instance when you want to communicate between VMS and Unix <br>
//!          to transfer files, or to do a remote procedure call <br>
//!          using files. <br>
//!          example : <br>
//!          OSD_Path myPath ("sparc4", "sga", "secret_passwd", <br>
//!                           "$5$dkb100","|users|examples"); <br>
//!          Internal ( Dependent_name ); <br>
//!          On UNIX  sga"secret_passwd"@sparc4:/users/examples <br>
//!          On VMS   sparc4"sga secret_passwd"::$5$dkb100:[users.examples] <br>//! Sets each component of a Path giving its system dependent name. <br>
  Standard_EXPORT     void SystemName(TCollection_AsciiString& FullName,const OSD_SysType aType = OSD_Default) const;
  //! Returns system dependent path resolving logical symbols. <br>
  Standard_EXPORT     void ExpandedName(TCollection_AsciiString& aName) ;
  //! Returns TRUE if <aDependentName> is valid for this SysType. <br>
  Standard_EXPORT     Standard_Boolean IsValid(const TCollection_AsciiString& aDependentName,const OSD_SysType aSysType = OSD_Default) const;
  //! This removes the last directory name in <aTrek> <br>
//!          and returns result. <br>
//!          ex:  me = "|usr|bin|todo.sh" <br>
//!               me.UpTrek() gives me = "|usr|todo.sh" <br>
//!          if <me> contains "|", me.UpTrek() will give again "|" <br>
//!          without any error. <br>
  Standard_EXPORT     void UpTrek() ;
  //! This appends a directory name into the Trek. <br>
//!          ex: me = "|usr|todo.sh" <br>
//!              me.DownTrek("bin") gives me = "|usr|bin|todo.sh". <br>
  Standard_EXPORT     void DownTrek(const TCollection_AsciiString& aName) ;
  //! Returns number of components in Trek of <me>. <br>
//!          ex: me = "|usr|sys|etc|bin" <br>
//!              me.TrekLength() returns 4. <br>
  Standard_EXPORT     Standard_Integer TrekLength() const;
  //! This removes a component of Trek in <me> at position <where>. <br>
//!          The first component of Trek is numbered 1. <br>
//!          ex:   me = "|usr|bin|" <br>
//!                me.RemoveATrek(1) gives me = "|bin|" <br>
//!          To avoid a 'NumericError' because of a bad <where>, use <br>
//!          TrekLength() to know number of components of Trek in <me>. <br>
  Standard_EXPORT     void RemoveATrek(const Standard_Integer where) ;
  //! This removes <aName> from <me> in Trek. <br>
//!          No error is raised if <aName> is not in <me>. <br>
//!          ex:  me = "|usr|sys|etc|doc" <br>
//!               me.RemoveATrek("sys") gives me = "|usr|etc|doc". <br>
  Standard_EXPORT     void RemoveATrek(const TCollection_AsciiString& aName) ;
  //! Returns component of Trek in <me> at position <where>. <br>
//!          ex:  me = "|usr|bin|sys|" <br>
//!               me.TrekValue(2) returns "bin" <br>
  Standard_EXPORT     TCollection_AsciiString TrekValue(const Standard_Integer where) const;
  //! This inserts <aName> at position <where> into Trek of <me>. <br>
//!          ex:  me = "|usr|etc|" <br>
//!               me.InsertATrek("sys",2) gives me = "|usr|sys|etc" <br>
  Standard_EXPORT     void InsertATrek(const TCollection_AsciiString& aName,const Standard_Integer where) ;
  //! Returns Node of <me>. <br>
  Standard_EXPORT     TCollection_AsciiString Node() const;
  //! Returns UserName of <me>. <br>
  Standard_EXPORT     TCollection_AsciiString UserName() const;
  //! Returns Password of <me>. <br>
  Standard_EXPORT     TCollection_AsciiString Password() const;
  //! Returns Disk of <me>. <br>
  Standard_EXPORT     TCollection_AsciiString Disk() const;
  //! Returns Trek of <me>. <br>
  Standard_EXPORT     TCollection_AsciiString Trek() const;
  //! Returns file name of <me>. <br>
//!          If <me> hasn't been initialized, it returns an empty AsciiString. <br>
  Standard_EXPORT     TCollection_AsciiString Name() const;
  //! Returns my extension name. <br>
//!          This returns an empty string if path contains no file name. <br>
  Standard_EXPORT     TCollection_AsciiString Extension() const;
  //! Sets Node of <me>. <br>
  Standard_EXPORT     void SetNode(const TCollection_AsciiString& aName) ;
  //! Sets UserName of <me>. <br>
  Standard_EXPORT     void SetUserName(const TCollection_AsciiString& aName) ;
  //! Sets Password of <me>. <br>
  Standard_EXPORT     void SetPassword(const TCollection_AsciiString& aName) ;
  //! Sets Disk of <me>. <br>
  Standard_EXPORT     void SetDisk(const TCollection_AsciiString& aName) ;
  //! Sets Trek of <me>. <br>
  Standard_EXPORT     void SetTrek(const TCollection_AsciiString& aName) ;
  //! Sets file name of <me>. <br>
//!          If <me> hasn't been initialized, it returns an empty AsciiString. <br>
  Standard_EXPORT     void SetName(const TCollection_AsciiString& aName) ;
  //! Sets my extension name. <br>
  Standard_EXPORT     void SetExtension(const TCollection_AsciiString& aName) ;
  //! Finds the full path of an executable file, like the <br>
//!          "which" Unix utility. Uses the path environment variable. <br>
//!          Returns False if executable file not found. <br>
  Standard_EXPORT     Standard_Boolean LocateExecFile(OSD_Path& aPath) ;
  //! Returns the relative file path between the absolute directory <br>
//!         path <DirPath>  and the absolute file path <AbsFilePath>. <br>
//!         If <DirPath> starts with "/", pathes are handled as <br>
//!         on Unix, if it starts with a letter followed by ":", as on <br>
//!         WNT. In particular on WNT directory names are not key sensitive. <br>
//!         If handling fails, an empty string is returned. <br>
  Standard_EXPORT   static  TCollection_AsciiString RelativePath(const TCollection_AsciiString& DirPath,const TCollection_AsciiString& AbsFilePath) ;
  //! Returns the absolute file path from the absolute directory path <br>
//!         <DirPath> and the relative file path returned by RelativePath(). <br>
//!         If the RelFilePath is an absolute path, it is returned and the <br>
//!         directory path is ignored. <br>
//!         If handling fails, an empty string is returned. <br>
  Standard_EXPORT   static  TCollection_AsciiString AbsolutePath(const TCollection_AsciiString& DirPath,const TCollection_AsciiString& RelFilePath) ;





protected:





private:



TCollection_AsciiString myNode;
TCollection_AsciiString myUserName;
TCollection_AsciiString myPassword;
TCollection_AsciiString myDisk;
TCollection_AsciiString myTrek;
TCollection_AsciiString myName;
TCollection_AsciiString myExtension;
Standard_Boolean myUNCFlag;
OSD_SysType SysDep;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
