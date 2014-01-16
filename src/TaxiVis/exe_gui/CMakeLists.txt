
# =============================================================================
# Define options specific to this sub-project

# =============================================================================
# Setup external libraries
# -----------------------------------------------------------------------------
# Qt (and perhaps other tools) will generate files outside of the source
# tree.  As a result, the current binary directory is added in order to 
# provide the location of the generated files.
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/TaxiVis
    ${CMAKE_BINARY_DIR}/src/TaxiVis
)

# =============================================================================
# Internal definitions for the library
ADD_DEFINITIONS( 
    -DTaxiVis_EXPORTS
)


# =============================================================================
# Configure files

# -----------------------------------------------------------------------------
SET(TAXIVIS_DEFAULT_WIDTH   1200) # Default window width
SET(TAXIVIS_DEFAULT_HEIGHT   800) # Default window height
SET(TAXIVIS_MAIN_DEFAULT_WIDTH   ${TAXIVIS_DEFAULT_WIDTH})  # Main window width
SET(TAXIVIS_MAIN_DEFAULT_HEIGHT  ${TAXIVIS_DEFAULT_HEIGHT}) # Main window height
SET(TAXIVIS_CHILD_DEFAULT_WIDTH  ${TAXIVIS_DEFAULT_WIDTH})  # Child window width
SET(TAXIVIS_CHILD_DEFAULT_HEIGHT ${TAXIVIS_DEFAULT_HEIGHT}) # Child window height
CONFIGURE_FILE(
   "${CMAKE_CURRENT_SOURCE_DIR}/TaxiVisGuiConstants.in.h" 
   "${CMAKE_CURRENT_BINARY_DIR}/TaxiVisGuiConstants.h"
)


# =============================================================================
# Setup all of the files that make up this project.
SET(SRC 
   main.cpp
   ScriptConfigMain.cpp

   TaxiVis.cpp
   TaxiVisDispatch.cpp

   ../TaxiVisUtils.cpp
   ../ObjectBaseWrapper.cpp
   ../ObjectBaseDispatch.cpp
   ../HtmlPage.cpp

   GuiTypes.cpp
   GuiFactory.cpp
   GuiFactoryHandler.cpp

   MainView.cpp
   MainViewDispatch.cpp
   MainViewScript.cpp
   MainViewScriptProto.cpp

   MainScene.cpp
   MainSceneDispatch.cpp
   MainSceneScript.cpp
   MainSceneScriptProto.cpp


   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Script source code
   ../Script/ScriptPrompt.cpp
   ../Script/ScriptEngine.cpp
   ../Script/ScriptConfig.cpp

   ../Script/ObjectBaseScript.cpp
   ../Script/ObjectBaseScriptProto.cpp

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Map source code
   ../Map/MapTypes.cpp

   ../Map/MapView.cpp

   ../Map/MapPage.cpp
   ../Map/MapPageDispatch.cpp
   ../Map/MapPageScript.cpp
   ../Map/MapPageScriptProto.cpp

   ../Map/GraphPage.cpp
   ../Map/GraphPageDispatch.cpp
   ../Map/GraphPageScript.cpp
   ../Map/GraphPageScriptProto.cpp

   ../Map/ScriptConfigMap.cpp

   ../Map/JsQueryRouteHandler.cpp
   ../Map/JsQueryRouteWrapper.cpp

   ../Map/JsSettingsLayer.cpp

   ../Map/JsSettingsMap.cpp
   ../Map/JsSettingsMapDispatch.cpp
   ../Map/JsSettingsMapScript.cpp
   ../Map/JsSettingsMapScriptProto.cpp

   ../Map/MapFactory.cpp
   ../Map/MapFactoryHandler.cpp

   ../Map/MapObject.cpp

   ../Map/JsPoint.cpp
   ../Map/JsPointDispatch.cpp
   ../Map/JsPointScript.cpp
   ../Map/JsPointScriptProto.cpp

   ../Map/JsRoute.cpp
   ../Map/JsRouteDispatch.cpp
   ../Map/JsRouteScript.cpp
   ../Map/JsRouteScriptProto.cpp

   ../Map/JsPointIcon.cpp
   ../Map/JsPointIconDispatch.cpp
   ../Map/JsPointIconScript.cpp
   ../Map/JsPointIconScriptProto.cpp

   ../Map/JsLayer.cpp
   ../Map/JsLayerDispatch.cpp
   ../Map/JsLayerScript.cpp
   ../Map/JsLayerScriptProto.cpp

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Vis source code
   ../Vis/GraphTypes.cpp
   ../Vis/CoordinateScale.cpp
   ../Vis/GraphMapping.cpp
   ../Vis/GraphMappingLinear.cpp
   ../Vis/GraphMappingLog10Y.cpp
   ../Vis/GraphFactory.cpp
   ../Vis/GraphFactoryHandler.cpp

   ../Vis/GraphBase.cpp
   ../Vis/GraphBaseObjWrap.cpp
   ../Vis/GraphBaseDispatch.cpp
   ../Vis/GraphBaseScript.cpp
   ../Vis/GraphBaseScriptProto.cpp

   ../Vis/GraphBar.cpp
   ../Vis/GraphBarItem.cpp
   ../Vis/GraphBarObjWrap.cpp
   ../Vis/GraphBarDispatch.cpp
   ../Vis/GraphBarScript.cpp
   ../Vis/GraphBarScriptProto.cpp

   ../Vis/GraphPie.cpp
   ../Vis/GraphPieObjWrap.cpp
   ../Vis/GraphPieDispatch.cpp
   ../Vis/GraphPieScript.cpp
   ../Vis/GraphPieScriptProto.cpp

   ../Vis/GraphRingMap.cpp
   ../Vis/GraphRingMapObjWrap.cpp
   ../Vis/GraphRingMapDispatch.cpp
   ../Vis/GraphRingMapScript.cpp
   ../Vis/GraphRingMapScriptProto.cpp

   ../Vis/GraphRingItem.cpp
   ../Vis/GraphRingItemObjWrap.cpp
   ../Vis/GraphRingItemDispatch.cpp
   ../Vis/GraphRingItemScript.cpp
   ../Vis/GraphRingItemScriptProto.cpp
   
   ../Vis/GraphText.cpp
   ../Vis/GraphTextObjWrap.cpp
   ../Vis/GraphTextDispatch.cpp
   ../Vis/GraphTextScript.cpp
   ../Vis/GraphTextScriptProto.cpp
   
   ../Vis/GraphPc.cpp
   ../Vis/GraphPc_Coord.cpp
   ../Vis/GraphPc_Line.cpp
   ../Vis/GraphPcObjWrap.cpp
   ../Vis/GraphPcDispatch.cpp
   ../Vis/GraphPcScript.cpp
   ../Vis/GraphPcScriptProto.cpp

   ../Vis/ScriptConfigVis.cpp

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # DataAccess source code
   ../DataAccess/DataPoint.cpp
   ../DataAccess/DataRoute.cpp
   ../DataAccess/QueryFunctions.cpp
   ../DataAccess/QueryRoute.cpp
   ../DataAccess/QueryRouteHandler.cpp
   ../DataAccess/QueryRouteCriteria.cpp
   )

