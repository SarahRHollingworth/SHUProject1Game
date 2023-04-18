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
  const float velocity = 200.0f;
  int type;
  bool active = false;
  bool exploding = false;

  const float maxDestroyAnimationTimer = 0.1f;
  float destroyAnimationTimer = maxDestroyAnimationTimer;

  int animationFrames = 2;
  int textureWidth;

  // Functions
public:
  void initialise(RenderWindow&, Texture&, RandomNumberGenerator*);
  void update(RenderWindow&, float timeElapsed);
  void render(RenderWindow&);

  bool checkForOutOfBounds(RenderWindow&);
  void destroy(Texture&);
  
  FloatRect GetGlobalBounds();
  Vector2f GetPosition();
  bool getActive();
  void setActive(bool active);
  bool getExploding();

private:
  void move(float timeElapsed);
  bool checkCollisionWithPlayer(FloatRect&, Vector2f&);
  void destroyAsteroidAnimation(float timeElapsed);
  void spin(float timeElapsed);
  int calcSpawnPosition(RenderWindow&);
  void applyTexture(Texture&, int animationFrames);
};