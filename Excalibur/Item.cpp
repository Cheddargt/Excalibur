#include "stdafx.h"
#include "Item.h"


Item::Item(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}


Item::~Item()
{
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
