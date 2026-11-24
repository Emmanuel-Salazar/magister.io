#include "FaseSegunda.hpp"
#include "GerenciadorGrafico.hpp"
#include "Lava.hpp"
#include <cstdlib>

using namespace Magisterio;
using namespace Fases;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Obstaculos;

FaseSegunda::FaseSegunda():
	maxSenhorTemebrosos (2),
	maxGoblins (rand() % 5 + 3),
	minLava(3),
	maxLava(4)
{
	sf::Texture* pTexturaFundo = GerenciadorGrafico::getGerenciadorGrafico()->carregarTextura("assets/wallpaper_fases.png");
	if (pTexturaFundo) {
		figura = new sf::Sprite(*pTexturaFundo);
		float escalaX = 800.f / static_cast<float>(pTexturaFundo->getSize().x);
		float escalaY = 600.f / static_cast<float>(pTexturaFundo->getSize().y);
		figura->setScale({ escalaX, escalaY });
	}
	criarPlataformas();
	criarObstaculos();
}

FaseSegunda::~FaseSegunda() = default;

void FaseSegunda::executar() {
	entidades.executar();
	gc.atualizar(entidades);
}

void FaseSegunda::criarObstaculos() {
	int qntd = std::rand() % (maxLava - minLava + 1) + minLava;
	Lava medidaTemp;
	float alt = 14.f;
	if (medidaTemp.getFigura()) {
		alt = medidaTemp.getFigura()->getGlobalBounds().size.y;
	}

	std::vector<sf::Vector2f> posicoes = gerarPosicoesNoChao(qntd, alt);
	for (const auto& pos : posicoes) {
		Lava* pLava = new Lava(pos);
		if (pLava == nullptr) {
			cerr << "Tentativa de incluir lava nula na lista de entidades." << endl;
		}
		else {
			entidades.inserir(pLava);
			gc.incluirObstaculo(pLava);
		}
	}
}

void FaseSegunda::criarInimigos() {}

