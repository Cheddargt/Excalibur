#include "stdafx.h"
#include "Fase.h"

Fase::Fase() : deltaTime(0.0f)
{
	void Executar(Jogador* player, Jogador *player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers);
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	pausou = false;
}

Fase::~Fase()
{
}
