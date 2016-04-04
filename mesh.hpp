#ifndef __MESH__
#define __MESH__

#include "ustd.hpp"
#include "component.hpp"
#include "transform.hpp"
#include "skeleton.hpp"


namespace OpenGLEngine {

  class Mesh : public Component {

  public:

    enum ModelFormat{

      FORMAT_OBJ,
      FORMAT_FBX,
      FORMAT_DAE,
	
      NUM_MODEL_FORMAT

    };

    Mesh(unsigned int id, std::string name, const ModelFormat model_format);
    Mesh(unsigned int id, std::string name, glm::mat4 global_inverse_matrix);
    virtual ~Mesh();

    void loadGeometryToGpu(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> coords, std::vector<unsigned int> indices);
    void update();

    Transform& getTransform();

  private:

    GLuint vbo[4], vao;
    unsigned int indicesSize;
    Transform* transform;

  };

}

#endif
