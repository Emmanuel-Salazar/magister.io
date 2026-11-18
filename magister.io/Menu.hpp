#pragma once

#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "stdafx.hpp"
#include "Ente.hpp"

class Jogo;


namespace Magisterio {

    enum class OpcaoMenu {
        Nenhuma,
        Jogar,
        Retomar,
        Sair
    };

    class Menu : public Ente {
     private:

        Jogo* pJogo;
        bool visivel;
        unsigned int opcaoSelecionada;
        sf::RectangleShape botaoFase1;
        sf::RectangleShape botaoFase2;
        sf::RectangleShape botaoSair;
        sf::Font fonte;
        std::optional<sf::Text> textoFase1;
        std::optional<sf::Text> textoFase2;
        std::optional<sf::Text> textoSair;

     public:
        Menu();
        ~Menu();

        void executar();
        void mostrar();
        void ocultar();
        bool estaVisivel() const;
        OpcaoMenu processarEvento(const sf::Event& evento);
        void desenhar(sf::RenderWindow& destino);
    };
}
#endif