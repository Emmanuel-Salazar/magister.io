#pragma once

#include "Entidade.hpp"

namespace Entidades {
    class Obstaculo : public Entidade {
    protected:
        int dano;

    public:
        Obstaculo();
        ~Obstaculo() override;
        virtual bool obstacular() = 0;
        void executar() override;
        void salvar() override;
        int getDano() const;
        void setDano(int valor);
    };
}
