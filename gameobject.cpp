#include "gameobject.hpp"



namespace OpenGLEngine {

  Gameobject::Gameobject() {

    mesh_renderers = new std::vector<MeshRenderer*>();

  }

  Gameobject::~Gameobject() {

    for(MeshRenderer *mr : *mesh_renderers)
      delete mr;

    mesh_renderers->clear();
    delete mesh_renderers;

  }

  void Gameobject::update(Camera mainCamera, float deltaTime) {

    for(MeshRenderer *mr : *mesh_renderers)
      mr->update(mainCamera, deltaTime);

  }

  void Gameobject::addMeshRenderer(MeshRenderer* mesh_renderer) {

    mesh_renderers->push_back(mesh_renderer);

  }

}
