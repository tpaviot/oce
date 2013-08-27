#include <winresrc.h>

#cmakedefine OCE_VERSION_PATCH
#define OCE_VERSION_PATCH_VAL @OCE_VERSION_PATCH@

/* If patch is not defined at project level, here is defined to 0 */
#ifndef OCE_VERSION_PATCH
#undef OCE_VERSION_PATCH_VAL
#define OCE_VERSION_PATCH_VAL 0
#endif

/* Stringify OCE_VERSION_PATCH */
#define QU(x) #x
#define QUH(x) QU(x)
#define OCE_VERSION_PATCH_STR QUH(OCE_VERSION_PATCH_VAL)

VS_VERSION_INFO VERSIONINFO
  FILEVERSION @OCE_VERSION_MAJOR@,@OCE_VERSION_MINOR@,OCE_VERSION_PATCH_VAL,0
  PRODUCTVERSION @OCE_VERSION_MAJOR@,@OCE_VERSION_MINOR@,OCE_VERSION_PATCH_VAL,0
  FILEFLAGSMASK VS_FFI_FILEFLAGSMASK
#ifndef DEBUG
  FILEFLAGS 0
#else
  FILEFLAGS VER_DEBUG
#endif
  FILEOS VOS_NT_WINDOWS32

#cmakedefine OCE_BUILD_STATIC_LIB

#ifdef OCE_VERSION_INFO_IS_EXE
#ifdef OCE_BUILD_STATIC_LIB
  FILETYPE VFT_STATIC_LIB
#else
  FILETYPE VFT_DLL
#endif
#else
  FILETYPE VFT_APP
#endif

  FILESUBTYPE VFT2_UNKNOWN
  BEGIN
    BLOCK "StringFileInfo"
    BEGIN
      BLOCK "04090000"
      BEGIN
        VALUE "FileDescription", "OpenCascade Community Edition"
        VALUE "FileVersion", "@OCE_VERSION_MAJOR@.@OCE_VERSION_MINOR@." OCE_VERSION_PATCH_STR
        VALUE "InternalName", "OCE"
        VALUE "LegalCopyright", ""
        VALUE "OriginalFilename", ""
        VALUE "ProductName", "OCE"
        VALUE "ProductVersion", "@OCE_VERSION_MAJOR@.@OCE_VERSION_MINOR@." OCE_VERSION_PATCH_STR
      END
    END
    BLOCK "VarFileInfo"
    BEGIN
      VALUE "Translation", 0x409, 1200
    END
  END
  
