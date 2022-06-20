#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class animation
{

public:
	animation(sf::Texture* texture sf::Vector2u imageCount, float switchTime);
	~animation();

	sf::IntRect uvRect;
	//void Update(int row, float deltaTime);
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime; 
	float swithTime; //有多久要換下一張
};

animation::animation(sf::Texture* texture sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->swithTime = swithTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

}
