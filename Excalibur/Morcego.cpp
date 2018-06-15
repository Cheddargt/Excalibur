#include "stdafx.h"
#include "Morcego.h"


Morcego::Morcego(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id) :
	Inimigo(texture, imageCount, switchTime, speed, health, attack, id)
{
	row = 0;
	faceRight = false;
	moveRight = false;
	moveUp = false;

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
	void OnCollision(sf::Vector2f direcao);

	body.setSize(sf::Vector2f(80.0f, 80.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(100.0f, 150.0f);
	body.setTexture(texture);
}


Morcego::~Morcego()
{
}


void Morcego::Update(float deltaTime)
{

	
	if (moveRight)
	{
		velocidade.x = speed;
	}
	else
	{
		velocidade.x = -speed;
	}

	if (moveUp)
	{
		velocidade.y = -speed;
	}
	else
	{
		velocidade.y = +speed;
	}

	//if (posição em X >)
	//{
	//	moveUp = false;
	//	printf("subindo\n %f", velocidade.y);
	//}
	//else
	//{
	//	moveUp = true;
	//	printf("descendo\n %f", velocidade.y);
	//}


	velocidade.y += 981.0f * deltaTime; //gravidade


	
	if (velocidade.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		/*row = 0;*/

		if (velocidade.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animacao.Update(row, deltaTime, faceRight);
	body.setTextureRect(animacao.uvRect);
	body.move(velocidade * deltaTime); //move não ser mais frame-específico
}

void Morcego::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Morcego::OnCollision(sf::Vector2f direcao)
{
	if (direcao.x < 0.0f)
	{
		//Colisão na direita
		velocidade.x = 0.0f;
		moveRight = false;
		printf("colidiu\n");

	}

	else if (direcao.x > 0.0f)
	{
		//Colisão na esquerda
		velocidade.x = 0.0f;
		moveRight = true;
		printf("colidiu\n");
	}

	if (direcao.y < 0.0f)
	{
		//Colisão embaixo
		velocidade.y = 0.0f;
		moveUp = true;
	}
	else if (direcao.y > 0.0f)
	{
		//Colisão em cima
		velocidade.y = 0.0f;
		setVida(1);
		printf("vida morcego: %d\n", getVida());
	}
}
