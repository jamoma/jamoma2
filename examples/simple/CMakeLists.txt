cmake_minimum_required(VERSION 3.0)


project(simple)



# Build the PortAudio dependency
SET(PORTAUDIO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/portaudio)

include(ExternalProject)
ExternalProject_Add(
  portaudio
  SOURCE_DIR ${PORTAUDIO_DIR}
  CONFIGURE_COMMAND ${PORTAUDIO_DIR}/configure --prefix=${PORTAUDIO_DIR}/build
  PREFIX ${PORTAUDIO_DIR}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
)


include_directories( 
	"${PROJECT_SOURCE_DIR}/../../includes"
	"${PROJECT_SOURCE_DIR}/../../includes/core"
	"${PROJECT_SOURCE_DIR}/../../includes/library"
	
	"${PROJECT_SOURCE_DIR}/../../dependencies/gtest"
	"${PROJECT_SOURCE_DIR}/../../dependencies/Mersenne-1.1"
	"${PROJECT_SOURCE_DIR}/../../dependencies/Murmur3"
	"${PROJECT_SOURCE_DIR}/../../dependencies/readerwriterqueue-master"

	"${PROJECT_SOURCE_DIR}/../../dependencies/portaudio/build/include"
)


SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS "-std=c++1y -stdlib=libc++")


add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)


if (APPLE)
	target_link_libraries(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/../../dependencies/portaudio/build/lib/libportaudio.a")	
	
	find_library(THE_LIBRARY "Carbon")
	target_link_libraries(${PROJECT_NAME} PUBLIC ${THE_LIBRARY})

	find_library(THE_LIBRARY2 "CoreAudio")
	target_link_libraries(${PROJECT_NAME} PUBLIC ${THE_LIBRARY2})

	find_library(THE_LIBRARY3 "AudioUnit")
	target_link_libraries(${PROJECT_NAME} PUBLIC ${THE_LIBRARY3})

	find_library(THE_LIBRARY4 "AudioToolbox")
	target_link_libraries(${PROJECT_NAME} PUBLIC ${THE_LIBRARY4})
else() # Assume Linux
	# NOTE: can't use find_library() because we haven't built it yet
	target_link_libraries(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/../../dependencies/portaudio/build/lib/libportaudio.so")
endif()
