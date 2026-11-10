#pragma once

#include "Obstaculo.hpp"

namespace Entidades {
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
