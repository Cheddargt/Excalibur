#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3

//Esse é o básico do menu. Podemos adicionar ainda mais alguns itens caso seja necessário.

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void Draw(sf::RenderWindow &window); //Função para desenhar o menu na tela
	void MoveUp(); //Função para quando a tecla up for apertada, e selecionar o item de cima
	void MoveDown(); //" para baixo
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

