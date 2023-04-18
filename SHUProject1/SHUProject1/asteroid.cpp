#include "asteroid.h"

void Asteroid::initialise(RenderWindow& window, Texture& texture, RandomNumberGenerator* rng_ptr) {
  applyTexture(texture, 1);

  this->rng_ptr = rng_ptr;

  spr.setPosition(calcSpawnPosition(window), -static_cast<float>(texture.getSize().y));
  
  active = true;
  exploding = false;
}

void Asteroid::update(RenderWindow& window, float timeElapsed) {
  if (active)
    move(timeElapsed);
  else
    destroyAsteroidAnimation(timeElapsed);
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

void Asteroid::destroyAsteroidAnimation(float timeElapsed) {
  destroyAnimationTimer -= timeElapsed;

  if (destroyAnimationTimer < 0.0f)
  {
    IntRect destroy_rect = spr.getTextureRect();

    if (destroy_rect.left < textureWidth * (animationFrames - 1))
      destroy_rect.left += destroy_rect.width;
    else
    {
      exploding = false;
    }
    spr.setTextureRect(destroy_rect);
    destroyAnimationTimer = maxDestroyAnimationTimer;
  }
}

void Asteroid::spin(float timeElapsed) {

}

bool Asteroid::checkForOutOfBounds(RenderWindow& window) {
  return spr.getPosition().y > window.getSize().y + spr.getGlobalBounds().height / 2.0f;
}

void Asteroid::destroy(Texture& destroyTex) {
  active = false;
  exploding = true;
  applyTexture(destroyTex, 2);
}

int Asteroid::calcSpawnPosition(RenderWindow& window) {
  int halfSpriteWidth = spr.getLocalBounds().width / 2;
  return rng_ptr->getRandomNumber(halfSpriteWidth, window.getSize().x - halfSpriteWidth);
}

void Asteroid::applyTexture(Texture& texture, int animationFrames) {
  spr.setTexture(texture);
  Vector2u texSize = texture.getSize();
  textureWidth = texSize.x / animationFrames;
  IntRect asteroid_rect(0, 0, textureWidth, texSize.y);
  spr.setTextureRect(asteroid_rect);
  spr.setOrigin(asteroid_rect.width / 2.0f, asteroid_rect.height / 2.0f);
  spr.setScale(0.5f, 0.5f);
}

FloatRect Asteroid::GetGlobalBounds() {
  return spr.getGlobalBounds();
}

Vector2f Asteroid::GetPosition() {
  return spr.getPosition();
}

bool Asteroid::getActive() {
  return active;
}

void Asteroid::setActive(bool active) {
  this->active = active;
}

bool Asteroid::getExploding() {
  return exploding;
}