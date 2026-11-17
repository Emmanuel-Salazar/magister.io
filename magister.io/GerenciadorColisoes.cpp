#include "GerenciadorColisoes.hpp"

using namespace Magisterio;
using namespace Gerenciadores;
using namespace Listas;
using namespace Entidades;

GerenciadorColisoes::GerenciadorColisoes() = default;
GerenciadorColisoes::~GerenciadorColisoes() = default;

bool GerenciadorColisoes::verificarColisao(const Entidade* primeiro, const Entidade* segundo) const
{
	return false;
}
void GerenciadorColisoes::tratarObstaculos(Jogador* jogador, Obstaculo* obstaculo) {}
void GerenciadorColisoes::tratarProjetil(Jogador* jogador, Projetil* projetil) {}
void GerenciadorColisoes::atualizar(ListaEntidades& entidades) {}

void GerenciadorColisoes::incluirInimigo(Inimigo* pInimigo) {}
void GerenciadorColisoes::incluirObstaculo(Obstaculo* pObstaculo) {}
void GerenciadorColisoes::incluirProjetil(Projetil* pProjetil) {}