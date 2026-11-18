#pragma once

#ifndef GERENCIADOR_GRAFICO_HPP_
#define GERENCIADOR_GRAFICO_HPP_

#include "stdafx.hpp"

#include "Jogador.hpp"
#include "Menu.hpp"
#include "Ente.hpp"

namespace Magisterio::Gerenciadores {

	class GerenciadorGrafico {

	 private:
		sf::RenderWindow janela;
		static GerenciadorGrafico* pGrafico;
		std::map<std::string, sf::Texture*> mapaTexturas;

	 public:
		 GerenciadorGrafico();
		 ~GerenciadorGrafico();
		 sf::RenderWindow* getJanela() { return &janela; }
		 static GerenciadorGrafico* getGerenciadorGrafico();
		 static void destruirGGrafico();
		 void desenharEnte(Magisterio::Ente* pE);
		 sf::Texture* carregarTextura(const std::string& caminho);
	};
}

#endif