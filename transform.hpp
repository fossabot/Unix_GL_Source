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

		glm::vec3 radianRotation = glm::radians(mRotation);	// Convert degree rotation angles to radians.

		glm::quat quaternion	 = glm::quat(radianRotation); // Generate a quaternion from radian rotation.

		glm::mat4 rotationMatrix = glm::toMat4(quaternion); // Construct a matrix from the quaternion vector.

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
