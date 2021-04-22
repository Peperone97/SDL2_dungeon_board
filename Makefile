CC=g++
OBJ=main.cpp window.cpp window.hpp
LIBS=`pkg-config --libs --cflags sdl2`
RES=program

$(RES): $(OBJ)
	$(CC) $(LIBS) $(OBJ) -o $(RES)