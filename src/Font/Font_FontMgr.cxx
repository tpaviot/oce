// Created on: 2008-01-20
// Created by: Alexander A. BORODIN
// Copyright (c) 2008-2012 OPEN CASCADE SAS
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

#include <Font_FontMgr.ixx>

#include <OSD_Environment.hxx>
#include <NCollection_List.hxx>
#include <NCollection_Map.hxx>
#include <Standard_Stream.hxx>
#include <TCollection_HAsciiString.hxx>

#include <ft2build.h>
#include FT_FREETYPE_H

struct Font_FontMgr_FontAliasMapNode
{
  const char *    EnumName;
  const char *    FontName;
  Font_FontAspect FontAspect;
};

static const Font_FontMgr_FontAliasMapNode Font_FontMgr_MapOfFontsAliases[] =
{

#ifdef WNT

  { "Courier"                  , "Courier New"    , Font_FA_Regular },
  { "Times-Roman"              , "Times New Roman", Font_FA_Regular  },
  { "Times-Bold"               , "Times New Roman", Font_FA_Bold },
  { "Times-Italic"             , "Times New Roman", Font_FA_Italic  },
  { "Times-BoldItalic"         , "Times New Roman", Font_FA_BoldItalic  },
  { "ZapfChancery-MediumItalic", "Script"         , Font_FA_Regular  },
  { "Symbol"                   , "Symbol"         , Font_FA_Regular  },
  { "ZapfDingbats"             , "WingDings"      , Font_FA_Regular  },
  { "Rock"                     , "Arial"          , Font_FA_Regular  },
  { "Iris"                     , "Lucida Console" , Font_FA_Regular  }

#else   //X11

  { "Courier"                  , "Courier"      , Font_FA_Regular },
  { "Times-Roman"              , "Times"        , Font_FA_Regular  },
  { "Times-Bold"               , "Times"        , Font_FA_Bold },
  { "Times-Italic"             , "Times"        , Font_FA_Italic  },
  { "Times-BoldItalic"         , "Times"        , Font_FA_BoldItalic  },
  { "Arial"                    , "Helvetica"    , Font_FA_Regular  }, 
  { "ZapfChancery-MediumItalic", "-adobe-itc zapf chancery-medium-i-normal--*-*-*-*-*-*-iso8859-1"              , Font_FA_Regular  },
  { "Symbol"                   , "-adobe-symbol-medium-r-normal--*-*-*-*-*-*-adobe-fontspecific"                , Font_FA_Regular  },
  { "ZapfDingbats"             , "-adobe-itc zapf dingbats-medium-r-normal--*-*-*-*-*-*-adobe-fontspecific"     , Font_FA_Regular  },
  { "Rock"                     , "-sgi-rock-medium-r-normal--*-*-*-*-p-*-iso8859-1"                             , Font_FA_Regular  },
  { "Iris"                     , "--iris-medium-r-normal--*-*-*-*-m-*-iso8859-1"                                , Font_FA_Regular  }
#endif

};

#define NUM_FONT_ENTRIES (sizeof(Font_FontMgr_MapOfFontsAliases)/sizeof(Font_FontMgr_FontAliasMapNode))

#if (defined(_WIN32) || defined(__WIN32__))

  #include <windows.h>
  #include <stdlib.h>

  namespace
  {

    // list of supported extensions
    static Standard_CString Font_FontMgr_Extensions[] =
    {
      "ttf",
      "otf",
      "ttc",
      NULL
    };

  };

