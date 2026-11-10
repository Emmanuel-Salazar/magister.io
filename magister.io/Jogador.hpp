#pragma once

#include "Personagem.hpp"

namespace Entidades {
    class Jogador : public Personagem {
    private:
        int pontos;

    public:
        Jogador();
        ~Jogador() override;
        void mover(float deslocamentoX, float deslocamentoY) override;
        void atacar() override;
        void executar() override;
        void salvar() override;
        void adicionarPontos(int valor);
        int getPontos() const;
    };
}
