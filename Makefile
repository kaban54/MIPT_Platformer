CC = g++
CFLAGS += -Wall -Wformat=0 -std=c++23 -fPIC
LDFLAGS += -lstdc++
SFMLFLAGS += -lsfml-graphics -lsfml-window -lsfml-system
OBJDIR = obj/
SRCDIR = src/

all: test

test: obj/main.o obj/app.o obj/camera.o obj/geometry.o obj/graphics.o obj/level.o obj/load.o \
	  obj/lvlload.o obj/object_man.o obj/player.o obj/sprite_man.o obj/vec2.o
	$(CC) -o test obj/main.o obj/app.o obj/camera.o obj/geometry.o obj/graphics.o obj/level.o obj/load.o \
	              obj/lvlload.o obj/object_man.o obj/player.o obj/sprite_man.o obj/vec2.o $(SFMLFLAGS) $(LDFLAGS)

ground1: obj/ground1.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/ground1.so obj/load.o obj/vec2.o obj/geometry.o obj/ground1.o $(LDFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

wind:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib                                            \
./src/main.cpp ./src/player.cpp   ./src/vec2.cpp  ./src/collidable.cpp  ./src/physics.cpp  \
./src/load.cpp ./src/geometry.cpp ./src/graphics.cpp                                       \
-lm -o test.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

clean:
	rm obj/*.o -f
	clear
	
.PHONY: test