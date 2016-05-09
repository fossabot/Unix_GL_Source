#ifndef __MATERIAL__
#define __MATERIAL__

#include "ustd.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "shader_default.hpp"
#include "shader_geometry.hpp"


namespace OpenGLEngine {
  class Material {
    public:
      Material();
      ~Material();
      void bind(Transform worldTransform, Camera mainCamera, float deltaTime);
      void unbind();
      void setShader(Shader *shader);
      void setDiffuseTexture(Texture *texture);
      void setNormalTexture(Texture *texture);
      void setSpecularTexture(Texture *texture);

    private:
      Texture *m_diffusetexture, *m_normaltexture, *m_speculartexture;
      Shader *m_shader;
  };
}


#endif
