#include "gameManager.h"

void GameManager::initialise(RenderWindow& window, Utility* utility_ptr) {
  this->utility_ptr = utility_ptr;
  
  rng.seed(std::time(0));

  rocket_tx.loadFromFile("Assets/Rocket/RocketFlySpriteBatch.png");
  destroyRocket_tx.loadFromFile("Assets/Rocket/RocketDestroySpriteBatch.png");
  rocket.initialise(window, rocket_tx);

  asteroid_tx[0].loadFromFile("Assets/Asteroid/Asteroid1.png");
  asteroid_tx[1].loadFromFile("Assets/Asteroid/Asteroid2.png");
  asteroid_tx[2].loadFromFile("Assets/Asteroid/Asteroid3.png");
  asteroid_tx[3].loadFromFile("Assets/Asteroid/Asteroid4.png");

  destroyAsteroid_tx.loadFromFile("Assets/Asteroid/AsteroidDestroySpriteBatch.png");

  currentScore = 0;
  numberOfAsteroids = 0;
  asteroidSpawnCounter = 0;
  asteroidSpawnTimer = maxAsteroidSpawnTimer;
  resetGameTimer = maxResetGameTimer;
}

void GameManager::update(RenderWindow& window, float timeElapsed, bool* inputs_arr) {
  rocket.update(window, timeElapsed, inputs_arr);
  
  for (int i = 0; i < maxAsteroids; ++i)
  {
    bool asteroidActive = asteroid_Arr[i].getActive();
    if (asteroidActive || asteroid_Arr[i].getExploding())
      asteroid_Arr[i].update(window, timeElapsed);

    if (asteroidActive)
    {
      if (asteroid_Arr[i].checkForOutOfBounds(window))
      {
        --numberOfAsteroids;
        asteroid_Arr[i].setActive(false);
      }
    }
  }

  CheckForAsteroidCollision();

  if (numberOfAsteroids < maxAsteroids)
  {
    if (CheckAsteroidSpawnTimer(timeElapsed))
      SpawnAsteroid(window);
  }

  if (!rocket.getActive())
  {
    if (CheckResetGameTimer(timeElapsed))
      reset(window);
  }
}

void GameManager::render(RenderWindow& window) {
  if (rocket.getActive())
    rocket.render(window);

  for (int i = 0; i < maxAsteroids; ++i)
  {
    if (asteroid_Arr[i].getActive() || asteroid_Arr[i].getExploding())
      asteroid_Arr[i].render(window);
  }
}

void GameManager::updateScore(int amount) {

}

void GameManager::reset(RenderWindow& window)
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
  rocket.reset(window, rocket_tx);
  resetGameTimer = maxResetGameTimer;
}

bool GameManager::CheckResetGameTimer(float timeElapsed)
{
  resetGameTimer -= timeElapsed;

  if (resetGameTimer < 0.0f)
  {
    return true;
  }

  return false;
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

void GameManager::CheckForAsteroidCollision() {
  std::vector<FloatRect> asteroidRect_vec;
  std::vector<Vector2f> asteroidPos_vec;
  std::vector<int> collidedAsteroids;

  for (int i = 0; i < maxAsteroids; ++i) 
  {
    if (asteroid_Arr[i].getActive())
    {
      asteroidRect_vec.push_back(asteroid_Arr[i].GetGlobalBounds());
      asteroidPos_vec.push_back(asteroid_Arr[i].GetPosition());
    }
  }

  if (rocket.checkForLaserShootAsteroid(&asteroidRect_vec, &asteroidPos_vec, &collidedAsteroids, numberOfAsteroids))
  {
    for (int i = 0; i < collidedAsteroids.size(); ++i)
    {
      --numberOfAsteroids;
      int collidedAsteroidIndex = FindNextActiveAsteroid(collidedAsteroids.at(i));
      asteroid_Arr[collidedAsteroidIndex].destroy(destroyAsteroid_tx);
    }
      utility_ptr->BubbleSort(&collidedAsteroids);
      for (int i = collidedAsteroids.size() - 1; i > -1; --i)
      {
        asteroidRect_vec.erase(asteroidRect_vec.begin() + i);
        asteroidPos_vec.erase(asteroidPos_vec.begin() + i);
      }
  }

  if (rocket.getActive() && !rocket.getExploding())
  {
    int collidedAsteroidIndex = numberOfAsteroids;
    if (rocket.checkForCollisionWithAsteroid(&asteroidRect_vec, &asteroidPos_vec, collidedAsteroidIndex))
    {
      --numberOfAsteroids;
      asteroid_Arr[FindNextActiveAsteroid(collidedAsteroidIndex)].destroy(destroyAsteroid_tx);
      rocket.destroy(destroyRocket_tx);
    }
  }
}

int GameManager::FindNextActiveAsteroid(int activeAsteroidNum) {
  bool found = false;
  int pos = 0;
  int activeAsteroidCounter = 0;
  
  for (int i = 0; i < maxAsteroids && !found; ++i)
  {
    if (asteroid_Arr[i].getActive())
    {
      if (activeAsteroidCounter >= activeAsteroidNum)
      {
        found = true;
        pos = i;
      }
      else 
      {
        ++activeAsteroidCounter;
      }
    }
  }

  return pos;
}

bool GameManager::getGameActive() {
  return gameActive;
}

int GameManager::getCurrentScore() {
  return currentScore;
}