// Created on: 2007-07-06
// Created by: Alexander GRIGORIEV
// Copyright (c) 2007-2014 OPEN CASCADE SAS
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

#ifndef NIS_InteractiveContext_HeaderFile
#define NIS_InteractiveContext_HeaderFile

#ifdef __BORLANDC__
# include <NIS_InteractiveObject.hxx>
# include <NIS_View.hxx>
#else
# include <Handle_NIS_InteractiveObject.hxx>
# include <Handle_NIS_View.hxx>
#endif
#include <NCollection_Map.hxx>
#include <NCollection_SparseArray.hxx>
#include <NIS_Allocator.hxx>
#include <NIS_Drawer.hxx>
#include <NIS_SelectFilter.hxx>

// undefine WinAPI macros
#ifdef GetObject
  #undef GetObject
#endif

class NIS_View;
class Bnd_B3f;
class Bnd_B2f;

/**
 * InteractiveContext is the central NIS structure that stores and manages
 * all NIS_InteractiveObject instances as well as the Drawers for their visualisation.
 * There may be one or more Views referred by an InteractiveContext instance.
 * Also there may be one or more InteractiveContext instances referring the same View.
 * However the latter case is not typical (see NIS_View description).
 * To add or remove a View in a Context, use methods AttachView() and DetachView().
 *
 * @section nis_interactivecontext_mgtobjects Management of objects
 * The main purpose of class NIS_InteractiveContext is allocation and
 * management of NIS_InteractiveObject instances.
 * <p>An InteractiveObject should be added to the Context by a call to method
 * Display() or DisplayOnTop(). After that (not before) it becomes possible to:
 * <ul>
 * <li>change the presentation of the InteractiveObject (e.g., modify the color)</li>
 * <li>make the InteractiveObject visible or invisible, selectable or unselectable;</li>
 * <li>set Transparency;</li>
 * <li>select InteractiveObject interactively, including the hilighting and the dynamic hilighting.</li>
 * </ul>
 * Methods that add/remove/display/hide NIS_InteractiveObject instances have
 * the optional parameter 'isUpdateViews'. When it is set to True (default),
 * the modification of the object brings about an immediate update of its
 * presentation (the corresponding Drawer flagged to recompute presentations).
 * Normally you do not have to worry about this parameter leaving it assigned to
 * the default value; use the alternative value 'Standard_False' only for
 * very special purposes, like animation -- when many updates should be
 * synchronized in time. For other methods like changing the transparency or
 * color definition there is no parameter 'isUpdateViews', all changes mark
 * the corresponding drawers immediately. 
 * <p>Typical scheme of usage:
 * @code
 *   const Handle(NIS_InteractiveContext) aContext = new NIS_InteractiveContext;
 *   const Handle(NIS_View) aView = new NIS_View(...);
 *   aContext->AttachView (aView);
 *   ....
 *   for (; ;) {
 *     const Handle(MyIOClass) anObject = new MyIOClass();
 *     aContext->Display (anObject);
 *     anObject->SetColor(...);  // method of class MyIOClass
 *     ...
 *   }
 * @endcode
 * @section nis_interactivecontext_display Method Display()
 * This method performs three important tasks, when called the first time for
 * an object:
 * <ul>
 * <li>Copy its argument to the memory pool that is managed by the internal
 *     Allocator of NIS_InteractiveContext. Then <b>the new instance of
 *     object</b> is returned back in the same argument (in-out parameter);</li>
 * <li>Store the copied instance in the internal vector of objects, so that
 *     the displayed object receives its ID (sequential address in the vector);
 *     </li>
 * <li>Create a Drawer instance if necessary; attach the displayed interactive
 *     object to this instance (or to a relevant and already existing Drawer)
 *     </li>
 * </ul>
 * Thus any methods dealing with Drawer-related properties like color, line
 * width, polygon offset, etc. can only be called following the necessary call
 * of method Display().
 * <p>
 * Subsequent calls to Display() just revert previous calls of Erase() without
 * any re-initialization of interactive object or its drawer.
 *
 * @section nis_interactivecontext_memory Using the memory
 * As described in the sections above, all interactive objects should completely
 * reside in the special memory pool managed by the InteractiveContext instance.
 * This is a fast memory (NCollection_IncAllocator is used) but it has the
 * drawback: when you destroy an object using method Remove() it is detached
 * from NIS_InteractiveContext and its presentation is removed from all Views.
 * But the memory allocated for that removed object is not released and it
 * cannot be reused by new interactive objects. In time there may appear too
 * many "dead" objects to hinder or even crash the application.
 * <p>
 * This problem is resolved by automatic keeping the record of the total size
 * of both  used and unused memory, in the instance of NIS_Allocator. When the
 * amount of unused memory becomes too big then the method compactObjects() 
 * creates a new NIS_Allocator instance and copies there all interactive
 * objects that are 'alive' then releasing the previous memory pool. All
 * object IDs and their drawers remain intact, so nothing is changed except
 * the greater amount of available memory in the system.
 * <p>
 * This mechanism works when either UpdateViews() or RebuildViews() is called
 * from time to time, only these two methods can call compactObjects().
 */

