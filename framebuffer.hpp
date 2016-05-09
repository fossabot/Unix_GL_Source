#ifndef __FRAMEBUFFER__
#define __FRAMEBUFFER__

#include "ustd.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "shader_framebuffer.hpp"

namespace OpenGLEngine {

  class Framebuffer {

    public:

      Framebuffer();
      ~Framebuffer();

      void clean();
      void reset(const std::string& filename, int width, int height);
      void initialize(int width, int height);
      void bind();
      void drawToScreen();

    private:

      GLuint quadVBO, quadVAO, texture_color0, fbo, rbo;
      FramebufferShader* screenShader;
      Camera* screenCamera;
      Transform* transform;
      std::string shaderFilename;

  };

}

#endif
