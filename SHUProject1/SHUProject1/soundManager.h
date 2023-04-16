#pragma once
#include <assert.h>

struct SoundManager {

  // Attributes
private:

  // Functions
public:
  void initialise();
  void update();

private:
  void playBackgroundMusic();
  void playLaserSootSFX();
  void playExplosionSFX();
};