class NIS_InteractiveContext : public Standard_Transient
{
 public:
  typedef enum {
    Mode_NoSelection = 0,       ///< Seelction is totally disabled
    Mode_Normal,                ///< Selected are added to or removed from list
    Mode_Additive,              ///< Selected are added to the list of selected
    Mode_Exclusive              ///< Selected are removed from the list
  } SelectionMode;

 public:
  // ---------- PUBLIC METHODS ----------


  /**
   * Empty constructor.
   */
  Standard_EXPORT NIS_InteractiveContext ();

  /**
   * Destructor.
   */
  Standard_EXPORT virtual ~NIS_InteractiveContext ();

  ///@name Management of Views
  //@{
  /**
   * Associate this Context with the given View.
   */
  Standard_EXPORT void AttachView (const Handle(NIS_View)& theView);

  /**
   * Stop the association of the Context with the given View.
   */
  Standard_EXPORT void DetachView (const Handle(NIS_View)& theView);
  //@}

  /**
   * Query the InteractiveObject instance by its ID.
   */
  Standard_EXPORT const Handle(NIS_InteractiveObject)&
                       GetObject  (const Standard_Integer theID) const;

  /**
   * Query the total number of InteractiveObject instances. This number can be
   * smaller than the greatest object ID, therefore you should not iterate till
   * this number using GetObject; use class NIS_ObjectsIterator instead.
   */
  inline Standard_Integer
                       NbObjects  ()
//  { return myObjects.Length()-1; }
  { return (myMapObjects[0].Extent() + myMapObjects[1].Extent() +
            myMapObjects[2].Extent()) + myMapObjects[3].Extent(); }

  /**
   * Query the total number of Drawers instances.
   */
  inline Standard_Integer
                       NbDrawers  ()
  { return myDrawers.Size(); }

  /**
   * Access to Drawers, can be used for specific operations where it is not
   * desirale to iterate InteractiveObjects.
   */
  inline NCollection_Map<Handle(NIS_Drawer)>::Iterator
                        GetDrawers () const
  { return NCollection_Map<Handle(NIS_Drawer)>::Iterator(myDrawers); }

  // ================ BEGIN Mangement of Objects ================
  ///@name Management of Objects
  //@{

  /**
   * Make the given interactive object visible in the current context.
   * If the object is not yet added to this context, it is added. Therefore
   * this method should follow the creation of an InteractiveObject instance
   * before it can be displayed.
   * @param theObj
   *   <tt>[in/out]</tt>Interactive object instance. If the object is displayed
   *   for the first time then the output value will be a new (cloned) object.
   * @param theDrawer
   *   If this parameter is NULL, the default drawer is used for theObj, defined
   *   by the object type. Otherwise the given Drawer (must be present in this
   *   context) is used for theObj. Use the parameter to change the presentation
   *   of theObj.
   * @param isUpdateViews
   *   If True, the drawer receives isUpdate flag, then it will recompute
   *   the presentations when Redraw event happens. You can leave the parameter
   *   to False if you have to make a number of similar calls, then you would
   *   call UpdateViews() in the end.
   */
  Standard_EXPORT void Display    (Handle(NIS_InteractiveObject)& theObj,
                                   const Handle(NIS_Drawer)& theDrawer = NULL,
                                   const Standard_Boolean isUpdateViews
                                                        = Standard_True);

  /**
   * Make the given interactive object visible on top of other objects in
   * the current context.
   * If the object is not yet added to this context, it is added. Therefore
   * this method should follow the creation of an InteractiveObject instance
   * before it can be displayed.
   * @param theObj
   *   Interactive object instance.
   * @param theDrawer
   *   If this parameter is NULL, the default drawer is used for theObj, defined
   *   by the object type. Otherwise the given Drawer (must be present in this
   *   context) is used for theObj. Use the parameter to change the presentation
   *   of theObj.
   * @param isUpdateViews
   *   If True, the drawer receives isUpdate flag, then it will recompute
   *   the presentations when Redraw event happens. You can leave the parameter
   *   to False if you have to make a number of similar calls, then you would
   *   call UpdateViews() in the end.
   */
  Standard_EXPORT void DisplayOnTop (Handle(NIS_InteractiveObject)& theObj,
                                     const Handle(NIS_Drawer)& theDrawer = NULL,
                                     const Standard_Boolean isUpdateViews
                                                          = Standard_True);

