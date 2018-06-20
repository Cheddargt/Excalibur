#pragma once
#include <SFML\Graphics.hpp>
#include "Animacao.h"
#include "Colisor.h"
#include "stdafx.h"

class Personagem
{

public:
	Personagem(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id);
	virtual ~Personagem();

	virtual void Update(float deltaTime) = 0; 
	virtual void Draw(sf::RenderWindow &window) = 0; 
	virtual void OnCollision(sf::Vector2f direcao) = 0; 
	virtual void ColidiuPersonagem(sf::Vector2f direcao, int dano) = 0;
	void SetVelocidade(float x, float y) { velocidade.x = x; velocidade.y = y; }
	void SetPosition(float x, float y) { body.setPosition(x, y); }
	sf::Vector2f GetPosition() { return body.getPosition(); } 
	Colisor GetCollider() { return Colisor(body); } 
	int getAttack() { return attack; }
	virtual void setVida(int danoRecebido) { health -= danoRecebido; };

protected:
	float switchTime;
	float speed;
	int health;
	int attack;
	int id;
	sf::RectangleShape body; 
	Animacao animacao; 
	unsigned int row; 
	bool faceRight;
	sf::Vector2f velocidade;
	sf::Vector2f posicao;



};

