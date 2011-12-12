# Makefile.am for Open Cascade toolkit TKOpenGl
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/OpenGl : @top_srcdir@/src/OpenGl


AM_CXXFLAGS = 


AM_CFLAGS = -DSILGL \
-DSILGL_VRS=50


INCLUDES = $(STLPort_INCLUDES) $(CSF_OpenGlLibs_INCLUDES) $(CSF_FREETYPE_INCLUDES) $(CSF_FTGL_INCLUDES) $(CSF_GL2PS_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_gdi32_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/OpenGl -I@top_srcdir@/src/OpenGl


lib_LTLIBRARIES=libTKOpenGl.la

libTKOpenGl_la_LIBADD = \
../TKService/libTKService.la \
../TKernel/libTKernel.la \
../TKV3d/libTKV3d.la \
$(STLPort_LIB) $(CSF_OpenGlLibs_LIB) $(CSF_FREETYPE_LIB) $(CSF_FTGL_LIB) $(CSF_GL2PS_LIB) $(CSF_user32_LIB) $(CSF_gdi32_LIB) 

libTKOpenGl_la_SOURCES = \
@top_srcdir@/drv/OpenGl/OpenGl_Error_0.cxx \
@top_srcdir@/src/OpenGl/OpenGl_AVIWriter.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Extension.cxx \
@top_srcdir@/src/OpenGl/OpenGl_FontMgr.cxx \
@top_srcdir@/src/OpenGl/OpenGl_FrameBuffer.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_1.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_2.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_3.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_4.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_5.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_6.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_7.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_703.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_705.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_707.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_709.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_710.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_711.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_712.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_713.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_8.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_9.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_Export.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_Layer.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_print.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ImageBox.cxx \
@top_srcdir@/src/OpenGl/OpenGl_LightBox.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Memory.cxx \
@top_srcdir@/src/OpenGl/OpenGl_PrimitiveArray.cxx \
@top_srcdir@/src/OpenGl/OpenGl_PrinterContext.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ResourceCleaner.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ResourceTexture.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ResourceVBO.cxx \
@top_srcdir@/src/OpenGl/OpenGl_TextRender.cxx \
@top_srcdir@/src/OpenGl/OpenGl_TextureBox.cxx \
@top_srcdir@/src/OpenGl/OpenGl_addnames.cxx \
@top_srcdir@/src/OpenGl/OpenGl_antialias.cxx \
@top_srcdir@/src/OpenGl/OpenGl_applid.cxx \
@top_srcdir@/src/OpenGl/OpenGl_attri.cxx \
@top_srcdir@/src/OpenGl/OpenGl_bintcol.cxx \
@top_srcdir@/src/OpenGl/OpenGl_bintrefl.cxx \
@top_srcdir@/src/OpenGl/OpenGl_bsurfprop.cxx \
@top_srcdir@/src/OpenGl/OpenGl_charexpan.cxx \
@top_srcdir@/src/OpenGl/OpenGl_charspace.cxx \
@top_srcdir@/src/OpenGl/OpenGl_curve.cxx \
@top_srcdir@/src/OpenGl/OpenGl_degmodel.cxx \
@top_srcdir@/src/OpenGl/OpenGl_depthcue.cxx \
@top_srcdir@/src/OpenGl/OpenGl_dind.cxx \
@top_srcdir@/src/OpenGl/OpenGl_dotexturemap.cxx \
@top_srcdir@/src/OpenGl/OpenGl_edgecol.cxx \
@top_srcdir@/src/OpenGl/OpenGl_edgeflag.cxx \
@top_srcdir@/src/OpenGl/OpenGl_edgetyp.cxx \
@top_srcdir@/src/OpenGl/OpenGl_edgewid.cxx \
@top_srcdir@/src/OpenGl/OpenGl_execstruct.cxx \
@top_srcdir@/src/OpenGl/OpenGl_facecull.cxx \
@top_srcdir@/src/OpenGl/OpenGl_facedmode.cxx \
@top_srcdir@/src/OpenGl/OpenGl_filters.cxx \
@top_srcdir@/src/OpenGl/OpenGl_funcs.cxx \
@top_srcdir@/src/OpenGl/OpenGl_graduatedtrihedron.cxx \
@top_srcdir@/src/OpenGl/OpenGl_highlight.cxx \
@top_srcdir@/src/OpenGl/OpenGl_hlind.cxx \
@top_srcdir@/src/OpenGl/OpenGl_indexpolygons.cxx \
@top_srcdir@/src/OpenGl/OpenGl_initelem.cxx \
@top_srcdir@/src/OpenGl/OpenGl_inquire.cxx \
@top_srcdir@/src/OpenGl/OpenGl_intcol.cxx \
@top_srcdir@/src/OpenGl/OpenGl_intrefl.cxx \
@top_srcdir@/src/OpenGl/OpenGl_intshademtd.cxx \
@top_srcdir@/src/OpenGl/OpenGl_intstyle.cxx \
@top_srcdir@/src/OpenGl/OpenGl_intstyleind.cxx \
@top_srcdir@/src/OpenGl/OpenGl_label.cxx \
@top_srcdir@/src/OpenGl/OpenGl_lightstate.cxx \
@top_srcdir@/src/OpenGl/OpenGl_localtran3.cxx \
@top_srcdir@/src/OpenGl/OpenGl_mrkr.cxx \
@top_srcdir@/src/OpenGl/OpenGl_mrkrcol.cxx \
@top_srcdir@/src/OpenGl/OpenGl_mrkrset.cxx \
@top_srcdir@/src/OpenGl/OpenGl_mrkrsize.cxx \
@top_srcdir@/src/OpenGl/OpenGl_mrkrtype.cxx \
@top_srcdir@/src/OpenGl/OpenGl_pick.cxx \
@top_srcdir@/src/OpenGl/OpenGl_pickid.cxx \
@top_srcdir@/src/OpenGl/OpenGl_polygon.cxx \
@top_srcdir@/src/OpenGl/OpenGl_polygonholes.cxx \
@top_srcdir@/src/OpenGl/OpenGl_polygonoffset.cxx \
@top_srcdir@/src/OpenGl/OpenGl_polyl.cxx \
@top_srcdir@/src/OpenGl/OpenGl_polylcol.cxx \
@top_srcdir@/src/OpenGl/OpenGl_polyltyp.cxx \
@top_srcdir@/src/OpenGl/OpenGl_polylwid.cxx \
@top_srcdir@/src/OpenGl/OpenGl_qstrip.cxx \
@top_srcdir@/src/OpenGl/OpenGl_remnames.cxx \
@top_srcdir@/src/OpenGl/OpenGl_subrs.cxx \
@top_srcdir@/src/OpenGl/OpenGl_subrvis.cxx \
@top_srcdir@/src/OpenGl/OpenGl_surfprop.cxx \
@top_srcdir@/src/OpenGl/OpenGl_telem_util.cxx \
@top_srcdir@/src/OpenGl/OpenGl_text.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textalignment.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textangle.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textcol.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textcolsubtitle.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textdisplaytype.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textfont.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textfontaspect.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textheight.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textstyle.cxx \
@top_srcdir@/src/OpenGl/OpenGl_texture.cxx \
@top_srcdir@/src/OpenGl/OpenGl_textzoomable.cxx \
@top_srcdir@/src/OpenGl/OpenGl_tgl_util.cxx \
@top_srcdir@/src/OpenGl/OpenGl_tgl_utilgr.cxx \
@top_srcdir@/src/OpenGl/OpenGl_tmesh.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_activateview.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_antialiasing.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_backfacing.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_background.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_begin.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_begin_animation.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_begin_immediat_mode.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_begin_layer_mode.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_bezier.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_bezier_weight.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_blink.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_boundarybox.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_cleargroup.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_clearstructure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_cliplimit.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_closegroup.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_connect.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_contextstructure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_curve.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_deactivateview.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_degeneratestructure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_depthcueing.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_depthtest.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_disconnect.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_displaystructure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_element_exploration.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_end.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_erasestructure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_facecontextgroup.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_gradient_background.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_graduatedtrihedron.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_group.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_highlightcolor.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_init_pick.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_inquirefacilities.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_inquirelight.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_inquireplane.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_inquireview.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_light.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_light_exploration.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_linecontextgroup.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_marker.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_marker_set.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_markercontextgroup.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_namesetstructure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_opengroup.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_parray.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_pick.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_pickid.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_plane.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_polygon.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_polygon_holes.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_polygon_indices.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_polygon_set.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_polyline.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_print.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_project_raster.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_quadrangle.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_ratio_window.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_redraw.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_removegroup.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_removestructure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_removeview.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_set_environment.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_setlight.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_setplane.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_setvisualisation.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_structure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_structure_exploration.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_text.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_textcontextgroup.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_texture.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_transformstructure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_transparency.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_triangle.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_triedron.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_unproject_raster.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_update.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_userdraw.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_view.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_view_exploration.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_viewmapping.cxx \
@top_srcdir@/src/OpenGl/OpenGl_togl_vieworientation.cxx \
@top_srcdir@/src/OpenGl/OpenGl_tox.cxx \
@top_srcdir@/src/OpenGl/OpenGl_transform_persistence.cxx \
@top_srcdir@/src/OpenGl/OpenGl_triedron.cxx \
@top_srcdir@/src/OpenGl/OpenGl_tsm.cxx \
@top_srcdir@/src/OpenGl/OpenGl_txgl.cxx \
@top_srcdir@/src/OpenGl/OpenGl_undefined.cxx \
@top_srcdir@/src/OpenGl/OpenGl_userdraw.cxx \
@top_srcdir@/src/OpenGl/OpenGl_view.cxx \
@top_srcdir@/src/OpenGl/OpenGl_vind.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ws.cxx

