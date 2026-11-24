#include "FaseSegunda.hpp"
#include "GerenciadorGrafico.hpp"
#include "Plataforma.hpp"
#include "Lava.hpp"

using namespace Magisterio;
using namespace Fases;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Obstaculos;

FaseSegunda::FaseSegunda():
	maxSenhorTemebrosos (2),
	maxGoblins (rand() % 5 + 3)
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

FaseSegunda::~FaseSegunda() = default;

void FaseSegunda::executar() {
	gc.atualizar(entidades);
}

void FaseSegunda::criarObstaculos() {
	Plataforma* pPlataforma1 = new Plataforma(sf::Vector2f(360.f, 350.f));
	entidades.inserir(pPlataforma1);
	gc.incluirObstaculo(pPlataforma1);

	Lava* pLava1 = new Lava(sf::Vector2f(550.f, 450.f));
	entidades.inserir(pLava1);
	gc.incluirObstaculo(pLava1);
}

void FaseSegunda::criarInimigos() {}

