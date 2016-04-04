#ifndef __TIMELINE__
#define __TIMELINE__


#include "ustd.hpp"
#include "skeleton.hpp"
#include "animation.hpp"



namespace OpenGLEngine {

  class Timeline {
    
  public:
    static Timeline* getInstance();
    ~Timeline();

    void play();
    void pause();
    void next();
    
    std::vector<Animation> animations;
    std::vector<Bone>* bones;
    
  private:
    Timeline(){
      bones = new std::vector<Bone>();
    }
    Timeline(Timeline const&){};
    static Timeline* instance;
    
    
  };
  
}

#endif
