#include "Obstaculo.hpp"

namespace Entidades {
	Obstaculo::Obstaculo() : dano(0) {}

	Obstaculo::~Obstaculo() = default;

	void Obstaculo::executar() {}

	void Obstaculo::salvar() {}

	int Obstaculo::getDano() const { return dano; }

	void Obstaculo::setDano(int valor) { dano = valor; }
}
