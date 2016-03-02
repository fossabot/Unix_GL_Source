#include "time.hpp"


namespace OpenGLEngine {

  EngineTime* EngineTime::instance = nullptr;
  bool EngineTime::started = false, EngineTime::paused = false;
  unsigned int EngineTime::startTicks = 0, EngineTime::pauseTicks = 0, EngineTime::countedFrames = 0;

  EngineTime* EngineTime::getInstance() {

    if(instance == nullptr)
      instance = new EngineTime;

    return instance;

  }

  EngineTime::~EngineTime() {

  }

  void EngineTime::start() {

    started = true;
    paused = false;

    startTicks = SDL_GetTicks();
    pauseTicks = 0;

  }

  void EngineTime::pause() {

    if(started && !paused) {

        paused = true;
        pauseTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;

    }

  }

  void EngineTime::resume() {

    if(started && paused) {

        paused = false;
        startTicks = SDL_GetTicks() - pauseTicks;
        pauseTicks = 0;

    }

  }

  void EngineTime::stop() {

      started = false;
      paused = false;

      startTicks = pauseTicks = 0;

  }

  double EngineTime::DeltaTime() {

    unsigned int time = 0;
    if(started) {

      if(paused) {
        time = pauseTicks;
      } else {
          time = SDL_GetTicks() - startTicks;
      }

    }

    return time;

  }

  unsigned int EngineTime::Fps() {

    float avgFps = countedFrames / (DeltaTime() / 1000.0f);
    if(avgFps > 2000000) {
      avgFps = 0;
    }
    return (unsigned int)avgFps;

  }

  void EngineTime::addFrame() {
    countedFrames++;
  }


}
