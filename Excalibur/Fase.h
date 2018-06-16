#pragma once
#include <SFML/Graphics.hpp>
#include "Gosma.h"
#include "Morcego.h"
#include "Objeto.h"
#include "Jogador.h"
#include <iostream>
#include <vector>

class Fase
{
public:
	Fase();
	~Fase();
	virtual void Executar(Jogador& player, sf::RenderWindow& window, sf::View& view) = 0;
	void ResizeView(const sf::RenderWindow& window, sf::View& view);

protected:
	sf::Texture backgroundTexture;
	sf::Texture plataformaTexture;
	sf::Sprite background;
	sf::Vector2f direcao; //passada pra OnCollision e pra player OnCollision
	
};

