#include "element.h"

using namespace std;

element::element():texture(new sf::Texture())
{

}

element::element(string t):texture(new sf::Texture())
{
	if (!texture->loadFromFile(t)) {
		//exit(0);
	}
	this->setTexture(*texture);
}

element::element(sf::Texture  *t): texture(t)
{
	this->setTexture(*texture);
}

element::~element() {//TODO:: Przerobiæ na smartpointery
	delete texture;
};

void element::set_size(float x, float y)
{
	float scale_x = x / texture->getSize().x;
	float scale_y = y / texture->getSize().y;
	this->setScale(scale_x, scale_y);

}

sf::Texture* element::get_Texture()
{
	return texture;
}
