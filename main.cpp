#include "display.hpp"



int main(int argc, char* argv[]) {

  OpenGLEngine::Display* display = OpenGLEngine::Display::getInstance();
  display->initialize();

  std::cout << "\n\n\tCONTROLLING KEYS:\n" << "\tWSDA -> MOVING THE CAMERA\n" << "\tMOUSE MOTION -> ROTATING THE CAMERA AROUND ITS AXIS\n" << "\tSPACE BAR -> CHANGING POST-PROCESSING SHADER\n\n";

  while(display->isRunning()) {

    display->update();

  }

  delete OpenGLEngine::Display::getInstance();
  return 0;

}
