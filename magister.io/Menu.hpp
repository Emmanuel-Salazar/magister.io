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
        Ranking,
        ComoJogar,
        Retomar,
        Sair,
        Iniciar1Jogador,
        Iniciar2Jogadores,
        ConfirmarSaida,
        CancelarSaida
    };

    enum class TelaMenu {
        Principal,
        SelecaoJogadores,
        EntradaNomes,
        Ranking
    };

    class Menu : public Ente {
    private:
        Jogo* pJogo;
        bool visivel;
        bool confirmandoSaida;
        TelaMenu telaAtual;
        unsigned int opcaoSelecionada;
        unsigned int opcaoJogadores;
        unsigned int opcaoConfirmacao; // 0 = Recusar (esquerda), 1 = Aceitar (direita)
        bool pedindoDoisJogadores;
        int campoNomeAtivo; // 0 = Jogador 1, 1 = Jogador 2
        std::string nomeJogador1;
        std::string nomeJogador2;

        list<std::optional<sf::Text>> opcoesMenu;

        sf::RectangleShape botaoFase1;
        sf::RectangleShape botaoFase2;
        sf::RectangleShape botaoRanking;
        sf::RectangleShape botaoComoJogar;
        sf::RectangleShape botaoSair;

        // Tela de selecao de jogadores (1 ou 2)
        sf::RectangleShape botao1Jogador;
        sf::RectangleShape botao2Jogadores;
        sf::RectangleShape botaoVoltarJogadores;
        std::optional<sf::Text> textoTituloJogadores;
        std::optional<sf::Text> texto1Jogador;
        std::optional<sf::Text> texto2Jogadores;
        std::optional<sf::Text> textoVoltarJogadores;
        std::optional<sf::Text> textoControlesJogadores;

        // Tela de entrada de nomes
        sf::RectangleShape caixaNomes;
        sf::RectangleShape campoNome1;
        sf::RectangleShape campoNome2;
        sf::RectangleShape botaoVoltarNomes;
        sf::RectangleShape botaoIniciarNomes;
        std::optional<sf::Text> textoTituloNomes;
        std::optional<sf::Text> textoLabelNome1;
        std::optional<sf::Text> textoLabelNome2;
        std::optional<sf::Text> textoVoltarNomes;
        std::optional<sf::Text> textoIniciarNomes;

        // Tela de ranking (memoria local)
        sf::RectangleShape caixaRanking;
        sf::RectangleShape botaoVoltarRanking;
        std::optional<sf::Text> textoTituloRanking;
        std::optional<sf::Text> textoVoltarRanking;

        // Modal de confirmacao de saida (ESC)
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
        void mostrarSelecaoJogadores();
        void mostrarEntradaNomes(bool doisJogadores);
        void mostrarRanking();
        void voltarPrincipal();
        const std::string& getNomeJogador1() const;
        const std::string& getNomeJogador2() const;
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