#include "Inimigo.hpp"

namespace Magisterio::Entidades {
	Inimigo::Inimigo(int nivel) : nivelMaldade(nivel) {}

	Inimigo::~Inimigo() = default;

	void Inimigo::perseguir() {}

	int Inimigo::getNivelMaldade() const { return nivelMaldade; }
}
