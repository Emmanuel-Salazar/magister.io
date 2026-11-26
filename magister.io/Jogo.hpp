#pragma once

#ifndef _JOGO_HPP_
#define _JOGO_HPP_

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"
#include "Menu.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace Magisterio {

	struct RegistroRanking {
		std::wstring descricao;
		int pontos;
	};

	class Jogo {
	 private:

		Gerenciadores::GerenciadorGrafico* pGG;
		bool menuAtivo;
		bool doisJogadores;
		int faseSelecionada;
		Entidades::Personagens::Jogador jogadorUm;
		Entidades::Personagens::Jogador jogadorDois;
		Fases::FasePrimeira fase;
		Fases::FaseSegunda faseSegunda;
		Fases::Fase* faseAtual;
		sf::Clock relogio;
		Menu menu;
		std::vector<RegistroRanking> ranking;

		void iniciarFase(int numFase, bool modoDoisJogadores);
		void registrarRanking();

	 public:
		Jogo();
		~Jogo();

		void executar();
		const Entidades::Personagens::Jogador& getJogadorUm() const;
		const Entidades::Personagens::Jogador& getJogadorDois() const;
		bool isDoisJogadores() const;
		int getPontosPartidaAtual() const;
		const std::vector<RegistroRanking>& getRanking() const;
		const Fases::FasePrimeira& getFase() const;
		const Fases::FaseSegunda& getFaseSegunda() const;
	};
}
#endif