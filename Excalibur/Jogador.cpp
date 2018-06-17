#include "stdafx.h"
#include "Jogador.h"
using namespace std;
#define KNOCKBACK_X 1000
#define KNOCKBACK_Y 320
#define JUMP_SWITCHTIME 0.6f

Jogador::Jogador (sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id, float jumpHeight) :
	Personagem(texture, imageCount, switchTime, speed, health, attack, id), jumpHeight(jumpHeight)

{
	row = 0;
	faceRight = true;


	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(100.0f, 200.0f);
	//body.setPosition(3200.0f, 200.0f); //(100.0f, 200.0f) //morcego
	//body.setPosition(1575.0f, 200.0); //(100.0f, 200.0f) 
	//body.setPosition(1375.0f, 375.0f); //(100.0f, 200.0f) //gosma

	body.setTexture(texture);
}

void Jogador::Update(float deltaTime)
{

}

Jogador::~Jogador()
{
}



void Jogador::playerUpdate(float deltaTime, bool* twoplayers)
{


	velocidade.x *= 0.5f;

	if (id == 0)
	{
		if (velocidade.y > 0.0f) //remover bug do pulo no ar
		{
			switchTime = 0.3f;
			canJump = false;
			isJumping = true; 

			if ((row != 1) && (row != 3))
				row = 5;
		}
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			velocidade.x -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			velocidade.x += speed;

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (canJump) && !(isJumping))
		{
			switchTime = JUMP_SWITCHTIME; //para o pulo

			if ((row != 2) && (row !=3))
				row = 2;

			isJumping = true;
			canJump = false;

			velocidade.y = -sqrtf(2.0f * 981.0f * jumpHeight); //gravidade 9.81 -> 100 unidades sfml = 1 metro
															   //sinal negativo -> sfml invertido no eixo Y
															   //squareroot (2.0f * gravity * jumpHeight);
															   //V(2gh) -> torricelli

		}
	}

	if (id == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			velocidade.x -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			velocidade.x += speed;

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (canJump) && !(isJumping))
		{
			switchTime = JUMP_SWITCHTIME; //para o pulo

			if ((row != 2) && (row != 3))
				row = 2;

			isJumping = true;
			canJump = false;

			velocidade.y = -sqrtf(2.0f * 981.0f * jumpHeight); //gravidade 9.81 -> 100 unidades sfml = 1 metro
															   //sinal negativo -> sfml invertido no eixo Y
															   //squareroot (2.0f * gravity * jumpHeight);
															   //V(2gh) -> torricelli


		}
	}


	velocidade.y += 981.0f * deltaTime; //gravidade

	if ((velocidade.x == 0.0f) && !(isJumping)) //não tá pulando
	{
		switchTime = 0.3f; //volta ao normal

		if ((row != 0) && (row!=3))
			row = 0;
		
	}
	else if ((velocidade.x != 0.0f)  &&! (isJumping)) //não tá pulando
	{
		switchTime = 0.3f; //volta ao normal

		if ((row != 1) && (row != 3))
			row = 1;

		if ((velocidade.x > 0.0f) && (row != 3))
			faceRight = true;
		else if (row != 3)
			faceRight = false;
	}

	if ((velocidade.x > 0.0f) && (row != 3))
		faceRight = true;
	else if ((velocidade.x < 0.0f) && (row != 3))
		faceRight = false;
	if ((this->id == 0))
	{
		animacao.Update(row, deltaTime, faceRight);
		body.setTextureRect(animacao.uvRect);
		body.move(velocidade * deltaTime); //move não ser mais frame-específico
	}

	if ((this->id == 1) && (twoplayers))
	{
		animacao.Update(row, deltaTime, faceRight);
		body.setTextureRect(animacao.uvRect);
		body.move(velocidade * deltaTime); //move não ser mais frame-específico
	}
	
}

void Jogador::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Jogador::OnCollision(sf::Vector2f direcao)
{

	if (direcao.x < 0.0f) //Colisão na esquerda
	{
		if (velocidade.x)
			velocidade.x = 0.0f;
	}

	else if (direcao.x > 0.0f) //Colisão na direita
	{
		velocidade.x = 0.0f;
	}

	if (direcao.y < 0.0f) //Colisão embaixo
	{
		velocidade.y = 0.0f;
		
	}
	else if (direcao.y > 0.0f) //Colisão em cima ARRUMAR
	{
		velocidade.y = 0.0f;
		canJump = false;
		isJumping = true;
	}

	if ((direcao.y < 0.0f) && (direcao.x == 0.0f)) //remover bug do pulo //Colisão embaixo
	{
		switchTime = 0.3f;

		velocidade.y = 0.0f;
		isJumping = false;
		canJump = true;

		row = 0;

		//printf("entrou\n");

	}


}

void Jogador::ColidiuPersonagem(sf::Vector2f direcao, int dano)
{
	if (direcao.x < 0.0f) //Colisão à esquerda
	{
		velocidade.y = -(KNOCKBACK_Y);
		velocidade.x = KNOCKBACK_X;
		switchTime = 0.3f;
		row = 3;

	}

	else if (direcao.x > 0.0f)
	{
	
		//Colisão na direita
		velocidade.y = -(KNOCKBACK_Y);
		velocidade.x = -(KNOCKBACK_X);
		switchTime = 0.3f; //volta ao normal
		row = 3;
	}

	if ((direcao.y < 0.0f) && (direcao.x == 0.0f)) //Colisão embaixo
	{
		switchTime = JUMP_SWITCHTIME;
		if((row != 2) && (row != 3))
			row = 2;

		velocidade.y = -sqrtf(2.0f * 981.0f * jumpHeight);
		isJumping = true;
		canJump = false;

	}
	else if (direcao.y > 0.0f) //colisão em cima ARRUMAR
	{
		velocidade.y = (KNOCKBACK_Y);

		if (faceRight)
			velocidade.x = -(KNOCKBACK_X);
		else 
			velocidade.x = (KNOCKBACK_X);

		switchTime = 0.3f; 
		row = 3;
	}

}
