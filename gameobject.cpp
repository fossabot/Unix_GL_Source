#include "gameobject.hpp"



namespace OpenGLEngine {

  Gameobject::Gameobject() {

    mesh_renderers = new std::vector<MeshRenderer*>();
    worldTransform = new Transform(glm::vec3(-90.0, 180.0, 0.0));

  }

  Gameobject::~Gameobject() {

    for(MeshRenderer *mr : *mesh_renderers)
      delete mr;

    mesh_renderers->clear();
    delete mesh_renderers;
    delete worldTransform;

  }

  void Gameobject::update(Camera mainCamera, float deltaTime) {

    worldTransform->getRotation().y += 0.01;

    for(MeshRenderer *mr : *mesh_renderers)
      mr->update(*worldTransform, mainCamera, deltaTime);

  }

  void Gameobject::addMeshRenderer(MeshRenderer* mesh_renderer) {

    mesh_renderers->push_back(mesh_renderer);

  }

}
