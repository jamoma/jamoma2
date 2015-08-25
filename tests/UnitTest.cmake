cmake_minimum_required(VERSION 3.0)


enable_testing()


include_directories( 
	"${PROJECT_SOURCE_DIR}/../../includes"
	"${PROJECT_SOURCE_DIR}/../../includes/core"
	"${PROJECT_SOURCE_DIR}/../../includes/library"
	
	"${PROJECT_SOURCE_DIR}/../../dependencies/gtest"
	"${PROJECT_SOURCE_DIR}/../../dependencies/Mersenne-1.1"
	"${PROJECT_SOURCE_DIR}/../../dependencies/Murmur3"
	"${PROJECT_SOURCE_DIR}/../../dependencies/readerwriterqueue-master"
)


set(CMAKE_CXX_FLAGS "-std=c++1y -stdlib=libc++ -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage")
#set(CMAKE_LD_FLAGS "-fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

add_executable(${PROJECT_NAME}.test ${PROJECT_NAME}.cpp)

add_test(NAME ${PROJECT_NAME}
         COMMAND ${PROJECT_NAME}.test)
