COMPILER=g++ -std=c++11
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
Debian: display.o camera.o framebuffer.o gameobject.o importer.o main.o material.o mesh_renderer.o mesh.o scene.o shader.o \
				shader_default.o shader_geometry.o shader_framebuffer.o stb_image.o texture.o time.o skybox.o shader_skybox.o
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
								skybox.o \
								shader_skybox.o \
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
display.o: ../display.cpp ../display.h
	$(COMPILER) -c ../display.cpp

camera.o: ../camera.cpp ../camera.h
	$(COMPILER) -c ../camera.cpp

framebuffer.o: ../framebuffer.cpp ../framebuffer.h
	$(COMPILER) -c ../framebuffer.cpp

gameobject.o: ../gameobject.cpp ../gameobject.h
	$(COMPILER) -c ../gameobject.cpp

importer.o: ../importer.cpp ../importer.h
	$(COMPILER) -c ../importer.cpp

main.o: ../main.cpp
	$(COMPILER) -c ../main.cpp

material.o: ../material.cpp ../material.h
	$(COMPILER) -c ../material.cpp

mesh_renderer.o: ../mesh_renderer.cpp ../mesh_renderer.h
	$(COMPILER) -c ../mesh_renderer.cpp

mesh.o: ../mesh.cpp ../mesh.h
	$(COMPILER) -c ../mesh.cpp

scene.o: ../scene.cpp ../scene.h
	$(COMPILER) -c ../scene.cpp

shader.o: ../shader.cpp ../shader.h
	$(COMPILER) -c ../shader.cpp

shader_default.o: ../shader_default.cpp ../shader_default.h
	$(COMPILER) -c ../shader_default.cpp

shader_framebuffer.o: ../shader_framebuffer.cpp ../shader_framebuffer.h
	$(COMPILER) -c ../shader_framebuffer.cpp

shader_geometry.o: ../shader_geometry.cpp ../shader_geometry.h
	$(COMPILER) -c ../shader_geometry.cpp

stb_image.o: ../stb_image.cpp ../stb_image.h
	$(COMPILER) -c ../stb_image.cpp

texture.o: ../texture.cpp ../texture.h
	$(COMPILER) -c ../texture.cpp

time.o: ../time.cpp ../time.h
	$(COMPILER) -c ../time.cpp

skybox.o: ../skybox.cpp ../skybox.h
	$(COMPILER) -c ../skybox.cpp

shader_skybox.o: ../shader_skybox.cpp ../shader_skybox.h
	$(COMPILER) -c ../shader_skybox.cpp
