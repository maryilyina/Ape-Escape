#OBJS specifies which files to compile as part of the project
OBJS = game.cpp menu.cpp options.cpp scores.cpp levels_menu.cpp level.cpp level_1.cpp level_2.cpp level_3.cpp level_4.cpp level_5.cpp pause_menu.cpp win_menu.cpp actions.cpp graphics.cpp text.cpp audio.cpp main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Ape_Escape

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)


