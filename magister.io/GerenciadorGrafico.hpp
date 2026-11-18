#pragma once

#ifndef GERENCIADOR_GRAFICO_HPP_
#define GERENCIADOR_GRAFICO_HPP_

#include "stdafx.hpp"

#include "Jogador.hpp"
#include "Menu.hpp"

namespace Magisterio::Gerenciadores {

	class GerenciadorGrafico {

	 private:
		sf::RenderWindow janela;
		static GerenciadorGrafico* pGrafico;

	 public:
		GerenciadorGrafico();
		~GerenciadorGrafico();
		sf::RenderWindow* getJanela() { return &janela; }
		GerenciadorGrafico* getGerenciadorGrafico();
		static void destruirGGrafico();
	};
}

#endif