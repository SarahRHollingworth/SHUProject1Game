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

  Texture laser_tx;
  std::vector<Laser> lasers;

  Vector2f pos{ 0.0f, 0.0f };
  float velocity = 200.0f;
  const float maxShootCooldown = 0.25f;
  float shootCooldown;
  bool canFire;
  int health;
  const float maxRocketAnimationTimer = 0.1f;
  float rocketAnimationTimer = maxRocketAnimationTimer;

  // Functions
public:
  void initialise(RenderWindow&, Texture&);
  void update(RenderWindow&, float timeElapsed, bool* inputs);
  void render(RenderWindow&);

  void takeDamage(int amount);
  void reset(RenderWindow&);
  int getHealth();

private:
  void move(RenderWindow&, float timeElapsed, bool* inputs);
  void shootLaser(RenderWindow&);
  void destroyRocketAnimation();
  void animateRocket(float timeElapsed);
  void tickLaserCooldown(float timeElapsed);
};