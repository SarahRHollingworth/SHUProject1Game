#include "laser.h"

void Laser::initialise(RenderWindow& window, Texture& texture, Vector2f playerPos) {
	spr.setTexture(texture);
	Vector2u texSize = texture.getSize();
	IntRect laser_rect(0, 0, texSize.x, texSize.y);
	spr.setTextureRect(laser_rect);
	spr.setOrigin(laser_rect.width / 2.0f, laser_rect.height / 2.0f);
	spr.setPosition(playerPos);
	spr.setScale(0.5f, 0.5f);
}

void Laser::update(RenderWindow& window, float timeElapsed) {
	move(timeElapsed);
}

void Laser::render(RenderWindow& window) {
	window.draw(spr);
}

void Laser::move(float timeElapsed) {
	spr.move(0.0f, -velocity * timeElapsed);
}

bool Laser::checkCollisionWithAsteroid(FloatRect* asteroidRect_Arr, Vector2f* asteroidPos_Arr, int& arrayIndex) {
  return false;
}

bool Laser::checkForOutOfBounds() {
	return spr.getPosition().y < 0.0f - spr.getGlobalBounds().height / 2.0f;
}