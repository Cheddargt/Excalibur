#include "stdafx.h"
#include "Gosma.h"


Gosma::Gosma(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id) :
	Inimigo (texture, imageCount, switchTime, speed, health, attack, id)
{
	row = 0;
	faceRight = false;
	moveRight = false;

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);

	body.setSize(sf::Vector2f(50.0f, 50.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(1575.0f, 375.0f);
	body.setTexture(texture);
}


Gosma::~Gosma()
{
}


void Gosma::Update(float deltaTime)
{
	if (moveRight)
	{ 
		velocidade.x = speed;
	}
	else
	{
		velocidade.x = -speed;
	}
		


	velocidade.y += 981.0f * deltaTime; //gravidade

	if (velocidade.x == 0.0f)
	{
		row = 0;
	}
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
	body.move(velocidade * deltaTime); //move n�o ser mais frame-espec�fico
}

void Gosma::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Gosma::OnCollision(sf::Vector2f direcao)
{
	if (direcao.x < 0.0f)
	{
		//Colis�o na direita
		velocidade.x = 0.0f;
		moveRight = false;
		printf("colidiu\n");

	}

	else if (direcao.x > 0.0f)
	{
		//Colis�o na esquerda
		velocidade.x = 0.0f;
		moveRight = true;
		printf("colidiu\n");
	}

	if (direcao.y < 0.0f)
	{
		//Colis�o embaixo
		velocidade.y = 0.0f;
	}
	else if (direcao.y > 0.0f)
	{
		//Colis�o em cima
		velocidade.y = 0.0f;
	}
}