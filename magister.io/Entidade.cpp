#include "Entidade.hpp"

using namespace Entidades;

Entidade::Entidade() {
    coordenada = new Coordenada();
    buffer = new ofstream();
}

Entidade::~Entidade() {
    delete coordenada;
    delete buffer;
}

