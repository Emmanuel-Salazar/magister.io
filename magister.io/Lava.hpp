#pragma once

#ifndef _LAVA_HPP_
#define _LAVA_HPP_

#include "Obstaculo.hpp"
#include <SFML/System/Clock.hpp>

namespace Magisterio::Entidades::Obstaculos {

    class Lava : public Obstaculo {
     private:
        short danosidade;
        sf::Clock relogioDano;

     public:
        Lava(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), short dano = 1);
        ~Lava() override;

        void obstaculizar() override;
        void obstaculizar(Personagens::Jogador* pJogador) override;

        short getDanosidade() const;
        void setDanosidade(short valor);
    };
}
#endif
