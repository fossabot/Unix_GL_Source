#include "texture.hpp"



namespace OpenGLEngine {


  GLuint Texture::staticLoadTexture(const char *filename) {

    GLuint texid;
    int width, height, numComponenets;
    unsigned char *data = stbi_load(filename, &width, &height, &numComponenets, 4);

    if (data == NULL) {

  			std::cerr << "TEXTURE LOADING FAILED \t FILENAME : " << filename << ".\n";
  			return false;

    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return texid;

  }

  Texture::Texture(unsigned int id, std::string name) : Component(id, name) {}

  Texture::~Texture() {

    glDeleteTextures(1, &texture_id);

  }

  bool Texture::loadTexture(const char *filename) {

    int width, height, numComponenets;
    unsigned char *data = stbi_load(filename, &width, &height, &numComponenets, 4);

    if (data == NULL) {

  			std::cerr << "TEXTURE LOADING FAILED \t FILENAME : " << filename << ".\n";
  			return false;

    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return true;

  }

  void Texture::bind(GLuint shaderProgram, unsigned int padding) {
    std::stringstream ss;
    ss << "texture_" << padding;
    glActiveTexture(GL_TEXTURE0 + padding);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(glGetUniformLocation(shaderProgram, ss.str().c_str()), padding);
  }

  void Texture::unbind(unsigned int padding) {
    glActiveTexture(GL_TEXTURE0 + padding);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

}