# Only add headers that are for Qt.
SET(MOC 
   ../ObjectBaseWrapper.h
   ../ObjectBaseDispatch.h
   ../HtmlPage.h

   TaxiVis.h
   TaxiVisDispatch.h
   
   GuiFactory.h
   GuiFactoryHandler.h

   MainView.h
   MainViewDispatch.h
   MainViewScript.h
   MainViewScriptProto.h

   MainScene.h
   MainSceneDispatch.h
   MainSceneScript.h
   MainSceneScriptProto.h

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Script moc header code
   ../Script/ScriptPrompt.h
   ../Script/ScriptEngine.h

   ../Script/ObjectBaseScript.h
   ../Script/ObjectBaseScriptProto.h

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Map moc header code
   ../Map/MapView.h

   ../Map/MapPage.h
   ../Map/MapPageDispatch.h
   ../Map/MapPageScript.h
   ../Map/MapPageScriptProto.h

   ../Map/GraphPage.h
   ../Map/GraphPageDispatch.h
   ../Map/GraphPageScript.h
   ../Map/GraphPageScriptProto.h

   ../Map/JsQueryRouteWrapper.h

   ../Map/JsSettingsLayer.h

   ../Map/JsSettingsMap.h
   ../Map/JsSettingsMapDispatch.h
   ../Map/JsSettingsMapScript.h
   ../Map/JsSettingsMapScriptProto.h

   ../Map/MapFactory.h
   ../Map/MapFactoryHandler.h

   ../Map/MapObject.h

   ../Map/JsPoint.h
   ../Map/JsPointDispatch.h
   ../Map/JsPointScript.h
   ../Map/JsPointScriptProto.h

   ../Map/JsRoute.h
   ../Map/JsRouteDispatch.h
   ../Map/JsRouteScript.h
   ../Map/JsRouteScriptProto.h

   ../Map/JsPointIcon.h
   ../Map/JsPointIconDispatch.h
   ../Map/JsPointIconScript.h
   ../Map/JsPointIconScriptProto.h

   ../Map/JsLayer.h
   ../Map/JsLayerDispatch.h
   ../Map/JsLayerScript.h
   ../Map/JsLayerScriptProto.h

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Vis source code
   ../Vis/GraphFactory.h
   ../Vis/GraphFactoryHandler.h

   ../Vis/GraphBaseObjWrap.h
   ../Vis/GraphBaseDispatch.h
   ../Vis/GraphBaseScript.h
   ../Vis/GraphBaseScriptProto.h

   ../Vis/GraphRingMapObjWrap.h
   ../Vis/GraphRingMapDispatch.h
   ../Vis/GraphRingMapScript.h
   ../Vis/GraphRingMapScriptProto.h

   ../Vis/GraphRingItemObjWrap.h
   ../Vis/GraphRingItemDispatch.h
   ../Vis/GraphRingItemScript.h
   ../Vis/GraphRingItemScriptProto.h

   ../Vis/GraphBarObjWrap.h
   ../Vis/GraphBarDispatch.h
   ../Vis/GraphBarScriptProto.h
   ../Vis/GraphBarScript.h

   ../Vis/GraphPieObjWrap.h
   ../Vis/GraphPieDispatch.h
   ../Vis/GraphPieScript.h
   ../Vis/GraphPieScriptProto.h
   
   ../Vis/GraphTextObjWrap.h
   ../Vis/GraphTextDispatch.h
   ../Vis/GraphTextScript.h
   ../Vis/GraphTextScriptProto.h
   
   ../Vis/GraphPcObjWrap.h
   ../Vis/GraphPcDispatch.h
   ../Vis/GraphPcScript.h
   ../Vis/GraphPcScriptProto.h
   ) 
