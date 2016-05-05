COMPILER=clang++ -std=c++11
CDIR= $(shell pwd)
CPP_FILES= ../camera.cpp ../display.cpp ../framebuffer.cpp ../gameobject.cpp ../importer.cpp ../main.cpp ../manager.cpp ../material.cpp ../mesh_renderer.cpp ../mesh.cpp ../scene.cpp ../shader.cpp ../shader_default.cpp ../shader_framebuffer.cpp ../shader_geometry.cpp ../stb_image.c ../texture.cpp ../time.cpp ../timeline.cpp ../skeleton.cpp


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



Mac:
	$(COMPILER) -o ../program_mac $(CPP_FILES) -I $(INCLUDE) -I $(ASSIMP_INC) -I $(GLM_INC) -L $(LIB) -framework OpenGL -L $(SDL2_FRAMEWORK) -framework SDL2 -L $(ASSIMP_LIB) -lassimp

setup:
	$(ASSIMP) && $(GLM)
