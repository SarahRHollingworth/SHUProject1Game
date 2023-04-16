#include "gameManager.h"

void GameManager::initialise(RenderWindow& window) {
  rng.seed(std::time(0));

  rocket_tx.loadFromFile("Assets/Rocket/RocketFlySpriteBatch.png");
  rocket.initialise(window, rocket_tx);

  asteroid_tx[0].loadFromFile("Assets/Asteroid/Asteroid1.png");
  asteroid_tx[1].loadFromFile("Assets/Asteroid/Asteroid2.png");
  asteroid_tx[2].loadFromFile("Assets/Asteroid/Asteroid3.png");
  asteroid_tx[3].loadFromFile("Assets/Asteroid/Asteroid4.png");

  currentScore = 0;
  numberOfAsteroids = 0;
  asteroidSpawnCounter = 0;
  asteroidSpawnTimer = maxAsteroidSpawnTimer;
}

void GameManager::update(RenderWindow& window, float timeElapsed) {
  rocket.update(window, timeElapsed);
  
  for (int i = 0; i < maxAsteroids; ++i)
  {
    if (asteroid_Arr[i].getActive())
    {
      asteroid_Arr[i].update(window, timeElapsed);
      if (asteroid_Arr[i].checkForOutOfBounds(window))
      {
        --numberOfAsteroids;
        asteroid_Arr[i].setActive(false);
      }
    }
  }

  if (numberOfAsteroids < maxAsteroids)
  {
    if (CheckAsteroidSpawnTimer(timeElapsed))
      SpawnAsteroid(window);
  }
}

void GameManager::render(RenderWindow& window) {
  rocket.render(window);

  for (int i = 0; i < maxAsteroids; ++i)
  {
    if (asteroid_Arr[i].getActive())
      asteroid_Arr[i].render(window);
  }
}

void GameManager::updateScore(int amount) {

}

void GameManager::reset()
{
  rng.seed(std::time(0));
  currentScore = 0;
  numberOfAsteroids = 0;
  asteroidSpawnCounter = 0;
  asteroidSpawnTimer = maxAsteroidSpawnTimer;
  for (int i = 0; i < maxAsteroids; ++i)
  {
    asteroid_Arr[i].setActive(false);
  }
  rocket.reset();
}

bool GameManager::CheckAsteroidSpawnTimer(float timeElapsed)
{
  asteroidSpawnTimer -= timeElapsed;

  if (asteroidSpawnTimer < 0.0f)
  {
    asteroidSpawnTimer = maxAsteroidSpawnTimer;
    return true;
  }

  return false;
}

void GameManager::SpawnAsteroid(RenderWindow& window)
{
  int spawnIndex = FindNextInactiveAsteroid();

  int randomNum = rng.getRandomNumber(0, 3);
  asteroid_Arr[spawnIndex].initialise(window, asteroid_tx[randomNum], &rng);

  ++numberOfAsteroids;
}

int GameManager::FindNextInactiveAsteroid()
{
  bool found;
  int position;

  do {
    found = !asteroid_Arr[asteroidSpawnCounter].getActive();
    position = asteroidSpawnCounter;

    if (asteroidSpawnCounter < maxAsteroids - 1)
      ++asteroidSpawnCounter;
    else
      asteroidSpawnCounter = 0;
  } while (!found);

  return position;
}

bool GameManager::getGameActive() {
  return gameActive;
}

int GameManager::getCurrentScore() {
  return currentScore;
}