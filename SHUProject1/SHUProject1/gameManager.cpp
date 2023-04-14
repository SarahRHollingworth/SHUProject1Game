#include "gameManager.h"

void GameManager::initialise(RenderWindow& window) {
  rocket_tx.loadFromFile("Assets/Rocket/RocketFlySpriteBatch.png");
  rocket.initialise(window, rocket_tx);
}

void GameManager::update(RenderWindow& window, float timeElapsed) {
  rocket.update(window, timeElapsed);
}

void GameManager::render(RenderWindow& window) {
  rocket.render(window);
}

void GameManager::updateScore(int amount) {

}

bool GameManager::getGameActive(){
  return gameActive;
}

int GameManager::getCurrentScore() {
  return currentScore;
}