#else

  #include <OSD_DirectoryIterator.hxx>
  #include <OSD_Path.hxx>
  #include <OSD_File.hxx>
  #include <OSD_OpenMode.hxx>
  #include <OSD_Protection.hxx>

  namespace
  {

    // list of supported extensions
    static Standard_CString Font_FontMgr_Extensions[] =
    {
      "ttf",
      "otf",
      "ttc",
      "pfa",
      "pfb",
      NULL
    };

    // X11 configuration file in plain text format (obsolete - doesn't exists in modern distributives)
    static Standard_CString myFontServiceConf[] = {"/etc/X11/fs/config",
                                                   "/usr/X11R6/lib/X11/fs/config",
                                                   "/usr/X11/lib/X11/fs/config",
                                                   NULL
                                                  };

  #ifdef __APPLE__
    // default fonts paths in Mac OS X
    static Standard_CString myDefaultFontsDirs[] = {"/System/Library/Fonts",
                                                    "/Library/Fonts",
                                                    NULL
                                                   };
  #else
    // default fonts paths in most Unix systems (Linux and others)
    static Standard_CString myDefaultFontsDirs[] = {"/usr/share/fonts",
                                                    "/usr/local/share/fonts",
                                                    NULL
                                                   };
  #endif

    static void addDirsRecursively (const OSD_Path&                           thePath,
                                    NCollection_Map<TCollection_AsciiString>& theDirsMap)
    {
      TCollection_AsciiString aDirName;
      thePath.SystemName (aDirName);
      if (!theDirsMap.Add (aDirName))
      {
        return;
      }

      for (OSD_DirectoryIterator aDirIterator (thePath, "*"); aDirIterator.More(); aDirIterator.Next())
      {
        OSD_Path aChildDirPath;
        aDirIterator.Values().Path (aChildDirPath);

        TCollection_AsciiString aChildDirName;
        aChildDirPath.SystemName (aChildDirName);
        if (!aChildDirName.IsEqual (".") && !aChildDirName.IsEqual (".."))
        {
          aChildDirName = aDirName + "/" + aChildDirName;
          OSD_Path aPath (aChildDirName);
          addDirsRecursively (aPath, theDirsMap);
        }
      }
    }

  };

#endif

// =======================================================================
// function : checkFont
// purpose  :
// =======================================================================
static Handle(Font_SystemFont) checkFont (FT_Library             theFTLib,
                                          const Standard_CString theFontPath)
{
  FT_Face aFontFace;
  FT_Error aFaceError = FT_New_Face (theFTLib, theFontPath, 0, &aFontFace);
  if (aFaceError != FT_Err_Ok)
  {
    return NULL;
  }

  Font_FontAspect anAspect = Font_FA_Regular;
  if (aFontFace->style_flags == (FT_STYLE_FLAG_ITALIC | FT_STYLE_FLAG_BOLD))
  {
    anAspect = Font_FA_BoldItalic;
  }
  else if (aFontFace->style_flags == FT_STYLE_FLAG_ITALIC)
  {
    anAspect = Font_FA_Italic;
  }
  else if (aFontFace->style_flags == FT_STYLE_FLAG_BOLD)
  {
    anAspect = Font_FA_Bold;
  }

  Handle(TCollection_HAsciiString) aFontName = new TCollection_HAsciiString (aFontFace->family_name);
  Handle(TCollection_HAsciiString) aFontPath = new TCollection_HAsciiString (theFontPath);
  Handle(Font_SystemFont) aResult = new Font_SystemFont (aFontName, anAspect, aFontPath);

  FT_Done_Face (aFontFace);

  return aResult;
}

// =======================================================================
// function : GetInstance
// purpose  :
// =======================================================================
Handle(Font_FontMgr) Font_FontMgr::GetInstance()
{
  static Handle(Font_FontMgr) _mgr;
  if (_mgr.IsNull())
  {
    _mgr = new Font_FontMgr();
  }

  return _mgr;
}

// =======================================================================
// function : Font_FontMgr
// purpose  :
// =======================================================================
Font_FontMgr::Font_FontMgr()
{
  InitFontDataBase();
}

