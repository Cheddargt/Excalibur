#include "stdafx.h"
#include "Jogo.h"



Jogo::Jogo() : 
window(sf::VideoMode(512, 512), "Excalibur", sf::Style::Close | sf::Style::Resize),
view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT))
{
	playerTexture.loadFromFile("tux_menino.png"); //verificar
	player2Texture.loadFromFile("tux_menina.png");

	player2 = new Jogador(&player2Texture, sf::Vector2u(3, 9), 0.3f, 100.0f, 3, 1, 1, 200.f);
	player = new Jogador(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 3, 1, 0, 200.f); //speed = 100.0f
	//textura, linhas x colunas animação, animação swaptime, speed, health, ataque, id, jumpHeight
	menu = new Menu(window.getSize().x, window.getSize().y);
	/*menu(window.getSize().x, window.getSize().y);*/
	deltaTime = 0.0f;
	two_players = false;
	/*twoplayers = &two_players;*/
	std::cout << two_players << std::endl;
	

	
}


Jogo::~Jogo() //inicializar variaveis
{
	
}

void Jogo::ResizeView(const sf::RenderWindow& window, sf::View& view) //Para reajustar a janela
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void Jogo::Executar()
{
	//playerTexture.loadFromFile("tux_menino.png");
	//sf::RenderWindow window(sf::VideoMode(512, 512), "Excalibur", sf::Style::Close | sf::Style::Resize); //verificar onde fica
	//Menu menu(window.getSize().x, window.getSize().y); //verificar onde fica
	//sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	//Jogador player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 3, 1, 0, 200.f);

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
		
		fase01.Executar(*player, *player2, window, view, &two_players); //& = player.funcao na fase e * = player->funcao
		//mando o endereço de two_players pro ponteiro *twoplayers
	}
	
}