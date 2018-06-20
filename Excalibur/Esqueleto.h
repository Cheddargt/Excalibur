#pragma once
#include "stdafx.h"
#include "Inimigo.h"
class Esqueleto :
	public Inimigo
{
public:
	Esqueleto(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id);
	~Esqueleto();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);
	void ColidiuPersonagem(sf::Vector2f direcao, int dano);
	int getHealth() { return health; }
	void ColidiuObstaculo(sf::Vector2f direcao, int dano);


private:
	bool moveRight;
};

