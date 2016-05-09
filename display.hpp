#ifndef __DISPLAY__
#define __DISPLAY__

#include "ustd.hpp"
#include "scene.hpp"
#include "framebuffer.hpp"
#include "time.hpp"


#define MAX_CAPTURED_FRAMES 600


namespace OpenGLEngine {

  class Display{

    public:
      // INSTANCE & DESTRUCTORS --------------------------------------------------
      static Display* getInstance();
      ~Display();
      // -------------------------------------------------------------------------


      // FUNCTIONS ---------------------------------------------------------------
      void initialize();
      void update();
      void captureScreenshot();
      // -------------------------------------------------------------------------


      // WINDOW SURFACE MANAGEMENT -----------------------------------------------
      bool isRunning();
      int getWindowWidth();
      int getWindowHeight();
      void getDisplayResolution(int *x, int *y);
      // -------------------------------------------------------------------------

    private:
      // CONSTRUCTORS ------------------------------------------------------------
      Display(){
        m_width = 640, m_height = 720, m_mouseRelX = 0, m_mouseRelY = 0;
        m_running = false;
        m_scene = new Scene();
        m_framebuffer = new Framebuffer();
      };
      Display(Display const&){};
      static Display* m_instance;
      // -------------------------------------------------------------------------


      // WINDOW SURFACE MANAGEMENT -----------------------------------------------
      SDL_Window* m_window;
      SDL_GLContext m_context;
      void swapBuffers();
      int m_width, m_height, m_mouseRelX, m_mouseRelY;
      bool m_running, m_usingFramebuffer;
      // -------------------------------------------------------------------------


      // INPUT HANDLING -------------------------------------------
      void updateKeyboardAndMouse();
      // -------------------------------------------------------------------------


      // VARS --------------------------------------------------------------------
      Scene* m_scene;
      Framebuffer* m_framebuffer;
      unsigned int m_numEffects;
      std::string m_windowTitle, m_windowFps, m_windowEffect;
      int m_currentCapturedFrame;
      // -------------------------------------------------------------------------

  };

}

#endif
