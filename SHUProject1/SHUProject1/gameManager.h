#pragma once
#include "rocket.h"
#include "asteroid.h"
#include "randomNumberGenerator.h"
#include "utility.h"

struct GameManager {

  // Attributes
private:
  Rocket rocket;
  Texture rocket_tx;
  Texture destroyRocket_tx;
  Texture asteroid_tx[4];
  Texture destroyAsteroid_tx;

  RandomNumberGenerator rng;
  Utility* utility_ptr;

  static const int maxAsteroids = 30;
  int numberOfAsteroids;
  Asteroid asteroid_Arr[maxAsteroids];
  int asteroidSpawnCounter;
  const float maxAsteroidSpawnTimer = 0.5f;
  float asteroidSpawnTimer;

  const float maxResetGameTimer = 1.0f;
  float resetGameTimer;

  int currentScore;
  bool gameActive;

  // Functions
public:
  void initialise(RenderWindow&, Utility*);
  void update(RenderWindow&, float timeElapsed, bool* inputs);
  void render(RenderWindow&);

  void reset(RenderWindow&);

  bool getGameActive();
  int getCurrentScore();

private:
  void updateScore(int amount);
  bool CheckResetGameTimer(float timeElapsed);
  bool CheckAsteroidSpawnTimer(float timeElapsed);
  void SpawnAsteroid(RenderWindow&);
  int FindNextInactiveAsteroid();
  void CheckForAsteroidCollision();
  int FindNextActiveAsteroid(int activeAsteroidNum);
};