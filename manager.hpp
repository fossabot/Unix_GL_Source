#ifndef __MANAGER__
#define __MANAGER__

#include "ustd.hpp"




namespace OpenGLEngine {

  class Manager {

    public:

      static Manager* getInstance();
      ~Manager();
      static unsigned int addGameobject();
      static unsigned int addMesh();
      static unsigned int addMaterial();
      static unsigned int addShader();
      static unsigned int addTexture();

    private:

      Manager() {};
      Manager(Manager const&){};

      static Manager* instance;
      unsigned int gameobjects, meshes, materials, shaders, textures;

  };

}

#endif
