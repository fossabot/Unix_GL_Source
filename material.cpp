#include "material.hpp"



namespace OpenGLEngine {

  Material::Material() {

  }

  Material::~Material() {

    delete diffusetexture;
    delete normaltexture;
    delete speculartexture;
    delete shader;

  }

  void Material::bind(Transform worldTransform, Camera mainCamera, float deltaTime) {

    shader->bind();
    shader->update(worldTransform, mainCamera, deltaTime);
    diffusetexture->bind(shader->Program(), 0);
    normaltexture->bind(shader->Program(), 1);
    speculartexture->bind(shader->Program(), 2);

  }

  void Material::unbind() {

    shader->unbind();
    diffusetexture->unbind(0);
    normaltexture->unbind(1);
    speculartexture->unbind(2);

  }

  void Material::setShader(Shader *shader) {

    this->shader = shader;

  }

  void Material::setDiffuseTexture(Texture *texture) {

    this->diffusetexture = texture;

  }

  void Material::setNormalTexture(Texture *texture) {

    this->normaltexture = texture;

  }

  void Material::setSpecularTexture(Texture *texture) {

    this->speculartexture = texture;

  }

}