// =======================================================================
// function : InitFontDataBase
// purpose  :
// =======================================================================
void Font_FontMgr::InitFontDataBase()
{
  myListOfFonts.Clear();
  FT_Library aFtLibrary = NULL;

#if (defined(_WIN32) || defined(__WIN32__))

  // font directory is placed in "C:\Windows\Fonts\"
  UINT aStrLength = GetSystemWindowsDirectoryA (NULL, 0);
  if (aStrLength == 0)
  {
    return;
  }

  char* aWinDir = new char[aStrLength];
  GetSystemWindowsDirectoryA (aWinDir, aStrLength);
  Handle(TCollection_HAsciiString) aFontsDir = new TCollection_HAsciiString (aWinDir);
  aFontsDir->AssignCat ("\\Fonts\\");
  delete[] aWinDir;

  // read fonts list from registry
  HKEY aFontsKey;
  if (RegOpenKeyExA (HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts",
                     0, KEY_READ, &aFontsKey) != ERROR_SUCCESS)
  {
    return;
  }

  NCollection_Map<TCollection_AsciiString> aSupportedExtensions;
  for (Standard_Integer anIter = 0; Font_FontMgr_Extensions[anIter] != NULL; ++anIter)
  {
    Standard_CString anExt = Font_FontMgr_Extensions[anIter];
    aSupportedExtensions.Add (TCollection_AsciiString (anExt));
  }

  FT_Init_FreeType (&aFtLibrary);
  static const DWORD aBufferSize = 256;
  char aNameBuff[aBufferSize];
  char aPathBuff[aBufferSize];
  DWORD aNameSize = aBufferSize;
  DWORD aPathSize = aBufferSize;
  for (DWORD anIter = 0;
       RegEnumValueA (aFontsKey, anIter,
                      aNameBuff, &aNameSize, NULL, NULL,
                      (LPBYTE )aPathBuff, &aPathSize) != ERROR_NO_MORE_ITEMS;
      ++anIter, aNameSize = aBufferSize, aPathSize = aBufferSize)
  {
    aPathBuff[(aPathSize < aBufferSize) ? aPathSize : (aBufferSize - 1)] = '\0'; // ensure string is NULL-terminated

    Handle(TCollection_HAsciiString) aFontName = new TCollection_HAsciiString (aNameBuff);
    Handle(TCollection_HAsciiString) aFontPath = new TCollection_HAsciiString (aPathBuff);
    if (aFontPath->Search ("\\") == -1)
    {
      aFontPath->Insert (1, aFontsDir); // make absolute path
    }

    // check file extension is in list of supported
    const Standard_Integer anExtensionPosition = aFontPath->SearchFromEnd (".") + 1;
    if (anExtensionPosition > 0 && anExtensionPosition < aFontPath->Length())
    {
      Handle(TCollection_HAsciiString) aFontExtension = aFontPath->SubString (anExtensionPosition, aFontPath->Length());
      aFontExtension->LowerCase();
      if (aSupportedExtensions.Contains (aFontExtension->String()))
      {
        Handle(Font_SystemFont) aNewFont = checkFont (aFtLibrary, aFontPath->ToCString());
        if (!aNewFont.IsNull())
        {
          myListOfFonts.Append (aNewFont);
        }
      }
    }
  }

  // close registry key
  RegCloseKey (aFontsKey);

#else

  NCollection_Map<TCollection_AsciiString> aMapOfFontsDirs;
  const OSD_Protection aProtectRead (OSD_R, OSD_R, OSD_R, OSD_R);

  // read fonts directories from font service config file (obsolete)
  for (Standard_Integer anIter = 0; myFontServiceConf[anIter] != NULL; ++anIter)
  {
    const TCollection_AsciiString aFileOfFontsPath (myFontServiceConf[anIter]);
    OSD_File aFile (aFileOfFontsPath);
    if (!aFile.Exists())
    {
      continue;
    }

    aFile.Open (OSD_ReadOnly, aProtectRead);
    if (!aFile.IsOpen())
    {
      continue;
    }

    Standard_Integer aNByte = 256;
    Standard_Integer aNbyteRead;
    TCollection_AsciiString aStr; // read string with information
    while (!aFile.IsAtEnd())
    {
      Standard_Integer aLocation = -1;
      Standard_Integer aPathLocation = -1;

      aFile.ReadLine (aStr, aNByte, aNbyteRead); // reading 1 line (256 bytes)
      aLocation = aStr.Search ("catalogue=");
      if (aLocation < 0)
      {
        aLocation = aStr.Search ("catalogue =");
      }

      aPathLocation = aStr.Search ("/");
      if (aLocation > 0 && aPathLocation > 0)
      {
        aStr = aStr.Split (aPathLocation - 1);
        TCollection_AsciiString aFontPath;
        Standard_Integer aPathNumber = 1;
        do
        {
          // Getting directory paths, which can be splitted by "," or ":"
          aFontPath = aStr.Token (":,", aPathNumber);
          aFontPath.RightAdjust();
          if (!aFontPath.IsEmpty())
          {
            OSD_Path aPath(aFontPath);
            addDirsRecursively (aPath, aMapOfFontsDirs);
          }
          aPathNumber++;
        }
        while (!aFontPath.IsEmpty());
      }
    }
    aFile.Close();
  }

  // append default directories
  for (Standard_Integer anIter = 0; myDefaultFontsDirs[anIter] != NULL; ++anIter)
  {
    Standard_CString anItem = myDefaultFontsDirs[anIter];
    TCollection_AsciiString aPathStr (anItem);
    OSD_Path aPath (aPathStr);
    addDirsRecursively (aPath, aMapOfFontsDirs);
  }

  NCollection_Map<TCollection_AsciiString> aSupportedExtensions;
  for (Standard_Integer anIter = 0; Font_FontMgr_Extensions[anIter] != NULL; ++anIter)
  {
    Standard_CString anExt = Font_FontMgr_Extensions[anIter];
    aSupportedExtensions.Add (TCollection_AsciiString (anExt));
  }

  FT_Init_FreeType (&aFtLibrary);
  for (NCollection_Map<TCollection_AsciiString>::Iterator anIter (aMapOfFontsDirs);
       anIter.More(); anIter.Next())
  {
    OSD_File aReadFile (anIter.Value() + "/fonts.dir");
    if (!aReadFile.Exists())
    {
      continue; // invalid fonts directory
    }

    aReadFile.Open (OSD_ReadOnly, aProtectRead);
    if (!aReadFile.IsOpen())
    {
      continue; // invalid fonts directory
    }

    Standard_Integer aNbyteRead, aNByte = 256;
    TCollection_AsciiString aLine (aNByte);
    Standard_Boolean isFirstLine = Standard_True;
    const TCollection_AsciiString anEncoding ("iso8859-1\n");
    while (!aReadFile.IsAtEnd())
    {
      aReadFile.ReadLine (aLine, aNByte, aNbyteRead);
      if (isFirstLine)
      {
        // first line contains the number of fonts in this file
        // just ignoring it...
        isFirstLine = Standard_False;
        continue;
      }

      Standard_Integer anExtensionPosition = aLine.Search (".") + 1;
      if (anExtensionPosition == 0)
      {
        continue; // can't find extension position in the font description
      }

      Standard_Integer anEndOfFileName = aLine.Location (" ", anExtensionPosition, aLine.Length()) - 1;
      if (anEndOfFileName < 0 || anEndOfFileName < anExtensionPosition)
      {
        continue; // font description have empty extension
      }

      TCollection_AsciiString aFontExtension = aLine.SubString (anExtensionPosition, anEndOfFileName);
      aFontExtension.LowerCase();
      if (aSupportedExtensions.Contains (aFontExtension) && (aLine.Search (anEncoding) > 0))
      {
        // In current implementation use fonts with ISO-8859-1 coding page.
        // OCCT not give to manage coding page by means of programm interface.
        // TODO: make high level interface for choosing necessary coding page.
        Handle(TCollection_HAsciiString) aXLFD =
          new TCollection_HAsciiString (aLine.SubString (anEndOfFileName + 2, aLine.Length()));
        Handle(TCollection_HAsciiString) aFontPath =
          new TCollection_HAsciiString (anIter.Value().ToCString());
        if (aFontPath->SearchFromEnd ("/") != aFontPath->Length())
        {
          aFontPath->AssignCat ("/");
        }
        Handle(TCollection_HAsciiString) aFontFileName =
        new TCollection_HAsciiString (aLine.SubString (1, anEndOfFileName));
        aFontPath->AssignCat (aFontFileName);

        Handle(Font_SystemFont) aNewFontFromXLFD = new Font_SystemFont (aXLFD, aFontPath);
        Handle(Font_SystemFont) aNewFont = checkFont (aFtLibrary, aFontPath->ToCString());

        if (aNewFontFromXLFD->IsValid() && !aNewFont.IsNull() &&
           !aNewFont->IsEqual (aNewFontFromXLFD))
        {
          myListOfFonts.Append (aNewFont);
          myListOfFonts.Append (aNewFontFromXLFD);
        }
        else if (!aNewFont.IsNull())
        {
          myListOfFonts.Append (aNewFont);
        }
        else if (aNewFontFromXLFD->IsValid())
        {
          myListOfFonts.Append (aNewFontFromXLFD);
        }

      }
    }
    aReadFile.Close();
  }
#endif
  FT_Done_FreeType (aFtLibrary);
}

