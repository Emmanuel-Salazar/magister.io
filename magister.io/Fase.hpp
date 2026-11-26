#pragma once

#ifndef _FASE_HPP_
#define _FASE_HPP_

#include "Ente.hpp"
#include "ListaEntidades.hpp"
#include "GerenciadorColisoes.hpp"
#include <vector>

namespace Magisterio::Fases {

    class Fase : public Ente {
     protected:
        int numJogadores;

        Entidades::Personagens::Jogador* pJ1;
        Entidades::Personagens::Jogador* pJ2;

        sf::RectangleShape chao;

        Listas::ListaEntidades entidades;
        Gerenciadores::GerenciadorColisoes gc;
        std::vector<sf::FloatRect> plataformasCriadas;

        const int minPlataformas;
        const int maxPlataformas;
        const int minGoblins;
        const int maxGoblins;

        void criarCenario();
        void criarPlataformas();
        void limparEntidades();
        std::vector<sf::Vector2f> gerarPosicoesNoChao(int qntd, float alt) const;
        void posicionarInimigo(Entidades::Personagens::Inimigo* pInim, bool emPlataforma, std::vector<size_t>& plataformasLivres);
        Entidades::Personagens::Jogador* obterAlvoMaisProximo(const sf::Vector2f& pos) const;

        virtual void criarObstaculos() = 0;
        virtual void criarInimigos() = 0;


     public:

        explicit Fase();
        Fase(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2 = nullptr);
        ~Fase() override;
        void desenhar();
        void executar() override;
        void reiniciar();

        void setJogador(Entidades::Personagens::Jogador* pJ);
        void setJogadores(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2);
        void incluirProjetil(Entidades::Projetil* pProj);
        bool temInimigosVivos() const;
        
        const Listas::ListaEntidades& getEntidades() const;
    };
}
#endif