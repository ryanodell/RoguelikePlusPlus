# OBJS specifies which files to compile as part of the project
OBJS = src\main.cpp src\backend.cpp src\core\logger.cpp src\core\ecs.cpp src\game.cpp src\systems.cpp src\core\event.cpp src\pch.cpp

# DEPS specifies the header files
DEPS = src\backend.h src\core\logger.h src\core\ecs.h src\core\macros.h src\math\vecs.h src\systems.h src\core\event.h src\pch.h

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\ExternalLibs\SDL2-2.29.3\i686-w64-mingw32\include\SDL2 \
                -IC:\ExternalLibs\SDL2_image\SDL2_image-2.8.2\i686-w64-mingw32\include\SDL2 \
                -IC:\ExternalLibs\SDL2_ttf\SDL2_ttf-2.22.0\i686-w64-mingw32\include\SDL2

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\ExternalLibs\SDL2-2.29.3\i686-w64-mingw32\lib \
                -LC:\ExternalLibs\SDL2_image\SDL2_image-2.8.2\i686-w64-mingw32\lib \
                -LC:\ExternalLibs\SDL2_ttf\SDL2_ttf-2.22.0\i686-w64-mingw32\lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -g enables debugging information
COMPILER_FLAGS = -w -g

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# OBJ_NAME specifies the name of our executable
OBJ_NAME = bin\main

# This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

# Dependencies
$(OBJS): $(DEPS)

