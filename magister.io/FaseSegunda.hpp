#pragma once

#include "Fase.hpp"

namespace Fases {
    class FaseSegunda : public Fase {
    public:
        FaseSegunda();
        ~FaseSegunda() override;
        void criarObstaculos() override;
        void criarInimigos() override;
        void criarProjetis() override;
    };
}
