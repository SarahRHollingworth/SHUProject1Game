#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"

#include "laser.h"

using namespace sf;

struct Rocket {

  // Attributes
private:
  Sprite spr;
  const int animationFrames = 3;
  int textureWidth;
  Vector2f pos{ 0.0f, 0.0f };
  float velocity;
  const float maxShootCooldown = 0.05f;
  float shootCooldown;
  bool canFire;
  int health;
  const float maxRocketAnimationTimer = 0.1f;
  float rocketAnimationTimer = maxRocketAnimationTimer;

  // Functions
public:
  void initialise(RenderWindow&, Texture&);
  void update(RenderWindow&, float timeElapsed);
  void render(RenderWindow&);

  void takeDamage(int amount);
  void reset();
  int getHealth();

private:
  void move(float timeElapsed);
  void shootLaser();
  void destroyRocketAnimation();
  void animateRocket(float timeElapsed);
};