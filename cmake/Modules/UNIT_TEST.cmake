# =============================================================================
# Enables the testing to begin including test projects.

# =============================================================================
# Qt Unit Testing macro
# 
# UNIT_TEST TEST_NAME [LIST_OF_LINKED_LIBRARIES]
#
# Macro takes the name of the executable and a list of libraries to
# link into the executable.  It relies on setting
#
#  TEST_SRC: Set to the source files that will get compiled into the test.
#  TEST_HDR: Set to any Qt header files that need to be moc'd
#  TEST_FRM: Set to any Qt ui files required
#  TEST_RES: Set to any Qt resource files for the test
MACRO( UNIT_TEST TEST_NAME )

    IF( TEST__ADD_UNIT_TESTS )
        INCLUDE_DIRECTORIES(
            ${CMAKE_CURRENT_BINARY_DIR}
            ${QT_QTTEST_INCLUDE_DIR}
        )

        INCLUDE(${QT_USE_FILE})

        # Process the files so that they go through the Qt preprocessing.
        QT4_WRAP_CPP     (TEST_SRC_MOC ${TEST_HDR})
        QT4_WRAP_UI      (TEST_FRM_MOC ${TEST_FRM})
        QT4_ADD_RESOURCES(TEST_RES_MOC ${TEST_RES})

        # Add executable that is built from the listed source files and the moc 
        # generated files.  Adding the FRM_MOC here is what adds the Qt 
        # generated headers for ui files to the project.
        # Note: This also names the project that is generated for Visual Studio.
        ADD_EXECUTABLE (${TEST_NAME}
            ${TEST_SRC}
            ${TEST_SRC_MOC}
            ${TEST_FRM_MOC}
            ${TEST_RES_MOC}
        )

        # This places the test in a folder according to the component name.
        SET_PROPERTY( TARGET ${TEST_FULL_NAME} PROPERTY FOLDER "Support/Tests" )
        # Qt Test support
        TARGET_LINK_LIBRARIES( ${TEST_NAME}
            ${QT_LIBRARIES}
            ${QT_QTTEST_LIBRARIES}
            ${ARGN}
        )
    ENDIF()
ENDMACRO( UNIT_TEST )
