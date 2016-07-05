COMPILER=clang++ -std=c++11
CDIR= $(shell pwd)


##############
#  Mac OS X  #
##############
INCLUDE= /usr/local/include
LIB= /usr/local/lib

SDL2_FRAMEWORK= /Library/Frameworks
ASSIMP= brew install assimp
ASSIMP_INC= /usr/local/Cellar/assimp/3.1.1/include
ASSIMP_LIB= /usr/local/Cellar/assimp/3.1.1/lib
GLM= brew install glm
GLM_INC= /usr/local/Cellar/glm/0.9.7.1/include





#######################
# BUILDING THE ENGINE #
#######################
Mac: display.o camera.o framebuffer.o gameobject.o importer.o main.o material.o mesh_renderer.o mesh.o scene.o shader.o \
				shader_default.o shader_geometry.o shader_framebuffer.o stb_image.o texture.o time.o skybox.o shader_skybox.o
	@$(COMPILER) -o ../program_mac \
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
								-I $(INCLUDE) -I $(ASSIMP_INC) -I $(GLM_INC) -L $(LIB) -framework OpenGL -L $(SDL2_FRAMEWORK) -framework SDL2 -L $(ASSIMP_LIB) -lassimp





#####################################
# SETUP THE SYSTEM LIBRARIES NEEDED #
#####################################
setup:
	$(ASSIMP) && $(GLM)





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
