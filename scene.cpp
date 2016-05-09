#include "scene.h"

namespace OpenGLEngine {

  // CONSTRUCTOR & DESTRUCTOR --------------------------------------------------------
  Scene::Scene() {}

  Scene::~Scene() {
    for(Gameobject *go : *m_gobjects)
      delete go;

    m_gobjects->clear();
    delete m_gobjects;

    delete m_importer;
    delete m_mainCamera;
    delete skybox;
  }
  // ---------------------------------------------------------------------------------



  // FUNCTIONS -----------------------------------------------------------------------
  void Scene::initialize(int width, int height) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_gobjects = new std::vector<Gameobject*>();
    m_mainCamera = new Camera(glm::vec3(0.0, 0.0, 2.0), width, height);
    m_importer = new Importer();
    m_gobjects->push_back(m_importer->importModel("assets/models/toy/toy.obj", Shader::VERTEX_FRAGMENT_SHADERS));
    skybox = new Skybox();
    skybox->load();
  }

  void Scene::render2D(float deltaTime) {
    //r = ( cos(SDL_GetTicks()/150) ) ;
  }

  void Scene::render3D(float deltaTime) {
    skybox->bind(*m_mainCamera, deltaTime);
    m_mainCamera->updateLocation(deltaTime);
    for(Gameobject *go : *m_gobjects)
      go->update(*m_mainCamera, deltaTime);
  }
  // ---------------------------------------------------------------------------------



  // INTERRUPTS ----------------------------------------------------------------------
  void Scene::interruptKeyboard(int type, int key) {
    if(type == SDL_KEYDOWN) {
      switch (key) {
        case SDLK_w:
          m_mainCamera->startMovingForward();
        break;
        case SDLK_s:
          m_mainCamera->startMovingBackward();
        break;
        case SDLK_d:
          m_mainCamera->startMovingRight();
        break;
        case SDLK_a:
          m_mainCamera->startMovingLeft();
        break;
      }
    } else if(type == SDL_KEYUP) {
      switch (key) {
        case SDLK_w:
          m_mainCamera->stopMovingForward();
        break;
        case SDLK_s:
          m_mainCamera->stopMovingBackward();
        break;
        case SDLK_d:
          m_mainCamera->stopMovingRight();
        break;
        case SDLK_a:
          m_mainCamera->stopMovingLeft();
        break;
      }
    }
  }

  void Scene::interruptMouse(int type, int button) {
    if(type == SDL_MOUSEMOTION) {
      int relX, relY;
      SDL_GetRelativeMouseState(&relX, &relY);
      m_mainCamera->updateDirection(relX, relY);
    } else if(type == SDL_MOUSEBUTTONDOWN) {
      m_mainCamera->setMouseDown(true);
    } else if(type == SDL_MOUSEBUTTONUP) {
      m_mainCamera->setMouseDown(false);
    }
  }
  // ---------------------------------------------------------------------------------


  Camera* Scene::MainCamera() {
    return m_mainCamera;
  }
}
