#include "GerenciadorColisoes.hpp"

using namespace Magisterio;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Personagens;



GerenciadorColisoes() = default;
~GerenciadorColisoes() = default;

bool verificarColisao(const Entidade* primeiro, const Entidade* segundo) const
{
	return false;
}

void tratarObstaculos(Jogador* jogador, Obstaculo* obstaculo) {}
void tratarProjetil(Jogador* jogador, Projetil* projetil) {}
void atualizar(ListaEntidades& entidades) {}
