#include "material.h"



namespace OpenGLEngine {
  Material::Material() {}

  Material::~Material() {
    delete m_diffusetexture;
    delete m_normaltexture;
    delete m_speculartexture;
    delete m_shader;
  }

  void Material::bind(Transform worldTransform, Camera mainCamera, float deltaTime) {
    m_shader->bind();
    m_shader->update(worldTransform, mainCamera, deltaTime);
    m_diffusetexture->bind(m_shader->Program(), 0);
    m_normaltexture->bind(m_shader->Program(), 1);
    m_speculartexture->bind(m_shader->Program(), 2);
  }

  void Material::unbind() {
    m_shader->unbind();
    m_diffusetexture->unbind(0);
    m_normaltexture->unbind(1);
    m_speculartexture->unbind(2);
  }

  void Material::setShader(Shader *shader) {
    m_shader = shader;
  }

  void Material::setDiffuseTexture(Texture *texture) {
    m_diffusetexture = texture;
  }

  void Material::setNormalTexture(Texture *texture) {
    m_normaltexture = texture;
  }

  void Material::setSpecularTexture(Texture *texture) {
    m_speculartexture = texture;
  }
}
