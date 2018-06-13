#include "Personagem.h"

//Funções construtoras e destrutoras
Personagem::Personagem(int v, int a, int i, float xi, float yi)
{
    vida = v;
    ataque = a;
    id = i;
    x = xi;
    y = yi;
}

Personagem::Personagem()
{
    Personagem(v,a,i,xi,yi);
}

Personagem::~Personagem()
{
    //dtor
}

//Set e get de VIDA
void Personagem::setVida(const int i)
{
    vida = i;
}

int Personagem::getVida()const
{
    return vida;
}

//Set e get de ATAQUE
void Personagem::setAtaque(const int a)
{
    ataque = a;
}

int Personagem::getAtaque()const
{
    return ataque;
}

//Set e get de ID
void Personagem::setId(const int i)
{
    id = i;
}

int Personagem::getId()const
{
    return id;
}

//Set e get de X
void Personagem::setX(const float xi)
{
    x = xi;
}

int Personagem::getX()const
{
    return x;
}

//Set e get de Y
void Personagem::setY(const float yi)
{
    y = yi;
}

int Personagem::getY()const
{
    return y;
}

//Função desenhar
void Personagem::desenhar()
{
    //implementação mais tarde
}

//Função de carregar textura
void Personagem::carregaTextura(const std::string &filename, const IntRect &area=IntRect())
{
    //essa parte precisa ser refeita mais tarde, não sei se está certo, apenas copiei
    //do site oficial do SFML
    texture.loadFromFile(filename, area); //função SFML que carrega textura no atributo "texture"
}
