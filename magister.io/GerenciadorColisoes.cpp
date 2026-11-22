#include "GerenciadorColisoes.hpp"

#include "ListaEntidades.hpp"
#include "Entidade.hpp"
#include "Jogador.hpp"
#include "Obstaculo.hpp"
#include "Inimigo.hpp"
#include "Projetil.hpp"

using namespace Magisterio;
using namespace Magisterio::Gerenciadores;
using namespace Magisterio::Entidades;
using namespace Magisterio::Entidades::Obstaculos;
using namespace Magisterio::Entidades::Personagens;
using namespace Magisterio::Listas;


GerenciadorColisoes::GerenciadorColisoes():
	pJogador1(NULL),
	pChao(NULL),
	limiteX(800.f),
	limiteY(585.f)
{

}
GerenciadorColisoes::~GerenciadorColisoes()
{
	LPs.clear();
	LIs.clear();
	LOs.clear();

	pJogador1 = NULL;
	pChao = NULL;
}

bool GerenciadorColisoes::verificarColisao(Entidade* primeiro, Entidade* segundo) const
{
	sf::Sprite* s1 = primeiro->getFigura();
	sf::Sprite* s2 = segundo->getFigura();
 
	if (s1 && s2 && s1->getGlobalBounds().findIntersection(s2->getGlobalBounds()))
	{
		return true;
	}
	return false;
}

void GerenciadorColisoes::tratarObstaculos(Jogador* jogador, Obstaculo* obstaculo) {}

void GerenciadorColisoes::tratarProjetil(Jogador* jogador, Projetil* projetil) {}

void GerenciadorColisoes::atualizar(ListaEntidades& entidades) 
{
	tratarLimites();
}

//incluir Entidades

void GerenciadorColisoes::incluirInimigo(Inimigo* pInimigo) 
{
	LIs.push_back(pInimigo);
}

void GerenciadorColisoes::incluirObstaculo(Obstaculo* pObstaculo) 
{
	LOs.push_back(pObstaculo);
}

void GerenciadorColisoes::incluirProjetil(Projetil* pProjetil)
{
	LPs.insert(pProjetil);
}

void GerenciadorColisoes::incluirChao(sf::RectangleShape* pChao)
{
	if (pChao == NULL)
		cerr << "Ponteiro Nulo." << endl;
	else
		this->pChao = pChao;
}

void GerenciadorColisoes::setJogador1(Jogador* pJ)
{
	if (pJ == NULL)
	{
		cerr << "Ponteiro Nulo" << endl;
		return;
	}
	else
	{
		pJogador1 = pJ;
		BoxJ1 = pJogador1->getFigura()->getGlobalBounds();
	}
}

void GerenciadorColisoes::tratarLimites()
{
	if (!pJogador1 || !pJogador1->getFigura())
	{
		return;
	}

	sf::Vector2f coord = pJogador1->getCoordenada();
	BoxJ1 = pJogador1->getFigura()->getGlobalBounds();
	int ajustou = 0;

	if (BoxJ1.position.y < 0)
	{
		ajustou++;
		coord.y -= BoxJ1.position.y;
	}
	if (BoxJ1.position.x < 0)
	{
		ajustou++;
		coord.x -= BoxJ1.position.x;
	}
	if (BoxJ1.position.y + BoxJ1.size.y > limiteY)
	{
		ajustou++;
		coord.y -= (BoxJ1.position.y + BoxJ1.size.y) - limiteY;
	}
	if (BoxJ1.position.x + BoxJ1.size.x > limiteX)
	{
		ajustou++;
		coord.x -= (BoxJ1.position.x + BoxJ1.size.x) - limiteX;
	}

	if(ajustou)
		pJogador1->setCoordenada(coord);
}