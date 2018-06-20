#include "stdafx.h"
#include "Menu.h"



Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		printf("Erro: arial.tff nao foi encontrada na pasta do jogo\n");
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Jogar modo continuo");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	menu[0].setCharacterSize(20);//adicionei isso

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Pular direto para fase 2");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	menu[1].setCharacterSize(20);//adicionei isso

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Sair");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	menu[2].setCharacterSize(20);//adicionei isso

	pausar.setString("Para pausar aperte ESC"); //adicionei isso daqui no menu pra falar como pausar //adicionei isso
	pausar.setFont(font);//adicionei isso
	pausar.setFillColor(sf::Color::Yellow);//adicionei isso
	pausar.setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));//adicionei isso
	pausar.setCharacterSize(14);//adicionei isso//adicionei isso

	continuar.setString("Para continuar aperte F5"); //e como despausar//adicionei isso
	continuar.setFont(font);//adicionei isso
	continuar.setFillColor(sf::Color::Yellow);//adicionei isso
	continuar.setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 5));//adicionei isso
	continuar.setCharacterSize(14); //função para colocar o tamanho da letra//adicionei isso

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}