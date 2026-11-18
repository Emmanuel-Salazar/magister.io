#include "Jogo.hpp"
#include "Ente.hpp"
#include <algorithm>

using namespace Magisterio;
using namespace Entidades;
using namespace Personagens;
 

Magisterio::Jogo::Jogo()
{
	Ente::setGG(&GerGrafico);
	j1 = new Jogador();

}

Magisterio::Jogo::~Jogo() = default;

void Magisterio::Jogo::executar()
{
	GerGrafico.executar();
}