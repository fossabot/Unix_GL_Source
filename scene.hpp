#ifndef __SCENE__
#define __SCENE__

#include "ustd.hpp"
#include "importer.hpp"


namespace OpenGLEngine {

  class Scene {

    public:

      Scene();
      ~Scene();
      void initialize(int width, int height);
      void render2D(float deltaTime);
      void render3D(float deltaTime);
      void interruptKeyboard(int type, int key);
      void interruptMouse(int type, int button);

      Camera* MainCamera();

    private:
      Importer *importer;
      std::vector<Gameobject*>* gobjects;
      Camera* mainCamera;
  };

}

#endif
