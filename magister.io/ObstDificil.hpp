#pragma once

#ifndef _OBSTDIFICIL_HPP_
#define _OBSTDIFICIL_HPP_

#include "Obstaculo.hpp"

namespace Magisterio::Entidades::Obstaculos{

    class ObstDificil : public Obstaculo {
     private:

        short danosidade;

     public:

        ObstDificil();
        ~ObstDificil() override;
        bool obstaculizar() override;
        short getDanosidade() const;
        void setDanosidade(short valor);
    };
}
#endif