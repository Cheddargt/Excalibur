#include "stdafx.h"
#include "Fase1.h"
#define VIEW_HEIGHT 600.0f
#include <iostream>

Fase1::Fase1()
	: Fase ()
{

	/*twoplayers = nullptr;*/
	/*std::cout << twoplayers << std::endl;*/
	void ResizeView(const sf::RenderWindow& window, sf::View& view); //acho que não precisa
	checkpoint_reached = false;

	srand((unsigned)time(NULL));


	num_gosmas = ((rand() % 10) + 1);
	num_morcegos = ((rand() % 5) + 1);

	backgroundTexture.loadFromFile("background_fase01.png");
	pedraTexture.loadFromFile("pedra.png");
	chaoTexture.loadFromFile("plataforma.png");

	gosmaTexture.loadFromFile("gosma.png");
	morcegoTexture.loadFromFile("morcego.png");
	
	plataformaTexture.loadFromFile("plataforma.png");
	buracoTexture.loadFromFile("plataforma_dark.png");
	entradaTexture.loadFromFile("entrada.png");
	
	entrada.setPosition(3750.0f, -180.0f);
	entrada.setScale(1.7f, 1.7f);
	entrada.setTexture(entradaTexture);

	background.setScale(1.5f, 1.0f);
	background.setOrigin(000.0f, 750.0f);
	background.setTexture(backgroundTexture);



	evnt = new sf::Event;
}

Fase1::~Fase1()
{
	delete evnt;
	delete player;
	delete player2;
}

