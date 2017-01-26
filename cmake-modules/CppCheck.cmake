# Copyright 2017 Tim Oltjenbruns

FIND_PROGRAM( CPPCHECK_PATH cppcheck )

IF(NOT UNIX)
    MESSAGE(FATAL_ERROR "CppCheck CMake module only supports Unix based systems")
ENDIF() # NOT UNIX

IF(NOT CPPCHECK_PATH)
    MESSAGE(FATAL_ERROR "cppcheck not found, aborting!")
ENDIF() # NOT CPPCHECK_PATH

FUNCTION(ADD_TARGET_CPPCHECK _target_name _source_dir _output_name)

    # TODO: generate a line delimited text file from INCLUDE_DIRECTORIES to use in --includes-file
    ADD_CUSTOM_TARGET(${_target_name}
            COMMAND ${CPPCHECK_PATH} --enable=all --xml-version=2 ${_source_dir} 2> '${CMAKE_BINARY_DIR}/${_output_name}.xml'
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Running cppcheck to produce code quality report."
            )

    # Show info where to find the report
    ADD_CUSTOM_COMMAND(TARGET ${_target_name} POST_BUILD
            COMMAND ;
            COMMENT "CppCheck report saved in ${_output_name}.xml."
            )

ENDFUNCTION() # ADD_TARGET_CPPCHECK)