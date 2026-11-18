#include "GerenciadorGrafico.hpp"


using namespace Magisterio;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Personagens;

GerenciadorGrafico* GerenciadorGrafico::pGrafico = nullptr;

GerenciadorGrafico* pGrafico = NULL;

GerenciadorGrafico::GerenciadorGrafico()
{
	janela.create(sf::VideoMode({ 800, 600 }), "Magister.io - Setas: selecionar | Enter: jogar | Esc: sair");
}

GerenciadorGrafico::~GerenciadorGrafico(){}

void GerenciadorGrafico::destruirGGrafico()
{
	if (pGrafico != NULL)
	{
		delete pGrafico;
		pGrafico = NULL;
	}
}

GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico()
{
	if (pGrafico == NULL)
	{
		pGrafico = new GerenciadorGrafico();
		std::atexit(destruirGGrafico);
	}

	return pGrafico;
}

