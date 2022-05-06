# HELPER = LTexture.cpp Dot.cpp helper.cpp LTimer.cpp music.hpp sdl_helper.cpp server.hpp
OBJS = cop.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -I/opt/homebrew/Cellar/sdl2/2.0.20/include/SDL2 -I/opt/homebrew/Cellar/sdl2_mixer/2.0.4_3/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.0.5/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.0.18_1/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
OBJ_NAME = cop.o
all : $(OBJS)
	$(CC) -std=c++11 -v $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) -g
	
clean:
	-rm *.out *.o *.so

