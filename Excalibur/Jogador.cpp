#include "stdafx.h"
#include "Jogador.h"


Jogador::Jogador (sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id, float jumpHeight) :
	Personagem(texture, imageCount, switchTime, speed, health, attack, id), jumpHeight(jumpHeight)

{
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(100.0f, 200.0f); //(100.0f, 200.0f)
	body.setTexture(texture);
}


Jogador::~Jogador()
{
}



void Jogador::Update(float deltaTime)
{

	velocidade.x *= 0.5f; //soltar botao para de mover, desaceleração do personagem (menor = mais rápido)

	if (velocidade.y > 0.0f) //remover bug do pulo
	{
		canJump = false;
		isJumping = true; 
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocidade.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocidade.x += speed;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (canJump) && !(isJumping))
	{
		row = 2; //remover pra tirar animacao
		isJumping = true;
		canJump = false; //pular apenas uma vez
		velocidade.y = -sqrtf(2.0f * 981.0f * jumpHeight); //gravidade 9.81 -> 100 unidades sfml = 1 metro
														   //sinal negativo -> sfml invertido no eixo Y
														   //squareroot (2.0f * gravity * jumpHeight);
														   //V(2gh) -> torricelli

	
	}


	velocidade.y += 981.0f * deltaTime; //gravidade

	if ((velocidade.x == 0.0f) && !(isJumping)) //remover &&!(isJumping) pra tirar animacao
	{
		row = 0;

	}
	else if ((velocidade.x != 0.0f) && !(isJumping)) //remover &&!(isJumping) pra tirar animacao
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
		if (velocidade.x)
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
	}
	else if (direcao.y > 0.0f)
	{
		//Colisão em cima
		velocidade.y = 0.0f;
	}

	if ((direcao.y < 0.0f) && (direcao.x == 0.0f)) //remover bug do pulo
	{
		//Colisão embaixo
		velocidade.y = 0.0f;
		isJumping = false;
		canJump = true;
		row = 0;
	}


}

