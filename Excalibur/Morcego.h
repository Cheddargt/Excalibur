#pragma once
#include "Inimigo.h"

class Morcego :
	public Inimigo
{
public:
	Morcego(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id);
	~Morcego();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);

private:
	bool moveRight;
	bool moveUp;
};

