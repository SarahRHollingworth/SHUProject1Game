#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"

using namespace sf;

struct Laser {

  // Attributes
private:
  Sprite spr;
  Vector2f pos{ 0.0f, 0.0f };
  float velocity;

  // Functions
public:
  void initialise(RenderWindow&, Texture&);
  void update(RenderWindow&, float timeElapsed);
  void render(RenderWindow&);

private:
  void move(float timeElapsed);
  bool checkCollisionWithAsteroid(FloatRect*, Vector2f*, int&);
  bool checkForOutOfBounds();
};