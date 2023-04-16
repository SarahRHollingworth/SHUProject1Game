#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"
#include "randomNumberGenerator.h"

using namespace sf;

struct Asteroid {

  // Attributes
private:
  RandomNumberGenerator* rng_ptr;

  Sprite spr;
  Vector2f pos{ 0.0f, 0.0f };
  const float velocity = 100.0f;
  int type;
  bool active = false;

  // Functions
public:
  void initialise(RenderWindow&, Texture&, RandomNumberGenerator*);
  void update(RenderWindow&, float timeElapsed);
  void render(RenderWindow&);

  bool checkForOutOfBounds(RenderWindow&);
  
  bool getActive();
  void setActive(bool active);

private:
  void move(float timeElapsed);
  bool checkCollisionWithPlayer(FloatRect&, Vector2f&);
  void destroyAsteroidAnimation();
  void spin(float timeElapsed);
  int calcSpawnPosition(RenderWindow&);
};