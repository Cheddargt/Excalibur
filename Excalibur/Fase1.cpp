#include "stdafx.h"
#include "Fase1.h"
#define VIEW_HEIGHT 600.0f

Fase1::Fase1()
{
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
}

Fase1::~Fase1()
{
}

void Fase1::Executar(Jogador& player, sf::RenderWindow& window, sf::View& view)
{
	backgroundTexture.loadFromFile("background.png");
	plataformaTexture.loadFromFile("plataforma.png");

	background.setScale(1.5f, 0.6f);
	background.setOrigin(000.0f, 550.0f);
	background.setTexture(backgroundTexture);
	chaoTexture.loadFromFile("plataforma.png");
	gosmaTexture.loadFromFile("gosma.png");
	morcegoTexture.loadFromFile("morcego.png"); //morcego.png

	Gosma gosma(&gosmaTexture, sf::Vector2u(3, 2), 0.3f, 100.0f, 3, 1, 1);
	Morcego morcego(&morcegoTexture, sf::Vector2u(3, 1), 0.3f, 100.0f, 3, 1, 1);

	std::vector<Objeto> plataformas;

	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(50.0f, 2000.0f), sf::Vector2f(0.0f, 0.0f))); //parede inicio
	plataformas.push_back(Objeto(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f))); //chao 1
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(500.0f, 310.0f))); //Pedra - obstaculo 1 sem bounce
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(975.0f, 375.0f))); //bloquinho esquerda
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(1275.0f, 375.0f))); //bloquinho direita
	plataformas.push_back(Objeto(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(1750.0f, 500.0f))); //chao 2
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(200.0f, 250.0f), sf::Vector2f(1825.0f, 285.0f))); //Pedra - obstaculo 2 bounce gosma
	plataformas.push_back(Objeto(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(3080.0f, 500.0f))); //chao 3
	plataformas.push_back(Objeto(&plataformaTexture, sf::Vector2f(50.0f, 2000.0f), sf::Vector2f(3580.0f, 0.0f))); //parede


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


	player.Update(deltaTime);
	gosma.Update(deltaTime);
	morcego.Update(deltaTime);

	sf::Vector2f direcao;

	//passada pra OnCollision e pra player OnCollision

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
	}

	if (player.GetCollider().CheckCollision(&(gosma.GetCollider()), direcao, 1.0f))
	{
		player.OnCollision(direcao);
		player.ColidiuPersonagem(direcao, gosma.getAttack());
		gosma.OnCollision(direcao);
	}


	if (player.GetCollider().CheckCollision(&(morcego.GetCollider()), direcao, 1.0f))
	{
		player.OnCollision(direcao);
		player.ColidiuPersonagem(direcao, morcego.getAttack());
		morcego.OnCollision(direcao);
	}


	view.setCenter(player.GetPosition()); //depois de update sempre


	window.clear(sf::Color(0, 250, 154)); // RED=0, GREEN=255, BLUE=0
	window.draw(background);
	window.setView(view);
	player.Draw(window);
	gosma.Draw(window);
	morcego.Draw(window);

	for (Objeto& plataforma : plataformas)
		plataforma.Draw(window);

	window.display();


}
}

void Fase1::ResizeView(const sf::RenderWindow & window, sf::View & view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

