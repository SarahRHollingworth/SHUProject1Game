#include "rocket.h"

void Rocket::initialise(RenderWindow& window, Texture& texture){
	laser_tx.loadFromFile("Assets/Laser.png");

	applyTexture(texture, aliveAnimationFrames);

	spr.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100.0f);

	shootCooldown = maxShootCooldown;
	canFire = true;

	active = true;
	exploding = false;
}

void Rocket::update(RenderWindow& window, float timeElapsed, bool* inputs_arr){
	if (!exploding)
	{
		move(window, timeElapsed, inputs_arr);
		animateRocket(timeElapsed);
	}
	else
	{
		destroyRocketAnimation(timeElapsed);
	}

	for (int i = 0; i < lasers.size(); ++i)
	{
		lasers.at(i).update(window, timeElapsed);
		if (lasers.at(i).checkForOutOfBounds())
		{
			lasers.erase(lasers.begin() + i);
		}
	}

	if (!exploding)
	{
		if (!canFire)
			tickLaserCooldown(timeElapsed);

		if (*(inputs_arr + 2) && canFire)
			shootLaser(window);
	}
}

void Rocket::render(RenderWindow& window){
	for (int i = 0; i < lasers.size(); ++i)
	{
		lasers.at(i).render(window);
	}

	window.draw(spr);
}

void Rocket::takeDamage(int amount){

}

void Rocket::reset(RenderWindow& window, Texture& texture){
	spr.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100.0f);
	shootCooldown = maxShootCooldown;
	canFire = true;
	active = true;
	exploding = false;
	applyTexture(texture, aliveAnimationFrames);
	for (int i = 0; i < lasers.size(); ++i)
	{
		lasers.erase(lasers.begin() + i);
	}
}

bool Rocket::checkForLaserShootAsteroid(std::vector<FloatRect>* asteroidRect_vec, std::vector<Vector2f>* asteroidPos_vec, std::vector<int>* collidedAsteroids, int numberOfAsteroids) {
	std::vector<int> collidedLasers;
	
	for (int i = 0; i < lasers.size(); ++i)
	{
		int asteroidIndex = numberOfAsteroids;
		if (lasers.at(i).checkCollisionWithAsteroid(asteroidRect_vec, asteroidPos_vec, asteroidIndex))
		{
			collidedAsteroids->push_back(asteroidIndex);
			collidedLasers.push_back(i);
		}
	}

	for (int i = collidedLasers.size() - 1; i > -1; --i)
	{
		lasers.erase(lasers.begin() + collidedLasers.at(i));
	}

	return collidedAsteroids->size() > 0;
}

bool Rocket::checkForCollisionWithAsteroid(std::vector<FloatRect>* asteroidRect_vec, std::vector<Vector2f>* asteroidPos_vec, int& arrayIndex)
{
	bool found = false;

	float rocketHalfWidth = spr.getGlobalBounds().width / 2;
	float rocketHalfHeight = spr.getGlobalBounds().height / 2;

	float rocketLowerXBound = spr.getPosition().x - rocketHalfWidth;
	float rocketUpperXBound = spr.getPosition().x + rocketHalfWidth;
	float rocketLowerYBound = spr.getPosition().y - rocketHalfHeight;
	float rocketUpperYBound = spr.getPosition().y + rocketHalfHeight;

	for (int i = arrayIndex - 1; i > -1 && !found; --i)
	{
		float asteroidHalfWidth = asteroidRect_vec->at(i).width / 2;
		float asteroidHalfHeight = asteroidRect_vec->at(i).height / 2;

		float asteroidLowerXBound = asteroidPos_vec->at(i).x - asteroidHalfWidth;
		float asteroidUpperXBound = asteroidPos_vec->at(i).x + asteroidHalfWidth;
		float asteroidLowerYBound = asteroidPos_vec->at(i).y - asteroidHalfHeight;
		float asteroidUpperYBound = asteroidPos_vec->at(i).y + asteroidHalfHeight;

		if (rocketLowerXBound < asteroidUpperXBound && rocketUpperXBound > asteroidLowerXBound
			&& rocketLowerYBound < asteroidUpperYBound && rocketUpperYBound > asteroidUpperYBound)
		{
			found = true;
			arrayIndex = i;
		}
	}

	return found;
}

void Rocket::destroy(Texture& destroyTex) {
	exploding = true;
	applyTexture(destroyTex, destroyAnimationFrames);
}

void Rocket::move(RenderWindow& window, float timeElapsed, bool* inputs_arr){
	if (*inputs_arr && spr.getPosition().x > spr.getGlobalBounds().width / 2.0f)
		spr.move(-velocity * timeElapsed, 0.0f);
	
	if (*(inputs_arr + 1) && spr.getPosition().x < window.getSize().x - spr.getGlobalBounds().width / 2.0f)
		spr.move(velocity * timeElapsed, 0.0f);
}

void Rocket::shootLaser(RenderWindow& window){
	Laser l;
	lasers.push_back(l);

	lasers.at(lasers.size() - 1).initialise(window, laser_tx, spr.getPosition());

	shootCooldown = maxShootCooldown;
	canFire = false;
}

void Rocket::destroyRocketAnimation(float timeElapsed){
	destroyAnimationTimer -= timeElapsed;

	if (destroyAnimationTimer < 0.0f)
	{
		IntRect destroy_rect = spr.getTextureRect();

		if (destroy_rect.left < textureWidth * (destroyAnimationFrames - 1))
			destroy_rect.left += destroy_rect.width;
		else
		{
			active = false;
			exploding = false;
		}
		spr.setTextureRect(destroy_rect);
		destroyAnimationTimer = maxDestroyAnimationTimer;
	}
}

void Rocket::animateRocket(float timeElapsed){
	rocketAnimationTimer -= timeElapsed;

	if (rocketAnimationTimer < 0.0f)
	{
		IntRect rocket_rect = spr.getTextureRect();

		if (rocket_rect.left < textureWidth * (aliveAnimationFrames - 1))
			rocket_rect.left += rocket_rect.width;
		else
			rocket_rect.left = 0.0f;
		spr.setTextureRect(rocket_rect);
		rocketAnimationTimer = maxRocketAnimationTimer;
	}
}

void Rocket::tickLaserCooldown(float timeElapsed) {
	shootCooldown -= timeElapsed;

	canFire = shootCooldown < 0.0f;
}

void Rocket::applyTexture(Texture& texture, int animationFrames) {
	spr.setTexture(texture);
	Vector2u texSize = texture.getSize();
	textureWidth = texSize.x / animationFrames;
	IntRect asteroid_rect(0, 0, textureWidth, texSize.y);
	spr.setTextureRect(asteroid_rect);
	spr.setOrigin(asteroid_rect.width / 2.0f, asteroid_rect.height / 2.0f);
	spr.setScale(0.5f, 0.5f);
}

int Rocket::getHealth(){
	return health;
}

bool Rocket::getActive() {
	return active;
}

bool Rocket::getExploding() {
	return exploding;
}