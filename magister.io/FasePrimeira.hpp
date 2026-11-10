#pragma once

#include "Fase.hpp"

namespace Fases {
    class FasePrimeira : public Fase {
    public:
        FasePrimeira();
        ~FasePrimeira() override;
        void criarObstaculos() override;
        void criarInimigos() override;
        void criarProjetis() override;
    };
}
