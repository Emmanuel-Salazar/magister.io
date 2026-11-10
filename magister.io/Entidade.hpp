#pragma once

#include "stdafx.hpp"
#include "Coordenada.hpp"
#include <SFML/Graphics.hpp>

namespace Entidades {
    class Entidade {
    protected:
        Coordenada* coordenada;
        ofstream* buffer;
        void salvarDataBuffer();

    public:
        Entidade();
        virtual ~Entidade();
        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void desenhar(sf::RenderTarget&) {}
        Coordenada* getCoordenada() const { return coordenada; }
    };
}
