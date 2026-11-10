#pragma once

#include "Inimigo.hpp"

namespace Entidades {
    class InimFacil : public Inimigo {
    public:
        InimFacil();
        ~InimFacil() override;
        void executar() override;
        void salvar() override;
    };
}
