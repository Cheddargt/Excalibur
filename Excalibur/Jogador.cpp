#include "stdafx.h"
#include "Jogador.h"
#include <iostream>
#define KNOCKBACK_X 1000
#define KNOCKBACK_Y 320
#define JUMP_SWITCHTIME 0.6f
bool Jogador::player2spawned = false;


Jogador::Jogador (sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, int attack, int id, float jumpHeight, int fase) :
	Personagem(texture, imageCount, switchTime, speed, health, attack, id), jumpHeight(jumpHeight)

{
	font.loadFromFile("arial.ttf");
	row = 0;
	faceRight = true;
	this->health = 5;

	if (fase == 1)
		this->SetPosition(100.0f, 200.0);
	else if (fase == 2)
		this->SetPosition(50.0f, -120.0f);
		


	vida.setString(std::to_string(this->health));
	vida.setFont(font);
	vida.setFillColor(sf::Color::Black);
	if (id == 1)
		vida.setFillColor(sf::Color::Red);


	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
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

	this->twoplayers = twoplayers; 

	velocidade.x *= 0.5f;

	if (velocidade.y > 0.0f)
	{
		switchTime = 0.3f;
		canJump = false;
		isJumping = true;

		if ((row != 1) && (row != 3))
			row = 5;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) && (!player2spawned))
	{
		*twoplayers = true;
		player2spawned = true;

	}
		
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		*twoplayers = false;
	

	if (id == 0)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			velocidade.x -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			velocidade.x += speed;

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (canJump) && !(isJumping) && (row != 3))
		{
			switchTime = JUMP_SWITCHTIME; 

			if ((row != 2) && (row !=3))
				row = 2;

			isJumping = true;
			canJump = false;

			velocidade.y = -sqrtf(2.0f * 981.0f * jumpHeight); 
		}

	}

	if ((id == 1) && (*twoplayers))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			velocidade.x -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			velocidade.x += speed;

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (canJump) && !(isJumping) && (row != 3))
		{
			switchTime = JUMP_SWITCHTIME;

			if ((row != 2) && (row != 3))
				row = 2;

			isJumping = true;
			canJump = false;

			velocidade.y = -sqrtf(2.0f * 981.0f * jumpHeight); 
			
		}
	}


	velocidade.y += 981.0f * deltaTime; 

	if ((velocidade.x == 0.0f) && !(isJumping))
	{
		switchTime = 0.3f; 

		if ((row != 0) && (row!=3) && (row != 4))
			row = 0;
		
	}
	else if ((velocidade.x != 0.0f)  &&! (isJumping)) 
	{
		switchTime = 0.3f;

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
		body.move(velocidade * deltaTime); 
	}


	if ((this->id == 1) && (*twoplayers))
	{
		animacao.Update(row, deltaTime, faceRight);
		body.setTextureRect(animacao.uvRect);
		body.move(velocidade * deltaTime);
	}
	
}

void Jogador::Draw(sf::RenderWindow& window)
{
	sf::Vector2f vidaPos = window.getView().getCenter();
	vidaPos.x -= (window.getView().getSize().x / 2);
	vidaPos.y -= (window.getView().getSize().y / 2);
	
	if (id == 1)
		vidaPos.x += 50;

	vida.setPosition(vidaPos);
	window.draw(vida);
	window.draw(body);
}

void Jogador::setVida(int danoRecebido)
{
	health -= danoRecebido;
	vida.setString(std::to_string (health));
}

void Jogador::OnCollision(sf::Vector2f direcao)
{

	if (direcao.x < 0.0f) 
	{
		if (velocidade.x)
			velocidade.x = 0.0f;
	}

	else if (direcao.x > 0.0f)
	{
		velocidade.x = 0.0f;
	}

	if (direcao.y < 0.0f) 
	{
		velocidade.y = 0.0f;
		
	}
	else if (direcao.y > 0.0f) 
	{
		velocidade.y = 0.0f;
		canJump = false;
		isJumping = true;
	}

	if ((direcao.y < 0.0f) && (direcao.x == 0.0f)) 
	{
		switchTime = 0.3f;
		velocidade.y = 0.0f;
		isJumping = false;
		canJump = true;
		row = 0;
	}
}

void Jogador::ColidiuPersonagem(sf::Vector2f direcao, int dano)
{
	if (direcao.x < 0.0f)   
	{ 
		velocidade.y = -(KNOCKBACK_Y);
		velocidade.x = (KNOCKBACK_X);
		if (row != 3)
		{
			setVida(dano);
			switchTime = 0.3f;
			row = 3;
		}
	}

	else if (direcao.x > 0.0f) 
	{ 
		velocidade.y = -(KNOCKBACK_Y);
		velocidade.x = -(KNOCKBACK_X);
		if (row != 3)
		{
			setVida(dano);
			switchTime = 0.3f;
			row = 3;
		}
	}

	if ((direcao.y < 0.0f) && (row != 3))
	{
		switchTime = JUMP_SWITCHTIME;
		row = 2;
		velocidade.y = -sqrtf(2.0f * 981.0f * jumpHeight);
		isJumping = true;
		canJump = false;
		velocidade.x = -(KNOCKBACK_X);
		switchTime = 0.3f; 
	}

	else if ((direcao.y < 0.0f) && (row == 3)) 
	{
		velocidade.y = -(KNOCKBACK_Y);
		if (faceRight)
			velocidade.x = -(KNOCKBACK_X);
		else
			velocidade.x = (KNOCKBACK_X);
	}

	else if (direcao.y > 0.0f) 
	{
			
			if (faceRight)
				velocidade.x = -(KNOCKBACK_X);
			else
				velocidade.x = (KNOCKBACK_X);

			if (row != 3)
			{
				setVida(dano);
				switchTime = 0.3f;
				row = 3;
			}
	}

}

void Jogador::ColidiuObstaculo(sf::Vector2f direcao, int dano)
{
	if ((direcao.x < 0.0f) && (row != 3))  // added row != 3
	{ //Colisão à esquerda

		setVida(dano);
		velocidade.y = -(KNOCKBACK_Y);
		velocidade.x = (KNOCKBACK_X);
		switchTime = 0.3f;
		row = 3;
	}

	else if ((direcao.x > 0.0f) && (row != 3)) 
	{ 

		setVida(dano);
		velocidade.y = -(KNOCKBACK_Y);
		velocidade.x = -(KNOCKBACK_X);
		switchTime = 0.3f; 
		row = 3;
	}

	if ((direcao.y < 0.0f) && (row != 3)) 
	{
		setVida(dano);
		canJump = false;
		row = 3;
		velocidade.y = -(KNOCKBACK_Y);
		velocidade.x = -(KNOCKBACK_X);
		switchTime = 0.3f; //volta ao normal

	}

	else if ((direcao.y > 0.0f) && (row != 3)) //colisão em cima ARRUMAR
	{
		setVida(dano);
		/*velocidade.y = (KNOCKBACK_Y);*/

		if (faceRight)
			velocidade.x = -(KNOCKBACK_X);
		else
			velocidade.x = (KNOCKBACK_X);

		switchTime = 0.3f;
		row = 3;

	}

}