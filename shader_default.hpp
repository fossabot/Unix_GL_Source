#ifndef __SHADER_DEFAULT__
#define __SHADER_DEFAULT__

#include "ustd.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "component.hpp"
#include "shader.hpp"



namespace OpenGLEngine {

  class DefaultShader : public Shader {

    public:

      DefaultShader(unsigned int id, std::string name);
      virtual ~DefaultShader();
      virtual void initialize();
      void update(Transform worldTransform, Camera mainCamera, float deltaTime);

      void loadShaderToGpu(const std::string& filename);
      void bind();
      void unbind();
      GLuint Program();

    private:

      enum
      {
        VERTEX_SHADER,
        FRAGMENT_SHADER,

        NUM_SHADERS
      };
      enum
      {
        MODEL_U,
        VIEW_U,
        PROJECTION_U,
        CAMERA_POSITION,
        CAMERA_DIRECTION,
        DELTATIME,
        TIME,

        NUM_UNIFORMS
      };

      GLuint shaders[NUM_SHADERS];
      GLuint uniforms[NUM_UNIFORMS];

      GLuint program;

      GLuint createShader(const std::string& text, unsigned int type);
      std::string loadShaderCode(const std::string& filename);
      void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

      void setupAttributes();
      void linkNValidate();
      void setupUniforms();

  };

}

#endif
