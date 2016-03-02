#include "display.hpp"



int main(int argc, char* argv[]) {

  OpenGLEngine::Display* display = OpenGLEngine::Display::getInstance();
  display->initialize();

  while(display->isRunning()) {

    display->update();

  }

  delete OpenGLEngine::Display::getInstance();
  return 0;

}
