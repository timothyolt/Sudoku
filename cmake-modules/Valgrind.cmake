# Copyright 2017 Tim Oltjenbruns

FIND_PROGRAM( VALGRIND_PATH valgrind )

IF(NOT UNIX)
    MESSAGE(FATAL_ERROR "Valgrind CMake module only supports Unix based systems")
ENDIF() # NOT UNIX

IF(NOT VALGRIND_PATH)
    MESSAGE(FATAL_ERROR "valgrind not found, aborting!")
ENDIF() # NOT VALGRIND_PATH

FUNCTION(ADD_TARGET_VALGRIND _target_name _test_runner _output_name)

    ADD_CUSTOM_TARGET(${_target_name}
            COMMAND ${VALGRIND_PATH} --xml=yes --xml-file=${_output_name}.xml ${_test_runner}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running valgrind memcheck to produce memory leak report."
            )

    # Show info where to find the report
    ADD_CUSTOM_COMMAND(TARGET ${_target_name} POST_BUILD
            COMMAND ;
            COMMENT "Valgrind memcheck report saved in ${_output_name}.xml."
            )

ENDFUNCTION() # ADD_TARGET_VALGRIND)