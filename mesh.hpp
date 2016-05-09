#ifndef __MESH__
#define __MESH__

#include "ustd.hpp"
#include "transform.hpp"


namespace OpenGLEngine {
  class Mesh {
  public:
    enum ModelFormat{
      FORMAT_OBJ,
      FORMAT_DAE,
    };
    Mesh(const glm::vec3& scale);
    ~Mesh();
    void loadGeometryToGpu(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> coords, std::vector<unsigned int> indices);
    void update();
    Transform& getTransform();

  private:
    GLuint m_vbo[4], m_vao;
    unsigned int m_indicesSize;
    Transform* m_transform;
  };
}

#endif
