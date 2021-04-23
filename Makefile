CC=g++
OBJ=main.o window.o
LIBS=`pkg-config --libs --cflags sdl2`
RES=program

$(RES): $(OBJ)
	c++ $(LIBS) $(OBJ) -o $(RES)

main.o: main.cpp window.h
window.o: window.cpp window.h

clean:
	rm *.o