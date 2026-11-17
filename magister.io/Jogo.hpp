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

		Gerenciadores::GerenciadorGrafico GerGrafico;
		Entidades::Personagens::Jogador jogador;
		Fases::FasePrimeira fase;

		Menu menu;
		bool menuAtivo;

	 public:
		Jogo();
		~Jogo();

		void executar();
		Entidades::Personagens::Jogador& getJogador();
		Fases::FasePrimeira& getFase();
	};
}
#endif