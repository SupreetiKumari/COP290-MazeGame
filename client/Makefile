# HELPER = LTexture.cpp Player.cpp setWalls.cpp
OBJS = player1.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJ_NAME = player1.out
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) -g
	
clean:
	-rm *.out *.o *.so
