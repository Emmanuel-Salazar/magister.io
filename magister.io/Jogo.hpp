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

		Gerenciadores::GerenciadorGrafico GerGrafico;
		Entidades::Personagens::Jogador* j1;
		Fases::FasePrimeira fase1;
		Fases::FaseSegunda fase2;

		Menu menu;
		bool menuAtivo;

	 public:
		Jogo();
		~Jogo();

		void executar();

		Entidades::Personagens::Jogador& getJogador();
		
	};
}
#endif