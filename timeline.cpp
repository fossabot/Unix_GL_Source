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

  std::vector<Bone> Timeline::getUniqueBones(){
    
    std::vector<Bone> ubones;
    
        
    for(AnimationChannel ch : animations[0].channels){

      for(Bone bone : *bones){
	bool found = false;
	for(Bone ubone : ubones){
	  if(ubone.name == bone.name){
	    found = true;
	  }
	}
	if(!found){
	  if(ch.name == bone.name)
	    ubones.push_back(bone);
	}
      }

    }
    
    return ubones;
    
  }
  
}
