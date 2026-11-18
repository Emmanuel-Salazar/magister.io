#pragma once

#ifndef _JOGO_HPP_
#define _JOGO_HPP_

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "FasePrimeira.hpp"
#include "Menu.hpp"
#include <SFML/Graphics.hpp>

namespace Magisterio {

	class Jogo {
	 private:

		Gerenciadores::GerenciadorGrafico* pGG;
		Entidades::Personagens::Jogador jogadorUm;
		Fases::FasePrimeira fase;
		sf::Clock relogio;
		Menu menu;
		bool menuAtivo;

	 public:
		Jogo();
		~Jogo();

		void executar();
		Entidades::Personagens::Jogador& getJogadorUm();
		Fases::FasePrimeira& getFase();
	};
}
#endif