# Qt ui files.
SET(FRM
   ui/TaxiVis.ui
   )
# Qt resource (qrc) files.
SET(RES
   TaxiVis.qrc
   )


# =============================================================================
# Process the files so that they go through the Qt preprocessing.
QT4_WRAP_CPP     (SRC_MOC ${MOC})
QT4_WRAP_UI      (FRM_MOC ${FRM})
QT4_ADD_RESOURCES(RES_MOC ${RES})


# =============================================================================
# Add executable that is built from the listed source files and the moc 
# generated files.  Adding the FRM_MOC here is what adds the Qt generated
# headers for ui files to the project.
# Note: This also names the project that is generated for Visual Studio.
ADD_EXECUTABLE (TaxiVis
   ${SRC}
   ${SRC_MOC}
   ${FRM_MOC}
   ${RES_MOC}
)

# Include the libraries that need linked.  This must come after the target
# (ADD_EXECUTABLE, ADD_LIBRARY, etc.).
TARGET_LINK_LIBRARIES( TaxiVis ${QT_LIBRARIES} )

# Installation materials
INSTALL(
    TARGETS TaxiVis
    RUNTIME
    DESTINATION bin
    )
INSTALL(
    FILES
    "${QT_BINARY_DIR}/QtCore4.dll"
    "${QT_BINARY_DIR}/QtGui4.dll"
    "${QT_BINARY_DIR}/QtScript4.dll"
    "${QT_BINARY_DIR}/QtSql4.dll"
    "${QT_BINARY_DIR}/QtWebKit4.dll"
    DESTINATION bin
    )
INSTALL(
    DIRECTORY "${SCRIPT_DIR}"
    DESTINATION .
    COMPONENT Scripts
    )
SET(CPACK_COMPONENTS_ALL Scripts)


# =============================================================================
IF(COMMAND add_pclint)
   # --------------------------------------------------------------------------
   # Setup various options and provide the reason for changing the default.
   # Note: User flags must be set before calling add_pc_lint...

   # Provide a description of why the target diverges from the defaults.
   #SET( PC_LINT_USER_FLAGS ${PC_LINT_USER_FLAGS} "Your flag here" )


   # --------------------------------------------------------------------------
   # Create the target for linting.
   add_pclint(TaxiVis ${SRC})
ENDIF()

# =============================================================================
## Only add the Unit Tests if the option has been set.
#IF( TEST__UNIT_TESTS )
#   ADD_SUBDIRECTORY(Test)
#ENDIF()

