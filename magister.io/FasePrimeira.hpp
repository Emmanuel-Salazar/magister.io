#pragma once

#ifndef _FASEPRIMEIRA_HPP_
#define _FASEPRIMEIRA_HPP_

#include "Fase.hpp"

namespace Magisterio::Fases {
    
    class FasePrimeira : public Fase {

     private:
         const int minEsqueletos;
         const int maxEsqueletos;
         const int minGelo;
         const int maxGelo;

     protected:
         
         void criarObstaculos() override;
         void criarInimigos() override;

     public:

        FasePrimeira();
        FasePrimeira(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2 = nullptr);
        ~FasePrimeira() override;
        void executar() override;
    };
}
#endif