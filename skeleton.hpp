#ifndef __SKELETON__
#define __SKELETON__

#include "ustd.hpp"

#define NUM_BONES_PER_VERTEX 34

namespace OpenGLEngine {

  
  struct BoneConfig{
    unsigned int vertex_id;
    float weight;
  };

  struct Bone {

    Bone() {
      hirearchical_level = 0;
      configured = false;
    }
    unsigned int hirearchical_level;
    std::string name;
    glm::mat4 offsetMatrix;
    std::vector<BoneConfig> configs;
    bool configured;
  };
  
  class Skeleton {

  public:
    std::vector<Skeleton> children;
    
  };
  
}


#endif
