// Excalibur.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Animacao.h"
#include "Jogador.h"
#include "Personagem.h"
#include "Gosma.h"
#include "Morcego.h"
#include "Objeto.h"
#include "Menu.h"
#define VIEW_HEIGHT 512.0f

void ResizeView(const sf::RenderWindow& window, sf::View& view) //Para reajustar a janela
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(512, 512), "Excalibur", sf::Style::Close | sf::Style::Resize);
	Menu menu(window.getSize().x, window.getSize().y);

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture playerTexture; //player
	sf::Texture parede; //plataforma
	sf::Texture gosmaTexture;
	sf::Texture morcegoTexture;
	playerTexture.loadFromFile("tux_from_linux.png");
	parede.loadFromFile("espada.png");
	gosmaTexture.loadFromFile("gosma.png");
	morcegoTexture.loadFromFile("espada.png"); //morcego.png

	Jogador player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 3, 1, 0, 200.f); //3 = linhas de animacao, 9 = colunas de animacao
	Gosma gosma(&gosmaTexture, sf::Vector2u(3, 2), 0.3f, 100.0f, 3, 1, 1);
	Morcego morcego(&morcegoTexture, sf::Vector2u(1, 1), 0.3f, 100.0f, 3, 1, 1);


	std::vector<Objeto> plataformas;

	plataformas.push_back(Objeto(&parede, sf::Vector2f(50.0f, 2000.0f), sf::Vector2f(0.0f, 0.0f))); //parede

	plataformas.push_back(Objeto(&parede, sf::Vector2f(50.0f, 2000.0f), sf::Vector2f(300.0f, 0.0f))); //parede

	plataformas.push_back(Objeto(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f))); //chao 1
	plataformas.push_back(Objeto(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(500.0f, 310.0f))); //Pedra - obstaculo 1
	plataformas.push_back(Objeto(nullptr, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(975.0f, 375.0f))); //bloquinho esquerda
	plataformas.push_back(Objeto(nullptr, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(1275.0f, 375.0f))); //bloquinho direita
	plataformas.push_back(Objeto(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(1750.0f, 500.0f))); //chao 2
	plataformas.push_back(Objeto(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(1825.0f , 310.0f))); //Pedra - obstaculo 2




	/*Objeto platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 100.0f));
	Objeto platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));
	Objeto platform3(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f));
	Objeto platform4(&parede, sf::Vector2f(50.0f, 2000.0f), sf::Vector2f(0.0f, 0.0f));
	Objeto platform5(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(1400.0f, 500.0f));
	Objeto platform6(nullptr, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(1400.0f, 450.0f));*/


	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			/**case sf::Event::KeyReleased: //Para o Menu
				switch (evnt.key.code)
				{
				case sf::Keyboard::Up: //Para o menu, caso Up esteja pressionado
					menu.MoveUp();
					break;

				case sf::Keyboard::Down: //Para o menu, caso Down esteja pressionado
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Jogar button has been pressed" << std::endl; //Aqui precisa ser mudado quando tiver as coisas do jogo. Função iniciar/executar deverá ser chamada
						break;

					case 1:
						std::cout << "Salvar button has been pressed" << std::endl; //Aqui também precisa ser mudado. Chamar função de Salvar jogo
						break;

					case 2:
						window.close(); //Aqui já está pronto. Quando a pessoa apertar enter aqui, o jogo fecha.
						break;

					}
					break;
				}

				break;
			**/
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				ResizeView(window, view);
				break;



			}

		}

		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		player.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));
		}
		*/

		player.Update(deltaTime);
		gosma.Update(deltaTime);
		morcego.Update(deltaTime);

		sf::Vector2f direcao; //passada pra OnCollision e pra player OnCollision
		
		/**for (int i = 0; i < plataformas.size(); i++)
		{
			Objeto& plataforma = plataformas[i];
		}**/

		for (Objeto& plataforma : plataformas) //checa todas as plataformas pra ver se alguma delas está colidindo com player
		{
			if (plataforma.GetCollider().CheckCollision(&(player.GetCollider()), direcao, 1.0f))
				player.OnCollision(direcao);
			if (plataforma.GetCollider().CheckCollision(&(gosma.GetCollider()), direcao, 1.0f))
				gosma.OnCollision(direcao);
			if (plataforma.GetCollider().CheckCollision(&(morcego.GetCollider()), direcao, 1.0f))
				morcego.OnCollision(direcao);
		} //isso fica na classe Principal

		// MOVIDO PRO FOR ACIMA
		//for (Objeto& plataforma : plataformas) //checa todas as plataformas pra ver se alguma delas está colidindo com player
		//{
		//	if (plataforma.GetCollider().CheckCollision(&(gosma.GetCollider()), direcao, 1.0f))
		//		gosma.OnCollision(direcao);
		//}

		if (player.GetCollider().CheckCollision(&(gosma.GetCollider()), direcao, 1.0f))
		{ 
			player.OnCollision(direcao);
			gosma.OnCollision(direcao);
		}


		if (player.GetCollider().CheckCollision(&(morcego.GetCollider()), direcao, 1.0f))
		{
			player.OnCollision(direcao);
			//morcego.OnCollision(direcao); //descomentar
		}


		view.setCenter(player.GetPosition()); //depois de update sempre
		
		
		window.clear(sf::Color(0, 250, 154)); // RED=0, GREEN=255, BLUE=0
		//menu.Draw(window);
		window.setView(view);
		player.Draw(window);
		gosma.Draw(window);
		morcego.Draw(window);
		//platform1.Draw(window);
		//platform2.Draw(window);

		for (Objeto& plataforma : plataformas)
			plataforma.Draw(window);

		window.display();
		

	}

	return 0;
}

