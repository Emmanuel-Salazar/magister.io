#include "Entidade.hpp"

using namespace Magisterio;
using namespace Entidades;

Entidade::Entidade() : Ente(0)
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

void Entidade::desenhar(sf::RenderTarget& destino)
{
    destino.draw(forma);
}

Coordenada* Entidade::getCoordenada() const 
{
    return coordenada;
}