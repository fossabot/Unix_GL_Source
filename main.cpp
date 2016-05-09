#include "display.hpp"



int main(int argc, char* argv[]) {

  OpenGLEngine::Display* display = OpenGLEngine::Display::getInstance();
  display->initialize();

  std::cout << "\nCONTROLLING KEYS:\n" << "WSDA -> MOVING THE CAMERA\n" << "MOUSE MOTION -> ROTATING THE CAMERA AROUND ITS AXIS\n" << "SPACE BAR -> CHANGING POST-PROCESSING SHADER\n";

  while(display->isRunning()) {

    display->update();

  }

  delete OpenGLEngine::Display::getInstance();
  return 0;

}
