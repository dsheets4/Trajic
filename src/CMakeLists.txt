
# =============================================================================
# Common Configuration among child directories.  Macros are carried to children

   FIND_PACKAGE(Qt4 4.7.0 REQUIRED QtCore QtGui QtSql QtScript QtWebKit )
   SET(QT_DONT_USE_QTGUI FALSE)
   SET(QT_USE_QTSQL      TRUE)
   SET(QT_USE_QTWEBKIT   TRUE)
   INCLUDE(${QT_USE_FILE})

# -----------------------------------------------------------------------------
# Visual Leak Detector - Only available with Visual Studio.
FIND_PACKAGE( VLD )
IF( VLD_FOUND )
   OPTION( LEAK_DETECTION__USE_VLD 
       "Use Visual Leak Detector to detect memory leak.  Only available for Windows with VLD installed"
       ON
       )

   IF( LEAK_DETECTION__USE_VLD )
       # Enable compiling in the leak detection macro
       ADD_DEFINITIONS( 
           -DUSE_LEAK_DETECTION
           )
       # Setup the include and libraries
       INCLUDE_DIRECTORIES(
          ${VLD_INCLUDE_DIRS}
          )
       LINK_DIRECTORIES(
          ${VLD_LIBRARY_PATH}
          ) 
       # Copy the configuration file into the executable path so it gets used.
       IF( NOT ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL "${EXECUTABLE_OUTPUT_PATH}/Debug" )
          CONFIGURE_FILE(
             "${CMAKE_CURRENT_SOURCE_DIR}/vld.ini" 
             "${EXECUTABLE_OUTPUT_PATH}/Debug/vld.ini"
          )
       ENDIF()
   ENDIF()
ENDIF()



# -----------------------------------------------------------------------
# Turns on organization of projects within folders.  It will cause CMake 
# to organize its projects into folders as well, which is nice
# Be sure to create the folder for the libraries and executables that
# are created in the CMakeLists.txt files.
#   SET_PROPERTY( TARGET target_name PROPERTY FOLDER "FolderPath/And/Name" ) 
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)


# -----------------------------------------------------------------------------
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# =============================================================================
# Configure files

# -----------------------------------------------------------------------------
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/CommonDefinitions.in.h" 
    "${CMAKE_CURRENT_BINARY_DIR}/CommonDefinitions.h"
)


# =============================================================================
# Recurse into the subdirectories representing the various sub-projects.
# This does not actually cause another cmake executable to run. The same 
# process will walk through the project's entire directory structure.
ADD_SUBDIRECTORY (TaxiVis)
#ADD_SUBDIRECTORY (IconGen)

