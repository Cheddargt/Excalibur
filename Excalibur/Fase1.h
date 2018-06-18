#pragma once
#include "Fase.h"
#include "Jogador.h"

class Fase1 :
	public Fase
{
public:
	Fase1();
	~Fase1();
	void Executar(Jogador player, Jogador player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers);
	void ResizeView(const sf::RenderWindow& window, sf::View& view); //verificar

private:
	bool *twoplayers;
	sf::Texture chaoTexture;
	sf::Texture gosmaTexture;
	sf::Texture morcegoTexture;
	sf::Texture pedraTexture;
	std::vector<Item> plataformas;

};

