#include "ObstMedio.hpp"

namespace Magisterio::Entidades {
	ObstMedio::ObstMedio() : largura(0.0f) {}
	ObstMedio::~ObstMedio() = default;
	bool ObstMedio::obstacular() { return true; }
	float ObstMedio::getLargura() const { return largura; }
	void ObstMedio::setLargura(float valor) { largura = valor; }
}
