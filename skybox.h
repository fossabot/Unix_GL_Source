#ifndef SKYBOX_H
#define SKYBOX_H

#include "ustd.h"
#include "shader_skybox.h"

namespace OpenGLEngine {

  class Skybox {
  public:
    Skybox();
    ~Skybox();
    void load();
    void bind(Camera camera, float deltaTime);

  private:
    GLuint m_quadVBO, m_quadVAO;
    SkyboxShader *m_skyboxShader;
    GLuint m_cubemap_texture_id;
    Transform *m_transform;
  };

}

#endif
