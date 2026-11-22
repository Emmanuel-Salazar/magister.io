#include "Entidade.hpp"

using namespace Magisterio;
using namespace Entidades;

Entidade::Entidade() : Ente()
{
    buffer = new ofstream();
}

Entidade::~Entidade()
{
    delete buffer;
}

sf::Sprite* Entidade::getSprite() const
{
    if(figura)
        return figura;
    return NULL;
}

void Entidade::salvarDataBuffer() {}

