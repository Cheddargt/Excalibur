#pragma once
#include <SFML\Graphics.hpp>
#include "Animacao.h"
#include "Colisor.h"
#include "stdafx.h"

class Personagem
{
protected:
	float switchTime;
	float speed;
	int health;
	int attack;
	int id;
	sf::RectangleShape body; //personagem
	Animacao animacao; //personagem
	unsigned int row; //personagem
	bool faceRight; //personagem

public:
	Personagem(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id);
	virtual ~Personagem();

	virtual void Update(float deltaTime) = 0; //declarada em inimigo / personagem
	virtual void Draw(sf::RenderWindow &window) = 0; //declarada em inimigo / personagem
	virtual void OnCollision(sf::Vector2f direcao) = 0; //declarada em inimigo / personagem

	sf::Vector2f GetPosition() { return body.getPosition(); } //não sei se serão virtual tb
	Colisor GetCollider() { return Colisor(body); } //não sei se serão virtual tb

};

