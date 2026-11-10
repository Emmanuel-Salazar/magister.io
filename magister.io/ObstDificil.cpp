#include "ObstDificil.hpp"

namespace Entidades {
	ObstDificil::ObstDificil() : danosidade(1) {}
	ObstDificil::~ObstDificil() = default;
	bool ObstDificil::obstacular() { return true; }
	short ObstDificil::getDanosidade() const { return danosidade; }
	void ObstDificil::setDanosidade(short valor) { danosidade = valor; }
}
