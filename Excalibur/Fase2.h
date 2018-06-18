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
	void Executar(Jogador player, Jogador player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers);
	void ResizeView(const sf::RenderWindow& window, sf::View& view); //verificar

private:
	bool *twoplayers;
	sf::Texture chaoTexture;
	sf::Texture esqueletoTexture;
	sf::Texture chefaoTexture;
	sf::Texture caixaTexture;
	sf::Texture espinhoTexture;
	std::vector<Item> plataformas;
	/*std::vector<Item> caixa;*/
	std::vector<Obstaculo> espinhos;

};

