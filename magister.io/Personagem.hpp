#pragma once

#ifndef _PERSONAGEM_HPP_
#define _PERSONAGEM_HPP_

#include "Entidade.hpp"

namespace Magisterio::Entidades::Personagens {
   
    class Personagem : public Entidade 
    {
     protected:

        int numVidas;

        bool emSuperficie;
        static const float gravidade;


     public:

        Personagem(int vidas = 3);
        ~Personagem() override;

        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void mover(float deltaTime) = 0;
        virtual void atacar() = 0;

        int getNumVidas() const;
        void setNumVidas(int vidas);
    };
}
#endif