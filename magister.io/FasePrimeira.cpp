#include "FasePrimeira.hpp"
#include "GerenciadorGrafico.hpp"
#include "Gelo.hpp"
#include <cstdlib>

using namespace Magisterio;
using namespace Fases;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Obstaculos;

FasePrimeira::FasePrimeira() :
	maxGoblins(rand() % 2 + 3),
	maxEsqueletos(6),
	minGelo(3),
	maxGelo(5)
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

FasePrimeira::~FasePrimeira() = default;

void FasePrimeira::executar() {
	gc.atualizar(entidades);
}

void FasePrimeira::criarObstaculos() {
	int qntd = std::rand() % (maxGelo - minGelo + 1) + minGelo;
	Gelo medidaTemp;
	float alt = 14.f;
	if (medidaTemp.getFigura()) {
		alt = medidaTemp.getFigura()->getGlobalBounds().size.y;
	}

	std::vector<sf::Vector2f> posicoes = gerarPosicoesNoChao(qntd, alt);
	for (const auto& pos : posicoes) {
		Gelo* pGelo = new Gelo(pos);
		if (pGelo == nullptr) {
			cerr << "Tentativa de incluir gelo nulo na lista de entidades." << endl;
		}
		else {
			entidades.inserir(pGelo);
			gc.incluirObstaculo(pGelo);
		}
	}
}
void FasePrimeira::criarInimigos() {}

