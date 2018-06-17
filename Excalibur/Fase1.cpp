#include "stdafx.h"
#include "Fase1.h"
#define VIEW_HEIGHT 600.0f

Fase1::Fase1()
{
	/*twoplayers = nullptr;*/
	/*std::cout << twoplayers << std::endl;*/
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	
}

Fase1::~Fase1()
{
}

void Fase1::Executar(Jogador player, Jogador player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers)
{
	this->twoplayers = twoplayers; //ok

	std::cout << *twoplayers << std::endl;

	backgroundTexture.loadFromFile("background_fase01.png");
	plataformaTexture.loadFromFile("plataforma.png");

	background.setScale(1.5f, 0.6f);
	background.setOrigin(000.0f, 550.0f);
	background.setTexture(backgroundTexture);
	chaoTexture.loadFromFile("plataforma.png");
	gosmaTexture.loadFromFile("gosma.png");
	morcegoTexture.loadFromFile("morcego.png"); //morcego.png

	Gosma gosma(&gosmaTexture, sf::Vector2u(3, 2), 0.3f, 100.0f, 3, 1, 1);
	Morcego morcego(&morcegoTexture, sf::Vector2u(3, 1), 0.3f, 100.0f, 3, 1, 1);

	//std::vector<Gosma> gosmas;
	std::vector<Objeto> plataformas;
	//std::vector<Morcego> morcegos;

	//morcegos.push_back(Morcego(&morcegoTexture, sf::Vector2u(3, 1), 0.3f, 100.0f, 3, 1, 1));
	//gosmas.push_back(Gosma(&gosmaTexture, sf::Vector2u(3, 2), 0.3f, 100.0f, 3, 1, 1));

	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(50.0f, 2000.0f), sf::Vector2f(0.0f, 0.0f))); //parede inicio
	plataformas.push_back(Objeto(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f))); //chao 1
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(500.0f, 310.0f))); //Pedra - obstaculo 1 sem bounce
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(975.0f, 375.0f))); //bloquinho esquerda
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(1275.0f, 375.0f))); //bloquinho direita
	plataformas.push_back(Objeto(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(1750.0f, 500.0f))); //chao 2
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(200.0f, 250.0f), sf::Vector2f(1825.0f, 285.0f))); //Pedra 2 - obstaculo 2 bounce gosma
	plataformas.push_back(Objeto(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(3080.0f, 500.0f))); //chao 3
	plataformas.push_back(Objeto(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(3950.0f, 500.0f))); //chao 4
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(3750.0f, 200.0f))); //Pedra - obstaculo 3 bounce morcego
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(3850.0f, -280.0f))); //Pedra - obstaculo 1 




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
	
	gosma.Update(deltaTime);
	/*for (Gosma& gosma : gosmas)
		gosma.Update(deltaTime);*/


	morcego.Update(deltaTime);
	/*for (Morcego& morcego : morcegos)
		morcego.Update(deltaTime);*/
	


	sf::Vector2f direcao;

	//passada pra OnCollision e pra player OnCollision

	/**for (int i = 0; i < plataformas.size(); i++)
	{
	Objeto& plataforma = plataformas[i];
	}**/

	for (Objeto& plataforma : plataformas) //checa todas as plataformas pra ver se alguma delas está colidindo com player
	{
		if (plataforma.GetCollider().CheckCollision(&(player.GetCollider()), direcao, 1.0f)) //1.0f não empurra, 0 empurra
			player.OnCollision(direcao);
		if ((plataforma.GetCollider().CheckCollision(&(player2.GetCollider()), direcao, 1.0f)) && (twoplayers))
			player2.OnCollision(direcao);

		if (plataforma.GetCollider().CheckCollision(&(gosma.GetCollider()), direcao, 1.0f))
			gosma.OnCollision(direcao);
		/*for (Gosma& gosma : gosmas)
			if (plataforma.GetCollider().CheckCollision(&(gosma.GetCollider()), direcao, 1.0f))
				gosma.OnCollision(direcao);*/

		if (plataforma.GetCollider().CheckCollision(&(morcego.GetCollider()), direcao, 1.0f))
			morcego.OnCollision(direcao);
		/*for (Morcego& morcego : morcegos)
			if (plataforma.GetCollider().CheckCollision(&(morcego.GetCollider()), direcao, 1.0f))
				morcego.OnCollision(direcao);
		*/
	}

	//for (Morcego& morcego : morcegos)
	//{
	//	if (morcego.GetCollider().CheckPlayerCollision(&(player.GetCollider()), direcao, 1.0f))
	//	{

	//		player.ColidiuPersonagem(direcao, morcego.getAttack());
	//		morcego.ColidiuPersonagem(direcao, player.getAttack());

	//	}

	//	if ((morcego.GetCollider().CheckCollision(&(player2.GetCollider()), direcao, 0.5f)) && (twoplayers))
	//	{
	//		player2.ColidiuPersonagem(direcao, morcego.getAttack());
	//		player2.OnCollision(direcao);
	//		morcego.ColidiuPersonagem(direcao, player.getAttack());

	//	}
	//			
	//}

	if (player.GetCollider().CheckPlayerCollision(&(morcego.GetCollider()), direcao, 1.0f)) //mudei pra check player collision
	{
		/*player.OnCollision(direcao);*/
		player.ColidiuPersonagem(direcao, morcego.getAttack());
		morcego.ColidiuPersonagem(direcao, player.getAttack());
	}
	
	//for (Gosma& gosma : gosmas)
	//{
	//	if (gosma.GetCollider().CheckPlayerCollision(&(player.GetCollider()), direcao, 1.0f))
	//	{

	//		player.ColidiuPersonagem(direcao, gosma.getAttack());
	//		gosma.ColidiuPersonagem(direcao, player.getAttack());

	//	}

	//	if ((gosma.GetCollider().CheckCollision(&(player2.GetCollider()), direcao, 0.5f)) && (twoplayers))
	//	{
	//		player2.ColidiuPersonagem(direcao, gosma.getAttack());
	//		//player2.OnCollision(direcao);
	//		gosma.ColidiuPersonagem(direcao, player.getAttack());

	//	}
	//			
	//}

	if (player.GetCollider().CheckPlayerCollision(&(gosma.GetCollider()), direcao, 1.0f)) //mudei pra check player collision
	{
		/*player.OnCollision(direcao);*/
		player.ColidiuPersonagem(direcao, gosma.getAttack());
		gosma.ColidiuPersonagem(direcao, player.getAttack());
	}

	if (player2.GetCollider().CheckPlayerCollision(&(gosma.GetCollider()), direcao, 1.0f)) //mudei pra check player collision
	{
		player2.ColidiuPersonagem(direcao, gosma.getAttack());
		gosma.ColidiuPersonagem(direcao, player2.getAttack());
	}


	view.setCenter(player.GetPosition()); //depois de update sempre

	window.clear(sf::Color(0, 250, 154)); // RED=0, GREEN=255, BLUE=0
	window.draw(background);
	window.setView(view);
	player.Draw(window);
	if (*twoplayers)
		player2.Draw(window);
	gosma.Draw(window);
	morcego.Draw(window);


	/*for (Gosma& gosma : gosmas)
		gosma.Draw(window);*/

	for (Objeto& plataforma : plataformas)
		plataforma.Draw(window);

	/*for (Morcego& morcego : morcegos)
		morcego.Draw(window);*/

	window.display();


}
}

void Fase1::ResizeView(const sf::RenderWindow & window, sf::View & view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

