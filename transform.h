#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "ustd.h"




namespace OpenGLEngine {

  class Transform {

  public:
    Transform() {
      m_position = m_rotation = glm::vec3(0.0, 0.0, 0.0);
      m_scale = glm::vec3(1.0, 1.0, 1.0);
    }
    Transform(const glm::vec3& rotation, const glm::vec3& scale) {
      m_position = glm::vec3(0.0, 0.0, 0.0);
      m_rotation = glm::vec3(rotation);
      m_scale = glm::vec3(scale);
    }
    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
      m_position = glm::vec3(position);
      m_rotation = glm::vec3(rotation);
      m_scale = glm::vec3(scale);
    }
    Transform(const glm::vec3& scale) {
      m_position = glm::vec3(0.0, 0.0, 0.0);
      m_rotation = glm::vec3(0.0, 0.0, 0.0);
      m_scale = scale;
    }
    glm::mat4 Model() {
      glm::mat4 model_matrix = glm::mat4(1.0);
      glm::mat4 positionMatrix = glm::mat4(1.0);
      positionMatrix = glm::translate(positionMatrix, m_position);
      glm::vec3 radianRotation = glm::radians(m_rotation);
      glm::quat quaternion	 = glm::quat(radianRotation);
      glm::mat4 rotationMatrix = glm::toMat4(quaternion);
      glm::mat4 scaleMatrix = glm::mat4(1.0);
      scaleMatrix = glm::scale(scaleMatrix, m_scale);
      model_matrix = glm::mat4(positionMatrix * rotationMatrix * scaleMatrix);
      return model_matrix;
    }
    void setPosition(const glm::vec3& position) { m_position = position; }
    void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }
    void setScale(const glm::vec3& scale) { m_scale = scale; }
    glm::vec3 getPosition() { return  m_position; }
    glm::vec3 getRotation() { return m_rotation; }
    glm::vec3 getScale() { return m_scale; }
    void Rotate(const glm::vec3 rotation) { m_rotation += rotation; }
    void Scale(const glm::vec3 scale) { m_scale += scale; }
    void Translate(const glm::vec3 translation) { m_position += translation; }

  private:
    glm::vec3 m_position, m_rotation, m_scale;
  };

}

#endif
