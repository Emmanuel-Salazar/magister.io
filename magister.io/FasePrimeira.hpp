#pragma once

#ifndef _FASEPRIMEIRA_HPP_
#define _FASEPRIMEIRA_HPP_

#include "Fase.hpp"

namespace Magisterio::Fases {
    
    class FasePrimeira : public Fase {

     private:

         const int maxInimMedios;
         const int maxInimFaceis;

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