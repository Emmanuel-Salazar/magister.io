#include "GerenciadorColisoes.hpp"
#include <algorithm>
#include <iostream>

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

void GerenciadorColisoes::tratarObstaculos(Jogador* jogador, Obstaculo* obstaculo) 
{
	if (jogador && obstaculo)
	{
		obstaculo->obstaculizar(jogador);
	}
}

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

	std::cout << "[Mago Tenebroso] Bola de fogo atingiu o jogador (-" << dano
	          << " vidas)! Vidas restantes: " << jogador->getNumVidas() << std::endl;
}

void GerenciadorColisoes::atualizar(ListaEntidades& entidades) 
{
	if (pJogador1)
	{
		pJogador1->setNoChao(false);
		pJogador1->resetarVelocidade();
	}

	tratarLimites();

	if (pJogador1) 
	{
		std::set<Obstaculo*> obstaculosProcessados;

		for (auto* pObst : LOs) 
		{
			if (pObst && verificarColisao(pJogador1, pObst)) 
			{
				resolverColisaoSolida(pJogador1, pObst);
				tratarObstaculos(pJogador1, pObst);
				obstaculosProcessados.insert(pObst);
			}
		}

		int tam = entidades.tamanho();
		for (int i = 0; i < tam; i++) 
		{
			Obstaculo* pObst = dynamic_cast<Obstaculo*>(entidades[i]);
			if (pObst && obstaculosProcessados.find(pObst) == obstaculosProcessados.end()) 
			{
				if (verificarColisao(pJogador1, pObst)) 
				{
					resolverColisaoSolida(pJogador1, pObst);
					tratarObstaculos(pJogador1, pObst);
				}
			}
		}

		for (auto* pInim : LIs)
		{
			if (pInim && pInim->getNumVidas() > 0 && verificarColisao(pJogador1, pInim))
			{
				tratarInimigos(pJogador1, pInim);
			}
		}

		// Colisão de projéteis do jogador com inimigos
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

			if (pProj->ehDoJogador())
			{
				for (auto* pInim : LIs)
				{
					if (pInim && pInim->getNumVidas() > 0 && verificarColisao(pProj, pInim))
					{
						(*pInim)--;
						pProj->desativar();
						projeteisRemover.push_back(pProj);

						std::cout << "[Combate] Inimigo atingido! Vidas restantes: "
						          << pInim->getNumVidas() << std::endl;

						if (pInim->getNumVidas() <= 0)
						{
							pJogador1->addPontos(pInim->getNivelMaldade() * 10);
							inimigosRemover.push_back(pInim);
						}
						break;
					}
				}
			}
			else
			{
				if (verificarColisao(pProj, pJogador1))
				{
					tratarProjetil(pJogador1, pProj);
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
		if (pJogador1->getVelY() < 0.f)
			pJogador1->setVelY(0.f);
	}
	if (BoxJ1.position.x < 0)
	{
		ajustou++;
		coord.x -= BoxJ1.position.x;
	}
	if (BoxJ1.position.y + BoxJ1.size.y >= limiteY)
	{
		ajustou++;
		coord.y -= (BoxJ1.position.y + BoxJ1.size.y) - limiteY;
		if (pJogador1->getVelY() >= 0.f)
		{
			pJogador1->setVelY(0.f);
			pJogador1->setNoChao(true);
		}
	}
	if (BoxJ1.position.x + BoxJ1.size.x > limiteX)
	{
		ajustou++;
		coord.x -= (BoxJ1.position.x + BoxJ1.size.x) - limiteX;
	}

	if(ajustou)
		pJogador1->setCoordenada(coord);
}