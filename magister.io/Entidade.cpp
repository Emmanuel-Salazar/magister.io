#include "Entidade.hpp"

using namespace Magisterio;
using namespace Entidades;

Entidade::Entidade() 
{
    coordenada = new Coordenada();
    buffer = new ofstream();
}

Entidade::~Entidade()
{
    delete coordenada;
    delete buffer;
}

void Entidade::salvarDataBuffer() {}

void Entidade::desenhar(sf::RenderTarget&) {}

Coordenada* Entidade::getCoordenada() const 
{
    return coordenada;
}