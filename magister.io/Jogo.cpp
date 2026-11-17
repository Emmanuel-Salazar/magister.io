#include "Jogo.hpp"
#include <algorithm>

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;

Magisterio::Jogo::Jogo()
{
}

Magisterio::Jogo::~Jogo() = default;

void Magisterio::Jogo::executar()
{
	GerGrafico.executar();
}

Jogador& Magisterio::Jogo::getJogador()
{
	return jogador;
}

Fases::FasePrimeira& Magisterio::Jogo::getFase()
{
	return fase;
}
