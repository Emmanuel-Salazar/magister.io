#include "Entidade.hpp"

using namespace Entidades;

Entidade::Entidade() {
    coordenada = new Coordenada();
    buffer = new ofstream();
}

void Entidade::salvarDataBuffer() {}

void Entidade::desenhar(sf::RenderTarget&) {}

Coordenada* Entidade::getCoordenada() const {
    return coordenada;
}

Entidade::~Entidade() {
    delete coordenada;
    delete buffer;
}

