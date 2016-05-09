#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "ustd.h"
#include "mesh_renderer.h"



namespace OpenGLEngine {
  class Gameobject {
    public:
      Gameobject();
      ~Gameobject();
      void update(Camera mainCamera, float deltaTime);
      void addMeshRenderer(MeshRenderer* mesh_renderer);

    private:
      std::vector<MeshRenderer*>* m_mesh_renderers;
  };
}

#endif
