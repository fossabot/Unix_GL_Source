#include "mesh_renderer.hpp"



namespace OpenGLEngine {

  MeshRenderer::MeshRenderer() {}

  MeshRenderer::~MeshRenderer() {

    delete mesh;
    delete material;

  }

  void MeshRenderer::update(Transform &worldTransform, Camera mainCamera, float deltaTime) {

    material->bind(worldTransform, mainCamera, deltaTime);
    mesh->update();
    material->unbind();

  }

  void MeshRenderer::setMesh(Mesh* mesh) {

    this->mesh = mesh;

  }

  void MeshRenderer::setMaterial(Material* material) {

    this->material = material;

  }

}
