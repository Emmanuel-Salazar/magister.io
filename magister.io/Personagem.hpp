#pragma once

#ifndef _PERSONAGEM_HPP_
#define _PERSONAGEM_HPP_

#include "Entidade.hpp"

namespace Magisterio::Entidades::Personagens {
   
    class Personagem : public Entidade 
    {
     protected:

        int numVidas;
        float velocidade;
        float velY;
        const float gravidade;
        sf::Clock relogioPiscaDano;
        bool sofrendoDano;

     public:

        Personagem(int vidas = 7, float vel = 0.f);
        ~Personagem() override;

        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void mover(float deltaTime) = 0;
        virtual void atacar() = 0;

        void desenhar(sf::RenderTarget& destino) override;

        int getNumVidas() const;
        void setNumVidas(int vidas);

        float getVelocidade() const;
        void setVelocidade(float v);

        float getVelY() const;
        void setVelY(float v);

		void operator++(int);
		void operator--(int);
    };
}
#endif