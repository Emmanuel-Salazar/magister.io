#include "FasePrimeira.hpp"
#include "GerenciadorGrafico.hpp"
#include "Gelo.hpp"
#include "Esqueleto.hpp"
#include <cstdlib>

using namespace Magisterio;
using namespace Fases;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

FasePrimeira::FasePrimeira() :
	maxGoblins(rand() % 2 + 3),
	minEsqueletos(3),
	maxEsqueletos(5),
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
	criarInimigos();
}

FasePrimeira::~FasePrimeira() = default;

void FasePrimeira::executar() {
	entidades.executar();
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
void FasePrimeira::criarInimigos() {
	int qntd = std::rand() % (maxEsqueletos - minEsqueletos + 1) + minEsqueletos;

	// Embaralha os índices das plataformas disponíveis para distribuir inimigos sem repetir
	std::vector<size_t> plataformasLivres;
	for (size_t idx = 0; idx < plataformasCriadas.size(); idx++) {
		plataformasLivres.push_back(idx);
	}
	for (int i = static_cast<int>(plataformasLivres.size()) - 1; i > 0; i--) {
		int j = std::rand() % (i + 1);
		std::swap(plataformasLivres[i], plataformasLivres[j]);
	}

	// Coloca cerca de metade dos esqueletos em plataformas e o restante no chão
	int qntdEmPlataforma = qntd / 2;
	if (qntdEmPlataforma < 1 && !plataformasLivres.empty())
		qntdEmPlataforma = 1;

	for (int i = 0; i < qntd; i++) {
		Esqueleto* pEsq = new Esqueleto();
		if (pEsq == nullptr) {
			cerr << "Tentativa de incluir esqueleto nulo na lista de entidades." << endl;
		}
		else {
			bool colocarEmPlataforma = (i < qntdEmPlataforma);
			posicionarInimigo(pEsq, colocarEmPlataforma, plataformasLivres);
			entidades.inserir(pEsq);
			gc.incluirInimigo(pEsq);
		}
	}
}

