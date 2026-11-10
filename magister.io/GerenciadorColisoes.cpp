#include "GerenciadorColisoes.hpp"

GerenciadorColisoes::GerenciadorColisoes() = default;
GerenciadorColisoes::~GerenciadorColisoes() = default;

bool GerenciadorColisoes::verificarColisao(const Entidades::Entidade*, const Entidades::Entidade*) const
{
	return false;
}

void GerenciadorColisoes::tratarObstaculos(Entidades::Jogador*, Entidades::Obstaculo*) {}
void GerenciadorColisoes::tratarProjetil(Entidades::Jogador*, Entidades::Projetil*) {}
void GerenciadorColisoes::atualizar(Entidades::ListaEntidades&) {}
