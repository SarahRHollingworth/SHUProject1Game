#include "rocket.h"

void Rocket::initialise(RenderWindow& window, Texture& texture){
	spr.setTexture(texture);
	IntRect rocket_rect(0, 0, 175, 290);
	spr.setTextureRect(rocket_rect);
	spr.setOrigin(rocket_rect.width / 2.0f, rocket_rect.height / 2.0f);
	spr.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100.0f);
	spr.setScale(0.5f, 0.5f);
}

void Rocket::update(RenderWindow& window, float timeElapsed){
	animateRocket(timeElapsed);
}

void Rocket::render(RenderWindow& window){
	window.draw(spr);
}

void Rocket::takeDamage(int amount){

}

void Rocket::reset(){

}

void Rocket::move(float timeElapsed){

}

void Rocket::shootLaser(){

}

void Rocket::destroyRocketAnimation(){

}

void Rocket::animateRocket(float timeElapsed){
	rocketAnimationTimer -= timeElapsed;

	if (rocketAnimationTimer < 0.0f)
	{
		IntRect rocket_rect = spr.getTextureRect();
		if (rocket_rect.left < 350)
			rocket_rect.left += rocket_rect.width;
		else
			rocket_rect.left = 0.0f;
		spr.setTextureRect(rocket_rect);
		rocketAnimationTimer = maxRocketAnimationTimer;
	}
}

int Rocket::getHealth(){
	return health;
}