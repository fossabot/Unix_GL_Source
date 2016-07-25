#include "skybox.h"


namespace OpenGLEngine {

  Skybox::Skybox() {
    m_transform = new Transform();
    m_transform->setScale(glm::vec3(100.0, 100.0, 100.0));
  }

  Skybox::~Skybox() {
    glDeleteBuffers(1, &m_quadVBO);
    glDeleteVertexArrays(1, &m_quadVAO);
    glDeleteTextures(1, &m_cubemap_texture_id);
    delete m_skyboxShader;
  }

  void Skybox::load() {
    GLfloat skyboxVertices[] = {
        // Positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &m_quadVBO);
    glBindVertexArray(m_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    std::vector<const char*> faces;
    faces.push_back("assets/textures/pos-x.png");
    faces.push_back("assets/textures/neg-x.png");
    faces.push_back("assets/textures/pos-y.png");
    faces.push_back("assets/textures/neg-y.png");
    faces.push_back("assets/textures/pos-z.png");
    faces.push_back("assets/textures/neg-z.png");

    glGenTextures(1, &m_cubemap_texture_id);
    glActiveTexture(GL_TEXTURE0);

    int width, height, numComponenets;
    unsigned char *data;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap_texture_id);
    for(unsigned int i=0; i<faces.size(); i++) {
      data = stbi_load(faces[i], &width, &height, &numComponenets, 3);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    m_skyboxShader = new SkyboxShader();
    m_skyboxShader->loadShaderToGpu("assets/shaders/skybox/skybox");
  }

  void Skybox::bind(Camera camera, float deltaTime) {
    m_transform->setPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z));
    glDepthMask(GL_FALSE);
    m_skyboxShader->bind();
    m_skyboxShader->update(*m_transform, camera, deltaTime);
    glBindVertexArray(m_quadVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap_texture_id);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
  }

  GLuint& Skybox::getCubemapTexture() {
    return m_cubemap_texture_id;
  }

}
