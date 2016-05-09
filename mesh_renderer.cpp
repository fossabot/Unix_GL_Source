#include "mesh_renderer.hpp"



namespace OpenGLEngine {

  MeshRenderer::MeshRenderer() {}

  MeshRenderer::~MeshRenderer() {
    delete m_mesh;
    delete m_material;
  }

  void MeshRenderer::update(Camera mainCamera, float deltaTime) {
    m_material->bind(m_mesh->getTransform(), mainCamera, deltaTime);
    m_mesh->update();
    m_material->unbind();
  }

  void MeshRenderer::setMesh(Mesh* mesh) {
    m_mesh = mesh;
  }

  void MeshRenderer::setMaterial(Material* material) {
    m_material = material;
  }
}
