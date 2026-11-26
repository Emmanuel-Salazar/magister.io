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

void Entidade::salvarDataBuffer() {}

