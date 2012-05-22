// Copyright (c) 1998-1999 Matra Datavision
// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.


#include <Standard_ProgramError.hxx>
#include <Standard_NullObject.hxx>
#include <Standard_ConstructionError.hxx>
#if !defined( WNT ) && !defined(__hpux) && !defined(HPUX)
#include <OSD_MailBox.ixx>
#include <OSD_WhoAmI.hxx>

#include <errno.h>

const OSD_WhoAmI Iam = OSD_WMailBox;

extern "C"{
int create_mailbox(char *,int, int (*)(...));
int open_mailbox(char *,int);
int remove_mailbox(int *, char *);
int write_mailbox(int *,char *,char *,int);
}


//====================== Create a mail box =========================

OSD_MailBox::OSD_MailBox(){
}



//============== Create an instanciated mail box ===================

OSD_MailBox::OSD_MailBox(const TCollection_AsciiString& box_name,
                         const Standard_Integer         box_size,
                         const OSD_Function&            async_function){


 if (!box_name.IsAscii())
  Standard_ConstructionError::Raise("OSD_MailBox::OSD_MailBox : box_name");

 myName = box_name;

 if (box_size <= 0)
  Standard_ProgramError::Raise("OSD_MailBox::OSD_MailBox : box_size");
 mySize = box_size;

 if (async_function == NULL)
  Standard_NullObject::Raise("OSD_MailBox::OSD_MailBox : async_function");
 myFunc = async_function;

}


//=======================================================================
//function : Build
//purpose  : 
//=======================================================================
void OSD_MailBox::Build()
{
  Standard_PCharacter pStr;
  pStr=(Standard_PCharacter)myName.ToCString();
  myId = create_mailbox(pStr, (int)mySize, myFunc);
  
  if (myId == 0)
    myError.SetValue (errno, Iam, "OSD_MailBox::Build");
}

//=======================================================================
//function : Open
//purpose  : 
//=======================================================================
void OSD_MailBox::Open ( const TCollection_AsciiString& box_name,
                         const Standard_Integer box_size)
{

 // Test function security 

 if (box_name == NULL)
  Standard_NullObject::Raise("OSD_MailBox::Open : box_name");

 if (!box_name.IsAscii())
  Standard_ConstructionError::Raise("OSD_MailBox::Open : box_name");

 myName = box_name;

 if (box_size <= 0)
  Standard_ProgramError::Raise("OSD_MailBox::Open : box_size");
 mySize = box_size;

 Standard_PCharacter pStr;
 //
 pStr=(Standard_PCharacter)box_name.ToCString();
 myId = open_mailbox(pStr, (int)box_size );
 if (myId == 0)
   myError.SetValue (errno, Iam, "OSD_MailBox::Open");
  
}





//====================== Close a mail box =======================

void OSD_MailBox::Delete ()
{
 
 if (myError.Failed()) myError.Perror();

 if (myId == 0)
  Standard_ProgramError::Raise("OSD_MailBox::Delete : mail box not opened/created");

 if (myName == NULL) 
  Standard_ProgramError::Raise("OSD_MailBox::Delete : mail box not opened/created");

 Standard_PCharacter pStr;
 pStr=(Standard_PCharacter)myName.ToCString();
 if (remove_mailbox((int *)&myId, pStr) == 0)
  myError.SetValue(errno, Iam, "OSD_MailBox::Delete");

 myId = 0;
}



//====================== Write into a mail box =======================

void OSD_MailBox::Write(const TCollection_AsciiString& message,
                        const Standard_Integer length)
{


 if (length <= 0 || length > mySize) 
  Standard_ProgramError::Raise("OSD_Mailbox::Write : bad length");

 Standard_PCharacter pStr, pStrM;
 //
 pStr=(Standard_PCharacter)myName.ToCString();
 pStrM=(Standard_PCharacter)message.ToCString();
 //
 if (write_mailbox((int *)&myId, pStr, pStrM, (int)length) == 0)
  myError.SetValue(errno, Iam, "OSD_Mailbox::Write");
}


void OSD_MailBox::Reset(){
 myError.Reset();
}

Standard_Boolean OSD_MailBox::Failed()const{
 return( myError.Failed());
}

void OSD_MailBox::Perror() {
 myError.Perror();
}


Standard_Integer OSD_MailBox::Error()const{
 return( myError.Error());
}
#endif



