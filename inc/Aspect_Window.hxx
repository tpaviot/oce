// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Aspect_Window_HeaderFile
#define _Aspect_Window_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_Aspect_Window_HeaderFile
#include <Handle_Aspect_Window.hxx>
#endif

#ifndef _Handle_Aspect_GraphicDevice_HeaderFile
#include <Handle_Aspect_GraphicDevice.hxx>
#endif
#ifndef _Aspect_Background_HeaderFile
#include <Aspect_Background.hxx>
#endif
#ifndef _TCollection_AsciiString_HeaderFile
#include <TCollection_AsciiString.hxx>
#endif
#ifndef _Aspect_FillMethod_HeaderFile
#include <Aspect_FillMethod.hxx>
#endif
#ifndef _Aspect_Handle_HeaderFile
#include <Aspect_Handle.hxx>
#endif
#ifndef _Aspect_GradientBackground_HeaderFile
#include <Aspect_GradientBackground.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _MMgt_TShared_HeaderFile
#include <MMgt_TShared.hxx>
#endif
#ifndef _Quantity_NameOfColor_HeaderFile
#include <Quantity_NameOfColor.hxx>
#endif
#ifndef _Standard_CString_HeaderFile
#include <Standard_CString.hxx>
#endif
#ifndef _Aspect_TypeOfResize_HeaderFile
#include <Aspect_TypeOfResize.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Quantity_Ratio_HeaderFile
#include <Quantity_Ratio.hxx>
#endif
#ifndef _Quantity_Parameter_HeaderFile
#include <Quantity_Parameter.hxx>
#endif
class Aspect_GraphicDevice;
class Aspect_WindowDefinitionError;
class Aspect_WindowError;
class Aspect_Background;
class Quantity_Color;
class Aspect_GradientBackground;


//! This class allows the definition of a window <br>
//! Warning: The position and size for the creation of the window <br>
//!          are defined in Device Screen Unit (DSU) <br>
//!          floating [0,1] space. <br>
class Aspect_Window : public MMgt_TShared {

public:

