#include "sceneManager.h"

void SceneManager::initialise(RenderWindow& window) {
  initialiseBackground(window);
  gameManager.initialise(window, &utility);
}

void SceneManager::update(RenderWindow& window, float timeElapsed, bool* inputs_arr) {
  gameManager.update(window, timeElapsed, inputs_arr);
}

void SceneManager::render(RenderWindow& window) {
  drawBackground(window);
  gameManager.render(window);
}

void SceneManager::initialiseBackground(RenderWindow& window)
{
  background_tx.loadFromFile("Assets/Background.png");
  IntRect background_rect(0, 0, window.getSize().x, window.getSize().y);
  background_spr.setTexture(background_tx);
  background_spr.setTextureRect(background_rect);
}

void SceneManager::drawBackground(RenderWindow& window) {
  window.draw(background_spr);
}

void SceneManager::playGame() {

}

void SceneManager::quitGame() {

}