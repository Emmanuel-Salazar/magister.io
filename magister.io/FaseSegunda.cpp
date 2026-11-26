#include "FaseSegunda.hpp"
#include "GerenciadorGrafico.hpp"
#include "Lava.hpp"
#include "SenhorTemebroso.hpp"
#include "Goblin.hpp"
#include "Projetil.hpp"
#include <cstdlib>

using namespace Magisterio;
using namespace Fases;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

FaseSegunda::FaseSegunda():
	minSenhorTemebrosos(1),
	maxSenhorTemebrosos(1),
	minLava(3),
	maxLava(4)
{
	sf::Texture* pTexturaFundo = carregarTextura("assets/wallpaper_fases.png");
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

FaseSegunda::FaseSegunda(Jogador* pJog1, Jogador* pJog2):
	Fase(pJog1, pJog2),
	minSenhorTemebrosos(1),
	maxSenhorTemebrosos(1),
	minLava(3),
	maxLava(4)
{
	sf::Texture* pTexturaFundo = carregarTextura("assets/wallpaper_fases.png");
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

FaseSegunda::~FaseSegunda() = default;

void FaseSegunda::executar() {
	int tam = entidades.tamanho();
	for (int i = 0; i < tam; i++) {
		if (SenhorTemebroso* pMago = dynamic_cast<SenhorTemebroso*>(entidades[i])) {
			if (pMago->getNumVidas() > 0)
				pMago->setAlvo(obterAlvoMaisProximo(pMago->getCoordenada()));
		}
		else if (Goblin* pGoblin = dynamic_cast<Goblin*>(entidades[i])) {
			if (pGoblin->getNumVidas() > 0)
				pGoblin->setAlvo(obterAlvoMaisProximo(pGoblin->getCoordenada()));
		}
	}

	entidades.executar();

	tam = entidades.tamanho();
	for (int i = 0; i < tam; i++) {
		SenhorTemebroso* pMago = dynamic_cast<SenhorTemebroso*>(entidades[i]);
		if (pMago && pMago->getNumVidas() > 0) {
			if (Projetil* pProj = pMago->tentarDisparar(obterAlvoMaisProximo(pMago->getCoordenada()))) {
				incluirProjetil(pProj);
			}
		}
	}

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

//A partir de ajuda do inetgrante do PETECO João Pedro
void FaseSegunda::criarInimigos() {
	SenhorTemebroso* pMago = new SenhorTemebroso();
	if (pMago == nullptr) {
		cerr << "Tentativa de incluir mago tenebroso nulo na lista de entidades." << endl;
		return;
	}

	float larg = 90.f;
	float alt = 149.f;
	if (pMago->getFigura()) {
		sf::FloatRect bounds = pMago->getFigura()->getGlobalBounds();
		larg = bounds.size.x;
		alt = bounds.size.y;
	}

	float minX = 520.f;
	int faixaX = static_cast<int>(790.f - larg - minX);
	if (faixaX < 1) faixaX = 1;

	float posX = minX + static_cast<float>(std::rand() % faixaX);
	float posY = 585.f - alt;

	pMago->setCoordenada({ posX, posY });
	pMago->setLimitesPatrulha(10.f, 790.f);
	pMago->setAlvo(pJ1);
	entidades.inserir(pMago);
	gc.incluirInimigo(pMago);

	// Embaralha plataformas disponíveis para distribuir Goblins em plataformas e no chão
	std::vector<size_t> plataformasLivres;
	for (size_t idx = 0; idx < plataformasCriadas.size(); idx++) {
		plataformasLivres.push_back(idx);
	}
	for (int i = static_cast<int>(plataformasLivres.size()) - 1; i > 0; i--) {
		int j = std::rand() % (i + 1);
		std::swap(plataformasLivres[i], plataformasLivres[j]);
	}

	int maxG = (maxGoblins >= minGoblins) ? maxGoblins : minGoblins;
	int qntdGoblins = std::rand() % (maxG - minGoblins + 1) + minGoblins;
	int qntdEmPlataforma = qntdGoblins / 2;
	if (qntdEmPlataforma < 1 && !plataformasLivres.empty())
		qntdEmPlataforma = 1;

	for (int i = 0; i < qntdGoblins; i++) {
		Goblin* pGoblin = new Goblin();
		if (pGoblin == nullptr) {
			cerr << "Tentativa de incluir goblin nulo na lista de entidades." << endl;
		}
		else {
			bool colocarEmPlataforma = (i < qntdEmPlataforma);
			posicionarInimigo(pGoblin, colocarEmPlataforma, plataformasLivres);
			pGoblin->setAlvo(pJ1);
			entidades.inserir(pGoblin);
			gc.incluirInimigo(pGoblin);
		}
	}
}

