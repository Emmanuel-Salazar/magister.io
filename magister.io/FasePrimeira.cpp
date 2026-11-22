#include "FasePrimeira.hpp"
#include "GerenciadorGrafico.hpp"
#include "Plataforma.hpp"

using namespace Magisterio;
using namespace Fases;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Obstaculos;

FasePrimeira::FasePrimeira() :
	maxInimMedios(rand() % 2 + 3),
	maxInimFaceis(6)
{
	sf::Texture* pTexturaFundo = GerenciadorGrafico::getGerenciadorGrafico()->carregarTextura("assets/wallpaper_fases.png");
	if (pTexturaFundo) {
		figura = new sf::Sprite(*pTexturaFundo);
		float escalaX = 800.f / static_cast<float>(pTexturaFundo->getSize().x);
		float escalaY = 600.f / static_cast<float>(pTexturaFundo->getSize().y);
		figura->setScale({ escalaX, escalaY });
	}
	criarObstaculos();
}

FasePrimeira::~FasePrimeira() = default;

void FasePrimeira::executar() {
	criarCenario();
	gc.atualizar(entidades);
}

void FasePrimeira::criarObstaculos() {
	Plataforma* pPlataforma1 = new Plataforma(sf::Vector2f(360.f, 350.f));
	entidades.inserir(pPlataforma1);
}
void FasePrimeira::criarInimigos() {}

