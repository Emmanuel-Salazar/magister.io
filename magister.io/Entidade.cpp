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

