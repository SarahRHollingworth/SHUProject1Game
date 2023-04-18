#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"

#include "laser.h"

using namespace sf;

struct Rocket {

  // Attributes
private:
  Sprite spr;
  const int aliveAnimationFrames = 3;
  const int destroyAnimationFrames = 5;
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

  const float maxDestroyAnimationTimer = 0.1f;
  float destroyAnimationTimer = maxDestroyAnimationTimer;

  bool active = true;
  bool exploding = false;

  // Functions
public:
  void initialise(RenderWindow&, Texture&);
  void update(RenderWindow&, float timeElapsed, bool* inputs);
  void render(RenderWindow&);

  void takeDamage(int amount);
  void reset(RenderWindow&, Texture&);
  bool checkForLaserShootAsteroid(std::vector<FloatRect>*, std::vector<Vector2f>*, std::vector<int>* collidedAsteroids, int numberOfAsteroids);
  bool checkForCollisionWithAsteroid(std::vector<FloatRect>*, std::vector<Vector2f>*, int& arrayIndex);

  void destroy(Texture&);

  int getHealth();
  bool getActive();
  bool getExploding();

private:
  void move(RenderWindow&, float timeElapsed, bool* inputs);
  void shootLaser(RenderWindow&);
  void destroyRocketAnimation(float timeElapsed);
  void animateRocket(float timeElapsed);
  void tickLaserCooldown(float timeElapsed);
  void applyTexture(Texture&, int animationFrames);
};