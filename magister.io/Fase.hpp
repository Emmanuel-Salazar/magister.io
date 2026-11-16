#pragma once

#ifndef _FASE_HPP_
#define _FASE_HPP_

#include "Ente.hpp"
#include "ListaEntidades.hpp"
#include "GerenciadorColisoes.hpp"

namespace Magisterio::Fases {

    class Fase : public Ente {
     protected:

        Listas::ListaEntidades entidades;
        Gerenciadores::GerenciadorColisoes gc;

        virtual void criarObstaculos() = 0;
        virtual void criarInimigos() = 0;
        virtual void criarCenarios() = 0;

     public:

        explicit Fase(int numero = 0);
        ~Fase() override;
        
        void executar() override;
        
        Listas::ListaEntidades& getEntidades();
    };
}
#endif