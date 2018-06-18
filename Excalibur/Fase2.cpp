#include "stdafx.h"
#include "Fase2.h"


#define VIEW_HEIGHT 600.0f

Fase2::Fase2()
{
	/*twoplayers = nullptr;*/
	/*std::cout << twoplayers << std::endl;*/
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
}


Fase2::~Fase2()
{
}

void Fase2::Executar(Jogador player, Jogador player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers)
{
	this->twoplayers = twoplayers; //ok

	player.SetPosition(50.0f, -120.0f);
	if(*twoplayers)
		player2.SetPosition(30.0f, -120.0f);

	/*if (*twoplayers)
		player2.SetPosition(00.0f, 200.0f);*/



	std::cout << *twoplayers << std::endl;

	backgroundTexture.loadFromFile("background_fase02.png");
	plataformaTexture.loadFromFile("pedra.png");
	esqueletoTexture.loadFromFile("gosma.png");
	caixaTexture.loadFromFile("caixa.png");
	background.setScale(5.0f, 3.0f);
	background.setOrigin(40.0f, 300.0f);
	background.setTexture(backgroundTexture);
	chaoTexture.loadFromFile("pedra.png");
	esqueletoTexture.loadFromFile("esqueleto.png");
	chefaoTexture.loadFromFile("chefao.png"); //morcego.png
	espinhoTexture.loadFromFile("espinhos.png");



	//Esqueleto morcego(&morcegoTexture, sf::Vector2u(3, 1), 0.3f, 100.0f, 3, 1, 1);
	Esqueleto esqueleto(&esqueletoTexture, sf::Vector2u(4, 2), 0.5f, 100.0f, 3, 1, 1);
	Chefao chefao(&chefaoTexture, sf::Vector2u(1, 6), 0.3f, 100.0f, 3, 1, 1);


	esqueleto.SetPosition(190.0f, -120.0f);
	//std::vector<Gosma> gosmas;
	std::vector<Item> plataformas;
	std::vector<Obstaculo> espinhos;
	//std::vector<Morcego> morcegos;

	//morcegos.push_back(Morcego(&morcegoTexture, sf::Vector2u(3, 1), 0.3f, 100.0f, 3, 1, 1));
	//gosmas.push_back(Gosma(&gosmaTexture, sf::Vector2u(3, 2), 0.3f, 100.0f, 3, 1, 1));

	plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(0.0f, 200.0f))); //Pedra inicio
	plataformas.push_back(Item(&chaoTexture, sf::Vector2f(3000.0f, 200.0f), sf::Vector2f(1300.0f, 500.0f))); //chao 1
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(500.0f, 310.0f))); //Pedra - obstaculo 1 sem bounce
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(975.0f, 375.0f))); //bloquinho esquerda
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(1275.0f, 375.0f))); //bloquinho direita
	//plataformas.push_back(Item(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(1750.0f, 500.0f))); //chao 2
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(200.0f, 250.0f), sf::Vector2f(1825.0f, 285.0f))); //Pedra 2 - obstaculo 2 bounce gosma
	//plataformas.push_back(Item(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(3080.0f, 500.0f))); //chao 3
	//plataformas.push_back(Item(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(3950.0f, 500.0f))); //chao 4
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(3750.0f, 200.0f))); //Pedra - obstaculo 3 bounce morcego
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(3850.0f, -280.0f))); //Pedra - obstaculo 1 

	espinhos.push_back(Obstaculo(&espinhoTexture, sf::Vector2f(200.0f, 180.0f), sf::Vector2f(610.0f, 310.0f), 1)); //caixa 1

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

		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::Resized:
			ResizeView(window, view);
			break;

		

		}
	}

	if (*twoplayers)
		player2.playerUpdate(deltaTime, twoplayers);
	player.playerUpdate(deltaTime, twoplayers);
	esqueleto.Update(deltaTime);


	for (Item& plataforma : plataformas) //checa todas as plataformas pra ver se alguma delas está colidindo com player
	{
		if (plataforma.GetCollider().CheckCollision(&(player.GetCollider()), direcao, 1.0f)) //1.0f não empurra, 0 empurra
			player.OnCollision(direcao);
		if (plataforma.GetCollider().CheckCollision(&(player2.GetCollider()), direcao, 1.0f))
			player2.OnCollision(direcao);

		if (plataforma.GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 1.0f)) //1.0f não empurra, 0 empurra
			esqueleto.OnCollision(direcao);

	}

	for (Obstaculo& espinho : espinhos) //checa todas as plataformas pra ver se alguma delas está colidindo com player
	{
		if (espinho.GetCollider().CheckCollision(&(player.GetCollider()), direcao, 1.0f)) //1.0f não empurra, 0 empurra
			player.ColidiuObstaculo(direcao, espinho.getDano());
		if ((espinho.GetCollider().CheckCollision(&(player2.GetCollider()), direcao, 1.0f)) && (twoplayers))
			player2.ColidiuObstaculo(direcao, espinho.getDano());

		if (espinho.GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 1.0f)) //1.0f não empurra, 0 empurra
			esqueleto.OnCollision(direcao);	
	}
			

	if (player.GetCollider().CheckPlayerCollision(&(chefao.GetCollider()), direcao, 1.0f)) //mudei pra check player collision
	{
		player.ColidiuPersonagem(direcao, chefao.getAttack());
		chefao.ColidiuPersonagem(direcao, player.getAttack());
	}


	if (player.GetCollider().CheckPlayerCollision(&(esqueleto.GetCollider()), direcao, 1.0f)) //mudei pra check player collision
	{
		player.ColidiuPersonagem(direcao, esqueleto.getAttack());		
		esqueleto.ColidiuPersonagem(direcao, player.getAttack());
	}

	if (player2.GetCollider().CheckPlayerCollision(&(esqueleto.GetCollider()), direcao, 1.0f) && (*twoplayers)) //mudei pra check player collision
	{
		player2.ColidiuPersonagem(direcao, esqueleto.getAttack());
		esqueleto.ColidiuPersonagem(direcao, player2.getAttack());
	}


	view.setCenter(player.GetPosition()); //depois de update sempre

	window.clear(sf::Color(0, 0, 0)); // RED=0, GREEN=255, BLUE=0
	window.draw(background);
	window.setView(view);
	player.Draw(window);
	if (*twoplayers)
		player2.Draw(window);
	esqueleto.Draw(window);
	chefao.Draw(window);


	/*for (Esqueleto& esqueleto : esqueletos)
	esqueleto.Draw(window);*/

	for (Item& plataforma : plataformas)
				plataforma.Draw(window);

			for (Obstaculo& espinho : espinhos)
				espinho.Draw(window);

			window.display();


		}
	}

void Fase2::ResizeView(const sf::RenderWindow & window, sf::View & view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

