#pragma once

#ifndef _GERENCIADORCOLISOES_HPP_
#define _GERENCIADORCOLISOES_HPP_

#include "ListaEntidades.hpp"
#include "Entidade.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Projetil.hpp"
#include <set>

namespace Magisterio::Gerenciadores{

	class Jogador;
	class Inimigo;
	class Obstaculo;
	class Projetil;

	class GerenciadorColisoes
	{
	 private:

		 std::vector<Inimigo*> LIs;
		 std::list<Obstaculo*> LOs;
		 std::set<Projetil*> LPs;
		 Jogador* pJog1;

		 bool verificarColisao(const Entidades::Entidade* pPrimeiro, const Entidades::Entidade* pSegundo) const;
		 void tratarObstaculos(Jogador* pJogador, Obstaculo* pObstaculo);
		 void tratarInimigos(Jogador* pJogador, Inimigo* pInimigo);
		 void tratarProjetil(Jogador* pJogador, Projetil* pProjetil);

	 public:

		GerenciadorColisoes();
		~GerenciadorColisoes();

		void incluirInimigo(Inimigo* pInimigo);
		void incluirObstaculo(Obstaculo* pObstaculo);
		void incluirProjetil(Projetil* pProjetil);

		void atualizar(Listas::ListaEntidades& entidades);
	};	
}
#endif