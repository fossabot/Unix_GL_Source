#include "gameobject.hpp"



namespace OpenGLEngine {
  Gameobject::Gameobject() {
    m_mesh_renderers = new std::vector<MeshRenderer*>();
  }

  Gameobject::~Gameobject() {
    for(MeshRenderer *mr : *m_mesh_renderers)
      delete mr;

    m_mesh_renderers->clear();
    delete m_mesh_renderers;
  }

  void Gameobject::update(Camera mainCamera, float deltaTime) {
    for(MeshRenderer *mr : *m_mesh_renderers)
      mr->update(mainCamera, deltaTime);
  }

  void Gameobject::addMeshRenderer(MeshRenderer* mesh_renderer) {
    m_mesh_renderers->push_back(mesh_renderer);
  }
}
