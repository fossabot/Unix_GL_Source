#ifndef __SCENE__
#define __SCENE__

#include "ustd.h"
#include "importer.h"
#include "skybox.h"



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
      Importer *m_importer;
      std::vector<Gameobject*>* m_gobjects;
      Camera* m_mainCamera;
      Skybox* skybox;
  };
}

#endif