  /**
   * Make the given object invisible in the current InteractiveContext.
   * @param theObj
   *   Interactive object instance. Must be already added to this context.
   * @param isUpdateViews
   *   If True, the drawer receives isUpdate flag, then it will recompute
   *   the presentations when Redraw event happens. You can leave the parameter
   *   to False if you have to make a number of similar calls, then you would
   *   call UpdateViews() in the end.
   */   
  Standard_EXPORT void Erase      (const Handle(NIS_InteractiveObject)& theObj,
                                   const Standard_Boolean isUpdateViews
                                                        = Standard_True);

  /**
   * Remove the given object from its Interactive context.
   * @param theObj
   *   Interactive object instance. Must be already added to this context.
   * @param isUpdateViews
   *   If True, the drawer receives isUpdate flag, then it will recompute
   *   the presentations when Redraw event happens. You can leave the parameter
   *   to False if you have to make a number of similar calls, then you would
   *   call UpdateViews() in the end.
   */   
  Standard_EXPORT void Remove     (const Handle(NIS_InteractiveObject)& theObj,
                                   const Standard_Boolean isUpdateViews
                                                        = Standard_True);

  /**
   * Make all stored InteractiveObject instances visible, equivalent to
   * calling method Display() for all contained objects.
   */
  Standard_EXPORT void DisplayAll ();

  /**
   * Make all stored InteractiveObject instances invisible, equivalent to
   * calling method Erase() for all contained objects.
   */
  Standard_EXPORT void EraseAll   ();

  /**
   * Clean the context of its contained objects. Drawers are destroyed
   * and all presentations become empty.
   */
  Standard_EXPORT void RemoveAll  ();

  /**
   * This method signals that the presenation should be refreshed in all updated
   * Drawers and in all Views. Calls Redraw() of each view from inside.
   */
  Standard_EXPORT void UpdateViews ();

  /**
   * Similar to UpdateViews but forces all presentations to be rebuilt whether
   * the drawers are marked as updated or not.
   */
  Standard_EXPORT void RebuildViews();

  /**
   * Find the bounding box of all Objects displayed (visible) in the given View.
   * @param theBox
   *   <tt>[out]</tt> Bounding box, updated (not reinitialized!) by the object
   *   boxes.
   * @param theView
   *   View instance where the objects are displayed.
   */
  Standard_EXPORT void GetBox     (Bnd_B3f&         theBox,
                                   const NIS_View * theView) const;

  //@}
  // ================ END Mangement of Objects ================

  // ================ BEGIN Selection API ================
  ///@name Selection API
  //@{

  /**
   * Query the current selection filter. Use the method SetFilter to install it.
   * By default returns a NULL handle.
   */
  inline const Handle(NIS_SelectFilter)&
                        GetFilter   () const
  { return mySelectFilter; }

  /**
   * Install a selection filter.
   */
  inline void           SetFilter   (const Handle(NIS_SelectFilter)& theFilter)
  { mySelectFilter = theFilter; }

  /**
   * Query the current selection mode.
   */
  inline SelectionMode  GetSelectionMode () const
  { return mySelectionMode; }

  /**
   * Set the selection mode.
   */
  inline void           SetSelectionMode (const SelectionMode theMode)
  { mySelectionMode = theMode; }

  /**
   * Set or unset the selected state of the object, also changing its hilight status.
   * If mySelectionMode == Mode_NoSelection this method does nothing (returns False always).
   * If the given object is NULL (e.g., if the mouse was clicked on empty area),
   * then the current selection is cleared (modes Normal and Additive only).
   * The selection algorithm with respect to the given object is defined by the current selection mode:
   * <ul>
   * <li>Mode_Normal    - the selection state is toggled</li>
   * <li>Mode_Additive  - the object is always added to the selection</li>
   * <li>Mode_Exclusive - the object is always removed from the selection</li>
   * </ul>
   * This method does not update the views.
   * @param O
   *   Object to be selected or deselected
   * @param isMultiple
   *   If True, then the objects are not automatically deselected.
   * @return
   *   True if the selection status has been changed, False if nothing changed
   */
  Standard_EXPORT Standard_Boolean
                        ProcessSelection(const Handle(NIS_InteractiveObject)& O,
                                         const Standard_Boolean     isMultiple
                                            = Standard_False);