int Fase1::Executar(Jogador* player, Jogador *player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers)
{
	this->player = player;
	this->twoplayers = twoplayers; //ok

	player->SetPosition(100.0f, 200.0);
	if (*twoplayers)
		player2->SetPosition(50.0f, 200.0);

	//body.setPosition(3200.0f, 200.0f); //morcego
	//body.setPosition(1575.0f, 200.0); 
	//body.setPosition(1375.0f, 375.0f); //gosma


	for (int i = 0; i < num_gosmas; i++)
	{
		gosmas.push_back(Gosma(&gosmaTexture, sf::Vector2u(3, 2), 0.3f, 100.0f, 3, 1, i));
		gosmas[i].SetPosition((float) (1575.0f + (227*i)), 200.0f);

		//(1575.0f, 200.0f) até (3850.0f, 200.0f)
	}

	for (int i = 0; i < num_morcegos; i++)
	{
		morcegos.push_back(Morcego(&morcegoTexture, sf::Vector2u(3, 1), 0.3f, 100.0f, 3, 1, i));
		morcegos[i].SetPosition((float)(1875.0f + (210*i)), 200.0f);

		//(1875.0f, 200.0f) até (3850.0f, 200.0f)
	}
	
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(50.0f, 2000.0f), sf::Vector2f(0.0f, 0.0f))); //parede inicio
	plataformas.push_back(Plataforma(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f))); //chao 1
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(500.0f, 310.0f))); //Pedra - obstaculo 1 sem bounce
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(975.0f, 375.0f))); //bloquinho esquerda
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(1275.0f, 375.0f))); //bloquinho direita
	plataformas.push_back(Plataforma(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(1750.0f, 500.0f))); //chao 2
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(200.0f, 250.0f), sf::Vector2f(1825.0f, 285.0f))); //Pedra 2 - obstaculo 2 bounce gosma
	plataformas.push_back(Plataforma(&chaoTexture, sf::Vector2f(1100.0f, 200.0f), sf::Vector2f(3080.0f, 500.0f))); //chao 3
	plataformas.push_back(Plataforma(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(3950.0f, 500.0f))); //chao 4
	plataformas.push_back(Plataforma(&pedraTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(3750.0f, 200.0f))); //Pedra - obstaculo 3 bounce morcego
	plataformas.push_back(Plataforma(&pedraTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(3850.0f, -280.0f))); //Pedra - obstaculo final
	
	buracos.push_back(Obstaculo(&buracoTexture, sf::Vector2f(580.0f, 500.0f), sf::Vector2f(1120.0f, 800.0f), 10)); //buraco 1
	buracos.push_back(Obstaculo(&buracoTexture, sf::Vector2f(580.0f, 500.0f), sf::Vector2f(2420.0f, 800.0f), 10)); //buraco 1

	Checkpoint checkpoint(&pedraTexture, sf::Vector2f(300.0f, 2000.0f), sf::Vector2f(4090.0f, -280.0f)); //Pedra - obstaculo final

	float deltaTime = 0.0f; //verificar
	sf::Clock clock; //verificar

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

	 //verificar
	while (window.pollEvent(*evnt))
	{
		switch (evnt->type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::Resized:
			ResizeView(window, view);
			break;
		}
	}

	player->playerUpdate(deltaTime, twoplayers);

	if (*twoplayers)
		player2->playerUpdate(deltaTime, twoplayers);
	
	for (Gosma& gosma : gosmas)
		gosma.Update(deltaTime);

	for (Morcego& morcego : morcegos)
		morcego.Update(deltaTime);

	/**for (int i = 0; i < plataformas.size(); i++)
	{
	Item& plataforma = plataformas[i];
	}**/

	
	for (Item& plataforma : plataformas) //checa todas as plataformas pra ver se alguma delas está colidindo com player
	{
		if (plataforma.GetCollider().CheckCollision(&(player->GetCollider()), direcao, 1.0f)) //1.0f não empurra, 0 empurra
			player->OnCollision(direcao);
		if (plataforma.GetCollider().CheckCollision(&(player2->GetCollider()), direcao, 1.0f))
			player2->OnCollision(direcao);

		for (Gosma& gosma : gosmas)
			if (plataforma.GetCollider().CheckCollision(&(gosma.GetCollider()), direcao, 1.0f))
				gosma.OnCollision(direcao);
				
		for (Morcego& morcego : morcegos)
			if (plataforma.GetCollider().CheckCollision(&(morcego.GetCollider()), direcao, 1.0f))
				morcego.OnCollision(direcao);
	}

	for (Obstaculo& buraco : buracos)
	{
		if (buraco.GetCollider().CheckCollision(&(player->GetCollider()), direcao, 1.0f))
		{ //1.0f não empurra, 0 empurra
			player->ColidiuObstaculo(direcao, buraco.getDano());
			return (0);
		}		
			
		if (buraco.GetCollider().CheckCollision(&(player2->GetCollider()), direcao, 1.0f))
			player2->ColidiuObstaculo(direcao, buraco.getDano());

		for (Gosma& gosma : gosmas)
			if (buraco.GetCollider().CheckCollision(&(gosma.GetCollider()), direcao, 1.0f))
				gosma.ColidiuObstaculo(direcao, buraco.getDano());

	}


	for (Morcego& morcego : morcegos)
	{
		if (player->GetCollider().CheckPlayerCollision(&(morcego.GetCollider()), direcao, 1.0f))
		{
			player->ColidiuPersonagem(direcao, morcego.getAttack());
			morcego.ColidiuPersonagem(direcao, player->getAttack());
		}

		if ((player2->GetCollider().CheckPlayerCollision(&(morcego.GetCollider()), direcao, 0.5f)) && (twoplayers))
		{
			player2->ColidiuPersonagem(direcao, morcego.getAttack());
			morcego.ColidiuPersonagem(direcao, player2->getAttack());

		}	
	}
	
	for (Gosma& gosma : gosmas)
	{
		if (player->GetCollider().CheckPlayerCollision(&(gosma.GetCollider()), direcao, 1.0f))
		{
			player->ColidiuPersonagem(direcao, gosma.getAttack());
			gosma.ColidiuPersonagem(direcao, player->getAttack());

		}

		if ((player2->GetCollider().CheckCollision(&(gosma.GetCollider()), direcao, 0.5f)) && (twoplayers))
		{
			player2->ColidiuPersonagem(direcao, gosma.getAttack());
			gosma.ColidiuPersonagem(direcao, player2->getAttack());

		}

	}

	view.setCenter(player->GetPosition()); //depois de update sempre
	window.clear(sf::Color(0, 250, 154));
	window.draw(background);
	window.draw(entrada);
	window.setView(view);
	checkpoint.Draw(window);

	if (player->getHealth() <= 0)
	{
		return (0);
	}
	else //game over
	{
		player->Draw(window);
	}


	if (*twoplayers)
		player2->Draw(window);
	

	for (unsigned int i = 0; i < gosmas.size(); i++)
	{
		if (gosmas[i].getHealth() > 0)
			gosmas[i].Draw(window);
		else
			gosmas.erase(gosmas.begin() + i);
	}
	
	for (unsigned int i = 0; i < morcegos.size(); i++)
	{
		if (morcegos[i].getHealth() > 0)
			morcegos[i].Draw(window);
		else
			morcegos.erase(morcegos.begin() + i);
	}
		

	for (Obstaculo& buraco : buracos)
		buraco.Draw(window);

	for (Plataforma& plataforma : plataformas)
		plataforma.Draw(window);

	for (Morcego& morcego : morcegos)
		morcego.Draw(window);

	window.display();

	if (checkpoint.GetCollider().CheckCollision(&(player->GetCollider()), direcao, 1.0f))
	{
		player->OnCollision(direcao);
		return (1);
	}

}
}

void Fase1::ResizeView(const sf::RenderWindow & window, sf::View & view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

