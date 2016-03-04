#ifndef __SKELETON__
#define __SKELETON__

#include "ustd.hpp"



namespace OpenGLEngine {

  class BoneWeight {

    public:
        unsigned int vertex_id;
        float weight;

  };

  class Bone {

    public:
      std::string name;
      std::vector<BoneWeight> weights;
      glm::mat4 offsetMatrix;

  };

}


#endif
