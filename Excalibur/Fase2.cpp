#include "stdafx.h"
#include "Fase2.h"
#include "time.h"


#define VIEW_HEIGHT 600.0f

Fase2::Fase2() :
	Fase()
{
	twoplayers = nullptr;
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	checkpoint_reached = false;

	srand((unsigned)time(NULL));

	num_esqueletos = ((rand() % 10) + 1);

	backgroundTexture.loadFromFile("background_fase02.png");
	plataformaTexture.loadFromFile("pedra.png");
	chaoTexture.loadFromFile("pedra.png");
	esqueletoTexture.loadFromFile("esqueleto.png");
	caixaTexture.loadFromFile("caixa.png");
	chefaoTexture.loadFromFile("chefao.png");
	espinhoTexture.loadFromFile("espinhos.png");

	background.setScale(5.0f, 3.0f);
	background.setOrigin(40.0f, 300.0f);
	background.setTexture(backgroundTexture);

	evnt = new sf::Event;

}


Fase2::~Fase2()
{
	delete evnt;

}

int Fase2::Executar(Jogador* player, Jogador **player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers)
{

	this->twoplayers = twoplayers;

	player->SetPosition(120.0f, -200.0f);
	if (*twoplayers)
		(*player2)->SetPosition(120.0f, -200.0f);
	

	for (int i = 0; i < num_esqueletos; i++)
	{
		esqueletos.push_back(Esqueleto(&esqueletoTexture, sf::Vector2u(4, 2), 0.3f, 100.0f, 3, 1, i));
		esqueletos[i].SetPosition((float)(200.0f + (400 * i)), 200.0f);
	}

	Chefao chefao(&chefaoTexture, sf::Vector2u(6, 1), 0.3f, 220.0f, 3, 1, 1);


	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(50.0f, 2000.0f), sf::Vector2f(-200.0f, 0.0f)));
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(0.0f, 200.0f)));
	plataformas.push_back(Plataforma(&chaoTexture, sf::Vector2f(3000.0f, 200.0f), sf::Vector2f(1300.0f, 500.0f))); 
	plataformas.push_back(Plataforma(&chaoTexture, sf::Vector2f(5000.0f, 200.0f), sf::Vector2f(1300.0f, 500.0f))); 
	espinhos.push_back(Obstaculo(&espinhoTexture, sf::Vector2f(100.0f, 150.0f), sf::Vector2f(610.0f, 330.0f), 1)); 
	caixas.push_back(Plataforma(&caixaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(1210.0f, 305.0f)));
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(1800.0f, 210.0f))); 
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(3600.0f, 210.0f))); 




	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;



		while (window.pollEvent(*evnt))
		{
			switch (evnt->type)
			{

			case sf::Event::KeyReleased: //pausar o jogo 
				switch ((*evnt).key.code)
				{
				case sf::Keyboard::Escape:
					pausou = true;
					break;

				case sf::Keyboard::F5:
					pausou = false;
					break;
				}
				break;

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				ResizeView(window, view);
				break;

			}
		}

		if (!pausou)
		{
			player->playerUpdate(deltaTime, twoplayers);

			if (*twoplayers)
				(*player2)->playerUpdate(deltaTime, twoplayers);

			for (Esqueleto& esqueleto : esqueletos)
				esqueleto.Update(deltaTime);

			chefao.Update(deltaTime);

		}
		


		for (Plataforma& plataforma : plataformas) //plataforma colidindo com as coisas
		{
			if (plataforma.GetCollider().CheckCollision(&(player->GetCollider()), direcao, 1.0f)) 
				player->OnCollision(direcao);
			if ((*twoplayers) && (plataforma.GetCollider().CheckCollision(&((*player2)->GetCollider()), direcao, 1.0f)))
				(*player2)->OnCollision(direcao);

			if (plataforma.GetCollider().CheckCollision(&(chefao.GetCollider()), direcao, 1.0f))
				chefao.OnCollision(direcao);

			for (Esqueleto& esqueleto : esqueletos)
				if (plataforma.GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
					esqueleto.OnCollision(direcao);

		}

		for (Plataforma& caixa : caixas) //plataforma colidindo com as coisas
		{
			if (caixa.GetCollider().CheckCollision(&(player->GetCollider()), direcao, 0.4f))
				player->OnCollision(direcao);
			if ((*twoplayers) && (caixa.GetCollider().CheckCollision(&((*player2)->GetCollider()), direcao, 0.4f)))
				(*player2)->OnCollision(direcao);

			if (caixa.GetCollider().CheckCollision(&(chefao.GetCollider()), direcao, 1.0f))
				chefao.OnCollision(direcao);

			for (Esqueleto& esqueleto : esqueletos)
				if (caixa.GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
					esqueleto.OnCollision(direcao);

		}

		for (Obstaculo& espinho : espinhos) //checa todas as plataformas pra ver se alguma delas está colidindo com player
		{
			if (espinho.GetCollider().CheckCollision(&(player->GetCollider()), direcao, 1.0f))
				player->ColidiuObstaculo(direcao, espinho.getDano());
			if ((*twoplayers) && (espinho.GetCollider().CheckCollision(&((*player2)->GetCollider()), direcao, 1.0f)))
				(*player2)->ColidiuObstaculo(direcao, espinho.getDano());

			for (Esqueleto& esqueleto : esqueletos)
				if (espinho.GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
					esqueleto.OnCollision(direcao);
		}



	if (player->GetCollider().CheckPlayerCollision(&(chefao.GetCollider()), direcao, 1.0f)) //chefao colidindo com as coisas
	{
		player->ColidiuPersonagem(direcao, chefao.getAttack());
		chefao.ColidiuPersonagem(direcao, player->getAttack());
	}
	if ((*twoplayers) && (player->GetCollider().CheckPlayerCollision(&(chefao.GetCollider()), direcao, 1.0f))) //chefao colidindo com as coisas
	{
		(*player2)->ColidiuPersonagem(direcao, chefao.getAttack());
		chefao.ColidiuPersonagem(direcao, (*player2)->getAttack());
	}


		for (Esqueleto& esqueleto : esqueletos) //esqueleto colidindo com as coisas
		{
			if (player->GetCollider().CheckPlayerCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
			{
				player->ColidiuPersonagem(direcao, esqueleto.getAttack());
				esqueleto.ColidiuPersonagem(direcao, player->getAttack());

			}

			if ((*twoplayers) && ((*player2)->GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 0.5f)))
			{
				(*player2)->ColidiuPersonagem(direcao, esqueleto.getAttack());
				esqueleto.ColidiuPersonagem(direcao, (*player2)->getAttack());

			}

			for (Obstaculo& espinho : espinhos) //checa todas as plataformas pra ver se alguma delas está colidindo com player
			{
				if (espinho.GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
					esqueleto.OnCollision(direcao);
			}


		}


		view.setCenter(player->GetPosition()); 
		window.clear(sf::Color(30, 30, 30)); 
		window.draw(background);
		window.setView(view);
		player->Draw(window);

		if (*twoplayers)
			(*player2)->Draw(window);

		chefao.Draw(window);

		for (unsigned int i = 0; i < esqueletos.size(); i++)
		{
			if (esqueletos[i].getHealth() > 0)
				esqueletos[i].Draw(window);
			else
				esqueletos.erase(esqueletos.begin() + i);
		}

		if ((*twoplayers) && (*player2)->getHealth() <= 0)
		{
			delete (*player2);
			(*player2) = nullptr;
			*twoplayers = false;
		}

		if (checkpoint_reached)
			return (0);

		if (chefao.getVida() <= 0)
			return (1);


		for (Plataforma& plataforma : plataformas)
			plataforma.Draw(window);
		
		for (Plataforma& caixa : caixas)
			caixa.Draw(window);

		for (Obstaculo& espinho : espinhos)
			espinho.Draw(window);

	

		window.display();



	}

	return(0);
}

void Fase2::ResizeView(const sf::RenderWindow & window, sf::View & view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}