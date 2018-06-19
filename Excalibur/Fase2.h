#pragma once
#include "Fase.h"
#include "Jogador.h"
#include "Obstaculo.h"
#include "Esqueleto.h"
#include "Chefao.h"


class Fase2 :
	public Fase
{
public:
	Fase2();
	~Fase2();
	int Executar(Jogador* player, Jogador* player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers);
	void ResizeView(const sf::RenderWindow& window, sf::View& view); //verificar

private:
	bool *twoplayers;
	sf::Texture chaoTexture;
	sf::Texture esqueletoTexture;
	sf::Texture chefaoTexture;
	sf::Texture caixaTexture;
	sf::Texture espinhoTexture;
	sf::Texture armaTextureEsq;
	sf::Texture armaTextureDir;
	std::vector<Plataforma> plataformas;
	std::vector<Plataforma> caixas;
	std::vector<Obstaculo> obstaculos;
	std::vector<Obstaculo> lavas;
	std::vector<Esqueleto> esqueletos;
	std::vector<Obstaculo> espinhos;
	std::vector<Arma> armas;

	int num_esqueletos;
	bool checkpoint_reached;
	sf::Event *evnt;

};

