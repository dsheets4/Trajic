#
# Adapted from http://www.cmake.org/Wiki/PC-Lint
#


# This file contains functions and configurations for generating PC-Lint build
# targets for your CMake projects.
IF( WIN32 )
   # Find the PC LINT executable.
   FIND_PROGRAM( PCLINT_EXECUTABLE NAMES lint-nt
      PATHS
      C:/lint
      D:/lint
      )

   # Create the include path to the installed files from PC LINT.
   GET_FILENAME_COMPONENT(PCLINT_CONFIG_DIR ${PCLINT_EXECUTABLE} PATH)
   SET(PCLINT_CONFIG_DIR "${PCLINT_CONFIG_DIR}/lnt")

   # Setup the directory for the project custom lint include files.
   SET(PCLINT_CUSTOM_DIR "${PROJECT_SOURCE_DIR}/lint"
      CACHE STRING "Full path to the directory containing the custom std.lnt configuration file."
      )

   # Command line arguemnts used to run lint.
   SET(PCLINT_USER_FLAGS "-b"
      CACHE STRING "Additional pc-lint command line options -- some flags of pc-lint cannot be set in option files (most notably -b)"
      )

   # A roll-up target that will be used to run all of the lint targets.
   add_custom_target(ALL_LINT)

   SET( PCLINT_TARGET_FOLDER "Support/PC_Lint")
   SET_PROPERTY( TARGET ALL_LINT PROPERTY FOLDER ${PCLINT_TARGET_FOLDER} )

   # add_pclint(target source1 [source2 ...])
   #
   # Takes a list of source files and generates a build target which can be used
   # for linting all files
   #
   # The generated lint commands assume that a top-level config file named
   # 'std.lnt' resides in the configuration directory 'PCLINT_CONFIG_DIR'. This
   # config file must include all other config files. This is standard lint
   # behaviour.
   #
   # Parameters:
   #  - target: the name of the target to which the sources belong. You will get a
   #            new build target named ${target}_LINT
   #  - source1 ... : a list of source files to be linted. Just pass the same list
   #            as you passed for add_executable or add_library. Everything except
   #            C and CPP files (*.c, *.cpp, *.cxx) will be filtered out.
   #
   # Example:
   #  If you have a CMakeLists.txt which generates an executable like this:
   #
   #    set(MAIN_SOURCES main.c foo.c bar.c)
   #    add_executable(main ${MAIN_SOURCES})
   #
   #  include this file
   #
   #    include(/path/to/pclint.cmake)
   #
   #  and add a line to generate the main_LINT target
   #
   #   if(COMMAND add_pclint)
   #    add_pclint(main ${MAIN_SOURCES})
   #   endif()
   #
   function(add_pclint target)
      get_directory_property(lint_include_directories INCLUDE_DIRECTORIES)
      get_directory_property(lint_defines COMPILE_DEFINITIONS)

      # let's get those elephants across the alps
      # prepend each include directory with "-i"; also quotes the directory
      set(lint_include_directories_transformed)
      foreach(include_dir ${lint_include_directories})
         list(APPEND lint_include_directories_transformed -i"${include_dir}")
      endforeach(include_dir)

      # prepend each definition with "-d"
      set(lint_defines_transformed)
      foreach(definition ${lint_defines})
         list(APPEND lint_defines_transformed -d${definition})
      endforeach(definition)

      # Reset the value of the variable from any previous executions.
      set(pclint_commands)
      SET(pclint_sources)

      # Create a list of commands to add to the custom command.
      foreach(sourcefile ${ARGN})
         # only include c and cpp files
         if( sourcefile MATCHES \\.c$|\\.cxx$|\\.cpp$ )
            # make filename absolute
            get_filename_component(sourcefile_abs ${sourcefile} ABSOLUTE)
            LIST(APPEND pclint_sources ${sourcefile_abs})
            # create command line for linting one source file and add it to the list of commands
            list(APPEND pclint_commands
               COMMAND ${PCLINT_EXECUTABLE}
               -i"${PCLINT_CONFIG_DIR}" -i"${PCLINT_CUSTOM_DIR}" std.lnt
               "-u" ${PCLINT_USER_FLAGS}
               ${lint_include_directories_transformed}
               ${lint_defines_transformed}
               ${sourcefile_abs})
         endif()
      endforeach(sourcefile)

      # Create a custom command consisting of the arguments generated above.
      SET( PCLINT_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${target}_lint.sentinel )
      MESSAGE( STATUS "OUTPUTS: ${PCLINT_OUTPUT}" )
      ADD_CUSTOM_COMMAND(
         OUTPUT ${PCLINT_OUTPUT}
         ${pclint_commands} VERBATIM
         COMMAND ${CMAKE_COMMAND} -E touch ${PCLINT_OUTPUT}
         DEPENDS ${pclint_sources}
         )

      add_custom_target(${target}_LINT ${pclint_commands} VERBATIM
         DEPENDS ${PCLINT_OUTPUT})
      # make the ALL_LINT target depend on each and every *_LINT target
      add_dependencies(ALL_LINT ${target}_LINT)

      # This places the test in a folder according to the component name.
      SET_PROPERTY( TARGET ${target}_LINT PROPERTY FOLDER ${PCLINT_TARGET_FOLDER} )

   endfunction(add_pclint)

ENDIF()
