#pragma once

#include "Obstaculo.hpp"

namespace Entidades {
    class ObstDificil : public Obstaculo {
    private:
        short danosidade;

    public:
        ObstDificil();
        ~ObstDificil() override;
        bool obstacular() override;
        short getDanosidade() const;
        void setDanosidade(short valor);
    };
}
