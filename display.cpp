#include "display.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"



namespace OpenGLEngine {

  // WINDOW SURFACE MANAGEMENT ---------------------------------------------------
  bool Display::isRunning() {
    return m_running;
  }
  int Display::getWindowWidth() {
    return m_width;
  }
  int Display::getWindowHeight() {
    return m_height;
  }
  void Display::getDisplayResolution(int *x, int *y) {
    *x = m_width; *y = m_height;
  }
  void Display::swapBuffers() {
    SDL_GetWindowSize(m_window, &m_width, &m_height);
    glViewport(0, 0, m_width, m_height);
    SDL_GL_SwapWindow(m_window);
  }
  // ------------------------------------------------

  // INSTANCE & DESTRUCTORS ------------------------------------------------------
  Display* Display::m_instance = nullptr;
  Display* Display::getInstance() {
    if(m_instance == nullptr)
      m_instance = new Display;

    return m_instance;
  }
  Display::~Display() {
    delete EngineTime::getInstance();
    SDL_GL_DeleteContext(m_context);
	  SDL_DestroyWindow(m_window);
    delete m_scene;
    delete m_framebuffer;
  }
  // -----------------------------------------------------------------------------



  // FUNCTIONS -------------------------------------------------------------------
  void Display::initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 1);

    m_window = SDL_CreateWindow("UnixGLEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);
    m_context = SDL_GL_CreateContext(m_window);

#ifdef __linux__
      glewExperimental=GL_TRUE;
      GLenum status = glewInit();
      if(status != GLEW_OK) {
          return;
      }
#endif
    std::cout << "Current OpenGL Version  :  " << glGetString(GL_VERSION);

    swapBuffers();
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    m_framebuffer->initialize(m_width, m_height);
    m_usingFramebuffer = true;
    m_scene->initialize(m_width, m_height);
    m_numEffects = 1;
    m_windowTitle = "GLSL TWEAKS  ";
    m_windowEffect = " [default] ";
    std::stringstream ss;
    ss << EngineTime::Fps();
    m_windowFps = ss.str();
    EngineTime::getInstance();
    EngineTime::start();
    m_currentCapturedFrame = 0;
    m_running = true;
  }

  void Display::update() {
    //Draw To Texture
    if(m_usingFramebuffer)
      m_framebuffer->bind();
    else {
      glEnable(GL_DEPTH_TEST);
      glClearColor(0.1, 0.1, 0.1, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    std::stringstream ss;
    ss << EngineTime::Fps();
    m_windowFps = ss.str();
    SDL_SetWindowTitle(m_window, std::string(m_windowTitle + m_windowFps + m_windowEffect).c_str());
    m_scene->render2D(EngineTime::DeltaTime());
    m_scene->render3D(EngineTime::DeltaTime());
    //Draw texture to screen
    if(m_usingFramebuffer)
      m_framebuffer->drawToScreen();

    if(m_currentCapturedFrame > 0) {
      captureScreenshot();
      m_currentCapturedFrame--;
    }
    swapBuffers();
    EngineTime::addFrame();
    updateKeyboardAndMouse();
  }

  void Display::captureScreenshot() {
    int pixels[m_width][m_height];
    glReadBuffer(GL_BACK);
    glPixelStoref(GL_UNPACK_ALIGNMENT, 1);
    glReadPixels(0, 0, m_height, m_width, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0][0]);
    int temp_num = m_currentCapturedFrame, digits = 0;
    while (temp_num)
    {
        temp_num /= 10;
        digits++;
    }
    std::stringstream ss;
    while (ss.str().length() + digits != 4)
    {
        ss << "0";
    }
    ss << m_currentCapturedFrame;
    stbi_write_png(std::string("assets/screenshots/shot").append(ss.str()).append(std::string(".png")).c_str(), m_height, m_width, 3, &pixels[0][0], 0);
  }
  // -----------------------------------------------------------------------------



  // 3D RENDERING & INPUT HANDLING -------------------------------------------
  void Display::updateKeyboardAndMouse() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT)
        m_running = false;

      if(e.type == SDL_KEYDOWN ) {
          if(e.key.keysym.sym == SDLK_SPACE) {
            switch (m_numEffects) {
              case 0:
                m_framebuffer->reset("assets/shaders/framebuffer/framebuffer", m_width, m_height);
                m_windowEffect = " [default] ";
              break;
              case 1:
                m_framebuffer->reset("assets/shaders/framebuffer_inverted/framebuffer_inverted", m_width, m_height);
                m_windowEffect = " [inverted] ";
              break;
              case 2:
                m_framebuffer->reset("assets/shaders/framebuffer_scanline/framebuffer_scanline", m_width, m_height);
                m_windowEffect = " [scanline] ";
              break;
              case 3:
                m_framebuffer->reset("assets/shaders/framebuffer_blur/framebuffer_blur", m_width, m_height);
                m_windowEffect = " [blur] ";
              break;
              case 4:
                m_framebuffer->reset("assets/shaders/framebuffer_godrays/framebuffer_godrays", m_width, m_height);
                m_windowEffect = " [godrays] ";
                m_numEffects = -1;
              break;
              default:
                m_numEffects = -1;
              break;
            }
            m_numEffects++;
            SDL_SetWindowTitle(m_window, std::string(m_windowTitle + m_windowFps + m_windowEffect).c_str());
          } else if(e.key.keysym.sym == SDLK_RSHIFT) {
            m_usingFramebuffer = !m_usingFramebuffer;
          } else if(e.key.keysym.sym == SDLK_RALT) {
            m_currentCapturedFrame = MAX_CAPTURED_FRAMES;
          }
      }
      m_scene->interruptKeyboard(e.type, e.key.keysym.sym);
      m_scene->interruptMouse(e.type, e.button.button);
    }
  }
  // -------------------------------------------------------------------------

}
