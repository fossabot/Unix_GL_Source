#ifndef __USTD__
#define __USTD__

// C HEADERS -----------------------------------
#include <stdio.h>
#include <stdlib.h>
// C++ HEADERS -----------------------------------
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <regex>
// ENGINE HEADERS -----------------------------------

#ifdef __APPLE__
  #include <OpenGL/gl3.h>
#elif __linux__
  #include <GL/glew.h>
  #include <GL/gl.h>
  #define GLM_FORCE_RADIANS
#endif
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"
// -----------------------------------

#endif
