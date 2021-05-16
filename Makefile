CC=g++
OBJ=main.o window.o texture.o entity.o core.o timer.o map.o phrase.o #new_core.o
LIBS=`pkg-config --libs --cflags sdl2` -lSDL2_image
RES=program

$(RES): $(OBJ)
	g++ $(LIBS) $(OBJ) -o $(RES)

main.o: main.cpp window.h
window.o: window.cpp window.h core.h phrase.h
texture.o: texture.cpp texture.h
core.o: core.cpp core.h texture.h entity.h map.h
menu.o: menu.cpp menu.h texture.h
new_core.o: new_core.cpp core.h texture.h entity.h
entity.o: entity.cpp entity.h texture.h timer.h
timer.o: timer.cpp timer.h
map.o: map.cpp map.h
phrase.o: phrase.cpp phrase.h

clean:
	rm *.o $(RES)
