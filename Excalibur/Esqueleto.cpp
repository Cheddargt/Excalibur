#include "stdafx.h"
#include "Esqueleto.h"
#define KNOCKBACK_X 450
#define KNOCKBACK_Y 320

Esqueleto::Esqueleto(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id) :
	Inimigo(texture, imageCount, switchTime, speed, health, attack, id)
{
	row = 0;
	faceRight = false;
	moveRight = false;

	//void Update(float deltaTime);
	//void Draw(sf::RenderWindow &window);
	//void OnCollision(sf::Vector2f direcao);
	void ColidiuPersonagem(sf::Vector2f direcao, int dano);


	body.setSize(sf::Vector2f(80.0f, 120.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(1575.0f, 375.0f);
	body.setTexture(texture);
}


Esqueleto::~Esqueleto()
{
}


void Esqueleto::Update(float deltaTime)
{
	if (moveRight)
		velocidade.x = speed;
	else
		velocidade.x = -speed;



	velocidade.y += 981.0f * deltaTime; //gravidade

	if (velocidade.x == 0.0f)
		row = 0;
	else
	{
		row = 1;

		if (velocidade.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animacao.Update(row, deltaTime, faceRight);
	body.setTextureRect(animacao.uvRect);
	body.move(velocidade * deltaTime); //move não ser mais frame-específico
}

void Esqueleto::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Esqueleto::OnCollision(sf::Vector2f direcao)
{
	if (direcao.x < 0.0f) //Colisão à direita
	{
		this->velocidade.x = 0.0f;
		this->moveRight = false;
	}

	else if (direcao.x > 0.0f) //Colisão à esquerda
	{
		this->velocidade.x = 0.0f;
		this->moveRight = true;
	}

	if (direcao.y < 0.0f) //Colisão embaixo
		this->velocidade.y = 0.0f;
	else if (direcao.y > 0.0f) //Colisão em cima
		this->velocidade.y = 0.0f;
}

void Esqueleto::ColidiuPersonagem(sf::Vector2f direcao, int dano)
{
	if (direcao.x < 0.0f)  //Colisão na direita
	{
		this->velocidade.x = 0.0f;
		this->moveRight = false;
	}

	else if (direcao.x > 0.0f) //Colisão na esquerda
	{
		this->velocidade.x = 0.0f;
		this->moveRight = true;
	}

	if (direcao.y < 0.0f) ////Colisão em cima
		this->velocidade.y = 0.0f;
	else if (direcao.y > 0.0f) //Colisão embaixo
		this->velocidade.y = 0.0f;
}
