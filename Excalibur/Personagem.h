#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include <SFML\Graphics.hpp>
#include "Animacao.h"
#include "Colisor.h"

class Personagem
{
public: 
	Personagem();
	~Personagem();
};

/**
class Personagem
{
 protected:
	int health;
	int attack;
	int id;

public:
	Personagem(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Personagem();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);


	sf::Vector2f GetPosition() { return body.getPosition(); }
	Colisor GetCollider() { return Colisor(body); }

private:
	sf::RectangleShape body; //personagem
	Animacao animacao; //personagem
	unsigned int row; //personagem
	bool faceRight; //personagem
};

#endif // PERSONAGEM_H
