#include "Obstaculo.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Obstaculos;

Obstaculo::Obstaculo() : danoso(false), solido(true) {}

Obstaculo::~Obstaculo() = default;

void Obstaculo::executar() {
	if (figura)
		figura->setPosition(coordenada.getPosicao());
}

void Obstaculo::salvar() {}

bool Obstaculo::getDanoso() const {
	return danoso;
}

bool Obstaculo::getSolido() const {
	return solido;
}
