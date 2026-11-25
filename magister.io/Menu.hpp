#pragma once

#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "stdafx.hpp"
#include "Ente.hpp"

namespace Magisterio {

    class Jogo;

    enum class OpcaoMenu {
        Nenhuma,
        JogarFase1,
        JogarFase2,
        ComoJogar,
        Retomar,
        Sair,
        ConfirmarSaida,
        CancelarSaida
    };

    class Menu : public Ente {
    private:
        Jogo* pJogo;
        bool visivel;
        bool confirmandoSaida;
        unsigned int opcaoSelecionada;
        unsigned int opcaoConfirmacao; // 0 = Recusar (esquerda), 1 = Aceitar (direita)

        list<std::optional<sf::Text>> opcoesMenu;

        sf::RectangleShape botaoFase1;
        sf::RectangleShape botaoFase2;
        sf::RectangleShape botaoComoJogar;
        sf::RectangleShape botaoSair;

        sf::RectangleShape fundoConfirmacao;
        sf::RectangleShape caixaConfirmacao;
        sf::RectangleShape botaoRecusar;
        sf::RectangleShape botaoAceitar;

        std::optional<sf::Text> textoTituloConfirmacao;
        std::optional<sf::Text> textoAvisoConfirmacao;
        std::optional<sf::Text> textoRecusar;
        std::optional<sf::Text> textoAceitar;

        sf::Font fonte;

     public:
        Menu();
        ~Menu();

        void setJogo(Jogo* pJ);
        void executar();
        void mostrar();
        void ocultar();
        bool estaVisivel() const;
        OpcaoMenu processarEvento(const sf::Event& evento);
        void desenhar(sf::RenderWindow& destino);

        void mostrarConfirmacaoSaida();
        void ocultarConfirmacaoSaida();
        bool estaConfirmandoSaida() const;
        OpcaoMenu processarEventoConfirmacao(const sf::Event& evento);
        void desenharConfirmacao(sf::RenderWindow& destino);
    };
}
#endif