
# =============================================================================
# Doxygen setup macro
MACRO( DOXYGEN TARGET_NAME DIRECTORY )

    FIND_PROGRAM( DOXYGEN_CMD doxygen )
    IF( DOXYGEN_CMD )
        # Create the custom target in Visual Studio to generate the documentation
        # and configure the doxyfile for use with this project.
        ADD_CUSTOM_TARGET( ${TARGET_NAME}_Doxygen
                        COMMAND ${DOXYGEN_CMD} "${DIRECTORY}/doc/Doxyfile.dox"
                        WORKING_DIRECTORY "${DIRECTORY}"
        )
        SET_PROPERTY( TARGET ${TARGET_NAME}_Doxygen PROPERTY FOLDER "Support/Doxygen" )

        CONFIGURE_FILE(
            "${DIRECTORY}/doc/Doxyfile.in.dox" 
            "${DIRECTORY}/doc/Doxyfile.dox"
        )
        CONFIGURE_FILE(
            "${DIRECTORY}/doc/header.in.html" 
            "${DIRECTORY}/doc/header.html"
        )
    ENDIF()

ENDMACRO( DOXYGEN )
