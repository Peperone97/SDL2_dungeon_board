CC=g++
OBJ=main.o window.o texture.o  floor.o entity.o
LIBS=`pkg-config --libs --cflags sdl2` -lSDL2_image
RES=program

$(RES): $(OBJ)
	g++ $(LIBS) $(OBJ) -o $(RES)

main.o: main.cpp window.h
window.o: window.cpp window.h texture.h
texture.o: texture.cpp texture.h
floor.o: floor.cpp floor.h texture.h entity.h
entity.o: entity.cpp entity.h texture.h

clean:
	rm *.o $(RES)
