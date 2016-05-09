COMPILER=clang++ -std=c++11
CDIR= $(shell pwd)


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





#######################
# BUILDING THE ENGINE #
#######################
Debian: display.o camera.o framebuffer.o gameobject.o importer.o main.o material.o mesh_renderer.o mesh.o scene.o shader.o shader_default.o shader_geometry.o shader_framebuffer.o stb_image.o texture.o time.o
	@$(COMPILER) -o ../program_debian \
								display.o \
								camera.o \
								framebuffer.o \
								gameobject.o \
								importer.o \
								main.o \
								material.o \
								mesh_renderer.o \
								mesh.o \
								scene.o \
								shader.o \
								shader_default.o \
								shader_geometry.o \
								shader_framebuffer.o \
								stb_image.o \
								texture.o \
								time.o \
								-I $(INCLUDES) -L $(LIBS) -lGL -lSDL2 -lGLEW -lassimp





#####################################
# SETUP THE SYSTEM LIBRARIES NEEDED #
#####################################
setup:
	$(ESSENTIALS) && $(SDL2) && $(GLEW) && $(GLM) && $(ASSIMP) && $(CLANG)







########################################
# CPP FILES AND OBJECTS TO BE COMPILED #
########################################
display.o: ../display.cpp ../display.hpp
	$(COMPILER) -c ../display.cpp

camera.o: ../camera.cpp ../camera.hpp
	$(COMPILER) -c ../camera.cpp

framebuffer.o: ../framebuffer.cpp ../framebuffer.hpp
	$(COMPILER) -c ../framebuffer.cpp

gameobject.o: ../gameobject.cpp ../gameobject.hpp
	$(COMPILER) -c ../gameobject.cpp

importer.o: ../importer.cpp ../importer.hpp
	$(COMPILER) -c ../importer.cpp

main.o: ../main.cpp
	$(COMPILER) -c ../main.cpp

material.o: ../material.cpp ../material.hpp
	$(COMPILER) -c ../material.cpp

mesh_renderer.o: ../mesh_renderer.cpp ../mesh_renderer.hpp
	$(COMPILER) -c ../mesh_renderer.cpp

mesh.o: ../mesh.cpp ../mesh.hpp
	$(COMPILER) -c ../mesh.cpp

scene.o: ../scene.cpp ../scene.hpp
	$(COMPILER) -c ../scene.cpp

shader.o: ../shader.cpp ../shader.hpp
	$(COMPILER) -c ../shader.cpp

shader_default.o: ../shader_default.cpp ../shader_default.hpp
	$(COMPILER) -c ../shader_default.cpp

shader_framebuffer.o: ../shader_framebuffer.cpp ../shader_framebuffer.hpp
	$(COMPILER) -c ../shader_framebuffer.cpp

shader_geometry.o: ../shader_geometry.cpp ../shader_geometry.hpp
	$(COMPILER) -c ../shader_geometry.cpp

stb_image.o: ../stb_image.cpp ../stb_image.h
	$(COMPILER) -c ../stb_image.cpp

texture.o: ../texture.cpp ../texture.hpp
	$(COMPILER) -c ../texture.cpp

time.o: ../time.cpp ../time.hpp
	$(COMPILER) -c ../time.cpp
