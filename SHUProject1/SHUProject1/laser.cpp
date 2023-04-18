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

bool Laser::checkCollisionWithAsteroid(std::vector<FloatRect>* asteroidRect_vec, std::vector<Vector2f>* asteroidPos_vec, int& arrayIndex) {
	bool found = false;

	float laserHalfWidth = spr.getGlobalBounds().width / 2;
	float laserHalfHeight = spr.getGlobalBounds().height / 2;

	float laserLowerXBound = spr.getPosition().x - laserHalfWidth;
	float laserUpperXBound = spr.getPosition().x + laserHalfWidth;
	float laserLowerYBound = spr.getPosition().y - laserHalfHeight;
	float laserUpperYBound = spr.getPosition().y + laserHalfHeight;
	
	for (int i = arrayIndex - 1; i > -1 && !found; --i)
	{
		float asteroidHalfWidth = asteroidRect_vec->at(i).width / 2;
		float asteroidHalfHeight = asteroidRect_vec->at(i).height / 2;

		float asteroidLowerXBound = asteroidPos_vec->at(i).x - asteroidHalfWidth;
		float asteroidUpperXBound = asteroidPos_vec->at(i).x + asteroidHalfWidth;
		float asteroidLowerYBound = asteroidPos_vec->at(i).y - asteroidHalfHeight;
		float asteroidUpperYBound = asteroidPos_vec->at(i).y + asteroidHalfHeight;

		if (laserLowerXBound < asteroidUpperXBound && laserUpperXBound > asteroidLowerXBound 
			&& laserLowerYBound < asteroidUpperYBound && laserUpperYBound > asteroidUpperYBound)
		{
			found = true;
			arrayIndex = i;
		}
	}

	return found;
}

bool Laser::checkForOutOfBounds() {
	return spr.getPosition().y < 0.0f - spr.getGlobalBounds().height / 2.0f;
}