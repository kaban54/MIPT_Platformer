CC = g++
CFLAGS += -Wall -Wformat=0 -std=c++23 -fPIC -DNDEBUG
LDFLAGS += -lstdc++
SFMLFLAGS += -lsfml-graphics -lsfml-window -lsfml-system
OBJDIR = obj/
SRCDIR = src/

all: jija ground1 bee plat cp mvplat

allW: wind ground1W beeW platW cpW mvplatW

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
	gcc -shared -o plugins/linux/ground1.so obj/load.o obj/vec2.o obj/geometry.o obj/ground1.o $(LDFLAGS)

ground1W:
	g++ -std=c++23 -D WIND ./src/ground1.cpp ./src/load.cpp ./src/vec2.cpp ./src/geometry.cpp -shared -o ./plugins/windows/ground1.dll

bee: obj/bee.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/linux/bee.so obj/load.o obj/vec2.o obj/geometry.o obj/bee.o $(LDFLAGS)

beeW:
	g++ -std=c++23 -D WIND ./src/bee.cpp ./src/load.cpp ./src/vec2.cpp ./src/geometry.cpp -shared -o ./plugins/windows/bee.dll

plat: obj/platform.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/linux/platform.so obj/load.o obj/vec2.o obj/geometry.o obj/platform.o $(LDFLAGS)

platW:
	g++ -std=c++23 -D WIND ./src/platform.cpp ./src/load.cpp ./src/vec2.cpp ./src/geometry.cpp -shared -o ./plugins/windows/platform.dll

cp: obj/checkpoint.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/linux/checkpoint.so obj/load.o obj/vec2.o obj/geometry.o obj/checkpoint.o $(LDFLAGS)

cpW:
	g++ -std=c++23 -D WIND ./src/checkpoint.cpp ./src/load.cpp ./src/vec2.cpp ./src/geometry.cpp -shared -o ./plugins/windows/checkpoint.dll

mvplat: obj/moving_platform.o obj/load.o obj/vec2.o obj/geometry.o
	gcc -shared -o plugins/linux/moving_platform.so obj/load.o obj/vec2.o obj/geometry.o obj/moving_platform.o $(LDFLAGS)

mvplatW:
	g++ -std=c++23 -D WIND ./src/moving_platform.cpp ./src/load.cpp ./src/vec2.cpp ./src/geometry.cpp -shared -o ./plugins/windows/moving_platform.dll

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

wind:
	g++ -std=c++23 -D WIND -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib                                             	            \
./src/main.cpp ./src/app.cpp ./src/camera.cpp ./src/geometry.cpp ./src/graphics.cpp ./src/level.cpp ./src/load.cpp  \
./src/lvlload.cpp ./src/object_man.cpp ./src/physics.cpp ./src/player.cpp ./src/sprite_man.cpp ./src/vec2.cpp       \
./src/gui.cpp ./src/widget.cpp                                                                                      \
-lm -o test.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

clean:
	rm obj/*.o -f
	clear
	
.PHONY: test