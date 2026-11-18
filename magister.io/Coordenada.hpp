#pragma once

#ifndef COORDENADA_HPP_
#define COORDENADA_HPP_

#include "stdafx.hpp"

namespace Magisterio {

    class Coordenada {
     private:
         sf::Vector2f posicao;
     public:

        Coordenada();
        Coordenada(float x, float y);
        ~Coordenada();
        sf::Vector2f getPosicao() const;
        void setPosicao(sf::Vector2f novaPosicao);
    };
}
#endif