// =======================================================================
// function : GetAvailableFonts
// purpose  :
// =======================================================================
const Font_NListOfSystemFont& Font_FontMgr::GetAvailableFonts() const
{
  return myListOfFonts;
}

void Font_FontMgr::GetAvailableFontsNames (TColStd_SequenceOfHAsciiString& theFontsNames) const
{
  theFontsNames.Clear();
  for (Font_NListOfSystemFont::Iterator anIter(myListOfFonts); anIter.More(); anIter.Next())
  {
    theFontsNames.Append (anIter.Value()->FontName());
  }
}

Handle(Font_SystemFont) Font_FontMgr::GetFont (const Handle(TCollection_HAsciiString)& theFontName,
                                               const Font_FontAspect theFontAspect,
                                               const Standard_Integer theFontSize) const
{
  if ( (theFontSize < 2 && theFontSize != -1) || theFontName.IsNull())
  {
    return NULL; 
  }

  Font_NListOfSystemFont::Iterator aFontsIterator (myListOfFonts);

  for (; aFontsIterator.More(); aFontsIterator.Next())
  {
    if (!theFontName->IsEmpty() && !aFontsIterator.Value()->FontName()->IsSameString (theFontName, Standard_False))
    {
      continue;
    }

    if (theFontAspect != Font_FA_Undefined && aFontsIterator.Value()->FontAspect() != theFontAspect)
    {
      continue;
    }

    if (theFontSize == -1 || aFontsIterator.Value()->FontHeight() == -1 ||
        theFontSize == aFontsIterator.Value()->FontHeight())
    {
      return aFontsIterator.Value();
    }
  }

  return NULL;
}

