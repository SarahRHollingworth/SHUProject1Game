#include "asteroid.h"

void Asteroid::initialise(RenderWindow& window, Texture& texture, RandomNumberGenerator* rng_ptr) {
  spr.setTexture(texture);
  Vector2u texSize = texture.getSize();
  IntRect asteroid_rect(0, 0, texSize.x, texSize.y);
  spr.setTextureRect(asteroid_rect);
  spr.setOrigin(asteroid_rect.width / 2.0f, asteroid_rect.height / 2.0f);
  spr.setScale(0.5f, 0.5f);

  this->rng_ptr = rng_ptr;

  spr.setPosition(calcSpawnPosition(window), -static_cast<float>(texSize.y));
  
  active = true;
}

void Asteroid::update(RenderWindow& window, float timeElapsed) {
  move(timeElapsed);
}

void Asteroid::render(RenderWindow& window) {
  window.draw(spr);
}

void Asteroid::move(float timeElapsed) {
  spr.move(0.0f, velocity * timeElapsed);
}

bool Asteroid::checkCollisionWithPlayer(FloatRect& playerRect, Vector2f& playerPos) {
  return false;
}

void Asteroid::destroyAsteroidAnimation() {

}

void Asteroid::spin(float timeElapsed) {

}

bool Asteroid::checkForOutOfBounds(RenderWindow& window) {
  return spr.getPosition().y > window.getSize().y + spr.getGlobalBounds().height / 2.0f;
}

int Asteroid::calcSpawnPosition(RenderWindow& window) {
  int halfSpriteWidth = spr.getLocalBounds().width / 2;
  return rng_ptr->getRandomNumber(halfSpriteWidth, window.getSize().x - halfSpriteWidth);
}

bool Asteroid::getActive() {
  return active;
}

void Asteroid::setActive(bool active) {
  this->active = active;
}