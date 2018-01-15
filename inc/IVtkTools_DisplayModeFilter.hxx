// Created on: 2011-11-15
// Created by: Roman KOZLOV
// Copyright (c) 2011-2014 OPEN CASCADE SAS 
// 
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef IVtkTOOLS_DISPLAYMODEFILTER_H
#define IVtkTOOLS_DISPLAYMODEFILTER_H

#include <IVtkTools.hxx>
#include <IVtkTools_SubPolyDataFilter.hxx>
#include <IVtk_Types.hxx>
#include <NCollection_DataMap.hxx>

//! @class IVtkTools_DisplayModeFilter 
//! @brief Cells filter according to the selected display mode by mesh parts types.
//! This filter is used to get parts of a shape according to different 
//! display modes.
class Standard_EXPORT IVtkTools_DisplayModeFilter : public IVtkTools_SubPolyDataFilter
{
public:
  vtkTypeMacro(IVtkTools_DisplayModeFilter,IVtkTools_SubPolyDataFilter);
  static IVtkTools_DisplayModeFilter *New();
  void PrintSelf (std::ostream& os, vtkIndent indent);

  //! Set display mode to define cells types to be passed through this filter.
  void SetDisplayMode (const IVtk_DisplayMode aMode);

  //! Display or not shared vertices.
  void SetDisplaySharedVertices (const bool doDisplay);

  //! Get current display mode.
  const IVtk_DisplayMode GetDisplayMode() const;

protected:
  //! Filter cells according to the given set of ids.
  virtual int RequestData (vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  IVtkTools_DisplayModeFilter();
  ~IVtkTools_DisplayModeFilter();  

protected:
  //! Display mode defining mesh types to pass through this filter.
  IVtk_DisplayMode                                      myDisplayMode;
  NCollection_DataMap<IVtk_DisplayMode, IVtk_IdTypeMap> myModesDefinition;
  bool                                                  myDoDisplaySharedVertices;
};

#endif // IVtkTOOLS_DISPLAYMODEFILTER_H