Handle(Font_SystemFont) Font_FontMgr::FindFont (const Handle(TCollection_HAsciiString)& theFontName,
                                                const Font_FontAspect theFontAspect,
                                                const Standard_Integer theFontSize) const
{
  Handle(TCollection_HAsciiString) aFontName   = theFontName;
  Font_FontAspect                  aFontAspect = theFontAspect;
  Standard_Integer                 aFontSize = theFontSize;

  Handle(Font_SystemFont) aFont = GetFont (aFontName, aFontAspect, aFontSize);

  if (!aFont.IsNull())
  {
    return aFont;
  }

  // Trying to use font names mapping
  for (Standard_Integer anIter = 0; anIter < NUM_FONT_ENTRIES; ++anIter)
  {
    Handle(TCollection_HAsciiString) aFontAlias =
      new TCollection_HAsciiString (Font_FontMgr_MapOfFontsAliases[anIter].EnumName);

    if (aFontAlias->IsSameString (aFontName, Standard_False))
    {
      aFontName = new TCollection_HAsciiString (Font_FontMgr_MapOfFontsAliases[anIter].FontName);
      aFontAspect = Font_FontMgr_MapOfFontsAliases[anIter].FontAspect;
      break;
    }
  }

  aFont = GetFont (aFontName, aFontAspect, aFontSize);

  if (!aFont.IsNull())
  {
    return aFont;
  }

  // Requested family name not found -> search for any font family with given aspect and height
  aFontName = new TCollection_HAsciiString ("");
  aFont = GetFont (aFontName, aFontAspect, aFontSize);

  if (!aFont.IsNull())
  {
    return aFont;
  }

  // The last resort: trying to use ANY font available in the system
  aFontAspect = Font_FA_Undefined;
  aFontSize = -1;
  aFont = GetFont (aFontName, aFontAspect, aFontSize);
  
  if (!aFont.IsNull())
  {
    return aFont;
  }

  return NULL; // Fonts are not found in the system.
}
