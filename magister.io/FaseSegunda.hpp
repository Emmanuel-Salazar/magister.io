#pragma once

#ifndef _FASESEGUNDA_HPP_
#define _FASESEGUNDA_HPP_

#include "Fase.hpp"

namespace Magisterio::Fases {

    class FaseSegunda : public Fase {

     private:
         const int maxChefoes;
         const int maxInimMedios;

     private: 

         void criarObstaculos() override;
         void criarInimigos() override;

     public:
        FaseSegunda();
        ~FaseSegunda() override;
        
    };

}
#endif