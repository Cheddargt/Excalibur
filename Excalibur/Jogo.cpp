#include "stdafx.h"
#include "Jogo.h"

//classe plataforma derivada de item
//delete vector

Jogo::Jogo() :
	window(sf::VideoMode(512, 512), "Excalibur", sf::Style::Close | sf::Style::Resize),
	view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)), player2(nullptr)

{
	menu = new Menu(static_cast <float> (window.getSize().x), static_cast <float> (window.getSize().y));
	playerTexture.loadFromFile("tux_menino.png");
	player2Texture.loadFromFile("tux_menina.png");
	player = new Jogador(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 0, 200.f, 1); //speed = 100.0f
	player2 = new Jogador(&player2Texture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 1, 200.f, 1);
	fase01 = new Fase1; //verificar
	fase02 = new Fase2; //verificar
	deltaTime = 0.0f;
	two_players = false;
	bool fase1_zerada = false;

}


Jogo::~Jogo()
{
	delete fase01;
	delete fase02;
	delete menu;
	delete player;
	if (player2)
		delete player2;
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

		sf::Event evnt; //verificar

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

		while (!fase1_zerada)
		{
			if (fase01->Executar(player, &player2, window, view, &two_players))
			{
				fase1_zerada = true;
				if (fase02->Executar(player, &player2, window, view, &two_players))
					printf("You win!\n");
			}
			else
			{
				printf("You died :(!\n");
				player = new Jogador(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 0, 200.f, 1);
				player2 = new Jogador(&player2Texture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 1, 200.f, 1);
				player2->setUnspawned();
			}
				
		}

		//if pessoa escolheu jogar fase1 - inicia sequencialmente
		////player->setFase(1); // p/ o menu
		////player2->setFase(1); //p/ o menu
		////fase01->Executar(player, player2, window, view, &two_players);
			//
			//else
			//{
			//fase01->Executar(player, player2, window, view, &two_players);
			//}
		//if pessoa escolheu jogar fase2
			//fase02->Executar(player, player2, window, view, &two_players);
			//player->setFase(2); // p/ o menu
			//player2->setFase(2); //p/ o menu


	}
	
}

//void Jogo::Executar()
//{
//
//
//	while (window.isOpen())
//	{
//		deltaTime = clock.restart().asSeconds();
//		if (deltaTime > 1.0f / 20.0f)
//			deltaTime = 1.0f / 20.0f;
//
//		sf::Event evnt; //header
//
//		while (window.pollEvent(evnt))
//		{
//			switch (evnt.type)
//			{
//				switch (evnt.type)
//				{
//				case sf::Event::KeyReleased: //Para o Menu
//					switch (evnt.key.code)
//					{
//					case sf::Keyboard::Up: //Para o menu, caso Up esteja pressionado
//						(*menu).MoveUp();
//						break;
//
//					case sf::Keyboard::Down: //Para o menu, caso Down esteja pressionado
//						(*menu).MoveDown();
//						break;
//
//					case sf::Keyboard::Return:
//						switch ((*menu).GetPressedItem())
//						{
//						case 0: //Jogar fase 1 modo continuo
//							fase01->Executar(player, &player2, window, view, &two_players);
//							player->setFase(1); // p/ o menu
//							player2->setFase(1); //p/ o menu
//							if (fase01->Executar(player, &player2, window, view, &two_players))
//							{
//								fase02->Executar(player, &player2, window, view, &two_players);
//							}
//
//							else
//							{
//								fase01->Executar(player, &player2, window, view, &two_players);
//							}
//							break;
//
//						case 1: //Pular direto para fase 2
//							fase02->Executar(player, &player2, window, view, &two_players);
//							player->setFase(2); // p/ o menu
//							player2->setFase(2); //p/ o menu
//							break;
//
//						case 2: //para sair
//							window.close(); //Aqui já está pronto. Quando a pessoa apertar enter aqui, o jogo fecha.
//							break;
//
//						}
//						break;
//					}
//
//					break;
//
//					//& = player.funcao na fase e * = player->funcao
//					//player->setFase(1); // p/ o menu
//					//player2->setFase(1); //p/ o menu
//
//					//fase02->Executar(*player, *player2, window, view, &two_players);
//					//player->setFase(2); // p/ o menu
//					//player2->setFase(2); //p/ o menu
//				}
//			case sf::Event::Closed:
//				window.close();
//				break;
//
//			case sf::Event::Resized:
//				ResizeView(window, view);
//				break;
//			}
//		}
//		window.clear();
//		(*menu).Draw(window);
//		window.display();
//	}
//	return;
//}