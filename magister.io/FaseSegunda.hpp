#pragma once

#ifndef _FASESEGUNDA_HPP_
#define _FASESEGUNDA_HPP_

#include "Fase.hpp"

namespace Magisterio::Fases {

    class FaseSegunda : public Fase {

     private:
         const int minSenhorTemebrosos;
         const int maxSenhorTemebrosos;
         const int minLava;
         const int maxLava;

     private: 

         void criarObstaculos() override;
         void criarInimigos() override;

     public:
        FaseSegunda();
        FaseSegunda(Entidades::Personagens::Jogador* pJog1, Entidades::Personagens::Jogador* pJog2 = nullptr);
        ~FaseSegunda() override;
        void executar() override;
        
    };

}
#endif