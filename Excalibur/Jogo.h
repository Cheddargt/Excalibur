#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Jogador.h"
#include "Menu.h"
#include "Fase1.h"
#include "Fase2.h"

#define VIEW_HEIGHT 600.0f

class Jogo
{
public:
	Jogo();
	void Executar();
	~Jogo();
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	/*void setWindow () { }*/

private:
	
	sf::View view;
	bool fase1_zerada;
	Menu *menu;
	sf::RenderWindow window;
	Jogador* player;
	Jogador* player2;
	sf::Texture playerTexture;
	sf::Texture player2Texture;
	Fase1 *fase01;
	Fase2 *fase02;
	sf::Clock clock;
	float deltaTime;
	bool two_players;
	sf::Event evnt; //verificar
	
};

