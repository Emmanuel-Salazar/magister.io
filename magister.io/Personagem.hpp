#pragma once

#include "Entidade.hpp"

namespace Magisterio {
    namespace Entidades {
        namespace Personagens {
            class Personagem : public Entidade 
            {
             protected:

                int numVidas;
                sf::CircleShape forma;

             public:

                Personagem();
                ~Personagem() override;

                virtual void executar() = 0;
                virtual void salvar() = 0;
                virtual void mover() = 0;
                virtual void atacar() = 0;

                void desenhar(sf::RenderTarget& destino) override;

                sf::Vector2f getPosicao() const;
                void setPosicao(sf::Vector2f posicao);

                float getRaio() const;

                int getNumVidas() const;
                void setNumVidas(int vidas);
            };
        }
    }
}