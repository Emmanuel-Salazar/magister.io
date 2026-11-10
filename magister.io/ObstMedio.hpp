#pragma once

#include "Obstaculo.hpp"

namespace Entidades {
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
