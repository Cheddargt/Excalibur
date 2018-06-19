#include "stdafx.h"
#include "Fase2.h"
#include "time.h"


#define VIEW_HEIGHT 600.0f

Fase2::Fase2() :
	Fase()
{
	//Jogador* player = nullptr;
	//Jogador* player2 = nullptr;
	///*twoplayers = nullptr;*/
	///*std::cout << twoplayers << std::endl;*/
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	checkpoint_reached = false;

	srand((unsigned)time(NULL));

	num_esqueletos = ((rand() % 10) + 1);

	backgroundTexture.loadFromFile("background_fase02.png");
	plataformaTexture.loadFromFile("pedra.png");
	chaoTexture.loadFromFile("pedra.png");

	esqueletoTexture.loadFromFile("esqueleto.png");
	caixaTexture.loadFromFile("caixa.png");

	chefaoTexture.loadFromFile("chefao.png"); //morcego.png
	espinhoTexture.loadFromFile("espinhos.png");

	armaTextureEsq.loadFromFile("espada_menino_esq.png");
	armaTextureDir.loadFromFile("espada_menino_dir.png");

	//excalibur.setPosition(, )
	//excalibur.setScale(, );
	//excalibur.setTexture();

	background.setScale(5.0f, 3.0f);
	background.setOrigin(40.0f, 300.0f);
	background.setTexture(backgroundTexture);

	evnt = new sf::Event;

}


Fase2::~Fase2()
{
	delete evnt;

}

