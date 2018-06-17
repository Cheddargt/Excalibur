#pragma once
#include <SFML\Graphics.hpp>
#include "Animacao.h"
#include "Colisor.h"
#include "Personagem.h"

class Jogador : public Personagem
{
public:
	Jogador(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id, float jumpHeight);
	~Jogador();

	void playerUpdate(float deltaTime, bool* twoplayers);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);
	void ColidiuPersonagem(sf::Vector2f direcao, int dano);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Colisor GetCollider() { return Colisor(body); }

private:
	bool* twoplayers;
	bool canJump;
	bool isJumping;
	float jumpHeight; //200.f


};

