COMPILER=clang++ -std=c++11
CDIR= $(shell pwd)


################
#  Arch Linux  #
################
LIBS= /usr/local/lib
INCLUDES= /usr/local/include

GLM= sudo pacman -S glm
ASSIMP= sudo pacman -S assimp
CLANG= sudo pacman -S clang
SDL2= sudo pacman -S sdl2





#######################
# BUILDING THE ENGINE #
#######################
Arch: display.o camera.o framebuffer.o gameobject.o importer.o main.o manager.o material.o mesh_renderer.o mesh.o scene.o shader.o shader_default.o shader_geometry.o shader_framebuffer.o stb_image.o texture.o time.o timeline.o skeleton.o
	$(COMPILER) -o ../program_arch \
								display.o \
								camera.o \
								framebuffer.o \
								gameobject.o \
								importer.o \
								main.o \
								manager.o \
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
								timeline.o \
								skeleton.o \
								-I $(INCLUDES) -L $(LIBS) -lGL -lSDL2 -lGLEW -lassimp






#####################################
# SETUP THE SYSTEM LIBRARIES NEEDED #
#####################################
setup:
	$(GLM) && $(ASSIMP) && $(CLANG) && $(SDL2)







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

manager.o: ../manager.cpp ../manager.hpp
	$(COMPILER) -c ../manager.cpp

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

stb_image.o: ../stb_image.c ../stb_image.h
	$(COMPILER) -c ../stb_image.c

texture.o: ../texture.cpp ../texture.hpp
	$(COMPILER) -c ../texture.cpp

time.o: ../time.cpp ../time.hpp
	$(COMPILER) -c ../time.cpp

timeline.o: ../timeline.cpp ../timeline.hpp
	$(COMPILER) -c ../timeline.cpp

skeleton.o: ../skeleton.cpp ../skeleton.hpp
	$(COMPILER) -c ../skeleton.cpp
