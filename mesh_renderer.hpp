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
      void update(Transform* worldTransform, Camera* mainCamera, float deltaTime);
      void setMesh(Mesh* mesh);
      void setMaterial(Material* material);

    private:

      Mesh *mesh;
      Material *material;

  };

}


#endif
