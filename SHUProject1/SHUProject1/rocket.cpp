#include "rocket.h"

void Rocket::initialise(RenderWindow& window, Texture& texture){
	laser_tx.loadFromFile("Assets/Laser.png");

	spr.setTexture(texture);
	Vector2u texSize = texture.getSize();
	textureWidth = texSize.x / animationFrames;
	IntRect rocket_rect(0, 0, textureWidth, texSize.y);
	spr.setTextureRect(rocket_rect);
	spr.setOrigin(rocket_rect.width / 2.0f, rocket_rect.height / 2.0f);
	spr.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100.0f);
	spr.setScale(0.5f, 0.5f);

	shootCooldown = maxShootCooldown;
	canFire = true;
}

void Rocket::update(RenderWindow& window, float timeElapsed, bool* inputs_arr){
	move(window, timeElapsed, inputs_arr);
	animateRocket(timeElapsed);

	for (int i = 0; i < lasers.size(); ++i)
	{
		lasers.at(i).update(window, timeElapsed);
		if (lasers.at(i).checkForOutOfBounds())
		{
			lasers.erase(lasers.begin() + i);
		}
	}

	if (!canFire)
		tickLaserCooldown(timeElapsed);

	if (*(inputs_arr + 2) && canFire)
		shootLaser(window);
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

void Rocket::reset(RenderWindow& window){
	spr.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100.0f);
	shootCooldown = maxShootCooldown;
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

void Rocket::destroyRocketAnimation(){

}

void Rocket::animateRocket(float timeElapsed){
	rocketAnimationTimer -= timeElapsed;

	if (rocketAnimationTimer < 0.0f)
	{
		IntRect rocket_rect = spr.getTextureRect();

		if (rocket_rect.left < textureWidth * (animationFrames - 1))
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

int Rocket::getHealth(){
	return health;
}