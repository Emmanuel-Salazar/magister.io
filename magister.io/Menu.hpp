#pragma once

#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "stdafx.hpp"
#include "Ente.hpp"

class Jogo;


namespace Magisterio {

    enum class OpcaoMenu {
        Nenhuma,
        JogarFase1,
        JogarFase2,
        ComoJogar,
        Retomar,
        Sair
    };

    class Menu : public Ente {
    private:
        Jogo* pJogo;
        bool visivel;
        unsigned int opcaoSelecionada;

        list<std::optional<sf::Text>> opcoesMenu;

        sf::RectangleShape botaoFase1;
        sf::RectangleShape botaoFase2;
        sf::RectangleShape botaoComoJogar;
        sf::RectangleShape botaoSair;

        sf::Font fonte;

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