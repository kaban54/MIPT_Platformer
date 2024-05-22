CC = g++
CFLAGS += -Wall -Wformat=0 -std=c++23 -fPIC -DNDEBUG
LDFLAGS += -lstdc++
SFMLFLAGS += -lsfml-graphics -lsfml-window -lsfml-system
OBJDIR = obj/
SRCDIR = src/

all: jija ground1 bee plat cp mvplat

prepare:
	mkdir obj
	mkdir logs

jija: obj/main.o obj/app.o obj/camera.o obj/geometry.o obj/graphics.o obj/level.o obj/load.o \
	  obj/lvlload.o obj/object_man.o obj/physics.o obj/player.o obj/sprite_man.o obj/vec2.o  \
	  obj/gui.o obj/widget.o
	$(CC) -o jija obj/main.o obj/app.o obj/camera.o obj/geometry.o obj/graphics.o obj/level.o obj/load.o \
	              obj/lvlload.o obj/object_man.o obj/physics.o obj/player.o obj/sprite_man.o obj/vec2.o  \
			      obj/gui.o obj/widget.o $(SFMLFLAGS) $(LDFLAGS)

ground1: obj/ground1.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/ground1.so obj/load.o obj/vec2.o obj/geometry.o obj/ground1.o $(LDFLAGS)

bee: obj/bee.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/bee.so obj/load.o obj/vec2.o obj/geometry.o obj/bee.o $(LDFLAGS)

plat: obj/platform.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/platform.so obj/load.o obj/vec2.o obj/geometry.o obj/platform.o $(LDFLAGS)

cp: obj/checkpoint.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/checkpoint.so obj/load.o obj/vec2.o obj/geometry.o obj/checkpoint.o $(LDFLAGS)

mvplat: obj/moving_platform.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/moving_platform.so obj/load.o obj/vec2.o obj/geometry.o obj/moving_platform.o $(LDFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

wind:
	g++ -std=c++20 -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib                                             						\
./src/main.cpp ./src/app.cpp ./src/camera.cpp ./src/geometry.cpp ./src/graphics.cpp ./src/level.cpp ./src/load.cpp 	\
./src/lvlload.cpp ./src/object_man.cpp ./src/physics.cpp ./src/player.cpp ./src/sprite_man.cpp ./src/vec2.cpp    	\
./src/gui.cpp ./src/widget.cpp																						\
-lm -D WIND -o test.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

clean:
	rm obj/*.o -f
	clear
	
.PHONY: test