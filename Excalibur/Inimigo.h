#pragma once
#include "Personagem.h"
#define KNOCKBACK 50
#define BOSS_KNOCKBACK 30

class Inimigo :
	public Personagem
{

public:
	Inimigo(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id);
	~Inimigo();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow &window) = 0;
	virtual void OnCollision(sf::Vector2f direcao) = 0;
	void setVida(int x) { health -= x; }
	int getVida() { return health; }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Colisor GetCollider() { return Colisor(body); }

private:


};

