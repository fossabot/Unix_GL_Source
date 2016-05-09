#include "framebuffer.hpp"


namespace OpenGLEngine {

  Framebuffer::Framebuffer() {

    shaderFilename = "assets/shaders/framebuffer/framebuffer";

  }

  Framebuffer::~Framebuffer() {

    clean();

  }

  void Framebuffer::clean() {

    glDeleteTextures(1, &texture_color0);
    glDeleteFramebuffers(1, &fbo);
    glDeleteRenderbuffers(1, &rbo);

    glDeleteBuffers(1, &quadVBO);
    glDeleteVertexArrays(1, &quadVAO);
    delete screenShader;
    delete screenCamera;
    delete transform;

  }

  void Framebuffer::reset(const std::string& filename, int width, int height) {

    clean();
    shaderFilename = filename;
    initialize(width, height);

  }

  void Framebuffer::initialize(int width, int height) {

    screenCamera = new Camera(glm::vec3(0.0, 0.0, 1.5), width, height);
    transform = new Transform();
    screenShader = new FramebufferShader();


    GLfloat quad[] = {
      -1.0f, 1.0f, 0.0f, 1.0f,
      -1.0f,-1.0f, 0.0f, 0.0f,
       1.0f,-1.0f, 1.0f, 0.0f,

      -1.0f, 1.0f, 0.0f, 1.0f,
       1.0f,-1.0f, 1.0f, 0.0f,
       1.0f, 1.0f, 1.0f, 1.0f,
    };
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), &quad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);
    screenShader->loadShaderToGpu(shaderFilename);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture_color0);
    glBindTexture(GL_TEXTURE_2D, texture_color0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_color0, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);


    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

  }

  void Framebuffer::bind() {

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

  }

  void Framebuffer::drawToScreen() {

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    screenShader->bind();
    screenShader->update(*transform, *screenCamera, 1.0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_color0);
    glUniform1i(glGetUniformLocation(screenShader->Program(), "screenTexture"), 0);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

  }

}
