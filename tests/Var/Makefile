
NAME = JamomaTest_Var
SRC = $(NAME).cpp

INCLUDES = -I../../includes
INCLUDES += -I../../includes/core
INCLUDES += -I../../includes/library

INCLUDES += -I../../dependencies/gtest
INCLUDES += -I../../dependencies/Mersenne-1.1
INCLUDES += -I../../dependencies/Murmur3
INCLUDES += -I../../dependencies/portaudio
INCLUDES += -I../../dependencies/readerwriterqueue-master
INCLUDES += -I../../dependencies/variant/include


OPTIONS = -std=c++1y -stdlib=libc++
OPTIONS += -fprofile-arcs -ftest-coverage


debug:
	$(CXX) $(SRC) -g ${OPTIONS} ${INCLUDES} -o $(NAME)

test: | debug
	./$(NAME)
