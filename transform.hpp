#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "ustd.hpp"




namespace OpenGLEngine {

  class Transform {

    public:

      Transform() {

        this->position = this->rotation = glm::vec3(0.0, 0.0, 0.0);
        this->scale = glm::vec3(1.0, 1.0, 1.0);

      }
      inline glm::mat4 Model() const {

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
      inline void setPosition(const glm::vec3& position) { this->position = position; }
      inline void setRotation(const glm::vec3& rotation) { this->rotation = rotation; }
      inline void setScale(const glm::vec3& scale) { this->scale = scale; }
      inline glm::vec3& Position() { return  this->position; }
      inline glm::vec3& Rotation() { return this->rotation; }
      inline glm::vec3& Scale() { return this->scale; }


    private:

      glm::vec3 position, rotation, scale;

  };

}

#endif
