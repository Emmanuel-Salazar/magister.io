#include "FasePrimeira.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Fases;
using namespace Gerenciadores;

FasePrimeira::FasePrimeira():
	maxInimMedios(3),
	maxInimFaceis(6)
{
	sf::Texture* pTexturaFundo = GerenciadorGrafico::getGerenciadorGrafico()->carregarTextura("assets/wallpaper_fase1.png");
}

FasePrimeira::~FasePrimeira() = default;

void FasePrimeira::criarObstaculos() {}
void FasePrimeira::criarInimigos() {}

