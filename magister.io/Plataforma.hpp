#pragma once

#ifndef _PLATAFORMA_HPP_
#define _PLATAFORMA_HPP_

#include "Obstaculo.hpp"

namespace Magisterio::Entidades::Obstaculos{ 

    class Plataforma : public Obstaculo {
     private:

     public:
        Plataforma(sf::Vector2f pos = sf::Vector2f(0.0f, 200.0f));
        ~Plataforma() override;
        bool obstaculizar() override;
    };
}
#endif