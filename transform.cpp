#include "transform.hpp"



namespace OpenGLEngine {

  Transform::Transform() {

    this->position = this->rotation = glm::vec3(0.0, 0.0, 0.0);
    this->scale = glm::vec3(1.0, 1.0, 1.0);

  }

  Transform::Transform(const glm::vec3& rotation, const glm::vec3& scale) {

    this->rotation = glm::radians(glm::vec3(rotation.x, rotation.y, rotation.z));
    this->scale = glm::vec3(scale.x, scale.y, scale.z);
    this->position = glm::vec3(0.0, 0.0, 0.0);

  }

  glm::mat4 Transform::Model() {

    glm::mat4 positionMatrix = glm::mat4(1.0);
    positionMatrix = glm::translate(positionMatrix, position);
    glm::mat4 rotationXMatrix = glm::mat4(1.0);
    rotationXMatrix = glm::rotate(rotationXMatrix, rotation.x, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 rotationYMatrix = glm::mat4(1.0);
    rotationYMatrix = glm::rotate(rotationYMatrix, rotation.y, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotationZMatrix = glm::mat4(1.0);
    rotationZMatrix = glm::rotate(rotationZMatrix, rotation.z, glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;
    glm::mat4 scaleMatrix = glm::mat4(1.0);
    scaleMatrix = glm::scale(scaleMatrix, glm::vec3(scale.x, scale.y, scale.z));
    return positionMatrix * rotationMatrix * scaleMatrix;

  }

  void Transform::setPosition(const glm::vec3& position) { this->position = position; }
  void Transform::setRotation(const glm::vec3& rotation) { this->rotation = rotation; }
  void Transform::setScale(const glm::vec3& scale) { this->scale = scale; }
  glm::vec3& Transform::getPosition() { return  this->position; }
  glm::vec3& Transform::getRotation() { return this->rotation; }
  glm::vec3& Transform::getScale() { return this->scale; }

  glm::mat4 Transform::assimpToGLmMatrix(aiMatrix4x4* from) {

      glm::mat4 to;
      to[0][0] = (GLfloat)from->a1; to[0][1] = (GLfloat)from->b1;  to[0][2] = (GLfloat)from->c1; to[0][3] = (GLfloat)from->d1;
      to[1][0] = (GLfloat)from->a2; to[1][1] = (GLfloat)from->b2;  to[1][2] = (GLfloat)from->c2; to[1][3] = (GLfloat)from->d2;
      to[2][0] = (GLfloat)from->a3; to[2][1] = (GLfloat)from->b3;  to[2][2] = (GLfloat)from->c3; to[2][3] = (GLfloat)from->d3;
      to[3][0] = (GLfloat)from->a4; to[3][1] = (GLfloat)from->b4;  to[3][2] = (GLfloat)from->c4; to[3][3] = (GLfloat)from->d4;
      return to;

  }


}
