cmake_minimum_required(VERSION 3.0)

project(Jamoma)


####### EXAMPLES

add_subdirectory(examples/simple)


####### UNIT TESTS

# Macro from http://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


enable_testing()

SUBDIRLIST(TESTDIRS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
foreach(testdir ${TESTDIRS})
	MESSAGE("Generating Unit Test: ${testdir}")
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/${testdir})
	add_test(NAME ${testdir}
	         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/${testdir}/${testdir}.test)
endforeach()
