#pragma once
#include "rocket.h"
#include "asteroid.h"

struct GameManager {

  // Attributes
private:
  Rocket rocket;
  Texture rocket_tx;
  static const int maxAsteroids = 30;
  Asteroid asteroid_Arr[maxAsteroids];
  int currentScore;
  const float maxAsteroidSpawnTimer = 0.05f;
  float asteroidSpawnTimer;
  bool gameActive;

  // Functions
public:
  void initialise(RenderWindow&);
  void update(RenderWindow&, float timeElapsed);
  void render(RenderWindow&);

  bool getGameActive();
  int getCurrentScore();

private:
  void updateScore(int amount);
};