#ifndef __EngineTime__
#define __EngineTime__


#include "ustd.hpp"


namespace OpenGLEngine {

  class EngineTime {

    public:

      static EngineTime* getInstance();
      ~EngineTime();
      static void start();
      static void pause();
      static void resume();
      static void stop();
      static double DeltaTime();
      static unsigned int Fps();
      static void addFrame();

    private:

      EngineTime() {

        startTicks = pauseTicks = countedFrames = 0;

      };
      EngineTime(const EngineTime&){};
      static EngineTime* instance;

      static bool started, paused;
      static unsigned int startTicks, pauseTicks, countedFrames;

  };

}


#endif
