#ifndef __IMPORTER__
#define __IMPORTER__

#include "ustd.hpp"
#include "gameobject.hpp"

namespace OpenGLEngine {

  class Importer {

  public:

    Importer(){}
    ~Importer(){}
    Gameobject* importModel(std::string path, unsigned int shaderType);

  private:

    void processNode(aiNode *node, const aiScene *scene, Gameobject* out, std::string path, unsigned int shaderType, const Mesh::ModelFormat model_format);
    MeshRenderer* processMesh(aiMesh* mesh, const aiScene* scene, std::string path, unsigned int shaderType, const Mesh::ModelFormat model_format);
    glm::mat4 global_inverse_transform;

  };

}

#endif
