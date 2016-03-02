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
    mainCamera = new Camera(glm::vec3(0.0, 0.0, 4.0), 512, 512);

    importer = new Importer();
    gobjects->push_back(importer->importModel("assets/models/monkey/monkey.obj", Shader::VERTEX_FRAGMENT_SHADERS));

  }

  void Scene::render2D(float deltaTime) {

    //r = ( cos(SDL_GetTicks()/150) ) ;

  }

  void Scene::render3D(float deltaTime) {

    for(Gameobject *go : *gobjects)
      go->update(mainCamera, deltaTime);

  }
  // ---------------------------------------------------------------------------------



  // INTERRUPTS ----------------------------------------------------------------------
  void Scene::interruptKeyboard(int type, int key) {

  }

  void Scene::interruptMouse(int type, int button) {

  }
  // ---------------------------------------------------------------------------------


  Camera* Scene::MainCamera() {

    return mainCamera;

  }

}
