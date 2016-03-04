#include "importer.hpp"

namespace OpenGLEngine {


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
    std::vector<Bone>* bones = new std::vector<Bone>();


    const std::string mesh_name =  std::string(mesh->mName.C_Str());
    Mesh* e_mesh = new Mesh(Manager::addMesh(), mesh_name, model_format);
    Material* e_material = new Material(Manager::addMaterial(), mesh_name + ":material");
    Shader* e_shader;
    if(shaderType == Shader::VERTEX_FRAGMENT_SHADERS)
      e_shader = new DefaultShader(Manager::addShader(), mesh_name + ":shader");
    else if(shaderType == Shader::VERTEX_GEOMETRY_FRAGMENT_SHADERS)
      e_shader = new GeometryShader(Manager::addShader(), mesh_name + ":shader");

    Texture* e_diffuse = new Texture(Manager::addTexture(), mesh_name + ":diffuse_texture");
    Texture* e_specular = new Texture(Manager::addTexture(), mesh_name + ":specular_texture");
    Texture* e_normal = new Texture(Manager::addTexture(), mesh_name + ":normal_texture");



    for(unsigned int v = 0; v < mesh->mNumVertices; v++) {

      vertices->push_back(glm::vec3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z));
      normals->push_back(glm::vec3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z));

      if(mesh->mTextureCoords[0]) {
			     coords->push_back(glm::vec2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y));
      } else {
      			coords->push_back(glm::vec2(1.0, 1.0));
      }

    }

    for(unsigned int b = 0; b < mesh->mNumBones; b++) {

      Bone bone = Bone();
      bone.name = mesh->mBones[b]->mName.C_Str();

      for (unsigned int bw = 0; bw < mesh->mBones[b]->mNumWeights; bw++) {
        BoneWeight weight = BoneWeight();
        weight.vertex_id = mesh->mBones[b]->mWeights[bw].mVertexId;
        weight.weight = mesh->mBones[b]->mWeights[bw].mWeight;
        bone.weights.push_back(weight);
      }

      const aiMatrix4x4* from = &mesh->mBones[b]->mOffsetMatrix;
      bone.offsetMatrix[0][0] = (GLfloat)from->a1; bone.offsetMatrix[0][1] = (GLfloat)from->b1;  bone.offsetMatrix[0][2] = (GLfloat)from->c1; bone.offsetMatrix[0][3] = (GLfloat)from->d1;
      bone.offsetMatrix[1][0] = (GLfloat)from->a2; bone.offsetMatrix[1][1] = (GLfloat)from->b2;  bone.offsetMatrix[1][2] = (GLfloat)from->c2; bone.offsetMatrix[1][3] = (GLfloat)from->d2;
      bone.offsetMatrix[2][0] = (GLfloat)from->a3; bone.offsetMatrix[2][1] = (GLfloat)from->b3;  bone.offsetMatrix[2][2] = (GLfloat)from->c3; bone.offsetMatrix[2][3] = (GLfloat)from->d3;
      bone.offsetMatrix[3][0] = (GLfloat)from->a4; bone.offsetMatrix[3][1] = (GLfloat)from->b4;  bone.offsetMatrix[3][2] = (GLfloat)from->c4; bone.offsetMatrix[3][3] = (GLfloat)from->d4;

      bones->push_back(bone);

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

          if(e_diffuse->loadTexture(std::string(path).append("/").append(str.C_Str()).c_str()))
            e_diffuse->setName(mesh_name + ":diffuse:" + std::string(str.C_Str()));
          else
            std::cerr << "DIFFUSE TEXTURE NOT FOUND\n";

        }

        for(unsigned int i = 0; i < mat->GetTextureCount(aiTextureType_HEIGHT); i++) {

          aiString str;
          mat->GetTexture(aiTextureType_HEIGHT, i, &str);
          if(e_normal->loadTexture(std::string(path).append("/").append(str.C_Str()).c_str()))
            e_normal->setName(mesh_name + ":normal:" + std::string(str.C_Str()));
          else
            std::cerr << "NORMAL TEXTURE FAILED\n";

        }

        for(unsigned int i = 0; i < mat->GetTextureCount(aiTextureType_SPECULAR); i++) {

          aiString str;
          mat->GetTexture(aiTextureType_SPECULAR, i, &str);
          if(e_specular->loadTexture(std::string(path).append("/").append(str.C_Str()).c_str()))
            e_specular->setName(mesh_name + ":specular:" + std::string(str.C_Str()));
          else
            std::cerr << "SPECULAR TEXTURE FAILED\n";

        }

      }

    }

    e_mesh->loadGeometryToGpu(*vertices, *normals, *coords, *indices);

    if(shaderType == Shader::VERTEX_FRAGMENT_SHADERS)
      e_shader->loadShaderToGpu("assets/shaders/diffuse/diffuse");
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

    bones->clear();
    delete bones;

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
      return nullptr;
    }

    std::string s_format = path.substr(path.length()-4, path.length());
    Mesh::ModelFormat m_format;
    if (s_format == ".obj") {
      m_format = Mesh::ModelFormat::FORMAT_OBJ;
    } else if(s_format == ".fbx") {
      m_format = Mesh::ModelFormat::FORMAT_FBX;
    }

    #ifdef __APPLE__

      std::regex pattern;
      if(m_format == Mesh::ModelFormat::FORMAT_OBJ)
        pattern = std::regex("(.*)\\/(.*)\\.obj");
      else if(m_format == Mesh::ModelFormat::FORMAT_FBX)
        pattern = std::regex("(.*)\\/(.*)\\.fbx");
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
