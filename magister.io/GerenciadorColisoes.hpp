#pragma once

#include "ListaEntidades.hpp"

namespace Entidades {
	class Jogador;
	class Obstaculo;
	class Projetil;
}

class GerenciadorColisoes {
public:
	GerenciadorColisoes();
	~GerenciadorColisoes();
	bool verificarColisao(const Entidades::Entidade* primeiro, const Entidades::Entidade* segundo) const;
	void tratarObstaculos(Entidades::Jogador* jogador, Entidades::Obstaculo* obstaculo);
	void tratarProjetil(Entidades::Jogador* jogador, Entidades::Projetil* projetil);
	void atualizar(Entidades::ListaEntidades& entidades);
};
