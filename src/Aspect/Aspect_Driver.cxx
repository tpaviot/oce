/***********************************************************************

     FONCTION :
     ----------
        Classe Aspect_Driver :

     HISTORIQUE DES MODIFICATIONS   :
     --------------------------------

      14-05-98 : GG ; Disable using MFT when the symbol
			CSF_MDTVFontDirectory is not defined.
		      See dirMFTisDefined changes. 

      30-01-98 : GG ; SPEC_MFT
              L'utilisation des polices MFT devient parametrable.
	      Le driver doit utiliser la methode UseMFT() pour
	      savoir s'il doit utiliser ou non les polices
	      MDTV a la place des polices system.

		-> Modifications dans SetFontMap()
		-> Nouvelle methode UseMFT()

***********************************************************************/

#include <Aspect_Driver.ixx>
#include <OSD_Environment.hxx>

static Standard_Boolean dirMFTisDefined = Standard_False;

Aspect_Driver::Aspect_Driver () {

  OSD_Environment CSF_MDTVFontDirectory ;

  const char *fontdir , *casroot ;
  fontdir =  getenv("CSF_MDTVFontDirectory" );
  if ( !fontdir) {
    casroot  = getenv("CASROOT");
#ifdef OCE_CASROOT_FALLBACK_DIR
    if ( !casroot ) {
      casroot = OCE_CASROOT_FALLBACK_DIR;
    }
#endif
    if ( casroot ) {
      TCollection_AsciiString CasRootString (casroot);
      CasRootString += "/src/FontMFT" ; 
      CSF_MDTVFontDirectory = OSD_Environment(CasRootString.ToCString());
    } else {
      cout << " CASROOT or CSF_MDTVFontDirectory  are mandatory to use this fonctionnality " << endl;
      Standard_Failure::Raise ( "CSF_MDTVTexturesDirectory and CASROOT not setted " );
    }
  } else {
    CSF_MDTVFontDirectory = OSD_Environment("CSF_MDTVFontDirectory");
  }
  TCollection_AsciiString dir(CSF_MDTVFontDirectory.Value());

  dirMFTisDefined = (dir.Length() > 0);
  myUseMFT = Standard_True;
  myColorMapIsDefined = Standard_False;   
  myWidthMapIsDefined = Standard_False;   
  myTypeMapIsDefined  = Standard_False;   
  myFontMapIsDefined  = Standard_False;   
}


void Aspect_Driver::SetColorMap (const Handle(Aspect_ColorMap)& aColorMap) 
 {
   myColorMap = aColorMap;
   this->InitializeColorMap(aColorMap);
   myColorMapIsDefined = Standard_True;
}
Handle(Aspect_ColorMap) Aspect_Driver::ColorMap () const {

  Aspect_UndefinedMap_Raise_if(!myColorMapIsDefined,"ColorMap");
  return myColorMap;
}


void Aspect_Driver::SetTypeMap (const Handle(Aspect_TypeMap)& aTypeMap) 
 {
   myTypeMap = aTypeMap;
   this->InitializeTypeMap(aTypeMap);
   myTypeMapIsDefined = Standard_True;
}
Handle(Aspect_TypeMap) Aspect_Driver::TypeMap () const {

  Aspect_UndefinedMap_Raise_if(!myTypeMapIsDefined,"TypeMap");
  return myTypeMap;
}

void Aspect_Driver::SetWidthMap (const Handle(Aspect_WidthMap)& aWidthMap) 
 {
   myWidthMap = aWidthMap;
   this->InitializeWidthMap(aWidthMap);
   myWidthMapIsDefined = Standard_True;
}
Handle(Aspect_WidthMap) Aspect_Driver::WidthMap () const {

  Aspect_UndefinedMap_Raise_if(!myWidthMapIsDefined,"WidthMap");
  return myWidthMap;
}

void Aspect_Driver::SetFontMap (const Handle(Aspect_FontMap)& aFontMap,
				const Standard_Boolean useMFT) 
 {
   myUseMFT = useMFT;
   myFontMap = aFontMap;
   this->InitializeFontMap(aFontMap);
   myFontMapIsDefined = Standard_True;
}
Handle(Aspect_FontMap) Aspect_Driver::FontMap () const {

  Aspect_UndefinedMap_Raise_if(!myFontMapIsDefined,"FontMap");
  return myFontMap;
}

void Aspect_Driver::SetMarkMap (const Handle(Aspect_MarkMap)& aMarkMap) 
 {
   myMarkMap = aMarkMap;
   this->InitializeMarkMap(aMarkMap);
   myMarkMapIsDefined = Standard_True;
}
Handle(Aspect_MarkMap) Aspect_Driver::MarkMap () const {

  Aspect_UndefinedMap_Raise_if(!myMarkMapIsDefined,"MarkMap");
  return myMarkMap;
}

Standard_Boolean Aspect_Driver::UseMFT () const {
  return myUseMFT & dirMFTisDefined;
}
