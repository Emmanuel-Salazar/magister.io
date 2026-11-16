#include "Plataforma.hpp"

namespace Magisterio::Entidades {
	Plataforma::Plataforma() : altura(0) {}
	Plataforma::~Plataforma() = default;
	bool Plataforma::obstacular() { return true; }
	int Plataforma::getAltura() const { return altura; }
	void Plataforma::setAltura(int valor) { altura = valor; }
}
