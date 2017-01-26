# Copyright 2017 Tim Oltjenbruns

FIND_PROGRAM( SONAR_PATH sonar-scanner )

IF(NOT UNIX)
    MESSAGE(FATAL_ERROR "Sonar CMake module only supports Unix based systems")
ENDIF() # NOT UNIX

IF(NOT SONAR_PATH)
    MESSAGE(FATAL_ERROR "sonar-scanner not found, aborting!")
ENDIF() # NOT SONAR_PATH

# disable optimization and enable coverage
set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
# create Coverage target
# based on CMake CodeCoverage module Copyright (c) 2012 - 2015, Lars Bilke
# https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
include(CodeCoverage)
include(CppCheck)
include(Valgrind)

FUNCTION(ADD_TARGET_SONAR _target_name _source_dir _test_dir _test_runner)

    SETUP_TARGET_FOR_COVERAGE_COBERTURA("Coverage" ${_test_dir} ${_test_runner} "gcovr")
    ADD_TARGET_CPPCHECK("CppCheck" ${_source_dir} "cppcheck")
    ADD_TARGET_VALGRIND("Valgrind" ${_test_runner} "valgrind")

    ADD_CUSTOM_TARGET(${_target_name}
            DEPENDS Coverage CppCheck Valgrind
            # TODO: ensure sonar server is running
            COMMAND ${SONAR_PATH} -D sonar.cxx.coverage.reportPath='${CMAKE_BINARY_DIR}/gcovr.xml' -D sonar.cxx.cppcheck.reportPath='${CMAKE_BINARY_DIR}/cppcheck.xml' -D sonar.cxx.valgrind.reportPath='${CMAKE_BINARY_DIR}/valgrind.xml'
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Running sonar-scanner to upload analysis reports to SonarQube server"
            )
ENDFUNCTION() # ADD_TARGET_SONAR)