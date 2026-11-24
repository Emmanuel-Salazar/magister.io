#pragma once

#ifndef _FASEPRIMEIRA_HPP_
#define _FASEPRIMEIRA_HPP_

#include "Fase.hpp"

namespace Magisterio::Fases {
    
    class FasePrimeira : public Fase {

     private:
         const int maxGoblins;
         const int maxEsqueletos;

     protected:
         
         void criarObstaculos() override;
         void criarInimigos() override;

     public:

        FasePrimeira();
        ~FasePrimeira() override;
        void executar() override;
    };
}
#endif