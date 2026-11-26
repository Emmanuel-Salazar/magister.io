#include "GerenciadorColisoes.hpp"
#include <algorithm>
#include <iostream>

#include "ListaEntidades.hpp"
#include "Entidade.hpp"
#include "Jogador.hpp"
#include "Obstaculo.hpp"
#include "Inimigo.hpp"
#include "Goblin.hpp"
#include "Projetil.hpp"

using namespace Magisterio;
using namespace Magisterio::Gerenciadores;
using namespace Magisterio::Entidades;
using namespace Magisterio::Entidades::Obstaculos;
using namespace Magisterio::Entidades::Personagens;
using namespace Magisterio::Listas;


GerenciadorColisoes::GerenciadorColisoes():
	pJogador1(NULL),
	pJogador2(NULL),
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
	pJogador2 = NULL;
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

void GerenciadorColisoes::tratarObstaculos(Jogador* jogador, Obstaculo* obstaculo) 
{
	if (jogador && obstaculo)
	{
		obstaculo->obstaculizar(jogador);
	}
}

//codigo de integrantes do PETECO
void GerenciadorColisoes::resolverColisaoSolida(Jogador* jogador, Obstaculo* obstaculo)
{
	if (!jogador || !obstaculo) return;
	if (!obstaculo->getSolido()) return;

	sf::Sprite* sJ = jogador->getFigura();
	sf::Sprite* sO = obstaculo->getFigura();
	if (!sJ || !sO) return;

	sf::FloatRect bJ = sJ->getGlobalBounds();
	sf::FloatRect bO = sO->getGlobalBounds();

	auto inter = bJ.findIntersection(bO);
	if (!inter) return;

	float overlapX = inter->size.x;
	float overlapY = inter->size.y;

	sf::Vector2f pos = jogador->getCoordenada();

	if (overlapX < overlapY)
	{
		if (bJ.position.x < bO.position.x)
			pos.x -= overlapX;
		else
			pos.x += overlapX; 
	}
	else
	{
		if (bJ.position.y < bO.position.y)
		{
			pos.y -= overlapY;
			if (jogador->getVelY() >= 0.f)
			{
				jogador->setVelY(0.f);
				jogador->setNoChao(true);
			}
		}
		else
		{
			pos.y += overlapY;
			if (jogador->getVelY() < 0.f)
			{
				jogador->setVelY(0.f);
			}
		}
	}

	jogador->setCoordenada(pos);
}

void GerenciadorColisoes::tratarInimigos(Jogador* jogador, Inimigo* inimigo)
{
	if (jogador && inimigo)
	{
		inimigo->danificar(jogador);
	}
}

void GerenciadorColisoes::tratarProjetil(Jogador* jogador, Projetil* projetil)
{
	if (!jogador || !projetil)
		return;

	int dano = projetil->getDano();
	for (int i = 0; i < dano; i++)
	{
		(*jogador)--;
	}
	projetil->desativar();

}

void GerenciadorColisoes::atualizarJogador(Jogador* pJogador, ListaEntidades& entidades)
{
	if (!pJogador || pJogador->getNumVidas() <= 0)
		return;

	pJogador->setNoChao(false);
	pJogador->resetarVelocidade();

	tratarLimites(pJogador);

	std::set<Obstaculo*> obstaculosProcessados;

	for (auto* pObst : LOs)
	{
		if (pObst && verificarColisao(pJogador, pObst))
		{
			resolverColisaoSolida(pJogador, pObst);
			tratarObstaculos(pJogador, pObst);
			obstaculosProcessados.insert(pObst);
		}
	}

	int tam = entidades.tamanho();
	for (int i = 0; i < tam; i++)
	{
		Obstaculo* pObst = dynamic_cast<Obstaculo*>(entidades[i]);
		if (pObst && obstaculosProcessados.find(pObst) == obstaculosProcessados.end())
		{
			if (verificarColisao(pJogador, pObst))
			{
				resolverColisaoSolida(pJogador, pObst);
				tratarObstaculos(pJogador, pObst);
			}
		}
	}

	for (auto* pInim : LIs)
	{
		if (pInim && pInim->getNumVidas() > 0 && verificarColisao(pJogador, pInim))
		{
			tratarInimigos(pJogador, pInim);
		}
	}
}

