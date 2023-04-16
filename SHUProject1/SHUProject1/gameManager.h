#pragma once
#include "rocket.h"
#include "asteroid.h"
#include "randomNumberGenerator.h"

struct GameManager {

  // Attributes
private:
  Rocket rocket;
  Texture rocket_tx;
  RandomNumberGenerator rng;

  Texture asteroid_tx[4];
  static const int maxAsteroids = 30;
  int numberOfAsteroids;
  Asteroid asteroid_Arr[maxAsteroids];
  int asteroidSpawnCounter;
  const float maxAsteroidSpawnTimer = 1.0f;
  float asteroidSpawnTimer;

  int currentScore;
  bool gameActive;

  // Functions
public:
  void initialise(RenderWindow&);
  void update(RenderWindow&, float timeElapsed, bool* inputs);
  void render(RenderWindow&);

  void reset(RenderWindow&);

  bool getGameActive();
  int getCurrentScore();

private:
  void updateScore(int amount);
  bool CheckAsteroidSpawnTimer(float timeElapsed);
  void SpawnAsteroid(RenderWindow&);
  int FindNextInactiveAsteroid();
};