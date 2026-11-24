#pragma once

#ifndef _GERENCIADORCOLISOES_HPP_
#define _GERENCIADORCOLISOES_HPP_

#include <SFML/Graphics.hpp>

#include <set>
#include <list>
#include <vector>

namespace Magisterio::Listas
{
	class ListaEntidades;
}

namespace Magisterio::Entidades
{
	class Projetil;
	class Entidade;
}

namespace Magisterio::Entidades::Obstaculos
{
	class Obstaculo;
}

namespace Magisterio::Entidades::Personagens
{
	class Inimigo;
	class Jogador;
}

namespace Magisterio::Gerenciadores
{
	class GerenciadorColisoes
	{
	 private:

		 std::vector<Entidades::Personagens::Inimigo*> LIs;
		 std::list<Entidades::Obstaculos::Obstaculo*> LOs;
		 std::set<Entidades::Projetil*> LPs;
		 Entidades::Personagens::Jogador* pJogador1;
		 sf::FloatRect BoxJ1;

		 sf::RectangleShape* pChao;
		 const float limiteX;
		 const float limiteY;

		 bool verificarColisao(Entidades::Entidade* pPrimeiro, Entidades::Entidade* pSegundo) const;
		 void resolverColisaoSolida(Entidades::Personagens::Jogador* pJogador, Entidades::Obstaculos::Obstaculo* pObstaculo);
		 void tratarObstaculos(Entidades::Personagens::Jogador* pJogador, Entidades::Obstaculos::Obstaculo* pObstaculo);
		 void tratarInimigos(Entidades::Personagens::Jogador* pJogador, Entidades::Personagens::Inimigo* pInimigo);
		 void tratarProjetil(Entidades::Personagens::Jogador* pJogador, Entidades::Projetil* pProjetil);

		 void tratarLimites();

	 public:

		GerenciadorColisoes();
		~GerenciadorColisoes();

		void incluirInimigo(Entidades::Personagens::Inimigo* pInimigo);
		void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObstaculo);
		void incluirProjetil(Entidades::Projetil* pProjetil);
		void incluirChao(sf::RectangleShape* pChao);

		void setJogador1(Entidades::Personagens::Jogador* pJ);
		void limparObstaculos();
		void limparInimigos();

		void atualizar(Listas::ListaEntidades& entidades);
	};	
}
#endif