  /**
   * Process the selection of multiple objects. Equivalent to the other
   * ProcessSelection method, on a set of objects. Particularly, the current
   * selection mode is respected.
   * @param map
   *   Container of IDs of objects to be processed
   * @param isMultiple
   *   If True, then the objects are not automatically deselected.
   */
  Standard_EXPORT void  ProcessSelection(const TColStd_PackedMapOfInteger& map,
                                         const Standard_Boolean     isMultiple
                                            = Standard_False);

  /**
   * Set or unset the selected state of the object, also changing its hilight status.
   * This method does not update the views.
   * @param theObj
   *   Object to be selected or deselected
   * @param isSelected
   *   true if the object should be selected, False - if deselected.
   * @return
   *   True if the selection status has been changed, False if noithing changed
   */
  Standard_EXPORT Standard_Boolean
                        SetSelected (const Handle(NIS_InteractiveObject)& theObj,
                                     const Standard_Boolean isSelected
                                                = Standard_True);

  /**
   * Set the selection. Previously selected objects are deselected if they
   * are not included in the given map.
   * @param map
   *   Container of IDs of objects to be selected
   * @param isAdded
   *   If True, the given IDs are added to the current selection (nothing is
   *   deselected). If False (default) - the previous selection is forgotten.
   */
  Standard_EXPORT void  SetSelected     (const TColStd_PackedMapOfInteger& map,
                                         const Standard_Boolean isAdded
                                                = Standard_False);

  /**
   * Query if the given object is selected.
   */
  Standard_EXPORT Standard_Boolean
                        IsSelected  (const Handle(NIS_InteractiveObject)& theOb);

  /**
   * Reset all previous selection.
   */
  Standard_EXPORT void  ClearSelected   ();

  /**
   * Query the set of selected objects.
   * @return
   *   Map of integer IDs of objects.
   */
  inline const TColStd_PackedMapOfInteger&
                        GetSelected     ()
  { return myMapObjects[NIS_Drawer::Draw_Hilighted]; }

  /**
   * Define objects that can be selected by no means (isSelectable = false),
   * or make the objects selectable (isSelectable = true).
   * @param IDs
   *   Container of IDs of objects to be set as selectable or not selectable
   * @param isSelectable
   *   If False, the given IDs are made non-selectable by SetSelected methods,
   *   If True, the given IDs are made selectable.
   */
  Standard_EXPORT void  SetSelectable   (const TColStd_PackedMapOfInteger& IDs,
                                         const Standard_Boolean isSelectable);

  /**
   * Return True if the object can be selected (processing by SetSelected
   * methods), or False if can not be.
   * @return
   *   Selectable state of the object.
   */
  inline Standard_Boolean IsSelectable  (const Standard_Integer objID) const
  { return (myMapNonSelectableObjects.Contains( objID ) == Standard_False); }

  /**
   * Set or reset the flag that tells to NIS_Drawer to create shared DrawList.
   * The default mode (in Constructor) is True.
   */
  inline void             SetShareDrawList  (Standard_Boolean isShare)
  { myIsShareDrawList = isShare; }

  //@}
  // ====== END Selection API ================

 protected:
  //! Structure referencing one detected (picked) interactive entity.
  struct DetectedEnt
  {
    Standard_Real          Dist; //!< Distance on the view direction
    NIS_InteractiveObject* PObj; //!< Pointer to interactive object
  };

  // ---------- PROTECTED METHODS ----------

  Standard_EXPORT void redraw           (const Handle(NIS_View)&     theView,
                                         const NIS_Drawer::DrawType theType);

  /**
   * Detect the object selected by the given ray.
   * @param theSel
   *   <tt>[out]</tt> The selected object that has the lowest ray distance.
   * @param theDet
   *   <tt>[out]</tt> Sorted list of all detected objects with ray distances
   * @param theAxis
   *   Selection ray
   * @param theOver
   *   Thickness of the selecting ray
   * @param isOnlySelectable
   *   If False, any displayed object can be picked, otherwise only selectable
   *   ones.
   * @return
   *   The ray distance of the intersection point between the ray and theSel. 
   */
  Standard_EXPORT Standard_Real
                       selectObject     (Handle(NIS_InteractiveObject)& theSel,
                                         NCollection_List<DetectedEnt>& theDet,
                                         const gp_Ax1&                 theAxis,
                                         const Standard_Real           theOver,
                                         const Standard_Boolean isOnlySelectable
                                         = Standard_True) const;

