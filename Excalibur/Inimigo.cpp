#include "stdafx.h"
#include "Inimigo.h"

Inimigo::Inimigo(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id) : 
	Personagem (texture, imageCount, switchTime, speed, health, attack, id)
{
}


Inimigo::~Inimigo()
{
}
