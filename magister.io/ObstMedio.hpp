#pragma once

#ifndef _OBSTMEDIO_HPP_
#define _OBSTMEDIO_HPP_

#include "Obstaculo.hpp"

namespace Magisterio::Entidades::Obstaculos {

    class ObstMedio : public Obstaculo {
     private:

     public:
        ObstMedio();
        ~ObstMedio() override;
        bool obstaculizar() override;
    };
}
#endif