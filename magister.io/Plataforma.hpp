#pragma once

#ifndef _PLATAFORMA_HPP_
#define _PLATAFORMA_HPP_

#include "Obstaculo.hpp"

namespace Magisterio::Entidades::Obstaculos 

    class Plataforma : public Obstaculo {
     private:
        int altura;

     public:
        Plataforma();
        ~Plataforma() override;
        bool obstacular() override;
        int getAltura() const;
        void setAltura(int valor);
    };
}
#endif