#TODO mkdir .sonar_reports
cppcheck --enable=all --xml-version=2 sudoku 2> .sonar_reports/cppcheck.xml
#TODO coverageS
valgrind --xml=yes --xml-file=.sonar_reports/valgrind.xml cmake-build-debug/sudoku_tests/tests/run_tests
sonar-scanner
