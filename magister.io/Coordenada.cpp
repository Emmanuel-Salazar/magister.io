#include "Coordenada.hpp"

namespace Magisterio {

    Coordenada::Coordenada() : posicao(0.0f, 0.0f) {
    }

    Coordenada::Coordenada(float x, float y) : posicao(x, y) {
    }

    sf::Vector2f Coordenada::getPosicao() const {
        return posicao;
    }

    void Coordenada::setPosicao(sf::Vector2f novaPosicao) {
        posicao = novaPosicao;
    }

    Coordenada::~Coordenada() {
    }

} 