#ifndef __ANIMATION__
#define __ANIMATION__

#include "ustd.hpp"



namespace OpenGLEngine {

  class AnimationChannel {
  public:
    std::string name;
    std::vector<glm::vec3> positions, scales;
    std::vector<glm::quat> rotations;
    
  };
  
  class Animation {

  public:
    std::vector<AnimationChannel> channels;
    double duration, ticksPerSecond;
    
  };
  
}


#endif
