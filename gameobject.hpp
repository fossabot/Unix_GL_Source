#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "ustd.hpp"
#include "mesh_renderer.hpp"



namespace OpenGLEngine {

  class Gameobject {

    public:

      Gameobject();
      ~Gameobject();

      void update(Camera mainCamera, float deltaTime);
      void addMeshRenderer(MeshRenderer* mesh_renderer);

    private:

      std::vector<MeshRenderer*>* mesh_renderers;

  };

}

#endif
