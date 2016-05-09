#include "importer.h"

namespace OpenGLEngine {


  glm::mat4 assimp_to_glm_mat4(aiMatrix4x4 assimp) {

    glm::mat4 temp = glm::mat4 (
				assimp[0][0], assimp[0][1], assimp[0][2], assimp[0][3],
				assimp[1][0], assimp[1][1], assimp[1][2], assimp[1][3],
				assimp[2][0], assimp[2][1], assimp[2][2], assimp[2][3],
				assimp[3][0], assimp[3][1], assimp[3][2], assimp[3][3]);

    return temp;

  }

  void Importer::processNode(aiNode *node, const aiScene *scene, Gameobject* out, std::string path, unsigned int shaderType, const Mesh::ModelFormat model_format) {

    for(unsigned int i = 0; i < node->mNumMeshes; i++) {

      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      out->addMeshRenderer(processMesh(mesh, scene, path, shaderType, model_format));

    }

    for(unsigned int j = 0; j < node->mNumChildren; j++) {

      processNode(node->mChildren[j], scene, out, path, shaderType, model_format);

    }

  }

  MeshRenderer* Importer::processMesh(aiMesh* mesh, const aiScene* scene, std::string path, unsigned int shaderType, const Mesh::ModelFormat model_format) {

    MeshRenderer* mr = new MeshRenderer();

    std::vector<glm::vec3>* vertices = new std::vector<glm::vec3>();
    std::vector<glm::vec3>* normals = new std::vector<glm::vec3>();
    std::vector<glm::vec2>* coords = new std::vector<glm::vec2>();
    std::vector<unsigned int>* indices = new std::vector<unsigned int>();

    const std::string mesh_name =  std::string(mesh->mName.C_Str());
    Mesh* e_mesh;
    switch (model_format) {
      case Mesh::ModelFormat::FORMAT_DAE:
        e_mesh = new Mesh(glm::vec3(0.01, 0.01, 0.01));
      break;
      case Mesh::ModelFormat::FORMAT_OBJ:
        e_mesh = new Mesh(glm::vec3(0.5, 0.5, 0.5));
      break;
      default:
        e_mesh = new Mesh(glm::vec3(1.0, 1.0, 1.0));
      break;
    }

    Material* e_material = new Material();
    Shader* e_shader;
    if(shaderType == Shader::VERTEX_FRAGMENT_SHADERS)
      e_shader = new DefaultShader();
    else if(shaderType == Shader::VERTEX_GEOMETRY_FRAGMENT_SHADERS)
      e_shader = new GeometryShader();

    Texture* e_diffuse = new Texture();
    Texture* e_specular = new Texture();
    Texture* e_normal = new Texture();


    for(unsigned int v = 0; v < mesh->mNumVertices; v++) {

      vertices->push_back(glm::vec3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z));
      normals->push_back(glm::vec3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z));

      if(mesh->mTextureCoords[0]) {
	       coords->push_back(glm::vec2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y));
      } else {
	       coords->push_back(glm::vec2(1.0, 1.0));
      }

    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {

      aiFace face = mesh->mFaces[i];
      for(unsigned int j = 0; j < face.mNumIndices; j++) {
        indices->push_back(face.mIndices[j]);
      }

    }

    for(unsigned int m = 0; m < scene->mNumMaterials; m++) {

      aiMaterial* mat = scene->mMaterials[m];

      if(m == mesh->mMaterialIndex) {

        for(unsigned int i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++) {

          aiString str;
          mat->GetTexture(aiTextureType_DIFFUSE, i, &str);

          if(e_diffuse->loadTexture(std::string(path).append("/").append(str.C_Str()).c_str()));
          else
            std::cerr << "DIFFUSE TEXTURE NOT FOUND\n";

        }

        for(unsigned int i = 0; i < mat->GetTextureCount(aiTextureType_HEIGHT); i++) {

          aiString str;
          mat->GetTexture(aiTextureType_HEIGHT, i, &str);
          if(e_normal->loadTexture(std::string(path).append("/").append(str.C_Str()).c_str()));
          else
            std::cerr << "NORMAL TEXTURE FAILED\n";

        }

        for(unsigned int i = 0; i < mat->GetTextureCount(aiTextureType_SPECULAR); i++) {

          aiString str;
          mat->GetTexture(aiTextureType_SPECULAR, i, &str);
          if(e_specular->loadTexture(std::string(path).append("/").append(str.C_Str()).c_str()));
          else
            std::cerr << "SPECULAR TEXTURE FAILED\n";

        }

      }

    }

    e_mesh->loadGeometryToGpu(*vertices, *normals, *coords, *indices);

    if(shaderType == Shader::VERTEX_FRAGMENT_SHADERS)
      e_shader->loadShaderToGpu("assets/shaders/reflection/reflection");
    else if(shaderType == Shader::VERTEX_GEOMETRY_FRAGMENT_SHADERS)
      e_shader->loadShaderToGpu("assets/shaders/geometry/geometry");

    e_material->setShader(e_shader);
    e_material->setDiffuseTexture(e_diffuse);
    e_material->setNormalTexture(e_normal);
    e_material->setSpecularTexture(e_specular);


    vertices->clear();
    delete vertices;

    normals->clear();
    delete normals;

    coords->clear();
    delete coords;

    indices->clear();
    delete indices;

    mr->setMesh(e_mesh);
    mr->setMaterial(e_material);
    return mr;

  }


  Gameobject* Importer::importModel(std::string path, unsigned int shaderType) {

    Gameobject* out = new Gameobject();

    const aiScene* scene;
    Assimp::Importer importer;

    scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
      delete out;
      return NULL;
    }


    std::string s_format = path.substr(path.length()-4, path.length());
    Mesh::ModelFormat m_format;
    if (s_format == ".obj") {
      m_format = Mesh::ModelFormat::FORMAT_OBJ;
    } else if(s_format == ".dae") {
      m_format = Mesh::ModelFormat::FORMAT_DAE;
    }

    #ifdef __APPLE__

    std::regex pattern;
    if(m_format == Mesh::ModelFormat::FORMAT_OBJ)
      pattern = std::regex("(.*)\\/(.*)\\.obj");
    else if(m_format == Mesh::ModelFormat::FORMAT_DAE)
      patter = std::regex("(.*)\\/(.*)\\.dae");

    std::smatch pieces_match;
    if(std::regex_match(path, pieces_match, pattern)) {
      std::ssub_match sub_match = pieces_match[1];
      processNode(scene->mRootNode, scene, out, sub_match.str(), shaderType, m_format);
    }

    #elif __linux__
    unsigned int num_slashes = 1;
    unsigned int len_path = path.length() - 1;
    while(num_slashes > 0) {
      if(path[len_path] == '/')
	num_slashes--;

      len_path--;
    }
    std::string final = path.substr(0, len_path+1);
    processNode(scene->mRootNode, scene, out, final, shaderType, m_format);
    #endif

    return out;

  }

}
