#include "Plataforma.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Obstaculos;

Plataforma::Plataforma() : altura(0) {}
Plataforma::~Plataforma() = default;
bool Plataforma::obstacular() { return true; }
int Plataforma::getAltura() const { return altura; }
void Plataforma::setAltura(int valor) { altura = valor; }

