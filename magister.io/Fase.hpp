#pragma once

#ifndef _FASE_HPP_
#define _FASE_HPP_

#include "Ente.hpp"
#include "ListaEntidades.hpp"
#include "GerenciadorColisoes.hpp"

namespace Magisterio::Fases {

    class Fase : public Ente {
     protected:
        int numJogadores;

        Entidades::Personagens::Jogador* pJ1;
        Entidades::Personagens::Jogador* pJ2;

        sf::RectangleShape chao;

        Listas::ListaEntidades entidades;
        Gerenciadores::GerenciadorColisoes gc;
        
        void inicializar();
        
        void criarCenario();

        virtual void criarObstaculos() = 0;
        virtual void criarInimigos() = 0;



     public:

        explicit Fase(int numero = 0);
        ~Fase() override;
        
        void executar() override;
        
        Listas::ListaEntidades& getEntidades();
    };
}
#endif