#include "stdafx.h"
#include "Jogo.h"

//classe plataforma derivada de item
//delete vector

Jogo::Jogo() : 
window(sf::VideoMode(512, 512), "Excalibur", sf::Style::Close | sf::Style::Resize),
view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT))

{
	menu = new Menu(window.getSize().x, window.getSize().y);
	evnt = new sf::Event; //verificar
	playerTexture.loadFromFile("tux_menino.png");
	player2Texture.loadFromFile("tux_menina.png");
	player = new Jogador(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 0, 200.f, 1); //speed = 100.0f
	player2 = new Jogador(&player2Texture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 1, 200.f, 1);
	fase01 = new Fase1; //verificar
	fase02 = new Fase2; //verificar
	deltaTime = 0.0f;
	two_players = false;
	/*std::cout << two_players << std::endl;*/

}


Jogo::~Jogo()
{
	delete fase01; //verificar
	delete fase02; 

}

void Jogo::ResizeView(const sf::RenderWindow& window, sf::View& view) //Para reajustar a janela
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void Jogo::Executar()
{

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

		//if pessoa escolheu jogar fase1 - inicia sequencialmente
			//player->setFase(1); // p/ o menu
			//player2->setFase(1); //p/ o menu
			//if (fase01->Executar(player, player2, window, view, &two_players))
			//{
				if(fase02->Executar(player, player2, window, view, &two_players));
					printf("You win!\n");
			//}
			//
			//else
			//{
			//	fase01->Executar(player, player2, window, view, &two_players);
			//}
		//if pessoa escolheu jogar fase2
			//fase02->Executar(player, player2, window, view, &two_players);

			//player->setFase(2); // p/ o menu
			//player2->setFase(2); //p/ o menu


	}
	
}