#include "Entidade.hpp"

using namespace Magisterio;
using namespace Entidades;

Entidade::Entidade() : Ente()
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

sf::Vector2f Entidade::getCoordenada() const 
{
    return coordenada->getPosicao();
}

void Entidade::setCoordenada(sf::Vector2f novaCoordenada)
{
	coordenada->setPosicao(novaCoordenada);
}