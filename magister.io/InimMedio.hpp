#pragma once

#include "Inimigo.hpp"

namespace Magisterio {
    namespace Entidades {
        class InimMedio : public Inimigo {
        public:
            InimMedio();
            ~InimMedio() override;
            void executar() override;
            void salvar() override;
        };
    }
}