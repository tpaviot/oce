
# Modules of OCCT

SET(BUILD_FoundationClasses ON CACHE BOOL "include FoundationClasses"  )
SET(BUILD_ModelingData ON CACHE BOOL "include ModelingData"  )
SET(BUILD_ModelingAlgorithms ON CACHE BOOL "include ModelingAlgorithms"  )
SET(BUILD_Visualization ON CACHE BOOL "include Visualization"  )
SET(BUILD_ApplicationFramework ON CACHE BOOL "include ApplicationFramework"  )
SET(BUILD_DataExchange ON CACHE BOOL "include DataExchange"  )
IF (NOT DEFINED ANDROID)
SET(BUILD_Draw ON CACHE BOOL "include Draw"  )
ENDIF()
