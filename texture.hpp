#ifndef __TEXTURE__
#define __TEXTURE__

#include "ustd.hpp"


namespace OpenGLEngine {
  class Texture {
    public:
      Texture();
      ~Texture();
      static GLuint staticLoadTexture(const char *filename);
      bool loadTexture(const char *filename);
      void bind(GLuint shaderProgram, unsigned int padding);
      void unbind(unsigned int padding);

    private:
      GLuint m_texture_id;
  };
}

#endif
