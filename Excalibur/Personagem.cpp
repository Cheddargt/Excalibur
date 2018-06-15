#include "stdafx.h"
#include "Personagem.h"

Personagem::Personagem(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id)
	: animacao(texture, imageCount, switchTime)
{
	this->switchTime = switchTime;
	this->speed = speed;
	this->health = health;
	this->attack = attack;
	this->id = id;

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);

}


Personagem::~Personagem()
{
}
