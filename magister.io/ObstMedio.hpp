#pragma once

#ifndef _OBSTMEDIO_HPP_
#define _OBSTMEDIO_HPP_

#include "Obstaculo.hpp"

namespace Magisterio::Entidades::Obstaculos {

    class ObstMedio : public Obstaculo {
     private:
        float largura;

     public:
        ObstMedio();
        ~ObstMedio() override;
        bool obstacular() override;
        float getLargura() const;
        void setLargura(float valor);
    };
}
#endif