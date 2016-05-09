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
      GLuint m_quadVBO, m_quadVAO, m_texture_color0, m_fbo, m_rbo;
      FramebufferShader* m_screenShader;
      Camera* m_screenCamera;
      Transform* m_transform;
      std::string m_shaderFilename;
  };
}

#endif
