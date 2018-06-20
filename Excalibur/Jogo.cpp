#include "stdafx.h"
#include "Jogo.h"


Jogo::Jogo() :
	window(sf::VideoMode(512, 512), "Excalibur", sf::Style::Close | sf::Style::Resize),
	view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)), player2(nullptr)

{
	menu = new Menu(static_cast <float> (window.getSize().x), static_cast <float> (window.getSize().y));
	playerTexture.loadFromFile("tux_menino.png");
	player2Texture.loadFromFile("tux_menina.png");
	player = new Jogador(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 0, 200.f, 1); 
	player2 = new Jogador(&player2Texture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 1, 200.f, 1);
	fase01 = new Fase1;
	fase02 = new Fase2;
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


		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{

			case sf::Event::KeyReleased:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Up:
					menu->MoveUp();
					break;

				case sf::Keyboard::Down:
					menu->MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu->GetPressedItem())
					{
					case 0:
						while (!fase1_zerada)
						{
							if (fase01->Executar(player, &player2, window, view, &two_players))
							{
								fase1_zerada = true;

								if (fase02->Executar(player, &player2, window, view, &two_players))
									printf("Congratulations! You win!\n");
							}
							else
							{
								printf("Game over :/\n");
								player = new Jogador(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 0, 200.f, 1);
								player2 = new Jogador(&player2Texture, sf::Vector2u(3, 9), 0.3f, 100.0f, 5, 1, 1, 200.f, 1);
								player2->setUnspawned();
							}

						}
						break;

					case 1:
						player->setFase(2);
						player2->setFase(2);
						if (fase02->Executar(player, &player2, window, view, &two_players))
						{
							printf("Congratulations! You beat the Guardian!\n");
							break;
						}
							
					case 2:
						window.close();
						break;

					}


				case sf::Event::Resized:
					ResizeView(window, view);
					break;

				}

			}

		}

		window.clear();
		menu->Draw(window);
		window.display();
	}
}

