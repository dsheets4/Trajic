# 
# CMake find package for Visual Leak Debugger library (VLD)
# http://vld.codeplex.com/
#
# Defines the following macros:
# * VLD_FOUND
# * VLD_INCLUDE_DIR
# * VLD_INCLUDE_DIRS
# * VLD_LIBRARY
# * VLD_LIBRARIES

# After finding VLD the following will need to be called for any target that
# is using the leak detector.  VLD uses a #Pragma to link the proper library
# so only the path needs added to the LINK_DIRECTORIES to find the .lib
#
#       INCLUDE_DIRECTORIES(
#          ${VLD_INCLUDE_DIRS}
#          )
#       LINK_DIRECTORIES(
#          ${VLD_LIBRARY_PATH}
#          ) 

# * Call the find_package_handle_standard_args() macro to set the <name>_FOUND
#   variable and print a success or failure message. 
INCLUDE(FindPackageHandleStandardArgs)

# Only use VLD on Windows
IF(WIN32)
   # Only use VLD for Visual Studio
   IF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv)")

      FIND_PATH(VLD_INCLUDE_DIR vld.h
         "$ENV{PROGRAMFILES}/Visual Leak Detector/include"
         "$ENV{PROGRAMFILES(x86)}/Visual Leak Detector/include"
         $ENV{VLD_HOME}/include
         )
      #MESSAGE(STATUS "VLD_INCLUDE_DIR=${VLD_INCLUDE_DIR}")

      # Note: Use FIND_PATH so that if it's not found a path selection dialog 
      #       is provided.
      IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
         FIND_PATH(VLD_LIBRARY_PATH
            NAMES vld.lib
            PATHS 
            "$ENV{PROGRAMFILES}/Visual Leak Detector/lib/Win64"
            "$ENV{PROGRAMFILES(x86)}/Visual Leak Detector/lib/Win64"
            "$ENV{VLD_HOME}/lib/Win64"
            DOC "Path to the Visual Leak Debugger library for 64-bit"
            )
      ELSE()
         FIND_PATH(VLD_LIBRARY_PATH
            NAMES vld.lib
            PATHS 
            "$ENV{PROGRAMFILES}/Visual Leak Detector/lib/Win32"
            "$ENV{PROGRAMFILES(x86)}/Visual Leak Detector/lib/Win32"
            "$ENV{VLD_HOME}/lib/Win32"
            DOC "Path to the Visual Leak Debugger library for 32-bit"
            )
      ENDIF()
      #MESSAGE(STATUS "VLD_LIBRARY_PATH=${VLD_LIBRARY_PATH}")

      IF(VLD_INCLUDE_DIR AND VLD_LIBRARY_PATH)
        SET(VLD_FOUND TRUE)

        # Set the INCLUDE_DIRS per CMake recommendation
        SET( VLD_INCLUDE_DIRS ${VLD_INCLUDE_DIR} )
        # Libraries are linked via #pragmas in the header file but the
        # path must be added to properly link.
        SET( VLD_LIBRARY )
        SET( VLD_LIBRARIES )
      ENDIF()

      FIND_PACKAGE_HANDLE_STANDARD_ARGS("VLD" REQUIRED_VARS 
          VLD_INCLUDE_DIR VLD_LIBRARY_PATH)

      IF( VLD_FOUND )
         MARK_AS_ADVANCED(
            VLD_INCLUDE_DIR
            VLD_LIBRARY_PATH
            )
      ENDIF()

   ENDIF()
ENDIF()

