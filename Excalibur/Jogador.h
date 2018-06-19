#pragma once
#include <SFML\Graphics.hpp>
#include "Animacao.h"
#include "Personagem.h"
#include <string>


class Jogador : public Personagem
{
public:
	Jogador(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id, float jumpHeight, int fase);
	~Jogador();

	void playerUpdate(float deltaTime, bool* twoplayers);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);
	void ColidiuPersonagem(sf::Vector2f direcao, int dano);
	void ColidiuObstaculo(sf::Vector2f direcao, int dano);
	void setFase(int fase) { this->fase = fase; }
	int getHealth() { return health; }
	void setVida(int danoRecebido);
	void setHealth(int vida) { health = vida; }
	bool getFaceRight() { return faceRight; }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Colisor GetCollider() { return Colisor(body); }
	void setUnspawned () { Jogador::player2spawned = false; }

private:
	bool* twoplayers;
	bool canJump;
	bool isJumping;
	float jumpHeight;
	int fase;
	sf::Text vida;
	sf::Font font;
	static bool player2spawned;


};

