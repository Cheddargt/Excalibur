#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Jogador.h"
#include "Personagem.h"
#include "Gosma.h"
#include "Morcego.h"
#include "Objeto.h"
#include "Menu.h"
#include "Fase.h"
#include "Fase1.h"


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
	sf::Texture playerTexture;
	Fase1 fase01;
	sf::Clock clock;
	float deltaTime;
	/*sf::RenderWindow window(sf::VideoMode(512, 512), "Excalibur", sf::Style::Close | sf::Style::Resize);
	Menu menu(window.getSize().x, window.getSize().y);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));*/
	
};

