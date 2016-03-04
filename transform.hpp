#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "ustd.hpp"



namespace OpenGLEngine {

  class Transform {

    public:

      Transform();
      Transform(const glm::vec3& rotation);
      glm::mat4 Model();
      void setPosition(const glm::vec3& position);
      void setRotation(const glm::vec3& rotation);
      void setScale(const glm::vec3& scale);
      glm::vec3& getPosition();
      glm::vec3& getRotation();
      glm::vec3& getScale();
      static glm::mat4 assimpToGLmMatrix(aiMatrix4x4* from);

    private:

      glm::vec3 position, rotation, scale;

  };

}

#endif
