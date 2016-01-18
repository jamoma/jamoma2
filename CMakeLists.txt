cmake_minimum_required(VERSION 3.0)

project(Jamoma)

####### PREREQUISITES

message(STATUS "Updating Git Submodules")
execute_process(
	COMMAND				git submodule update --init --recursive
	WORKING_DIRECTORY	"${PROJECT_SOURCE_DIR}"
)


####### EXAMPLES

add_subdirectory(src/filtered-noise-example)
add_subdirectory(src/sine-tone-example)


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

SUBDIRLIST(TESTDIRS ${CMAKE_CURRENT_SOURCE_DIR}/test)
foreach(testdir ${TESTDIRS})
	MESSAGE("Generating Unit Test: ${testdir}")
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/${testdir})
	add_test(NAME ${testdir}
	         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test/${testdir}/${testdir}.test)
endforeach()
