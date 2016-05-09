#ifndef __SHADER__
#define __SHADER__

#include "ustd.hpp"
#include "transform.hpp"
#include "camera.hpp"



namespace OpenGLEngine {
  class Shader {
    public:
      Shader();
      virtual ~Shader();
      void clean();
      void reset(const std::string& filename);
      virtual void initialize();
      virtual void update(Transform worldTransform, Camera mainCamera, float deltaTime) = 0;
      virtual void loadShaderToGpu(const std::string& filename) = 0;
      virtual void bind() = 0;
      virtual void unbind() = 0;
      virtual GLuint Program() = 0;
      enum {
        VERTEX_FRAGMENT_SHADERS,
        VERTEX_GEOMETRY_FRAGMENT_SHADERS
      } SHADERTYPE;

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
