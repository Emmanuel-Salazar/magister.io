#include "Jogo.hpp"
#include <algorithm>

#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Entidades;
using namespace Gerenciadores;
using namespace Personagens;

Magisterio::Jogo::Jogo():
	pGG(pGG->getGerenciadorGrafico())
{
}

Magisterio::Jogo::~Jogo() = default;

void Magisterio::Jogo::executar()
{
	sf::RenderWindow* janela = pGG->getJanela();
	while (pGG->getJanela()->isOpen())
	{
		pGG->processarEventos();
		pGG->atualizar(pGG->getRelogio()->restart().asSeconds());
		pGG->desenhar();
	}
}

Entidades::Personagens::Jogador& Magisterio::Jogo::getJogadorUm()
{
	return jogadorUm;
}

Fases::FasePrimeira& Magisterio::Jogo::getFase()
{
	return fase;
}
