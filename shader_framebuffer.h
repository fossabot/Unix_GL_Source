#ifndef __SHADER_FRAMEBUFFER__
#define __SHADER_FRAMEBUFFER__

#include "ustd.h"
#include "transform.h"
#include "camera.h"
#include "shader.h"


namespace OpenGLEngine {
  class FramebufferShader : public Shader {
    public:
      FramebufferShader();
      virtual ~FramebufferShader();
      void clean();
      void reset(const std::string& filename);
      virtual void initialize();
      virtual void update(Transform worldTransform, Camera mainCamera, float deltaTime);
      void loadShaderToGpu(const std::string& filename);
      virtual void bind();
      virtual void unbind();
      virtual GLuint Program();

    private:
      enum {
        VERTEX_SHADER,
        FRAGMENT_SHADER,

        NUM_SHADERS
      };
      enum {
        MODEL_U,
        VIEW_U,
        PROJECTION_U,
        CAMERA_POSITION,
        CAMERA_DIRECTION,
        DELTATIME,
        TIME,

        NUM_UNIFORMS
      };

      GLuint m_shaders[NUM_SHADERS];
      GLuint m_uniforms[NUM_UNIFORMS];
      GLuint m_program;

      GLuint createShader(const std::string& text, unsigned int type);
      std::string loadShaderCode(const std::string& filename);
      void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
      void setupAttributes();
      void linkNValidate();
      void setupUniforms();
  };
}

#endif
