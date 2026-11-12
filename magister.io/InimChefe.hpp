#pragma once

#include "Inimigo.hpp"

namespace Magisterio {
    namespace Entidades {
        class InimChefe : public Inimigo {
        private:
            short forca;

        public:
            InimChefe();
            ~InimChefe() override;
            void executar() override;
            void salvar() override;
            short getForca() const;
        };
    }
}