#include "scene.hpp"

namespace OpenGLEngine {

  // CONSTRUCTOR & DESTRUCTOR --------------------------------------------------------
  Scene::Scene() {

  }

  Scene::~Scene() {

    for(Gameobject *go : *gobjects)
      delete go;

    gobjects->clear();
    delete gobjects;

    delete importer;
    delete mainCamera;

  }
  // ---------------------------------------------------------------------------------



  // FUNCTIONS -----------------------------------------------------------------------
  void Scene::initialize() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gobjects = new std::vector<Gameobject*>();
    mainCamera = new Camera(glm::vec3(0.0, 1.1, 3.0), 512, 512);

    importer = new Importer();
    gobjects->push_back(importer->importModel("assets/models/nervous/nervous.dae", Shader::VERTEX_FRAGMENT_SHADERS));

  }

  void Scene::render2D(float deltaTime) {

    //r = ( cos(SDL_GetTicks()/150) ) ;

  }

  void Scene::render3D(float deltaTime) {

    mainCamera->updateLocation(deltaTime);

    for(Gameobject *go : *gobjects)
      go->update(*mainCamera, deltaTime);

  }
  // ---------------------------------------------------------------------------------



  // INTERRUPTS ----------------------------------------------------------------------
  void Scene::interruptKeyboard(int type, int key) {

    if(type == SDL_KEYDOWN) {

      switch (key) {

        case SDLK_w:
          mainCamera->startMovingForward();
        break;

        case SDLK_s:
          mainCamera->startMovingBackward();
        break;

        case SDLK_d:
          mainCamera->startMovingRight();
        break;

        case SDLK_a:
          mainCamera->startMovingLeft();
        break;

      }

    } else if(type == SDL_KEYUP) {

      switch (key) {

        case SDLK_w:
          mainCamera->stopMovingForward();
        break;

        case SDLK_s:
          mainCamera->stopMovingBackward();
        break;

        case SDLK_d:
          mainCamera->stopMovingRight();
        break;

        case SDLK_a:
          mainCamera->stopMovingLeft();
        break;

      }

    }
  }

  void Scene::interruptMouse(int type, int button) {

    if(type == SDL_MOUSEMOTION) {

      int relX, relY;
      SDL_GetRelativeMouseState(&relX, &relY);
      mainCamera->updateDirection(relX, relY);

    } else if(type == SDL_MOUSEBUTTONDOWN) {
      mainCamera->setMouseDown(true);
    } else if(type == SDL_MOUSEBUTTONUP) {
      mainCamera->setMouseDown(false);
    }

  }
  // ---------------------------------------------------------------------------------


  Camera* Scene::MainCamera() {

    return mainCamera;

  }

}
