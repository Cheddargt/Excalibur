#include "stdafx.h"
#include "Jogador.h"


Jogador::Jogador(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animacao(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);
}


Jogador::~Jogador()
{
}



void Jogador::Update(float deltaTime)
{
	
	velocidade.x *= 0.5f; //soltar botao para de mover, desaceleração do personagem (menor = mais rápido)

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocidade.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocidade.x += speed;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
	{
		canJump = false; //pular apenas uma vez -> já está pulando
		
		velocidade.y = -sqrtf(2.0f * 981.0f * jumpHeight); //gravidade 9.81 -> 100 unidades sfml = 1 metro
														   //sinal negativo -> sfml invertido no eixo Y
														   //squareroot (2.0f * gravity * jumpHeight);
														   //V(2gh) -> torricelli
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
	body.move(velocidade * deltaTime); //move não ser mais frame-específico
}

void Jogador::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Jogador::OnCollision(sf::Vector2f direcao)
{
	if (direcao.x < 0.0f)
	{
		//Colisão na esquerda
		velocidade.x = 0.0f;

	}

	else if (direcao.x > 0.0f)
	{
		//Colisão na direita
		velocidade.x = 0.0f;
	}

	if (direcao.y < 0.0f)
	{
		//Colisão embaixo
		velocidade.y = 0.0f;
		canJump = true;
	}
	else if (direcao.y > 0.0f)
	{
		//Colisão em cima
		velocidade.y = 0.0f;
	}
}

