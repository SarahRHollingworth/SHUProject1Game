#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"

using namespace sf;

struct Asteroid {

  // Attributes
private:
  Sprite spr;
  Vector2f pos{ 0.0f, 0.0f };
  float velocity;
  bool active;

  // Functions
public:
  void initialise(RenderWindow&, Texture&);
  void update(RenderWindow&, float timeElapsed);
  void render(RenderWindow&);

private:
  void move(float timeElapsed);
  bool checkCollisionWithPlayer(FloatRect&, Vector2f&);
  void destroyAsteroidAnimation();
  void spin(float timeElapsed);
  bool checkForOutOfBounds();
};