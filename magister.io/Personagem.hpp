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
        virtual void mover(float, float);
        virtual void atacar() {}
        void executar() override;
        void salvar() override;
        void desenhar(sf::RenderTarget&) override;
        sf::Vector2f getPosicao() const { return forma.getPosition(); }
        void setPosicao(sf::Vector2f posicao) { forma.setPosition(posicao); }
        float getRaio() const { return forma.getRadius(); }
        int getNumVidas() const { return numVidas; }
        void setNumVidas(int vidas) { numVidas = vidas; }
    };

}
