#include "timeline.hpp"



namespace OpenGLEngine {

  Timeline* Timeline::instance = NULL;
  Timeline* Timeline::getInstance() {

    if(instance == NULL)
      instance = new Timeline;

    return instance;
    
  }

  Timeline::~Timeline(){

    bones->clear();
    delete bones;
    
  }

  void Timeline::play(){

    for(Animation anim : animations){
      std::cout << "\n\nDuration:\t" <<  anim.duration << std::endl;
      for(AnimationChannel ac : anim.channels){
	std::cout << ac.name << "\t" << ac.positions.size() << " / " << ac.scales.size() << " / " << ac.rotations.size() << std::endl;
      }
      std::cout << anim.channels.size() << std::endl;
    }
    
  }

  void Timeline::pause(){

  }

  void Timeline::next(){

  }
  
}
