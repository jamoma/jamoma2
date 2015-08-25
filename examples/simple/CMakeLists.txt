cmake_minimum_required(VERSION 3.3)


project(simple)

include_directories( 
	"${PROJECT_SOURCE_DIR}/../../includes"
	"${PROJECT_SOURCE_DIR}/../../includes/core"
	"${PROJECT_SOURCE_DIR}/../../includes/library"
	
	"${PROJECT_SOURCE_DIR}/../../dependencies/gtest"
	"${PROJECT_SOURCE_DIR}/../../dependencies/Mersenne-1.1"
	"${PROJECT_SOURCE_DIR}/../../dependencies/Murmur3"
	"${PROJECT_SOURCE_DIR}/../../dependencies/readerwriterqueue-master"

	"${PROJECT_SOURCE_DIR}/../../dependencies/portaudio/include"
)


set(CMAKE_CXX_FLAGS "-std=c++1y -stdlib=libc++")


add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)


if (APPLE)
	target_link_libraries(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/../../dependencies/portaudio/libportaudio.a")

	find_library(THE_LIBRARY "Carbon")
	target_link_libraries(${PROJECT_NAME} PUBLIC ${THE_LIBRARY})

	find_library(THE_LIBRARY2 "CoreAudio")
	target_link_libraries(${PROJECT_NAME} PUBLIC ${THE_LIBRARY2})

	find_library(THE_LIBRARY3 "AudioUnit")
	target_link_libraries(${PROJECT_NAME} PUBLIC ${THE_LIBRARY3})

	find_library(THE_LIBRARY4 "AudioToolbox")
	target_link_libraries(${PROJECT_NAME} PUBLIC ${THE_LIBRARY4})
endif()