int Fase2::Executar(Jogador* player, Jogador *player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers)
{

	this->player = player;
	this->twoplayers = twoplayers; //ok

	/*player->SetPosition(1900.0f, 10.0f);*/
	player->SetPosition(50.0f, -120.0f);
	if (*twoplayers)
	{
		player2->SetPosition(50.0f, -120.0f);
		player2->setHealth(5);

	}

	player->setHealth(5);


	for (int i = 0; i < num_esqueletos; i++)
	{
		esqueletos.push_back(Esqueleto(&esqueletoTexture, sf::Vector2u(4, 2), 0.3f, 100.0f, 3, 1, i));
		esqueletos[i].SetPosition((float)(200.0f + (400 * i)), 200.0f);
		//esqueleto.SetPosition(190.0f, 200.0f);

	}

	Chefao chefao(&chefaoTexture, sf::Vector2u(6, 1), 0.3f, 220.0f, 3, 1, 1);

	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(50.0f, 2000.0f), sf::Vector2f(-200.0f, 0.0f))); //parede inicio
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(0.0f, 200.0f))); //Pedra inicio
	plataformas.push_back(Plataforma(&chaoTexture, sf::Vector2f(3000.0f, 200.0f), sf::Vector2f(1300.0f, 500.0f))); //chao 1
	//caixas.push_back(Plataforma(&caixaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(1210.0f, 330.0f))); //Pedra - obstaculo 1 sem bounce
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(975.0f, 375.0f))); //bloquinho esquerda
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(1275.0f, 375.0f))); //bloquinho direita
	//plataformas.push_back(Item(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(1750.0f, 500.0f))); //chao 2
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(200.0f, 250.0f), sf::Vector2f(1825.0f, 285.0f))); //Pedra 2 - obstaculo 2 bounce gosma
	//plataformas.push_back(Item(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(3080.0f, 500.0f))); //chao 3
	//plataformas.push_back(Item(&chaoTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(3950.0f, 500.0f))); //chao 4
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(3750.0f, 200.0f))); //Pedra - obstaculo 3 bounce morcego
	//plataformas.push_back(Item(&plataformaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(3850.0f, -280.0f))); //Pedra - obstaculo 1 

	plataformas.push_back(Plataforma(&chaoTexture, sf::Vector2f(5000.0f, 200.0f), sf::Vector2f(1300.0f, 500.0f))); //chao 2
	espinhos.push_back(Obstaculo(&espinhoTexture, sf::Vector2f(100.0f, 150.0f), sf::Vector2f(610.0f, 330.0f), 1)); //espinhos
	caixas.push_back(Plataforma(&caixaTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(1210.0f, 305.0f)));
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(1800.0f, 210.0f))); //pedra grande 1
	Arma arma(&armaTextureDir, sf::Vector2f(150.0f, 50.0f), sf::Vector2f(0.0f, 0.0f), 5); //(150.0f, 50.0f)
	plataformas.push_back(Plataforma(&plataformaTexture, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(3600.0f, 210.0f))); //pedra grande 2

	float deltaTime = 0.0f;
	sf::Clock clock;


	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;



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

		for (Esqueleto& esqueleto : esqueletos)
			esqueleto.Update(deltaTime);

		chefao.Update(deltaTime);


		for (Plataforma& plataforma : plataformas) //plataforma colidindo com as coisas
		{
			if (plataforma.GetCollider().CheckCollision(&(player->GetCollider()), direcao, 1.0f)) 
				player->OnCollision(direcao);
			if (plataforma.GetCollider().CheckCollision(&(player2->GetCollider()), direcao, 1.0f))
				player2->OnCollision(direcao);

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
			if (caixa.GetCollider().CheckCollision(&(player2->GetCollider()), direcao, 0.4f))
				player2->OnCollision(direcao);

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
			if ((espinho.GetCollider().CheckCollision(&(player2->GetCollider()), direcao, 1.0f)) && (twoplayers))
				player2->ColidiuObstaculo(direcao, espinho.getDano());

			for (Esqueleto& esqueleto : esqueletos)
				if (espinho.GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
					esqueleto.OnCollision(direcao);
		}

		for (Obstaculo& lava : lavas) //lava colidindo com as coisas
		{
			if (lava.GetCollider().CheckCollision(&(player->GetCollider()), direcao, 1.0f)) 
				player->ColidiuObstaculo(direcao, lava.getDano());
			if ((lava.GetCollider().CheckCollision(&(player2->GetCollider()), direcao, 1.0f)) && (twoplayers))
				player2->ColidiuObstaculo(direcao, lava.getDano());

			for (Esqueleto& esqueleto : esqueletos)
				if (lava.GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
					esqueleto.ColidiuObstaculo(direcao, lava.getDano());
		}


		if (player->GetCollider().CheckPlayerCollision(&(chefao.GetCollider()), direcao, 1.0f)) //chefao colidindo com as coisas
		{
			player->ColidiuPersonagem(direcao, chefao.getAttack());
			chefao.ColidiuPersonagem(direcao, player->getAttack());
		}


		for (Esqueleto& esqueleto : esqueletos) //esqueleto colidindo com as coisas
		{
			if (player->GetCollider().CheckPlayerCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
			{
				player->ColidiuPersonagem(direcao, esqueleto.getAttack());
				esqueleto.ColidiuPersonagem(direcao, player->getAttack());

			}

			if ((player2->GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 0.5f)) && (twoplayers))
			{
				player2->ColidiuPersonagem(direcao, esqueleto.getAttack());
				esqueleto.ColidiuPersonagem(direcao, player2->getAttack());

			}

			for (Obstaculo& espinho : espinhos) //checa todas as plataformas pra ver se alguma delas está colidindo com player
			{
				if (espinho.GetCollider().CheckCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
					esqueleto.OnCollision(direcao);
			}

			if (arma.GetCollider().CheckPlayerCollision(&(esqueleto.GetCollider()), direcao, 1.0f))
			{
				esqueleto.ColidiuObstaculo(direcao, arma.getAttack());
			}

		}


		view.setCenter(player->GetPosition()); //depois de update sempre
		window.clear(sf::Color(30, 30, 30)); // RED=0, GREEN=255, BLUE=0
		window.draw(background);
		window.setView(view);
		player->Draw(window);

		if (*twoplayers)
			player2->Draw(window);

		chefao.Draw(window);

		for (unsigned int i = 0; i < esqueletos.size(); i++)
		{
			if (esqueletos[i].getHealth() > 0)
				esqueletos[i].Draw(window);
			else
				esqueletos.erase(esqueletos.begin() + i);
		}

		////Excalibur
		//////if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		//////{
		//////	if (player->getFaceRight())
		//////	{
		//////		arma.setTexture(&armaTextureDir);
		//////		arma.setPosition(player->GetPosition());
		//////		arma.Draw(window);
		//////		/*arma.setPosition(sf::Vector2u(0.0f, 0.0f));*/
		//////	}
		//////	else
		//////	{
		//////		arma.setTexture(&armaTextureEsq);
		//////		arma.setPosition(player->GetPosition());
		//////		arma.Draw(window);
		//////		/*arma.setPosition(0.0f, 0.0f);*/
		//////	}
		//////	
		//////}
		//////else
		//////{

		//////}

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
}

void Fase2::ResizeView(const sf::RenderWindow & window, sf::View & view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

