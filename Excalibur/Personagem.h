#ifndef PERSONAGEM_H
#define PERSONAGEM_H
//falta inclusão de arquivos SFML
#include <Texture.hpp>
#include <Sprite.hpp>


class Personagem
{

    protected:
        int vida;
        int ataque;
        int id;
        float x; //atributo para verificar a posição do personagem
        float y;
        //atributos gráficos
        sf::Texture texture;
        sf::Sprite sprite; //verificar depois se está correto

    public:
        Personagem(int v, int a, int i, float xi, float yi);//falta o parâmetro de inicializar a imagem
        Personagem();
        virtual ~Personagem();

        //respectivas funções gets e sets
        void setVida(const int v);
        int getVida() const;

        void setAtaque(const int a);
        int getAtaque() const;

        void setId(const int i);
        int getId() const;


        void setX(const float xi);
        int getX() const;

        void setY(const float yi);
        int getY()const;

        //funções para parte gráfica do personagem
        virtual void mover()=0;
        virtual void desenhar();

        //função para carregar uma textura chamando uma função da SFML
        void carregaTextura(const std::string &filename, const IntRect &area=IntRect());

        //qui vai precisar de funções para o sprite, ou podemos pensar em usar a função
        //desenhar para esse fiz

};

#endif // PERSONAGEM_H