  /**
   * Build a list of objects that are inside or touched by an oriented box.
   * @param mapObj
   *   <tt>[out]</tt> Container of object IDs, updated by detected objects.
   * @param theBox
   *   3D box of selection
   * @param theTrf
   *   Position/Orientation of the box (for box-box intersections)
   * @param theTrfInv
   *   Inverted Position/Orientation of the box (for box-object intersections)
   * @param isFullyIn
   *   True if only those objects are processed that are fully inside the
   *   selection rectangle. False if objects fully or partially included in
   *   the rectangle are processed. 
   * @return
   *   True if at least one object was selected.
   */
  Standard_EXPORT Standard_Boolean
                        selectObjects   (TColStd_PackedMapOfInteger& mapObj,
                                         const Bnd_B3f&        theBox,
                                         const gp_Trsf&        theTrf,
                                         const gp_Trsf&        theTrfInv,
                                         const Standard_Boolean isFullyIn)const;

  /**
   * Build a list of objects that are inside or touched by a polygon.
   * @param mapObj
   *   <tt>[out]</tt> Container of object IDs, updated by detected objects.
   * @param thePolygon
   *   the list of vertices of a free-form closed polygon without
   *   self-intersections. The last point should not coincide with the first
   *   point of the list. Any two neighbor points should not be confused.
   * @param thePolygonBox
   *   2D box of selection polygon
   * @param theTrfInv
   *   Inverted Position/Orientation of the plane where thePolygon is defined
   *   (for polygon-object intersections)
   * @param isFullyIn
   *   True if only those objects are processed that are fully inside the
   *   selection polygon. False if objects fully or partially included in
   *   the polygon are processed. 
   * @return
   *   True if at least one object was selected.
   */
  Standard_EXPORT Standard_Boolean
        selectObjects           (TColStd_PackedMapOfInteger    &mapObj,
                                 const NCollection_List<gp_XY> &thePolygon,
                                 const Bnd_B2f                 &thePolygonBox,
                                 const gp_Trsf                 &theTrfInv,
                                 const Standard_Boolean        isFullyIn) const;

private:
  void  deselectObj             (const Handle(NIS_InteractiveObject)&,
                                 const Standard_Integer);

  void  selectObj               (const Handle(NIS_InteractiveObject)&,
                                 const Standard_Integer);

  const Handle(NIS_Drawer)&
        drawerForDisplay        (const Handle(NIS_InteractiveObject)&,
                                 const Handle(NIS_Drawer)&);

  void  objectForDisplay        (Handle(NIS_InteractiveObject)&,
                                 const NIS_Drawer::DrawType);

  Handle(NIS_Allocator)
        compactObjects          ();

 private:
  // ---------- PRIVATE FIELDS ----------

  /**
   * Allocator for all data associated with objects.
   */
  Handle(NIS_Allocator)                              myAllocator;

  /**
   * The last added object ID.
   */
  Standard_Integer                                  myLastObjectId;
  /**
   * Container of InteractiveObject instances.
   */ 
  NCollection_SparseArray <Handle(NIS_InteractiveObject)>
                                                    myObjects;

  /**
   * List of Views.
   */
  NCollection_List   <Handle(NIS_View)>              myViews;

  /**
   * Container of Drawers. There should be one or more Drawers for each type of
   * contained InteractiveObject.
   */
  NCollection_Map    <Handle(NIS_Drawer)>            myDrawers;

  /**
   * Three maps indicating the state of contained objects:
   *  - #0 - normally presented objects
   *  - #1 - top objects
   *  - #2 - hilighted objects (i.e., selected)
   *  - #3 - transparent objects
   * Each object can have only one entry in these maps.
   */
  TColStd_PackedMapOfInteger                        myMapObjects[4];

  /**
   * Objects contained in this map are ignored by SetSelected methods,
   * these objects are not selectable.
   */
  TColStd_PackedMapOfInteger                        myMapNonSelectableObjects;

  /**
   * Instance of selection filter used for interactive selections.
   */
  Handle(NIS_SelectFilter)                           mySelectFilter;

  /**
   * Current mode of selection.
   */
  SelectionMode                                     mySelectionMode;

  /**
   * Flag that allows to use single draw list for all views.
   */
  Standard_Boolean                                  myIsShareDrawList;

  friend class NIS_View;
  friend class NIS_Drawer;
  friend class NIS_InteractiveObject;
  friend class NIS_ObjectsIterator;

 public:
// Declaration of CASCADE RTTI
DEFINE_STANDARD_RTTI (NIS_InteractiveContext)
};

// Definition of HANDLE object using Standard_DefineHandle.hxx
DEFINE_STANDARD_HANDLE (NIS_InteractiveContext, Standard_Transient)


#endif
