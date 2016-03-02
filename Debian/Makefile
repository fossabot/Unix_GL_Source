COMPILER=clang++ -std=c++11
CDIR= $(shell pwd)
CPP_FILES= ../camera.cpp ../display.cpp ../framebuffer.cpp ../gameobject.cpp ../importer.cpp ../main.cpp ../manager.cpp ../material.cpp ../mesh_renderer.cpp ../mesh.cpp ../scene.cpp ../shader.cpp ../shader_default.cpp ../shader_framebuffer.cpp ../shader_geometry.cpp ../stb_image.c ../texture.cpp ../time.cpp


##################
#  Debian Linux  #
##################


LIBS= /usr/local/lib
INCLUDES= /usr/local/include

ESSENTIALS= sudo apt-get install build-essential && sudo apt-get install mesa-utils
GLM= sudo apt-get install libglm-dev
GLEW= sudo apt-get install libglew-dev
SDL2= sudo apt-get install libsdl2-dev
ASSIMP= sudo apt-get install libassimp-dev
CLANG= sudo apt-get install clang




Debian:
	$(COMPILER) -o ../program_debian $(CPP_FILES) -I $(INCLUDES) -L $(LIBS) -lGL -lSDL2 -lGLEW -lassimp

setup:
	$(ESSENTIALS) && $(SDL2) && $(GLEW) && $(GLM) && $(ASSIMP) && $(CLANG)
