cmake_minimum_required(VERSION 3.0)


project(filtered-noise-example)


find_path(PORTMIDI_INCLUDES "portmidi.h")
find_path(PORTAUDIO_INCLUDES "portaudio.h")

include_directories( 
	"${PROJECT_SOURCE_DIR}/../../include"
	"${PROJECT_SOURCE_DIR}/../../include/core"
	"${PROJECT_SOURCE_DIR}/../../include/objects"
	
	"${PROJECT_SOURCE_DIR}/../../include/third-party/gtest"
	"${PROJECT_SOURCE_DIR}/../../include/third-party/mersenne"
	"${PROJECT_SOURCE_DIR}/../../include/third-party/murmur"

	"${PORTMIDI_INCLUDES}"
	"${PORTAUDIO_INCLUDES}"
)
file(GLOB_RECURSE PROJECT_HEADERS ${PROJECT_SOURCE_DIR}/../../includes/*)


SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-std=c++1y -stdlib=libc++")


add_executable( ${PROJECT_NAME} 
				${PROJECT_NAME}.cpp
				${PROJECT_HEADERS}
)


# Link Installed Dynamic Libraries
find_library(PORTMIDI_LIB "portmidi")
target_link_libraries(${PROJECT_NAME} ${PORTMIDI_LIB} ${SUPPORT_LIBS})

find_library(PORTAUDIO_LIB "portaudio")
target_link_libraries(${PROJECT_NAME} ${PORTAUDIO_LIB} ${SUPPORT_LIBS})
