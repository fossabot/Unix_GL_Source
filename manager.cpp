#include "manager.hpp"



namespace OpenGLEngine {

  Manager* Manager::instance = nullptr;
  Manager* Manager::getInstance() {

    if(instance == nullptr)
      instance = new Manager;

    return instance;

  }

  Manager::~Manager() {}

  unsigned int Manager::addGameobject() {

    if(instance == nullptr)
      instance = new Manager;

    return instance->gameobjects++;

  }

  unsigned int Manager::addMesh() {

    if(instance == nullptr)
      instance = new Manager;

    return instance->meshes++;

  }

  unsigned int Manager::addMaterial() {

    if(instance == nullptr)
      instance = new Manager;

    return instance->materials++;

  }

  unsigned int Manager::addShader() {

    if(instance == nullptr)
      instance = new Manager;

    return instance->shaders++;

  }

  unsigned int Manager::addTexture() {

    if(instance == nullptr)
      instance = new Manager;

    return instance->textures++;

  }




}