  //! Modifies the window background. <br>
  Standard_EXPORT   virtual  void SetBackground(const Aspect_Background& ABack)  = 0;
  //! Modifies the window background from a Named Color. <br>
  Standard_EXPORT   virtual  void SetBackground(const Quantity_NameOfColor BackColor)  = 0;
  //! Modifies the window background. <br>
  Standard_EXPORT   virtual  void SetBackground(const Quantity_Color& color)  = 0;
  //! Loads the window background from an image file <aName> <br>
//! defined with a supported format XWD,GIF or BMP <br>
//! and returns TRUE if the operation is successfull. <br>
  Standard_EXPORT   virtual  Standard_Boolean SetBackground(const Standard_CString aName,const Aspect_FillMethod aMethod = Aspect_FM_CENTERED)  = 0;
  //! Loads the window background from a predefined bitmap. <br>
//!  Warning: the bitmap and window must have the same depth. <br>
  Standard_EXPORT   virtual  void SetBackground(const Aspect_Handle aBitmap)  = 0;
  //! Modifies the window gradient background. <br>
  Standard_EXPORT   virtual  void SetBackground(const Aspect_GradientBackground& ABackground)  = 0;
  //! Activates/Deactivates the Double Buffering capability <br>
//!          for this window. <br>
//!  Warning: Double Buffering is always DISABLE by default <br>
//!          If there is not enought ressources to activate the <br>
//!          double-buffering the DB mode flag can be set to FALSE. <br>
  Standard_EXPORT   virtual  void SetDoubleBuffer(const Standard_Boolean DBmode)  = 0;
  //! Flushs all graphics to the screen and Swap the Double <br>
//!          buffer if Enable <br>
  Standard_EXPORT   virtual  void Flush() const = 0;
  //! Opens the window <me>. <br>
  Standard_EXPORT   virtual  void Map() const = 0;
  //! Closes the window <me>. <br>
  Standard_EXPORT   virtual  void Unmap() const = 0;
  //! Apply the resizing to the window <me>. <br>
  Standard_EXPORT   virtual  Aspect_TypeOfResize DoResize() const = 0;
  //! Apply the mapping change to the window <me>. <br>
//! and returns TRUE if the window is mapped at screen. <br>
  Standard_EXPORT   virtual  Standard_Boolean DoMapping() const = 0;
  //! Destroy the Window <br>
  Standard_EXPORT   virtual  void Destroy()  = 0;
  //! Clear The Window in the Background Color <br>
  Standard_EXPORT   virtual  void Clear() const = 0;
  //! Clear The Window Area defined in PIXELS <br>
//!	    in the Background Color <br>
  Standard_EXPORT   virtual  void ClearArea(const Standard_Integer XCenter,const Standard_Integer YCenter,const Standard_Integer Width,const Standard_Integer Height) const = 0;
  //! Restore the BackingStored Window <me>. <br>
  Standard_EXPORT   virtual  void Restore() const = 0;
  //! Restore the BackingStored Window Area <br>
//!	    defined in PIXELS. <br>
  Standard_EXPORT   virtual  void RestoreArea(const Standard_Integer XCenter,const Standard_Integer YCenter,const Standard_Integer Width,const Standard_Integer Height) const = 0;
  //! Dumps the Window to an image file (PNG, BMP, JPEG, GIF) with <br>
  Standard_EXPORT   virtual  Standard_Boolean Dump(const Standard_CString aFilename,const Standard_Real aGammaValue = 1.0) const = 0;
  //! Dumps the Window Area defined by his center and PIXEL size <br>
//! to an image file with <br>
//! an optional gamma correction value according to the graphic system <br>
  Standard_EXPORT   virtual  Standard_Boolean DumpArea(const Standard_CString aFilename,const Standard_Integer Xc,const Standard_Integer Yc,const Standard_Integer Width,const Standard_Integer Height,const Standard_Real aGammaValue = 1.0) const = 0;
  //! Loads the XWD file to this Window. <br>
//! Returns TRUE if the loading occurs normaly. <br>
//!  Warning: Note that the Window is enlarged automatically <br>
  Standard_EXPORT   virtual  Standard_Boolean Load(const Standard_CString aFilename) const = 0;
  //! Loads the XWD file to Window Area defined by his center <br>
  Standard_EXPORT   virtual  Standard_Boolean LoadArea(const Standard_CString aFilename,const Standard_Integer Xc,const Standard_Integer Yc,const Standard_Integer Width,const Standard_Integer Height) const = 0;
  //! Returns the window background. <br>
  Standard_EXPORT     Aspect_Background Background() const;
  //! Returns the current image background string <br>
//! or NULL if nothing is defined. <br>
  Standard_EXPORT     Standard_CString BackgroundImage() const;
  //! Returns the current image background fill mode. <br>
  Standard_EXPORT     Aspect_FillMethod BackgroundFillMethod() const;
  //! Returns the window gradient background. <br>
  Standard_EXPORT     Aspect_GradientBackground GradientBackground() const;
  //! Returns the background bitmap handle or <br>
//! 0 when nothing is defined <br>
        Aspect_Handle HBackground() const;
  //! Returns the Graphic Device associated to this Window. <br>
  Standard_EXPORT     Handle_Aspect_GraphicDevice GraphicDevice() const;
  //! Returns True if the window <me> is opened <br>
//!	    and False if the window is closed. <br>
  Standard_EXPORT   virtual  Standard_Boolean IsMapped() const = 0;
  //! Returns True if the window <me> is virtual <br>
  Standard_EXPORT     Standard_Boolean IsVirtual() const;
  //! Setup the virtual state <br>
  Standard_EXPORT     void SetVirtual(const Standard_Boolean theVirtual) ;
  //! Returns The Window RATIO equal to the physical <br>
//!	    WIDTH/HEIGHT dimensions <br>
  Standard_EXPORT   virtual  Quantity_Ratio Ratio() const = 0;
  //! Returns The Window POSITION in DSU <br>
  Standard_EXPORT   virtual  void Position(Quantity_Parameter& X1,Quantity_Parameter& Y1,Quantity_Parameter& X2,Quantity_Parameter& Y2) const = 0;
  //! Returns The Window POSITION in PIXEL <br>
  Standard_EXPORT   virtual  void Position(Standard_Integer& X1,Standard_Integer& Y1,Standard_Integer& X2,Standard_Integer& Y2) const = 0;
  //! Returns The Window SIZE in DSU <br>
  Standard_EXPORT   virtual  void Size(Quantity_Parameter& Width,Quantity_Parameter& Height) const = 0;
  //! Returns The Window SIZE in PIXEL <br>
  Standard_EXPORT   virtual  void Size(Standard_Integer& Width,Standard_Integer& Height) const = 0;
  //! Returns The Window SIZE in MM <br>
  Standard_EXPORT   virtual  void MMSize(Standard_Real& Width,Standard_Real& Height) const = 0;
  //! Returns the DSU value depending of the PIXEL value. <br>
  Standard_EXPORT   virtual  Quantity_Parameter Convert(const Standard_Integer PV) const = 0;
  //! Returns the PIXEL value depending of the DSU value. <br>
  Standard_EXPORT   virtual  Standard_Integer Convert(const Quantity_Parameter DV) const = 0;
  //! Returns the DSU position depending of the PIXEL position. <br>
  Standard_EXPORT   virtual  void Convert(const Standard_Integer PX,const Standard_Integer PY,Quantity_Parameter& DX,Quantity_Parameter& DY) const = 0;
  //! Returns the PIXEL position depending of the DSU position. <br>
  Standard_EXPORT   virtual  void Convert(const Quantity_Parameter DX,const Quantity_Parameter DY,Standard_Integer& PX,Standard_Integer& PY) const = 0;
  //! Returns the BackingStore capability for this Window . <br>
//!          If Answer is True Exposure can be recovered by <br>
//!          Restore RestoreArea methods . <br>
//!          If Answer is False,Application must Redraw <br>
//!	    the exposed area. <br>
  Standard_EXPORT   virtual  Standard_Boolean BackingStore() const = 0;
  //! Returns the DoubleBuffer state. <br>
  Standard_EXPORT   virtual  Standard_Boolean DoubleBuffer() const = 0;




  DEFINE_STANDARD_RTTI(Aspect_Window)

protected:

  //! Initializes the datas of a Window. <br>
  Standard_EXPORT   Aspect_Window(const Handle(Aspect_GraphicDevice)& aGraphicDevice);

Handle_Aspect_GraphicDevice MyGraphicDevice;
Aspect_Background MyBackground;
TCollection_AsciiString MyBackgroundImage;
Aspect_FillMethod MyBackgroundFillMethod;
Aspect_Handle MyHBackground;
Aspect_GradientBackground MyGradientBackground;
Standard_Boolean MyIsVirtual;


private: 




};


#include <Aspect_Window.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
