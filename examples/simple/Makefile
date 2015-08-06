
NAME = simple
CC = /usr/bin/clang++
SRC = $(NAME).cpp

INCLUDES = -I../../includes
INCLUDES += -I../../includes/core
INCLUDES += -I../../includes/library

INCLUDES += -I../../dependencies/gtest
INCLUDES += -I../../dependencies/Mersenne-1.1
INCLUDES += -I../../dependencies/Murmur3
INCLUDES += -I../../dependencies/portaudio/include
INCLUDES += -I../../dependencies/readerwriterqueue-master

LIBRARIES = ../../dependencies/portaudio/libportaudio.a

FRAMEWORKS = /System/Library/Frameworks/Carbon.framework/Versions/A/Carbon
FRAMEWORKS += /System/Library/Frameworks/CoreAudio.framework/Versions/A/CoreAudio
FRAMEWORKS += /System/Library/Frameworks/AudioUnit.framework/Versions/A/AudioUnit
FRAMEWORKS += /System/Library/Frameworks/AudioToolbox.framework/Versions/A/AudioToolbox


OPTIONS += -std=c++14 -stdlib=libc++


debug:
	$(CC) $(SRC) -g ${OPTIONS} ${INCLUDES} ${LIBRARIES} ${FRAMEWORKS} -o $(NAME)

test: | debug
	./$(NAME)
