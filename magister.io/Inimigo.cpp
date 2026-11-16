#include "Inimigo.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;


Inimigo::Inimigo(int nivel) : nivelMaldade(nivel) {}

Inimigo::~Inimigo() = default;

int Inimigo::getNivelMaldade() const { return nivelMaldade; }

