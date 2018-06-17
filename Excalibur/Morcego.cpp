#include "stdafx.h"
#include "Morcego.h"
#define KNOCKBACK_X 450
#define KNOCKBACK_Y 320

Morcego::Morcego(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id) :
	Inimigo(texture, imageCount, switchTime, speed, health, attack, id)
{
	row = 0;
	faceRight = false;
	moveRight = false;
	moveUp = false;

	tempoDescida = relogio1.restart().asSeconds();
	tempoEsquerda = relogio2.restart().asSeconds();

	
	//void Update(float deltaTime);
	//void Draw(sf::RenderWindow &window);
	//void OnCollision(sf::Vector2f direcao);
	void ColidiuPersonagem(sf::Vector2f direcao, int dano);

	body.setSize(sf::Vector2f(80.0f, 80.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(3200.0f, 50.0f);
	body.setTexture(texture);


}


Morcego::~Morcego()
{
}


void Morcego::Update(float deltaTime)
{
	tempoDescida = relogio1.getElapsedTime().asSeconds();
	tempoEsquerda = relogio2.getElapsedTime().asSeconds();

	if ((moveRight) && (tempoEsquerda > 3.0f))
	{
		this->velocidade.x = speed;
		tempoEsquerda = relogio2.restart().asSeconds();
	} 
	else if ((!moveRight) && (tempoDescida > 3.0f))
	{
		this->velocidade.x = -speed;
		tempoEsquerda = relogio2.restart().asSeconds();
	}

	if (moveRight)
	{
		this->velocidade.x = speed;
	}
	else 
	{
		this->velocidade.x = -speed;
	}

	if ((tempoEsquerda > 3.0f) && !(moveRight))
	{
		moveRight = true;
		//printf("direita %f\n", tempoDescida);
		tempoDescida = relogio1.restart().asSeconds();
	}
	else if ((tempoEsquerda > 6.0f) && (moveRight))
	{
		moveRight = false;
		//printf("descendo%f\n ", tempoDescida);
		tempoDescida = relogio1.restart().asSeconds();
	}

	//////////////////

	if (moveUp)
	{
		this->velocidade.y = -speed;
	}
	else
	{
		this->velocidade.y = +speed;
	}

	if ((tempoDescida > 3.0f) && !(moveUp))
	{
		moveUp = true;
		//printf("subindo %f\n", tempoDescida);
		tempoDescida = relogio1.restart().asSeconds();
	}
	else if ((tempoDescida > 3.0f) && (moveUp))
	{
		moveUp = false;
		//printf("descendo%f\n ", tempoDescida);
		tempoDescida = relogio1.restart().asSeconds();
	}


	//velocidade.y += 981.0f * deltaTime; //gravidade


	
	if (velocidade.x == 0.0f)
	{
		this->row = 0;
	}
	else
	{
		if (velocidade.x > 0.0f)
			this->faceRight = true;
		else
			this->faceRight = false;
	}

	animacao.Update(this->row, deltaTime, this->faceRight);
	body.setTextureRect(this->animacao.uvRect);
	body.move((this->velocidade) * deltaTime); //move não ser mais frame-específico
}

void Morcego::Draw(sf::RenderWindow& window)
{
	window.draw(this->body);
}

void Morcego::OnCollision(sf::Vector2f direcao)
{
	if (direcao.x < 0.0f)		//Colisão à direita
	{

		velocidade.x = 0.0f;
		moveRight = false;
		tempoEsquerda = relogio2.restart().asSeconds();
	}

	else if (direcao.x > 0.0f)		//Colisão na esquerda
	{

		velocidade.x = 0.0f;
		moveRight = true;
		tempoEsquerda = relogio2.restart().asSeconds();
	}

	if (direcao.y < 0.0f)		//Colisão embaixo
	{

		velocidade.y = 0.0f;
		moveUp = true;
		tempoDescida = relogio1.restart().asSeconds();
	}
	else if (direcao.y > 0.0f)		//Colisão em cima
	{
		moveUp = false;
		velocidade.y = 0.0f;
		tempoDescida = relogio1.restart().asSeconds();
	}
}

void Morcego::ColidiuPersonagem(sf::Vector2f direcao, int dano)
{
	if (direcao.x < 0.0f) //Colisão à direita
	{
		velocidade.x = 0.0f;
		moveRight = false;
		/*tempoEsquerda = relogio2.restart().asSeconds();*/

		//if dano -> knockback
	}

	else if (direcao.x > 0.0f) //Colisão à esquerda
	{
		velocidade.x = 0.0f;
		moveRight = true;
		/*tempoEsquerda = relogio2.restart().asSeconds();*/

		//if dano -> knockback
	}

	if (direcao.y < 0.0f) //Colisão embaixo
	{
		velocidade.y = 0.0f;
		moveUp = true;
	}
	else if (direcao.y > 0.0f) //colisão em cima
	{
		velocidade.y = 0.0f;
		moveUp = false;

	}

	//if (direcao.x < 0.0f)  //Colisão na direita
	//{
	//	velocidade.x = 0.0f;
	//	moveRight = false;
	//}

	//else if (direcao.x > 0.0f) //Colisão na esquerda
	//{
	//	velocidade.x = 0.0f;
	//	moveRight = true;
	//}

	//if (direcao.y < 0.0f) ////Colisão em cima
	//	velocidade.y = 0.0f;
	//else if (direcao.y > 0.0f) //Colisão embaixo
	//	velocidade.y = 0.0f;

}