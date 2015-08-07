
NAME = JamomaTest_LowpassFourPole
SRC = $(NAME).cpp

INCLUDES = -I../../includes
INCLUDES += -I../../includes/core
INCLUDES += -I../../includes/library

INCLUDES += -I../../dependencies/gtest
INCLUDES += -I../../dependencies/Mersenne-1.1
INCLUDES += -I../../dependencies/Murmur3
INCLUDES += -I../../dependencies/portaudio
INCLUDES += -I../../dependencies/readerwriterqueue-master

OPTIONS += -std=c++1y -stdlib=libc++


debug:
	$(CXX) $(SRC) -g ${OPTIONS} ${INCLUDES} -o $(NAME)

test: | debug
	./$(NAME)
