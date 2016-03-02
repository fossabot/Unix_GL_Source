#ifndef __TEXTURE__
#define __TEXTURE__

#include "ustd.hpp"
#include "component.hpp"


namespace OpenGLEngine {

  class Texture : public Component {

    public:

      Texture(unsigned int id, std::string name);
      ~Texture();
      static GLuint staticLoadTexture(const char *filename);
      bool loadTexture(const char *filename);
      void bind(GLuint shaderProgram, unsigned int padding);
      void unbind(unsigned int padding);

    private:

      GLuint texture_id;

  };

}

#endif
