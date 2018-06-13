#pragma once
#include <SFML\Graphics.hpp>
#include "Animacao.h"
#include "Colisor.h"
//#include "Arma.h"

class Jogador
{
public:
	Jogador(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Jogador();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);


	sf::Vector2f GetPosition() { return body.getPosition(); }
	Colisor GetCollider() { return Colisor(body); }

private:
	sf::RectangleShape body; //personagem
	Animacao animacao; //personagem
	unsigned int row; //personagem
	float speed; //personagem
	bool faceRight; //personagem

	sf::Vector2f velocidade;
	bool canJump;
	float jumpHeight;
};

