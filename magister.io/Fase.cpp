#include "Fase.hpp"

using namespace Magisterio;
using namespace Fases;

Fase::Fase(int numero) : Ente() {}
Fase::~Fase() = default;

void Fase::executar() {}

Listas::ListaEntidades& Fase::getEntidades() { return entidades; }

