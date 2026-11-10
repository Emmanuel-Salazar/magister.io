#pragma once

#include "ListaEntidades.hpp"

namespace Entidades {
	class Jogador;
	class Obstaculo;
	class Projetil;
}

class GerenciadorColisoes {
public:
	GerenciadorColisoes() = default;
	~GerenciadorColisoes() = default;

	bool verificarColisao(const Entidades::Entidade*, const Entidades::Entidade*) const { return false; }
	void tratarObstaculos(Entidades::Jogador*, Entidades::Obstaculo*) {}
	void tratarProjetil(Entidades::Jogador*, Entidades::Projetil*) {}
	void atualizar(Entidades::ListaEntidades&) {}
};
