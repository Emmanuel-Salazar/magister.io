#include "Projetil.hpp"

namespace Magisterio::Entidades {
	Projetil::Projetil() : ativo(false) {}

	Projetil::~Projetil() = default;

	void Projetil::executar() {}

	void Projetil::salvar() {}

	void Projetil::lancar() { ativo = true; }

	bool Projetil::estaAtivo() const { return ativo; }
}
