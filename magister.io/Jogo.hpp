#pragma once

#ifndef _JOGO_HPP_
#define _JOGO_HPP_

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"
#include "Menu.hpp"
#include <SFML/Graphics.hpp>

namespace Magisterio {

	class Jogo {
	 private:

		Gerenciadores::GerenciadorGrafico* pGG;
		bool menuAtivo;
		Entidades::Personagens::Jogador jogadorUm;
		Fases::FasePrimeira fase;
		Fases::FaseSegunda faseSegunda;
		Fases::Fase* faseAtual;
		sf::Clock relogio;
		Menu menu;

	 public:
		Jogo();
		~Jogo();

		void executar();
		const Entidades::Personagens::Jogador& getJogadorUm() const;
		const Fases::FasePrimeira& getFase() const;
		const Fases::FaseSegunda& getFaseSegunda() const;
	};
}
#endif