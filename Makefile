CC = g++
CFLAGS += -Wall -Wformat=0 -std=c++23
LDFLAGS += 
SFMLFLAGS += -lsfml-graphics -lsfml-window -lsfml-system
OBJDIR = obj/
SRCDIR = src/

all: test

test: obj/main.o obj/vec2.o obj/graphics.o obj/physics.o obj/geometry.o obj/load.o obj/player.o
	$(CC) -o test obj/main.o obj/vec2.o obj/graphics.o obj/physics.o obj/geometry.o obj/load.o obj/player.o $(SFMLFLAGS) $(LDFLAGS)

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