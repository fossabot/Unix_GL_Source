#ifndef __FRAMEBUFFER__
#define __FRAMEBUFFER__

#include "ustd.h"
#include "mesh.h"
#include "texture.h"
#include "shader_framebuffer.h"

namespace OpenGLEngine {
  class Framebuffer {
    public:
      Framebuffer();
      ~Framebuffer();
      void clean();
      void reset(const std::string& filename, int width, int height);
      void initialize(int width, int height);
      void bind();
      void drawToScreen(int width, int height);

    private:
      GLuint m_quadVBO, m_quadVAO, m_texture_color0, m_fbo, m_rbo, m_multisample_fbo, m_multisample_texture;
      FramebufferShader* m_screenShader;
      Camera* m_screenCamera;
      Transform* m_transform;
      std::string m_shaderFilename;
  };
}

#endif
