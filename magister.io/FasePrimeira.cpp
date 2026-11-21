#include "FasePrimeira.hpp"
#include "GerenciadorGrafico.hpp"

using namespace Magisterio;
using namespace Fases;
using namespace Gerenciadores;

FasePrimeira::FasePrimeira() :
	maxInimMedios(3),
	maxInimFaceis(6)
{
	sf::Texture* pTexturaFundo = GerenciadorGrafico::getGerenciadorGrafico()->carregarTextura("assets/wallpaper_fases.png");
	if (pTexturaFundo) {
		figura = new sf::Sprite(*pTexturaFundo);
		float escalaX = 800.f / static_cast<float>(pTexturaFundo->getSize().x);
		float escalaY = 600.f / static_cast<float>(pTexturaFundo->getSize().y);
		figura->setScale({ escalaX, escalaY });
	}
}

FasePrimeira::~FasePrimeira() = default;

void FasePrimeira::executar() {
	criarCenario();
}

void FasePrimeira::criarObstaculos() {}
void FasePrimeira::criarInimigos() {}

