#pragma once
#include "Fase.h"
#include "Jogador.h"


class Fase1 :
	public Fase
{
public:
	Fase1();
	~Fase1();
	int Executar(Jogador player, Jogador player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers);
	void ResizeView(const sf::RenderWindow& window, sf::View& view); //verificar

private:
	bool *twoplayers;
	sf::Texture chaoTexture;
	sf::Texture gosmaTexture;
	sf::Texture morcegoTexture;
	sf::Texture pedraTexture;
	sf::Texture buracoTexture;
	sf::Texture entradaTexture;
	sf::Sprite entrada;
	Jogador* player;
	Jogador* player2;

	std::vector<Plataforma> plataformas;
	std::vector<Gosma> gosmas;
	std::vector<Morcego> morcegos;
	std::vector<Obstaculo> obstaculos;
	std::vector<Obstaculo> buracos;
	int num_gosmas;
	int num_morcegos;
	bool checkpoint_alcançado;
	sf::Event *evnt;

};

