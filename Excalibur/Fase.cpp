#include "stdafx.h"
#include "Fase.h"

Fase::Fase()
{
	void Executar(Jogador* player, Jogador *player2, sf::RenderWindow& window, sf::View& view, bool* twoplayers);
	void ResizeView(const sf::RenderWindow& window, sf::View& view);

	player = nullptr;
	player2 = nullptr;
}

Fase::~Fase()
{
}
