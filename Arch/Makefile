COMPILER=clang++ -std=c++11
CDIR= $(shell pwd)
CPP_FILES= ../transform.cpp ../camera.cpp ../display.cpp ../framebuffer.cpp ../gameobject.cpp ../importer.cpp ../main.cpp ../manager.cpp ../material.cpp ../mesh_renderer.cpp ../mesh.cpp ../scene.cpp ../shader.cpp ../shader_default.cpp ../shader_framebuffer.cpp ../shader_geometry.cpp ../stb_image.c ../texture.cpp ../time.cpp


################
#  Arch Linux  #
################


LIBS= /usr/local/lib
INCLUDES= /usr/local/include

GLM= sudo pacman -S glm
ASSIMP= sudo pacman -S assimp
CLANG= sudo pacman -S clang



Arch:
	$(COMPILER) -o ../program_arch $(CPP_FILES) -I $(INCLUDES) -L $(LIBS) -lGL -lSDL2 -lGLEW -lassimp

setup:
	$(GLM) && $(ASSIMP) && $(CLANG)
