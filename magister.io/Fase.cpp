#include "Fase.hpp"

using namespace Magisterio;
using namespace Fases;
using namespace Entidades;
using namespace Personagens;
using namespace Listas;



Fase::Fase(Jogador* jg1):
	Ente(0),
	j1(jg1)
{
	entidades = new ListaEntidades();
	inicializaElementos();
}

void Fase::inicializaElementos()
{
	entidades->LEs.push(j1);
	criarObstaculos();
	criarInimigos();
	criarCenarios();
}

ListaEntidades* Fase::getEntidades() const 
{
	return entidades;
}

void Fase::executar() {}



