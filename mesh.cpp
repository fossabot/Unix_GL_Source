#include "mesh.hpp"


namespace OpenGLEngine {

  Mesh::Mesh(glm::mat4 global_inverse_matrix) {
    transform = new Transform(global_inverse_matrix);
  }

  Mesh::~Mesh() {

    for(unsigned int i = 0; i < 4; i++)
      glDeleteBuffers(1, &vbo[i]);

    glDeleteVertexArrays(1, &vao);

  }

  void Mesh::loadGeometryToGpu(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> coords, std::vector<unsigned int> indices) {
    indicesSize = indices.size();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(4, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(coords[0]), &coords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);


  }

  void Mesh::update() {

    transform->Rotate(glm::vec3(0.0, 0.1, 0.0));
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

  }

  Transform& Mesh::getTransform() {
    return *transform;
  }

}
