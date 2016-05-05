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
        width = 640, height = 720, mouseRelX = 0, mouseRelY = 0;
        running = false;
        scene = new Scene();
        framebuffer = new Framebuffer();

      };
      Display(Display const&){};
      static Display* instance;
      // -------------------------------------------------------------------------


      // WINDOW SURFACE MANAGEMENT -----------------------------------------------
      SDL_Window* window;
      SDL_GLContext context;
      void swapBuffers();
      int width, height, mouseRelX, mouseRelY;
      bool running, usingFramebuffer;
      // -------------------------------------------------------------------------


      // INPUT HANDLING -------------------------------------------
      void updateKeyboardAndMouse();
      // -------------------------------------------------------------------------


      // VARS --------------------------------------------------------------------
      Scene* scene;
      Framebuffer* framebuffer;
      unsigned int numEffects;
      std::string windowTitle, windowFps, windowEffect;
      int currentCapturedFrame;
      // -------------------------------------------------------------------------

  };

}

#endif
