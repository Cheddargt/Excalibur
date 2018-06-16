#pragma once
#include "Fase.h"
#include "Jogador.h"

class Fase1 :
	public Fase
{
public:
	Fase1();
	~Fase1();
	void Executar(Jogador& player, sf::RenderWindow& window, sf::View& view);
	void ResizeView(const sf::RenderWindow& window, sf::View& view);

private:
	sf::Texture chaoTexture;
	sf::Texture gosmaTexture;
	sf::Texture morcegoTexture;
	std::vector<Objeto> plataformas;

};