//atraves de ajuda do monitor Pedro
void GerenciadorColisoes::atualizar(ListaEntidades& entidades) 
{
	atualizarJogador(pJogador1, entidades);
	atualizarJogador(pJogador2, entidades);

	for (auto* pInim : LIs)
	{
		if (!pInim || pInim->getNumVidas() <= 0)
			continue;

		if (Goblin* pGoblin = dynamic_cast<Goblin*>(pInim))
		{
			for (auto* pObst : LOs)
			{
				if (pObst && pObst->getSolido() && verificarColisao(pGoblin, pObst))
				{
					sf::Sprite* sG = pGoblin->getFigura();
					sf::Sprite* sO = pObst->getFigura();
					if (sG && sO)
					{
						sf::FloatRect bG = sG->getGlobalBounds();
						sf::FloatRect bO = sO->getGlobalBounds();
						auto inter = bG.findIntersection(bO);
						if (inter && inter->size.y <= inter->size.x && bG.position.y < bO.position.y && pGoblin->getVelY() >= 0.f)
						{
							sf::Vector2f pos = pGoblin->getCoordenada();
							pos.y -= inter->size.y;
							pGoblin->setCoordenada(pos);
							pGoblin->setVelY(0.f);
						}
					}
				}
			}
		}
	}

	// Colisão de projéteis (plataformas, inimigos e jogadores)
	std::vector<Projetil*> projeteisRemover;
	std::vector<Inimigo*> inimigosRemover;

	for (auto* pProj : LPs)
	{
		if (!pProj || !pProj->estaAtivo())
		{
			if (pProj)
				projeteisRemover.push_back(pProj);
			continue;
		}

		// Projéteis colidem e são destruídos ao atingir obstáculos sólidos (plataformas)
		bool atingiuObstaculo = false;
		for (auto* pObst : LOs)
		{
			if (pObst && pObst->getSolido() && verificarColisao(pProj, pObst))
			{
				pProj->desativar();
				projeteisRemover.push_back(pProj);
				atingiuObstaculo = true;
				break;
			}
		}
		if (atingiuObstaculo)
			continue;

		if (pProj->ehDoJogador())
		{
			for (auto* pInim : LIs)
			{
				if (pInim && pInim->getNumVidas() > 0 && verificarColisao(pProj, pInim))
				{
					(*pInim)--;
					pProj->desativar();
					projeteisRemover.push_back(pProj);

					if (pInim->getNumVidas() <= 0)
					{
						Jogador* pDono = pProj->getDono() ? pProj->getDono() : pJogador1;
						if (pDono)
							pDono->addPontos(pInim->getNivelMaldade() * 10);
						inimigosRemover.push_back(pInim);
					}
					break;
				}
			}
		}
		else
		{
			if (pJogador1 && pJogador1->getNumVidas() > 0 && verificarColisao(pProj, pJogador1))
			{
				tratarProjetil(pJogador1, pProj);
				projeteisRemover.push_back(pProj);
			}
			else if (pJogador2 && pJogador2->getNumVidas() > 0 && verificarColisao(pProj, pJogador2))
			{
				tratarProjetil(pJogador2, pProj);
				projeteisRemover.push_back(pProj);
			}
		}
	}

	for (auto* pProj : projeteisRemover)
	{
		LPs.erase(pProj);
		entidades.remover(pProj);
		delete pProj;
	}

	for (auto* pInim : inimigosRemover)
	{
		LIs.erase(std::remove(LIs.begin(), LIs.end(), pInim), LIs.end());
		entidades.remover(pInim);
		delete pInim;
	}
}

void GerenciadorColisoes::incluirInimigo(Inimigo* pInimigo) 
{
	LIs.push_back(pInimigo);
}

void GerenciadorColisoes::incluirObstaculo(Obstaculo* pObstaculo) 
{
	LOs.push_back(pObstaculo);
}

void GerenciadorColisoes::limparObstaculos()
{
	LOs.clear();
}

void GerenciadorColisoes::limparInimigos()
{
	LIs.clear();
}

void GerenciadorColisoes::limparProjeteis()
{
	LPs.clear();
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
	pJogador1 = pJ;
	if (pJogador1 && pJogador1->getFigura())
		BoxJ1 = pJogador1->getFigura()->getGlobalBounds();
}

void GerenciadorColisoes::setJogador2(Jogador* pJ)
{
	pJogador2 = pJ;
}

//a partir de codigo do monitor Giovanni
void GerenciadorColisoes::tratarLimites(Jogador* pJogador)
{
	if (!pJogador || !pJogador->getFigura())
	{
		return;
	}

	sf::Vector2f coord = pJogador->getCoordenada();
	sf::FloatRect box = pJogador->getFigura()->getGlobalBounds();
	int ajustou = 0;

	if (box.position.y < 0)
	{
		ajustou++;
		coord.y -= box.position.y;
		if (pJogador->getVelY() < 0.f)
			pJogador->setVelY(0.f);
	}
	if (box.position.x < 0)
	{
		ajustou++;
		coord.x -= box.position.x;
	}
	if (box.position.y + box.size.y >= limiteY)
	{
		ajustou++;
		coord.y -= (box.position.y + box.size.y) - limiteY;
		if (pJogador->getVelY() >= 0.f)
		{
			pJogador->setVelY(0.f);
			pJogador->setNoChao(true);
		}
	}
	if (box.position.x + box.size.x > limiteX)
	{
		ajustou++;
		coord.x -= (box.position.x + box.size.x) - limiteX;
	}

	if (ajustou)
		pJogador->setCoordenada(coord);
}