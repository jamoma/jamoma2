cmake_minimum_required(VERSION 3.0)


enable_testing()


SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)


include_directories( 
	"${PROJECT_SOURCE_DIR}/../../include"
	"${PROJECT_SOURCE_DIR}/../../include/core"
	"${PROJECT_SOURCE_DIR}/../../include/objects"
	
	"${PROJECT_SOURCE_DIR}/../../include/third-party/gtest"
	"${PROJECT_SOURCE_DIR}/../../include/third-party/mersenne"
	"${PROJECT_SOURCE_DIR}/../../include/third-party/murmur"
)


set(CMAKE_CXX_FLAGS "-std=c++1y -stdlib=libc++ -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage")
#set(CMAKE_LD_FLAGS "-fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

add_executable(${PROJECT_NAME}.test ${PROJECT_NAME}.cpp)

add_test(NAME ${PROJECT_NAME}
         COMMAND ${PROJECT_NAME}.test)
