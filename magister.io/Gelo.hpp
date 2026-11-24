#pragma once

#ifndef _GELO_HPP_
#define _GELO_HPP_

#include "Obstaculo.hpp"

namespace Magisterio::Entidades::Obstaculos {

    class Gelo : public Obstaculo {
     private:
        float atrito;

     public:
        Gelo(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), float coefAtrito = 0.4f);
        ~Gelo() override;

        void obstaculizar() override;
        void obstaculizar(Personagens::Jogador* pJogador) override;

        float getAtrito() const;
        void setAtrito(float coef);
    };
}
#endif
