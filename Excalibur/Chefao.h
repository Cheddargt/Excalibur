#pragma once
#include "stdafx.h"
#include "Inimigo.h"

class Chefao :
	public Inimigo
{
public:
	Chefao(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id);
	~Chefao();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);
	void ColidiuPersonagem(sf::Vector2f direcao, int dano);

private:
	bool moveRight;
	bool moveUp;
	float tempoDescida;
	float tempoEsquerda;
	sf::Clock relogio1;
	sf::Clock relogio2;
};
