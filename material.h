#ifndef __MATERIAL__
#define __MATERIAL__

#include "ustd.h"
#include "texture.h"
#include "shader.h"
#include "shader_default.h"
#include "shader_geometry.h"



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
