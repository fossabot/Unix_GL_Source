#ifndef __MESH_RENDERER__
#define __MESH_RENDERER__

#include "ustd.hpp"
#include "mesh.hpp"
#include "material.hpp"


namespace OpenGLEngine {
  class MeshRenderer {
    public:
      MeshRenderer();
      ~MeshRenderer();
      void update(Camera mainCamera, float deltaTime);
      void setMesh(Mesh* mesh);
      void setMaterial(Material* material);

    private:
      Mesh *m_mesh;
      Material *m_material;
  };
}


#endif
