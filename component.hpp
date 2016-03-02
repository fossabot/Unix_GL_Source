#ifndef __COMPONENT__
#define __COMPONENT__

#include "ustd.hpp"



namespace OpenGLEngine {

  class Component {

    public:

      Component(unsigned int id, std::string name) {

        this->id = id;
        this->name = name;
        this->enabled = true;

      }
      virtual ~Component() {}
      bool isEqual(Component &c1, Component &c2) {

        std::stringstream a, b;
        a << c1.name << c1.id;
        b << c2.name << c2.id;

        return (a.str() == b.str());

      }

      void setName(std::string name) { this->name = name; }

      unsigned int getId() { return this->id; }
      std::string getName() { return this->name; }
      bool isEnabled() { return this->enabled; }

    protected:
      unsigned int id;
      std::string name;
      bool enabled;

  };

}


#endif
