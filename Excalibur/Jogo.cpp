#include "stdafx.h"
#include "Jogo.h"
#

Jogo::Jogo()
{

	deltaTime = 0.0f;
	//textura, linhas x colunas animação, animação swaptime, speed, health, ataque, id, jumpHeight
}


Jogo::~Jogo()
{
}

void Jogo::ResizeView(const sf::RenderWindow& window, sf::View& view) //Para reajustar a janela
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void Jogo::Executar()
{

	playerTexture.loadFromFile("tux_from_linux.png");

	sf::RenderWindow window(sf::VideoMode(512, 512), "Excalibur", sf::Style::Close | sf::Style::Resize);

	Menu menu(window.getSize().x, window.getSize().y);

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	Jogador player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 3, 1, 0, 200.f);

	
	; //header


	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt; //header

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}

		}
		
		fase01.Executar(player, window, view); //& = player.funcao na fase e * = player->funcao

	}
	
}