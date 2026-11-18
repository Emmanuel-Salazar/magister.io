#pragma once

#ifndef _FASE_HPP_
#define _FASE_HPP_

#include "Jogador.hpp"
#include "ListaEntidades.hpp"

namespace Magisterio::Fases {

    class Fase : public Ente {
     protected:

        Listas::ListaEntidades* entidades;
        Entidades::Personagens::Jogador* j1;

        virtual void criarObstaculos() = 0;
        virtual void criarInimigos() = 0;
        virtual void criarCenarios() = 0;

        void inicializaElementos();

     public:

        Fase(Entidades::Personagens::Jogador* jg1);
        ~Fase() override;
        
        void executar() override;
        
        Listas::ListaEntidades* getEntidades() const;
    };
}
#endif