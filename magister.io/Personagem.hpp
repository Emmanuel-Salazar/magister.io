#pragma once

#include "Entidade.hpp"

namespace Entidades {
    class Personagem : public Entidade {
    protected:
        int numVidas;
        sf::CircleShape forma;

    public:
        Personagem();
        ~Personagem() override;
        virtual void mover(float deslocamentoX, float deslocamentoY);
        virtual void atacar();
        void executar() override;
        void salvar() override;
        void desenhar(sf::RenderTarget& destino) override;
        sf::Vector2f getPosicao() const;
        void setPosicao(sf::Vector2f posicao);
        float getRaio() const;
        int getNumVidas() const;
        void setNumVidas(int vidas);
    };
}
