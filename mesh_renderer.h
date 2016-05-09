#ifndef __MESH_RENDERER__
#define __MESH_RENDERER__

#include "ustd.h"
#include "mesh.h"
#include "material.h"


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
